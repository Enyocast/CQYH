#ifndef _BALANCE_SERVER_H_
#define _BALANCE_SERVER_H_

#include "external_message_handler.h"
#include "internal_message_handler.h"
#include "packet_allocator.h"

class INet;
class ISocketAcceptor;

class CBalanceServer
{
public:
	CBalanceServer();
	~CBalanceServer();

	static CBalanceServer& GetInstance(void);

	BOOL Init(INetEventHandler* poInterMessageHandler, INetEventHandler* poExternalMessageHandler);
	BOOL UnInit(void);

	BOOL MainLoop(void);
	BOOL Close(void);

	INet* GetExternalNet(void)                  {return m_pExternalNet;}
	INet* GetInternalNet(void)                  {return m_pInternalNet;}
	IPacketAllocator* GetPacketAllocator(void)  {return &m_PacketAllocator;}

	ISocketAcceptor*	GetGTSocketAcceptor(void) {return m_pGTSocketAcceptor;}

private:
	static CBalanceServer      ms_Instance;

	INet*                   m_pExternalNet;
	INet*                   m_pInternalNet;
	ISocketAcceptor*        m_pGTSocketAcceptor;

	CPacketAllocator        m_PacketAllocator;

	INT32					m_nExternalAddrCount;
	ISocketAcceptor*        m_pClientSocketAcceptor[MAX_EXTERNAL_IP_COUNT];
	UINT32					m_dwExternalAddr[MAX_EXTERNAL_IP_COUNT];
};

#endif  // _BALANCE_SERVER_H_