#ifndef _SPIRIT_DATA_H_
#define _SPIRIT_DATA_H_

#include "data_manager.h"
#include "spirit_def.h"
#include "string_def.h"
#include "role_def.h"

struct SPIRIT_DATA
{
	// base
	INT32 nLevel;
	INT32 nNextLevelExp;										// 升级经验
	INT32 nSoulCost;											// 每次转化消耗魂
	INT32 nAddExp;												// 每次转化增加经验
	INT32 nAddSpiritPts;										// 每次转化增加修炼点
	INT32 nPower;												// 战斗力
	INT32 nAttrTemplateNodeID[MAX_SPIRIT_NODE_PER_LEVEL];		// 属性模板ID
	INT32 nAttrNodeID[MAX_SPIRIT_NODE_PER_LEVEL];				
	BOOL  nBroadcastStringID;									// 是否需要电视机广播

	// Exp2Pts
	UINT32	dwDailyChangeCDTime;								// 转化CD时间
	INT32	nOfflineChangeDiscount[vlTotal-1];					// vip离线转化的折扣
	INT32	nVipOnlineChangeDiscount[vlTotal-1];				// vip在线转化的加成
	INT32	nMoneyCostOneShot;									// 一键转化金币消耗
	INT32	nDailyExp2PtsMoneyCost;								// 魂转修炼点每日最大消耗
	INT32	nDailyExp2PtsMaxCount;								// 混转修炼点每日最大次数

	static BOOL ReadLine(INT32& rnID, const char*& rpcszName, SPIRIT_DATA* pData, CTabFile* pTabConfig, INT32 nRow);
};

struct SPIRIT_CHANGE_DATA
{
	INT32	nIndex;
	INT32	nDailyChangeTime;					// 每日完成次数
	INT32	nMoneyCostDiscount;					// 金币加成 

	static BOOL ReadLine(INT32& rnID, const char*& rpcszName, SPIRIT_CHANGE_DATA* pData, CTabFile* pTabConfig, INT32 nRow);
};

struct AIR_LEVEL_DATA							// 练气阶段数据
{
	INT32	nLevel;								// 练气阶段
	INT32	nPtsCost;
	INT32	nNextLevelRate;
	INT32	nSpiritLevelLimit;					// 境界等级限制
	INT32	nDropMoneyCount;					// 万法之气数量
	INT32	nClassLimit;						// 职业限制(用于控制掉落气的类型)   
	BOOL	nBroadcastStringID;					// 是否需要广播

	INT32	nDropAirID[MAX_DROP_AIR_COUNT];
	INT32	nDropAirRate[MAX_DROP_AIR_COUNT];   

	static BOOL ReadLine(INT32& rnID, const char*& rpcszName, AIR_LEVEL_DATA* pData, CTabFile* pTabConfig, INT32 nRow);
};

struct AIR_DATA						// 气属性模板
{
	INT32	nAirID;
	INT32	nColor;
	INT32	nLevel;					// 气的等级
	INT32	nExp;					// 初始经验
	INT32	nNextLevelExp;			// 升级经验
	INT32	nNextLevelID;
	INT32	nExchangeCount;			// 万法之气兑换数量
	INT32	nGroupID;				// 组id 同组的气只能装备一个
	INT32	nBroadcastStringID;			// 是否需要广播

	INT32	nHandbookType;	
	INT32	nHandbookIndex;		

	INT32	nNodeTemplateID[MAX_ATTR_PER_NODE];
	INT32	nNodeID[MAX_ATTR_PER_NODE];
	char	szAirname[AIR_NAME_LEN];

	static BOOL ReadLine(INT32& rnID, const char*& rpcszName, AIR_DATA* pData, CTabFile* pTabConfig, INT32 nRow);
};

struct BLOOD_DATA												// 血脉
{
	INT32	nPage;
	INT32	nSlot;
	INT32	nNumber;

	INT32	nSpiritPtsCost;
	INT32	nRate;												// 刷出10的概率
	INT32	nLevelLimit;										// 所需境界等级

	INT32	nPageLevelLimit;									// 开启此血脉所需要人物等级

	INT32	nAttrTemplateNodeID[MAX_BLOODSEA_ATTR_PER_SLOT];	// 属性
	INT32	nNodeID[MAX_BLOODSEA_ATTR_PER_SLOT];

	static BOOL ReadLine(INT32& rnID, const char*& rpcszName, BLOOD_DATA* pData, CTabFile* pTabConfig, INT32 nRow);
};

struct SPIRIT_SLOT_DATA
{
	INT32	nSlotIndex;
	INT32	nLevelLimit;
	INT32	nMoneyCost;

	static BOOL ReadLine(INT32& rnID, const char*& rpcszName, SPIRIT_SLOT_DATA* pData, CTabFile* pTabConfig, INT32 nRow);
};

#endif // _SPIRIT_DATA_H_