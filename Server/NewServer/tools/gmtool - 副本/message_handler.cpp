/********************************************************************
	created:	6:8:2013   13:33
	file:		message_handler.cpp
	author:		Allan Tao
	
	purpose:	
*********************************************************************/

#include "stdafx.h"
#include "message_handler.h"
#include "session_mgr.h"
#include "tl_config.h"

#include "common_message.h"
#include "gmtl_message.h"
#include "string_ex.h"
#include "server_mgr.h"
#include "cmd_manager.h"
#include "base_role.h"
#include "gmtool.h"
#include "loader.h"
#include "gm_manager.h"
#include "data_mgr.h"
#include "gm_log.h"
#include "gm_def.h"
#include "str_def.h"
#include <QtWidgets/QMessageBox>
#include "server_list.h"
#include "role_info.h"
#include "logic.h"
#include "gm_version.h"
#include "ld_widget.h"


using namespace InternalMessage;


CMessageHandler CMessageHandler::ms_Instance;

CMessageHandler &CMessageHandler::GetInstance()
{
    return ms_Instance;
}

CMessageHandler::CMessageHandler()
{


}

CMessageHandler::~CMessageHandler()
{
    UnInit();
}

void CMessageHandler::OnAccepted(ISocketAcceptor* pSocketAcceptor, ISocketSession* pSocketSession)
{
    LOG_PROCESS_ERROR(pSocketSession);
    LOG_PROCESS_ERROR(pSocketAcceptor);

Exit0:
    return ;
}

void CMessageHandler::OnConnected(ISocketSession* pSocketSession)
{
    INT32       nRetCode = 0;

    GM_SESSION  *pGMSession = NULL;

    LOG_PROCESS_ERROR(pSocketSession);

    pGMSession = (GM_SESSION*)pSocketSession->GetUserData();
    LOG_PROCESS_ERROR(pGMSession);

    pGMSession->nConnectState = SESSION_CONNECTED;
    pGMSession->qwTimer = GetTickCount() + PING_SVR_TIMEOUT;           // todo_tq Allan Tao[7.8.2013] 

    // register
    //nRetCode = CSvrManager::GetInstance().SetGMState(pGMSession->dwSessionID, );
    //LOG_PROCESS_ERROR(nRetCode);

    nRetCode = DoRegisterToGM(pGMSession->dwSessionID);
    LOG_PROCESS_ERROR(nRetCode);

    INF("GM server connected");

    return;
Exit0:
    if (pSocketSession)
        pSocketSession->Close();
    return;
}

void CMessageHandler::OnRecv(ISocketSession* pSocketSession, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize)
{
    MESSAGE_HEADER  *pHeader = (MESSAGE_HEADER*)pPacketBuffer;

    LOG_PROCESS_ERROR(pSocketSession);
    LOG_PROCESS_ERROR(pPacketBuffer);

    LOG_PROCESS_ERROR(m_MessageFuncList[pHeader->wMsg]);

    (this->*m_MessageFuncList[pHeader->wMsg])(pPacketBuffer, dwSize, pSocketSession);

    if (pPacketBuffer)
        m_pPacketAllocator->Free(pPacketBuffer);

    return ;
Exit0:
    if (pHeader)
        CRI("Unknow message id %d size %d", pHeader->wMsg, dwSize);
    if (pPacketBuffer)
        m_pPacketAllocator->Free(pPacketBuffer);
    if (pSocketSession)
        pSocketSession->Close();
    return ;
}

void CMessageHandler::OnDisconnected(ISocketSession* pSocketSession, BOOL bRemoteShutdown)
{
    INT32       nRetCode = 0;
    GM_SESSION  *pGMSession = NULL;     // only GM Session

    LOG_PROCESS_ERROR(pSocketSession);

    pGMSession = (GM_SESSION*)pSocketSession->GetUserData();
    LOG_PROCESS_ERROR(pGMSession);

    pGMSession->pSocketSession = NULL;
    if (pGMSession->nConnectState != SESSION_DEAD)
        pGMSession->nConnectState = SESSION_DISCONNECTED;    
    pGMSession->qwTimer = GetTickCount() + RECONNECT_TIME;

    INF("GM server disconnected");

    //nRetCode = CSvrManager::GetInstance().UnregisteredGMSvr(pGMSession->dwSessionID);
    //LOG_PROCESS_ERROR(nRetCode);

    if (pGMSession->eState != GM_SVR_STATE_DISCONNECT && pGMSession->eState != GM_SVR_STATE_NONE)
    {
        nRetCode = CGMLog::GetInstance().Log("服务器[%s]断连!!!", QString::fromUtf8(pGMSession->szGMName).toLocal8Bit().data());
        LOG_PROCESS_ERROR(nRetCode);

        pGMSession->eState  = GM_SVR_STATE_DISCONNECT;
        nRetCode = g_gmtool.UpdateSvrNameColor(pGMSession->dwSessionID, GM_SVR_STATE_DISCONNECT);
        LOG_PROCESS_ERROR(nRetCode);
    }

    nRetCode = CServerMgr::GetInstance().UpdateSelectServer();
    LOG_PROCESS_ERROR(nRetCode);

    return ;
Exit0:
    return ;
}

BOOL CMessageHandler::Init(INet *pNet, IPacketAllocator *pPacketAllocator)
{
    LOG_PROCESS_ERROR(pNet);
    LOG_PROCESS_ERROR(pPacketAllocator);

    m_pNet = pNet;
    m_pPacketAllocator = pPacketAllocator;

    // register
    m_MessageFuncList[a2a_ping] = &CMessageHandler::OnAllPing;

    m_MessageFuncList[gm2tl_register_ack] = &CMessageHandler::OnGMRegisterAck;
    m_MessageFuncList[gm2tl_verify_ack] = &CMessageHandler::OnGMVerifyAck;
    m_MessageFuncList[gm2tl_login_ack] = &CMessageHandler::OnGMLoginAck;
    m_MessageFuncList[gm2tl_item_list_ntf] = &CMessageHandler::OnGMItemListNtf;
    m_MessageFuncList[gm2tl_logout_ack] = &CMessageHandler::OnGMLogoutAck;
    m_MessageFuncList[gm2tl_pre_query_ack] = &CMessageHandler::OnGMPreQueryAck;
    m_MessageFuncList[gm2tl_query_role_id_ack] = &CMessageHandler::OnGMQueryRoleID;
    m_MessageFuncList[gm2tl_query_role_data_ack] = &CMessageHandler::OnGMQueryRoleDataAck;

    m_MessageFuncList[gm2tl_forbid_chat_ack] = &CMessageHandler::OnGMForbidChatAck;
    m_MessageFuncList[gm2tl_freeze_role_ack] = &CMessageHandler::OnGMFreezeRoleAck;
    m_MessageFuncList[gm2tl_kick_role_ack] = &CMessageHandler::OnGMKickRoleAck;
    m_MessageFuncList[gm2tl_send_mail_ack] = &CMessageHandler::OnGMSendMailAck;
    m_MessageFuncList[gm2tl_announce_ack] = &CMessageHandler::OnGMAnnouceAck;
    m_MessageFuncList[gm2tl_get_announce_list_ack] = &CMessageHandler::OnGMGetAnnounceAck;
    m_MessageFuncList[gm2tl_del_announce_ack] = &CMessageHandler::OnGMDelAnnounce;
    m_MessageFuncList[gm2tl_log_ack] = &CMessageHandler::OnGMLogAck;
    m_MessageFuncList[gm2tl_exe_gm_str_ack] = &CMessageHandler::OnGMExecuteGMStrAck;
    m_MessageFuncList[gm2tl_load_role_data_ack] = &CMessageHandler::OnGMLoadRoleDataAck;
    m_MessageFuncList[gm2tl_modify_role_data_ack] = &CMessageHandler::OnGMModifyRoleDataAck;
    m_MessageFuncList[gm2tl_query_name_to_id_ack] = &CMessageHandler::OnGMQueryNameToIDAck;
    m_MessageFuncList[gm2tl_error_str] = &CMessageHandler::OnGMErrorStr;
    m_MessageFuncList[gm2tl_role_exe_gm_cmd] = &CMessageHandler::OnGMRoleExeGMCmd;

    m_MessageFuncList[gm2tl_select_group_ack] = &CMessageHandler::OnGMSelectGroupAck;
    m_MessageFuncList[gm2tl_query_exchange_log_ack] = &CMessageHandler::OnGMQueryExchangeLogAck;
    m_MessageFuncList[gm2tl_query_exchange_history_ack] = &CMessageHandler::OnGMQueryExchangeHistoryAck;
    m_MessageFuncList[gm2tl_exchange_price] = &CMessageHandler::OnGMExchangePrice;
    m_MessageFuncList[gm2tl_query_order_detail_ack] = &CMessageHandler::OnGMQueryOrderDetailAck;
    m_MessageFuncList[gm2tl_add_system_order_ack] = &CMessageHandler::OnGMAddSystemOrderAck;
    m_MessageFuncList[gm2tl_del_system_order_ack] = &CMessageHandler::OnGMDelSystemOrderAck;
    m_MessageFuncList[gm2tl_query_sys_exchange_info_ack] = &CMessageHandler::OnGMQuerySysExchangeInfoAck;
    m_MessageFuncList[gm2tl_get_exchange_limit_ack] = &CMessageHandler::OnGMGetExchangeLimitAck;
    m_MessageFuncList[gm2tl_set_exchange_limit_ack] = &CMessageHandler::OnGMSetExchangeLimitAck;



    return TRUE;
Exit0:
    return FALSE;
}

BOOL CMessageHandler::UnInit()
{
    return TRUE;
}

BOOL CMessageHandler::_SendGM(UINT32 dwSessionID, PACKET_BUFFER *pPacketBuffer, UINT32 dwSize, INT32 nOffSet)
{
    INT32   nRetCode = 0;
    GM_SESSION  *pGMSession  = CSessionMgr::GetInstance().GetGMSession(dwSessionID);

    LOG_PROCESS_ERROR(pGMSession);
    LOG_PROCESS_ERROR(pGMSession->pSocketSession);
    LOG_PROCESS_ERROR(pGMSession->nConnectState == SESSION_CONNECTED);

    nRetCode = pGMSession->pSocketSession->Send(pPacketBuffer, dwSize, nOffSet);
    LOG_PROCESS_ERROR(nRetCode == dwSize);

    return TRUE;
Exit0:
    return FALSE;
}

