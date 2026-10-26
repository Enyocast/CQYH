package ActionScript3.PlayerInfoWidget
{
	import ActionScript3.MyPanel;
	import scaleform.clik.controls.Button;
	import flash.display.MovieClip;
	import flash.text.TextField;
	import scaleform.clik.controls.UILoader;

	public class SimplePlayerInfoWidget extends MyPanel
	{
		public var PlayerName_tf:TextField;
		public var Level_tf:TextField;
		public var ClassName_tf:TextField;
		public var Guild_tf:TextField;
		public var MapName_tf:TextField;
		public var Team_tf:TextField;
		public var vipTag:MovieClip;

		public var PlayerIcon:UILoader;

		override protected function configUI():void
		{
			super.configUI();
            MyWindowsFrame_mc.InfoDragButton_mc.visible=false;
			this.SetWindowTitle("玩家信息");
			(MyWindowsFrame_mc.getChildByName("divide") as MovieClip).visible=false;
			//var dat:Object = { IsVip:false , RoleName:"a" , Level:25 , ClassName:"刺客"};
			//UpdatePlayerInfo(dat);
		}

		public function UpdatePlayerInfo(data:Object)
		{
			if(vipTag)
			{
				vipTag.visible = data.IsVip;
			}
			if(PlayerName_tf)
			{
				PlayerName_tf.htmlText = data.RoleName;
			}
			if(Level_tf)
			{
				Level_tf.htmlText = data.Level;
			}
			if(PlayerIcon)
			{
				PlayerIcon.source = data.HeadIcon;
			}
			if(ClassName_tf)
			{
				ClassName_tf.htmlText = data.ClassName;
			}
			if(MapName_tf)
			{
				MapName_tf.htmlText = data.MapName;
			}
			if(Guild_tf)
			{
				Guild_tf.htmlText = data.Guild;
			}
			if(Team_tf)
			{
				Team_tf.htmlText = data.Team;
			}
			
			
		}
		
	}
}