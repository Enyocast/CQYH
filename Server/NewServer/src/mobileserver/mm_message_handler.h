#ifndef _MM_MESSAGE_HANDLER_H_
#define _MM_MESSAGE_HANDLER_H_

#include "net.h"
#include "internal_message_header.h"
#include "common_message.h"

class CMMMesageHandler : public INetEventHandler
{
public:
	virtual void OnAccepted(ISocketAcceptor* pSocketAcceptor, ISocketSession* pSocketSession);
	virtual void OnConnected(ISocketSession* pSocketSession);
	virtual void OnRecv(ISocketSession* pSocketSession, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize);
	virtual void OnDisconnected(ISocketSession* pSocketSession, BOOL bRemoteShutdown);

public:
	CMMMesageHandler();
	virtual ~CMMMesageHandler();

	BOOL Init(INet* pNet, IPacketAllocator* pPacketAllocator);
	BOOL UnInit(void);
	static CMMMesageHandler& GetInstance(void);

public:
	/************************************************************************/
	// To All
	BOOL DoAllPing(void);

	// To GD
	BOOL DoGDRegister(void);
	/************************************************************************/
	// To MS
	BOOL DoMSRegister(UINT32 dwAddr, UINT16 wPort);
	BOOL DoMSReady(void);
	BOOL DoMSCloseAck(void);

	/************************************************************************/
	// To MG
	BOOL DoMGRegisterAck(UINT32 dwMGSessionID);
	BOOL DoMGServerInfo(UINT32 dwMGSessionID);
	BOOL DoMGCloseClientSession(UINT32 dwClientSessionID);
	BOOL DoMGAllReady(void);

private:
	/************************************************************************/
	// From All
	void OnAllPing(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);

	/************************************************************************/
	// From MS
	void OnMSRegisterAck(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
	void OnMSServerInfo(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
	void OnMSAllReady(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
	void OnMSClose(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);

	/************************************************************************/
	// From MG
	void OnMGRegister(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
	void OnMGReady(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);

private:
	inline BOOL _SendGD(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, INT32 nOffset = 0);
	inline BOOL _SendMS(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, INT32 nOffset = 0);
	inline BOOL _SendMG(UINT32 dwMGSessionID, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, INT32 nOffset = 0);
	inline BOOL _BroadcastMG(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, INT32 nOffset = 0);

	void _CheckAllReady(void);

private:
	INet*                               m_pNet;
	IPacketAllocator*                   m_pPacketAllocator;
	static CMMMesageHandler				ms_Instance;
	InternalMessage::M2A_SERVER_INFO	m_ServerInfo;

	typedef void (CMMMesageHandler::*MESSAGE_FUNC)(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
	MESSAGE_FUNC                        m_MessageFuncList[InternalMessage::max_message_count];
};

#endif	// _MM_MESSAGE_HANDLER_H_