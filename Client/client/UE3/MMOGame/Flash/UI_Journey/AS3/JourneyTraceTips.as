package UI_Journey.AS3
{
	import flash.display.MovieClip;
	import flash.external.ExternalInterface;
	import flash.text.TextField;
	import flash.text.TextFieldAutoSize;
	
	import ActionScript3.MyCloseButton;
	
	import scaleform.clik.core.UIComponent;
	import scaleform.clik.events.ButtonEvent;
	
	public class JourneyTraceTips extends UIComponent
	{
		public var btn_close:MyCloseButton;
		public var tips_tf:TextField;
		public var tips_bg_mc:MovieClip;
		
		private static const MIN_HEIGHT_OF_BG:Number = 80;
		private static const MARGIN:Number = 13;
		
		public function JourneyTraceTips()
		{
			super();
		}
		
		override protected function configUI():void
		{
			super.configUI();
			tips_tf.mouseEnabled = tips_bg_mc.mouseEnabled = false;
			tips_tf.autoSize = TextFieldAutoSize.LEFT;
			tips_tf.wordWrap = true;
			btn_close.RemoveAddedEventListener();
			
			btn_close.addEventListener(ButtonEvent.CLICK, onHideTips);
		}
		
		private function onHideTips(evt:ButtonEvent):void
		{
			this.visible = false;
			ExternalInterface.call("ASHideNPCTips");
		}
		
		public function updateTips(info:String):void
		{
			tips_tf.htmlText = info;
			tips_tf.height = tips_tf.textHeight + MARGIN;
			tips_bg_mc.height = Math.max(MIN_HEIGHT_OF_BG, tips_tf.y + tips_tf.height - tips_bg_mc.y);
		}
	}
}