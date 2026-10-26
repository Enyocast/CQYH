package ActionScript3.RankList
{
	import flash.text.TextField;

	public class GuildPageLevel extends BaseGuildPage
	{
		private const rlGuild_Level:int = 21;
		
		override public function UpdateGuildListData( dat:Array ):void
		{
			var type:int = dat[0] as int;
			if(rlGuild_Level == type)
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