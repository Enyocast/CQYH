package UI_Minimap.MinimapAS3 {
	
	import flash.display.MovieClip;
	import scaleform.clik.core.UIComponent;
	import flash.events.MouseEvent;
	import flash.external.ExternalInterface;
	
	
	public class MapType extends UIComponent {
		
		public var zoneType:int=0;
		override protected  function configUI():void 
		{
			super.configUI();
			this.addEventListener(MouseEvent.ROLL_OVER,overZoneTypeHandler);
			this.addEventListener(MouseEvent.ROLL_OUT,outZoneTypeHandler);
		}
		
		private function overZoneTypeHandler(evt:MouseEvent):void
		{
			ExternalInterface.call("ASShowTips_MapZone",zoneType);
		}
	    private function outZoneTypeHandler(evt:MouseEvent):void
		{
			ExternalInterface.call("ASHideTips_MapZone");
		}
		
		public function SetMapZoneType(dat:int):void
		{
			zoneType=dat;
			this.gotoAndStop(zoneType+1);
		}
	}
	
}
