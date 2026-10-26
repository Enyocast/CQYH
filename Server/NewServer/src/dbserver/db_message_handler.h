#ifndef _INTERNAL_MESSAGE_HANDLER_H_
#define _INTERNAL_MESSAGE_HANDLER_H_

#include "net.h"
#include "internal_message_header.h"

struct BASE_SESSION;
class CDBUser;

class CDBMessageHandler : public INetEventHandler
{
public:
    virtual void OnAccepted(ISocketAcceptor* pSocketAcceptor, ISocketSession* pSocketSession);
    virtual void OnConnected(ISocketSession* pSocketSession);
    virtual void OnRecv(ISocketSession* pSocketSession, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize);
    virtual void OnDisconnected(ISocketSession* pSocketSession, BOOL bRemoteShutdown);

public:
    CDBMessageHandler();
    virtual ~CDBMessageHandler();

    BOOL Init(INet* pNet, IPacketAllocator* pPacketAllocator);
    BOOL UnInit(void);
    static CDBMessageHandler& GetInstance(void);

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

    BOOL DoMSCreateRole(CDBUser* dbuser, void* pBaseData);
    BOOL DoMSCanDeleteRole(UINT32 dwClientSessionID, UINT32 dwRoleID);
    BOOL DoMSDeleteRole(UINT32 dwClientSessionID, UINT32 dwRoleID);
    BOOL DoMSLeaveDBAck(UINT32 dwClientSessionID);
    BOOL DoMSClearRoleCacheAck(UINT32 dwRoleID, UINT32 dwTLUserID, UINT32 dwCmdSerialID, UINT8 byResult);

    /************************************************************************/
    // To GS
    BOOL DoGSRegisterAck(UINT32 dwGSSessionID);
    BOOL DoGSLoadLockRoleDataAck(UINT32 dwGSSessionID, UINT32 dwClientSessionID, UINT32 dwRoleID, UINT32 dwDataSize, char* pData);
    BOOL DoGSUnlockRoleDataAck(UINT32 dwGSSessionID, UINT32 dwClientSessionID, UINT32 dwRoleID, INT32 nError);
    BOOL DoGSLoadLockRoleDataFailAck(UINT32 dwGSSessionID, UINT32 dwClientSessionID, UINT32 dwRoleID);

    /************************************************************************/
    // To GT
    BOOL DoGTRegisterAck(UINT32 dwGTSessionID);

    BOOL DoGTCloseClientSession(UINT32 dwClientSessionID);
    BOOL DoGTCreateRoleAck(UINT32 dwClientSessionID, INT32 nErrCode, void* pBaseData);
    BOOL DoGTDeleteRoleAck(UINT32 dwClientSessionID, INT32 nErrCode, UINT32 dwRoleID);
    BOOL DoGTUnDeleteRoleAck(UINT32 dwClientSessionID, INT32 nErrCode, UINT32 dwRoleID);
    BOOL DoGTForeverDeleteRoleAck(UINT32 dwClientSessionID, INT32 nErrCode, UINT32 dwRoleID);
    BOOL DoGTSyncRoleList(CDBUser* dbuser);

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

    void OnMSCreateRoleAck(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnMSCanDeleteRoleAck(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnMSDeleteRoleAck(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnMSLeaveDB(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnMSClearRoleCache(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
	void OnMSGMCommand(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);

    /************************************************************************/
    // From GS
    void OnGSRegister(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnGSLoadLockRoleData(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnGSSaveRoleData(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnGSUnlockRoleData(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);

    /************************************************************************/
    // From GT
    void OnGTRegister(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnGTQueryRoleList(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnGTCreateRole(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnGTDeleteRole(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnGTUnDeleteRole(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnGTForeverDeleteRole(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);

private:
    inline BOOL _SendGD(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, INT32 nOffset = 0);
    inline BOOL _SendMS(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, INT32 nOffset = 0);
    inline BOOL _SendGS(UINT32 dwGSSessionID, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, INT32 nOffset = 0);
    inline BOOL _SendGT(UINT32 dwGSSessionID, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, INT32 nOffset = 0);

private:
    INet*                               m_pNet;
    IPacketAllocator*                   m_pPacketAllocator;
    static CDBMessageHandler            ms_Instance;

    typedef void (CDBMessageHandler::*MESSAGE_FUNC)(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    MESSAGE_FUNC                        m_MessageFuncList[InternalMessage::max_message_count];
};



#endif  // _INTERNAL_MESSAGE_HANDLER_H_