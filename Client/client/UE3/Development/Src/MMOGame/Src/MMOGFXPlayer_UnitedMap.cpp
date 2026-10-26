#include "stdafx.h"
#include "MMOGameUIClasses.h"
#include "MMOFacade.h"
#include "MMOMapDataManager.h"

IMPLEMENT_CLASS(UMMOGFXPlayer_UnitedMap)


//==============================================================================================
void UMMOGFXPlayer_UnitedMap::ASClickToWorldMap( INT tileIdx, INT mapID, const FString &regionName )
{
	//if( _UnitedMap == NULL ){
	//	return;
	//}

	//_UnitedMap->OnClickUnitedMapTile( tileIdx, mapID, regionName );
}

//==============================================================================================
void UMMOGFXPlayer_UnitedMap::ASClickToBack( UGFxObject *fromMc, UGFxObject *toBackMc )
{
	//if( _UnitedMap == NULL ){
	//	return;
	//}

	//_UnitedMap->ShowMapTilesIn( fromMc, toBackMc );
}
//======================================================================================
void UMMOGFXPlayer_UnitedMap::ASClickToNewWorld( UGFxObject *fromMc, UGFxObject *toNewMc )
{

}

//======================================================================================
void UMMOGFXPlayer_UnitedMap::Init()
{
	Super::Init();
	check(FALSE && "UMMOGFXPlayer_UnitedMap::Init()");
	//MMOUI::RegisterMoviePlayer(this, MMOUI::GetUIManager()->MoviePlayer_UnitedMap);
}