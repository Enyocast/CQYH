#include "stdafx.h"
#include "mg_internal_message_handler.h"

#include "common_message.h"
#include "mm2mg_message.h"
#include "mg2mm_message.h"
#include "mg2l_message.h"
#include "l2mg_message.h"
#include "external_message_size.h"

#include "server_config.h"
#include "statis_info.h"
#include "time_ex.h"
#include "version.h"

#include "mgateserver.h"
#include "mg_external_message_handler.h"
#include "mg_session_mgr.h"

using namespace InternalMessage;
CMGInternalMessageHandler CMGInternalMessageHandler::ms_Instance;

void CMGInternalMessageHandler::OnAccepted(ISocketAcceptor* pSocketAcceptor, ISocketSession* pSocketSession)
{
	CRI("accepted new session");

	if (pSocketSession)
		pSocketSession->Close();

	return;
}

void CMGInternalMessageHandler::OnConnected(ISocketSession* pSocketSession)
{
	INT32 nRetCode = 0;
	BASE_SESSION* pBaseSession = NULL;
	CMGSessionMgr& rSessionMgr = CMGSessionMgr::GetInstance();

	LOG_PROCESS_ERROR(pSocketSession);

	pBaseSession = (BASE_SESSION*)pSocketSession->GetUserData();
	LOG_PROCESS_ERROR(pBaseSession);

	pBaseSession->qwTimer = GetTickCountEx() + g_ServerConfig.Common.nServerPingTimeout;

	switch (pBaseSession->byType)
	{
	case stGD:
	{
		GD_SESSION* pGDSession = (GD_SESSION*)pBaseSession;
		pGDSession->bConnected = true;
		pGDSession->qwTimer = GetTickCountEx() + g_ServerConfig.Common.nRegisterGuardTimeout;
		INF("GD connected");

		if (CMGSessionMgr::GetInstance().GetServerState() == sgsSelfReady ||
			CMGSessionMgr::GetInstance().GetServerState() == sgsAllReady)
		{
			nRetCode = DoGDRegister();
			LOG_PROCESS_ERROR(nRetCode);
		}
	}
		break;
	case stLS:
	{
		LS_SESSION* pLSSession = (LS_SESSION*)pBaseSession;
		pLSSession->bConnected = true;
		INF("LS connected");

		nRetCode = DoLSRegister();
		LOG_PROCESS_ERROR(nRetCode);
	}
		break;
	case stMM:
	{
		MM_SESSION* pMMSession = (MM_SESSION*)pBaseSession;
		pMMSession->bConnected = true;
		INF("MM connected");

		nRetCode = DoMMRegister();
		LOG_PROCESS_ERROR(nRetCode);
	}
		break;
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

void CMGInternalMessageHandler::OnRecv(ISocketSession* pSocketSession, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize)
{
	MESSAGE_HEADER* pHeader = (MESSAGE_HEADER*)pPacketBuffer;
	LOG_PROCESS_ERROR(pHeader);

	g_ChangeStatisInfo(statInternalNetflowIncome, (INT32)dwSize);
	g_ChangeStatisInfo(statInternalPacketIncome, 1);

	if (pHeader->wMsg >= InternalMessage::max_message_count)
	{
		CRI("msg ID %d beyond InternalMessage::max_message_count!");
		LOG_PROCESS_ERROR(FALSE);
	}
	LOG_PROCESS_ERROR(m_MessageFuncList[pHeader->wMsg]);

	LOG_PROCESS_ERROR(pSocketSession);
	LOG_PROCESS_ERROR(pPacketBuffer);

	(this->*m_MessageFuncList[pHeader->wMsg])(pSocketSession, pPacketBuffer, dwSize);

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

void CMGInternalMessageHandler::OnDisconnected(ISocketSession* pSocketSession, BOOL bRemoteShutdown)
{
	INT32 nRetCode = 0;
	BASE_SESSION* pBaseSession = (BASE_SESSION*)pSocketSession->GetUserData();
	PROCESS_ERROR(pBaseSession);

	LOG_PROCESS_ERROR(pSocketSession);
	LOG_PROCESS_ERROR(pSocketSession == pBaseSession->pSocketSession);  // 必须检查  
	pBaseSession->pSocketSession = NULL;

	switch (pBaseSession->byType)
	{
	case stGD:
	{
		GD_SESSION* pGDSession = (GD_SESSION*)pBaseSession;
		pGDSession->qwTimer = GetTickCountEx() + g_ServerConfig.Common.nReconnectTime;
		pGDSession->bConnected = false;
		CRI("GD disconnected");

		break;
	}
	case stLS:
	{
		if (CMGSessionMgr::GetInstance().GetServerState() != sgsInitializing)
		{
			LS_SESSION* pLSSession = (LS_SESSION*)pBaseSession;
			pLSSession->bConnected = false;
			pLSSession->qwTimer = GetTickCountEx() + g_ServerConfig.Common.nReconnectTime;
		}

		CRI("LS disconnected");

		break;
	}
	case stMM:
	{
		MM_SESSION* pMMSession = (MM_SESSION*)pBaseSession;
		pMMSession->bConnected = false;
		pMMSession->qwTimer = GetTickCountEx() + g_ServerConfig.Common.nReconnectTime;

		if (CMGSessionMgr::GetInstance().GetServerState() != sgsInitializing)
		{
			pMMSession->qwTimer = 0xFFFFFFFF;

			CRI("MM disconnected");

			CMGSessionMgr::GetInstance().SetServerState(sgsClosing);
		}
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

CMGInternalMessageHandler::CMGInternalMessageHandler()
{
	m_pNet = NULL;
	m_pPacketAllocator = NULL;
	memset(m_MessageFuncList, 0, sizeof(m_MessageFuncList));
}

CMGInternalMessageHandler::~CMGInternalMessageHandler()
{
	UnInit();
}

BOOL CMGInternalMessageHandler::Init(INet* pNet, IPacketAllocator* pPacketAllocator)
{
	LOG_PROCESS_ERROR(pNet);

	m_pNet = pNet;
	m_pPacketAllocator = pPacketAllocator;

	// All
	m_MessageFuncList[a2a_ping] = &CMGInternalMessageHandler::OnAllPing;
	m_MessageFuncList[m2a_server_info] = &CMGInternalMessageHandler::OnMMServerInfo;
	m_MessageFuncList[m2a_all_ready] = &CMGInternalMessageHandler::OnMMAllReady;
	m_MessageFuncList[m2a_close] = &CMGInternalMessageHandler::OnMMClose;

	// MM
	m_MessageFuncList[mm2mg_register_ack] = &CMGInternalMessageHandler::OnMMRegisterAck;
	m_MessageFuncList[mm2mg_server_info] = &CMGInternalMessageHandler::OnMMServerInfo;
	m_MessageFuncList[mm2mg_all_ready] = &CMGInternalMessageHandler::OnMMAllReady;

	// LS
	m_MessageFuncList[l2mg_register_ack] = &CMGInternalMessageHandler::OnLSRegisterAck;
	m_MessageFuncList[l2mg_login_ack] = &CMGInternalMessageHandler::OnLSLoginAck;

	return TRUE;
Exit0:
	return FALSE;
}

BOOL CMGInternalMessageHandler::UnInit(void)
{

	return TRUE;
}

CMGInternalMessageHandler& CMGInternalMessageHandler::GetInstance(void)
{
	return ms_Instance;
}

inline BOOL CMGInternalMessageHandler::_SendMM(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, INT32 nOffset)
{
	INT32 nRetCode = 0;

	MM_SESSION& rMMSession = CMGSessionMgr::GetInstance().GetMMSession();
	LOG_PROCESS_ERROR(rMMSession.bConnected);
	LOG_PROCESS_ERROR(rMMSession.pSocketSession);

	nRetCode = rMMSession.pSocketSession->Send((PACKET_BUFFER*)pPacketBuffer, dwSize, nOffset);
	LOG_PROCESS_ERROR(nRetCode == dwSize);

	g_ChangeStatisInfo(statInternalNetflowOutgoing, (INT32)dwSize);
	g_ChangeStatisInfo(statInternalPacketOutgoing, 1);

	return TRUE;
Exit0:
	return FALSE;
}

inline BOOL CMGInternalMessageHandler::_SendLS(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, INT32 nOffset)
{
	INT32 nRetCode = 0;

	LS_SESSION& rLSSession = CMGSessionMgr::GetInstance().GetLSSession();
	LOG_PROCESS_ERROR(rLSSession.bConnected);
	LOG_PROCESS_ERROR(rLSSession.pSocketSession);

	nRetCode = rLSSession.pSocketSession->Send((PACKET_BUFFER*)pPacketBuffer, dwSize, nOffset);
	LOG_PROCESS_ERROR(nRetCode == dwSize);

	g_ChangeStatisInfo(statInternalNetflowOutgoing, (INT32)dwSize);
	g_ChangeStatisInfo(statInternalPacketOutgoing, 1);

	return TRUE;
Exit0:
	return FALSE;
}

inline BOOL CMGInternalMessageHandler::_SendGD(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, INT32 nOffset)
{
	INT32 nRetCode = 0;

	GD_SESSION& rGDSession = CMGSessionMgr::GetInstance().GetGDSession();
	LOG_PROCESS_ERROR(rGDSession.bConnected);
	LOG_PROCESS_ERROR(rGDSession.pSocketSession);

	nRetCode = rGDSession.pSocketSession->Send((PACKET_BUFFER*)pPacketBuffer, dwSize, nOffset);
	LOG_PROCESS_ERROR(nRetCode == dwSize);

	g_ChangeStatisInfo(statInternalNetflowOutgoing, (INT32)dwSize);
	g_ChangeStatisInfo(statInternalPacketOutgoing, 1);

	return TRUE;
Exit0:
	return FALSE;

}

inline void CMGInternalMessageHandler::_CheckReady(void)
{
	INT32 nRetCode = 0;
	CMGSessionMgr& rSessionMgr = CMGSessionMgr::GetInstance();

	if (rSessionMgr.GetLSSession().bConnected &&
		rSessionMgr.GetServerState() == sgsInitializing)
	{
		nRetCode = DoMMReady();
		LOG_CHECK_ERROR(nRetCode);

		if (rSessionMgr.GetGDSession().bConnected)
		{
			nRetCode = DoGDRegister();
			LOG_CHECK_ERROR(nRetCode);
		}
	}
}

/************************************************************************/
// To All
BOOL CMGInternalMessageHandler::DoAllPing(void)
{
	INT32 nRetCode = 0;
	A2A_PING* pMsg = NULL;

	if (CMGSessionMgr::GetInstance().GetGDSession().bConnected)
	{
		pMsg = (A2A_PING*)m_pPacketAllocator->Alloc(sizeof(A2A_PING));
		LOG_PROCESS_ERROR(pMsg);

		pMsg->wMsg = a2a_ping;

		nRetCode = _SendGD((PACKET_BUFFER*)pMsg, sizeof(A2A_PING));
		LOG_CHECK_ERROR(nRetCode);

		if (!nRetCode)
			m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
		pMsg = NULL;
	}

	if (CMGSessionMgr::GetInstance().GetMMSession().bConnected)
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

	if (CMGSessionMgr::GetInstance().GetLSSession().bConnected)
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

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

/************************************************************************/
// To GD

BOOL CMGInternalMessageHandler::DoGDRegister(void)
{
	INT32 nRetCode = 0;

	A2U_REGRISTER* pMsg = (A2U_REGRISTER*)m_pPacketAllocator->Alloc(sizeof(A2U_REGRISTER));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = a2u_regrister;
	pMsg->byType = stMG;
	pMsg->bySessionID = (UINT8)CMGSessionMgr::GetInstance().GetSelfSessionID();
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
// To MM

BOOL CMGInternalMessageHandler::DoMMRegister()
{
	INT32 nRetCode = 0;

	MG2MM_REGISTER* pMsg = (MG2MM_REGISTER*)m_pPacketAllocator->Alloc(sizeof(MG2MM_REGISTER));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = mg2mm_register;
	pMsg->byExternalCount = (UINT8)CMGateServer::GetInstance().GetExternalAddrCount();
	for (INT32 nIndex = 0; nIndex < pMsg->byExternalCount; nIndex++)
	{
		pMsg->dwExternalAddr[nIndex] = CMGateServer::GetInstance().GetExternalAddr(nIndex);
		pMsg->wExternalPort[nIndex] = (UINT16)CMGateServer::GetInstance().GetExternalPort(nIndex);
	}

	nRetCode = _SendMM((PACKET_BUFFER*)pMsg, sizeof(*pMsg));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CMGInternalMessageHandler::DoMMReady(void)
{
	INT32 nRetCode = 0;

	MG2MM_READY* pMsg = (MG2MM_READY*)m_pPacketAllocator->Alloc(sizeof(MG2MM_READY));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = mg2mm_ready;

	nRetCode = _SendMM((PACKET_BUFFER*)pMsg, sizeof(*pMsg));
	LOG_PROCESS_ERROR(nRetCode);

	CMGSessionMgr::GetInstance().SetServerState(sgsSelfReady);

	INF("MG %d is self ready", CMGSessionMgr::GetInstance().GetSelfSessionID());

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CMGInternalMessageHandler::DoMMCloseAck(void)
{
	INT32 nRetCode = 0;

	MG2MM_CLOSE_ACK* pMsg = (MG2MM_CLOSE_ACK*)m_pPacketAllocator->Alloc(sizeof(MG2MM_CLOSE_ACK));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = mg2mm_close_ack;

	nRetCode = _SendMM((PACKET_BUFFER*)pMsg, sizeof(*pMsg));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

/************************************************************************/
// To LS

BOOL CMGInternalMessageHandler::DoLSRegister(void)
{
	INT32 nRetCode = 0;

	MG2L_REGISTER* pMsg = (MG2L_REGISTER*)m_pPacketAllocator->Alloc(sizeof(MG2L_REGISTER));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = mg2l_register;
	pMsg->dwMGSessionID = CMGSessionMgr::GetInstance().GetSelfSessionID();

	nRetCode = _SendLS((PACKET_BUFFER*)pMsg, sizeof(MG2L_REGISTER));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CMGInternalMessageHandler::DoLSLoginReq(UINT32 dwSessionID, CHAR szUserName[], CHAR szOASessionID[])
{
	INT32 nRetCode = 0;

	MG2L_LOGIN_REQ* pMsg = (MG2L_LOGIN_REQ*)m_pPacketAllocator->Alloc(sizeof(MG2L_LOGIN_REQ));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = mg2l_login_req;
	pMsg->dwClientSessionID = dwSessionID;
	strxcpy(pMsg->szUserName, szUserName, USER_NAME_LEN);
	strxcpy(pMsg->szOASessionID, szOASessionID, OA_SESSION_ID_LEN);

	nRetCode = _SendLS((PACKET_BUFFER*)pMsg, sizeof(MG2L_LOGIN_REQ));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

/************************************************************************/
// From All
void CMGInternalMessageHandler::OnAllPing(ISocketSession* pSocketSession, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize)
{
	BASE_SESSION* pBaseSession = (BASE_SESSION*)pSocketSession->GetUserData();
	LOG_PROCESS_ERROR(pBaseSession);

	if (pBaseSession->byType == stGD)
		pBaseSession->qwTimer = GetTickCountEx() + g_ServerConfig.Common.nPingGuardTimeout;
	else
		pBaseSession->qwTimer = GetTickCountEx() + g_ServerConfig.Common.nServerPingTimeout;

	m_pPacketAllocator->Free(pPacketBuffer);

	return;
Exit0:
	m_pPacketAllocator->Free(pPacketBuffer);
	if (pSocketSession)
		pSocketSession->Close();
	return;
}

/************************************************************************/
// From MM
void CMGInternalMessageHandler::OnMMRegisterAck(ISocketSession* pSocketSession, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize)
{
	INT32 nRetCode = 0;
	MM2MG_REGISTER_ACK* pMsg = (MM2MG_REGISTER_ACK*)pPacketBuffer;

	CMGSessionMgr::GetInstance().SetSelfSessionID(pMsg->dwMGSessionID);

	INF("MG %d registered to MM", pMsg->dwMGSessionID);

#if defined(WIN32)
	{
		char szTitle[1024];
#ifdef _FINAL
		snprintf(szTitle, 1024, "Mobile Gate Server %d, ver %d.%d.%d final, msg ver %08X", pMsg->dwMGSessionID, MAJOR_VERSION, MINOR_VERSION, BUILD_NUMBER, g_nMessageVersion);
#else
		snprintf(szTitle, 1024, "Mobile Gate Server %d, ver %d.%d.%d, msg ver %08X", pMsg->dwMGSessionID, MAJOR_VERSION, MINOR_VERSION, BUILD_NUMBER, g_nMessageVersion);
#endif	// _FINAL
		SetConsoleTitle(szTitle);
		INF(szTitle);
	}
#endif  // WIN32
}

void CMGInternalMessageHandler::OnMMServerInfo(ISocketSession* pSocketSession, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize)
{
	INT32 nRetCode = 0;
	MM2MG_SERVER_INFO* pMsg = (MM2MG_SERVER_INFO*)pPacketBuffer;

	CMGSessionMgr::GetInstance().GetLSSession().dwAddr = pMsg->dwLSAddr;
	CMGSessionMgr::GetInstance().GetLSSession().wPort = pMsg->wLSPort;

	m_pPacketAllocator->Free(pPacketBuffer);
}

void CMGInternalMessageHandler::OnMMAllReady(ISocketSession* pSocketSession, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize)
{
	INT32 nRetCode = 0;

	CMGSessionMgr::GetInstance().SetServerState(sgsAllReady);
	INF("all servers are ready");
}

void CMGInternalMessageHandler::OnMMClose(ISocketSession* pSocketSession, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize)
{
	CMGSessionMgr::GetInstance().SetServerState(sgsClosing);
	INF("MG %d is closing", CMGSessionMgr::GetInstance().GetSelfSessionID());
	m_pPacketAllocator->Free(pPacketBuffer);
}

/************************************************************************/
// From LS

void CMGInternalMessageHandler::OnLSRegisterAck(ISocketSession* pSocketSession, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize)
{
	CMGSessionMgr::GetInstance().GetLSSession().bConnected = true;

	INF("MG %d registered to LS", CMGSessionMgr::GetInstance().GetSelfSessionID());

	_CheckReady();

	m_pPacketAllocator->Free(pPacketBuffer);
}

void CMGInternalMessageHandler::OnLSLoginAck(ISocketSession* pSocketSession, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize)
{
	INT32 nResult = errLoginUnknownError;
	INT32 nRetCode = 0;
	L2MG_LOGIN_ACK* pMsg = (L2MG_LOGIN_ACK*)pPacketBuffer;
	MG_CLIENT_SESSION* pSession = NULL;

	m_pPacketAllocator->Free(pPacketBuffer);
	MG_SYS_LOG_SUCCESS(pSession);
	return;
Exit0:
	MG_SYS_LOG_ERROR(pSession);
	m_pPacketAllocator->Free(pPacketBuffer);

	if (pSession && pSession->pSocketSession)
	{
		nRetCode = pSession->pSocketSession->Close();
		LOG_CHECK_ERROR(nRetCode);
	}

	return;
}
