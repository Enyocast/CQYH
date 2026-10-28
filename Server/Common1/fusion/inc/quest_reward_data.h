#ifndef _QUEST_REWARD_DATA_H_
#define _QUEST_REWARD_DATA_H_

#include "quest_def.h"

struct QUEST_REWARD_DATA
{
	// Quest completion rewards
	INT32       nAwardMoneyType1;                                   // Currency reward type 1
	INT32       nAwardMoneyAmount1;                                 // Currency reward amount 1
	INT32       nAwardMoneyType2;                                   // Currency reward type 2
	INT32       nAwardMoneyAmount2;                                 // Currency reward amount 2
	INT32       nAwardExp;                                          // Experience reward
	INT32       nAwardBuffID;                                       // Reward buff ID
	INT32       nAwardBuffLevel;                                    // Reward buff level
	INT32		nAwardTitleID;										// Reward title ID
	INT32       nAwardReputationForceID;                            // Reputation reward type
	INT32       nAwardReputation;                                   // Reputation reward
	INT32		nActivity;											// Activity points
	INT32       vecAwardItemID[MAX_REWARD_PER_QUEST];				// Item rewards
	INT32       vecAwardItemCnt[MAX_REWARD_PER_QUEST];
	BOOL        bNeedSelectAward;
	INT32       vecSelectableAwardItemID[MAX_SELECTABLE_REWARD_COUNT];  // Selectable item rewards
	INT32       vecSelectableAwardItemCnt[MAX_SELECTABLE_REWARD_COUNT];
};


#endif // _QUEST_REWARD_DATA_H_