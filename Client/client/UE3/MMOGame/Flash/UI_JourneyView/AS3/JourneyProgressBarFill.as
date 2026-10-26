package  UI_JourneyView.AS3
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
		
		public function UpdateData(dat:Object)
		{
			if(dat==null)
			{
				_progress_str = "0/0";
				ProcesBarMask.width = 0;
				return;
			}
			
			var process = (dat.curReputation-dat.minReputation)/(dat.maxReputation-dat.minReputation);
			if(process>=1)
			{
				process=1;
			}
			_progress_str = (dat.curReputation-dat.minReputation)+"/"+(dat.maxReputation-dat.minReputation);
			ProcesBarMask.width = ruler_mc.width*process;//(dat.curReputation-dat.minReputation)/(dat.maxReputation-dat.minReputation);
		}
	}
}