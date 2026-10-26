package ActionScript3.RankList {
	
	import flash.display.MovieClip;
	import scaleform.clik.core.UIComponent;
	import scaleform.clik.data.DataProvider;
	import flash.text.TextField;
	import scaleform.clik.controls.ScrollingList;
	
	
	public class ActivePageBZ extends UIComponent {
		
		public var tabTitle:MovieClip;
		public var content_list_mc:ScrollingList;
		public const rlType:int = 17;
		override protected function configUI():void
		{
			super.configUI();
            (tabTitle.getChildByName("tf_dec") as TextField).text="英雄帖数";
			
		}
		
		public function UpdateData( dat:Array ):void
		{
			content_list_mc.dataProvider = new DataProvider(dat);
			content_list_mc.validateNow();
			content_list_mc.invalidateData();
		}
	}
	
}
