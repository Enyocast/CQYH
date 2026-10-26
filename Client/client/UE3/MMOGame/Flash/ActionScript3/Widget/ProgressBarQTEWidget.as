package ActionScript3.Widget
{
	import ActionScript3.MyPanel;
	import flash.external.ExternalInterface;

	import flash.display.MovieClip;
	import flash.utils.Timer;
	import flash.events.TimerEvent;
	import flash.text.TextField;
	import flash.events.Event;

	public class ProgressBarQTEWidget extends MyPanel
	{
		var timeMax:Number = 4000;
		var timeCur:Number = 4000;
		var timeDelay:Number = 0;
		var MaxFrame:Number = 241;//圆盘帧数
		var TimeFrame:Number = 33;//时间侦听间隔
		public var btnQteTop:MovieClip;
		public var mask_mc:MovieClip;
		public var qteProcessBar_mc:MovieClip;
		public var timeUpHint_mc:MovieClip;
		public var tF_key:TextField;

		var timerCountDown:Timer = new Timer(TimeFrame);
		var timerDelete:Timer = new Timer(400);

		override protected function configUI():void
		{
			super.configUI();
		//	ExternalInterface.call( "RegisterQTEBar", this);
			
			timerCountDown.addEventListener(TimerEvent.TIMER, timeUpHandle);
			timerDelete.addEventListener(TimerEvent.TIMER, gameOverHandle);
			btnQteTop.addEventListener("click",clickQTE);
		}
		function clickQTE(e:Event)
		{
			ExternalInterface.call("ASClickQTE");
		}
		
		public function ShowQTE(time:Number,keyName:String,imgName:String)
		{
			timeMax = time;
			timeCur = time;
			this.visible = true;
			tF_key.text = keyName;
			timeUpHint_mc.gotoAndStop(1);
			timerCountDown.start();
			SetDivide(0,timeMax);
			btnQteTop.IconLoader_mc.source = "img://"+ imgName;
		}

		public function CloseQTE(closeType:Number)
		{
			if (this.visible)
			{
				timerCountDown.stop();
				if(closeType==0)
				{
					timeUpHint_mc.gotoAndPlay("start");
				}
				timerDelete.start();
			}
		}


		function timeUpHandle()
		{
			timeCur = timeCur - TimeFrame;
			if (timeCur<=0)
			{
				timeCur = 0;
				CloseQTE(1);
			}
			SetDivide(timeMax-timeCur,timeMax);
		}

		function gameOverHandle()
		{
			timerDelete.stop();
			this.visible = false;
		}

		public function SetDivide(divideNum:Number,divideMax:Number)
		{
			mask_mc.gotoAndStop( divideNum*MaxFrame/divideMax );
		}


	}
}