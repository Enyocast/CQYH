#ifndef _BS_INTERNAL_MESSAGE_HANDLER_H_
#define _BS_INTERNAL_MESSAGE_HANDLER_H_

#include "net.h"
#include "internal_message_header.h"

using namespace InternalMessage;

struct BASE_SESSION;

struct SGTInfo
{
	INT32	nAddrCount;
    UINT32	dwAddr[MAX_EXTERNAL_IP_COUNT];
	UINT16  wPort[MAX_EXTERNAL_IP_COUNT];
};

class CBSInternalMessageHandler : public INetEventHandler
{
public:
	virtual void OnAccepted(ISocketAcceptor* pSocketAcceptor, ISocketSession* pSocketSession);
	virtual void OnConnected(ISocketSession* pSocketSession);
	virtual void OnRecv(ISocketSession* pSocketSession, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize);
	virtual void OnDisconnected(ISocketSession* pSocketSession, BOOL bRemoteShutdown);

public:
	CBSInternalMessageHandler();
	~CBSInternalMessageHandler();

	BOOL Init(INet* pNet, IPacketAllocator* pPacketAllocator, ISocketAcceptor* pSocketAcceptor);
	BOOL UnInit(void);
	static CBSInternalMessageHandler& GetInstance(void);
    
    inline SGTInfo* GetGTInfo(UINT32 dwGTSessionID);
public:
	/************************************************************************/
	// To ALL
	BOOL DoAllPing(void);

	// To GD
    BOOL DoGDRegister(void);

	// To MS
    BOOL DoMSRegister(UINT32 dwAddr, UINT16 wPort);
	BOOL DoMSReady(void);
	BOOL DoMSCloseAck(void);

private:
	/************************************************************************/
	// From GT
	void OnAllPing(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);

	// From MS
	void OnMSRegisterAck(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
	void OnMSAllReady(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
	void OnMSClose(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
	void OnMSServerInfo(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    //void OnMSReport(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);

private:
	inline BOOL _SendGT(UINT32 dwGTSessionID, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, INT32 nOffset = 0);
	inline BOOL _SendGD(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, INT32 nOffset = 0);
	inline BOOL _SendMS(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, INT32 nOffset = 0);

private:
	INet*                               m_pNet;
	IPacketAllocator*                   m_pPacketAllocator;
	ISocketAcceptor*					m_pGTSocketAcceptor;
	static CBSInternalMessageHandler            ms_Instance;

    SGTInfo                                 m_GTInfo[MAX_GT_SESSION_COUNT];
	typedef void (CBSInternalMessageHandler::*MESSAGE_FUNC)(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
	MESSAGE_FUNC                        m_MessageFuncList[InternalMessage::max_message_count];
};

inline SGTInfo* CBSInternalMessageHandler::GetGTInfo(UINT32 dwGTSessionID)
{
    LOG_PROCESS_ERROR(dwGTSessionID < MAX_GT_SESSION_COUNT);

    return m_GTInfo + dwGTSessionID;
Exit0:
    return NULL;
}

#endif // _BS_INTERNAL_MESSAGE_HANDLER_H_