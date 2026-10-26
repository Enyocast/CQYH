package UI_Hurt.HurtAS3  {
	import scaleform.clik.controls.ScrollingList;
	import scaleform.clik.data.DataProvider;
	import flash.events.MouseEvent;
	import scaleform.clik.events.ListEvent;
		
	public class HurtItem extends Object {

		protected var _list_view:ScrollingList;
		
		public function HurtItem(listView:ScrollingList) {
			
			 _list_view = listView;
			updateListData(createTestItemList());
		}
		
		public function createTestItemList():Array
		{					
			var itemsData:Array = new Array();
			for (var i:int = 1; i < 10; i++)
			{
				var dat:HurtItemData = new HurtItemData();
				dat.RankID = i;
				dat.SkillName = "技能名称"+i.toString();
				dat.SkillHurt = i;
				dat.SkillHurtValue = 100+"%";
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