BOOL CMessageHandler::_BroadcastGM(PACKET_BUFFER *pPacketBuffer, UINT32 dwSize, INT32 nOffSet)
{
    INT32           nRetCode = 0;
    UINT32          dwSessionID = 0;
    PACKET_BUFFER   *pMsg = NULL;
    GM_SESSION      *pGMSession = NULL;
    INT32           nSendServerNum = 0;

    for (INT32 nIndex = 0; nIndex < CServerMgr::GetInstance().GetSelectedNum(); ++nIndex)
    {
        dwSessionID = CServerMgr::GetInstance().GetSessionIDByIndex(nIndex);
        LOG_PROCESS_ERROR(dwSessionID != 0xFFFFFFFF);

        pGMSession = CSessionMgr::GetInstance().GetGMSession(dwSessionID);

        LOG_PROCESS_ERROR(pGMSession);
        LOG_PROCESS_ERROR(pGMSession->pSocketSession);
        LOG_PROCESS_ERROR(pGMSession->nConnectState == SESSION_CONNECTED);

        pMsg = m_pPacketAllocator->Alloc(dwSize);
        LOG_PROCESS_ERROR(pMsg);

        memcpy(pMsg + nOffSet, pPacketBuffer + nOffSet, dwSize);

        nRetCode = pGMSession->pSocketSession->Send(pMsg, dwSize, nOffSet);
        if (nRetCode != dwSize)
        {
            LOG_CHECK_ERROR(nRetCode == dwSize);
            m_pPacketAllocator->Free(pMsg);
        }
        ++nSendServerNum;

        pMsg = NULL;
    }

    CCmdManager::GetInstance().SetExeServerNum(nSendServerNum);

    m_pPacketAllocator->Free(pPacketBuffer);
    return TRUE;
Exit0:
    return FALSE;
}

void CMessageHandler::OnAllPing(PACKET_BUFFER *pPacketBuffer, UINT32 dwSize, ISocketSession *pSocketSession)
{
    GM_SESSION  *pSession = NULL;
    
    LOG_PROCESS_ERROR(pSocketSession);

    pSession = (GM_SESSION*)pSocketSession->GetUserData();
    LOG_PROCESS_ERROR(pSession);
    
    pSession->qwTimer = GetTickCount() + PING_SVR_TIMEOUT;

    return ;
Exit0:
    if (pSocketSession)
        pSocketSession->Close();
    return ;
}

BOOL CMessageHandler::DoAllPing()
{
    INT32   nRetCode = 0;
    A2A_PING    *pMsg = NULL;

    for (INT32 nIndex = 0; nIndex < MAX_GM_SESSION_COUNT; ++nIndex)
    {
        GM_SESSION  *pGMSession  = CSessionMgr::GetInstance().GetGMSession(nIndex);
        if (pGMSession == NULL)
            continue;

        if (pGMSession->pSocketSession == NULL)
            continue;

        if (SESSION_CONNECTED != pGMSession->nConnectState)
            continue;

        pMsg = (A2A_PING*)m_pPacketAllocator->Alloc(sizeof(A2A_PING));
        LOG_PROCESS_ERROR(pMsg);

        pMsg->wMsg = a2a_ping;

        nRetCode = _SendGM(pGMSession->dwSessionID, (PACKET_BUFFER*)pMsg, sizeof(A2A_PING), 0);
        LOG_CHECK_ERROR(nRetCode);
        if ( !nRetCode && pMsg )
            m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);

        pMsg = NULL;
    }

    return TRUE;
Exit0:
    return FALSE;
}

