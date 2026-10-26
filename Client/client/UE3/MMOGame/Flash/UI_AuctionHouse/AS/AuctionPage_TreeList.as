package UI_AuctionHouse.AS
{
	import flash.display.MovieClip;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.external.ExternalInterface;
	import flash.text.TextField;
	
	import ActionScript3.MyPanel;
	import ActionScript3.TreeListData;
	import ActionScript3.Common.MoneyInputNew;
	import ActionScript3.Common.Events.ParamEvent;
	import ActionScript3.Slot.ItemSlotData;
	import ActionScript3.controls.ListItemHeader;
	
	import UI_AuctionHouse.AS.AuctionItemData;
	import UI_AuctionHouse.AS.AuctionListItem_TreeView;
	
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

	public class AuctionPage_TreeList extends UIComponent
	{
		public var item_tree_list:ScrollingList;
		public var last_selected:AuctionListItem_TreeView;
		
		public var arr_orange:Array;
		
		public function AuctionPage_TreeList()
		{
			// constructor code
		}
		
		public function LOG(info:String):void
		{
			(parent as AuctionPage_View).LOG(info);
		}

		override protected function configUI():void
		{
			super.configUI();
			item_tree_list.addEventListener(ListEvent.ITEM_CLICK, onTreeListItemClick, false, 0, true);
			last_selected = null;
			LOG("AuctionPage_TreeList configUI");
		}
		
		public function UCUpdateTreeList(dat:Array):void
		{
			var array:Array = sortArray(dat);
			LOG("UCUpdateTreeList: " + dat.length);
			//dat.sortOn("ItemColor", Array.NUMERIC);
			item_tree_list.dataProvider = new DataProvider(array);
			item_tree_list.validateNow();
			item_tree_list.invalidateData();
		}
		
		public function onTreeListItemClick(event:ListEvent):void
		{
			var list:ScrollingList = event.target as ScrollingList;
			
			if (list != null)
			{
				var provider:DataProvider = list.dataProvider as DataProvider;
				if (provider!=null)
				{
					var obj:AuctionItemData = provider.requestItemAt(event.index) as AuctionItemData;
					ExternalInterface.call( "ASTreeListPage_ClickItem", obj.AuctionID);
				}
			}
			
			
			if(last_selected != null)
			{
				last_selected.selected = false;
			}
			event.itemRenderer.selected = true;
			last_selected = (AuctionListItem_TreeView)(event.itemRenderer);
			
		}
		
		public function sortArray(dat:Array):Array
		{
			//dat.sortOn(["ItemColor","ItemLevel"],[Array.DESCENDING,Array.NUMERIC]);
			var arr_wihte:Array = new Array();
			var arr_green:Array = new Array();
			var arr_blue:Array = new Array();
			var arr_purple:Array = new Array();
			var arr_orange:Array = new Array();
			
			for(var i:int=0; i<dat.length;i++)
			{
				var item:AuctionItemData = dat[i];
				switch(item.ItemColor)
				{
				case 0: //白
					arr_wihte.push(item);
					break;
				case 1: //绿
					arr_green.push(item);
					break;
				case 2: //蓝
					arr_blue.push(item);
					break;
				case 3: //紫
					arr_purple.push(item);
					break;
				case 4: //橙
					arr_orange.push(item);
					break;
				}
			}
		
			dat = new Array();
			sortByLevel(arr_orange,dat);
			sortByLevel(arr_purple,dat);
			sortByLevel(arr_blue,dat);
			sortByLevel(arr_green,dat);
			sortByLevel(arr_wihte,dat);
			
			return dat;
		}
		
		public function sortByLevel(dat:Array,datSource:Array):void
		{
			dat.sortOn("ItemLevel",Array.DESCENDING|Array.NUMERIC);
			
			for(var i:int=0; i<dat.length; i++)
			{
				datSource.push(dat[i]);
			}
		}
		
		
	}

}