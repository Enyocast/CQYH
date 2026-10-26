class MMOUIUnitedMap extends Object
	native(UI)
	config(UIVisibleMask);


struct native UnitedMapTileData
{
	var int SceneID;
	var string RegionName;
	var int AchievementID;
};
var int MapUnachieveID;
var int MapDefaultAchieveID;
//
var MMOGFXPlayer GFXPlayer;
var MMOPlayerController ctrl;
var MMOPlayer Player;

//
var MMOUIBase _ContainerPanel;
var array<GFxObject> MapTiles;
var array<GFxObject> MapTileContainers;
var array<UnitedMapTileData> MapTileData;
//var native Map_Mirror TilesLinkGraph{TMap< INT, UGFxObject* >};

var int LastMapID;
var string LastMapVolumeName;

//
event InitMapTile( GFxObject tileMc, int mapID, string regionName )
{
	if( _ContainerPanel != none ){
		_ContainerPanel.ActionScriptVoid( "UCInitMapTile" );
	}
	else{
		//ActionScriptVoid( "UCInitMapTile" );
	}
}

//
final native function ShowCurMap();
event ShowMapTile( int mapID, string regionName, bool isHighlight )
{
	if( isHighlight ){
		LastMapID = mapID;
		LastMapVolumeName = regionName;
	}

	if( _ContainerPanel != none ){
		_ContainerPanel.ActionScriptVoid( "UCShowMapTile" );
	}
	else{
		//ActionScriptVoid( "UCShowMapTile" );
	}
}

//
final native function ResetLastMapTile();
event HighlightMapTile( int mapID, string regionName, bool isHighlight )
{
	if( isHighlight ){
		LastMapID = mapID;
		LastMapVolumeName = regionName;
	}
	
	if( _ContainerPanel != none ){
		_ContainerPanel.ActionScriptVoid( "UCHighlightMapTile" );
	}
	else{
		//ActionScriptVoid( "UCHighlightMapTile" );
	}
}

event CallASGrapUnitedMapTile( GFxObject tileMapIDArray )
{
	if( _ContainerPanel != none ){
		_ContainerPanel.ActionScriptVoid( "UCUpdateUnitedMapTiles" );
	}
	else{
		//ActionScriptVoid( "UCHighlightMapTile" );
	}
}

event CallASShowUnitedMapTileLevel( bool isTOShow )
{
	if( _ContainerPanel != none ){
		_ContainerPanel.ActionScriptVoid( "UCToggleShowUnitedMapTileLevel" );
	}
	else{
		//ActionScriptVoid( "UCHighlightMapTile" );
	}
}

event array<GFxObject> CallASGetAllUnitedMapTileData()
{
	if( _ContainerPanel != none ){
		return _ContainerPanel.ActionScriptArray( "UCGetMapNode" );
	}
	else{
		//ActionScriptVoid( "UCGetMapNode" );
	}
}

//===============================================================================================================
//===============================================================================================================
////native function PostAdvance(float DeltaTime);

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
//===============================================================================================================
//===============================================================================================================

DefaultProperties
{
	//FriendlyName=UnitedMap
	MapUnachieveID=1
	MapDefaultAchieveID=0
	LastMapID=-1
	//IsDynamicLoad=true
	//CloseOnEsc=false
}
