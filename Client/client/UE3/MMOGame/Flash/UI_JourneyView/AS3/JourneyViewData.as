package  UI_JourneyView.AS3
{
	import ActionScript3.TreeListData;
	
	public class JourneyViewData extends TreeListData
	{
		public var journey_view_id:int;
		public var journey_view_title:String;
		public var journey_view_icon:String;
		public var journey_view_desc:String;
		public var journey_view_progress:Object;
		public var journey_view_rewards:Array;
		public var journey_view_complete:Boolean;
		public var journey_view_get_awards:Boolean;
		
		public function JourneyViewData()
		{
		}
	}
}