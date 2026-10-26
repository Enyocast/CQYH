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
    unsigned short  usZoneX;    // 区域X坐标
    unsigned short  usZoneY;    // 区域Y坐标

    unsigned short  GroundGrid[GRID_PER_ZONE][GRID_PER_ZONE];  // 地面网格索引表
    int             nGridCount;  // 网格总数
	
    unsigned char   byVolume[MAX_VOLUME_PER_ZONE];     // 体积区域标记
    unsigned char   byDoor[MAX_DOOR_PER_ZONE];         // 门状态
	unsigned short	wEdge[MAX_EDGE_INDEX_PER_ZONE];    // 边缘索引
    int             nQuestID[MAX_QUEST_PER_ZONE];      // 关联任务ID
	unsigned char	byServerPointIndex;                // 服务器点索引
    
	GRID_DATA		GridList[0];  // 网格数据动态数组
};

// 区域实例数据
struct ZONE_INSTANCE_DATA
{
	GRID_INSTANCE_DATA	GridList[0];
};

#pragma pack(pop)

#endif  // _ZONE_DEF_H_