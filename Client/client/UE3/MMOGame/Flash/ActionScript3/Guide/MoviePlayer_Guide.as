package ActionScript3.Guide
{
	import ActionScript3.fla.MoviePlayerBase;
	
	public class MoviePlayer_Guide extends MoviePlayerBase
	{
		override protected function configUI():void
		{
			super.configUI();			
			
			trace(">>>>>>>>>> MoviePlayer_Guide::configUI");
			trace("<<<<<<<<<< MoviePlayer_Guide::configUI");
		}		
	}
}