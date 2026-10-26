package ActionScript3.Quest{
	public class QuestTraceTargetData extends Object
	{
		public static const quest_target_progress_type_null = 0;
		public static const quest_target_progress_type_count_progress = 1;
		public static const quest_target_progress_type_hp_progress = 2;
		
		public var quest_target_desc:String;
		public var quest_target_progress_type:int;
		public var quest_target_progress_cur:int;
		public var quest_target_progress_max:int;
		public var quest_target_complete:Boolean;
		
		public function QuestTraceData()
		{
			// constructor code
			quest_target_desc = "";
			quest_target_progress_type = 0;
		    quest_target_progress_cur = 0;
		    quest_target_progress_max = 1;
			quest_target_complete = false;
		}
		
		public function toString():String
		{
			return "";
		}
		
		public function RemoveAll()
		{
		}				
	}
}