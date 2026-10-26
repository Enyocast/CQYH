// test_net_server.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <list>

#include "process_error.h"


#include "net.h"
#include "external_message_size.h"
#include "external_message_header.h"
#include "packet_allocator.h"
#include "profile.h"

#include "string.h"

#if defined(WIN32)
	#include <winsock2.h>
#elif defined(__linux__)
       #include <sys/socket.h>
       #include <netinet/in.h>
       #include <arpa/inet.h>
#endif

#if defined(__linux__)
	#define Sleep(t) usleep( (t)*1000)	
        time_t GetTickCount()
        {
                struct timespec ts;
                int nRetCode = clock_gettime( CLOCK_MONOTONIC, &ts );
                if( 0 != nRetCode )
                        return 0;

                return ts.tv_sec;
        }
#endif

#define PACKET_LEN      (1024)
#define TEST_FPS        (1024 * 32)
#define NET_TYPE_DEF    (netSimple)

IOCP_INIT_PARAM IocpInitParam;
SHMEM_INIT_PARAM stInitParam;
SIMPLE_INIT_PARAM SimpleInitParam;
void* g_pNetInitParam = &SimpleInitParam;

typedef std::list<ISocketSession*>  SESSION_LIST;
SESSION_LIST SessionList;
CPacketAllocator g_PacketAllocator;
PACKET_BUFFER* g_pSendBuffer;

class CNetEventHandler : public INetEventHandler
{
public:
    virtual void OnAccepted(ISocketAcceptor* pSocketAcceptor, ISocketSession* pSocketSession)
    {
        INT32 nRetCode = 0;

//        SessionList.push_back(pSocketSession);
        INF("accept session %08x count %d", pSocketSession, SessionList.size());

        PACKET_BUFFER* pPacketBuffer = g_PacketAllocator.Alloc(PACKET_LEN);
        LOG_PROCESS_ERROR(pPacketBuffer);

        memcpy(pPacketBuffer, g_pSendBuffer, PACKET_LEN);

        nRetCode = pSocketSession->Send(pPacketBuffer, PACKET_LEN, 0);
        LOG_PROCESS_ERROR(nRetCode);

Exit0:
        pSocketSession->Close();
        return;
    }

    virtual void OnConnected(ISocketSession* pSocketSession)
    {
        SessionList.push_back(pSocketSession);
        INF("connect session %08x count %d", pSocketSession, SessionList.size());
    }

    virtual void OnRecv(ISocketSession* pSocketSession, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize)
    {
		m_qwRecvBytes += dwSize;
        g_PacketAllocator.Free(pPacketBuffer);
        return;
    }

    virtual void OnDisconnected(ISocketSession* pSocketSession, BOOL bRemoteShutdown)
    {
        for (SESSION_LIST::iterator it = SessionList.begin();
            it != SessionList.end(); ++it)
        {
            if (*it == pSocketSession)
            {
                SessionList.erase(it);
                break;
            }
        }

        INF("disconnected session %08x count %d", pSocketSession, SessionList.size());
    }
	UINT64 m_qwSendBytes;
	UINT64 m_qwRecvBytes;
};

