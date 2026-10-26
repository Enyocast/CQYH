package ActionScript3.RankList
{
	import flash.text.TextField;

	public class PersonPageLevel extends BasePersonPage
	{
		public const rlType:int = 0;
		public var maxlevel:TextField;
		
		override protected function configUI():void
		{
			super.configUI();
		}
		
		override public function clear():void
		{//还原数据
		    category0_btn_mc.selected=true;
			super.clear();
		}
		
		public function SetMaxLevel(lv:String):void
		{
			maxlevel.htmlText = lv;
		}
	}

}