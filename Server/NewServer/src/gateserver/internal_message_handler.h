#ifndef _INTERNAL_MESSAGE_HANDLER_H_
#define _INTERNAL_MESSAGE_HANDLER_H_

#include "net.h"
#include "internal_message_header.h"

struct BASE_SESSION;

struct CreateRoleParam
{
    UINT8 byClass;
    UINT8 bySex;
    UINT8 byHairType;
    UINT8 byHairColor;
    UINT8 byFaceType;
    UINT8 bySkinColor;
};

#define NOTIFY_GD(__level__, __str_content__, ...)													\
    do																							\
	{																							\
        CInternalMessageHandler::GetInstance().DoGDNotify(__level__, __str_content__, ##__VA_ARGS__);	\
	} while (0)

class CInternalMessageHandler : public INetEventHandler
{
public:
	virtual void OnAccepted(ISocketAcceptor* pSocketAcceptor, ISocketSession* pSocketSession);
	virtual void OnConnected(ISocketSession* pSocketSession);
	virtual void OnRecv(ISocketSession* pSocketSession, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize);
	virtual void OnDisconnected(ISocketSession* pSocketSession, BOOL bRemoteShutdown);

public:
	CInternalMessageHandler();
	virtual ~CInternalMessageHandler();

	BOOL Init(INet* pNet, IPacketAllocator* pPacketAllocator);
	BOOL UnInit(void);
	static CInternalMessageHandler& GetInstance(void);

public:
	/************************************************************************/
	// To All
	BOOL DoAllPing(void);

	// To GD
	BOOL DoGDRegister(void);
	BOOL DoGDNotify(UINT8 byLevel, const char* szContent, ...);
	/************************************************************************/
	// To MS
	BOOL DoMSRegister(void);
	BOOL DoMSReady(void);
	BOOL DoMSCloseAck(void);

	BOOL DoMSEnterGate(UINT32 dwClientSessionID);
	BOOL DoMSQueryScene(UINT32 dwClientSessionID, UINT32 dwRoleID);
	BOOL DoMSClientMsg(UINT32 dwClientSessionID, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize);
	BOOL DoMSClientShutdown(UINT32 dwClientSessionID, UINT8 byClientShutDownType);
	BOOL DoMSReturnSelectRole(UINT32 dwClientSessionID);
	BOOL DoMSChangeGSAck(UINT32 dwClientSessionID);
	BOOL DoMSCheckNewName(UINT32 dwClientSessionID, const char* szName, const char* UserData, UINT32 dwUserDataLen);

	/************************************************************************/
	// To GS
	BOOL DoGSRegisterAck(UINT32 dwGSSessionID);
	BOOL DoGSClientMsg(UINT32 dwGSSessionID, UINT32 dwSessionID, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize);
	BOOL DoGSRoleEnter(UINT32 dwGSSessionID, UINT32 dwClientSessionID, UINT32 dwRoleID);

	/************************************************************************/
	// To LS
	BOOL DoLSRegister(void);
	BOOL DoLSLoginReq(UINT32 dwSessionID, CHAR szUserName[], CHAR szPassword[], CHAR szOASessionID[]);

	/************************************************************************/
	// To DB
	BOOL DoDBRegister(void);
	BOOL DoDBQueryRoleList(UINT32 dwSessionID);
	BOOL DoDBCreateRole(UINT32 dwSessionID, UINT32 dwRoleID, CHAR szRoleName[], UINT8 bySex, UINT8 byClass,
		UINT8 byHairType, UINT8 byHairColor, UINT8 byFaceType, UINT8 bySkinColor);
	BOOL DoDBDeleteRole(UINT32 dwSessionID, UINT32 dwRoleID);
	BOOL DoDBUnDeleteRole(UINT32 dwSessionID, UINT32 dwRoleID);
    BOOL DoDBForeverDeleteRole(UINT32 dwSessionID, UINT32 dwRoleID);

private:
	/************************************************************************/
	// From All
	void OnAllPing(ISocketSession* pSocketSession, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize);

	/************************************************************************/
	// From MS
	void OnMSRegisterAck(ISocketSession* pSocketSession, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize);
	void OnMSServerInfo(ISocketSession* pSocketSession, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize);
	void OnMSAllReady(ISocketSession* pSocketSession, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize);
	void OnMSClose(ISocketSession* pSocketSession, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize);

	void OnMSEnterGateAck(ISocketSession* pSocketSession, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize);
	void OnMSQuerySceneAck(ISocketSession* pSocketSession, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize);
	void OnMSCloseClientSession(ISocketSession* pSocketSession, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize);
	void OnMSReturnSelectRole(ISocketSession* pSocketSession, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize);
	void OnMSChangeGS(ISocketSession* pSocketSession, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize);

	void OnMSClientMsg(ISocketSession* pSocketSession, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize);
	void OnMSBroadcastClientMsg(ISocketSession* pSocketSession, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize);
	void OnMSSwitchServerState(ISocketSession* pSocketSession, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize);
	void OnMSGMCommand(ISocketSession* pSocketSession, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize);
	void OnMSCheckNewName(ISocketSession* pSocketSession, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize);

	/************************************************************************/
	// From GS
	void OnGSRegister(ISocketSession* pSocketSession, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize);
	void OnGSCloseClientSession(ISocketSession* pSocketSession, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize);
	void OnGSClientMsg(ISocketSession* pSocketSession, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize);
	void OnGSBroadcastClientMsg(ISocketSession* pSocketSession, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize);
	void OnGSReturnSelectRole(ISocketSession* pSocketSession, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize);
	/************************************************************************/
	// From LS
	void OnLSRegisterAck(ISocketSession* pSocketSession, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize);
	void OnLSLoginAck(ISocketSession* pSocketSession, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize);

	/************************************************************************/
	// From DB
	void OnDBRegisterAck(ISocketSession* pSocketSession, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize);
	void OnDBSyncRoleList(ISocketSession* pSocketSession, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize);
	void OnDBCreateRoleAck(ISocketSession* pSocketSession, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize);
	void OnDBDeleteRoleAck(ISocketSession* pSocketSession, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize);
	void OnDBUnDeleteRoleAck(ISocketSession* pSocketSession, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize);
    void OnDBForeverDeleteRoleAck(ISocketSession* pSocketSession, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize); 
    void OnDBCloseClientSession(ISocketSession* pSocketSession, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize);

	/************************************************************************/
	// From NS

private:
	inline BOOL _SendMS(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, INT32 nOffset = 0);
	inline BOOL _SendGS(UINT32 dwGSSessionID, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, INT32 nOffset = 0);
	inline BOOL _SendLS(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, INT32 nOffset = 0);
	inline BOOL _SendDB(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, INT32 nOffset = 0);
	inline BOOL _SendGD(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, INT32 nOffset = 0);

	inline void _CheckReady(void);

private:
	INet*                               m_pNet;
	IPacketAllocator*                   m_pPacketAllocator;
	static CInternalMessageHandler      ms_Instance;

	typedef void (CInternalMessageHandler::*MESSAGE_FUNC)(ISocketSession* pSocketSession, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize);
	MESSAGE_FUNC                        m_MessageFuncList[InternalMessage::max_message_count];
};

#endif  // _INTERNAL_MESSAGE_HANDLER_H_