#include "stdafx.h"
#include "sabac_mgr.h"

#include "game_world.h"

CSabacMgr CSabacMgr::ms_Instance;

CSabacMgr::CSabacMgr()
{
	memset(m_dwOccupyGuildID, 0, sizeof(m_dwOccupyGuildID));
}

CSabacMgr::~CSabacMgr()
{
	UnInit();
}

BOOL CSabacMgr::Init(void)
{
	for (INT32 nIndex = 0; nIndex < MAX_SERVER_GROUP_COUNT; nIndex++)
		m_EnrollList[nIndex].clear();

	return TRUE;
}

BOOL CSabacMgr::UnInit(void)
{
	for (INT32 nIndex = 0; nIndex < MAX_SERVER_GROUP_COUNT; nIndex++)
		m_EnrollList[nIndex].clear();

	return TRUE;
}

CSabacMgr& CSabacMgr::GetInstance(void)
{
	return ms_Instance;
}

void CSabacMgr::Enroll(UINT32 dwGuildID, UINT32 dwEnrollTime, INT32 nServerGroup)
{
	ENROLL_SABAC_DATA EnrollSabacData;
	ENROLL_LIST::iterator it;

	LOG_PROCESS_ERROR(nServerGroup >= 0 && nServerGroup < MAX_SERVER_GROUP_COUNT);

	EnrollSabacData.dwGuildID = dwGuildID;
	EnrollSabacData.dwEnrollTime = dwEnrollTime;

	it = m_EnrollList[nServerGroup].begin();
	for (; it != m_EnrollList[nServerGroup].end() && it->dwEnrollTime <= dwEnrollTime; ++it);
	m_EnrollList[nServerGroup].insert(it, EnrollSabacData);

	INF("guild %X enrolled sabac at %u", dwGuildID, dwEnrollTime/86400);

Exit0:
	return;
}

INT32 CSabacMgr::GetEnrolledGuildCount(INT32 nServerGroup)
{
	UINT32 dwTime = CGameWorld::GetInstance().GetGameTime() + CGameWorld::GetInstance().GetTimeZone();
	dwTime = dwTime / 86400;

	LOG_PROCESS_ERROR(nServerGroup >= 0 && nServerGroup < MAX_SERVER_GROUP_COUNT);

	for (ENROLL_LIST::iterator it = m_EnrollList[nServerGroup].begin();
		it != m_EnrollList[nServerGroup].end();)
	{
		UINT32 dwEnrollTime = it->dwEnrollTime + CGameWorld::GetInstance().GetTimeZone();
		dwEnrollTime = dwEnrollTime / 86400;

		if (dwTime > dwEnrollTime + 3)
			it = m_EnrollList[nServerGroup].erase(it);
		else
			break;
	}

	return m_EnrollList[nServerGroup].size();
Exit0:
	return 0;
}

const ENROLL_SABAC_DATA* CSabacMgr::GetFirstGuild(INT32 nServerGroup)
{
	LOG_PROCESS_ERROR(nServerGroup >= 0 && nServerGroup < MAX_SERVER_GROUP_COUNT);

	m_Iterator[nServerGroup] = m_EnrollList[nServerGroup].begin();
	PROCESS_ERROR(m_Iterator[nServerGroup] != m_EnrollList[nServerGroup].end());

	return &*m_Iterator[nServerGroup];
Exit0:
	return 0;
}

const ENROLL_SABAC_DATA* CSabacMgr::GetNextGuild(INT32 nServerGroup)
{
	LOG_PROCESS_ERROR(nServerGroup >= 0 && nServerGroup < MAX_SERVER_GROUP_COUNT);

	++m_Iterator[nServerGroup];
	PROCESS_ERROR(m_Iterator[nServerGroup] != m_EnrollList[nServerGroup].end());

	return &*m_Iterator[nServerGroup];
Exit0:
	return 0;
}

BOOL CSabacMgr::HasEnrolledGuildToday(INT32 nServerGroup)
{
	UINT32 dwTime = CGameWorld::GetInstance().GetGameTime() + CGameWorld::GetInstance().GetTimeZone();
	dwTime = dwTime / 86400;

	for (ENROLL_LIST::iterator it = m_EnrollList[nServerGroup].begin();
		it != m_EnrollList[nServerGroup].end();)
	{
		UINT32 dwEnrollTime = it->dwEnrollTime + CGameWorld::GetInstance().GetTimeZone();
		dwEnrollTime = dwEnrollTime / 86400;

		if (dwTime > dwEnrollTime + 3)
			it = m_EnrollList[nServerGroup].erase(it);
		else if (dwTime == dwEnrollTime + 3)
			return TRUE;
		else
			return FALSE;
	}

	return FALSE;
}
