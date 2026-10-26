package UI_UnitedMap.UnitedMapAS3  {
	import flash.events.Event
	
	public class UnitedMapTileEvent extends Event {
		
		public static const MAP_TILE_EVENT:String="mapTileEvent";
		
		public var EvtUserData:Object;
		
		public function UnitedMapTileEvent( eventName:String, dat:Object )
		{
			EvtUserData = dat;
			
			super( eventName, false, false );
		}

	}
	
}
