package ActionScript3
{
	import flash.display.MovieClip;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.external.ExternalInterface;
	import flash.text.TextField;
	
	import ActionScript3.MyPanel;
	
	import scaleform.clik.controls.Button;
	import scaleform.clik.controls.NumericStepper;
	import scaleform.clik.controls.TextInput;
	import scaleform.clik.events.IndexEvent;
	import scaleform.clik.managers.FocusHandler;
	import scaleform.clik.events.ComponentEvent;
	import flash.events.FocusEvent;
	import scaleform.clik.events.ButtonEvent;
	

	public class MyShopMessage extends MyPanel
	{
		public var MsgId:Number = -1;
		public var MsgInfoId:Number = -1;
		public var yesButton_mc:Button;
		public var noButton_mc:Button;
		public var numstep:NumericStepper;

		public var MsgText_mc:TextField;
		public var MsgText2_mc:TextField;
		
		public var testText:TextField;
		
		override protected function configUI():void {
			ShowMode="BC";
			super.configUI();
			(this.MyWindowsFrame_mc.getChildByName("divide") as MovieClip).y=182;
			numstep.edit=true;
			numstep.maxChar=2;
			numstep.textField.addEventListener(FocusEvent.FOCUS_IN,FOCUS_INhandler);
			numstep.textField.addEventListener(FocusEvent.FOCUS_OUT,FOCUS_OUThandler);
			yesButton_mc.addEventListener( MouseEvent.CLICK,ClickYes );
			noButton_mc.addEventListener( MouseEvent.CLICK,ClickNo );
            MyWindowsFrame_mc.btn_close.RemoveAddedEventListener();
			MyWindowsFrame_mc.btn_close.addEventListener(MouseEvent.CLICK,ClickNo);
			numstep.addEventListener( IndexEvent.INDEX_CHANGE,indexHandler );
/*			numstep.prevBtn.addEventListener( MouseEvent.CLICK,ClickdownArrow );
			numstep.nextBtn.addEventListener( MouseEvent.CLICK,ClickupArrow );*/
		    this.addEventListener(ComponentEvent.HIDE,hideHandler);
		}
		
		private function FOCUS_INhandler(evt:FocusEvent):void
		{
			ExternalInterface.call( "ASFocusInTextInput" , true );
		}
		private function FOCUS_OUThandler(evt:FocusEvent):void
		{
			ExternalInterface.call( "ASFocusInTextInput" , false );
		}
		
		private function hideHandler(evt:Event):void
		{
			FocusHandler.getInstance().setFocus(null);
			UCResetShopMessage();
		}
		
		public function UCResetShopMessage():void
		{
			numstep.value=1;
		}
		
		public function UCUpdateShopMessageMoney(money1:String, money2:String):void
		{
			MsgText_mc.htmlText = money1;
			MsgText2_mc.htmlText = money2;
		}
		
		private function indexHandler(evt:IndexEvent):void
		{
			var num:int=evt.index;
			ExternalInterface.call( "ASShopMsgNumChange",num );
		}

		private function ClickYes(e:MouseEvent):void
		{
			var num:int = numstep.value;
			ExternalInterface.call( "ASShopMsgAck",true,num );
			visible = false;
		}
		public function setFocus():void
		{
			FocusHandler.getInstance().setFocus(numstep.textField);
			numstep.textField.setSelection(1,1);
		}
		
		public function UCUpdateNum(num:int):void
		{
			
		}

		private function ClickNo(e:MouseEvent):void
		{
			var num:int = numstep.value;
			ExternalInterface.call( "ASShopMsgAck",false,num );
			visible = false;
			UCResetShopMessage();
		}

	}
}