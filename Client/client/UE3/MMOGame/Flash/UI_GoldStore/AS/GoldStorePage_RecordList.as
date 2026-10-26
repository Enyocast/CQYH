package UI_GoldStore.AS
{
	import scaleform.clik.controls.ScrollingList;
	import scaleform.clik.core.UIComponent;
	import scaleform.clik.data.DataProvider;
	import flash.text.TextField;
	
	public class GoldStorePage_RecordList extends UIComponent
	{
		public var item_list:ScrollingList;
		private var _listData:DataProvider;
		public var txt_description:TextField;
		
		public function GoldStorePage_RecordList()
		{
			super();
		}
		
		override protected function configUI():void
		{
			super.configUI();
			_listData = new DataProvider();
		}
		
		public function UCSetGoldStore_RecordList(dat:Array):void
		{
			if(dat == null || dat.length == 0)
			{
				return;
			}
			dat.reverse();
			_listData.cleanUp();
			_listData.setSource(dat);
			item_list.dataProvider = _listData;
			item_list.validateNow();
			item_list.invalidateData();
		}
		
		public function UCSetGoldStore_RecordList_Text(str:String)
		{
			txt_description.text = str;
		}
	}
}