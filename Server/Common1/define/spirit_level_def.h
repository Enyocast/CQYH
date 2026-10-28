#ifndef _SPIRITLEVEL_DEF_H_
#define _SPIRITLEVEL_DEF_H_    

// Spirit level overview
#define  MAX_EXT2PTS_MULTIPLE				20	// Maximum gold cost multiplier for one-click soul-to-cultivation conversion (depends on the number of conversions)
#define  MAX_EXP2PTS_THRESHOLD				50	// Daily completion limit for one-click soul-to-cultivation conversion

// Air sea
#define  MAX_AIRSEA_CONTAINER_SIZE			24	// Air sea bag size 1
#define  ORIGINAL_AIRSEA_CONTAINER_SIZE		12	// Initial air sea bag size
#define  MAX_SPIRIT_LEVEL					18	// Maximum spirit level

#define  MAX_AIR_PROCEDURE					5	// Qi cultivation stages

#define  MAX_AIR_LEVEL						9	// Maximum qi level
#define  MAX_AIR_NODE						256	// Maximum node count
#define	 MAX_ATTR_PER_NODE					2	// Maximum attributes per node

// Blood sea
#define  MAX_DAN_PER_LEVEL					1024 // Maximum pills consumable per pill level
#define	 MAX_DAN_TYPE						5	 // Number of pill types
#define  MAX_DAN_LEVEL_PER_TYPE				7	 // Pill levels per type

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

#endif  //_SPIRITLEVEL_DEF_H_