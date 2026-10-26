package ActionScript3.RankList
{
	import flash.text.TextField;

	public class PersonPagePK extends BasePersonPage
	{
		public const rlType:int = 15;

		override protected function configUI():void
		{
			super.configUI();
            (tabTitle.getChildByName("tf_dec") as TextField).text="PK值";
		}
	}

}