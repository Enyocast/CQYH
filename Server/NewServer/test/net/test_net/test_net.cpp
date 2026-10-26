// test_net.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <list>

#if defined(WIN32)
	#include <winsock2.h>
#elif defined(__linux__)
	#include <string.h>
	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <arpa/inet.h>

	#include <unistd.h>
	#define Sleep(t) usleep( (t)*1000)
#endif

#include "process_error.h"
#include "net.h"
#include "packet_allocator.h"
#include "external_message_header.h"
#include "external_message_size.h"
//#include "message_lua_init.h"

#define NET_TYPE_DEF    (netSimple)
#define NET_TEST_COUNT  (24)

IOCP_INIT_PARAM IocpInitParam;
SIMPLE_INIT_PARAM SimpleInitParam;
INTRANET_INIT_PARAM stInitParem;
void* g_pNetInitParam = &SimpleInitParam;

INT32 nRetCode = 0;
CPacketAllocator g_PacketAllocator[2];

//#define DEFAULT_PAYLOAD "\000\015\000123456789"
#define DEFAULT_PAYLOAD    "\0031234567890123456789"
#define DISCONNECT_PAYLOAD "\002123"

#define DEFAULT_OFFSET "Offset"


typedef std::list<ISocketSession*>  SESSION_LIST;
SESSION_LIST g_ConnectSessionList;
SESSION_LIST g_AcceptSessionList;
SESSION_LIST g_DisconnectSessionList;
INet* g_pNet = NULL;
INT32 g_nCounter1, g_nCounter2;

class CNetEventHandler : public INetEventHandler
{
public:
    virtual void OnAccepted(ISocketAcceptor* pSocketAcceptor, ISocketSession* pSocketSession)
    {
        LOG_PROCESS_ERROR(pSocketAcceptor);
        LOG_PROCESS_ERROR(pSocketSession);

        pSocketSession->SetUserData((void*)0x00000001);

        g_AcceptSessionList.push_back(pSocketSession);
Exit0:
        return;
    }

    virtual void OnConnected(ISocketSession* pSocketSession)
    {
        PACKET_BUFFER* pPacketBuffer = NULL;
        LOG_PROCESS_ERROR(pSocketSession);

        pPacketBuffer = g_PacketAllocator[0].Alloc(sizeof(DEFAULT_PAYLOAD));
        memcpy(pPacketBuffer, DEFAULT_PAYLOAD, sizeof(DEFAULT_PAYLOAD));

        nRetCode = pSocketSession->Send(pPacketBuffer, sizeof(DEFAULT_PAYLOAD), 0);
        LOG_PROCESS_ERROR(nRetCode == sizeof(DEFAULT_PAYLOAD));

        g_ConnectSessionList.push_back(pSocketSession);
Exit0:
        return;
    }

    virtual void OnRecv(ISocketSession* pSocketSession, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize)
    {
        LOG_PROCESS_ERROR(pSocketSession);
        LOG_PROCESS_ERROR(pPacketBuffer);
        LOG_PROCESS_ERROR(dwSize == sizeof(DEFAULT_PAYLOAD));
        LOG_PROCESS_ERROR(memcmp(pPacketBuffer, DEFAULT_PAYLOAD, dwSize-1) == 0);

        //pSocketSession->SetUserData((void*)((UINT32)pSocketSession->GetUserData() | 0x10000000));
        pSocketSession->SetUserData((void*)((UINT64)pSocketSession->GetUserData() | 0x10000000));

        g_PacketAllocator[0].Free(pPacketBuffer);
Exit0:
        return;
    }

    virtual void OnDisconnected(ISocketSession* pSocketSession, BOOL bRemoteShutdown)
    {
        UINT64 dwTag = NULL;
        LOG_PROCESS_ERROR(pSocketSession);
        dwTag = (UINT64)pSocketSession->GetUserData();
        if (dwTag & 1)
        {
            LOG_PROCESS_ERROR(dwTag & 0x10000001);
            g_nCounter1++;
        }
        else
        {
            g_nCounter2++;
        }

        g_DisconnectSessionList.push_back(pSocketSession);
        return;
Exit0:
        return;
    }
};
CNetEventHandler g_NetEventHandler;

class CNetEventHandler2 : public INetEventHandler
{
public:
    virtual void OnAccepted(ISocketAcceptor* pSocketAcceptor, ISocketSession* pSocketSession)
    {
        LOG_PROCESS_ERROR(pSocketAcceptor);
        LOG_PROCESS_ERROR(pSocketSession);

        pSocketSession->SetUserData((void*)0x00000001);
        g_AcceptSessionList.push_back(pSocketSession);

Exit0:
        return;
    }

    virtual void OnConnected(ISocketSession* pSocketSession)
    {
        PACKET_BUFFER* pPacketBuffer = NULL;
        LOG_PROCESS_ERROR(pSocketSession);

        pPacketBuffer = g_PacketAllocator[0].Alloc(sizeof(DEFAULT_PAYLOAD));
        memcpy(pPacketBuffer, DEFAULT_PAYLOAD, sizeof(DEFAULT_PAYLOAD));

        nRetCode = pSocketSession->Send(pPacketBuffer, sizeof(DEFAULT_PAYLOAD), 0);
        LOG_PROCESS_ERROR(nRetCode == sizeof(DEFAULT_PAYLOAD));

        g_ConnectSessionList.push_back(pSocketSession);
Exit0:
        pSocketSession->Close();
        return;
    }

