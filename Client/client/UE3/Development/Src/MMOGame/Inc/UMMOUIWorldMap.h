
virtual void Init();
void InitWorldMapMc();
virtual void UnInit();

void ShowCurSceneMapConent();

void ShowMapPanelContent( EPanelTypeWorldMap worldMapType );
void ShowWorldMapInUnitedMapContent( INT mapID, INT regionInMapIdx );

UBOOL CreateMapMarkUIObject( struct FObjInMapUI *pMapMarkData );
//UGFxObject* GetMapMarkUIObjectContainer( INT type );
void DistoryRootMc( UGFxObject* &pMc );

virtual void PostOnShow(UBOOL v);
void WorldMapOnShow( UBOOL isShow );

const struct FMapMark *AddMapMark();
void UpdateShareUserMarkButtonState( INT shareTargetType );

//
FVector ConvertPosInMapUIToWorld3DPos( INT posX, INT posY );
FVector2D ConvertPosInMapUIToWorldmapResPos( INT posX, INT posY );
FVector2D ConvertWorld3DPosToPosInMapUI( FVector pos3D );
UBOOL CheckMapPosition( FLOAT &moveDeltaX, FLOAT &moveDeltaY );

//
void ShowMapMarksInfomation( UBOOL isToShow );
void UpdateMapMarksInfomation( FVector centerPos3D, FLOAT fYawDeg );

// 更新公会据点战信息
void UpdateGuildOccupyInfo(INT mapId);