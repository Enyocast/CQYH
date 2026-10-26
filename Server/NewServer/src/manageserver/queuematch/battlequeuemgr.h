#ifndef _BATTLE_QUENE_MGR_H_
#define _BATTLE_QUENE_MGR_H_

#include "base_list.h"
#include "string_def.h"
#include "scene_def.h"
#include "id_object_pool.h"
#include "object_pool.h"
#include "queue_match_def.h"

struct SCENE_INFO;
struct SCENE_DATA;

struct SBattleTempRole : public BASE_LIST_NODE
{
	UINT32 dwRoleID;
	UINT32 dwSceneTempID;
	UINT32 dwSceneID;
	UINT8  bySide;
	UINT32 dwTimer;
};

struct SBattleQueueInfo : public BASE_LIST_NODE
{	
	UINT32 dwBattleQueueID;					//teamID or roleID
	UINT32 dwStartTime;
	UINT32 dwStopTime;
	UINT32 dwRoleCount;

	UINT32 dwBattleMatch;
	UINT8  bySide;
};

struct SStatisticsDataForBattle
{
	UINT32 dwAverageTime;
	UINT32 dwMaxTime;
	UINT32 dwMinTime;

	UINT32 dwCurQueueRoleCount;
};

struct SBattleScene
{
	UINT32 dwSceneTempID;
	SStatisticsDataForBattle stStatisticsBattleData;
	
	UINT8  bySideCount;
	CBaseList m_lstNewBattleQueue[MAX_SIDE_COUNT];
	UINT8	  m_lstNewBattleQueueRoleCount[MAX_SIDE_COUNT];

	UINT8  byMinRoleCount[MAX_SIDE_COUNT];
	UINT8  byMaxRoleCount[MAX_SIDE_COUNT];
};

class CBattleQueueMgr
{
public:
	CBattleQueueMgr();
	~CBattleQueueMgr();

	BOOL Init(VOID);
	BOOL UnInit(VOID);
	static CBattleQueueMgr& GetInstance(VOID);

	SBattleQueueInfo* FindBattleQueneInfo(UINT32 dwBattleQueneInfoID);
	SBattleQueueInfo* CreateBattleQueneInfo(UINT32 dwBattleQueneInfoID);
	BOOL DestroyBattleQueneInfo(SBattleQueueInfo* stBattleQueneInfo);
	
	BOOL JoinBattle(UINT32 dwID, UINT32 dwRoleCount, UINT32 dwMatch);
	BOOL CancelJoinBattle(UINT32 dwRoleID);

	BOOL StartQueue(SBattleQueueInfo* stBattleQueneInfo);
	BOOL StopQueue(SBattleQueueInfo* stBattleQueneInfo);

	BOOL AddBattleInfo(UINT32 dwSceneTempID, UINT32 byBattleType, UINT8 byMinRole, UINT8 byMaxRole, UINT8 bySide = 1);
	BOOL LeaveBattle(UINT32 dwRoleID, UINT32 dwSceneTempID, UINT32 dwSceneID, BOOL bNormalLeave, UINT8 bySide = 1);
	BOOL CheckBattleTempRole(UINT32 dwRoleID, UINT32 dwSceneTempID, UINT32 dwSceneID, UINT8 bySide = 1);

private:
	BOOL _AddtoCurBattle(UINT32 dwID, UINT32 dwRoleCount, UINT32 dwMatch);
	BOOL _AddtoNewBattle(SBattleQueueInfo* stBattleQueueInfo);
	BOOL _CheckStartNewBattle(UINT32 dwSceneTempID);
	BOOL _StartNewBattle(UINT32 dwSceneTempID);
	BOOL _UpdateNewBattle(UINT32 dwSceneTempID);
	BOOL _UpdateBattleTempRole();

	BOOL _EnterBattle(SCENE_INFO* pstEnterScene, UINT8 bySide, UINT32 dwID);
	BOOL _GetBattleScene(UINT32 dwSceneTempID, UINT32 dwRoleCount, UINT32& nSceneID, UINT8& bySide);

private:
	struct CTraverseSceneDataForBattle
	{
		BOOL operator()(const SCENE_DATA* pSceneData);
	};

private:
	static CBattleQueueMgr ms_Instance;
	CIDObjectPool<SBattleQueueInfo, UINT32>			m_BattleQueueInfoPool;
	CIDObjectPool<SBattleTempRole, UINT32>			m_BattleTempRolePool;
	UINT32											m_BattleMatchToSceneTempID[32];

	SBattleScene m_lstBattleScene[MAX_SCENE_TEMPLATE_COUNT];
	CBaseList m_lstBattleQueue;
	CBaseList m_lstBattleTempRole;
};

#endif