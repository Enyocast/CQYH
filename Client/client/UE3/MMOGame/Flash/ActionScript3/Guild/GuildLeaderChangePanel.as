//
// 家族总揽
//
package ActionScript3.Guild
{
	import flash.external.ExternalInterface;
	import flash.events.MouseEvent;
	import UI_ChatWidget.AS3.ChatTextField;

	public class GuildLeaderChangePanel extends BaseGuildInput
	{
		override protected function configUI():void
		{
			super.configUI();
			this.SetWindowTitle("传位");
			show();
		}

		override protected function onBtClickOk(evt:MouseEvent):void
		{
			ExternalInterface.call("ASLeaderDemise", txt_name.text);
			onBtClickClose(null);
		}
		
		public function show():void
		{
			txt_name.textField.maxChars=12;
			updateTextFormat(true);
			txt_name.defaultText="(最多8个汉字)";
		}
	}
}


























