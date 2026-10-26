package ActionScript3.MatineeSubtitle
{
	import ActionScript3.fla.MoviePlayerBase;
	import flash.display.MovieClip;
	import flash.text.TextField;
	import flash.external.ExternalInterface;
	

	public class MoviePlayer_MatineeSubtitle extends MoviePlayerBase
	{
		public var _subtiltle_mc:MatineeSubtitlePanel;
		
		override protected function configUI():void
		{
			trace("----------------MoviePlayer_MatineeSubtitle::configUI");
			
			super.configUI();
			
			//UCUpdateSubtitle("<font color='#ffee00'>在经历了一系列的战争之后，世界开始弥漫着血惺大雾……</font>");
		}
		
		public function UCUpdateSubtitle(str:String)
		{
			var mc:MovieClip = this.getChildByName("_subtiltle_mc") as MovieClip;
			var txt:TextField = mc.getChildByName("_subtitle_txt") as TextField;
			txt.htmlText = str;
			ExternalInterface.call("ASTrace", "UCUpdateSubtitle:" + str);
		}
		
		public function UCShow(v:Boolean, scrW:int, scrH:int)
		{
			var mc:MovieClip = this.getChildByName("_subtiltle_mc") as MovieClip;
			mc.visible = v;
			
			if(v)
			{
				var newX:int = (scrW - mc.width) / 2;
				var newY:int = (scrH - mc.height);
				mc.x = newX;
				mc.y = newY;
			}
		}
		
	}
}