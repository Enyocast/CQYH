#ifndef _QUEST_DATA_H_
#define _QUEST_DATA_H_

#include "string_def.h"
#include "quest_def.h"
#include "data_manager.h"
#include "quest_reward_data.h"

//tolua_begin
struct QUEST_DATA
{
    // 基本属性
    INT32       nQuestID;                                           // 任务ID
    INT32       eResetType;                                         // 重置任务类型
	INT32		nQuestType;											// 任务类型
	INT32		nCircleID;											// 环ID
	INT32		nQuality;											// 品质
    UINT32      dwResetTime;                                        // 重置任务偏移时间
    BOOL        bCanAbandon;                                        // 是否可以放弃任务
	BOOL		bCanShare;											// 是否可被共享
	BOOL		bCanPublish;										// 是否可发布

	INT32		nEmergencyCoolDown;									// CD时间

	UINT32		nDurationLimit;										// 是否限时
	char		szName[COMMON_NAME_LEN];							// 任务名称

	INT32		nSceneID[MAX_FLY_SPOT_PER_QUEST];					// 飞行地图ID
	INT32		nX[MAX_FLY_SPOT_PER_QUEST];							// 飞行点x
	INT32		nY[MAX_FLY_SPOT_PER_QUEST];							// 飞行点y
	INT32		nZ[MAX_FLY_SPOT_PER_QUEST];							// 飞行点z

    // 接交任务检测条件
    INT32       nMaxCompletedCount;                                 // 任务最多可以被完成的次数（在任务重置之后）,0表示可无限制完成
    INT32       nClassLimit;                                        // 任务职业需求
    INT32       nSexLimit;                                          // 性别需求
    INT32       nRelationLimit;                                     // 关系需求

    // 接任务检测条件
    INT32       nPreQuestID1;                                       // 前置任务ID
    INT32       nPreQuestID2;                                       // 前置任务ID
    INT32       nStartNpcID;                                        // 开始任务的NPC ID
    INT32       nStartItemID;                                       // 开始任务的Item ID
    BOOL        bStartZone;                                         // 是否从区域触发

    INT32       nMinLevelLimit;                                     // 任务最低等级需求
    INT32       nMaxLevelLimit;                                     // 任务最高等级需求
    INT32       nBuffIDLimit;                                       // 需求BUFF ID
    INT32       nBuffLevelLimit;                                    // 需求BUFF ID
    INT32       nMoneyTypeLimit;                                    // 需求货币类型
    INT32       nMoneyAmountLimit;                                  // 需求货币数量（不扣除）
    INT32       nReputationForceID;                                 // 需求Npc势力声望
    INT32       nReputationMinLimit;                                // 需求最低声望
    INT32       nReputationMaxLimit;                                // 需求最高声望

    INT32       nYearLimit;
    INT32       nMonthLimit;

    INT32       nStartWeekday;                                      // 星期重复任务允许接受的开始时间
    INT32       nWeekdayDuration;                                   // 星期重复任务的持续时间

    INT32       nStartMonthday;                                      // 月份重复任务允许接受的开始时间
    INT32       nMonthdayDuration;                                   // 月份重复任务的持续时间（不可以跨月）

    UINT32      dwAcceptStartTime;                                  // 允许接受时间范围开始
    UINT32      dwAcceptEndTime;                                    // 允许接受时间范围结束
    INT32       nAcceptStartHour;
    INT32       nAcceptStartMin;
    INT32       nAcceptEndHour;
    INT32       nAcceptEndMin;
    INT32       nAcceptStartDayTime;
    INT32       nAcceptEndDayTime;

    INT32       vecItemLimitID[4];                                  // 身上道具需求
    INT32       vecItemLimitCnt[4];

    INT32       nLimitVarID1;                                       // 需求变量ID1
    INT32       nLimitVarValue1;                                    // 需求变量值1（判断相等）
    INT32       nLimitVarID2;                                       // 需求变量ID2
    INT32       nLimitVarValue2;                                    // 需求变量值2（判断相等）
    CHAR        szBeforeAcceptScriptName[COMMON_NAME_LEN];          // 接任务前检测脚本名称

    // 接任务执行动作
    INT32       nOfferMoneyType;                                    // 接任务获得货币类型
    INT32       nOfferMoneyAmount;                                  // 接任务获得货币数量(负值为扣钱)
    INT32       nOfferBuffID;                                       // 接任务获得 BUFF ID
    INT32       nOfferBuffLevel;                                    // 接任务获得 BUFF Level

