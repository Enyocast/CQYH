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
	import scaleform.clik.events.ButtonEvent;
	import scaleform.clik.events.ListEvent;
	import scaleform.clik.data.DataProvider;
	import scaleform.clik.data.TreeDataProvider;
	import scaleform.clik.utils.Padding;
	
	import ActionScript3.MyPanel;
	import ActionScript3.MyTipButton;
	import ActionScript3.Common.CustomScrollBar;

	public class GuildSummaryPanel extends UIComponent
	{
		public var guild_sum_name_tf:TextField;
		public var guild_sum_level_tf:TextField;
		public var guild_sum_id_tf:TextField;
		public var guild_sum_leader_tf:TextField;
		public var guild_sum_create_time_tf:TextField;
		public var guild_sum_creator_tf:TextField;
		public var guild_sum_member_count_tf:TextField;
		public var guild_sum_money_tf:TextField;
		public var guild_sum_job_tf:TextField;
		public var guild_sum_contribute_tf:TextField;
		public var guild_sum_notify_tf:TextField;
		public var guild_sum_event_tf:TextField;
		//public var guild_sum_gongxun_tf:TextField;
		
		public var guild_sum_notify_modify_mc:MovieClip;
		public var guild_sum_view_more_mc:Button;
		public var guild_money_contribute_panel_mc:MovieClip;
		public var guild_summary_change_notice_panel_mc:GuildNoticeModifyPanel;
		
		public var guild_money_contribute_mc:MovieClip;
		public var guild_contribute_panel_mc:GuildMoneyContributePanel;
		
		public var guild_sum_id_tips_mc:MovieClip;
		public var guild_sum_level_tips_mc:MovieClip;
		public var guild_sum_leader_tips_mc:MovieClip;
		public var guild_sum_create_time_tips_mc:MovieClip;
		public var guild_sum_creator_tips_mc:MovieClip;
		public var guild_sum_member_count_tips_mc:MovieClip;
		public var guild_sum_money_tips_mc:MovieClip;
		public var guild_sum_job_tips_mc:MovieClip;
		public var guild_sum_contribute_tips_mc:MovieClip;
		public var guild_sum_gongxun_tips_mc:MovieClip;
		public var btn_enounce:Button;
		public var bar:CustomScrollBar;
		public var change_enounce_panel_mc:GuildEnounceModifyPanel;
		public var guild_sum_data:Object;

		override protected function configUI():void
		{
			super.configUI();
			guild_sum_notify_modify_mc.addEventListener(MouseEvent.CLICK, onBtClickNotifyModify);
			guild_sum_view_more_mc.addEventListener(MouseEvent.CLICK, onBtClickViewMore);
			guild_money_contribute_mc.addEventListener(MouseEvent.CLICK, onBtClickContribute);
			btn_enounce.addEventListener(MouseEvent.CLICK,cnClickEnounceHandler);
			guild_summary_change_notice_panel_mc.visible = false;
			guild_contribute_panel_mc.visible = false;
			change_enounce_panel_mc.visible=false;
			guild_sum_money_tips_mc.addEventListener("rollOver", onItemRollOver);
			guild_sum_money_tips_mc.addEventListener("rollOut", onItemRollOut);
		}
		
		private function cnClickEnounceHandler(evt:MouseEvent):void
		{
			change_enounce_panel_mc.visible=true;
			change_enounce_panel_mc.show();
			//change_enounce_panel_mc.SetFocusMc("txt_name", "textField", "", "");
		}
		
		public function onBtClickNotifyModify(evt:MouseEvent):void
		{
			guild_summary_change_notice_panel_mc.visible = true;
			guild_summary_change_notice_panel_mc.show();
			//guild_summary_change_notice_panel_mc.SetFocusMc("txt_name", "textField", "", "");
		}
		
		public function onBtClickViewMore(evt:MouseEvent):void
		{
			ExternalInterface.call("ASViewMoreEvents");
		}
		
		public function onBtClickContribute(evt:MouseEvent):void
		{
			guild_contribute_panel_mc.visible = true;
			guild_contribute_panel_mc.show();
			//guild_contribute_panel_mc.SetFocusMc("guild_money_contribute_input_mc", "textField", "", "");
		}
		
		public function updateGuildBaseInfo(data:Object):void
		{
			if (!data)
			{
				return;
			}
			guild_sum_data = data;
			guild_sum_name_tf.text = data.guild_name;
			guild_sum_level_tf.text = String(data.guild_level);
			guild_sum_id_tf.text = String(data.guild_id);
			guild_sum_leader_tf.text = data.guild_leader_name;
			guild_sum_create_time_tf.text = data.guild_create_time;
			guild_sum_creator_tf.text = data.guild_creator_name;
			guild_sum_member_count_tf.text = String(data.guild_member_count) + "/" + String(data.guild_max_member_count);
			guild_sum_money_tf.text = String(data.guild_money);
			if(data.guild_announce)
			  change_enounce_panel_mc.updateEnounce(data.guild_announce);//公会宣言
			
			guild_sum_contribute_tf.text = String(data.guild_contribute);
			//guild_sum_gongxun_tf.text = String(data.guild_achievement);
			guild_sum_notify_modify_mc.enabled = data.guild_rights_notice;
			btn_enounce.enabled = data.guild_rights_notice;
			guild_sum_job_tf.text = String(data.guild_post_name);
		}
		
		public function updateGuildNotice(notice:String)
		{
			guild_sum_notify_tf.text = notice;
		}
		
		public function updateGuildEvents(events:String)
		{
			guild_sum_event_tf.htmlText = events;
		}
		
		public function updateContributeInfo(money:int, inro:String)
		{
			guild_contribute_panel_mc.updateContributeInfo(money, inro);
		}
		
		public function SetMoreButtonState(bl:Boolean):void
		{
			if(guild_sum_view_more_mc)
			  guild_sum_view_more_mc.enabled=bl;
		}
		
		public function onItemRollOver(e:Event)
		{
			var item_mc:MovieClip = e.currentTarget as MovieClip;
			if (item_mc && guild_sum_data)
			{
				ExternalInterface.call("ASShowTips_PlainText_WithString", item_mc, String(guild_sum_data.guild_money_tips));
			}
		}
		
		public function onItemRollOut(e:Event)
		{
			var item_mc:MovieClip = e.currentTarget as MovieClip;
			if (item_mc)
			{
				ExternalInterface.call("ASHideTips_PlainText", item_mc);
			}
		}
	}
}


























