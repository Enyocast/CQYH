#include "stdafx.h"
#include "intranet.h"


namespace Intranet
{

	CSocketAcceptor::CSocketAcceptor(void)
	{
		m_poShareMemAcceptor = NULL;
		m_poSimpleNetAcceptor = NULL;
		m_pUserData = NULL;
	}

	CSocketAcceptor::~CSocketAcceptor(void)
	{

	}

	BOOL CSocketAcceptor::Open(UINT32 dwAddr, UINT16 wPort)
	{
		INT32 nRetCode = 0;
		LOG_PROCESS_ERROR(m_poShareMemAcceptor);
		LOG_PROCESS_ERROR(m_poSimpleNetAcceptor);

		nRetCode = m_poShareMemAcceptor->Open(dwAddr, wPort);
		LOG_PROCESS_ERROR(nRetCode);

		nRetCode = m_poSimpleNetAcceptor->Open(dwAddr, wPort);
		LOG_PROCESS_ERROR(nRetCode);

		return TRUE;
Exit0:
		return FALSE;
	}

	BOOL CSocketAcceptor::Close(void)
	{
		INT32 nRetCode = 0;
		LOG_PROCESS_ERROR(m_poShareMemAcceptor);
		LOG_PROCESS_ERROR(m_poSimpleNetAcceptor);

		nRetCode = m_poShareMemAcceptor->Close();
		LOG_PROCESS_ERROR(nRetCode);

		nRetCode = m_poSimpleNetAcceptor->Close();
		LOG_PROCESS_ERROR(nRetCode);

		return TRUE;
Exit0:
		return FALSE;
	}

	void* CSocketAcceptor::GetUserData(void)
	{
		return m_pUserData;
	}

	void CSocketAcceptor::SetUserData(void* pUserData)
	{
		m_pUserData = pUserData;
	}

	CIntranetEventHandler::CIntranetEventHandler(void)
	{
		m_pUserEventHandler = NULL;
	}

	CIntranetEventHandler::~CIntranetEventHandler(void)
	{

	}

	void CIntranetEventHandler::OnAccepted(ISocketAcceptor* pSocketAcceptor, ISocketSession* pSocketSession)
	{
		m_pUserEventHandler->OnAccepted((CSocketAcceptor*)pSocketAcceptor->GetUserData(), pSocketSession);
	}

	void CIntranetEventHandler::OnConnected(ISocketSession* pSocketSession)
	{
		m_pUserEventHandler->OnConnected(pSocketSession);
	}

	void CIntranetEventHandler::OnRecv(ISocketSession* pSocketSession, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize)
	{
		m_pUserEventHandler->OnRecv(pSocketSession, pPacketBuffer, dwSize);
	}

	void CIntranetEventHandler::OnDisconnected(ISocketSession* pSocketSession, BOOL bPassiveShutdown)
	{
		m_pUserEventHandler->OnDisconnected(pSocketSession, bPassiveShutdown);
	}

	void CIntranetEventHandler::Init(INetEventHandler* pUserHandler)
	{
		m_pUserEventHandler = pUserHandler;
	}

	CNet::CNet(void)
	{
		m_poShareMemNet = NULL;
		m_poSimpleNet = NULL;
	}

	CNet::~CNet(void)
	{

	}

	BOOL CNet::Init(IPacketAllocator* pPacketAllocator, INetEventHandler* pNetEventHandler, void* pInitParam)
	{
		INT32 nRetCode = 0;
		INTRANET_INIT_PARAM* p = NULL;

		SHMEM_INIT_PARAM ShMemInitParam;
		SIMPLE_INIT_PARAM SimpleInitParam;

		LOG_PROCESS_ERROR(m_poShareMemNet == NULL);
		LOG_PROCESS_ERROR(m_poSimpleNet == NULL);

		m_Handler.Init(pNetEventHandler);

		p = (INTRANET_INIT_PARAM*)pInitParam;

		ShMemInitParam.nMaxAcceptor = p->nMaxAcceptor;
		ShMemInitParam.nMaxConnector = p->nMaxConnector;
		ShMemInitParam.nMaxSessionCount = p->nMaxSessionCount;
		ShMemInitParam.nRecvBufSize = p->nRecvBufSize;
		ShMemInitParam.nSendBufSize = p->nSendBufSize;
        ShMemInitParam.nDisconnectTimeout = p->nDisconnectTimeout;

		m_poShareMemNet = g_CreateNetInterface(netShareMemory, pPacketAllocator, &m_Handler, &ShMemInitParam);
		LOG_PROCESS_ERROR(m_poShareMemNet);

		SimpleInitParam.nMaxAcceptor = p->nMaxAcceptor;
		SimpleInitParam.nMaxConnector = p->nMaxConnector;
		SimpleInitParam.nMaxSessionCount = p->nMaxSessionCount;
		SimpleInitParam.nRecvBufSize = p->nRecvBufSize;
		SimpleInitParam.nSendBufSize = p->nSendBufSize;
		SimpleInitParam.nPacketBufferSize = p->nPacketBufferSize;

		m_poSimpleNet = g_CreateNetInterface(netSimple, pPacketAllocator, &m_Handler, &SimpleInitParam);
		LOG_PROCESS_ERROR(m_poSimpleNet);

		nRetCode = m_AcceptorPool.Init(p->nMaxAcceptor);
		LOG_PROCESS_ERROR(nRetCode);

		return TRUE;
Exit0:
		return FALSE;
	}

