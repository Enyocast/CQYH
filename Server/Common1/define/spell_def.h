#ifndef _SPELL_DEF_H_
#define _SPELL_DEF_H_

/// @file spell_def.h

#include "attribute_def.h"

//#define MAX_SPELL_SLOT 16
#define MAX_SPELL_LEVEL 3 
#define MAX_RUNE_SLOT 0xFF
#define MAX_EX_PARAM_COUNT	(4)
#define MAX_SPELL_NAME	(64)
#define MAX_CD_GROUP	(8)
#define MAX_EX_CAST		(5)
#define MAX_SPELL_TARGET_COUNT	(20)
#define MAX_SPELL_EFFECT_DISTANCE (1024 * GRID_WIDTH)
#define MAX_SUBSPELL_DEPTH	(8)

enum SPELL_SLOTS_DEF
{
	qssSlotInvalid = -1,

	qssSlotBegin,
	qssNormalAtk = qssSlotBegin,
	qssQteBegin,
	qssBossQTE = qssQteBegin,
	qssQteEnd,

	qssPassiveBegin = qssQteEnd,
	qssPassive1 = qssPassiveBegin,
	qssPassive2,
	qssPassive3,
	qssPassiveEnd,

	qssActiveBegin = qssPassiveEnd,
	qssKey0 = qssActiveBegin,
	qssKey1,
	qssKey2,
	qssKey3,
	qssKey4,
	qssKey5,
	qssKey6,
	qssKey7,
	qssKey8,
	qssKey9,
	qssKey10,
	qssKey11,
	qssActiveEnd,

	qssSlotCount = qssActiveEnd,
};

enum SPELL_FLAG_BITS
{
	sfbInvalid = -1,

	sfbRoundTableBegin,
	sfbCrit = sfbRoundTableBegin,	// ±©ª˜ = 0
	sfbBlock,						// ∏Òµ≤ = 1
	sfbDodge,						// …¡±‹ = 2
	sfbParry,						// ’–º‹ = 3
	sfbMiss,						// Œ¥√¸÷– = 4
	sfbNormal,						// ∆’Õ® = 5
	sfbRoundTableEnd,

	sfbImmune = sfbRoundTableEnd,	// √‚“ﬂ = 6
	sfbDead,						// À¿Õˆ = 7
	sfbEmptyEffect,

	sfbTotal
};

enum SPELL_CAST_TYPE
{
	spctInvalid = -1,

	spctPassive,
	spctActive,
	spctSubSpell,
	spctDirectly,
	spctSwitch,

	spctTotal
};

enum SPELL_JUDGE_TYPE
{
	spjtInvalid = -1,

	spjtDirectly,
	spjtPhy,
	spjtMag,

	spjtTotal
};

enum SPELL_ATTACK_TYPE
{
	spatInvalid = -1,
	
	spatNone,
	spatPhy,
	spatMag,
	spatTao,

	spatTotal
};

enum SPELL_DAMAGE_TYPE
{
	spdtInvalid = -1,

	spdtNone,

	spdtDamageTypeBegin,
	spdtPhy = spdtDamageTypeBegin,
	spdtEarth,
	spdtFire,
	spdtWater,
	spdtWind,
	spdtThunder,
	spdtLight,
	spdtShadow,
	spdtNature,
	spdtDamageTypeEnd,

	spdtTotal
};

enum SPELL_RANGE_TYPE
{
	sprtInvalid = -1,

	sprtSingle,
	sprtCircle,
	sprtSector,
	sprtArc,
	sprtRectangle,
	sprtRearHalfCircle,

	sprtGridBegin = sprtRearHalfCircle,
	sprtGridLine,
	sprtGridRect,
	sprtGridCross,
	sprtGridX,
	sprtGridU,
	sprtGridSingle,
	sprtGridLineTransverse,
	sprtGridEnd,

	sprtTotal = sprtGridEnd,
};

enum SPELL_LOCK_TYPE
{
	spltInvalid = -1,

	spltSelf,
	spltObject,
	spltDirection,
	spltPos,
	spltSelfPos,
	spltSmartPos,

