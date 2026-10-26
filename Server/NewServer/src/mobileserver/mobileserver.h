#ifndef _MOBILE_SERVER_H_
#define _MOBILE_SERVER_H_

#include "server_def.h"
#include "mm_message_handler.h"
#include "packet_allocator.h"

class INet;
class ISocketAcceptor;

class CMobileServer
{
public:
	CMobileServer();
	~CMobileServer();

	static CMobileServer& GetInstance(void);

	BOOL Init(INetEventHandler* poMessageHandler);
	BOOL UnInit(void);

	BOOL MainLoop(void);
	BOOL Close(void);

	INet* GetNet(void)							{ return m_pNet; }
	IPacketAllocator* GetPacketAllocator(void)  { return &m_PacketAllocator; }

private:
	static CMobileServer      ms_Instance;

	INet*                   m_pNet;
	CPacketAllocator        m_PacketAllocator;
	ISocketAcceptor*		m_pSocketAcceptor;
};

#endif  // _MOBILE_SERVER_H_