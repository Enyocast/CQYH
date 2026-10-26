#include "stdafx.h"
#include "dungeon_data.h"
#include "script_mgr.h"

BOOL DUNGEON_DATA::ReadLine(INT32& rnID, const char*& rpcszName, DUNGEON_DATA* pData, CTabFile* pTabConfig, INT32 nRow)
{
    READ_START();

	READ_INT("SceneID", nSceneID);
	READ_INT("InitState", nInitState);
    READ_INT("Type", nType);
    READ_INT("MinLevel", nMinLevel);
	READ_INT("MaxLevel", nMaxLevel);
    READ_INT("MaxEnterCount", nMaxEnterCount);
    READ_INT("RoleLimit", nRoleLimit);

	READ_TIME("StandardTime", nStandardTime);
	READ_INT("StandardNpcValue", nStandardNpcValue);
	READ_INT("StandardDoodadValue", nStandarddDoodadValue);
    READ_INT("StandardBossValue", nStandardBossValue);
    READ_INT("StandardEliteNpcValue", nStandardEliteNpcValue);
    READ_TIME("StandardSwiftTime", nStandardSwiftTime);

    for (INT32 nIndex = 0; nIndex < MAX_CUSTOM_GOAL_PER_DUNGEON; nIndex++)
    {
        char szField[256];

        snprintf(szField, 256, "CustomGoalVarID%d", nIndex + 1);
        READ_INT_EXPR(szField, nCustomGoalVarID[nIndex]);

        snprintf(szField, 256, "CustomGoalVarValue%d", nIndex + 1);
        READ_INT_EXPR(szField, nCustomGoalVarValue[nIndex]);

        snprintf(szField, 256, "CustomGoalScore%d", nIndex + 1);
        READ_INT_EXPR(szField, nCustomGoalScore[nIndex]);
    }

    READ_INT("Reward1_group", nRewardGroup[0]);
    READ_INT("Reward2_group", nRewardGroup[1]);
    READ_INT("Reward3_group", nRewardGroup[2]);

    READ_INT("Reward1_cost", nRewardCost[0]);
    READ_INT("Reward2_cost", nRewardCost[1]);
    READ_INT("Reward3_cost", nRewardCost[2]);

    READ_INT("Reward1_free", nRewardFree[0]);
    READ_INT("Reward2_free", nRewardFree[1]);
    READ_INT("Reward3_free", nRewardFree[2]);

    pData->nVipExp[vlLevel0] = 0;
	READ_INT("Exp_vip1", nVipExp[vlLevel1]);
    READ_INT("Exp_vip2", nVipExp[vlLevel2]);
    READ_INT("Exp_vip3", nVipExp[vlLevel3]);
	READ_INT("Exp_team", nTeamExp);
	READ_INT("Exp_guild", nGuildExp);
	READ_INT("Exp_activity", nActivityExp);
	READ_INT("Exp_first", nFirstPassExp);

    READ_INT("ItemID", nItemID);
    READ_INT("ItemIsAll", nItemIsAll);
    READ_INT("ItemNumber", nItemNumber);
    READ_INT("Fatigue", nFatigueValue);

	READ_END(nSceneID);
}
