package MMO_UI.GameLoading.AS
{

	import ActionScript3.fla.MoviePlayerBase;
	import flash.events.Event;
	import flash.display.StageScaleMode;


	public class MoviePlayer_LoadingWidget extends MoviePlayerBase
	{

		public var bar_mc:LoadingProgressBar;

		public function MoviePlayer_LoadingWidget()
		{
			//constructor
		}

		override protected function configUI():void
		{
			super.configUI();
			stage.scaleMode = StageScaleMode.NO_SCALE;
			stage.align = "TL";
		}
		
		override public function _ReSizeStage(evt:Event):void
		{
			bar_mc.x=0;
			bar_mc.y=0;
			bar_mc.updatePos();
		}
	}

}