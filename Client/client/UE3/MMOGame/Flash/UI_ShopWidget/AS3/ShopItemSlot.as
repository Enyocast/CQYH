package UI_ShopWidget.AS3 {
	import ActionScript3.ItemSlot.MyItemSlot;
	import flash.events.TimerEvent;
	import flash.utils.Timer;
	import flash.utils.getTimer;
	
	public class ShopItemSlot extends MyItemSlot {

        private var timer:Timer;
		private var curTimer:int;
		private var startTimer:int;
		private var cdTotal:int;
		override protected function configUI():void
		{
			super.configUI();
			timer=new Timer(1000);
			//SetCD(93000,72000000);
		}
		
		private function step(e:TimerEvent):void
		{
			curTimer = getTimer();
			var passedMiniSec:int = curTimer - startTimer;
			var leftSec:int = (int)( ((int)(cdTotal - passedMiniSec) + 999) / 1000 );
			if (leftSec <= 0 )
			{
				coolDown.gotoAndStop(2);
				cdTotal = 0;
				StopCDTimer();
				playSound("iCooldown");
				return;
			}
			var nframe:uint = passedMiniSec / cdTotal * 240;//240为动画总帧数
			coolDown.gotoAndStop(nframe);
		}

		//==================================================================================================
		override public function SetCD( leftMiniSec:int, totalMiniSec:int )
		{
			if ( cdTotal > 0 )
			{
				//已有倒计时在运行，先停掉
				StopCDTimer();
			}

			StartCDTimer( totalMiniSec - leftMiniSec, totalMiniSec );
			coolDown.gotoAndStop(2);
		}
		
		override public function CancelCD()
		{
			StopCDTimer();
		}
		
		override public function StopCDTimer()
		{
			coolDown.gotoAndStop(2);
			timer.stop();
			timer.removeEventListener( TimerEvent.TIMER , step );
			startTimer = 0;
			curTimer = 0;
			cdTotal = 0;
		}
		//-----------------------------------------------------------------------------------------------------
		override public function StartCDTimer( passedMiniSec:int, totalMiniSec:int )
		{
			cdTotal = totalMiniSec;
			curTimer = getTimer();

			if ( curTimer > passedMiniSec )
			{
				startTimer = curTimer - passedMiniSec;
			}
			else
			{
				cdTotal = totalMiniSec - passedMiniSec;
				startTimer = curTimer;
			}

			if (timer)
			{
				coolDown.gotoAndStop(3);
				timer.addEventListener( TimerEvent.TIMER , step );
				timer.start();
			}
		}

	}
	
}
