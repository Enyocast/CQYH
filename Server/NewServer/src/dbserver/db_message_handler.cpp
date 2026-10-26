#include "stdafx.h"
#include "db_message_handler.h"

#include "time_ex.h"
#include "statis_info.h"

#include "role_db_def.h"
#include "server_config.h"
#include "dbserver.h"
#include "db_session_mgr.h"
#include "d2m_message.h"
#include "m2d_message.h"
#include "d2g_message.h"
#include "g2d_message.h"
#include "d2t_message.h"
#include "t2d_message.h"
#include "common_message.h"
#include <time.h>
#include "dump.h"
#include "report.h"

using namespace InternalMessage;
CDBMessageHandler CDBMessageHandler::ms_Instance;

UINT32 hash(const char* str)
{
    UINT32 res = 0;
    while(*str)
        res += (*str++);
    return res;
}

void CDBMessageHandler::OnAccepted(ISocketAcceptor* pSocketAcceptor, ISocketSession* pSocketSession)
{
    //DB_BASE_SESSION* pBaseSession = NULL;

    LOG_PROCESS_ERROR(pSocketSession);

    LOG_PROCESS_ERROR(CDBSessionMgr::GetInstance().GetServerState() != sgsClosing);

    return;
Exit0:
    if (pSocketSession)
        pSocketSession->Close();

    return;
}

void CDBMessageHandler::OnConnected(ISocketSession* pSocketSession)
{
    INT32 nRetCode = 0;
    DB_BASE_SESSION* pBaseSession = NULL;

    LOG_PROCESS_ERROR(pSocketSession);

    pBaseSession = (DB_BASE_SESSION*)pSocketSession->GetUserData();
    LOG_PROCESS_ERROR(pBaseSession);

    pBaseSession->qwTimer = GetTickCountEx() + g_ServerConfig.Common.nServerPingTimeout;;

    switch (pBaseSession->dwType)
    {
    case stGD:
        {
            GD_SESSION* pGDSession = (GD_SESSION*)pBaseSession;
            pGDSession->bConnected = true;
			pGDSession->qwTimer = GetTickCountEx() + g_ServerConfig.Common.nRegisterGuardTimeout;

            if(CDBSessionMgr::GetInstance().GetServerState() == sgsSelfReady || 
                CDBSessionMgr::GetInstance().GetServerState() == sgsAllReady)
            {
                nRetCode = DoGDRegister();
                LOG_PROCESS_ERROR(nRetCode);
            }
        }
        break;
    case stMS:
        {
            MS_SESSION* pMSSession = (MS_SESSION*)pBaseSession;
            pMSSession->bConnected = true;

			nRetCode = GetIp(g_ServerConfig.Common.szIntranetAddr, g_ServerConfig.Common.szIntranetMask, TRUE, 0);
            LOG_PROCESS_ERROR(nRetCode);

            nRetCode = DoMSRegister(nRetCode, g_ServerConfig.DB.dwPort);
            LOG_PROCESS_ERROR(nRetCode);
        }
        break;
    case stGS:
    case stGT:
    default:
        LOG_PROCESS_ERROR(FALSE);
        break;
    }

    return;
Exit0:
    if (pSocketSession)
        pSocketSession->Close();

    return;
}

void CDBMessageHandler::OnRecv(ISocketSession* pSocketSession, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize)
{
    MESSAGE_HEADER* pHeader = (MESSAGE_HEADER*)pPacketBuffer;
    LOG_PROCESS_ERROR(pHeader);

    g_ChangeStatisInfo(statInternalNetflowIncome, (INT32)dwSize);
    g_ChangeStatisInfo(statInternalPacketIncome, 1);

    LOG_PROCESS_ERROR(pSocketSession);
    LOG_PROCESS_ERROR(m_MessageFuncList[pHeader->wMsg]);

#if defined(WIN32)
	__try
	{
		(this->*m_MessageFuncList[pHeader->wMsg])(pPacketBuffer, dwSize, pSocketSession);
	}
	__except (DumpExceptionFilter(GetExceptionInformation()))
	{
		CRI("failed to process internal message id %d size %d", pHeader->wMsg, dwSize);
	}
#elif defined (__linux__)
	(this->*m_MessageFuncList[pHeader->wMsg])(pPacketBuffer, dwSize, pSocketSession);
#endif 

    if (pPacketBuffer)
        m_pPacketAllocator->Free(pPacketBuffer);

    return;
Exit0:
    if (pHeader)
        CRI("unknown internal message id %d size %d", pHeader->wMsg, dwSize);
    else
        CRI("unknown internal message with null pointer");
    if (pPacketBuffer)
        m_pPacketAllocator->Free(pPacketBuffer);
    if (pSocketSession)
        pSocketSession->Close();

    return;
}

void CDBMessageHandler::OnDisconnected(ISocketSession* pSocketSession, BOOL bRemoteShutdown)
{
    DB_BASE_SESSION* pBaseSession = NULL;

    LOG_PROCESS_ERROR(pSocketSession);

    pBaseSession = (DB_BASE_SESSION*)pSocketSession->GetUserData();
    LOG_PROCESS_ERROR(pBaseSession);

    pBaseSession->pSocketSession = NULL;

    switch (pBaseSession->dwType)
    {
    case stGD:
        {
            GD_SESSION* pGDSession = (GD_SESSION*)pBaseSession;
            pGDSession->bConnected = false;
            pGDSession->qwTimer = GetTickCountEx() + g_ServerConfig.Common.nReconnectTime;
            CRI("GD disconnected");
        }
        break;
    case stMS:
        {
            MS_SESSION* pMSSession = (MS_SESSION*)pBaseSession;
            pMSSession->bConnected = false;
            pMSSession->qwTimer = GetTickCountEx() + g_ServerConfig.Common.nReconnectTime;

            if (CDBSessionMgr::GetInstance().GetServerState() != sgsInitializing)
            {
                pMSSession->qwTimer = 0xFFFFFFFF;

                CRI("MS disconnected");

                CDBSessionMgr::GetInstance().SetServerState(sgsClosing);
                CDBServer::GetInstance().m_bForceClose = TRUE;
            }
        }
        break;
    case stGS:
        {
            GS_SESSION* pGSSession = (GS_SESSION*)pBaseSession;
            pGSSession->qwTimer = 0xFFFFFFFF;

            CRI("GS %d disconnected", pGSSession->dwSessionID);
        }        
        break;
    case stGT:
        {
            GT_SESSION* pGTSession = (GT_SESSION*)pBaseSession;
            pGTSession->qwTimer = 0xFFFFFFFF;

            CRI("GT %d disconnected", pGTSession->dwSessionID);
        }        
        break;
    default:
        LOG_PROCESS_ERROR(FALSE);
        break;
    }

    return;
Exit0:
    return;
}

CDBMessageHandler::CDBMessageHandler()
{
    m_pNet = NULL;
    m_pPacketAllocator = NULL;
    memset(m_MessageFuncList, 0, sizeof(m_MessageFuncList));
}

CDBMessageHandler::~CDBMessageHandler()
{
    UnInit();
}

BOOL CDBMessageHandler::Init(INet* pNet, IPacketAllocator* pPacketAllocator)
{
    LOG_PROCESS_ERROR(pNet);
    LOG_PROCESS_ERROR(pPacketAllocator);

    m_pNet = pNet;
    m_pPacketAllocator = pPacketAllocator;

    m_MessageFuncList[a2a_ping] = &CDBMessageHandler::OnAllPing;

    m_MessageFuncList[m2d_register_ack] = &CDBMessageHandler::OnMSRegisterAck;
    m_MessageFuncList[m2a_server_info] = &CDBMessageHandler::OnMSServerInfo;
    m_MessageFuncList[m2a_all_ready] = &CDBMessageHandler::OnMSAllReady;
    m_MessageFuncList[m2a_close] = &CDBMessageHandler::OnMSClose;
    m_MessageFuncList[m2d_create_role_ack] = &CDBMessageHandler::OnMSCreateRoleAck;
    m_MessageFuncList[m2d_can_delete_role_ack] = &CDBMessageHandler::OnMSCanDeleteRoleAck;
    m_MessageFuncList[m2d_delete_role_ack] = &CDBMessageHandler::OnMSDeleteRoleAck;
    m_MessageFuncList[m2d_leave_db] = &CDBMessageHandler::OnMSLeaveDB;
    m_MessageFuncList[m2d_clear_role_cache] = &CDBMessageHandler::OnMSClearRoleCache;
	m_MessageFuncList[m2d_gm_command] = &CDBMessageHandler::OnMSGMCommand;

    m_MessageFuncList[g2d_register] = &CDBMessageHandler::OnGSRegister;
    m_MessageFuncList[g2d_load_lock_role_data] = &CDBMessageHandler::OnGSLoadLockRoleData;
    m_MessageFuncList[g2d_save_role_data] = &CDBMessageHandler::OnGSSaveRoleData;
    m_MessageFuncList[g2d_unlock_role_data] = &CDBMessageHandler::OnGSUnlockRoleData;

    m_MessageFuncList[t2d_register] = &CDBMessageHandler::OnGTRegister;
    m_MessageFuncList[t2d_query_role_list] = &CDBMessageHandler::OnGTQueryRoleList;
    m_MessageFuncList[t2d_create_role] = &CDBMessageHandler::OnGTCreateRole;
    m_MessageFuncList[t2d_delete_role] = &CDBMessageHandler::OnGTDeleteRole;
    m_MessageFuncList[t2d_undelete_role] = &CDBMessageHandler::OnGTUnDeleteRole;
    m_MessageFuncList[t2d_forever_delete_role] = &CDBMessageHandler::OnGTForeverDeleteRole;

    return TRUE;
Exit0:
    return FALSE;
}

