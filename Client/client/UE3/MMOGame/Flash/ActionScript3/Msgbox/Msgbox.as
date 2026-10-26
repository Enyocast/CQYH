package ActionScript3.Msgbox
{
	import flash.display.MovieClip;
	import flash.events.MouseEvent;
	import flash.external.ExternalInterface;
	import flash.filters.BevelFilter;
	import flash.filters.DropShadowFilter;
	import flash.text.TextField;
	import flash.text.TextFormat;
	import flash.text.TextFormatAlign;
	import flash.ui.Keyboard;
	
	import ActionScript3.MyPanel;
	import ActionScript3.MyWindowsFrame;
	import ActionScript3.Common.Events.ParamEvent;
	import ActionScript3.Common.Utils.ConfigConstants;
	import ActionScript3.Common.Utils.StyleType;
	
	import scaleform.clik.constants.InputValue;
	import scaleform.clik.constants.NavigationCode;
	import scaleform.clik.events.InputEvent;
	import scaleform.clik.managers.FocusHandler;
	import scaleform.clik.ui.InputDetails;
	import scaleform.clik.controls.Button;

	//¡ä????
	public class Msgbox extends MyPanel
	{
		public var MsgId:Number = -1;
		public var MsgInfoId:Number = -1;
		public var yesButton_mc:Button;
		public var noButton_mc:Button;
		
		public var bevel:BevelFilter= StyleType.getInstance().getBevel();
		public var shade:DropShadowFilter=StyleType.getInstance().getDropShadow();
		public function ClickYes(e:MouseEvent):void
		{
			ExternalInterface.call( "ASUnLockMsgAck",true,this );
			if(parent){
				FocusHandler.getInstance().setFocus(null);
				parent.removeChild( this);
			}
		}


		public function ClickNo(e:MouseEvent):void
		{
			ExternalInterface.call( "ASUnLockMsgAck",false,this );
			if(parent){
				FocusHandler.getInstance().setFocus(null);
				parent.removeChild( this);
			}
		}
		
		public function SetOneButton()
		{
			if( MyWindowsFrame_mc && yesButton_mc && noButton_mc )
			{
				yesButton_mc.x = ( MyWindowsFrame_mc.width - yesButton_mc.width )/2 + MyWindowsFrame_mc.x;
				noButton_mc.visible = false;
			}
		}

		
		override protected function configUI():void 
		{
			ShowMode = ConfigConstants.PANEL_SHOW_MODE_BC;
			super.configUI();
			this.MyWindowsFrame_mc.content.y=40+(100-this.MyWindowsFrame_mc.content.textHeight)/2;
			setTxt(this.MyWindowsFrame_mc.content);
			this.SetWindowTitle("提示");
			if( noButton_mc )
				noButton_mc.addEventListener(MouseEvent.CLICK,ClickNo );
			if( yesButton_mc )
				yesButton_mc.addEventListener(MouseEvent.CLICK,ClickYes );
		    if(MyWindowsFrame_mc!=null && MyWindowsFrame_mc.btn_close.visible==true){
				MyWindowsFrame_mc.btn_close.RemoveAddedEventListener();
				MyWindowsFrame_mc.btn_close.addEventListener(MouseEvent.CLICK,ClickNo);
			}
			
			addEventListener(InputEvent.INPUT, handleInput, false, 0, true);
		}
		
		override public function handleInput(event:InputEvent):void 
		{
			if (event.isDefaultPrevented()) { return; }
			var details:InputDetails = event.details;
			
			switch (details.code) 
			{
				case Keyboard.ESCAPE:
					if (details.value == InputValue.KEY_UP) 
					{
						ClickNo(null);
					}
					break;
			}
		}
				
		public function setTxt(txt:TextField):void
		{
			//FocusHandler.getInstance().setFocus(txt);
			txt.filters=null;
			bevel.shadowColor=0xf5d46e;
			bevel.highlightColor=0xe29025;
			var format:TextFormat=txt.getTextFormat();
			format.leading=0;
			format.size=14;
			format.align=TextFormatAlign.CENTER;
			txt.setTextFormat(format);
			txt.textColor=0xffffff;
			shade.blurX=shade.blurY=2;
			shade.distance=1;
			txt.filters=[shade,bevel];
		}
		
	}

}