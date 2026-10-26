#ifndef ns_message_handler_h__
#define ns_message_handler_h__

#include "net.h"
#include "internal_message_header.h"
#include "packet_allocator.h"

#define MAX_REMOTE_SERVER_COUNT (256)

struct REMOTE_SESSION
{
	INT32 nMessageVersion;
	INT32 nSessionIndex;
    UINT64 qwTimer;
};

class CNSMessageHandler : public INetEventHandler
{
public:
	virtual void OnAccepted(ISocketAcceptor* pSocketAcceptor, ISocketSession* pSocketSession);
	virtual void OnConnected(ISocketSession* pSocketSession);
	virtual void OnRecv(ISocketSession* pSocketSession, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize);
	virtual void OnDisconnected(ISocketSession* pSocketSession, BOOL bRemoteShutdown);

public:
	CNSMessageHandler(void);
	virtual ~CNSMessageHandler(void);
	static CNSMessageHandler& GetInstance(void);

	BOOL Init(void);
	BOOL UnInit(void);

	BOOL MainLoop(void);

    void DoNewNameResult(INT32 nSessionID, UINT32 dwCliSessionID, INT32 nErrCode, INT32 eType, UINT32 dwNewID, const char* szNewName, const char* UserData);

private:

	void _OnCheckVersion(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
	void _OnNewName(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
	void _OnAllPing(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);

	void _DoNewNameResult(ISocketSession* pSocketSession, UINT32 dwCliSessionID, INT32 nErrCode, INT32 eType, UINT32 dwNewID, const char* szNewName, const char* UserData);
	void _DoAllPing(void);

    typedef void (CNSMessageHandler::*MESSAGE_FUNC)(PACKET_BUFFER*, UINT32, ISocketSession*);
	static CNSMessageHandler ms_Instance;

    INet* m_pNet;
	INT32 m_nNetType;
	ISocketAcceptor* m_pAcceptor;
    CPacketAllocator m_PacketAllocator;

    MESSAGE_FUNC m_MessageFuncList[InternalMessage::max_message_count];

	ISocketSession* m_SessionList[MAX_REMOTE_SERVER_COUNT];
	INT32 m_nFreeSlotIndex;
	UINT64 m_qwLastPingTick;
};


#endif // ns_message_handler_h__

