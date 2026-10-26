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
	import scaleform.gfx.Extensions;	
	
	import scaleform.clik.core.UIComponent;
	import scaleform.clik.controls.Button;

	import ActionScript3.fla.MoviePlayerBase;
	import UI_WeaponSkill.WeaponSkillAS3.WeaponSkillPanel;
	//import UI_WeaponSkill.WeaponSkillAS3.WeaponSkillSettingPanel;
	
	public class MoviePlayer_WeaponSkill extends MoviePlayerBase
	{		
		public var WeaponSkillPanelMc:WeaponSkillPanel;
		//public var WeaponSkillSettingPanelMc:WeaponSkillSettingPanel;
		
		override protected function configUI():void
		{
			super.configUI();
		}
//		public function GetMouseTopMostEntity()
//		{
//			var topMostObject:DisplayObject = Extensions.getMouseTopMostEntity();
//			ExternalInterface.call( "ASGetMouseTopMostEntity", topMostObject );
//		}				
	}
}