    virtual void OnRecv(ISocketSession* pSocketSession, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize)
    {
        LOG_PROCESS_ERROR(pSocketSession);
        LOG_PROCESS_ERROR(pPacketBuffer);
        LOG_PROCESS_ERROR(dwSize == sizeof(DEFAULT_PAYLOAD));
        LOG_PROCESS_ERROR(memcmp(pPacketBuffer, DEFAULT_PAYLOAD, dwSize) == 0);

        pSocketSession->SetUserData((void*)((UINT64)pSocketSession->GetUserData() | 0x10000000));

        g_PacketAllocator->Free(pPacketBuffer);
Exit0:
        return;
    }

    virtual void OnDisconnected(ISocketSession* pSocketSession, BOOL bRemoteShutdown)
    {
        UINT32 dwTag = NULL;
        LOG_PROCESS_ERROR(pSocketSession);
        dwTag = (UINT64)pSocketSession->GetUserData();
        if (dwTag & 1)
        {
            LOG_PROCESS_ERROR(dwTag == 0x10000001);
            g_nCounter1++;
        }
        else
        {
            g_nCounter2++;
        }
        g_DisconnectSessionList.push_back(pSocketSession);
Exit0:
        return;
    }
};
CNetEventHandler2 g_NetEventHandler2;


class CNetEventHandler3 : public INetEventHandler
{
public:
    virtual void OnAccepted(ISocketAcceptor* pSocketAcceptor, ISocketSession* pSocketSession)
    {
        PACKET_BUFFER* pPacketBuffer = NULL;
        LOG_PROCESS_ERROR(pSocketAcceptor);
        LOG_PROCESS_ERROR(pSocketSession);

        pPacketBuffer = g_PacketAllocator[0].Alloc(sizeof(DEFAULT_PAYLOAD));
        memcpy(pPacketBuffer, DEFAULT_PAYLOAD, sizeof(DEFAULT_PAYLOAD));

        nRetCode = pSocketSession->Send(pPacketBuffer, sizeof(DEFAULT_PAYLOAD), 0);
        LOG_PROCESS_ERROR(nRetCode == sizeof(DEFAULT_PAYLOAD));

        pSocketSession->SetUserData((void*)0x00000010);

        g_AcceptSessionList.push_back(pSocketSession);
Exit0:
        pSocketSession->Close();
        return;
    }

    virtual void OnConnected(ISocketSession* pSocketSession)
    {
        LOG_PROCESS_ERROR(pSocketSession);

        pSocketSession->SetUserData((void*)0x00000001);
        g_ConnectSessionList.push_back(pSocketSession);
Exit0:
        return;
    }

    virtual void OnRecv(ISocketSession* pSocketSession, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize)
    {
        LOG_PROCESS_ERROR(pSocketSession);
        LOG_PROCESS_ERROR(pPacketBuffer);
        
        if (memcmp(pPacketBuffer, DEFAULT_PAYLOAD, dwSize) == 0)
        {
            pSocketSession->SetUserData((void*)((UINT64)(pSocketSession->GetUserData()) | 0x10000000));
        }
        else if (memcmp(pPacketBuffer, DISCONNECT_PAYLOAD, dwSize) == 0)
        {
            pSocketSession->SetUserData((void*)((UINT64)(pSocketSession->GetUserData()) | 0x01000000));
        }
        else
        {
            LOG_PROCESS_ERROR(FALSE);
        }

Exit0:
        if (pPacketBuffer)
            g_PacketAllocator->Free(pPacketBuffer);
        return;
    }

    virtual void OnDisconnected(ISocketSession* pSocketSession, BOOL bRemoteShutdown)
    {
        LOG_PROCESS_ERROR(pSocketSession);

        if (bRemoteShutdown)
        {
            UINT64 dwTag = (UINT64)pSocketSession->GetUserData();
            LOG_PROCESS_ERROR(dwTag == 0x10000001);

            //PACKET_BUFFER* pPacketBuffer = g_PacketAllocator[0].Alloc(sizeof(DISCONNECT_PAYLOAD));
            //memcpy(pPacketBuffer, DISCONNECT_PAYLOAD, sizeof(DISCONNECT_PAYLOAD));

            //nRetCode = pSocketSession->Send(pPacketBuffer, sizeof(DISCONNECT_PAYLOAD), 0);
            //LOG_PROCESS_ERROR(nRetCode == sizeof(DISCONNECT_PAYLOAD));

            g_nCounter1++;
        }
        else
        {
            //UINT32 dwTag = (UINT32)pSocketSession->GetUserData();
            //LOG_PROCESS_ERROR(dwTag == 0x01000010);

            g_nCounter2++;
        }

Exit0:
        g_DisconnectSessionList.push_back(pSocketSession);

        return;
    }
};
CNetEventHandler3 g_NetEventHandler3;