	spltTotal
};

enum SPELL_COST_TYPE
{
	spcotInvalid = -1,

	spcotFury,
	spcotEnergy,
	spcotMana,
	spcotWhite,

	spcotTotal
};

enum SPELL_TARGET_SEX_TYPE
{
	sptstInvalid	= -1,
	sptstMale,
	sptstFemale,
	sptstNone
};

enum SPELL_TARGET_POS_TYPE
{
	sptptInvalid	= -1,
	sptptFront,
	sptptBack,
};

enum SPELL_TARGET_RELATIONSHIP
{
	sptrInvalid = -1,

	sptrSelf,
	sptrFriendly,
	sptrEnemy,

	sptrTotal
};


enum SPELL_TARGET_RACE_TYPE
{
	sptotInvalid = -1,

	sptotNone,
	sptotPlayer,
	sptotHuman,
	sptotHumanlike,
	sptotBeast,
	sptotInsect,
	sptotPlant,
	sptotUndead,
	sptotMachine,
	sptotDragon,
	sptotDemon,
	sptotElements,
	sptotBuilding,

	sptotTotal
};
enum SPELL_COOLDOWN_TRIGGER_TYPE
{
	spcdtInvalid = -1,

	spcdtOnPrepare,
	spcdtOnCast,

	spcdtTotal,
};

enum SPELL_FAKE_PREPARE_TYPE
{
	sfpptInvalid = -1,

	sfpptChanneled,
	sfpptPrepared,
	sfpptPreparedEx,
	sfpptInstantCast,
	sfpptAccumulated,

	sfpptTotal

};

enum SPELL_PREPARE_TYPE
{
	spptInvalid = -1,

	spptChanneled,
	spptPrepared,
	spptAccumulated,

	spptTotal
};

enum SPELL_CANCEL_TYPE
{
	spcltInvalid = -1,

	spcltNone,
	spcltDependOnValue,
	spcltInstant,

	spcltTotal,
};

enum SPELL_CONTROL_TAG
{
	spctagInvalid = -1,

	spctagNoMove,
	spctagNoCast,

	spctagTotal,
};

enum SPELL_HIT_TAG
{
	sphtagInvalid = -1,

	sphtagCommon,
	sphtagDefence,
	sphtagSuperArmor,
	sphtagInvincible,

	sphtagTotal,
};

enum SPELL_STIFF_BITS
{
	spslInvalid = -1,

	spslBreakCast,
	spslBreakMovement,
	spslKnockBack,

	spslTotal
};

enum SPELL_QTE_TYPE
{
	spqteInvalid = -1,

	spqteNone,
	spqteCounter,
	spqteChase,
	spqteTerminate,

	spqteTotal
};

inline INT32 MakeSpellKey(INT32 nID, INT32 nLevel, INT32 nRuneID)
{
    return (nID << 16) + (nLevel << 8) + nRuneID;
}

inline INT32 MakeSpellProgressKey(INT32 nID, INT32 nLevel)
{
    return (nID << 16) + nLevel;
}

inline INT32 MakeAuraKey(INT32 nID, INT32 nLevel)
{
    return (nID << 16) + nLevel;
}

inline UINT32 MakeAuraInstanceKey(UINT32 nType, UINT32 dwGenerator)
{
	return (nType << 24) + dwGenerator;
}

inline INT32 GetAuraTypeFromInstanceID(UINT32 dwAuraInstanceID)
{
	return dwAuraInstanceID >> 24;
}

enum COOLDOWN_TYPE
{
	COOLDOWN_INVALID = -1,
	COOLDOWN_GROUP,         /// @line
	COOLDOWN_SPELL,         /// @line
	COOLDOWN_ITEM,          /// @line
	COOLDOWN_QUEST,         /// @line
    COOLDOWN_AI,            /// @line
	COOLDOWN_SPELL_EVENT_TRIGGER, /// @line
	COOLDOWN_MISC,          /// @line
	COOLDOWN_SCRIPT_SPELL,  /// @line
	COOLDOWN_SPECIAL_ITEM,	/// @line
	COOLDOWN_TOTAL          /// @line
};

