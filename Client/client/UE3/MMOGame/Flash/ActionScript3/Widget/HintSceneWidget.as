package ActionScript3.Widget
{
	import ActionScript3.MyPanel;
	import flash.external.ExternalInterface;

	import flash.display.MovieClip;
	import flash.text.TextField;
	import flash.text.TextFormat;
	import ActionScript3.Common.Events.ParamEvent;
	import ActionScript3.GameDispathcher;

	public class HintSceneWidget extends MyPanel
	{
		public var hintScene_mc:MovieClip;

		override protected function configUI():void
		{
			ShowMode="BCB";
			super.configUI();
			this.mouseChildren=false;
			this.enabled=false;
			stageChangeHandler(null);
			CloseHintScene();
			//ShowHintScene("",48);
		}
		
		override protected function stageChangeHandler(evt:ParamEvent):void
		{
			super.stageChangeHandler(evt);
			this.x=(cavasWidth-492>>1)+245;
		}

		public function ShowHintScene(strSceneName:String, textSize:int)
		{
			if(hintScene_mc)
			{
			   var contentTf:TextField = hintScene_mc.getChildByName( "tF_hintScene" ) as TextField;
			   if( contentTf == null )
			   {
				  return;
			   }
			   contentTf.text = strSceneName;
		       var format:TextFormat=contentTf.getTextFormat();
			   format.size=textSize;
			   if(textSize==48)
			   {
				   contentTf.y=0;
			   }
			   else
			   {
				   contentTf.y=15;
			   }
			   contentTf.setTextFormat(format);
			   this.gotoAndPlay(1);
			}
		}
		
		public function CloseHintScene():void
		{
			this.gotoAndStop(1);
			ExternalInterface.call("ASOnPanelClose",this.name);
		}		
	}
}