package ActionScript3.RankList
{
	import scaleform.clik.controls.ListItemTreeRenderer;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.text.TextField;
	
	public class ListItemGuild extends ListItemTreeRenderer 
	{
		public var rankindex_txt_mc:TextField;
		public var guildname_txt_mc:TextField;
		public var guildername_txt_mc:TextField;
		public var guildnum_txt_mc:TextField;
		public var guildcontribute_txt_mc:TextField;
		public var guildlevel_txt_mc:TextField;
		public var GuildData:ListItemGuildData;
		
		public function ListItemGuild()
		{
			// constructor code
		}
		
		override protected function configUI():void
		{
			super.configUI();
			setUpdateDataCallBack(UpdateData);
		}
		
		function UpdateData(data:Object):void
		{
			GuildData = data as ListItemGuildData;
			if(null != GuildData)
			{
				rankindex_txt_mc.text = GuildData.RankIndex;
				guildname_txt_mc.text = GuildData.GuildName;
				guildername_txt_mc.text = GuildData.GuilderName;
				guildnum_txt_mc.text = GuildData.GuildNum;
				guildcontribute_txt_mc.text = GuildData.GuildContribute;
				guildlevel_txt_mc.text = GuildData.GuildLevel;
			}
		}
		
	}
	
}
