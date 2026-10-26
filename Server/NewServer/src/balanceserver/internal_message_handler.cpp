#include "stdafx.h"
#include "internal_message_handler.h"

#include "time_ex.h"

#include "server_config.h"

#include "b2m_message.h"
#include "m2b_message.h"
#include "bs_session_mgr.h"
#include "common_message.h"

using namespace InternalMessage;
CBSInternalMessageHandler CBSInternalMessageHandler::ms_Instance;

void CBSInternalMessageHandler::OnAccepted(ISocketAcceptor* pSocketAcceptor, ISocketSession* pSocketSession)
{
    LOG_PROCESS_ERROR(FALSE);
    LOG_PROCESS_ERROR(CBSSessionMgr::GetInstance().GetServerState() != sgsClosing );

Exit0:
    if (pSocketSession)
        pSocketSession->Close();
	return;
}

void CBSInternalMessageHandler::OnConnected(ISocketSession* pSocketSession)
{
	INT32 nRetCode = 0;
	UINT32 dwIP = 0;
    BASE_SESSION* pBaseSession = NULL;
	LOG_PROCESS_ERROR(pSocketSession);

	pBaseSession = (BASE_SESSION*)pSocketSession->GetUserData();
	LOG_PROCESS_ERROR(pBaseSession);

    pBaseSession->qwTimer = GetTickCountEx() + g_ServerConfig.Common.nServerPingTimeout;

	switch(pBaseSession->dwType)
	{
	case stMS:
		{
			MS_SESSION* pMSSession = (MS_SESSION*)pBaseSession;
			pMSSession->bConnected = true;

			dwIP = GetIp(g_ServerConfig.Common.szIntranetAddr, g_ServerConfig.Common.szIntranetMask, TRUE, 0);
			LOG_PROCESS_ERROR(dwIP);

			nRetCode = DoMSRegister(dwIP, g_ServerConfig.BS.dwInternalPort);
			LOG_PROCESS_ERROR(nRetCode);
		}
		break;;
	case stGD:
		{
			GD_SESSION* pGDSession = (GD_SESSION*)pBaseSession;
			pGDSession->bConnected = true;
			pGDSession->qwTimer = GetTickCountEx() + g_ServerConfig.Common.nRegisterGuardTimeout;

			if(CBSSessionMgr::GetInstance().GetServerState() == sgsSelfReady || 
				CBSSessionMgr::GetInstance().GetServerState() == sgsAllReady)
			{
				nRetCode = DoGDRegister();
				LOG_PROCESS_ERROR(nRetCode);
			}
		}
		break;
	case stDB:
	case stGS:
	case stGT:
	case stLS:
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

void CBSInternalMessageHandler::OnRecv(ISocketSession* pSocketSession, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize)
{
    MESSAGE_HEADER* pHeader = NULL;

    LOG_PROCESS_ERROR(pSocketSession);
	LOG_PROCESS_ERROR(pPacketBuffer);

	pHeader = (MESSAGE_HEADER*)pPacketBuffer;
	LOG_PROCESS_ERROR(m_MessageFuncList[pHeader->wMsg]);

	(this->*m_MessageFuncList[pHeader->wMsg])(pPacketBuffer, dwSize, pSocketSession);

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

void CBSInternalMessageHandler::OnDisconnected(ISocketSession* pSocketSession, BOOL bRemoteShutdown)
{
    BASE_SESSION* pBaseSession = NULL;

	LOG_PROCESS_ERROR(pSocketSession);

	pBaseSession = (BASE_SESSION*)pSocketSession->GetUserData();
	PROCESS_ERROR(pBaseSession);

	pBaseSession->pSocketSession = NULL;

	switch (pBaseSession->dwType)
	{
	case stMS:
		{
			MS_SESSION* pMSSession = (MS_SESSION*)pBaseSession;

			pMSSession->qwTimer = GetTickCountEx() + g_ServerConfig.Common.nReconnectTime;
			pMSSession->bConnected = false;
			
			CRI("MS disconnected");
		}
		break;
	case  stGD:
		{
			GD_SESSION* pGDSession = (GD_SESSION*)pBaseSession;
			
			pGDSession->qwTimer = GetTickCountEx() + g_ServerConfig.Common.nReconnectTime;
			pGDSession->bConnected = false;
			
			CRI("GD disconnected");
		}
		break;
    case stGT:
	case stDB:
	case stLS:
	case stGS:
	default:
		LOG_PROCESS_ERROR(FALSE);
		break;
	}

	return;
Exit0:
	return;
}

CBSInternalMessageHandler::CBSInternalMessageHandler()
{
	m_pNet = NULL;
	m_pPacketAllocator = NULL;
	m_pGTSocketAcceptor = NULL;
	memset(m_GTInfo, 0, sizeof(m_GTInfo));
	memset(m_MessageFuncList, 0, sizeof(m_MessageFuncList));
}

CBSInternalMessageHandler::~CBSInternalMessageHandler()
{
    UnInit();
}

BOOL CBSInternalMessageHandler::Init(INet* pNet, IPacketAllocator* pPacketAllocator, ISocketAcceptor* pGTSocketAcceptor)
{
	LOG_PROCESS_ERROR(pNet);

	m_pNet = pNet;
	m_pPacketAllocator = pPacketAllocator;
	m_pGTSocketAcceptor = pGTSocketAcceptor;

	// From All
	m_MessageFuncList[a2a_ping]   =  &CBSInternalMessageHandler::OnAllPing;
	m_MessageFuncList[m2a_all_ready] = &CBSInternalMessageHandler::OnMSAllReady;

	// From MS
	m_MessageFuncList[m2b_register_ack] = &CBSInternalMessageHandler::OnMSRegisterAck;
	m_MessageFuncList[m2a_server_info] = &CBSInternalMessageHandler::OnMSServerInfo;
	m_MessageFuncList[m2a_close] = &CBSInternalMessageHandler::OnMSClose;

    memset(m_GTInfo, 0, sizeof(m_GTInfo));
	return TRUE;
Exit0:
	return FALSE;
}

BOOL CBSInternalMessageHandler::UnInit(void)
{
	return TRUE;
}

CBSInternalMessageHandler& CBSInternalMessageHandler::GetInstance(void)
{
	return ms_Instance;
}

inline BOOL CBSInternalMessageHandler::_SendGD(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, INT32 nOffset)
{
	INT32 nRetCode = 0;

	GD_SESSION& rGDSession = CBSSessionMgr::GetInstance().GetGDSession();
	LOG_PROCESS_ERROR(rGDSession.bConnected);
	LOG_PROCESS_ERROR(rGDSession.pSocketSession);

	nRetCode = rGDSession.pSocketSession->Send((PACKET_BUFFER*)pPacketBuffer, dwSize, nOffset);
	LOG_PROCESS_ERROR(nRetCode == dwSize);

	return TRUE;
Exit0:
	return FALSE;
}

inline BOOL CBSInternalMessageHandler::_SendMS(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, INT32 nOffset)
{
	INT32 nRetCode = 0;

	MS_SESSION& rMSSession = CBSSessionMgr::GetInstance().GetMSSession();
	LOG_PROCESS_ERROR(rMSSession.bConnected);
	LOG_PROCESS_ERROR(rMSSession.pSocketSession);

	nRetCode = rMSSession.pSocketSession->Send((PACKET_BUFFER*)pPacketBuffer, dwSize, nOffset);
	LOG_PROCESS_ERROR(nRetCode == dwSize);

	return TRUE;
Exit0:
	return FALSE;
}

BOOL CBSInternalMessageHandler::DoAllPing(void)
{
	INT32 nRetCode = 0;
	A2A_PING* pMsg = NULL;
	CBSSessionMgr &rSessionMgr = CBSSessionMgr::GetInstance(); 

	if(rSessionMgr.GetGDSession().bConnected)
	{
		pMsg = (A2A_PING*)m_pPacketAllocator->Alloc(sizeof(A2A_PING));
		LOG_PROCESS_ERROR(pMsg);

		pMsg->wMsg = a2a_ping;
		
		nRetCode = _SendGD((PACKET_BUFFER*)pMsg, sizeof(A2A_PING));
		PROCESS_ERROR(nRetCode);
	}

	if(CBSSessionMgr::GetInstance().GetMSSession().bConnected)
	{
		pMsg = (A2A_PING*)m_pPacketAllocator->Alloc(sizeof(A2A_PING));
		LOG_PROCESS_ERROR(pMsg);

		pMsg->wMsg = a2a_ping;
		
		nRetCode = _SendMS((PACKET_BUFFER*)pMsg, sizeof(A2A_PING));
		PROCESS_ERROR(nRetCode);
	} 

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

/************************************************************************/
// To MS

BOOL CBSInternalMessageHandler::DoMSRegister(UINT32 dwAddr, UINT16 wPort)
{
	INT32 nRetCode = 0;

	B2M_REGISTER* pMsg = (B2M_REGISTER*)m_pPacketAllocator->Alloc(sizeof(B2M_REGISTER));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = b2m_register;
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

BOOL CBSInternalMessageHandler::DoMSReady(void)
{
	INT32 nRetCode = 0;

	B2M_READY* pMsg = (B2M_READY*)m_pPacketAllocator->Alloc(sizeof(B2M_READY));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = b2m_ready;

	nRetCode = _SendMS((PACKET_BUFFER*)pMsg, sizeof(B2M_READY));
	LOG_PROCESS_ERROR(nRetCode);

	CBSSessionMgr::GetInstance().SetServerState(sgsSelfReady);
	INF("BS is self ready");

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CBSInternalMessageHandler::DoMSCloseAck(void)
{
	INT32 nRetCode = 0;

	B2M_CLOSE_ACK* pMsg = (B2M_CLOSE_ACK*)m_pPacketAllocator->Alloc(sizeof(B2M_CLOSE_ACK));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = b2m_close_ack;

	nRetCode = _SendMS((PACKET_BUFFER*)pMsg, sizeof(*pMsg));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

/************************************************************************/
// To GD

BOOL CBSInternalMessageHandler::DoGDRegister(void)
{
	INT32 nRetCode = 0;

	A2U_REGRISTER* pMsg = (A2U_REGRISTER*)m_pPacketAllocator->Alloc(sizeof(A2U_REGRISTER));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = a2u_regrister;
	pMsg->byType = stBS;
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
// From ALL

void CBSInternalMessageHandler::OnAllPing(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession)
{
	BASE_SESSION* pBaseSession = (BASE_SESSION*)pSocketSession->GetUserData();

	if(pBaseSession)
		pBaseSession->qwTimer = GetTickCountEx() + g_ServerConfig.Common.nServerPingTimeout;
	
	return;
}

// From MS
//void CBSInternalMessageHandler::OnMSReport(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession)
//{
//	INT32 nRetCode = 0;
//	SGTInfo* pGTSession = NULL;
//
//	T2B_REPORT* pMsg = (T2B_REPORT*)pPacketBuffer;
//	LOG_PROCESS_ERROR(pMsg);
//
//	pGTSession = (SGTInfo*)pSocketSession->GetUserData();
//	PROCESS_SUCCESS(!pGTSession);
//
//	pGTSession->dwCurSessionCount = pMsg->dwCurrentSessionCount;
//	//INF("GT <%08X> Report, Current Session Number is : %d", pGTSession->dwSessionID, pGTSession->dwCurSessionCount);
//	
//	return;
//Exit0:
//	CRI("GT Report Error");
//	if (pSocketSession)
//		pSocketSession->Close();
//Exit1:
//	return;
//}

void CBSInternalMessageHandler::OnMSRegisterAck(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession)
{
	INT32 nRetCode = 0;

    GD_SESSION& rGDSession = CBSSessionMgr::GetInstance().GetGDSession();

	nRetCode = DoMSReady();
	LOG_PROCESS_ERROR(nRetCode);

    if (rGDSession.bConnected && rGDSession.pSocketSession)
    {
        nRetCode = DoGDRegister();
        LOG_PROCESS_ERROR(nRetCode);
    }
	
	INF("register to MS successfully");
	LOG_PROCESS_ERROR(nRetCode);

Exit0:
	return;
}

void CBSInternalMessageHandler::OnMSServerInfo(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession)
{
    INT32 nRetCode = 0;   
    SGTInfo* pGTSession = NULL; 

    M2A_SERVER_INFO* pMsg = (M2A_SERVER_INFO*)pPacketBuffer;
    for(INT32 i = 0; i < MAX_GT_SESSION_COUNT; ++i)
    {
		m_GTInfo[i].nAddrCount = pMsg->GT[i].byCount;
		for (INT32 nAddrIndex = 0; nAddrIndex < pMsg->GT[i].byCount; nAddrIndex++)
		{
			m_GTInfo[i].dwAddr[nAddrIndex] = pMsg->GT[i].dwExternalAddr[nAddrIndex];
			m_GTInfo[i].wPort[nAddrIndex] = pMsg->GT[i].wExternalPort[nAddrIndex];
		}
    }

    return;
}

void CBSInternalMessageHandler::OnMSAllReady(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession)
{
	INT32 nRetCode = 0;

	CBSSessionMgr::GetInstance().SetServerState(sgsAllReady);
	INF("all servers are ready");
}

void CBSInternalMessageHandler::OnMSClose(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession)
{
	CBSSessionMgr::GetInstance().SetServerState(sgsClosing);
	INF("BS is closing");
}