package UI_HintCombat.HintCombatAS3
{

	import flash.external.ExternalInterface;
	import scaleform.clik.core.UIComponent;
	import flash.utils.Timer;
	import flash.events.TimerEvent;

	public class CounterBarFill extends UIComponent
	{
		public var timerCountDown:Timer = new Timer(33);
		public var timerCountCur:int = 0;
		public var timerCountTol:int = 0;
		public var timerCountMax:int = 0;
		public var MaxFrame:int = 240;
		override protected function configUI():void
		{
			super.configUI();
			SetCounterBarMax(4);
			timerCountTol = (timerCountMax-timerCountMax)*MaxFrame/timerCountMax;
			UpdateCounterBar()
			timerCountDown.addEventListener(TimerEvent.TIMER, UpdateCounterBar);
		}
		
		public function SetCounterBarMax(count:int):void
		{
			timerCountMax = count;
		}
		
		public function SetCounterBar(count:int):void
		{
			if(timerCountMax<count)
			{
				SetCounterBarMax(count);
			}
			
			timerCountTol = (timerCountMax-count)*MaxFrame/timerCountMax;
			timerCountDown.start();
		}
		
		public function UpdateCounterBar():void
		{
			if(timerCountCur!=timerCountTol)
			{
				var Default = 4;
				var CurDelta = timerCountTol-timerCountCur;
				
				if(CurDelta<0)Default=-Default;
				
				var delta = CurDelta/10 + Default;
				if(CurDelta>=-4 && CurDelta<=4){
					delta=timerCountTol-timerCountCur;
				}
				timerCountCur = timerCountCur + delta;
				gotoAndStop(timerCountCur);
			}
		}		
		
		public function DoCounterBar():void
		{
			timerCountDown.stop();
			stop();				
				
			timerCountCur = 0;
			timerCountMax = 0;
			ExternalInterface.call( "AsCloseBossQTEPanel" );
		}		

	}
}