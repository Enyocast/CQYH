#include "stdafx.h"

#if defined(WIN32)

#include "iocp.h"

#include <intrin.h>
#include "time_ex.h"

#include "external_message_header.h"

using namespace ExternalMessage;

#define MAX_LISTEN_COUNT                (256) 
#define SHUTDOWN_TIME_OUT               (4 * 1000LL)
#define MAX_ACCEPT_SESSION_COUNT        (64)
#define DELAY_SEND_THRESHOLD            (1)
#define DELAY_SEND_DURATION             (16LL)

//#ifndef _ROBOT
//	#define MAX_OPERATION_PER_LOOP          (64)
//#else
//	#define MAX_OPERATION_PER_LOOP          (1024)
//#endif

#define MAX_MAIN_THREAD_PROCESS_TIME    (500)

namespace IOCP
{ 
    INT32 CSocketSession::Send(PACKET_BUFFER* pPacketBuffer, INT32 nSize, INT32 nOffset)
    {
        INT32 nRetCode = 0;
        INT32 nSendDataSize = 0;
		INT32 SEND_LOOP_BUFFER_SIZE = 0;

		LOG_PROCESS_ERROR(pPacketBuffer);
        LOG_PROCESS_ERROR(nSize > 0);

		PROCESS_ERROR(m_eState == ssNormal);
#if defined(_DEBUG)
        LOG_PROCESS_ERROR(m_pPacketAllocator->IsAllocated(pPacketBuffer));
#endif	//_DEBUG

		LOG_PROCESS_ERROR(m_pNet);
		SEND_LOOP_BUFFER_SIZE = m_pNet->GetInitParam().nSendLoopBufferSize;

        nSendDataSize = m_SendIndex.Rear - m_SendIndex.Head;
        nSendDataSize = nSendDataSize < 0 ? SEND_LOOP_BUFFER_SIZE + nSendDataSize : nSendDataSize;
        LOG_PROCESS_ERROR(nSendDataSize + nSize < SEND_LOOP_BUFFER_SIZE);

        if (m_SendIndex.Head <= m_SendIndex.Rear)
        {
            if (m_SendIndex.Rear + nSize < SEND_LOOP_BUFFER_SIZE)
            {
                memcpy(m_pSendLoopBuffer + m_SendIndex.Rear, (char*)pPacketBuffer + nOffset, nSize);
            }
            else
            {
                INT32 nPartSize = SEND_LOOP_BUFFER_SIZE - m_SendIndex.Rear;

                memcpy(m_pSendLoopBuffer + m_SendIndex.Rear, (char*)pPacketBuffer + nOffset, nPartSize);
                memcpy(m_pSendLoopBuffer, (char*)pPacketBuffer + nOffset + nPartSize, nSize - nPartSize);
            }
        }
        else
        {
            memcpy(m_pSendLoopBuffer + m_SendIndex.Rear, (char*)pPacketBuffer + nOffset, nSize);
        }

        m_SendIndex.Rear = (m_SendIndex.Rear + nSize) % SEND_LOOP_BUFFER_SIZE;

        if (!m_bSending)
        {
            nSendDataSize = m_SendIndex.Rear - m_SendIndex.Head;
            nSendDataSize = nSendDataSize < 0 ? SEND_LOOP_BUFFER_SIZE + nSendDataSize : nSendDataSize;
			if (nSendDataSize >= DELAY_SEND_THRESHOLD)
            {
				nRetCode = StartSend();
                LOG_PROCESS_ERROR(nRetCode);

				m_qwSendTimer = GetTickCountEx() + DELAY_SEND_DURATION;
			}
        }

        m_pPacketAllocator->Free(pPacketBuffer);

        return nSize;
Exit0:
		CRI("session ptr <%08X> failed to send message", (INT32)this);
        if (m_eState == ssNormal)
            Close();

        return 0;
    }

    void* CSocketSession::GetUserData(void)
    {
        return m_pUserData;
    }

    void CSocketSession::SetUserData(void* pUserData)
    {
        m_pUserData = pUserData;
    }

    BOOL CSocketSession::GetAddress(UINT32& dwAddr, UINT16& wPort)
    {
        INT32 nRetCode;
        SOCKADDR_IN stSockAddr;
        INT32 nSockSize = sizeof(stSockAddr);

        LOG_PROCESS_ERROR(m_pNet != NULL);
        LOG_PROCESS_ERROR(m_Socket != INVALID_SOCKET);
        LOG_PROCESS_ERROR(m_eState == ssNormal);

        nRetCode = getsockname(m_Socket, ((SOCKADDR*)&stSockAddr), &nSockSize);
        LOG_PROCESS_ERROR(nRetCode == 0);

        dwAddr = stSockAddr.sin_addr.s_addr;
        wPort = ntohs(stSockAddr.sin_port);

        return TRUE;
Exit0:
        return FALSE;
    }

    BOOL CSocketSession::GetRemoteAddress(UINT32& dwRemoteAddr, UINT16& wRemotePort)
    {
        INT32 nRetCode;
        SOCKADDR_IN stSockAddr;
        INT32 nSockSize = sizeof(stSockAddr);

        LOG_PROCESS_ERROR(m_pNet != NULL);
        LOG_PROCESS_ERROR(m_Socket != INVALID_SOCKET);
        LOG_PROCESS_ERROR(m_eState == ssNormal || m_eState == ssDisconnecting);

        nRetCode = getpeername(m_Socket, ((SOCKADDR*)&stSockAddr), &nSockSize);
        LOG_PROCESS_ERROR(nRetCode == 0);

        dwRemoteAddr = stSockAddr.sin_addr.s_addr;
        wRemotePort = ntohs(stSockAddr.sin_port);
        return TRUE;
Exit0:
        return FALSE;

    }

