package UI_AuctionHouse.AS {
		
	import flash.events.Event;
	import flash.events.FocusEvent;
	import flash.events.MouseEvent;
	import flash.external.ExternalInterface;
	import flash.text.TextField;
	
	import ActionScript3.Common.TextInput_Advanced;
	import ActionScript3.Common.Utils.ConfigConstants;
	
	import scaleform.clik.controls.Button;
	import scaleform.clik.controls.DropdownMenu;
	import scaleform.clik.controls.TextInput;
	import scaleform.clik.core.UIComponent;
	import scaleform.clik.managers.FocusHandler;
	
	public class Auction_SearchPage extends UIComponent
	{
		public var filter_item_name:TextInput_Advanced;
		public var filter_class:DropdownMenu;
		
		public var filter_lv_min:TextInput_Advanced;
		public var filter_lv_max:TextInput_Advanced;
		
		
		//public var filter_item_color:DropdownMenu;
		public var filter_auction_status:DropdownMenu;
		
		public var btn_searchItem:Button;
		
		public static const FILTERTYPE_PROFESSION = 1;
		public static const FILTERTYPE_ITEMCOLOR = 2;
		public static const FILTERTYPE_LEVEL = 3;
		public static const FILTERTYPE_NAME = 4;
		public static const FILTERTYPE_ALL = 5;
		
		protected var _filterType:int;
		
		public function Auction_SearchPage()
		{
			// constructor code
		}
		
		override protected  function configUI():void 
		{		
			super.configUI();
			//restrict"0-9"
			filter_lv_min.textField.restrict = ConfigConstants.RESTRICT_OF_MONEY_INPUT;
			filter_lv_max.textField.restrict = ConfigConstants.RESTRICT_OF_MONEY_INPUT;
			onReset();
			//btn_reset.addEventListener(MouseEvent.CLICK, onReset);
			btn_searchItem.addEventListener(MouseEvent.CLICK,onSearchItem);
			
		//	filter_class.addEventListener(Event.CHANGE,onProfessionListChange);
		//	filter_item_color.addEventListener(Event.CHANGE, onItemColorListChange);
			
		//	filter_lv_min.addEventListener(Event.CHANGE,OnMinLvChange);
		//	filter_lv_max.addEventListener(Event.CHANGE,OnMaxLvChange);
			
		//	filter_item_name.addEventListener(Event.CHANGE,OnNameChange);
			
			//Test();
		}
		
		public function onSearch():void
		{
			ExternalInterface.call("ASSearch", getCurrentFilterData());
		}
		
		public function onReset():void
		{
			var dat:SearchFilterData  = new SearchFilterData();
			DefaultFillData(dat);
			
			UCSetFilterData(dat);
			
			ExternalInterface.call("ASSearch_ResetFilter");
			dispatchEvent(new Event_Search(Event_Search.RESET));
		}
		
		public function getCurrentFilterData():SearchFilterData
		{
			var dat:SearchFilterData  = new SearchFilterData();
			dat.item_name = filter_item_name.text;
			dat.player_class_idx = filter_class.selectedIndex;
			
			dat.lv_max = parseInt(filter_lv_max.text);
			dat.lv_min = parseInt(filter_lv_min.text);
			
			//eidt by wph:传奇版本中装备没有颜色之分 ，保留数据接口，使用默认值0
			//dat.item_color_idx = filter_item_color.selectedIndex - 1;
			//dat.auction_status = filter_auction_status.selectedIndex;
			
			return dat;
		}
		
		public function UCSetFilterData(dat:SearchFilterData):void
		{
			filter_item_name.text = dat.item_name;
						
			filter_class.dataList = dat.player_class_list;
			filter_class.SplitData();
			filter_class.selectedIndex = dat.player_class_idx;
			
			filter_lv_min.text = dat.lv_min.toString();
			filter_lv_max.text = dat.lv_max.toString();
			
			//eidt by wph:传奇版本中装备没有颜色之分 
//			filter_item_color.dataList = dat.item_color_list;
//			filter_item_color.SplitData();
//			filter_item_color.selectedIndex = dat.item_color_idx;
			
			filter_auction_status.dataList = dat.auction_status_list;
			filter_auction_status.SplitData();
			filter_auction_status.selectedIndex = dat.auction_status;			
		}
		
		public function DefaultFillData(dat:SearchFilterData)
		{			
			dat.item_name = "";
			dat.player_class_list.push("所有职业");
			dat.player_class_list.push("战士");
			dat.player_class_list.push("法师");
			dat.player_class_list.push("道士");
			//dat.player_class_list.push("弓手");
			
			// 保持和DefaultUIColor.ini中的道具品质色一致的顺序和颜色值
			dat.item_color_list.push("所有品质");			
			dat.item_color_list.push("<font color='#F2FBFF'>白品</font>");
			dat.item_color_list.push("<font color='#1EFF00'>绿品</font>");
			dat.item_color_list.push("<font color='#0070DD'>蓝品</font>");
			dat.item_color_list.push("<font color='#A335EE'>紫品</font>");
			dat.item_color_list.push("<font color='#FF8000'>橙品</font>");
			dat.auction_status_list.push("所有状态");
			dat.auction_status_list.push("已出价");
			dat.auction_status_list.push("未出价");
		}
		
		public function Test()
		{
			if(1)
			{
				var dat:SearchFilterData = new SearchFilterData();
				DefaultFillData(dat);
				
				dat.item_name = "什么样的武器才够厉害";
				dat.auction_status = 1;
				dat.item_color_idx = 2;				
				dat.player_class_idx = 3;
				dat.lv_max = 88;
				dat.lv_min = 66;
				UCSetFilterData(dat);
			}
		}
		
		public function onSearchItem():void
		{
			ExternalInterface.call("ASAuction_FilterTreeList",FILTERTYPE_ALL,getCurrentFilterData());
		}
		
		public function onProfessionListChange():void
		{
			//ExternalInterface.call("ASTrace", "------------------------------------onProfessionListChange:" + filter_class.selectedIndex);
			ExternalInterface.call("ASAuction_FilterTreeList",FILTERTYPE_PROFESSION,getCurrentFilterData());
		}
		
		public function onItemColorListChange():void
		{
			//ExternalInterface.call("ASTrace", "------------------------------------onItemColorListChange:" + filter_class.selectedIndex);
			ExternalInterface.call("ASAuction_FilterTreeList",FILTERTYPE_ITEMCOLOR,getCurrentFilterData());
		}
		
		public function OnMinLvChange():void
		{
			//ExternalInterface.call("ASTrace", "------------------------------------OnMinLvChange:" + filter_class.selectedIndex);
			ExternalInterface.call("ASAuction_FilterTreeList",FILTERTYPE_LEVEL,getCurrentFilterData());
		}
		
		public function OnMaxLvChange():void
		{
			//ExternalInterface.call("ASTrace", "------------------------------------OnMinLvChange:" + filter_class.selectedIndex);
			ExternalInterface.call("ASAuction_FilterTreeList",FILTERTYPE_LEVEL,getCurrentFilterData());
		}
		
		public function OnNameChange():void
		{
			ExternalInterface.call("ASAuction_FilterTreeList",FILTERTYPE_NAME,getCurrentFilterData());
		}
		
	}
	
}
