#ifndef _GUARD_SESSION_MGR_H_
#define _GUARD_SESSION_MGR_H_

#include <list>

#include "id_object_pool.h"

#include "server_def.h"

#define MAX_ALL_SESSION_COUNT   (64)

class INet;
class ISocketSession;

struct ServerSession
{
    UINT32              dwType;
    ISocketSession*     pSocketSession;
    UINT64              qwTimer;
    INT32               eState;		// eProcessState
	UINT32              dwSessionID;
	UINT32              dwProcessID;
    //BOOL                bAuto;
};

struct SMSSession : ServerSession
{
};

struct SGTSession : ServerSession
{
};

struct SGSSession : ServerSession
{
};

struct SDBSession : ServerSession
{
};

struct SLSSession : ServerSession
{
};

struct SBSSession : ServerSession
{
};

struct SDLSession : ServerSession
{
};

struct SMTSession : ServerSession
{

};

struct SGMSession : ServerSession
{
};

struct SMMSession : ServerSession
{
};

struct SMGSession : ServerSession
{
};

struct SRemoteSessionInfo
{
	UINT8               byType;
	UINT32              dwProcessID;
	UINT32				dwSessionID;
	BOOL                bAuto;
	INT32				nState;	// eProcessState
};

struct SRemoteGuardSession
{
	ISocketSession*     pSocketSession;
	UINT64              qwTimer;
	UINT32				dwIp;
	BOOL				bConnecting;
	SRemoteSessionInfo	lstProcess[MAX_REMOTE_SESSION_COUNT];
};

class CGDSessionMgr
{
public:
    CGDSessionMgr();
    ~CGDSessionMgr();

    BOOL Init(INet* pNet);
    BOOL UnInit(void);
    static CGDSessionMgr& GetInstance(void);

    inline SGSSession* GetGSSession(UINT32 dwGSSessionID);
    inline SGTSession* GetGTSession(UINT32 dwGTSessionID);
    inline SLSSession& GetLSSession(void);
    inline SDBSession& GetDBSession(void);
    inline SMSSession& GetMSSession(void);
	inline SBSSession& GetBSSession(void);
	inline SDLSession& GetDLSession(void);
    inline SMTSession& GetMTSession(void);
    inline SGMSession& GetGMSession(void);
	inline SMMSession& GetMMSession(void);
	inline SMGSession* GetMGSession(UINT32 dwMGSessionID);

	inline SRemoteGuardSession* GetRemoteGDSessionByIndex(UINT32 dwIndex);// TODO: traverse
	SRemoteGuardSession* GetRemoteGDSession(UINT32 dwIp);

    inline INT32 GetServerState(void);
    inline void SetServerState(INT32 eServerState);

    BOOL CheckHasSocketSession();
	BOOL CloseAllSocketSession();
	BOOL CheckSocketConnected(UINT8 byType, UINT8 byNum);

    BOOL AddServerSession(ISocketSession* poSession);
    BOOL RemoveServerSession(ISocketSession* poSession);

    BOOL MainLoop(void);
private:

    static CGDSessionMgr                        ms_Instance;
    INet*                                       m_pNet;
	INet*										m_pRemoteGuardNet;
	UINT64                                      m_qwLastPingTick;
	//UINT64										m_qwLastStatisTick;

    SGTSession                                  m_GTSession[MAX_GT_SESSION_COUNT];
    SGSSession                                  m_GSSession[MAX_GS_SESSION_COUNT];
    SDBSession                                  m_DBSession;
    SLSSession                                  m_LSSession;
    SMSSession                                  m_MSSession;
	SBSSession									m_BSSession;
	SDLSession									m_DLSession;
	SMTSession									m_MTSession;
    SGMSession                                  m_GMSession;
	SMMSession									m_MMSession;
	SMGSession									m_MGSession[MAX_MG_SESSION_COUNT];

    typedef std::list<ServerSession>            CServerSessionList;
    typedef CServerSessionList::iterator         CServerSessionListItr;
    CServerSessionList                           m_ServerSessionList;

	SRemoteGuardSession							m_RemoteGDSession[MAX_GUARD_COUNT_PER_AREA];
};

#include "gd_session_mgr.inl"

#endif  // _GUARD_SESSION_MGR_H_