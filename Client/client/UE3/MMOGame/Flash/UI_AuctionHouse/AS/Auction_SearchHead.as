package UI_AuctionHouse.AS
{
	import flash.events.Event;
	import flash.events.FocusEvent;
	import flash.external.ExternalInterface;
	import flash.text.TextField;
	
	import ActionScript3.Common.TextInput_Advanced;
	import ActionScript3.Common.Utils.ConfigConstants;
	
	import scaleform.clik.controls.DropdownMenu;
	import scaleform.clik.core.UIComponent;
	import scaleform.clik.managers.FocusHandler;
	
	public class Auction_SearchHead extends UIComponent
	{
		public var filter_item_name:TextInput_Advanced;
		
		public static const FILTERTYPE_PROFESSION = 1;
		public static const FILTERTYPE_ITEMCOLOR = 2;
		public static const FILTERTYPE_LEVEL = 3;
		public static const FILTERTYPE_NAME = 4;
		
		public function Auction_SearchHead()
		{
			super();
		}
		
		override protected  function configUI():void 
		{		
			super.configUI();
			onReset();

			filter_item_name.addEventListener(Event.CHANGE,onSearchItem);
		}
		
		public function onSearchItem():void
		{
			ExternalInterface.call("ASAuction_FilterTreeList", FILTERTYPE_NAME, getCurrentFilterData());
		}
		
		public function getCurrentFilterData():SearchFilterData
		{
			var dat:SearchFilterData  = new SearchFilterData();
			dat.item_name = filter_item_name.text;
			dat.item_color_idx = -1;
			return dat;
		}
		
		public function onReset():void
		{
			filter_item_name.text = "";
			ExternalInterface.call("ASSearch_ResetFilter");
			dispatchEvent(new Event_Search(Event_Search.RESET));
		}
		
		public function SetSearchName(name:String):void
		{
			filter_item_name.text = name;
		}
	}
}