#ifndef _MONEY_DEF_H_
#define _MONEY_DEF_H_

/// @file money_def.h
/// lua package file money_def.pkg

/// @enum MONEY_TYPE
enum MONEY_TYPE
{
	MONEYTYPE_INVALID = -1,

	MONEYTYPE_01,           	///< 绑金
	MONEYTYPE_02,           	///< 金币
	MONEYTYPE_03,           	///< unused
	MONEYTYPE_04,           	///< unused
	MONEYTYPE_FATIGUE,      	///< 疲劳度
	MONEYTYPE_SOUL_PTS,     	///< 魂
	MONEYTYPE_MASTER_EXP,   	///< 名师值
	MONEYTYPE_AIR,          	///< 万法之气
	MONEYTYPE_BF,           	///< 战场点数
	MONEYTYPE_GUILD,        	///< 家族贡献
	MONEYTYPE_SPELL_PTS,    	///< 修炼点
    MONEYTYPE_MORAL,        	///< 道义值
    MONEYTYPE_ARENA,        	///< 竞技场点数
	MONEYTYPE_ACHIEVEMENTPTS,	///< 成就点数

	MONEYTYPE_COUNT
};

static const INT64 MAX_MONEY = 10000000000ll;

#endif // _MONEY_DEF_H_
