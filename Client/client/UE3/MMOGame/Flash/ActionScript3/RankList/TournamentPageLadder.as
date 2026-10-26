package ActionScript3.RankList
{
	import scaleform.clik.controls.ScrollingList;
	import scaleform.clik.data.DataProvider;
	import flash.text.TextField;
	
	public class TournamentPageLadder extends BasePersonPage
	{
		public var ladder_list_mc:ScrollingList;
		private const rlRoleArenaScore:int = 34;
		public var myrank_txt_mc:TextField;
		override protected function configUI():void
		{
			super.configUI();
			(tabTitle.getChildByName("tf_dec") as TextField).text="天梯积分";
		}
		
		public function UpdateTournamentListData( data:Array ):void
		{
			if(visible && null != data)
			{
				ladder_list_mc.dataProvider = new DataProvider(data);
				ladder_list_mc.validateNow();
				ladder_list_mc.invalidateData();
			}
		}
	}

}