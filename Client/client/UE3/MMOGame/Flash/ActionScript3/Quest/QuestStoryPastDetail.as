package ActionScript3.Quest {
	
	import flash.display.MovieClip;
	import ActionScript3.MyPanel;
	import flash.text.TextField;
	import scaleform.clik.controls.Button;
	
	
	public class QuestStoryPastDetail extends MyPanel {
		
		public var quest_story_past_stage_title_mc:TextField;
		public var quest_story_past_stage_content_mc:TextField;
		public var quest_story_past_back_mc:Button;
		public var quest_story_past_sound_mc:Button;
		
		public function QuestStoryPastDetail() {
			
		}
		override protected function configUI():void
		{
			super.configUI();
		}
	}
	
}
