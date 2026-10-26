package ActionScript3.Handbook.MonsterPage
{
	import flash.display.MovieClip;
	import flash.text.TextField;
	
	import scaleform.clik.controls.Button;
	
	public class Detail_Monster extends MovieClip
	{
		//public var monster_level_tf:TextField;
		public var monster_map_tf:TextField;
		public var btn_goto_map:Button;
		
		public var skill_list_mc:SkillList_Monster;
		public var drop_list_mc:DropList_Monster;
		
		public var frame_mc:MovieClip;
		
		private static const FRAME_INIT_HEIGHT:Number = 48;
		private static const MARGIN:Number = 13;
		
		public function Detail_Monster()
		{
			super();
		}
		
		public function updateFrameHeight():void
		{
			var frameHeight:Number = FRAME_INIT_HEIGHT;
			if(skill_list_mc.visible == true){
				if(drop_list_mc.visible){
					drop_list_mc.updateFrameSize();
					drop_list_mc.y = skill_list_mc.y + skill_list_mc.height + MARGIN;
					frameHeight = drop_list_mc.y + drop_list_mc.height + MARGIN;
				}else{
					frameHeight = skill_list_mc.y + skill_list_mc.height + MARGIN;
				}
			}else{
				if(drop_list_mc.visible){
					drop_list_mc.updateFrameSize();
					drop_list_mc.y = skill_list_mc.y + MARGIN * 0.5;
					frameHeight = drop_list_mc.y + drop_list_mc.height + MARGIN;
				}
			}
			frame_mc.height = frameHeight;
		}
	}
}