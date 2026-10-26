package UI_UnitedMap.UnitedMapAS3
{
	import flash.external.ExternalInterface;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import scaleform.gfx.MouseEventEx;
	import UI_UnitedMap.UnitedMapAS3.UnitedMapTileEvent;
	
	import scaleform.clik.core.UIComponent;
	import UI_UnitedMap.UnitedMapAS3.UnitedMapTile;
	import scaleform.clik.controls.Button;
	import flash.display.MovieClip;
	
	public class UnitedMapTilesContainer extends UIComponent
	{
		public var LastUnitedMapTilesContainer:UnitedMapTilesContainer;
		//public var M1000002_0:UnitedMapTile;
		public var EventReceiverBtn:Button;
		
		override protected function configUI():void 
		{
			super.configUI();
			
			mouseChildren = true;
			
			//
			var mapTileMc:UnitedMapTile;
			var mapTileAnim:MovieClip;
			var mapIDStrIdx:int;
			var mapIDStr:String;
			for( var i:int = numChildren - 1; i >= 0; --i ){
				mapTileMc = getChildAt( i ) as UnitedMapTile;
				
				if( mapTileMc == null ){
					continue;
				}
				mapTileMc.addEventListener( UnitedMapTileEvent.MAP_TILE_EVENT, onClickMapTileContainer );
				
				mapIDStrIdx = mapTileMc.name.lastIndexOf( "_" );
				mapIDStr = mapTileMc.name.substr( 1, mapIDStrIdx - 1 );
				mapTileMc.MapID = int( mapIDStr );
				
				mapTileMc.MapRegionName = "MMOVolume_MapSize_";
				mapTileMc.MapRegionName += mapTileMc.name.substr( mapIDStrIdx + 1, mapTileMc.name.length );
				//trace( ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>mapTileMapID:", mapTileMc.MapID, mapTileMc.MapRegionName );
				
				mapTileMc.Index = i;
				
				//
				var animMcName = "A" + mapTileMc.name;
				mapTileAnim = getChildByName( animMcName ) as MovieClip;
				//trace( ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>animMcName:", animMcName, "mapTileAnim:", mapTileAnim );
				mapTileMc.ShowMovieClip = mapTileAnim;
			}
			
			//
			EventReceiverBtn.addEventListener( MouseEvent.CLICK, onClickMapTileContainer, false, 0, true);
		}
		
		//
		function onClickMapTileContainer( evt:Event )
		{
			var mouseIdx:int = -1;
			var userIdx:int = -1;
			if( evt is MouseEventEx ){
				var mouseEventEx:MouseEventEx = evt as MouseEventEx;
				mouseIdx = mouseEventEx.buttonIdx;
			}
			else if( evt is UnitedMapTileEvent ){
				var mapTileEvt:UnitedMapTileEvent = evt as UnitedMapTileEvent;
				mouseIdx = mapTileEvt.EvtUserData.ButtonEvtIdx;
				userIdx = mapTileEvt.EvtUserData.ContainerID;
			}
			else{
				return;
			}
			
			
			//
			if( mouseIdx == MouseEventEx.RIGHT_BUTTON ){
				if( LastUnitedMapTilesContainer ){
					ExternalInterface.call( "ASClickToBack", this, LastUnitedMapTilesContainer );

					//test
					LastUnitedMapTilesContainer.visible = true;
					this.visible = false;
				}
			}
			else if( mouseIdx == MouseEventEx.LEFT_BUTTON ){
				var mapTileContainer:UnitedMapTilesContainer = parent.getChildByName( "TilesContainerMc" + userIdx ) as UnitedMapTilesContainer;
				//trace( ">>>>>>>>>>>>>>>>>>>", mapTileContainer, userIdx );
				ExternalInterface.call( "ASClickToNewWorld", this, mapTileContainer );

				//test
				mapTileContainer.visible = true;
				this.visible = false;
			}
		}
		//==========================================================================================
		public function FindMapTile( mapID:int, mapRegionName:String ):UnitedMapTile
		{
			var mapTileMc:UnitedMapTile;
			for( var i:int = numChildren - 1; i >= 0; --i ){
				mapTileMc = getChildAt( i ) as UnitedMapTile;
				
				if( mapTileMc == null ){
					continue;
				}
				
				if( mapID != mapTileMc.MapID ){
					continue;
				}
				
				if( mapRegionName == mapTileMc.MapRegionName ){
					return mapTileMc;
					break;
				}
			}
			
			return null;
		}
		//==========================================================================================
		public function HighlightMapTile( mapID:int, mapRegionName:String, isHighlight:Boolean ):Boolean
		{
			var mapTile:UnitedMapTile = FindMapTile( mapID, mapRegionName );
			if( mapTile ){
				mapTile.selected = isHighlight;
				return true;
			}
			
			return false;
		}
	}
}