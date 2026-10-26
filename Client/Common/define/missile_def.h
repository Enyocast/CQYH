#ifndef _MISSILE_DEF_H_
#define _MISSILE_DEF_H_

//tolua_begin
enum MISSILE_MOVE_TYPE
{
	mmtInvalid = -1,

	mmtLine,
	mmtAccordingToTerrain,
	mmtStatic,
	mmtLockTarget,

	mmtTotal
};

enum MISSILE_COLLISION_GROUP
{
	mcgRole			= 0x00000001,
	mcgNpc			= 0x00000002,
	mcgDoodad		= 0x00000004,
};

enum MISSILE_LOCK_TYPE
{
	mltInvalid = -1,

	mltSelf,
	mltObject,
	mltPos,

	mltTotal
};

//tolua_end

#endif // _missile_def_h__
