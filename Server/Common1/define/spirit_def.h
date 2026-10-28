#ifndef _SPIRIT_DEF_H_
#define _SPIRIT_DEF_H_    

// Spirit level overview
#define  SPIRIT_OPEN_LEVEL					1	// (Level at which spirit progression unlocks)

#define  MAX_EXT2PTS_MULTIPLE				20	// Maximum gold cost multiplier for one-click soul-to-cultivation conversion (depends on the number of conversions)
#define  MAX_EXP2PTS_THRESHOLD				50	// Daily completion limit for one-click soul-to-cultivation conversion
#define  MAX_SPIRIT_LEVEL					70	// Maximum spirit level

#define  MAX_SPIRIT_NODE_PER_LEVEL			2	// Nodes assignable at each spirit level

// Air sea
#define  MAX_AIRSEA_BAG_CONTAINER_SIZE		32	// Air sea bag size
#define	 MAX_AIRSEA_STALL_CONTAINER_SIZE	16  // Air sea storage size
#define  MAX_AIRSEA_EQUIP_CONTAINER_SIZE	9	// Air sea equipment slot count

#define  MAX_AIR_PROCEDURE					5	// Qi cultivation stages
#define	 MAX_DROP_AIR_COUNT					40	// Configurable drop count during cultivation

#define  MAX_AIR_LEVEL						10	// Maximum qi level
#define  MAX_AIR_NODE						256	// Maximum node count
#define	 MAX_ATTR_PER_NODE					2	// Maximum attributes per node

#define  MAX_SPIRIT_BUY_SLOT_COST			100	// Cost of buying bag slots
#define  INVALID_AIR_ID						0	// Invalid qi ID
#define  INVALID_AIR_INDEX					(-1)// Invalid qi index

#define  MAX_EXP2PTS_LEVEL					32	// Level brackets for configured soul-to-cultivation conversion counts

// Blood sea
#define  MAX_BLOODSEA_PAGE					4	// Bloodline
#define  MAX_BLOODSEA_SLOT_PER_PAGE			10	// Slots per bloodline
#define  MAX_BLOODSEA_SLOT_NUMBER			10	// Maximum value for each bloodline slot
#define	 MAX_BLOODSEA_ATTR_PER_SLOT			2	// Maximum attributes per bloodline slot
#define  BLOODSEA_SLOT_INIT_SLOT			0	// Initial position for each bloodline slot

enum SPIRIT_AIR_SEA_BAG_TYPE
{
	sasbtInvalid = -1,
	sasbtBag,
	sasbtStall,
	sasbtEquip,

	sasbtTotal,
};

enum SPIRIT_AIR_TYPE
{
	spiritInvalid = -1,
	spiritPower,	// Strength
	spiritSwift,	// Swiftness
	spiritWise,		// Wisdom
	spiritBody,		// Toughness
	spiritDivine,	// Divinity
	spiritKing,		// Arcane
};

inline INT32 MAKE_AIR_LEVEL_KEY(INT32 nLevel, INT32 nClass)
{
	return ((nLevel << 16) | nClass);
}

inline INT32 MAKE_BLOOD_KEY(INT32 nPage, INT32 nIndex, INT32 nNumber)
{
	return ((nPage << 24) | (nIndex << 16) | nNumber);
}

static const INT8 INIT_SPIRIIT_AIR_SEA_BAG_SIZE[sasbtTotal] = {16, 8, 2};

#endif  //_SPIRITLEVEL_DEF_H_