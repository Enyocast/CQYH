#include "stdafx.h"
#include "circle_quest_mgr.h"
#include "game_world.h"

CCIRCLE_QUEST_MGR CCIRCLE_QUEST_MGR::ms_Instance;

CCIRCLE_QUEST_MGR::CCIRCLE_QUEST_MGR()
{

}

CCIRCLE_QUEST_MGR::~CCIRCLE_QUEST_MGR()
{

}

BOOL CCIRCLE_QUEST_MGR::Init(const char* pcszConfigName, const char* pcszPath)
{
	memset(m_nGroupID, 0, sizeof(m_nGroupID));
	return FALSE;
}

BOOL CCIRCLE_QUEST_MGR::UnInit(void)
{
	return TRUE;
}

CCIRCLE_QUEST_MGR& CCIRCLE_QUEST_MGR::GetInstance(void)
{
	return ms_Instance;
}

INT32 CCIRCLE_QUEST_MGR::AddCircleQuest(QUEST_DATA* pQuest)
{
	INT32 nRetCode = 0;

	LOG_PROCESS_ERROR(pQuest);
	LOG_PROCESS_ERROR((pQuest->nCircleID > 0) && (pQuest->nCircleID < MAX_CIRCLE_QUEST_COUNT));

	for (INT32 nIndex = 0; nIndex < MAX_ROLE_LEVEL/CIRCLE_QUEST_LEVEL_PER_GRADE; nIndex++)
	{
		if ((pQuest->nMinLevelLimit <= CIRCLE_QUEST_LEVEL_PER_GRADE*nIndex) && (pQuest->nMaxLevelLimit >= CIRCLE_QUEST_LEVEL_PER_GRADE*(nIndex + 1)-1))
		{
			nRetCode = _AddtoCircleList(pQuest->nCircleID, nIndex, pQuest->nQuestID);
			LOG_PROCESS_ERROR(nRetCode);
		}
	}

	for (INT32 nIndex = 0; nIndex < MAX_ROLE_LEVEL/CIRCLE_QUEST_LEVEL_PER_GRADE; nIndex++)
	{
		if (!m_Circle_Quest_ID_List[pQuest->nCircleID][nIndex].empty())
		{
			const QUEST_DATA* pQuestBegin = CDataManager<QUEST_DATA>::GetInstance().GetData(*(m_Circle_Quest_ID_List[pQuest->nCircleID][nIndex].begin()));
			PROCESS_SUCCESS(!pQuestBegin);	// 找不到为合理,因为设置key在最后

			if(pQuest->nStartNpcID != pQuestBegin->nStartNpcID)
			{
				WRN("Circle quest: %d and %d in circle id: %d don't have the same startnpc!", pQuest->nQuestID, pQuestBegin->nQuestID, pQuest->nCircleID);
			}

			break;
		}
	}

	return TRUE;
Exit1:
	return TRUE;
Exit0:
	return FALSE;
}

INT32 CCIRCLE_QUEST_MGR::GetRandomCircleQuest(INT32 nCircleID, INT32 nLevel)
{
	INT32 nRandomNumber = 0;
	INT32 nListSize = 0;
	INT32 nLevelIndex = 0;
	IterCircleQuestIDList Iter;

	LOG_PROCESS_ERROR(nCircleID > 0 && nCircleID <= MAX_CIRCLE_QUEST_COUNT);
	LOG_PROCESS_ERROR(nLevel > 0 && nLevel <= MAX_ROLE_LEVEL/CIRCLE_QUEST_LEVEL_PER_GRADE);

	nListSize = (INT32)m_Circle_Quest_ID_List[nCircleID-1][nLevel].size();
	PROCESS_ERROR(nListSize);

	nRandomNumber = g_Random(nListSize);

	Iter = m_Circle_Quest_ID_List[nCircleID-1][nLevel].begin();

	for (INT32 nIndex = 0;nIndex < nRandomNumber; nIndex++, Iter++)
	{
		LOG_PROCESS_ERROR(Iter != m_Circle_Quest_ID_List[nCircleID-1][nLevel].end());
	}

	return *Iter;
Exit0:
	return 0;
}

INT32 CCIRCLE_QUEST_MGR::_AddtoCircleList(INT32 nCircleID, INT32 nIndexID, INT32 nQuestID)
{
	LOG_PROCESS_ERROR(nCircleID > 0 && nCircleID <= MAX_CIRCLE_COUNT);
	LOG_PROCESS_ERROR(nIndexID > 0 && nIndexID <= MAX_ROLE_LEVEL/CIRCLE_QUEST_LEVEL_PER_GRADE);

	for (IterCircleQuestIDList Iter = m_Circle_Quest_ID_List[nCircleID-1][nIndexID].begin(); Iter != m_Circle_Quest_ID_List[nCircleID-1][nIndexID].end(); Iter++)
	{
		PROCESS_SUCCESS(*Iter == nQuestID);
	}

	m_Circle_Quest_ID_List[nCircleID-1][nIndexID].push_back(nQuestID);

	return TRUE;
Exit1:
	return TRUE;
Exit0:
	return FALSE;
}

INT32 CCIRCLE_QUEST_MGR::_SetGroupID(INT32 nCircleID, INT32 nGroupID)
{
	LOG_PROCESS_ERROR((nCircleID>=0) && (nCircleID<MAX_CIRCLE_QUEST_COUNT));
	m_nGroupID[nCircleID] = nGroupID;

	return TRUE;
Exit0:
	return FALSE;
}