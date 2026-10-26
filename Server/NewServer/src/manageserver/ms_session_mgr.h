#ifndef _MS_SESSION_MGR_H_
#define _MS_SESSION_MGR_H_

#include <list>

#include "id_object_pool.h"

#include "server_def.h"

#define MAX_ALL_SESSION_COUNT   (64)

class INet;
class ISocketSession;
struct MS_USER;

struct SMSSession
{
    UINT32              dwType;
    ISocketSession*     pSocketSession;
    UINT64              qwTimer;
};

struct SGTSession : SMSSession
{
    UINT32              dwSessionID;
    INT32               eState;
};

struct SGSSession : SMSSession
{
    UINT32              dwSessionID;
	INT32               nWorkload;	// scene count
    BOOL                bIsExiting; // wait exiting db
    INT32               nOnlineRoleCount;
};

struct SDBSession : SMSSession
{
};

struct SLSSession : SMSSession
{
};

struct SDLSession : SMSSession
{
};

struct SMMSession : SMSSession
{

};

struct SGDSession : SMSSession
{
    BOOL                bConnected;
};

struct SBSSession : SMSSession
{
};

struct SGMSession : SMSSession 
{
    BOOL                bConnected;
    BOOL                bRegistered;
};

struct SNSSession : SMSSession
{
    BOOL                bConnected;
};

class CMSSessionMgr
{
public:
    CMSSessionMgr();
    ~CMSSessionMgr();

    BOOL Init(INet* pNet);
    BOOL UnInit(void);
    static CMSSessionMgr& GetInstance(void);

	inline SGTSession* NewGTSession(ISocketSession* pSession);
    inline void DelGTSession(SGTSession* pGTSession);

	inline SGSSession* NewGSSession(ISocketSession* pSession);
    inline void DelGSSession(SGSSession* pGSSession);

    inline SGSSession* GetGSSession(UINT32 dwGSSessionID);
    inline SGTSession* GetGTSession(UINT32 dwGTSessionID);
    inline SLSSession& GetLSSession(void);
    inline SDBSession& GetDBSession(void);
    inline SGDSession& GetGDSession(void);
	inline SBSSession& GetBSSession(void);
	inline SDLSession& GetDLSession(void);
    inline SGMSession& GetGMSession(void);
    inline SNSSession& GetNSSession(void);
	inline SMMSession& GetMMSession(void);

    inline INT32 GetServerState(void);
    inline void SetServerState(INT32 eServerState);

	UINT32 GetSuitableGS(UINT32 dwPreferGSSessionID);

    BOOL CheckSession();
    BOOL CloseAllSession();

    BOOL MainLoop(void);

    inline void AddToDBWaitList(MS_USER* poUser);

    inline BOOL IsGMValid();

private:
    static CMSSessionMgr                        ms_Instance;
    INT32                                       m_eServerState;
    INet*                                       m_pNet;
	UINT64                                      m_qwLastPingTick;
    std::list<MS_USER*>                         m_DBWaitList;

    SGTSession                                  m_GTSession[MAX_GT_SESSION_COUNT];
    SGSSession                                  m_GSSession[MAX_GS_SESSION_COUNT];
    SDBSession                                  m_DBSession;
    SLSSession                                  m_LSSession;
	SDLSession									m_DLSession;
    SGDSession                                  m_GDSession;
	SBSSession									m_BSSession;
    SGMSession                                  m_GMSession;
    SNSSession                                  m_NSSession;
	SMMSession									m_MMSession;
};

#include "ms_session_mgr.inl"

#endif  // _MS_SESSION_MGR_H_