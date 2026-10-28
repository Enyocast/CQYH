#ifndef _MONEY_DEF_H_
#define _MONEY_DEF_H_

/// @file money_def.h
/// lua package file money_def.pkg

/// @enum MONEY_TYPE
enum MONEY_TYPE
{
	MONEYTYPE_INVALID = -1,

	MONEYTYPE_01,           	///< Bound gold
	MONEYTYPE_02,           	///< Gold
	MONEYTYPE_03,           	///< unused
	MONEYTYPE_04,           	///< unused
	MONEYTYPE_FATIGUE,      	///< Fatigue
	MONEYTYPE_SOUL_PTS,     	///< Soul
	MONEYTYPE_MASTER_EXP,   	///< Mentor points
	MONEYTYPE_AIR,          	///< Arcane qi
	MONEYTYPE_BF,           	///< Battlefield points
	MONEYTYPE_GUILD,        	///< Guild contribution
	MONEYTYPE_SPELL_PTS,    	///< Cultivation points
    MONEYTYPE_MORAL,        	///< Virtue points
    MONEYTYPE_ARENA,        	///< Arena points
	MONEYTYPE_ACHIEVEMENTPTS,	///< Achievement points

	MONEYTYPE_COUNT
};

static const INT64 MAX_MONEY = 10000000000ll;

#endif // _MONEY_DEF_H_