BOOL CMessageHandler::DoRegisterToGM(UINT32 dwGMSessionID)
{
    INT32 nRetCode = 0;
    UINT32      dwIP;
    UINT16      wPort;
    TL2GM_REGISTER      *pMsg = NULL;

    GM_SESSION *pGMSession = CSessionMgr::GetInstance().GetGMSession(dwGMSessionID);
    LOG_PROCESS_ERROR(pGMSession != NULL);
    LOG_PROCESS_ERROR(pGMSession->pSocketSession != NULL);

    pMsg = (TL2GM_REGISTER*)m_pPacketAllocator->Alloc(sizeof(TL2GM_REGISTER));
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = tl2gm_register;

    nRetCode = pGMSession->pSocketSession->GetAddress(dwIP, wPort);
    LOG_PROCESS_ERROR(nRetCode);

    pMsg->dwIP = dwIP;
    pMsg->wPort = wPort;
    nRetCode = gethostname(pMsg->szComputerName, sizeof(pMsg->szComputerName));
    LOG_PROCESS_ERROR(0 == nRetCode);

    nRetCode = _SendGM(pGMSession->dwSessionID, (PACKET_BUFFER*)pMsg, sizeof(TL2GM_REGISTER));
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

BOOL CMessageHandler::DoVerify(UINT32 dwGMSessionID, const char *pcszName, const char *pcszPwd)
{
    INT32   nRetCode = 0;
    TL2GM_VERIFY  *pMsg = NULL;

    LOG_PROCESS_ERROR(pcszName);
    LOG_PROCESS_ERROR(pcszPwd);

    pMsg = (TL2GM_VERIFY*)m_pPacketAllocator->Alloc(sizeof(TL2GM_VERIFY));
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = tl2gm_verify;
    strxcpy(pMsg->szName, pcszName, sizeof(pMsg->szName));
    strxcpy(pMsg->szPwd, pcszPwd, sizeof(pMsg->szPwd));

    nRetCode = _SendGM(dwGMSessionID, (PACKET_BUFFER*)pMsg, sizeof(TL2GM_VERIFY));
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

BOOL CMessageHandler::DoLoginToGM(UINT32 dwGMSessionID, const char *pcszName, const char *pcszPwd)
{
    INT32   nRetCode = 0;
    TL2GM_LOGIN  *pMsg = NULL;

    LOG_PROCESS_ERROR(pcszName);
    LOG_PROCESS_ERROR(pcszPwd);
    
    pMsg = (TL2GM_LOGIN*)m_pPacketAllocator->Alloc(sizeof(TL2GM_LOGIN));
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = tl2gm_login;
    pMsg->nVersion = GM_MAJOR_VERSION;
    pMsg->nDependVersion = GM_DEPEND_VERSION;
    strxcpy(pMsg->szName, pcszName, sizeof(pMsg->szName));
    strxcpy(pMsg->szPwd, pcszPwd, sizeof(pMsg->szPwd));

    nRetCode = _SendGM(dwGMSessionID, (PACKET_BUFFER*)pMsg, sizeof(TL2GM_LOGIN));
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

BOOL CMessageHandler::DoLogoutToGM(UINT32 dwGMSessionID)
{
    INT32       nRetCode = 0;

    TL2GM_LOGOUT    *pMsg = (TL2GM_LOGOUT*)m_pPacketAllocator->Alloc(sizeof(TL2GM_LOGOUT));
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = tl2gm_logout;

    nRetCode = _SendGM(dwGMSessionID, (PACKET_BUFFER*)pMsg, sizeof(TL2GM_LOGOUT));
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

BOOL CMessageHandler::DoPreQuery(const char *pcszRoleName)
{
    INT32       nRetCode = 0;
    TL2GM_PRE_QUERY *pMsg = NULL;

    LOG_PROCESS_ERROR(pcszRoleName);

    pMsg = (TL2GM_PRE_QUERY *)m_pPacketAllocator->Alloc(sizeof(TL2GM_PRE_QUERY));
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = tl2gm_pre_query;
    strxcpy(pMsg->szRoleName, pcszRoleName, sizeof(pMsg->szRoleName));

    nRetCode = _BroadcastGM((PACKET_BUFFER*)pMsg, sizeof(TL2GM_PRE_QUERY));
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

BOOL CMessageHandler::DoQueryRoleID(INT32 nQueryType, const char *pcszName)
{
    INT32       nRetCode = 0;
    TL2GM_QUERY_ROLE_ID *pMsg = NULL;

    LOG_PROCESS_ERROR(pcszName);

    pMsg = (TL2GM_QUERY_ROLE_ID *)m_pPacketAllocator->Alloc(sizeof(TL2GM_QUERY_ROLE_ID));
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = tl2gm_query_role_id;
    pMsg->nQueryType = nQueryType;
    strxcpy(pMsg->szName, pcszName, sizeof(pMsg->szName));

    nRetCode = _BroadcastGM((PACKET_BUFFER*)pMsg, sizeof(TL2GM_QUERY_ROLE_ID));
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

BOOL CMessageHandler::DoQueryRoleData(UINT32 dwRoleID)
{
    INT32   nRetCode = 0;
    TL2GM_QUERY_ROLE_DATA *pMsg = (TL2GM_QUERY_ROLE_DATA*)m_pPacketAllocator->Alloc(sizeof(TL2GM_QUERY_ROLE_DATA));
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = tl2gm_query_role_data;
    pMsg->dwRoleID = dwRoleID;

    nRetCode = _BroadcastGM((PACKET_BUFFER*)pMsg, sizeof(TL2GM_QUERY_ROLE_DATA));
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

BOOL CMessageHandler::DoForbidChat(UINT32 dwTime, UINT32 dwRoleID)
{
    INT32       nRetCode = 0;
    TL2GM_FORBID_CHAT   *pMsg = NULL;

    pMsg = (TL2GM_FORBID_CHAT *)m_pPacketAllocator->Alloc(sizeof(TL2GM_FORBID_CHAT));
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = tl2gm_forbid_chat;
    pMsg->dwTime = dwTime;
    pMsg->dwRoleID = dwRoleID;

    nRetCode = _BroadcastGM((PACKET_BUFFER*)pMsg, sizeof(TL2GM_FORBID_CHAT));
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

BOOL CMessageHandler::DoFreezeRole(UINT32 dwTime, UINT32 dwRoleID)
{
    INT32       nRetCode = 0;
    TL2GM_FREEZE_ROLE   *pMsg = NULL;

    pMsg = (TL2GM_FREEZE_ROLE *)m_pPacketAllocator->Alloc(sizeof(TL2GM_FREEZE_ROLE));
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = tl2gm_freeze_role;
    pMsg->dwTime = dwTime;
    pMsg->dwRoleID = dwRoleID;

    nRetCode = _BroadcastGM((PACKET_BUFFER*)pMsg, sizeof(TL2GM_FREEZE_ROLE));
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

BOOL CMessageHandler::DoKickRole(UINT32 dwRoleID)
{
    INT32       nRetCode = 0;
    TL2GM_KICK_ROLE   *pMsg = NULL;
    const char  *pNameBuffer = NULL;

    pMsg = (TL2GM_KICK_ROLE *)m_pPacketAllocator->Alloc(sizeof(TL2GM_KICK_ROLE));
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = tl2gm_kick_role;
    pMsg->dwRoleID = dwRoleID;

    nRetCode = _BroadcastGM((PACKET_BUFFER*)pMsg, sizeof(TL2GM_KICK_ROLE));
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

BOOL CMessageHandler::DoSendMail(UINT32 dwRoleID, const char *pcszSubject, const char *pcszContent, const char *pcszReason, UINT32 dwItemID, INT32 nItemNum)
{
    INT32       nRetCode = 0;
    TL2GM_SEND_MAIL *pMsg = NULL;

    LOG_PROCESS_ERROR(pcszSubject);
    LOG_PROCESS_ERROR(pcszContent);
    LOG_PROCESS_ERROR(pcszReason);

    pMsg = (TL2GM_SEND_MAIL *)m_pPacketAllocator->Alloc(sizeof(TL2GM_SEND_MAIL));
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = tl2gm_send_mail;
    strxcpy(pMsg->szSubject, pcszSubject, sizeof(pMsg->szSubject));
    strxcpy(pMsg->szContent, pcszContent, sizeof(pMsg->szContent));
    strxcpy(pMsg->szReason, pcszReason, sizeof(pMsg->szReason));

    pMsg->dwItemID = dwItemID;
    pMsg->nItemNum = nItemNum;
    pMsg->dwRoleID = dwRoleID;

    nRetCode = _BroadcastGM((PACKET_BUFFER*)pMsg, sizeof(TL2GM_SEND_MAIL));
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

BOOL CMessageHandler::DoAnnounce(INT32 nGroupID, UINT32 dwBeginTime, INT32 nRepeatNum, INT32 nIntervalTime, const char *pcszText)
{
    INT32       nRetCode = 0;
    TL2GM_ANNOUNCE   *pMsg = NULL;
    INT32       nLength = 0;

    LOG_PROCESS_ERROR(pcszText);
    nLength = strlen(pcszText) + 1;
    LOG_PROCESS_ERROR((nLength + sizeof(TL2GM_ANNOUNCE) * 2) < MAX_MESSAGE_SIZE);

    pMsg = (TL2GM_ANNOUNCE *)m_pPacketAllocator->Alloc(MAX_MESSAGE_SIZE);
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = tl2gm_announce;
    pMsg->nGroupID = nGroupID;
    pMsg->dwBeginTime = dwBeginTime;
    pMsg->nRepeatNum = nRepeatNum;
    pMsg->dwIntervalTime = nIntervalTime;
    strxcpy(pMsg->szText, pcszText, nLength);
    
    nRetCode = _BroadcastGM((PACKET_BUFFER*)pMsg, sizeof(TL2GM_ANNOUNCE) + nLength);
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

BOOL CMessageHandler::DoGetAnnounceList(INT32 nGroupID)
{
    INT32       nRetCode = 0;
    TL2GM_GET_ANNOUNCE_LIST   *pMsg = NULL;

    pMsg = (TL2GM_GET_ANNOUNCE_LIST *)m_pPacketAllocator->Alloc(sizeof(TL2GM_GET_ANNOUNCE_LIST));
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = tl2gm_get_announce_list;
    pMsg->nGroupID = nGroupID;

    nRetCode = _BroadcastGM((PACKET_BUFFER*)pMsg, sizeof(TL2GM_GET_ANNOUNCE_LIST));
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

BOOL CMessageHandler::DoDelAnnounce(INT32 nGroupID, UINT32 dwAnnounceSerial)
{
    INT32       nRetCode = 0;
    TL2GM_DEL_ANNOUNCE   *pMsg = NULL;

    pMsg = (TL2GM_DEL_ANNOUNCE *)m_pPacketAllocator->Alloc(sizeof(TL2GM_DEL_ANNOUNCE));
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = tl2gm_del_announce;
    pMsg->nGroupID = nGroupID;
    pMsg->dwAnnounceSerial = dwAnnounceSerial;

    nRetCode = _BroadcastGM((PACKET_BUFFER*)pMsg, sizeof(TL2GM_DEL_ANNOUNCE));
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

BOOL CMessageHandler::DoLog(INT32 nLogType, UINT32 dwBeginTime, UINT32 dwEndTime, const char *pcszQueryStr)
{
    INT32       nRetCode = 0;
    INT32       nLength = 0;
    TL2GM_LOG *pMsg = NULL;

    LOG_PROCESS_ERROR(pcszQueryStr);

    pMsg = (TL2GM_LOG *)m_pPacketAllocator->Alloc(MAX_MESSAGE_SIZE);
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = tl2gm_log;
    nLength = strlen(pcszQueryStr) + 1;
    pMsg->nLogType = nLogType;
    pMsg->dwBeginTime = dwBeginTime;
    pMsg->dwEndTime = dwEndTime;
    strxcpy(pMsg->szQueryStr, pcszQueryStr, nLength);

    nLength += sizeof(TL2GM_LOG);

    nRetCode = _BroadcastGM((PACKET_BUFFER*)pMsg, nLength);
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

BOOL CMessageHandler::DoExecuteGMStrCmd(const char* pcszStrCmd)
{
    INT32       nRetCode = 0;
    INT32       nLength = 0;
    TL2GM_EXE_GM_STR *pMsg = NULL;

    LOG_PROCESS_ERROR(pcszStrCmd);

    nLength = strlen(pcszStrCmd) + 1;

    LOG_PROCESS_ERROR(nLength < (MAX_MESSAGE_SIZE - 100));
    pMsg = (TL2GM_EXE_GM_STR *)m_pPacketAllocator->Alloc(MAX_MESSAGE_SIZE);
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = tl2gm_exe_gm_str;
    strxcpy(pMsg->szStr, pcszStrCmd, nLength + 1);
    
    nRetCode = _BroadcastGM((PACKET_BUFFER*)pMsg, sizeof(TL2GM_EXE_GM_STR) + nLength);
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

BOOL CMessageHandler::DoQueryNameToID(INT32 nIndex, const char *pcszRoleName)
{
    INT32       nRetCode = 0;
    INT32       nLength = 0;
    TL2GM_QUERY_NAME_TO_ID *pMsg = NULL;

    LOG_PROCESS_ERROR(pcszRoleName);
    pMsg = (TL2GM_QUERY_NAME_TO_ID *)m_pPacketAllocator->Alloc(sizeof(TL2GM_QUERY_NAME_TO_ID));
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = tl2gm_query_name_to_id;
    pMsg->nIndex = nIndex;
    strxcpy(pMsg->szRoleName, pcszRoleName, sizeof(pMsg->szRoleName));

    nRetCode = _BroadcastGM((PACKET_BUFFER*)pMsg, sizeof(TL2GM_QUERY_NAME_TO_ID));
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

BOOL CMessageHandler::DoLoadRoleData(UINT32 dwRoleID)
{
    INT32       nRetCode = 0;
    INT32       nLength = 0;
    TL2GM_LOAD_ROLE_DATA *pMsg = NULL;

    pMsg = (TL2GM_LOAD_ROLE_DATA *)m_pPacketAllocator->Alloc(sizeof(TL2GM_LOAD_ROLE_DATA));
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = tl2gm_load_role_data;
    pMsg->dwRoleID = dwRoleID;

    nRetCode = _BroadcastGM((PACKET_BUFFER*)pMsg, sizeof(TL2GM_LOAD_ROLE_DATA));
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

BOOL CMessageHandler::DoModifyRoleData(UINT32 dwRoleID, UINT32 dwTargetRoleID, INT32 nLength, const char *pcszData, const char *pcszReason)
{
    INT32       nRetCode = 0;
    TL2GM_MODIFY_ROLE_DATA *pMsg = NULL;

    LOG_PROCESS_ERROR(pcszData);
    LOG_PROCESS_ERROR(pcszReason);

    pMsg = (TL2GM_MODIFY_ROLE_DATA *)m_pPacketAllocator->Alloc(MAX_MESSAGE_SIZE);
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = tl2gm_modify_role_data;
    strxcpy(pMsg->szReason, pcszReason, sizeof(pMsg->szReason));
    memcpy(pMsg->szData, pcszData, nLength);
    pMsg->nLength = nLength;
    pMsg->dwRoleID = dwRoleID;
    pMsg->dwTargetRoleID = dwTargetRoleID;

    nLength = sizeof(TL2GM_MODIFY_ROLE_DATA) + pMsg->nLength;

    nRetCode = _BroadcastGM((PACKET_BUFFER*)pMsg, nLength);
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

BOOL CMessageHandler::DoReleaseRole(UINT32 dwGMSessionID, UINT32 dwRoleID)
{
    INT32       nRetCode = 0;
    INT32       nLength = 0;
    TL2GM_RELEASE_ROLE *pMsg = NULL;

    pMsg = (TL2GM_RELEASE_ROLE *)m_pPacketAllocator->Alloc(sizeof(TL2GM_RELEASE_ROLE));
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = tl2gm_release_role;
    pMsg->dwRoleID = dwRoleID;

    nRetCode = _SendGM(dwGMSessionID, (PACKET_BUFFER*)pMsg, sizeof(TL2GM_RELEASE_ROLE));
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

BOOL CMessageHandler::DoExeRoleGMCmd(UINT32 dwRoleID, const char *pcszGM, const char *pcszReason)
{
    INT32       nRetCode = 0;
    TL2GM_ROLE_EXE_CMD *pMsg = NULL;

    LOG_PROCESS_ERROR(pcszGM);
    LOG_PROCESS_ERROR(pcszReason);

    pMsg = (TL2GM_ROLE_EXE_CMD *)m_pPacketAllocator->Alloc(sizeof(TL2GM_ROLE_EXE_CMD));
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = tl2gm_role_exe_cmd;
    strxcpy(pMsg->szReason, pcszReason, sizeof(pMsg->szReason));
    strxcpy(pMsg->szGM, pcszGM, sizeof(pMsg->szGM));
    pMsg->dwRoleID = dwRoleID;

    nRetCode = _BroadcastGM((PACKET_BUFFER*)pMsg, sizeof(TL2GM_ROLE_EXE_CMD));
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}



BOOL CMessageHandler::DoSelectGroup(INT32 nGroupID)
{
    INT32       nRetCode = 0;
    TL2GM_SELECT_GROUP  *pMsg = (TL2GM_SELECT_GROUP*)m_pPacketAllocator->Alloc(sizeof(TL2GM_SELECT_GROUP));
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = tl2gm_select_group;
    pMsg->byGroupID = nGroupID;

    nRetCode = _BroadcastGM((PACKET_BUFFER*)pMsg, sizeof(TL2GM_SELECT_GROUP));
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

BOOL CMessageHandler::DoQueryExchangeLog(INT32 nGroupID)
{
    INT32       nRetCode = 0;
    TL2GM_EXCHANGE_PRICE *pMsg = (TL2GM_EXCHANGE_PRICE*)m_pPacketAllocator->Alloc(sizeof(TL2GM_EXCHANGE_PRICE));
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = tl2gm_exchange_price;
    pMsg->byGroupID = nGroupID;

    nRetCode = _BroadcastGM((PACKET_BUFFER*)pMsg, sizeof(TL2GM_EXCHANGE_PRICE));
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;   
}

BOOL CMessageHandler::DoQueryExchangeHistory(INT32 nGroupID)
{
    INT32       nRetCode = 0;
    TL2GM_EXCHANGE_HISTORY  *pMsg = (TL2GM_EXCHANGE_HISTORY*)m_pPacketAllocator->Alloc(sizeof(TL2GM_EXCHANGE_HISTORY));
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = tl2gm_exchange_history;
    pMsg->byGroupID = nGroupID;

    nRetCode = _BroadcastGM((PACKET_BUFFER*)pMsg, sizeof(TL2GM_EXCHANGE_HISTORY));
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

BOOL CMessageHandler::DoQueryOrderDetail(INT32 nGroupID, UINT8 byOrderType, INT32 nPrice)
{
    INT32       nRetCode = 0;
    TL2GM_ORDER_DETAIL  *pMsg = (TL2GM_ORDER_DETAIL*)m_pPacketAllocator->Alloc(sizeof(TL2GM_ORDER_DETAIL));
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = tl2gm_order_detail;
    pMsg->byGroupID = nGroupID;
    pMsg->nPrice = nPrice;
    pMsg->byOrderType = byOrderType;

    nRetCode = _BroadcastGM((PACKET_BUFFER*)pMsg, sizeof(TL2GM_ORDER_DETAIL));
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

BOOL CMessageHandler::DoAddSystemOrder( INT32 nGroupID, INT32 nPrice, INT32 nCount)
{
    INT32       nRetCode = 0;
    TL2GM_ADD_SYSTEM_ORDER  *pMsg = (TL2GM_ADD_SYSTEM_ORDER*)m_pPacketAllocator->Alloc(sizeof(TL2GM_ADD_SYSTEM_ORDER));
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = tl2gm_add_system_order;
    pMsg->byGroupID = nGroupID;
    pMsg->nPrice = nPrice;
    pMsg->nCount = nCount;

    nRetCode = _BroadcastGM((PACKET_BUFFER*)pMsg, sizeof(TL2GM_ADD_SYSTEM_ORDER));
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

BOOL CMessageHandler::DoDelSystemOrder(INT32 nGroupID, UINT64 qwOrderID)
{
    INT32       nRetCode = 0;
    TL2GM_DEL_SYSTEM_ORDER  *pMsg = (TL2GM_DEL_SYSTEM_ORDER*)m_pPacketAllocator->Alloc(sizeof(TL2GM_DEL_SYSTEM_ORDER));
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = tl2gm_del_system_order;
    pMsg->byGroupID = nGroupID;
    pMsg->qwOrderID = qwOrderID;

    nRetCode = _BroadcastGM((PACKET_BUFFER*)pMsg, sizeof(TL2GM_DEL_SYSTEM_ORDER));
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

BOOL CMessageHandler::DoQuerySysExchangeInfo(INT32 nGroupID, INT32 nFlag, UINT32 dwBeginToday, UINT32 dwEndToday, UINT32 dwBeginHour, UINT32 dwEndHour)
{
    INT32       nRetCode = 0;
    TL2GM_SYS_EXCHANGE_INFO  *pMsg = (TL2GM_SYS_EXCHANGE_INFO*)m_pPacketAllocator->Alloc(sizeof(TL2GM_SYS_EXCHANGE_INFO));
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = tl2gm_sys_exchange_info;
    pMsg->byGroupID = nGroupID;
    pMsg->byFlag = nFlag;
    pMsg->dwBeginDayTime = dwBeginToday;
    pMsg->dwEndDayTime = dwEndToday;
    pMsg->dwBeginHourTime = dwBeginHour;
    pMsg->dwEndHourTime = dwEndHour;

    nRetCode = _BroadcastGM((PACKET_BUFFER*)pMsg, sizeof(TL2GM_SYS_EXCHANGE_INFO));
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

BOOL CMessageHandler::DoQueryExchangeLimit(INT32 nGroupID)
{
    INT32       nRetCode = 0;
    TL2GM_GET_EXCHANGE_LIMIT  *pMsg = (TL2GM_GET_EXCHANGE_LIMIT*)m_pPacketAllocator->Alloc(sizeof(TL2GM_GET_EXCHANGE_LIMIT));
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = tl2gm_get_exchange_limit;
    pMsg->byGroupID = (UINT8)nGroupID;

    nRetCode = _BroadcastGM((PACKET_BUFFER*)pMsg, sizeof(TL2GM_GET_EXCHANGE_LIMIT));
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

BOOL CMessageHandler::DoSetExchangeLimit(INT32 nGroupID, INT32 nPriceHigh, INT32 nPriceLow, INT32 nSingleOrderLimit, INT32 nDailyOrderLimit)
{
    INT32       nRetCode = 0;
    TL2GM_SET_EXCHANGE_LIMIT  *pMsg = (TL2GM_SET_EXCHANGE_LIMIT*)m_pPacketAllocator->Alloc(sizeof(TL2GM_SET_EXCHANGE_LIMIT));
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = tl2gm_set_exchange_limit;
    pMsg->byGroupID = nGroupID;
    pMsg->nPriceHigh = nPriceHigh;
    pMsg->nPriceLow = nPriceLow;
    pMsg->nSingleOrderLimit = nSingleOrderLimit;
    pMsg->nDailyOrderLimit = nDailyOrderLimit;

    nRetCode = _BroadcastGM((PACKET_BUFFER*)pMsg, sizeof(TL2GM_SET_EXCHANGE_LIMIT));
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}







void CMessageHandler::OnGMRegisterAck(PACKET_BUFFER *pPacketBuffer, UINT32 dwSize, ISocketSession *pSocketSession)
{
    INT32       nRetCode = 0;
    GM_SESSION  *pGMSession = NULL;
    GM2TL_REGISTER_ACK  *pMsg = (GM2TL_REGISTER_ACK*)pPacketBuffer;
    LOG_PROCESS_ERROR(pMsg);

    pGMSession = (GM_SESSION *)pSocketSession->GetUserData();
    LOG_PROCESS_ERROR(pGMSession);

    if (pMsg->nResult == errSuccess)
    {
        pGMSession->eState = GM_SVR_STATE_REGISTERED;
        nRetCode = g_gmtool.UpdateSvrNameColor(pGMSession->dwSessionID, GM_SVR_STATE_REGISTERED);
        LOG_PROCESS_ERROR(nRetCode);
    }
    else
    {
        pGMSession->nConnectState = SESSION_DEAD;
        CGMLog::GetInstance().Log("未能注册到服务器[%s]", QString::fromUtf8(pGMSession->szGMName).toLocal8Bit().data());
    }

    return ;
Exit0:
    return ;
}

void CMessageHandler::OnGMVerifyAck(PACKET_BUFFER *pPacketBuffer, UINT32 dwSize, ISocketSession *pSocketSession)
{
    INT32           nRetCode = 0;
    CMD_DATA_BASE        *pCmd = NULL;
    GM_SESSION      *pGMSession = NULL;

    GM2TL_VERIFY_ACK *pMsg = (GM2TL_VERIFY_ACK*)pPacketBuffer;
    LOG_PROCESS_ERROR(pMsg);

    pGMSession = (GM_SESSION *)pSocketSession->GetUserData();
    LOG_PROCESS_ERROR(pGMSession);

    nRetCode = g_loader.VerifyUser(pMsg->nResult, pMsg->bLD);
    LOG_PROCESS_ERROR(nRetCode);

    nRetCode = g_gmtool.SetTitle();

Exit0:
    return ;
}

void CMessageHandler::OnGMLoginAck(PACKET_BUFFER *pPacketBuffer, UINT32 dwSize, ISocketSession *pSocketSession)
{
    INT32           nRetCode = 0;
    CMD_DATA_BASE        *pCmd = NULL;
    GM_SESSION      *pGMSession = NULL;

    GM2TL_LOGIN_ACK *pMsg = (GM2TL_LOGIN_ACK*)pPacketBuffer;
    LOG_PROCESS_ERROR(pMsg);

    pGMSession = (GM_SESSION *)pSocketSession->GetUserData();
    LOG_PROCESS_ERROR(pGMSession);

    if (errSuccess == pMsg->nResult)
    {
        pGMSession->eState  = GM_SVR_STATE_LOGIN;
        nRetCode = g_gmtool.UpdateSvrNameColor(pGMSession->dwSessionID, GM_SVR_STATE_LOGIN);
        LOG_PROCESS_ERROR(nRetCode);

        nRetCode = CGMLog::GetInstance().Log("成功登陆服务器[%s]", QString::fromUtf8(pGMSession->szGMName).toLocal8Bit().data());
        LOG_PROCESS_ERROR(nRetCode);
    }
    else
    {
        nRetCode = CGMLog::GetInstance().Log("登陆服务器失败[%s], errCode[%d]", QString::fromUtf8(pGMSession->szGMName).toLocal8Bit().data(), pMsg->nResult);
        LOG_PROCESS_ERROR(nRetCode);
    }

    nRetCode = CServerMgr::GetInstance().UpdateSelectServer();
    LOG_PROCESS_ERROR(nRetCode);

    g_gmtool.ServerLogin(pGMSession->nSvrID);

    return ;
Exit0:
    nRetCode = CServerMgr::GetInstance().UpdateSelectServer();
    LOG_CHECK_ERROR(nRetCode);
    return;
}

void CMessageHandler::OnGMItemListNtf(PACKET_BUFFER *pPacketBuffer, UINT32 dwSize, ISocketSession *pSocketSession)
{
    INT32           nRetCode = 0;
    GM_SESSION      *pGMSession = NULL;
    GM2TL_ITEM_LIST_NTF *pMsg = (GM2TL_ITEM_LIST_NTF*)pPacketBuffer;
    LOG_PROCESS_ERROR(pMsg);

    pGMSession = (GM_SESSION *)pSocketSession->GetUserData();
    LOG_PROCESS_ERROR(pGMSession);

    INF("recv item list count[%d] cls[%d]", pMsg->nCount, pMsg->bCLS);

    if (pMsg->bCLS == TRUE)
    {
        CDataMgr::GetInstance().ClearItemMap(pGMSession->dwSessionID);
    }

    for (INT32 i = 0; i < pMsg->nCount; ++i)
    {
        nRetCode = CDataMgr::GetInstance().AddItem(pGMSession->dwSessionID, pMsg->data[i].dwTempID, pMsg->data[i].szName);
        LOG_CHECK_ERROR(nRetCode);
    }

    return;
Exit0:
    return;
}

void CMessageHandler::OnGMLogoutAck(PACKET_BUFFER *pPacketBuffer, UINT32 dwSize, ISocketSession *pSocketSession)
{
    INT32       nRetCode = 0;
    CMD_DATA_BASE        *pCmd = NULL;
    GM_SESSION      *pGMSession = NULL;

    GM2TL_LOGOUT_ACK *pMsg = (GM2TL_LOGOUT_ACK*)pPacketBuffer;
    LOG_PROCESS_ERROR(pMsg);

    pGMSession = (GM_SESSION *)pSocketSession->GetUserData();
    LOG_PROCESS_ERROR(pGMSession);

    pGMSession->eState  = GM_SVR_STATE_REGISTERED;
    nRetCode = g_gmtool.UpdateSvrNameColor(pGMSession->dwSessionID, GM_SVR_STATE_REGISTERED);
    LOG_PROCESS_ERROR(nRetCode);

    g_gmtool.LogoutServer(pGMSession->dwSessionID);

    if (g_gmtool.GetLDWidget())
        g_gmtool.GetLDWidget()->UnInit();

    nRetCode = CGMLog::GetInstance().Log("成功登出服务器[%s]", QString::fromUtf8(pGMSession->szGMName).toLocal8Bit().data());
    LOG_PROCESS_ERROR(nRetCode);

    nRetCode = CServerMgr::GetInstance().UpdateSelectServer();
    LOG_PROCESS_ERROR(nRetCode);

    return ;
Exit0:
    nRetCode = CServerMgr::GetInstance().UpdateSelectServer();
    LOG_CHECK_ERROR(nRetCode);
    return;
}


void CMessageHandler::OnGMPreQueryAck(PACKET_BUFFER *pPacketBuffer, UINT32 dwSize, ISocketSession *pSocketSession)
{
    INT32           nRetCode = 0;
    GM_SESSION      *pGMSession = NULL;
    CMD_BASE        *pCmd = NULL;
    PRE_QUERY       *pQueryCmd = NULL;
    GM2TL_PRE_QUERY_ACK *pMsg = (GM2TL_PRE_QUERY_ACK*)pPacketBuffer;

    pGMSession = (GM_SESSION *)pSocketSession->GetUserData();
    LOG_PROCESS_ERROR(pGMSession);

    pCmd = CCmdManager::GetInstance().GetCurrentCmd();
    LOG_PROCESS_ERROR(pCmd);
    LOG_PROCESS_ERROR(pCmd->nSvrNum > 0);
    LOG_PROCESS_ERROR(pCmd->nType == CMD_PRE_QUERY);

    pQueryCmd = (PRE_QUERY *)pCmd;
    --pCmd->nSvrNum;

    LOG_PROCESS_ERROR(pQueryCmd->pCmd);

    if (pMsg->dwRoleID == 0)
    {
        g_gmtool.OutputMessageBox("未查询到角色");
        LOG_PROCESS_ERROR(FALSE);
    }

    switch (pQueryCmd->nCmdType)
    {
    case CMD_QUERY_ROLE_DATA:
    {
        QUERY_ROLE_DATA *pQueryRole = (QUERY_ROLE_DATA*)pQueryCmd->pCmd;

        nRetCode = strncmp(pQueryRole->szRoleName, pMsg->szRoleName, ROLE_NAME_LEN);
        LOG_PROCESS_ERROR(nRetCode == 0);
        pQueryRole->dwRoleID = pMsg->dwRoleID;

        nRetCode = CCmdManager::GetInstance().QueryRoleData(pQueryRole);
        LOG_PROCESS_ERROR(nRetCode);
    }
        break;
    case CMD_LOAD_ROLE_DATA:
    {
        LOAD_ROLE_DATA* pLoadRole = (LOAD_ROLE_DATA*)pQueryCmd->pCmd;

        nRetCode = strncmp(pLoadRole->szRoleName, pMsg->szRoleName, ROLE_NAME_LEN);
        LOG_PROCESS_ERROR(nRetCode == 0);

        pLoadRole->dwRoleID = pMsg->dwRoleID;

        nRetCode = CCmdManager::GetInstance().LoadRoleData(pLoadRole);
        LOG_PROCESS_ERROR(nRetCode);
    }
        break;
    case CMD_EXE_ROLE_GM_CMD:
    {
        EXE_ROLE_CMD    *pGMCmd = (EXE_ROLE_CMD*)pQueryCmd->pCmd;

        nRetCode = strncmp(pGMCmd->szRoleName, pMsg->szRoleName, ROLE_NAME_LEN);
        LOG_PROCESS_ERROR(nRetCode == 0);

        pGMCmd->dwRoleID = pMsg->dwRoleID;

        nRetCode = CCmdManager::GetInstance().ExeRoleGMCmd(pGMCmd);
        LOG_PROCESS_ERROR(nRetCode);
    }
        break;
    case CMD_FORBIDDEN_CHAT:
    {
        FORBIDDEN_CHAT *pForbidCmd = (FORBIDDEN_CHAT*)pQueryCmd->pCmd;

        nRetCode = strncmp(pForbidCmd->roleList.begin()->szRoleName, pMsg->szRoleName, ROLE_NAME_LEN);
        LOG_PROCESS_ERROR(nRetCode == 0);

        pForbidCmd->roleList.begin()->dwRoleID = pMsg->dwRoleID;

        nRetCode = CCmdManager::GetInstance().ForbidChat(pForbidCmd);
        LOG_PROCESS_ERROR(nRetCode);
    }
        break;
    case CMD_FREEZE_ROLE:
    {
        FORBIDDEN_CHAT *pFreezeCmd = (FORBIDDEN_CHAT*)pQueryCmd->pCmd;

        nRetCode = strncmp(pFreezeCmd->roleList.begin()->szRoleName, pMsg->szRoleName, ROLE_NAME_LEN);
        LOG_PROCESS_ERROR(nRetCode == 0);
        pFreezeCmd->roleList.begin()->dwRoleID = pMsg->dwRoleID;

        nRetCode = CCmdManager::GetInstance().FreezeRole(pFreezeCmd);
        LOG_PROCESS_ERROR(nRetCode);
    }
        break;
    case CMD_KICK_ROLE:
    {
        KICK_ROLE *pKickCmd = (KICK_ROLE*)pQueryCmd->pCmd;

        nRetCode = strncmp(pKickCmd->roleList.begin()->szRoleName, pMsg->szRoleName, ROLE_NAME_LEN);
        LOG_PROCESS_ERROR(nRetCode == 0);
        pKickCmd->roleList.begin()->dwRoleID = pMsg->dwRoleID;

        nRetCode = CCmdManager::GetInstance().KickRole(pKickCmd);
        LOG_PROCESS_ERROR(nRetCode);
    }
        break;
    case CMD_SEND_MAIL:
    {
        SEND_MAIL *pSendMail = (SEND_MAIL*)pQueryCmd->pCmd;

        nRetCode = strncmp(pSendMail->roleList.begin()->szRoleName, pMsg->szRoleName, ROLE_NAME_LEN);
        LOG_PROCESS_ERROR(nRetCode == 0);
        pSendMail->roleList.begin()->dwRoleID = pMsg->dwRoleID;

        nRetCode = CCmdManager::GetInstance().SendMail(pSendMail);
        LOG_PROCESS_ERROR(nRetCode);
    }
        break;
    default:
        break;
    }

Exit0:
    nRetCode = CCmdManager::GetInstance().DelCmd(pQueryCmd);
    LOG_CHECK_ERROR(nRetCode);
    return;
}

void CMessageHandler::OnGMQueryRoleID(PACKET_BUFFER *pPacketBuffer, UINT32 dwSize, ISocketSession *pSocketSession)
{
    INT32           nRetCode = 0;
    GM_SESSION      *pGMSession = NULL;
    CMD_BASE        *pCmd = NULL;
    QUERY_ROLE_ID   *pQueryCmd = NULL;
    GM2TL_QUERY_ROLE_ID_ACK *pMsg = (GM2TL_QUERY_ROLE_ID_ACK*)pPacketBuffer;

    pGMSession = (GM_SESSION *)pSocketSession->GetUserData();
    LOG_PROCESS_ERROR(pGMSession);

    pCmd = CCmdManager::GetInstance().GetCurrentCmd();
    LOG_PROCESS_ERROR(pCmd);
    LOG_PROCESS_ERROR(pCmd->nSvrNum > 0);
    pQueryCmd = (QUERY_ROLE_ID *)pCmd;

    --pCmd->nSvrNum;
    
    for (INT32 i = 0; i < pMsg->nCount; ++i)
    {
        nRetCode = g_gmtool.AddQueryRoleIDResult(pMsg->nAreaID, 
            pMsg->RoleKey[i].dwRoleID, pMsg->RoleKey[i].szRoleName, pMsg->RoleKey[i].szUserName);
        LOG_PROCESS_ERROR(nRetCode);
    }

    if (pMsg->byIsEnd == 1)
        CGMLog::GetInstance().Log("数据过多，部分数据未显示");


    return;
Exit0:
    return;
}

void CMessageHandler::OnGMQueryRoleDataAck(PACKET_BUFFER *pPacketBuffer, UINT32 dwSize, ISocketSession *pSocketSession)
{
    INT32           nRetCode = 0;
    GM_SESSION      *pGMSession = NULL;
    CMD_BASE        *pCmd = NULL;
    QUERY_ROLE_DATA *pQueryCmd = NULL;
    GM_ROLE_DATA    *pRole = NULL;
    INT32           nLength = 0;

    GM2TL_QUERY_ROLE_DATA_ACK *pMsg = (GM2TL_QUERY_ROLE_DATA_ACK*)pPacketBuffer;

    pGMSession = (GM_SESSION *)pSocketSession->GetUserData();
    LOG_PROCESS_ERROR(pGMSession);

    pCmd = CCmdManager::GetInstance().GetCurrentCmd();
    LOG_PROCESS_ERROR(pCmd);
    LOG_PROCESS_ERROR(pCmd->nSvrNum > 0);

    pQueryCmd = (QUERY_ROLE_DATA *)pCmd;
    --pQueryCmd->nSvrNum;

    pRole = CDataMgr::GetInstance().NewRole(pMsg->dwRoleID);
    LOG_PROCESS_ERROR(pRole);

    pRole->nLength = pMsg->nLength;
    memcpy(pRole->szData, pMsg->szData, pRole->nLength);

    nRetCode = g_gmtool.AddQueryRoleDataResult(pMsg->nAreaID, pMsg->bIsOnline, pRole);
    LOG_PROCESS_ERROR(nRetCode);

    return;
Exit0:
    if (pRole)
    {
        CDataMgr::GetInstance().DeleteRole(pRole);
    }

    return;
}

void CMessageHandler::OnGMForbidChatAck(PACKET_BUFFER *pPacketBuffer, UINT32 dwSize, ISocketSession *pSocketSession)
{
    INT32           nRetCode = 0;
    GM_SESSION      *pGMSession = NULL;
    CMD_BASE        *pCmd = NULL;
    FORBIDDEN_CHAT  *pForbidChat = NULL;

    GM2TL_FORBID_CHAT_ACK *pMsg = (GM2TL_FORBID_CHAT_ACK*)pPacketBuffer;

    pGMSession = (GM_SESSION *)pSocketSession->GetUserData();
    LOG_PROCESS_ERROR(pGMSession);

    pCmd = CCmdManager::GetInstance().GetCurrentCmd();
    LOG_PROCESS_ERROR(pCmd);
    LOG_PROCESS_ERROR(pCmd->nSvrNum > 0);
    
    pForbidChat = (FORBIDDEN_CHAT *)pCmd;
    
    if (pForbidChat->roleList.begin()->dwRoleID != pMsg->dwRoleID)
    {
        g_gmtool.OutputLog("禁言处理返回不是同一角色，严重错误！");
        LOG_PROCESS_ERROR(FALSE);
    }
    else
    {
        pForbidChat->roleList.begin()->nResult = pMsg->nResult;
        pForbidChat->roleResList.push_back(*(pForbidChat->roleList.begin()));
        pForbidChat->roleList.pop_front();

        if (pForbidChat->roleList.size() != 0)
        {
            nRetCode = CCmdManager::GetInstance().PreQuery(CMD_FORBIDDEN_CHAT, pForbidChat->roleList.begin()->szRoleName, pForbidChat);
            if (nRetCode == FALSE)
            {
                //QMessageBox::critical(this, "critical", QString::fromLocal8Bit("发送命令失败"), QMessageBox::Yes);
                LOG_PROCESS_ERROR(FALSE);
            }
        }
    }

    if (pForbidChat->roleList.size() == 0)
    {
        --pForbidChat->nSvrNum;

        nRetCode = g_gmtool.UpdateRoleResult(pForbidChat->szFileName, CMD_FORBIDDEN_CHAT, pForbidChat->roleResList);
        LOG_PROCESS_ERROR(nRetCode);
    }

    return;
Exit0:
    return;
}

void CMessageHandler::OnGMFreezeRoleAck(PACKET_BUFFER *pPacketBuffer, UINT32 dwSize, ISocketSession *pSocketSession)
{
    INT32           nRetCode = 0;
    GM_SESSION      *pGMSession = NULL;
    CMD_BASE        *pCmd = NULL;
    FREEZE_ROLE     *pFreezeRole = NULL;

    GM2TL_FREEZE_ROLE_ACK *pMsg = (GM2TL_FREEZE_ROLE_ACK*)pPacketBuffer;

    pGMSession = (GM_SESSION *)pSocketSession->GetUserData();
    LOG_PROCESS_ERROR(pGMSession);

    pCmd = CCmdManager::GetInstance().GetCurrentCmd();
    LOG_PROCESS_ERROR(pCmd);
    LOG_PROCESS_ERROR(pCmd->nSvrNum > 0);

    pFreezeRole = (FREEZE_ROLE *)pCmd;

    if (pFreezeRole->roleList.begin()->dwRoleID != pMsg->dwRoleID)
    {
        g_gmtool.OutputLog("封号处理返回不是同一角色，严重错误！");
        LOG_PROCESS_ERROR(FALSE);
    }
    else
    {
        pFreezeRole->roleList.begin()->nResult = pMsg->nResult;
        pFreezeRole->roleResList.push_back(*(pFreezeRole->roleList.begin()));
        pFreezeRole->roleList.pop_front();

        if (pFreezeRole->roleList.size() != 0)
        {
            nRetCode = CCmdManager::GetInstance().PreQuery(CMD_FREEZE_ROLE, pFreezeRole->roleList.begin()->szRoleName, pFreezeRole);
            if (nRetCode == FALSE)
            {
                //QMessageBox::critical(this, "critical", QString::fromLocal8Bit("发送命令失败"), QMessageBox::Yes);
                LOG_PROCESS_ERROR(FALSE);
            }
        }
    }

    if (pFreezeRole->roleList.size() == 0)
    {
        --pFreezeRole->nSvrNum;

        nRetCode = g_gmtool.UpdateRoleResult(pFreezeRole->szFileName, CMD_FREEZE_ROLE, pFreezeRole->roleResList);
        LOG_PROCESS_ERROR(nRetCode);
    }

    return;
Exit0:
    return;
}

void CMessageHandler::OnGMKickRoleAck(PACKET_BUFFER *pPacketBuffer, UINT32 dwSize, ISocketSession *pSocketSession)
{
    INT32           nRetCode = 0;
    GM_SESSION      *pGMSession = NULL;
    CMD_BASE        *pCmd = NULL;
    KICK_ROLE       *pKickRole = NULL;

    GM2TL_KICK_ROLE_ACK *pMsg = (GM2TL_KICK_ROLE_ACK*)pPacketBuffer;

    pGMSession = (GM_SESSION *)pSocketSession->GetUserData();
    LOG_PROCESS_ERROR(pGMSession);

    pCmd = CCmdManager::GetInstance().GetCurrentCmd();
    LOG_PROCESS_ERROR(pCmd);
    LOG_PROCESS_ERROR(pCmd->nSvrNum > 0);

    pKickRole = (KICK_ROLE *)pCmd;

    if (pKickRole->roleList.begin()->dwRoleID != pMsg->dwRoleID)
    {
        g_gmtool.OutputLog("踢人处理返回不是同一角色，严重错误！");
        LOG_PROCESS_ERROR(FALSE);
    }
    else
    {
        pKickRole->roleList.begin()->nResult = pMsg->nResult;
        pKickRole->roleResList.push_back(*(pKickRole->roleList.begin()));
        pKickRole->roleList.pop_front();

        if (pKickRole->roleList.size() != 0)
        {
            nRetCode = CCmdManager::GetInstance().PreQuery(CMD_KICK_ROLE, pKickRole->roleList.begin()->szRoleName, pKickRole);
            if (nRetCode == FALSE)
            {
                //QMessageBox::critical(this, "critical", QString::fromLocal8Bit("发送命令失败"), QMessageBox::Yes);
                LOG_PROCESS_ERROR(FALSE);
            }
        }
    }

    if (pKickRole->roleList.size() == 0)
    {
        --pKickRole->nSvrNum;

        nRetCode = g_gmtool.UpdateRoleResult(pKickRole->szFileName, CMD_KICK_ROLE, pKickRole->roleResList);
        LOG_PROCESS_ERROR(nRetCode);
    }

    return;
Exit0:
    return;
}

void CMessageHandler::OnGMSendMailAck(PACKET_BUFFER *pPacketBuffer, UINT32 dwSize, ISocketSession *pSocketSession)
{
    INT32           nRetCode = 0;
    GM_SESSION      *pGMSession = NULL;
    CMD_BASE        *pCmd = NULL;
    SEND_MAIL       *pSendMail = NULL;

    GM2TL_SEND_MAIL_ACK *pMsg = (GM2TL_SEND_MAIL_ACK*)pPacketBuffer;

    pGMSession = (GM_SESSION *)pSocketSession->GetUserData();
    LOG_PROCESS_ERROR(pGMSession);

    pCmd = CCmdManager::GetInstance().GetCurrentCmd();
    LOG_PROCESS_ERROR(pCmd);
    LOG_PROCESS_ERROR(pCmd->nSvrNum > 0);

    pSendMail = (SEND_MAIL *)pCmd;

    if (pSendMail->roleList.begin()->dwRoleID != pMsg->dwRoleID)
    {
        g_gmtool.OutputLog("发送邮件处理返回不是同一角色，严重错误！");
        LOG_PROCESS_ERROR(FALSE);
    }
    else
    {
        pSendMail->roleList.begin()->nResult = pMsg->nResult;
        pSendMail->roleResList.push_back(*(pSendMail->roleList.begin()));
        pSendMail->roleList.pop_front();

        if (pSendMail->roleList.size() != 0)
        {
            nRetCode = CCmdManager::GetInstance().PreQuery(CMD_SEND_MAIL, pSendMail->roleList.begin()->szRoleName, pSendMail);
            if (nRetCode == FALSE)
            {
                //QMessageBox::critical(this, "critical", QString::fromLocal8Bit("发送命令失败"), QMessageBox::Yes);
                LOG_PROCESS_ERROR(FALSE);
            }
        }
    }

    if (pSendMail->roleList.size() == 0)
    {
        --pSendMail->nSvrNum;

        nRetCode = g_gmtool.UpdateRoleResult(pSendMail->szFileName, CMD_SEND_MAIL, pSendMail->roleResList);
        LOG_PROCESS_ERROR(nRetCode);
    }

    return;
Exit0:
    return;
}

void CMessageHandler::OnGMAnnouceAck(PACKET_BUFFER *pPacketBuffer, UINT32 dwSize, ISocketSession *pSocketSession)
{
    INT32           nRetCode = 0;
    GM_SESSION      *pGMSession = NULL;
    CMD_BASE        *pCmd = NULL;
    ANNOUNCE        *pAnnounce = NULL;

    GM2TL_ANNOUNCE_ACK *pMsg = (GM2TL_ANNOUNCE_ACK*)pPacketBuffer;

    pGMSession = (GM_SESSION *)pSocketSession->GetUserData();
    LOG_PROCESS_ERROR(pGMSession);

    pCmd = CCmdManager::GetInstance().GetCurrentCmd();
    LOG_PROCESS_ERROR(pCmd);
    LOG_PROCESS_ERROR(pCmd->nSvrNum > 0);

    pAnnounce = (ANNOUNCE *)pCmd;
    --pAnnounce->nSvrNum;

    return;
Exit0:
    return;
}

void CMessageHandler::OnGMGetAnnounceAck(PACKET_BUFFER *pPacketBuffer, UINT32 dwSize, ISocketSession *pSocketSession)
{
    INT32           nRetCode = 0;
    GM_SESSION      *pGMSession = NULL;
    CMD_BASE        *pCmd = NULL;
    GET_ANNOUNCE_LIST   *pAnnounce = NULL;

    GM2TL_GET_ANNOUNCE_LIST_ACK *pMsg = (GM2TL_GET_ANNOUNCE_LIST_ACK*)pPacketBuffer;

    pGMSession = (GM_SESSION *)pSocketSession->GetUserData();
    LOG_PROCESS_ERROR(pGMSession);

    pCmd = CCmdManager::GetInstance().GetCurrentCmd();
    LOG_PROCESS_ERROR(pCmd);
    LOG_PROCESS_ERROR(pCmd->nSvrNum > 0);

    pAnnounce = (GET_ANNOUNCE_LIST *)pCmd;
    --pAnnounce->nSvrNum;

    if (pMsg->nCount > 0)
    {
        TL_ANNOUNCE_LIST    &List = CDataMgr::GetInstance().GetAnnounceList();
        List.nCount = pMsg->nCount;
        for (INT32 i = 0; i < List.nCount; ++i)
        {
            List.data[i].dwIntervalTime = pMsg->data[i].dwIntervalTime;
            List.data[i].dwRepeatNum = pMsg->data[i].dwRepeatNum;
            List.data[i].dwSerial = pMsg->data[i].dwSerial;
            List.data[i].nGroupID = pMsg->data[i].nGroupID;
            List.data[i].nSvrID = pGMSession->nSvrID;
            strxcpy(List.data[i].szText, pMsg->data[i].szText, sizeof(List.data[i].szText));
        }

        nRetCode = g_gmtool.UpdateAnnounceList();
        LOG_PROCESS_ERROR(nRetCode);
    }
    else
        g_gmtool.OutputMessageBox("当前没有公告");

    return;
Exit0:
    return;
}

void CMessageHandler::OnGMDelAnnounce(PACKET_BUFFER *pPacketBuffer, UINT32 dwSize, ISocketSession *pSocketSession)
{
    INT32           nRetCode = 0;
    GM_SESSION      *pGMSession = NULL;
    CMD_BASE        *pCmd = NULL;
    DEL_ANNOUNCE   *pAnnounce = NULL;
    GM2TL_DEL_ANNOUNCE_ACK *pMsg = (GM2TL_DEL_ANNOUNCE_ACK*)pPacketBuffer;

    pGMSession = (GM_SESSION *)pSocketSession->GetUserData();
    LOG_PROCESS_ERROR(pGMSession);

    pCmd = CCmdManager::GetInstance().GetCurrentCmd();
    LOG_PROCESS_ERROR(pCmd);
    LOG_PROCESS_ERROR(pCmd->nSvrNum > 0);

    pAnnounce = (DEL_ANNOUNCE *)pCmd;
    --pAnnounce->nSvrNum;

    nRetCode = g_gmtool.DelAnnounce(pMsg->dwAnnounceSerial);
    LOG_PROCESS_ERROR(nRetCode);

    return;
Exit0:
    return;
}

void CMessageHandler::OnGMLogAck(PACKET_BUFFER *pPacketBuffer, UINT32 dwSize, ISocketSession *pSocketSession)
{
    INT32           nRetCode = 0;
    GM_SESSION      *pGMSession = NULL;
    CMD_BASE        *pCmd = NULL;
    LOG_DATA        *pLogData = NULL;

    GM2TL_LOG_ACK *pMsg = (GM2TL_LOG_ACK*)pPacketBuffer;

    pGMSession = (GM_SESSION *)pSocketSession->GetUserData();
    LOG_PROCESS_ERROR(pGMSession);

    pCmd = CCmdManager::GetInstance().GetCurrentCmd();
    LOG_PROCESS_ERROR(pCmd);
    LOG_PROCESS_ERROR(pCmd->nSvrNum > 0);

    pLogData = (LOG_DATA *)pCmd;

    pMsg->szBuffer[pMsg->nLength-1] = '\0';

    nRetCode = g_gmtool.PutsGameLog(pMsg->nLogType, pMsg->bTruncated, pMsg->nLength, pMsg->szBuffer);
    LOG_PROCESS_ERROR(nRetCode);

    --pLogData->nSvrNum;

    return;
Exit0:
    return;
}

void CMessageHandler::OnGMExecuteGMStrAck(PACKET_BUFFER *pPacketBuffer, UINT32 dwSize, ISocketSession *pSocketSession)
{
    INT32           nRetCode = 0;
    GM_SESSION      *pGMSession = NULL;
    CMD_BASE        *pCmd = NULL;
    EXECUTE_GM_STR  *pExeStrCmd = NULL;

    GM2TL_EXE_GM_STR_ACK *pMsg = (GM2TL_EXE_GM_STR_ACK*)pPacketBuffer;

    pGMSession = (GM_SESSION *)pSocketSession->GetUserData();
    LOG_PROCESS_ERROR(pGMSession);

    pCmd = CCmdManager::GetInstance().GetCurrentCmd();
    LOG_PROCESS_ERROR(pCmd);
    LOG_PROCESS_ERROR(pCmd->nSvrNum > 0);

    pExeStrCmd = (EXECUTE_GM_STR *)pCmd;
    --pExeStrCmd->nSvrNum;

    return;
Exit0:
    return;
}

void CMessageHandler::OnGMLoadRoleDataAck(PACKET_BUFFER *pPacketBuffer, UINT32 dwSize, ISocketSession *pSocketSession)
{
    INT32           nRetCode = 0;
    GM_SESSION      *pGMSession = NULL;
    CMD_BASE        *pCmd = NULL;
    LOAD_ROLE_DATA  *pLoadRoleCmd = NULL;
    GM_ROLE_DATA    *pRole = NULL;
    INT32           nLength = 0;

    GM2TL_LOAD_ROLE_DATA_ACK *pMsg = (GM2TL_LOAD_ROLE_DATA_ACK*)pPacketBuffer;

    pGMSession = (GM_SESSION *)pSocketSession->GetUserData();
    LOG_PROCESS_ERROR(pGMSession);

    pCmd = CCmdManager::GetInstance().GetCurrentCmd();
    LOG_PROCESS_ERROR(pCmd);
    LOG_PROCESS_ERROR(pCmd->nSvrNum > 0);

    pLoadRoleCmd = (LOAD_ROLE_DATA *)pCmd;
    --pLoadRoleCmd->nSvrNum;

    pRole = CDataMgr::GetInstance().NewRole(pMsg->dwRoleID);
    LOG_PROCESS_ERROR(pRole);

    pRole->nLength = pMsg->nLength;
    memcpy(pRole->szData, pMsg->szData, pMsg->nLength);

    nRetCode = g_gmtool.LoadRoleData(pGMSession->dwSessionID, pMsg->dwRoleID);
    LOG_PROCESS_ERROR(nRetCode);

    return;
Exit0:
    if (pRole)
    {
        CDataMgr::GetInstance().DeleteRole(pRole);
    }

    return;
}

void CMessageHandler::OnGMModifyRoleDataAck(PACKET_BUFFER *pPacketBuffer, UINT32 dwSize, ISocketSession *pSocketSession)
{
    INT32           nRetCode = 0;
    GM_SESSION      *pGMSession = NULL;
    CMD_BASE        *pCmd = NULL;
    MODIFY_ROLE_DATA *pModifyRole = NULL;
    INT32           nLength = 0;

    GM2TL_MODIFY_ROLE_DATA_ACK *pMsg = (GM2TL_MODIFY_ROLE_DATA_ACK*)pPacketBuffer;

    pGMSession = (GM_SESSION *)pSocketSession->GetUserData();
    LOG_PROCESS_ERROR(pGMSession);

    pCmd = CCmdManager::GetInstance().GetCurrentCmd();
    LOG_PROCESS_ERROR(pCmd);
    LOG_PROCESS_ERROR(pCmd->nSvrNum > 0);

    pModifyRole = (MODIFY_ROLE_DATA *)pCmd;
    --pModifyRole->nSvrNum;

    return;
Exit0:
    return;
}


void CMessageHandler::OnGMQueryNameToIDAck(PACKET_BUFFER *pPacketBuffer, UINT32 dwSize, ISocketSession *pSocketSession)
{
    INT32           nRetCode = 0;
    GM_SESSION      *pGMSession = NULL;
    CMD_BASE        *pCmd = NULL;
    QUERY_NAME_TO_ID *pQuery = NULL;
    INT32           nLength = 0;
    FILE            *pFile = NULL;
    char            *pBuffer = NULL;
    INT32           nWriteFileLength = 0;
    std::map<INT32, ROLE_NAME_DATA>::iterator   iter;
    GM2TL_QUERY_NAME_TO_ID_ACK *pMsg = (GM2TL_QUERY_NAME_TO_ID_ACK*)pPacketBuffer;

    pGMSession = (GM_SESSION *)pSocketSession->GetUserData();
    LOG_PROCESS_ERROR(pGMSession);

    pCmd = CCmdManager::GetInstance().GetCurrentCmd();
    LOG_PROCESS_ERROR(pCmd);
    LOG_PROCESS_ERROR(pCmd->nSvrNum > 0);

    pQuery = (QUERY_NAME_TO_ID *)pCmd;

    iter = pQuery->RoleNameMap.find(pMsg->nIndex);
    if (iter != pQuery->RoleNameMap.end())
    {
        iter->second.dwRoleID = pMsg->dwRoleID;
    }

    if (pMsg->nIndex == pQuery->nMaxCount)
    {
        pFile = fopen("../nameTOid.txt", "w");
        if (pFile == NULL)
        {
            nRetCode = CGMLog::GetInstance().Log("  服务器[%s]，批量查询ID打开文件失败", QString::fromUtf8(pGMSession->szGMName).toLocal8Bit().data());
            LOG_PROCESS_ERROR(FALSE);
        }

        pBuffer = new char[1024 * 1024 * 10];
        memset(pBuffer, 0, 1024 * 1024 * 10);
        //
        for (std::map<INT32, ROLE_NAME_DATA>::iterator index_iter = pQuery->RoleNameMap.begin(); index_iter != pQuery->RoleNameMap.end(); ++index_iter)
        {
            INT32       nTempLength = 0;

            nTempLength = sprintf(pBuffer + nLength, "%s  %d\r\n", iter->second.szRoleName, iter->second.dwRoleID);
            if (nTempLength == -1)
            {
                CGMLog::GetInstance().Log("  服务器[%s]，批量查询ID文件写入失败", QString::fromUtf8(pGMSession->szGMName).toLocal8Bit().data());
                LOG_PROCESS_ERROR(FALSE);
            }
            else
                nLength += nTempLength;
        }

        nWriteFileLength = fwrite(pBuffer, 1, nLength, pFile);
        LOG_PROCESS_ERROR(nWriteFileLength == nLength);

        fclose(pFile);
    }

    if (pMsg->nIndex != pQuery->nMaxCount)
    {
        iter = pQuery->RoleNameMap.find(pMsg->nIndex + 1);
        if (iter != pQuery->RoleNameMap.end())
        {
            nRetCode = CMessageHandler::GetInstance().DoQueryNameToID(iter->first, iter->second.szRoleName);
            LOG_PROCESS_ERROR(nRetCode);
        }
    }
    
    return;
Exit0:
    if (pFile)
        fclose(pFile);
    return;
}

void CMessageHandler::OnGMErrorStr(PACKET_BUFFER *pPacketBuffer, UINT32 dwSize, ISocketSession *pSocketSession)
{
    INT32       nRetCode = 0;
    GM2TL_ERROR_STR *pMsg = (GM2TL_ERROR_STR*)pPacketBuffer;

    extern INT32 g_State;

    if ( g_State == 2)
    {
        g_gmtool.OutputLog(pMsg->szErr);
    }
    else if (g_State == 1)
    {
        QMessageBox::critical(&g_loader, QString::fromLocal8Bit("error"), QString::fromLocal8Bit(pMsg->szErr), QMessageBox::Yes);
    }

    

Exit0:
    return;
}

void CMessageHandler::OnGMRoleExeGMCmd(PACKET_BUFFER *pPacketBuffer, UINT32 dwSize, ISocketSession *pSocketSession)
{
    INT32           nRetCode = 0;
    GM_SESSION      *pGMSession = NULL;
    CMD_BASE        *pCmd = NULL;
    EXE_ROLE_CMD    *pRoleExeCmd = NULL;
    INT32           nLength = 0;

    GM2TL_ROLE_EXE_GM_CMD *pMsg = (GM2TL_ROLE_EXE_GM_CMD*)pPacketBuffer;

    pGMSession = (GM_SESSION *)pSocketSession->GetUserData();
    LOG_PROCESS_ERROR(pGMSession);

    pCmd = CCmdManager::GetInstance().GetCurrentCmd();
    LOG_PROCESS_ERROR(pCmd);
    LOG_PROCESS_ERROR(pCmd->nSvrNum > 0);

    pRoleExeCmd = (EXE_ROLE_CMD *)pCmd;
    --pRoleExeCmd->nSvrNum;

    return;
Exit0:
    return;
}


void CMessageHandler::OnGMSelectGroupAck(PACKET_BUFFER *pPacketBuffer, UINT32 dwSize, ISocketSession *pSocketSession)
{
    INT32       nRetCode = 0;

    GM2TL_SELECT_GROUP_ACK  *pMsg = (GM2TL_SELECT_GROUP_ACK*)pPacketBuffer;

    LOG_PROCESS_ERROR(g_gmtool.GetLDWidget());

    g_gmtool.GetLDWidget()->SetGroupID(pMsg->byGroupID);

Exit0:
    return;
}

void CMessageHandler::OnGMQueryExchangeLogAck(PACKET_BUFFER *pPacketBuffer, UINT32 dwSize, ISocketSession *pSocketSession)
{
    INT32       nRetCode = 0;
    GM2TL_QUERY_EXCHANGE_LOG_ACK    *pMsg = (GM2TL_QUERY_EXCHANGE_LOG_ACK*)pPacketBuffer;

    LOG_PROCESS_ERROR(g_gmtool.GetLDWidget());

    g_gmtool.GetLDWidget()->UpdateExchangeLog(pMsg->byGroupID, pMsg->nCount, pMsg->byIsClear, pMsg->pBuffer);

Exit0:
    return;
}

void CMessageHandler::OnGMQueryExchangeHistoryAck(PACKET_BUFFER *pPacketBuffer, UINT32 dwSize, ISocketSession *pSocketSession)
{
    INT32       nRetCode = 0;
    GM2TL_QUERY_EXCHANGE_HISTORY_ACK    *pMsg = (GM2TL_QUERY_EXCHANGE_HISTORY_ACK*)pPacketBuffer;

    LOG_PROCESS_ERROR(g_gmtool.GetLDWidget());

    g_gmtool.GetLDWidget()->UpdateExchangeHistory(pMsg->byGroupID, pMsg->nCount, pMsg->byIsClear, pMsg->pBuffer);

Exit0:
    return;
}

void CMessageHandler::OnGMExchangePrice(PACKET_BUFFER *pPacketBuffer, UINT32 dwSize, ISocketSession *pSocketSession)
{
    INT32       nRetCode = 0;
    PRICE_DATA      data[40];
    INT32       i = 0;
    GM2TL_EXCHANGE_PRICE    *pMsg = (GM2TL_EXCHANGE_PRICE*)pPacketBuffer;

    LOG_PROCESS_ERROR(g_gmtool.GetLDWidget());
    LOG_PROCESS_ERROR(40 >= (pMsg->byBuyPriceCount + pMsg->bySellPriceCount));

    for (; i < pMsg->bySellPriceCount; ++i)
    {
        data[i].nPrice = pMsg->stPrices[i].nPrice;
        data[i].nCount = pMsg->stPrices[i].nCount;
    }

    for (; i < pMsg->byBuyPriceCount + pMsg->bySellPriceCount; ++i)
    {
        data[i].nPrice = pMsg->stPrices[i].nPrice;
        data[i].nCount = pMsg->stPrices[i].nCount;
    }
    
    g_gmtool.GetLDWidget()->UpdatePrice(pMsg->byGroupID, pMsg->bySellPriceCount, pMsg->byBuyPriceCount, data);

Exit0:
    return;
}

void CMessageHandler::OnGMQueryOrderDetailAck(PACKET_BUFFER *pPacketBuffer, UINT32 dwSize, ISocketSession *pSocketSession)
{
    INT32       nRetCode = 0;
    GM2TL_QUERY_ORDER_DETAIL_ACK    *pMsg = (GM2TL_QUERY_ORDER_DETAIL_ACK*)pPacketBuffer;
    EXCHANGE_COUNT_DATA *pData = NULL;

    LOG_PROCESS_ERROR(g_gmtool.GetLDWidget());

    pData = new EXCHANGE_COUNT_DATA[pMsg->byCountCount];
    LOG_PROCESS_ERROR(pData);

    for (INT32 i = 0; i < pMsg->byCountCount; ++i)
    {
        pData[i].dwRoleID = pMsg->stCounts[i].dwRoleID;
        strxcpy(pData[i].szRoleName, pMsg->stCounts[i].szRoleName, ROLE_NAME_LEN);
        pData[i].qwOrderID = pMsg->stCounts[i].qwOrderID;
        pData[i].nCount = pMsg->stCounts[i].nCount;
    }
    
    g_gmtool.GetLDWidget()->UpdateOrderDetail(pMsg->byGroupID, pMsg->byOrderType, pMsg->nPrice, pMsg->byCountCount, pData);

    delete[] pData;
    pData = NULL;
Exit0:
    if (pData != NULL)
        delete[] pData;
    return;
}

void CMessageHandler::OnGMAddSystemOrderAck(PACKET_BUFFER *pPacketBuffer, UINT32 dwSize, ISocketSession *pSocketSession)
{
    char        szBuffer[256] = { 0 };
    GM2TL_ADD_SYSTEM_ORDER_ACK  *pMsg = (GM2TL_ADD_SYSTEM_ORDER_ACK*)pPacketBuffer;

    if (pMsg->nResult == errSuccess)
        snprintf(szBuffer, 256, "增加订单成功. 单价 %.2lf, 数量 %d", (double)pMsg->nPrice / 100, pMsg->nCount);
    else
        snprintf(szBuffer, 256, "增加订单失败. 单价 %.2lf, 数量 %d", (double)pMsg->nPrice / 100, pMsg->nCount);
    g_gmtool.OutputLog(szBuffer);
}

void CMessageHandler::OnGMDelSystemOrderAck(PACKET_BUFFER *pPacketBuffer, UINT32 dwSize, ISocketSession *pSocketSession)
{
    char        szBuffer[256] = { 0 };
    GM2TL_DEL_SYSTEM_ORDER_ACK  *pMsg = (GM2TL_DEL_SYSTEM_ORDER_ACK*)pPacketBuffer;

    if (pMsg->nResult == errSuccess)
        snprintf(szBuffer, 256, "取消订单成功. 单价 %.2lf, 数量 %d", (double)pMsg->nPrice / 100, pMsg->nCount);
    else
        snprintf(szBuffer, 256, "取消订单失败. 单价 %.2lf, 数量 %d", (double)pMsg->nPrice / 100, pMsg->nCount);

    g_gmtool.OutputLog(szBuffer);

    LOG_PROCESS_ERROR(g_gmtool.GetLDWidget());
    g_gmtool.GetLDWidget()->DelDetail();

Exit0:
    return;
}

void CMessageHandler::OnGMQuerySysExchangeInfoAck(PACKET_BUFFER *pPacketBuffer, UINT32 dwSize, ISocketSession *pSocketSession)
{
    INT32       nRetCode = 0;
    GM2TL_QUERY_SYS_EXCHANGE_INFO_ACK    *pMsg = (GM2TL_QUERY_SYS_EXCHANGE_INFO_ACK*)pPacketBuffer;

    LOG_PROCESS_ERROR(g_gmtool.GetLDWidget());

    if (pMsg->byFlag == 1)
    {
        g_gmtool.GetLDWidget()->ShowTodayStat(pMsg->byGroupID, 
            pMsg->llSysTotalMoney, pMsg->llTotalMoney, 
            pMsg->llSysTotalExchangeMoney, pMsg->llTotalExchangeMoney, 
            pMsg->llSysExchangeRMB, pMsg->llExchangeRMB, 
            pMsg->nAveragePriceToday, pMsg->nAveragePriceLastHour);
    }
    else if (pMsg->byFlag == 0)
    {
        g_gmtool.GetLDWidget()->ShowYesterdayStat(pMsg->byGroupID, 
            pMsg->llSysTotalMoney, pMsg->llTotalMoney,
            pMsg->llSysTotalExchangeMoney, pMsg->llTotalExchangeMoney,
            pMsg->llSysExchangeRMB, pMsg->llExchangeRMB, 
            pMsg->nAveragePriceToday, pMsg->nAveragePriceLastHour);
    }
    else if (pMsg->byFlag == 3)
    {
        g_gmtool.GetLDWidget()->OutputStatToFile(pMsg->dwBeginTime, pMsg->dwEndTime, 
            pMsg->byGroupID,            
            pMsg->llSysTotalMoney, pMsg->llTotalMoney,
            pMsg->llSysTotalExchangeMoney, pMsg->llTotalExchangeMoney,
            pMsg->llSysExchangeRMB, pMsg->llExchangeRMB,
            pMsg->nAveragePriceToday, pMsg->nAveragePriceLastHour);

        g_gmtool.OutputLog("导出数据成功");
    }
    

Exit0:
    return;
}

void CMessageHandler::OnGMGetExchangeLimitAck(PACKET_BUFFER *pPacketBuffer, UINT32 dwSize, ISocketSession *pSocketSession)
{
    INT32       nRetCode = 0;
    GM2TL_GET_EXCHANGE_LIMIT_ACK    *pMsg = (GM2TL_GET_EXCHANGE_LIMIT_ACK*)pPacketBuffer;

    if (g_gmtool.GetLDWidget())
    {
        g_gmtool.GetLDWidget()->ShowExchangeLimit(pMsg->nPriceHigh, pMsg->nPriceLow, pMsg->nSingleOrderLimit, pMsg->nDailyOrderLimit);
    }

Exit0:
    return;
}

void CMessageHandler::OnGMSetExchangeLimitAck(PACKET_BUFFER *pPacketBuffer, UINT32 dwSize, ISocketSession *pSocketSession)
{
    INT32       nRetCode = 0;
    GM2TL_SET_EXCHANGE_LIMIT_ACK    *pMsg = (GM2TL_SET_EXCHANGE_LIMIT_ACK*)pPacketBuffer;

    if (g_gmtool.GetLDWidget())
    {
        g_gmtool.GetLDWidget()->ShowExchangeLimit(pMsg->nPriceHigh, pMsg->nPriceLow, pMsg->nSingleOrderLimit, pMsg->nDailyOrderLimit);
        g_gmtool.OutputLog("修改订单限制成功");
    }

Exit0:
    return;
}


