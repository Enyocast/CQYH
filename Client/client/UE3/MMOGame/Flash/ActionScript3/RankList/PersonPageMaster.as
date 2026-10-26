package ActionScript3.RankList
{
	import flash.text.TextField;

	public class PersonPageMaster extends BasePersonPage
	{
		public const rlType:int = 14; 
		
		override protected function configUI():void
		{
			super.configUI();
			(tabTitle.getChildByName("tf_dec") as TextField).text="名师值";
		}

	}

}