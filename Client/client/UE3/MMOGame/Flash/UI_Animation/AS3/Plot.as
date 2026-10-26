package  AS3 {
	
	import flash.display.MovieClip;
	import scaleform.clik.motion.Tween;
	import flash.utils.setInterval;
	import flash.external.ExternalInterface;
	
	public class Plot extends MovieClip {
		public var btn_light:MovieClip;
		public var btn_black:MovieClip;
		public var _mask:MovieClip;
		public var tween:Tween;
		public function Plot() {
			_mask.x=30;
			//UCPlay(10000);
			//setInterval(test,11000);
		}
		
		private function test():void
		{
			UCPlay(10000);
		}
		
		//通知服务器动画播放完成（调用脚本）
		private function handleTweenComplete():void
		{
			ExternalInterface.call("ASViewPage_ClickPlotComplete");
		}
		
		// 服务器调用播放脚本动画
		public function UCPlay(timer:int):void
		{
			if(tween){
				tween.reset();
				tween.paused=true;
			   tween=null;
			}
			_mask.x=0;
            tween=new Tween(timer,_mask,{ x:30});
		}
	}
	
}
