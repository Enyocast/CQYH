#ifndef _GS_SESSION_MGR_H_
#define _GS_SESSION_MGR_H_

#include <list>
#include <map>
#include "base_list.h"
#include "server_def.h"

class INet;
class ISocketSession;
class CRole;

struct GS_BASE_SESSION : BASE_LIST_NODE
{
    UINT8               byType;
    UINT8               bConnected;
    ISocketSession*     pSocketSession;
    UINT64              qwTimer;
};

struct GT_SESSION : GS_BASE_SESSION
{
    UINT32              dwSessionID;
    UINT32              dwAddr;
    UINT16              wPort;
};

struct MS_SESSION : GS_BASE_SESSION
{
};

struct DB_SESSION : GS_BASE_SESSION
{
    UINT8				byReady;
	UINT32              dwAddr;
    UINT16              wPort;
};

struct DL_SESSION : GS_BASE_SESSION
{
	UINT8				byReady;
	UINT32				dwAddr;
	UINT16              wPort;
};

struct GD_SESSION : GS_BASE_SESSION
{

};

class CGSSessionMgr
{
public:
    CGSSessionMgr();
    ~CGSSessionMgr();

    BOOL Init(INet* pNet);
    BOOL UnInit(void);
    BOOL MainLoop(void);

    static CGSSessionMgr& GetInstance(void);

    BOOL CheckSession();
    BOOL CloseAllSession();

    inline GT_SESSION* GetGTSession(UINT32 dwGTSessionID);
	inline MS_SESSION& GetMSSession(void);
	inline DB_SESSION& GetDBSession(void);
	inline GD_SESSION& GetGDSession(void);
	inline DL_SESSION& GetDLSession(void);

    INT32 GetServerState(void);
    void SetServerState(INT32 eServerState);

    UINT32 GetSelfSessionID(void);
    void SetSelfSessionID(UINT32 dwGSSessionID);

    BOOL AttachRoleToSession(UINT32 dwClientSessionID, CRole* poRole);
    BOOL DetachRoleFromSession(UINT32 dwClientSessionID);
    CRole* FindRoleBySessionID(UINT32 dwClientSessionID);

private:
    static CGSSessionMgr                    ms_Instance;
    INT32                                   m_eServerState;
    UINT32                                  m_dwGSSessionID;
	UINT64                                  m_qwLastPingTick;

    INet*                                   m_pNet;

    GT_SESSION                              m_GTSession[MAX_GT_SESSION_COUNT];
    MS_SESSION                              m_MSSession;
    DB_SESSION                              m_DBSession;
    GD_SESSION                              m_GDSession;
	DL_SESSION								m_DLSession;

    typedef std::map<UINT32, CRole*>        MAP_SESSION_2_ROLE;
    MAP_SESSION_2_ROLE                      m_mapSession2Role;
};

inline GT_SESSION* CGSSessionMgr::GetGTSession(UINT32 dwGTSessionID)
{
	LOG_PROCESS_ERROR(dwGTSessionID > 0 && dwGTSessionID < MAX_GT_SESSION_COUNT);

	return m_GTSession + dwGTSessionID;
Exit0:
	return NULL;
}

inline MS_SESSION& CGSSessionMgr::GetMSSession(void)
{
	return m_MSSession;
}

inline DB_SESSION& CGSSessionMgr::GetDBSession(void)
{
	return m_DBSession;
}

inline GD_SESSION& CGSSessionMgr::GetGDSession(void)
{
	return m_GDSession;
}

inline DL_SESSION& CGSSessionMgr::GetDLSession(void)
{
	return m_DLSession;
}

#endif  // _GS_SESSION_MGR_H_