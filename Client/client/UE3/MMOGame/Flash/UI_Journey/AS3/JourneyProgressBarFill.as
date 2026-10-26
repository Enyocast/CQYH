package UI_Journey.AS3
{
	import flash.display.MovieClip;
	
	import scaleform.clik.core.UIComponent;
	
	public class JourneyProgressBarFill extends UIComponent
	{
		public var ProcesBarMask:MovieClip;
		public var ruler_mc:MovieClip;
		public var _progress_str:String;
		
		public function JourneyProgressBarFill()
		{
			super();
		}
		
		override protected function configUI():void
		{
			super.configUI();
			_progress_str = "0/0";
			ProcesBarMask.width = 0;
		}
		
		public function UpdateData(curReputation:int, maxReputation:int, minReputation:int = 0)
		{
			var process = (curReputation - minReputation) / (maxReputation - minReputation);
			if(process >= 1)
			{
				process = 1;
			}
			_progress_str = (curReputation - minReputation) + "/" + (maxReputation - minReputation);
			ProcesBarMask.width = ruler_mc.width * process;//(dat.curReputation-dat.minReputation)/(dat.maxReputation-dat.minReputation);
		}
	}
}