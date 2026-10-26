package ActionScript3.Handbook
{
	public class HandbookData extends Object
	{
		public var handbook_class:int;
		public var handbook_type:int;
		public var handbook_index:int;
		public var handbook_ui_type:int;
		public var handbook_name:String;
		public var handbook_temp:int;
		public var handbook_icon:String;
		public var handbook_sound:String;
		public var handbook_invalid:Boolean;
		public var handbook_obtain:Boolean;
		
		public var handbook_text0:String;
		public var handbook_text1:String;
		public var handbook_text2:String;
		
		public var handbook_data0:Array;
		public var handbook_data1:Array;
		
		
		public function QuestTraceData()
		{
			// constructor code
			handbook_class = 0;
			handbook_type = 0;
			handbook_index = 0;
			handbook_ui_type = 0;
			handbook_name = "";
			handbook_icon = "";
		
			handbook_text0 = "";
			handbook_text1 = "";
			handbook_text2 = "";
		}
	}
}