package ActionScript3.RankList
{
	import flash.text.TextField;

	public class PersonPageKill extends BasePersonPage
	{
		public const rlType:int = 16;
		
		override protected function configUI():void
		{
			super.configUI();
            (tabTitle.getChildByName("tf_dec") as TextField).text="杀人数";
		}
		
	}

}