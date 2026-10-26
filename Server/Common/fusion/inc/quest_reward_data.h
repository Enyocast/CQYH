#ifndef _QUEST_REWARD_DATA_H_
#define _QUEST_REWARD_DATA_H_

#include "quest_def.h"

struct QUEST_REWARD_DATA
{
	// 完成任务奖励
	INT32       nAwardMoneyType1;                                   // 货币奖励类型1
	INT32       nAwardMoneyAmount1;                                 // 货币奖励数量1
	INT32       nAwardMoneyType2;                                   // 货币奖励类型2
	INT32       nAwardMoneyAmount2;                                 // 货币奖励数量2
	INT32       nAwardExp;                                          // 经验奖励
	INT32       nAwardBuffID;                                       // 奖励BUFF ID
	INT32       nAwardBuffLevel;                                    // 奖励BUFF Level
	INT32		nAwardTitleID;										// 奖励称号 ID
	INT32       nAwardReputationForceID;                            // 声望奖励类型
	INT32       nAwardReputation;                                   // 声望奖励
	INT32		nActivity;											// 活力值
	INT32       vecAwardItemID[MAX_REWARD_PER_QUEST];				// 物品奖励
	INT32       vecAwardItemCnt[MAX_REWARD_PER_QUEST];
	BOOL        bNeedSelectAward;
	INT32       vecSelectableAwardItemID[MAX_SELECTABLE_REWARD_COUNT];  // 可选物品奖励
	INT32       vecSelectableAwardItemCnt[MAX_SELECTABLE_REWARD_COUNT];
};


#endif // _QUEST_REWARD_DATA_H_