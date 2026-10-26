package MMO_UI.GameLoading.AS
{
	import flash.display.MovieClip;
	
	import scaleform.clik.core.UIComponent;
	
	public class CastBar extends UIComponent
	{
		public var mask_mc:MovieClip;
		public var shine:MovieClip;
		public var fill_mc:MovieClip;
		
		public function CastBar()
		{
			super();
		}
		
		
		public function setDivide(divideNum:Number,divideMax:Number):void
		{
			mask_mc.width = fill_mc.width*divideNum/divideMax;
			shine.x       = mask_mc.x + mask_mc.width;	
		}
		
		public function setState( frameName:String ):void
		{
			shine.visible = true;
			shine.gotoAndPlay(frameName);
			fill_mc.gotoAndPlay(frameName);
		}
		
		public function hideShine():void
		{
			shine.visible = false;
		}
	}
}