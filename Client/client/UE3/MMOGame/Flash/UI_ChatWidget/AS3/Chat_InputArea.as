package UI_ChatWidget.AS3 {
	
	import flash.display.MovieClip;
	import scaleform.clik.controls.Button;
	import flash.text.TextField;
	import scaleform.clik.controls.RadioButton;
	import flash.events.MouseEvent;
	import flash.external.ExternalInterface;
	import flash.events.Event;
	
	
	public class Chat_InputArea extends MovieClip {
		
		public var enter_mc:Button;
		public var FaceButton_mc:Button;
		public var NewInput_mc:ChatTextField;
		public var defaultTxt:TextField;
		public var channelTxt:MovieClip;
		
		public var tipsHtml:String;
		public var ChannelArr:Array;
		public function Chat_InputArea() 
		{
			ChannelArr=["广播","附近","公会","队伍","私聊","系统","提示","传音"];
			channelTxt.addEventListener(MouseEvent.MOUSE_OVER,overHandler);
			channelTxt.addEventListener(MouseEvent.MOUSE_OUT,outHandler);
			NewInput_mc.addEventListener(Event.CHANGE,changeHandler);
			show();
		}
		
	    private function changeHandler(evt:Event):void
		{
			show();
		}
		
		private function overHandler(evt:MouseEvent):void
		{
			ExternalInterface.call("ASShowTips_PlainText",this );
		}
		
		private function outHandler(evt:MouseEvent):void
		{
			ExternalInterface.call("ASHideTips_PlainText",this );
		}
		
		public function setHtmlTips(id:int):void
		{
			updateDefault(id);
			tipsHtml=ChannelArr[id].toString();
			channelTxt.textField.text=tipsHtml.substr(0,1);
		}
		
		public function updateDefault(curChannel:int):void
		{
			if(curChannel==0)
			{
				defaultTxt.text="每次发言需要消耗1000金币";
			}
			else
			{
				defaultTxt.text="每次发言需要消耗一个千里传音";
			}
		}
		
		public function show(bl:Boolean=false):void
		{
			if(NewInput_mc.length>0)
			{
				defaultTxt.visible=false;
			}
			else
			{
				defaultTxt.visible=bl;
			}
			
		}
		
	}
	
}
