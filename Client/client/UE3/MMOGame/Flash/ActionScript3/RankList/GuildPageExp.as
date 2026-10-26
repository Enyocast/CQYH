package ActionScript3.RankList
{
	import flash.text.TextField;

	public class GuildPageExp extends BaseGuildPage
	{
		private const rlTotalKillCount:int = 50;
		
		override protected function configUI():void
		{
			super.configUI();
			(tabTitle.getChildByName("tf_dec") as TextField).text="经验获取";
		}
		
		override public function UpdateGuildListData( dat:Array ):void
		{
			var type:int = dat[0] as int;
			if(rlTotalKillCount == type)
			{
				dat.shift();
				visible = true;
			}
			else
			{
				visible = false;
			}
			super.UpdateGuildListData(dat);
			
		}
	}

}