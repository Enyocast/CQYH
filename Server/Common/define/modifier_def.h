#ifndef _MODIFIER_DEF_H_
#define _MODIFIER_DEF_H_

#define MODIFIER_PARAM_COUNT		(3)

enum MODIFIER_X_TYPE
{
	mxtUseNone = 0,

	mxtUseX1,
	mxtUseX2,
	mxtUseX3,
	mxtUseX4,

	mxtTotal,
};

enum MODIFIER_TARGET_TYPE
{
	mttInvalid = -1,

	mttCharacter,
	mttBullet,
	mttMissile,

	mttTotal
};

enum MODIFIER_RET_CODE
{
	mrcError = -1,

	mrcFalse,
	mrcTrue,
	mrcTrueAndBreak,
};

enum MODIFIER_EVENT_OCCASION
{
	meoInvalid = -1,

	meoBulletEventBegin,
	meoOnBulletCreate = meoBulletEventBegin,
	meoBeforeRoll,
	meoAfterRollAsCaster,
	meoAfterRollAsTarget,
	meoOnBulletHitAsCaster,
	meoOnBulletHitAsTarget,
	meoAfterApplyDefenceAsCaster,
	meoAfterApplyDefenceAsTarget,
	meoBeforeDamageEnhancedAsCaster,
	meoBeforeDamageEnhancedAsTarget,
	meoAfterDamageAsCaster,
	meoAfterDamageAsTarget,
	meoBeforeApplyDamageAsTarget,
	meoBulletEventEnd,

	meoCharEventBegin = meoBulletEventEnd,
	meoOnCharCast = meoCharEventBegin,
	meoOnCharCastSuccess,
	meoOnCharPreCast1,
	meoOnCharPreCast2,
	meoOnCharPreCast3,
	meoOnCharPreCast4,
	meoOnCharPreCast5,
	meoOnTimeup,
	meoOnAppendAura,
	meoOnRemoveAura,
	meoOnEquipItem,
	meoOnAuraTimeup,
	meoOnAuraEffect,
	meoOnAppendAuraAsCaster,
	meoOnDying,
	meoCharEventEnd,

	meoTotal = meoCharEventEnd
};

enum CHAR_MODIFIER_INDEX
{
	cmiInvalid = 0,

