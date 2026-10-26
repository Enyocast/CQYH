package ActionScript3.RankList
{
	import scaleform.clik.controls.Button;
	import scaleform.clik.controls.ScrollingList;
	import scaleform.clik.data.DataProvider;
	import flash.text.TextField;
	
	public class TournamentPageKill extends BasePersonPage
	{
		public var kill_list_mc:ScrollingList;
		private const rlTotalKillCount:int = 36;
		public var myrank_txt_mc:TextField;
		override protected function configUI():void
		{
			super.configUI();
			(tabTitle.getChildByName("tf_dec") as TextField).text="杀人数";
		}
		
		public function UpdateTournamentListData( data:Array ):void
		{
			if(visible && null != data)
			{
				kill_list_mc.dataProvider = new DataProvider(data);
				kill_list_mc.validateNow();
				kill_list_mc.invalidateData();
			}
		}
		
	}

}