	BOOL CNet::UnInit(void)
	{
		INT32 nRetCode = 0;

		LOG_PROCESS_ERROR(m_poShareMemNet);
		LOG_PROCESS_ERROR(m_poSimpleNet);

		nRetCode = m_poShareMemNet->UnInit();
		LOG_PROCESS_ERROR(nRetCode);

		nRetCode = m_poSimpleNet->UnInit();
		LOG_PROCESS_ERROR(nRetCode);

		return TRUE;
Exit0:
		return FALSE;
	}

	ISocketAcceptor* CNet::CreateAcceptor(void)
	{
		ISocketAcceptor* poShareMemAcceptor = NULL;
		ISocketAcceptor* poSimpleNetAcceptor = NULL;
		CSocketAcceptor* poRet = NULL;

		LOG_PROCESS_ERROR(m_poShareMemNet);
		LOG_PROCESS_ERROR(m_poSimpleNet);

		poShareMemAcceptor = m_poShareMemNet->CreateAcceptor();
		LOG_PROCESS_ERROR(poShareMemAcceptor);

		poSimpleNetAcceptor = m_poSimpleNet->CreateAcceptor();
		LOG_PROCESS_ERROR(poSimpleNetAcceptor);

		poRet = m_AcceptorPool.New();
		LOG_PROCESS_ERROR(poRet);

		poRet->Init(poShareMemAcceptor, poSimpleNetAcceptor);

		return poRet;
Exit0:
		m_poShareMemNet->DestroyAcceptor(poShareMemAcceptor);
		m_poSimpleNet->DestroyAcceptor(poSimpleNetAcceptor);

		SAFE_DELETE(poRet);

		return NULL;
	}

	BOOL CNet::DestroyAcceptor(ISocketAcceptor* pSocket)
	{
		INT32 nRetCode = 0;

		CSocketAcceptor* poAcc = (CSocketAcceptor*)pSocket;

		LOG_PROCESS_ERROR(m_poShareMemNet);
		LOG_PROCESS_ERROR(m_poSimpleNet);

		nRetCode = poAcc->Close();
		LOG_CHECK_ERROR(nRetCode);

		nRetCode = m_poShareMemNet->DestroyAcceptor(poAcc->GetShareMemAcceptor());
		LOG_CHECK_ERROR(nRetCode);

		nRetCode = m_poSimpleNet->DestroyAcceptor(poAcc->GetSimpleNetAcceptor());
		LOG_CHECK_ERROR(nRetCode);

		m_AcceptorPool.Delete(poAcc);

		return TRUE;
Exit0:
		return FALSE;
	}

	ISocketSession* CNet::Connect(UINT32 dwAddr, UINT16 wPort)
	{
		INT32 nRetCode = 0;

		ISocketSession* poSession = NULL;

		LOG_PROCESS_ERROR(m_poShareMemNet);
		LOG_PROCESS_ERROR(m_poSimpleNet);

		poSession = m_poShareMemNet->Connect(dwAddr, wPort);
		if(poSession != NULL)
			return poSession;

		poSession = m_poSimpleNet->Connect(dwAddr, wPort);

		return poSession;
Exit0:
		return NULL;
	}

	BOOL CNet::MainLoop(void)
	{
		INT32 nRetCode = 0;

		LOG_PROCESS_ERROR(m_poShareMemNet);
		LOG_PROCESS_ERROR(m_poSimpleNet);

		nRetCode = m_poShareMemNet->MainLoop();
		LOG_PROCESS_ERROR(nRetCode);

		nRetCode = m_poSimpleNet->MainLoop();
		LOG_PROCESS_ERROR(nRetCode);

        return TRUE;
Exit0:
		return FALSE;
	}

	INT64 CNet::PrintMemoryStat(void)
	{
		return 0;
	}
};
