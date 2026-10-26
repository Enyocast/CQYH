package UI_StallWidget.AS3
{
	import flash.display.MovieClip;
	
	import scaleform.clik.controls.ScrollingList;
	import scaleform.clik.core.UIComponent;
	import scaleform.clik.data.DataProvider;
	
	public class StallRecordList extends UIComponent
	{
		public var tabTitle:MovieClip;
		public var scrolling_list_mc:ScrollingList;
		
		private var _listDataProvide:DataProvider;
		
		
		public function StallRecordList()
		{
			super();
		}
		
		override protected function configUI():void
		{
			super.configUI();
			_listDataProvide = new DataProvider();
		}
		
		public function updateListData(data:Array):void
		{
			_listDataProvide.cleanUp();
			_listDataProvide.setSource(data); 
			scrolling_list_mc.dataProvider = _listDataProvide;
			scrolling_list_mc.invalidateData();
		}
	}
}