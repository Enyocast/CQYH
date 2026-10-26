package ActionScript3.Guild {
	
	import flash.events.MouseEvent;
	import flash.external.ExternalInterface;
	import flash.text.TextField;
	import UI_ChatWidget.AS3.ChatTextField;
	import scaleform.clik.managers.FocusHandler;
	
	public class GuildEnounceModifyPanel extends BaseGuildAlert {
		
		public var txt_name:ChatTextField;
		override protected function configUI():void
		{
			super.configUI();
			this.SetWindowTitle("更改宣言");
			txt_name.textField.maxChars=30;
			txt_name.textField.wordWrap=true;
			txt_name.textField.multiline=true;
		}
		
		override protected function onBtClickClose(evt:MouseEvent):void
		{
			super.onBtClickClose(evt);
			FocusHandler.getInstance().setFocus(null);
		}
				
		public function show():void
		{
			FocusHandler.getInstance().setFocus(txt_name.textField);
			txt_name.textField.maxChars=30;
		}
		
		//更新宣言
		public function updateEnounce(dat:String):void
		{
			txt_name.htmlText=dat;
		}
		
		override protected function onBtClickOk(evt:MouseEvent):void
		{
			ExternalInterface.call("ASChangeAnnounce", txt_name.textField.text);
			onBtClickClose(null);
		}
	}
	
}
