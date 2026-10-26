package ActionScript3.Guild {
	import ActionScript3.TreeListData;
	
	public class GuildActiveData extends TreeListData {
		public var ID:int;
		public var active_name:String;
		public var active_timer:String;
		public var active_map:String;
		public var active_content:String;
		public var current:int;//当前状态
		public var max:int;//最大完成状态
		public var active_state:int;//当前活动完成状态
		public function GuildActiveData() {
			// constructor code
		}

	}
	
}
