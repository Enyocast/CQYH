#ifndef _MMOUNITEDMAP_H_
#define _MMOUNITEDMAP_H_

//virtual void Init();
void InitMc();

void InitAllTiles();
void OnClickUnitedMapTile( INT tileIdx, INT mapID, const FString &regionName );
void ShowMapTilesIn( UGFxObject *fromContainer, UGFxObject *toContainer );
void HighlightTile( INT tileIdx, UBOOL isToSel );

virtual void PreOnShow(UBOOL show);
void UnitedMapOnShow( UBOOL isShow );

void InitByParent( class UMMOUIBase *parentPanel );
virtual void UnInit();

#endif