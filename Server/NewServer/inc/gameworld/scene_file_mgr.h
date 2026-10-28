#ifndef _SCENE_FILE_MGR_H_
#define _SCENE_FILE_MGR_H_

#include "scene_file_def.h"
#include "string_def.h"
#include "scene_data.h"
#include "grid_def.h"
#include "nav_def.h"
#include "teleport_def.h"
#include "weight_rand.h"
#include "bt_event.h"

class CWeightRand;
class CScene;
struct KIS_TEMPLATE;
struct KIS_INSTANCE;
struct GRID_DATA;
struct ZONE_DATA;
class CLuaScript;

struct BTNod;

// 额外添加刷新怪物
struct ADD_NPC_SPAWN_POINT
{
    INT32                   nID;
    INT32                   nTemplateID;
    INT32                   nX;
    INT32                   nY;
    INT32                   nZ;
    INT32                   nDirection;
    INT32					nRange;

    INT32                   nLevelOffset;
    INT32                   nQuality;			// 0 : default value

    INT32                   nMinRespawnTime;	// 0 : default value
    INT32                   nMaxRespawnTime;	// 0 : default value

    INT32                   nCurrentHp;			// 0 : default value
    INT32                   nCurrentMp;			// 0 : default value
    BOOL                    bCanDropItem;		// default : true

    BOOL                    bAutoSpawn;
    BOOL                    bAutoRespawn;

    INT32                   nSmallGroupID;
    INT32                   nMediumGroupID;
    INT32                   nLargeGroupID;
    //BTNod* pDeadBTRoot;
};

struct NPC_SPAWN_POINT
{
    INT32                   nID;
    NAMEID                  qwNameID;
    INT32                   nX;
    INT32                   nY;
    INT32                   nZ;
    INT32                   nDirection;
	INT32					nRange;

    CWeightRand             RandNpc;
    INT32                   nLevelOffset;
    INT32                   nAIID;				// 0 : default value
    INT32                   nQuality;			// 0 : default value

    INT32                   nMinRespawnTime;	// 0 : default value
	INT32                   nMaxRespawnTime;	// 0 : default value
	INT32                   nSpawnTime;			// 0 : default value
    INT32                   nReviveTime;		// 0 : default value

    INT32                   nCurrentHp;			// 0 : default value
    INT32                   nCurrentMp;			// 0 : default value
    BOOL                    bCanDropItem;		// default : true

    INT32                   nPatrolPathID;
    INT32                   nPatrolStyle;

    INT32                   nFollowHostID;
    INT32			        nFollowOffsetX;
    INT32			        nFollowOffsetY;

    BOOL                    bAutoSpawn;
    BOOL                    bAutoRespawn;

    INT32                   nSmallGroupID;
    INT32                   nMediumGroupID;
    INT32                   nLargeGroupID;
    BTNod*                  pDeadBTRoot;
};

struct NPC_SMALL_SPAWN_GROUP
{
    INT32                   nPointCount;
	BOOL					bDynamicRespawnTime;
    NPC_SPAWN_POINT         PointList[0];
};

struct NPC_MEDIUM_SPAWN_GROUP
{
    INT32                   nID;
    BOOL                    bAutoSpawn;
    char                    szDeadScript[MAX_EMBEDDED_SCRIPT_LEN];
    BTNod*                  pDeadBTRoot;
    INT32                   nSmallGroupCount;
    NPC_SMALL_SPAWN_GROUP*  SmallGroupList[MAX_NPC_SMALL_GROUP_PER_MEDIUM_GROUP];
    CWeightRand             RandSmallGroup;
};

struct NPC_LARGE_SPAWN_GROUP
{
    INT32                   nID;
    INT32                   nEliteMin;
    INT32                   nEliteMax;
    INT32                   nEliteInterval;
    INT32                   nMaxDieCount;
    BTNod*                  pDeadBTRoot;
    INT32                   nMediumGroupCount;
    INT32                   MediumGroupList[MAX_NPC_MEDIUM_GROUP_PER_LARGE_GROUP];
};

struct SERVER_PATH
{
    INT32           nPointCount;
    SERVER_POINT    PointList[MAX_POINT_COUNT_PER_PATH];
};

struct DOODAD_SPAWN_POINT
{
    INT32           nID;
    INT32           nX;
    INT32           nY;
    INT32           nZ;
    INT32           nFaceDirection;

    INT32           nGroupID;
};

struct DOODAD_SPAWN_GROUP
{
    INT32	            nGroupID;
    INT32	            nMaxConcurrentPoint;
    BOOL	            IsAutoSpawn;
    BOOL	            IsAutoReSpawn;
    INT32               nRespawnInterval;

    CWeightRand         RandDoodad;

    INT32               nPointCount;
    DOODAD_SPAWN_POINT* pPointList;
};

struct REVIVE_POINT : SERVER_POINT
{
    INT32               nFaction;
};

class CSceneStaticData
{
public:
    CSceneStaticData();
    ~CSceneStaticData();

