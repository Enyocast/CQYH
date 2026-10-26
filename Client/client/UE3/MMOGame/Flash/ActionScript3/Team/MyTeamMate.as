package ActionScript3.Team{
	
	import ActionScript3.MyPanel;
	import flash.display.MovieClip;
	import flash.events.MouseEvent;
	import flash.events.Event;
	import scaleform.gfx.MouseEventEx;
	import flash.external.ExternalInterface;
	import scaleform.clik.core.UIComponent;
	import scaleform.clik.controls.Button;
	import flash.text.TextField;
	
	public class MyTeamMate extends MyPanel
	{
		public var TeamMate4:MyNormalTeamMate;
		public var TeamMate20:MyLargeTeamMate;
		
		override protected  function configUI():void {

			super.configUI();
			
			
		}
		
		public function UCUpdateTeamMenber(data:Array):void
		{
			if(TeamMate4.visible == true)
			{
				TeamMate4.UCUpdateTeamMenber(data);
				
			}
			else if(TeamMate20.visible == true)
			{
				TeamMate20.UCUpdateTeamMenber(data);
				
			}
			
		}
	}
}