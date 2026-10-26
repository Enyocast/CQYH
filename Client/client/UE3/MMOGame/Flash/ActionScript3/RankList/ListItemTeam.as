package ActionScript3.RankList
{
	import scaleform.clik.controls.ListItemTreeRenderer;
	import scaleform.clik.controls.Button;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.text.TextField;
	import flash.external.ExternalInterface;
	
	public class ListItemTeam extends ListItemTreeRenderer 
	{
		public var rankindex_txt_mc:TextField;
		public var teamname_txt_mc:TextField;
		public var result_txt_mc:TextField;
		public var teamername_txt_mc:TextField;
		public var grades_txt_mc:TextField;
		public var config_btn_mc:Button;
		public var teamData:ListItemTeamData;
		
		public function ListItemTeam()
		{
			// constructor code
		}
		
		override protected function configUI():void
		{
			super.configUI();
			//this.mouseChildren = true;
			this.mouseEnabled = true;
			config_btn_mc.addEventListener(MouseEvent.CLICK, OnConfigClick);
			setUpdateDataCallBack(UpdateData);
		}
		
		function UpdateData(data:Object):void
		{
			teamData = data as ListItemTeamData;
			if(null != teamData)
			{
				rankindex_txt_mc.text = teamData.RankIndex;
				teamname_txt_mc.text = teamData.Teamname;
				result_txt_mc.text = teamData.Result;
				teamername_txt_mc.text = teamData.Teamername;
				grades_txt_mc.text = teamData.Grades;
			}
		}
		
		function OnConfigClick()
		{
			ExternalInterface.call( "ASTeamConfigClick");
		}
		
	}
	
}
