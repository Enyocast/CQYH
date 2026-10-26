package ActionScript3.Guild {
	import ActionScript3.MyPanel;
	import scaleform.clik.controls.Button;
	import flash.events.MouseEvent;
	import flash.display.MovieClip;
	import UI_ChatWidget.AS3.ChatTextField;
	import scaleform.clik.managers.FocusHandler;
	
	public class BaseGuildAlert extends MyPanel {

		public var guild_ok_mc:Button;
		public var guild_cancel_mc:Button;
		
		override protected function configUI():void
		{
			super.configUI();
			(MyWindowsFrame_mc.getChildByName("divide") as MovieClip).y=174;
			btn_close.RemoveAddedEventListener();
			btn_close.addEventListener(MouseEvent.CLICK,onBtClickClose);
			guild_ok_mc.addEventListener(MouseEvent.CLICK,onBtClickOk);
			guild_cancel_mc.addEventListener(MouseEvent.CLICK,onBtClickClose);
		}
		
		protected function onBtClickClose(evt:MouseEvent):void
		{
			FocusHandler.getInstance().setFocus(null);
			this.visible = false;
		}
		
		protected function onBtClickOk(evt:MouseEvent):void
		{

		}
	}
	
}
