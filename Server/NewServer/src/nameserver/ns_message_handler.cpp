#include "stdafx.h"
#include "ns_message_handler.h"
#include "ns_message.h"
#include "nameserver.h"
#include "server_config.h"
#include "common_message.h"
#include "time_ex.h"

CNSMessageHandler CNSMessageHandler::ms_Instance;

CNSMessageHandler::CNSMessageHandler(void)
{
	m_pNet = NULL;
	m_pAcceptor = NULL;
	m_nNetType = 0;
	m_nFreeSlotIndex = 0;
	m_qwLastPingTick = 0;
	memset(m_MessageFuncList, 0, sizeof(m_MessageFuncList));
	memset(m_SessionList, 0, sizeof(m_SessionList));
}

CNSMessageHandler::~CNSMessageHandler(void)
{

}

CNSMessageHandler& CNSMessageHandler::GetInstance(void)
{
	return ms_Instance;
}

BOOL CNSMessageHandler::Init(void)
{
	INT32 nRetCode = 0;
#if defined(WIN32)
    INTRANET_INIT_PARAM IntranetInitParam;
#else
    SIMPLE_INIT_PARAM SimpleInitParam;
#endif

    nRetCode = m_PacketAllocator.Init(g_NSConfig.net_config.small_packet_count, g_NSConfig.net_config.large_packet_count);
    LOG_PROCESS_ERROR(nRetCode);

#if defined(WIN32)
	m_nNetType = netIntranet;
	IntranetInitParam.nMaxAcceptor = g_NSConfig.net_config.max_acceptor;
    IntranetInitParam.nMaxConnector = g_NSConfig.net_config.max_connector;
    IntranetInitParam.nMaxSessionCount = g_NSConfig.net_config.max_session;
    IntranetInitParam.nSendBufSize = g_NSConfig.net_config.send_buf_size;
    IntranetInitParam.nRecvBufSize = g_NSConfig.net_config.recv_buf_size;
    IntranetInitParam.nPacketBufferSize = g_NSConfig.net_config.packet_buf_size;
    IntranetInitParam.nDisconnectTimeout = g_NSConfig.net_config.sharemem_disconnect_timeout;
    m_pNet = g_CreateNetInterface(m_nNetType, &m_PacketAllocator, this, &IntranetInitParam);
#else
	m_nNetType = netSimple;
    SimpleInitParam.nMaxAcceptor = g_NSConfig.net_config.max_acceptor;
    SimpleInitParam.nMaxConnector = g_NSConfig.net_config.max_connector;
    SimpleInitParam.nMaxSessionCount = g_NSConfig.net_config.max_session;
    SimpleInitParam.nSendBufSize = g_NSConfig.net_config.send_buf_size;
    SimpleInitParam.nRecvBufSize = g_NSConfig.net_config.recv_buf_size;
    SimpleInitParam.nPacketBufferSize = g_NSConfig.net_config.packet_buf_size;
    m_pNet = g_CreateNetInterface(netSimple, &m_PacketAllocator, this, &SimpleInitParam);
#endif
    LOG_PROCESS_ERROR(m_pNet);

	m_pAcceptor = m_pNet->CreateAcceptor();
	LOG_PROCESS_ERROR(m_pAcceptor);

	nRetCode = m_pAcceptor->Open(inet_addr(g_NSConfig.net_config.ip), g_NSConfig.net_config.port);
	LOG_PROCESS_ERROR(nRetCode);

    INF("opened listen port at %s:%d", g_NSConfig.net_config.ip, g_NSConfig.net_config.port);

	m_nFreeSlotIndex = 0;
	m_qwLastPingTick = 0;

	m_MessageFuncList[InternalMessage::x2n_message_version] = &CNSMessageHandler::_OnCheckVersion;
	m_MessageFuncList[InternalMessage::x2n_new_name] = &CNSMessageHandler::_OnNewName;
	m_MessageFuncList[InternalMessage::a2a_ping] = &CNSMessageHandler::_OnAllPing;

	return TRUE;
Exit0:
	return FALSE;
}

