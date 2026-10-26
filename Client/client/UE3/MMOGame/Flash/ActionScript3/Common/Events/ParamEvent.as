package ActionScript3.Common.Events  {
	import flash.events.Event;
	
	public class ParamEvent extends Event {
        public var param:Object;
		public static const PAGE_CHANGE:String="page_change";
		public static const INPUT_CHANGE:String="input_change";
		public static const STAGECHANGE:String="stagechange";
		public function ParamEvent(type:String,dat:Object) {
			super(type,false,true);
			this.param=dat;
		}

	}
	
}
