#ifndef _SESSION_MGR_H_
#define _SESSION_MGR_H_

#include <list>
#include "base_list.h"

#include "id_object_pool.h"

#include "server_def.h"
#include "string_def.h"
#include "role_def.h"

class INet;
class ISocketSession;

enum CLIENT_SESSION_STATE
{
	cssInvalid,

	cssUnAuthed,
	cssLSAuthing,
	cssMSAuthing,
	cssInQueue,
	cssAuthed,
	cssRoleOperating,
    cssCreatingRole,
	cssDeletingRole,
	cssEnteringGame,
	cssPlaying,
	cssReturnSelectRole,

	cssTotal
};

struct BASE_SESSION : BASE_LIST_NODE
{
	UINT8               byType;
	ISocketSession*     pSocketSession;
	UINT64              qwTimer;
	UINT32				dwReportTime;
};

struct CLIENT_SESSION : BASE_SESSION
{
	UINT8               bConnected;
	UINT8				byShutDownType;
	UINT8				byServerGroup;
	UINT8               bAdult;            // 成年
	UINT32              dwSessionID;
	UINT32              dwGSSessionID;
	INT32               eState;
	char                szOASessionID[OA_SESSION_ID_LEN];
	char                szPGT[OA_PGT_FIELD_LEN];
	char                szUserName[USER_NAME_LEN];
	char                szPassword[USER_PASSWORD_LEN];
	UINT16				wClientPort;
	UINT8				bIpWhiteList;
	UINT8				bUserWhiteList;
	UINT8				byEncryptCode;
	UINT8               byRoleCount;
	UINT32				dwClientIp;

	char                szMac[MAC_ADDRESS_LEN];
	struct ROLE_BRIEF_INFO
	{
		UINT32              dwRoleID;
		UINT32              dwSaveTime;

		INT32               nSceneTemplateID;
		INT32               nSceneID;
		INT32               nX;
		INT32               nY;
		INT32               nZ;
		UINT16              wFaceDirection;

		INT32	            nReturnSceneTemplateID;
		INT32	            nReturnSceneID;
		INT32	            nReturnX;
		INT32	            nReturnY;
		INT32	            nReturnZ;
		UINT16	            wReturnFaceDirection;
		UINT8               byDeleted;
	}                   RoleList[MAX_ROLE_PER_USER];
};

struct GS_SESSION : BASE_SESSION
{
	UINT32              dwSessionID;
};

struct DB_SESSION : BASE_SESSION
{
	UINT8               bConnected;
	UINT32              dwAddr;
	UINT16              wPort;
};

struct MS_SESSION : BASE_SESSION
{
	UINT8               bConnected;
};

struct LS_SESSION : BASE_SESSION
{
	UINT8               bConnected;
	UINT32              dwAddr;
	UINT16              wPort;
};

struct GD_SESSION : BASE_SESSION
{
	UINT8               bConnected;
};

class CGTSessionMgr
{
public:
	CGTSessionMgr();
	~CGTSessionMgr();

	BOOL Init(INet* pExternalNet, INet* pInternalNet);
	BOOL UnInit(void);
	static CGTSessionMgr& GetInstance(void);

	CLIENT_SESSION* NewClientSession(void);
	void DelClientSession(CLIENT_SESSION* pClientSession);
	CLIENT_SESSION* FindClientSession(UINT32 dwSessionID);
	INT32 GetClientSessionCount(void);

	inline GS_SESSION* GetGSSession(UINT32 dwGSSessionID);
	inline MS_SESSION& GetMSSession(void);
	inline LS_SESSION& GetLSSession(void);
	inline DB_SESSION& GetDBSession(void);
	inline GD_SESSION& GetGDSession(void);

	inline INT32 GetServerState(void);
	inline void SetServerState(INT32 eServerState);

	inline void SetOpenned(INT32 nServerGroupID, BOOL bOpened);
	inline BOOL IsOpened(INT32 nServerGroupID);

	inline UINT32 GetSelfSessionID(void);
	inline void SetSelfSessionID(UINT32 dwGTSessionID);

	BOOL CloseAllClientSession(void);
	BOOL IsAllClientSessionClosed(void);

	BOOL CheckSession();
	BOOL CloseAllSession();

	BOOL MainLoop(void);
private:
	static CGTSessionMgr					ms_Instance;
	INT32                                   m_eServerState;
	BOOL									m_bOpened[MAX_SERVER_GROUP_COUNT];
	UINT32                                  m_dwGTSessionID;
	UINT64                                  m_qwLastPingTick;
	UINT64                                  m_qwLastStatisTick;

	INet*                                   m_pExternalNet;
	INet*                                   m_pInternalNet;

	CLIENT_SESSION                          m_ClientSessionPool[MAX_CLIENT_SESSION_COUNT];
	typedef std::list<CLIENT_SESSION*>      FREE_CLIENT_SESSION_LIST;
	FREE_CLIENT_SESSION_LIST                m_FreeClientSessionList;
	CBaseList                               m_UsedClientSessionList;

	GS_SESSION                              m_GSSession[MAX_GS_SESSION_COUNT];
	DB_SESSION                              m_DBSession;
	LS_SESSION                              m_LSSession;
	MS_SESSION                              m_MSSession;
	GD_SESSION                              m_GDSession;
};

#include "gt_session_mgr.inl"

#endif  // _SESSION_MGR_H_