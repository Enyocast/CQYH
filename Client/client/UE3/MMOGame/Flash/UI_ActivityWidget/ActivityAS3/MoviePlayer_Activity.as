
package UI_ActivityWidget.ActivityAS3
{

	import ActionScript3.fla.MoviePlayerBase;
	import UI_ActivityWidget.ActivityAS3.ActivityPanel;
	
	public class MoviePlayer_Activity extends MoviePlayerBase
	{
		public var ActivityView_mc:ActivityPanel;
		
		override protected function configUI():void
		{
			trace("----------------MoviePlayer_Activity::configUI");
			
			super.configUI();
		}		
	}
}