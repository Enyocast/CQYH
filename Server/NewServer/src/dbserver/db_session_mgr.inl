#ifndef _SESSION_MGR_INL_
#define _SESSION_MGR_INL_

inline GS_SESSION* CDBSessionMgr::GetGSSession(UINT32 dwGSSessionID)
{
    LOG_PROCESS_ERROR(dwGSSessionID < MAX_GS_SESSION_COUNT);
    return m_GSSession + dwGSSessionID;
Exit0:
    return NULL;
}

inline GT_SESSION* CDBSessionMgr::GetGTSession(UINT32 dwGTSessionID)
{
    LOG_PROCESS_ERROR(dwGTSessionID < MAX_GT_SESSION_COUNT);
    return m_GTSession + dwGTSessionID;
Exit0:
    return NULL;
}

inline MS_SESSION& CDBSessionMgr::GetMSSession(void)
{
    return m_MSSession;
}

inline GD_SESSION& CDBSessionMgr::GetGDSession(void)
{
    return m_GDSession;
}

inline INT32 CDBSessionMgr::GetServerState(void)
{
    return m_eServerState;
}

inline void CDBSessionMgr::SetServerState(INT32 eServerState)
{
    m_eServerState = eServerState;
}

#endif  // _SESSION_MGR_INL_