bool test_packet_allocator()
{
    INT32 nRetCode = 0;
    typedef std::list<PACKET_BUFFER*> BUFFER_LIST;
    BUFFER_LIST BufferList;
    PACKET_BUFFER* pPacketBuffer = NULL;
    CPacketAllocator PacketAllocator;

    nRetCode = PacketAllocator.Init(1000, 1000);
    LOG_PROCESS_ERROR(nRetCode);

    pPacketBuffer = PacketAllocator.Alloc(0);
    LOG_PROCESS_ERROR(pPacketBuffer == NULL);

    for (int i = 1; i <= 1000; i++)
    {
        pPacketBuffer = PacketAllocator.Alloc(i);
        LOG_PROCESS_ERROR(pPacketBuffer);

        BufferList.push_back(pPacketBuffer);
    }

    pPacketBuffer = PacketAllocator.Alloc(1000);
    LOG_PROCESS_ERROR(pPacketBuffer == NULL);

    for (int i = 1; i <= 1000; i++)
    {
        pPacketBuffer = PacketAllocator.Alloc(1024 + i * 64);
        LOG_PROCESS_ERROR(pPacketBuffer);

        BufferList.push_back(pPacketBuffer);
    }
    pPacketBuffer = PacketAllocator.Alloc(2048);
    LOG_PROCESS_ERROR(pPacketBuffer == NULL);

    for (BUFFER_LIST::iterator it = BufferList.begin();
        it != BufferList.end(); ++it)
    {
        PacketAllocator.Free(*it);
    }

    nRetCode = PacketAllocator.UnInit();
    LOG_PROCESS_ERROR(nRetCode);

    return true;
Exit0:
    return false;
}

bool test_net(INT32 eNetType, void* pInitParam)
{
    std::list<ISocketAcceptor*> AcceptorList;

    INet* pNet = g_CreateNetInterface(eNetType, NULL, &g_NetEventHandler, pInitParam);
    LOG_PROCESS_ERROR(pNet == NULL);

    pNet = g_CreateNetInterface(eNetType, &g_PacketAllocator[0], NULL, pInitParam);
    LOG_PROCESS_ERROR(pNet == NULL);

    pNet = g_CreateNetInterface(eNetType, &g_PacketAllocator[0], &g_NetEventHandler, NULL);
    LOG_PROCESS_ERROR(pNet == NULL);

    pNet = g_CreateNetInterface(netInvalid, &g_PacketAllocator[0], &g_NetEventHandler, pInitParam);
    LOG_PROCESS_ERROR(pNet == NULL);

    pNet = g_CreateNetInterface(netTotal, &g_PacketAllocator[0], &g_NetEventHandler, pInitParam);
    LOG_PROCESS_ERROR(pNet == NULL);

    nRetCode = g_DestroyNetInterface(eNetType, NULL);
    LOG_PROCESS_ERROR(nRetCode == FALSE);

    for (int i = 0; i < 100; i++)
    {
        INet* pNet_1 = g_CreateNetInterface(eNetType, &g_PacketAllocator[0], &g_NetEventHandler, pInitParam);
        LOG_PROCESS_ERROR(pNet_1);

        INet* pNet_2 = g_CreateNetInterface(eNetType, &g_PacketAllocator[1], &g_NetEventHandler, pInitParam);
        LOG_PROCESS_ERROR(pNet_2);

        nRetCode = g_DestroyNetInterface(eNetType, pNet_1);
        LOG_PROCESS_ERROR(nRetCode);

        nRetCode = g_DestroyNetInterface(eNetType, pNet_2);
        LOG_PROCESS_ERROR(nRetCode);
    }

    pNet = g_CreateNetInterface(eNetType, &g_PacketAllocator[0], &g_NetEventHandler, pInitParam);
    LOG_PROCESS_ERROR(pNet);

    for (int i = 0; i < NET_TEST_COUNT; i++)
    {
        ISocketAcceptor* pSocketAcceptor = pNet->CreateAcceptor();
        LOG_PROCESS_ERROR(pSocketAcceptor);

        AcceptorList.push_back(pSocketAcceptor);
    }

    for (std::list<ISocketAcceptor*>::iterator it = AcceptorList.begin();
        it != AcceptorList.end(); ++it)
    {
        nRetCode = pNet->DestroyAcceptor(*it);
        LOG_PROCESS_ERROR(nRetCode);
    }

    nRetCode = g_DestroyNetInterface(eNetType, pNet);
    LOG_PROCESS_ERROR(nRetCode);

    return true;
Exit0:
    return false;
}

