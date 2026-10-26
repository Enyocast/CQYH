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
	import UI_SkillSetting.SkillSettingAS3.SkillSettingPanel;

	public class MoviePlayer_SkillSetting extends MoviePlayerBase
	{		
		public var SkillSettingPanelMc:SkillSettingPanel;
		
		override protected function configUI():void
		{
			super.configUI();
		}
	}
}