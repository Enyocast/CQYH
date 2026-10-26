package ActionScript3.RankList
{
	import flash.text.TextField;

	public class PowerPageAmbit extends BasePersonPage
	{
		public var myrank_txt_mc:TextField;
		public const rlType:int = 20;

		override protected function configUI():void
		{
			super.configUI();
            (tabTitle.getChildByName("tf_dec") as TextField).text="总战力值";
		}
	}

}