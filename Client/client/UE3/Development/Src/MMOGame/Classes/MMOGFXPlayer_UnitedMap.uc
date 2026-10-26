class MMOGFXPlayer_UnitedMap extends MMOGFXPlayer
	native(UI)
	config(MMOGame);

//var MMOUIUnitedMap _UnitedMap;

////native function PostAdvance(float DeltaTime);

//function RegisterUnitedMap( MMOUIUnitedMap mc )
//{
//	_UnitedMap = mc;
//	RegisterUI( mc, class'MMOUIManager'.default.Panel_UnitedMap );
//}

////
//event bool SkipCaptureInputKey(const string key, EInputEvent eIE, const string strHoverControllerName, Vector2D ClickPosInMovieSpace)
//{
//	if( strHoverControllerName == "PlayerArraw_mc" || strHoverControllerName == "MapNpcView_mc" ){
//		return false;
//	}

//	return super.SkipCaptureInputKey(key, eIE, strHoverControllerName, ClickPosInMovieSpace);
//}

//
native function ASClickToWorldMap( int tileIdx, int mapID, string regionName );
native function ASClickToBack( GfxObject fromMc, GfxObject toBackMc );
native function ASClickToNewWorld( GfxObject fromMc, GfxObject toNewMc );
//End
DefaultProperties
{
	//MovieInfoStr="UI_UnitedMap.UnitedMap"
	Priority=6
}
