package ActionScript3.Handbook.MonsterPage
{
	import flash.display.MovieClip;
	import flash.text.TextField;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.external.ExternalInterface;
	
	import ActionScript3.ItemSlot.MyItemSlot;
	
	public class SkillList_Monster extends MovieClip
	{
		public var monster_skill_title_tf:TextField;
		public var monster_skill_0_mc:HandbookSkillIcon;
		public var monster_skill_1_mc:HandbookSkillIcon;
		public var monster_skill_2_mc:HandbookSkillIcon;
		public var monster_skill_3_mc:HandbookSkillIcon;
		public var monster_skill_4_mc:HandbookSkillIcon;
		
		public function SkillList_Monster()
		{
			super();
			
			monster_skill_0_mc.addEventListener("rollOver", handleSkillRollOver);
            monster_skill_0_mc.addEventListener("rollOut", handleSkillRollOut);
			
			monster_skill_1_mc.addEventListener("rollOver", handleSkillRollOver);
            monster_skill_1_mc.addEventListener("rollOut", handleSkillRollOut);
			
			monster_skill_2_mc.addEventListener("rollOver", handleSkillRollOver);
            monster_skill_2_mc.addEventListener("rollOut", handleSkillRollOut);
			
			monster_skill_3_mc.addEventListener("rollOver", handleSkillRollOver);
            monster_skill_3_mc.addEventListener("rollOut", handleSkillRollOut);
			
			monster_skill_4_mc.addEventListener("rollOver", handleSkillRollOver);
            monster_skill_4_mc.addEventListener("rollOut", handleSkillRollOut);
		}
		
		public function handleSkillRollOver(e:Event):void
		{
			var item_mc:HandbookSkillIcon = e.currentTarget as HandbookSkillIcon;
			if (item_mc)
			{
				ExternalInterface.call("ASShowTips_MonsterSkill", item_mc);
			}
		}

		public function handleSkillRollOut(e:Event):void
		{
			ExternalInterface.call("ASHideTips_MonsterSkill", this);
		}
	}
}