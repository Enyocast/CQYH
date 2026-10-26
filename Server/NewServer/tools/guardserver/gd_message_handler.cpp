#include "stdafx.h"
#include "time_ex.h"

#include "guard_config.h"
#include "maintain_tool_version.h"
#include "common_message.h"
#include "gd_session_mgr.h"
#include "gd_message_handler.h"
#include "guardserver.h"
#include "process_mgr.h"
#include "cmd_mgr.h"
#include "direct.h"
#include "dir.h"
#include "ifile.h"
#include "statis_info.h"
#include "process_option.h"
#include "shellapi.h"

using namespace InternalMessage;
CGDMessageHandler CGDMessageHandler::ms_Instance;

void CGDMessageHandler::OnAccepted(ISocketAcceptor* pSocketAcceptor, ISocketSession* pSocketSession)
{
    INT32 nRetCode = 0;

    LOG_PROCESS_ERROR(pSocketSession);

    nRetCode = CGDSessionMgr::GetInstance().AddServerSession(pSocketSession);
    LOG_PROCESS_ERROR(nRetCode);

    INF("a connecting is accepted");

    return;
Exit0:
    if(pSocketSession)
        pSocketSession->Close();
    return;
}

void CGDMessageHandler::OnConnected(ISocketSession* pSocketSession)
{
    LOG_PROCESS_ERROR(FALSE);

    return;
Exit0:
    if (pSocketSession)
        pSocketSession->Close();

    return;
}

