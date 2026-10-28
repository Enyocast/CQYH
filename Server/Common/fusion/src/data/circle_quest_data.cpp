#include "stdafx.h"
#include "circle_quest_data.h"
#include "string_def.h"

BOOL CIRCLE_QUEST_DATA::ReadLine(INT32& rnID, const char*& rpcszName, CIRCLE_QUEST_DATA* pData, CTabFile* pTabConfig, INT32 nRow)
{
	READ_START();

	READ_INT("CircleID", nCircleID);
	READ_INT("GroupID", nGroupID);

	READ_INT("MaxCirclePerDay", nMaxCirclePerDay);
	READ_INT("MaxQuestPerNum", nMaxQuestPerNum);

	READ_INT("Level", nLevel);
	READ_INT("CircleNum", nCircleNum);

	READ_INT("ResetTime", nResetTime);

	for (INT32 nIndex = 0; nIndex < MAX_QUEST_PER_CIRCLE; nIndex++)
	{
		char szColumn[COMMON_NAME_LEN];

		snprintf(szColumn, COMMON_NAME_LEN, "RewardGroupID%d", nIndex + 1);
		READ_INT(szColumn, nRewardGroupID[nIndex]);
	}

	rnID = MAKE_CIRCLE_QUEST_KEY(pData->nCircleID, pData->nCircleNum, pData->nLevel);

	return TRUE;
Exit0:
	return TRUE;
}

BOOL CIRCLE_REWARD_DATA::ReadLine(INT32& rnID, const char*& rpcszName, CIRCLE_REWARD_DATA* pData, CTabFile * pTabConfig, INT32 nRow)
{
	READ_START();

	READ_INT("GroupID", nRewardGroupID);

	// 交任务执行动作
 	READ_INT("AwardMoneyType", stQuestRewardData.nAwardMoneyType1);
 	READ_INT("AwardMoneyAmount", stQuestRewardData.nAwardMoneyAmount1);
 	READ_INT("AwardMoneyTypeEx", stQuestRewardData.nAwardMoneyType2);
 	READ_INT("AwardMoneyAmountEx", stQuestRewardData.nAwardMoneyAmount2);
    READ_INT("AwardActivity", stQuestRewardData.nActivity);
	READ_INT("AwardExp", stQuestRewardData.nAwardExp);
	READ_INT("AwardBuffID", stQuestRewardData.nAwardBuffID);
	READ_INT("AwardBuffLevel", stQuestRewardData.nAwardBuffLevel);
	READ_INT("AwardTitleID", stQuestRewardData.nAwardTitleID);
	READ_INT("AwardReputationForceID", stQuestRewardData.nAwardReputationForceID);
	READ_INT("AwardReputation", stQuestRewardData.nAwardReputation);

	for (INT32 nIdx = 0; nIdx < MAX_REWARD_PER_QUEST; ++nIdx)
	{
		char szColumn[COMMON_NAME_LEN];

		snprintf(szColumn, COMMON_NAME_LEN, "%s%d", "AwardItemID", nIdx + 1);
		READ_INT(szColumn, stQuestRewardData.vecAwardItemID[nIdx]);

		snprintf(szColumn, COMMON_NAME_LEN, "%s%d", "AwardItemCnt", nIdx + 1);
		READ_INT(szColumn, stQuestRewardData.vecAwardItemCnt[nIdx]);
	}

	pData->stQuestRewardData.bNeedSelectAward = FALSE;

	for (INT32 nIdx = 0; nIdx < MAX_SELECTABLE_REWARD_COUNT; ++nIdx)
	{
		char szColumn[COMMON_NAME_LEN];

		snprintf(szColumn, COMMON_NAME_LEN, "%s%d", "SelectableAwardItemID", nIdx + 1);
		READ_INT(szColumn, stQuestRewardData.vecSelectableAwardItemID[nIdx]);

		snprintf(szColumn, COMMON_NAME_LEN, "%s%d", "SelectableAwardItemCnt", nIdx + 1);
		READ_INT(szColumn, stQuestRewardData.vecSelectableAwardItemCnt[nIdx]);

		if (pData->stQuestRewardData.vecSelectableAwardItemID[nIdx] != 0)
			pData->stQuestRewardData.bNeedSelectAward = TRUE;
	}

	READ_END(nRewardGroupID);
}
