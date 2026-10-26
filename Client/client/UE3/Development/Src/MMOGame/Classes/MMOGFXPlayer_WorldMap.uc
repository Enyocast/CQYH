class MMOGFXPlayer_WorldMap extends MMOGFXPlayer
	native(UI)
	config(MMOGame);

var MMOUIWorldMap _WorldMap;

//native function PostAdvance(float DeltaTime);

function RegisterWorldMap( MMOUIWorldMap mc )
{
	_WorldMap = mc;
	RegisterUI( mc, class'MMOUIManager'.default.Panel_WorldMap);
}

// event UnRegister()
// {
// 	if( _WorldMap != none ){
// 		_WorldMap.ClearWorldMapUI();
// 	}
// 
// 	super.UnRegister();
// 	RegisterUI( none, class'MMOUIManager'.default.Panel_WorldMap);
// 	MMOUI::RegisterMoviePlayer(class'MMOUIManager'.default.MoviePlayer_WorldMap);
// }

//
native function ASWorldMapZoom( bool ZoomIn );
native function ASWorldMapZoomTo( int level );

native function ASMapDrag( float deltaX, float deltaY );

//地图点击移动
native function ASMoveToMapPos( int clickPosX, int clickPosY );
//native function ASMoveToRealMapPos( int mapPosX, int mapPosY );
native function ASInputCoodinateAndMoveTo( int inputX, int inputY );
//加注标记点
native function ASAddOrRemoveMarkMap( int clickPosX, int clickPosY );
//选择标记点共享目标
native function ASChangeShareUserMarkTarget( int listIdx, int targetType );
//共享标记点
native function ASShareUserMark( int targetType );
//切换地图
native function ASChangeMap( int mapID, int regionInMapIdx );
//切换显示大地图或是全局地图
native function ASShowWorldMapTabPanel( int type );
//找寻地图上的固定点
native function ASFindThisMapMark( int idx );
//移动到地图标记点
native function ASMoveToThisMapMark( int idxInStaticMap );
//
native function ASFindMapTask( int npcIdx );
//切换显示功能NPC
native function ASToggleFuncNpc( bool isShow );
//切换显示任务NPC
native function ASToggleTaskNpc( bool isShow );
//
native function ASConfirmAddUserMark();
//
native function ASConfirmDelUserMark();
//
native function ASCloseUserMarkPanel();
//地图点提示显示
native function ASShowWorldMapMarkHint( int type, int idx );
//
native function ASHideWorldMapMarkHint();
//
native function ASShowTipsWorldMapMarkListItem( GFxObject mc, int idxInStaticMap, string contentText );
native function ASHideTipsWorldMapMarkListItem( GFxObject mc );
//function ToggleWorldMap()
//{
//	ToggleShowUI( class'MMOUIManager'.default.Panel_WorldMap );
	
//}

//世界地图
native function ASClickToWorldMap( int tileIdx, int mapID, string regionName );
native function ASClickToBack( GfxObject fromMc, GfxObject toBackMc );
native function ASClickToNewWorld( GfxObject fromMc, GfxObject toNewMc );

native function ASShowTipsUnitedMapTile( GfxObject fromMc, int mapID, string regionName, string displayMapName );
native function ASHideTipsUnitedMapTile();
native function ASToggleShowUnitedMapTileLevel( bool isToShow );
//End
DefaultProperties
{
	MovieInfoStr="UI_WorldMap.WorldMap"
	Priority=5
}
