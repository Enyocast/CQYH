package ActionScript3.Bag
{

	import ActionScript3.MyPanel;
	import flash.external.ExternalInterface;
	import scaleform.clik.controls.Button;
	import scaleform.clik.controls.RadioButton;
	import flash.events.MouseEvent;
	import flash.events.Event;
	import scaleform.clik.events.ButtonEvent;
	import scaleform.clik.core.UIComponent;
	import flash.text.TextField;
	import flash.utils.Timer;
	import flash.events.TimerEvent;
	import flash.display.MovieClip;
	import flash.utils.getDefinitionByName;
	import ActionScript3.Widget.MyTipsText;
	import ActionScript3.MyTipButtonNew;

	public class LogPanel extends UIComponent
	{
		public var logText:TextField;
		public var pageCtrl:MovieClip;

		override protected function configUI():void
		{
			super.configUI();
			
			
		}

		public function SetPanelText( data:Object )
		{
			if (! data)
			{
				return;
			}

			
		}
		
		public function UpdateShowLog( log:String )
		{
			logText.htmlText = log;
		}
		
	}

}