enum COOLDOWN_MISC_TYPE
{
	COOLDOWN_MISC_INVALID = -1,

	COOLDOWN_MISC_HERO_REVIVE,
	COOLDOWN_MISC_ARREST,

	COOLDOWN_MISC_TOTAL
};

enum COOLDOWN_SAVE_TYPE
{
	COOLDOWN_SAVE_TYPE_INVALID = 0,
	COOLDOWN_SAVE_TYPE_1,
	COOLDOWN_SAVE_TYPE_2,
};

inline INT32 MakeCoolDownID(INT32 nType, INT32 nID)
{
	return (nType << 24) + nID;
}

inline void ParseCoolDownID(INT32 ID, INT32& nType, INT32& nID)
{
	nType = ID >> 24;
	nID = (ID << 8 ) >> 8;
}

enum SPELL_PRACTICE_TYPE
{
	ptInvalid = -1,

	ptNone,
	ptNormal,
	ptFast,

	ptTotal
};

enum NORMAL_PRACTICE_TYPE
{
	nptInvalid = 0,
	nptType1,
	nptType2,
	nptType3,

	nptCount,
};

enum RUNE_FRAG_TYPE
{
	rftInvalid = -1,

	rftFragA,
	rftFragB,
	rftFragC,
	rftFragD,
	rftFragE,

	rftCount,
};

enum RUNE_DURABILITY_TYPE
{
	rdtInvalid = -1,

	rdtNever,
	rdtByUseTimes,
	rdtByDuration,

	rdtCount,
};

inline INT32 MakeRuneKey(INT32 nSpellID, INT32 nRuneSlot)
{
    return (nSpellID << 16) + nRuneSlot;
}

struct ExtraParam
{
	INT32 m_nX[MAX_EX_PARAM_COUNT];
};

enum SPELL_EVENT_SOURCE
{
	sesInvalid = -1,

	sesFromSpell,
	sesFromAura,
	sesFromEquip,

	sesTotal
};

static INT32 s_MaxAtkTable[spatTotal] =
{
	catDefault,		// none
	catMaxPhyAtk,	// melee
	catMaxMagAtk,	// magic
	catMaxTaoAtk,	// tao 
};

static INT32 s_AtkTable[spatTotal] =
{
	catDefault,	// none
	catPhyAtk,	// melee
	catMagAtk,	// magic
	catTaoAtk,	// magic
};

static INT32 s_MaxDefTable[spatTotal] =
{
	catDefault,		// none
	catMaxPhyDef,	// phy
	catMaxMagDef,	// mag
	catMaxMagDef,	// tao 
};

static INT32 s_DefTable[spatTotal] =
{
	catDefault,	// none
	catPhyDef,	// phy
	catMagDef,	// mag
	catMagDef,	// tao 
};

static INT32 s_AntiDefTable[spatTotal] =
{
	catDefault,	// none
	catAntiPhyDef,	// phy
	catAntiMagDef,	// mag
	catAntiMagDef,	// tao 
};

static INT32 s_SpeedTable[] =
{
	catDefault,			// spatNone
	catAtkSpeedRate,	// spatPhy
	catAtkSpeedRate,	// spatMag
	catAtkSpeedRate,	// spatTao
};



union SpellEventKey
{
	struct
	{
		unsigned uOccID			: 8;
		unsigned uSource		: 8;
		unsigned uRegisterID	: 16;
		unsigned uGenerator		: 32;
	};

	UINT64 qwEventKey;
};

inline void SplitEventKey(UINT64 qwEventKey, INT32& nOccasionID, INT32& eSource, INT32& nRegisterID)
{
	SpellEventKey Key;
	Key.qwEventKey = qwEventKey;

	nOccasionID = Key.uOccID;
	eSource = Key.uSource;
	nRegisterID = Key.uRegisterID;
}

inline INT32 GetOccasionID(UINT64 qwEventKey)
{
	SpellEventKey Key;
	Key.qwEventKey = qwEventKey;

	return Key.uOccID;
}

#endif // _spell_def_h__
