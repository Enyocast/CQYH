#ifndef _SESSION_MGR_H_
#define _SESSION_MGR_H_

#include <list>
#include "base_list.h"
#include "server_def.h"

class INet;
class ISocketSession;

struct LS_BASE_SESSION : BASE_LIST_NODE
{
    UINT32              dwType;
    ISocketSession*     pSocketSession;
    UINT64              qwTimer;
};

struct GT_SESSION : LS_BASE_SESSION
{
    UINT32              dwSessionID;
};

struct MS_SESSION : LS_BASE_SESSION
{
    BOOL               bConnected;
};

struct GD_SESSION : LS_BASE_SESSION
{
    BOOL               bConnected;
};

struct MG_SESSION : LS_BASE_SESSION
{
	UINT32              dwSessionID;
};

class CLSSessionMgr
{
public:
    CLSSessionMgr();
    ~CLSSessionMgr();

    BOOL Init(INet* pNet);
    BOOL UnInit(void);
    static CLSSessionMgr& GetInstance(void);

    GT_SESSION* GetGTSession(UINT32 dwSessionID);
	MG_SESSION* GetMGSession(UINT32 dwSessionID);
    MS_SESSION& GetMSSession(void);
    GD_SESSION& GetGDSession(void);

    INT32 GetServerState(void);
    void SetServerState(INT32 eServerState);

    BOOL CheckSession();
    BOOL CloseAllSession();

    BOOL MainLoop(void);

private:
    static CLSSessionMgr                    ms_Instance;
    INT32                                   m_eServerState;
	UINT64                                  m_qwLastPingTick;
	UINT64                                  m_qwLastStatisTick;

    INet*                                   m_pNet;

    GT_SESSION                              m_GTSession[MAX_GT_SESSION_COUNT];
	MG_SESSION								m_MGSession[MAX_MG_SESSION_COUNT];
    MS_SESSION                              m_MSSession;
    GD_SESSION                              m_GDSession;
};

#endif  // _SESSION_MGR_H_