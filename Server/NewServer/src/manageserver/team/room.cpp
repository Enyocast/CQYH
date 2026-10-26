#include "stdafx.h"
#include "room.h"

CRoom CRoom::m_Instance;

CRoom::CRoom()
{
	memset(&nActivityTeam, 0, sizeof(nActivityTeam));
	memset(&nDungeonTeam, 0, sizeof(nDungeonTeam));

	MapActivityTeam.clear();
	MapDungeonTeam.clear();
}

CRoom::~CRoom()
{

}

INT32 CRoom::Init()
{
	memset(&nActivityTeam, 0, sizeof(nActivityTeam));
	memset(&nDungeonTeam, 0, sizeof(nDungeonTeam));

	MapActivityTeam.clear();
	MapDungeonTeam.clear();

	return TRUE;	
}

CRoom& CRoom::GetInstance()
{
	return m_Instance;
}

INT32 CRoom::UnInit()
{
	return TRUE;	
}

INT32 CRoom::AddTeam(BOOL bActivity, INT32 nActivityID, INT32 nTeamID)
{
	INT32 nRetCode = 0;
	INT32* pTeamHead = NULL;
	Iter_MapId2Team Iter;

	if (bActivity)
	{
		Iter_MapId2Team Iter = MapActivityTeam.find(nActivityID);
		LOG_PROCESS_ERROR(Iter != MapActivityTeam.end());
	}
	else
	{
		Iter_MapId2Team Iter = MapDungeonTeam.find(nActivityID);
		LOG_PROCESS_ERROR(Iter != MapDungeonTeam.end());
	}

	pTeamHead = Iter->second;

	for (INT32 nIndex = 0; nIndex < MAX_TEAM_COUNT; nIndex++)
	{
		if (*pTeamHead == 0)
		{
			*pTeamHead = nTeamID;

			return TRUE;
		}

		pTeamHead++;
	}

Exit0:
	return FALSE;
}

INT32 CRoom::DeleteTeam(BOOL bActivity, INT32 nActivityID, INT32 nTeamID)
{
	INT32 nRetCode = 0;
	INT32* pTeamHead = NULL;
	Iter_MapId2Team Iter;

	if (bActivity)
	{
		Iter_MapId2Team Iter = MapActivityTeam.find(nActivityID);
		LOG_PROCESS_ERROR(Iter != MapActivityTeam.end());
	}
	else
	{
		Iter_MapId2Team Iter = MapDungeonTeam.find(nActivityID);
		LOG_PROCESS_ERROR(Iter != MapDungeonTeam.end());
	}

	pTeamHead = Iter->second;

	for (INT32 nIndex = 0; nIndex < MAX_TEAM_COUNT; nIndex++)
	{
		if (*pTeamHead == nTeamID)
		{
			*pTeamHead = 0;
		}

		pTeamHead++;
	}

	return TRUE;
Exit0:
	return FALSE;
}

INT32* CRoom::GetTeamHead(BOOL bActivity, INT32 nActivityID)
{
	INT32 nRetCode = 0;
	INT32* pTeamHead = NULL;
	Iter_MapId2Team Iter;

	if (bActivity)
	{
		Iter_MapId2Team Iter = MapActivityTeam.find(nActivityID);
		LOG_PROCESS_ERROR(Iter != MapActivityTeam.end());
	}
	else
	{
		Iter_MapId2Team Iter = MapDungeonTeam.find(nActivityID);
		LOG_PROCESS_ERROR(Iter != MapDungeonTeam.end());
	}

	return Iter->second;

Exit0:
	return NULL;
}