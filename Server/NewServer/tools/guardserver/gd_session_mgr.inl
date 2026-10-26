#ifndef _SESSION_MGR_INL_
#define _SESSION_MGR_INL_


inline SGSSession* CGDSessionMgr::GetGSSession(UINT32 dwGSSessionID)
{
    LOG_PROCESS_ERROR(dwGSSessionID > 0 && dwGSSessionID < MAX_GS_SESSION_COUNT);

    return m_GSSession + dwGSSessionID;
Exit0:
    return NULL;
}

inline SGTSession* CGDSessionMgr::GetGTSession(UINT32 dwGTSessionID)
{
    LOG_PROCESS_ERROR(dwGTSessionID > 0 && dwGTSessionID < MAX_GS_SESSION_COUNT);

    return m_GTSession + dwGTSessionID;
Exit0:
    return NULL;
}

inline SLSSession& CGDSessionMgr::GetLSSession(void)
{
    return m_LSSession;
}

inline SBSSession& CGDSessionMgr::GetBSSession(void)
{
	return m_BSSession;
}

inline SDLSession& CGDSessionMgr::GetDLSession(void)
{
	return m_DLSession;
}

inline SMMSession& CGDSessionMgr::GetMMSession(void)
{
	return m_MMSession;
}

inline SMGSession* CGDSessionMgr::GetMGSession(UINT32 dwMGSessionID)
{
	LOG_PROCESS_ERROR(dwMGSessionID > 0 && dwMGSessionID < MAX_MG_SESSION_COUNT);

	return m_MGSession + dwMGSessionID;
Exit0:
	return NULL;
}

inline SDBSession& CGDSessionMgr::GetDBSession(void)
{
    return m_DBSession;
}

inline SMSSession& CGDSessionMgr::GetMSSession(void)
{
    return m_MSSession;
}

inline SMTSession& CGDSessionMgr::GetMTSession(void)
{
	return m_MTSession;
}

inline SGMSession& CGDSessionMgr::GetGMSession(void)
{
    return m_GMSession;
}

inline SRemoteGuardSession* CGDSessionMgr::GetRemoteGDSessionByIndex(UINT32 dwIndex)
{
	LOG_PROCESS_ERROR(dwIndex > 0 && dwIndex < MAX_GUARD_COUNT_PER_AREA);

	return m_RemoteGDSession + dwIndex;
Exit0:
	return NULL;
}


#endif  // _SESSION_MGR_INL_