    BOOL CSocketSession::Close(void)
    {
        switch (m_eState)
        {
        case ssConnecting:
            {
                SetState(ssDisconnecting);
            }
            break;
        case ssNormal:
            {
                SetState(ssDisconnecting);
                if (m_SendIndex.Head == m_SendIndex.Rear)
                {
                    shutdown(m_Socket, SD_SEND);
                }
                else
                {
                    TrySend(0xFFFFFFFFFFFFFFFF);
                }
                m_qwShutdownTimer = GetTickCountEx() + SHUTDOWN_TIME_OUT;
            }
            break;
        case ssDisconnecting:
            break;
        case ssDisconnected:
        case ssAccepted:
        default:
            CRI("error session state : %d", m_eState);
            LOG_PROCESS_ERROR(FALSE);
        }

        return TRUE;
Exit0:
        return FALSE;
    }

    INT32 CSocketSession::Recv(void)
    {
        MESSAGE_HEADER* pHeader = NULL;
        INT32 nMessageSize = 0;
        INT32 nSize = 0;

		UINT16 wMsgID = 0;

		INT32 RECV_LOOP_BUFFER_SIZE = 0;
		LOG_PROCESS_ERROR(m_pNet);
		RECV_LOOP_BUFFER_SIZE = m_pNet->GetInitParam().nRecvLoopBufferSize;

        INT32 nRecvDataSize = m_RecvIndex.Rear - m_RecvIndex.Head;
        PACKET_BUFFER* pPacketBuffer = NULL;
        static UINT32 dwAllowState = ssNormal | ssDisconnecting;

        PROCESS_SUCCESS(m_RecvIndex.Rear == m_RecvIndex.Head);
        PROCESS_SUCCESS((m_eState | dwAllowState) != dwAllowState);
        
        nRecvDataSize = nRecvDataSize < 0 ? RECV_LOOP_BUFFER_SIZE + nRecvDataSize : nRecvDataSize;
		PROCESS_SUCCESS(nRecvDataSize < sizeof(MESSAGE_HEADER));

		wMsgID = *(UINT8*)(m_pRecvLoopBuffer + m_RecvIndex.Head);

		wMsgID |= *((UINT8*)(m_pRecvLoopBuffer + (m_RecvIndex.Head + 1) % RECV_LOOP_BUFFER_SIZE)) << 8;
		LOG_PROCESS_ERROR(wMsgID < max_message_count);

        nSize = m_pNet->GetInitParam().pnMessageSizeList[wMsgID];
        if (nSize == flex_message_size)
        {
            UINT16 wTempSize = 0;
            PROCESS_SUCCESS(nRecvDataSize < sizeof(FLEX_MESSAGE_HEADER));

            wTempSize = *((UINT8*)(m_pRecvLoopBuffer + (m_RecvIndex.Head + sizeof(MESSAGE_HEADER)) % RECV_LOOP_BUFFER_SIZE));
            nSize = wTempSize;
            
            wTempSize = *((UINT8*)(m_pRecvLoopBuffer + (m_RecvIndex.Head + sizeof(MESSAGE_HEADER) + 1) % RECV_LOOP_BUFFER_SIZE));
            nSize += wTempSize << 8;
        }
        LOG_PROCESS_ERROR(nSize > 0);
        PROCESS_SUCCESS(nRecvDataSize < nSize);
        
        //recv ok
        nMessageSize = nSize;

        pPacketBuffer = m_pNet->GetPacketAllocator()->Alloc(nMessageSize);
        LOG_PROCESS_ERROR(pPacketBuffer);

        if (m_RecvIndex.Head < m_RecvIndex.Rear)
        {
            memcpy(pPacketBuffer, m_pRecvLoopBuffer + m_RecvIndex.Head, nMessageSize);
        }
        else
        {
            if (m_RecvIndex.Head + nMessageSize <= RECV_LOOP_BUFFER_SIZE)
            {
                memcpy(pPacketBuffer, m_pRecvLoopBuffer + m_RecvIndex.Head, nMessageSize);
            }
            else
            {
                INT32 nPartSize = RECV_LOOP_BUFFER_SIZE - m_RecvIndex.Head;
                memcpy(pPacketBuffer, m_pRecvLoopBuffer + m_RecvIndex.Head, nPartSize);
                memcpy(pPacketBuffer + nPartSize, m_pRecvLoopBuffer, nMessageSize - nPartSize);
            }
        }
        m_RecvIndex.Head = (m_RecvIndex.Head + nMessageSize) % RECV_LOOP_BUFFER_SIZE;

        m_pNet->GetEventHandler()->OnRecv(this, pPacketBuffer, nMessageSize);

Exit1:
        return nMessageSize;
Exit0:
		CRI("session ptr <%08X> detected error while receiving client message", (INT32)this);
        if (pPacketBuffer)
            m_pNet->GetPacketAllocator()->Free(pPacketBuffer);
        Close();
        return 0;
    }

    CSocketSession::CSocketSession()
    {
        m_eState = ssInvalid;
        m_pNet = NULL;
        m_pPacketAllocator = NULL;
        m_Socket = INVALID_SOCKET;
        m_pSocketAcceptor = NULL;

        m_SendIndex.Head = m_SendIndex.Rear = m_RecvIndex.Head = m_RecvIndex.Rear = 0;

        memset(&m_SendIoData, 0, sizeof(m_SendIoData));
        memset(&m_RecvIoData, 0, sizeof(m_RecvIoData));
        memset(&m_CommonIoData, 0, sizeof(m_CommonIoData));

        m_ListNode.pNext = m_ListNode.pPrev = NULL;
        m_pUserData = NULL;
        m_qwShutdownTimer = 0;
        m_qwSendTimer = 0;
		m_bSending = FALSE;
		m_bRecving = FALSE;

		m_pSendLoopBuffer = NULL;
		m_pRecvLoopBuffer = NULL;
    }

    CSocketSession::~CSocketSession()
    {
        UnInit();
    }

    BOOL CSocketSession::Init(CNet* pNet, CSocketAcceptor* pSocketAcceptor)
    {
        INT32 nRetCode = 0;
		INT32 nOption = 0;

        m_SendIndex.Head = m_SendIndex.Rear = m_RecvIndex.Head = m_RecvIndex.Rear = 0;

        m_Socket = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);
        LOG_PROCESS_ERROR(m_Socket != INVALID_SOCKET);

