package UI_Minimap.MinimapAS3 {
	
	import flash.display.MovieClip;
	import flash.external.ExternalInterface;
	
	import scaleform.clik.controls.CoreList;
	import scaleform.clik.controls.DropdownMenu;
	import scaleform.clik.controls.ScrollingList;
	import scaleform.clik.events.ListEvent;
	import flash.events.MouseEvent;
	
	
	public class MapDropdownMenu extends DropdownMenu {
		
		public var mc_line:MovieClip;
		public var index:int=0;
		public var LineState:int=0;
		public function MapDropdownMenu() {
			super();
			mc_line.visible=false;
		}
		
		override protected function handleClick(controllerIndex:uint = 0):void 
		{
			if(!_selected)
			{
				ExternalInterface.call("ASShowMapLineDropList");
			}
			//(parent as MinimapPanel).UCUpdateSceneLinesList(getTestData(), int(4 * Math.random()));
			super.handleClick();
		}
		
		private function getTestData():Array
		{
			var result:Array = [];
			var len:int = 4 +  6 * Math.random();
			var item:SceneLinesDropDownListData;
			for(var i:int = 0; i < len; i++)
			{
				item = new SceneLinesDropDownListData();
				item.label = i.toString() + "线";
				item.lineID = i;
				item.lineState = i % 3;
				result.push(item);
			}
			return result;
		}
		
		override protected function handleMenuItemClick(e:ListEvent):void {
			if( _dropdownRef != null )
			{
				var offset:uint = (_dropdownRef is ScrollingList) ? (_dropdownRef as ScrollingList).scrollPosition : 0;
				dispatchEvent(new ListEvent(ListEvent.ITEM_CLICK, true, false, e.index, 
					-1, -1, (_dropdownRef).getRendererAt(e.index, offset), _dataProvider[e.index]));
			}
			var itemData:SceneLinesDropDownListData = dataProvider.requestItemAt( e.index ) as SceneLinesDropDownListData;
			if( itemData != null )
			{
				LineState=itemData.lineState;
				ExternalInterface.call( "ASChangeSceneLine",  itemData.lineID );
			}
			index=e.index;
			close();
		}
		
		override public function set selectedIndex(value:int):void {
			super.selectedIndex=value;
			updateState(LineState);
		}
		
		public function updateState(str:int):void
		{
			if(str>0){
				mc_line.visible=true;
				mc_line.gotoAndStop(str);
			}else{
				mc_line.visible=false;
			}
			
		}
		
	    private function overHandler(evt:MouseEvent):void
		{
			ExternalInterface.call("ASShowTipsMapItem",this);
		}
		
		private function outHandler(evt:MouseEvent):void
		{
			ExternalInterface.call("ASHideTipsMapItem",this);
		}
	}
	
}
