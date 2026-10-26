package UI_VIP.AS3 {
	import scaleform.clik.controls.ScrollingList;
	import scaleform.clik.data.DataProvider;
	
	public class VIPItem extends Object{
        protected var _list_view:ScrollingList;
		public function VIPItem(listView:ScrollingList) {
			
			 _list_view = listView;
			//updateListData(createTestItemList());
		}
		
		public function createTestItemList():Array
		{					
			var itemsData:Array = new Array();
			for (var i:int = 1; i < 30; i++)
			{
				var dat:VipItemData = new VipItemData();
				dat.Vipname = "VIP"+i.toString();
				dat.silver = i+"100";
				dat.gold = i+"1";
				dat.diamond=i+"30";
				itemsData.push(dat);
			}
			return itemsData;
		}
		
		public function updateListData( data:Array ):void
		{
			_list_view.dataProvider = new DataProvider(data);
			_list_view.validateNow();
			_list_view.invalidateData();
		}

	}
	
}