BOOL CDBMessageHandler::UnInit(void)
{

    return TRUE;
}

CDBMessageHandler& CDBMessageHandler::GetInstance(void)
{
    return ms_Instance;
}

inline BOOL CDBMessageHandler::_SendGD(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, INT32 nOffset)
{
    INT32 nRetCode = 0;

    GD_SESSION& rGDSession = CDBSessionMgr::GetInstance().GetGDSession();
    LOG_PROCESS_ERROR(rGDSession.bConnected);
    LOG_PROCESS_ERROR(rGDSession.pSocketSession);

    nRetCode = rGDSession.pSocketSession->Send(pPacketBuffer, dwSize, nOffset);
    LOG_PROCESS_ERROR(nRetCode == dwSize);

    g_ChangeStatisInfo(statInternalNetflowOutgoing, (INT32)dwSize);
    g_ChangeStatisInfo(statInternalPacketOutgoing, 1);

    return TRUE;
Exit0:
    return FALSE;
}

inline BOOL CDBMessageHandler::_SendMS(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, INT32 nOffset)
{
    INT32 nRetCode = 0;

    MS_SESSION& rMSSession = CDBSessionMgr::GetInstance().GetMSSession();
    LOG_PROCESS_ERROR(rMSSession.bConnected);
    LOG_PROCESS_ERROR(rMSSession.pSocketSession);

    nRetCode = rMSSession.pSocketSession->Send(pPacketBuffer, dwSize, nOffset);
    LOG_PROCESS_ERROR(nRetCode == dwSize);

    g_ChangeStatisInfo(statInternalNetflowOutgoing, (INT32)dwSize);
    g_ChangeStatisInfo(statInternalPacketOutgoing, 1);

    return TRUE;
Exit0:
    return FALSE;
}

inline BOOL CDBMessageHandler::_SendGS(UINT32 dwGSSessionID, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, INT32 nOffset)
{
    INT32 nRetCode = 0;

    GS_SESSION* pGSSession = CDBSessionMgr::GetInstance().GetGSSession(dwGSSessionID);
    LOG_PROCESS_ERROR(pGSSession);
    LOG_PROCESS_ERROR(pGSSession->pSocketSession);

    nRetCode = pGSSession->pSocketSession->Send(pPacketBuffer, dwSize, nOffset);
    LOG_PROCESS_ERROR(nRetCode == dwSize);

    g_ChangeStatisInfo(statInternalNetflowOutgoing, (INT32)dwSize);
    g_ChangeStatisInfo(statInternalPacketOutgoing, 1);

    return TRUE;
Exit0:
    return FALSE;
}

inline BOOL CDBMessageHandler::_SendGT(UINT32 dwGTSessionID, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, INT32 nOffset)
{
    INT32 nRetCode = 0;

    GT_SESSION* pGTSession = CDBSessionMgr::GetInstance().GetGTSession(dwGTSessionID);
    LOG_PROCESS_ERROR(pGTSession);
    LOG_PROCESS_ERROR(pGTSession->pSocketSession);

    nRetCode = pGTSession->pSocketSession->Send(pPacketBuffer, dwSize, nOffset);
    LOG_PROCESS_ERROR(nRetCode == dwSize);

    g_ChangeStatisInfo(statInternalNetflowOutgoing, (INT32)dwSize);
    g_ChangeStatisInfo(statInternalPacketOutgoing, 1);

    return TRUE;
Exit0:
    return FALSE;
}

/************************************************************************/
// To All

