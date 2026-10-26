package ActionScript3.fla
{
	import flash.external.ExternalInterface;
	import flash.text.TextField;
	import flash.ui.Mouse;	
	import flash.events.Event;
	import flash.events.TimerEvent;
	import flash.events.MouseEvent;
	import flash.utils.Timer;
	import flash.display.MovieClip;
	import flash.display.DisplayObject;
	import flash.display.StageScaleMode;

	import scaleform.clik.core.UIComponent;
	import scaleform.clik.controls.Button;

	import ActionScript3.MyPanel;
	import ActionScript3.fla.MoviePlayerBase;
	import ActionScript3.Widget.MySkillPanel;

	public class MoviePlayer_Skill extends MoviePlayerBase
	{		
		public var SkillPanel:MySkillPanel;
		
		override protected function configUI():void
		{
			trace("MoviePlayer_Skill configUI:");
			super.configUI();
		}
	}
}