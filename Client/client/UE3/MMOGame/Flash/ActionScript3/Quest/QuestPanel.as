package ActionScript3.Quest
{
	import ActionScript3.MyPanel;
	import flash.external.ExternalInterface;
	import flash.events.MouseEvent;
	import flash.display.MovieClip;
	import scaleform.clik.core.UIComponent;
	import flash.text.TextField;
	import scaleform.clik.controls.Button;
	import scaleform.clik.events.ListEvent;
	import scaleform.clik.controls.ScrollingList;
	import scaleform.gfx.Extensions;
	import scaleform.clik.motion.Tween;
	import fl.transitions.easing.*;
	import ActionScript3.MyScrollBar;
	import scaleform.clik.controls.ScrollingView;
	import scaleform.clik.controls.RadioButton;
	import scaleform.clik.events.ButtonEvent;

	public class QuestPanel extends MyPanel
	{
		public static const c_group_accepted = 0;
		public static const c_group_available = 1;
		public static const c_group_completed = 2;

		public var quest_accepted_tab_mc:RadioButton;
		public var quest_available_tab_mc:RadioButton;
		public var quest_completed_tab_mc:RadioButton;
		
		public var quest_list_mc:ScrollingList;
		public var quest_detail_mc:QuestDetailPage;
		public var quest_detail_sb_mc:MyScrollBar;
		
		public var quest_share_bt_mc:Button;
		public var quest_abort_bt_mc:Button;
		public var quest_accept_bt_mc:Button;
		public var quest_complete_bt_mc:Button;
		
		public var quest_complete_tf:TextField;
		public var quest_trace_cb_mc:Button;
		public var quest_low_level_filter_cb_mc:Button;
		
		public var quest_group:int;
		public var quest_id:int;
		
		public var testMC:RadioButton;
		
		public var _scrollingView:ScrollingView;
		
		public var _noTask:MovieClip;
		public var _taskbg:MovieClip;

		override protected function configUI():void
		{
			ShowMode="BC";
			super.configUI();
			
			quest_accepted_tab_mc.addEventListener(ButtonEvent.CLICK, onTabClickAcceptedQuest);
			quest_available_tab_mc.addEventListener(ButtonEvent.CLICK, onTabClickAvailableQuest);
			quest_completed_tab_mc.addEventListener(ButtonEvent.CLICK, onTabClickCompletedQuest);
			
			quest_completed_tab_mc.visible = false;
			_noTask.visible=false;

			quest_list_mc.addEventListener(ListEvent.ITEM_CLICK, onListItemClick);
			quest_detail_mc.setupScrollBar(this.quest_detail_sb_mc);

			quest_trace_cb_mc.addEventListener(MouseEvent.CLICK, onToggleTraceAll);
			quest_low_level_filter_cb_mc.addEventListener(MouseEvent.CLICK, onToggleFilterLowLevel);

			quest_share_bt_mc.addEventListener(MouseEvent.CLICK, onBtClickShareQuest);
			quest_abort_bt_mc.addEventListener(MouseEvent.CLICK, onBtClickAbortQuest);
			quest_accept_bt_mc.addEventListener(MouseEvent.CLICK, onBtClickAcceptQuest);
			quest_complete_bt_mc.addEventListener(MouseEvent.CLICK, onBtClickCompleteQuest);
			quest_accept_bt_mc.visible = false;
			quest_complete_bt_mc.visible = false;

			quest_accepted_tab_mc.selected = true;
			quest_group = c_group_accepted;
			quest_id = 0;
			quest_low_level_filter_cb_mc.selected = false;
			_scrollingView.displayMc=quest_detail_mc;
            quest_share_bt_mc.enabled=false;
			// clear the list
			UCUpdateQuestList(new Array(), 0, 0);
           //testData();
		}

		private function onTabClickAcceptedQuest(evt:ButtonEvent):void
		{
			this.quest_group = c_group_accepted;
			ExternalInterface.call("ASUpdateQuestList", c_group_accepted);
		}

		private function onTabClickAvailableQuest(evt:ButtonEvent):void
		{
			this.quest_group = c_group_available;
			ExternalInterface.call("ASUpdateQuestList", c_group_available);
		}

		private function onTabClickCompletedQuest(evt:ButtonEvent):void
		{
			this.quest_group = c_group_completed;
			ExternalInterface.call("ASUpdateQuestList", c_group_completed);
		}

		private function onListItemClick( event:ListEvent ):void
		{
			var list:ScrollingList = event.target as ScrollingList;
			if (list != null)
			{
				var provider:QuestDataProvider = list.dataProvider as QuestDataProvider;
				if (provider != null)
				{
					var quest_data:QuestData = provider.requestItemAt(event.index) as QuestData;
					if(quest_data != null)					
					{
						if (quest_data.quest_item_type == QuestData.quest_item_type_group)
						{
							quest_data.quest_is_expanded = !quest_data.quest_is_expanded; 
							//event.itemRenderer.selected = !event.itemRenderer.selected;
						}
						else
						{
							if (quest_data.quest_id > 0)
							{
								quest_id = quest_data.quest_id;
						
								var cnt:int = provider.length;
								for(var i:int = 0; i < cnt; ++i)
								{
									var dat:QuestData = provider.requestItemAt(i) as QuestData;
									if(dat != null)
									{
										dat.quest_is_select = false;
									}
								}
			
								quest_data.quest_is_select = true;
							
								quest_share_bt_mc.enabled = quest_data.quest_can_share;
								quest_abort_bt_mc.enabled = quest_data.quest_can_abort;
			
								quest_list_mc.validateNow();
								quest_list_mc.invalidateData();
			
								ExternalInterface.call("ASUpdateQuestDetail", quest_data.quest_id);
							}
						}
					}
					provider.validateLength();
				}
				list.invalidateData();
			}
		}

		private function onToggleTraceAll(evt:MouseEvent):void
		{
			ExternalInterface.call("ASTraceAllQuest", this.quest_trace_cb_mc.selected);
			var cnt:int = quest_list_mc.dataProvider.length;
			for(var i:int = 0; i < cnt; ++i)
			{
				var quest_data:QuestData = quest_list_mc.dataProvider.requestItemAt(i) as QuestData;
				if(quest_data != null)
				{
					quest_data.quest_is_traced = this.quest_trace_cb_mc.selected;
				}
			}
			quest_list_mc.validateNow();
			quest_list_mc.invalidateData();			
		}
		
		private function onToggleFilterLowLevel():void
		{
			ExternalInterface.call("ASFilterLowLevelQuest", this.quest_low_level_filter_cb_mc.selected);
		}
		
		private function onBtClickShareQuest(evt:MouseEvent):void
		{
			if (quest_id > 0)
			{
				ExternalInterface.call("ASShareQuest", quest_id);
			}
		}

		private function onBtClickAbortQuest(evt:MouseEvent):void
		{
			if (quest_id > 0)
			{
				ExternalInterface.call("ASAbortQuest", quest_id);
			}
		}

		private function onBtClickAcceptQuest(evt:MouseEvent):void
		{
			if (quest_id > 0)
			{
				ExternalInterface.call("ASAcceptQuestWithoutNpc", quest_id);
			}
		}
		
		private function onBtClickCompleteQuest(evt:MouseEvent):void
		{
			if (quest_id > 0)
			{
				ExternalInterface.call("ASCompleteQuestWithoutNpc", quest_id);
			}
		}
			
		public function UCUpdateQuestList(list:Array, complete:int, total:int):void
		{
			if(list && list.length>0)
			{
				_noTask.visible=false;
				_taskbg.visible=true;
				quest_detail_mc.visible=true;
				quest_list_mc.visible=true;
				quest_detail_sb_mc.visible=true;
			}
			else
			{
				_noTask.visible=true;
				_taskbg.visible=false;
				quest_detail_mc.visible=false;
				quest_list_mc.visible=false;
				quest_detail_sb_mc.visible=false;
			}
			quest_detail_sb_mc.position=0;
			quest_list_mc.dataProvider = new QuestDataProvider(list);
			quest_list_mc.validateNow();
			quest_list_mc.invalidateData();
			//quest_complete_tf.text = "(" + String(complete) + "/" + String(total) + ")";
		}
		
		public function UCUpdateQuestDetailData(detail_data:QuestDetailData):void
		{
			if (detail_data)
			{
				this.quest_id = detail_data.quest_id;
				this.quest_detail_mc.visible = true;
				this.quest_detail_mc.updateQuestDetailData(detail_data);
				
				if (detail_data.quest_is_accepted)
				{
					quest_accepted_tab_mc.selected = true;
					quest_available_tab_mc.selected = false;
					quest_completed_tab_mc.selected = false;
				}
				if (detail_data.quest_is_available)
				{
					quest_accepted_tab_mc.selected = false;
					quest_available_tab_mc.selected = true;
					quest_completed_tab_mc.selected = false;
				}
				else if (detail_data.quest_is_completed)
				{
					quest_accepted_tab_mc.selected = false;
					quest_available_tab_mc.selected = false;
					quest_completed_tab_mc.selected = true;
				}
				
				if (detail_data.quest_without_npc)
				{
					quest_share_bt_mc.visible = false;
					quest_abort_bt_mc.visible = false;
					if (detail_data.quest_is_available)
					{
						quest_accept_bt_mc.visible = true;
						quest_complete_bt_mc.visible = false;
					}
					else if (detail_data.quest_is_compassable)
					{
						quest_accept_bt_mc.visible = false;
						quest_complete_bt_mc.visible = true;
					}
				}
				else
				{
					// 可以直接接取/完成的任务
					quest_share_bt_mc.visible = true;
					quest_abort_bt_mc.visible = true;
					
					if (detail_data.quest_is_completed)
					{
						quest_accept_bt_mc.visible = false;
						quest_complete_bt_mc.visible = false;
					}
					
					quest_accept_bt_mc.visible = false;
					quest_complete_bt_mc.visible = false;
				}
			}
			else
			{
				this.quest_detail_mc.visible = false;
			}
		}
		public function UCSetWindowTitle(title:String):void
		{
			SetWindowTitle(title);
		}
		
/*		private function testData():void
		{
						// list test
			var i:int = 0;
			var quest_data:QuestData = null;
			var itemsData:Array = new Array;
	
			quest_data = new QuestData  ;
			quest_data.quest_item_type = QuestData.quest_item_type_group;
			quest_data.quest_caption = "Trunk Quest";
			quest_data.quest_is_expanded = true;
			itemsData.push(quest_data);
				
			// trunk
			for (i = 1; i < 20; i++)
			{
				quest_data = new QuestData  ;
				quest_data.quest_item_type = QuestData.quest_item_type_item;
				quest_data.quest_id = i;
				quest_data.quest_is_compassable = (i % 3) == 0;
				quest_data.quest_type = QuestData.quest_type_trunk;
				quest_data.quest_caption = "【主线】Trunk Quest" + i;
				quest_data.quest_can_abort = i % 2 == 0;
				quest_data.quest_can_share = i % 3 == 0;
								quest_data.quest_is_traceable=true;
				quest_data.quest_is_traced=true;
				itemsData.push(quest_data);
			}

			quest_data = new QuestData  ;
			quest_data.quest_item_type = QuestData.quest_item_type_group;
			quest_data.quest_caption = "Branch Quest";
			quest_data.quest_is_expanded = false;
			itemsData.push(quest_data);
				
			// branch
			for (i = 20; i < 30; i++)
			{
				quest_data = new QuestData;
				quest_data.quest_item_type = QuestData.quest_item_type_item;
				quest_data.quest_id = i;
				quest_data.quest_type = QuestData.quest_type_branch;
				quest_data.quest_caption = "【支线】Branch Quest" + i;
								quest_data.quest_is_traceable=true;
				quest_data.quest_is_traced=true;
				itemsData.push(quest_data);
			}

			quest_data = new QuestData;
			quest_data.quest_item_type = QuestData.quest_item_type_group;
			quest_data.quest_caption = "Daily Quest";
			quest_data.quest_is_expanded = true;
			itemsData.push(quest_data);

			// daily
			for (i = 30; i < 40; i++)
			{
				quest_data = new QuestData;
				quest_data.quest_item_type = QuestData.quest_item_type_item;
				quest_data.quest_id = i;
				quest_data.quest_type = QuestData.quest_type_daily;
				quest_data.quest_caption = "【活动】Daily Quest" + i;
				quest_data.quest_is_traceable=true;
				quest_data.quest_is_traced=true;
				itemsData.push(quest_data);
			}

			this.UCUpdateQuestList(itemsData,10,10);
				
			// detail test
			var testDetailData:QuestDetailData = new QuestDetailData();
			
			testDetailData.quest_id = 888;
			testDetailData.quest_type = 2;
			testDetailData.quest_caption = "任务标题";
			testDetailData.quest_conditions_caption = "任务目标";
			testDetailData.quest_conditions = new Array;
			for(var k:int = 0; k < 8; ++k)
			{
				testDetailData.quest_conditions.push("conditions" + k);
			}
			
			testDetailData.quest_targets = null;
			
			testDetailData.quest_desc_caption = "任务描述";
			testDetailData.quest_desc = "quest_desc<u>underline</u><a href='event:123,12,3.15,4.24,7.2'>伏地魔伏地魔</a>伏地魔伏地魔伏地魔伏地魔伏地魔伏地魔伏地魔伏地魔伏地魔伏地魔伏地魔伏地魔伏地魔伏地魔伏地魔伏地魔伏地魔伏地魔伏地魔伏地魔伏地魔伏地魔伏地魔伏地魔伏地魔伏地魔伏地魔伏地魔伏地魔伏地魔伏地魔伏地魔\n这是测试";
			//<img src='img_SysTitleText_warehouse'>
			testDetailData.quest_submit_caption = "交付NPC";
			testDetailData.quest_submit = "完成后找<u><a href='event:,2,6009,2'>村长</a></u>谈话";
			
			testDetailData.quest_award_caption = "任务奖励";
			testDetailData.quest_awards = new Array;
			
			var n:int;
			var iconDat:QuestAwardIconData;
			
			for(n = 0; n < 4; ++ n)
			{
				iconDat = new QuestAwardIconData;
				iconDat.icon_img_name = "testImage";
				iconDat.item_template_id = n;
				iconDat.item_index = n;
				testDetailData.quest_awards.push(iconDat);
			}
			
			testDetailData.quest_award_select_caption = "您还可以选择一个奖励";
			testDetailData.quest_award_select = new Array;
			for(n = 0; n < 4; ++n)
			{
				iconDat = new QuestAwardIconData;
				iconDat.icon_img_name = "testImage";
				iconDat.item_template_id = n;
				iconDat.item_index = n;
				testDetailData.quest_award_select.push(iconDat);
			}
			
			testDetailData.quest_award_money_caption = "奖励很长的很长的金钱：";
			testDetailData.quest_award_money ="169530";
			
			testDetailData.quest_award_exp_caption = "奖励经验值:";
			testDetailData.quest_award_exp = 169530;				
			
			this.UCUpdateQuestDetailData(testDetailData);
		}*/
	}
}