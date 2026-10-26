package ActionScript3.RankList
{
	import scaleform.clik.controls.ListItemTreeRenderer;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.text.TextField;
	
	public class ListItemPerson extends ListItemTreeRenderer 
	{
		public var rankindex_txt_mc:TextField;
		public var rolename_txt_mc:TextField;
		public var job_txt_mc:TextField;
		public var guildname_txt_mc:TextField;
		public var level_txt_mc:TextField;
		public var title_txt_mc:TextField;
		public var PersonData:ListItemPersonData;
		
		public function ListItemPerson()
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
			PersonData = data as ListItemPersonData;
			if(null != PersonData)
			{
				rankindex_txt_mc.text = PersonData.RankIndex;
				rolename_txt_mc.text = PersonData.RoleName;
				job_txt_mc.text = PersonData.Job;
				guildname_txt_mc.text = PersonData.GuildName;
				level_txt_mc.text = PersonData.Level;
				title_txt_mc.text = PersonData.Title;
			}
		}
		
	}
	
}