    BOOL Init(void);
    BOOL UnInit(void);

    // Npc spawn
    INT32 GetNpcLargeGroupCount(void);
    const NPC_LARGE_SPAWN_GROUP* GetNpcLargeGroup(INT32 nGroupID);
    INT32 GetNpcMediumGroupCount(void);
    const NPC_MEDIUM_SPAWN_GROUP* GetNpcMediumGroup(INT32 nGroupID);

    INT32 GetSingleNpcCount(void);
    const NPC_SPAWN_POINT* GetSingleNpc(INT32 nSingleNpcID);
    const NPC_SPAWN_POINT* GetSingleNpc(const char* pcszName);
    const NPC_SPAWN_POINT* GetSingleNpcByName(NAMEID qwNameID);

    // doodad spawn
    INT32 GetDoodadSpawnGroupCount(void);
    const DOODAD_SPAWN_GROUP* GetDoodadSpawnGroup(INT32 nGroupID);

    // server point
    UINT32 GetServerPointCount(void);
    const SERVER_POINT* GetServerPoint(INT32 nPointID);
    const SERVER_POINT* GetServerPoint(const char* pcszName);

    UINT32 GetRevivePointCount(void);
    const SERVER_POINT* GetRevivePoint(INT32 nIndex);
    const SERVER_POINT* GetNearestRevivePoint(INT32 nFaction, INT64 llX, INT64 llY, INT64 llZ);

    INT32 GetPathPointCount(INT32 nPathID);
    const SERVER_POINT* GetPathPoint(INT32 nPathID, INT32 nPointIndex);

    const SCENE_TELEPORTS* FindTeleportPoint(INT32 nPointID);

    // volume script
    INT32 GetMaxVolumeTriggerCount(INT32 nVolumeID);
    inline CLuaScript* GetScript(void) {return m_pScript;}
    inline BTNod*      GetVolumeTree( INT32 nVolumeID )
    { 
        LOG_PROCESS_ERROR(nVolumeID >= 0 && nVolumeID < MAX_VOLUME_COUNT);
        return m_VolumeTreeTable[nVolumeID];
Exit0:
        return NULL; 
    }

    inline BTNod* GetBT(INT32 nEventType);

    // grid & zone
    BOOL GetLowerGrid(INT64 llX, INT64 llY, INT64 llZ, const ZONE_DATA*& rpcZoneData, const GRID_DATA*& rpcGridData);
	const GRID_DATA* GetGroundGrid(INT64 llX, INT64 llY);
	const GRID_DATA* GetNextGrid(INT64 llX, INT64 llY, const GRID_DATA* pcGrid);
    INT32 GetLowerZ(INT64 llX, INT64 llY, INT64 llZ);
	BOOL CheckGrid(INT64 llX, INT64 llY, INT64 llZ);
    INT32 GetNearestAvailablePos(INT32 nCenterX, INT32 nCenterY, INT32 nCenterZ, 
        INT32 nMaxRange, INT32 nPosCount, INT32 nPos[][3]);

    inline INT32 GetMaxZoneX(void) {return m_nMaxZoneX;}
    inline INT32 GetMaxZoneY(void) {return m_nMaxZoneY;}
	inline INT32 GetInstanceZoneTotalSize(void) {return m_nInstanceZoneTotalSize;}
	inline UINT32* GetValidRegionList(void) { return m_pdwValidRegionList; }

	inline const ZONE_DATA* GetZoneData(INT32 nZoneX, INT32 nZoneY)
	{
		LOG_PROCESS_ERROR(nZoneX >= 0 && nZoneX < MAX_ZONE_PER_SCENE && 
			nZoneY >= 0 && nZoneY < MAX_ZONE_PER_SCENE);
		return m_ZoneData[nZoneX][nZoneY];
Exit0:
		return NULL;
	}

	BOOL FindPath(INT32 nSrcX, INT32 nSrcY, INT32 nSrcZ, UINT16 wSrcEdge, 
		INT32 nDestX, INT32 nDestY, INT32 nDestZ, UINT16 wDestEdge, 
		INT32& rnResultSize, INT32* pnResult);

private:
    void _ClearNpcSpawnData(void);
    void _ClearDoodadSpawnData(void);
	void _CheckSpawnPos(void);

private:
    friend class CSceneFileMgr;

	const SCENE_DATA*			m_pcSceneData;

    // npc
    INT32                       m_nNpcLargeGroupCount;
    NPC_LARGE_SPAWN_GROUP*      m_pNpcLargeGroupTable;
    INT32                       m_nNpcMediumGroupCount;
    NPC_MEDIUM_SPAWN_GROUP*     m_pNpcMediumGroupTable;

    INT32                       m_nSingleNpcCount;
    NPC_SPAWN_POINT*            m_pSingleNpcTable;

    typedef std::map<UINT64, NPC_SPAWN_POINT*> MAP_NAME_2_NPC;
    MAP_NAME_2_NPC              m_mapSingleNpc;

