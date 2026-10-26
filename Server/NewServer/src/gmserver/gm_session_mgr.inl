
#ifndef _H_GM_SESSION_MGR_INL_H_
#define _H_GM_SESSION_MGR_INL_H_


inline void CGMSessionMgr::DelTLSession(STLSession *pTLSession)
{
    LOG_PROCESS_ERROR(pTLSession);
    pTLSession->pSocketSession = NULL;

Exit0:
    return;
}

inline SMSSession* CGMSessionMgr::GetMSSession()
{
    return &m_MSSession;
}

inline void CGMSessionMgr::DelMSSession()
{
    m_MSSession.pSocketSession = NULL;
}

inline SGDSession* CGMSessionMgr::GetGDSession(void)
{
    return &m_GDSession;
}

inline STLSession *CGMSessionMgr::GetTLSession(UINT32 dwTLSessionID)
{
    LOG_PROCESS_ERROR(dwTLSessionID > 0 && dwTLSessionID < MAX_GM_TL_SESSION_COUNT);

    return m_TLSession + dwTLSessionID;
Exit0:
    return NULL;
}



inline BOOL CGMSessionMgr::IsMSOnline()
{
    return m_MSSession.eState == egmssNormal;
}

inline INT32 CGMSessionMgr::GetServerState()
{
    return m_eSvrState;
}

inline void CGMSessionMgr::SetServerState(INT32 eSvrState)
{
    m_eSvrState = eSvrState;
}




#endif //_H_GM_SESSION_MGR_INL_H_

