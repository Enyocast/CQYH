#ifndef _QUEST_DATA_H_
#define _QUEST_DATA_H_

#include "string_def.h"
#include "quest_def.h"
#include "data_manager.h"
#include "quest_reward_data.h"
struct QUEST_DATA
{
    // Basic attributes
    INT32       nQuestID;                                           // Quest ID
    INT32       eResetType;                                         // Quest reset type
	INT32		nQuestType;											// Quest type
	INT32		nCircleID;											// Cycle ID
	INT32		nQuality;											// Quality
    UINT32      dwResetTime;                                        // Quest reset time offset
    BOOL        bCanAbandon;                                        // Whether the quest can be abandoned
	BOOL		bCanShare;											// Whether the quest can be shared
	BOOL		bCanPublish;										// Whether the quest can be published

	INT32		nEmergencyCoolDown;									// Cooldown

	UINT32		nDurationLimit;										// Whether the quest is time-limited
	char		szName[COMMON_NAME_LEN];							// Quest name

	INT32		nSceneID[MAX_FLY_SPOT_PER_QUEST];					// Teleport destination map IDs
	INT32		nX[MAX_FLY_SPOT_PER_QUEST];							// Teleport point X
	INT32		nY[MAX_FLY_SPOT_PER_QUEST];							// Teleport point Y
	INT32		nZ[MAX_FLY_SPOT_PER_QUEST];							// Teleport point Z

    // Quest acceptance and completion conditions
    INT32       nMaxCompletedCount;                                 // Maximum completions after a quest reset; 0 means unlimited
    INT32       nClassLimit;                                        // Required class
    INT32       nSexLimit;                                          // Required sex
    INT32       nRelationLimit;                                     // Required relationship

    // Quest acceptance conditions
    INT32       nPreQuestID1;                                       // Prerequisite quest ID
    INT32       nPreQuestID2;                                       // Prerequisite quest ID
    INT32       nStartNpcID;                                        // NPC ID that starts the quest
    INT32       nStartItemID;                                       // Item ID that starts the quest
    BOOL        bStartZone;                                         // Whether the quest is triggered by an area

    INT32       nMinLevelLimit;                                     // Minimum required level
    INT32       nMaxLevelLimit;                                     // Maximum allowed level
    INT32       nBuffIDLimit;                                       // Required buff ID
    INT32       nBuffLevelLimit;                                    // Required buff ID
    INT32       nMoneyTypeLimit;                                    // Required currency type
    INT32       nMoneyAmountLimit;                                  // Required currency amount (not deducted)
    INT32       nReputationForceID;                                 // Required NPC faction reputation
    INT32       nReputationMinLimit;                                // Minimum required reputation
    INT32       nReputationMaxLimit;                                // Maximum allowed reputation

    INT32       nYearLimit;
    INT32       nMonthLimit;

    INT32       nStartWeekday;                                      // Acceptance start time for a weekly recurring quest
    INT32       nWeekdayDuration;                                   // Duration of a weekly recurring quest

    INT32       nStartMonthday;                                      // Acceptance start time for a monthly recurring quest
    INT32       nMonthdayDuration;                                   // Duration of a monthly recurring quest (cannot cross a month boundary)

    UINT32      dwAcceptStartTime;                                  // Start of the allowed acceptance period
    UINT32      dwAcceptEndTime;                                    // End of the allowed acceptance period
    INT32       nAcceptStartHour;
    INT32       nAcceptStartMin;
    INT32       nAcceptEndHour;
    INT32       nAcceptEndMin;
    INT32       nAcceptStartDayTime;
    INT32       nAcceptEndDayTime;

    INT32       vecItemLimitID[4];                                  // Required carried items
    INT32       vecItemLimitCnt[4];

    INT32       nLimitVarID1;                                       // Required variable ID 1
    INT32       nLimitVarValue1;                                    // Required variable value 1 (equality check)
    INT32       nLimitVarID2;                                       // Required variable ID 2
    INT32       nLimitVarValue2;                                    // Required variable value 2 (equality check)
    CHAR        szBeforeAcceptScriptName[COMMON_NAME_LEN];          // Script checked before quest acceptance

    // Actions performed on quest acceptance
    INT32       nOfferMoneyType;                                    // Currency type granted on acceptance
    INT32       nOfferMoneyAmount;                                  // Currency amount granted on acceptance (negative deducts money)
    INT32       nOfferBuffID;                                       // Buff ID granted on acceptance
    INT32       nOfferBuffLevel;                                    // Buff level granted on acceptance

