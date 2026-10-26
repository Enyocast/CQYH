package ActionScript3.Option {
	
	import flash.display.MovieClip;
	import flash.external.ExternalInterface;
	import flash.text.TextField;
	
	import UI_AuctionHouse.AS.AuctionItemData;
	
	import UI_Minimap.MinimapAS3.SceneLinesDropDownListData;
	
	import scaleform.clik.controls.Button;
	import scaleform.clik.controls.ScrollingList;
	import scaleform.clik.core.UIComponent;
	import scaleform.clik.data.DataProvider;
	import scaleform.clik.data.TreeDataProvider;
	import scaleform.clik.events.ListEvent;
	import flash.events.MouseEvent;
	
	public class LineMenu extends UIComponent {
		
		public var _bg:MovieClip;
		public var mapTitle:TextField;
		public var list:ScrollingList;
        public var btn_close:Button;
		override protected function configUI():void 
		{
			super.configUI();
			btn_close.addEventListener(MouseEvent.CLICK,closeHandler);
		}
		
		private function closeHandler(evt:MouseEvent):void
		{
			this.visible=false;
		}
		
		public function updateLine(mapName:String,dat:Array):void
		{
			mapTitle.text=mapName;
			list.dataProvider = new DataProvider(dat);
			list.invalidateData();
			list.validateNow();
			
			var l:int=dat.length-1;
			list.height=(l+1)*38
			_bg.height+=l*38;
		}
	}
	
}
