//
// 家族战进行中
//
package ActionScript3.Guild
{
	import flash.external.ExternalInterface;
	import flash.events.MouseEvent;
	import flash.text.TextField;
	import ActionScript3.MyPanel;
	import flash.display.MovieClip;

	public class GuildWarHintPanel extends MyPanel
	{
		public var guild_war_hint_attack_tf:TextField;
		public var guild_war_hint_defend_tf:TextField;
		public var guild_war_hint_time_title_tf:TextField;
		public var guild_war_hint_time_tf:TextField;
		public var guild_war_hint_button_mc:MovieClip;
		
		override protected function configUI():void
		{
			super.configUI();
			ExternalInterface.call("ASRegisterGuildWarHintPanel", this);
			this.MyWindowsFrame_mc.InfoDragButton_mc.visible=false;
			this.MyWindowsFrame_mc.btn_close.visible=false;
			this.SetWindowTitle("");
			
			guild_war_hint_button_mc.addEventListener(MouseEvent.CLICK, onExpandPanel);
			guild_war_hint_button_mc.selected = false;
		}
		
		function onExpandPanel()
		{
			guild_war_hint_button_mc.selected = !guild_war_hint_button_mc.selected;
			
			this.MyWindowsFrame_mc.visible = !guild_war_hint_button_mc.selected;
			guild_war_hint_attack_tf.visible = !guild_war_hint_button_mc.selected;
			guild_war_hint_defend_tf.visible = !guild_war_hint_button_mc.selected;
			guild_war_hint_time_title_tf.visible = !guild_war_hint_button_mc.selected;
			guild_war_hint_time_tf.visible = !guild_war_hint_button_mc.selected;
			
			playSound("MicroButton");
		}
		
		public function UCSetWindowTitle(title:String)
		{
			SetWindowTitle(title);
		}
		
		public function UCUpdateGuildWarHintInfo(attack:String, defend:String, timeTitle:String, time:String)
		{
			guild_war_hint_attack_tf.htmlText = attack;
			guild_war_hint_defend_tf.htmlText = defend;
			guild_war_hint_time_title_tf.text = timeTitle;
			guild_war_hint_time_tf.text = time;
		}
		
		public function UCUpdateGuildWarHintTime(time:String)
		{
			guild_war_hint_time_tf.text = time;
		}
	}
}


























