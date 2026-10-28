#ifndef _DUNGEON_DATA_H_
#define _DUNGEON_DATA_H_

#include "string_def.h"
#include "scene_def.h"
#include "data_manager.h"
#include "lua_script.h"
#include "score_def.h"
#include "role_def.h"
#include "weight_rand.h"
#define MAX_CUSTOM_GOAL_PER_DUNGEON (4)

struct DUNGEON_DATA
{
	INT32	nID;
	INT32	nInitState;
	INT32	nType;
    INT32   nMinLevel;
	INT32	nMaxLevel;
    INT32   nMaxEnterCount;
    INT32   nRoleLimit;

	INT32   nStandardTime;              // unit: frame
	INT32   nStandardNpcValue;
	INT32   nStandarddDoodadValue;
    INT32   nStandardBossValue;
    INT32   nStandardEliteNpcValue;
    INT32   nStandardSwiftTime;         // unit: frame

    INT32   nCustomGoalVarID[MAX_CUSTOM_GOAL_PER_DUNGEON];
    INT32   nCustomGoalVarValue[MAX_CUSTOM_GOAL_PER_DUNGEON];
    INT32   nCustomGoalScore[MAX_CUSTOM_GOAL_PER_DUNGEON];

    INT32   nRewardGroup[MAX_SCORE_REWARD_COUNT];
    INT32   nRewardCost[MAX_SCORE_REWARD_COUNT];
    INT32   nRewardFree[MAX_SCORE_REWARD_COUNT];

	INT32	nTeamExp;
	INT32	nGuildExp;
    INT32   nVipExp[vlTotal];
    INT32	nFirstPassExp;
	INT32	nActivityExp;

    INT32   nItemID;
    INT32   nItemIsAll;
    INT32   nItemNumber;

    INT32   nFatigueValue;

	static BOOL ReadLine(INT32& rnID, const char*& rpcszName, DUNGEON_DATA* pData, CTabFile* pTabConfig, INT32 nRow);
};

#endif	// _DUNGEON_DATA_H_