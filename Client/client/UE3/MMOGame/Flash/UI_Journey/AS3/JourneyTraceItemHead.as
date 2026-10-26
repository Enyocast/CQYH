package UI_Journey.AS3
{
	import flash.display.MovieClip;
	import flash.text.TextField;
	
	import scaleform.clik.controls.RadioButton;
	
	public class JourneyTraceItemHead extends RadioButton
	{
		public var category_text_mc:MovieClip;
		public var recommand_level_stars_mc:MovieClip;
		public var quest_complete_txt:TextField;
		
		public function JourneyTraceItemHead()
		{
			super();
		}
		
		override protected function configUI():void
		{
			super.configUI();
			quest_complete_txt.visible = false;
		}
	}
}