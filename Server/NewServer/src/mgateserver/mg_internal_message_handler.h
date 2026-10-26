#ifndef _INTERNAL_MESSAGE_HANDLER_H_
#define _INTERNAL_MESSAGE_HANDLER_H_

#include "net.h"
#include "internal_message_header.h"

struct BASE_SESSION;

class CMGInternalMessageHandler : public INetEventHandler
{
public:
	virtual void OnAccepted(ISocketAcceptor* pSocketAcceptor, ISocketSession* pSocketSession);
	virtual void OnConnected(ISocketSession* pSocketSession);
	virtual void OnRecv(ISocketSession* pSocketSession, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize);
	virtual void OnDisconnected(ISocketSession* pSocketSession, BOOL bRemoteShutdown);

public:
	CMGInternalMessageHandler();
	virtual ~CMGInternalMessageHandler();

	BOOL Init(INet* pNet, IPacketAllocator* pPacketAllocator);
	BOOL UnInit(void);
	static CMGInternalMessageHandler& GetInstance(void);

public:
	/************************************************************************/
	// To All
	BOOL DoAllPing(void);

	// To GD
	BOOL DoGDRegister(void);
	/************************************************************************/
	// To MM
	BOOL DoMMRegister(void);
	BOOL DoMMReady(void);
	BOOL DoMMCloseAck(void);

	/************************************************************************/
	// To LS
	BOOL DoLSRegister(void);
	BOOL DoLSLoginReq(UINT32 dwSessionID, CHAR szUserName[], CHAR szOASessionID[]);

private:
	/************************************************************************/
	// From All
	void OnAllPing(ISocketSession* pSocketSession, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize);

	/************************************************************************/
	// From MM
	void OnMMRegisterAck(ISocketSession* pSocketSession, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize);
	void OnMMServerInfo(ISocketSession* pSocketSession, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize);
	void OnMMAllReady(ISocketSession* pSocketSession, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize);
	void OnMMClose(ISocketSession* pSocketSession, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize);

	/************************************************************************/
	// From LS
	void OnLSRegisterAck(ISocketSession* pSocketSession, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize);
	void OnLSLoginAck(ISocketSession* pSocketSession, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize);

private:
	inline BOOL _SendMM(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, INT32 nOffset = 0);
	inline BOOL _SendLS(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, INT32 nOffset = 0);
	inline BOOL _SendGD(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, INT32 nOffset = 0);

	inline void _CheckReady(void);

private:
	INet*                               m_pNet;
	IPacketAllocator*                   m_pPacketAllocator;
	static CMGInternalMessageHandler	ms_Instance;

	typedef void (CMGInternalMessageHandler::*MESSAGE_FUNC)(ISocketSession* pSocketSession, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize);
	MESSAGE_FUNC                        m_MessageFuncList[InternalMessage::max_message_count];
};

#endif  // _INTERNAL_MESSAGE_HANDLER_H_