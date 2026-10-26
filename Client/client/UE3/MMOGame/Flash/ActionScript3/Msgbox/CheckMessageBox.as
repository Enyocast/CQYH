package ActionScript3.Msgbox {
	
	import flash.display.MovieClip;
	import flash.events.MouseEvent;
	import flash.external.ExternalInterface;
	import flash.text.TextFormatAlign;
	
	import scaleform.clik.controls.CheckBox;
	
	
	public class CheckMessageBox extends Msgbox {
		
		public var chb_msg:CheckBox;
		public function CheckMessageBox() {
			// constructor code
			super();
		}
		
		override protected function configUI():void 
		{
			super.configUI();
			this.MyWindowsFrame_mc.content.y=40+(80-this.MyWindowsFrame_mc.content.textHeight)/2;
			chb_msg.addEventListener(MouseEvent.CLICK,clickHandler);
		}
		
		private function clickHandler(evt:MouseEvent):void
		{
			ExternalInterface.call("ASMessageBoxCheck",this,chb_msg.selected);
		}
		
		public function InitCheckMessage( strDescrible:String,bCheck:Boolean ):void
		{
			chb_msg.validateNow();
			chb_msg.selected = bCheck;
			if(chb_msg&&strDescrible != "")
			{
				chb_msg.label=strDescrible;
			}
		}
		
		//控制关闭按钮显示隐藏
		public function UCShowCloseBtn(bool:Boolean):void
		{
			this.MyWindowsFrame_mc.btn_close.visible=bool;
		}
	}
	
}
