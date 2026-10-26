#ifndef _EXTERNAL_MESSAGE_HANDLER_H_
#define _EXTERNAL_MESSAGE_HANDLER_H_

#include "net.h"
#include "external_message_header.h"

struct MG_CLIENT_SESSION;

class CMGExternalMessageHandler : public INetEventHandler
{
public:
	virtual void OnAccepted(ISocketAcceptor* pSocketAcceptor, ISocketSession* pSocketSession);
	virtual void OnConnected(ISocketSession* pSocketSession);
	virtual void OnRecv(ISocketSession* pSocketSession, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize);
	virtual void OnDisconnected(ISocketSession* pSocketSession, BOOL bPassiveShutdown);

public:
	CMGExternalMessageHandler();
	virtual ~CMGExternalMessageHandler();

	BOOL Init(INet* pNet, IPacketAllocator* pPacketAllocator);
	BOOL UnInit(void);
	static CMGExternalMessageHandler& GetInstance(void);

private:
	BOOL OnClientMessage(MG_CLIENT_SESSION* pSession, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize);

private:
	BOOL Send(UINT32 dwSessionID, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, INT32 nOffset = 0);

private:
	INet*                               m_pNet;
	IPacketAllocator*                   m_pPacketAllocator;
	ISocketAcceptor*					m_pClientSocketAcceptor;
	static CMGExternalMessageHandler	ms_Instance;

	typedef BOOL(CMGExternalMessageHandler::*MESSAGE_FUNC)(MG_CLIENT_SESSION* pSession, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize);
	MESSAGE_FUNC                        m_MessageFuncList[ExternalMessage::max_message_count];
};

#endif  // _EXTERNAL_MESSAGE_HANDLER_H_