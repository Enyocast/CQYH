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

	import ActionScript3.MyPanel;
	import ActionScript3.fla.MoviePlayerBase;
	import UI_SkillTree.SkillTreeAS3.SkillTreePanel;
	import UI_SkillTree.SkillTreeAS3.HeavenGasExchangePanel;
	import UI_SkillTree.SkillTreeAS3.HeavenGasPractisePanel;

	public class MoviePlayer_SkillTree extends MoviePlayerBase
	{		
		public var SkillTreePanelMc:SkillTreePanel;
		public var GasExchangePanel_mc:HeavenGasExchangePanel;
		public var gasPractisePanel_mc:HeavenGasPractisePanel;
		
		override protected function configUI():void
		{
			super.configUI();
		}
	}
}