#ifndef _BS_EXTERNAL_MESSAGE_HANDLER_H_
#define _BS_EXTERNAL_MESSAGE_HANDLER_H_

#include "net.h"
#include "bs_session_mgr.h"
#include "external_message_header.h"
#include "internal_message_handler.h"

using namespace ExternalMessage;

class CBSExternalMessageHandler : public INetEventHandler
{
public:
	virtual void OnAccepted(ISocketAcceptor* pSocketAcceptor, ISocketSession* pSocketSession);
	virtual void OnConnected(ISocketSession* pSocketSession);
	virtual void OnRecv(ISocketSession* pSocketSession, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize);
	virtual void OnDisconnected(ISocketSession* pSocketSession, BOOL bRemoteShutdown);

public:
	CBSExternalMessageHandler();
	~CBSExternalMessageHandler();

	BOOL Init(INet* pNet, IPacketAllocator* pPacketAllocator);
	BOOL UnInit(void);
	static CBSExternalMessageHandler& GetInstance(void);

public:
	BOOL DoQueryGateAck(UINT32 dwAddr, UINT16 wPort, ISocketSession* psession);
private:
	BOOL _Send(ISocketSession* pCliSession, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, INT32 nOffset=0);

private:
	INet*                                       m_pNet;
	IPacketAllocator*                           m_pPacketAllocator;
	static CBSExternalMessageHandler            ms_Instance;
};

#endif // _BS_EXTERNAL_MESSAGE_HANDLER_H_