    INT32       nOfferItemID;                                       // 接任务获得(扣除)道具
    INT32       nOfferItemCnt;                                      // 负值为扣除量
    CHAR        szAfterAcceptScriptName[COMMON_NAME_LEN];           // 接任务后完成脚本名称

    // 交任务检测条件
    INT32       nFinishNpc;                                         // 任务结束的NPC ID
	INT32		nFinishItemID;										// 结束任务的Item ID
    INT32       nCheckBuffID;                                       // 任务完成的BUF检查
    INT32       nCheckBuffLevel;
	INT32		nCheckLevel;										// 任务完成登记检查

	INT32		nCheckKillPlayerLevlStart[CHECK_KILL_PLAYER_CONDITION];	// 检查杀死玩家最低等极
	INT32		nCheckKillPlayerLevlEnd[CHECK_KILL_PLAYER_CONDITION];	// 检查杀死玩家最高等极
	INT32		nCheckKillPlayerCount[CHECK_KILL_PLAYER_CONDITION];		// 检查杀死玩家个数	
	INT32		nCheckKillBufPlayerBufID[CHECK_KILL_PLAYER_CONDITION];	// 杀死指定bufID的玩家
	INT32		nCheckKillBufPlayerCount[CHECK_KILL_PLAYER_CONDITION];	// 杀死指定bufID的玩家数量

    INT32       nCheckKillNpcID[MAX_CONDITION_PER_QUEST];			// 杀怪数检查
    INT32       nCheckKillNpcGroupID[MAX_CONDITION_PER_QUEST];			// 杀怪组检查
    INT32       nCheckKillNpcCnt[MAX_CONDITION_PER_QUEST];

	INT32		nCheckKillItemNpcID[MAX_CONDITION_PER_QUEST];		// 任务物品掉落npcid
	INT32		nCheckKillItemNpcRate[MAX_CONDITION_PER_QUEST];		// 任务物品掉落概率
    INT32       nCheckKillItemCnt[MAX_CONDITION_PER_QUEST];
 
	UINT32		nCheckKillDoodadID[MAX_CONDITION_PER_QUEST];		// 需要摧毁的Doodad ID
	INT32		nCheckKillDoodadCnt[MAX_CONDITION_PER_QUEST];		// 需要摧毁的Doodad ID

	INT32		nCheckItemID[MAX_CONDITION_PER_QUEST];				// 检查物品
    INT32       nCheckItemCount[MAX_CONDITION_PER_QUEST];

	INT32       nCheckReputationForceID;							// 需求Npc势力声望
	INT32       nCheckReputationForceValue;	                        // 需求声望

    INT32       nCheckVarID[MAX_CHECK_VAR_COUNT];                   // 需求变量ID1
    INT32       nCheckVarValue[MAX_CHECK_VAR_COUNT];                // 需求变量值1（判断相等）

    CHAR        szBeforeCompleteScriptName[COMMON_NAME_LEN];        // 完成任务条件脚本名称

    // 交任务执行动作
	INT32		nTalkNpcID;											// 对话的NPC ID
	INT32		nTalkVarID;											// 对话所用Var ID
	INT32		nExploreVarID;										// 探索所用Var ID
    CHAR        szAfterCompleteScriptName[COMMON_NAME_LEN];         // 完成任务脚本名称
	
	// 交任务奖励
	QUEST_REWARD_DATA stRewardData;									// 奖励物品

	// 放弃任务执行动作
    CHAR        szAbandonScriptName[COMMON_NAME_LEN];				// 完成任务脚本名称

    static BOOL ReadLine(INT32& rnID, const char*& rpcszName, QUEST_DATA* pData, CTabFile * pTabConfig, INT32 nRow);
	static BOOL CheckValidQuestID(INT32 nQuestType, INT32 nQuestID);
};


struct REWARD_QUEST_MONEY_COST_DATA
{
	// 悬赏任务突破上限金币消耗

	INT32		nTime;
	INT32		nMoneyCost;

    static BOOL ReadLine(INT32& rnID, const char*& rpcszName, REWARD_QUEST_MONEY_COST_DATA* pData, CTabFile * pTabConfig, INT32 nRow);
};

struct QUEST_RECYCLE_DATA
{
	// 装备回收任务，对应变量指定

	INT32		nItemLevel;
	INT32		nItemColor;
	INT32		nItemSubType;

	INT32		nVarIndex;

	static BOOL ReadLine(INT32& rnID, const char*& rpcszName, QUEST_RECYCLE_DATA* pData, CTabFile * pTabConfig, INT32 nRow);
};

//tolua_end

#endif // _QUEST_DATA_H_
