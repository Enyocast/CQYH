#ifndef _ZONE_DEF_H_
#define _ZONE_DEF_H_

#include "grid_def.h"
#include "scene_def.h"

#if defined(WIN32) | defined(WIN64)
#pragma warning(disable:4200)
#endif  // WIN32

#pragma pack(push, 1)

struct ZONE_DATA
{
    unsigned short  usZoneX;    // Zone X coordinate
    unsigned short  usZoneY;    // Zone Y coordinate

    unsigned short  GroundGrid[GRID_PER_ZONE][GRID_PER_ZONE];  // Ground grid index table
    int             nGridCount;  // Total grid count
	
    unsigned char   byVolume[MAX_VOLUME_PER_ZONE];     // Volume region flags
    unsigned char   byDoor[MAX_DOOR_PER_ZONE];         // Door state
	unsigned short	wEdge[MAX_EDGE_INDEX_PER_ZONE];    // Edge indices
    int             nQuestID[MAX_QUEST_PER_ZONE];      // Associated quest IDs
	unsigned char	byServerPointIndex;                // Server point index
    
	GRID_DATA		GridList[0];  // Variable-length grid data array
};

// Zone instance data
struct ZONE_INSTANCE_DATA
{
	GRID_INSTANCE_DATA	GridList[0];
};

#pragma pack(pop)

#endif  // _ZONE_DEF_H_