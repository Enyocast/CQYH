#ifndef _MMOMINIMAP_H_
#define _MMOMINIMAP_H_

virtual void Init();
void InitMc();

UBOOL CreateMapMarkUIObject( struct FObjInMapUI *pMapMarkData );
//UGFxObject* GetMapMarkUIObjectContainer( INT type );
void DistoryRootMc( UGFxObject* &pMc );

void ResizeMap();
FVector2D CvtScenePosToCurMinimapUiPosByScaledCenterPos( FVector mapPos3D, FVector2D centerPos2D, float cosine, float sine );
FVector ConvertPosInMapUIToWorld3DPos( INT posX, INT posY );

virtual void PreOnShow(UBOOL show);
void UpdateMapPath( FVector2D pivotPos, FLOAT fYawDegCosine, FLOAT fYawDegSine );

void OnClickBattleInfoBtn( INT x , INT y );
void HintBattleInfo();
void HideHintBattleInfo();
void UpdatePingRate(float DeltaTime);

void UpdateArenaEntVisible();

virtual void UnInit();
virtual void OnNativeGameEvent(struct MMOGameEvent* evt);

void ShowTipsToggleShowMap();
void ShowMapTimeCount( INT sec, UBOOL isToShow = TRUE );

FString GetFPS();

#endif