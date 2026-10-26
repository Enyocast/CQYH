//
// 家族创建
//
package ActionScript3.Guild
{
	import flash.external.ExternalInterface;
	import flash.events.MouseEvent;
	import flash.display.MovieClip;
	import flash.text.TextField;
	
	import ActionScript3.MyPanel;
	import UI_ChatWidget.AS3.ChatTextField;
	import scaleform.clik.controls.Button;

	public class GuildWarPanel extends MyPanel
	{
		public var guild_war_enemy_mc:ChatTextField;
		//public var guild_war_consume_mc:TextField;
		//public var guild_war_cd_mc:TextField;
		public var guild_war_tips_mc:TextField;
		public var txt_money:TextField;
		public var txt_herb:TextField;
		public var txt_wood:TextField;
		public var txt_crystal:TextField;
		public var txt_silver:TextField;
		public var guild_war_challenge_mc:Button;
		
		override protected function configUI():void
		{
			super.configUI();
			guild_war_challenge_mc.addEventListener(MouseEvent.CLICK, onBtClickOk);
			guild_war_enemy_mc.text = ""
			//guild_war_consume_mc.htmlText = "";
			//guild_war_cd_mc.text = "";
		}
		
		public function updateGuildWarInfo(data:Object):void
		{
			//guild_war_consume_mc.htmlText = String(data.guild_war_consume);
			//guild_war_cd_mc.text = String(data.guild_war_cd);
			guild_war_tips_mc.htmlText = String(data.guild_war_introduce);
			txt_money.htmlText=data.money;
			txt_herb.htmlText=data.herb;
			txt_wood.htmlText=data.wood;
			txt_crystal.htmlText=data.crystal;
			txt_silver.htmlText=data.silver;
			guild_war_challenge_mc.enabled=data.enough;
		}
		
		private function onBtClickOk(evt:MouseEvent):void
		{
			ExternalInterface.call("ASChallenge", guild_war_enemy_mc.text);
			guild_war_enemy_mc.text = ""
			//guild_war_consume_mc.htmlText = "";
			//guild_war_cd_mc.text = "";
		}
		
		public function updateGuildWarCD(time:String)
		{
			//guild_war_cd_mc.text = time;
		}
	}
}


























