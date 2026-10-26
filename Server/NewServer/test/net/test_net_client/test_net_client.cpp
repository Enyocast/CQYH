// test_net_client.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "sdtype.h"
#include <list>

#include "process_error.h"
#include "net.h"
#include "external_message_header.h"
#include "external_message_size.h"
#include "packet_allocator.h"
//#include "../../src/net/iocp.h"
#include "../../src/net/simple_net.h"

#if defined(WIN32)
	#include <conio.h>
	#include <winsock2.h>
#elif defined(__linux__)
       #include <sys/socket.h>
       #include <netinet/in.h>
       #include <arpa/inet.h>
#endif

#if defined(__linux__)
	time_t GetTickCount()
	{
		struct timespec ts;
		int nRetCode = clock_gettime( CLOCK_MONOTONIC, &ts ); 
		if( 0 != nRetCode )
			return 0;

		return ts.tv_sec;
	}
#endif

#define PACKET_LEN      (128)
#define TEST_FPS        (1024 * 32)
#define NET_TYPE_DEF    (netIocp)
//#define NET_TYPE_DEF    (netSimple)

IOCP_INIT_PARAM IocpInitParam;
SIMPLE_INIT_PARAM SimpleInitParam;
SHMEM_INIT_PARAM stInitParam;

void* g_pNetInitParam = &SimpleInitParam;

typedef std::list<ISocketSession*>  SESSION_LIST;
SESSION_LIST SessionList;
CPacketAllocator g_PacketAllocator;

class CNetEventHandler : public INetEventHandler
{
public:
    virtual void OnAccepted(ISocketAcceptor* pSocketAcceptor, ISocketSession* pSocketSession)
    {
        SessionList.push_back(pSocketSession);
        INF("session %08x count %d", pSocketSession, SessionList.size());
    }

    virtual void OnConnected(ISocketSession* pSocketSession)
    {
        SessionList.push_back(pSocketSession);
        INF("session %08x count %d", pSocketSession, SessionList.size());
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
int main(int argc, char *argv[])
{
    INT32 nRetCode = 0;
    PACKET_BUFFER* pSendBuffer= NULL;
    PACKET_BUFFER* pRecvBuffer = NULL;
	CNetEventHandler NetEventHandler;
	INet* pNet = NULL;
    //INT64 qwFrameCounter = 0;
    INT64 qwStartTime = 0;
    UINT64 qwLastTime = 0;

    SimpleInitParam.nMaxSessionCount = 8192;
    //SimpleInitParam.nThreadCount = 2;
    //SimpleInitParam.pnMessageSizeList = g_nS2CMessageSize;

    stInitParam.nMaxAcceptor = 8;
    stInitParam.nMaxConnector = 8;
    stInitParam.nMaxSessionCount = 8192;
    stInitParam.nSendBufSize = 1024 * 1024;
    stInitParam.nRecvBufSize = 1024 * 1024;

    SimpleInitParam.nMaxAcceptor = 8;
    SimpleInitParam.nMaxConnector = 8;
    SimpleInitParam.nMaxSessionCount = 64;
    SimpleInitParam.nPacketBufferSize = 1024 * 32;
    SimpleInitParam.nRecvBufSize = 1024 * 1024;
    SimpleInitParam.nSendBufSize = 1024 * 1024;

    nRetCode = CLog::GetInstance().Init("client", lltAll, lotAll, FALSE, TRUE, TRUE);
    LOG_PROCESS_ERROR(nRetCode);

	pNet = g_CreateNetInterface(NET_TYPE_DEF, &g_PacketAllocator, &NetEventHandler, g_pNetInitParam);
	LOG_PROCESS_ERROR(pNet);
    nRetCode = g_PacketAllocator.Init(1024*32*16*2, 1024);
	LOG_PROCESS_ERROR(nRetCode);


    pSendBuffer = g_PacketAllocator.Alloc(64 * 1024);
    LOG_PROCESS_ERROR(pSendBuffer);

    pRecvBuffer = g_PacketAllocator.Alloc(64 * 1024);
    LOG_PROCESS_ERROR(pRecvBuffer);

    for (int nIndex = 0; nIndex < PACKET_LEN; nIndex++)
    {
        ((char*)pSendBuffer)[nIndex] = (char)nIndex;
    }
    ((char*)pSendBuffer)[1] = PACKET_LEN;
    ((char*)pSendBuffer)[2] = 0;

/* // Comment it since the codes below which use these viarables has been commented
*/
    qwStartTime = GetTickCount();

    qwLastTime = qwStartTime;
    //for (int nIndex = 0; nIndex < 3; nIndex++)
    //{
    //    ISocketSession* pSocketSession = pNet->Connect("172.30.61.55", 8111);
    //    LOG_PROCESS_ERROR(pSocketSession);
    //}

    while (true)
    {
		char ch = 0;
#if defined(WIN32)
        if (kbhit())
        {
            ch = getch();
#elif defined(__linux__)
		ch = getchar(); // TODO: blocking! use ncurse if hope noblocking
		{ 
#endif
            if (ch == 's')
            {
                for (int nIndex = 0; nIndex < 1; nIndex++)
				{
					ISocketSession* pSocketSession = pNet->Connect(inet_addr("127.0.0.1"), 8111);
					LOG_PROCESS_ERROR(pSocketSession);
					
					//pSocketSession->Send();	
					
					//((IOCP::CSocketSession*)pSocketSession)->UnInit();
					((SimpleNet::CSocketSession*)pSocketSession)->Close();
				}
            }
        }

//        nRetCode = pNet->MainLoop();
//        LOG_PROCESS_ERROR(nRetCode);

  //      UINT64 qwCurrentTime = GetTickCount();
  //      if ((qwCurrentTime - qwStartTime) * TEST_FPS > qwFrameCounter * 1000)
  //      {
  //          for (SESSION_LIST::iterator it = SessionList.begin();
  //              it != SessionList.end(); ++it)
  //          {
  //              ISocketSession* pSocketSession = *it;

  //              PACKET_BUFFER* pPacketBuffer = g_PacketAllocator.Alloc(PACKET_LEN);
  //              LOG_PROCESS_ERROR(pPacketBuffer);

  //              memcpy(pPacketBuffer, pSendBuffer, PACKET_LEN);

  //              nRetCode = pSocketSession->Send(pPacketBuffer, PACKET_LEN, 0);
		//		NetEventHandler.m_qwSendBytes += nRetCode;
  //          }

		//	qwFrameCounter++;
		//}
		//else
		//{
		//	Sleep(1);
  //          if(qwCurrentTime - qwLastTime > 1000)
  //          {
  //              DBG("Send Bytes: %llu, RecvBytes: %llu", NetEventHandler.m_qwSendBytes, NetEventHandler.m_qwRecvBytes);
  //              qwLastTime = qwCurrentTime;
  //          }
		//}

    }
    INF("main thread exit");

Exit0:
    if (pNet)
    {
        g_DestroyNetInterface(NET_TYPE_DEF, pNet);
        pNet = NULL;
    }

    g_PacketAllocator.UnInit();

    CLog::GetInstance().UnInit();

	return 0;
}

