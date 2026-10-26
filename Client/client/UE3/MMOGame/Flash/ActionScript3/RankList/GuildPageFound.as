package ActionScript3.RankList
{
	import flash.text.TextField;

	public class GuildPageFound extends BaseGuildPage
	{
		private const rlGuild_Money:int = 22;

		override public function UpdateGuildListData( dat:Array ):void
		{
			var type:int = dat[0] as int;
			if(rlGuild_Money == type)
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