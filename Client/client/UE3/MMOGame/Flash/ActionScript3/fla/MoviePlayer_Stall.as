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
	import ActionScript3.Widget.StallBuyWidget;
	import ActionScript3.Widget.StallWidget;
	import ActionScript3.Widget.StallBuyWidget;
	
	public class MoviePlayer_Stall extends MoviePlayerBase
	{
		public var mc_StallSetting:StallWidget;
		public var mc_StallBuy:StallBuyWidget;

		override function initStage()
		{	
			super.initStage();
			/*if( mc_StallSetting )
				mc_StallSetting.visible = false;
			if( mc_StallBuy )
				mc_StallBuy.visible = false;*/
		}

		override  function OnMouseMove()
		{

		}

		override  function UpdateFrame()
		{

		}		
	}
}