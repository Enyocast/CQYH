#ifndef _UMAPDATAMANAGER_H_
#define _UMAPDATAMANAGER_H_

#include "MMOSingleton.h"
#include "MMOGameClasses.h"
#include "CommonGameEvents.h"

namespace ExternalMessage
{
    struct G2C_SYNC_COMBAT_STAT;
}

	struct FTeleportNetNodeData
	{
		FTeleportNodeObj* _NodeTemplate;
		UBOOL _isPlayerOpened;
	};

	enum EActorInMapUIType
	{
		EACTMUI_InVisible,
		EACTMUI_StaticNPC,
		EACTMUI_NpcGroup,
		EACTMUI_QuestZone,
		EACTMUI_NavPoint,
		EACTMUI_TeleportFB,
		EACTMUI_TeleportMap,
		EACTMUI_TeleportInDoor,
		EACTMUI_TeleportNode,
		EACTMUI_NearMonster,
		EACTMUI_NearBoss,
		EACTMUI_NearPlayer,
		EACTMUI_NearNormalNPC,
		EACTMUI_UserMark,
		EACTMUI_PathPoint,
		EACTMUI_GlobalTeammate,
		EACTMUI_BattleFlag,
		EACTMUI_ExtaInfo,//并非标记，配合标记显示的文字描述
		EACTMUI_MyPet,
		EACTMUI_OtherPet,
		EACTMUI_Max
	};

	enum EActorInMapFlag
	{
		EACTUIF_None=0x00,
		EACTUIF_FunctionNpc=0x01,
		EACTUIF_TaskNpc=0x02,
		EACTUIF_FB=0x04
	};

	enum EActorInMapUpdateFlag
	{
		EACTUIUF_NoUpdate=0x00,
		EACTUIUF_WorldMap=0x01,
		EACTUIUF_MiniMap=0x02,
		EACTUIUF_PathMap=0x04,
		EACTUIUF_UpdateAll=0x07,
	};

	enum EShareUserMarkTargetType
	{
		ESUType_Team,
		ESUType_Guild
	};

	struct FObjInMapUI
	{
		UINT _ID;
		INT _Type;
		FString _DisplayName;
		UGFxObject *_UiObjInWorldMap;
		UGFxObject *_UiObjInMiniMap;
		UGFxObject *_UiObjInPathMap;
		INT _NeedUpdateFlag;
		//UBOOL _IsWorldmapVisible;
		//UBOOL _IsMinimapVisible;
		FString _UiIconIdx;
		UBOOL _IsValid;

		FObjInMapUI();
	};

	struct FMapMark
	{
		INT _MarkID;
		FString _MarkName;
		INT _SceneID;
		FString _RegionName;
		FVector _Pos;
		INT _MarkType;

		UBOOL _isValid;

		FMapMark();
	};

	struct FMapMarkExport
	{
		TCHAR _MarkName[17];
		TCHAR _RegionName[33];
		FVector _Pos;
		INT _MarkType;
	};

	struct FUserMarkInMapUI : FObjInMapUI
	{
		UINT _RelatedMarkID;

		FUserMarkInMapUI();
	};

	struct FActorInMapUI : FObjInMapUI
	{
		UINT _ActorID;
		UINT _AidID;
		UINT _InMapID;
		INT _ToggleFlag;
		FVector _OrigInMapPos;
		FVector2D _CurMapPos2D;

		FActorInMapUI();
	};

	//struct FActorGroupInMapUI : FObjInMapUI
	//{
	//	INT _LookupIdx;
	//	INT _GroupType;
	//	INT _ActorTemplateID;
	//	UINT _InMapID;
	//	INT _ToggleFlag;
	//	FVector _OrigInMapPos;

	//	FActorGroupInMapUI();
	//};

	struct FPathPointInMapUI : FObjInMapUI
	{
		FVector _OrigInMapPos;
		INT _MapID;
		//FPathPointInMapUI();
	};

	//
	struct MapLineInfo
	{
		INT _SceneLineCombineID;
		INT _PercentState;
	};

	//
	struct CurSceneProgress
	{
		const FSceneProgress *_Template;
		INT _CurValue;
	};

	struct CurSceneTarget
	{
		CurSceneProgress _MainTarget;
		CurSceneProgress _ChildTargets[UCONST_MaxSceneMinorTarget];
	};

	enum EDungeonConstTargetType
	{
		EDgenCnstTgtTyp_TargetKilled,
		EDgenCnstTgtTyp_SpecialKilled,
		EDgenCnstTgtTyp_ShortTimeKill,
		EDgenCnstTgtTyp_Undead,
		EDgenCnstTgtTyp_Max
	};
	static INT MAX_Dungeon_Target_ID_Start = 24;
	static INT MAX_Dungeon_Target = 8;
	struct FBAchievementsState
	{
		const FDungeonTarget *_achievementTemplate;
		INT _score;
	};

	static UINT MAP_PATH_POINT_INTERVAL_FACTOR = 4;
	static UINT MAP_PATH_POINT_REMOVE_LENGTH = 100000;
	
	class MMOMapDataManager : public SingletonMeyers<MMOMapDataManager>, public INativeGameEventHandler
	{
	public:
		static void ParseServerMapLine(UINT serverMapLine, UINT &serverID, UINT &lineID);
	public:
		typedef TMap< INT, TMap< INT, FMapMark > > MapUserMarksContainer;
		typedef TMap< INT, TArray<FNPCInstanceInfo*> > MapNPCsContainer;
		//typedef TMap< INT, const TArray<FNPCGroupInfo>* > MapNpcGroupsContainer;
		typedef TMap< UINT, UINT > NPCsMarkedInMapContainer;
		typedef TMap< INT, UINT > NpcGroupsMarkedInMapContainer;
		typedef TMap< UINT, UINT > FBsMarkedInMapContainer;
		typedef TMap< UINT, UINT > MapNavPointsInMapContainer;
		typedef TMap< INT, TArray<FInMapRegion*> > MapRegionsContainer;

		typedef TMap< INT, FActorInMapUI > MapDynamicActorContainer;
		typedef TMap< INT, FActorInMapUI >::TIterator MapDynamicActorIterator;
		typedef TArray< FActorInMapUI > MapStaticActorContainer;
		typedef TArray< FUserMarkInMapUI > MapUserMarkContainer;
	public:
		MMOMapDataManager(void);
		virtual ~MMOMapDataManager(void);

		void Initialize();
		//
		void InitTeleportClientData();
		//
		void InitAllMapRegionData();
		//
		void InitCurWorldMapRegionData();
		//
		void ClearTeleportDynamicData();
		void UpdateTeleportDynamicData();
		void Shutdown();
		void OnNativeGameEvent( struct MMOGameEvent* evt );

		FVector MMOMapDataManager::CvtSceneVecToGridIdx( const FVector &pos3D );
		//传送点
	public:
		//FTeleportNodeObj *GetTeleportNetNodes( EWorldRegion regionID, INT nodeID );
		//INT GetTeleportNetNodesIn( EWorldRegion regionID, INT mapID, UBOOL isAllMap, TArray<FTeleportNodeObj*> *rtnList );
		FTeleportNetNodeData *GetTeleportNetNodes( EWorldRegion regionID, INT nodeID );
		FTeleportNetNodeData *GetTeleportNetNodes( EWorldRegion regionID, INT inSceneID, const FString &nodeName );
		FTeleportNetNodeData *GetTeleportNetNodes( INT nodeID );
		INT GetTeleportNetNodesIn( EWorldRegion regionID, INT mapID, UBOOL isAllMap, TArray<FTeleportNetNodeData*> *rtnList );
		INT GetTeleportNetNodesIn( INT mapID, TArray<FTeleportNetNodeData*> *rtnList );
		ATeleportNetNode *FindSceneTeleportsNetNode( INT inSceneID, const FString &nodeName );

		void SetGettedServerTeleportData(UBOOL isGetted){ _IsTeleportUpdatedByServer = isGetted; }
		UBOOL IsGettedServerTeleportData(){ return _IsTeleportUpdatedByServer; }
		void SetCurOpenedNodeID( INT nodeID ){ _LastOpenedTeleportNodeID = nodeID; }
		FTeleportNodeObj *GetLastOpendNode(){ return UGlobalMapInfo::GetSingleton()->FindTeleportNetNodes( _LastOpenedTeleportNodeID ); }

		void NotifyTeleportsNetNodesOpened( INT nodeID, UBOOL isOpened );
		void ActiveCurSceneTeleports();
		void FirstOpeneTeleportsNetNodes( INT nodeID );

		//地图
	public:
		////当前人物所在地图中的区域
		//INT GetCurReginIdxInMap(){ return _InCurMapRegionIdx; };
		//AMMOVolume_MapSize *GetReginInMap( INT inRegionIdx ){ 
		//	if( inRegionIdx < 0 || inRegionIdx >= _CurMapRegionInfo.Num() ){
		//		return NULL;
		//	}
		//	return _CurMapRegionInfo(inRegionIdx);
		//}

		////检查当前人物所在地图内区域
		//INT CheckRegion();
		FInMapRegion *GetCurReginInCurMap(){ return _InCurMapRegion; }
		//
		FInMapRegion *GetReginInCurMap( INT inRegionIdx ){
			return GetReginInMap( _CurSceneInfo.ServerID, inRegionIdx );
		}
		//
		UBOOL IsCurMapRegionMultilayer(){ return IsMapRegionMultilayer( _CurSceneInfo.ServerID ); }
		UBOOL IsWorldmapRegionMultilayer(){ return IsMapRegionMultilayer( _CurWorldMapInfo.ServerID ); }
		UBOOL IsMapRegionMultilayer( INT mapID );
		//
		FInMapRegion *GetReginInMap( INT mapID, INT inRegionIdx ){
			TArray<FInMapRegion*> &singleMapRegionList = _AllMapRegionsInfo.FindOrAdd( mapID );
			if( !singleMapRegionList.IsValidIndex( inRegionIdx ) ){
				return NULL;
			}
			return singleMapRegionList(inRegionIdx);
		}
		//
		FInMapRegion *GetReginInMap( INT mapID, const FString &inRegionVolumeName );
		INT GetReginInMapIdx( INT mapID, const FString &inRegionVolumeName );
		//
		TMap< INT, TArray<FInMapRegion*> > &GetAllMapRegions(){
			return _AllMapRegionsInfo;
		}

		//检查当前人物所在地图内区域
		INT GetCurPlayerRegionIn( const FVector &playerPos );
		UBOOL IsInCurRegion( const FVector &checkPos );
		//
		INT CheckRegionIn( INT mapID, const FVector &checkPos );
		//当前人物所在地图中的区域
		INT GetCurReginIdxInMap(){ return _InCurMapRegionIdx; }
		//INT SetCurReginIdxInMap( UINT regionInMapIdx ){ _InRegionIdx = regionInMapIdx; }

		//当前人物所在地图信息
		void SetCurMap( INT sceneID );
		void SetCurMap( const FString &mapName );
		FExportMap &GetCurMap(){ return _CurSceneInfo; }
		//当前地图的线信息
		INT GetCurSceneLineIn(){ return _CurSceneLineIn; }
		void SetCurSceneLineIn( INT lineID );

		TArray< MapLineInfo > &GetCurMapLines(){ return _CurSceneLines; }
		void AddNewCurMapLine( INT lineID, INT percentState );
		void RemoveOldCurMapLine( INT lineID );
		void ClearCurMapLines(){ _CurSceneLines.Empty(); }
		//当前地图进度信息
		TArray<CurSceneTarget> &GetCurSceneProgress(){ return _CurSceneProgress; }
		void InitCurSceneProgress();
		//副本评价点
		void InitFBConstAchievements();
		TArray<FDungeonTarget> &GetFBConstAchievements(){ return _FBConstAchievements; }

		void ParseDungeonFinishDatasForAchievement( G2C_DUNGEON_FINISH_DATA* serverMsg );
		void ParseDungeonCombatDatas( ExternalMessage::G2C_SYNC_COMBAT_STAT* serverMsg, UINT dataCnt );
		void PrepareCurFBAchievementsScore( INT mapID, INT fbDifficult );

		TArray<FBAchievementsState> &GetFBAchievementsScoreData(){ return _FBAchievementsData; }
		FBAchievementsState *FindFBAchievementCurrentDungeon( INT fbAchieveID );
		//当前大地图信息
		void SetCurWorldMap( INT sceneID, INT inRegionIdx );
		FExportMap &GetCurWorldMap(){ return _CurWorldMapInfo; }
		FInMapRegion *GetCurWorldMapRegion(){ return _InWorldmapRegion; }
	public:
		//修改过地图标记的地图
		TMap< INT, INT > &GetNeedUpdateMap(){ return _UserMarksEditedMapContainer; }
		//地图标记
		void InitialMapUserMarks( INT sceneID );
		UBOOL LoadMapUserMarks( INT sceneID );
		UBOOL ExportMapUserMarks( INT sceneID );
		void ResetCurWorldUserMarkUI();
		FMapMark *GetMapMarkData( INT sceneID, INT markID );
		FMapMark *AddMapMarkData( INT sceneID, const FString &regionVolumeName, const FString &markName, INT markType, const FVector &pos );
		FUserMarkInMapUI *AddMapMarkToUI( FMapMark *pNewMapMarkData );
		//地图标记显示
		FUserMarkInMapUI *AddMapMark( INT sceneID, const FString &regionVolumeName );
		void RemoveMapMark( INT sceneID, INT markID );
		TArray<FUserMarkInMapUI> &GetCurWorldMapMarks(){
			return _ListWorldMapUserMarks;
		}

		//动态的物体
		//void ClearAllTeammateInDymcActorGlobal();
		FActorInMapUI *AddOrUpdateMapDymcActorNear( AMMOActor &addCharactor );
		FActorInMapUI *AddOrUpdateMapDymcActorGlobal( INT actorID, EActorInMapUIType type, INT inMapID, const FString &displayName );
		FActorInMapUI *FindMapDymcActorGlobal( INT actorID );
		void FindMapDymcActorGlobalOfType( EActorInMapUIType actorType, TArray<FActorInMapUI*> &rtnArray );

		void RemoveMapDymcActorNear( INT actorID ){
			RemoveMapDymcActor( _MapNearActors, actorID );
		}
		void RemoveMapDymcActorGlobal( INT actorID );
		void RemoveAllMapDymcActorGlobalOfType( EActorInMapUIType actorType );
		void RemoveMapDymcActorGlobalOfType( EActorInMapUIType actorType, INT actorID );

		MapDynamicActorIterator BeginIterateDymcActorNear(){
			MapDynamicActorIterator it( _MapNearActors );
			return it;
		}
		MapDynamicActorIterator BeginIterateDymcActorGlobal(){
			MapDynamicActorIterator it( _MapGlobalActors );
			return it;
		}

		FActorInMapUI *GetMapDymcActorNear( INT actorID ){
			return GetMapDymcActor( _MapNearActors, actorID );
		}
		FActorInMapUI *GetMapDymcActorGlobal( INT actorID ){
			return GetMapDymcActor( _MapGlobalActors, actorID );
		}

		FActorInMapUI *GetMapDymcActorNearByUiID( INT uiID ){
			return GetMapDymcActorByUiID( _MapNearActors, uiID );
		}
		FActorInMapUI *GetMapDymcActorGlobalByUiID( INT uiID ){
			return GetMapDymcActorByUiID( _MapGlobalActors, uiID );
		}

		//场景静态NPC信息
		const TArray<FNPCInstanceInfo*> *GetNpcInstanceInMap( INT sceneID );

		//-------------------------------------------
		//
		void InitMinimapStaticActorsContainer();
		//当前地图场景所显示的NPC表，GetNpcInstanceInMap中的索引为为Key,在标示点列表(_ListCurMapUIStaticActors)中的编号为value
		const TMap< UINT, UINT > &GetCurScenePuttedUsefulNpcs(){ return _CurScenePuttedUsefulNpcContainer; }

		//当前小地图UI所显示的NPC表，NPC的ID为Key, 在标示点列表(_ListCurMapUIStaticActors)中的编号为value
		TArray<FActorInMapUI*> &GetStaticActorsInCurRegion(){ return _MinimapStaticActorsContainer; }

		//-------------------------------------------
		//
		void InitWorldMapStaticActorsContainer( INT inRegionIdx );
		TArray<FActorInMapUI*> &GetStaticActorsInWorldmap(){ return _WorldMapStaticActorsContainer; }
		//当前大地图场景所显示的NPC表，GetNpcInstanceInMap中的索引为为Key,在标示点列表(_ListWorldMapUIStaticActors)中的编号为value
		const TMap< UINT, UINT > &GetScenePuttedUsefulNpcs(){ return _ScenePuttedUsefulNpcContainer; }

		//
		void ClassifyWorldMapStaicMarks();

		//
		void InitWorldMapPuttedUsefulNpcs();
		//当前大地图UI所显示的NPC表，NPC的ID为Key, 在标示点列表(_ListWorldMapUIStaticActors)中的编号为value
		const TMap< UINT, UINT > &GetWorldMapPuttedUsefulNpcs(){ return _WorldMapPuttedUsefulNpcContainer; }

		//场景中的怪点
		void InitWorldMapPuttedNpcGroups();
		const TMap< INT, UINT > &GetWorldMapPuttedNpcGroups(){ return _WorldMapPuttedNpcGroupsContainer; }
		//
		const TArray<FNPCGroupInfo> *GetNpcGroupsInMap( INT sceneID );

		//场景中的特殊区域
		const TArray<FQuestVolumeInfo> *GetSpeciZoneInMap( INT sceneID );
		//场景中的寻路点
		const TArray<FNaviPointInfo> *GetNavPointsInMap( INT sceneID );

		//场景中的副本
		void InitWorldMapPuttedFBs();
		//当前大地图UI所显示的FB表，FB跳转点的ID为Key, 在标示点列表(_ListWorldMapUIStaticActors)中的编号为value
		const TMap< UINT, UINT > &GetWorldMapPuttedFBs(){ return _WorldMapPuttedFBContainer; }

		//场景中的副本
		void InitWorldMapNavPoints();
		//当前大地图UI所显示的寻路点表, GetNavPointsInMap中的编号为Key，地图中的标记编号为value
		const TMap< UINT, UINT > &GetWorldMapNavPoints(){ return _WorldMapNavPointsContainer; }
		
		//更新固定点状态
		//void UpdateCurMapStaticMarksOfType( EActorInMapUIType actorType ){
		//	UpdateMapStaticMarksOfType( actorType, _CurSceneInfo.ServerID );
		//}
		//void UpdateWorldMapStaticMarksOfType( EActorInMapUIType actorType ){
		//	UpdateMapStaticMarksOfType( actorType, _CurWorldMapInfo.ServerID );
		//}
		//静态物体：地图NPC
		//需先SetCurMap
		void PrepareCurMapStaticActorInMapUI(){
			PrepareMapStaticActorInMapUI( _CurSceneInfo.ServerID, _ListCurMapUIStaticActors, true );
			InitMinimapStaticActorsContainer();
		}
		//需先SetCurWorldMap
		void PrepareWorldMapStaticActorInMapUI(){
			PrepareMapStaticActorInMapUI( _CurWorldMapInfo.ServerID, _ListWorldMapUIStaticActors, false );
			InitWorldMapStaticActorsContainer( _InWorldmapRegionIdx );
		}
		//
		void PrepareMapStaticActorInMapUI( INT sceneServerID, TArray< FActorInMapUI > &container, bool isCurScene );
		//
		TArray< FActorInMapUI > &GetCurMapStaticActorPointsList(){
			return _ListCurMapUIStaticActors;
		}

		TArray< FActorInMapUI > &GetCurWorldMapStaticActorPointsList(){
			return _ListWorldMapUIStaticActors;
		}

		FActorInMapUI &GetCurWorldMapStaticActorInMapUIByActorID( UINT id ){
			INT cnt = _ListWorldMapUIStaticActors.Num();
			for( INT i = 0; i < cnt; ++i ){
				FActorInMapUI &actorInMap = _ListWorldMapUIStaticActors( i );
				if( actorInMap._ActorID == id ){
					return actorInMap;
				}
			}
		}

		//地图标志信息
		TArray< FActorInMapUI > &GetCurWorldMapMarksHintInfo(){
			return _ListWorldMapUIMarksHintInfo;
		}
		void AddWorldMapMarkInfo( FVector real3DPos, const FString &info );
		void InvalidAllWorldMapMarkInfo();

		//寻路路径
		TArray<FVector> GetCurMainPlayerPath( UINT interval, UBOOL is2D );
		void SetLastInputMoveToPos( FVector pos ){ _LastInputPos = pos; }
		FVector GetLastInputMoveToPos(){ return _LastInputPos; }

		//
		void InvalidCurPath();
		UINT GetCurSceneWorldMapPathInterval();
		void SetMapPath( TArray< FVector > &pathList );
		TArray< FPathPointInMapUI > &GetCurMapPath();
		TArray< FPathPointInMapUI > &GetAllMapPathResource(){ return _MapCurPath; }

		//当前大地图上可接，可完成，已完成任务列表,任务ID为Key，所属NPC的ID为Value
		TMap< UINT, UINT > &GetCompleteTaskInWorldMap(){ return _CompleteTaskContainer; }
		TMap< UINT, UINT > &GetUncompleteTaskInWorldMap(){ return _UncompleteTaskContainer; }
		TMap< UINT, UINT > &GetAcceptableTaskInWorldMap(){ return _AcceptableTaskContainer; }
	public:
		//副本难度
		INT GetCurFBDiff(){ return _CurFBDiff; }
		void SetCurFBDiff( INT difficulty ){ _CurFBDiff = difficulty; }

		//副本难度
		INT GetMaxDiffOfType( INT mapID, INT type, INT allTypeMaxDiff );
		INT GetCurFBMaxDiff(){ return _CurFBMaxDiff; }
		void SetCurFBMaxDiff( INT difficulty ){ _CurFBMaxDiff = difficulty; }

		//
		INT GetCurFBEnterFrequence(){ return _CurFBFrequence; }
		void SetCurFBEnterFrequence( INT frequence ){ _CurFBFrequence = frequence; }

		//
		//UBOOL LoadDungonInfo();
		const FDungeonInfo *GetDungeonInfo( UINT mapID, UINT diffculty );
		INT GetDungeonInfoDifftyMask( UINT mapID );

		//副本时间
		INT GetTimeSinceDungeonBegin();
		UINT32 GetDungeonStartTime(){ return _DungeonStartUtcTime; }
		void SetDungeonStartTime( UINT32 startTime, INT modifySec = 0 ){ _DungeonStartUtcTime = startTime + modifySec; }

	private:
		//地图上动态更新物体
		FActorInMapUI *AddOrUpdateMapDymcActor( MapDynamicActorContainer &container, INT actorID, const FString &displayName );
		void ChangeMapMarkDisplayIcon( FActorInMapUI *pActorInMapUI, AMMOActor &charactor );
		void ChangeMapNearPlayerMarkDisplayIcon( FActorInMapUI *pActorInMapUI,  AMMOActor &charactor );

		void RemoveMapDymcActor( MapDynamicActorContainer &container, INT actorID );
		FActorInMapUI *GetMapDymcActor( MapDynamicActorContainer &container, INT actorID );
		FActorInMapUI *GetMapDymcActorByUiID( MapDynamicActorContainer &container, INT uiID );

		//地图标记
		FMapMark *AddMapMarkData( INT sceneID, const FString &regionVolumeName );
		FMapMark *RemoveMapMarkData( INT sceneID, INT markID );
		TMap< INT, FMapMark > *GetMapMarkDatas( INT sceneID );
		//
		int PutNpcToMapUI( INT sceneServerID, INT curObjIdx, TArray< FActorInMapUI > &container, TMap< UINT, UINT > &npcContainer );
		int PutNpcGroupsToMapUI( INT sceneServerID, INT curObjIdx, TArray< FActorInMapUI > &container );
		int PutTelportToMapUI( INT sceneServerID, INT curObjIdx, TArray< FActorInMapUI > &container );
		int PutTelportNodeToMapUI( INT sceneServerID, INT curObjIdx, TArray< FActorInMapUI > &container );
		int PutSpeciZoneToMapUI( INT sceneServerID, INT curObjIdx, TArray< FActorInMapUI > &container );
		int PutNavPointsToMapUI( INT sceneServerID, INT curObjIdx, TArray< FActorInMapUI > &container );

		void UpdateMapStaticMarksOfType( EActorInMapUIType actorType, INT sceneID );

		//复活点
	public:
		void ActiveRevivePoint( FVector &activePnt );
		//void OnActiveRevivePointActiveEffectFinished( UParticleSystemComponent *psc );

		//传送点
	private:
		UBOOL _IsTeleportInited;
		UBOOL _IsTeleportUpdatedByServer;
		//一个经过显示优先级排序的且按地图存储的跳转点表，包含在各自的区域中（固定数组中）
		//TArray<FTeleportNodeObj*> _RegionTeleportNetList[EWR_MAX];
		TArray<FTeleportNetNodeData> _RegionTeleportNetList[EWR_MAX];
		//
		INT _LastOpenedTeleportNodeID;

		//寻路
	private:
		FVector _LastInputPos;

		//地图
	private:
		//所有场景地图区块信息
		MapRegionsContainer _AllMapRegionsInfo;
		//当前地图信息
		FExportMap _CurSceneInfo;
		//当前地图线信息
		TArray< MapLineInfo > _CurSceneLines;
		//现在所在线
		INT _CurSceneLineIn;
		//当前副本难度
		INT _CurFBDiff;
		INT _CurFBMaxDiff;
		//当前副本进入
		INT _CurFBFrequence;
		//副本进度
		TArray<CurSceneTarget> _CurSceneProgress;
		////副本信息
		//DungeonInfoContainer _AllDungeonBaseInfo;
		//当前地图区块信息
		TArray< AMMOVolume_MapSize* > _CurMapRegionInfo;
		//当前地图区域
		INT _InCurMapRegionIdx;
		FInMapRegion *_InCurMapRegion;
		//当前大地图区域
		INT _InWorldmapRegionIdx;
		FInMapRegion *_InWorldmapRegion;
		//当前大地图显示地图信息
		FExportMap _CurWorldMapInfo;

		//各地图NPC点
		MapNPCsContainer _AllMapNpcContainer;
		//各地图怪点
		//MapNpcGroupsContainer _AllMapNpcGroupsContainer;

		//各地图标记点
		MapUserMarksContainer _AllMapUserMarkContainer;
		TMap< INT, INT > _UserMarksEditedMapContainer;

		//需显示的地图玩周围九屏动态标记（现为玩家和怪物）,actorID为Key
		MapDynamicActorContainer _MapNearActors;

		//需显示在整个地图上动态标记（如队友，某些特殊物体）,actorID为Key
		MapDynamicActorContainer _MapGlobalActors;

		//地图上的静态标记点，即为场景中事先放置的NPC(_ActorID为_AllMapNpcContainer该地图NPC表中的索引)，跳转点。
		//当前地图需显示的地图静态标记（现为地图摆放的需要显示在地图UI上的NPC，其中_UiObjInWorldMap无效）
		MapStaticActorContainer _ListCurMapUIStaticActors;
		//大地图需显示的地图静态标记（现为地图摆放的需要显示在地图UI上的NPC，其中_UiObjInMinimapap无效）
		MapStaticActorContainer _ListWorldMapUIStaticActors;
		MapStaticActorContainer _ListWorldMapUIMarksHintInfo;

		//大地图的玩家自定义标记
		MapUserMarkContainer _ListWorldMapUserMarks;

		//需显示在地图上的当前路径
		TArray<FPathPointInMapUI> _MapCurPath;

		//_CurScenePuttedUsefulNpcContainer与_ScenePuttedUsefulNpcContainer的存在
		//是为了在显示附近NPC时把已经显示了的NPC剔除
		//当前地图的NPC表，GetNpcInstanceInMap中的索引为为Key
		NPCsMarkedInMapContainer _CurScenePuttedUsefulNpcContainer;
		//当前小地图所显示的NPC表，GetNpcInstanceInMap中的索引为Key
		TArray< FActorInMapUI* > _MinimapStaticActorsContainer;

		//当前大地图所在场景上的NPC表，GetNpcInstanceInMap中的索引为Key
		NPCsMarkedInMapContainer _ScenePuttedUsefulNpcContainer;
		//当前大地图所显示的NPC表，GetNpcInstanceInMap中的索引为Key
		NPCsMarkedInMapContainer _WorldMapPuttedUsefulNpcContainer;
		//
		TArray< FActorInMapUI* > _WorldMapStaticActorsContainer;
		//大地图上的怪点
		NpcGroupsMarkedInMapContainer _WorldMapPuttedNpcGroupsContainer;
		//当前大地图副本表,跳转点ID为Key，在地图中显示的uiObject所标记编号为value
		FBsMarkedInMapContainer _WorldMapPuttedFBContainer;
		//
		MapNavPointsInMapContainer _WorldMapNavPointsContainer;

		//当前大地图上可接，可完成，已完成任务列表
		TMap< UINT, UINT > _CompleteTaskContainer;
		TMap< UINT, UINT > _UncompleteTaskContainer;
		TMap< UINT, UINT > _AcceptableTaskContainer;

		//副本评价点
		TArray<FDungeonTarget> _FBConstAchievements;
		TArray<FBAchievementsState> _FBAchievementsData;
		//副本时间
		UINT32 _DungeonStartUtcTime;
	};
	
#endif