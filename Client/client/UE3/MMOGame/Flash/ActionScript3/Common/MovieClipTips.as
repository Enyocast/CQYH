package ActionScript3.Common {
	import flash.display.MovieClip;
	import flash.events.MouseEvent;
	import flash.external.ExternalInterface;
	
	public class MovieClipTips extends MovieClip {

		public function MovieClipTips() {
			this.addEventListener( MouseEvent.ROLL_OVER, ShowTips);
			this.addEventListener( MouseEvent.ROLL_OUT, HideTips);
		}
		
		private function ShowTips(e:MouseEvent):void
		{
			ExternalInterface.call("ASShowTips_Tab", this);
			//this["root"].ChangeTips();
		}
		
		private function HideTips(e:MouseEvent):void
		{
			ExternalInterface.call("ASHideTips_Tab", this);
			//trace("hidetips");
			//this["root"].tooltips_mc.visible =false;
			
		}

	}
	
}
