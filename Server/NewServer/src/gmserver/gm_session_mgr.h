/********************************************************************
	created:	20:11:2013   15:28
	file:		gm_session_mgr.h
	author:		Allan Tao
	
	purpose:	
*********************************************************************/

#ifndef _H_GM_SESSION_MGR_H_
#define _H_GM_SESSION_MGR_H_

#include <list>
#include <map>
#include "base_list.h"
#include "server_def.h"


class INet;
class ISocketSession;

enum GM_SESSION_STATE_ENUM
{
    egmssDisconnected,
    egmssConnected,
    egmssRegistering,
    egmssNormal,
};

struct SGMSession : BASE_LIST_NODE 
{
    UINT32      dwType;
    ISocketSession  *pSocketSession;
    UINT64      qwTimer;
};

struct STLSession : SGMSession
{
    UINT32      dwTLUserID;
    UINT32      dwSessionID;
    INT32       eState;
};

struct SMSSession : SGMSession 
{
    UINT32      dwSessionID;
    INT32       eState;
};

struct SGDSession : SGMSession
{
    UINT32      dwSessionID;
    UINT8       bConnected;
    INT32       eState;
};

class CGMSessionMgr
{
public:
    CGMSessionMgr();
    ~CGMSessionMgr();

    BOOL    Init(INet *pNet);
    BOOL    UnInit();
    static  CGMSessionMgr& GetInstance();

    STLSession *NewTLSession();
    inline  void DelTLSession(STLSession *pTLSession);
    inline  STLSession *GetTLSession(UINT32 dwTLSessionID);

    inline SMSSession  *GetMSSession();
    inline  void DelMSSession();
    //inline  SMSSession *GetMSSession(INT32  nMSSessionID);
    BOOL    IsMSOnline();

    inline SGDSession* GetGDSession(void);

    inline  INT32   GetServerState();
    inline  void    SetServerState(INT32 eSvrState);

    BOOL    MainLoop();

    BOOL    CheckSession();
    BOOL    CloseAllSession();

private:
    static CGMSessionMgr        ms_Instance;
    INT32               m_eSvrState;
    INet                *m_pNet;
	UINT64              m_qwLastPingTick;
	UINT64              m_qwLastStatisTick;

    INT32               m_TLSessionIndex;
    STLSession          m_TLSession[MAX_GM_TL_SESSION_COUNT];

    //INT32               m_MSSessionIndex;
    SMSSession          m_MSSession/*[MAX_MS_SESSION_COUNT]*/;
    SGDSession          m_GDSession;
};


#include "gm_session_mgr.inl"






#endif //_H_GM_SESSION_MGR_H_





