package ActionScript3.Quest{
	public class QuestTraceData extends Object
	{
		public var quest_id:int;
		public var quest_type:int;
		
		public var quest_caption:String;
		public var quest_level:String;
		public var quest_item_id:int;
		public var quest_item_icon:String;
		public var quest_detail:String;
		public var quest_targets:Array;
		
		public var quest_is_new:Boolean;
		public var quest_is_delay_complete:Boolean;
		public var quest_is_compassable:Boolean;
		public var quest_time_limit:int;
		public var quest_failed:Boolean;
		
		public var quest_award_caption:String;
		
		public var quest_award_money_icon:String;
		public var quest_award_money:String;
		
		public var quest_award_money_icon_ex:String;
		public var quest_award_money_ex:String;
		
		public var quest_award_exp_icon:String;
		public var quest_award_exp:int;
		
		public var quest_award_activity_icon:String;
		public var quest_award_activity:int;
		
		public var quest_awards:Array;
		
		public function QuestTraceData()
		{
			// constructor code
			quest_id = 0;
			quest_type = 0;

			quest_caption = "";
			quest_level = "";
		    quest_item_id = 0;
		    quest_item_icon = "";
			quest_detail = "";
			
			quest_is_new = false;
			quest_is_delay_complete = false;
			quest_time_limit = 0;
			quest_failed = false;
			
			quest_award_caption = "";
			
			quest_award_money_icon = "";
			quest_award_money = "";
			
			quest_award_money_icon_ex = "";
			quest_award_money_ex = "";
		
			quest_award_exp_icon = "";
			quest_award_exp = 0;
		
			quest_award_activity_icon = "";
			quest_award_activity = 0;
		}
		
		public function toString():String
		{
			return "[" + quest_caption + " " + quest_id.toString() + "]";
		}
		public function RemoveAll()
		{
		}				
	}
}