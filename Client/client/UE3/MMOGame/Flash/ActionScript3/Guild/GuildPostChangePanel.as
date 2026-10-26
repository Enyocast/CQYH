//
// 家族职位变更
//
package ActionScript3.Guild
{
	import flash.external.ExternalInterface;
	import flash.events.MouseEvent;
	import flash.display.MovieClip;
	import flash.text.TextField;
	import scaleform.clik.controls.RadioButton;

	public class GuildPostChangePanel extends BaseGuildAlert
	{
		public var guild_post_change_vice_leader_mc:RadioButton;
		public var guild_post_change_zhanglao_mc:RadioButton;
		public var guild_post_change_dianzhu_mc:RadioButton;
		public var guild_post_change_zhishi_mc:RadioButton;
		public var guild_post_change_zhubu_mc:RadioButton;
		public var guild_post_change_member_mc:RadioButton;

		public var guild_post_change_role_id:int;
		
		override protected function configUI():void
		{
			super.configUI();
			this.SetWindowTitle("变更职位");
			clear();
		}
		
		override protected function onBtClickClose(evt:MouseEvent):void
		{
			clear();
			super.onBtClickClose(evt);
		}
		
		private function clear():void
		{
			guild_post_change_vice_leader_mc.selected = true;
			guild_post_change_zhanglao_mc.selected = false;
			guild_post_change_dianzhu_mc.selected = false;
			guild_post_change_zhishi_mc.selected = false;
			guild_post_change_zhubu_mc.selected = false;
			guild_post_change_member_mc.selected = false;
			
			guild_post_change_role_id = 0;
		}
		
		override protected function onBtClickOk(evt:MouseEvent):void
		{
			var post_change_data = new Array();
			post_change_data.push(guild_post_change_vice_leader_mc.selected);
			post_change_data.push(guild_post_change_zhanglao_mc.selected);
			post_change_data.push(guild_post_change_dianzhu_mc.selected);
			post_change_data.push(guild_post_change_zhishi_mc.selected);
			post_change_data.push(guild_post_change_zhubu_mc.selected);
			post_change_data.push(guild_post_change_member_mc.selected);
			                          
			for (var i:int = 0; i < post_change_data.length; i ++)
			{
				if(post_change_data[i] == true)
				{
					ExternalInterface.call("ASChangePost", guild_post_change_role_id, i + 2);
					break;
				}
			}
			guild_post_change_role_id = 0;
			this.visible = false;
		}

		
		public function setRoleId(id:int):void
		{
			guild_post_change_role_id = id;
		}
	}
}


























