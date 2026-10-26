package  UI_JourneyView.AS3
{
	import flash.text.TextField;
	
	import scaleform.clik.core.UIComponent;
	
	public class JourneyProgressBar extends UIComponent
	{
		public var progressBar_fill_mc:JourneyProgressBarFill;
		public var Number_txt:TextField;
		
		public function JourneyProgressBar()
		{
			super();
		}
		
		public function UpdateData(dat:Object)
		{
			if(progressBar_fill_mc){
				progressBar_fill_mc.UpdateData(dat);
				if(dat){
					Number_txt.text = (dat.curReputation-dat.minReputation)+"/"+(dat.maxReputation-dat.minReputation);
				}
				else
				{
					Number_txt.text = "";
				}
			}
		}
	}
}