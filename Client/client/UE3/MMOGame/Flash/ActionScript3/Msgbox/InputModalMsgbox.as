package ActionScript3.Msgbox
{
	import flash.text.TextFormat;
	import flash.text.TextFormatAlign;
	
	import UI_ChatWidget.AS3.ChatTextField;
	
	import scaleform.clik.controls.TextInput;
	import scaleform.gfx.FocusManager;
	import scaleform.clik.managers.FocusHandler;

	public class InputModalMsgbox extends Msgbox
	{

		public var textInput:ChatTextField;
		public function InputModalMsgbox():void
		{
			super();
		}
		
		override protected function configUI():void 
		{
			super.configUI();
			this.MyWindowsFrame_mc.InfoDragButton_mc.visible = false;
			this.MyWindowsFrame_mc.content.y=40+(80-this.MyWindowsFrame_mc.content.textHeight)/2;
			textInput.defaultTextFormat.align=TextFormatAlign.CENTER;
			textInput.textField.setTextFormat(textInput.defaultTextFormat);
			textInput.maxChars=15;
			SetTextInputFocus();
		}
		
		public function SetTextInputFocus():void
		{
			FocusHandler.getInstance().setFocus(textInput.textField);
			//textInput.validateNow();
			//stage.focus = textInput.textField;
			//textInput.textField.setSelection(200,200);
		}

		public function SetInputText( inputText:String ):void
		{
			if(textInput)
			{
				textInput.textField.text = inputText;
			}
		}
		
	}

}