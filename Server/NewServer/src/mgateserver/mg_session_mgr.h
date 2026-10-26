#ifndef _MG_SESSION_MGR_H_
#define _MG_SESSION_MGR_H_

#include <list>
#include "base_list.h"

#include "id_object_pool.h"

#include "server_def.h"
#include "string_def.h"
#include "role_def.h"

class INet;
class ISocketSession;

struct BASE_SESSION : BASE_LIST_NODE
{
	UINT8               byType;
	ISocketSession*     pSocketSession;
	UINT64              qwTimer;
	UINT32				dwReportTime;
};

struct MG_CLIENT_SESSION : BASE_SESSION
{
	UINT8               bConnected;
	UINT8				byShutDownType;
	UINT8				byServerGroup;
	UINT8				bIpWhiteList;
	UINT32              dwSessionID;
	UINT32				dwClientIp;
	UINT16				wClientPort;
	char                szMac[MAC_ADDRESS_LEN];
};

struct MM_SESSION : BASE_SESSION
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

class CMGSessionMgr
{
public:
	CMGSessionMgr();
	~CMGSessionMgr();

	BOOL Init(INet* pExternalNet, INet* pInternalNet);
	BOOL UnInit(void);
	static CMGSessionMgr& GetInstance(void);

	MG_CLIENT_SESSION* NewClientSession(void);
	void DelClientSession(MG_CLIENT_SESSION* pClientSession);
	MG_CLIENT_SESSION* FindClientSession(UINT32 dwSessionID);
	INT32 GetClientSessionCount(void);

	inline MM_SESSION& GetMMSession(void);
	inline LS_SESSION& GetLSSession(void);
	inline GD_SESSION& GetGDSession(void);

	inline INT32 GetServerState(void);
	inline void SetServerState(INT32 eServerState);

	inline void SetOpenned(INT32 nServerGroupID, BOOL bOpened);
	inline BOOL IsOpened(INT32 nServerGroupID);

	inline UINT32 GetSelfSessionID(void);
	inline void SetSelfSessionID(UINT32 dwMGSessionID);

	BOOL CloseAllClientSession(void);
	BOOL IsAllClientSessionClosed(void);

	BOOL CheckSession();
	BOOL CloseAllSession();

	BOOL MainLoop(void);
private:
	static CMGSessionMgr					ms_Instance;
	INT32                                   m_eServerState;
	BOOL									m_bOpened[MAX_SERVER_GROUP_COUNT];
	UINT32                                  m_dwMGSessionID;
	UINT64                                  m_qwLastPingTick;

	INet*                                   m_pExternalNet;
	INet*                                   m_pInternalNet;

	MG_CLIENT_SESSION                       m_ClientSessionPool[MAX_CLIENT_SESSION_COUNT];
	typedef std::list<MG_CLIENT_SESSION*>   FREE_MG_CLIENT_SESSION_LIST;
	FREE_MG_CLIENT_SESSION_LIST             m_FreeClientSessionList;
	CBaseList                               m_UsedClientSessionList;

	LS_SESSION                              m_LSSession;
	MM_SESSION                              m_MMSession;
	GD_SESSION                              m_GDSession;
};

#include "mg_session_mgr.inl"

#endif  // _MG_SESSION_MGR_H_