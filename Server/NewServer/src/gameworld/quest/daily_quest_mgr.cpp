#include "stdafx.h"
#include "daily_quest_mgr.h"
#include "game_world.h"

CDailyQuestMgr CDailyQuestMgr::ms_Instance;

CDailyQuestMgr::CDailyQuestMgr()
{
	memset(m_DailyQuestGroup, 0, sizeof(m_DailyQuestGroup));
	memset(m_DailyQuestGroupSize, 0, sizeof(m_DailyQuestGroupSize));	
}

CDailyQuestMgr::~CDailyQuestMgr()
{

}

BOOL CDailyQuestMgr::Init()
{
	memset(m_DailyQuestGroup, 0, sizeof(m_DailyQuestGroup));
	memset(m_DailyQuestGroupSize, 0, sizeof(m_DailyQuestGroupSize));

	return TRUE;
}

BOOL CDailyQuestMgr::UnInit(void)
{
	return TRUE;
}

CDailyQuestMgr& CDailyQuestMgr::GetInstance(void)
{
	return ms_Instance;
}

INT32 CDailyQuestMgr::AddDailyQuest(QUEST_DATA* pQuest)
{
	INT32 nRetCode = 0;

	LOG_PROCESS_ERROR(pQuest);

	for (INT32 nIndex = 0; nIndex < MAX_DAILY_QUEST_GROUP_COUNT; nIndex++)
	{
		if ((pQuest->nMinLevelLimit <= nIndex*5) && (pQuest->nMaxLevelLimit >= ((nIndex+1)*5)-1))
		{
			nRetCode = _AddDailyQuest(nIndex, pQuest->nQuestID);
			LOG_CHECK_ERROR(nRetCode);
		}
	}

	return TRUE;
Exit0:
	return FALSE;
}

INT32 CDailyQuestMgr::GetRandomQuestIndex(INT32 nIndex)
{
	INT32 nRetCode = 0;
	INT32 nRandom = 0;

	LOG_PROCESS_ERROR(nIndex>0 && nIndex<MAX_DAILY_QUEST_GROUP_COUNT);
	PROCESS_ERROR(m_DailyQuestGroupSize[nIndex]);

	nRandom = g_Random(m_DailyQuestGroupSize[nIndex]);
	LOG_PROCESS_ERROR(nRandom < MAX_REWARD_QUEST_COUNT_PER_GROUP);

	LOG_PROCESS_ERROR(m_DailyQuestGroup[nIndex][nRandom] != INVALID_QUEST_ID);

	return nRandom;
Exit0:
	return -1;
}

INT32 CDailyQuestMgr::GetQuestIDByIndex(INT32 nLevelIndex, INT32 nIndex)
{
	INT32 nRetCode = 0;

	LOG_PROCESS_ERROR(nLevelIndex>=0 && nLevelIndex<MAX_DAILY_QUEST_GROUP_COUNT);
	LOG_PROCESS_ERROR(nIndex>=0 && nIndex<MAX_REWARD_QUEST_COUNT_PER_GROUP);
	LOG_PROCESS_ERROR(m_DailyQuestGroup[nLevelIndex][nIndex] != INVALID_QUEST_ID);

	return m_DailyQuestGroup[nLevelIndex][nIndex];
Exit0:
	return INVALID_QUEST_ID;
}

INT32 CDailyQuestMgr::GetIndexByQuestID(INT32 nLevelIndex, INT32 nQuestID)
{
	INT32 nRetCode = 0;
	INT32 nGroupIndex = 0;
	LOG_PROCESS_ERROR(nLevelIndex>0 && nLevelIndex<MAX_ROLE_LEVEL);

	for (INT32 nIndex = 0; nIndex < MAX_REWARD_QUEST_COUNT_PER_GROUP; nIndex++)
	{
		if (m_DailyQuestGroup[nLevelIndex][nIndex] == nQuestID)
		{
			return nIndex;
		}
	}

Exit0:
	return -1;
}

BOOL CDailyQuestMgr::_AddDailyQuest(INT32 nIndex, INT32 nQuestID)
{
	INT32 nRetCode = 0;
	INT32 nQuestCount = 0;

	LOG_PROCESS_ERROR(nIndex >= 0 && nIndex < MAX_DAILY_QUEST_GROUP_COUNT);

	nQuestCount = m_DailyQuestGroupSize[nIndex];
	LOG_PROCESS_ERROR(nQuestCount < MAX_REWARD_QUEST_COUNT_PER_GROUP);	// 目前每个等级段最多只允许维护64个任务

	m_DailyQuestGroup[nIndex][nQuestCount] = nQuestID;
	m_DailyQuestGroupSize[nIndex]++;

	return TRUE;
Exit0:
	CRI("error daily quest id : %d, level : %d-%d", nQuestID, nIndex * 5, (nIndex + 1) * 5 - 1);

	return FALSE;
}