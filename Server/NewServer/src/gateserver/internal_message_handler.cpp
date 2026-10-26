#include "stdafx.h"
#include "internal_message_handler.h"

#include "time_ex.h"
#include "report.h"
#include "process_option.h"
#include "server_config.h"
#include "version.h"
#include "statis_info.h"

#include "t2m_message.h"
#include "m2t_message.h"
#include "t2l_message.h"
#include "l2t_message.h"
#include "t2d_message.h"
#include "d2t_message.h"
#include "t2g_message.h"
#include "g2t_message.h"
#include "ns_message.h"
#include "common_message.h"
#include "external_message_size.h"
#include "role_db_def.h"

#include "gateserver.h"
#include "gt_session_mgr.h"
#include "external_message_handler.h"

#define IN_QUEUE_TIMEOUT	(4 * 60 * 60 * 1000)

using namespace InternalMessage;
CInternalMessageHandler CInternalMessageHandler::ms_Instance;

void CInternalMessageHandler::OnAccepted(ISocketAcceptor* pSocketAcceptor, ISocketSession* pSocketSession)
{
	LOG_PROCESS_ERROR(pSocketSession);
	LOG_PROCESS_ERROR(CGTSessionMgr::GetInstance().GetServerState() != sgsClosing);

	INF("accepted new gs session");

	return;
Exit0:
	if (pSocketSession)
		pSocketSession->Close();

	return;
}

