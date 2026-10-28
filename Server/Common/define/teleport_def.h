#ifndef _TELEPORT_DEF_H_
#define _TELEPORT_DEF_H_

#define TELEPORT_FILE_NAME  "teleports.bin"
#define TELEPORT_PLATFORM_FILE_NAME	"teleport_platforms.bin"
#define MAX_TELEPORT_POINT_PER_SCENE    128
#define INVALID_TELEPORT_ID             -1

#define MAX_TELEPORT_PLATFORM_COUNT			128

struct SCENE_TELEPORTS
{
    INT32 ID;

    INT32 SrcSceneID;	// Source scene ID
    INT32 SrcRadius;	// Teleport point radius (POINT)
    INT32 SrcSceneX;	// Teleport point position in the source scene (POINT)
    INT32 SrcSceneY;
    INT32 SrcSceneZ;

    INT32 TargetSceneID; // Target scene ID
    INT32 TargetSceneX;	// Target position (POINT)
    INT32 TargetSceneY;
    INT32 TargetSceneZ;
	INT32 TargetRotationYaw;
	INT32 TargetRadius;
};

struct TELEPORT_PLATFORM
{
	INT32 ID;
	INT32 nInitEnable;		//Initially enabled
	INT32 nMoneyType;		//Currency type consumed
	INT32 nMoney;			//Amount consumed

	INT32 nSceneID;			//Scene ID
	INT32 nRadius;			//Radius
	INT32 nSceneX;			
	INT32 nSceneY;
	INT32 nSceneZ;
	INT32 nRotationYaw;
};

#endif  // _TELEPORT_DEF_H_