        nOption = 16 * 1024;
        nRetCode = setsockopt(m_Socket, SOL_SOCKET, SO_SNDBUF, (char*)&nOption, sizeof(nOption));
        LOG_PROCESS_ERROR(nRetCode != SOCKET_ERROR);

        nOption = 16 * 1024;
        nRetCode = setsockopt(m_Socket, SOL_SOCKET, SO_RCVBUF, (char*)&nOption, sizeof(nOption));
        LOG_PROCESS_ERROR(nRetCode != SOCKET_ERROR);

		m_pNet = pNet;
		LOG_PROCESS_ERROR(m_pNet);

        m_pSocketAcceptor = pSocketAcceptor;
        m_ListNode.pNext = m_ListNode.pPrev = NULL;

        m_pPacketAllocator = pNet->GetPacketAllocator();
        LOG_PROCESS_ERROR(m_pPacketAllocator);

        m_SendIoData.nIoOperation = ioSend;
        m_RecvIoData.nIoOperation = ioRecv;
        m_CommonIoData.nIoOperation = ioAccept;
        m_SendIoData.pSession = this;
        m_RecvIoData.pSession = this;
        m_CommonIoData.pSession = this;
        m_pUserData = NULL;
        m_qwShutdownTimer = 0xFFFFFFFFFFFFFFFF;
        m_qwSendTimer = 0;
		m_bSending = FALSE;
		m_bRecving = FALSE;
		m_eState = ssDisconnected;

		m_pSendLoopBuffer = new char[m_pNet->GetInitParam().nSendLoopBufferSize];
		LOG_PROCESS_ERROR(m_pSendLoopBuffer);

		m_pRecvLoopBuffer = new char[m_pNet->GetInitParam().nRecvLoopBufferSize];
		LOG_PROCESS_ERROR(m_pRecvLoopBuffer);

        return TRUE;
Exit0:

