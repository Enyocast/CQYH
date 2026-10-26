package UI_UnitedMap.UnitedMapAS3
{
	import flash.external.ExternalInterface;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import scaleform.gfx.MouseEventEx;
	import UI_UnitedMap.UnitedMapAS3.UnitedMapTileEvent;
	
	import scaleform.clik.core.UIComponent;
	import ActionScript3.LinkShowButton
	import flash.display.MovieClip;
	
	public class UnitedMapTile extends LinkShowButton
	{
		[Inspectable(type="int", name="SetTileIndex")] 
		public var Index:int;
		
		[Inspectable(type="int", name="SetMapID")] 
		public var MapID:int;
		
		//public var MapRegionID:int;
		[Inspectable(type="String", name="SetMapRegionName")] 
		public var MapRegionName:String;
		
		//
		public var NextLinkBtn:LinkShowButton;
		override protected function configUI():void 
		{
			super.configUI();
			
			addEventListener( MouseEvent.CLICK, onClickMapTile, false, 0, true);
		}
		//==========================================================================================
		/*
		override public function set selected(value:Boolean):void 
		{
			super.selected = value;
			
			//
			if( LastUnitedMapTile != null ){
				LastUnitedMapTile.selected = value;
			}
		}
		*/
		//==========================================================================================
		public function InitMapTileData( index:int, mapID:int, mapRegionName:String )
		{
			Index = index;
			MapID = mapID;
			//MapRegionID = mapRegionID;
			MapRegionName = mapRegionName;
		}
		//==========================================================================================
		function onClickMapTile( evt:Event )
		{
			var mouseEvt:MouseEventEx = evt as MouseEventEx;
			if( mouseEvt == null ){
				return;
			}
			var dat:Object={};
			
			if( mouseEvt.buttonIdx == MouseEventEx.LEFT_BUTTON ){
				if( MapID < 1000000 ){
					ExternalInterface.call( "ASClickToWorldMap", Index, MapID, MapRegionName );
				}
				else{
					dat={ ButtonEvtIdx: MouseEventEx.LEFT_BUTTON, ContainerID:MapID - 1000000 };
					dispatchEvent( new UnitedMapTileEvent( UnitedMapTileEvent.MAP_TILE_EVENT, dat ) );
				}
			}
			else if( mouseEvt.buttonIdx == MouseEventEx.RIGHT_BUTTON ){
				dat={ ButtonEvtIdx: MouseEventEx.RIGHT_BUTTON };
				dispatchEvent( new UnitedMapTileEvent( UnitedMapTileEvent.MAP_TILE_EVENT, dat ) );
			}
		}
	}
}