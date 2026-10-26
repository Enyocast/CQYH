package ActionScript3.Quest
{
	public class QuestDetailData extends Object
	{		
		public var quest_id:int		
		public var quest_type:int
		
		public var quest_chapter_name:String;
		public var quest_chapter_desc:String;
		public var quest_stage_name:String;
		public var quest_stage_desc:String;
		public var quest_chapter_icon:String;
		
		public var quest_is_accepted:Boolean;
		public var quest_is_available:Boolean;
		public var quest_is_compassable:Boolean;
		public var quest_is_completed:Boolean;
		
		public var quest_without_npc:Boolean;
		public var quest_can_abort:Boolean;
		public var quest_can_share:Boolean;
				
		public var quest_caption:String;
		
		public var quest_desc_caption:String;		
		public var quest_desc:String;
		
		public var quest_circle:String;
		
		public var quest_conditions_caption:String;		
		public var quest_conditions:Array;
		
		public var quest_targets_caption:String;		
		public var quest_targets:Array;
		
		public var quest_submit_caption:String;		
		public var quest_submit:String;
		
		public var quest_award_caption:String;
		public var quest_awards:Array;
		
		public var quest_award_select_caption:String;
		public var quest_award_select:Array;
		
		public var quest_award_money_caption:String;
		public var quest_award_money_icon:String;
		public var quest_award_money:String;
		
		public var quest_award_money_caption_ex:String;
		public var quest_award_money_icon_ex:String;
		public var quest_award_money_ex:String;
		
		public var quest_award_exp_caption:String;
		public var quest_award_exp_icon:String;
		public var quest_award_exp:int;
		
		public var quest_award_activity_caption:String;
		public var quest_award_activity_icon:String;
		public var quest_award_activity:int;
		
		public var quest_is_urgent:Boolean=false;// 是否显示紧急事件
		public var quest_urgent:String="";//紧急事件内容
	}
}