        return FALSE;
    }

    BOOL CSocketSession::UnInit(void)
    {
        if (m_Socket != INVALID_SOCKET)
        {
            closesocket(m_Socket);
            m_Socket = INVALID_SOCKET;
        }

        LOG_CHECK_ERROR(!m_bSending);
		LOG_CHECK_ERROR(!m_bRecving);

		SAFE_DELETE_ARRAY(m_pSendLoopBuffer);
		SAFE_DELETE_ARRAY(m_pRecvLoopBuffer);

        m_eState = ssInvalid;
        m_pSocketAcceptor = NULL;
        m_pNet = NULL;
        m_ListNode.pNext = m_ListNode.pPrev = NULL;

        return TRUE;
    }

    BOOL CSocketSession::CompleteSend(INT32 nIoSize)
    {
        INT32 nRetCode = 0;
		INT32 nWSALastError = 0;
		INT32 nSendDataSize = 0;

		INT32 SEND_LOOP_BUFFER_SIZE = 0;
		LOG_PROCESS_ERROR(m_pNet);
		SEND_LOOP_BUFFER_SIZE = m_pNet->GetInitParam().nSendLoopBufferSize;

        LOG_PROCESS_ERROR(m_eState == ssNormal || m_eState == ssDisconnecting);

        m_SendIndex.Head = (m_SendIndex.Head + nIoSize) % SEND_LOOP_BUFFER_SIZE;

		nSendDataSize = m_SendIndex.Rear - m_SendIndex.Head;
		nSendDataSize = nSendDataSize < 0 ? SEND_LOOP_BUFFER_SIZE + nSendDataSize : nSendDataSize;

		if (nSendDataSize >= DELAY_SEND_THRESHOLD || nIoSize == 0 ||
			(nSendDataSize > 0 && m_eState == ssDisconnecting))
		{
			LOG_PROCESS_ERROR(nSendDataSize > 0);

			m_SendIoData.nIoOperation = ioSend;
			m_SendIoData.wsabuf.buf = m_pSendLoopBuffer + m_SendIndex.Head;
			if (m_SendIndex.Head <= m_SendIndex.Rear)
			{
				m_SendIoData.wsabuf.len = m_SendIndex.Rear - m_SendIndex.Head;
			}
			else
			{
				m_SendIoData.wsabuf.len = SEND_LOOP_BUFFER_SIZE - m_SendIndex.Head;
			}

			nRetCode = WSASend(m_Socket, &(m_SendIoData.wsabuf), 1, NULL, 0, &m_SendIoData, NULL);
			nWSALastError = WSAGetLastError();
			LOG_PROCESS_ERROR(nRetCode != SOCKET_ERROR || nWSALastError == ERROR_IO_PENDING);
		}
		else if (m_eState == ssDisconnecting)
        {
			StopSend();
            shutdown(m_Socket, SD_SEND);
        }
		else
		{
			StopSend();
		}

        return TRUE;
Exit0:
        CRI("failed to complete send, session %08x, error code %d", this, WSAGetLastError());

        return FALSE;
    }

    BOOL CSocketSession::CompleteRecv(INT32 nIoSize)
    {
        INT32 nRetCode = 0;
		DWORD dwFlag = 0;

		INT32 RECV_LOOP_BUFFER_SIZE = 0;
		LOG_PROCESS_ERROR(m_pNet);
		RECV_LOOP_BUFFER_SIZE = m_pNet->GetInitParam().nRecvLoopBufferSize;

        LOG_PROCESS_ERROR(m_eState == ssNormal || m_eState == ssAccepted || m_eState == ssDisconnecting);

        INT32 nNewRecvRear = (m_RecvIndex.Rear + nIoSize) % RECV_LOOP_BUFFER_SIZE;
        m_RecvIndex.Rear = nNewRecvRear;

        INT32 nRecvDataSize = m_RecvIndex.Rear - m_RecvIndex.Head;
        nRecvDataSize = nRecvDataSize < 0 ? RECV_LOOP_BUFFER_SIZE + nRecvDataSize : nRecvDataSize;
        LOG_PROCESS_ERROR(nRecvDataSize + 1 < RECV_LOOP_BUFFER_SIZE);

        m_RecvIoData.nIoOperation = ioRecv;
        m_RecvIoData.wsabuf.buf = m_pRecvLoopBuffer + m_RecvIndex.Rear;
        if (m_RecvIndex.Head <= m_RecvIndex.Rear)
            m_RecvIoData.wsabuf.len = RECV_LOOP_BUFFER_SIZE - m_RecvIndex.Rear;
        else
            m_RecvIoData.wsabuf.len = m_RecvIndex.Head - m_RecvIndex.Rear - 1;
		if (m_RecvIoData.wsabuf.len > 2048)
			m_RecvIoData.wsabuf.len = 2048;

        nRetCode = WSARecv(m_Socket, &m_RecvIoData.wsabuf, 1, (LPDWORD)&nIoSize, &dwFlag, &m_RecvIoData, NULL);
        LOG_PROCESS_ERROR(nRetCode != SOCKET_ERROR || WSAGetLastError() == ERROR_IO_PENDING);

        return TRUE;
Exit0:
        CRI("failed to complete recv, session %08x, error code %d", this, WSAGetLastError());

        return FALSE;
    }

    BOOL CSocketSession::Shutdown(void)
    {
        closesocket(m_Socket);
        m_Socket = INVALID_SOCKET;

        return TRUE;
    }

    BOOL CSocketSession::CheckCleanup(void)
    {
        if (!m_bSending && !m_bRecving)
            return TRUE;
        else
            return FALSE;
    }

    void CSocketSession::TrySend(UINT64 qwCurrentTick)
    {
		INT32 nRetCode = 0;
		INT32 SEND_LOOP_BUFFER_SIZE = 0;

		LOG_PROCESS_ERROR(m_pNet);
		SEND_LOOP_BUFFER_SIZE = m_pNet->GetInitParam().nSendLoopBufferSize;

        if (!m_bSending && (m_qwSendTimer < qwCurrentTick))
        {
			INT32 nSendDataSize = 0;

			nSendDataSize = m_SendIndex.Rear - m_SendIndex.Head;
			nSendDataSize = nSendDataSize < 0 ? SEND_LOOP_BUFFER_SIZE + nSendDataSize : nSendDataSize;
			if (nSendDataSize > 0)
			{
				m_bSending = TRUE;
				nRetCode = PostQueuedCompletionStatus(m_pNet->GetIOCPHandle(), 0, (ULONG_PTR)this, &m_SendIoData);
				if (!nRetCode)
					m_bSending = FALSE;
				LOG_PROCESS_ERROR(nRetCode);

				m_qwSendTimer = GetTickCountEx() + DELAY_SEND_DURATION;
			}
        }

Exit0:
        return;
    }

	inline BOOL CSocketSession::StartSend(void)
	{
		INT32 nRetCode = 0;

		m_bSending = TRUE;

		nRetCode = PostQueuedCompletionStatus(m_pNet->GetIOCPHandle(), 0, (ULONG_PTR)this, &m_SendIoData);
		LOG_PROCESS_ERROR(nRetCode);

		return TRUE;
Exit0:
		m_bSending = FALSE;
		return FALSE;
	}

	inline BOOL CSocketSession::StopSend(void)
	{
		m_bSending = FALSE;
		return TRUE;
	}

	inline BOOL CSocketSession::StartRecv(void)
	{
		INT32 nRetCode = 0;

		m_bRecving = TRUE;

		nRetCode = CompleteRecv(0);
		LOG_PROCESS_ERROR(nRetCode);

		return TRUE;
Exit0:
		m_bRecving = FALSE;
		return FALSE;
	}

	inline BOOL CSocketSession::StopRecv(void)
	{
		m_bRecving = FALSE;
		return TRUE;
	}

    /************************************************************************/
    BOOL CSocketAcceptor::Open(UINT32 dwAddr, UINT16 wPort)
    {
        INT32 nRetCode = 0;
        INT32 nOption = 0;
        HANDLE hIOCP = NULL;
        struct sockaddr_in Address = {0};
        struct hostent* pHost = NULL;
        GUID AcceptExGuid = WSAID_ACCEPTEX;

        LOG_PROCESS_ERROR(dwAddr != INADDR_NONE);
        LOG_PROCESS_ERROR(m_pNet);

        m_sockListen = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);
        LOG_PROCESS_ERROR(m_sockListen != INVALID_SOCKET);

        Address.sin_family = AF_INET;
        Address.sin_addr.s_addr = dwAddr;
        Address.sin_port = htons(wPort);

        nRetCode = bind(m_sockListen, (sockaddr*)&Address, sizeof(Address));
        LOG_PROCESS_ERROR(nRetCode != SOCKET_ERROR);

        nOption = 1;
        nRetCode = setsockopt(m_sockListen, IPPROTO_TCP, TCP_NODELAY, (char*)&nOption, sizeof(nOption));
        LOG_PROCESS_ERROR(nRetCode != SOCKET_ERROR);

        nRetCode = listen(m_sockListen, MAX_LISTEN_COUNT);
        LOG_PROCESS_ERROR(nRetCode != SOCKET_ERROR);

        hIOCP = CreateIoCompletionPort((HANDLE)m_sockListen, m_pNet->GetIOCPHandle(), (DWORD_PTR)this, 0);
        LOG_PROCESS_ERROR(hIOCP == m_pNet->GetIOCPHandle());

        nRetCode = WSAIoctl(m_sockListen, SIO_GET_EXTENSION_FUNCTION_POINTER,
            &AcceptExGuid, sizeof(AcceptExGuid), &m_fnAcceptEx, sizeof(m_fnAcceptEx),
            (LPDWORD)&nOption, NULL, NULL);
        LOG_PROCESS_ERROR(nRetCode != SOCKET_ERROR);

        for (INT32 nIndex = 0; nIndex < MAX_ACCEPT_SESSION_COUNT; nIndex++)
        {
            nRetCode = CreateAcceptSocket();
            LOG_PROCESS_ERROR(nRetCode);
        }

        return TRUE;
