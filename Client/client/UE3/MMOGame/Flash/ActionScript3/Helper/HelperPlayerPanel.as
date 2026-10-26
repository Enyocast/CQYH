package ActionScript3.Helper
{
	import ActionScript3.MyPanel;
	import flash.external.ExternalInterface;
	import flash.events.MouseEvent;
	import flash.display.MovieClip;

	public class HelperPlayerPanel extends MyPanel
	{
		public var player_head_mc:MovieClip;
		//public var player_picture_mc:MovieClip;
		public var player_play_mc:MovieClip;
		public var player_pause_mc:MovieClip;
		
		public function HelperPlayerPanel()
		{
			// constructor code
		}

		override protected function configUI():void
		{
			super.configUI();
			//ExternalInterface.call("ASRegisterHelperPlayerPanel", this);			
			
			player_play_mc.addEventListener(MouseEvent.CLICK, onBtClickPlay);
			player_pause_mc.addEventListener(MouseEvent.CLICK, onBtClickPause);
		}
		
		public function onBtClickPlay(evt:MouseEvent):void
		{
			ExternalInterface.call("ASPlayHelperSound");			
		}
		
		public function onBtClickPause(evt:MouseEvent):void
		{
			ExternalInterface.call("ASPauseHelperSound");			
		}
		
		public function UCUpdateHelperSoundData(data:Object):void
		{
			if (data)
			{
				player_head_mc.source = data.player_head_icon;
				//player_picture_mc.source = data.player_picture;
				player_play_mc.visible = !data.player_is_playing;
				player_pause_mc.visible = data.player_is_playing;
			}
		}
		public function UCSetWindowTitle(title:String):void
		{
			SetWindowTitle(title);
		}
	}
}