    //doodad
    INT32                       m_nDoodadSpawnGroupCount;
    DOODAD_SPAWN_GROUP*         m_pDoodadSpawnGroupTable;

    // server point
    INT32						m_nServerPointCount;
    SERVER_POINT*               m_pServerPointTable;

    INT32						m_nRevivePointCount;
    REVIVE_POINT*               m_pRevivePointTable;

    SERVER_PATH                 m_PathPointTable[MAX_PATROL_PATH_ID];

    typedef std::map<UINT64, SERVER_POINT*> MAP_NAME_2_POINT;
    MAP_NAME_2_POINT            m_mapServerPoint;

    SCENE_TELEPORTS             m_TeleportPointList[MAX_TELEPORT_POINT_PER_SCENE];

    // grid & zone
    ZONE_DATA*                  m_ZoneData[MAX_ZONE_PER_SCENE][MAX_ZONE_PER_SCENE];
    char*                       m_pZoneRawData;
    INT32                       m_nMaxZoneX;
    INT32                       m_nMaxZoneY;
	UINT32*						m_pdwValidRegionList;
	INT32						m_nInstanceZoneTotalSize;
    BTNod*                      m_VolumeTreeTable[MAX_VOLUME_COUNT];
    INT32                       m_nMaxVolumeTriggerCount[MAX_VOLUME_COUNT];
    BTNod*                      m_pBTTable[evtTotal];

	INT32						m_nNavVertexCount;
	NAV_VERTEX_DATA*			m_NavVertexData;
    NAV_VERTEX_DATA*            m_NavFixedVertexData;
	INT32						m_nNavEdgeCount;
	NAV_EDGE_DATA*				m_NavEdgeData;

    CLuaScript*                 m_pScript;

    UINT32                      m_dwMemorySize;
    UINT32                      m_dwSceneArea;
    UINT32                      m_dwSceneWalkableArea;
	UINT32						m_dwValidRegion;
};

struct NPC_POSITION
{
    INT32 nSceneTemplateID;
    INT32 nX, nY, nZ;
};

class CSceneFileMgr
{
public:
    CSceneFileMgr();
    ~CSceneFileMgr();

    BOOL Init(void);
    BOOL UnInit(void);
    static CSceneFileMgr& GetInstance(void);

    CSceneStaticData* GetStaticData(UINT32 dwSceneTempID);
	const TELEPORT_PLATFORM* GetTeleportPlatform(UINT32 dwTeleportPlatformID);

    const NPC_POSITION* GetNpcPosition(INT32 nTemplateID) const;

    // 额外添加刷新怪物
    void Init_AdditionalProcessNpcs();

private:
    static CSceneFileMgr    ms_Instance;

    struct CTraverseSceneData
    {
        CSceneFileMgr*  pThis;
        BOOL operator()(const SCENE_DATA* pSceneData);
    };

    BOOL _LoadNpcSpawnData(const SCENE_DATA* pSceneData, CSceneStaticData* pSceneStaticData, char* pData, INT32 nSize);
    BOOL _LoadSingleNpc(const SCENE_DATA* pSceneData, CSceneStaticData* pSceneStaticData, char* pData, INT32 nSize);
    BOOL _LoadDoodadSpawnData(const SCENE_DATA* pSceneData, CSceneStaticData* pSceneStaticData, char* pData, INT32 nSize);
    BOOL _LoadServerPoint(const SCENE_DATA* pSceneData, CSceneStaticData* pSceneStaticData, char* pData, INT32 nSize);
    BOOL _LoadPhyxData(const SCENE_DATA* pSceneData, CSceneStaticData* pSceneStaticData, char* pData, INT32 nSize);
	BOOL _LoadNavData(const SCENE_DATA* pSceneData, CSceneStaticData* pSceneStaticData, char* pData, INT32 nSize);

    BOOL _LoadTeleport(void);
	BOOL _LoadTeleportPlatforms(void);

    typedef std::map<INT32, CSceneStaticData*> MAP_ID_2_DATA;
    MAP_ID_2_DATA           m_mapScene;
    UINT32                  m_dwMemorySize;
    INT32			        m_nLoadedCount;
    INT32                   m_nErrorCount;

	TELEPORT_PLATFORM			m_lstTeleportPlatforms[MAX_TELEPORT_PLATFORM_COUNT];

    typedef std::map<INT32, NPC_POSITION> NPC_POS_MAP;
    NPC_POS_MAP m_NpcPosMap;

    // key = 地图ID, value = 额外添加刷新怪物
    std::map<INT32, std::vector<ADD_NPC_SPAWN_POINT>> m_vecAddSpawnNpcs;
    std::map<INT32, std::set<INT32>> m_mapBlockNpc;
};

inline BTNod* CSceneStaticData::GetBT(INT32 nEventType)
{
    LOG_PROCESS_ERROR(nEventType >= evtSceneBegin && nEventType < evtSceneEnd);
    return m_pBTTable[nEventType];
Exit0:
    return NULL;
}

#endif  // _SCENE_FILE_MGR_H_