bool test_acceptor(INT32 eNetType, void* pInitParam)
{
    ISocketSession* pSocketSession = NULL;
    ISocketAcceptor* pSocketAcceptor = NULL;

    INet* pNet = g_CreateNetInterface(eNetType, &g_PacketAllocator[0], &g_NetEventHandler, pInitParam);
    LOG_PROCESS_ERROR(pNet);

    pSocketAcceptor = pNet->CreateAcceptor();
    LOG_PROCESS_ERROR(pSocketAcceptor);

    g_ConnectSessionList.clear();
    g_DisconnectSessionList.clear();
    g_AcceptSessionList.clear();

    nRetCode = pSocketAcceptor->Open(inet_addr("127.0.0.1"), 8111);
    LOG_PROCESS_ERROR(nRetCode);

    for (int i = 0; i < NET_TEST_COUNT; i++)
    {
        pSocketSession = pNet->Connect(inet_addr("127.0.0.1"), 8111);
        LOG_PROCESS_ERROR(pSocketSession);

        nRetCode = pNet->MainLoop();
		LOG_PROCESS_ERROR(nRetCode);
    }

    while (g_ConnectSessionList.size() < NET_TEST_COUNT || g_AcceptSessionList.size() < NET_TEST_COUNT)
    {
        nRetCode = pNet->MainLoop();
        LOG_PROCESS_ERROR(nRetCode);
    }

    for (SESSION_LIST::iterator it = g_ConnectSessionList.begin();
        it != g_ConnectSessionList.end(); ++it)
    {
        UINT32 dwAddr;
        UINT16 wPort;
        UINT32 dwRemoteAddr;
        UINT16 wRemotePort;
        INT32 nRetCode = 0;
        BOOL  bFlag = FALSE;

        nRetCode = (*it)->GetAddress(dwAddr, wPort);
        LOG_PROCESS_ERROR(nRetCode);

        nRetCode = (*it)->GetRemoteAddress(dwRemoteAddr, wRemotePort);
        LOG_PROCESS_ERROR(nRetCode);

        bFlag = FALSE;
        for(SESSION_LIST::iterator itr = g_AcceptSessionList.begin();
            itr != g_AcceptSessionList.end(); ++itr)
        {
            UINT32 dwAddr1;
            UINT16 wPort1;
            UINT32 dwRemoteAddr1;
            UINT16 wRemotePort1;

            nRetCode = (*itr)->GetAddress(dwAddr1, wPort1);
            LOG_PROCESS_ERROR(nRetCode);

            nRetCode = (*itr)->GetRemoteAddress(dwRemoteAddr1, wRemotePort1);
            LOG_PROCESS_ERROR(nRetCode);
            
            if(dwAddr1 == dwRemoteAddr && wPort1 == wRemotePort && dwRemoteAddr1 == dwAddr && wRemotePort1 == wPort)
            {
                bFlag = TRUE;
                break;
            }
        }
        LOG_PROCESS_ERROR(bFlag);
    }

    for (SESSION_LIST::iterator it = g_ConnectSessionList.begin();
        it != g_ConnectSessionList.end(); ++it)
    {
        (*it)->Close();
    }

    while (g_DisconnectSessionList.size() < NET_TEST_COUNT + NET_TEST_COUNT)
    {
        nRetCode = pNet->MainLoop();
        LOG_PROCESS_ERROR(nRetCode);
    }

    nRetCode = pSocketAcceptor->Close();
    LOG_PROCESS_ERROR(nRetCode);

    g_ConnectSessionList.clear();
    g_DisconnectSessionList.clear();
    g_AcceptSessionList.clear();

    for (int i = 0; i < NET_TEST_COUNT; i++)
    {
        nRetCode = pSocketAcceptor->Open(inet_addr("127.0.0.1"), 8111);
        LOG_PROCESS_ERROR(nRetCode);

        nRetCode = pSocketAcceptor->Close();
        LOG_PROCESS_ERROR(nRetCode);
    }

    nRetCode = pNet->DestroyAcceptor(pSocketAcceptor);
    LOG_PROCESS_ERROR(nRetCode);

    nRetCode = g_DestroyNetInterface(eNetType, pNet);
    LOG_PROCESS_ERROR(nRetCode);

    return true;
Exit0:
    return false;
}

