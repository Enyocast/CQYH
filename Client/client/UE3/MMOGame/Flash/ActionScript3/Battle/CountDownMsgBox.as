package ActionScript3.Battle{
	import scaleform.clik.controls.Button;
	import flash.text.TextField;
	import ActionScript3.MyPanel;
	import flash.external.ExternalInterface;
	import flash.events.Event;
	import flash.events.TimerEvent;
	import flash.utils.Timer;
	
	public class CountDownMsgBox extends MyPanel
	{
		public var Hint:String;
		
		public var tF_timeCounter:TextField;
		public var yesButton_mc:Button;
		public var noButton_mc:Button;

		static var MAX_TIME:int = 30000;//30秒
		public var timeLeft:Number = MAX_LEAVE_TIME;
		public var timerCountDown:Timer = new Timer(1000);
		
		override protected function configUI():void
		{
			super.configUI();
			
			//add component events
			yesButton_mc.addEventListener( "click",ClickYes );
			noButton_mc.addEventListener( "click",ClickNo );

			timerCountDown.addEventListener(TimerEvent.TIMER, timerHandle);
			
		}
		//
		public function StartCloseCountDown( hint:String, LeftTime:int )
		{
			Hint = hint;
			timeLeft = LeftTime;
			tF_timeCounter.text = Hint + timeLeft/1000 + "秒";
			timerCountDown.start();
			
			visible = true;
		}
		//
		public function StopAndHideFB()
		{
			timerCountDown.stop();
			
			visible = false;
			parent.removeChild( this);
		}
		//
		function timerHandle()
		{
			timeLeft = timeLeft - 1000;
			tF_timeCounter.text = Hint + timeLeft/1000 + "秒";
			if (timeLeft <= 0 )
			{
				timeLeft = 0;
				ExternalInterface.call( "ASCountDownMsgBoxTimeUp",this );
				
				visible = false;
				parent.removeChild( this);
			}			
		}
		//
		function ClickYes()
		{
			ExternalInterface.call( "ASCountDownMsgBoxAck",true,this );
			
			visible = false;
			parent.removeChild( this);
		}
		//
		function ClickNo()
		{
			ExternalInterface.call( "ASCountDownMsgBoxAck",false,this );
			
			visible = false;
			parent.removeChild( this);
		}
	}
}

