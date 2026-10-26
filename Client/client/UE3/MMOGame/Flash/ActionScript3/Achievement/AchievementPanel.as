//
//成就系统主面板
//
package ActionScript3.Achievement
{
	import flash.display.DisplayObject;
	import flash.display.MovieClip;
	import flash.events.Event;
	import flash.events.KeyboardEvent;
	import flash.events.MouseEvent;
	import flash.external.ExternalInterface;
	import flash.text.TextField;
	import flash.text.TextFieldAutoSize;
	import flash.utils.getDefinitionByName;
	
	import ActionScript3.MyPanel;
	import ActionScript3.MyScrollBar;
	import ActionScript3.MyScrollPanel;
	import ActionScript3.MyTipButtonNew;
	import ActionScript3.TreeListData;
	import ActionScript3.Common.CustomScrollBar;
	import ActionScript3.Common.Utils.ConfigConstants;
	
	import scaleform.clik.constants.InvalidationType;
	import scaleform.clik.controls.Button;
	import scaleform.clik.controls.ListItemRenderer;
	import scaleform.clik.controls.RadioButton;
	import scaleform.clik.controls.ScrollBar;
	import scaleform.clik.controls.ScrollingList;
	import scaleform.clik.core.UIComponent;
	import scaleform.clik.data.DataProvider;
	import scaleform.clik.data.TreeDataProvider;
	import scaleform.clik.events.ButtonEvent;
	import scaleform.clik.events.ListEvent;
	import scaleform.clik.events.SliderEvent;
	import scaleform.clik.utils.Padding;

	public class AchievementPanel extends MyPanel
	{
		public var achievement_personal_tab_mc:RadioButton;
		public var achievement_guild_tab_mc:RadioButton;
		
		public var achievement_point_type_tf:TextField;
		public var achievement_point_tf:TextField;
		public var achievement_cateory_tree_mc:ScrollingList;
		public var achievement_summary_panel_mc:AchievementSummaryPanel;
		public var achievement_list_panel_mc:AchievementListPanel;
		//public var achievement_stat_list_panel_mc:AchievementStatListPanel;
		public var achievement_cateory_scroll_bar_mc:CustomScrollBar;
		
		const c_cateory_type_achievement = 0;
		const c_cateory_type_guild = 1;
		public var achievement_cateory_type;
		
		// test
		public var personal_cate_item_data:Array;
		public var item_data_stat:Array;

		protected var _localTest:Boolean = false;
		
		override protected function configUI():void
		{
			ShowMode =  ConfigConstants.PANEL_SHOW_MODE_BC;
			super.configUI();
			//ExternalInterface.call( "ASRegisterAchievementPanel", this);
			//achievement_personal_tab_mc.icon_mc.loader_mc.source = "img://MMO_UIImg.img_tab_archievement_0";
			//achievement_stat_tab_mc.icon_mc.loader_mc.source = "img://MMO_UIImg.img_tab_archievement_1";
			achievement_personal_tab_mc.addEventListener(MouseEvent.CLICK, onTabClickAchievementPersonal);
			achievement_guild_tab_mc.addEventListener(MouseEvent.CLICK, onTabClickAchievementGuild);
			achievement_personal_tab_mc.selected = true;
			
			achievement_cateory_tree_mc.selectedIndex = 0;
			achievement_cateory_tree_mc.addEventListener(ListEvent.INDEX_CHANGE, onListItemChange, false, 0, true);
			achievement_cateory_tree_mc.addEventListener(ListEvent.ITEM_CLICK, onListItemClick, false, 0, true);
			achievement_cateory_tree_mc.addEventListener(ListEvent.ITEM_ROLL_OVER, onListItemRollOver, false, 0, true);
			achievement_cateory_tree_mc.addEventListener(ListEvent.ITEM_ROLL_OUT, onListItemRollOut, false, 0, true);
		
			achievement_cateory_type = c_cateory_type_achievement;
			
			achievement_summary_panel_mc.visible = true;
			achievement_list_panel_mc.visible = false;
			
			if(!_localTest){
				return;
			}
			// test
			
			/*personal_cate_item_data = new Array();
			var achievement_cate_data:AchievementData = null;
			
			achievement_cate_data = new AchievementData;
			achievement_cate_data.label = "第" + 0 + "级";
			achievement_cate_data.index = 0;
			achievement_cate_data.type = 1;
			achievement_cate_data.deepth = 0;
			achievement_cate_data.visible = true;
			achievement_cate_data.baseClass = 0;		
			achievement_cate_data.subClass = 0;
			achievement_cate_data.isSelected = false;
			personal_cate_item_data.push(achievement_cate_data);
			
			achievement_cate_data = new AchievementData;
			achievement_cate_data.label = "第" + 1 + "级";
			achievement_cate_data.index = 1;
			achievement_cate_data.type = 1;
			achievement_cate_data.deepth = 0;
			achievement_cate_data.visible = true;
			achievement_cate_data.baseClass = 0;		
			achievement_cate_data.subClass = 0;
			achievement_cate_data.isSelected = false;
			personal_cate_item_data.push(achievement_cate_data);
			
			achievement_cate_data = new AchievementData;
			achievement_cate_data.label = "第" + 2 + "级";
			achievement_cate_data.index = 2;
			achievement_cate_data.type = 1;
			achievement_cate_data.deepth = 1;
			achievement_cate_data.visible = true;
			achievement_cate_data.baseClass = 0;		
			achievement_cate_data.subClass = 1;
			achievement_cate_data.isSelected = false;
			personal_cate_item_data.push(achievement_cate_data);
			
			achievement_cate_data = new AchievementData;
			achievement_cate_data.label = "第" + 3 + "级";
			achievement_cate_data.index = 3;
			achievement_cate_data.type = 1;
			achievement_cate_data.deepth = 1;
			achievement_cate_data.visible = true;
			achievement_cate_data.baseClass = 0;		
			achievement_cate_data.subClass = 2;
			achievement_cate_data.isSelected = false;
			personal_cate_item_data.push(achievement_cate_data);
			
			achievement_cate_data = new AchievementData;
			achievement_cate_data.label = "第" + 4 + "级";
			achievement_cate_data.index = 4;
			achievement_cate_data.type = 1;
			achievement_cate_data.deepth = 0;
			achievement_cate_data.visible = true;
			achievement_cate_data.baseClass = 1;		
			achievement_cate_data.subClass = 0;
			achievement_cate_data.isSelected = false;
			personal_cate_item_data.push(achievement_cate_data);
			
			achievement_cate_data = new AchievementData;
			achievement_cate_data.label = "第" + 5 + "级";
			achievement_cate_data.index = 5;
			achievement_cate_data.type = 1;
			achievement_cate_data.deepth = 1;
			achievement_cate_data.visible = true;
			achievement_cate_data.baseClass = 1;		
			achievement_cate_data.subClass = 1;
			achievement_cate_data.isSelected = false;
			personal_cate_item_data.push(achievement_cate_data);
			
			achievement_cate_data = new AchievementData;
			achievement_cate_data.label = "第" + 6 + "级";
			achievement_cate_data.index = 6;
			achievement_cate_data.type = 1;
			achievement_cate_data.deepth = 1;
			achievement_cate_data.visible = true;
			achievement_cate_data.baseClass = 1;		
			achievement_cate_data.subClass = 2;
			achievement_cate_data.isSelected = false;
			personal_cate_item_data.push(achievement_cate_data);
				
			
			achievement_cate_data = new AchievementData;
			achievement_cate_data.label = "第" + 7 + "级";
			achievement_cate_data.index = 7;
			achievement_cate_data.type = 1;
			achievement_cate_data.deepth = 1;
			achievement_cate_data.visible = true;
			achievement_cate_data.baseClass = 1;		
			achievement_cate_data.subClass = 2;
			achievement_cate_data.isSelected = false;
			personal_cate_item_data.push(achievement_cate_data);
			
			
			achievement_cate_data = new AchievementData;
			achievement_cate_data.label = "第" + 8 + "级";
			achievement_cate_data.index = 8;
			achievement_cate_data.type = 1;
			achievement_cate_data.deepth = 1;
			achievement_cate_data.visible = true;
			achievement_cate_data.baseClass = 1;		
			achievement_cate_data.subClass = 2;
			achievement_cate_data.isSelected = false;
			personal_cate_item_data.push(achievement_cate_data);
			
			
			achievement_cate_data = new AchievementData;
			achievement_cate_data.label = "第" + 9 + "级";
			achievement_cate_data.index = 9;
			achievement_cate_data.type = 1;
			achievement_cate_data.deepth = 1;
			achievement_cate_data.visible = true;
			achievement_cate_data.baseClass = 1;		
			achievement_cate_data.subClass = 2;
			achievement_cate_data.isSelected = false;
			personal_cate_item_data.push(achievement_cate_data);
			
			
			achievement_cate_data = new AchievementData;
			achievement_cate_data.label = "第" + 10 + "级";
			achievement_cate_data.index = 10;
			achievement_cate_data.type = 1;
			achievement_cate_data.deepth = 1;
			achievement_cate_data.visible = true;
			achievement_cate_data.baseClass = 1;		
			achievement_cate_data.subClass = 2;
			achievement_cate_data.isSelected = false;
			personal_cate_item_data.push(achievement_cate_data);
			
			
			achievement_cate_data = new AchievementData;
			achievement_cate_data.label = "第" + 11 + "级";
			achievement_cate_data.index = 11;
			achievement_cate_data.type = 1;
			achievement_cate_data.deepth = 1;
			achievement_cate_data.visible = true;
			achievement_cate_data.baseClass = 1;		
			achievement_cate_data.subClass = 2;
			achievement_cate_data.isSelected = false;
			personal_cate_item_data.push(achievement_cate_data);
			
			
			achievement_cate_data = new AchievementData;
			achievement_cate_data.label = "第" + 12 + "级";
			achievement_cate_data.index = 12;
			achievement_cate_data.type = 1;
			achievement_cate_data.deepth = 1;
			achievement_cate_data.visible = true;
			achievement_cate_data.baseClass = 1;		
			achievement_cate_data.subClass = 2;
			achievement_cate_data.isSelected = false;
			personal_cate_item_data.push(achievement_cate_data);
			
			
			achievement_cate_data = new AchievementData;
			achievement_cate_data.label = "第" + 13 + "级";
			achievement_cate_data.index = 13;
			achievement_cate_data.type = 1;
			achievement_cate_data.deepth = 1;
			achievement_cate_data.visible = true;
			achievement_cate_data.baseClass = 1;		
			achievement_cate_data.subClass = 2;
			achievement_cate_data.isSelected = false;
			personal_cate_item_data.push(achievement_cate_data);
			
			achievement_cate_data = new AchievementData;
			achievement_cate_data.label = "第" + 14 + "级";
			achievement_cate_data.index = 14;
			achievement_cate_data.type = 1;
			achievement_cate_data.deepth = 1;
			achievement_cate_data.visible = true;
			achievement_cate_data.baseClass = 1;		
			achievement_cate_data.subClass = 2;
			achievement_cate_data.isSelected = false;
			personal_cate_item_data.push(achievement_cate_data);
			
			achievement_cate_data = new AchievementData;
			achievement_cate_data.label = "第" + 15 + "级";
			achievement_cate_data.index = 15;
			achievement_cate_data.type = 1;
			achievement_cate_data.deepth = 1;
			achievement_cate_data.visible = true;
			achievement_cate_data.baseClass = 1;		
			achievement_cate_data.subClass = 2;
			achievement_cate_data.isSelected = false;
			personal_cate_item_data.push(achievement_cate_data);
			
			item_data_stat = new Array();
			item_data_stat.push({label:"角色", type:0, deepth:0, visible:true });
			item_data_stat.push({label:"声望", type:0, deepth:0, visible:true });
			item_data_stat.push({label:"装备", type:0, deepth:0, visible:true });
			item_data_stat.push({label:"货币", type:0, deepth:0, visible:true });
			item_data_stat.push({label:"消耗", type:0, deepth:0, visible:true });
			item_data_stat.push({label:"拍卖行", type:0, deepth:0, visible:true });
			item_data_stat.push({label:"死亡", type:0, deepth:0, visible:true });
			item_data_stat.push({label:"任务", type:0, deepth:0, visible:true });
			item_data_stat.push({label:"战斗", type:0, deepth:0, visible:true });
		
			UCUpdateCagetoryData(personal_cate_item_data);
			testUpdateListItemPanelData();*/
			trace("<<<<<<<<<<<<<<< AchievementPanel::configUI");
		}
		
		public function testUpdateListItemPanelData():void
		{
			if(!_localTest){
				return;
			}
			var itemNum:int = 1 + int(10 * Math.random());
			var achievement_list:Array = new Array();
			
			var achievement_data:Object = new Object;
			achievement_data.label = "";
			achievement_data.index = 1;
			achievement_data.type = 1;
			achievement_data.deepth = 1;
			achievement_data.visible = true;
			achievement_data.achievement_is_pre_obtain = true;
			achievement_data.achievement_icon = "1_109.TGA";
			achievement_data.achievement_is_obtain = false;
			achievement_data.achievement_name = "测试1";
			achievement_data.achievement_desc = "测试1";
			achievement_data.achievement_point = 20;
			achievement_data.achievement_date = "2014.5.19";
			achievement_data.achievement_icon_comp = "1_109.TGA";
			achievement_data.achievement_date_comp = "2014.5.19";
			
			achievement_data.achievement_detail = 1;
			achievement_data.achievement_condition_name0 = "测试0"
			achievement_data.achievement_condition_complete0 = true;
			achievement_data.achievement_condition_name1 = "测试1"
			achievement_data.achievement_condition_complete1 = true;
			achievement_data.achievement_condition_name2 = "测试2"
			achievement_data.achievement_condition_complete2 = true;
			achievement_data.achievement_condition_name3 = "测试3"
			achievement_data.achievement_condition_complete3 = true;
			achievement_data.achievement_condition_name4 = "测试4"
			achievement_data.achievement_condition_complete4 = true;
			achievement_data.achievement_condition_name5 = "测试5"
			achievement_data.achievement_condition_complete5 = true;
			achievement_data.achievement_condition_name6 = "测试6"
			achievement_data.achievement_condition_complete6 = true;
			achievement_data.achievement_condition_name7 = "测试7"
			achievement_data.achievement_condition_complete7 = true;
			
			achievement_data.achievement_reward_type = 2;
			achievement_data.achievement_reward_id = 1011101;
			achievement_data.achievement_reward_icon = "1_109.TGA";
			achievement_list.push(achievement_data);
			
			for(var i:int = 1; i < itemNum; i++)
			{
				achievement_data = new Object;
				achievement_data.label = "";
				achievement_data.index = i + 1;
				achievement_data.type = 1;
				achievement_data.deepth = 1;
				achievement_data.visible = true;
				achievement_data.achievement_is_pre_obtain = true;
				achievement_data.achievement_icon = "1_109.TGA";
				achievement_data.achievement_is_obtain = true;
				achievement_data.achievement_name = "测试" + (i + 1);
				achievement_data.achievement_desc = "测试" + (i + 1);
				achievement_data.achievement_point = 20;
				achievement_data.achievement_date = "2014.5.19";
				achievement_data.achievement_icon_comp = "1_109.TGA";
				achievement_data.achievement_date_comp = "2014.5.19";
				
				achievement_data.achievement_detail = 2;
				achievement_data.achievement_progress_cur = 50;
				achievement_data.achievement_progress_max = 100;
				
				achievement_list.push(achievement_data);
			}
			
			UCSetState(true);
			UCShowAchievementList();
			UCUpdateAchievementList(achievement_list);
		}
		
		//
		// event function 
		//
		public function onTabClickAchievementPersonal()
		{
			achievement_point_type_tf.text = "成就点数";
			achievement_summary_panel_mc.visible = true;
			achievement_list_panel_mc.visible = false;
			//achievement_stat_list_panel_mc.visible = false;
			
			achievement_cateory_type = c_cateory_type_achievement;
			ExternalInterface.call("ASUpdateCagetoryData", c_cateory_type_achievement);
			ExternalInterface.call("ASUpdateSummaryData", c_cateory_type_achievement);
			ExternalInterface.call("ASUpdateAchievementData", 0, 1);
		}

		public function onTabClickAchievementGuild()
		{
			achievement_point_type_tf.text = "公会成就";
			achievement_summary_panel_mc.visible = true;
			achievement_list_panel_mc.visible = false;
			//achievement_stat_list_panel_mc.visible = false;
			
			achievement_cateory_type = c_cateory_type_guild;
			ExternalInterface.call("ASUpdateCagetoryData", c_cateory_type_guild);
			ExternalInterface.call("ASUpdateSummaryData", c_cateory_type_guild);
			ExternalInterface.call("ASUpdateAchievementData", 0, 1);
		}

		public function onListItemChange( event:Event ):void
		{
			var list:ScrollingList = event.target as ScrollingList;
			if (list != null)
			{
				list.invalidateData();
			}
		}

		public function onListItemClick(event:ListEvent):void
		{
			var list:ScrollingList = event.target as ScrollingList;
			if (list != null)
			{
				var provider:TreeDataProvider = list.dataProvider as TreeDataProvider;
				if (provider!=null)
				{
					provider.handleListItemClick( event );
					
					if (true)//achievement_stat_list_panel_mc.visible == false
					{
						var obj:AchievementData = provider.requestItemAt(event.index) as AchievementData;
						var i:int;
						var item:AchievementData;

						if (obj.index == 0)
						{
							for(i = 0; i < provider.length; ++i)
							{
								item = provider.requestItemAt(i) as AchievementData;
								if(item != null)
								{
									item.isSelected = false;
								}
							}
							
							obj.isSelected = true;
							achievement_cateory_tree_mc.validateNow();
							achievement_cateory_tree_mc.invalidateData();
							
							achievement_summary_panel_mc.visible = true;
							achievement_list_panel_mc.visible = false;
							//achievement_stat_list_panel_mc.visible = false;
							
							ExternalInterface.call("ASUpdateSummaryData", achievement_cateory_type);
						}
						else if (obj.deepth == 0)
						{
							for(i = 0; i < provider.length; ++i)
							{
								item = provider.requestItemAt(i) as AchievementData;
								if(item != null)
								{
									item.isSelected = false;
								}
							}
							
							achievement_cateory_tree_mc.validateNow();
							achievement_cateory_tree_mc.invalidateData();
							
							for(i = 0; i < provider.length; ++i)
							{
								item = provider.requestItemAt(i) as AchievementData;
								if(item != null)
								{
									if (item.deepth == 1 && item.visible == true && item.baseClass == obj.baseClass)
									{
										obj.isSelected = true;
									}
								}
							}
						}
						else if (obj.deepth == 1)
						{
							for(i = 0; i < provider.length; ++i)
							{
								item = provider.requestItemAt(i) as AchievementData;
								if(item != null)
								{
									item.isSelected = false;
									if (item.deepth == 0 && item.baseClass == obj.baseClass)
									{
										item.isSelected = true;
									}
								}
							}

							obj.isSelected = true;
							achievement_cateory_tree_mc.validateNow();
							achievement_cateory_tree_mc.invalidateData();
							
							achievement_summary_panel_mc.visible = false;
							achievement_list_panel_mc.visible = true;
							//achievement_stat_list_panel_mc.visible = false;
							
							ExternalInterface.call("ASUpdateAchievementData", obj.baseClass, obj.subClass);
							ExternalInterface.call("ASUpdateAchievementList", obj.baseClass, obj.subClass);
							//
							//testUpdateListItemPanelData();
						}
					}
					else
					{
						var stat_data:Object = provider.requestItemAt(event.index);
						ExternalInterface.call("ASUpdateStatList", stat_data.statClass);
					}
				}
				
				list.validateNow();
			}
		}

		public function onListItemRollOver(event:ListEvent ):void
		{
		}

		public function onListItemRollOut(event:ListEvent ):void
		{
		}
		
		//
		// call from UC
		//
		public function UCSetState(compare:Boolean)
		{
			if (compare)
			{
				achievement_summary_panel_mc.visible = false;
				achievement_list_panel_mc.visible = true;
			}
			
			//achievement_stat_list_panel_mc.visible = false;
			achievement_list_panel_mc.setState(compare);
		}
		
		public function UCUpdateCagetoryData(data:Array)
		{
			achievement_cateory_tree_mc.dataProvider = new TreeDataProvider(data);
			achievement_cateory_tree_mc.validateNow();
			achievement_cateory_tree_mc.invalidateData();
		}
		
		public function UCUpdateCagetoryComplete(baseClass:int, baseCount:int, subClass:int, subCount:int):void
		{
			var provider:TreeDataProvider = achievement_cateory_tree_mc.dataProvider as TreeDataProvider;
			var source:Array = provider.getRoot();
			var len:int = source.length;
			var itemData:AchievementData;
			for(var i:int = 0; i < len; i++)
			{
				itemData = source[i] as AchievementData;
				if(itemData != null)
				{
					if(itemData.baseClass == baseClass)
					{
						if(itemData.deepth == 0)
						{
							itemData.percent = baseCount.toString();
						}
						else if(itemData.deepth == 1)
						{
							if(itemData.subClass == subClass)
							{
								itemData.percent = "(" + subCount + ")";
							}
						}
					}
				}
			}
			achievement_cateory_tree_mc.validateNow();
		}
		
		public function UCUpdateAchievementSummaryData(cur_total:int, max_total:int, sub_data:Array, recent_title:String, recent_data:Array)
		{
			achievement_summary_panel_mc.setTotal(cur_total, max_total);
			achievement_summary_panel_mc.setDetail(sub_data);
			achievement_summary_panel_mc.setRecent(recent_title, recent_data);
		}
		
		public function UCUpdateAchievementData(roleName:String, point:int, complete:int, total:int, roleNameComp:String, pointComp:int, completeComp:int, totalComp:int)
		{
			achievement_point_tf.text = String(point);
			achievement_list_panel_mc.updateData(roleName, point, complete, total, roleNameComp, pointComp, completeComp, totalComp);
		}
		
		public function UCUpdateAchievementList(data:Array)
		{
			achievement_list_panel_mc.updateList(data);
		}
		
		// 这个只用来更新当前列表的数据,不重建列表
		public function UCUpdateAchievementListData(data:Array)
		{
			achievement_list_panel_mc.updateListData(data);
		}
		
		public function UCUpdateStatList(data:Array)
		{
			//achievement_stat_list_panel_mc.updateList(data);
		}
		
		public function UCShowAchievementSummary()
		{
			achievement_summary_panel_mc.visible = true;
			achievement_list_panel_mc.visible = false;
			//achievement_stat_list_panel_mc.visible = false;
		}
		
		public function UCShowAchievementList()
		{
			achievement_summary_panel_mc.visible = false;
			achievement_list_panel_mc.visible = true;
			//achievement_stat_list_panel_mc.visible = false;
		}
		
		public function UCShowAchievementListItem(id:int)
		{
			achievement_summary_panel_mc.visible = false;
			achievement_list_panel_mc.visible = true;
			//achievement_stat_list_panel_mc.visible = false;
			
			achievement_list_panel_mc.scrollList(id);
		}
		
		public function UCSetWindowTitle(title:String)
		{
			SetWindowTitle(title);
		}
		
		public function UCHasGuild(hasGuild:Boolean):void
		{
			achievement_guild_tab_mc.visible = hasGuild;
		}
		
		public function UCUpdateSelectedTab(cateory_type:int):void
		{
			if(cateory_type == c_cateory_type_achievement)
			{
				achievement_personal_tab_mc.selected = true;
				achievement_guild_tab_mc.selected = false;
			}
			else if(cateory_type == c_cateory_type_guild)
			{
				achievement_personal_tab_mc.selected = false;
				achievement_guild_tab_mc.selected = true;
			}
		}
	}
}
