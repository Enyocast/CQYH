//
// 家族解散
//
package ActionScript3.Guild
{
	import flash.external.ExternalInterface;
	import flash.events.MouseEvent;
	import UI_ChatWidget.AS3.ChatTextField;
	import scaleform.clik.managers.FocusHandler;

	public class GuildDissolvePanel extends BaseGuildAlert
	{
		public var guild_dissolve_input_mc:ChatTextField;

		override protected function configUI():void
		{
			super.configUI();
			this.SetWindowTitle("主动解散");
			guild_dissolve_input_mc.textField.maxChars=2;
		}
		
	    public function show():void
		{
			FocusHandler.getInstance().setFocus(guild_dissolve_input_mc.textField);
		}
		
		override protected function onBtClickClose(evt:MouseEvent):void
		{
			guild_dissolve_input_mc.text="";
			super.onBtClickClose(evt);
		}
		
		override protected function onBtClickOk(evt:MouseEvent):void
		{
			ExternalInterface.call("ASDisbandGuild", guild_dissolve_input_mc.text);
			onBtClickClose(null);
		}
	}
}


