//int _tmain(int argc, _TCHAR* argv[])
int main(int argc, char* argv[])
{
    INT32 nRetCode = 0;
    ISocketAcceptor* pSocketAcceptor = NULL;
    //ISocketSession* pSocketSession = NULL;
    INet* pNet = NULL;

    INT64 qwFrameCounter = 0;
    INT64 qwStartTime = 0;
    UINT64 qwLastTime = 0;
    
    CNetEventHandler NetEventHandler;
    NetEventHandler.m_qwSendBytes = 0;
	NetEventHandler.m_qwRecvBytes = 0;

    stInitParam.nMaxAcceptor = 8;
    stInitParam.nMaxConnector = 8;
    stInitParam.nMaxSessionCount = 64;
    stInitParam.nRecvBufSize = 1024 * 1024;
    stInitParam.nSendBufSize = 1024 * 1024;

    IocpInitParam.nMaxSessionCount = 2;
    IocpInitParam.nThreadCount = 2;
    IocpInitParam.pnMessageSizeList = g_nC2SMessageSize;

    SimpleInitParam.nMaxAcceptor = 8;
    SimpleInitParam.nMaxConnector = 8;
    SimpleInitParam.nMaxSessionCount = 64;
    SimpleInitParam.nPacketBufferSize = 1024 * 32;
    SimpleInitParam.nRecvBufSize = 1024 * 1024;
    SimpleInitParam.nSendBufSize = 1024 * 1024;

    nRetCode = CLog::GetInstance().Init("server", lltAll, lotAll, FALSE, TRUE, TRUE);
    LOG_PROCESS_ERROR(nRetCode);

    nRetCode = g_PacketAllocator.Init(1024*64*16, 1024);
    LOG_PROCESS_ERROR(nRetCode);

    pNet = g_CreateNetInterface(NET_TYPE_DEF, &g_PacketAllocator, &NetEventHandler, g_pNetInitParam);
    LOG_PROCESS_ERROR(pNet);

    pSocketAcceptor = pNet->CreateAcceptor();
    LOG_PROCESS_ERROR(pSocketAcceptor);

    nRetCode = pSocketAcceptor->Open(inet_addr("127.0.0.1"), 8111);
    LOG_PROCESS_ERROR(nRetCode);

    INF("server start to listen...");

    g_pSendBuffer = g_PacketAllocator.Alloc(64 * 1024);
    LOG_PROCESS_ERROR(g_pSendBuffer);

    for (int nIndex = 0; nIndex < PACKET_LEN; nIndex++)
    {
        ((char*)g_pSendBuffer)[nIndex] = (char)nIndex + 128;
    }
    ((char*)g_pSendBuffer)[0] = 0;
    ((char*)g_pSendBuffer)[1] = PACKET_LEN;
    ((char*)g_pSendBuffer)[2] = 0;

    qwStartTime = GetTickCount();
    qwLastTime = qwStartTime;

    while (true)
    {
        nRetCode = pNet->MainLoop();
        LOG_PROCESS_ERROR(nRetCode);

        INT64 qwCurrentTime = GetTickCount();
        if ((qwCurrentTime - qwStartTime) * TEST_FPS > qwFrameCounter * 1000)
        {
            for (SESSION_LIST::iterator it = SessionList.begin();
                it != SessionList.end(); ++it)
            {
                ISocketSession* pSocketSession = *it;
				LOG_PROCESS_ERROR(pSocketSession);

                PACKET_BUFFER* pPacketBuffer = g_PacketAllocator.Alloc(PACKET_LEN);
                LOG_PROCESS_ERROR(pPacketBuffer);

                memcpy(pPacketBuffer, g_pSendBuffer, PACKET_LEN);

                nRetCode = pSocketSession->Send(pPacketBuffer, PACKET_LEN, 0);
				//LOG_PROCESS_ERROR(nRetCode);
				NetEventHandler.m_qwSendBytes += nRetCode;
            }

            qwFrameCounter++;
        }
        else
        {
            Sleep(1);
		    //if(qwCurrentTime - qwLastTime > 1000)
		    //{
			   // DBG("Send Bytes: %llu, RecvBytes: %llu", NetEventHandler.m_qwSendBytes, NetEventHandler.m_qwRecvBytes);
			   // qwLastTime = qwCurrentTime;
		    //}
        }
    }

    INF("main thread exit");

    nRetCode = pSocketAcceptor->Close();
    LOG_PROCESS_ERROR(nRetCode);

Exit0:
    if (pNet)
    {
        if (pSocketAcceptor)
            pNet->DestroyAcceptor(pSocketAcceptor);
        g_DestroyNetInterface(NET_TYPE_DEF, pNet);
        pNet = NULL;
    }

    g_PacketAllocator.UnInit();

    CLog::GetInstance().UnInit();

    return 0;
}
