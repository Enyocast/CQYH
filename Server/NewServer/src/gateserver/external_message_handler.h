#ifndef _EXTERNAL_MESSAGE_HANDLER_H_
#define _EXTERNAL_MESSAGE_HANDLER_H_

#include "net.h"
#include "external_message_header.h"

struct CLIENT_SESSION;
struct TRIE_NODE;

class CExternalMessageHandler : public INetEventHandler
{
public:
    virtual void OnAccepted(ISocketAcceptor* pSocketAcceptor, ISocketSession* pSocketSession);
    virtual void OnConnected(ISocketSession* pSocketSession);
    virtual void OnRecv(ISocketSession* pSocketSession, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize);
    virtual void OnDisconnected(ISocketSession* pSocketSession, BOOL bPassiveShutdown);

public:
    CExternalMessageHandler();
    virtual ~CExternalMessageHandler();

    BOOL Init(INet* pNet, IPacketAllocator* pPacketAllocator);
    BOOL UnInit(void);
    static CExternalMessageHandler& GetInstance(void);

public:
    BOOL Send(UINT32 dwSessionID, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, INT32 nOffset = 0);

    void DoErrorNotify(UINT32 dwSessionID, INT32 nErrorCode, INT32 nParam1, INT32 nParam2);
    void DoLoginAck(UINT32 dwSessionID);
    void DoSyncRoleList(UINT32 dwSessionID, INT32 nRoleCount, CHAR BaseData[]);
    void DoSelectRoleAck(UINT32 dwSessionID, UINT32 dwRoleID);
    void DoCreateRoleAck(UINT32 dwSessionID, CHAR BaseData[]);
    void DoDeleteRoleAck(UINT32 dwSessionID, UINT32 dwRoleID);
    void DoUnDeleteRoleAck(UINT32 dwSessionID, UINT32 dwRoleID);
    void DoForeverDeleteRoleAck(UINT32 dwSessionID, UINT32 dwRoleID);
	void DoReturnSelectRole(UINT32 dwSessionID);

    void DoPingAck(UINT32 dwSessionID, UINT32 dwPingTick);

private:
    BOOL OnLoginReq(CLIENT_SESSION* pSession, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize);
    BOOL OnSelectRole(CLIENT_SESSION* pSession, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize);
    BOOL OnCreateRole(CLIENT_SESSION* pSession, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize);
    BOOL OnDeleteRole(CLIENT_SESSION* pSession, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize);
    BOOL OnUnDeleteRole(CLIENT_SESSION* pSession, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize);
    BOOL OnForeverDeleteRole(CLIENT_SESSION* pSession, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize);
    BOOL OnPing(CLIENT_SESSION* pSession, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize);

	BOOL Send(CLIENT_SESSION* pCliSession, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, INT32 nOffset);
private:
	inline BOOL _CheckCensoredWord(const char* pcszText);

private:
    INet*                               m_pNet;
    IPacketAllocator*                   m_pPacketAllocator;
	ISocketAcceptor*					m_pClientSocketAcceptor;
    static CExternalMessageHandler      ms_Instance;
    TRIE_NODE*                          m_pRoot;

    typedef BOOL (CExternalMessageHandler::*MESSAGE_FUNC)(CLIENT_SESSION* pSession, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize);
    MESSAGE_FUNC                        m_MessageFuncList[ExternalMessage::max_message_count];
};

#endif  // _EXTERNAL_MESSAGE_HANDLER_H_