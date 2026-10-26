#ifndef _MG_SESSION_MGR_INL_
#define _MG_SESSION_MGR_INL_

inline MM_SESSION& CMGSessionMgr::GetMMSession(void)
{
	return m_MMSession;
}

inline LS_SESSION& CMGSessionMgr::GetLSSession(void)
{
	return m_LSSession;
}

inline GD_SESSION& CMGSessionMgr::GetGDSession(void)
{
	return m_GDSession;
}

inline INT32 CMGSessionMgr::GetServerState(void)
{
	return m_eServerState;
}

inline void CMGSessionMgr::SetServerState(INT32 eServerState)
{
	m_eServerState = eServerState;
}

inline void CMGSessionMgr::SetOpenned(INT32 nServerGroup, BOOL bOpened)
{
	LOG_PROCESS_ERROR(nServerGroup >= 0 && nServerGroup < MAX_SERVER_GROUP_COUNT);

	m_bOpened[nServerGroup] = bOpened;

Exit0:
	return;
}

inline BOOL CMGSessionMgr::IsOpened(INT32 nServerGroup)
{
	LOG_PROCESS_ERROR(nServerGroup >= 0 && nServerGroup < MAX_SERVER_GROUP_COUNT);

	return m_bOpened[nServerGroup];
Exit0:
	return FALSE;
}

inline UINT32 CMGSessionMgr::GetSelfSessionID(void)
{
	return m_dwMGSessionID;
}

inline void CMGSessionMgr::SetSelfSessionID(UINT32 dwGTSessionID)
{
	m_dwMGSessionID = dwGTSessionID;

	for (INT32 nIndex = 1; nIndex < MAX_CLIENT_SESSION_COUNT; nIndex++)
	{
		CLIENT_SESSION_ID SessionID;
		SessionID.GTSessionID = dwGTSessionID;
		SessionID.GroupID = 0;
		SessionID.SessionID = nIndex;
		m_ClientSessionPool[nIndex].dwSessionID = SessionID.dwSessionID;
	}
}
#endif  // _MG_SESSION_MGR_INL_