bool test_close(INT32 eNetType, void* pInitParam)
{
    ISocketSession* pSocketSession = NULL;
    ISocketAcceptor* pSocketAcceptor = NULL; 

    INet* pNet = g_CreateNetInterface(eNetType, &g_PacketAllocator[0], &g_NetEventHandler, pInitParam);
    LOG_PROCESS_ERROR(pNet);

    pSocketAcceptor = pNet->CreateAcceptor();
    LOG_PROCESS_ERROR(pSocketAcceptor);

    INF("test_close 1.1************************************");
    Sleep(1);

    g_ConnectSessionList.clear();
    g_DisconnectSessionList.clear();
    g_AcceptSessionList.clear();
    g_nCounter1 = g_nCounter2 = 0;

    nRetCode = pSocketAcceptor->Open(inet_addr("127.0.0.1"), 8111);
    LOG_PROCESS_ERROR(nRetCode);

    for (int i = 0; i < NET_TEST_COUNT; i++)
    {
        pSocketSession = pNet->Connect(inet_addr("127.0.0.1"), 8111);
        LOG_PROCESS_ERROR(pSocketSession);

        nRetCode = pNet->MainLoop();	
	LOG_PROCESS_ERROR(nRetCode);
    }

    while (g_ConnectSessionList.size() < NET_TEST_COUNT || g_AcceptSessionList.size() < NET_TEST_COUNT)
    {
        nRetCode = pNet->MainLoop();
        LOG_PROCESS_ERROR(nRetCode);
    }

    for (SESSION_LIST::iterator it = g_ConnectSessionList.begin();
        it != g_ConnectSessionList.end(); ++it)
    {
        //for (int i = 0; i < 10; i++)
            (*it)->Close();
    }

    while (g_DisconnectSessionList.size() < NET_TEST_COUNT + NET_TEST_COUNT)
    {
        nRetCode = pNet->MainLoop();
        LOG_PROCESS_ERROR(nRetCode);
    }
    LOG_PROCESS_ERROR(g_DisconnectSessionList.size() == NET_TEST_COUNT + NET_TEST_COUNT);
    INF("recved %d, not connected %d", g_nCounter1, g_nCounter2);
    LOG_PROCESS_ERROR(g_nCounter1 == NET_TEST_COUNT);
    LOG_PROCESS_ERROR(g_nCounter2 == NET_TEST_COUNT);

    nRetCode = pSocketAcceptor->Close();
    LOG_PROCESS_ERROR(nRetCode);

    INF("test_close 1.2************************************");
    Sleep(1);

    g_ConnectSessionList.clear();
    g_DisconnectSessionList.clear();
    g_AcceptSessionList.clear();
    g_nCounter1 = g_nCounter2 = 0;

    nRetCode = pSocketAcceptor->Open(inet_addr("127.0.0.1"), 8111);
    LOG_PROCESS_ERROR(nRetCode);

    for (int i = 0; i < NET_TEST_COUNT; i++)
    {
        pSocketSession = pNet->Connect(inet_addr("127.0.0.1"), 8111);
        LOG_PROCESS_ERROR(pSocketSession);
    }

    while (g_ConnectSessionList.size() < NET_TEST_COUNT || g_AcceptSessionList.size() < NET_TEST_COUNT)
    {
        nRetCode = pNet->MainLoop();
        LOG_PROCESS_ERROR(nRetCode);
    }

    for (SESSION_LIST::iterator it = g_ConnectSessionList.begin();
        it != g_ConnectSessionList.end(); ++it)
    {
        (*it)->Close();
    }

    for (SESSION_LIST::iterator it = g_AcceptSessionList.begin();
        it != g_AcceptSessionList.end(); ++it)
    {
        (*it)->Close();
    }

    while (g_DisconnectSessionList.size() < NET_TEST_COUNT + NET_TEST_COUNT)
    {
        nRetCode = pNet->MainLoop();
        LOG_PROCESS_ERROR(nRetCode);
    }
    LOG_PROCESS_ERROR(g_DisconnectSessionList.size() == NET_TEST_COUNT + NET_TEST_COUNT);
    INF("recved %d, not connected %d", g_nCounter1, g_nCounter2);
    LOG_PROCESS_ERROR(g_nCounter1 == NET_TEST_COUNT);
    LOG_PROCESS_ERROR(g_nCounter2 == NET_TEST_COUNT);

    nRetCode = pSocketAcceptor->Close();
    LOG_PROCESS_ERROR(nRetCode);

    INF("test_close 1.3************************************");
    Sleep(1);

    g_ConnectSessionList.clear();
    g_DisconnectSessionList.clear();
    g_AcceptSessionList.clear();
    g_nCounter1 = g_nCounter2 = 0;

    nRetCode = pSocketAcceptor->Open(inet_addr("127.0.0.1"), 8111);
    LOG_PROCESS_ERROR(nRetCode);

    for (int i = 0; i < NET_TEST_COUNT; i++)
    {
        pSocketSession = pNet->Connect(inet_addr("127.0.0.1"), 8111);
        LOG_PROCESS_ERROR(pSocketSession);

		nRetCode = pNet->MainLoop();
        LOG_PROCESS_ERROR(nRetCode);

        nRetCode = pSocketSession->Close();
        LOG_PROCESS_ERROR(nRetCode);

		nRetCode = pNet->MainLoop();
        LOG_PROCESS_ERROR(nRetCode);
    }

    while (g_DisconnectSessionList.size() < NET_TEST_COUNT + g_AcceptSessionList.size())
    {
        nRetCode = pNet->MainLoop();
        LOG_PROCESS_ERROR(nRetCode);
    }
    LOG_PROCESS_ERROR(g_DisconnectSessionList.size() == NET_TEST_COUNT + g_AcceptSessionList.size());
    INF("recved %d, not connected %d", g_nCounter1, g_nCounter2);
    LOG_PROCESS_ERROR(g_nCounter1 == g_AcceptSessionList.size());
    LOG_PROCESS_ERROR(g_nCounter2 == NET_TEST_COUNT);

    nRetCode = pSocketAcceptor->Close();
    LOG_PROCESS_ERROR(nRetCode);

    nRetCode = pNet->DestroyAcceptor(pSocketAcceptor);
    LOG_PROCESS_ERROR(nRetCode);

    nRetCode = g_DestroyNetInterface(eNetType, pNet);
    LOG_PROCESS_ERROR(nRetCode);

    return true;
Exit0:
    return false;
}

