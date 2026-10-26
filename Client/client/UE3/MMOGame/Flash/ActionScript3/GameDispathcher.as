package ActionScript3 {
	import flash.events.IEventDispatcher;
	import flash.events.EventDispatcher;
	import flash.events.Event;
	
	public class GameDispathcher {

        public static var instance:GameDispathcher;
		public var StageWidth:int=1280;
		public var StageHeight:int=720;
		private var eventDispathcher:IEventDispatcher;
		public static function getInstance():GameDispathcher
		{
			if(instance==null)
			{
				instance=new GameDispathcher();
			}
			return instance;
		}
		
		public function GameDispathcher(target:IEventDispatcher=null)
		{
			eventDispathcher=new EventDispatcher(target);
		}
		
		public function addEventListener(type:String,listener:Function,useCapture:Boolean=false,priority:int=0,useWeakReference:Boolean=false):void
		{
			eventDispathcher.addEventListener(type,listener,useCapture,priority,useWeakReference);
		}
		
		public function removeEventListener(type:String,listener:Function,useCapture:Boolean=false):void
		{
			eventDispathcher.removeEventListener(type,listener,useCapture);
		}
		
		public function dispatchEvent(event:Event):Boolean
		{
			return eventDispathcher.dispatchEvent(event);
		}
		
		public function hasEventListener(type:String):Boolean
		{
			return eventDispathcher.hasEventListener(type);
		}
		
		public function willTrigger(type:String):Boolean
		{
			return eventDispathcher.willTrigger(type);
		}

	}
	
}
