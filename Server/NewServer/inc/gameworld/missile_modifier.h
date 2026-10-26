#ifndef _MISSILE_MODIFIER_H_
#define _MISSILE_MODIFIER_H_


enum MISSILE_MODIFIER_INDEX
{
	mmiInvalid = 0,

	mmi_001,	//	mmi_CastSubSpellToCurPos,
	mmi_002,	//	mmi_BulletToEachTarget,
	mmi_003,	//	mmi_JustAddCollisionCount,
	mmi_004,	//	mmi_RotateTo,
	mmi_005,	//	mmi_CoverParam1WithTargetPt,
	mmi_006,	//	mmi_ReduceMaxCollisionCountIfCollision,
	mmi_007,	//	mmi_LockNearestTargetInSector,
	mmi_008,	//	mmi_LockNearestTargetInCircle,
	mmi_009,	//	mmi_CheckOwnerMovementStateAndDeleteSelf,
	mmi_010,	//	mmi_CheckOwnerExFlag,
	mmi_011,	//	mmi_AddEffectByRemainCollisionCount,
	mmi_012,	//	mmi_DeleteSelf,
	mmi_013,	//	mmi_TurnToCaster,
	mmi_014,	//	mmi_ModifyMissileAttr,
	mmi_015,	//	mmi_RemoveSameMissile,
	mmi_016,	//	mmi_RemoveSameMissile,
	mmi_017,	//	mmi_RemoveSameMissile,
	mmi_018,	//	mmi_RemoveSameMissile,
	mmi_019,	//	mmi_RemoveSameMissile,
	mmi_020,	//	mmi_RemoveSameMissile,
	mmi_021,	//	mmi_RemoveSameMissile,
	mmi_022,	//	mmi_RemoveSameMissile,

	mmiCount
};

#endif // _missile_modifier_h__