bool test_close2(INT32 eNetType, void* pInitParam)
{
    ISocketSession* pSocketSession = NULL;
    ISocketAcceptor* pSocketAcceptor = NULL;

    g_pNet = g_CreateNetInterface(eNetType, &g_PacketAllocator[0], &g_NetEventHandler2, pInitParam);
    LOG_PROCESS_ERROR(g_pNet);

    pSocketAcceptor = g_pNet->CreateAcceptor();
    LOG_PROCESS_ERROR(pSocketAcceptor);

    INF("test_close 2************************************");
    Sleep(1);

    g_ConnectSessionList.clear();
    g_DisconnectSessionList.clear();
    g_AcceptSessionList.clear();
    g_nCounter1 = g_nCounter2 = 0;

    nRetCode = pSocketAcceptor->Open(inet_addr("127.0.0.1"), 8111);
    LOG_PROCESS_ERROR(nRetCode);

    for (int i = 0; i < NET_TEST_COUNT; i++)
    {
        pSocketSession = g_pNet->Connect(inet_addr("127.0.0.1"), 8111);
        LOG_PROCESS_ERROR(pSocketSession);

        nRetCode = g_pNet->MainLoop();
        LOG_PROCESS_ERROR(nRetCode);
    }

    while (g_ConnectSessionList.size() < NET_TEST_COUNT || g_AcceptSessionList.size() < NET_TEST_COUNT)
    {
        nRetCode = g_pNet->MainLoop();
        LOG_PROCESS_ERROR(nRetCode);
    }

    while (g_DisconnectSessionList.size() < NET_TEST_COUNT + NET_TEST_COUNT)
    {
        nRetCode = g_pNet->MainLoop();
        LOG_PROCESS_ERROR(nRetCode);
    }
    LOG_PROCESS_ERROR(g_DisconnectSessionList.size() == NET_TEST_COUNT + NET_TEST_COUNT);
    INF("recved %d, not connected %d", g_nCounter1, g_nCounter2);
    LOG_PROCESS_ERROR(g_nCounter1 == NET_TEST_COUNT);
    LOG_PROCESS_ERROR(g_nCounter2 == NET_TEST_COUNT);

    nRetCode = pSocketAcceptor->Close();
    LOG_PROCESS_ERROR(nRetCode);

    nRetCode = g_pNet->DestroyAcceptor(pSocketAcceptor);
    LOG_PROCESS_ERROR(nRetCode);

    nRetCode = g_DestroyNetInterface(eNetType, g_pNet);
    LOG_PROCESS_ERROR(nRetCode);

    g_pNet = NULL;

    return true;
Exit0:
    return false;
}

bool test_close3(INT32 eNetType, void* pInitParam)
{
    ISocketSession* pSocketSession = NULL;
    ISocketAcceptor* pSocketAcceptor = NULL;

    g_pNet = g_CreateNetInterface(eNetType, &g_PacketAllocator[0], &g_NetEventHandler3, pInitParam);
    LOG_PROCESS_ERROR(g_pNet);

    pSocketAcceptor = g_pNet->CreateAcceptor();
    LOG_PROCESS_ERROR(pSocketAcceptor);

    INF("test_close 3************************************");
    Sleep(1);
    g_ConnectSessionList.clear();
    g_DisconnectSessionList.clear();
    g_AcceptSessionList.clear();
    g_nCounter1 = g_nCounter2 = 0;

    nRetCode = pSocketAcceptor->Open(inet_addr("127.0.0.1"), 8111);
    LOG_PROCESS_ERROR(nRetCode);

    for (int i = 0; i < NET_TEST_COUNT; i++)
    {
        pSocketSession = g_pNet->Connect(inet_addr("127.0.0.1"), 8111);
        LOG_PROCESS_ERROR(pSocketSession);
    }

    while (g_ConnectSessionList.size() < NET_TEST_COUNT || g_AcceptSessionList.size() < NET_TEST_COUNT)
    {
        nRetCode = g_pNet->MainLoop();
        LOG_PROCESS_ERROR(nRetCode);
    }

    while (g_DisconnectSessionList.size() < NET_TEST_COUNT + NET_TEST_COUNT)
    {
        nRetCode = g_pNet->MainLoop();
        LOG_PROCESS_ERROR(nRetCode);
    }
    LOG_PROCESS_ERROR(g_DisconnectSessionList.size() == NET_TEST_COUNT + NET_TEST_COUNT);
    INF("recved %d, not connected %d", g_nCounter1, g_nCounter2);
    LOG_PROCESS_ERROR(g_nCounter1 == NET_TEST_COUNT);
    LOG_PROCESS_ERROR(g_nCounter2 == NET_TEST_COUNT);

    nRetCode = pSocketAcceptor->Close();
    LOG_PROCESS_ERROR(nRetCode);

    nRetCode = g_pNet->DestroyAcceptor(pSocketAcceptor);
    LOG_PROCESS_ERROR(nRetCode);

    nRetCode = g_DestroyNetInterface(eNetType, g_pNet);
    LOG_PROCESS_ERROR(nRetCode);

    g_pNet = NULL;

    return true;
Exit0:
    return false;
}

