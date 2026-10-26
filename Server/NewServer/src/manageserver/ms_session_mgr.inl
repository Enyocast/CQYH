#ifndef _SESSION_MGR_INL_
#define _SESSION_MGR_INL_

inline SGTSession* CMSSessionMgr::NewGTSession(ISocketSession* pSession)
{
    for (INT32 nIndex = 1; nIndex < MAX_GT_SESSION_COUNT; ++nIndex)
    {
        if (m_GTSession[nIndex].pSocketSession == NULL)
        {
			m_GTSession[nIndex].pSocketSession = pSession;
            return m_GTSession + nIndex;
        }
    }

    return NULL;
}

inline void CMSSessionMgr::DelGTSession(SGTSession* pGTSession)
{
    LOG_PROCESS_ERROR(pGTSession);
    pGTSession->pSocketSession = NULL;
Exit0:
    return;
}

inline SGSSession* CMSSessionMgr::NewGSSession(ISocketSession* pSession)
{
    for (INT32 nIndex = 1; nIndex < MAX_GS_SESSION_COUNT; ++nIndex)
    {
        if (m_GSSession[nIndex].pSocketSession == NULL &&   // socket has disconnected
            m_GSSession[nIndex].bIsExiting == FALSE ) 
		{
			m_GSSession[nIndex].pSocketSession = pSession;
            return m_GSSession + nIndex;
        }
    }

    return NULL;
}

inline void CMSSessionMgr::DelGSSession(SGSSession* pGSSession)
{
    LOG_PROCESS_ERROR(pGSSession);
    pGSSession->pSocketSession = NULL;
Exit0:
    return;
}


inline SGSSession* CMSSessionMgr::GetGSSession(UINT32 dwGSSessionID)
{
    LOG_PROCESS_ERROR(dwGSSessionID > 0 && dwGSSessionID < MAX_GS_SESSION_COUNT);

    return m_GSSession + dwGSSessionID;
Exit0:
    return NULL;
}

inline SGTSession* CMSSessionMgr::GetGTSession(UINT32 dwGTSessionID)
{
    LOG_PROCESS_ERROR(dwGTSessionID > 0 && dwGTSessionID < MAX_GS_SESSION_COUNT);

    return m_GTSession + dwGTSessionID;
Exit0:
    return NULL;
}

inline SLSSession& CMSSessionMgr::GetLSSession(void)
{
    return m_LSSession;
}

inline SDBSession& CMSSessionMgr::GetDBSession(void)
{
    return m_DBSession;
}

inline SGDSession& CMSSessionMgr::GetGDSession(void)
{
    return m_GDSession;
}

inline SBSSession& CMSSessionMgr::GetBSSession(void)
{
	return m_BSSession;
}

inline SDLSession& CMSSessionMgr::GetDLSession(void)
{
	return m_DLSession;
}

inline SMMSession& CMSSessionMgr::GetMMSession(void)
{
	return m_MMSession;
}

inline SGMSession& CMSSessionMgr::GetGMSession()
{
    return m_GMSession;
}

inline SNSSession& CMSSessionMgr::GetNSSession(void)
{
	return m_NSSession;
}

inline INT32 CMSSessionMgr::GetServerState(void)
{
    return m_eServerState;
}

inline void CMSSessionMgr::SetServerState(INT32 eServerState)
{
    m_eServerState = eServerState;
}

inline void CMSSessionMgr::AddToDBWaitList(MS_USER* poUser)
{
    m_DBWaitList.push_back(poUser);
}

inline BOOL CMSSessionMgr::IsGMValid()
{
    return m_GMSession.bRegistered;
}

#endif  // _SESSION_MGR_INL_