BOOL CDBMessageHandler::DoAllPing(void)
{
    INT32 nRetCode = 0;
    A2A_PING* pMsg = NULL;

    if (CDBSessionMgr::GetInstance().GetGDSession().bConnected)
    {
        pMsg = (A2A_PING*)m_pPacketAllocator->Alloc(sizeof(A2A_PING));
        LOG_PROCESS_ERROR(pMsg);

        pMsg->wMsg = a2a_ping;

        nRetCode = _SendGD((PACKET_BUFFER*)pMsg, sizeof(*pMsg));
        LOG_CHECK_ERROR(nRetCode);

        if (!nRetCode)
            m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
        pMsg = NULL;
    }

    if (CDBSessionMgr::GetInstance().GetMSSession().bConnected)
    {
        pMsg = (A2A_PING*)m_pPacketAllocator->Alloc(sizeof(A2A_PING));
        LOG_PROCESS_ERROR(pMsg);

        pMsg->wMsg = a2a_ping;

        nRetCode = _SendMS((PACKET_BUFFER*)pMsg, sizeof(*pMsg));
        LOG_CHECK_ERROR(nRetCode);

        if (!nRetCode)
            m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
        pMsg = NULL;
    }

    for (INT32 nIndex = 1; nIndex < MAX_GS_SESSION_COUNT; nIndex++)
    {
        GS_SESSION* pGSSession = CDBSessionMgr::GetInstance().GetGSSession(nIndex);
        if (pGSSession && pGSSession->pSocketSession)
        {
            pMsg = (A2A_PING*)m_pPacketAllocator->Alloc(sizeof(A2A_PING));
            LOG_PROCESS_ERROR(pMsg);

            pMsg->wMsg = a2a_ping;

            nRetCode = pGSSession->pSocketSession->Send((PACKET_BUFFER*)pMsg, sizeof(*pMsg), 0);
            LOG_CHECK_ERROR(nRetCode);

            if (!nRetCode)
                m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
            pMsg = NULL;
        }
    }

    for (INT32 nIndex = 1; nIndex < MAX_GT_SESSION_COUNT; nIndex++)
    {
        GT_SESSION* pGTSession = CDBSessionMgr::GetInstance().GetGTSession(nIndex);
        if (pGTSession && pGTSession->pSocketSession)
        {
            pMsg = (A2A_PING*)m_pPacketAllocator->Alloc(sizeof(A2A_PING));
            LOG_PROCESS_ERROR(pMsg);

            pMsg->wMsg = a2a_ping;

            nRetCode = pGTSession->pSocketSession->Send((PACKET_BUFFER*)pMsg, sizeof(*pMsg), 0);
            LOG_CHECK_ERROR(nRetCode);

            if (!nRetCode)
                m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
            pMsg = NULL;
        }
    }

    return TRUE;
Exit0:
    if (pMsg)
        m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

/************************************************************************/
// To GD
BOOL CDBMessageHandler::DoGDRegister(void)
{
    INT32 nRetCode = 0;

    A2U_REGRISTER* pMsg = (A2U_REGRISTER*)m_pPacketAllocator->Alloc(sizeof(A2U_REGRISTER));
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = a2u_regrister;
    pMsg->byType = stDB;
    pMsg->bySessionID = 1;
    pMsg->dwProcessID = GetCurrentProcessId();

    nRetCode = _SendGD((PACKET_BUFFER*)pMsg, sizeof(A2U_REGRISTER));
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

/************************************************************************/
// To MS

BOOL CDBMessageHandler::DoMSRegister(UINT32 dwAddr, UINT16 wPort)
{
    INT32 nRetCode = 0;

    D2M_REGISTER* pMsg = (D2M_REGISTER*)m_pPacketAllocator->Alloc(sizeof(D2M_REGISTER));
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = d2m_register;
    pMsg->dwAddr = dwAddr;
    pMsg->wPort = wPort;

    nRetCode = _SendMS((PACKET_BUFFER*)pMsg, sizeof(*pMsg));
    LOG_PROCESS_ERROR(nRetCode);
    
    return TRUE;
Exit0:
    if (pMsg)
        m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

BOOL CDBMessageHandler::DoMSReady(void)
{
    INT32 nRetCode = 0;

    D2M_READY* pMsg = (D2M_READY*)m_pPacketAllocator->Alloc(sizeof(D2M_READY));
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = d2m_ready;

    nRetCode = _SendMS((PACKET_BUFFER*)pMsg, sizeof(*pMsg));
    LOG_PROCESS_ERROR(nRetCode);

    CDBSessionMgr::GetInstance().SetServerState(sgsSelfReady);
    INF("DB is self ready");

    return TRUE;
Exit0:
    if (pMsg)
        m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

BOOL CDBMessageHandler::DoMSCloseAck(void)
{
    INT32 nRetCode = 0;

    D2M_CLOSE_ACK* pMsg = NULL;

    LOG_PROCESS_ERROR(m_pPacketAllocator);

    pMsg = (D2M_CLOSE_ACK*)m_pPacketAllocator->Alloc(sizeof(D2M_CLOSE_ACK));
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = d2m_close_ack;

    nRetCode = _SendMS((PACKET_BUFFER*)pMsg, sizeof(*pMsg));
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

BOOL CDBMessageHandler::DoMSCreateRole(CDBUser* dbuser, void* pBaseData)
{
    INT32 nRetCode = 0;
    D2M_CREATE_ROLE* pMsg = NULL;

    LOG_PROCESS_ERROR(dbuser);
    LOG_PROCESS_ERROR(pBaseData);

    pMsg = (D2M_CREATE_ROLE*)m_pPacketAllocator->Alloc(sizeof(D2M_CREATE_ROLE) + sizeof(ROLE_DB_BASE_DATA));
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = d2m_create_role;
    pMsg->dwClientSessionID = dbuser->m_dwClientSessionID;
	strxcpy(pMsg->szUserName, dbuser->m_szUserName, USER_NAME_LEN);
	pMsg->byServerGroup = (UINT8)dbuser->m_nServerGroup;
    memcpy(pMsg->BaseData, pBaseData, sizeof(ROLE_DB_BASE_DATA));

    nRetCode = _SendMS((PACKET_BUFFER*)pMsg, sizeof(D2M_CREATE_ROLE) + sizeof(ROLE_DB_BASE_DATA));
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

BOOL CDBMessageHandler::DoMSCanDeleteRole(UINT32 dwClientSessionID, UINT32 dwRoleID)
{
    INT32 nRetCode = 0;

    D2M_CAN_DELETE_ROLE* pMsg = (D2M_CAN_DELETE_ROLE*)m_pPacketAllocator->Alloc(sizeof(D2M_CAN_DELETE_ROLE));
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = d2m_can_delete_role;
    pMsg->dwClientSessionID = dwClientSessionID;
    pMsg->dwRoleID = dwRoleID;

    nRetCode = _SendMS((PACKET_BUFFER*)pMsg, sizeof(*pMsg));
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

BOOL CDBMessageHandler::DoMSDeleteRole(UINT32 dwClientSessionID, UINT32 dwRoleID)
{
    INT32 nRetCode = 0;

    D2M_DELETE_ROLE* pMsg = (D2M_DELETE_ROLE*)m_pPacketAllocator->Alloc(sizeof(D2M_DELETE_ROLE));
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = d2m_delete_role;
    pMsg->dwClientSessionID = dwClientSessionID;
    pMsg->dwRoleID = dwRoleID;

    nRetCode = _SendMS((PACKET_BUFFER*)pMsg, sizeof(*pMsg));
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

BOOL CDBMessageHandler::DoMSLeaveDBAck(UINT32 dwClientSessionID)
{
    INT32 nRetCode = 0;

    D2M_LEAVE_DB_ACK* pMsg = (D2M_LEAVE_DB_ACK*)m_pPacketAllocator->Alloc(sizeof(D2M_LEAVE_DB_ACK));
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = d2m_leave_db_ack;
    pMsg->dwClientSessionID = dwClientSessionID;

    nRetCode = _SendMS((PACKET_BUFFER*)pMsg, sizeof(*pMsg));
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

BOOL CDBMessageHandler::DoMSClearRoleCacheAck(UINT32 dwRoleID, UINT32 dwTLUserID, UINT32 dwCmdSerialID, UINT8 byResult)
{
    INT32 nRetCode = 0;

    D2M_CLEAR_ROLE_CACHE_ACK* pMsg = (D2M_CLEAR_ROLE_CACHE_ACK*)m_pPacketAllocator->Alloc(sizeof(D2M_CLEAR_ROLE_CACHE_ACK));
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = d2m_clear_role_cache_ack;
    pMsg->dwRoleID = dwRoleID;
    pMsg->dwTLUserID = dwTLUserID;
    pMsg->dwCmdSerialID = dwCmdSerialID;
    pMsg->byResult = byResult;

    nRetCode = _SendMS((PACKET_BUFFER*)pMsg, sizeof(*pMsg));
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

/************************************************************************/
// To GS
BOOL CDBMessageHandler::DoGSRegisterAck(UINT32 dwGSSessionID)
{
    INT32 nRetCode = 0;

    D2G_REGISTER_ACK* pMsg = (D2G_REGISTER_ACK*)m_pPacketAllocator->Alloc(sizeof(D2G_REGISTER_ACK));
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = d2g_register_ack;

    nRetCode = _SendGS(dwGSSessionID, (PACKET_BUFFER*)pMsg, sizeof(D2G_REGISTER_ACK));
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

BOOL CDBMessageHandler::DoGSLoadLockRoleDataAck(
    UINT32 dwGSSessionID, UINT32 dwClientSessionID, UINT32 dwRoleID, UINT32 dwDataSize, char* pData)
{
    INT32 nRetCode = 0;

    D2G_LOAD_LOCK_ROLE_DATA_ACK* pMsg = (D2G_LOAD_LOCK_ROLE_DATA_ACK*)m_pPacketAllocator->Alloc(MAX_MESSAGE_SIZE);
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = d2g_load_lock_role_data_ack;
    pMsg->dwClientSessionID = dwClientSessionID;
    pMsg->dwRoleID = dwRoleID;
    pMsg->dwDataSize = dwDataSize;
    memcpy(pMsg->RoleData, pData, dwDataSize);

    nRetCode = _SendGS(dwGSSessionID, (PACKET_BUFFER*)pMsg, sizeof(D2G_LOAD_LOCK_ROLE_DATA_ACK) + dwDataSize);
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

BOOL CDBMessageHandler::DoGSUnlockRoleDataAck(UINT32 dwGSSessionID, UINT32 dwClientSessionID, UINT32 dwRoleID, INT32 nError)
{
    INT32 nRetCode = 0;

    D2G_UNLOCK_ROLE_DATA_ACK* pMsg = (D2G_UNLOCK_ROLE_DATA_ACK*)m_pPacketAllocator->Alloc(sizeof(D2G_UNLOCK_ROLE_DATA_ACK));
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = d2g_unlock_role_data_ack;
	pMsg->nError = nError;
    pMsg->dwClientSessionID = dwClientSessionID;
    pMsg->dwRoleID = dwRoleID;

    nRetCode = _SendGS(dwGSSessionID, (PACKET_BUFFER*)pMsg, sizeof(D2G_UNLOCK_ROLE_DATA_ACK));
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

BOOL CDBMessageHandler::DoGSLoadLockRoleDataFailAck(UINT32 dwGSSessionID, UINT32 dwClientSessionID, UINT32 dwRoleID)
{
    INT32 nRetCode = 0;

    D2G_LOAD_LOCK_ROLE_DATA_FAIL_ACK* pMsg = (D2G_LOAD_LOCK_ROLE_DATA_FAIL_ACK*)m_pPacketAllocator->Alloc(sizeof(D2G_LOAD_LOCK_ROLE_DATA_FAIL_ACK));
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = d2g_load_lock_role_data_fail_ack;
    pMsg->dwClientSessionID = dwClientSessionID;
    pMsg->dwRoleID = dwRoleID;

    nRetCode = _SendGS(dwGSSessionID, (PACKET_BUFFER*)pMsg, sizeof(D2G_LOAD_LOCK_ROLE_DATA_FAIL_ACK));
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}


/************************************************************************/
// To GT
BOOL CDBMessageHandler::DoGTRegisterAck(UINT32 dwGTSessionID)
{
    BOOL bRet = FALSE;
    D2T_REGISTER_ACK* pMsg = (D2T_REGISTER_ACK*)m_pPacketAllocator->Alloc(sizeof(D2T_REGISTER_ACK));
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = d2t_register_ack;

    bRet = _SendGT(dwGTSessionID, (PACKET_BUFFER*)pMsg, sizeof(D2T_REGISTER_ACK));
    LOG_PROCESS_ERROR(bRet);

    return TRUE;
Exit0:
    if (pMsg)
        m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

BOOL CDBMessageHandler::DoGTCloseClientSession(UINT32 dwClientSessionID)
{
    BOOL bRet = FALSE;
    D2T_CLOSE_CLIENT_SESSION* pMsg = (D2T_CLOSE_CLIENT_SESSION*)m_pPacketAllocator->Alloc(sizeof(D2T_CLOSE_CLIENT_SESSION));
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = d2t_close_client_session;
    pMsg->dwClientSessionID = dwClientSessionID;

    bRet = _SendGT(GET_GT_INDEX_FROM_SESSION_ID(dwClientSessionID), (PACKET_BUFFER*)pMsg, sizeof(D2T_CLOSE_CLIENT_SESSION));
    LOG_PROCESS_ERROR(bRet);

    INF("close client session <%08X>", dwClientSessionID);

    return TRUE;
Exit0:
    if (pMsg)
        m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

BOOL CDBMessageHandler::DoGTCreateRoleAck(UINT32 dwClientSessionID, INT32 nErrCode, void* pBaseData)
{
    BOOL bRet = FALSE;
    D2T_CREATE_ROLE_ACK* pMsg = (D2T_CREATE_ROLE_ACK*)m_pPacketAllocator->Alloc(
        sizeof(D2T_CREATE_ROLE_ACK) + sizeof(ROLE_DB_BASE_DATA));
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = d2t_create_role_ack;
    pMsg->dwClientSessionID = dwClientSessionID;
    pMsg->nErrCode = nErrCode;
    if (pBaseData)
    {
        memcpy(pMsg->BaseData, pBaseData, sizeof(ROLE_DB_BASE_DATA));
    }

    bRet = _SendGT(GET_GT_INDEX_FROM_SESSION_ID(dwClientSessionID), (PACKET_BUFFER*)pMsg, 
        sizeof(D2T_CREATE_ROLE_ACK) + sizeof(ROLE_DB_BASE_DATA));
    LOG_PROCESS_ERROR(bRet);

    return TRUE;
Exit0:
    if (pMsg)
        m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

BOOL CDBMessageHandler::DoGTDeleteRoleAck(UINT32 dwClientSessionID, INT32 nErrCode, UINT32 dwRoleID)
{
    BOOL bRet = FALSE;
    D2T_DELETE_ROLE_ACK* pMsg = (D2T_DELETE_ROLE_ACK*)m_pPacketAllocator->Alloc(sizeof(D2T_DELETE_ROLE_ACK));
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = d2t_delete_role_ack;
    pMsg->dwClientSessionID = dwClientSessionID;
    pMsg->dwRoleID = dwRoleID;
    pMsg->nErrCode = nErrCode;

    bRet = _SendGT(GET_GT_INDEX_FROM_SESSION_ID(dwClientSessionID), (PACKET_BUFFER*)pMsg, sizeof(D2T_DELETE_ROLE_ACK));
    LOG_PROCESS_ERROR(bRet);

    return TRUE;
Exit0:
    if (pMsg)
        m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

BOOL CDBMessageHandler::DoGTUnDeleteRoleAck(UINT32 dwClientSessionID, INT32 nErrCode, UINT32 dwRoleID)
{
    BOOL bRet = FALSE;
    D2T_UNDELETE_ROLE_ACK* pMsg = 
        (D2T_UNDELETE_ROLE_ACK*)m_pPacketAllocator->Alloc(sizeof(D2T_UNDELETE_ROLE_ACK));
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = d2t_undelete_role_ack;
    pMsg->dwClientSessionID = dwClientSessionID;
    pMsg->dwRoleID = dwRoleID;
    pMsg->nErrCode = nErrCode;

    bRet = _SendGT(GET_GT_INDEX_FROM_SESSION_ID(dwClientSessionID), (PACKET_BUFFER*)pMsg, sizeof(D2T_UNDELETE_ROLE_ACK));
    LOG_PROCESS_ERROR(bRet);

    return TRUE;
Exit0:
    if (pMsg)
        m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

BOOL CDBMessageHandler::DoGTForeverDeleteRoleAck(UINT32 dwClientSessionID, INT32 nErrCode, UINT32 dwRoleID)
{
    BOOL bRet = FALSE;
    D2T_FOREVER_DELETE_ROLE_ACK* pMsg = (D2T_FOREVER_DELETE_ROLE_ACK*)m_pPacketAllocator->Alloc(sizeof(D2T_FOREVER_DELETE_ROLE_ACK));
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = d2t_forever_delete_role_ack;
    pMsg->dwClientSessionID = dwClientSessionID;
    pMsg->dwRoleID = dwRoleID;
    pMsg->nErrCode = nErrCode;

    bRet = _SendGT(GET_GT_INDEX_FROM_SESSION_ID(dwClientSessionID), (PACKET_BUFFER*)pMsg, sizeof(D2T_FOREVER_DELETE_ROLE_ACK));
    LOG_PROCESS_ERROR(bRet);

    return TRUE;
Exit0:
    if (pMsg)
        m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

BOOL CDBMessageHandler::DoGTSyncRoleList(CDBUser* dbuser)
{
    BOOL bRet = FALSE;
    INT32 nSize = 0;
    D2T_SYNC_ROLE_LIST* pMsg = NULL;
    LOG_PROCESS_ERROR(dbuser);

    nSize = sizeof(D2T_SYNC_ROLE_LIST) + dbuser->m_byRoleCount * sizeof(ROLE_DB_BASE_DATA);
    pMsg = (D2T_SYNC_ROLE_LIST*)m_pPacketAllocator->Alloc(nSize);
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = d2t_sync_role_list;
    pMsg->dwClientSessionID = dbuser->m_dwClientSessionID;
    pMsg->nErrCode = dbuser->m_nResult;
    if (dbuser->m_nResult == errSuccess)
    {
        pMsg->byRoleCount = dbuser->m_byRoleCount;
        for (UINT8 i=0; i<dbuser->m_byRoleCount; i++)
        {
            memcpy(pMsg->BaseData + sizeof(ROLE_DB_BASE_DATA) * i, &dbuser->m_BaseData[i], sizeof(ROLE_DB_BASE_DATA));
        }
    }
    else
        pMsg->byRoleCount = 0;

    bRet = _SendGT(GET_GT_INDEX_FROM_SESSION_ID(dbuser->m_dwClientSessionID), (PACKET_BUFFER*)pMsg, nSize);
    LOG_PROCESS_ERROR(bRet);

    return TRUE;
Exit0:
    if (pMsg)
        m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

/************************************************************************/
// From All

void CDBMessageHandler::OnAllPing(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession)
{
    DB_BASE_SESSION* pBaseSession = (DB_BASE_SESSION*)pSocketSession->GetUserData();
    LOG_PROCESS_ERROR(pBaseSession);

    if(pBaseSession->dwType == stGD)
		pBaseSession->qwTimer = GetTickCountEx() + g_ServerConfig.Common.nPingGuardTimeout;
    else
        pBaseSession->qwTimer = GetTickCountEx() + g_ServerConfig.Common.nServerPingTimeout;
    
    return;
Exit0:
    if (pSocketSession)
        pSocketSession->Close();
    return;
}

/************************************************************************/
// From MS
void CDBMessageHandler::OnMSRegisterAck(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession)
{
    INT32 nRetCode = 0;

    M2D_REGISTER_ACK* pMsg = (M2D_REGISTER_ACK*)pPacketBuffer;

    nRetCode = CDBServer::GetInstance().InitDataBaseAndWorkerThread(pMsg->szServerAddr,
        pMsg->szLoginName, pMsg->szPassword, pMsg->szDBName, pMsg->szCharSet, pMsg->dwServerPort);
    LOG_PROCESS_ERROR(nRetCode);

    nRetCode = DoMSReady();
    LOG_PROCESS_ERROR(nRetCode);

    if(CDBSessionMgr::GetInstance().GetGDSession().bConnected)
    {
        nRetCode = DoGDRegister();
        LOG_PROCESS_ERROR(nRetCode);
    }

    INF("DB registered to MS");
Exit0:
    return;
}

void CDBMessageHandler::OnMSServerInfo(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession)
{

    return;
}

void CDBMessageHandler::OnMSAllReady(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession)
{
    CDBSessionMgr::GetInstance().SetServerState(sgsAllReady);
    INF("all servers are ready");
}

void CDBMessageHandler::OnMSClose(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession)
{
    CDBSessionMgr::GetInstance().SetServerState(sgsClosing);
    INF("DB is closing");
}

void CDBMessageHandler::OnMSCreateRoleAck(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession)
{
    INT32 nRetCode = 0;
    M2D_CREATE_ROLE_ACK* pMsg = (M2D_CREATE_ROLE_ACK*)pPacketBuffer;

    nRetCode = DoGTCreateRoleAck(pMsg->dwClientSessionID, errSuccess, (ROLE_DB_BASE_DATA*)pMsg->BaseData);
    LOG_PROCESS_ERROR(nRetCode);

    return;
Exit0:
    DoGTCloseClientSession(pMsg->dwClientSessionID);

    return; 
}

void CDBMessageHandler::OnMSCanDeleteRoleAck(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession)
{
    BOOL bRet = FALSE;
    CDBServer& dbserver = CDBServer::GetInstance();
    CDBUserMgr& usermgr = dbserver.m_usermgr;
    CDBRoleMgr& rolemgr = dbserver.m_rolemgr;
    ROLE_DB_BASE_DATA* basedata = NULL;

    M2D_CAN_DELETE_ROLE_ACK* pMsg = (M2D_CAN_DELETE_ROLE_ACK*)pPacketBuffer;
    CDBUser* dbuser = NULL;
    CDBRole* dbrole = NULL;
    UINT8 rolepos = 0;

    LOG_PROCESS_ERROR(CDBSessionMgr::GetInstance().GetServerState() == sgsAllReady);

    if (pMsg->nResult != errSuccess)
    {
        DoGTDeleteRoleAck(pMsg->dwClientSessionID, pMsg->nResult, pMsg->dwRoleID);
        return;
    }

    dbuser = usermgr.GetDBUserBySessionID(pMsg->dwClientSessionID);
    LOG_PROCESS_ERROR(dbuser);
    LOG_PROCESS_ERROR(dbuser->m_state == CDBUser::dusAuthed);
    LOG_PROCESS_ERROR(dbuser->m_dbstate == CDBUser::dtsFree);

    for (; rolepos<dbuser->m_byRoleCount; rolepos++)
    {
        if (dbuser->m_dwRoleID[rolepos] == pMsg->dwRoleID)
        {
            break;
        }
    }
    LOG_PROCESS_ERROR(rolepos<dbuser->m_byRoleCount);

    dbrole = rolemgr.GetDBRoleByID(pMsg->dwRoleID);
    LOG_PROCESS_ERROR(dbrole == dbuser->m_pDBRole[rolepos]);
    if (dbrole)
    {
        LOG_PROCESS_ERROR(dbrole->m_dbuser == dbuser);
        LOG_PROCESS_ERROR(dbrole->m_dbtask == CDBRole::DB_TASK_FREE);
        LOG_PROCESS_ERROR(dbrole->m_lockstate == CDBRole::LOCK_STATE_UNLOCKED);

        basedata = &dbuser->m_BaseData[rolepos];
        LOG_PROCESS_ERROR(basedata->dwDeleteTime == 0);

        bRet = rolemgr.Pop(dbrole);
        LOG_PROCESS_ERROR(bRet);

        basedata->dwDeleteTime = (UINT32)time(NULL);

        dbrole->m_dwDeleteTime = basedata->dwDeleteTime;
        dbrole->m_dbtask = CDBRole::DB_TASK_UPDATE_ROLE_DELETE_TIME;
        dbuser->m_dbstate = CDBUser::dtsUpdatingRoleDeleteTime;
        bRet = dbserver.m_threads[pMsg->dwClientSessionID % dbserver.m_dwThreadCount].AddRoleDbTask(dbrole);
        LOG_PROCESS_ERROR(bRet);
    }
    else
    {
        dbrole = rolemgr.Pop();
        LOG_PROCESS_ERROR(dbrole);

        basedata = &dbuser->m_BaseData[rolepos];
        LOG_PROCESS_ERROR(basedata->dwDeleteTime == 0);

        basedata->dwDeleteTime = (UINT32)time(NULL);

        dbuser->m_pDBRole[rolepos] = dbrole;
        dbrole->m_dwRoleID = pMsg->dwRoleID;
        dbrole->m_dwDeleteTime = basedata->dwDeleteTime;
        dbrole->m_dbuser = dbuser;
        dbrole->m_dbtask = CDBRole::DB_TASK_UPDATE_ROLE_DELETE_TIME_WITHOUT_DATA;
        dbuser->m_dbstate = CDBUser::dtsUpdatingRoleDeleteTime;
        bRet = dbserver.m_threads[pMsg->dwClientSessionID % dbserver.m_dwThreadCount].AddRoleDbTask(dbrole);
        LOG_PROCESS_ERROR(bRet);
    }

    DB_SYS_LOG_SUCCESS(dbuser);
    return;
Exit0:
    DB_SYS_LOG_ERROR(dbuser);

    DoGTCloseClientSession(pMsg->dwClientSessionID);
    return;
}

void CDBMessageHandler::OnMSDeleteRoleAck(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession)
{
    INT32 nRetCode = 0;
    M2D_DELETE_ROLE_ACK* pMsg = (M2D_DELETE_ROLE_ACK*)pPacketBuffer;

    nRetCode = DoGTForeverDeleteRoleAck(pMsg->dwClientSessionID, errSuccess, pMsg->dwRoleID);
    LOG_PROCESS_ERROR(nRetCode);

    return;
Exit0:
    DoGTCloseClientSession(pMsg->dwClientSessionID);

    return;
}

void CDBMessageHandler::OnMSLeaveDB(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession)
{
    BOOL bRet = FALSE;
    M2D_LEAVE_DB* pMsg = (M2D_LEAVE_DB*)pPacketBuffer;
    CDBServer& dbserver = CDBServer::GetInstance();
    CDBUserMgr& usermgr = dbserver.m_usermgr;
    CDBRoleMgr& rolemgr = dbserver.m_rolemgr;

    CDBUser* dbuser = NULL;
    CDBRole* dbrole = NULL;

    dbuser = usermgr.GetDBUserBySessionID(pMsg->dwClientSessionID);
    LOG_PROCESS_ERROR(dbuser);

    dbrole = dbuser->m_pPlayingRole;
    if (dbrole)
    {
        LOG_PROCESS_ERROR(dbuser->m_state == CDBUser::dusPlaying);

        if (dbrole->m_lockstate == CDBRole::LOCK_STATE_LOCKED)
        {
            dbrole->m_lockstate = CDBRole::LOCK_STATE_UNLOCKING;
            bRet = dbserver.m_threads[dbrole->m_dwRoleID%dbserver.m_dwThreadCount].AddRoleLockTask(dbrole);
            LOG_PROCESS_ERROR(bRet);
        }
        else if (dbrole->m_lockstate == CDBRole::LOCK_STATE_LOCKING)
        {
            dbrole->m_lockstate = CDBRole::LOCK_STATE_LOCKING_AND_UNLOCKING;
        }
        else
        {
            LOG_PROCESS_ERROR(FALSE);
        }
        dbuser->m_pPlayingRole = NULL;
    }

    if (dbuser->m_state != CDBUser::dusInvalid)
    {
        dbuser->m_state = CDBUser::dusLogout;
    }

	DB_SYS_LOG_SUCCESS(dbuser);

    dbserver.m_nOnlineUserCount--;
    usermgr.Push(dbuser);

    bRet = usermgr.DelFromSessionIDMap(dbuser);
    LOG_PROCESS_ERROR(bRet);

	INF("user <%08X> logout, total %d", pMsg->dwClientSessionID, dbserver.m_nOnlineUserCount);

	bRet = DoMSLeaveDBAck(pMsg->dwClientSessionID);
	LOG_CHECK_ERROR(bRet);
	
	return;
Exit0:
	DB_SYS_LOG_ERROR(dbuser);
    INF("user <%08X> logout, total %d", pMsg->dwClientSessionID, dbserver.m_nOnlineUserCount);

    bRet = DoMSLeaveDBAck(pMsg->dwClientSessionID);
    LOG_CHECK_ERROR(bRet);
}

void CDBMessageHandler::OnMSClearRoleCache(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession)
{
    BOOL bRet = FALSE;
    M2D_CLEAR_ROLE_CACHE* pMsg = (M2D_CLEAR_ROLE_CACHE*)pPacketBuffer;
    CDBRole* dbrole = NULL;

    LOG_PROCESS_ERROR(CDBSessionMgr::GetInstance().GetServerState() == sgsAllReady);

    dbrole = CDBServer::GetInstance().m_rolemgr.GetDBRoleByID(pMsg->dwRoleID);
    if (dbrole)
    {
        dbrole->m_dbuser->m_bRoleListCached = FALSE;

        bRet = CDBServer::GetInstance().m_rolemgr.Pop(dbrole);
        LOG_PROCESS_ERROR(bRet);

        bRet = dbrole->m_dbuser->RemoveRole(dbrole, FALSE);
        LOG_PROCESS_ERROR(bRet);
    }

    DoMSClearRoleCacheAck(pMsg->dwRoleID, pMsg->dwTLUserID, pMsg->dwCmdSerialID, 1);

    return;

Exit0:
    DoMSClearRoleCacheAck(pMsg->dwRoleID, pMsg->dwTLUserID, pMsg->dwCmdSerialID, 0);
}

void CDBMessageHandler::OnMSGMCommand(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession)
{
	INT32 nRetCode = 0;
	M2D_GM_COMMAND* pMsg = (M2D_GM_COMMAND*)pPacketBuffer;

	if (strnicmp(pMsg->szGMCommand, "reload", sizeof("reload") - 1) == 0)
	{
		nRetCode = LoadGlobalConfig(g_szGlobalConfigFileName);
		LOG_CHECK_ERROR(nRetCode);
	}

	return;
}

/************************************************************************/
// From GS
void CDBMessageHandler::OnGSRegister(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession)
{
    INT32 nRetCode = 0;
    G2D_REGISTER* pMsg = (G2D_REGISTER*)pPacketBuffer;

    GS_SESSION* pGSSession = CDBSessionMgr::GetInstance().GetGSSession(pMsg->dwGSSessionID);
    LOG_PROCESS_ERROR(pGSSession);
    LOG_PROCESS_ERROR(CDBSessionMgr::GetInstance().GetServerState() != sgsClosing );

    pGSSession->pSocketSession = pSocketSession;
    pGSSession->qwTimer = GetTickCountEx() + g_ServerConfig.Common.nServerPingTimeout;
    pSocketSession->SetUserData(pGSSession);

    nRetCode = DoGSRegisterAck(pGSSession->dwSessionID);
    LOG_PROCESS_ERROR(nRetCode);

    INF("GS %d register to DB", pMsg->dwGSSessionID);

    return;
Exit0:
    if (pSocketSession)
        pSocketSession->Close();

    return;
}

void CDBMessageHandler::OnGSLoadLockRoleData(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession)
{
    G2D_LOAD_LOCK_ROLE_DATA* pMsg = (G2D_LOAD_LOCK_ROLE_DATA*)pPacketBuffer;
    CDBServer& dbserver = CDBServer::GetInstance();
    CDBRoleMgr& rolemgr = dbserver.m_rolemgr;
    CDBUserMgr& usermgr = dbserver.m_usermgr;
    BOOL bRet = FALSE;
    GS_SESSION* pGSSession = NULL;
    CDBUser* dbuser = NULL;
    CDBRole* dbrole = NULL;
    UINT8 rolepos = 0;

    LOG_PROCESS_ERROR(CDBSessionMgr::GetInstance().GetServerState() == sgsAllReady);

    pGSSession = (GS_SESSION*)pSocketSession->GetUserData();
    LOG_PROCESS_ERROR(pGSSession);

    dbuser = usermgr.GetDBUserBySessionID(pMsg->dwClientSessionID);
    LOG_PROCESS_ERROR(dbuser);
    LOG_PROCESS_ERROR(dbuser->m_dwClientSessionID == pMsg->dwClientSessionID);
    LOG_PROCESS_ERROR(dbuser->m_pPlayingRole == NULL);
    LOG_PROCESS_ERROR(dbuser->m_state == CDBUser::dusAuthed);
    LOG_PROCESS_ERROR(dbuser->m_dbstate == CDBUser::dtsFree);

    for (; rolepos<dbuser->m_byRoleCount; rolepos++)
    {
        if (dbuser->m_dwRoleID[rolepos] == pMsg->dwRoleID)
        {
            break;
        }
    }
    LOG_PROCESS_ERROR(rolepos<dbuser->m_byRoleCount);

    dbrole = rolemgr.GetDBRoleByID(pMsg->dwRoleID);
    LOG_PROCESS_ERROR(dbrole == dbuser->m_pDBRole[rolepos]);
    if (dbrole)
    {
        LOG_PROCESS_ERROR(dbrole->m_dbuser == dbuser);
        LOG_PROCESS_ERROR(dbrole->m_dwRoleID == pMsg->dwRoleID);
        LOG_PROCESS_ERROR(dbrole->m_dwDeleteTime == 0);
        if (dbrole->m_lockstate == CDBRole::LOCK_STATE_UNLOCKED)
        {
            bRet = rolemgr.Pop(dbrole);
            LOG_PROCESS_ERROR(bRet);

            dbrole->m_lockstate = CDBRole::LOCK_STATE_LOCKING;
            bRet = dbserver.m_threads[dbrole->m_dwRoleID%dbserver.m_dwThreadCount].AddRoleLockTask(dbrole);
            LOG_PROCESS_ERROR(bRet);
        }
        else if (dbrole->m_lockstate == CDBRole::LOCK_STATE_UNLOCKING)
        {
            dbrole->m_lockstate = CDBRole::LOCK_STATE_UNLOCKING_AND_LOCKING;
        }
        else if (dbrole->m_lockstate == CDBRole::LOCK_STATE_LOCKING_AND_UNLOCKING)
        {
            dbrole->m_lockstate = CDBRole::LOCK_STATE_LOCKING;
        }
        else
        {
            CRI("GS lock Role %d <%08X> Failed, Current Lock State: %d", pMsg->dwRoleID, pMsg->dwClientSessionID, dbrole->m_lockstate);
            bRet = DoGSLoadLockRoleDataFailAck(pGSSession->dwSessionID, pMsg->dwClientSessionID, pMsg->dwRoleID);
            LOG_PROCESS_ERROR(bRet);
            return;
        }

        dbrole->m_dwGSSessionID = pGSSession->dwSessionID;
        dbrole->m_qwLastSaveTime = GetTickCountEx();

        dbuser->m_pPlayingRole = dbrole;
        dbuser->m_state = CDBUser::dusPlaying;

        bRet = CDBMessageHandler::GetInstance().DoGSLoadLockRoleDataAck(
            dbrole->m_dwGSSessionID,
            dbuser->m_dwClientSessionID,
            pMsg->dwRoleID,
            dbrole->m_pCurMem->CtrlNode.dwDataSize,
            dbrole->m_pCurMem->RoleData);
        LOG_PROCESS_ERROR(bRet);
    }
    else
    {
        LOG_PROCESS_ERROR(dbuser->m_BaseData[rolepos].dwDeleteTime == 0);

        dbrole = rolemgr.Pop();
        LOG_PROCESS_ERROR(dbrole);
        LOG_PROCESS_ERROR(dbrole->m_pCurMem == NULL);
        LOG_PROCESS_ERROR(dbrole->m_lockstate == CDBRole::LOCK_STATE_INVALID);

        dbuser->m_pDBRole[rolepos] = dbrole;
        dbrole->m_dwRoleID = pMsg->dwRoleID;
        dbrole->m_dbuser = dbuser;
        dbrole->m_dwGSSessionID = pGSSession->dwSessionID;
        dbrole->m_lockstate = CDBRole::LOCK_STATE_LOCKING;
        bRet = dbrole->LoadData();
        LOG_PROCESS_ERROR(bRet);
    }

	DB_SYS_LOG_SUCCESS(dbuser);
    return;
Exit0:
	DB_SYS_LOG_ERROR(dbuser);
    //INF("failed to lock role %d <%08X>", pMsg->dwRoleID, pMsg->dwClientSessionID);
    DoGTCloseClientSession(pMsg->dwClientSessionID);
    return;
}

void CDBMessageHandler::OnGSSaveRoleData(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession)
{
    BOOL bRet = FALSE;
    CDBRole* dbrole = NULL;
    G2D_SAVE_ROLE_DATA* pMsg = (G2D_SAVE_ROLE_DATA*)pPacketBuffer;
    CDBServer& dbserver = CDBServer::GetInstance();
    CDBRoleMgr& rolemgr = dbserver.m_rolemgr;

    GS_SESSION* pGSSession = (GS_SESSION*)pSocketSession->GetUserData();
    LOG_PROCESS_ERROR(pGSSession);

    dbrole = rolemgr.GetDBRoleByID(pMsg->dwRoleID);
    LOG_PROCESS_ERROR(dbrole);
    LOG_PROCESS_ERROR(dbrole->m_dwGSSessionID == pGSSession->dwSessionID);
    LOG_PROCESS_ERROR(dbrole->m_lockstate == CDBRole::LOCK_STATE_LOCKING ||
        dbrole->m_lockstate == CDBRole::LOCK_STATE_UNLOCKING_AND_LOCKING ||
        dbrole->m_lockstate == CDBRole::LOCK_STATE_LOCKED);

    bRet = dbrole->SaveData(pMsg->RoleData, pMsg->dwDataSize);
    LOG_PROCESS_ERROR(bRet);

    //INF("save role %d <%08X>", pMsg->dwRoleID, pMsg->dwClientSessionID);
	DB_SYS_LOG_SUCCESS(dbrole->m_dbuser);
    return;
Exit0:
    //CRI("failed to save role %d <%08X>", pMsg->dwRoleID, pMsg->dwClientSessionID);
    REPORT(1, "SAVE FAILED!!!");
    if (dbrole)
    {
    	DB_SYS_LOG_ERROR(dbrole->m_dbuser);
    }
    return;
}

void CDBMessageHandler::OnGSUnlockRoleData(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession)
{
    BOOL bRet = FALSE;
    G2D_UNLOCK_ROLE_DATA* pMsg = (G2D_UNLOCK_ROLE_DATA*)pPacketBuffer;
    CDBServer& dbserver = CDBServer::GetInstance();
    CDBUserMgr& usermgr = dbserver.m_usermgr;
    CDBRoleMgr& rolemgr = dbserver.m_rolemgr;
    CDBUser* dbuser = NULL;
    CDBRole* dbrole = NULL;
	INT32 nError = errUnknownError;

    GS_SESSION* pGSSession = (GS_SESSION*)pSocketSession->GetUserData();
    LOG_PROCESS_ERROR(pGSSession);
    
    dbuser = usermgr.GetDBUserBySessionID(pMsg->dwClientSessionID);
    LOG_PROCESS_ERROR(dbuser);
    LOG_CHECK_ERROR(dbuser->m_state == CDBUser::dusPlaying);

    dbrole = rolemgr.GetDBRoleByID(pMsg->dwRoleID);
    LOG_PROCESS_ERROR(dbrole);
    LOG_PROCESS_ERROR(dbuser->m_pPlayingRole == dbrole);
    LOG_PROCESS_ERROR(dbrole->m_dwGSSessionID == pGSSession->dwSessionID);

    if (dbrole->m_lockstate == CDBRole::LOCK_STATE_LOCKED)
    {
        dbrole->m_lockstate = CDBRole::LOCK_STATE_UNLOCKING;
        bRet = dbserver.m_threads[dbrole->m_dwRoleID%dbserver.m_dwThreadCount].AddRoleLockTask(dbrole);
        LOG_PROCESS_ERROR(bRet);
    }
    else if (dbrole->m_lockstate == CDBRole::LOCK_STATE_LOCKING)
    {
        dbrole->m_lockstate = CDBRole::LOCK_STATE_LOCKING_AND_UNLOCKING;
    }
    else if (dbrole->m_lockstate == CDBRole::LOCK_STATE_UNLOCKING_AND_LOCKING)
    {
        dbrole->m_lockstate = CDBRole::LOCK_STATE_UNLOCKING;
    }
    else
    {
        CRI("GS Unlock Role %d <%08X> Failed, Current Lock State: %d", pMsg->dwRoleID, pMsg->dwClientSessionID, dbrole->m_lockstate);
		LOG_PROCESS_ERROR(FALSE);
    }

    dbuser->m_pPlayingRole = NULL;
    dbuser->m_state = CDBUser::dusAuthed;

	nError = errSuccess;
    bRet = DoGSUnlockRoleDataAck(dbrole->m_dwGSSessionID, pMsg->dwClientSessionID, pMsg->dwRoleID, nError);
    LOG_PROCESS_ERROR(bRet);

    dbrole->m_dwGSSessionID = 0;

	DB_SYS_LOG_SUCCESS(dbuser);
    return;
Exit0:
	//INF("failed to unlock role %d <%08X>", pMsg->dwRoleID, pMsg->dwClientSessionID);
	DB_SYS_LOG_ERROR(dbuser);

	if(pGSSession)
	{
		bRet = DoGSUnlockRoleDataAck(pGSSession->dwSessionID, pMsg->dwClientSessionID, pMsg->dwRoleID, nError);
		LOG_CHECK_ERROR(bRet);
	}
    return;
}

/************************************************************************/
// From GT
void CDBMessageHandler::OnGTRegister(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession)
{
    INT32 nRetCode = 0;
    T2D_REGISTER* pMsg = (T2D_REGISTER*)pPacketBuffer;

    GT_SESSION* pGTSession = CDBSessionMgr::GetInstance().GetGTSession(pMsg->dwGTSessionID);
    LOG_PROCESS_ERROR(pGTSession);
    LOG_PROCESS_ERROR(CDBSessionMgr::GetInstance().GetServerState() != sgsClosing);

    pGTSession->pSocketSession = pSocketSession;
    pGTSession->qwTimer = GetTickCountEx() + g_ServerConfig.Common.nServerPingTimeout;
    pSocketSession->SetUserData(pGTSession);

    nRetCode = DoGTRegisterAck(pGTSession->dwSessionID);
    LOG_PROCESS_ERROR(nRetCode);

    INF("GT %d register to DB", pMsg->dwGTSessionID);

    return;
Exit0:
    if (pSocketSession)
        pSocketSession->Close();

    return;
}

void CDBMessageHandler::OnGTQueryRoleList(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession)
{
    BOOL bRet = FALSE;
    T2D_QUERY_ROLE_LIST* pMsg = (T2D_QUERY_ROLE_LIST*)pPacketBuffer;
    CDBUser* dbuser = NULL;
    CDBServer& dbserver = CDBServer::GetInstance();
    CDBUserMgr& usermgr = dbserver.m_usermgr;

    LOG_PROCESS_ERROR(CDBSessionMgr::GetInstance().GetServerState() == sgsAllReady);

    dbuser = usermgr.GetDBUserByName(pMsg->szUserName, pMsg->byServerGroup);
    if (dbuser)
    {
        LOG_PROCESS_ERROR(dbuser->m_state == CDBUser::dusLogout);
        LOG_PROCESS_ERROR(dbuser->m_dbstate == CDBUser::dtsFree);
		LOG_PROCESS_ERROR(dbuser->m_nServerGroup == pMsg->byServerGroup);

        dbuser->m_dwClientSessionID = pMsg->dwClientSessionID;

        usermgr.Pop(dbuser);

        dbuser->m_state = CDBUser::dusAuthed;

        bRet = usermgr.AddToSessionIDMap(dbuser);
        LOG_PROCESS_ERROR(bRet);

        if (dbuser->m_bRoleListCached)
        {
            bRet = CDBMessageHandler::GetInstance().DoGTSyncRoleList(dbuser);
            LOG_PROCESS_ERROR(bRet);
        }
        else
        {
            dbuser->m_dbstate = CDBUser::dtsListing;
            bRet = dbserver.m_threads[hash(pMsg->szUserName) % dbserver.m_dwThreadCount].AddUserTask(dbuser);
            LOG_PROCESS_ERROR(bRet);
        }
    }
    else
    {
        dbuser = usermgr.Pop();
        LOG_PROCESS_ERROR(dbuser);

        dbuser->m_state = CDBUser::dusAuthed;
        
        strxcpy(dbuser->m_szUserName, pMsg->szUserName, USER_NAME_LEN);
        dbuser->m_dwClientSessionID = pMsg->dwClientSessionID;
		dbuser->m_nServerGroup = pMsg->byServerGroup;

        bRet = usermgr.AddToUserNameMap(dbuser);
        LOG_PROCESS_ERROR(bRet);

        bRet = usermgr.AddToSessionIDMap(dbuser);
        LOG_PROCESS_ERROR(bRet);

        dbuser->m_dbstate = CDBUser::dtsListing;
        bRet = dbserver.m_threads[hash(pMsg->szUserName)%dbserver.m_dwThreadCount].AddUserTask(dbuser);
        LOG_PROCESS_ERROR(bRet);
    }

	dbserver.m_nOnlineUserCount++;
    INF("user <%08X> login, total %d",pMsg->dwClientSessionID, dbserver.m_nOnlineUserCount);	
	
	DB_SYS_LOG_SUCCESS(dbuser);
	return;
Exit0:
	DB_SYS_LOG_ERROR(dbuser);

    DoGTCloseClientSession(pMsg->dwClientSessionID);
    return;
}

void CDBMessageHandler::OnGTCreateRole(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession)
{
    BOOL bRet = FALSE;
    CDBServer& dbserver = CDBServer::GetInstance();
    CDBUserMgr& usermgr = dbserver.m_usermgr;
    CDBRoleMgr& rolemgr = dbserver.m_rolemgr;
    CDBUser* dbuser = NULL;
    CDBRole* dbrole = NULL;
    INT32 nUsableRoles = 0;
    T2D_CREATE_ROLE* pMsg = (T2D_CREATE_ROLE*)pPacketBuffer;

    LOG_PROCESS_ERROR(CDBSessionMgr::GetInstance().GetServerState() == sgsAllReady);

    dbuser = usermgr.GetDBUserBySessionID(pMsg->dwClientSessionID);
    LOG_PROCESS_ERROR(dbuser);
    LOG_PROCESS_ERROR(dbuser->m_state == CDBUser::dusAuthed);
    LOG_PROCESS_ERROR(dbuser->m_dbstate == CDBUser::dtsFree);

    if (dbuser->m_byRoleCount >= MAX_ROLE_PER_USER)
    {
        bRet = DoGTCreateRoleAck(pMsg->dwClientSessionID, errLoginCreateRoleTooMany, NULL);
        LOG_PROCESS_ERROR(bRet);

        return;
    }

    for (UINT8 i = 0; i < dbuser->m_byRoleCount; i++)
    {
        if (dbuser->m_BaseData[i].dwDeleteTime == 0)
            nUsableRoles++;
    }
    if (nUsableRoles >= MAX_USABLE_ROLE_PER_USER)
    {
        bRet = DoGTCreateRoleAck(pMsg->dwClientSessionID, errLoginCreateRoleTooMany, NULL);
        LOG_PROCESS_ERROR(bRet);

        return;
    }

    dbrole = rolemgr.Pop();
    LOG_PROCESS_ERROR(dbrole);
    LOG_PROCESS_ERROR(dbrole->m_pCurMem == NULL);

    dbrole->m_pCurMem = dbserver.m_memmgr.Pop();
    LOG_PROCESS_ERROR(dbrole->m_pCurMem);

    bRet = dbrole->m_MemList.Push(dbrole->m_pCurMem);
    LOG_PROCESS_ERROR(bRet);

    dbrole->m_dwRoleID = pMsg->dwRoleID;
    strxcpy(dbrole->m_CreateRoleParam.szUserName, dbuser->m_szUserName, USER_NAME_LEN);
    strxcpy(dbrole->m_CreateRoleParam.szRoleName, pMsg->szRoleName, ROLE_NAME_LEN);
    dbrole->m_CreateRoleParam.byClass = pMsg->byClass;
    dbrole->m_CreateRoleParam.bySex = pMsg->bySex;
    dbrole->m_CreateRoleParam.byHairType = pMsg->byHairType;
    dbrole->m_CreateRoleParam.byHairColor = pMsg->byHairColor;
    dbrole->m_CreateRoleParam.byFaceType = pMsg->byFaceType;
    dbrole->m_CreateRoleParam.bySkinColor = pMsg->bySkinColor;
    dbrole->m_dbuser = dbuser;

    dbuser->m_pDBRole[dbuser->m_byRoleCount] = dbrole;
    dbuser->m_dwRoleID[dbuser->m_byRoleCount] = pMsg->dwRoleID;
    dbuser->m_byRoleCount++;

    dbrole->m_dbtask = CDBRole::DB_TASK_CREATE_ROLE;
    dbuser->m_dbstate = CDBUser::dtsCreating;
    bRet = dbserver.m_threads[pMsg->dwClientSessionID % dbserver.m_dwThreadCount].AddRoleDbTask(dbrole);
    LOG_PROCESS_ERROR(bRet);

	DB_SYS_LOG_SUCCESS(dbuser);
    return;
Exit0:
	DB_SYS_LOG_ERROR(dbuser);
    DoGTCloseClientSession(pMsg->dwClientSessionID);

    return;
}

void CDBMessageHandler::OnGTDeleteRole(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession)
{
    BOOL bRet = FALSE;
    CDBServer& dbserver = CDBServer::GetInstance();
    CDBUserMgr& usermgr = dbserver.m_usermgr;
    CDBRoleMgr& rolemgr = dbserver.m_rolemgr;
    ROLE_DB_BASE_DATA* basedata = NULL;
    INT32 nDeletedRoles = 0;
    T2D_DELETE_ROLE* pMsg = (T2D_DELETE_ROLE*)pPacketBuffer;
    CDBUser* dbuser = NULL;
    CDBRole* dbrole = NULL;
    UINT8 rolepos = 0;

    LOG_PROCESS_ERROR(CDBSessionMgr::GetInstance().GetServerState() == sgsAllReady);

    dbuser = usermgr.GetDBUserBySessionID(pMsg->dwClientSessionID);
    LOG_PROCESS_ERROR(dbuser);
    LOG_PROCESS_ERROR(dbuser->m_state == CDBUser::dusAuthed);
    LOG_PROCESS_ERROR(dbuser->m_dbstate == CDBUser::dtsFree);

    for (; rolepos<dbuser->m_byRoleCount; rolepos++)
    {
        if (dbuser->m_dwRoleID[rolepos] == pMsg->dwRoleID)
        {
            break;
        }
    }
    LOG_PROCESS_ERROR(rolepos<dbuser->m_byRoleCount);

    for (UINT8 i = 0; i < dbuser->m_byRoleCount; i++)
    {
        if (dbuser->m_BaseData[i].dwDeleteTime != 0)
            nDeletedRoles++;
    }
    LOG_PROCESS_ERROR(nDeletedRoles < MAX_DELETE_ROLE_PER_USER);

    dbrole = rolemgr.GetDBRoleByID(pMsg->dwRoleID);
    LOG_PROCESS_ERROR(dbrole == dbuser->m_pDBRole[rolepos]);

    bRet = DoMSCanDeleteRole(pMsg->dwClientSessionID, pMsg->dwRoleID);
    LOG_PROCESS_ERROR(bRet);

    return;
Exit0:

    DoGTCloseClientSession(pMsg->dwClientSessionID);
    return;
}

void CDBMessageHandler::OnGTUnDeleteRole(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession)
{
    BOOL bRet = FALSE;
    CDBServer& dbserver = CDBServer::GetInstance();
    CDBUserMgr& usermgr = dbserver.m_usermgr;
    CDBRoleMgr& rolemgr = dbserver.m_rolemgr;
    ROLE_DB_BASE_DATA* basedata = NULL;
    INT32 nUsableRoles = 0;
    T2D_UNDELETE_ROLE* pMsg = (T2D_UNDELETE_ROLE*)pPacketBuffer;
    CDBUser* dbuser = NULL;
    CDBRole* dbrole = NULL;
    UINT8 rolepos = 0;

    LOG_PROCESS_ERROR(CDBSessionMgr::GetInstance().GetServerState() == sgsAllReady);

    dbuser = usermgr.GetDBUserBySessionID(pMsg->dwClientSessionID);
    LOG_PROCESS_ERROR(dbuser);
    LOG_PROCESS_ERROR(dbuser->m_state == CDBUser::dusAuthed);
    LOG_PROCESS_ERROR(dbuser->m_dbstate == CDBUser::dtsFree);

    for (; rolepos<dbuser->m_byRoleCount; rolepos++)
    {
        if (dbuser->m_dwRoleID[rolepos] == pMsg->dwRoleID)
        {
            break;
        }
    }
    LOG_PROCESS_ERROR(rolepos<dbuser->m_byRoleCount);

    for (UINT8 i = 0; i < dbuser->m_byRoleCount; i++)
    {
        if (dbuser->m_BaseData[i].dwDeleteTime == 0)
            nUsableRoles++;
    }
    LOG_PROCESS_ERROR(nUsableRoles < MAX_USABLE_ROLE_PER_USER);

    dbrole = rolemgr.GetDBRoleByID(pMsg->dwRoleID);
    LOG_PROCESS_ERROR(dbrole == dbuser->m_pDBRole[rolepos]);
    if (dbrole)
    {
        LOG_PROCESS_ERROR(dbrole->m_dbuser == dbuser);
        LOG_PROCESS_ERROR(dbrole->m_dbtask == CDBRole::DB_TASK_FREE);
        LOG_PROCESS_ERROR(dbrole->m_lockstate == CDBRole::LOCK_STATE_UNLOCKED);

        basedata = &dbuser->m_BaseData[rolepos];
        LOG_PROCESS_ERROR(basedata->dwDeleteTime != 0);

        bRet = rolemgr.Pop(dbrole);
        LOG_PROCESS_ERROR(bRet);

        basedata->dwDeleteTime = 0;

        dbrole->m_dwDeleteTime = 0;
        dbrole->m_dbtask = CDBRole::DB_TASK_UPDATE_ROLE_DELETE_TIME;
        dbuser->m_dbstate = CDBUser::dtsUpdatingRoleDeleteTime;
        bRet = dbserver.m_threads[pMsg->dwClientSessionID % dbserver.m_dwThreadCount].AddRoleDbTask(dbrole);
        LOG_PROCESS_ERROR(bRet);
    }
    else
    {
        dbrole = rolemgr.Pop();
        LOG_PROCESS_ERROR(dbrole);

        basedata = &dbuser->m_BaseData[rolepos];
        LOG_PROCESS_ERROR(basedata->dwDeleteTime != 0);

        basedata->dwDeleteTime = 0;

        dbuser->m_pDBRole[rolepos] = dbrole;
        dbrole->m_dwRoleID = pMsg->dwRoleID;
        dbrole->m_dwDeleteTime = 0;
        dbrole->m_dbuser = dbuser;
        dbrole->m_dbtask = CDBRole::DB_TASK_UPDATE_ROLE_DELETE_TIME_WITHOUT_DATA;
        dbuser->m_dbstate = CDBUser::dtsUpdatingRoleDeleteTime;
        bRet = dbserver.m_threads[pMsg->dwClientSessionID % dbserver.m_dwThreadCount].AddRoleDbTask(dbrole);
        LOG_PROCESS_ERROR(bRet);
    }

    DB_SYS_LOG_SUCCESS(dbuser);
    return;
Exit0:
    DB_SYS_LOG_ERROR(dbuser);

    DoGTCloseClientSession(pMsg->dwClientSessionID);
    return;
}

void CDBMessageHandler::OnGTForeverDeleteRole(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession)
{
    BOOL bRet = FALSE;
    CDBServer& dbserver = CDBServer::GetInstance();
    CDBUserMgr& usermgr = dbserver.m_usermgr;
    CDBRoleMgr& rolemgr = dbserver.m_rolemgr;
    ROLE_DB_BASE_DATA* basedata = NULL;
    T2D_FOREVER_DELETE_ROLE* pMsg = (T2D_FOREVER_DELETE_ROLE*)pPacketBuffer;
    CDBUser* dbuser = NULL;
    CDBRole* dbrole = NULL;
    UINT8 rolepos = 0;

    LOG_PROCESS_ERROR(CDBSessionMgr::GetInstance().GetServerState() == sgsAllReady);

    dbuser = usermgr.GetDBUserBySessionID(pMsg->dwClientSessionID);
    LOG_PROCESS_ERROR(dbuser);
    LOG_PROCESS_ERROR(dbuser->m_state == CDBUser::dusAuthed);
    LOG_PROCESS_ERROR(dbuser->m_dbstate == CDBUser::dtsFree);

    for (; rolepos < dbuser->m_byRoleCount; rolepos++)
    {
        if (dbuser->m_dwRoleID[rolepos] == pMsg->dwRoleID)
        {
            break;
        }
    }
    LOG_PROCESS_ERROR(rolepos < dbuser->m_byRoleCount);

    dbrole = rolemgr.GetDBRoleByID(pMsg->dwRoleID);
    LOG_PROCESS_ERROR(dbrole == dbuser->m_pDBRole[rolepos]);

    if (dbrole)
    {
        LOG_PROCESS_ERROR(dbrole->m_dbuser == dbuser);
        LOG_PROCESS_ERROR(dbrole->m_dbtask == CDBRole::DB_TASK_FREE);
        LOG_PROCESS_ERROR(dbrole->m_lockstate == CDBRole::LOCK_STATE_UNLOCKED);

        basedata = &dbuser->m_BaseData[rolepos];
        LOG_PROCESS_ERROR(basedata->dwDeleteTime != 0);

        bRet = rolemgr.Pop(dbrole);
        LOG_PROCESS_ERROR(bRet);

        dbrole->m_dbtask = CDBRole::DB_TASK_DELETE_ROLE;
        dbuser->m_dbstate = CDBUser::dtsDeleting;
        bRet = dbserver.m_threads[pMsg->dwClientSessionID % dbserver.m_dwThreadCount].AddRoleDbTask(dbrole);
        LOG_PROCESS_ERROR(bRet);
    }
    else
    {
        dbrole = dbserver.m_rolemgr.Pop();
        LOG_PROCESS_ERROR(dbrole);

        dbuser->m_pDBRole[rolepos] = dbrole;
        dbrole->m_dwRoleID = pMsg->dwRoleID;
        dbrole->m_dbuser = dbuser;
        dbrole->m_dbtask = CDBRole::DB_TASK_DELETE_ROLE_WITHOUT_DATA;
        dbuser->m_dbstate = CDBUser::dtsDeleting;
        bRet = dbserver.m_threads[pMsg->dwClientSessionID % dbserver.m_dwThreadCount].AddRoleDbTask(dbrole);
        LOG_PROCESS_ERROR(bRet);
    }

    DB_SYS_LOG_SUCCESS(dbuser);
    return;
Exit0:
    DB_SYS_LOG_ERROR(dbuser);

    DoGTCloseClientSession(pMsg->dwClientSessionID);
    return;
}
