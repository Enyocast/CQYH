#ifndef _CIRCLE_QUEST_DATA_H_
#define _CIRCLE_QUEST_DATA_H_

#include "data_manager.h"
#include "quest_def.h"
#include "quest_reward_data.h"

struct	CIRCLE_QUEST_DATA 
{
	INT32		nCircleID;													// Cycle number
	INT32		nGroupID;													// Group ID

	INT32		nMaxCirclePerDay;											// Maximum completions per day
	INT32		nMaxQuestPerNum;											// Maximum rounds per attempt

	// Determine the reward group
	INT32		nCircleNum;													// Count
	INT32		nLevel;														// Level
	INT32		nRewardGroupID[MAX_QUEST_PER_CIRCLE];						// Reward group ID

	INT32		nResetTime;													// Reset time for each cycle

	static BOOL ReadLine(INT32& rnID, const char*& rpcszName, CIRCLE_QUEST_DATA* pData, 
		CTabFile * pTabConfig, INT32 nRow);
};

struct	CIRCLE_REWARD_DATA
{
	// Basic data
	INT32		nRewardGroupID;										// Cycle quest reward group ID

	QUEST_REWARD_DATA stQuestRewardData;

	static BOOL ReadLine(INT32& rnID, const char*& rpcszName, CIRCLE_REWARD_DATA* pData, 
		CTabFile * pTabConfig, INT32 nRow);
};

#endif //_CIRCLE_QUEST_DATA_H_