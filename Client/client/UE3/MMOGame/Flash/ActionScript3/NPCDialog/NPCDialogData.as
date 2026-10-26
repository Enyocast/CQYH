package ActionScript3.NPCDialog
{	
	import ActionScript3.Quest.QuestDetailData;

	public class NPCDialogData extends Object
	{				
		public static const DiagDataType_Dialog = 0;
		public static const DiagDataType_QuestAccept = 1;
		
		public var diag_type:int; // 对话显示类型
		public var diag_text:String;
		public var diag_npc_name:String;
		public var option_list:Array;
		public var quest_detail_data:QuestDetailData;
		public var quest_share:Boolean;
		public var quest_share_id:int;
		
		public function toString():String
		{
			var str:String;
			str = "[type:" + diag_type + " " + diag_text;
			if(quest_detail_data != null)
			{
				str += " " + quest_detail_data.quest_caption + " " + quest_detail_data.quest_id.toString();
			}
			
			if(option_list != null)
			{
				for(var i:int = 0; i < option_list.length; ++i)
				{
					str += " " + option_list[i].toString();
				}
			}
			
			str += "]";
			
			return str;
		}
		
	}

}