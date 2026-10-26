package ActionScript3.Msgbox
{
	import flash.external.ExternalInterface;
	import flash.events.MouseEvent;
	import flash.text.TextFormat;
	import UI_ChatWidget.AS3.ChatTextField;
	import scaleform.clik.managers.FocusHandler;

	//¡ä????
	public class InputMsgbox extends Msgbox
	{


		public var textInput:ChatTextField;

		override public function ClickYes(e:MouseEvent):void
		{
			ExternalInterface.call( "ASInputMsgAck",true,this );
		    FocusHandler.getInstance().setFocus(null);
			parent.removeChild( this);
		}
		
		public function SetInputText( inputText:String )
		{
			if(textInput)
			{
				textInput.text = inputText;
			}
		}

		override public function ClickNo(e:MouseEvent):void
		{
			ExternalInterface.call( "ASInputMsgAck",false,this );
		    FocusHandler.getInstance().setFocus(null);
			parent.removeChild( this);
		}

		function InputMsgbox()
		{
			//trace("msgbox!!!!");
			super();
			configUI();
			textInput.validateNow();
		}
		
		override protected function configUI():void 
		{
			super.configUI();
            //this.MyWindowsFrame_mc.tF_windowTitle.text="标题";
			this.MyWindowsFrame_mc.tF_windowTitle.filters=null;
			this.MyWindowsFrame_mc.tF_windowTitle.textColor=0xfff5de;
			this.MyWindowsFrame_mc.content.y=40+(80-this.MyWindowsFrame_mc.content.textHeight)/2;
			this.MyWindowsFrame_mc.content.filters=null;
			this.MyWindowsFrame_mc.content.textColor=0xfff5de;
			//this.MyWindowsFrame_mc.content.for
			var format:TextFormat=this.MyWindowsFrame_mc.content.getTextFormat();
			format.size=16;
			this.MyWindowsFrame_mc.content.defaultTextFormat=format;
			this.MyWindowsFrame_mc.content.setTextFormat(format);
			textInput.maxChars=15;
			//textInput.y-=6;
			//trace( "?:"+ this.MyWindowsFrame_mc.tF_windowTitle );
			//this.MyWindowsFrame_mc.windowTitle.htmlText = "aabb";
			//this.MyWindowsFrame_mc.content.htmlText = "bbaa";
		}
		
	}

}