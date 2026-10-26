package UI_BattleSummary.BattleSummaryAS3
{
	import ActionScript3.MyPanel;
	import flash.display.MovieClip;
	import scaleform.clik.core.UIComponent;
	import flash.text.TextField;
	import scaleform.clik.controls.UILoader;
	
	import flash.events.MouseEvent;
	import flash.events.Event;
	import flash.external.ExternalInterface;

	
	public class BtlDescPanel extends UIComponent
	{
		public var WinDesc_tf:TextField;
		public var PlayDesc_tf:TextField;
		//public var BattlePlayImg_ld:UILoader;
		
		override protected function configUI():void
		{
			super.configUI();
		}

	}
}