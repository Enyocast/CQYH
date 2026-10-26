package UI_KillRecord.killrecordAS{
	
	import ActionScript3.MyPanel;
	import flash.display.MovieClip;
	import flash.text.TextField;
	import flash.utils.Timer;
	import flash.events.TimerEvent;
	import flash.external.ExternalInterface;

	public class KillRecordPanel extends MyPanel
	{
		public var numberTitle_mc:NumberTitle;
		public var newRecord_mc:MovieClip;
		public var recordName_mc:TextField;
		public var reward_mc:TextField;
		public var rewardExp_mc:TextField;
		
		public var tCount:int = 1;
		
		var timeChange:Timer = new Timer(33);
		
		
		override protected function configUI():void
		{
			//
			super.configUI();

			timeChange.addEventListener(TimerEvent.TIMER, timeUpHandle);
			
			ExternalInterface.call( "RegisterKillRecordPanel", this);
			
			//UCSetNewRecord(true,0,7,980);
			
			/*UCSetNewRecord(true,2,5,980);
			
			UCSetNewRecord(true,2,6,980);*/
		}
		
		public function UCSetNewRecord(bNew:Boolean,nType:int,nCount:int,nReward:int)
		{
			timeChange.stop();
			newRecord_mc.visible = bNew;
			numberTitle_mc.SetNewKillCount(nType,nCount);
			//recordName_mc.text = strTitle;
			//reward_mc.text = strReward;
			recordName_mc.visible = (nType == 0);
			if(nType < 2)
			{
				reward_mc.text = "额外奖励经验";
				rewardExp_mc.text = nReward.toString();
				
				if(nType == 0)
				{
					alpha = 0.0;
					tCount = 0;
				}
				else
				{
					alpha = 1.0;
					tCount = 30;
				}
			}
			else
			{
				reward_mc.text = "连续击杀";
				rewardExp_mc.text = nCount.toString();
				
				alpha = 0.0;
				tCount = 0;
			}
			visible = true;
			timeChange.start();
		}
		
		function timeUpHandle()
		{
			if(visible)
			{
				tCount += 1;
				if(tCount > 30)
				{
					if(tCount > 70)
					{
						alpha = (70-tCount)*0.1;
						if(tCount >= 70)
						{
							ExternalInterface.call( "ASClosedKillRecordPanel", this);
							visible = false;
							timeChange.stop();
						}
					}
				}
				else
				{
					if(tCount > 20)
						alpha = (tCount - 20)*0.1;
				}
			}
		}
	}
}