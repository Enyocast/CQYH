#ifndef _CIRCLE_QUEST_DATA_H_
#define _CIRCLE_QUEST_DATA_H_

#include "data_manager.h"
#include "quest_def.h"
#include "quest_reward_data.h"

struct	CIRCLE_QUEST_DATA 
{
	INT32		nCircleID;													// 环号
	INT32		nGroupID;													// 组ID

	INT32		nMaxCirclePerDay;											// 每日最大完成次数
	INT32		nMaxQuestPerNum;											// 每次最大环数

	// 决定奖励组
	INT32		nCircleNum;													// 次数
	INT32		nLevel;														// 等级
	INT32		nRewardGroupID[MAX_QUEST_PER_CIRCLE];						// 奖励组ID

	INT32		nResetTime;													// 每个环的重置时间

	static BOOL ReadLine(INT32& rnID, const char*& rpcszName, CIRCLE_QUEST_DATA* pData, 
		CTabFile * pTabConfig, INT32 nRow);
};

struct	CIRCLE_REWARD_DATA
{
	// 基本数据
	INT32		nRewardGroupID;										// 环任务奖励组ID

	QUEST_REWARD_DATA stQuestRewardData;

	static BOOL ReadLine(INT32& rnID, const char*& rpcszName, CIRCLE_REWARD_DATA* pData, 
		CTabFile * pTabConfig, INT32 nRow);
};

#endif //_CIRCLE_QUEST_DATA_H_