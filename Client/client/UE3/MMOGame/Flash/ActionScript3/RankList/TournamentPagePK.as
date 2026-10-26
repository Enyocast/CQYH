package ActionScript3.RankList
{
	import scaleform.clik.controls.ScrollingList;
	import scaleform.clik.data.DataProvider;
	import flash.text.TextField;
	
	public class TournamentPagePK extends BasePersonPage
	{
		public var pk_list_mc:ScrollingList;
		private const rlPkValue:int = 35;
		public var myrank_txt_mc:TextField;

		override protected function configUI():void
		{
			super.configUI();
			(tabTitle.getChildByName("tf_dec") as TextField).text="PK值";
		}
		
		public function UpdateTournamentListData( data:Array ):void
		{
			if(visible && null != data)
			{
				pk_list_mc.dataProvider = new DataProvider(data);
				pk_list_mc.validateNow();
				pk_list_mc.invalidateData();
			}
		}
	}

}