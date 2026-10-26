package ActionScript3.Quest{
	
	import ActionScript3.TreeListData;
	
	public class QuestData extends TreeListData
	{
		public static const quest_type_trunk = 0;
		public static const quest_type_branch = 1;
		public static const quest_type_daily = 2;
		public static const quest_type_reward = 3;
    	public static const quest_type_circle = 4;
    	public static const quest_type_activity = 5;
    	public static const quest_type_guild = 6;
    	public static const quest_type_master = 7;
    	public static const quest_type_wedding = 8;
		
		public static const quest_item_type_group = 0;
		public static const quest_item_type_item = 1;
		
		public var quest_id:int		
		public var quest_type:int
		public var quest_item_type:int;
		
		public var quest_caption:String;
		public var quest_level:String;
		
		public var quest_is_expanded:Boolean;
		public var quest_is_select:Boolean;
		public var quest_is_traceable:Boolean;
		public var quest_is_traced:Boolean;		
		public var quest_is_new:Boolean;
		
		public var quest_is_accepted:Boolean;
		public var quest_is_available:Boolean;
		public var quest_is_compassable:Boolean;
		public var quest_is_completed:Boolean;
		public var quest_is_failed:Boolean;
		
		public var quest_can_abort:Boolean;
		public var quest_can_share:Boolean;
		
		public var quest_stars:int;
		
		override public function toString():String
		{
			return "[" + quest_caption + " " + quest_id.toString() + "]";
		}
	}
}