Exit0:
        CRI("Failed to open socket, error code %d", WSAGetLastError());

        nRetCode = UnInit();
        LOG_CHECK_ERROR(nRetCode);

        return FALSE;
    }

    BOOL CSocketAcceptor::Close(void)
    {
        if (m_sockListen != INVALID_SOCKET)
        {
            SOCKET sockListen = m_sockListen;
            m_sockListen = INVALID_SOCKET;
            closesocket(sockListen);
        }

        while (_InterlockedAnd((LONG*)&m_nAcceptSocketCount, 0xFFFFFFFF))
        {
            Sleep(1);
        }

        return TRUE;
    }

    CSocketAcceptor::CSocketAcceptor()
    {
        m_sockListen = INVALID_SOCKET;
        m_nAcceptSocketCount = 0;
		m_pUserData = NULL;
        m_pNet = NULL;
        m_fnAcceptEx = NULL;
        m_nThreadCount = 0;
    }

    CSocketAcceptor::~CSocketAcceptor()
    {
        UnInit();
    }

    BOOL CSocketAcceptor::Init(CNet* pNet)
    {
        INT32 nRetCode = 0;

        LOG_PROCESS_ERROR(pNet);

        m_pNet = pNet;
        m_nAcceptSocketCount = 0;
		m_pUserData = NULL;

        m_nThreadCount = pNet->GetInitParam().nThreadCount;
        LOG_PROCESS_ERROR(m_nThreadCount > 0);

        return TRUE;
Exit0:
        CRI("Failed to initialize socket acceptor, error code %d", WSAGetLastError());

        nRetCode = UnInit();
        LOG_CHECK_ERROR(nRetCode);

        return FALSE;
    }

    BOOL CSocketAcceptor::UnInit(void)
    {
        Close();

        return TRUE;
    }

    inline BOOL CSocketAcceptor::OnAccept(BOOL bOperateResult, CSocketSession* pSocketSession)
    {
        INT32 nRetCode = 0;
        INT32 nOption;
        HANDLE hIOCP;

        PROCESS_ERROR(bOperateResult);
        LOG_PROCESS_ERROR(pSocketSession);

        nRetCode = setsockopt(pSocketSession->GetSocket(), SOL_SOCKET, SO_UPDATE_ACCEPT_CONTEXT,
            (char *)&m_sockListen, sizeof(m_sockListen));
        LOG_PROCESS_ERROR(nRetCode != SOCKET_ERROR);

        hIOCP = CreateIoCompletionPort((HANDLE)pSocketSession->GetSocket(), m_pNet->GetIOCPHandle(), (DWORD_PTR)pSocketSession, 0);
        LOG_PROCESS_ERROR(hIOCP == m_pNet->GetIOCPHandle());

        nRetCode = m_pNet->PushSessionToMainThread(pSocketSession);
        LOG_PROCESS_ERROR(nRetCode);

        InterlockedDecrement((LONG*)&m_nAcceptSocketCount);

        return TRUE;
Exit0:
        if (m_sockListen != INVALID_SOCKET)
            CRI("Failed to accept session %08x, %08x, error code %d", pSocketSession, pSocketSession->GetSocket(), WSAGetLastError());

        pSocketSession->UnInit();
        m_pNet->DestroySession(pSocketSession);

        InterlockedDecrement((LONG*)&m_nAcceptSocketCount);

        return FALSE;
    }

    BOOL CSocketAcceptor::CreateAcceptSocket(void)
    {
        INT32 nRetCode = 0;
        DWORD dwSize;
        CSocketSession* pSession = NULL;
        
        nRetCode = InterlockedIncrement((LONG volatile*)&m_nAcceptSocketCount);
        PROCESS_ERROR(nRetCode <= MAX_ACCEPT_SESSION_COUNT);

        PROCESS_ERROR(_InterlockedAnd((LONG*)&m_sockListen, 0xFFFFFFFF) != INVALID_SOCKET);
        LOG_PROCESS_ERROR(m_pNet);
        LOG_PROCESS_ERROR(m_fnAcceptEx);

        pSession = m_pNet->CreateSession();
        PROCESS_ERROR(pSession);

        nRetCode = pSession->Init(m_pNet, this);
        LOG_PROCESS_ERROR(nRetCode);

        pSession->SetState(ssAccepted);

        IO_DATA* pIoData = pSession->GetCommonIoData();
        LOG_PROCESS_ERROR(pIoData);
        
        pIoData->nIoOperation = ioAccept;

        nRetCode = m_fnAcceptEx(m_sockListen, pSession->GetSocket(), pSession->GetAcceptBuffer(),
            0, sizeof(sockaddr_in) + 16, sizeof(sockaddr_in) + 16,
            &dwSize, pIoData);
        LOG_PROCESS_ERROR(nRetCode != SOCKET_ERROR || WSAGetLastError() == ERROR_IO_PENDING);

        return TRUE;
Exit0:
        InterlockedDecrement((LONG*)&m_nAcceptSocketCount);

//        CRI("Failed to create accept session, error code : %d", WSAGetLastError());

        if (pSession && m_pNet)
        {
            pSession->UnInit();
            m_pNet->DestroySession(pSession);
        }

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

    /************************************************************************/
    ISocketAcceptor* CNet::CreateAcceptor(void)
    {
        CSocketAcceptor* pResult = NULL;
        INT32 nRetCode = 0;

        pResult = new CSocketAcceptor;
        LOG_PROCESS_ERROR(pResult);

        nRetCode = pResult->Init(this);
        LOG_PROCESS_ERROR(nRetCode);

        m_AcceptorList.push_back(pResult);

        return pResult;
Exit0:
        SAFE_DELETE(pResult);

        return NULL;
    }

    BOOL CNet::DestroyAcceptor(ISocketAcceptor* pSocketAcceptor)
    {
        INT32 nRetCode = 0;

        LOG_PROCESS_ERROR(pSocketAcceptor);

        for (ACCEPTOR_LIST::iterator it = m_AcceptorList.begin();
            it != m_AcceptorList.end(); ++it)
        {
            if (*it == pSocketAcceptor)
            {
                m_AcceptorList.erase(it);
                break;
            }
        }

        nRetCode = ((CSocketAcceptor*)pSocketAcceptor)->UnInit();
        LOG_CHECK_ERROR(nRetCode);

        SAFE_DELETE(pSocketAcceptor);

        return TRUE;
Exit0:
        return FALSE;
    }

    ISocketSession* CNet::Connect(UINT32 dwAddr, UINT16 wPort)
    {
        CSocketSession* pResult = NULL;
        INT32 nRetCode = 0;
        struct sockaddr_in Address = {0};
        HANDLE hIOCP;
		INT32 nOption = 1;
		INT32 nZero = 0;
        GUID ConnectExGuid = WSAID_CONNECTEX;

        pResult = CreateSession();
        LOG_PROCESS_ERROR(pResult);

        nRetCode = pResult->Init(this, NULL);
        LOG_PROCESS_ERROR(nRetCode);

        hIOCP = CreateIoCompletionPort((HANDLE)pResult->GetSocket(), m_hIOCP, (DWORD_PTR)pResult, 0);
        LOG_PROCESS_ERROR(hIOCP == m_hIOCP);

        Address.sin_family = AF_INET;
        Address.sin_addr.s_addr = INADDR_ANY;
        Address.sin_port = 0;

        nRetCode = bind(pResult->GetSocket(), (sockaddr*)&Address, sizeof(Address));
        LOG_PROCESS_ERROR(nRetCode != SOCKET_ERROR);

        if (m_fnConnectEx == NULL)
        {
            nRetCode = WSAIoctl(pResult->GetSocket(), SIO_GET_EXTENSION_FUNCTION_POINTER,
                &ConnectExGuid, sizeof(ConnectExGuid), &m_fnConnectEx, sizeof(m_fnConnectEx),
                (LPDWORD)&nZero, NULL, NULL);
            LOG_PROCESS_ERROR(nRetCode != SOCKET_ERROR);
        }

        Address.sin_family = AF_INET;
        Address.sin_addr.s_addr = dwAddr;
        Address.sin_port = htons(wPort);

		nRetCode = setsockopt(pResult->GetSocket(), IPPROTO_TCP, TCP_NODELAY, (char*)&nOption, sizeof(nOption));
		LOG_PROCESS_ERROR(nRetCode != SOCKET_ERROR);

        IO_DATA* pIoData = pResult->GetCommonIoData();
        LOG_PROCESS_ERROR(pIoData);

        pResult->SetState(ssConnecting);
        m_SessionList.PushRear(&pResult->GetListNode());

        pIoData->nIoOperation = ioConnect;

        nRetCode = m_fnConnectEx(pResult->GetSocket(), (sockaddr*)&Address, sizeof(Address), NULL, 0, NULL, pIoData);
        LOG_PROCESS_ERROR(nRetCode != SOCKET_ERROR || WSAGetLastError() == ERROR_IO_PENDING);

        return pResult;
Exit0:
        CRI("Failed to connect to server, error code %d", WSAGetLastError());

        if (pResult)
        {
            pResult->UnInit();
            DestroySession(pResult);
        }

        return NULL;
    }

    BOOL CNet::MainLoop(void)
    {
        INT32 nRetCode = 0;
        CSocketSession* pSocketSession = NULL;
        UINT64 qwStartTick = GetTickCountEx();
        UINT64 qwCurrentTick = GetTickCountEx();

		INT32 SEND_LOOP_BUFFER_SIZE = m_InitParam.nSendLoopBufferSize;

        LOG_PROCESS_ERROR(m_pEventHandler);

        // try to create accept socket
        for (ACCEPTOR_LIST::iterator it = m_AcceptorList.begin();
            it != m_AcceptorList.end(); ++it)
        {
            CSocketAcceptor* pSocketAcceptor = *it;
            LOG_PROCESS_ERROR(pSocketAcceptor);

            pSocketAcceptor->CreateAcceptSocket();
        }

        // traverse session
        BASE_LIST_NODE* pListNode = m_SessionList.Head().pNext;
        while (pListNode != &m_SessionList.Rear())
        {
            BASE_LIST_NODE* pNextNode = pListNode->pNext;

            pSocketSession = node_cast(CSocketSession*, GetListNode(), pListNode);
            LOG_CHECK_ERROR(pSocketSession);

            if (pSocketSession == NULL)
                continue;

            switch (pSocketSession->GetState())
            {
            case ssDisconnecting:
                {
                    INT32 nMaxPacketPerLoop = m_InitParam.nMaxOperationPerLoop;
                    if (pSocketSession->GetShutdownTimer() < qwCurrentTick)
                        pSocketSession->Shutdown();
                    while (pSocketSession->Recv() > 0 && nMaxPacketPerLoop > 0)
                        nMaxPacketPerLoop--;
					if (nMaxPacketPerLoop <= 0)
						CRI("session ptr <%08X> received package count is over max package per loop when ssDisconnecting", (INT32)pSocketSession);
                }
                break;
            case ssNormal:
                {
					INT32 nMaxPacketPerLoop = m_InitParam.nMaxOperationPerLoop;
                    while (pSocketSession->Recv() > 0 && nMaxPacketPerLoop > 0)
                        nMaxPacketPerLoop--;
					if (nMaxPacketPerLoop <= 0)
						CRI("session ptr <%08X> received package count is over max package per loop", (INT32)pSocketSession);
					pSocketSession->TrySend(qwCurrentTick);
                }
                break;
            case ssCleanup:
                if (pSocketSession->CheckCleanup())
                {
                    CBaseList::Remove(&pSocketSession->GetListNode());
                    pSocketSession->UnInit();
                    DestroySession(pSocketSession);
                }
                break;
            case ssConnecting:
                break;
            default:
                CRI("error session %08X state %d", pSocketSession, pSocketSession->GetState());
                LOG_CHECK_ERROR(FALSE);
                break;
            }

            qwCurrentTick = GetTickCountEx();
            if (qwCurrentTick - qwStartTick > MAX_MAIN_THREAD_PROCESS_TIME)
            {
                INF("processing iocp session message over time %d", (INT32)(qwCurrentTick - qwStartTick));
                break;
            }

            pListNode = pNextNode;
        }

        // connected & accepted & disconnected
        STACK_NODE* pStackNode = m_SessionStack.Pop();
        INT32 nOperationCount = 0;
        while (pStackNode)
        {
            pSocketSession = (CSocketSession*)pStackNode->pData;
            switch (pSocketSession->GetState())
            {
            case ssNormal:
                {
                    while(pSocketSession->Recv() > 0);

                    pSocketSession->SetState(ssCleanup);

                    m_pEventHandler->OnDisconnected(pSocketSession, TRUE);
                }
                break;
            case ssDisconnecting:
                {
                    while(pSocketSession->Recv() > 0);

                    pSocketSession->SetState(ssCleanup);

                    m_pEventHandler->OnDisconnected(pSocketSession, FALSE);
                }
                break;
            case ssConnecting:
                {
                    pSocketSession->SetState(ssNormal);
                    m_pEventHandler->OnConnected(pSocketSession);

                    nRetCode = pSocketSession->StartRecv();
                    LOG_CHECK_ERROR(nRetCode);
                    if (!nRetCode)
                    {
                        pSocketSession->SetState(ssDisconnected);
                        CBaseList::Remove(&pSocketSession->GetListNode());

                        m_pEventHandler->OnDisconnected(pSocketSession, TRUE);

                        pSocketSession->UnInit();
                        DestroySession(pSocketSession);
                    }
                }
                break;
            case ssAccepted:
                {
                    pSocketSession->SetState(ssNormal);
                    m_SessionList.PushRear(&pSocketSession->GetListNode());
                    m_pEventHandler->OnAccepted(pSocketSession->GetSocketAcceptor(), pSocketSession);

                    nRetCode = pSocketSession->StartRecv();
                    LOG_CHECK_ERROR(nRetCode);
                    if (!nRetCode)
                    {
                        pSocketSession->SetState(ssDisconnected);
                        CBaseList::Remove(&pSocketSession->GetListNode());

                        m_pEventHandler->OnDisconnected(pSocketSession, TRUE);

                        pSocketSession->UnInit();
                        DestroySession(pSocketSession);
                    }
                }
                break;
            case ssDisconnected:
            default:
                CRI("error socket session state : %d", pSocketSession->GetState());
                LOG_PROCESS_ERROR(FALSE);
                break;
            }

            qwCurrentTick = GetTickCountEx();
            if (qwCurrentTick - qwStartTick > MAX_MAIN_THREAD_PROCESS_TIME)
            {
                INF("processing iocp session event over time %d", (INT32)(qwCurrentTick - qwStartTick));
                break;
            }

            pStackNode = m_SessionStack.Pop();
        }

        return TRUE;
Exit0:
        return FALSE;
    }

	INT64 CNet::PrintMemoryStat(void)
	{
		INT64 llSessionSize = m_SessionPool.GetDataSize() * 
			(m_SessionPool.GetDataSize() + m_InitParam.nSendLoopBufferSize + m_InitParam.nRecvLoopBufferSize) / (1024 * 1024.0f);
		INF("iocp session pool allocated %d session %.2fMB", m_SessionPool.GetSize(), llSessionSize);

		return llSessionSize;
	}

    CNet::CNet()
    {
        m_pPacketAllocator = NULL;
        m_pEventHandler = NULL;
        m_hIOCP = NULL;
        m_pThreadHandle = NULL;
        m_fnConnectEx = NULL;
        memset(&m_InitParam, 0, sizeof(m_InitParam));
        memset(&m_QuitIoData, 0, sizeof(m_QuitIoData));
    }

    CNet::~CNet()
    {
        UnInit();
    }

    BOOL CNet::Init(IPacketAllocator* pPacketAllocator, INetEventHandler* pNetEventHandler, void* pInitParam)
    {
        INT32 nRetCode = 0;
        WSADATA wsaData;
        DWORD dwThreadID;

        LOG_PROCESS_ERROR(pPacketAllocator);
        LOG_PROCESS_ERROR(pNetEventHandler);
        LOG_PROCESS_ERROR(pInitParam);

        memcpy(&m_InitParam, pInitParam, sizeof(m_InitParam));
        LOG_PROCESS_ERROR(m_InitParam.pnMessageSizeList);

        LOG_PROCESS_ERROR(m_InitParam.nMaxSessionCount > 0);

        nRetCode = m_SessionPool.Init(m_InitParam.nMaxSessionCount);
        LOG_PROCESS_ERROR(nRetCode);

        nRetCode = m_SessionStack.Init();
        LOG_PROCESS_ERROR(nRetCode);

        m_SessionList.Clear();
        m_AcceptorList.clear();

        nRetCode = WSAStartup(MAKEWORD(2, 2), &wsaData);
        LOG_PROCESS_ERROR(nRetCode == 0);

        m_hIOCP = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, NULL, m_InitParam.nThreadCount/2);
        LOG_PROCESS_ERROR(m_hIOCP);

        LOG_PROCESS_ERROR(m_InitParam.nThreadCount > 0);
        m_pThreadHandle = new HANDLE[m_InitParam.nThreadCount];
        LOG_PROCESS_ERROR(m_pThreadHandle);

        for (INT32 nIndex = 0; nIndex < m_InitParam.nThreadCount; nIndex++)
        {
            m_pThreadHandle[nIndex] = CreateThread(NULL, 0, _IocpThreadFunc, this, 0, &dwThreadID);
            LOG_PROCESS_ERROR(m_pThreadHandle[nIndex]);

            SetThreadPriority(m_pThreadHandle[nIndex], THREAD_PRIORITY_HIGHEST);
        }

        m_pPacketAllocator = pPacketAllocator;
        m_pEventHandler = pNetEventHandler;

        return TRUE;
Exit0:
        UnInit();

        return FALSE;
    }

    BOOL CNet::UnInit(void)
    {
        INT32 nRetCode = 0;

        if (m_pThreadHandle)
        {
            memset(&m_QuitIoData, 0, sizeof(m_QuitIoData));
            m_QuitIoData.nIoOperation = ioQuit;

            for (INT32 nIndex = 0; nIndex < m_InitParam.nThreadCount; nIndex++)
            {
                PostQueuedCompletionStatus(m_hIOCP, 0, NULL, &m_QuitIoData);
            }

            WaitForMultipleObjects(m_InitParam.nThreadCount, m_pThreadHandle, TRUE, INFINITE);

            for (INT32 nIndex = 0; nIndex < m_InitParam.nThreadCount; nIndex++)
            {
                if (m_pThreadHandle[nIndex])
                    CloseHandle(m_pThreadHandle[nIndex]);
            }
        }
        SAFE_DELETE_ARRAY(m_pThreadHandle);

        nRetCode = MainLoop();
        LOG_CHECK_ERROR(nRetCode);

        if (m_hIOCP)
        {
            CloseHandle(m_hIOCP);
            m_hIOCP = NULL;
        }

        WSACleanup();

        LOG_CHECK_ERROR(m_SessionList.IsEmpty());
        m_SessionList.Clear();

        LOG_CHECK_ERROR(m_AcceptorList.empty());
        m_AcceptorList.clear();

        nRetCode = m_SessionStack.UnInit();
        LOG_CHECK_ERROR(nRetCode);

        nRetCode = m_SessionPool.UnInit();
        LOG_CHECK_ERROR(nRetCode);

        m_pPacketAllocator = NULL;
        m_pEventHandler = NULL;
        m_fnConnectEx = NULL;

        return TRUE;
    }

    CSocketSession* CNet::CreateSession(void)
    {
        CSocketSession* pResult = NULL;

        pResult = m_SessionPool.New();

        return pResult;
    }

    void CNet::DestroySession(CSocketSession* pSession)
    {
        m_SessionPool.Delete(pSession);
    }

    BOOL CNet::PushSessionToMainThread(CSocketSession* pSocketSession)
    {
        INT32 nRetCode = 0;

        LOG_PROCESS_ERROR(pSocketSession);

        m_SessionStack.Push((STACK_NODE*)pSocketSession - 1);

        return TRUE;
Exit0:
        return FALSE;
    }

    inline BOOL CNet::_OnConnect(BOOL bOperateResult, CSocketSession* pSocketSession)
    {
        INT32 nRetCode = 0;

        PROCESS_ERROR(bOperateResult);
        PROCESS_ERROR(pSocketSession->GetState() == ssConnecting);

        nRetCode = setsockopt(pSocketSession->GetSocket(), SOL_SOCKET, SO_UPDATE_CONNECT_CONTEXT, NULL, 0);
        LOG_PROCESS_ERROR(nRetCode != SOCKET_ERROR);

        nRetCode = PushSessionToMainThread(pSocketSession);
        LOG_CHECK_ERROR(nRetCode);

        return TRUE;
Exit0:
        CRI("Failed to connect socket session %08x, %08x, state:%d, error code %d", 
            pSocketSession, pSocketSession->GetSocket(), pSocketSession->GetState(), WSAGetLastError());

        pSocketSession->SetState(ssDisconnecting);

        nRetCode = PushSessionToMainThread(pSocketSession);
        LOG_CHECK_ERROR(nRetCode);

        return FALSE;
    }

    inline BOOL CNet::_OnSend(BOOL bOperateResult, CSocketSession* pSocketSession, DWORD dwIoSize)
    {
        INT32 nRetCode = FALSE;

        PROCESS_ERROR(bOperateResult);

        nRetCode = pSocketSession->CompleteSend(dwIoSize);
        LOG_PROCESS_ERROR(nRetCode);

        return TRUE;
Exit0:
		pSocketSession->StopSend();

        return FALSE;
    }

    inline BOOL CNet::_OnRecv(BOOL bOperateResult, CSocketSession* pSocketSession, DWORD dwIoSize)
    {
        INT32 nRetCode = FALSE;

        PROCESS_ERROR(bOperateResult);
        PROCESS_ERROR(dwIoSize > 0);

        nRetCode = pSocketSession->CompleteRecv(dwIoSize);
        LOG_PROCESS_ERROR(nRetCode);

        return TRUE;
Exit0:
        if (!bOperateResult && dwIoSize == 0)
        {
            CRI("socket session %08x terminated, error code %d", pSocketSession, WSAGetLastError());
        }

        nRetCode = PushSessionToMainThread(pSocketSession);
        LOG_CHECK_ERROR(nRetCode);

		pSocketSession->StopRecv();

        return FALSE;
    }

    DWORD WINAPI CNet::_IocpThreadFunc(void* pParam)
    {
        INT32 nRetCode = 0;
        BOOL bOperateResult = FALSE;
        BOOL bStop = FALSE;

        CNet* pThis = (CNet*)pParam;
        LOG_PROCESS_ERROR(pThis);

        while (!bStop)
        {
            CSocketAcceptor* pSocketAcceptor = NULL;
            CSocketSession* pSocketSession = NULL;
            DWORD* lpCompletionKey = NULL;
            DWORD dwIoSize = 0;
            IO_DATA* pIoData = NULL;

            bOperateResult = GetQueuedCompletionStatus(pThis->m_hIOCP, &dwIoSize, 
                (PULONG_PTR)&lpCompletionKey, (LPOVERLAPPED*)&pIoData, INFINITE);
            if (!bOperateResult && pIoData == NULL)
            {
                    bStop = TRUE;
                    continue;
            }

            pSocketSession = pIoData->pSession;

            switch (pIoData->nIoOperation)
            {
            case ioConnect:
                pThis->_OnConnect(bOperateResult, pSocketSession);
                break;
            case ioAccept:
                {
                    CSocketAcceptor* pSocketAcceptor = (CSocketAcceptor*)lpCompletionKey;
                    LOG_PROCESS_ERROR(pSocketAcceptor);

                    nRetCode = pSocketAcceptor->OnAccept(bOperateResult, pSocketSession);
                    LOG_CHECK_ERROR(nRetCode);
                }
                break;
            case ioSend:
                pThis->_OnSend(bOperateResult, pSocketSession, dwIoSize);
                break;
            case ioRecv:
                pThis->_OnRecv(bOperateResult, pSocketSession, dwIoSize);
                break;
            case ioQuit:
                bStop = TRUE;
                INF("recieved quit signal");
                break;
            default:
                LOG_PROCESS_ERROR(FALSE);
                break;
            }

            continue;
Exit0:
            CRI("Iocp work thread error : %d", WSAGetLastError());
        }

        INF("Iocp work thread quit");

        return 0;
    }

}

#endif

