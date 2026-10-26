package ActionScript3.SceneHint {
	
	import flash.display.MovieClip;
	import scaleform.clik.core.UIComponent;
	import flash.text.TextField;
	
	
	public class GuildLeaderName extends UIComponent {
		
		public var tf_guildName:TextField;
		public var tf_leader:TextField;
		override protected function configUI():void
		{
			super.configUI();
			clear();
			mouseChildren = false;
		}
		
		public function updateData(playerName:String,guildName:String):void
		{
			this.visible=true;
			tf_guildName.text=guildName;
			tf_leader.text=playerName;
		}
		
		public function clear():void
		{
			this.mouseChildren=false;
			this.mouseEnabled=false;
		    this.visible=false;
			tf_guildName.text="";
			tf_leader.text="";
		}
	}
	
}