void CInternalMessageHandler::OnConnected(ISocketSession* pSocketSession)
{
	INT32 nRetCode = 0;
	BASE_SESSION* pBaseSession = NULL;
	CGTSessionMgr& rSessionMgr = CGTSessionMgr::GetInstance();

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

		if (CGTSessionMgr::GetInstance().GetServerState() == sgsSelfReady ||
			CGTSessionMgr::GetInstance().GetServerState() == sgsAllReady)
		{
			if (CGTSessionMgr::GetInstance().GetSelfSessionID() > 0 &&
				rSessionMgr.GetGDSession().bConnected)
			{
				nRetCode = DoGDRegister();
				LOG_PROCESS_ERROR(nRetCode);
			}
		}
	}
		break;
	case stDB:
	{
		DB_SESSION* pDBSession = (DB_SESSION*)pBaseSession;
		pDBSession->bConnected = true;
		INF("DB connected");

		nRetCode = DoDBRegister();
		LOG_PROCESS_ERROR(nRetCode);
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
	case stMS:
	{
		MS_SESSION* pMSSession = (MS_SESSION*)pBaseSession;
		pMSSession->bConnected = true;
		INF("MS connected");

		nRetCode = DoMSRegister();
		LOG_PROCESS_ERROR(nRetCode);
	}
		break;
	case stBS:
	case stGS:
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

void CInternalMessageHandler::OnRecv(ISocketSession* pSocketSession, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize)
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

void CInternalMessageHandler::OnDisconnected(ISocketSession* pSocketSession, BOOL bRemoteShutdown)
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
	}
		break;
	case stDB:
	{
		DB_SESSION* pDBSession = (DB_SESSION*)pBaseSession;
		pDBSession->bConnected = false;
		pDBSession->qwTimer = GetTickCountEx() + g_ServerConfig.Common.nReconnectTime;

		if (CGTSessionMgr::GetInstance().GetServerState() != sgsInitializing)
		{
			pDBSession->qwTimer = 0xFFFFFFFF;

			CRI("DB disconnected");

			CGTSessionMgr::GetInstance().SetServerState(sgsClosing);
		}
	}
		break;
	case stLS:
	{
		if (CGTSessionMgr::GetInstance().GetServerState() != sgsInitializing)
		{
			LS_SESSION* pLSSession = (LS_SESSION*)pBaseSession;
			pLSSession->bConnected = false;
			pLSSession->qwTimer = GetTickCountEx() + g_ServerConfig.Common.nReconnectTime;

			CRI("LS disconnected");
		}
	}
		break;

	case stMS:
	{
		MS_SESSION* pMSSession = (MS_SESSION*)pBaseSession;
		pMSSession->bConnected = false;
		pMSSession->qwTimer = GetTickCountEx() + g_ServerConfig.Common.nReconnectTime;

		if (CGTSessionMgr::GetInstance().GetServerState() != sgsInitializing)
		{
			pMSSession->qwTimer = 0xFFFFFFFF;

			CRI("MS disconnected");

			CGTSessionMgr::GetInstance().SetServerState(sgsClosing);
		}
	}
		break;
	case stGS:
	{
		GS_SESSION* pGSSession = (GS_SESSION*)pBaseSession;
		pGSSession->qwTimer = GetTickCountEx() + g_ServerConfig.Common.nReconnectTime;

		if (CGTSessionMgr::GetInstance().GetServerState() != sgsInitializing)
		{
			pGSSession->qwTimer = 0xFFFFFFFF;

			CRI("GS %d disconnected", pGSSession->dwSessionID);
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

CInternalMessageHandler::CInternalMessageHandler()
{
	m_pNet = NULL;
	m_pPacketAllocator = NULL;
	memset(m_MessageFuncList, 0, sizeof(m_MessageFuncList));
}

CInternalMessageHandler::~CInternalMessageHandler()
{
	UnInit();
}

BOOL CInternalMessageHandler::Init(INet* pNet, IPacketAllocator* pPacketAllocator)
{
	LOG_PROCESS_ERROR(pNet);

	m_pNet = pNet;
	m_pPacketAllocator = pPacketAllocator;

	// All
	m_MessageFuncList[a2a_ping] = &CInternalMessageHandler::OnAllPing;

	// MS
	m_MessageFuncList[m2t_register_ack] = &CInternalMessageHandler::OnMSRegisterAck;
	m_MessageFuncList[m2a_server_info] = &CInternalMessageHandler::OnMSServerInfo;
	m_MessageFuncList[m2a_all_ready] = &CInternalMessageHandler::OnMSAllReady;
	m_MessageFuncList[m2a_close] = &CInternalMessageHandler::OnMSClose;

	m_MessageFuncList[m2t_enter_gate_ack] = &CInternalMessageHandler::OnMSEnterGateAck;
	m_MessageFuncList[m2t_query_scene_ack] = &CInternalMessageHandler::OnMSQuerySceneAck;
	m_MessageFuncList[m2t_close_client_session] = &CInternalMessageHandler::OnMSCloseClientSession;
	m_MessageFuncList[m2t_return_select_role] = &CInternalMessageHandler::OnMSReturnSelectRole;
	m_MessageFuncList[m2t_change_gs] = &CInternalMessageHandler::OnMSChangeGS;
	m_MessageFuncList[m2t_client_msg] = &CInternalMessageHandler::OnMSClientMsg;
	m_MessageFuncList[m2t_broadcast_client_msg] = &CInternalMessageHandler::OnMSBroadcastClientMsg;
	m_MessageFuncList[m2t_switch_server_group_state] = &CInternalMessageHandler::OnMSSwitchServerState;
	m_MessageFuncList[m2t_gm_command] = &CInternalMessageHandler::OnMSGMCommand;
	m_MessageFuncList[m2t_check_new_name] = &CInternalMessageHandler::OnMSCheckNewName;

	// GS
	m_MessageFuncList[g2t_register] = &CInternalMessageHandler::OnGSRegister;
	m_MessageFuncList[g2t_close_client_session] = &CInternalMessageHandler::OnGSCloseClientSession;
	m_MessageFuncList[g2t_client_msg] = &CInternalMessageHandler::OnGSClientMsg;
	m_MessageFuncList[g2t_broadcast_client_msg] = &CInternalMessageHandler::OnGSBroadcastClientMsg;
	m_MessageFuncList[g2t_return_role_select] = &CInternalMessageHandler::OnGSReturnSelectRole;

	// LS
	m_MessageFuncList[l2t_register_ack] = &CInternalMessageHandler::OnLSRegisterAck;
	m_MessageFuncList[l2t_login_ack] = &CInternalMessageHandler::OnLSLoginAck;

	// DB
	m_MessageFuncList[d2t_register_ack] = &CInternalMessageHandler::OnDBRegisterAck;
	m_MessageFuncList[d2t_sync_role_list] = &CInternalMessageHandler::OnDBSyncRoleList;
	m_MessageFuncList[d2t_create_role_ack] = &CInternalMessageHandler::OnDBCreateRoleAck;
	m_MessageFuncList[d2t_delete_role_ack] = &CInternalMessageHandler::OnDBDeleteRoleAck;
	m_MessageFuncList[d2t_undelete_role_ack] = &CInternalMessageHandler::OnDBUnDeleteRoleAck;
    m_MessageFuncList[d2t_forever_delete_role_ack] = &CInternalMessageHandler::OnDBForeverDeleteRoleAck;
	m_MessageFuncList[d2t_close_client_session] = &CInternalMessageHandler::OnDBCloseClientSession;

	// NS
//	m_MessageFuncList[n2x_new_name_result] = &CInternalMessageHandler::OnNSNewNameResult;

	return TRUE;
Exit0:
	return FALSE;
}

BOOL CInternalMessageHandler::UnInit(void)
{

	return TRUE;
}

CInternalMessageHandler& CInternalMessageHandler::GetInstance(void)
{
	return ms_Instance;
}

inline BOOL CInternalMessageHandler::_SendMS(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, INT32 nOffset)
{
	INT32 nRetCode = 0;

	MS_SESSION& rMSSession = CGTSessionMgr::GetInstance().GetMSSession();
	LOG_PROCESS_ERROR(rMSSession.bConnected);
	LOG_PROCESS_ERROR(rMSSession.pSocketSession);

	nRetCode = rMSSession.pSocketSession->Send((PACKET_BUFFER*)pPacketBuffer, dwSize, nOffset);
	LOG_PROCESS_ERROR(nRetCode == dwSize);

	g_ChangeStatisInfo(statInternalNetflowOutgoing, (INT32)dwSize);
	g_ChangeStatisInfo(statInternalPacketOutgoing, 1);

	return TRUE;
Exit0:
	return FALSE;
}

inline BOOL CInternalMessageHandler::_SendGS(UINT32 dwGSSessionID, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, INT32 nOffset)
{
	INT32 nRetCode = 0;

	GS_SESSION* pGSSession = CGTSessionMgr::GetInstance().GetGSSession(dwGSSessionID);
	LOG_PROCESS_ERROR(pGSSession);
	LOG_PROCESS_ERROR(pGSSession->pSocketSession);

	nRetCode = pGSSession->pSocketSession->Send((PACKET_BUFFER*)pPacketBuffer, dwSize, nOffset);
	LOG_PROCESS_ERROR(nRetCode == dwSize);

	g_ChangeStatisInfo(statInternalNetflowOutgoing, (INT32)dwSize);
	g_ChangeStatisInfo(statInternalPacketOutgoing, 1);

	return TRUE;
Exit0:
	return FALSE;
}

inline BOOL CInternalMessageHandler::_SendLS(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, INT32 nOffset)
{
	INT32 nRetCode = 0;

	LS_SESSION& rLSSession = CGTSessionMgr::GetInstance().GetLSSession();
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

inline BOOL CInternalMessageHandler::_SendDB(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, INT32 nOffset)
{
	INT32 nRetCode = 0;

	DB_SESSION& rDBSession = CGTSessionMgr::GetInstance().GetDBSession();
	LOG_PROCESS_ERROR(rDBSession.bConnected);
	LOG_PROCESS_ERROR(rDBSession.pSocketSession);

	nRetCode = rDBSession.pSocketSession->Send((PACKET_BUFFER*)pPacketBuffer, dwSize, nOffset);
	LOG_PROCESS_ERROR(nRetCode == dwSize);

	g_ChangeStatisInfo(statInternalNetflowOutgoing, (INT32)dwSize);
	g_ChangeStatisInfo(statInternalPacketOutgoing, 1);

	return TRUE;
Exit0:
	return FALSE;
}

inline BOOL CInternalMessageHandler::_SendGD(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, INT32 nOffset)
{
	INT32 nRetCode = 0;

	GD_SESSION& rGDSession = CGTSessionMgr::GetInstance().GetGDSession();
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

inline void CInternalMessageHandler::_CheckReady(void)
{
	INT32 nRetCode = 0;
	CGTSessionMgr& rSessionMgr = CGTSessionMgr::GetInstance();

	if (rSessionMgr.GetDBSession().bConnected &&
		rSessionMgr.GetLSSession().bConnected &&
		rSessionMgr.GetServerState() == sgsInitializing)	//注意: 如果 ms配置的 gt数量小于guard启动的gt数量,可能ms已经发送过 allready,gt这里状态已经变成allready
	{
		nRetCode = DoMSReady();
		LOG_CHECK_ERROR(nRetCode);
	}

	if (rSessionMgr.GetDBSession().bConnected &&
		rSessionMgr.GetLSSession().bConnected &&
		CGTSessionMgr::GetInstance().GetSelfSessionID() > 0 &&
		rSessionMgr.GetGDSession().bConnected)
	{
		nRetCode = DoGDRegister();
		LOG_CHECK_ERROR(nRetCode);
	}
}

/************************************************************************/
// To All
BOOL CInternalMessageHandler::DoAllPing(void)
{
	INT32 nRetCode = 0;
	A2A_PING* pMsg = NULL;

	if (CGTSessionMgr::GetInstance().GetGDSession().bConnected)
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

	if (CGTSessionMgr::GetInstance().GetMSSession().bConnected)
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

	if (CGTSessionMgr::GetInstance().GetLSSession().bConnected)
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

	if (CGTSessionMgr::GetInstance().GetDBSession().bConnected)
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

	for (INT32 nIndex = 1; nIndex < MAX_GS_SESSION_COUNT; nIndex++)
	{
		GS_SESSION* pGSSession = CGTSessionMgr::GetInstance().GetGSSession(nIndex);
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

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

/************************************************************************/
// To GD

BOOL CInternalMessageHandler::DoGDRegister(void)
{
	INT32 nRetCode = 0;

	A2U_REGRISTER* pMsg = (A2U_REGRISTER*)m_pPacketAllocator->Alloc(sizeof(A2U_REGRISTER));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = a2u_regrister;
	pMsg->byType = stGT;
	pMsg->bySessionID = (UINT8)CGTSessionMgr::GetInstance().GetSelfSessionID();
	pMsg->dwProcessID = GetCurrentProcessId();

	nRetCode = _SendGD((PACKET_BUFFER*)pMsg, sizeof(A2U_REGRISTER));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CInternalMessageHandler::DoGDNotify(UINT8 byLevel, const char* szContent, ...)
{
	INT32 nRetCode = 0;
	char szInfo[4096] = { 0 };
	va_list valist;
	va_start(valist, szContent);
	vsnprintf(szInfo, sizeof(szInfo), szContent, valist);
	va_end(valist);

	INT32 nSize = sizeof(A2U_NOTIFY) + strlen(szInfo) + 1;

	A2U_NOTIFY* pMsg = (A2U_NOTIFY*)m_pPacketAllocator->Alloc(nSize);
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = a2u_notify;
	pMsg->bySvrType = stGT;
	pMsg->bySvrID = (UINT8)CGTSessionMgr::GetInstance().GetSelfSessionID();
	pMsg->byLevel = byLevel;
	pMsg->nErrorCode = errCritical;
	strxcpy(pMsg->szContent, szInfo, strlen(szInfo) + 1);

	nRetCode = _SendGD((PACKET_BUFFER*)pMsg, nSize);
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;

}

/************************************************************************/
// To MS

BOOL CInternalMessageHandler::DoMSRegister()
{
	INT32 nRetCode = 0;

	T2M_REGISTER* pMsg = (T2M_REGISTER*)m_pPacketAllocator->Alloc(sizeof(T2M_REGISTER));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = t2m_register;
	pMsg->dwInternalAddr = CGateServer::GetInstance().GetInternalAddr();
	pMsg->wInternalPort = (UINT16)CGateServer::GetInstance().GetInternalPort();
	pMsg->byExternalCount = (UINT8)CGateServer::GetInstance().GetExternalAddrCount();
	for (INT32 nIndex = 0; nIndex < pMsg->byExternalCount; nIndex++)
	{
		pMsg->dwExternalAddr[nIndex] = CGateServer::GetInstance().GetExternalAddr(nIndex);
		pMsg->wExternalPort[nIndex] = (UINT16)CGateServer::GetInstance().GetExternalPort(nIndex);
	}

	nRetCode = _SendMS((PACKET_BUFFER*)pMsg, sizeof(*pMsg));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CInternalMessageHandler::DoMSReady(void)
{
	INT32 nRetCode = 0;

	T2M_READY* pMsg = (T2M_READY*)m_pPacketAllocator->Alloc(sizeof(T2M_READY));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = t2m_ready;

	nRetCode = _SendMS((PACKET_BUFFER*)pMsg, sizeof(*pMsg));
	LOG_PROCESS_ERROR(nRetCode);

	CGTSessionMgr::GetInstance().SetServerState(sgsSelfReady);

	INF("GT %d is self ready", CGTSessionMgr::GetInstance().GetSelfSessionID());

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CInternalMessageHandler::DoMSCloseAck(void)
{
	INT32 nRetCode = 0;

	T2M_CLOSE_ACK* pMsg = (T2M_CLOSE_ACK*)m_pPacketAllocator->Alloc(sizeof(T2M_CLOSE_ACK));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = t2m_close_ack;

	nRetCode = _SendMS((PACKET_BUFFER*)pMsg, sizeof(*pMsg));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CInternalMessageHandler::DoMSEnterGate(UINT32 dwClientSessionID)
{
	INT32 nRetCode = 0;
	CLIENT_SESSION* pSession = NULL;

	T2M_ENTER_GATE* pMsg = (T2M_ENTER_GATE*)m_pPacketAllocator->Alloc(sizeof(T2M_ENTER_GATE));
	LOG_PROCESS_ERROR(pMsg);

	pSession = CGTSessionMgr::GetInstance().FindClientSession(dwClientSessionID);
	LOG_PROCESS_ERROR(pSession);

	pMsg->wMsg = t2m_enter_gate;
	pMsg->dwClientSessionID = dwClientSessionID;
	pMsg->dwIpAddr = pSession->dwClientIp;
	strxcpy(pMsg->szMac, pSession->szMac, MAC_ADDRESS_LEN);
	strxcpy(pMsg->szOASessionID, pSession->szOASessionID, OA_SESSION_ID_LEN);
	strxcpy(pMsg->szUserName, pSession->szUserName, USER_NAME_LEN);
	strxcpy(pMsg->szPGT, pSession->szPGT, OA_PGT_FIELD_LEN);
	pMsg->bAdult = pSession->bAdult;
	pMsg->bIpWhiteList = pSession->bIpWhiteList;
	pMsg->bUserWhiteList = pSession->bUserWhiteList;

	nRetCode = _SendMS((PACKET_BUFFER*)pMsg, sizeof(*pMsg));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CInternalMessageHandler::DoMSQueryScene(UINT32 dwSessionID, UINT32 dwRoleID)
{
	INT32 nRetCode = 0;
	INT32 nIndex = 0;
	CLIENT_SESSION* pSession = NULL;

	T2M_QUERY_SCENE* pMsg = (T2M_QUERY_SCENE*)m_pPacketAllocator->Alloc(sizeof(T2M_QUERY_SCENE));
	LOG_PROCESS_ERROR(pMsg);

	pSession = CGTSessionMgr::GetInstance().FindClientSession(dwSessionID);
	LOG_PROCESS_ERROR(pSession);

	for (; nIndex < pSession->byRoleCount; nIndex++)
	{
		if (pSession->RoleList[nIndex].dwRoleID == dwRoleID)
			break;
	}
	// 没找到是外挂，或者客户端有BUG
	LOG_PROCESS_ERROR(nIndex < pSession->byRoleCount);

	pMsg->wMsg = t2m_query_scene;
	pMsg->dwClientSessionID = dwSessionID;
	pMsg->dwRoleID = dwRoleID;
	pMsg->dwSaveTime = pSession->RoleList[nIndex].dwSaveTime;

	pMsg->nSceneTempID = pSession->RoleList[nIndex].nSceneTemplateID;
	pMsg->nSceneID = pSession->RoleList[nIndex].nSceneID;
	pMsg->nX = pSession->RoleList[nIndex].nX;
	pMsg->nY = pSession->RoleList[nIndex].nY;
	pMsg->nZ = pSession->RoleList[nIndex].nZ;
	pMsg->wFaceDirection = pSession->RoleList[nIndex].wFaceDirection;

	pMsg->nReturnSceneTempID = pSession->RoleList[nIndex].nReturnSceneTemplateID;
	pMsg->nReturnSceneID = pSession->RoleList[nIndex].nReturnSceneID;
	pMsg->nReturnX = pSession->RoleList[nIndex].nReturnX;
	pMsg->nReturnY = pSession->RoleList[nIndex].nReturnY;
	pMsg->nReturnZ = pSession->RoleList[nIndex].nReturnZ;
	pMsg->wReturnFaceDirection = pSession->RoleList[nIndex].wReturnFaceDirection;

	nRetCode = _SendMS((PACKET_BUFFER*)pMsg, sizeof(*pMsg));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CInternalMessageHandler::DoMSClientMsg(UINT32 dwClientSessionID, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize)
{
	INT32 nRetCode = 0;

	T2M_CLIENT_MSG* pMsg = (T2M_CLIENT_MSG*)((char*)pPacketBuffer - sizeof(T2M_CLIENT_MSG));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = t2m_client_msg;
	pMsg->dwClientSessionID = dwClientSessionID;

	nRetCode = _SendMS(pPacketBuffer, dwSize + sizeof(T2M_CLIENT_MSG), -(INT32)sizeof(T2M_CLIENT_MSG));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	return FALSE;
}

BOOL CInternalMessageHandler::DoMSClientShutdown(UINT32 dwClientSessionID, UINT8 byClientShutDownType)
{
	INT32 nRetCode = 0;

	T2M_CLIENT_SHUTDOWN* pMsg = (T2M_CLIENT_SHUTDOWN*)m_pPacketAllocator->Alloc(sizeof(T2M_CLIENT_SHUTDOWN));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = t2m_client_shutdown;
	pMsg->dwClientSessionID = dwClientSessionID;
	pMsg->byShutDownType = byClientShutDownType;

	nRetCode = _SendMS((PACKET_BUFFER*)pMsg, sizeof(T2M_CLIENT_SHUTDOWN));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CInternalMessageHandler::DoMSReturnSelectRole(UINT32 dwClientSessionID)
{
	INT32 nRetCode = 0;

	T2M_RETURN_SELECT_ROLE* pMsg = (T2M_RETURN_SELECT_ROLE*)m_pPacketAllocator->Alloc(sizeof(T2M_RETURN_SELECT_ROLE));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = t2m_return_select_role;
	pMsg->dwClientSessionID = dwClientSessionID;

	nRetCode = _SendMS((PACKET_BUFFER*)pMsg, sizeof(T2M_RETURN_SELECT_ROLE));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CInternalMessageHandler::DoMSChangeGSAck(UINT32 dwClientSessionID)
{
	INT32 nRetCode = 0;

	T2M_CHANGE_GS_ACK* pMsg = (T2M_CHANGE_GS_ACK*)m_pPacketAllocator->Alloc(sizeof(T2M_CHANGE_GS_ACK));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = t2m_change_gs_ack;
	pMsg->dwClientSessionID = dwClientSessionID;

	nRetCode = _SendMS((PACKET_BUFFER*)pMsg, sizeof(T2M_CHANGE_GS_ACK));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

/************************************************************************/
// To GS

BOOL CInternalMessageHandler::DoGSRegisterAck(UINT32 dwGSSessionID)
{
	INT32 nRetCode = 0;

	T2G_REGISTER_ACK* pMsg = (T2G_REGISTER_ACK*)m_pPacketAllocator->Alloc(sizeof(T2G_REGISTER_ACK));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = t2g_register_ack;
	pMsg->dwGTSessionID = CGTSessionMgr::GetInstance().GetSelfSessionID();

	nRetCode = _SendGS(dwGSSessionID, (PACKET_BUFFER*)pMsg, sizeof(T2G_REGISTER_ACK));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CInternalMessageHandler::DoGSClientMsg(UINT32 dwGSSessionID, UINT32 dwSessionID, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize)
{
	INT32 nRetCode = 0;

	T2G_CLIENT_MSG* pMsg = (T2G_CLIENT_MSG*)((char*)pPacketBuffer - sizeof(T2G_CLIENT_MSG));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = t2g_client_msg;
	pMsg->dwSessionID = dwSessionID;

	nRetCode = _SendGS(dwGSSessionID, pPacketBuffer, dwSize + sizeof(T2G_CLIENT_MSG), -(INT32)sizeof(T2G_CLIENT_MSG));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:

	return FALSE;
}

BOOL CInternalMessageHandler::DoGSRoleEnter(UINT32 dwGSSessionID, UINT32 dwClientSessionID, UINT32 dwRoleID)
{
	INT32 nRetCode = 0;

	T2G_ROLE_ENTER* pMsg = (T2G_ROLE_ENTER*)m_pPacketAllocator->Alloc(sizeof(T2G_ROLE_ENTER));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = t2g_role_enter;
	pMsg->dwClientSessionID = dwClientSessionID;
	pMsg->dwRoleID = dwRoleID;

	nRetCode = _SendGS(dwGSSessionID, (PACKET_BUFFER*)pMsg, sizeof(T2G_ROLE_ENTER));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

/************************************************************************/
// To LS

BOOL CInternalMessageHandler::DoLSRegister(void)
{
	INT32 nRetCode = 0;

	T2L_REGISTER* pMsg = (T2L_REGISTER*)m_pPacketAllocator->Alloc(sizeof(T2L_REGISTER));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = t2l_register;
	pMsg->dwGTSessionID = CGTSessionMgr::GetInstance().GetSelfSessionID();

	nRetCode = _SendLS((PACKET_BUFFER*)pMsg, sizeof(T2L_REGISTER));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CInternalMessageHandler::DoLSLoginReq(UINT32 dwSessionID, CHAR szUserName[], CHAR szPassword[], CHAR szOASessionID[])
{
	INT32 nRetCode = 0;

	T2L_LOGIN_REQ* pMsg = (T2L_LOGIN_REQ*)m_pPacketAllocator->Alloc(sizeof(T2L_LOGIN_REQ));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = t2l_login_req;
	pMsg->dwClientSessionID = dwSessionID;
	strxcpy(pMsg->szUserName, szUserName, USER_NAME_LEN);
	strxcpy(pMsg->szPassword, szPassword, USER_PASSWORD_LEN);
	strxcpy(pMsg->szOASessionID, szOASessionID, OA_SESSION_ID_LEN);

	nRetCode = _SendLS((PACKET_BUFFER*)pMsg, sizeof(T2L_LOGIN_REQ));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

/************************************************************************/
// To DB

BOOL CInternalMessageHandler::DoDBRegister(void)
{
	INT32 nRetCode = 0;

	T2D_REGISTER* pMsg = (T2D_REGISTER*)m_pPacketAllocator->Alloc(sizeof(T2D_REGISTER));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = t2d_register;
	pMsg->dwGTSessionID = CGTSessionMgr::GetInstance().GetSelfSessionID();

	nRetCode = _SendDB((PACKET_BUFFER*)pMsg, sizeof(T2D_REGISTER));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CInternalMessageHandler::DoDBQueryRoleList(UINT32 dwSessionID)
{
	INT32 nRetCode = 0;
	CLIENT_SESSION* pSession = NULL;

	T2D_QUERY_ROLE_LIST* pMsg = (T2D_QUERY_ROLE_LIST*)m_pPacketAllocator->Alloc(sizeof(T2D_QUERY_ROLE_LIST));
	LOG_PROCESS_ERROR(pMsg);

	pSession = CGTSessionMgr::GetInstance().FindClientSession(dwSessionID);
	LOG_PROCESS_ERROR(pSession);

	pMsg->wMsg = t2d_query_role_list;
	pMsg->byServerGroup = pSession->byServerGroup;
	pMsg->dwClientSessionID = dwSessionID;
	strxcpy(pMsg->szUserName, pSession->szUserName, USER_NAME_LEN);

	nRetCode = _SendDB((PACKET_BUFFER*)pMsg, sizeof(T2D_QUERY_ROLE_LIST));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CInternalMessageHandler::DoDBCreateRole(UINT32 dwSessionID, UINT32 dwRoleID,
	CHAR szRoleName[], UINT8 bySex, UINT8 byClass, UINT8 byHairType, UINT8 byHairColor, UINT8 byFaceType, UINT8 bySkinColor)
{
	INT32 nRetCode = 0;

	T2D_CREATE_ROLE* pMsg = (T2D_CREATE_ROLE*)m_pPacketAllocator->Alloc(sizeof(T2D_CREATE_ROLE));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = t2d_create_role;
	pMsg->dwClientSessionID = dwSessionID;
    pMsg->dwRoleID = dwRoleID;
	strxcpy(pMsg->szRoleName, szRoleName, ROLE_NAME_LEN);
	pMsg->bySex = bySex;
	pMsg->byClass = byClass;
	pMsg->byHairType = byHairType;
	pMsg->byHairColor = byHairColor;
	pMsg->byFaceType = byFaceType;
	pMsg->bySkinColor = bySkinColor;

	nRetCode = _SendDB((PACKET_BUFFER*)pMsg, sizeof(T2D_CREATE_ROLE));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CInternalMessageHandler::DoDBDeleteRole(UINT32 dwSessionID, UINT32 dwRoleID)
{
	INT32 nRetCode = 0;

	T2D_DELETE_ROLE* pMsg = (T2D_DELETE_ROLE*)m_pPacketAllocator->Alloc(sizeof(T2D_DELETE_ROLE));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = t2d_delete_role;
	pMsg->dwClientSessionID = dwSessionID;
	pMsg->dwRoleID = dwRoleID;

	nRetCode = _SendDB((PACKET_BUFFER*)pMsg, sizeof(T2D_DELETE_ROLE));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CInternalMessageHandler::DoDBUnDeleteRole(UINT32 dwSessionID, UINT32 dwRoleID)
{
	INT32 nRetCode = 0;

	T2D_UNDELETE_ROLE* pMsg = (T2D_UNDELETE_ROLE*)m_pPacketAllocator->Alloc(sizeof(T2D_UNDELETE_ROLE));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = t2d_undelete_role;
	pMsg->dwClientSessionID = dwSessionID;
	pMsg->dwRoleID = dwRoleID;

	nRetCode = _SendDB((PACKET_BUFFER*)pMsg, sizeof(T2D_UNDELETE_ROLE));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CInternalMessageHandler::DoDBForeverDeleteRole(UINT32 dwSessionID, UINT32 dwRoleID)
{
    INT32 nRetCode = 0;

    T2D_FOREVER_DELETE_ROLE* pMsg = (T2D_FOREVER_DELETE_ROLE*)m_pPacketAllocator->Alloc(sizeof(T2D_DELETE_ROLE));
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = t2d_forever_delete_role;
    pMsg->dwClientSessionID = dwSessionID;
    pMsg->dwRoleID = dwRoleID;

    nRetCode = _SendDB((PACKET_BUFFER*)pMsg, sizeof(T2D_FOREVER_DELETE_ROLE));
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

/************************************************************************/
// From All
void CInternalMessageHandler::OnAllPing(ISocketSession* pSocketSession, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize)
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
// From MS
void CInternalMessageHandler::OnMSRegisterAck(ISocketSession* pSocketSession, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize)
{
	INT32 nRetCode = 0;
	M2T_REGISTER_ACK* pMsg = (M2T_REGISTER_ACK*)pPacketBuffer;

	CGTSessionMgr::GetInstance().SetSelfSessionID(pMsg->dwGTSessionID);
	g_InitReportSetting(GetServerShortName(stGT), pMsg->dwGTSessionID, g_ServerConfig.Common.szReportAbsolutePath);

	INF("GT %d registered to MS", pMsg->dwGTSessionID);

#if defined(WIN32)
	{
		char szTitle[1024];
#ifdef _FINAL
		snprintf(szTitle, 1024, "Gate Server %d, ver %d.%d.%d final, msg ver %08X", pMsg->dwGTSessionID, MAJOR_VERSION, MINOR_VERSION, BUILD_NUMBER, g_nMessageVersion);
#else
		snprintf(szTitle, 1024, "Gate Server %d, ver %d.%d.%d, msg ver %08X", pMsg->dwGTSessionID, MAJOR_VERSION, MINOR_VERSION, BUILD_NUMBER, g_nMessageVersion);
#endif	// _FINAL
		SetConsoleTitle(szTitle);
		INF(szTitle);
	}
#endif  // WIN32
}

void CInternalMessageHandler::OnMSServerInfo(ISocketSession* pSocketSession, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize)
{
	INT32 nRetCode = 0;
	M2A_SERVER_INFO* pMsg = (M2A_SERVER_INFO*)pPacketBuffer;

	CGTSessionMgr::GetInstance().GetDBSession().dwAddr = pMsg->DB.dwAddr;
	CGTSessionMgr::GetInstance().GetDBSession().wPort = pMsg->DB.wPort;
	CGTSessionMgr::GetInstance().GetLSSession().dwAddr = pMsg->LS.dwAddr;
	CGTSessionMgr::GetInstance().GetLSSession().wPort = pMsg->LS.wPort;

	m_pPacketAllocator->Free(pPacketBuffer);
}

void CInternalMessageHandler::OnMSAllReady(ISocketSession* pSocketSession, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize)
{
	INT32 nRetCode = 0;

	CGTSessionMgr::GetInstance().SetServerState(sgsAllReady);
	INF("all servers are ready");
}

void CInternalMessageHandler::OnMSClose(ISocketSession* pSocketSession, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize)
{
	CGTSessionMgr::GetInstance().SetServerState(sgsClosing);
	INF("GT %d is closing", CGTSessionMgr::GetInstance().GetSelfSessionID());
	m_pPacketAllocator->Free(pPacketBuffer);
}

void CInternalMessageHandler::OnMSEnterGateAck(ISocketSession* pSocketSession, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize)
{
	INT32 nResult = errLoginUnknownError;
	INT32 nRetCode = 0;
	M2T_ENTER_GATE* pMsg = (M2T_ENTER_GATE*)pPacketBuffer;

	// 此处找不到session属于合理异常
	// 状态不对必然有BUG
	CLIENT_SESSION* pSession = CGTSessionMgr::GetInstance().FindClientSession(pMsg->dwSessionID);
	PROCESS_ERROR(pSession);

	if (pMsg->nErrCode == errLoginTooManyOnlineRole)
	{
		LOG_PROCESS_ERROR(pSession->eState == cssMSAuthing);

		pSession->eState = cssInQueue;
		pSession->qwTimer = GetTickCountEx() + IN_QUEUE_TIMEOUT;
	}
	else
	{
		LOG_PROCESS_ERROR(pSession->eState == cssMSAuthing || pSession->eState == cssInQueue);
		LOG_PROCESS_ERROR_RET_CODE(pMsg->nErrCode == errSuccess, pMsg->nErrCode);

		nRetCode = CInternalMessageHandler::GetInstance().DoDBQueryRoleList(pSession->dwSessionID);
		LOG_PROCESS_ERROR(nRetCode);

		CExternalMessageHandler::GetInstance().DoLoginAck(pMsg->dwSessionID);

		pSession->eState = cssAuthed;
		pSession->qwTimer = GetTickCountEx() + g_ServerConfig.GT.nLoginAuthTimeout;
	}

	m_pPacketAllocator->Free(pPacketBuffer);

	GT_SYS_LOG_SUCCESS(pSession);
	return;
Exit0:
	GT_SYS_LOG_ERROR(pSession);
	m_pPacketAllocator->Free(pPacketBuffer);

	CRI("OnMSEnterGateAck pMsg->nErrCode = %d", nResult);
	if (pSession && pSession->pSocketSession)
	{
		CExternalMessageHandler::GetInstance().DoErrorNotify(pMsg->dwSessionID, nResult, 0, 0);
		pSession->pSocketSession->Close();
		pSession->byShutDownType = csdtGT;
	}

	return;
}

void CInternalMessageHandler::OnMSQuerySceneAck(ISocketSession* pSocketSession, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize)
{
	INT32 nRetCode = 0;
	M2T_QUERY_SCENE_ACK* pMsg = (M2T_QUERY_SCENE_ACK*)pPacketBuffer;

	CLIENT_SESSION* pSession = CGTSessionMgr::GetInstance().FindClientSession(pMsg->dwClientSessionID);
	PROCESS_ERROR(pSession);
	LOG_PROCESS_ERROR(pSession->eState == cssEnteringGame);

	if (pMsg->nErrorCode == errSuccess)
	{
		CExternalMessageHandler::GetInstance().DoSelectRoleAck(pMsg->dwClientSessionID, pMsg->dwRoleID);

		pSession->dwGSSessionID = pMsg->dwGSSessionID;

		nRetCode = DoGSRoleEnter(pMsg->dwGSSessionID, pMsg->dwClientSessionID, pMsg->dwRoleID);
		LOG_PROCESS_ERROR(nRetCode);

		pSession->eState = cssPlaying;
		pSession->qwTimer = GetTickCountEx() + g_ServerConfig.GT.nPlayingTimeout;
	}
	else
	{
		CExternalMessageHandler::GetInstance().DoErrorNotify(pMsg->dwClientSessionID, pMsg->nErrorCode, pMsg->nErrCodeParam1, pMsg->nErrCodeParam2);
		CRI("session<%08X> query scene failed %d", pSession->dwSessionID, pMsg->nErrorCode);
		pSession->eState = cssRoleOperating;
	}

	m_pPacketAllocator->Free(pPacketBuffer);

	GT_SYS_LOG_SUCCESS(pSession);
	return;
Exit0:
	GT_SYS_LOG_ERROR(pSession);
	m_pPacketAllocator->Free(pPacketBuffer);

	if (pSession && pSession->pSocketSession)
	{
		nRetCode = pSession->pSocketSession->Close();
		pSession->byShutDownType = csdtGT;
		LOG_CHECK_ERROR(nRetCode);
	}

	return;
}

void CInternalMessageHandler::OnMSCloseClientSession(ISocketSession* pSocketSession, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize)
{
	INT32 nRetCode = 0;
	M2T_CLOSE_CLIENT_SESSION* pMsg = (M2T_CLOSE_CLIENT_SESSION*)pPacketBuffer;

	CLIENT_SESSION* pSession = CGTSessionMgr::GetInstance().FindClientSession(pMsg->dwClientSessionID);
	PROCESS_ERROR(pSession);
	LOG_PROCESS_ERROR(pSession->pSocketSession);

	nRetCode = pSession->pSocketSession->Close();
	pSession->byShutDownType = csdtMS;
	LOG_PROCESS_ERROR(nRetCode);

	m_pPacketAllocator->Free(pPacketBuffer);
	return;
Exit0:
	//INF("MS close client session <%08X>", pMsg->dwClientSessionID);
	GT_SYS_LOG_ERROR(pSession);
	m_pPacketAllocator->Free(pPacketBuffer);

	return;
}

void CInternalMessageHandler::OnMSReturnSelectRole(ISocketSession* pSocketSession, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize)
{
	INT32 nRetCode = 0;
	M2T_RETURN_SELECT_ROLE* pMsg = (M2T_RETURN_SELECT_ROLE*)pPacketBuffer;

	CLIENT_SESSION* pSession = CGTSessionMgr::GetInstance().FindClientSession(pMsg->dwClientSessionID);
	PROCESS_ERROR(pSession);
	LOG_PROCESS_ERROR(pSession->eState == cssReturnSelectRole);

	nRetCode = DoDBQueryRoleList(pMsg->dwClientSessionID);
	LOG_PROCESS_ERROR(nRetCode);

	pSession->eState = cssAuthed;
	pSession->qwTimer = GetTickCountEx() + g_ServerConfig.GT.nLoginAuthTimeout;

	m_pPacketAllocator->Free(pPacketBuffer);

	GT_SYS_LOG_SUCCESS(pSession);
	return;
Exit0:

	GT_SYS_LOG_ERROR(pSession);
	m_pPacketAllocator->Free(pPacketBuffer);

	if (pSession && pSession->pSocketSession)
	{
		nRetCode = pSession->pSocketSession->Close();
		pSession->byShutDownType = csdtGT;
		LOG_CHECK_ERROR(nRetCode);
	}

	return;
}

void CInternalMessageHandler::OnMSChangeGS(ISocketSession* pSocketSession, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize)
{
	INT32 nRetCode = 0;
	M2T_CHANGE_GS* pMsg = (M2T_CHANGE_GS*)pPacketBuffer;

	CLIENT_SESSION* pSession = CGTSessionMgr::GetInstance().FindClientSession(pMsg->dwClientSessionID);
	PROCESS_ERROR(pSession);
	LOG_PROCESS_ERROR(pSession->eState == cssPlaying);

	pSession->dwGSSessionID = pMsg->dwGSSessionID;

	nRetCode = DoMSChangeGSAck(pMsg->dwClientSessionID);
	LOG_PROCESS_ERROR(nRetCode);

	m_pPacketAllocator->Free(pPacketBuffer);
	GT_SYS_LOG_SUCCESS(pSession);
	return;
Exit0:
	GT_SYS_LOG_ERROR(pSession);
	m_pPacketAllocator->Free(pPacketBuffer);

	if (pSession && pSession->pSocketSession)
	{
		nRetCode = pSession->pSocketSession->Close();
		pSession->byShutDownType = csdtGT;
		LOG_CHECK_ERROR(nRetCode);
	}

	return;
}

void CInternalMessageHandler::OnMSClientMsg(ISocketSession* pSocketSession, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize)
{
	INT32 nRetCode = 0;
	M2T_CLIENT_MSG* pMsg = (M2T_CLIENT_MSG*)pPacketBuffer;

	nRetCode = CExternalMessageHandler::GetInstance().Send(pMsg->dwSessionID, pPacketBuffer,
		dwSize - sizeof(M2T_CLIENT_MSG), sizeof(M2T_CLIENT_MSG));
	LOG_PROCESS_ERROR(nRetCode);

	return;
Exit0:
	if (pPacketBuffer)
		m_pPacketAllocator->Free(pPacketBuffer);

	return;
}

void CInternalMessageHandler::OnMSBroadcastClientMsg(ISocketSession* pSocketSession, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize)
{
	INT32 nRetCode = 0;
	M2T_BROADCAST_CLIENT_MSG* pMsg = (M2T_BROADCAST_CLIENT_MSG*)pPacketBuffer;
	PACKET_BUFFER* pOutMsg = NULL;

	UINT32 dwMsgSize = dwSize - pMsg->wSessionCount * sizeof(pMsg->dwSessionIDList[0]) -
		sizeof(M2T_BROADCAST_CLIENT_MSG);
	LOG_PROCESS_ERROR(dwMsgSize > 0);

	for (INT32 nIndex = 0; nIndex < pMsg->wSessionCount; nIndex++)
	{
		pOutMsg = m_pPacketAllocator->Alloc(dwMsgSize);
		LOG_PROCESS_ERROR(pOutMsg);

		memcpy(pOutMsg, pMsg->dwSessionIDList + pMsg->wSessionCount, dwMsgSize);

		nRetCode = CExternalMessageHandler::GetInstance().Send(pMsg->dwSessionIDList[nIndex], pOutMsg, dwMsgSize);
		if (!nRetCode)
			m_pPacketAllocator->Free(pOutMsg);
		pOutMsg = NULL;
	}

Exit0:
	if (pOutMsg)
		m_pPacketAllocator->Free(pOutMsg);
	m_pPacketAllocator->Free(pPacketBuffer);

	return;
}

void CInternalMessageHandler::OnMSSwitchServerState(ISocketSession* pSocketSession, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize)
{
	INT32 nRetCode = 0;
	M2T_SWITCH_SERVER_GROUP_STATE* pMsg = (M2T_SWITCH_SERVER_GROUP_STATE*)pPacketBuffer;

	CGTSessionMgr::GetInstance().SetOpenned(pMsg->byServerGroup, pMsg->byOpened);
	INF("GT %d group %d switched to %d", CGTSessionMgr::GetInstance().GetSelfSessionID(), pMsg->byServerGroup, pMsg->byOpened);

Exit0:
	m_pPacketAllocator->Free(pPacketBuffer);

	return;
}

void CInternalMessageHandler::OnMSGMCommand(ISocketSession* pSocketSession, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize)
{
	INT32 nRetCode = 0;
	M2T_GM_COMMAND* pMsg = (M2T_GM_COMMAND*)pPacketBuffer;

	if (strnicmp(pMsg->szGMCommand, "reload", sizeof("reload") - 1) == 0)
	{
		nRetCode = LoadGlobalConfig(g_szGlobalConfigFileName);
		LOG_CHECK_ERROR(nRetCode);
	}

Exit0:
	m_pPacketAllocator->Free(pPacketBuffer);

	return;
}

/************************************************************************/
// From GS

void CInternalMessageHandler::OnGSRegister(ISocketSession* pSocketSession, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize)
{
	INT32 nRetCode = 0;
	G2T_REGISTER* pMsg = (G2T_REGISTER*)pPacketBuffer;

	GS_SESSION* pGSSession = CGTSessionMgr::GetInstance().GetGSSession(pMsg->dwGSSessionID);
	LOG_PROCESS_ERROR(pGSSession);

	LOG_PROCESS_ERROR(CGTSessionMgr::GetInstance().GetServerState() != sgsClosing);

	LOG_PROCESS_ERROR(pSocketSession);

	//LOG_PROCESS_ERROR(pGSSession->pSocketSession == NULL);
	if (pGSSession->pSocketSession)
	{
		struct in_addr addr;
		UINT32 dwRemoteIp = 0;
		UINT16 wRemotePort = 0;
		nRetCode = pGSSession->pSocketSession->GetRemoteAddress(dwRemoteIp, wRemotePort);
		LOG_CHECK_ERROR(nRetCode);
		addr.s_addr = dwRemoteIp;
		CRI("OnGSRegister, but GSSessionID %d have set socket %X from %s:%d",
			pMsg->dwGSSessionID, pGSSession->pSocketSession, inet_ntoa(addr), wRemotePort);

		LOG_PROCESS_ERROR(((GS_SESSION*)pGSSession->pSocketSession->GetUserData()) == pGSSession);
		LOG_PROCESS_ERROR(FALSE);
	}

	pGSSession->pSocketSession = pSocketSession;
	pGSSession->qwTimer = GetTickCountEx() + g_ServerConfig.Common.nServerPingTimeout;
	pSocketSession->SetUserData(pGSSession);

	nRetCode = DoGSRegisterAck(pMsg->dwGSSessionID);
	LOG_PROCESS_ERROR(nRetCode);

	INF("GS %d register to GT %d", pMsg->dwGSSessionID, CGTSessionMgr::GetInstance().GetSelfSessionID());

	m_pPacketAllocator->Free(pPacketBuffer);

	return;
Exit0:
	m_pPacketAllocator->Free(pPacketBuffer);
	if (pSocketSession)
		pSocketSession->Close();

	return;
}

void CInternalMessageHandler::OnGSClientMsg(ISocketSession* pSocketSession, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize)
{
	INT32 nRetCode = 0;
	G2T_CLIENT_MSG* pMsg = (G2T_CLIENT_MSG*)pPacketBuffer;

	nRetCode = CExternalMessageHandler::GetInstance().Send(pMsg->dwSessionID, pPacketBuffer,
		dwSize - sizeof(G2T_CLIENT_MSG), sizeof(G2T_CLIENT_MSG));
	PROCESS_ERROR(nRetCode);

	return;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return;
}

void CInternalMessageHandler::OnGSBroadcastClientMsg(ISocketSession* pSocketSession, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize)
{
	INT32 nRetCode = 0;
	G2T_BROADCAST_CLIENT_MSG* pMsg = (G2T_BROADCAST_CLIENT_MSG*)pPacketBuffer;
	PACKET_BUFFER* pOutMsg = NULL;

	UINT32 dwMsgSize = dwSize - pMsg->wSessionCount * sizeof(pMsg->dwSessionIDList[0]) -
		sizeof(G2T_BROADCAST_CLIENT_MSG);
	LOG_PROCESS_ERROR(dwMsgSize > 0);

	for (INT32 nIndex = 0; nIndex < pMsg->wSessionCount; nIndex++)
	{
		pOutMsg = m_pPacketAllocator->Alloc(dwMsgSize);
		LOG_PROCESS_ERROR(pOutMsg);

		memcpy(pOutMsg, pMsg->dwSessionIDList + pMsg->wSessionCount, dwMsgSize);

		nRetCode = CExternalMessageHandler::GetInstance().Send(pMsg->dwSessionIDList[nIndex], pOutMsg, dwMsgSize);
		if (!nRetCode)
			m_pPacketAllocator->Free(pOutMsg);
		pOutMsg = NULL;
	}

Exit0:
	if (pOutMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pOutMsg);
	m_pPacketAllocator->Free(pPacketBuffer);

	return;
}

void CInternalMessageHandler::OnGSCloseClientSession(ISocketSession* pSocketSession, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize)
{
	INT32 nRetCode = 0;
	G2T_CLOSE_CLIENT_SESSION* pMsg = (G2T_CLOSE_CLIENT_SESSION*)pPacketBuffer;

	CLIENT_SESSION* pSession = CGTSessionMgr::GetInstance().FindClientSession(pMsg->dwClientSessionID);
	PROCESS_ERROR(pSession);
	LOG_PROCESS_ERROR(pSession->pSocketSession);

	nRetCode = pSession->pSocketSession->Close();
	LOG_PROCESS_ERROR(nRetCode);

Exit0:
	if (pMsg->byLogout)
	{
		GT_SYS_LOG_SUCCESS(pSession);
		//INF("logout client session <%08X>", pMsg->dwClientSessionID);
		if (pSession)
			pSession->byShutDownType = csdtLogout;
	}
	else
	{
		GT_SYS_LOG_ERROR(pSession);
		//INF("GS close client session <%08X>", pMsg->dwClientSessionID);
		if (pSession)
			pSession->byShutDownType = csdtGS;
	}

	m_pPacketAllocator->Free(pPacketBuffer);
	return;
}

void CInternalMessageHandler::OnGSReturnSelectRole(ISocketSession* pSocketSession, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize)
{
	INT32 nRetCode = 0;
	G2T_RETURN_ROLE_SELECT* pMsg = (G2T_RETURN_ROLE_SELECT*)pPacketBuffer;

	CLIENT_SESSION* pSession = CGTSessionMgr::GetInstance().FindClientSession(pMsg->dwClientSessionID);
	PROCESS_ERROR(pSession);
	LOG_PROCESS_ERROR(pSession->eState == cssPlaying);

	nRetCode = DoMSReturnSelectRole(pMsg->dwClientSessionID);
	LOG_PROCESS_ERROR(nRetCode);

	CExternalMessageHandler::GetInstance().DoReturnSelectRole(pMsg->dwClientSessionID);

	pSession->eState = cssReturnSelectRole;

	m_pPacketAllocator->Free(pPacketBuffer);
	GT_SYS_LOG_SUCCESS(pSession);
	return;

Exit0:
	GT_SYS_LOG_ERROR(pSession);
	m_pPacketAllocator->Free(pPacketBuffer);

	if (pSession && pSession->pSocketSession)
	{
		nRetCode = pSession->pSocketSession->Close();
		pSession->byShutDownType = csdtGT;
		LOG_CHECK_ERROR(nRetCode);
	}

	return;
}

/************************************************************************/
// From LS

void CInternalMessageHandler::OnLSRegisterAck(ISocketSession* pSocketSession, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize)
{
	CGTSessionMgr::GetInstance().GetLSSession().bConnected = true;

	INF("GT %d registered to LS", CGTSessionMgr::GetInstance().GetSelfSessionID());

	_CheckReady();

	m_pPacketAllocator->Free(pPacketBuffer);
}

void CInternalMessageHandler::OnLSLoginAck(ISocketSession* pSocketSession, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize)
{
	INT32 nResult = errLoginUnknownError;
	INT32 nRetCode = 0;
	L2T_LOGIN_ACK* pMsg = (L2T_LOGIN_ACK*)pPacketBuffer;
	CLIENT_SESSION* pSession = NULL;

	// 此处找不到session属于合理异常, 状态不对必然有BUG
	pSession = CGTSessionMgr::GetInstance().FindClientSession(pMsg->dwClientSessionID);
	PROCESS_ERROR(pSession);
	LOG_PROCESS_ERROR(pSession->eState == cssLSAuthing);
	PROCESS_ERROR_RET_CODE(pMsg->nErrorCode == errSuccess, pMsg->nErrorCode);

	// pMsg->szUserName hold SNDA ID from login server which indirectly from oa_authorize
	strxcpy(pSession->szOASessionID, pMsg->szOASessionID, OA_SESSION_ID_LEN);
	strxcpy(pSession->szUserName, pMsg->szUserName, USER_NAME_LEN);
	strxcpy(pSession->szPGT, pMsg->szPGT, OA_PGT_FIELD_LEN);
	pSession->bAdult = pMsg->bAdult;

	// 暂时屏蔽 白名单
	//for (INT32 nIndex = 1; nIndex < sizeof(g_ServerConfig.Common.UserWhiteList) / sizeof(g_ServerConfig.Common.UserWhiteList[0]); nIndex++)
	//{
	//	if (g_ServerConfig.Common.UserWhiteList[nIndex].szUserName[0] == 0)
	//		break;
	//
	//	if (strncmp(g_ServerConfig.Common.UserWhiteList[nIndex].szUserName, pMsg->szUserName, COMMON_NAME_LEN) == 0)
	//	{
	//		pSession->bUserWhiteList = TRUE;
	//		break;
	//	}
	//
	//	if (g_ServerConfig.Common.UserWhiteList[nIndex].szUserName[0] == '*')
	//	{
	//		pSession->bUserWhiteList = TRUE;
	//		break;
	//	}
	//}

	if (pSession->bUserWhiteList)
		LOG_PROCESS_ERROR(pSession->bIpWhiteList);

	if (!CGTSessionMgr::GetInstance().IsOpened(pSession->byServerGroup))
	{
		PROCESS_ERROR_RET_CODE(pSession->bUserWhiteList, errLoginServerNotReady);
	}

	// 发送给MS
	nRetCode = DoMSEnterGate(pMsg->dwClientSessionID);
	LOG_PROCESS_ERROR(nRetCode);

	pSession->eState = cssMSAuthing;
	pSession->qwTimer = GetTickCountEx() + g_ServerConfig.GT.nLoginAuthTimeout;

	m_pPacketAllocator->Free(pPacketBuffer);
	GT_SYS_LOG_SUCCESS(pSession);
	return;
Exit0:
	GT_SYS_LOG_ERROR(pSession);
	m_pPacketAllocator->Free(pPacketBuffer);

	if (pSession && pSession->pSocketSession)
	{
		CExternalMessageHandler::GetInstance().DoErrorNotify(pMsg->dwClientSessionID, nResult, 0, 0);

		nRetCode = pSession->pSocketSession->Close();
		pSession->byShutDownType = csdtGT;
		LOG_CHECK_ERROR(nRetCode);
	}

	return;
}

/************************************************************************/
// From DB

void CInternalMessageHandler::OnDBRegisterAck(ISocketSession* pSocketSession, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize)
{
	CGTSessionMgr::GetInstance().GetDBSession().bConnected = true;

	INF("GT %d registered to DB", CGTSessionMgr::GetInstance().GetSelfSessionID());

	_CheckReady();

	m_pPacketAllocator->Free(pPacketBuffer);
}

void CInternalMessageHandler::OnDBSyncRoleList(ISocketSession* pSocketSession, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize)
{
	INT32 nResult = errUnknownError;
	INT32 nRetCode = 0;
	D2T_SYNC_ROLE_LIST* pMsg = (D2T_SYNC_ROLE_LIST*)pPacketBuffer;
	CLIENT_SESSION* pSession = NULL;

	// 此处找不到session为合理异常
	// 状态不对表示有BUG
	pSession = CGTSessionMgr::GetInstance().FindClientSession(pMsg->dwClientSessionID);
	PROCESS_ERROR(pSession);
	LOG_PROCESS_ERROR(pSession->eState == cssAuthed);
	LOG_PROCESS_ERROR_RET_CODE(pMsg->nErrCode = errSuccess, pMsg->nErrCode);

	CExternalMessageHandler::GetInstance().DoSyncRoleList(pMsg->dwClientSessionID, pMsg->byRoleCount, pMsg->BaseData);

	pSession->byRoleCount = pMsg->byRoleCount;
	LOG_PROCESS_ERROR(pMsg->byRoleCount <= MAX_ROLE_PER_USER);

	for (INT32 nIndex = 0; nIndex < pMsg->byRoleCount; nIndex++)
	{
		ROLE_DB_BASE_DATA* pBaseData = ((ROLE_DB_BASE_DATA*)pMsg->BaseData) + nIndex;

		pSession->RoleList[nIndex].dwRoleID = pBaseData->dwRoleID;

		pSession->RoleList[nIndex].nSceneTemplateID = pBaseData->nSceneTempID;
		pSession->RoleList[nIndex].nSceneID = pBaseData->nSceneID;
		pSession->RoleList[nIndex].nX = pBaseData->nX;
		pSession->RoleList[nIndex].nY = pBaseData->nY;
		pSession->RoleList[nIndex].nZ = pBaseData->nZ;
		pSession->RoleList[nIndex].wFaceDirection = pBaseData->wFaceDirection;

		pSession->RoleList[nIndex].nReturnSceneTemplateID = pBaseData->byStaticReturnSceneTempID;
		pSession->RoleList[nIndex].nReturnSceneID = pBaseData->nStaticReturnSceneID;
		pSession->RoleList[nIndex].nReturnX = pBaseData->nStaticReturnX;
		pSession->RoleList[nIndex].nReturnY = pBaseData->nStaticReturnY;
		pSession->RoleList[nIndex].nReturnZ = pBaseData->nStaticReturnZ;
		pSession->RoleList[nIndex].wReturnFaceDirection = pBaseData->wStaticReturnFaceDirection;
		pSession->RoleList[nIndex].byDeleted = pBaseData->dwDeleteTime ? 1 : 0;
	}

	pSession->eState = cssRoleOperating;
	pSession->qwTimer = GetTickCountEx() + g_ServerConfig.GT.nRoleOperateTimeout;

	m_pPacketAllocator->Free(pPacketBuffer);

	GT_SYS_LOG_SUCCESS(pSession);
	return;
Exit0:
	GT_SYS_LOG_ERROR(pSession);
	m_pPacketAllocator->Free(pPacketBuffer);

	if (pSession && pSession->pSocketSession)
	{
		CExternalMessageHandler::GetInstance().DoErrorNotify(pMsg->dwClientSessionID, nResult, 0, 0);
		nRetCode = pSession->pSocketSession->Close();
		pSession->byShutDownType = csdtGT;
		LOG_CHECK_ERROR(nRetCode);
	}

	return;
}

void CInternalMessageHandler::OnDBCreateRoleAck(ISocketSession* pSocketSession, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize)
{
	INT32 nRetCode = 0;
	D2T_CREATE_ROLE_ACK* pMsg = (D2T_CREATE_ROLE_ACK*)pPacketBuffer;
	ROLE_DB_BASE_DATA* pBaseData = NULL;

	// 此处找不到session属于合理异常
	// 状态不对可能是外挂在做尝试，可能是客户端或服务端有BUG
	CLIENT_SESSION* pSession = CGTSessionMgr::GetInstance().FindClientSession(pMsg->dwClientSessionID);
	PROCESS_ERROR(pSession);
	LOG_PROCESS_ERROR(pSession->eState == cssCreatingRole);

	pSession->qwTimer = GetTickCountEx() + g_ServerConfig.GT.nRoleOperateTimeout;
	if (pMsg->nErrCode == errSuccess)
	{
		// 此处数量不对是有BUG
		pBaseData = (ROLE_DB_BASE_DATA*)pMsg->BaseData;
		LOG_PROCESS_ERROR(pSession->byRoleCount < MAX_ROLE_PER_USER);

		pSession->RoleList[pSession->byRoleCount].dwRoleID = pBaseData->dwRoleID;

		pSession->RoleList[pSession->byRoleCount].nSceneTemplateID = pBaseData->nSceneTempID;
		pSession->RoleList[pSession->byRoleCount].nSceneID = pBaseData->nSceneID;
		pSession->RoleList[pSession->byRoleCount].nX = pBaseData->nX;
		pSession->RoleList[pSession->byRoleCount].nY = pBaseData->nY;
		pSession->RoleList[pSession->byRoleCount].nZ = pBaseData->nZ;
		pSession->RoleList[pSession->byRoleCount].wFaceDirection = pBaseData->wFaceDirection;

		pSession->RoleList[pSession->byRoleCount].nReturnSceneTemplateID = pBaseData->byStaticReturnSceneTempID;
		pSession->RoleList[pSession->byRoleCount].nReturnSceneID = pBaseData->nStaticReturnSceneID;
		pSession->RoleList[pSession->byRoleCount].nReturnX = pBaseData->nStaticReturnX;
		pSession->RoleList[pSession->byRoleCount].nReturnY = pBaseData->nStaticReturnY;
		pSession->RoleList[pSession->byRoleCount].nReturnZ = pBaseData->nStaticReturnZ;
		pSession->RoleList[pSession->byRoleCount].wReturnFaceDirection = pBaseData->wStaticReturnFaceDirection;
        pSession->RoleList[pSession->byRoleCount].byDeleted = pBaseData->dwDeleteTime ? 1 : 0;

		pSession->byRoleCount++;

		CExternalMessageHandler::GetInstance().DoCreateRoleAck(pMsg->dwClientSessionID, pMsg->BaseData);
	}
	else
	{
		CExternalMessageHandler::GetInstance().DoErrorNotify(pMsg->dwClientSessionID, pMsg->nErrCode, 0, 0);
	}

    pSession->eState = cssRoleOperating;

	m_pPacketAllocator->Free(pPacketBuffer);
	GT_SYS_LOG_SUCCESS(pSession);
	return;
Exit0:
	GT_SYS_LOG_ERROR(pSession);
	m_pPacketAllocator->Free(pPacketBuffer);

	if (pSession && pSession->pSocketSession)
	{
		pSession->pSocketSession->Close();
		pSession->byShutDownType = csdtGT;
	}

	return;
}

void CInternalMessageHandler::OnDBDeleteRoleAck(ISocketSession* pSocketSession, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize)
{
	INT32 nRetCode = 0;
	D2T_DELETE_ROLE_ACK* pMsg = (D2T_DELETE_ROLE_ACK*)pPacketBuffer;

	// 此处找不到session属于合理异常
	// 状态不对可能是外挂在做尝试，可能是客户端或服务端有BUG
	CLIENT_SESSION* pSession = CGTSessionMgr::GetInstance().FindClientSession(pMsg->dwClientSessionID);
	PROCESS_ERROR(pSession);
	LOG_PROCESS_ERROR(pSession->eState == cssDeletingRole);

	pSession->qwTimer = GetTickCountEx() + g_ServerConfig.GT.nRoleOperateTimeout;
	if (pMsg->nErrCode == errSuccess)
	{
		INT32 nRoleIndex = 0;
		for (; nRoleIndex < pSession->byRoleCount; nRoleIndex++)
		{
			if (pSession->RoleList[nRoleIndex].dwRoleID == pMsg->dwRoleID)
			{
				pSession->RoleList[nRoleIndex].byDeleted = 1;
				break;
			}
		}

		CExternalMessageHandler::GetInstance().DoDeleteRoleAck(pMsg->dwClientSessionID, pMsg->dwRoleID);
	}
	else
	{
		CExternalMessageHandler::GetInstance().DoErrorNotify(pMsg->dwClientSessionID, pMsg->nErrCode, 0, 0);
	}

	pSession->eState = cssRoleOperating;

	m_pPacketAllocator->Free(pPacketBuffer);
	GT_SYS_LOG_SUCCESS(pSession);
	return;
Exit0:
	GT_SYS_LOG_ERROR(pSession);
	m_pPacketAllocator->Free(pPacketBuffer);

	if (pSession && pSession->pSocketSession)
	{
		pSession->pSocketSession->Close();
		pSession->byShutDownType = csdtGT;
	}

	return;
}

void CInternalMessageHandler::OnDBUnDeleteRoleAck(ISocketSession* pSocketSession, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize)
{
	INT32 nRetCode = 0;
	D2T_UNDELETE_ROLE_ACK* pMsg = (D2T_UNDELETE_ROLE_ACK*)pPacketBuffer;

	// 此处找不到session属于合理异常
	// 状态不对可能是外挂在做尝试，可能是客户端或服务端有BUG
	CLIENT_SESSION* pSession = CGTSessionMgr::GetInstance().FindClientSession(pMsg->dwClientSessionID);
	PROCESS_ERROR(pSession);
	LOG_PROCESS_ERROR(pSession->eState == cssDeletingRole);

	pSession->qwTimer = GetTickCountEx() + g_ServerConfig.GT.nRoleOperateTimeout;
	if (pMsg->nErrCode == errSuccess)
	{
		INT32 nRoleIndex = 0;
		for (; nRoleIndex < pSession->byRoleCount; nRoleIndex++)
		{
			if (pSession->RoleList[nRoleIndex].dwRoleID == pMsg->dwRoleID)
			{
				pSession->RoleList[nRoleIndex].byDeleted = 0;
				break;
			}
		}

		CExternalMessageHandler::GetInstance().DoUnDeleteRoleAck(pMsg->dwClientSessionID, pMsg->dwRoleID);
	}
	else
	{
		CExternalMessageHandler::GetInstance().DoErrorNotify(pMsg->dwClientSessionID, pMsg->nErrCode, 0, 0);
	}

	pSession->eState = cssRoleOperating;

	m_pPacketAllocator->Free(pPacketBuffer);
	GT_SYS_LOG_SUCCESS(pSession);
	return;
Exit0:
	GT_SYS_LOG_ERROR(pSession);
	m_pPacketAllocator->Free(pPacketBuffer);

	if (pSession && pSession->pSocketSession)
	{
		pSession->pSocketSession->Close();
		pSession->byShutDownType = csdtGT;
	}

	return;
}

void CInternalMessageHandler::OnDBForeverDeleteRoleAck(ISocketSession* pSocketSession, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize)
{
    INT32 nRetCode = 0;
    D2T_FOREVER_DELETE_ROLE_ACK* pMsg = (D2T_FOREVER_DELETE_ROLE_ACK*)pPacketBuffer;

    // 此处找不到session属于合理异常
    // 状态不对可能是外挂在做尝试，可能是客户端或服务端有BUG
    CLIENT_SESSION* pSession = CGTSessionMgr::GetInstance().FindClientSession(pMsg->dwClientSessionID);
    PROCESS_ERROR(pSession);
    LOG_PROCESS_ERROR(pSession->eState == cssDeletingRole);

    pSession->qwTimer = GetTickCountEx() + g_ServerConfig.GT.nRoleOperateTimeout;
    if (pMsg->nErrCode == errSuccess)
    {
        INT32 nRoleIndex = 0;
        for (; nRoleIndex < pSession->byRoleCount; nRoleIndex++)
        {
            if (pSession->RoleList[nRoleIndex].dwRoleID == pMsg->dwRoleID)
            {
                break;
            }
        }
        LOG_PROCESS_ERROR(nRoleIndex < pSession->byRoleCount);

        pSession->byRoleCount--;

        for (; nRoleIndex < pSession->byRoleCount; nRoleIndex++)
        {
            memcpy(&pSession->RoleList[nRoleIndex], &pSession->RoleList[nRoleIndex + 1], sizeof(CLIENT_SESSION::ROLE_BRIEF_INFO));
        }

        CExternalMessageHandler::GetInstance().DoForeverDeleteRoleAck(pMsg->dwClientSessionID, pMsg->dwRoleID);
    }
    else
    {
        CExternalMessageHandler::GetInstance().DoErrorNotify(pMsg->dwClientSessionID, pMsg->nErrCode, 0, 0);
    }

    pSession->eState = cssRoleOperating;

    m_pPacketAllocator->Free(pPacketBuffer);
    GT_SYS_LOG_SUCCESS(pSession);
    return;
Exit0:
    GT_SYS_LOG_ERROR(pSession);
    m_pPacketAllocator->Free(pPacketBuffer);

    if (pSession && pSession->pSocketSession)
    {
        pSession->pSocketSession->Close();
        pSession->byShutDownType = csdtGT;
    }

    return;
}

void CInternalMessageHandler::OnDBCloseClientSession(ISocketSession* pSocketSession, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize)
{
	INT32 nRetCode = 0;
	D2T_CLOSE_CLIENT_SESSION* pMsg = (D2T_CLOSE_CLIENT_SESSION*)pPacketBuffer;

	CLIENT_SESSION* pSession = CGTSessionMgr::GetInstance().FindClientSession(pMsg->dwClientSessionID);
	PROCESS_ERROR(pSession);
	LOG_PROCESS_ERROR(pSession->pSocketSession);

	nRetCode = pSession->pSocketSession->Close();
	LOG_PROCESS_ERROR(nRetCode);

	pSession->byShutDownType = csdtDB;
Exit0:
	//INF("DB close client session <%08X>", pMsg->dwClientSessionID);
	GT_SYS_LOG_ERROR(pSession);
	m_pPacketAllocator->Free(pPacketBuffer);

	return;
}

BOOL CInternalMessageHandler::DoMSCheckNewName(UINT32 dwClientSessionID, const char* szName, const char* UserData, UINT32 dwUserDataLen)
{
	INT32 nRetCode = 0;

	T2M_CHECK_NEW_NAME* pMsg = (T2M_CHECK_NEW_NAME*)m_pPacketAllocator->Alloc(sizeof(T2M_CHECK_NEW_NAME));
	LOG_PROCESS_ERROR(pMsg);
    LOG_PROCESS_ERROR(dwUserDataLen <= USER_DATA_LEN);

	pMsg->wMsg = t2m_check_new_name;
	pMsg->dwClientSessionID = dwClientSessionID;
	strncpy(pMsg->szName, szName, sizeof(pMsg->szName) - 1);
    memcpy(pMsg->UserData, UserData, dwUserDataLen);

	nRetCode = _SendMS((PACKET_BUFFER*)pMsg, sizeof(T2M_CHECK_NEW_NAME));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;

}

void CInternalMessageHandler::OnMSCheckNewName(ISocketSession* pSocketSession, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize)
{
    INT32 nRetCode = 0;
    M2T_CHECK_NEW_NAME* pMsg = (M2T_CHECK_NEW_NAME*)pPacketBuffer;
    CreateRoleParam* p = (CreateRoleParam*)pMsg->UserData;

    CLIENT_SESSION* pSession = CGTSessionMgr::GetInstance().FindClientSession(pMsg->dwClientSessionID);
    PROCESS_ERROR(pSession);
    LOG_PROCESS_ERROR(pSession->eState == cssCreatingRole);

    if (pMsg->nErrorCode == errNsSuccess)
    {
        nRetCode = DoDBCreateRole(pSession->dwSessionID, pMsg->dwID, pMsg->szName,
            p->bySex, p->byClass, p->byHairType, p->byHairColor, p->byFaceType, p->bySkinColor);
        LOG_PROCESS_ERROR(nRetCode);
    }
    else
    {
        INT32 err = errUnknownError;
        switch (pMsg->nErrorCode)
        {
        case errNsNameDuplicated:
            err = errLoginCreateRoleNsDupeName;
            break;
        case errNsNameDBSysErr:
            err = errLoginCreateRoleNsDbSysErr;
            break;
        default:
            WRN("Unknown Error From NameServer: %d", pMsg->nErrorCode);
        }
        CExternalMessageHandler::GetInstance().DoErrorNotify(pMsg->dwClientSessionID, err, 0, 0);

        pSession->eState = cssRoleOperating;
    }

    m_pPacketAllocator->Free(pPacketBuffer);
    GT_SYS_LOG_SUCCESS(pSession);
    return;
Exit0:
    GT_SYS_LOG_ERROR(pSession);
    m_pPacketAllocator->Free(pPacketBuffer);

    if (pSession && pSession->pSocketSession)
    {
        pSession->pSocketSession->Close();
        pSession->byShutDownType = csdtGT;
    }

    return;

}
