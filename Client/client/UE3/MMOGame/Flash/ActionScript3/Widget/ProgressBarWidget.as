package ActionScript3.Widget
{
	import ActionScript3.MyProgressBarPanel;
	import flash.external.ExternalInterface;
	import ActionScript3.Common.Events.ParamEvent;
	
	public class ProgressBarWidget extends MyProgressBarPanel
	{
		override protected function configUI():void
		{
			super.configUI();
			this.enabled=false;
			this.mouseChildren=false;
			stageChangeHandler(null);
		}
		
		override protected function stageChangeHandler(evt:ParamEvent):void
		{
			super.stageChangeHandler(evt);
			this.x=(cavasWidth-290)>>1;
			this.y=cavasHeight-238;
		}
	}
}