package ActionScript3.NPCDialog
{	
	import ActionScript3.Quest.QuestDetailData;

	public class NPCDialogOptionData extends Object
	{				
		public static const OptionType_Default = 0;
		public static const OptionType_Quest = 1;
		
		public var option_type:int;
		public var option_id:int;		
		public var option_label:String;
		public var option_icon:String;
		
		public function toString():String
		{
			var str:String;
			
			str = "[" + option_label + " " + " type:" + option_type + " id:" + option_id + " icon:" + option_icon;						
			str += "]";
			
			return str;
		}
	}

}