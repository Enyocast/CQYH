package UI_GoldStore.AS 
{
	import flash.display.MovieClip;
	import flash.events.Event;
	import flash.events.FocusEvent;
	import flash.events.MouseEvent;
	import flash.external.ExternalInterface;
	import flash.text.TextField;
	
	import ActionScript3.MoneyIcon;
	import ActionScript3.MoneyInput;
	import ActionScript3.MoneyInput_Event;
	import ActionScript3.MyPanel;
	import ActionScript3.TreeListData;
	import ActionScript3.Common.MoneyInput_Coupon;
	import ActionScript3.Common.Events.ParamEvent;
	import ActionScript3.Slot.ItemSlotData;
	import ActionScript3.UndergroundTrade.SearchPanel;
	import ActionScript3.controls.ListItemHeader;
	
	import UI_GoldStore.AS.GoldStoreListItem_Control;
	import UI_GoldStore.AS.SellInfoData;
	
	import scaleform.clik.controls.Button;
	import scaleform.clik.controls.CheckBox;
	import scaleform.clik.controls.DropdownMenu;
	import scaleform.clik.controls.RadioButton;
	import scaleform.clik.controls.ScrollingList;
	import scaleform.clik.controls.TextInput;
	import scaleform.clik.core.UIComponent;
	import scaleform.clik.data.DataProvider;
	import scaleform.clik.data.TreeDataProvider;
	import scaleform.clik.events.ListEvent;
	import scaleform.clik.interfaces.IDataProvider;
	
	
	public class PageTotal_SellInfo extends UIComponent 
	{			
		public var item_list:ScrollingList;
		public var hdr_item_unitPrice:Button;
		public var hdr_item_price:Button;
		public var hdr_item_time:Button;
		 
		public var txt_label1:TextField;
		public var txt_label2:TextField;
		public var txt_label3:TextField;
		
		var itemControl:GoldStoreListItem_Control;
		
		override protected function configUI():void
		{
			itemControl = new GoldStoreListItem_Control(item_list);
			itemControl.updateGoldStoreItemListData(null);
		}
		
		public function PageTotal_SellInfo() 
		{
			// constructor code
		}

		//for cancel action
		public function getSelectedItemData():GoldStoreItemData
		{
			var dp:DataProvider = item_list.dataProvider as DataProvider;
			if(dp != null){
				var selectedIndex:int = item_list.selectedIndex;
				if(selectedIndex >=0 && selectedIndex < dp.length){
					return dp[selectedIndex] as GoldStoreItemData;
				}
			}
			return null;
		}
		
		public function setListTitle(lableStr1:String, lableStr2:String, lableStr3:String):void
		{
			txt_label1 && (txt_label1.text = lableStr1);
			txt_label2 && (txt_label2.text = lableStr2);
			txt_label3 && (txt_label3.text = lableStr3);
		}
		
	}
	
}
