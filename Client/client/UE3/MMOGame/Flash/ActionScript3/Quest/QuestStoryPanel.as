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
	import ActionScript3.MyScrollBar;
	
	import scaleform.clik.motion.Tween;
	import fl.transitions.easing.*;
	import scaleform.clik.controls.RadioButton;
	import scaleform.clik.events.ComponentEvent;
	import flash.events.Event;

	public class QuestStoryPanel extends MyPanel
	{
		public static const c_group_current = 0;
		public static const c_group_past = 1;
		
		public var quest_group:int;
		
		public var quest_story_cur_tab_mc:RadioButton;
		public var quest_story_past_tab_mc:RadioButton;
		
		public var cur_mc:QuestStoryCurPanel;
		public var detail_mc:QuestStoryPastDetailPanel;

		override protected function configUI():void
		{
			ShowMode="BC";
			super.configUI();
			quest_story_cur_tab_mc.addEventListener(MouseEvent.CLICK, onTabClickCurQuest);
			quest_story_past_tab_mc.addEventListener(MouseEvent.CLICK, onTabClickPastQuest);
			
			cur_mc.setupScrollBar();
			
			quest_story_cur_tab_mc.selected = true;
			quest_group = c_group_current;
            show();
			this.addEventListener(ComponentEvent.HIDE,hideHandler);
		}
		
		private function hideHandler(evt:Event):void
		{
			if(detail_mc && detail_mc.dropDown)
			{
				detail_mc.dropDown.close();
			}
		}

		private function onTabClickCurQuest(evt:MouseEvent):void
		{
			quest_group = c_group_current;
            show();
			//quest_story_detail_sb_mc.visible = true;
			ExternalInterface.call("ASUpdateCurQuestInfo");
		}

		private function onTabClickPastQuest(evt:MouseEvent):void
		{
			quest_group = c_group_past;
			hide();
			//quest_story_detail_sb_mc.visible = false;
			ExternalInterface.call("ASUpdateQuestChapterList");
			ExternalInterface.call("ASUpdateQuestStageList", 1);
		}
		
		private function show():void
		{
			cur_mc.visible = true;
		 	detail_mc.visible = false;
		}
		
		private function hide():void
		{
			cur_mc.visible = false;
		 	detail_mc.visible = true;
		}
		
		public function UCSetWindowTitle(title:String):void
		{
			SetWindowTitle(title);
		}
		
		public function UCUpdateQuestStoryOverDesc(desc:String):void
		{
			cur_mc.quest_story_cur_detail_mc.updateQuestStoryOverDesc(desc);
		}
		
		public function UCUpdateQuestDetailData(detail_data:QuestDetailData):void
		{
			cur_mc.quest_story_cur_detail_mc.updateQuestDetailData(detail_data);
		}
		
		public function UCUpdateQuestStoryChapterList(list:Array):void
		{
			detail_mc.updateQuestStoryChapterList(list);
		}
		
		public function UCUpdateQuestStoryStageList(list:Array):void
		{
			detail_mc.updateQuestStoryStageList(list);
		}
		
		public function UCUpdateQuestStoryStageInfo(caption:String, desc:String):void
		{
			detail_mc.updateQuestStoryStageInfo(caption, desc);
		}
	}
}