#ifndef _ATTRIBUTE_DEF_H_
#define _ATTRIBUTE_DEF_H_

///@file attribute_def.h
/// lua package file attribute_def.pkg
#define RATE_MAX			(10000LL)			///< @line
#define MAX_ATTR_NAME_LEN	(128)				///< @line


/// Warning: catPhyAtkHi, catPhyAtkLo, catMagAtkHi, catMagAtkLo These four attributes are stored multiplied by 10,000, but do not end in Rate.

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

	// ====================

	catPhyDef = catBeginExAttr,    // 2	 Physical defense
	catMaxPhyDef,				   // 3	 Maximum physical defense
	catMagDef,					   // 4	 Magic defense
	catMaxMagDef,				   // 5	 Maximum magic defense
	catPhyAtk,					   // 6	 Physical attack
	catMaxPhyAtk,				   // 7	 Maximum physical attack
	catMagAtk,					   // 8	 Magic attack
	catMaxMagAtk,				   // 9	 Maximum magic attack
	catTaoAtk,					   // 10 Tao attack
	catMaxTaoAtk,				   // 11 Maximum Tao attack
	catMaxHp,					   // 12 Maximum HP
	catMaxMp,					   // 13 Maximum MP
	catWalkSpeed,				   // 14 Walking speed
	catRunSpeed,				   // 15 Running speed

	catAccurate,				   // 16 Accuracy / hit chance
	catAgility,					   // 17 Agility
	catMagDodge,				   // 18 Magic evasion
	catCrit,					   // 19 Critical hit rate
	catCritDmg,					   // 20 Critical damage
	catCritResist,				   // 21 Critical hit resistance
	catCritDmgResist,			   // 22 Critical damage resistance
	catAntiPhyDef,				   // 23 Physical penetration
	catAntiMagDef,				   // 24 Magic penetration
	catDrugHpRecovery,			   // 25 Potion HP recovery
	catDrugMpRecovery,			   // 26 Potion MP recovery
	catLuck,					   // 27 Luck
	catHolyDmg,					   // 28 Holy damage

	catHurtEnhanced,			   // 29 Damage bonus when hit (increases the next attack’s damage)
	catDmgResist,				   // 30 Damage resistance
	catDmgEnhance,				   // 31 Damage bonus
	catAtkSpeed,				   // 32 Attack speed

	catHpRecovery,				   // 33 HP recovery
	catMpRecovery,				   // 34 MP recovery
	catHpRecoveryTap,			   // 35 HP recovery coefficient
	catMpRecoveryTap,			   // 36 MP recovery coefficient
	catTapIncrease,				   // 37 Coefficient increase?
	catAtkSpeedRate,			   // 38 Attack speed bonus rate

	catPoisonDef,				   // 39 Poison defense
	catPoisonRecovery,			   // 40 Poison recovery

	catPoisonResist,			   // 41 Poison resistance
	catStunResist,				   // 42 Stun resistance
	catRepelResist,				   // 43 Knockback resistance
	catHurtResist,				   // 44 Hit-stun resistance
	catBurnResist,				   // 45 Burn resistance

	catWeaponWeightLmt,			   // 46 Weapon weight limit
	catArmorWeightLmt,			   // 47 Armor weight limit
	catBagWeightLmt,			   // 48 Bag weight limit

	catEndExAttr,				   // 49 

	// ====================

	catDmgAbsorb = catEndExAttr,   // 49 Damage absorption
	catExtraDmg,				   // 50 Additional flat damage - in use
	catExtraHardTime,			   // 51 Extended stun duration - in use
	catPHitCountDown,			   // 52 Physical combo interval - in use
	catPHitNum,					   // 53 Physical combo count - in use
	catSpellPtsIncr,			   // 54 Skill point bonus - in use
	catLeech,					   // 55 Life-steal coefficient - in use
	catMpToHp,					   // 56 Convert MP to HP - in use
	catMpToHpRemain,			   // 57 Convert remaining MP to HP - in use
	catExtraThunderDmg,			   // 58 Additional lightning damage
	catDrugHpSlowRecovery,		   // 59 Potion recovery over time - in use
	catExpRate,					   // 60 Experience gain rate

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
	satWeaponTypeL,								///< @line  Never called

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
	satTolerantDistance,						///< @line  Never called
	satTolerantGrids,							///< @line
	satRangeType,								///< @line
	satRangeParam1,								///< @line
	satRangeParam2,								///< @line
	satRangeParam3,								///< @line
	satIgnoreObstacle,							///< @line
	satUseWeaponRange,							///< @line
	satIgnoreTargetRadius,						///< @line
	satAffectedByAtkSpeed,						///< @line
	satUseDPH,									///< @line  Never called
	satIgnoreDefense,							///< @line
	satIgnoreClientTarget,						///< @line

	satMaxTargetCount,							///< @line
	satOffsetDirection,							///< @line
	satOffsetDistance,							///< @line

	satHOffsetGrids,							///< @line
	satVOffsetGrids,							///< @line

	satTargetObjType,							///< @line
	satTargetRelationship,						///< @line
	satTargetSpecies,							///< @line  Never called
	satTargetSex,								///< @line  Never called

	satTargetDirection,							///< @line  Never called

	satTargetStance,							///< @line
	satSelfStance,								///< @line  Never called

	satCostType,								///< @line  Never called
	satInitialCostValue,						///< @line
	satInitialCostValuePct,						///< @line
	satDurativeCostValue,						///< @line
	satDurativeCostValuePct,					///< @line
	satModifierCostValue,						///< @line
	satModifierCostValuePct,					///< @line

	satItemCostID,								///< @line
	satItemCostCount,							///< @line
	satConsumeItem,								///< @line  Never called

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

	satHitLevel,								///< @line  Never called
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

	satIsMixEffect,								///< @line  Never called
	satMixEffectPhyRate,						///< @line  Never called
	satMixEffectMagRate,						///< @line  Never called

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
	satSceneTypeLimit,							///< @line  Never called

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
	aatSameIdStackType,							///< @line  Never called
	aatDiffIdStackType,							///< @line  Never called

	aatStackTypeSameIdSameCaster,				///< @line
	aatStackSameTypeSameCaster,					///< @line
	aatStackSameGroupSameCaster,				///< @line  Never called
	aatStackTypeSameIdDiffCaster,				///< @line
	aatStackSameTypeDiffCaster,					///< @line
	aatStackSameGroupDiffCaster,				///< @line  Never called


	aatTimeCover,								///< @line
	aatStackResetTime,							///< @line
	aatInitStackCount,							///< @line
	aatMaxStackCount,							///< @line
