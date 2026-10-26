package ActionScript3.Widget
{
	import ActionScript3.MyPanel;
	import flash.external.ExternalInterface;

	import flash.display.MovieClip;
	import flash.text.TextField;
	import UI_DynamicUIWidget.AS3.LevelMc;
	import ActionScript3.Common.Events.ParamEvent;
	import ActionScript3.GameDispathcher;
	import flash.events.MouseEvent;
	import flash.events.Event;

	public class HintLevelUpWidget extends MyPanel
	{
		//public var tF_Title_mc:MovieClip;
		public var glow_mc:LevelMc;
		
		override protected function configUI():void
		{
			ShowMode="BCB";
			super.configUI();
			this.mouseChildren=false;
			this.enabled=false;
			stageChangeHandler(null);
			glow_mc.addEventListener("CloseLevelUp",CloseLevelUpHandler);
			//ShowLevelUp("54",0,0,0,0,0,0);
		}
		
		override protected function stageChangeHandler(evt:ParamEvent):void
		{
			super.stageChangeHandler(evt);
			this.x=cavasWidth-520>>1;
		}
		
		public function ShowLevelUp(strLevelUp:String,attribute1:Number,attribute2:Number,attribute3:Number,attribute4:Number,attribute5:Number,attribute6:Number )
		{
			glow_mc.updateData(strLevelUp);
		}
		
		public function CloseLevelUpHandler(e:Event):void
		{
			ExternalInterface.call("ASOnPanelClose",this.name);
		}
	}
}