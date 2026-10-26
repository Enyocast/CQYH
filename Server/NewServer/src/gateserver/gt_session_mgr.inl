#ifndef _SESSION_MGR_INL_
#define _SESSION_MGR_INL_

inline GS_SESSION* CGTSessionMgr::GetGSSession(UINT32 dwGSSessionID)
{
	LOG_PROCESS_ERROR(dwGSSessionID > 0 && dwGSSessionID < MAX_GS_SESSION_COUNT);
	return m_GSSession + dwGSSessionID;
Exit0:
	return NULL;
}

inline MS_SESSION& CGTSessionMgr::GetMSSession(void)
{
	return m_MSSession;
}

inline LS_SESSION& CGTSessionMgr::GetLSSession(void)
{
	return m_LSSession;
}

inline DB_SESSION& CGTSessionMgr::GetDBSession(void)
{
	return m_DBSession;
}

inline GD_SESSION& CGTSessionMgr::GetGDSession(void)
{
	return m_GDSession;
}

inline INT32 CGTSessionMgr::GetServerState(void)
{
	return m_eServerState;
}

inline void CGTSessionMgr::SetServerState(INT32 eServerState)
{
	m_eServerState = eServerState;
}

inline void CGTSessionMgr::SetOpenned(INT32 nServerGroup, BOOL bOpened)
{
	LOG_PROCESS_ERROR(nServerGroup >= 0 && nServerGroup < MAX_SERVER_GROUP_COUNT);

	m_bOpened[nServerGroup] = bOpened;

Exit0:
	return;
}

inline BOOL CGTSessionMgr::IsOpened(INT32 nServerGroup)
{
	LOG_PROCESS_ERROR(nServerGroup >= 0 && nServerGroup < MAX_SERVER_GROUP_COUNT);

	return m_bOpened[nServerGroup];
Exit0:
	return FALSE;
}

inline UINT32 CGTSessionMgr::GetSelfSessionID(void)
{
	return m_dwGTSessionID;
}

inline void CGTSessionMgr::SetSelfSessionID(UINT32 dwGTSessionID)
{
	m_dwGTSessionID = dwGTSessionID;

	for (INT32 nIndex = 1; nIndex < MAX_CLIENT_SESSION_COUNT; nIndex++)
	{
		CLIENT_SESSION_ID SessionID = { 0 };

		SessionID.GTSessionID = dwGTSessionID;
		SessionID.GroupID = 0;
		SessionID.SessionID = nIndex;
		m_ClientSessionPool[nIndex].dwSessionID = SessionID.dwSessionID;
	}
}
#endif  // _SESSION_MGR_INL_