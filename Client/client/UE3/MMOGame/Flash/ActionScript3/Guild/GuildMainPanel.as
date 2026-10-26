//
// 家族
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
	import scaleform.clik.controls.RadioButton;

	import ActionScript3.MyPanel;
	import ActionScript3.MyTipButtonNew;

	public class GuildMainPanel extends MyPanel
	{
		//public var guild_main_title_tf:TextField;

		public var guild_main_summary_tab_mc:RadioButton;
		public var guild_main_info_tab_mc:RadioButton;
		public var guild_main_manage_tab_mc:RadioButton;
		public var guild_main_foreign_tab_mc:RadioButton;
		public var guild_main_event_tab_mc:RadioButton;

		public var guild_main_sub_tab_0_mc:RadioButton;
		public var guild_main_sub_tab_1_mc:RadioButton;
		public var guild_main_sub_tab_2_mc:RadioButton;
		public var guild_main_sub_tab_3_mc:RadioButton;
		public var guild_main_sub_tab_4_mc:RadioButton;

		public var guild_main_bg_mc:MovieClip;
		public var guild_summary_panel_mc:MovieClip;
		public var guild_info_full_member_mc:GuildFullMemberPanel;
		public var guild_info_pending_member_mc:MovieClip;
		public var guild_rights_panel_mc:MovieClip;
		public var guild_storage_rights_panel:MovieClip;
		public var guild_money_panel_mc:MovieClip;
		public var guild_foreign_info_panel_mc:MovieClip;
		public var guild_apply_ally_panel_mc:MovieClip;
		public var guild_war_panel_mc:MovieClip;
		public var guild_introduce_panel_mc:MovieClip;
		public var guild_search_panel_mc:MovieClip;
		public var guild_active:GuildActive;
		
		public var common_bg:MovieClip;

		public var guild_page:int;
		public var guild_sub_page:int;
		const c_guild_page_summary = 1;
		const c_guild_page_info = 2;
		const c_guild_page_manage = 3;
		const c_guild_page_foreign = 4;
		const c_guild_page_event = 5;

		override protected function configUI():void
		{
			ShowMode="BC";
			super.configUI();

			guild_main_summary_tab_mc.addEventListener(ButtonEvent.CLICK,onTabClickSummary, false, 0, true);
			guild_main_info_tab_mc.addEventListener(ButtonEvent.CLICK,onTabClickInfo, false, 0, true);
			guild_main_manage_tab_mc.addEventListener(ButtonEvent.CLICK,onTabClickManage, false, 0, true);
			guild_main_foreign_tab_mc.addEventListener(ButtonEvent.CLICK,onTabClickForeign, false, 0, true);
			guild_main_event_tab_mc.addEventListener(ButtonEvent.CLICK,onTabClickEvent, false, 0, true);
			
			guild_main_summary_tab_mc.groupName = "main";
			guild_main_info_tab_mc.groupName = "main";
			guild_main_manage_tab_mc.groupName = "main";
			guild_main_foreign_tab_mc.groupName = "main";
			guild_main_event_tab_mc.groupName = "main";

			guild_main_sub_tab_0_mc.addEventListener(ButtonEvent.CLICK, onTabClickSub0, false, 0, true);
			guild_main_sub_tab_1_mc.addEventListener(ButtonEvent.CLICK, onTabClickSub1, false, 0, true);
			guild_main_sub_tab_2_mc.addEventListener(ButtonEvent.CLICK, onTabClickSub2, false, 0, true);
			guild_main_sub_tab_3_mc.addEventListener(ButtonEvent.CLICK, onTabClickSub3, false, 0, true);
			guild_main_sub_tab_4_mc.addEventListener(ButtonEvent.CLICK, onTabClickSub4, false, 0, true);
			
			guild_main_sub_tab_0_mc.groupName = "sub";
			guild_main_sub_tab_1_mc.groupName = "sub";
			guild_main_sub_tab_2_mc.groupName = "sub";
			guild_main_sub_tab_3_mc.groupName = "sub";
			guild_main_sub_tab_4_mc.groupName = "sub";

			guild_summary_panel_mc.x = guild_main_bg_mc.x;
			guild_summary_panel_mc.y = guild_main_bg_mc.y;

			guild_info_full_member_mc.x = guild_main_bg_mc.x;
			guild_info_full_member_mc.y = guild_main_bg_mc.y;

			guild_info_pending_member_mc.x = guild_main_bg_mc.x;
			guild_info_pending_member_mc.y = guild_main_bg_mc.y;

			guild_rights_panel_mc.x = guild_main_bg_mc.x;
			guild_rights_panel_mc.y = guild_main_bg_mc.y;

			UCInitGuild(true);
/*			var i:int=0;
			var arr:Array=[];
			for(i;i<10;i++)
			{
				var obj:Object={};
				obj.guild_name="公会"+i;
				obj.guild_level=i;
				obj.guild_member_count=i;
				obj.guild_leader_name="玩家"+i;
				obj.guild_left_time="2011年"+i;
				arr.push(obj);
			}
			UCUpdateGuildApplyAllyList(arr);*/
		}
		// util
		public function showSummaryPanel(show:Boolean,index:int)
		{
			guild_summary_panel_mc.visible = show;
			common_bg.height=410;
			if (show)
			{
				guild_main_sub_tab_0_mc.visible = false;
				guild_main_sub_tab_1_mc.visible = false;
				guild_main_sub_tab_2_mc.visible = false;
				guild_main_sub_tab_3_mc.visible = false;
				guild_main_sub_tab_4_mc.visible = false;
			}
		}

		public function showInfoPanel(show:Boolean,index:int)
		{
			common_bg.height=410;
			if (!show)
			{
				guild_info_full_member_mc.visible = false;
				guild_info_pending_member_mc.visible = false;
				guild_money_panel_mc.visible = false;
			}
			else
			{
				guild_main_sub_tab_0_mc.visible = true;
				guild_main_sub_tab_1_mc.visible = true;
			    guild_main_sub_tab_2_mc.visible = true;
			    guild_main_sub_tab_3_mc.visible = false;
			    guild_main_sub_tab_4_mc.visible = false;
				
				guild_main_sub_tab_0_mc.selected = false;
				guild_main_sub_tab_1_mc.selected = false;
				guild_main_sub_tab_2_mc.selected = false;
			    guild_main_sub_tab_3_mc.selected = false;
			    guild_main_sub_tab_4_mc.selected = false;
				
				guild_main_sub_tab_0_mc.label = "正式成员";
				guild_main_sub_tab_1_mc.label = "待定成员";
				guild_main_sub_tab_2_mc.label = "资金记录";
				
				switch (index)
				{
				case 1 :
					guild_main_sub_tab_0_mc.selected = true;
					guild_info_full_member_mc.visible = true;
					guild_info_pending_member_mc.visible = false;
					guild_money_panel_mc.visible = false;
					break;
				case 2 :
					guild_main_sub_tab_1_mc.selected = true;
					guild_info_full_member_mc.visible = false;
					guild_info_pending_member_mc.visible = true;
					guild_money_panel_mc.visible = false;
					break;
				case 3 :
					guild_main_sub_tab_2_mc.selected = true;
					guild_info_full_member_mc.visible = false;
					guild_info_pending_member_mc.visible = false;
					guild_money_panel_mc.visible = true;
					break;
				}
				
				if (guild_info_pending_member_mc.visible == true)
				{
					ExternalInterface.call("ASUpdateGuildPendingMemberList");
				}
			}
		}

		public function showManagePanel(show:Boolean,index:int)
		{
			common_bg.height=410;
			if (! show)
			{
				guild_rights_panel_mc.visible = false;
				guild_storage_rights_panel.visible = false;
			}
			else
			{
				guild_main_sub_tab_0_mc.visible = true;
				guild_main_sub_tab_1_mc.visible = true;
			    guild_main_sub_tab_2_mc.visible = false;
			    guild_main_sub_tab_3_mc.visible = false;
			    guild_main_sub_tab_4_mc.visible = false;
				
				guild_main_sub_tab_0_mc.selected = false;
				guild_main_sub_tab_1_mc.selected = false;
				guild_main_sub_tab_2_mc.selected = false;
			    guild_main_sub_tab_3_mc.selected = false;
			    guild_main_sub_tab_4_mc.selected = false;
				
				guild_main_sub_tab_0_mc.label = "权限管理";
				guild_main_sub_tab_1_mc.label = "仓库管理";

				switch (index)
				{
					case 1 :
						guild_main_sub_tab_0_mc.selected = true;
						guild_rights_panel_mc.visible = true;
						guild_storage_rights_panel.visible = false;
						break;
					case 2 :
						guild_main_sub_tab_1_mc.selected = true;
						guild_rights_panel_mc.visible = false;
						guild_storage_rights_panel.visible = true;
						break;
				}
			}
		}

		public function showForeignPanel(show:Boolean,index:int)
		{
			common_bg.height=410;
			if (! show)
			{
				guild_foreign_info_panel_mc.visible = false;
				guild_apply_ally_panel_mc.visible = false;
				guild_war_panel_mc.visible = false;
				guild_search_panel_mc.visible = false;
			}
			else
			{
				guild_main_sub_tab_0_mc.visible = true;
				guild_main_sub_tab_1_mc.visible = true;
				guild_main_sub_tab_2_mc.visible = false;
			    guild_main_sub_tab_3_mc.visible = false;
			    guild_main_sub_tab_4_mc.visible = false;
				
				guild_main_sub_tab_0_mc.selected = false;
				guild_main_sub_tab_1_mc.selected = false;
				guild_main_sub_tab_2_mc.selected = false;
			    guild_main_sub_tab_3_mc.selected = false;
			    guild_main_sub_tab_4_mc.selected = false;
				
				guild_main_sub_tab_0_mc.label = "外交信息";
				guild_main_sub_tab_1_mc.label = "结盟消息";
				guild_main_sub_tab_2_mc.label = "公会宣战";
				guild_main_sub_tab_3_mc.label = "公会匹配战";

				switch (index)
				{
					case 1 :
						guild_main_sub_tab_0_mc.selected = true;
						guild_foreign_info_panel_mc.visible = true;
						guild_apply_ally_panel_mc.visible = false;
						guild_war_panel_mc.visible = false;
						guild_search_panel_mc.visible = false;
						break;
					case 2 :
						guild_main_sub_tab_1_mc.selected = true;
						guild_foreign_info_panel_mc.visible = false;
						guild_apply_ally_panel_mc.visible = true;
						guild_war_panel_mc.visible = false;
						guild_search_panel_mc.visible = false;
						break;
					case 3 :
						guild_main_sub_tab_2_mc.selected = true;
						guild_foreign_info_panel_mc.visible = false;
						guild_apply_ally_panel_mc.visible = false;
						guild_war_panel_mc.visible = true;
						guild_search_panel_mc.visible = false;
						break;
					case 4 :
						guild_main_sub_tab_3_mc.selected = true;
						guild_foreign_info_panel_mc.visible = false;
						guild_apply_ally_panel_mc.visible = false;
						guild_war_panel_mc.visible = false;
						guild_search_panel_mc.visible = false;
						break;
				}
			}
		}

		public function showEventPanel(show:Boolean,index:int):void
		{
			guild_active.visible = show;
			common_bg.height=440;
			if (show)
			{
				guild_main_sub_tab_0_mc.visible = false;
				guild_main_sub_tab_1_mc.visible = false;
				guild_main_sub_tab_2_mc.visible = false;
				guild_main_sub_tab_3_mc.visible = false;
				guild_main_sub_tab_4_mc.visible = false;
			}
		}

		public function showPage(page:int,subPage:int)
		{
			guild_page = page;
			
			showSummaryPanel(false,0);
			showInfoPanel(false,0);
			showManagePanel(false,0);
			showForeignPanel(false,0);
			showEventPanel(false,0);

			switch (page)
			{
				case c_guild_page_summary :
					showSummaryPanel(true,subPage);
					break;
				case c_guild_page_info :
					showInfoPanel(true,subPage);
					break;
				case c_guild_page_manage :
					showManagePanel(true,subPage);
					break;
				case c_guild_page_foreign :
					showForeignPanel(true,subPage);
					break;
				case c_guild_page_event :
					showEventPanel(true,subPage);
					break;
			}
			
			ExternalInterface.call("ASSetShowPage", page, subPage);
		}

		// event
		public function onTabClickSummary()
		{
			showPage(c_guild_page_summary,1);
		}

		public function onTabClickInfo()
		{
			showPage(c_guild_page_info,1);
		}

		public function onTabClickManage()
		{
			showPage(c_guild_page_manage,1);
		}

		public function onTabClickForeign()
		{
			showPage(c_guild_page_foreign,1);
		}

		public function onTabClickEvent()
		{
			showPage(c_guild_page_event,1);
		}

		public function onTabClickSub0()
		{
			showPage(guild_page,1);
		}

		public function onTabClickSub1()
		{
			showPage(guild_page,2);
		}

		public function onTabClickSub2()
		{
			showPage(guild_page,3);
		}

		public function onTabClickSub3()
		{
			showPage(guild_page,4);
		}

		public function onTabClickSub4()
		{
			showPage(guild_page,5);
		}

		// UC
		public function UCInitGuild(hasGuild:Boolean)
		{
			guild_main_summary_tab_mc.visible = hasGuild;
			guild_main_info_tab_mc.visible = hasGuild;
			guild_main_manage_tab_mc.visible = hasGuild;
			guild_main_foreign_tab_mc.visible = hasGuild;
			guild_main_event_tab_mc.visible = hasGuild;

			guild_main_sub_tab_0_mc.visible = hasGuild;
			guild_main_sub_tab_1_mc.visible = hasGuild;
			guild_main_sub_tab_2_mc.visible = hasGuild;
			guild_main_sub_tab_3_mc.visible = hasGuild;
			guild_main_sub_tab_4_mc.visible = hasGuild;

			guild_summary_panel_mc.visible = hasGuild;
			guild_info_full_member_mc.visible = hasGuild;
			guild_info_pending_member_mc.visible = hasGuild;
			guild_rights_panel_mc.visible = hasGuild;
			guild_storage_rights_panel.visible = hasGuild;
			guild_money_panel_mc.visible = hasGuild;
			guild_foreign_info_panel_mc.visible = hasGuild;
			guild_apply_ally_panel_mc.visible = hasGuild;
			guild_war_panel_mc.visible = hasGuild;
			guild_search_panel_mc.visible = hasGuild;
			guild_introduce_panel_mc.visible = ! hasGuild;
			guild_active.visible = hasGuild;

		}

		public function UCUpdateGuildActive(dat:Array):void
		{//更新公会活动
			guild_active.updateGuildActiveList(dat);
		}
		
		public function UCShowActiveOpenConfirm(dat:Object):void
		{//设置公会开启数据
		    guild_active.ShowGuildActiveConfirm(dat);
		}
		
		public function UCHideActiveOpenConfirm():void
		{
		    guild_active.HideGuildActiveConfirm();
		}

		public function UCUpdateGuildFullMemberList(data:Array)
		{
			guild_info_full_member_mc.updateGuildFullMemberList(data);
		}

		public function UCUpdateGuildPendingMemberList(data:Array)
		{
			guild_info_pending_member_mc.updateGuildPendingMemberList(data);
		}

		public function UCUpdateGuildBaseInfo(data:Object)
		{
			guild_summary_panel_mc.updateGuildBaseInfo(data);
			guild_info_full_member_mc.updateGuildBaseInfo(data);
			//guild_info_pending_member_mc.updateGuildBaseInfo(data);
			guild_rights_panel_mc.updateGuildBaseInfo(data);
			guild_storage_rights_panel.updateGuildBaseInfo(data);
			guild_foreign_info_panel_mc.updateGuildBaseInfo(data);
			guild_apply_ally_panel_mc.updateGuildBaseInfo(data);
		}

		public function UCUpdateGuildNotice(notice:String)
		{
			guild_summary_panel_mc.updateGuildNotice(notice);
		}

		public function UCUpdateGuildEvents(events:String)
		{
			guild_summary_panel_mc.updateGuildEvents(events);
		}
		
		public function UCUpdateGuildMoneyEvents(events:String)
		{
			guild_money_panel_mc.updateGuildMoneyEvents(events);
		}
		
		public function UCUpdateGuildRights(data:Object)
		{
			guild_rights_panel_mc.updateGuildRights(data);
		}

		public function UCUpdateGuildStorageRights(data:GuildStorageData, tips:String)
		{
			guild_storage_rights_panel.updateGuildStorageRights(data, tips);
		}

		public function UCUpdateGuildStorageState(data:Object)
		{
			guild_storage_rights_panel.updateGuildStorageState(data);
		}
		
		public function UCUpdateGuildSalary(data:Array)
		{
		}

		public function UCUpdateContributeInfo(money:int, inro:String)
		{
			guild_summary_panel_mc.updateContributeInfo(money, inro);
		}
		
		public function UCUpdateGuildAllyList(data:Array)
		{
			guild_foreign_info_panel_mc.updateGuildAllyList(data);
		}

		public function UCUpdateGuildEnemyList(data:Array)
		{
			guild_foreign_info_panel_mc.updateGuildEnemyList(data);
		}

		public function UCUpdateGuildApplyAllyList(data:Array)
		{
			guild_apply_ally_panel_mc.updateGuildApplyAllyList(data);
		}
		
		public function UCUpdateGuildWarInfo(data:Object)
		{
			guild_war_panel_mc.updateGuildWarInfo(data);
		}
		
		public function UCSetWindowTitle(title:String)
		{
			SetWindowTitle(title);
		}
		
		public function UCUpdateForeignApplyConsume(money:String)
		{
			guild_foreign_info_panel_mc.updateForeignApplyConsume(money);
		}
		
		public function UCUpdateGuildWarCD(time:String)
		{
			guild_war_panel_mc.updateGuildWarCD(time);
		}
		
		public function UCUpdateGuildWarSearchInfo(data:Object)
		{
			guild_search_panel_mc.updateGuildWarSearchInfo(data);
		}
		
		public function UCUpdateGuildWarSearchState(data:Object)
		{
			guild_search_panel_mc.updateGuildWarSearchState(data);
		}
		
		public function UCUpdateGuildIntroduce(intro:String)
		{
			guild_introduce_panel_mc.updateGuildIntroduce(intro);
		}
		
		public function UCShowGuildMainPage(page:int, subPage:int)
		{
			guild_main_summary_tab_mc.selected = false;
			guild_main_info_tab_mc.selected = false;
			guild_main_manage_tab_mc.selected = false;
			guild_main_foreign_tab_mc.selected = false;
			guild_main_event_tab_mc.selected = false;
				
			switch (page)
			{
				case c_guild_page_summary :
					guild_main_summary_tab_mc.selected = true;
					break;
				case c_guild_page_info :
					guild_main_info_tab_mc.selected = true;
					break;
				case c_guild_page_manage :
					guild_main_manage_tab_mc.selected = true;
					break;
				case c_guild_page_foreign :
					guild_main_foreign_tab_mc.selected = true;
					break;
				case c_guild_page_event :
					guild_main_event_tab_mc.selected = true;
					break;
			}
				
			showPage(page, subPage);
		}
		
		public function UCClear():void
		{
			guild_info_full_member_mc.clear();
		}
		
		public function UCSetMoreButtonState(bl:Boolean):void
		{
			guild_summary_panel_mc.SetMoreButtonState(bl);
		}
	}
}