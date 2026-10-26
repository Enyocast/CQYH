//
// 家族战开始
//
package ActionScript3.Guild
{
	import flash.external.ExternalInterface;
	import flash.events.MouseEvent;
	import flash.text.TextField;
	import scaleform.clik.controls.Button;
	
	import ActionScript3.MyPanel;
	import scaleform.clik.controls.UILoader;

	public class GuildWarStartPanel extends MyPanel
	{
		public var guild_war_start_icon_mc:UILoader;
		public var guild_war_start_text_mc:TextField;
		public var guild_war_start_mc:Button;
		public var guild_war_end_close_mc:Button;
		public var txt_title:TextField;
		override protected function configUI():void
		{
			super.configUI();
			guild_war_end_close_mc.addEventListener(MouseEvent.CLICK,closeHandler);
			guild_war_start_mc.addEventListener(MouseEvent.CLICK, onBtClickFight);
		}
		
		public function closeHandler(e:MouseEvent):void
		{
			ExternalInterface.call("ASOnPanelClose" , this.PanelName);
		}
		
		public function onBtClickFight(e:MouseEvent):void
		{
			ExternalInterface.call("ASJoinWar");
			ExternalInterface.call("ASOnPanelClose" , this.PanelName);
		}
		
		public function UCSetWindowTitle(title:String):void
		{
			txt_title.text=title;
		}
		
		public function UCUpdateGuildWarStartInfo(icon:String, text:String):void
		{
			guild_war_start_icon_mc.source = icon;
			guild_war_start_text_mc.htmlText = text;
		}
	}
}


























