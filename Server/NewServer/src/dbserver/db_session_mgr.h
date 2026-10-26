#ifndef _SESSION_MGR_H_
#define _SESSION_MGR_H_

#include <list>
#include "base_list.h"

#include "id_object_pool.h"

#include "server_def.h"

class INet;
class ISocketSession;

struct DB_BASE_SESSION
{
    UINT32              dwType;
    ISocketSession*     pSocketSession;
    UINT64              qwTimer;
};

struct GS_SESSION : DB_BASE_SESSION
{
    UINT32              dwSessionID;
};

struct GT_SESSION : DB_BASE_SESSION
{
    UINT32              dwSessionID;
};

struct MS_SESSION : DB_BASE_SESSION
{
    UINT8               bConnected;
};

struct GD_SESSION : DB_BASE_SESSION
{
    UINT8               bConnected;
};

class CDBSessionMgr
{
public:
    CDBSessionMgr();
    ~CDBSessionMgr();

    BOOL Init(INet* pInternalNet);
    BOOL UnInit(void);
    static CDBSessionMgr& GetInstance(void);

    inline GS_SESSION* GetGSSession(UINT32 dwGSSessionID);
    inline GT_SESSION* GetGTSession(UINT32 dwGSSessionID);
    inline MS_SESSION& GetMSSession(void);
    inline GD_SESSION& GetGDSession(void);

    inline INT32 GetServerState(void);
    inline void SetServerState(INT32 eServerState);

    BOOL CheckSession();
    BOOL CloseAllSession();

    BOOL MainLoop(void);

private:
    static CDBSessionMgr                    ms_Instance;
    INT32                                   m_eServerState;
	UINT64                                  m_qwLastPingTick;
	UINT64                                  m_qwLastStatisTick;

    INet*                                   m_pNet;

    GS_SESSION                              m_GSSession[MAX_GS_SESSION_COUNT];
    GT_SESSION                              m_GTSession[MAX_GT_SESSION_COUNT];
    MS_SESSION                              m_MSSession;
    GD_SESSION                              m_GDSession;
};

#include "db_session_mgr.inl"

#endif  // _SESSION_MGR_H_