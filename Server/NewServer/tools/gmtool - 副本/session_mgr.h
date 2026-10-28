/********************************************************************
	created:	6:8:2013   10:21
	file:		session_mgr.h
	author:		Allan Tao
	
	purpose:	
*********************************************************************/

#ifndef _H_SESSION_MGR_H_
#define _H_SESSION_MGR_H_

#include "base_list.h"
#include "predefine.h"
#include "server_def.h"

class INet;
class ISocketSession;



struct GM_SESSION : BASE_LIST_NODE 
{
    UINT32              dwType;
    ISocketSession*     pSocketSession;
    UINT64              qwTimer;
    INT32               nConnectState;
    UINT32              dwSessionID;

    GM_SVR_STATE    eState;             // todo_tq 这边state需要统一处理一次 Allan Tao[17.12.2013] 
    INT32           nSvrID;
    char            szGMName[33];
};


class CSessionMgr
{
protected:
    CSessionMgr();
    ~CSessionMgr();

    static CSessionMgr  m_Instance;
public:
    BOOL Init(INet *pNet);
    BOOL UnInit();
    static CSessionMgr &GetInstance();

    GM_SESSION *NewGMSession();
    void DeleteGMSession(GM_SESSION *pSession);

    GM_SESSION* GetGMSession(UINT32 dwSessionID);

    //GM_SESSION &GetGMSession();

    BOOL CheckSession();
    BOOL CloseAllSession();

    BOOL MainLoop(void);


protected:
    INet        *m_pNet;

    UINT32      m_dwLastPingTick;

    GM_SESSION  m_GMSession[MAX_GM_SESSION_COUNT];
};






#endif //_H_SESSION_MGR_H_



