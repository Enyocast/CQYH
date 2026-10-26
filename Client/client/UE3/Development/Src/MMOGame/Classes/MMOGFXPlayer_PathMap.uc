class MMOGFXPlayer_PathMap extends MMOGFXPlayer
	native(UI)
	config(MMOGame);

var MMOUIPathMap _PathMap;

//native function PostAdvance(float DeltaTime);

function RegisterPathMap( MMOUIPathMap mc )
{
	_PathMap = mc;
	RegisterUI( mc, class'MMOUIManager'.default.Panel_PathMap);
}

//
event bool SkipCaptureInputKey(const string key, EInputEvent eIE, const string strHoverControllerName, Vector2D ClickPosInMovieSpace)
{
	//return false;
	//if( strHoverControllerName == "mapMaskZone_mc" || strHoverControllerName == "mapZone_mc" || strHoverControllerName == "MapNpcView_mc" ){
	//{
	//	return false;
	//}
	//return super.SkipCaptureInputKey(key, eIE, strHoverControllerName, ClickPosInMovieSpace);

	if( strHoverControllerName == "BackToMinimapBtn" )
	{
		return super.SkipCaptureInputKey(key, eIE, strHoverControllerName, ClickPosInMovieSpace);
	}

	return false;
}

//
native function ASPathMapToMinimap();

//
native function ASShowPathMapMarkHint( int type, int idx );
native function ASHidePathMapMarkHint();

//End
DefaultProperties
{
	MovieInfoStr="UI_PathMap.PathMap"
	Priority=3
}
