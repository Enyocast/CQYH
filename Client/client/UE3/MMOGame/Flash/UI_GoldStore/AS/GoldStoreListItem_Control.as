package UI_GoldStore.AS
{
	import flash.events.MouseEvent;
	import flash.external.ExternalInterface;
	
	import ActionScript3.Slot.ItemSlotData;
	
	import UI_GoldStore.AS.GoldStoreItemData;
	
	import scaleform.clik.controls.Button;
	import scaleform.clik.controls.ScrollingList;
	import scaleform.clik.data.DataProvider;
	import scaleform.clik.events.ListEvent;
	
	public class GoldStoreListItem_Control extends Object 
	{				
		protected var _list_view:ScrollingList;

		public function GoldStoreListItem_Control(listView:ScrollingList)
		{
			_list_view = listView;
			if(_list_view != null)
			{
				_list_view.dataProvider = new DataProvider();
			}
		}
		
		public function updateGoldStoreItemListData( data:Array ):void
		{
			if(_list_view == null)
			{
				return;
			}
			var dp:DataProvider = (_list_view.dataProvider as DataProvider);
			if(dp != null)
			{
				dp.cleanUp();
				dp.setSource(data);
				_list_view.dataProvider = dp;
				_list_view.validateNow();
				_list_view.invalidateData();
			}
		}
	}
}
