//
// 家族查找
//
package ActionScript3.Guild
{
	import flash.external.ExternalInterface;
	import flash.events.MouseEvent;
	import flash.text.TextField;
	import UI_ChatWidget.AS3.ChatTextField;
	import scaleform.clik.controls.RadioButton;
	import scaleform.clik.managers.FocusHandler;

	public class GuildFindPanel extends BaseGuildInput
	{
		public var guild_find_title_tf:TextField;
		public var guild_find_by_name_mc:RadioButton;
		public var guild_find_by_id_mc:RadioButton;
		
		override protected function configUI():void
		{
			super.configUI();
			this.SetWindowTitle("查找公会");
			
			guild_find_by_name_mc.addEventListener(MouseEvent.CLICK, onBtClickName);
			guild_find_by_id_mc.addEventListener(MouseEvent.CLICK, onBtClickId);

			onBtClickName(null);
			guild_find_by_name_mc.selected = true;
		}
		
		public function onBtClickName(evt:MouseEvent):void
		{
			guild_find_by_name_mc.selected=true;
			guild_find_title_tf.text = "公会名称";
			txt_name.textField.restrict=null;
			txt_name.textField.maxChars=12;
			txt_name.text="";
			updateTextFormat(true,12);
			txt_name.defaultText="(最多8个汉字)";
		}
		
		private function onBtClickId(evt:MouseEvent):void
		{
			guild_find_title_tf.text = "公会ID";
			txt_name.textField.restrict="0-9";
			txt_name.textField.maxChars=12;
			txt_name.text="";
			txt_name.defaultText="";
			updateTextFormat(false,12);
		}
		
		override protected function onBtClickClose(evt:MouseEvent):void
		{
			super.onBtClickClose(evt);
			txt_name.text="";
		}
		
		override protected function onBtClickOk(evt:MouseEvent):void
		{
			ExternalInterface.call("ASFindGuild", guild_find_by_id_mc.selected, txt_name.text);
			onBtClickClose(null);
		}
		
	}
}


























