#ifndef _MONEY_DEF_H_
#define _MONEY_DEF_H_

/// @file money_def.h
/// lua package file money_def.pkg

// tolua_begin

/// @enum MONEY_TYPE
enum MONEY_TYPE
{
	MONEYTYPE_INVALID = -1,

	MONEYTYPE_01,           	///< 绑金
	MONEYTYPE_02,           	///< 金币
	MONEYTYPE_03,           	///< 擂台币
	MONEYTYPE_04,           	///< 元宝
	MONEYTYPE_FATIGUE,      	///< 疲劳度
	MONEYTYPE_SOUL_PTS,     	///< 魂
	MONEYTYPE_MASTER_EXP,   	///< 名师值
	MONEYTYPE_AIR,          	///< 万法之气
	MONEYTYPE_BF,           	///< 战场点数
	MONEYTYPE_GUILD,        	///< 家族贡献
	MONEYTYPE_SPELL_PTS,    	///< 修炼点
    MONEYTYPE_MORAL,        	///< 道义值
    MONEYTYPE_ARENA,        	///< 擂台积分
	MONEYTYPE_ACHIEVEMENTPTS,	///< 成就点数

	MONEYTYPE_COUNT
};

// tolua_end

static const INT64 MAX_MONEY = 1000000000000ll;
static const INT64 ONE_TIME_MAX_MONEY = 2000000000;

#endif // _MONEY_DEF_H_