BOOL CNSMessageHandler::UnInit(void)
{
	for (INT32 i = 0; i < MAX_REMOTE_SERVER_COUNT; i++)
	{
		ISocketSession* pSession = m_SessionList[i];
		if (pSession == NULL)
			continue;

		pSession->Close();
	}

	if (m_pAcceptor)
	{
		m_pAcceptor->Close();
		if (m_pNet)
			m_pNet->DestroyAcceptor(m_pAcceptor);
	}


	if (m_pNet)
		g_DestroyNetInterface(m_nNetType, m_pNet);

	return TRUE;
}

void CNSMessageHandler::OnAccepted(ISocketAcceptor* pSocketAcceptor, ISocketSession* pSocketSession)
{
	REMOTE_SESSION* pSessionData = NULL;

	LOG_PROCESS_ERROR(m_nFreeSlotIndex < MAX_REMOTE_SERVER_COUNT);
	LOG_PROCESS_ERROR(m_SessionList[m_nFreeSlotIndex] == NULL);

	m_SessionList[m_nFreeSlotIndex] = pSocketSession;

	INF("Remote Connection Accepted, slot: %d", m_nFreeSlotIndex);

	pSessionData = new REMOTE_SESSION;
	LOG_PROCESS_ERROR(pSessionData);

	pSessionData->nMessageVersion = 0;

	pSessionData->nSessionIndex = m_nFreeSlotIndex;

	pSocketSession->SetUserData(pSessionData);

	for (INT32 i = 0; i < MAX_REMOTE_SERVER_COUNT; i++)
	{
		if (m_SessionList[i] == NULL)
		{
			m_nFreeSlotIndex = i;
			break;;
		}
	}

	return;
Exit0:
	if (pSessionData)
		delete pSessionData;
	return;
}

void CNSMessageHandler::OnConnected(ISocketSession* pSocketSession)
{

}

void CNSMessageHandler::OnRecv(ISocketSession* pSocketSession, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize)
{
	InternalMessage::MESSAGE_HEADER* pHeader = (InternalMessage::MESSAGE_HEADER*)pPacketBuffer;
	LOG_PROCESS_ERROR(pHeader);

	LOG_PROCESS_ERROR(pSocketSession);
	LOG_PROCESS_ERROR(m_MessageFuncList[pHeader->wMsg]);

	(this->*m_MessageFuncList[pHeader->wMsg])(pPacketBuffer, dwSize, pSocketSession);

	if (pPacketBuffer)
		m_PacketAllocator.Free(pPacketBuffer);

	return;
Exit0:
	if (pHeader)
		CRI("unknown internal message id %d size %d", pHeader->wMsg, dwSize);
	else
		CRI("unknown internal message with null pointer");
	if (pPacketBuffer)
		m_PacketAllocator.Free(pPacketBuffer);
	if (pSocketSession)
		pSocketSession->Close();

	return;
}

void CNSMessageHandler::OnDisconnected(ISocketSession* pSocketSession, BOOL bRemoteShutdown)
{
	REMOTE_SESSION* pSessionData = (REMOTE_SESSION*)pSocketSession->GetUserData();
	LOG_PROCESS_ERROR(pSessionData);

	LOG_PROCESS_ERROR(pSessionData->nSessionIndex < MAX_REMOTE_SERVER_COUNT);
	LOG_PROCESS_ERROR(m_SessionList[pSessionData->nSessionIndex] == pSocketSession);

	INF("Connection Closed, slot: %d", pSessionData->nSessionIndex);

	m_SessionList[pSessionData->nSessionIndex] = NULL;

Exit0:

	delete pSessionData;
	return;
}

void CNSMessageHandler::DoNewNameResult(INT32 nSessionID, UINT32 dwCliSessionID, INT32 nErrCode, INT32 eType, UINT32 dwNewID, const char* szNewName, const char* UserData)
{
	LOG_PROCESS_ERROR(nSessionID < MAX_REMOTE_SERVER_COUNT);
	LOG_PROCESS_ERROR(m_SessionList[nSessionID] != NULL);

	_DoNewNameResult(m_SessionList[nSessionID], dwCliSessionID, nErrCode, eType, dwNewID, szNewName, UserData);
Exit0:
	return;
}

void CNSMessageHandler::_OnCheckVersion(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession)
{
	INT32 nResult = 0;
	InternalMessage::X2N_MESSAGE_VERSION* pMsg = (InternalMessage::X2N_MESSAGE_VERSION*)pPacketBuffer;

	REMOTE_SESSION* pSessionData = (REMOTE_SESSION*)pSocketSession->GetUserData();

	LOG_PROCESS_ERROR(pSessionData->nSessionIndex < MAX_REMOTE_SERVER_COUNT);

	pSessionData->nMessageVersion = pMsg->byVersion;

	return;
Exit0:
	return;
}


