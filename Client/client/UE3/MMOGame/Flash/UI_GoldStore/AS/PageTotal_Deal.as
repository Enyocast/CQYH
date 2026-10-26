package UI_GoldStore.AS 
{
	import flash.external.ExternalInterface;
	import ActionScript3.MyPanel;
	import flash.display.MovieClip;
	import scaleform.clik.controls.TextInput;
	import scaleform.clik.controls.DropdownMenu;
	import scaleform.clik.controls.Button;
	import scaleform.clik.controls.ScrollingList;
	import flash.events.MouseEvent;
	import scaleform.clik.events.ListEvent;
	import scaleform.clik.core.UIComponent;
	import flash.events.Event;
	import scaleform.clik.data.DataProvider;
	import scaleform.clik.interfaces.IDataProvider;
	import scaleform.clik.data.TreeDataProvider;
	import ActionScript3.TreeListData;
	import flash.text.TextField;
	import scaleform.clik.controls.RadioButton;
	import ActionScript3.MoneyInput;
	import scaleform.clik.controls.CheckBox;
	import ActionScript3.Slot.ItemSlotData;
	import ActionScript3.UndergroundTrade.SearchPanel;
	import ActionScript3.controls.ListItemHeader;
	import ActionScript3.MoneyInput_Event;
	import flash.events.FocusEvent;
	import ActionScript3.MoneyIcon;
	import UI_GoldStore.AS.GoldStoreListItem_Control;
	import ActionScript3.Common.Events.ParamEvent;
	import ActionScript3.Common.MoneyInput_Coupon;
	import UI_GoldStore.AS.SellInfoData;
	
	
	public class PageTotal_Deal extends UIComponent 
	{			
		public var item_list:ScrollingList;
		
		public var hdr_item_unitPrice:Button;
		public var hdr_item_price:Button;
		
		var itemControl:GoldStoreListItem_Control;
		public var item_title:GoldStore_Title;
		
		override protected function configUI():void
		{

			itemControl = new GoldStoreListItem_Control(item_list);
			itemControl.updateGoldStoreItemListData(null);
			
			item_title.setLabel("出售单价(金币：点券)","订单数量");
			trace("PageTotal_Deal::configUI");
		}
		
		public function PageTotal_Deal() 
		{
			// constructor code
		}
		
		public function getSelectedItemData():GoldStoreItemData
		{
			var dp:DataProvider = item_list.dataProvider as DataProvider;
			if(dp != null){
				var selectedIndex:int = item_list.selectedIndex;
				if(selectedIndex >=0 && selectedIndex < dp.length){
					return dp[selectedIndex];
				}
			}
			return null;
		}
	}
	
}
