package ActionScript3.Widget
{
	import flash.display.MovieClip;
	import scaleform.clik.controls.UILoader;

	public class UILoaderWithBG extends UILoader
	{
		public var Title_BG:MovieClip;
		
        override protected function configUI():void {
			
			super.configUI();
			mouseChildren = false;
        }		
	}
}