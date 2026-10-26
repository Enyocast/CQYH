package ActionScript3
{
	import ActionScript3.MyPanel;
	import flash.external.ExternalInterface;
	import flash.utils.getTimer;
	import flash.display.MovieClip;
	import flash.utils.Timer;
	import flash.events.TimerEvent;	
	import flash.text.TextField;

	public class MyProgressBarPanel extends MyPanel
	{
		public var tF_title:TextField;
		public var castbar_mc:MovieClip;
		var timeFrame:Number = 33;
		var timeCur:Number =3000;
		var timeMax:Number =3000;
		var timeStart:Number =0;
				
		var timeType:Number = 0;

		var timerCountDown:Timer = new Timer(timeFrame);
		var timerDelete:Timer = new Timer(400);
		
		override protected function configUI():void
		{
			ShowMode="BCB";
			super.configUI();
			//
			//castbar_mc.fill_mc.width = width;
			//trace( "MyProgressBarPanel:  "+castbar_mc.fill_mc.width );
			//
			timerCountDown.addEventListener(TimerEvent.TIMER, timeUpHandle);
			timerDelete.addEventListener(TimerEvent.TIMER, gameOverHandle);
		}


		public function ShowProcesses(countDownTime:Number,strTitle:String,type:Number)
		{
			timeType = type;
			timeMax = countDownTime;
			timeCur = countDownTime;
			this.visible = true;
			timeStart = getTimer();
			SetTitle(strTitle);
			SetState("casting");

			if (timeType==0)
			{
				SetDivide(0,timeMax);
			}
			else
			{
				SetDivide(timeCur,timeMax);
			}
			timerCountDown.start();
		}
		
		public function CloseProcesses(closeType:Number)
		{
			if (this.visible)
			{
				timerCountDown.stop();
				if(closeType==0)
				{
					SetState("completed");
					//
					TimeUpCallback();
				}
				else
				{
					SetState("interrupted");
				}
				
				timerDelete.start();
			}
		}		
		public function TimeUpCallback()
		{
			ExternalInterface.call( "ProgressBarTimeUpCallback" );
		}
		public function SetPos( posX:Number, posY:Number )
		{
			x = posX;
			y = posY;
		}

		public function SetTitle( strTitle:String )
		{
			tF_title.text = strTitle;
		}

		public function SetState( frameName:String )
		{
			castbar_mc.SetState( frameName );
		}

		public function SetDivide(divideNum:Number,divideMax:Number)
		{
			castbar_mc.SetDivide(divideNum,divideMax);
		}

		function timeUpHandle()
		{
			timeCur = timeMax - (getTimer()-timeStart);
			//timeCur = timeCur - timeFrame;
			if (timeCur<=0)
			{
				timeCur = 0;
				CloseProcesses(0);
			}
			
			if (timeType==0)
			{
				SetDivide(timeMax-timeCur,timeMax);
			}
			else
			{
				SetDivide(timeCur,timeMax);
			}
		}
		
		function gameOverHandle()
		{
			timerDelete.stop();
			this.visible = false;
			ExternalInterface.call("ASOnPanelClose",PanelName);
		}		
		
	}
}