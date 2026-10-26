package ActionScript3.RankList
{
	import flash.text.TextField;

	public class PersonPagePower extends BasePersonPage
	{
		public const rlType:int = 6;

		override protected function configUI():void
		{
			super.configUI();
            (tabTitle.getChildByName("tf_dec") as TextField).text="总战力值";
		}
		
		override public function clear():void
		{//还原数据
		    category0_btn_mc.selected=true;
			super.clear();
		}
	}

}