package ActionScript3.Achievement
{

	import ActionScript3.fla.MoviePlayerBase;
	
	public class MoviePlayer_Achievement extends MoviePlayerBase
	{
		override protected function configUI():void
		{
			trace(">>>>>>>>>>>>>>> MoviePlayer_Achievement::configUI");
			
			super.configUI();			
			
			//stage.scaleMode = "exactFit";
			//this.addEventListener( Event.ENTER_FRAME ,UpdateFrame );
			//initStage();
			
			trace("<<<<<<<<<<<<<<< MoviePlayer_Achievement::configUI");
		}		
	}
}