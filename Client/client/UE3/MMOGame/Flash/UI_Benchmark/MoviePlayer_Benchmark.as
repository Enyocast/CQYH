package UI_Benchmark
{

	import ActionScript3.fla.MoviePlayerBase;
	import flash.display.StageScaleMode;
	
	public class MoviePlayer_Benchmark extends MoviePlayerBase
	{
		override protected function configUI():void
		{
			trace("----------------MoviePlayer_Benchmark::configUI");
			
			super.configUI();
		}		
	}
	
}