void CGDMessageHandler::OnRecv(ISocketSession* pSocketSession, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize)
{
    MESSAGE_HEADER* pHeader = (MESSAGE_HEADER*)pPacketBuffer;
    LOG_PROCESS_ERROR(pHeader);

    LOG_PROCESS_ERROR(pSocketSession);
    LOG_PROCESS_ERROR(pPacketBuffer);

    LOG_PROCESS_ERROR(m_GuardMessageFuncList[pHeader->wMsg]);

    (this->*m_GuardMessageFuncList[pHeader->wMsg])(pPacketBuffer, dwSize, pSocketSession);

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

void CGDMessageHandler::OnDisconnected(ISocketSession* pSocketSession, BOOL bRemoteShutdown)
{
    INT32 nRetCode = 0;
    ServerSession* pSession = NULL;

    LOG_PROCESS_ERROR(pSocketSession);

    pSession = (ServerSession*)pSocketSession->GetUserData();
    if(!pSession)
    {
        nRetCode = CGDSessionMgr::GetInstance().RemoveServerSession(pSocketSession);
		LOG_PROCESS_ERROR(nRetCode);
    }
    else
	{
		// notify MT before set NULL
		nRetCode = CProcessMgr::GetInstance().SyncProcessInfo(epsUnonnect, pSession->dwProcessID);
		LOG_CHECK_ERROR(nRetCode);

		pSession->pSocketSession = NULL;
        pSession->dwProcessID = 0;
        pSession->qwTimer = (UINT64)(~0);

        switch (pSession->dwType)
        {
        case stDB:
            {
                CRI("DB disconnected");
            }
            break;
        case stLS:
            {
                CRI("LS disconnected");
            }
            break;
        case stMS:
            {
                CRI("MS disconnected");
            }
            break;
        case stGT:
            {
                SGTSession* pGTSession = (SGTSession*)pSession;
                CRI("GT %d disconnected", pGTSession->dwSessionID);
            }
            break;
        case stGS:
            {
                SGSSession* pGSSession = (SGSSession*)pSession;
                CRI("GS %d disconnected", pGSSession->dwSessionID);
            }
            break;
        case stMG:
            {
                SMGSession* pMGSession = (SMGSession*)pSession;
				CRI("MG %d disconnected", pMGSession->dwSessionID);
            }
            break;
		case stBS:
			{
				CRI("BS disconnected");
			}
			break;
		case stDL:
			{
				CRI("DL disconnected");
			}
			break;
		case stMT:
			{
				CRI("MT disconnected");
			}
			break;
		case stMM:
			CRI("MM disconnected");
			break;
        default:
            LOG_PROCESS_ERROR(FALSE);
            break;
        }
    }

    return;
Exit0:
    return;
}

CGDMessageHandler::CGDMessageHandler()
{
    m_pNet = NULL;
    m_pPacketAllocator = NULL;
	m_pRecvFileHandle = NULL;
	m_nRecvBufferIndex = 0;
	memset(m_szRecvFilePath, 0, sizeof(m_szRecvFilePath));
	memset(m_GuardMessageFuncList, 0, sizeof(m_GuardMessageFuncList));
}

CGDMessageHandler::~CGDMessageHandler()
{
    UnInit();
}

BOOL CGDMessageHandler::Init(INet* pNet, IPacketAllocator* pPacketAllocator)
{
    LOG_PROCESS_ERROR(pNet);
    LOG_PROCESS_ERROR(pPacketAllocator);

	m_nRecvBufferIndex = 0;
	m_pRecvFileHandle = NULL;
	memset(m_szRecvFilePath, 0, sizeof(m_szRecvFilePath));
    m_pNet = pNet;
    m_pPacketAllocator = pPacketAllocator;

    //All
    //////////////////////////////////////////////////////////////////////////////////////
    m_GuardMessageFuncList[a2a_ping] = &CGDMessageHandler::OnAllPing;
    m_GuardMessageFuncList[a2u_regrister] = &CGDMessageHandler::OnProcessRegrister;
	m_GuardMessageFuncList[n2u_regrister] = &CGDMessageHandler::OnMTRegrister;

	// from MS
	m_GuardMessageFuncList[m2u_command_ack] = &CGDMessageHandler::OnMSCommandAck;
	m_GuardMessageFuncList[a2u_notify] = &CGDMessageHandler::OnAllNotify;

	// from MT
	m_GuardMessageFuncList[n2u_exec_cmd] = &CGDMessageHandler::OnMTExecCmd;
    m_GuardMessageFuncList[n2u_send_files] = &CGDMessageHandler::OnMTSendFiles;
	m_GuardMessageFuncList[n2u_deploy_server_version] = &CGDMessageHandler::OnMTDeployServerVersion;
	m_GuardMessageFuncList[n2u_hot_update_patch] = &CGDMessageHandler::OnMTHotUpdatePatch;
    /////////////////////////////////////////////////////////////////////////////////////

	memset(g_GuardConfig.szGuardPath, 0, sizeof(g_GuardConfig.szGuardPath));
	snprintf(g_GuardConfig.szGuardPath, sizeof(g_GuardConfig.szGuardPath), "%s", _getcwd(NULL, 0));

    return TRUE;
Exit0:
    return FALSE;
}

BOOL CGDMessageHandler::UnInit(void)
{
    INT32 nRetCode = 0;
	if(m_pRecvFileHandle)
	{
		nRetCode = fclose(m_pRecvFileHandle);
		LOG_CHECK_ERROR(nRetCode);
	}
	
	return TRUE;
}

CGDMessageHandler& CGDMessageHandler::GetInstance(void)
{
    return ms_Instance;
}

BOOL CGDMessageHandler::_SendGT(UINT32 dwGTSessionID, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, INT32 nOffset)
{
    INT32 nRetCode = 0;

    SGTSession* pGTSession = CGDSessionMgr::GetInstance().GetGTSession(dwGTSessionID);
	LOG_PROCESS_ERROR(pGTSession && pGTSession->pSocketSession);

    nRetCode = pGTSession->pSocketSession->Send((PACKET_BUFFER*)pPacketBuffer, dwSize, nOffset);
    LOG_PROCESS_ERROR(nRetCode == dwSize);

    return TRUE;
Exit0:
    return FALSE;
}

BOOL CGDMessageHandler::_SendGS(UINT32 dwGSSessionID, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, INT32 nOffset)
{
    INT32 nRetCode = 0;

    SGSSession* pGSSession = CGDSessionMgr::GetInstance().GetGSSession(dwGSSessionID);
    LOG_PROCESS_ERROR(pGSSession);
    LOG_PROCESS_ERROR(pGSSession->pSocketSession);

    nRetCode = pGSSession->pSocketSession->Send((PACKET_BUFFER*)pPacketBuffer, dwSize, nOffset);
    LOG_PROCESS_ERROR(nRetCode == dwSize);

    return TRUE;
Exit0:
    return FALSE;
}

BOOL CGDMessageHandler::_SendLS(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, INT32 nOffset)
{
    INT32 nRetCode = 0;

    SLSSession& rLSSession = CGDSessionMgr::GetInstance().GetLSSession();
    LOG_PROCESS_ERROR(rLSSession.pSocketSession);

    nRetCode = rLSSession.pSocketSession->Send((PACKET_BUFFER*)pPacketBuffer, dwSize, nOffset);
    LOG_PROCESS_ERROR(nRetCode == dwSize);

    return TRUE;
Exit0:
    return FALSE;
}

BOOL CGDMessageHandler::_SendDB(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, INT32 nOffset)
{
    INT32 nRetCode = 0;

    SDBSession& rDBSession = CGDSessionMgr::GetInstance().GetDBSession();
    LOG_PROCESS_ERROR(rDBSession.pSocketSession);

    nRetCode = rDBSession.pSocketSession->Send((PACKET_BUFFER*)pPacketBuffer, dwSize, nOffset);
    LOG_PROCESS_ERROR(nRetCode == dwSize);

    return TRUE;
Exit0:
    return FALSE;
}

BOOL CGDMessageHandler::_SendMS(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, INT32 nOffset)
{
    INT32 nRetCode = 0;

    SMSSession& rMSSession = CGDSessionMgr::GetInstance().GetMSSession();
    LOG_PROCESS_ERROR(rMSSession.pSocketSession);

    nRetCode = rMSSession.pSocketSession->Send((PACKET_BUFFER*)pPacketBuffer, dwSize, nOffset);
    LOG_PROCESS_ERROR(nRetCode == dwSize);

    return TRUE;
Exit0:
    return FALSE;
}

BOOL CGDMessageHandler::_SendBS(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, INT32 nOffset)
{
	INT32 nRetCode = 0;

	SBSSession& rBSSession = CGDSessionMgr::GetInstance().GetBSSession();
	LOG_PROCESS_ERROR(rBSSession.pSocketSession);

	nRetCode = rBSSession.pSocketSession->Send((PACKET_BUFFER*)pPacketBuffer, dwSize, nOffset);
	LOG_PROCESS_ERROR(nRetCode == dwSize);

	return TRUE;
Exit0:
	return FALSE;
}

BOOL CGDMessageHandler::_SendDL(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, INT32 nOffset)
{	
	INT32 nRetCode = 0;

	SDLSession& rDLSession = CGDSessionMgr::GetInstance().GetDLSession();
	LOG_PROCESS_ERROR(rDLSession.pSocketSession);

	nRetCode = rDLSession.pSocketSession->Send((PACKET_BUFFER*)pPacketBuffer, dwSize, nOffset);
	LOG_PROCESS_ERROR(nRetCode == dwSize);

	return TRUE;
Exit0:
	return FALSE;
}

BOOL CGDMessageHandler::_SendMT(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, INT32 nOffset)
{
	INT32 nRetCode = 0;

	SMTSession& rMTSession = CGDSessionMgr::GetInstance().GetMTSession();
	LOG_PROCESS_ERROR(rMTSession.pSocketSession);

	nRetCode = rMTSession.pSocketSession->Send((PACKET_BUFFER*)pPacketBuffer, dwSize, nOffset);
	LOG_PROCESS_ERROR(nRetCode == dwSize);

	return TRUE;
Exit0:
	return FALSE;
}

BOOL CGDMessageHandler::_SendGM(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, INT32 nOffset)
{
    INT32 nRetCode = 0;

    SGMSession& rGMSession = CGDSessionMgr::GetInstance().GetGMSession();
    LOG_PROCESS_ERROR(rGMSession.pSocketSession);

    nRetCode = rGMSession.pSocketSession->Send((PACKET_BUFFER*)pPacketBuffer, dwSize, nOffset);
    LOG_PROCESS_ERROR(nRetCode == dwSize);

    return TRUE;
Exit0:
    return FALSE;
}

BOOL CGDMessageHandler::_SendMM(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, INT32 nOffset)
{
	INT32 nRetCode = 0;

	SMMSession& rMMSession = CGDSessionMgr::GetInstance().GetMMSession();
	LOG_PROCESS_ERROR(rMMSession.pSocketSession);

	nRetCode = rMMSession.pSocketSession->Send((PACKET_BUFFER*)pPacketBuffer, dwSize, nOffset);
	LOG_PROCESS_ERROR(nRetCode == dwSize);

	return TRUE;
Exit0:
	return FALSE;
}

BOOL CGDMessageHandler::_BroadcastGT(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, INT32 nOffset)
{
    INT32 nRetCode = 0;
    PACKET_BUFFER* pMsg = NULL;

    for(INT32 i = 1; i < MAX_GT_SESSION_COUNT; ++i)
    {
        SGTSession* pGTSession = CGDSessionMgr::GetInstance().GetGTSession(i);
        LOG_PROCESS_ERROR(pGTSession);
        LOG_PROCESS_ERROR(pGTSession->pSocketSession);

        pMsg = m_pPacketAllocator->Alloc(dwSize);
        LOG_PROCESS_ERROR(pMsg);

        memcpy(pMsg + nOffset, pPacketBuffer + nOffset, dwSize);

        nRetCode = pGTSession->pSocketSession->Send(pMsg, dwSize, nOffset);
        LOG_PROCESS_ERROR(nRetCode == dwSize);

        pMsg = NULL;
    }

    m_pPacketAllocator->Free(pPacketBuffer);

    return TRUE;
Exit0:
    if(pMsg)
        m_pPacketAllocator->Free(pMsg);
    if(pPacketBuffer)
        m_pPacketAllocator->Free(pPacketBuffer);
    return FALSE;
}

BOOL CGDMessageHandler::_BroadcastGS(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, INT32 nOffset)
{
    INT32 nRetCode = 0;
    PACKET_BUFFER* pMsg = NULL;

    for(INT32 i = 1; i < MAX_GS_SESSION_COUNT; ++i)
    {
        SGSSession* pGSSession = CGDSessionMgr::GetInstance().GetGSSession(i);
        LOG_PROCESS_ERROR(pGSSession);

        if(!pGSSession->pSocketSession)
            continue;

        pMsg = m_pPacketAllocator->Alloc(dwSize);
        LOG_PROCESS_ERROR(pMsg);

        memcpy(pMsg + nOffset, pPacketBuffer + nOffset, dwSize);

        nRetCode = pGSSession->pSocketSession->Send(pMsg, dwSize, nOffset);
        LOG_PROCESS_ERROR(nRetCode == dwSize);

        pMsg = NULL;
    }

    m_pPacketAllocator->Free(pPacketBuffer);

    return TRUE;
Exit0:
    if(pMsg)
        m_pPacketAllocator->Free(pMsg);
    if(pPacketBuffer)
        m_pPacketAllocator->Free(pPacketBuffer);
    return FALSE;
}

BOOL CGDMessageHandler::_BroadcastAll(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, INT32 nOffset)
{
    INT32 nRetCode = 0;
    PACKET_BUFFER* pMsg = NULL;

    for(INT32 i = 1; i < MAX_GT_SESSION_COUNT; ++i)
    {
        SGTSession* pGTSession = CGDSessionMgr::GetInstance().GetGTSession(i);
        LOG_PROCESS_ERROR(pGTSession);

        if (pGTSession->pSocketSession == NULL)
            continue;

        pMsg = m_pPacketAllocator->Alloc(dwSize);
        LOG_PROCESS_ERROR(pMsg);

        memcpy(pMsg + nOffset, pPacketBuffer + nOffset, dwSize);

        nRetCode = pGTSession->pSocketSession->Send(pMsg, dwSize, nOffset);
        LOG_CHECK_ERROR(nRetCode == dwSize);

        pMsg = NULL;
    }

    for(INT32 i = 1; i < MAX_GS_SESSION_COUNT; ++i)
    {
        SGSSession* pGSSession = CGDSessionMgr::GetInstance().GetGSSession(i);
        LOG_PROCESS_ERROR(pGSSession);
        
        if (pGSSession->pSocketSession == NULL)
            continue;

        pMsg = m_pPacketAllocator->Alloc(dwSize);
        LOG_PROCESS_ERROR(pMsg);

        memcpy(pMsg + nOffset, pPacketBuffer + nOffset, dwSize);

        nRetCode = pGSSession->pSocketSession->Send(pMsg, dwSize, nOffset);
        LOG_PROCESS_ERROR(nRetCode == dwSize);

        pMsg = NULL;
    }
    
    {
        SMSSession& rMSSession = CGDSessionMgr::GetInstance().GetMSSession();
        if (rMSSession.pSocketSession)
        {
            pMsg = m_pPacketAllocator->Alloc(dwSize);
            LOG_PROCESS_ERROR(pMsg);

            memcpy(pMsg + nOffset, pPacketBuffer + nOffset, dwSize);

            nRetCode = rMSSession.pSocketSession->Send(pMsg, dwSize, nOffset);
            LOG_PROCESS_ERROR(nRetCode == dwSize);

            pMsg = NULL;
        }
    }

    {
        SDBSession& rDBSession = CGDSessionMgr::GetInstance().GetDBSession();
        if (rDBSession.pSocketSession)
        {
            pMsg = m_pPacketAllocator->Alloc(dwSize);
            LOG_PROCESS_ERROR(pMsg);

            memcpy(pMsg + nOffset, pPacketBuffer + nOffset, dwSize);

            nRetCode = rDBSession.pSocketSession->Send(pMsg, dwSize, nOffset);
            LOG_PROCESS_ERROR(nRetCode == dwSize);

            pMsg = NULL;
        }
    }

    {
        SLSSession& rLSSession = CGDSessionMgr::GetInstance().GetLSSession();
        if (rLSSession.pSocketSession)
        {
            pMsg = m_pPacketAllocator->Alloc(dwSize);
            LOG_PROCESS_ERROR(pMsg);

            memcpy(pMsg + nOffset, pPacketBuffer + nOffset, dwSize);

            nRetCode = rLSSession.pSocketSession->Send(pMsg, dwSize, nOffset);
            LOG_PROCESS_ERROR(nRetCode == dwSize);

            pMsg = NULL;
        }
    }

	{
		SBSSession& rBSSession = CGDSessionMgr::GetInstance().GetBSSession();
		if (rBSSession.pSocketSession)
		{
			pMsg = m_pPacketAllocator->Alloc(dwSize);
			LOG_PROCESS_ERROR(pMsg);

			memcpy(pMsg + nOffset, pPacketBuffer + nOffset, dwSize);

			nRetCode = rBSSession.pSocketSession->Send(pMsg, dwSize, nOffset);
			LOG_PROCESS_ERROR(nRetCode == dwSize);

			pMsg = NULL;
		}
	}

	{
		SMMSession& rMMSession = CGDSessionMgr::GetInstance().GetMMSession();
		if (rMMSession.pSocketSession)
		{
			pMsg = m_pPacketAllocator->Alloc(dwSize);
			LOG_PROCESS_ERROR(pMsg);

			memcpy(pMsg + nOffset, pPacketBuffer + nOffset, dwSize);

			nRetCode = rMMSession.pSocketSession->Send(pMsg, dwSize, nOffset);
			LOG_PROCESS_ERROR(nRetCode == dwSize);

			pMsg = NULL;
		}
	}

    if(pPacketBuffer)
        m_pPacketAllocator->Free(pPacketBuffer);

    return TRUE;
Exit0:
    if(pMsg)
        m_pPacketAllocator->Free(pMsg);
    return FALSE;
}

BOOL CGDMessageHandler::DoMTUpdateStatisInfo(void)
{
    INT32 nRetCode = 0;
    U2N_UPDATE_STATIS_INFO* pMsg = NULL;
    CGDSessionMgr &rSessionMgr = CGDSessionMgr::GetInstance();

    pMsg = (U2N_UPDATE_STATIS_INFO*)m_pPacketAllocator->Alloc(sizeof(U2N_UPDATE_STATIS_INFO));
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = u2n_update_statis_info;       
    pMsg->bConnected = TRUE;

    stStatisInfoShm * pShm = g_GetStatisInfoShm();
    LOG_PROCESS_ERROR( pShm ); 
    memcpy( &pMsg->oStatisInfo, &pShm->oInfo, sizeof(pMsg->oStatisInfo) );

    nRetCode = _SendMT((PACKET_BUFFER*)pMsg, sizeof(U2N_UPDATE_STATIS_INFO));
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

BOOL CGDMessageHandler::DoAllPing(void)
{
    INT32 nRetCode = 0;
    A2A_PING* pMsg = NULL;
    CGDSessionMgr &rSessionMgr = CGDSessionMgr::GetInstance();

    if (rSessionMgr.GetGMSession().pSocketSession)
    {
        pMsg = (A2A_PING*)m_pPacketAllocator->Alloc(sizeof(A2A_PING));
        LOG_PROCESS_ERROR(pMsg);

        pMsg->wMsg = a2a_ping;

        nRetCode = _SendGM((PACKET_BUFFER*)pMsg, sizeof(A2A_PING));
        LOG_CHECK_ERROR(nRetCode);

        if (!nRetCode)
            m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
        pMsg = NULL;
    }

    if (rSessionMgr.GetMSSession().pSocketSession)
    {
        pMsg = (A2A_PING*)m_pPacketAllocator->Alloc(sizeof(A2A_PING));
        LOG_PROCESS_ERROR(pMsg);

        pMsg->wMsg = a2a_ping;

        nRetCode = _SendMS((PACKET_BUFFER*)pMsg, sizeof(A2A_PING));
        LOG_CHECK_ERROR(nRetCode);

        if (!nRetCode)
            m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
        pMsg = NULL;
    }

    if (rSessionMgr.GetLSSession().pSocketSession)
    {
        pMsg = (A2A_PING*)m_pPacketAllocator->Alloc(sizeof(A2A_PING));
        LOG_PROCESS_ERROR(pMsg);

        pMsg->wMsg = a2a_ping;

        nRetCode = _SendLS((PACKET_BUFFER*)pMsg, sizeof(A2A_PING));
        LOG_CHECK_ERROR(nRetCode);

        if (!nRetCode)
            m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
        pMsg = NULL;
    }

	if (rSessionMgr.GetBSSession().pSocketSession)
	{
		pMsg = (A2A_PING*)m_pPacketAllocator->Alloc(sizeof(A2A_PING));
		LOG_PROCESS_ERROR(pMsg);

		pMsg->wMsg = a2a_ping;

		nRetCode = _SendBS((PACKET_BUFFER*)pMsg, sizeof(A2A_PING));
        LOG_CHECK_ERROR(nRetCode);

        if (!nRetCode)
            m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
        pMsg = NULL;
	}

    if (rSessionMgr.GetDBSession().pSocketSession)
    {
        pMsg = (A2A_PING*)m_pPacketAllocator->Alloc(sizeof(A2A_PING));
        LOG_PROCESS_ERROR(pMsg);

        pMsg->wMsg = a2a_ping;

        nRetCode = _SendDB((PACKET_BUFFER*)pMsg, sizeof(A2A_PING));
        LOG_CHECK_ERROR(nRetCode);

        if (!nRetCode)
            m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
        pMsg = NULL;
    }

	if (rSessionMgr.GetDLSession().pSocketSession)
	{
		pMsg = (A2A_PING*)m_pPacketAllocator->Alloc(sizeof(A2A_PING));
		LOG_PROCESS_ERROR(pMsg);

		pMsg->wMsg = a2a_ping;

		nRetCode = _SendDL((PACKET_BUFFER*)pMsg, sizeof(A2A_PING));
        LOG_CHECK_ERROR(nRetCode);

        if (!nRetCode)
            m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
        pMsg = NULL;
	}

	if (rSessionMgr.GetMTSession().pSocketSession)
	{
		pMsg = (A2A_PING*)m_pPacketAllocator->Alloc(sizeof(A2A_PING));
		LOG_PROCESS_ERROR(pMsg);

		pMsg->wMsg = a2a_ping;

		nRetCode = _SendMT((PACKET_BUFFER*)pMsg, sizeof(A2A_PING));
        LOG_CHECK_ERROR(nRetCode);

        if (!nRetCode)
            m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
        pMsg = NULL;
	}

	if (rSessionMgr.GetMMSession().pSocketSession)
	{
		pMsg = (A2A_PING*)m_pPacketAllocator->Alloc(sizeof(A2A_PING));
		LOG_PROCESS_ERROR(pMsg);

		pMsg->wMsg = a2a_ping;

		nRetCode = _SendMM((PACKET_BUFFER*)pMsg, sizeof(A2A_PING));
		LOG_CHECK_ERROR(nRetCode);

		if (!nRetCode)
			m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
		pMsg = NULL;
	}

    for (INT32 nIndex = 1; nIndex < MAX_GS_SESSION_COUNT; nIndex++)
    {
        SGSSession* pGSSession = rSessionMgr.GetGSSession(nIndex);
        if (pGSSession && pGSSession->pSocketSession)
        {
            pMsg = (A2A_PING*)m_pPacketAllocator->Alloc(sizeof(A2A_PING));
            LOG_PROCESS_ERROR(pMsg);

            pMsg->wMsg = a2a_ping;

            nRetCode = _SendGS(pGSSession->dwSessionID, (PACKET_BUFFER*)pMsg, sizeof(A2A_PING));
            LOG_CHECK_ERROR(nRetCode);

            if (!nRetCode)
                m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
            pMsg = NULL;
        }
    }

    for (INT32 nIndex = 1; nIndex < MAX_GT_SESSION_COUNT; nIndex++)
    {
        SGTSession* pGTSession = rSessionMgr.GetGTSession(nIndex);
        if (pGTSession && pGTSession->pSocketSession)
        {
            pMsg = (A2A_PING*)m_pPacketAllocator->Alloc(sizeof(A2A_PING));
            LOG_PROCESS_ERROR(pMsg);

            pMsg->wMsg = a2a_ping;

            nRetCode = _SendGT(pGTSession->dwSessionID, (PACKET_BUFFER*)pMsg, sizeof(A2A_PING));
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

BOOL CGDMessageHandler::DoMSClose(void)
{
    INT32 nRetCode = 0;

    U2M_CLOSE* pMsg = (U2M_CLOSE*)(m_pPacketAllocator->Alloc(sizeof(U2M_CLOSE)));
    LOG_PROCESS_ERROR(pMsg);
    pMsg->wMsg = u2m_close;

    nRetCode = _SendMS((PACKET_BUFFER*)pMsg, sizeof(U2M_CLOSE));
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

BOOL CGDMessageHandler::DoMSCommand(const char* pszCommand)
{
    INT32 nRetCode = 0;
	INT32 nCommandLen = strlen(pszCommand);

	INT32 nSize = sizeof(U2M_COMMAND) + nCommandLen + 1;

	U2M_COMMAND* pMsg = (U2M_COMMAND*)(m_pPacketAllocator->Alloc(nSize));
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = u2m_command;	// only be processed by final version
	strxcpy(pMsg->szCommand, pszCommand, nCommandLen+1);

	nRetCode = _SendMS((PACKET_BUFFER*)pMsg, nSize);
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

BOOL CGDMessageHandler::DoMTNotify(UINT8 bySvrType, UINT8 bySvrID, UINT8 byLevel, INT32 nErrorCode, const char* szContent, ...)
{
	INT32 nRetCode = 0;

	char szInfo[4096] = { 0 };
	va_list valist;
	va_start(valist, szContent);
	vsnprintf(szInfo, sizeof(szInfo), szContent, valist);
	va_end(valist);

	INT32 nSize = sizeof(U2N_NOTIFY) + strlen(szInfo) + 1;

	U2N_NOTIFY* pMsg = (U2N_NOTIFY*)(m_pPacketAllocator->Alloc(nSize));
	LOG_PROCESS_ERROR(pMsg);

	memset(pMsg, 0, sizeof(U2N_NOTIFY));
	pMsg->wMsg = u2n_notify;
	pMsg->bySvrID = bySvrID;
	pMsg->bySvrType = bySvrType;
	pMsg->byLevel = byLevel;
	pMsg->nErrorCode = nErrorCode;
	strxcpy(pMsg->szContent, szInfo, strlen(szInfo) + 1);

	CRI("DoMTNotify: %s", szInfo);
	nRetCode = _SendMT((PACKET_BUFFER*)pMsg, nSize);
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CGDMessageHandler::DoMTError(INT32 nErrorCode, const char* szContent, ...)
{
	INT32 nRetCode = 0;

	char szInfo[4096] = { 0 };
	va_list valist;
	va_start(valist, szContent);
	vsnprintf(szInfo, sizeof(szInfo), szContent, valist);
	va_end(valist);

	INT32 nSize = sizeof(U2N_ERROR) + strlen(szInfo) + 1;

	U2N_ERROR* pMsg = (U2N_ERROR*)(m_pPacketAllocator->Alloc(nSize));
	LOG_PROCESS_ERROR(pMsg);

	memset(pMsg, 0, sizeof(U2N_ERROR));
	pMsg->wMsg = u2n_error;
	pMsg->nErrorCode = nErrorCode;
	strxcpy(pMsg->szErrorInfo, szInfo, strlen(szInfo) + 1);

	CRI("DoMTError: %s", szInfo);
	nRetCode = _SendMT((PACKET_BUFFER*)pMsg, nSize);
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CGDMessageHandler::DoMTUpdateCmdAck(INT32 nErrorCode, const char* szResult)
{
	INT32 nRetCode = 0;
	INT32 nSize = sizeof(U2N_UPDATE_CMD_ACK) + strlen(szResult) + 1;

	U2N_UPDATE_CMD_ACK* pMsg = (U2N_UPDATE_CMD_ACK*)(m_pPacketAllocator->Alloc(nSize));
	LOG_PROCESS_ERROR(pMsg);

	memset(pMsg, 0, sizeof(U2N_UPDATE_CMD_ACK));
	pMsg->wMsg = u2n_exec_cmd_ack;
	pMsg->nErrorCode = nErrorCode;
	strxcpy(pMsg->szResult, szResult, strlen(szResult) + 1);

	nRetCode = _SendMT((PACKET_BUFFER*)pMsg, nSize);
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CGDMessageHandler::DoMTRegristerAck(INT32 nErrorCode, const char* szVersion, INT32 nMsgVersion, const char* szBuildVersion)
{
	INT32 nRetCode = 0;

	U2N_REGRISTER_ACK* pMsg = (U2N_REGRISTER_ACK*)(m_pPacketAllocator->Alloc(sizeof(U2N_REGRISTER_ACK)));
	LOG_PROCESS_ERROR(pMsg);
	
	memset(pMsg, 0, sizeof(U2N_REGRISTER_ACK));
	pMsg->wMsg = u2n_regrister_ack;
    pMsg->nErrorCode = nErrorCode;
    strxcpy(pMsg->szVersion, szVersion, sizeof(pMsg->szVersion) );
	pMsg->nMsgVersion = nMsgVersion;
	strxcpy(pMsg->szBuildVersion, szBuildVersion, sizeof(pMsg->szBuildVersion));

	nRetCode = _SendMT((PACKET_BUFFER*)pMsg, sizeof(U2N_REGRISTER_ACK));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CGDMessageHandler::DoMTSyncProcessSummary()
{	
	INT32 nRetCode = 0;

	U2N_SYNC_DEFAULT_INFO* pMsg = (U2N_SYNC_DEFAULT_INFO*)(m_pPacketAllocator->Alloc(sizeof(U2N_SYNC_DEFAULT_INFO)));
	LOG_PROCESS_ERROR(pMsg);

	memset(pMsg, 0, sizeof(U2N_SYNC_DEFAULT_INFO));

	pMsg->wMsg = u2n_sync_processes_summary;
	pMsg->nDefaultCount[stMS] = g_GuardConfig.nLocalMSCount;
	pMsg->nDefaultCount[stDB] = g_GuardConfig.nLocalDBCount;
	pMsg->nDefaultCount[stBS] = g_GuardConfig.nLocalBSCount;
	pMsg->nDefaultCount[stLS] = g_GuardConfig.nLocalLSCount;
	pMsg->nDefaultCount[stGT] = g_GuardConfig.nLocalGTCount;
	pMsg->nDefaultCount[stGS] = g_GuardConfig.nLocalGSCount;
	pMsg->nDefaultCount[stDL] = g_GuardConfig.nLocalDLCount;
	pMsg->nDefaultCount[stMM] = g_GuardConfig.nLocalMMCount;
	pMsg->nDefaultCount[stMG] = g_GuardConfig.nLocalMGCount;

	nRetCode = _SendMT((PACKET_BUFFER*)pMsg, sizeof(U2N_SYNC_DEFAULT_INFO));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CGDMessageHandler::DoMTUpdateProcess(INT32 nState, UINT32 dwProcessID, UINT8 byType, UINT32 dwSessionID, BOOL bAuto)
{
	INT32 nRetCode = 0;
	N2U_UPDATE_SESSION* pMsg = NULL;
	CGDSessionMgr &rSessionMgr = CGDSessionMgr::GetInstance();

	pMsg = (N2U_UPDATE_SESSION*)m_pPacketAllocator->Alloc(sizeof(N2U_UPDATE_SESSION));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = n2u_update_process_info;
	pMsg->dwProcessID = dwProcessID;
	pMsg->nState = nState;
	pMsg->bAuto = bAuto;
	pMsg->dwSessionID = dwSessionID;
	pMsg->byType = byType;

	nRetCode = _SendMT((PACKET_BUFFER*)pMsg, sizeof(N2U_UPDATE_SESSION));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CGDMessageHandler::DoMTDeployServerVersionAck(INT32 nErrorCode, const char* pcszInfo)
{
	INT32 nRetCode = 0;
	U2N_DEPLOY_SERVER_VERSION_ACK* pMsg = NULL;
	CGDSessionMgr &rSessionMgr = CGDSessionMgr::GetInstance();

	pMsg = (U2N_DEPLOY_SERVER_VERSION_ACK*)m_pPacketAllocator->Alloc(sizeof(U2N_DEPLOY_SERVER_VERSION_ACK));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = u2n_deploy_server_version_ack;
	pMsg->nErrorCode = nErrorCode;
	strxcpy(pMsg->szInfo, pcszInfo, sizeof(pMsg->szInfo));

	nRetCode = _SendMT((PACKET_BUFFER*)pMsg, sizeof(U2N_DEPLOY_SERVER_VERSION_ACK));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CGDMessageHandler::DoMTHotUpdatePatchAck(INT32 nErrorCode, const char* pcszInfo)
{
	INT32 nRetCode = 0;
	U2N_HOT_UPDATE_PATCH_ACK* pMsg = NULL;
	CGDSessionMgr &rSessionMgr = CGDSessionMgr::GetInstance();

	pMsg = (U2N_HOT_UPDATE_PATCH_ACK*)m_pPacketAllocator->Alloc(sizeof(U2N_HOT_UPDATE_PATCH_ACK));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = u2n_hot_update_patch_ack;
	pMsg->nErrorCode = nErrorCode;
	strxcpy(pMsg->szInfo, pcszInfo, sizeof(pMsg->szInfo));

	nRetCode = _SendMT((PACKET_BUFFER*)pMsg, sizeof(U2N_HOT_UPDATE_PATCH_ACK));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

void CGDMessageHandler::OnAllPing(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession)
{
    ServerSession* pSession = (ServerSession*)pSocketSession->GetUserData();
    if(pSession)
		pSession->qwTimer = GetTickCountEx() + g_GuardConfig.nPingGuardTimeout;

    return;
}

void CGDMessageHandler::OnProcessRegrister(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession)
{
    INT32 nRetCode = 0;

    A2U_REGRISTER* pMsg = (A2U_REGRISTER*)pPacketBuffer;
    CGDSessionMgr& rSessionMgr = CGDSessionMgr::GetInstance();
    UINT64 qwCurrentTick = GetTickCountEx();

	LOG_PROCESS_ERROR(pMsg->bySessionID > 0);

    ServerSession* pSession = (ServerSession*)pSocketSession->GetUserData();
    LOG_PROCESS_ERROR(pSession == NULL);
    
    nRetCode = rSessionMgr.RemoveServerSession(pSocketSession);
    LOG_PROCESS_ERROR(nRetCode);
    
    switch(pMsg->byType)
    {
    case stLS:
        {
            SLSSession& oLSSession = rSessionMgr.GetLSSession();
            oLSSession.pSocketSession = pSocketSession;
            oLSSession.qwTimer = qwCurrentTick + g_GuardConfig.nServerPingTimeout;
            oLSSession.eState = epsNormal;
			oLSSession.dwSessionID = pMsg->bySessionID;

            pSocketSession->SetUserData(&oLSSession);
            INF("ls registered successfully, pid = %d", pMsg->dwProcessID);
        }
        break;
    case stMS:
        {
            SMSSession& oMSSession = rSessionMgr.GetMSSession();
            oMSSession.pSocketSession = pSocketSession;
			oMSSession.qwTimer = qwCurrentTick + g_GuardConfig.nServerPingTimeout;
			oMSSession.eState = epsNormal;
			oMSSession.dwSessionID = pMsg->bySessionID;

            pSocketSession->SetUserData(&oMSSession);
			INF("ms registered successfully, pid = %d", pMsg->dwProcessID);
        }
        break;
    case stDB:
        {
            SDBSession& oDBSession = rSessionMgr.GetDBSession();
            oDBSession.pSocketSession = pSocketSession;
			oDBSession.qwTimer = qwCurrentTick + g_GuardConfig.nServerPingTimeout;
			oDBSession.eState = epsNormal;
			oDBSession.dwSessionID = pMsg->bySessionID;

			pSocketSession->SetUserData(&oDBSession);
			INF("db registered successfully, pid = %d", pMsg->dwProcessID);
		}
		break;
	case stBS:
	{
		SBSSession& oBSSession = rSessionMgr.GetBSSession();
		oBSSession.pSocketSession = pSocketSession;
		oBSSession.qwTimer = qwCurrentTick + g_GuardConfig.nServerPingTimeout;
		oBSSession.eState = epsNormal;
		oBSSession.dwSessionID = pMsg->bySessionID;

		pSocketSession->SetUserData(&oBSSession);
		INF("bs registered successfully, pid = %d", pMsg->dwProcessID);
	}
		break;
	case stDL:
	{
		SDLSession& oDLSession = rSessionMgr.GetDLSession();
		oDLSession.pSocketSession = pSocketSession;
		oDLSession.qwTimer = qwCurrentTick + g_GuardConfig.nServerPingTimeout;
		oDLSession.eState = epsNormal;
		oDLSession.dwSessionID = pMsg->bySessionID;

		pSocketSession->SetUserData(&oDLSession);
		INF("dl registered successfully, pid = %d", pMsg->dwProcessID);
	}
		break;
	case stGT:
	{
		SGTSession* poGTSession = rSessionMgr.GetGTSession(pMsg->bySessionID);
		LOG_PROCESS_ERROR(poGTSession);

		poGTSession->pSocketSession = pSocketSession;
		poGTSession->qwTimer = qwCurrentTick + g_GuardConfig.nServerPingTimeout;
		poGTSession->eState = epsNormal;
		poGTSession->dwSessionID = pMsg->bySessionID;

		pSocketSession->SetUserData(poGTSession);
		INF("gt %d registered successfully, pid = %d", poGTSession->dwSessionID, pMsg->dwProcessID);
	}
		break;
	case stGS:
	{
		SGSSession* poGSSession = rSessionMgr.GetGSSession(pMsg->bySessionID);
		LOG_PROCESS_ERROR(poGSSession);

		poGSSession->pSocketSession = pSocketSession;
		poGSSession->qwTimer = qwCurrentTick + g_GuardConfig.nServerPingTimeout;
		poGSSession->eState = epsNormal;
		poGSSession->dwSessionID = pMsg->bySessionID;

		pSocketSession->SetUserData(poGSSession);
		INF("gs %d registered successfully, pid = %d", poGSSession->dwSessionID, pMsg->dwProcessID);
	}
		break;
	case stGM:
	{
		SGMSession& rGMSession = rSessionMgr.GetGMSession();
		rGMSession.pSocketSession = pSocketSession;
		rGMSession.qwTimer = qwCurrentTick + g_GuardConfig.nServerPingTimeout;
		rGMSession.eState = epsNormal;
		rGMSession.dwSessionID = pMsg->bySessionID;

		pSocketSession->SetUserData(&rGMSession);
		INF("gm registered successfully, pid = %d", pMsg->dwProcessID);
	}
		break;
	case stMM:
	{
		SMMSession& rMMSession = rSessionMgr.GetMMSession();
		rMMSession.pSocketSession = pSocketSession;
		rMMSession.qwTimer = qwCurrentTick + g_GuardConfig.nServerPingTimeout;
		rMMSession.eState = epsNormal;
		rMMSession.dwSessionID = pMsg->bySessionID;

		pSocketSession->SetUserData(&rMMSession);
		INF("mm registered successfully, pid = %d", pMsg->dwProcessID);

		break;
	}
	case stMG:
	{
		SMGSession* pMGSession = rSessionMgr.GetMGSession(pMsg->bySessionID);
		pMGSession->pSocketSession = pSocketSession;
		pMGSession->qwTimer = qwCurrentTick + g_GuardConfig.nServerPingTimeout;
		pMGSession->eState = epsNormal;
		pMGSession->dwSessionID = pMsg->bySessionID;

		pSocketSession->SetUserData(pMGSession);
		INF("mg %d registered successfully, pid = %d", pMsg->bySessionID, pMsg->dwProcessID);

		break;
	}
	default:
		LOG_PROCESS_ERROR(FALSE);
		break;
	}

	pSession = (ServerSession*)pSocketSession->GetUserData();
	LOG_PROCESS_ERROR(pSession);

	pSession->dwProcessID = pMsg->dwProcessID;
	if (CProcessMgr::GetInstance().IsProcessRuningByID(pMsg->dwProcessID))
	{
		//pSession->bAuto = TRUE;
	}
	else
	{
		//pSession->bAuto = FALSE;
		nRetCode = CProcessMgr::GetInstance().AddProcessInfo(pMsg->byType, pMsg->dwProcessID, 0, FALSE);
		LOG_CHECK_ERROR(nRetCode);
	}

	nRetCode = CProcessMgr::GetInstance().SetProcessInfo(pMsg->dwProcessID, pMsg->byType, pMsg->bySessionID);
	LOG_PROCESS_ERROR(nRetCode);

	nRetCode = CProcessMgr::GetInstance().SyncProcessInfo(epsNormal, pMsg->dwProcessID);
	LOG_PROCESS_ERROR(nRetCode);

	return;
Exit0:
	CRI("OnProcessRegrister fail, type is %d, PID = %d, session =%d", pMsg->byType, pMsg->dwProcessID, pMsg->bySessionID);
	return;
}

void CGDMessageHandler::GDAlertMT(const char* szContent, ...)
{
	INT32 nRetCode = 0;
	const tm_ex* pNow = NULL;

	PROCESS_ERROR(CGDSessionMgr::GetInstance().GetMTSession().pSocketSession);

	char szInfo[4096] = { 0 };
	va_list valist;
	va_start(valist, szContent);
	vsnprintf(szInfo, sizeof(szInfo), szContent, valist);
	va_end(valist);

	pNow = localtime_ex();
	nRetCode = DoMTNotify(stGD, 0, 0, errCritical,
		"%d-%02d-%02d %02d:%02d:%02d.%03d %s",
		pNow->tm_year, pNow->tm_mon, pNow->tm_mday,
		pNow->tm_hour, pNow->tm_min, pNow->tm_sec, pNow->tm_msec,
		szInfo);
	LOG_CHECK_ERROR(nRetCode);
Exit0:
	return;
}

void CGDMessageHandler::OnAllNotify(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession)
{
	INT32 nRetCode = 0;
	WIN32_FIND_DATA FileData;
	const tm_ex* pNow = NULL;

	char szBuffer[4096] = { 0 };
	INT32 nBufferOffset = 0;
	FILE* poReportFileHandle = NULL;

	A2U_NOTIFY * pPkg = (A2U_NOTIFY*)pPacketBuffer;
	LOG_PROCESS_ERROR(pPkg);

	// 1 make content
	pNow = localtime_ex();
	nBufferOffset = snprintf(szBuffer, sizeof(szBuffer),
		"NOTIFY_%d [%s:%d] %d-%02d-%02d %02d:%02d:%02d.%03d %s",
		pPkg->byLevel,  // szLevel
		GetServerShortName(pPkg->bySvrType), pPkg->bySvrID,
		pNow->tm_year, pNow->tm_mon, pNow->tm_mday,
		pNow->tm_hour, pNow->tm_min, pNow->tm_sec, pNow->tm_msec,
		pPkg->szContent);
	INF(szBuffer);

	// 2 notify MT
	nRetCode = DoMTNotify(pPkg->bySvrType, pPkg->bySvrID, pPkg->byLevel, pPkg->nErrorCode, "%s", szBuffer);
	LOG_CHECK_ERROR(nRetCode);

Exit0:
	if (poReportFileHandle)
	{
		fclose(poReportFileHandle);
		poReportFileHandle = NULL;
	}
	return;
}

void CGDMessageHandler::OnMSCommandAck(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession)
{
	INT32 nRetCode = 0;
	M2U_COMMAND_RESPONSE * pPkg = (M2U_COMMAND_RESPONSE*) pPacketBuffer;
	LOG_PROCESS_ERROR(pPkg);

	nRetCode = DoMTUpdateCmdAck( errSuccess, pPkg->szResult);
	LOG_PROCESS_ERROR( nRetCode );

Exit0:
	return;
}

void CGDMessageHandler::OnMTRegrister(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession)
{
    INT32 nRetCode = 0;
    ServerSession* pSession = NULL;
    char pcszInfo[PATH_LEN] = {0};

	N2U_REGRISTER* pMsg = (N2U_REGRISTER*)pPacketBuffer;
	CGDSessionMgr& rSessionMgr = CGDSessionMgr::GetInstance();
	UINT64 qwCurrentTick = GetTickCountEx();

    struct in_addr newAddr = {0};
    UINT32 dwRemoteAddr = 0; 
    UINT16 wRemotePort = 0; 
    LOG_PROCESS_ERROR( pSocketSession );
    nRetCode = pSocketSession->GetRemoteAddress(dwRemoteAddr, wRemotePort);
    LOG_CHECK_ERROR( nRetCode ); 
    newAddr.s_addr = dwRemoteAddr;

    pSession = (ServerSession*)pSocketSession->GetUserData();
    LOG_PROCESS_ERROR(pSession == NULL);

	nRetCode = rSessionMgr.RemoveServerSession(pSocketSession);
	LOG_PROCESS_ERROR(nRetCode);

	if (strnicmp(pMsg->szName, g_GuardConfig.szMTUser, strlen(g_GuardConfig.szMTUser)) != 0 ||
		strnicmp(pMsg->szPwd, g_GuardConfig.szMTPwd, strlen(g_GuardConfig.szMTPwd)) != 0)
	{
		GD_ERROR_MT("name or password don't match!");
		LOG_PROCESS_ERROR(FALSE);
	}

    SMTSession& oMTSession = rSessionMgr.GetMTSession();
    //LOG_PROCESS_ERROR( oMTSession.eState != egssNormal  );
    //LOG_PROCESS_ERROR( oMTSession.qwTimer != 0xFFFFFFFF  );
    if( oMTSession.pSocketSession != NULL && oMTSession.pSocketSession != pSocketSession ) 
    {
        struct in_addr oldAddr = {0};
        UINT32 dwOldRemoteAddr = 0; 
        UINT16 wOldRemotePort = 0; 
        nRetCode = oMTSession.pSocketSession->GetRemoteAddress(dwOldRemoteAddr, wOldRemotePort);
        LOG_CHECK_ERROR( nRetCode ); 
        oldAddr.s_addr = dwOldRemoteAddr;

		snprintf(pcszInfo, sizeof(pcszInfo), "kick off old MT from %s, because new MT from %s login", inet_ntoa(oldAddr), inet_ntoa(newAddr));
		CRI(pcszInfo);
		GD_ERROR_MT(pcszInfo);

        nRetCode = DoMTRegristerAck(errLoginRepeat, pcszInfo, MAINTAIN_TOOLS_MSG_VERSION, MAINTAIN_TOOLS_BUILD_VERSION);
        LOG_CHECK_ERROR(nRetCode);

		oMTSession.pSocketSession->Close();
    }

	// set new MT session
	oMTSession.pSocketSession = pSocketSession;
	oMTSession.qwTimer = qwCurrentTick + g_GuardConfig.nServerPingTimeout;
	oMTSession.eState = epsNormal;

	pSocketSession->SetUserData(&oMTSession);

	snprintf(pcszInfo, sizeof(pcszInfo), "set new session: MT from %s", inet_ntoa(newAddr));
	INF(pcszInfo);

	// reply new MT
    nRetCode = CGuardServer::GetInstance().FetchCurrentVersion(pcszInfo, sizeof(pcszInfo));
    LOG_CHECK_ERROR(nRetCode);

	nRetCode = DoMTRegristerAck(errSuccess, pcszInfo, MAINTAIN_TOOLS_MSG_VERSION, MAINTAIN_TOOLS_BUILD_VERSION);
	LOG_CHECK_ERROR(nRetCode);

	nRetCode = DoMTSyncProcessSummary();
	LOG_CHECK_ERROR(nRetCode);

	nRetCode = CProcessMgr::GetInstance().SyncAllProcessInfo();
	LOG_CHECK_ERROR(nRetCode);

    INF("MT Register Success from %s:%d", inet_ntoa(newAddr), wRemotePort );
	return;
Exit0:
	if(pSocketSession)
		pSocketSession->Close();
}

void CGDMessageHandler::OnMTExecCmd(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession)
{
	INT32 nRetCode = 0;
	char szInfo[256] = { 0 };
	N2U_UPDATE_CMD* pMsg = (N2U_UPDATE_CMD*)pPacketBuffer;

	LOG_PROCESS_ERROR(pMsg->szCmd[0] != '\0' );

	if (pMsg->szCmd[0] == '.') // lua gm command
	{
		nRetCode = CCmdMgr::GetInstance().ExecGMCmd(pMsg->szCmd);
		LOG_PROCESS_ERROR(nRetCode);
	}
	else
	{
		nRetCode = CCmdMgr::GetInstance().ExecOPCmd(pMsg->szCmd);
		LOG_PROCESS_ERROR(nRetCode);

		_snprintf(szInfo, sizeof(szInfo), "ExecCmd [%s] issue ok", pMsg->szCmd);
		nRetCode = CGDMessageHandler::GetInstance().DoMTUpdateCmdAck(errSuccess, szInfo);
		LOG_CHECK_ERROR(nRetCode);
	}

	return;
Exit0:
	_snprintf(szInfo, sizeof(szInfo), "ExecCmd [%s] issue failed", pMsg->szCmd);
	nRetCode = DoMTUpdateCmdAck(nRetCode, szInfo );
	LOG_CHECK_ERROR(nRetCode);// LOG_PROCESS_ERROR will result in infinite loop

	return;
}

BOOL CGDMessageHandler::_GenerateHotUpdateBatFile(const char* pzName, const char* pszPatchPath, const char* pszServerRunPath)
{
	FILE *fp = NULL;
	char szResultFilePath[PATH_LEN] = { 0 };
	snprintf(szResultFilePath, sizeof(szResultFilePath), "%s\\%s", ".", HOT_UPDATE_PATCH_RESULT_FILE_NAME);

	fp = fopen(pzName, "w+");
	LOG_PROCESS_ERROR(fp);

	fprintf(fp, "set PatchFileName=%%1\r\n");

	fprintf(fp, "attrib -R %s\\data \r\n", pszServerRunPath);
	fprintf(fp, "del /F/Q %s\\data\\commonconfig_patch*.pak \r\n", pszServerRunPath);
	fprintf(fp, "del /F/Q %s\\data\\globalconfig_patch*.pak \r\n", pszServerRunPath);
	fprintf(fp, "copy %s\\%%PatchFileName%% %s\\data\\ /Y \r\n", pszPatchPath, pszServerRunPath);
	fprintf(fp, "IF NOT %%ERRORLEVEL%% == 0 ( echo \"error: copy %%PatchFileName%% to data failed!\" > %s && GOTO :EOF )\r\n\r\n", szResultFilePath);
	//
	fprintf(fp, "del /f/q version_exclude.txt\r\n");

	// 5 finish
	fprintf(fp, "echo %%PatchFileName%% > %s\r\n", szResultFilePath);
	fprintf(fp, "echo %%PatchFileName%% > %s \r\n", CURRENT_PATCH_FILE_NAME);		// leave a tag in ServerRunPath
	fprintf(fp, "echo %%PatchFileName%% > %s\\%s \r\n\r\n", g_GuardConfig.szGuardPath, CURRENT_PATCH_FILE_NAME);		// and do the same in GuardPath

	fclose(fp);
	return TRUE;

Exit0:
	if (fp)
	{
		fclose(fp);
		fp = NULL;
	}
	return FALSE;
}

BOOL CGDMessageHandler::_GenerateDeployBatFile(const char* pzName, const char* pszVersionPath, const char* pszServerRunPath)
{
	FILE *fp = NULL;

	char szDeployResultFile[PATH_LEN] = { 0 };
	snprintf(szDeployResultFile, sizeof(szDeployResultFile), "%s\\%s", g_GuardConfig.szGuardPath, DEPLOY_RESULT_FILE_NAME);

	fp = fopen(pzName, "w+");
	LOG_PROCESS_ERROR(fp);

	fprintf(fp, "set VersionFileName=%%1\r\n");
	fprintf(fp, "set VersionNo=%%VersionFileName:.zip=%%\r\n\r\n");

	fprintf(fp, "IF NOT EXIST %s ( echo \"error: VersionPath %s not exist!\" > %s && GOTO :EOF)\r\n", pszVersionPath, pszVersionPath, szDeployResultFile);
	fprintf(fp, "IF NOT EXIST %s ( echo \"error: ServerRunPath %s not exist!\" > %s && GOTO :EOF)\r\n", pszServerRunPath, pszServerRunPath, szDeployResultFile);

	//// 0 for guard self, update ..\\guardconfig\\guard_area_config.lua
	//fprintf(fp, "IF NOT EXIST guardconfig (  echo \"error: guardconfig %s not exist!\" > %s && GOTO :EOF)\r\n");
	//fprintf(fp, "attrib -R guardconfig\\guard_area_config.lua\r\n");
	//fprintf(fp, "copy %s\\%%VersionFileName%%-guard_area_config.lua guardconfig\\guard_area_config.lua /Y\r\n", pszVersionPath);
	//fprintf(fp, "IF NOT %%ERRORLEVEL%% == 0 ( echo \"error: copy %%VersionFileName%%-guard_area_config.lua failed!\" > %s && GOTO :EOF)\r\n", szDeployResultFile);

	// 1
	fprintf(fp, "cd %s\r\n", pszVersionPath);

	fprintf(fp, "..\\7z.exe -y x %%VersionFileName%%\r\n");
	fprintf(fp, "IF NOT EXIST %%VersionNo%% ( echo \"error: 7z unzip %%VersionFileName%% failed!\" > %s && GOTO :EOF)\r\n", szDeployResultFile);

	// 2 update globalconfig\\area_config.lua
	fprintf(fp, "IF NOT EXIST %%VersionNo%%\\globalconfig ( mkdir %%VersionNo%%\\globalconfig )\r\n");
	fprintf(fp, "attrib -R  %%VersionNo%%\\globalconfig\\area_config.lua \r\n");
	fprintf(fp, "copy %%VersionFileName%%-area_config.lua %%VersionNo%%\\globalconfig\\area_config.lua /Y\r\n");
	fprintf(fp, "IF NOT %%ERRORLEVEL%% == 0 ( echo \"error: copy %%VersionFileName%%-area_config.lua failed!\" > %s && GOTO :EOF)\r\n", szDeployResultFile);

	fprintf(fp, "copy %%VersionFileName%%-gmsecurityconfig.lua %%VersionNo%%\\globalconfig\\gmsecurityconfig.lua /Y\r\n");
	fprintf(fp, "IF NOT %%ERRORLEVEL%% == 0 ( echo \"error: copy %%VersionFileName%%-gmsecurityconfig.lua failed!\" > %s && GOTO :EOF)\r\n", szDeployResultFile);
	//
	fprintf(fp, "cd ..\r\n\r\n");

	////////////////////
	fprintf(fp, "cd %s\r\n\r\n", pszServerRunPath);	// below all output in pszServerRunPath

	// 3 delete old file
	fprintf(fp, "call :try_del dbserver\r\n");
	fprintf(fp, "call :try_del manageserver\r\n");
	fprintf(fp, "call :try_del gameserver\r\n");
	fprintf(fp, "call :try_del gateserver\r\n");
	fprintf(fp, "call :try_del datalogserver\r\n");
	fprintf(fp, "call :try_del loginserver\r\n");
	fprintf(fp, "call :try_del balanceserver\r\n");
	fprintf(fp, "call :try_del gmserver\r\n");

	fprintf(fp, "call :try_del cache /S/Q\r\n");
	fprintf(fp, "call :try_del data\r\n");
	fprintf(fp, "del /Q gpkitsvr64.dll\r\n");
	fprintf(fp, "del /Q SdoBase.dll\r\n");
	fprintf(fp, "del /Q sotsapi\r\n");
	//fprintf(fp, "del /Q global_config.lua\r\n");	// guard used
	// remove patch file
	fprintf(fp, "call :try_del globalconfig /S/Q \r\n");
	//fprintf(fp, "call :del_exclude globalconfig area_config.lua \r\n");
	fprintf(fp, "call :try_del commonconfig /S/Q \r\n");
	//
	fprintf(fp, "IF NOT %%ERRORLEVEL%% == 0 ( echo \"error: remove server folder failed!\" > %s && GOTO :EOF )\r\n", szDeployResultFile);
	fprintf(fp, "\r\n");

	// 4 copy
	fprintf(fp, "echo placeholder > version_exclude.txt\r\n");
	//fprintf(fp, "echo lua64_d.dll		>> version_exclude.txt\r\n");	// not to copy guard relevant files
	//fprintf(fp, "echo lua64.dll		>> version_exclude.txt\r\n");
	//fprintf(fp, "echo msvcp120d.dll	>> version_exclude.txt\r\n");
	//fprintf(fp, "echo msvcp120.dll	>> version_exclude.txt\r\n");
	//fprintf(fp, "echo msvcr120d.dll	>> version_exclude.txt\r\n");
	//fprintf(fp, "echo msvcr120.dll	>> version_exclude.txt\r\n");
	fprintf(fp, "echo %%VersionNo%%\\_GUARD		>> version_exclude.txt\r\n");
	//fprintf(fp, "echo guardserver\\guardserver64.exe	>> version_exclude.txt\r\n");
	//fprintf(fp, "echo guardserver\\guardserver64.pdb	>> version_exclude.txt\r\n");
	//fprintf(fp, "echo guardserver\\guardserver64_d.exe	>> version_exclude.txt\r\n");
	//fprintf(fp, "echo guardserver\\guardserver64_d.pdb	>> version_exclude.txt\r\n");
	//
	fprintf(fp, "xcopy %s\\%%VersionNo%%\\* . /E/I/R/Y /EXCLUDE:version_exclude.txt\r\n", pszVersionPath);// pszServerRunPath
	fprintf(fp, "IF NOT %%ERRORLEVEL%% == 0 ( echo \"error: xcopy all files outer failed!\" > %s && GOTO :EOF )\r\n\r\n", szDeployResultFile);
	//
	fprintf(fp, "del /f/q version_exclude.txt\r\n");

	// 5 finish
	fprintf(fp, "echo %%VersionFileName%% > %s\r\n", szDeployResultFile);
	fprintf(fp, "echo %%VersionFileName%% > %s \r\n", CURRENT_VERSION_FILE_NAME);	// leave a tag in ServerRunPath
	fprintf(fp, "echo %%VersionFileName%% > %s\\%s \r\n\r\n", g_GuardConfig.szGuardPath, CURRENT_VERSION_FILE_NAME);		// and do the same in GuardPath
	// remove all version files but this version
	fprintf(fp, "call :del_exclude %s %%VersionNo%% \r\n", pszVersionPath);

	// 8 delete bat self
	//fprintf(fp, ":done\r\n", );
	//fprintf(fp, "\tdel /f/q %0\r\n", );
	fprintf(fp, "goto :EOF\r\n\r\n");

	// 9 func define
	fprintf(fp, ":try_del\r\n");
	fprintf(fp, "\tsetlocal\r\n");
	fprintf(fp, "\tIF EXIST %%1 ( del /F/S/Q %%1 & rd /S/Q %%1 )\r\n");// to defend bug in windows
	fprintf(fp, "\tendlocal&goto :EOF\r\n");

	fprintf(fp, ":del_exclude\r\n");	// %1 target dir, %2 exclude file prefix
	fprintf(fp, "setlocal \r\n");
	fprintf(fp, "IF NOT EXIST %%1 (GOTO :EOF)\r\n");
	fprintf(fp, "mkdir %%1-%%2 \r\n");
	fprintf(fp, "move /Y %%1\\%%2* %%1-%%2\\ \r\n");	// move file
	fprintf(fp, "move /Y %%1\\%%2  %%1-%%2\\ \r\n");	// move folder
	//fprintf(fp, "rd %%1 /S/Q & ping -n 1 127.0.0.1 > null & if exist %%1 (rd %%1 /S/Q )\r\n");				// to defend bug in windows
	fprintf(fp, "del /F/S/Q %%1 & rd /S/Q %%1\r\n");
	fprintf(fp, "mkdir %%1 \r\n");
	fprintf(fp, "xcopy %%1-%%2\\* %%1\\  /E/I/R/Y \r\n");
	fprintf(fp, "del /F/S/Q %%1-%%2 & rd /S/Q %%1-%%2\r\n");
	fprintf(fp, "endlocal&goto :EOF\r\n");

	fclose(fp);

	return TRUE;
Exit0:
	if (fp)
	{
		fclose(fp);
		fp = NULL;
	}
	return FALSE;
}

void CGDMessageHandler::OnMTDeployServerVersion(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession)
{
	INT32 nRetCode = 0;
	char szErrorLog[256] = {0};
	N2U_DEPLOY_SERVER_VERSION* pMsg = (N2U_DEPLOY_SERVER_VERSION*)pPacketBuffer;
	INT32 nRuningProcessCount = 0;

	sprintf(szErrorLog, "system internal error");

	nRuningProcessCount = CProcessMgr::GetInstance().CountRuningProcessByType(stAll);
	if ( nRuningProcessCount > 0)
	{
		sprintf(szErrorLog, "deploying is not allowed because some processes still running");
		CRI(szErrorLog);
		LOG_PROCESS_ERROR(FALSE);
	}

	//// 1 reload Guard self first
	//char szParam[PATH_LEN] = { 0 };
	//snprintf(szParam, sizeof(szParam), "/C \"attrib -R guardconfig\\guard_area_config.lua && copy %s\\%s-guard_area_config.lua guardconfig\\guard_area_config.lua /Y\"", g_GuardConfig.szServerVersionPath, pMsg->szVersion);
	//nRetCode = (INT32)ShellExecute(NULL, "open", "cmd.exe", szParam, NULL, SW_HIDE);// _getcwd(NULL, 0)
	//LOG_PROCESS_ERROR(nRetCode > 32);

	char szSrcPath[PATH_LEN] = { 0 };
	char szDstPath[PATH_LEN] = { 0 };
	snprintf(szSrcPath, sizeof(szSrcPath), "%s\\%s-guard_area_config.lua", g_GuardConfig.szServerVersionPath, pMsg->szVersion);
	snprintf(szDstPath, sizeof(szDstPath), "guardconfig\\guard_area_config.lua");

	DWORD dwAttrs = GetFileAttributes(szDstPath);
	LOG_PROCESS_ERROR(dwAttrs != INVALID_FILE_ATTRIBUTES);
	if (dwAttrs & FILE_ATTRIBUTE_READONLY)
	{
		SetFileAttributes(szDstPath, dwAttrs & (~FILE_ATTRIBUTE_READONLY) );
	}

	if (CopyFile(szSrcPath, szDstPath, FALSE))
	{
		nRetCode = CGuardServer::GetInstance().ReloadConfig();
		if (!nRetCode)
		{
			sprintf(szErrorLog, "guard server ReloadConfig failed!");
			LOG_PROCESS_ERROR(FALSE);
		}
	}
	else
	{
		sprintf(szErrorLog, "copy file from %s to %s failed!", szSrcPath, szDstPath);
		LOG_PROCESS_ERROR(FALSE);
	}

	// 2  
	nRetCode = g_DirectoryExists(g_GuardConfig.szServerRunPath);
	if (!nRetCode)
	{
		INF("szServerRunPath %s not exist, now create it", g_GuardConfig.szServerRunPath);
		g_CreateDirectory(g_GuardConfig.szServerRunPath, TRUE);
	}
	if (!g_DirectoryExists(g_GuardConfig.szServerRunPath))
	{
		sprintf(szErrorLog, "szServerRunPath %s don't exist and create it failed!", g_GuardConfig.szServerRunPath);
		LOG_PROCESS_ERROR(FALSE);
	}

	// 3
	const char* szBatFile = "deploy_server_generated.bat";
	//if (pFile = fopen(szBatFile, "r"))
	//	fclose(pFile);
	//else
	{
		nRetCode = _GenerateDeployBatFile(szBatFile, g_GuardConfig.szServerVersionPath, g_GuardConfig.szServerRunPath);
		if (!nRetCode)
		{
			sprintf(szErrorLog, "generate bat file failed!");
			LOG_PROCESS_ERROR(FALSE);
		}
	}

	char szParam[PATH_LEN] = { 0 };
	sprintf(szParam, "%s > deploy_version.log", pMsg->szVersion);
	nRetCode = (INT32)ShellExecute(NULL, "open", szBatFile, szParam, NULL, SW_HIDE);// _getcwd(NULL, 0)
	if (nRetCode <= 32)
	{
		sprintf(szErrorLog, "ShellExecute %s %s Failed!", szBatFile, szParam);
		LOG_PROCESS_ERROR(FALSE);
	}

	// 4
	CGuardServer::GetInstance().SetProcessingVersion(pMsg->szVersion);  // used to verify when async checking
	return;

Exit0:

	CRI(szErrorLog);
	GD_ERROR_MT(szErrorLog);

	nRetCode = DoMTDeployServerVersionAck(errCritical, pMsg->szVersion);
	LOG_CHECK_ERROR(nRetCode);

	return;
}

void CGDMessageHandler::OnMTHotUpdatePatch(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession)
{
	INT32 nRetCode = 0;
	N2U_HOT_UPDATE_PATCH* pMsg = (N2U_HOT_UPDATE_PATCH*)pPacketBuffer;
	char szParam[PATH_LEN] = { 0 };
	FILE *pFile = NULL;

	const char* szBatFile = "hot_update_patch_generated.bat";

	if (pFile = fopen(szBatFile, "r"))
		fclose(pFile);
	else
	{
		nRetCode = _GenerateHotUpdateBatFile(szBatFile, g_GuardConfig.szServerPatchPath, g_GuardConfig.szServerRunPath);
		LOG_PROCESS_ERROR(nRetCode);
	}

	sprintf(szParam, "%s > hot_update_patch.log", pMsg->szPatch);
	//nRetCode = (INT32)
	ShellExecute(NULL, "open", szBatFile, szParam, NULL, SW_HIDE);
	//LOG_PROCESS_ERROR(nRetCode > 32);

	CGuardServer::GetInstance().SetProcessingPatch(pMsg->szPatch); 
	return;
Exit0:
	nRetCode = DoMTHotUpdatePatchAck(errUnknownError, pMsg->szPatch);
	LOG_CHECK_ERROR(nRetCode);

	return;
}

void CGDMessageHandler::OnMTSendFiles(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession)
{
	char szErrorLog[256] = {0};
    INT32 nRetCode = 0;
	CHAR *pszTargetFolderPath = NULL;

	sprintf(szErrorLog, "system internal error");

    N2U_SEND_FILES* pMsg = (N2U_SEND_FILES*)pPacketBuffer;
    LOG_PROCESS_ERROR( pMsg );

    if(pMsg->wBufferIndex == 0)
    {
        LOG_CHECK_ERROR( NULL==m_pRecvFileHandle );
        if(m_pRecvFileHandle)
        {
            nRetCode = fclose(m_pRecvFileHandle);
            m_pRecvFileHandle = NULL;
            LOG_PROCESS_ERROR(nRetCode == 0);
        }

        //create version folder if need
        WIN32_FIND_DATA FileData; 

        // Note: escape char '\' in m_szVersionPath
		switch (pMsg->nFileType)
		{
		case etftVersion:
			pszTargetFolderPath = g_GuardConfig.szServerVersionPath;
			break;
		case etftPatch:
			pszTargetFolderPath = g_GuardConfig.szServerPatchPath;
			break;
		case etftConfig:
			pszTargetFolderPath = g_GuardConfig.szServerVersionPath;
			break;
		default:
			sprintf(szErrorLog, "invalid send file type! %d", pMsg->nFileType);
			LOG_PROCESS_ERROR(FALSE);
		}

		{
			HANDLE hFind = FindFirstFile(pszTargetFolderPath, &FileData);
			if (hFind == INVALID_HANDLE_VALUE)
			{
				nRetCode = CreateDirectory(pszTargetFolderPath, NULL);
				LOG_PROCESS_ERROR(nRetCode);
			}
			else
			{
				FindClose(hFind);
				if (!(FileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
				{
					sprintf(szErrorLog, "%s exist but not a directory!", pszTargetFolderPath);
					LOG_PROCESS_ERROR(FALSE);
				}
			}
			hFind = FindFirstFile(pszTargetFolderPath, &FileData);
			LOG_PROCESS_ERROR((hFind != INVALID_HANDLE_VALUE));

			snprintf(m_szRecvFilePath, sizeof(m_szRecvFilePath), "%s\\%s", pszTargetFolderPath, pMsg->szFileName);
		}
        m_pRecvFileHandle = fopen(m_szRecvFilePath, "wb");
        LOG_PROCESS_ERROR(m_pRecvFileHandle);

        m_nRecvBufferIndex = 0;
    }

    LOG_PROCESS_ERROR(m_nRecvBufferIndex == pMsg->wBufferIndex);
    LOG_PROCESS_ERROR(m_pRecvFileHandle);

    nRetCode = fwrite(pMsg->szBuffer, 1, pMsg->wBufferSize, m_pRecvFileHandle);
    LOG_PROCESS_ERROR(nRetCode == pMsg->wBufferSize);
    m_nRecvBufferIndex++;

    if( pMsg->wBufferIndex + 1 == pMsg->wBufferTotal )  // the last buffer
    {
        nRetCode = fflush(m_pRecvFileHandle);
        LOG_PROCESS_ERROR(nRetCode == 0);

        nRetCode = fclose(m_pRecvFileHandle);
        m_pRecvFileHandle = NULL;
        LOG_PROCESS_ERROR(nRetCode == 0);
		LOG_PROCESS_ERROR(g_IsFileExist(m_szRecvFilePath));

		if (pMsg->nFileType == etftConfig )
		{
			CHAR szVersionName[PATH_LEN] = { 0 };
			nRetCode = CGuardServer::GetInstance().FetchCurrentVersion(szVersionName, sizeof(szVersionName));
			LOG_PROCESS_ERROR(nRetCode);

			char szParam[PATH_LEN] = { 0 };

			// overwrite version file
			sprintf(szParam, "/C \"copy /Y %s %s\\%s-%s 1>overwrite_version.log\"", m_szRecvFilePath, pszTargetFolderPath, szVersionName, pMsg->szFileName);
			nRetCode = (INT32)ShellExecute(NULL, "open", "cmd.exe", szParam, NULL, SW_HIDE);// _getcwd(NULL, 0)
			if (nRetCode <= 32)
			{
				sprintf(szErrorLog, "ShellExecute overwrite_version error :cmd.exe %s %d", szParam, nRetCode);
				LOG_PROCESS_ERROR(FALSE);
			}

			if (strcmp(pMsg->szFileName, "guard_area_config.lua") == 0)
			{
				//directly move to guard run path
				CHAR szRealTargetPath[PATH_LEN] = { 0 };
				snprintf(szRealTargetPath, sizeof(szRealTargetPath), "%s\\guardconfig\\", _getcwd(NULL, 0));
				sprintf(szParam, "/C \"copy /Y %s %s 1>guard_deploy.log\"", m_szRecvFilePath, szRealTargetPath);
				nRetCode = (INT32)ShellExecute(NULL, "open", "cmd.exe", szParam, NULL, SW_HIDE);// _getcwd(NULL, 0)
				if (nRetCode <= 32)
				{
					sprintf(szErrorLog, "ShellExecute guard_deploy error :cmd.exe %s %d", szParam, nRetCode);
					LOG_PROCESS_ERROR(FALSE);
				}

				nRetCode = CGuardServer::GetInstance().ReloadConfig();// NOTE: maybe change g_GuardConfig.szServerRunPath
				if (!nRetCode)
				{
					sprintf(szErrorLog, "guard ReloadConfig failed!");
					LOG_PROCESS_ERROR(FALSE);
				}
			}
			else
			{
				//directly move to server run path
				CHAR szRealTargetPath[PATH_LEN] = { 0 };
				snprintf(szRealTargetPath, sizeof(szRealTargetPath), "%s\\globalconfig\\", g_GuardConfig.szServerRunPath);
				sprintf(szParam, "/C \"copy /Y %s %s 1>server_deploy.log\"", m_szRecvFilePath, szRealTargetPath);
				nRetCode = (INT32)ShellExecute(NULL, "open", "cmd.exe", szParam, NULL, SW_HIDE);// _getcwd(NULL, 0)
				if (nRetCode <= 32)
				{
					sprintf(szErrorLog, "ShellExecute direct_deploy error :cmd.exe %s %d", szParam, nRetCode);
					LOG_PROCESS_ERROR(FALSE);
				}
			}
		}
		memset(m_szRecvFilePath, 0, sizeof(m_szRecvFilePath));

        nRetCode = DoMTSendFilesAck(errSuccess, pMsg->szFileName, 
            pMsg->wBufferIndex, pMsg->wBufferTotal, pMsg->wFileIndex, pMsg->wFileTotal);
        LOG_PROCESS_ERROR(nRetCode);
    }

    return;
Exit0:
    if(m_pRecvFileHandle)
    {
        nRetCode = fclose(m_pRecvFileHandle);
        LOG_CHECK_ERROR(nRetCode == 0);

        m_pRecvFileHandle = NULL;
        m_nRecvBufferIndex = 0;
        memset(m_szRecvFilePath, 0, sizeof(m_szRecvFilePath));
    }

	CRI(szErrorLog);
	GD_ERROR_MT(szErrorLog);

	nRetCode = DoMTSendFilesAck(-1, pMsg->szFileName,
        pMsg->wBufferIndex, pMsg->wBufferTotal, pMsg->wFileIndex, pMsg->wFileTotal);
    LOG_CHECK_ERROR(nRetCode);

    return;
}


BOOL CGDMessageHandler::DoMTSendFilesAck(INT32 nErrorCode, const char* szFileName, 
                                      UINT16 wBufferIndex, UINT16 wBufferTotal,
                                      UINT16 wFileIndex, UINT16 wFileTotal)
{
    INT32 nRetCode = 0;
    U2N_SEND_FILES_ACK* pMsg = NULL;
    CGDSessionMgr &rSessionMgr = CGDSessionMgr::GetInstance();

    pMsg = (U2N_SEND_FILES_ACK*)m_pPacketAllocator->Alloc(sizeof(U2N_SEND_FILES_ACK));
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = u2n_send_files_ack;

    pMsg->wBufferIndex = wBufferIndex;
    pMsg->wBufferTotal = wBufferTotal;
    pMsg->nErrorCode = nErrorCode;

    pMsg->wFileIndex = wFileIndex;
    pMsg->wFileTotal = wFileTotal;
    strxcpy(pMsg->szFileName, szFileName, sizeof(pMsg->szFileName));

    nRetCode = _SendMT((PACKET_BUFFER*)pMsg, sizeof(U2N_SEND_FILES_ACK));
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

