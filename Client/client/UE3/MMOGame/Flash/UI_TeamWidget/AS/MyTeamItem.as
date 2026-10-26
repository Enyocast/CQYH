package UI_TeamWidget.AS {

	import scaleform.clik.controls.RadioButton;
	import ActionScript3.Common.Utils.StyleType;
	import flash.text.TextField;
	import flash.display.MovieClip;
	
	public class MyTeamItem extends RadioButton {
		
		public var leaderclass:TextField;
		public var mc_line:MovieClip;
		public var team_name:TextField;
		//public var leaderlv:TextField;
		public var tF_offline:TextField;
		public function MyTeamItem() {
			leaderclass.visible=false;
			mc_line.visible=false;
		}
		
        public function updateState(online:Boolean):void
		{
			if(online==true){
				mc_line.visible=false;
				team_name.textColor=0xffcb71;
				//leaderlv.textColor=0xFFF5DE;
				tF_offline.textColor=0xFFF5DE;
			}else{
				mc_line.visible=true;
				team_name.textColor=0xffcb71;
				//leaderlv.textColor=0x62605C;
				tF_offline.textColor=0x62605C;
			}
		}
	}
	
}
