package UI_LoginWidget.AS3 {
	
	import ActionScript3.MyPanel;
	import flash.external.ExternalInterface;
	import flash.display.MovieClip;
	import ActionScript3.Common.Events.ParamEvent;
	import flash.events.Event;
	
	public class Logo extends MovieClip {
		
		public function Logo() {
			this.addFrameScript(58,compontHandler);
			this.gotoAndStop(1);
			this.mouseChildren=false;
			this.mouseEnabled=false;
		}
		public function compontHandler():void
		{
			this.gotoAndStop(1);
			this.dispatchEvent(new Event("LogoMovieEnd"));//动画播放完成
            //ExternalInterface.call( "LogoMovieEnd" );
		}
	}
	
}
