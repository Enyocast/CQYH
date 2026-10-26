
//virtual void PostLoad();

static UGlobalMapInfo* GetSingleton();
// void Draw(FViewport* Viewport, FCanvas* Canvas);
static UPackage* GetGlobalMapInfoPackage();

//FTeleportLink* FindLinkByOrig(const FString& mapName, const FString& origObjName);
FExportMap* FindMapInfoPointer( int mapID );
FServerMapInfos* FindServerMapInfPointer(INT serverID);

int FindLinkByOrig( TArray<FTeleportLink*> *plinkList, const FString& MapName, const FString& origObjName);
int FindLinkByOrigID( TArray<FTeleportLink*> *plinkList, const FString& MapName, int origID);
FTeleportLink* FindLinkByMapAndID( const FString& mapName, int linkID );
void UpdateLinks();
// >add by zhangrui05@snda
int GetMapLinks(INT fromMapId, INT toMapId, TArray<FTeleportLink*>& linkList);
// <add by zhangrui05@snda 

TArray<FDungeonInfo> &GetDungeonInfoList();
const TArray<FExportMap> &GetAllScenesInfo();

FTeleportObject* FindOrig(const FString& mapName, const FString& origObjName);
const TArray< FTeleportObject > *FindAllOrigInMap( const FString& mapName );
FTeleportObject* FindTarget(const FString& mapName, const FString& origObjName);

int FindTeleportNetNodesInRegion( TArray<FTeleportNodeObj*> *pNodesList, INT RegionID );
FTeleportNodeObj* FindTeleportNetNodes( INT nodeID );
FTeleportNodeObj* FindTeleportNetNodes( INT inSceneID, FString nodeName );

//return the position of the first data found in data container
INT GetNpcInstanceInMap( INT sceneID, TArray<FNPCInstanceInfo*> &rtnList );
//
const TArray<FNPCGroupInfo>* GetNpcGroupsInMap( INT sceneID );
//
const TArray<FQuestVolumeInfo>* GetQuestVolumesInMap( INT sceneID );
const TArray<FNaviPointInfo>* GetAllNavPointsInMap( INT sceneID );
//
TArray<FInMapRegion> &GetAllMapRegionInfo();
void FindAllMapOfType( BYTE type, TArray<UINT> &mapIDContainer );

void SaveToFile( const FString& BinFile );
void SaveNetNodesToFile( const FString& BinFile );

void PostEditChangeProperty( struct FPropertyChangedEvent& PropertyChangedEvent);

void LoadNPCInfoFromXMLFiles();
void LoadMapSizeVolumeFromXML();
void LoadSearchPointFromXMLFiles();
void LoadNaviPointInfoFromXMLFiles();
void LoadNpcSpawnGroupInfoFromXMLFiles();
void LoadQuestVolumeInfoFromXMLFiles();

#if !SHIPPING_PC_GAME

void ImportFromExcel(TArray< TArray<FString> >& sceneDat, TArray< TArray<FString> >& dungeonDat);
void ImportFromText();
#endif