// SHANDA GAMES PROPRIETARY INFORMATION
//
// This software is supplied under the terms of a license agreement or
// nondisclosure agreement with Shanda Games and may not 
// be copied or disclosed except in accordance with the terms of that 
// agreement.
//
//      Copyright (c) 1999-2010 Shanda Games.
//      All Rights Reserved.
//
// Shanda Games Limited, Shanghai, China, 201203
// http://www.shandagames.com

#ifndef _CLISESSION_H_
#define _CLISESSION_H_

#include "process_error.h"
#include "object_pool.h"
#include "net.h"

using namespace std;

class CRole;

class CCliSession
{
public:
    CCliSession(void);
    virtual ~CCliSession(void);

public:
    BOOL            Init(UINT32 dwSessionID);

    BOOL            Send(PACKET_BUFFER* pData, UINT32 dwLen);

    BOOL            SendMsg(const char* pData, UINT16 wMsgID);

    VOID            SetGateID(UINT32 dwGateID) {m_dwGateID = dwGateID;}
    UINT32          GetGateID(){return m_dwGateID;}

    VOID            SetJump(BOOL bJump){m_bJump = bJump;}
    BOOL            IsJump(){return m_bJump;}
        
    UINT32          GetSessionID(){return m_dwCliSessionID;}

    VOID            SetRole(CRole* pRole) { m_poRole = pRole;}
    CRole*          GetRole(){return m_poRole;}

    BOOL            KickOffline(void);


private:
    CRole*          m_poRole;   

    UINT32          m_dwGateID;
    UINT32          m_dwCliSessionID;
    BOOL            m_bJump;
};

class CCliSessionMgr
{
public:
    CCliSessionMgr(VOID);        
    ~CCliSessionMgr(VOID);

    static CCliSessionMgr& GetInstance(VOID);

    BOOL Init();

    CCliSession*  CreateSession(UINT32 dwSessionID);
   
    BOOL          AddSession(CCliSession* poSession);   

    BOOL          DeleteSession(CCliSession* poSession);    
    
    CCliSession*  FindCliSession(UINT32 dwSessionID);

    BOOL          RemoveSessionByGateID(UINT32 dwGateID);

    BOOL          CloseSession();

    BOOL          SaveSessionData();

    template<class TFunc>
    inline BOOL Traverse(TFunc& rFunc);
private:
    static CCliSessionMgr ms_Instance;
    CObjectPool<CCliSession>  m_SessionPool;

    typedef map<UINT32 , CCliSession*> CCliSessionMap;
    typedef CCliSessionMap::iterator CCliSessionMapItr;

    CCliSessionMap  m_mapCliSession;
};

template<class TFunc>
inline BOOL CCliSessionMgr::Traverse(TFunc& rFunc)
{
    INT32 nRetCode = 0;

    for (CCliSessionMapItr itr = m_mapCliSession.begin(); itr != m_mapCliSession.end(); ++itr)
    {
        nRetCode = rFunc(itr->second);
        PROCESS_ERROR(nRetCode);
    }

    return TRUE;
Exit0:
    return FALSE;
}

#endif //#ifndef _CLISESSION_H_