void CNSMessageHandler::_OnNewName(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession)
{
	INT32 nResult = 0;
	InternalMessage::X2N_NEW_NAME* pMsg = (InternalMessage::X2N_NEW_NAME*)pPacketBuffer;

	REMOTE_SESSION* pSessionData = (REMOTE_SESSION*)pSocketSession->GetUserData();

	LOG_PROCESS_ERROR(pSessionData->nSessionIndex < MAX_REMOTE_SERVER_COUNT);

    nResult = CNameServer::GetInstance().AddNewData(pMsg->byType, pSessionData->nSessionIndex, pMsg->dwSessionID, pMsg->szName, pMsg->UserData);
	PROCESS_ERROR(nResult == errNsSuccess);

	return;
Exit0:
    _DoNewNameResult(pSocketSession, pMsg->dwSessionID, nResult, pMsg->byType, 0, pMsg->szName, pMsg->UserData);
	return;
}

void CNSMessageHandler::_DoNewNameResult(ISocketSession* pSocketSession, UINT32 dwCliSessionID, INT32 nErrCode, INT32 eType, UINT32 dwNewID, const char* szNewName, const char* UserData)
{
    INT32 nRetCode = 0;

    InternalMessage::N2X_NEW_NAME_RESULT* pMsg = (InternalMessage::N2X_NEW_NAME_RESULT*)m_PacketAllocator.Alloc(sizeof(InternalMessage::N2X_NEW_NAME_RESULT));
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = InternalMessage::n2x_new_name_result;
	pMsg->dwSessionID = dwCliSessionID;
	pMsg->byType = eType;
	pMsg->dwID = dwNewID;
	pMsg->nErrorCode = nErrCode;
	strncpy(pMsg->szName, szNewName, sizeof(pMsg->szName) - 1);
    memcpy(pMsg->UserData, UserData, USER_DATA_LEN);

	nRetCode = pSocketSession->Send((PACKET_BUFFER*)pMsg, sizeof(InternalMessage::N2X_NEW_NAME_RESULT), 0);
    LOG_PROCESS_ERROR(nRetCode == sizeof(InternalMessage::N2X_NEW_NAME_RESULT));

	return;
Exit0:
    if (pMsg)
        m_PacketAllocator.Free((PACKET_BUFFER*)pMsg);
    return;
}

BOOL CNSMessageHandler::MainLoop(void)
{
	UINT64 qwCurrentTick = GetTickCountEx();

	if (qwCurrentTick  > m_qwLastPingTick + g_NSConfig.net_config.ping_interval)
	{
		m_qwLastPingTick = qwCurrentTick;

		_DoAllPing();
	}

	return m_pNet->MainLoop();
}

void CNSMessageHandler::_OnAllPing(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession)
{
	REMOTE_SESSION* pSession = (REMOTE_SESSION*)pSocketSession->GetUserData();
	LOG_PROCESS_ERROR(pSession);

	LOG_PROCESS_ERROR(pSession->nMessageVersion == NS_MESSAGE_VERSION);

	pSession->qwTimer = GetTickCountEx() + g_NSConfig.net_config.ping_timeout;

	return;
Exit0:
	if (pSocketSession)
		pSocketSession->Close();
	return;

}

void CNSMessageHandler::_DoAllPing(void)
{
    INT32 nRetCode = 0;
    PACKET_BUFFER* pMsg = NULL;

	for (INT32 i = 0; i < MAX_REMOTE_SERVER_COUNT; i++)
	{
		if (m_SessionList[i] == NULL)
			continue;

		InternalMessage::A2A_PING* pMsg = (InternalMessage::A2A_PING*)(m_PacketAllocator.Alloc(sizeof(InternalMessage::A2A_PING)));
		if (pMsg)
		{
			pMsg->wMsg = InternalMessage::a2a_ping;

			nRetCode = m_SessionList[i]->Send((PACKET_BUFFER*)pMsg, sizeof(InternalMessage::A2A_PING), 0);

			if (!nRetCode)
				m_PacketAllocator.Free((PACKET_BUFFER*)pMsg);

			pMsg = NULL;
		}
	}
}
