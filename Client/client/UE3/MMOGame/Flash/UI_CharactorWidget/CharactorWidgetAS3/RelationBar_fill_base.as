package UI_CharactorWidget.CharactorWidgetAS3
{
	import flash.text.TextField;
	import scaleform.clik.core.UIComponent;
	import flash.display.MovieClip;

	public class RelationBar_fill_base extends UIComponent
	{
		public var ProcesBarMask:MovieClip;
		public var ruler_mc:MovieClip;
		
		override protected function configUI():void
		{
			super.configUI();
			
		}
		
		public function UpdateData(dat:Object)
		{
			if(dat==null)
			{
				ProcesBarMask.width = 0;
				return;
			}
			
			var process = (dat.curReputation-dat.minReputation)/(dat.maxReputation-dat.minReputation);
			if(process>=1)
			{
				gotoAndStop( 2 );
				process=1;
			}
			else
			{
				gotoAndStop( 1 );
			}
			
			ProcesBarMask.width = ruler_mc.width*process;//(dat.curReputation-dat.minReputation)/(dat.maxReputation-dat.minReputation);
		}		
		
	}
}