#ifndef _LOGIN_SERVER_H_
#define _LOGIN_SERVER_H_

#include "packet_allocator.h"
#include "ls_message_handler.h"

class INet;
class ISocketAcceptor;

class CLoginServer
{
public:
    CLoginServer();
    ~CLoginServer();

    static CLoginServer& GetInstance(void);
    
    BOOL Init(INetEventHandler* pNetEventHandler);
    BOOL UnInit(void);

    BOOL Close(void);
    BOOL MainLoop(void);

    INet* GetNetInterface(void)                     {return m_pNet;}
    IPacketAllocator* GetPacketAllocator(void)      {return &m_PacketAllocator;}

private:
    static CLoginServer     ms_Instance;

    INet*                   m_pNet;
    ISocketAcceptor*        m_pGTSocketAcceptor;
    CPacketAllocator        m_PacketAllocator;
};

#endif  // _LOGIN_SERVER_H_