package ActionScript3.RankList
{
	import flash.text.TextField;

	public class PersonPageExp extends BasePersonPage
	{
		public const rlType:int = 28;
		
		override protected function configUI():void
		{
			super.configUI();
            (tabTitle.getChildByName("tf_dec") as TextField).text="经验获取";
		}
	}

}