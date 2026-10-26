//
// 家族总揽
//
package ActionScript3.Guild
{
	import flash.display.DisplayObject;
	import flash.external.ExternalInterface;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.events.KeyboardEvent;
	import flash.display.MovieClip;
	import flash.text.TextField;
	import flash.text.TextFieldAutoSize;
	import flash.utils.getDefinitionByName;

	import scaleform.clik.core.UIComponent;
	import scaleform.clik.constants.InvalidationType;
	import scaleform.clik.controls.Button;
	import scaleform.clik.controls.ScrollBar;
	import scaleform.clik.controls.ScrollingList;
	import scaleform.clik.controls.ListItemRenderer;
	import scaleform.clik.controls.DropdownMenu;
	import scaleform.clik.events.ButtonEvent;
	import scaleform.clik.events.ListEvent;
	import scaleform.clik.data.DataProvider;
	import scaleform.clik.data.TreeDataProvider;
	import scaleform.clik.utils.Padding;
	
	import ActionScript3.MyPanel;
	import ActionScript3.MyTipButton;

	public class GuildRightsManagePanel extends UIComponent
	{
		public var guild_rights_post_mc:DropdownMenu;
		
		public var guild_rights_invite_mc:MovieClip;
		public var guild_rights_refuse_mc:MovieClip;
		public var guild_rights_forbid_mc:MovieClip;
		public var guild_rights_post_change_mc:MovieClip;
		public var guild_rights_building_up_mc:MovieClip;
		public var guild_rights_skill_up_mc:MovieClip;
		public var guild_rights_bank_setting_mc:MovieClip;
		public var guild_rights_expel_mc:MovieClip;
		public var guild_rights_dungeon_mc:MovieClip;
		public var guild_rights_foreign_mc:MovieClip;
		public var guild_rights_notice_mc:MovieClip;
		public var guild_rights_activity_mc:MovieClip;
		
		public var guild_rights_leader_change_mc:MovieClip;
		public var guild_rights_dissolve_mc:MovieClip;
		public var guild_rights_exit_mc:MovieClip;
		
		public var guild_leader_change_panel_mc:GuildLeaderChangePanel;
		public var guild_dissolve_panel_mc:MovieClip;
		
		public var guild_rights_tips_tf:TextField;
		
		override protected function configUI():void
		{
			super.configUI();
			guild_rights_post_mc.dataProvider = new DataProvider();
			guild_rights_post_mc.addEventListener(Event.CHANGE, onChangeSelect);
			guild_rights_post_mc.selectedIndex = 0;
			
			guild_rights_leader_change_mc.addEventListener(MouseEvent.CLICK, onBtClickChangeLeader);
			guild_rights_dissolve_mc.addEventListener(MouseEvent.CLICK, onBtClickDissolve);
			guild_rights_exit_mc.addEventListener(MouseEvent.CLICK, onBtClickExit);
		
			guild_leader_change_panel_mc.visible = false;
			guild_dissolve_panel_mc.visible = false;
		
			guild_rights_post_mc.datastring = "会长=副会长=长老=监事=理事=执事=会员";
			guild_rights_post_mc.SplitData();
			
			guild_rights_tips_tf.text = "";
		}
		
		private function onChangeSelect(evt:Event):void
		{
			ExternalInterface.call("ASUpdateGuildRights", guild_rights_post_mc.selectedIndex);
		}
		
		private function onBtClickChangeLeader(evt:MouseEvent):void
		{
			guild_leader_change_panel_mc.visible = true;
			guild_leader_change_panel_mc.show();
		}
		
		private function onBtClickDissolve(evt:MouseEvent):void
		{
			guild_dissolve_panel_mc.visible = true;
			guild_dissolve_panel_mc.show();
		}
		
		private function onBtClickExit(evt:MouseEvent):void
		{
			ExternalInterface.call("ASQuitGuild");
		}
		
		public function updateGuildRights(data:Object):void
		{
			guild_rights_invite_mc.selected = data.guild_rights_invite;
			guild_rights_refuse_mc.selected = data.guild_rights_recruit;
			guild_rights_forbid_mc.selected = data.guild_rights_forbid_chat;
			guild_rights_notice_mc.selected = data.guild_rights_notice;
			guild_rights_bank_setting_mc.selected = data.guild_rights_storage_right;
			guild_rights_dungeon_mc.selected = data.guild_rights_dungeon;
			guild_rights_building_up_mc.selected = data.guild_rights_upgrade_building;
			guild_rights_skill_up_mc.selected = data.guild_rights_upgrade_skill;
			guild_rights_post_change_mc.selected = data.guild_rights_change_pos;
			guild_rights_expel_mc.selected = data.guild_rights_banish;
			guild_rights_foreign_mc.selected = data.guild_rights_foreign;
			guild_rights_activity_mc.selected = data.guild_rights_activity;
			
			guild_rights_tips_tf.text = String(data.guild_rights_tips);
		}
		
		public function updateGuildBaseInfo(data:Object):void
		{
			guild_rights_leader_change_mc.enabled = data.guild_rights_leader;
			guild_rights_dissolve_mc.enabled = data.guild_rights_leader;
			
			guild_rights_post_mc.selectedIndex = data.guild_post - 1;
			ExternalInterface.call("ASUpdateGuildRights", guild_rights_post_mc.selectedIndex);
		}
	}
}


























