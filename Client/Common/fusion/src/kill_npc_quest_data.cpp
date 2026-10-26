#include "stdafx.h"
#include "kill_npc_quest_data.h"

BOOL KILL_NPC_QUEST_DATA::ReadLine(INT32& rnID, const char*& rpcszName, KILL_NPC_QUEST_DATA* pData, CTabFile* pTabConfig, INT32 nRow)
{
	READ_START();

	READ_INT("QuestID", nQuestID);
	READ_INT("NpcTemplateID", nNpcTemplateID);
	READ_INT("NpcGroupID", nNpcGroupID);
	READ_INT_EXPR("ResetType", eResetType);

	for (INT32 nIndex = 0; nIndex < MAX_KILL_COUNT_PER_NPC; nIndex++)
	{
		char szField[256];

		snprintf(szField, 256, "Name%d", nIndex + 1);
		READ_STR(szField, szName[nIndex]);

		snprintf(szField, 256, "KillCount%d", nIndex + 1);
		READ_INT(szField, nKillCount[nIndex]);

		snprintf(szField, 256, "AchievementPts%d", nIndex + 1);
		READ_INT(szField, nAchievementPts[nIndex]);
		if (pData->eResetType != qttNoReset)
			LOG_PROCESS_ERROR(pData->nAchievementPts[nIndex] == 0);

		snprintf(szField, 256, "RewardExp%d", nIndex + 1);
		READ_INT(szField, nRewardExp[nIndex]);
	}

	READ_END(nQuestID);
}
