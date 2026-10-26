#include "stdafx.h"
#include "gamble.h"
#include "gamble_data.h"
#include "attribute_def.h"
#include "game_world.h"
#include "role.h"

CGamble::CGamble()
{
	m_pOwner = NULL;
	Clear();
}

void CGamble::Clear()
{
}

void CGamble::SetOwner(CRole* role)
{
	m_pOwner = role;
}

const DROP_CHANCE_DATA* CGamble::GetDropChangeData(const GAMBLE_DATA* data)
{
	BOOL world_group_activated = FALSE;
	
	// ÔÝÊ±ÆÁ±Î
	/*
	LOG_PROCESS_ERROR(data);
	LOG_PROCESS_ERROR(data->nGambleType >= 0 && data->nGambleType < egtTotal);
	LOG_PROCESS_ERROR(data->nGambleLevel >= 0 && data->nGambleLevel < GAMBLE_LEVEL_COUNT);
	
	CGameWorld::GetInstance().SetServerVariable(m_pOwner->GetServerGroup(), MakeServerKey(esvtWorldGambleCount, data->nGambleKey), FALSE, 1);
	if (data->nWorldCount > 0)
	{
		INT32 world_count = CGameWorld::GetInstance().GetServerVariable(m_pOwner->GetServerGroup(), MakeServerKey(esvtWorldGambleCount, data->nGambleKey));
		INT32 modified_world_count = world_count;
		if (data->nGameLevel == 0)
		{
			modified_world_count += CGameWorld::GetInstance().GetServerVariable(m_pOwner->GetServerGroup(), MakeServerKey(esvtWorldGambleCount, GAMBLE_DATA::MakeKey(data->nGameType, 1))) * data->nL1ModL0;
			modified_world_count += CGameWorld::GetInstance().GetServerVariable(m_pOwner->GetServerGroup(), MakeServerKey(esvtWorldGambleCount, GAMBLE_DATA::MakeKey(data->nGameType, 2))) * data->nL2ModL0;
		}
		if (data->nGameLevel == 1)
		{
			modified_world_count += CGameWorld::GetInstance().GetServerVariable(m_pOwner->GetServerGroup(), MakeServerKey(esvtWorldGambleCount, GAMBLE_DATA::MakeKey(data->nGameType, 2))) * data->nL2ModL1;
		}
		
		INT32 previous_world_count = CGameWorld::GetInstance().GetServerVariable(m_pOwner->GetServerGroup(), MakeServerKey(esvtPreviousWorldGambleCount, data->nGambleKey));
		if (modified_world_count % data->nWorldCount == 0)
		{
			world_group_activated = TRUE;
			CGameWorld::GetInstance().SetServerVariable(m_pOwner->GetServerGroup(), MakeServerKey(esvtPreviousWorldGambleCount, data->nGambleKey), TRUE, 0);
		}
	}
	
	dwValue[data->nGambleType][data->nGameLevel]++;
	dwTotalValue[data->nGambleType][data->nGameLevel]++;
	
	UINT32 cur_value = dwValue[data->nGambleType][data->nGameLevel];
	
	for (INT32 i = 3; i >= 0; i--)
	{
		if (data->nBossCount[i] > 0 && cur_value % data->nBossCount[i] == 0)
		{
#ifdef _DEBUG
			char debug_string[1024];
			snprintf(debug_string, 1024, "Boss Group %d", i + 1);
			m_pOwner->Say(cctScreen, cltNormal, debug_string);
#endif
			return &data->BossDrop[i];
		}
		if (i + 1 == data->nWorldGroupPos && world_group_activated)
		{
#ifdef _DEBUG
			m_pOwner->Say(cctScreen, cltNormal, "World Group");
#endif
			return &data->WorldDrop;
		}
	}
	
#ifdef _DEBUG
	m_pOwner->Say(cctScreen, cltNormal, "Normal Group");
#endif
	return &data->NormalDrop;
	*/

Exit0:
	return NULL;
}

INT32 CGamble::GetJieDian()
{
	return CGameWorld::GetInstance().GetServerVariable(m_pOwner->GetServerGroup(), 38655819776);
}

INT32 CGamble::GetDropGambleItem()
{
	BOOL world_group_activated = FALSE;
	
	CGameWorld::GetInstance().SetServerVariable(m_pOwner->GetServerGroup(), 38655819776, FALSE, 1);
	INT32 world_count = CGameWorld::GetInstance().GetServerVariable(m_pOwner->GetServerGroup(), 38655819776);
	
	if (world_count % 30000 == 0)
	{
		return 1800069;
	}
	
	if (world_count % 10000 == 0)
	{
		return 1800068;
	}
	
	if (world_count % 3000 == 0)
	{
		return 1800067;
	}
	
	if (world_count % 1000 == 0)
	{
		return 1800066;
	}
	
	if (world_count % 100 == 0)
	{
		return 1800065;
	}
	
	return 1800064;
	
Exit0:
	return NULL;
}

void CGamble::ClearValue(INT32 nGambleType, INT32 nGambleLevel)
{
	LOG_PROCESS_ERROR(nGambleType >= 0 && nGambleType < egtTotal);
	LOG_PROCESS_ERROR(nGambleLevel >= 0 && nGambleLevel < GAMBLE_LEVEL_COUNT);
	
	dwValue[nGambleType][nGambleLevel] = 0;
	
Exit0:
	return;
}

UINT32 CGamble::GetTotalValue(INT32 nGambleType, INT32 nGambleLevel)
{
	LOG_PROCESS_ERROR(nGambleType >= 0 && nGambleType < egtTotal);
	LOG_PROCESS_ERROR(nGambleLevel >= 0 && nGambleLevel < GAMBLE_LEVEL_COUNT);
	
	return dwTotalValue[nGambleType][nGambleLevel];
	
Exit0:
	return 0;
}

UINT32 CGamble::GetValue(INT32 nGambleType, INT32 nGambleLevel)
{
	LOG_PROCESS_ERROR(nGambleType >= 0 && nGambleType < egtTotal);
	LOG_PROCESS_ERROR(nGambleLevel >= 0 && nGambleLevel < GAMBLE_LEVEL_COUNT);
	
	return dwValue[nGambleType][nGambleLevel];
	
Exit0:
	return 0;
}

void CGamble::SetValue(INT32 nGambleType, INT32 nGambleLevel, UINT32 dwVar)
{
	LOG_PROCESS_ERROR(nGambleType >= 0 && nGambleType < egtTotal);
	LOG_PROCESS_ERROR(nGambleLevel >= 0 && nGambleLevel < GAMBLE_LEVEL_COUNT);
	
	dwValue[nGambleType][nGambleLevel] = dwVar;
	
Exit0:
	return;
}

INT32 CGamble::GetNextID(INT32 nGambleType, INT32 nGambleLevel)
{
	LOG_PROCESS_ERROR(nGambleType >= 0 && nGambleType < egtTotal);
	LOG_PROCESS_ERROR(nGambleLevel >= 0 && nGambleLevel < GAMBLE_LEVEL_COUNT);
	
	return nNextID[nGambleType][nGambleLevel];
	
Exit0:
	return 0;
}

void CGamble::SetNextID(INT32 nGambleType, INT32 nGambleLevel, INT32 nVar)
{
	LOG_PROCESS_ERROR(nGambleType >= 0 && nGambleType < egtTotal);
	LOG_PROCESS_ERROR(nGambleLevel >= 0 && nGambleLevel < GAMBLE_LEVEL_COUNT);
	
	nNextID[nGambleType][nGambleLevel] = nVar;
	
Exit0:
	return;
}








