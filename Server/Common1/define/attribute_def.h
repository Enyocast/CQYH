#ifndef _ATTRIBUTE_DEF_H_
#define _ATTRIBUTE_DEF_H_

///@file attribute_def.h
/// lua package file attribute_def.pkg
#define RATE_MAX			(10000LL)			///< @line
#define MAX_ATTR_NAME_LEN	(128)				///< @line


/// Warning: catPhyAtkHi, catPhyAtkLo, catMagAtkHi, catMagAtkLo这四个属性是放大1w倍存储的，但并不用Rate结尾。

///@enum CHAR_ATTR_TYPE
enum CHAR_ATTR_TYPE
{
	catInvalid = 0,								///< @line

	catDefault,									///< @line
	//	catBeginMainAttr,
	//	catValue = catBeginMainAttr,
	//	catCombatParam,
	//	catEndMainAttr,
	catBeginExAttr,
	catPhyDef = catBeginExAttr,
	catMaxPhyDef,
	catMagDef,
	catMaxMagDef,
	catPhyAtk,
	catMaxPhyAtk,
	catMagAtk,
	catMaxMagAtk,
	catTaoAtk,
	catMaxTaoAtk,
	catMaxHp,
	catMaxMp,
	catWalkSpeed,
	catRunSpeed,

	catAccurate,
	catAgility,
	catMagDodge,
	catCrit,
	catCritDmg,
	catCritResist,
	catCritDmgResist,
	catAntiPhyDef,
	catAntiMagDef,
	catDrugHpRecovery,
	catDrugMpRecovery,
	catLuck,
	catHolyDmg,

	catHurtEnhanced,
	catDmgResist,
	catDmgEnhance,
	catAtkSpeed,

	catHpRecovery,
	catMpRecovery,
	catHpRecoveryTap,
	catMpRecoveryTap,
	catTapIncrease,
	catAtkSpeedRate,

	catPoisonDef,
	catPoisonRecovery,
	catPoisonResist,
	catStunResist,

	catRepelResist,
	catHurtResist,
	catBurnResist,

	catWeaponWeightLmt,
	catArmorWeightLmt,
	catBagWeightLmt,
	catEndExAttr,

	catDmgAbsorb = catEndExAttr,
	catExtraDmg,
	catExtraHardTime,
	catPHitCountDown,
	catPHitNum,
	catSpellPtsIncr,
	catLeech,
	catMpToHp,
	catMpToHpRemain,
	catExtraThunderDmg,
	catDrugHpSlowRecovery,

	catTotal,					///< @line
};

///@enum SPELL_ATTR_TYPE
enum SPELL_ATTR_TYPE
{
	satInvalid = -1,							///< @line
	satBegin,

	satClass = satBegin,						///< @line
	satRequireLevel,							///< @line

	satNextSpell,								///< @line
	satSwitchSpell,								///< @line
	satResetTime,								///< @line
	satCacheTime,								///< @line

	satWeaponTypeR,								///< @line
	satWeaponTypeL,								///< @line

	satCanEquip,								///< @line
	satCastType,								///< @line
	satJudgeType,								///< @line
	satAttackType,								///< @line
	satElementaryType,							///< @line
	satQteType,									///< @line

	satLockType,								///< @line
	satMinDistance,								///< @line
	satMaxDistance,								///< @line
	satMinGrids,								///< @line
	satMaxGrids,								///< @line
	satTolerantDistance,						///< @line
	satTolerantGrids,							///< @line
	satRangeType,								///< @line
	satRangeParam1,								///< @line
	satRangeParam2,								///< @line
	satRangeParam3,								///< @line
	satIgnoreObstacle,							///< @line
	satUseWeaponRange,							///< @line
	satIgnoreTargetRadius,						///< @line
	satAffectedByAtkSpeed,						///< @line
	satUseDPH,									///< @line
	satIgnoreDefense,							///< @line
	satIgnoreClientTarget,						///< @line

	satMaxTargetCount,							///< @line
	satOffsetDirection,							///< @line
	satOffsetDistance,							///< @line

	satHOffsetGrids,							///< @line
	satVOffsetGrids,							///< @line

	satTargetObjType,							///< @line
	satTargetRelationship,						///< @line
	satTargetSpecies,								///< @line
	satTargetSex,								///< @line

	satTargetDirection,							///< @line

	satTargetStance,							///< @line
	satSelfStance,								///< @line

	satCostType,								///< @line
	satInitialCostValue,						///< @line
	satInitialCostValuePct,						///< @line
	satDurativeCostValue,						///< @line
	satDurativeCostValuePct,					///< @line
	satModifierCostValue,						///< @line
	satModifierCostValuePct,					///< @line

	satItemCostID,								///< @line
	satItemCostCount,							///< @line
	satConsumeItem,								///< @line

	satItemCostType,							///< @line
	satItemCostSubType,							///< @line

	satDuraCost,								///< @line

	satCoolDownTriggerType,						///< @line
	satSelfCoolDown,							///< @line
	satEventCoolDown,							///< @line
	satAdjustDirection,							///< @line
	satAffectedByWeaponSpeed,					///< @line
	satPrepareType,								///< @line
	satPrepareTimeMin,							///< @line
	satPrepareTimeMax,							///< @line
	satAccumulateTimeMax,						///< @line
	satAccumulateSeg,							///< @line
	satChannelCount,							///< @line
	satMinEffectCount,							///< @line
	satInterval,								///< @line
	satHardTime,								///< @line
	satWalkDelayTime,							///< @line
	satRunDelayTime,							///< @line

	satHitLevel,								///< @line
	satMoveBreak,								///< @line
	satBreakMove,								///< @line
	satCanMoveInPrepare,						///< @line
	satCanMoveInHardTime,						///< @line
	satHitBreak,								///< @line
	satHardTimeAffectedByCharLevel,				///< @line

