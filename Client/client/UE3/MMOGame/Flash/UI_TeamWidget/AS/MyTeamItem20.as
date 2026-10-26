package UI_TeamWidget.AS {
	
	import scaleform.clik.controls.RadioButton;
	import ActionScript3.Common.Utils.StyleType;
	import flash.text.TextField;
	import flash.display.MovieClip;
	import scaleform.clik.controls.Button;
	
	
	public class MyTeamItem20 extends RadioButton {
		
		public var leaderclass:TextField;
	    public var tag_offline_mc:MovieClip;
		public var team_name:TextField;
		public function MyTeamItem20() {
			leaderclass.visible=false;
			tag_offline_mc.visible=false;
		}
		
        public function updateState(online:Boolean):void
		{
			if(online==true){
				tag_offline_mc.visible=false;
				team_name.textColor=0xffcb71;
			}else{
				tag_offline_mc.visible=true;
				team_name.textColor=0x62605C;
			}
		}
	}
	
}
