#ifndef _GRID_DEF_H_
#define _GRID_DEF_H_

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

	gptNormal,  // Normal area (default player-versus-player rules)
	gptFree,    // Free PvP area (unrestricted PvP allowed)
	gptSafe,    // Safe area (PvP prohibited)

    gptTotal
};


// GRID_DATA defines grid rules (whether it is walkable and whether it is a safe area).
// GRID_INSTANCE_DATA tracks live grid changes (current character count and skill effects).

#pragma pack(push, 1)

struct GRID_DATA
{
	// Basic attributes
	unsigned uNextGrid				: NEXT_GRID_BIT;    // Next grid layer index (for multilayer structures)
	unsigned uNoObstacle			: 6;				// Obstacle-free flag (possibly for quick checks)
	unsigned uVolume				: GRID_VOLUME_BIT;  // Volume region index
	unsigned uDoor					: GRID_DOOR_BIT;    // If nonzero, the door state may affect passage

	// Other functions
	unsigned uPkType				: 2;    // Door state (0 = no door)
	unsigned bBorder				: 1;

	// Stall area: grid stall eligibility and level (0 = no stalls; 1/2/3 = stall area levels).
	unsigned uStallLevel			: 2;

	unsigned bQuest					: 1;    // Quest point?

	// Blocking flags
	unsigned bBlockMove				: 1;    // 1 = blocks movement (obstacle)
	unsigned bBlockLeap				: 1;	// 1 = blocks jumping
	unsigned bBlockMissile			: 1;	// 1 = blocks missiles
	unsigned bBlockBullet			: 1;	// 1 = blocks bullets


	unsigned bNotBlockChar			: 1;
	unsigned bMine                  : 1;    // Whether this is a mining point
	unsigned bCannotTeleport		: 1;    // Whether teleporting is prohibited (1 = prohibited, 0 = allowed)
	unsigned bRoleCannotLoseItem	: 1;    // Whether death-related item loss is prohibited here (e.g. a safe area; 1 = prohibited, 0 = allowed)
	unsigned bRoleCannotDropItem	: 1;    // Whether characters are prohibited from discarding items here (1 = prohibited, 0 = allowed)
	// End of first 32 bits

	unsigned bSlayerArea			: 1;    // Red-name area
	unsigned bCannotDropItem		: 1;	// Whether item dropping is prohibited (1 = prohibited, 0 = allowed)
	unsigned uMineLevel				: 2;	// Mining point level?
	unsigned bTeleportPoint			: 1;    // Whether this is a teleport point
	unsigned uReserved1				: 27;	// 27 reserved bits
	// End of second 32 bits

	unsigned uReserved2				: 32;	// 32 reserved bits
	// End of third 32 bits

	// Height
	unsigned uLowLayer				: GRID_LAYER_HEIGHT_BIT;    // Lower layer height
	unsigned uHighLayer				: GRID_LAYER_HEIGHT_BIT;    // Upper layer height
	unsigned uEdge					: EDGE_INDEX_BIT;

	// Logic flags
	unsigned bOutOfPoly				: 1;    // 1 = outside the polygon area (not walkable)
	unsigned bInServerPointRange	: 1;	// Whether within server-point range
	unsigned uReserved3				: 2;	// 2 reserved bits
	// End of fourth 32 bits
};

// Grid instance data
struct GRID_INSTANCE_DATA
{
	unsigned char uCharRef			: 4;    // Number of character references in the current grid
	unsigned char uDropRef			: 2;    // Number of dropped-item references in the current grid
	unsigned char uMissileTag1		: 1;    // Whether a missile/projectile is present in the current grid
	unsigned char uMissileTag2		: 1;
	unsigned short uReserved		: 8;    // 8 reserved bits
};

#pragma pack(pop)

#endif  // _GRID_DEF_H_