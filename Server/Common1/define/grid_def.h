#ifndef _GRID_DEF_H_
#define _GRID_DEF_H_

// tolua_begin

#define GRID_LAYER_HEIGHT_BIT   (12)
#define NEXT_GRID_BIT           (7)
#define MAX_NEXT_GRID			(1 << NEXT_GRID_BIT)
#define GRID_VOLUME_BIT			(2)
#define GRID_DOOR_BIT			(2)
#define EDGE_INDEX_BIT			(4)
#define MAX_DOOR_PER_ZONE       (1 << GRID_DOOR_BIT)
#define MAX_VOLUME_PER_ZONE		(1 << GRID_VOLUME_BIT)
#define MAX_EDGE_INDEX_PER_ZONE	(1 << EDGE_INDEX_BIT)
#define MAX_CHAR_PER_GRID		(15)
#define MAX_DROP_PER_GRID       (3)
#define MAX_QUEST_PER_ZONE		(4)

enum GRID_PK_TYPE
{
    gptInvalid = -1,

	gptNormal,
	gptFree,
	gptSafe,

    gptTotal
};

#pragma pack(push, 1)

struct GRID_DATA
{
	unsigned uNextGrid				: NEXT_GRID_BIT;
	unsigned uNoObstacle			: 6;
	unsigned uVolume				: GRID_VOLUME_BIT;
	unsigned uDoor					: GRID_DOOR_BIT;
	unsigned uPkType				: 2;
	unsigned bBorder				: 1;
	unsigned uStallLevel			: 2;
	unsigned bQuest					: 1;
	unsigned bBlockMove				: 1;
	unsigned bBlockLeap				: 1;
	unsigned bBlockMissile			: 1;
	unsigned bBlockBullet			: 1;
	unsigned bNotBlockChar			: 1;
	unsigned bMine					: 1;
	unsigned bCannotTeleport		: 1;
	unsigned bRoleCannotLoseItem	: 1;
	unsigned bRoleCannotDropItem	: 1;
	unsigned bSlayerArea			: 1;
	unsigned bCannotDropItem		: 1;
	unsigned uReserved1				: 30;
	unsigned uReserved2				: 32;

	unsigned uLowLayer				: GRID_LAYER_HEIGHT_BIT;
	unsigned uHighLayer				: GRID_LAYER_HEIGHT_BIT;
	unsigned uEdge					: EDGE_INDEX_BIT;
	unsigned bOutOfPoly				: 1;
	unsigned bInServerPointRange	: 1;
	unsigned uReserved3				: 2;
};

struct GRID_INSTANCE_DATA
{
	unsigned char uCharRef			: 4;
	unsigned char uDropRef			: 2;
	unsigned char uMissileTag1		: 1;
	unsigned char uMissileTag2		: 1;
	unsigned short uReserved		: 8;
};

#pragma pack(pop)

// tolua_end

#endif  // _GRID_DEF_H_