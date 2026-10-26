package ActionScript3.RankList
{
	import flash.text.TextField;

	public class PersonPageAchievement extends BasePersonPage
	{
		public const rlType:int = 13;
		
		override protected function configUI():void
		{
			super.configUI();
            (tabTitle.getChildByName("tf_dec") as TextField).text="成就点数";
		}
	}

}