//	aatStackEfficient,							///< @line
//	aatCoexist,									///< @line
	aatStrengthLevel,							///< @line

	aatCanDispel,								///< @line
	aatCanCancel,								///< @line
	aatDispelCount,								///< @line  Never called
	aatTrigOnRemoveWhenDispel,					///< @line
	aatTrigOnRemoveWhenTimeup,					///< @line

	aatAttackType,								///< @line
	aatJudgeType,								///< @line  Never called
	aatElementaryType,							///< @line  Never called

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
	aatIgnoreResistence,						///< @line  Never called
	aatAffectedCharAttr,						///< @line  Never called
	aatDisplayGroup,							///< @line
	aatDisplayValue,							///< @line
	aatResistType,								///< @line
	aatEffectDecay,								///< @line

	aatOnAppend,								///< @line
	aatBeforeStack,								///< @line  Never called
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
	matLockType,								///< @line  Never called
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
	matBlockShape,								///< @line  Never called
	matBlockParam,								///< @line  Never called
	matOffsetDirection,							///< @line
	matOffsetDistance,							///< @line
	matHOffsetGrids,							///< @line
	matVOffsetGrids,							///< @line
	matDelay,									///< @line
	matInterval,								///< @line
	matNotMultiEffect,							///< @line
	matNotHitLastTarget,						///< @line
	matBlockType,								///< @line  Never called
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
