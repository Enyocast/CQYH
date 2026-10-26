package ActionScript3.RankList
{
	import scaleform.clik.data.DataProvider;
	import flash.text.TextField;

	public class PersonPageRich extends BasePersonPage
	{
		public const rlType:int = 12;

		override protected function configUI():void
		{
			super.configUI();
			(tabTitle.getChildByName("tf_dec") as TextField).text="金币数量";
		}
	}

}