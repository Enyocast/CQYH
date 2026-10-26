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
    unsigned short  usZoneX;
    unsigned short  usZoneY;

    unsigned short  GroundGrid[GRID_PER_ZONE][GRID_PER_ZONE];
    int             nGridCount;
	
    unsigned char   byVolume[MAX_VOLUME_PER_ZONE];
    unsigned char   byDoor[MAX_DOOR_PER_ZONE];
	unsigned short	wEdge[MAX_EDGE_INDEX_PER_ZONE];
    int             nQuestID[MAX_QUEST_PER_ZONE];
	unsigned char	byServerPointIndex;
    
	GRID_DATA		GridList[0];
};

struct ZONE_INSTANCE_DATA
{
	GRID_INSTANCE_DATA	GridList[0];
};

#pragma pack(pop)

#endif  // _ZONE_DEF_H_