package UI_KillRecord.killrecordAS{
	
	import ActionScript3.MyPanel;
	import flash.display.MovieClip;
	import flash.text.TextField;
	import flash.utils.Timer;
	import flash.events.TimerEvent;
	import flash.external.ExternalInterface;
	import flash.utils.getDefinitionByName;
	
	public class KillCountPanel extends MyPanel
	{
		public var numberTitle_mc:NumberTitle;
		
		public var tCount:int = 1;
		var timeChange:Timer = new Timer(33);
		
		var timeChangeClose:Timer = new Timer(33);
		
		override protected function configUI():void
		{
			//
			super.configUI();

			timeChange.addEventListener(TimerEvent.TIMER, timeUpHandle);
			
			timeChangeClose.addEventListener(TimerEvent.TIMER, CloseTimeUpHandle);
			
			ExternalInterface.call( "RegisterKillCountPanel", this);
			
			/*UCSetNewKillCount(0,263);
			
			UCSetNewKillCount(0,79);
			
			UCSetNewKillCount(0,4);*/
		}
		
		public function UCSetNewKillCount(nType:int,nCount:int)
		{
			numberTitle_mc.SetNewKillCount(nType,nCount);
			//count_mc.text = strCount;
			alpha = 0.0;
			tCount = 0;
			visible = true;
			timeChange.start();
		}
		
		public function UCCloseCountPanel()
		{
			if(visible)
			{
				tCount = 10;
				timeChangeClose.start();
			}
		}
		function CloseTimeUpHandle()
		{
			if(visible)
			{
				tCount -= 1;
				if(tCount < 0)
				{
					timeChangeClose.stop();
					visible = false;
				}
				else
				{
					alpha = tCount*0.1;
				}
			}
		}
		function timeUpHandle()
		{
			if(visible)
			{
				tCount += 1;
				if(tCount > 10)
				{
					/*if(tCount > 90)
					{
						alpha = (205-tCount)*0.00833;
						if(tCount >= 205)
						{
							ExternalInterface.call( "ASClosedKillCountPanel", this);
							visible = false;
							timeChange.stop();
						}
					}*/
					timeChange.stop();
				}
				else
				{
					alpha = tCount*0.1;
				}
			}
		}
		
	}
}