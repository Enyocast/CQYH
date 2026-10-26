package ActionScript3.Quest
{
	import ActionScript3.MyPanel;
	import flash.external.ExternalInterface;
	import flash.events.MouseEvent;
	import flash.events.Event;
	import flash.display.MovieClip;
	import ActionScript3.MyTipButton;
	import scaleform.clik.core.UIComponent;
	import flash.text.TextField;
	import scaleform.clik.controls.Button;
	import scaleform.clik.events.ListEvent;
	import scaleform.clik.controls.ScrollingList;
	import scaleform.gfx.Extensions;
	import ActionScript3.MyScrollBar;
	import scaleform.clik.data.DataProvider;
	import scaleform.clik.data.TreeDataProvider;
	import scaleform.clik.events.ListEvent;

	public class QuestRewardPanel extends MyPanel
	{
		public var quest_reward_list_mc:QuestRewardList;
		public var quest_reward_detail_mc:QuestRewardDetailPage;
		public var quest_reward_detail_sb_mc:MyScrollBar;
		
		public var quest_reward_accept_tf:TextField;
		public var quest_reward_upgrade_bt_mc:Button;
		public var quest_reward_tips_tf:TextField;
		public var quest_reward_show_complete_cb_mc:Button;
		public var quest_reward_refresh_top_cb_mc:Button;
		public var quest_reward_left_time_tf:TextField;
		public var quest_reward_refresh_bt_mc:Button;
		public var quest_reward_complete_bt_mc:Button;
		
		public var quest_data:QuestData;
		
		public function QuestRewardPanel()
		{
			// constructor code
		}

		override protected function configUI():void
		{
			ShowMode="BC";
			super.configUI();
			quest_reward_list_mc.selectedIndex = 0;
			quest_reward_list_mc.addEventListener(ListEvent.INDEX_CHANGE, onListItemChange, false, 0, true);
			quest_reward_list_mc.addEventListener(ListEvent.ITEM_CLICK, onListItemClick, false, 0, true);
			quest_reward_list_mc.addEventListener(ListEvent.ITEM_ROLL_OVER, onListItemRollOver, false, 0, true);
			quest_reward_list_mc.addEventListener(ListEvent.ITEM_ROLL_OUT, onListItemRollOut, false, 0, true);
			
			quest_reward_detail_mc.setupScrollBar(this.quest_reward_detail_sb_mc);

			// 悬赏
			quest_reward_upgrade_bt_mc.addEventListener(MouseEvent.CLICK, onBtClickUpgradeAwardQuestLimit);
			quest_reward_refresh_bt_mc.addEventListener(MouseEvent.CLICK, onBtClickRefreshAwardQuest);
			quest_reward_complete_bt_mc.addEventListener(MouseEvent.CLICK, onBtClickCompleteAwardQuest);
			quest_reward_show_complete_cb_mc.addEventListener(MouseEvent.CLICK, onToggleShowCompleteAwardQuest);

			quest_reward_refresh_top_cb_mc.addEventListener(MouseEvent.CLICK, onToggleRefreshTopLevelAwardQuest);
			
			quest_reward_left_time_tf.text = "00:00";
			quest_reward_complete_bt_mc.visible = false;
			
			// clear the list
			UCUpdateRewardQuestList(new Array());

			/*
			// test
			var i:int = 0;
			var quest_data:QuestData = null;
			var itemsData:Array = new Array;
			for (i = 1; i < 20; i++)
			{
				quest_data = new QuestData;
				
		 		quest_data.label = "";
		 		quest_data.index = i;
				quest_data.type = 0;
		 		quest_data.deepth = 0;
		 		quest_data.visible = true;
		
				quest_data.quest_id = i;
				quest_data.quest_caption = "Reward Quest" + i;
				quest_data.quest_stars = i % 5 + 1;
				quest_data.quest_is_accepted = true;
				quest_data.quest_is_compassable = false;
				quest_data.quest_is_completed = false;
				
				itemsData.push(quest_data);
			}
			UCUpdateRewardQuestList(itemsData);
			*/
		}

		function onListItemClick( event:ListEvent ):void
		{
			var list:ScrollingList = event.target as ScrollingList;
			if (list != null)
			{
				var provider:TreeDataProvider = list.dataProvider as TreeDataProvider;
				if (provider != null)
				{
					provider.handleListItemClick(event);
					quest_data = provider.requestItemAt(event.index) as QuestData;
					if (quest_data != null)
					{
						ExternalInterface.call("ASUpdateRewardQuestDetail", quest_data.quest_id);
					}
				}
				list.invalidateData();
			}
		}
		
		public function onListItemChange(event:Event):void
		{
			var list:ScrollingList = event.target as ScrollingList;
			if (list != null)
			{
				list.invalidateData();
			}
		}
		
		public function onListItemRollOver(event:ListEvent):void
		{
		}

		public function onListItemRollOut(event:ListEvent):void
		{
		}
		
		public function onBtClickUpgradeAwardQuestLimit()
		{
			ExternalInterface.call("ASUpgradeAvailableLimit");
		}
		
		public function onBtClickRefreshAwardQuest()
		{
			ExternalInterface.call("ASRefreshRewardQuestList", this.quest_reward_refresh_top_cb_mc.selected);
		}
		
		public function onBtClickCompleteAwardQuest()
		{
			ExternalInterface.call("ASCompleteAllRewardQuest");
		}
			
		public function onToggleShowCompleteAwardQuest()
		{
			ExternalInterface.call("ASShowCompletedRewardQuest", !this.quest_reward_show_complete_cb_mc.selected);
		}
		
		public function onToggleRefreshTopLevelAwardQuest()
		{
			ExternalInterface.call("ASRefreshTopLevelRewardQuest", this.quest_reward_refresh_top_cb_mc.selected);
		}
		
		public function UCSetWindowTitle(title:String)
		{
			SetWindowTitle(title);
		}
		
		public function UCUpdateRewardQuestList(list:Array)
		{
			quest_reward_list_mc.dataProvider = new TreeDataProvider(list);
			quest_reward_list_mc.validateNow();
			quest_reward_list_mc.invalidateData();
		}
		
		public function UCUpdateRewardQuestDetailData(detail_data:QuestDetailData)
		{
			if (detail_data)
			{
				quest_reward_detail_mc.visible = true;
				quest_reward_detail_mc.updateQuestDetailData(detail_data);
			}
			else
			{
				quest_reward_detail_mc.visible = false;
			}
		}
		
		public function UCUpdateRewardQuestAvailableLimit(cur:int)
		{
			quest_reward_accept_tf.text = cur.toString();
		}
		
		public function UCUpdateRewardQuestRefreshTime(hour:int, min:int, sec:int)
		{
			quest_reward_left_time_tf.text = hour.toString() + "小时" + min.toString() + "分";
		}
	}
}