bool test_send(INT32 eNetType, void* pInitParam)
{
    ISocketSession* pSocketSession = NULL;
    PACKET_BUFFER* pPacketBuffer = NULL;
    ISocketAcceptor* pSocketAcceptor = NULL;

    INet* pNet = g_CreateNetInterface(eNetType, &g_PacketAllocator[0], &g_NetEventHandler, pInitParam);
    LOG_PROCESS_ERROR(pNet);

    pSocketAcceptor = pNet->CreateAcceptor();
    LOG_PROCESS_ERROR(pSocketAcceptor);

    INF("test_send************************************");
    Sleep(1);
    g_ConnectSessionList.clear();
    g_DisconnectSessionList.clear();
    g_AcceptSessionList.clear();
    g_nCounter1 = g_nCounter2 = 0;

    nRetCode = pSocketAcceptor->Open(inet_addr("127.0.0.1"), 8111);
    LOG_PROCESS_ERROR(nRetCode);

    pSocketSession = pNet->Connect(inet_addr("127.0.0.1"), 8111);
    LOG_PROCESS_ERROR(pSocketSession);

    while (g_ConnectSessionList.size() < 1 || g_AcceptSessionList.size() < 1)
    {
        nRetCode = pNet->MainLoop();
        LOG_PROCESS_ERROR(nRetCode);
    }

    pPacketBuffer = g_PacketAllocator[0].Alloc(sizeof(DEFAULT_PAYLOAD));
    memcpy(pPacketBuffer, DEFAULT_PAYLOAD, sizeof(DEFAULT_PAYLOAD));
    nRetCode = pSocketSession->Send(pPacketBuffer, sizeof(DEFAULT_PAYLOAD), 0);
    LOG_PROCESS_ERROR(nRetCode == sizeof(DEFAULT_PAYLOAD));

    pPacketBuffer = g_PacketAllocator[0].Alloc(sizeof(DEFAULT_PAYLOAD));
    memcpy(pPacketBuffer, DEFAULT_PAYLOAD, sizeof(DEFAULT_PAYLOAD));

    nRetCode = pSocketSession->Send(pPacketBuffer, 0, 0);
    LOG_PROCESS_ERROR(nRetCode == 0);

    pPacketBuffer = g_PacketAllocator[0].Alloc(sizeof(DEFAULT_PAYLOAD));
    memcpy(pPacketBuffer, DEFAULT_PAYLOAD, sizeof(DEFAULT_PAYLOAD));

    nRetCode = pSocketSession->Send(pPacketBuffer, -1, 0);
    LOG_PROCESS_ERROR(nRetCode == 0);

    while (g_DisconnectSessionList.size() < 2)
    {
        nRetCode = pNet->MainLoop();
        LOG_PROCESS_ERROR(nRetCode);
    }
    LOG_PROCESS_ERROR(g_DisconnectSessionList.size() == 2);
    INF("recved %d, not connected %d", g_nCounter1, g_nCounter2);

    nRetCode = pSocketAcceptor->Close();
    LOG_PROCESS_ERROR(nRetCode);

    nRetCode = pNet->DestroyAcceptor(pSocketAcceptor);
    LOG_PROCESS_ERROR(nRetCode);

    nRetCode = g_DestroyNetInterface(eNetType, pNet);
    LOG_PROCESS_ERROR(nRetCode);

    return true;
Exit0:
    return false;
}

bool test_send_offset(INT32 eNetType, void* pInitParam)
{
    ISocketSession* pSocketSession = NULL;
    ISocketAcceptor* pSocketAcceptor = NULL;
    PACKET_BUFFER* pPacketBuffer = NULL;

    INet* pNet = g_CreateNetInterface(eNetType, &g_PacketAllocator[0], &g_NetEventHandler, pInitParam);
    LOG_PROCESS_ERROR(pNet);

    pSocketAcceptor = pNet->CreateAcceptor();
    LOG_PROCESS_ERROR(pSocketAcceptor);

    INF("test send offset************************************");
    Sleep(1);
    g_ConnectSessionList.clear();
    g_DisconnectSessionList.clear();
    g_AcceptSessionList.clear();
    g_nCounter1 = g_nCounter2 = 0;

    nRetCode = pSocketAcceptor->Open(inet_addr("127.0.0.1"), 8111);
    LOG_PROCESS_ERROR(nRetCode);

    pSocketSession = pNet->Connect(inet_addr("127.0.0.1"), 8111);
    LOG_PROCESS_ERROR(pSocketSession);

    while (g_ConnectSessionList.size() < 1 || g_AcceptSessionList.size() < 1)
    {
        nRetCode = pNet->MainLoop();
        LOG_PROCESS_ERROR(nRetCode);
    }

    pPacketBuffer = g_PacketAllocator[0].Alloc(sizeof(DEFAULT_PAYLOAD));
    memcpy((CHAR*)pPacketBuffer - sizeof(DEFAULT_OFFSET), DEFAULT_OFFSET, sizeof(DEFAULT_OFFSET));
    memcpy(pPacketBuffer, DEFAULT_PAYLOAD, sizeof(DEFAULT_PAYLOAD));
    nRetCode = pSocketSession->Send(pPacketBuffer, sizeof(DEFAULT_PAYLOAD), 0);
    LOG_PROCESS_ERROR(nRetCode == sizeof(DEFAULT_PAYLOAD));

    pPacketBuffer = g_PacketAllocator[0].Alloc(sizeof(DEFAULT_PAYLOAD));
    memcpy(pPacketBuffer, DEFAULT_OFFSET, sizeof(DEFAULT_OFFSET));
    memcpy((CHAR*)pPacketBuffer + sizeof(DEFAULT_OFFSET), DEFAULT_PAYLOAD, sizeof(DEFAULT_PAYLOAD));
    nRetCode = pSocketSession->Send(pPacketBuffer, sizeof(DEFAULT_PAYLOAD), sizeof(DEFAULT_OFFSET));
    LOG_PROCESS_ERROR(nRetCode == sizeof(DEFAULT_PAYLOAD));

    pPacketBuffer = g_PacketAllocator[0].Alloc(sizeof(DEFAULT_PAYLOAD));
    memcpy((CHAR*)pPacketBuffer - sizeof(DEFAULT_OFFSET), DEFAULT_PAYLOAD, sizeof(DEFAULT_PAYLOAD));
    nRetCode = pSocketSession->Send(pPacketBuffer, sizeof(DEFAULT_PAYLOAD), -sizeof(DEFAULT_OFFSET));
    LOG_PROCESS_ERROR(nRetCode == sizeof(DEFAULT_PAYLOAD));

    pPacketBuffer = g_PacketAllocator[0].Alloc(sizeof(DEFAULT_PAYLOAD));
    memcpy(pPacketBuffer + sizeof(DEFAULT_OFFSET), DEFAULT_PAYLOAD, sizeof(DEFAULT_PAYLOAD));
    nRetCode = pSocketSession->Send(pPacketBuffer, sizeof(DEFAULT_PAYLOAD), sizeof(DEFAULT_OFFSET));
    LOG_PROCESS_ERROR(nRetCode == sizeof(DEFAULT_PAYLOAD));

    pPacketBuffer = g_PacketAllocator[0].Alloc(sizeof(DEFAULT_PAYLOAD));
    memcpy(pPacketBuffer, DEFAULT_OFFSET, sizeof(DEFAULT_OFFSET));
    memcpy(pPacketBuffer + sizeof(DEFAULT_OFFSET), DEFAULT_PAYLOAD, sizeof(DEFAULT_PAYLOAD));
    nRetCode = pSocketSession->Send(pPacketBuffer, 0, 0);
    LOG_PROCESS_ERROR(nRetCode == 0);

    while (g_DisconnectSessionList.size() < 2)
    {
        nRetCode = pNet->MainLoop();
        LOG_PROCESS_ERROR(nRetCode);
    }
    LOG_PROCESS_ERROR(g_DisconnectSessionList.size() == 2);
    INF("recved %d, not connected %d", g_nCounter1, g_nCounter2);

    nRetCode = pSocketAcceptor->Close();
    LOG_PROCESS_ERROR(nRetCode);

    nRetCode = pNet->DestroyAcceptor(pSocketAcceptor);
    LOG_PROCESS_ERROR(nRetCode);

    nRetCode = g_DestroyNetInterface(eNetType, pNet);
    LOG_PROCESS_ERROR(nRetCode);

    return true;
Exit0:
    return false;
}

