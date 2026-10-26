package ActionScript3.Common {

	import flash.events.TimerEvent;
	import flash.utils.Dictionary;
	import flash.utils.Timer;
	
	public class TimerManager {

        private static var _instance:TimerManager=null;
		private var timerDic:Dictionary;
		private var funTotimerDic:Dictionary;
		private var funListDic:Dictionary;
		public function TimerManager() {
			timerDic=new Dictionary();
			funTotimerDic=new Dictionary();
			funListDic=new Dictionary();
		}
		
		public static function getInstance():TimerManager
		{
			if(_instance==null){
				_instance=new TimerManager();
			}
			return _instance;
		}
		
		public function add(delay:int,func:Function):void
		{
			if(funTotimerDic[func]!= undefined) return;
			funTotimerDic[func]=createTimer(delay);
			funListDic[delay].push(func);
		}
		
		public function remove(func:Function):void
		{
			if(funTotimerDic[func]!= undefined) return;
			var timer:Timer=funTotimerDic[func];
			delete funTotimerDic[func];
			if(timer){
				var list:Array=funListDic[timer.delay];
				
				if(list.indexOf(func)>-1){
					list.splice(list.indexOf(func),1);
				}
				if(list.length==0){
					timer.stop();
					timer.removeEventListener(TimerEvent.TIMER,timerHandler);
					delete funListDic[timer.delay];						
					delete timerDic[timer.delay];
					
				}
			}
		}
		
		private function createTimer(delay:int):Timer
		{
			if(timerDic[delay]==undefined){
				var timer:Timer=new Timer(delay);
				timer.addEventListener(TimerEvent.TIMER,timerHandler);
				timer.start();
				timerDic[delay]=timer;
			}
			if(funListDic[delay]==undefined){
				funListDic[delay]=new Array();
			}
            return timerDic[delay];
		}
		
		private function timerHandler(e:TimerEvent):void
		{
			var list:Array=funListDic[Timer(e.target).delay];
			for(var i:* in list){
				list[i]();
			}
		}

	}
	
}
