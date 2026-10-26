package ActionScript3.Guild {
	import UI_ChatWidget.AS3.ChatTextField;
	import flash.events.Event;
	import flash.events.FocusEvent;
	import flash.events.MouseEvent;
	
	public class BaseGuildInput extends BaseGuildAlert {
        
		public var txt_name:ChatTextField;
		private var max:int;
		override protected function configUI():void
		{
			super.configUI();
			txt_name.addEventListener(FocusEvent.FOCUS_IN,focusinHandler);
			txt_name.addEventListener(FocusEvent.FOCUS_OUT,focusoutHandler);
			txt_name.addEventListener(Event.CHANGE,changeHandler);
		}
		
		override protected function onBtClickClose(evt:MouseEvent):void
		{
			txt_name.text="";
			updateTextFormat(true);
			super.onBtClickClose(evt);
		}
		
		private function changeHandler(evt:Event):void
		{
			updateTextFormat(false,max);
		}
		
		private function focusinHandler(evt:FocusEvent):void
		{
			updateTextFormat(false,max);
		}
		private function focusoutHandler(evt:FocusEvent):void
		{
			if(txt_name.text!="")
			{
				updateTextFormat(false,max);
			}
			else
			{
				updateTextFormat(true,max);
			}
		}
		protected function updateTextFormat(bl:Boolean,_maxChar:int=12):void
		{
			max=_maxChar;
			txt_name.textField.maxChars=_maxChar;
			if(bl)
			{
				txt_name.defaultTextFormat.color=0x85919E;
				txt_name.textField.setTextFormat(txt_name.defaultTextFormat);
			}
			else
			{
				txt_name.defaultTextFormat.color=0xFFFFFF;
				txt_name.textField.setTextFormat(txt_name.defaultTextFormat);
			}
		}

	}
	
}
