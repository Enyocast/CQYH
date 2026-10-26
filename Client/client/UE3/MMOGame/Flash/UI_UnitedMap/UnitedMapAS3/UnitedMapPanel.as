package UI_UnitedMap.UnitedMapAS3
{
	import flash.external.ExternalInterface;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import scaleform.gfx.MouseEventEx;
	
	import scaleform.clik.core.UIComponent;
	import ActionScript3.MyPanel;
	import UI_UnitedMap.UnitedMapAS3.UnitedMapTile;
	import UI_UnitedMap.UnitedMapAS3.UnitedMapTilesContainer;
	import scaleform.clik.controls.Button;
	import flash.display.MovieClip;
	
	public class UnitedMapPanel extends MyPanel
	{
		public var TilesContainerMc1:UnitedMapTilesContainer;
		public var TilesContainerMc2:UnitedMapTilesContainer;
		
		override protected function configUI():void 
		{
			super.configUI();
			
			//
			TilesContainerMc1.LastUnitedMapTilesContainer = null;
			TilesContainerMc1.visible = true;

			TilesContainerMc2.LastUnitedMapTilesContainer = TilesContainerMc1;
			TilesContainerMc2.visible = false;
			
			//
			ExternalInterface.call( "RegisterUnitedMap", this);
		}
		//==========================================================================================
		public function UCShowMapTile( mapID:int, mapRegionName:String, isHighlight:Boolean )
		{
			TilesContainerMc1.visible = false;
			TilesContainerMc2.visible = false;
			
			var mapTile:UnitedMapTile;
			//
			mapTile = TilesContainerMc1.FindMapTile( mapID, mapRegionName );
			if( mapTile ){
				TilesContainerMc1.visible = true;
				mapTile.selected = isHighlight;
				return;
			}
			
			//
			mapTile = TilesContainerMc2.FindMapTile( mapID, mapRegionName );
			if( mapTile ){
				TilesContainerMc1.visible = true;
				mapTile.selected = isHighlight;
				return;
			}
		}
		//==========================================================================================
		public function UCHighlightMapTile( mapID:int, mapRegionName:String, isHighlight:Boolean )
		{
			var isFound:Boolean = false;
			//
			isFound = TilesContainerMc1.HighlightMapTile( mapID, mapRegionName, isHighlight );
			if( isFound ){
				return;
			}
			
			//
			isFound = TilesContainerMc2.HighlightMapTile( mapID, mapRegionName, isHighlight );
			if( isFound ){
				return;
			}
		}
		//==========================================================================================
		public function UCInitMapTile( tileMc:MovieClip, mapID:int, mapRegionName:String )
		{
			var mapTile:UnitedMapTile = tileMc as UnitedMapTile;
			if( mapTile == null ){
				return;
			}
			
			//
			mapTile.InitMapTileData( mapTile.Index, mapID, mapRegionName );
		}
	}
}