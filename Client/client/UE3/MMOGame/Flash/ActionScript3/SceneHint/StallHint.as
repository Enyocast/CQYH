package ActionScript3.SceneHint
{
	import scaleform.clik.core.UIComponent;
	import flash.external.ExternalInterface;
	import flash.display.MovieClip;
	import flash.text.TextField;
	import scaleform.clik.controls.Button;
	import scaleform.clik.events.ButtonEvent;
	import flash.external.ExternalInterface;

	public class StallHint extends Button
	{
		private var stallName:String;
		private var palyerName:String;
		public var _bg:MovieClip;
		override protected function configUI():void
		{
			super.configUI();
			
			this.addEventListener(ButtonEvent.CLICK,clickHandler);
		}
		
		private function clickHandler(evt:ButtonEvent):void
		{ 
			ExternalInterface.call("ASClickStallInfo",palyerName,stallName);
		}
		
		public function SetStallText(palyerTxt:String, stallTxt:String,attention:Boolean ):void
		{
			stallName=stallTxt;
			palyerName=palyerTxt;
			textField.text = stallTxt;
			if (attention)
			{
				_bg.gotoAndStop(2);
				textField.textColor = 0x68fff6;
			}
			else
			{
				_bg.gotoAndStop(1);
				textField.textColor = 0xfff775;
			}
		}
		
	}
}