	satCancelType,								///< @line
	satCancelLevel,								///< @line
	satCancelHardTime,							///< @line

	satHitTag,									///< @line
	satSpeed,									///< @line

	satEffectPct,								///< @line

	satEffectValue,								///< @line
	satEffectValueMax,							///< @line
	satDefaultValue,							///< @line
	satDefaultValueMax,							///< @line
	satAffectedByNpcParam,

	satThreatPct,								///< @line
	satThreatValue,								///< @line
	satThreatMax,								///< @line
	satCanCastOnMount,							///< @line
	satCasterDeadLimit,							///< @line
	satTargetDeadLimit,							///< @line
	satCasterLimitBits,							///< @line
	satCasterCCLimitBits,						///< @line
	satSceneTypeLimit,							///< @line

	satCasterCheckNode,							///< @line
	satTargetCheckNode,							///< @line
	satOnLearn,									///< @line
	satOnForget,								///< @line
	satOnEquip,									///< @line
	satOnUnEquip,								///< @line
	satOnPrepare,								///< @line
	satOnCast,									///< @line
	satOnBreak,									///< @line
	satOnCreateBullet,							///< @line
	satBeforeRoll,								///< @line
	satAfterRoll,								///< @line
	satBeforeEffect,							///< @line
	satAfterEffect,								///< @line
	satNeedCache,								///< @line

	satCancelStiff,								///< @line
	satKnockBackRate,							///< @line
	satBaseStiffTime,							///< @line
	satMonsterChaseDelayTime,					///< @line
	satChainEffect,								///< @line
	satBindSlot,								///< @line
	satTrigEvent,								///< @line

	satTotal									///< @line
};

///@enum AURA_ATTR_TYPE
enum AURA_ATTR_TYPE
{
	aatInvalid = -1,							///< @line

	aatCategory,								///< @line
	aatType,									///< @line
	aatGroup,									///< @line
	aatDuration,								///< @line
	aatDelay,									///< @line
	aatInterval,								///< @line
	aatSameIdStackType,							///< @line
	aatDiffIdStackType,							///< @line

	aatStackTypeSameIdSameCaster,				///< @line
	aatStackSameTypeSameCaster,					///< @line
	aatStackSameGroupSameCaster,				///< @line
	aatStackTypeSameIdDiffCaster,				///< @line
	aatStackSameTypeDiffCaster,					///< @line
	aatStackSameGroupDiffCaster,				///< @line


	aatTimeCover,								///< @line
	aatStackResetTime,							///< @line
	aatInitStackCount,							///< @line
	aatMaxStackCount,							///< @line
//	aatStackEfficient,							///< @line
//	aatCoexist,									///< @line
	aatStrengthLevel,							///< @line

	aatCanDispel,								///< @line
	aatCanCancel,								///< @line
	aatDispelCount,								///< @line
	aatTrigOnRemoveWhenDispel,					///< @line
	aatTrigOnRemoveWhenTimeup,					///< @line

	aatAttackType,								///< @line
	aatJudgeType,								///< @line
	aatElementaryType,							///< @line

	aatEffectPctX,								///< @line
	aatEffectValueX,							///< @line
	aatEffectPct,								///< @line
	aatEffectValue,								///< @line
	aatThreatPct,								///< @line
	aatThreatValue,								///< @line
	aatThreatMax,								///< @line
	aatRemoveWhenDead,							///< @line
	aatSaveToDB,								///< @line
	aatOfflineTimeValid,						///< @line
	aatHiddenToClient,							///< @line
	aatHiddenToSelf,							///< @line
	aatControlDecay,							///< @line
	aatEffectTimeMin,							///< @line
	aatEternal,									///< @line
	aatIgnoreDefense,							///< @line
	aatIgnoreResistence,
	aatAffectedCharAttr,
	aatDisplayGroup,							///< @line
	aatDisplayValue,							///< @line
	aatResistType,								///< @line
	aatEffectDecay,								///< @line

	aatOnAppend,								///< @line
	aatBeforeStack,								///< @line
	aatAfterStack,								///< @line
	aatOnTimeup,								///< @line
	aatOnDispel,								///< @line
	aatOnRemove,								///< @line

	aatTotal									///< @line
};

///@enum MISSILE_ATTR_TYPE
enum MISSILE_ATTR_TYPE
{
	matInvalid = -1,							///< @line

	matDefault,									///< @line
	matLockType,								///< @line
	matMoveType,								///< @line
	matMoveSpeed,								///< @line
	matHeight,									///< @line
	matLifeTime,								///< @line
	matMaxCollisionCount,						///< @line
	matMaxTargetCountPerCollision,				///< @line
	matRangeType,								///< @line
	matRangeParam1,								///< @line
	matRangeParam2,								///< @line
	matRangeParam3,								///< @line
	matBlockShape,								///< @line
	matBlockParam,								///< @line
	matOffsetDirection,							///< @line
	matOffsetDistance,							///< @line
	matHOffsetGrids,							///< @line
	matVOffsetGrids,							///< @line
	matDelay,									///< @line
	matInterval,								///< @line
	matNotMultiEffect,							///< @line
	matNotHitLastTarget,						///< @line
	matBlockType,								///< @line
	matOnInit,									///< @line
	matOnCreate,								///< @line
	matOnScan,									///< @line
	matOnTimeup,								///< @line
	matOnRemove,								///< @line
	matOnCharEnter,								///< @line
	matOnCharLeave,								///< @line

	matTotal									///< @line
};

inline INT32 MakeAttrKey(INT32 nKey, INT32 nClass)
{
	return (nKey << 16) + nClass;
}

#endif // _attribute_def_h__
