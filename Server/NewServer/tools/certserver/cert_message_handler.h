#ifndef _CERT_MESSAGE_HANDLER_H_
#define _CERT_MESSAGE_HANDLER_H_

#include "net.h"

class CCertMessageHandler : public INetEventHandler
{
public:
    virtual void OnAccepted(ISocketAcceptor* pSocketAcceptor, ISocketSession* pSocketSession);
    virtual void OnConnected(ISocketSession* pSocketSession);
    virtual void OnRecv(ISocketSession* pSocketSession, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize);
    virtual void OnDisconnected(ISocketSession* pSocketSession, BOOL bRemoteShutdown);

public:
    CCertMessageHandler();
    ~CCertMessageHandler();

    BOOL Init(INet* pNet, IPacketAllocator* pPacketAllocator);
    BOOL UnInit(void);

    static CCertMessageHandler& GetInstance(void);
public:

private:
    static CCertMessageHandler      ms_Instance;
    INet*                           m_pNet;
    IPacketAllocator*               m_pPacketAllocator;
};

extern CCertMessageHandler g_MessageHandler;

#endif  // _CERT_MESSAGE_HANDLER_H_