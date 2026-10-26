package UI_TeamAuction.AS{
	
	import scaleform.clik.core.UIComponent;
	import flash.events.TimerEvent;
	
	import flash.display.MovieClip;
	import flash.text.TextField;
	import flash.utils.Timer;
	
	
	public class ProgressBar extends UIComponent
	{
		public var time_tf:TextField;
		public var progress_mc:MovieClip;
		public var rule_mc:MovieClip;
		public var timerCountDown:Timer = new Timer(1000);
		
		var currentT:int;
		var totalT:int;		

		override protected  function configUI():void 
		{		
			super.configUI();
			timerCountDown.addEventListener(TimerEvent.TIMER, timerHandle);
		}

		private function timerHandle(evt:TimerEvent):void
		{
			currentT = currentT-1;
			if(currentT<0)
			{
				currentT = 0;
				timerCountDown.stop();
			}
			updateProgress();
		}
		
		public function setupProgress(curTime:int , tolTime:int):void
		{
			timerCountDown.stop();
			currentT = curTime;
			totalT	= tolTime;
			updateProgress();
			timerCountDown.start();
		}
		
		public function updateProgress():void
		{
			var txtTime:String = "";
			var curMinutes =   Math.floor(currentT/60);
			if(curMinutes>0)
			{
				txtTime = "" + curMinutes + "m";
			}
			else
			{
				txtTime = "" + currentT + "s";
			}
			time_tf.text = txtTime;
			
			progress_mc.width = 200 *(currentT)/totalT;
			rule_mc.x = progress_mc.x + progress_mc.width - rule_mc.width;
			//progress_mc.x     = rule_mc.x + rule_mc.width - progress_mc.width;
		}
	}
}


