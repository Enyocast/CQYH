package UI_GameAnnouncement.AS3 {
	
	import flash.display.MovieClip;
	import ActionScript3.MyPanel;
	import flash.text.TextField;
	import scaleform.clik.controls.Button;
	import flash.events.MouseEvent;
	import flash.external.ExternalInterface;
	
	
	public class GameAnnouncePanel extends MyPanel {
		
		public var txt_dec:TextField;
		public var btn_ok:Button;
		override protected function configUI():void
		{
			ShowMode="BC";
			super.configUI();
			this.SetWindowTitle("更新公告");
			btn_ok.addEventListener(MouseEvent.CLICK,closeHandler);
		}
		
		private function closeHandler(evt:MouseEvent):void
		{
			ExternalInterface.call( "ASOnPanelClose" , this.PanelName );
		}
		
		public function SetAnnouncemmentContent(dat:String):void 
		{
			txt_dec.htmlText=dat;
		}
	}
	
}
