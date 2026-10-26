package ActionScript3.fla
{
	import flash.external.ExternalInterface;
	import flash.display.StageScaleMode;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.ui.Mouse;
	
	import ActionScript3.MyPanel;	
	import ActionScript3.fla.MoviePlayerBase;

	public class MoviePlayer_NpcDialog extends MoviePlayerBase
	{
		public var NpcDialog_mc:MyPanel;
		
		override function initStage()
		{			
			if(NpcDialog_mc)
			{
				ExternalInterface.call( "RegisterDialog" , NpcDialog_mc );
			}

			super.initStage();
		}
	}
}