    INT32       nOfferItemID;                                       // Item granted or removed on acceptance
    INT32       nOfferItemCnt;                                      // Negative values indicate the amount removed
    CHAR        szAfterAcceptScriptName[COMMON_NAME_LEN];           // Script executed after quest acceptance

    // Quest completion conditions
    INT32       nFinishNpc;                                         // NPC ID that completes the quest
	INT32		nFinishItemID;										// Item ID that completes the quest
    INT32       nCheckBuffID;                                       // Buff check for quest completion
    INT32       nCheckBuffLevel;
	INT32		nCheckLevel;										// Level check for quest completion

	INT32		nCheckKillPlayerLevlStart[CHECK_KILL_PLAYER_CONDITION];	// Minimum level of player kills to count
	INT32		nCheckKillPlayerLevlEnd[CHECK_KILL_PLAYER_CONDITION];	// Maximum level of player kills to count
	INT32		nCheckKillPlayerCount[CHECK_KILL_PLAYER_CONDITION];		// Required number of player kills
	INT32		nCheckKillBufPlayerBufID[CHECK_KILL_PLAYER_CONDITION];	// Kill a player with the specified buff ID
	INT32		nCheckKillBufPlayerCount[CHECK_KILL_PLAYER_CONDITION];	// Required kills of players with the specified buff ID

    INT32       nCheckKillNpcID[MAX_CONDITION_PER_QUEST];			// Monster kill count check
    INT32       nCheckKillNpcGroupID[MAX_CONDITION_PER_QUEST];			// Monster group kill check
    INT32       nCheckKillNpcCnt[MAX_CONDITION_PER_QUEST];

	INT32		nCheckKillItemNpcID[MAX_CONDITION_PER_QUEST];		// NPC ID that drops the quest item
	INT32		nCheckKillItemNpcRate[MAX_CONDITION_PER_QUEST];		// Quest item drop probability
    INT32       nCheckKillItemCnt[MAX_CONDITION_PER_QUEST];
 
	UINT32		nCheckKillDoodadID[MAX_CONDITION_PER_QUEST];		// Doodad ID to destroy
	INT32		nCheckKillDoodadCnt[MAX_CONDITION_PER_QUEST];		// Doodad ID to destroy

	INT32		nCheckItemID[MAX_CONDITION_PER_QUEST];				// Check items
    INT32       nCheckItemCount[MAX_CONDITION_PER_QUEST];

	INT32       nCheckReputationForceID;							// Required NPC faction reputation
	INT32       nCheckReputationForceValue;	                        // Required reputation

    INT32       nCheckVarID[MAX_CHECK_VAR_COUNT];                   // Required variable ID 1
    INT32       nCheckVarValue[MAX_CHECK_VAR_COUNT];                // Required variable value 1 (equality check)

    CHAR        szBeforeCompleteScriptName[COMMON_NAME_LEN];        // Script checking quest completion conditions

    // Actions performed on quest completion
	INT32		nTalkNpcID;											// NPC ID for dialogue
	INT32		nTalkVarID;											// Variable ID used for dialogue
	INT32		nExploreVarID;										// Variable ID used for exploration
    CHAR        szAfterCompleteScriptName[COMMON_NAME_LEN];         // Quest completion script name
	
	// Quest completion reward
	QUEST_REWARD_DATA stRewardData;									// Reward item

	// Actions performed when abandoning the quest
    CHAR        szAbandonScriptName[COMMON_NAME_LEN];				// Quest completion script name

    static BOOL ReadLine(INT32& rnID, const char*& rpcszName, QUEST_DATA* pData, CTabFile * pTabConfig, INT32 nRow);
	static BOOL CheckValidQuestID(INT32 nQuestType, INT32 nQuestID);
};


struct REWARD_QUEST_MONEY_COST_DATA
{
	// Gold cost to raise the bounty quest limit

	INT32		nTime;
	INT32		nMoneyCost;

    static BOOL ReadLine(INT32& rnID, const char*& rpcszName, REWARD_QUEST_MONEY_COST_DATA* pData, CTabFile * pTabConfig, INT32 nRow);
};

struct QUEST_RECYCLE_DATA
{
	// Equipment recycling quest; specified by the corresponding variable

	INT32		nItemLevel;
	INT32		nItemColor;
	INT32		nItemSubType;

	INT32		nVarIndex;

	static BOOL ReadLine(INT32& rnID, const char*& rpcszName, QUEST_RECYCLE_DATA* pData, CTabFile * pTabConfig, INT32 nRow);
};

#endif // _QUEST_DATA_H_
