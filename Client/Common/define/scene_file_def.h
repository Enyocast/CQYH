#ifndef _SCENE_SPAWN_DEF_H_
#define _SCENE_SPAWN_DEF_H_

#include "scene_def.h"
#include "string_def.h"

#define SCENE_FILE_EXT_NAME     "scn"
#define SCENE_FILE_TAG          'scen'
#define SCENE_FILE_VERSION      (12)

#define PATROL_TAG "#P"
#define PATROL_SEPERATOR "."

#define MAX_POINT_COUNT_PER_PATH 256
#define MAX_PATROL_PATH_ID 64

#ifdef WIN32
#pragma warning(disable:4200)
#endif  //WIN32

#pragma pack(push, 4)
struct SCENE_FILE_BLOCK_HEADER
{
    INT32    eBlockType;
    INT32    nBlockSize;
    INT32    nBlockOffset;   // global offset
};

struct SCENE_FILE_HEADER
{
    UINT32                  dwTag;
    UINT32                  dwVersion;
    INT32                   nBlockCount;
    SCENE_FILE_BLOCK_HEADER BlockTable[0];
};

enum SCENE_BLOCK_TYPE
{
    sbtInvalid = 0,

    sbtNpcSingleSpawn,
    sbtNpcSpawnData,
    sbtDoodadSpawnData,
    sbtServerPoint,

    sbtTotal
};

/************************************************************************/
// sbtNpcSingleSpawn
struct NPC_SINGLE_SPAWN
{
    INT32           nNpcTemplateID;
    INT32           nID;
    UINT64			qwNameID;
    INT32           nX;
    INT32           nY;
    INT32           nZ;
    UINT16			wRange;
    UINT16          wDirection;
    UINT8           byQuality;			// 0 : default value
    INT32           nSpawnTime;			// 0 : default value
    INT32           nReviveTime;		// 0 : default value
    INT32           nAIID;				// 0 : default value
    INT32           nCurrentHp;			// 0 : default value
    INT32           nCurrentMp;			// 0 : default value
    BOOL            bCanDropItem;		// default : true
    BOOL	        IsAutoSpawn;
    BOOL	        IsAutoReSpawn;
    INT32           nMinRespawnTime;	// 0 : default value
    INT32           nMaxRespawnTime;	// 0 : default value
    INT32           nLevelOffset;
    INT32           nPatrolPathID;
    INT32           nPatrolStyle;
    INT32           nFollowHostID;
    INT32			nFollowOffsetX;
    INT32			nFollowOffsetY;
    INT32           nReserved[4];
    char            szDeadScript[MAX_EMBEDDED_SCRIPT_LEN];
};

struct NPC_SINGLE_SPAWN_HEADER
{
    INT32               nNpcCount;
    NPC_SINGLE_SPAWN    NpcTable[0];
};

/************************************************************************/
// sbtNpcSpawnData
struct NPC_SPAWN_POINT_DATA
{
    INT32           nX;
    INT32           nY;
    INT32           nZ;
    UINT16			wRange;
    UINT16          wDirection;
    UINT8           byQuality;      // 0 : default value
    INT32           nSpawnTime;		// 0 : default value
    INT32           nReviveTime;    // 0 : default value
    INT32           nAIID;          // 0 : default value
    INT32           nCurrentHp;     // 0 : default value
    INT32           nCurrentMp;     // 0 : default value
    BOOL            bCanDropItem;   // default : true
    INT32           nPatrolPathID;
    INT32           nPatrolStyle;
    INT32           nFollowHostID;
    INT32			nFollowOffsetX;
    INT32			nFollowOffsetY;
    INT32           nReserved[4];
    struct NPC_TEMPLATE_LIST
    {
        INT32   nTemplateID;
        INT32   nWeight;
    } NpcList[MAX_NPC_TEMPLATE_COUNT];
};

struct NPC_SPAWN_SMALL_GROUP
{
    INT32                   nWeight;
    INT32                   nPointCount;
    BOOL					bDynamicRespawnTime;
    NPC_SPAWN_POINT_DATA    PointList[0];
};

struct NPC_SPAWN_MEDIUM_GROUP
{
    INT32           		nID;
    BOOL                    bAutoSpawn;
    BOOL                    bAutoRespawn;
    INT32                   nMinRespawnTime;   // 0 : default value
    INT32                   nMaxRespawnTime;   // 0 : default value
    INT32                   nLevelOffset;
    char                    szDeadScript[MAX_EMBEDDED_SCRIPT_LEN];
    INT32                   nTotalWeight;
    INT32                   nSmallGroupCount;
    // NPC_SPAWN_SMALL_GROUP
};

struct NPC_SPAWN_LARGE_GROUP
{
    INT32           		nID;
    INT32                   nEliteMin;
    INT32                   nEliteMax;
    INT32					nEliteInterval;
    INT32                   nChampionMin;
    INT32                   nChampionMax;
    INT32					nChampionInterval;
    INT32					nMaxDieCount;
    char                    szDeadScript[MAX_EMBEDDED_SCRIPT_LEN];
    INT32                   nMediumGroupCount;
    // NPC_SPAWN_MEDIUM_GROUP
};

struct NPC_SPAWN_DATA_HEADER
{
    INT32                   nLargeGroupCount;
    // NPC_SPAWN_LARGE_GROUP
};

/************************************************************************/
// sbtDoodadSpawnData
struct DOODAD_SPAWN_POINT_DATA
{
    INT32           nX;
    INT32           nY;
    INT32           nZ;
    UINT16          shDirection;
};

struct DOODAD_SPAWN_GROUP_DATA
{
    INT32	                nGroupID;
    INT32	                nMaxConcurrentPoint;
    BOOL	                IsAutoSpawn;
    BOOL	                IsAutoReSpawn;
    INT32                   nRespawnInterval;       // unit: ms
    struct
    {
        INT32   nTemplateID;
        INT32   nWeight;
    }                       DoodadList[MAX_DOODAD_COUNT_PER_GROUP];
    INT32                   nPointCount;
    DOODAD_SPAWN_POINT_DATA PointList[0];
};

struct DOODAD_SPAWN_DATA_HEADER
{
    INT32                   nGroupCount;
};

/************************************************************************/
// sbtServerPoint

// tolua_begin
enum SERVER_POINT_TYPE
{
    sptInvalid,

    sptCustom,
    sptRevive,
    sptReplay,

    sptTotal
};
// tolua_end

struct SERVER_POINT
{
    UINT64  qwNameID;
    INT32   nID;
    INT32   nX;
    INT32   nY;
    INT32   nZ;
    INT32	nDirection;
    INT32	nRange;
};

struct SERVER_POINT_OLD
{
    UINT64  qwNameID;
    INT32   nID;
    INT32   nX;
    INT32   nY;
    INT32   nZ;
};

struct SERVER_POINT_HEADER
{
    INT32					nPointCount;
    SERVER_POINT			PointTable[0];
};

struct SERVER_POINT_HEADER_OLD
{
    INT32					nPointCount;
    SERVER_POINT_OLD		PointTable[0];
};


/************************************************************************/

#pragma pack(pop)
#endif  // _SCENE_SPAWN_DEF_H_
