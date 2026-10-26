#ifndef _MS_MESSAGE_HANDLER_H_
#define _MS_MESSAGE_HANDLER_H_

#include "robot_message_notifier.h"
#include "error_def.h"
#include "net.h"
#include "external_message_header.h"

class CUser;

class CAsimovMessageHandler : public INetEventHandler
{
public:
    virtual void OnAccepted(ISocketAcceptor* pSocketAcceptor, ISocketSession* pSocketSession);
    virtual void OnConnected(ISocketSession* pSocketSession);
    virtual void OnRecv(ISocketSession* pSocketSession, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize);
    virtual void OnDisconnected(ISocketSession* pSocketSession, BOOL bRemoteShutdown);

public:
    CAsimovMessageHandler();
    ~CAsimovMessageHandler();

    virtual BOOL Init(INet* pNet, IPacketAllocator* pPacketAllocator);
    virtual BOOL UnInit(void);

    static CAsimovMessageHandler& GetInstance(void);
private:
    void OnGTErrorNotify(CUser* poUser, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize);
	void OnMSErrorNotify(CUser* poUser, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize);
	void OnGSErrorNotify(CUser* poUser, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize);
	void OnLoginAck(CUser* poUser, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize);
    void OnSelectRoleAck(CUser* poUser, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize);
    void OnSyncRoleList(CUser* poUser, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize);
    void OnCreateRoleAck(CUser* poUser, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize);
    void OnDeleteRoleAck(CUser* poUser, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize);
    void OnLeaveScene(CUser* poUser, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize);
    void OnSyncGameDataEnd(CUser* poUser, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize);
    void OnChangeSceneEnter(CUser* poUser, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize);
	void OnQueryGateAck(CUser* poUser, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize);
    void OnGatePingAck(CUser* poUser, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize);
    void OnGamePingAck(CUser* poUser, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize);

	void OnSyncRoleAttrData(CUser* poUser, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize);
	void OnSyncRoleEquipData(CUser* poUser, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize);
	void OnSyncRoleSpiritData(CUser* poUser, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize);
	void OnSyncRoleSpellData(CUser* poUser, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize);

	void OnSyncRolePow(CUser* poUser, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize);

protected:
    static CAsimovMessageHandler    ms_AsimovInstance;
    CRobotMessageNotifier           m_Notifier;
    INet*                           m_poNet;
    IPacketAllocator*               m_pPacketAllocator;

    typedef void (CAsimovMessageHandler::*ASIMOV_MESSAGE_FUNC)(CUser* poUser, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize);
    ASIMOV_MESSAGE_FUNC  m_AsimovMessageFuncList[ExternalMessage::max_message_count];
};

#endif  // _MESSAGE_HANDLER_H_