//int _tmain(int argc, _TCHAR* argv[])
int main(int argc, char* argv[])
{
    //IocpInitParam.nMaxSessionCount = 64;
    //IocpInitParam.nThreadCount = 4;
    //IocpInitParam.pnMessageSizeList = g_nC2SMessageSize;

    stInitParem.nMaxSessionCount = 64;
    stInitParem.nMaxAcceptor = 32;
    stInitParem.nMaxConnector = 32;
    stInitParem.nPacketBufferSize = 1024 * 32;
    stInitParem.nRecvBufSize = 1024 * 1024;
    stInitParem.nSendBufSize = 1024 * 1024;

    SimpleInitParam.nMaxSessionCount = 64;//NET_TEST_COUNT * 2 + 16 + 1;
    SimpleInitParam.nMaxAcceptor = 32;
    SimpleInitParam.nMaxConnector = 32;
    SimpleInitParam.nPacketBufferSize = 1024 * 32;
    SimpleInitParam.nRecvBufSize = 1024 * 1024;
    SimpleInitParam.nSendBufSize = 1024 * 1024;

    nRetCode = CLog::GetInstance().Init("server", lltAll, lotFile, FALSE, TRUE, TRUE);
    LOG_PROCESS_ERROR(nRetCode);

    nRetCode = g_PacketAllocator[0].Init(1024, 1024);
    LOG_PROCESS_ERROR(nRetCode);

    nRetCode = g_PacketAllocator[1].Init(1024, 1024);
    LOG_PROCESS_ERROR(nRetCode);

    for (int i = 0; i < 10; i++)
    {
        nRetCode = test_packet_allocator();
        LOG_PROCESS_ERROR(nRetCode);

        nRetCode = test_net(NET_TYPE_DEF, g_pNetInitParam);
        LOG_PROCESS_ERROR(nRetCode);

        nRetCode = test_acceptor(NET_TYPE_DEF, g_pNetInitParam);
        LOG_PROCESS_ERROR(nRetCode);

        nRetCode = test_close(NET_TYPE_DEF, g_pNetInitParam);
        LOG_PROCESS_ERROR(nRetCode);

        nRetCode = test_close2(NET_TYPE_DEF, g_pNetInitParam);
        LOG_PROCESS_ERROR(nRetCode);

        nRetCode = test_close3(NET_TYPE_DEF, g_pNetInitParam);
        LOG_PROCESS_ERROR(nRetCode);

        nRetCode = test_send(NET_TYPE_DEF, g_pNetInitParam);
        LOG_PROCESS_ERROR(nRetCode);

        nRetCode = test_send_offset(NET_TYPE_DEF, g_pNetInitParam);
        LOG_PROCESS_ERROR(nRetCode);
    }

    INF("passed all test cases");
Exit0:
    nRetCode = g_PacketAllocator[1].UnInit();
    LOG_CHECK_ERROR(nRetCode);

    nRetCode = g_PacketAllocator[0].UnInit();
    LOG_CHECK_ERROR(nRetCode);

    CLog::GetInstance().UnInit();

    return 0;
}

