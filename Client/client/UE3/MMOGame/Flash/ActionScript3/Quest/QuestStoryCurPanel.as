package ActionScript3.Quest {
	
	import ActionScript3.MyPanel;
	import flash.display.MovieClip;
	import flash.text.TextField;
	import ActionScript3.MyScrollBar;
	import flash.utils.getDefinitionByName;
	import scaleform.clik.events.SliderEvent;
	import flash.external.ExternalInterface;
	import flash.events.MouseEvent;
	import scaleform.clik.controls.ScrollBar;
	import scaleform.clik.controls.ScrollingView;
	import ActionScript3.Common.CustomScrollBar;
	
	
	
	public class QuestStoryCurPanel extends MyPanel {
		
		public var quest_chapter_icon_mc:MovieClip;
		public var quest_story_name:TextField;
		public var quest_title_tf:TextField;
		public var quest_story_cur_detail_mc:QuestStoryCurDetailPanel;
		public var quest_story_detail_sb_mc:CustomScrollBar
		public var _scrollingView:ScrollingView;
		public function QuestStoryCurPanel() {
			// constructor code
		}
		
		override protected function configUI():void
		{
			super.configUI();
		}
		
		public function setupScrollBar():void
		{
/*			_scrollingView.displayMc=quest_story_cur_detail_mc;
			quest_story_detail_sb_mc.position = 0;
			if (quest_story_detail_sb_mc)
			{
			}
			else
			{
				ExternalInterface.call("ASTrace", "_traceScrollbar is null!");
			}*/
		}

	}
	
}
