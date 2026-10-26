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
    // 应用程序调用Send()，但数据量很小
    INT32 CSocketSession::Send(PACKET_BUFFER* pPacketBuffer, INT32 nSize, INT32 nOffset)
    {
        INT32 nRetCode = 0;
        INT32 nSendDataSize = 0;
        INT32 SEND_LOOP_BUFFER_SIZE = 0;

        LOG_PROCESS_ERROR(pPacketBuffer);
        LOG_PROCESS_ERROR(nSize > 0);

        // 1. 检查状态和参数
        PROCESS_ERROR(m_eState == ssNormal);
#if defined(_DEBUG)
        LOG_PROCESS_ERROR(m_pPacketAllocator->IsAllocated(pPacketBuffer));
#endif	//_DEBUG

        LOG_PROCESS_ERROR(m_pNet);
        SEND_LOOP_BUFFER_SIZE = m_pNet->GetInitParam().nSendLoopBufferSize;

        // 2. 计算发送缓冲区剩余空间
        nSendDataSize = m_SendIndex.Rear - m_SendIndex.Head;
        nSendDataSize = nSendDataSize < 0 ? SEND_LOOP_BUFFER_SIZE + nSendDataSize : nSendDataSize;
        LOG_PROCESS_ERROR(nSendDataSize + nSize < SEND_LOOP_BUFFER_SIZE);

        // 3. 将数据拷贝到发送循环缓冲区（处理回绕）
        if (m_SendIndex.Head <= m_SendIndex.Rear)
        {
            if (m_SendIndex.Rear + nSize < SEND_LOOP_BUFFER_SIZE)
            {
                memcpy(m_pSendLoopBuffer + m_SendIndex.Rear, (char*)pPacketBuffer + nOffset, nSize);
            }
            else
            {
                // 处理缓冲区回绕
                INT32 nPartSize = SEND_LOOP_BUFFER_SIZE - m_SendIndex.Rear;

                memcpy(m_pSendLoopBuffer + m_SendIndex.Rear, (char*)pPacketBuffer + nOffset, nPartSize);
                memcpy(m_pSendLoopBuffer, (char*)pPacketBuffer + nOffset + nPartSize, nSize - nPartSize);
            }
        }
        else
        {
            memcpy(m_pSendLoopBuffer + m_SendIndex.Rear, (char*)pPacketBuffer + nOffset, nSize);
        }

        // 4. 更新尾部索引
        m_SendIndex.Rear = (m_SendIndex.Rear + nSize) % SEND_LOOP_BUFFER_SIZE;

        // 5. 如果没有正在发送，启动发送流程
        // 如果没有正在发送，但数据量小于阈值，设置延迟发送
        if (!m_bSending)
        {
            nSendDataSize = m_SendIndex.Rear - m_SendIndex.Head;
            nSendDataSize = nSendDataSize < 0 ? SEND_LOOP_BUFFER_SIZE + nSendDataSize : nSendDataSize;
            if (nSendDataSize >= DELAY_SEND_THRESHOLD)
            {
                nRetCode = StartSend();  // 触发异步发送
                LOG_PROCESS_ERROR(nRetCode);

                // 更新下次发送时间
                m_qwSendTimer = GetTickCountEx() + DELAY_SEND_DURATION;
            }
        }

        // 6. 释放包缓冲区
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

    // gateserver 收包函数
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

        // 代码解释
        {
            // 为什么要用%计算
            {
            	// 循环缓冲区是环形的，索引到达末尾后会回到开头
            	// % RECV_LOOP_BUFFER_SIZE确保索引在缓冲区范围内
            	// 防止数组越界访问
                // 这种设计避免了频繁的内存拷贝，提高了I/O效率，是高性能网络编程中常见的技术

                // 例子
                // 假设缓冲区大小=1000，当前Head=980，消息大小=30
                // 980 + 30 = 1010
                // 1010 % 1000 = 10
                // Head从980移动到10，实现循环缓冲
            }
            
            // << 左移的作用
            {
            	// 第二个字节是消息ID的高8位
            	// 左移8位后与低8位组合成16位消息ID
            	// 例如：0x34 | (0x12 << 8) = 0x1234
            }
        }

        // 读取第一个字节（低8位）
        wMsgID = *(UINT8*)(m_pRecvLoopBuffer + m_RecvIndex.Head);

        // 读取第二个字节（高8位），使用%处理循环缓冲区回绕
        wMsgID |= *((UINT8*)(m_pRecvLoopBuffer + (m_RecvIndex.Head + 1) % RECV_LOOP_BUFFER_SIZE)) << 8;
        LOG_PROCESS_ERROR(wMsgID < max_message_count);

        nSize = m_pNet->GetInitParam().pnMessageSizeList[wMsgID];
        if (nSize == flex_message_size)
        {
            UINT16 wTempSize = 0;
            PROCESS_SUCCESS(nRecvDataSize < sizeof(FLEX_MESSAGE_HEADER));

            // 读取长度字段的第一个字节（低8位）
            wTempSize = *((UINT8*)(m_pRecvLoopBuffer + (m_RecvIndex.Head + sizeof(MESSAGE_HEADER)) % RECV_LOOP_BUFFER_SIZE));
            nSize = wTempSize;

            // 读取长度字段的第二个字节（高8位）
            wTempSize = *((UINT8*)(m_pRecvLoopBuffer + (m_RecvIndex.Head + sizeof(MESSAGE_HEADER) + 1) % RECV_LOOP_BUFFER_SIZE));

            // 组合成16位长度
            nSize += wTempSize << 8;
        }
        LOG_PROCESS_ERROR(nSize > 0);

        // 1. 检查是否有完整消息
        PROCESS_SUCCESS(nRecvDataSize < nSize);

        //recv ok
        nMessageSize = nSize;

        pPacketBuffer = m_pNet->GetPacketAllocator()->Alloc(nMessageSize);
        LOG_PROCESS_ERROR(pPacketBuffer);

        // 2. 从循环缓冲区拷贝完整消息
        if (m_RecvIndex.Head < m_RecvIndex.Rear)
        {
            // Head在Rear前面，数据是连续的
            memcpy(pPacketBuffer, m_pRecvLoopBuffer + m_RecvIndex.Head, nMessageSize);
        }
        else
        {
            if (m_RecvIndex.Head + nMessageSize <= RECV_LOOP_BUFFER_SIZE)
            {
                // Head在Rear后面，但数据还在缓冲区末尾之前
                memcpy(pPacketBuffer, m_pRecvLoopBuffer + m_RecvIndex.Head, nMessageSize);
            }
            else
            {
                // 数据跨越缓冲区末尾和开头
                INT32 nPartSize = RECV_LOOP_BUFFER_SIZE - m_RecvIndex.Head;

                // 拷贝末尾部分
                memcpy(pPacketBuffer, m_pRecvLoopBuffer + m_RecvIndex.Head, nPartSize);

                // 拷贝开头部分
                memcpy(pPacketBuffer + nPartSize, m_pRecvLoopBuffer, nMessageSize - nPartSize);
            }
        }

        // 3. 更新读取位置
        m_RecvIndex.Head = (m_RecvIndex.Head + nMessageSize) % RECV_LOOP_BUFFER_SIZE;

        // 4. 交给业务层处理
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

        // 1. 更新发送缓冲区头部索引
        m_SendIndex.Head = (m_SendIndex.Head + nIoSize) % SEND_LOOP_BUFFER_SIZE;

        // 2. 计算剩余待发送数据量
        nSendDataSize = m_SendIndex.Rear - m_SendIndex.Head;
        nSendDataSize = nSendDataSize < 0 ? SEND_LOOP_BUFFER_SIZE + nSendDataSize : nSendDataSize;

        // 3. 如果还有数据要发送，继续发起异步发送
        if (nSendDataSize >= DELAY_SEND_THRESHOLD || nIoSize == 0 ||
            (nSendDataSize > 0 && m_eState == ssDisconnecting))
        {
            LOG_PROCESS_ERROR(nSendDataSize > 0);

            m_SendIoData.nIoOperation = ioSend;

            // 设置WSABUF参数
            m_SendIoData.wsabuf.buf = m_pSendLoopBuffer + m_SendIndex.Head;
            if (m_SendIndex.Head <= m_SendIndex.Rear)
            {
                m_SendIoData.wsabuf.len = m_SendIndex.Rear - m_SendIndex.Head;
            }
            else
            {
                m_SendIoData.wsabuf.len = SEND_LOOP_BUFFER_SIZE - m_SendIndex.Head;
            }

            // 发起异步发送
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

    // 完整的接收数据流程: 网络数据到达 → IOCP完成通知 → CompleteRecv()更新Rear → 主线程Recv()处理数据 → 更新Head
    BOOL CSocketSession::CompleteRecv(INT32 nIoSize)
    {
        INT32 nRetCode = 0;
        DWORD dwFlag = 0;

        INT32 RECV_LOOP_BUFFER_SIZE = 0;
        LOG_PROCESS_ERROR(m_pNet);
        RECV_LOOP_BUFFER_SIZE = m_pNet->GetInitParam().nRecvLoopBufferSize;

        LOG_PROCESS_ERROR(m_eState == ssNormal || m_eState == ssAccepted || m_eState == ssDisconnecting);

        // 索引变化示例
        {
            // 假设缓冲区大小=1000，初始状态：Head=0, Rear=0

            // 1, 接收200字节数据
            // CompleteRecv(200) → Rear = (0 + 200) % 1000 = 200
            // Head=0, Rear=200

            // 2, 主线程处理150字节消息
            // Recv()处理完成后 → Head = (0 + 150) % 1000 = 150
            // Head=150, Rear=200

            // 3, 再接收300字节数据
            // CompleteRecv(300) → Rear = (200 + 300) % 1000 = 500
            // Head=150, Rear=500
        }

        // 1. 更新接收缓冲区尾部索引 (使用模运算确保索引在合法范围内)（如果nIoSize>0，说明是数据到达通知）
        INT32 nNewRecvRear = (m_RecvIndex.Rear + nIoSize) % RECV_LOOP_BUFFER_SIZE;
        m_RecvIndex.Rear = nNewRecvRear;  // Rear ∈ [0, RECV_LOOP_BUFFER_SIZE-1]

        // 检查缓冲区是否足够
        INT32 nRecvDataSize = m_RecvIndex.Rear - m_RecvIndex.Head;
        nRecvDataSize = nRecvDataSize < 0 ? RECV_LOOP_BUFFER_SIZE + nRecvDataSize : nRecvDataSize;
        LOG_PROCESS_ERROR(nRecvDataSize + 1 < RECV_LOOP_BUFFER_SIZE);

        // 准备下一次接收
        m_RecvIoData.nIoOperation = ioRecv;

        // 2. 计算下一次接收参数
        m_RecvIoData.wsabuf.buf = m_pRecvLoopBuffer + m_RecvIndex.Rear;

        // 3. 计算下一次接收的长度
        if (m_RecvIndex.Head <= m_RecvIndex.Rear)
            m_RecvIoData.wsabuf.len = RECV_LOOP_BUFFER_SIZE - m_RecvIndex.Rear;  // 连续空间：从Rear到缓冲区末尾
        else
            m_RecvIoData.wsabuf.len = m_RecvIndex.Head - m_RecvIndex.Rear - 1;   // 回绕空间：从Rear到Head-1

        if (m_RecvIoData.wsabuf.len > 2048)
            m_RecvIoData.wsabuf.len = 2048;

        // 4. 立即发起下一次异步接收（保持接收链不断）（非阻塞！）
        nRetCode = WSARecv(m_Socket, &m_RecvIoData.wsabuf, 1, (LPDWORD)&nIoSize, &dwFlag, &m_RecvIoData, NULL);

        // 5. 检查结果：允许异步挂起
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

        // 检查是否满足发送条件
        // 条件1：当前没有正在进行的发送操作 (m_bSending = FALSE 表示没有异步发送在进行中, 这是触发新发送的基本前提)
        // 条件2：延迟发送计时器已到期 (m_qwSendTimer 是下一次允许发送的时间戳, 用于实现发送合并和流量控制)
        // 条件3：缓冲区中有待发送数据 (计算循环缓冲区中的有效数据量, 只有有数据时才需要触发发送)
        if (!m_bSending && (m_qwSendTimer < qwCurrentTick))
        {
            INT32 nSendDataSize = 0;

            // 计算待发送数据量
            nSendDataSize = m_SendIndex.Rear - m_SendIndex.Head;
            nSendDataSize = nSendDataSize < 0 ? SEND_LOOP_BUFFER_SIZE + nSendDataSize : nSendDataSize;

            // 如果有数据且满足条件，触发发送
            if (nSendDataSize > 0)
            {
                m_bSending = TRUE;
                nRetCode = PostQueuedCompletionStatus(m_pNet->GetIOCPHandle(), 0, (ULONG_PTR)this, &m_SendIoData);
                if (!nRetCode)
                    m_bSending = FALSE;
                LOG_PROCESS_ERROR(nRetCode);

                // 每次发送后更新计时器，避免连续触发
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

        // 通过IOCP通知工作线程开始发送
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
        struct sockaddr_in Address = { 0 };
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

        // 1. 检查接受结果
        PROCESS_ERROR(bOperateResult);
        LOG_PROCESS_ERROR(pSocketSession);

        // 2. 更新接受上下文
        nRetCode = setsockopt(pSocketSession->GetSocket(), SOL_SOCKET, SO_UPDATE_ACCEPT_CONTEXT,
            (char*)&m_sockListen, sizeof(m_sockListen));
        LOG_PROCESS_ERROR(nRetCode != SOCKET_ERROR);

        // 3. 将新socket关联到IOCP端口
        hIOCP = CreateIoCompletionPort((HANDLE)pSocketSession->GetSocket(), m_pNet->GetIOCPHandle(), (DWORD_PTR)pSocketSession, 0);
        LOG_PROCESS_ERROR(hIOCP == m_pNet->GetIOCPHandle());

        // 4. 通知主线程有新连接
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

        // 1. 增加接受计数器
        nRetCode = InterlockedIncrement((LONG volatile*)&m_nAcceptSocketCount);
        PROCESS_ERROR(nRetCode <= MAX_ACCEPT_SESSION_COUNT);

        PROCESS_ERROR(_InterlockedAnd((LONG*)&m_sockListen, 0xFFFFFFFF) != INVALID_SOCKET);
        LOG_PROCESS_ERROR(m_pNet);
        LOG_PROCESS_ERROR(m_fnAcceptEx);

        // 2. 创建新的会话对象
        pSession = m_pNet->CreateSession();
        PROCESS_ERROR(pSession);

        // 初始化会话对象
        nRetCode = pSession->Init(m_pNet, this);
        LOG_PROCESS_ERROR(nRetCode);

        // 3. 设置状态为已接受
        pSession->SetState(ssAccepted);

        // 4. 发起异步接受操作
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
        struct sockaddr_in Address = { 0 };
        HANDLE hIOCP;
        INT32 nOption = 1;
        INT32 nZero = 0;
        GUID ConnectExGuid = WSAID_CONNECTEX;

        // 1. 创建会话对象
        pResult = CreateSession();
        LOG_PROCESS_ERROR(pResult);

        // 2. 初始化会话
        nRetCode = pResult->Init(this, NULL);
        LOG_PROCESS_ERROR(nRetCode);

        // 3. 将socket关联到IOCP端口
        hIOCP = CreateIoCompletionPort((HANDLE)pResult->GetSocket(), m_hIOCP, (DWORD_PTR)pResult, 0);
        LOG_PROCESS_ERROR(hIOCP == m_hIOCP);

        Address.sin_family = AF_INET;
        Address.sin_addr.s_addr = INADDR_ANY;
        Address.sin_port = 0;

        // 4. 绑定本地地址
        nRetCode = bind(pResult->GetSocket(), (sockaddr*)&Address, sizeof(Address));
        LOG_PROCESS_ERROR(nRetCode != SOCKET_ERROR);

        // 5. 获取ConnectEx函数指针（第一次使用时）
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

        // 6. 发起异步连接
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

    // 主线程（同步处理）
    BOOL CNet::MainLoop(void)
    {
        INT32 nRetCode = 0;
        CSocketSession* pSocketSession = NULL;
        UINT64 qwStartTick = GetTickCountEx();
        UINT64 qwCurrentTick = GetTickCountEx();

        INT32 SEND_LOOP_BUFFER_SIZE = m_InitParam.nSendLoopBufferSize;

        LOG_PROCESS_ERROR(m_pEventHandler);

        // 在MainLoop开头补充AcceptEx操作
        // 每个AcceptEx操作只能接受一个连接
        // 连接接受后需要立即补充新的AcceptEx
        // 确保随时有Accept操作等待新连接，避免连接丢失
        // try to create accept socket
        for (ACCEPTOR_LIST::iterator it = m_AcceptorList.begin(); it != m_AcceptorList.end(); ++it)
        {
            CSocketAcceptor* pSocketAcceptor = *it;
            LOG_PROCESS_ERROR(pSocketAcceptor);

            pSocketAcceptor->CreateAcceptSocket();
        }

        // 循环1：遍历现有会话列表，处理活跃连接
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
                case ssDisconnecting:  // 断开中状态：只收不发，等待关闭
                {
                    INT32 nMaxPacketPerLoop = m_InitParam.nMaxOperationPerLoop;
                    if (pSocketSession->GetShutdownTimer() < qwCurrentTick)
                        pSocketSession->Shutdown();

                    // 消息解析和业务处理, 从应用层缓冲区解析完整消息, 调用业务层的事件处理器, 不涉及网络I/O操作
                    while (pSocketSession->Recv() > 0 && nMaxPacketPerLoop > 0)
                        nMaxPacketPerLoop--;

                    if (nMaxPacketPerLoop <= 0)
                        CRI("session ptr <%08X> received package count is over max package per loop when ssDisconnecting", (INT32)pSocketSession);

                    break;
                }
                case ssNormal:  // 处理已建立连接的会话（ssNormal状态）
                {
                    INT32 nMaxPacketPerLoop = m_InitParam.nMaxOperationPerLoop;

                    // - 接收数据处理 (Recv())
                    while (pSocketSession->Recv() > 0 && nMaxPacketPerLoop > 0)
                        nMaxPacketPerLoop--;

                    if (nMaxPacketPerLoop <= 0)
                        CRI("session ptr <%08X> received package count is over max package per loop", (INT32)pSocketSession);

                    // - 触发发送 (TrySend())
                    pSocketSession->TrySend(qwCurrentTick);

                    break;
                }
                case ssCleanup:  // 清理状态：检查是否可以销毁
                {
                    if (pSocketSession->CheckCleanup())
                    {
                        CBaseList::Remove(&pSocketSession->GetListNode());
                        pSocketSession->UnInit();
                        DestroySession(pSocketSession);
                    }
                    break;
                }
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

        // 循环2：处理事件栈中的新事件
        // connected & accepted & disconnected
        STACK_NODE* pStackNode = m_SessionStack.Pop();
        INT32 nOperationCount = 0;
        while (pStackNode)
        {
            // 处理各种状态变化：
            pSocketSession = (CSocketSession*)pStackNode->pData;
            switch (pSocketSession->GetState())
            {
                case ssNormal:  // 连接就绪
                {
                    while (pSocketSession->Recv() > 0);

                    pSocketSession->SetState(ssCleanup);

                    m_pEventHandler->OnDisconnected(pSocketSession, TRUE);
                }
                break;
                case ssDisconnecting:  // 断开中
                {
                    while (pSocketSession->Recv() > 0);

                    pSocketSession->SetState(ssCleanup);

                    m_pEventHandler->OnDisconnected(pSocketSession, FALSE);
                }
                break;
                case ssConnecting:  // 连接完成
                {
                    pSocketSession->SetState(ssNormal);  // 改为正常状态
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
                case ssAccepted:  // 新接受连接
                {
                    // 设置状态为ssNormal
                    pSocketSession->SetState(ssNormal);

                    // 加入会话列表
                    m_SessionList.PushRear(&pSocketSession->GetListNode());

                    // 调用事件处理器OnAccepted
                    m_pEventHandler->OnAccepted(pSocketSession->GetSocketAcceptor(), pSocketSession);

                    // 开始异步接收
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

        m_hIOCP = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, NULL, m_InitParam.nThreadCount / 2);
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

        // 1. 检查连接结果
        PROCESS_ERROR(bOperateResult);
        PROCESS_ERROR(pSocketSession->GetState() == ssConnecting);

        // 2. 更新连接上下文
        nRetCode = setsockopt(pSocketSession->GetSocket(), SOL_SOCKET, SO_UPDATE_CONNECT_CONTEXT, NULL, 0);
        LOG_PROCESS_ERROR(nRetCode != SOCKET_ERROR);

        // 3. 通知主线程连接完成
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

        // 1. 检查发送结果
        PROCESS_ERROR(bOperateResult);

        // 2. 处理发送完成
        nRetCode = pSocketSession->CompleteSend(dwIoSize);
        LOG_PROCESS_ERROR(nRetCode);

        return TRUE;
    Exit0:
        pSocketSession->StopSend();

        return FALSE;
    }

    // 完整的接收数据流程: 网络数据到达 → IOCP完成通知 → CompleteRecv()更新Rear → 主线程Recv()处理数据 → 更新Head
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

    // IOCP工作线程（异步接收）在工作线程中执行 - 真正的网络I/O操作
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

            // 等待IOCP通知（这里会阻塞，但这是工作线程，不是主线程）
            bOperateResult = GetQueuedCompletionStatus(pThis->m_hIOCP, &dwIoSize,
                (PULONG_PTR)&lpCompletionKey, (LPOVERLAPPED*)&pIoData, INFINITE);
            if (!bOperateResult && pIoData == NULL)
            {
                bStop = TRUE;
                continue;
            }

            pSocketSession = pIoData->pSession;

            // 根据标识分发处理
            // pIoData 就是之前提交的 m_RecvIoData，nIoOperation 仍然是 ioRecv
            switch (pIoData->nIoOperation)
            {
                case ioConnect:  // 连接完成
                {
                    pThis->_OnConnect(bOperateResult, pSocketSession);
                    break;
                }
                case ioAccept:  // 接受完成
                {
                    CSocketAcceptor* pSocketAcceptor = (CSocketAcceptor*)lpCompletionKey;
                    LOG_PROCESS_ERROR(pSocketAcceptor);

                    nRetCode = pSocketAcceptor->OnAccept(bOperateResult, pSocketSession);
                    LOG_CHECK_ERROR(nRetCode);
                    break;
                }
                case ioSend:  // 发送完成
                {
                    pThis->_OnSend(bOperateResult, pSocketSession, dwIoSize);
                    break;
                }
                case ioRecv:  // 接收完成
                {
                    // 真正的网络数据接收, 将数据从内核缓冲区拷贝到应用层缓冲区, "不处理业务逻辑", 只做数据搬运
                    pThis->_OnRecv(bOperateResult, pSocketSession, dwIoSize);
                    break;
                }
                case ioQuit:  // 连接完成
                {
                    bStop = TRUE;
                    INF("recieved quit signal");
                    break;
                }
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

    // 详细的工作流程
    // 
    // 阶段1：异步接收（IOCP工作线程）
    // 网络数据到达 → 操作系统内核 → IOCP完成端口通知 → 工作线程唤醒 → 
    // 调用CompleteRecv() → 数据拷贝到循环缓冲区 → 发起新的异步接收
    // 
    // 阶段2：同步处理（主线程）
    // 主循环检查 → 发现缓冲区有数据 → 调用Recv() → 解析消息头 → 
    // 检查消息完整性 → 拷贝完整消息 → 调用OnRecv事件处理器

    // 实际数据流向示例
    // 网络数据流: [消息1][消息2][消息3]...
    //     
    // IOCP工作线程:
    // 接收→[消息1部]→[消息1剩余+消息2]→[消息3]...（持续接收）
    // 
    // 主线程:
    // 检查缓冲区→发现完整[消息1]→处理→检查→发现完整[消息2]→处理...

    // Rear 和 Head 的关系
    // 
    // Rear（尾部索引）
    // 由IOCP工作线程在CompleteRecv()中修改
    // 表示已接收数据的结束位置
    // 只能向后移动（增加）
    // 
    // Head（头部索引）
    // 由主线程在Recv()中修改
    // 表示已处理数据的开始位置
    // 只能向后移动（增加）

}

#endif

