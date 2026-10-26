package ActionScript3.Common
{
	import flash.events.FocusEvent;
	import flash.external.ExternalInterface;
	import flash.text.TextFormat;
	import flash.text.TextFormatAlign;
	import flash.ui.Keyboard;
	
	import scaleform.clik.constants.InputValue;
	import scaleform.clik.controls.TextInput;
	import scaleform.clik.events.FocusHandlerEvent;
	import scaleform.clik.events.InputEvent;
	import scaleform.clik.ui.InputDetails;
	
	public class TextInput_Advanced extends TextInput
	{
		protected var _textColor_default:String;
		protected var _textColor_focus:String;
		
		public function TextInput_Advanced()
		{
			super();
		}
		
		override protected function configUI():void 
		{ 
			_textFormat.color = textColor_focus;
			_textFormat.align = textAlign;
			textField.setTextFormat(_textFormat);
			defaultTextFormat.color = textColor_default;
			defaultTextFormat.align = textAlign;
			textField.addEventListener(FocusHandlerEvent.FOCUS_IN, onFocusInChangeTextFormat);
			textField.addEventListener(FocusHandlerEvent.FOCUS_OUT, onFocusOut);
			
			super.configUI();
		}
		
		protected function onFocusInChangeTextFormat(evt:FocusHandlerEvent):void
		{
			_focused = 1;
			if(_textFormat && _textFormat != textField.getTextFormat())
			{
				textField.setTextFormat(_textFormat);
			}
		}
		
		protected function onFocusOut(evt:FocusHandlerEvent):void
		{
			_focused = 0;
		}
		
		[Inspectable(defaultValue="center", enumeration="left,right,center,justify")]
		public var textAlign:String = "center";
		
		[Inspectable(type="String", defaultValue="0xFFFFFF", name="textColor_default")]
		public function get textColor_default():String
		{
			return _textColor_default;
		}
		
		public function set textColor_default(value:String):void
		{
			_textColor_default = value;
		}
		
		[Inspectable(type="String", defaultValue="0xFFFFFF", name="textColor_focus")]
		public function get textColor_focus():String
		{
			return _textColor_focus;
		}
		
		public function set textColor_focus(value:String):void
		{
			_textColor_focus = value;
		}
	}
}