	cmi_A,			///< @line		Change walk or run speed; parameter 1 specifies the change type (absolute value)
	cmi_B,			///< @line		Change selected attributes by an absolute value
	cmi_003,		///< @line		Change selected attributes by a percentage obtained from the aura’s GetEffectPct() function
	cmi_004,		///< @line		Change walk or run speed; parameter 1 specifies the change type (percentage from the aura’s GetEffectPct())
	cmi_005,		///< @line		GenerateSingleBullet,							Generate one bullet (single-target attack)
	cmi_006,		///< @line		GenerateMultiBullet,							Generate multiple bullets (spread or multi-shot)
	cmi_007,		///< @line		GenerateMissile,								Generate a projectile (such as a fireball or arrow)
	cmi_008,		///< @line		Charge,											Charge (straight-line movement and damage)
	cmi_009,		///< @line		SingleAura,										Apply a single-target status effect (such as a buff)
	cmi_010,		///< @line		MultiAura,										Apply a group status effect (such as a party buff)
	cmi_011,		///< @line		Stun,											Stun (hard crowd control)
	cmi_012,		///< @line		EnableAttribute,								Enable an attribute
	cmi_013,		///< @line		MutiBulletWithAvgDamage,						Generate multiple bullets with shared damage (such as a shotgun)
	cmi_014,		///< @line		AuraRegisterEvent,								Register an event for a status effect (such as a trigger condition)
	cmi_015,		///< @line		______NotImplemented_No15,						
	cmi_016,		///< @line		LeapToTargetPos,								Leap to the target position (gap closer)
	cmi_017,		///< @line		SpellRegisterEventOnEquip,						Register a spell event on equip (such as a triggered effect)
	cmi_018,		///< @line		Fear,											Fear (soft crowd control; target flees)
	cmi_019,		///< @line		ModifyAttackWithDefense,						Adjust attack based on defense (armor penetration)
	cmi_020,		///< @line		DirectlyAddSpell,								Add a spell directly
	cmi_021,		///< @line		CircleSearchEnemyAndCastSubSpell,				Search for enemies in a circle and cast a sub-spell
	cmi_022,		///< @line		ReduceCurrentAuraStackCount,					Reduce the current aura stack count
	cmi_023,		///< @line		ModifyPendingSpell,								Modify a pending spell (dynamic adjustment)
	cmi_024,		///< @line		SetDamageAbsorb,								Set damage absorption (shield value)
	cmi_025,		///< @line		AuraCheckDamageAbsorb,							Check status damage absorption (such as a shield)
	cmi_026,		///< @line		SpellRegisterTimerEvent,						Register a timed spell event (delayed trigger)
	cmi_027,		///< @line		DirectlyCastSubSpell,							Cast a sub-spell directly
	cmi_028,		///< @line		TeleportToLockedTarget,							Teleport to the locked target (blink)
	cmi_029,		///< @line		CharInvincible,									Make the character invincible (brief damage immunity)
	cmi_030,		///< @line		ChargeToTarget,									Charge toward the target
	cmi_031,		///< @line		GenerateSingleHealBullet,						Generate a single-target healing bullet (such as a healing arrow)
	cmi_032,		///< @line		GenerateMultiHealBullet,						Generate multiple healing bullets (area healing)
	cmi_033,		///< @line		GenerateTeamHealBullet,							Generate team healing bullets
	cmi_034,		///< @line		AdjustSpellDirectionWithFaceDirection,			Adjust spell direction to match character facing
	cmi_035,		///< @line		RecoveryHp,										Restore HP
	cmi_036,		///< @line		CheckItem,										Check an item (consumable or equipment requirement)
	cmi_037,		///< @line		CheckAccumulateTime,							Check accumulated time (such as a charge mechanic)
	cmi_038,		///< @line		SetCharFlagBit,									Set a character flag bit
	cmi_039,		///< @line		Random,											Random
	cmi_040,		///< @line		ClearNextTarget,								Clear the next target
	cmi_041,		///< @line		CheckMpByPercent,								Check MP by percentage
	cmi_042,		///< @line		CheckMpByValue,									Check MP by fixed value
	cmi_043,		///< @line		ReviveTarget,									Revive the target
	cmi_044,		///< @line		TeleportToNearestGraveyard,						Teleport to the nearest graveyard (death and revival)
	cmi_045,		///< @line		CheckAndConsumeMoney,							Check and consume currency
	cmi_046,		///< @line		CheckTargetCount,								Check target count
	cmi_047,		///< @line		LockNearestTargetInSector,						Lock the nearest target in a sector
	cmi_048,		///< @line		LockNearestTarget,								Lock the nearest target
	cmi_049,		///< @line		KnockBack,										Knock back
	cmi_050,		///< @line		ModifierCost,									Modify spell cost
	cmi_051,		///< @line		SummonNpc,										Summon an NPC (pet or totem)
	cmi_052,		///< @line		RotateTargetPt,									Rotate the target angle
	cmi_053,		///< @line		CheckIntervalAndCastSubSpell,					Check the interval and cast a sub-spell (periodic effect)
	cmi_054,		///< @line		RotateSelf,										Rotate self
	cmi_055,		///< @line		CheckMultiAccumulateTime,						Check multiple accumulated times
	cmi_056,		///< @line		CheckHpByPct,									Check HP by percentage
	cmi_057,		///< @line		CheckHpByValue,									Check HP by fixed value
	cmi_058,		///< @line		CheckExFlag,									Check the Ex flag (spell?)
	cmi_059,		///< @line		SetExFlag,										Set the Ex flag (spell?)
	cmi_060,		///< @line		RemoveAura,										Remove an aura
	cmi_061,		///< @line		CastSubSpellByAuraCaster,						Trigger a sub-spell based on the aura caster
	cmi_062,		///< @line		CheckCurrentWeaponType,							Check the current weapon type
	cmi_063,		///< @line		AuraTimeupEffect,								Effect when the status expires (such as an explosion or healing)
	cmi_064,		///< @line		AuraKnockBack,									Apply knockback from a status (such as an aura explosion)
	cmi_065,		///< @line		GenerateDivergentMissile,						Generate a branching projectile (such as a splitting shot)
	cmi_066,		///< @line		GenerateRandomTargetPt,							Generate a random target point (such as area bombardment)
	cmi_067,		///< @line		FindAura,										Find a status effect (check whether it exists)
	cmi_068,		///< @line		SubstituteNextSpell,							Replace the next spell
	cmi_069,		///< @line		AddAuraToCaster,								Apply a status effect to the caster (self-buff)
	cmi_070,		///< @line		ScanTarget,										Scan for targets in range
	cmi_071,		///< @line		Silence,										Silence (prevent spellcasting)
	cmi_072,		///< @line		CheckCurrentAura,								Check the current aura
	cmi_073,		///< @line		GhostStep,										Ghost step (teleport with an afterimage)
	cmi_074,		///< @line		LeapAndMissile,									Leap and missile?
	cmi_075,		///< @line		DispelAuraByID,									Dispel a status by ID
	cmi_076,		///< @line		DispelAuraByType,								Dispel statuses by type (such as all debuffs)
	cmi_077,		///< @line		DispelAuraBySubType,							Dispel an aura by subtype
	cmi_078,		///< @line		BatchDispelAuraByType,							Batch-dispel statuses of the same type
	cmi_079,		///< @line		CheckLockTarget,								Check the locked target
	cmi_080,		///< @line		BreakCast,										Stop triggering
	cmi_081,		///< @line		ChargeToNextTarget,								Charge to the next target
	cmi_082,		///< @line		ModifyParamX,									Modify parameter X (general value adjustment)
	cmi_083,		///< @line		CheckCurrentSpell,								Check the current spell
	cmi_084,		///< @line		Freeze,											Freeze (immobilization and ice damage)
	cmi_085,		///< @line		CheckObjType,									Check object type (player, NPC, trap, etc.)
	cmi_086,		///< @line		SetStance,										Set stance (combat or non-combat)
	cmi_087,		///< @line		DragByAura,										Pull with a status effect (such as black-hole attraction)
	cmi_088,		///< @line		SyncFlagPos,									Synchronize flag position
	cmi_089,		///< @line		Thrown,											Throw (forced movement, such as a grab and throw)
	cmi_090,		///< @line		CheckThrown,									Check throw
	cmi_091,		///< @line		RotateToLockedTarget,							Rotate toward the locked target
	cmi_092,		///< @line		DirectlySummonNpc,								Summon an NPC directly (without delay)
	cmi_093,		///< @line		ResetScanner,									Reset the scanner
	cmi_094,		///< @line		CheckChangedWeaponType,							Check the weapon type after switching
	cmi_095,		///< @line		Suicide,										Suicide (self-destruct spell)
	cmi_096,		///< @line		ModifyCanbeThrown,								Modify whether the target can be thrown
	cmi_097,		///< @line		CheckPass,										Check pass conditions
	cmi_098,		///< @line		LockNearestTargetInRect,						Lock the nearest target in a rectangle
	cmi_099,		///< @line		ScanTargetAndExcludeLocked,						Scan targets excluding the locked target
	cmi_100,		///< @line		NpcCopySelf,									NPCNPC copies itself (mirror image)
	cmi_101,		///< @line		ClientShowTime,									Client display time (such as a countdown UI)
	cmi_102,		///< @line		JumpToAuraCaster,								Leap to the aura caster
	cmi_103,		///< @line		BreakAuraCasterSpell,							Interrupt the aura caster’s spell
	cmi_104,		///< @line		SingleBulletToNextLoopedTarget,					Bullet attacks the next target in a loop (bounce mechanic)
	cmi_105,		///< @line		ChargeCertainDistance,							Charge a fixed distance
	cmi_106,		///< @line		CheckDistanceBetweenCasterAndTarget,			Check distance between caster and target
	cmi_107,		///< @line		GenerateMissileFromCaster,						Generate a projectile from the caster
	cmi_108,		///< @line		ModifyParam1WithTargetDistance,					Modify parameter 1 based on target distance (such as ranged falloff)
	cmi_109,		///< @line		ModifySpellEffectAccordingToAccumulateParam,    Modify spell effects based on accumulated parameters
	cmi_110,		///< @line		ReduceAuraStackCount,							Reduce the status effect stack count
	cmi_111,		///< @line		CastingSpellRegisterEvent,						Register an event when casting a spell (such as a cast-bar callback)
	cmi_112,		///< @line		GenerateBlock,									Generate a block effect
	cmi_113,		///< @line		RefreshSlotCD,									Refresh the spell slot cooldown
	cmi_114,		///< @line		CheckHpInCircle,								Check HP of targets within a circular area
	cmi_115,		///< @line		RemoveTargetAura,								Remove an aura from the target
	cmi_116,		///< @line		CheckWeather,									Check weather (such as rain enhancing lightning spells)
	cmi_117,		///< @line		CheckAuraCasterLive,							Check whether the aura caster is alive
	cmi_118,		///< @line		RemovePendingAura,								Remove a pending status effect
	cmi_119,		///< @line		AddPendingSpellAttr,							Add pending spell attributes
	cmi_120,		///< @line		AddMaxHpAndCurrentHp,							Increase maximum HP and current HP
	cmi_121,		///< @line		CheckIsBoss,									Check whether the target is a boss
	cmi_122,		///< @line		CheckIsDaytime,									Check whether it is daytime
	cmi_123,		///< @line		AddParamX,										Increase ParamX
	cmi_124,		///< @line		AuraLoadTransformSpell,							Load a transformation spell for the status effect
	cmi_125,		///< @line		CastSubSpellToAuraCaster,						Trigger a sub-spell on the status caster
	cmi_126,		///< @line		Seduced,										Charm (target temporarily defects)
	cmi_127,		///< @line		CheckIsMoving,									Check whether moving
	cmi_128,		///< @line		Like 063,										[Effect when the status expires (such as an explosion or healing)]?
	cmi_129,		///< @line		ModifyAuraAttr,									Modify status attributes (such as extending duration)
	cmi_130,		///< @line		ThrownFromCurrentPos,							Throw from the current position
	cmi_131,		///< @line		Leap,											Leap
	cmi_132,		///< @line		LeapToLockedTarget,								Leap to the locked target (such as a pounce)
	cmi_133,		///< @line		SuperMassiveBlackHole,							Supermassive black hole (large-area pull effect)
	cmi_134,		///< @line		ShareDamageWithAuraCaster,						Share damage with the status caster (life link)
	cmi_135,		///< @line		TriggerEventRootSpellCD,						Trigger the associated spell cooldown event
	cmi_136,		///< @line		IgnoreDynamicBlock,								Ignore dynamic obstacles (wall-crossing spell)
	cmi_AllNpcSpecies,	///< @line	AllNpcSpeciesDamage,							Deal specific damage to an NPC species (species advantage)
	cmi_138,		///< @line		SetSpellFlag,									Set spell flags (such as “cannot be interrupted”)
	cmi_139,		///< @line		RemoveAllDebuff,								Remove all negative statuses (cleanse)
	cmi_140,		///< @line		ChangeWeather,									Change weather (spell-triggered environmental change)
	cmi_141,		///< @line		SubstituteMainSpellID,							Replace the main spell ID
	cmi_142,		///< @line		CheckSlotSpellID,								Check the spell ID in the spell slot
	cmi_143,		///< @line		,
	cmi_144,		///< @line		,
	cmi_145,		///< @line		,
	cmi_146,		///< @line		,
	cmi_147,		///< @line		,
	cmi_148,		///< @line		,
	cmi_149,		///< @line		,
	cmi_150,		///< @line		,
	cmi_151,		///< @line		,
	cmi_152,		///< @line		,
	cmi_153,		///< @line		,
	cmi_154,		///< @line		,
	cmi_155,		///< @line		,
	cmi_156,		///< @line		,
	cmi_157,		///< @line		,
	cmi_158,		///< @line		,
	cmi_159,		///< @line		,
	cmi_160,		///< @line		,
	cmi_161,		///< @line		,
	cmi_162,		///< @line		,
	cmi_163,		///< @line		,
	cmi_164,		///< @line		,
	cmi_165,		///< @line		,
	cmi_166,		///< @line		,
	cmi_167,		///< @line		,
	cmi_168,		///< @line		,
	cmi_169,		///< @line		,
	cmi_170,		///< @line		,
	cmi_171,		///< @line		,
	cmi_172,		///< @line		,
	cmi_173,		///< @line		,
	cmi_174,		///< @line		,
	cmi_175,		///< @line		,
	cmi_176,		///< @line		,
	cmi_177,		///< @line		,
	cmi_178,		///< @line		,
	cmi_179,		///< @line		,
	cmi_180,		///< @line		,
	cmi_181,		///< @line		,
	cmi_182,		///< @line		,
	cmi_183,		///< @line		,
	cmi_184,		///< @line		,
	cmi_185,		///< @line		,
	cmi_186,		///< @line		,
	cmi_187,		///< @line		,
	cmi_188,		///< @line		,
	cmi_189,		///< @line		,
	cmi_190,		///< @line		,
	cmi_191,		///< @line		,
	cmi_192,		///< @line		,
	cmi_193,		///< @line		,
	cmi_194,		///< @line		,
	cmi_195,		///< @line		,
	cmi_196,		///< @line		,
	cmi_197,		///< @line		,
	cmi_198,		///< @line		,
	cmi_199,		///< @line		,
	cmi_200,		///< @line		,
	cmi_201,		///< @line		,
	cmi_202,		///< @line		,
	cmi_203,		///< @line		,
	cmi_204,		///< @line		,
	cmi_205,		///< @line		,
	cmi_206,		///< @line		,
	cmi_207,		///< @line		,
	cmi_208,		///< @line		,
	cmi_209,		///< @line		,
	cmi_210,		///< @line		Protective / paralysis / overload / resurrection / invisibility / Hongmo ring; necklace; bracelet; ruby ring; Sibeier bracelet; dragon bracelet; Xiaoyao fan; dragon ring; soul bracelet; demon bell; platinum ring; knight bracelet
	cmi_211,		///< @line		Rally order
	cmi_212,		///< @line		Detection necklace
	cmi_213,		///< @line		Teleport ring
	cmi_214,		///< @line		,
	cmi_215,		///< @line		,
	cmi_216,		///< @line		,
	cmi_217,		///< @line		,
	cmi_218,		///< @line		,
	cmi_219,		///< @line		,
	cmi_220,		///< @line		,
	cmi_221,		///< @line		,
	cmi_222,		///< @line		,
	cmi_223,		///< @line		Magic blood ring / necklace / bracelet / magic blood conversion
	cmi_224,		///< @line		,
	cmi_225,		///< @line		,
	cmi_226,		///< @line		,
	cmi_227,		///< @line		,
	cmi_228,		///< @line		,
	cmi_229,		///< @line		,
	cmi_230,		///< @line		,
	cmi_231,		///< @line		,
	cmi_232,		///< @line		,
	cmi_233,		///< @line		,
	cmi_234,		///< @line		,
	cmi_235,		///< @line		,
	cmi_236,		///< @line		,
	cmi_237,		///< @line		,
	cmi_238,		///< @line		,
	cmi_239,		///< @line		,
	cmi_240,		///< @line		,
	cmi_241,		///< @line		,
	cmi_242,		///< @line		,
	cmi_243,		///< @line		,
	cmi_244,		///< @line		,
	cmi_245,		///< @line		,
	cmi_246,		///< @line		,
	cmi_247,		///< @line		,
	cmi_248,		///< @line		,
	cmi_249,		///< @line		,
	cmi_250,		///< @line		,
	cmi_251,		///< @line		,
	cmi_252,		///< @line		,
	cmi_253,		///< @line		,
	cmi_254,		///< @line		,
	cmi_255,		///< @line		,
	cmi_256,		///< @line		,
	cmi_257,		///< @line		,
	cmi_258,		///< @line		,
	cmi_259,		///< @line		,
	cmi_260,		///< @line		,
	cmi_261,		///< @line		,
	cmi_262,		///< @line		,
	cmi_263,		///< @line		,

	cmiCount
};

#endif // _modifier_def_h__

