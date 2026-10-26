package ActionScript3.RankList
{
	import scaleform.clik.controls.ScrollingList;
	import scaleform.clik.data.DataProvider;
	import flash.text.TextField;
	
	public class TournamentPageFB extends BasePersonPage
	{
        public var myrank_txt_mc:TextField;
		public var fbsingle_list_mc:ScrollingList;

		private const rlDungeonScore: int = 24;
		
		override protected function configUI():void
		{
			super.configUI();
			(tabTitle.getChildByName("tf_dec") as TextField).text="通关评级";
		}
		
		public function UpdateTournamentListData( data:Array ):void
		{
			if(null != data && visible)
			{
				fbsingle_list_mc.dataProvider = new DataProvider(data);
				fbsingle_list_mc.validateNow();
				fbsingle_list_mc.invalidateData();
			}
		}
	}

}