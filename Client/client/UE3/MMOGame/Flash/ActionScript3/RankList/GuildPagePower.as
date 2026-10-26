package ActionScript3.RankList
{
	import flash.text.TextField;

	public class GuildPagePower extends BaseGuildPage
	{
		private const rlGuild_Power:int = 27;

		override public function UpdateGuildListData( dat:Array ):void
		{
			var type:int = dat[0] as int;
			if(rlGuild_Power == type)
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