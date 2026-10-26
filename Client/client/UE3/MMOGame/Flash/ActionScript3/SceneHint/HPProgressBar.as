package ActionScript3.SceneHint
{
	import scaleform.clik.core.UIComponent;
	import flash.external.ExternalInterface;
	import flash.display.MovieClip;
	import flash.text.TextField;

	public class HPProgressBar extends UIComponent
	{
		public var progressBar_mc:MovieClip;
		public var maxWidth:int;
		public var progressBar_txt:TextField;
		private var CurFrameIndex:int;

		override protected function configUI():void
		{
			trace("------HPProgressBar  super.configUI:");
			super.configUI();
			maxWidth = 54;//progressBar_mc.width;
			SetDivide(50,100,true);
			CurFrameIndex=1;
		}

		public function SetDivide(divideNum:Number,divideMax:Number,isTxt:Boolean)
		{
			if(isTxt==false)
			{
				progressBar_txt.visible=false;
				progressBar_txt.text="";
			}
			else
			{
				progressBar_txt.visible=true;
				progressBar_txt.text = ""+divideNum+"/"+divideMax;
			}
			if(divideMax>0 && divideNum<=divideMax ){
				progressBar_mc.width = maxWidth * divideNum / divideMax;
			}
			else
			{
				progressBar_mc.width = maxWidth;
			}
		}

		public function SetState( frameName:String )
		{
			progressBar_mc.gotoAndStop(frameName);
		}
		public function SetStateByFrame( frameIndex:Number )
		{
			if(CurFrameIndex!=frameIndex){
				progressBar_mc.gotoAndStop(frameIndex);
				CurFrameIndex = frameIndex;
			}
		}
		
		public function getHeight():int
		{
			var h:int=progressBar_txt.textHeight+5;
			return h;
		}
	}
}