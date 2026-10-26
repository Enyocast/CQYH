//
// 家族公告修改
//
package ActionScript3.Guild
{
	import flash.external.ExternalInterface;
	import flash.events.MouseEvent;
	import flash.display.MovieClip;
	import flash.text.TextField;
	import UI_ChatWidget.AS3.ChatTextField;
	import flash.events.FocusEvent;
	import flash.events.Event;

	public class GuildNoticeModifyPanel extends BaseGuildInput
	{
		override protected function configUI():void
		{
			super.configUI();
			this.SetWindowTitle("更改公告");
			show();
		}
		
		public function show():void
		{
			txt_name.textField.maxChars=60;
			txt_name.textField.wordWrap=true;
			txt_name.textField.multiline=true;
			updateTextFormat(true,60);
			txt_name.defaultText="(最多60个汉字)";
		}

		override protected function onBtClickOk(evt:MouseEvent):void
		{
			ExternalInterface.call("ASChangeNotice", txt_name.textField.text);
			onBtClickClose(null);
		}
	}
}


























