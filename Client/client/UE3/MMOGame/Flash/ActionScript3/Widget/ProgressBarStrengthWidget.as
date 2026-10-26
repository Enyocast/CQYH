package ActionScript3.Widget
{
	import ActionScript3.MyPanel;
	import flash.external.ExternalInterface;

	import flash.display.MovieClip;
	import flash.utils.Timer;
	import flash.events.TimerEvent;	

	public class ProgressBarStrengthWidget extends MyPanel
	{
		var MaxFrame:Number = 8 + 1;
		var TimeFrame:Number = 33;
		var timeMax:Number = 1000;
		var timeCur:Number = 1000;
		var maxStrength:Number = 1;
		var curStrength:Number = 0;
		public  var fillContainer_mc:MovieClip;
		public  var numberContainer_mc:MovieClip;

		var timerCountDown:Timer = new Timer(TimeFrame);

		override protected function configUI():void
		{
			super.configUI();
			//ExternalInterface.call( "RegisterStrengthBar", this);
			timerCountDown.addEventListener(TimerEvent.TIMER, timeUpHandle);
		}


		public function ShowStrength(time:Number,max:Number)
		{
			timeMax = time;
			timeCur = time;
			if(max>MaxFrame)max=MaxFrame;
			maxStrength = max;
			curStrength = 0;
			numberContainer_mc.gotoAndStop(curStrength+1);
			this.visible = true;
			timerCountDown.start();
			SetDivide(0,timeMax);
		}

		public function CloseStrength()
		{
			this.visible = false;
		}


		public function timeUpHandle()
		{
			timeCur = timeCur - TimeFrame;
			if (timeCur<=0)
			{
				curStrength++;
				if (curStrength>=maxStrength)
				{
					curStrength = maxStrength;
					numberContainer_mc.gotoAndStop(MaxFrame+1);
					timeCur = 0;
					timerCountDown.stop();

				}
				else
				{
					numberContainer_mc.gotoAndStop(curStrength+1);
					timeCur = timeCur + timeMax;
				}

			}
			SetDivide(timeMax-timeCur,timeMax);
		}

		public function SetState( frameName:String )
		{
			fillContainer_mc.SetState( frameName );
		}

		public function SetDivide(divideNum:Number,divideMax:Number)
		{
			fillContainer_mc.SetDivide(divideNum,divideMax);
		}




	}
}