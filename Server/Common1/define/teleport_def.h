#ifndef _TELEPORT_DEF_H_
#define _TELEPORT_DEF_H_

#define TELEPORT_FILE_NAME  "teleports.bin"
#define TELEPORT_PLATFORM_FILE_NAME	"teleport_platforms.bin"

// tolua_begin
#define MAX_TELEPORT_POINT_PER_SCENE    128
#define INVALID_TELEPORT_ID             -1

#define MAX_TELEPORT_PLATFORM_COUNT			128

struct SCENE_TELEPORTS
{
    INT32 ID;

    INT32 SrcSceneID;	// 源场景ID
    INT32 SrcRadius;	// 传送点半径范围(POINT)
    INT32 SrcSceneX;	// 传送点在源场景中的位置(POINT)
    INT32 SrcSceneY;
    INT32 SrcSceneZ;

    INT32 TargetSceneID; // 目标场景ID
    INT32 TargetSceneX;	// 目标位置(POINT)
    INT32 TargetSceneY;
    INT32 TargetSceneZ;
	INT32 TargetRotationYaw;
};

struct TELEPORT_PLATFORM
{
	INT32 ID;
	INT32 nInitEnable;		//初始可用
	INT32 nMoneyType;		//消耗金钱类型
	INT32 nMoney;			//消耗数量

	INT32 nSceneID;			//场景ID
	INT32 nRadius;			//范围
	INT32 nSceneX;			
	INT32 nSceneY;
	INT32 nSceneZ;
	INT32 nRotationYaw;
};
// tolua_end

#endif  // _TELEPORT_DEF_H_