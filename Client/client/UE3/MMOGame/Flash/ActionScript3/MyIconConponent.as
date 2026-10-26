package ActionScript3
{
	import flash.display.MovieClip;
	//import scaleform.clik.controls.UILoader;
	import scaleform.clik.controls.UILoader;

	public class MyIconConponent extends MovieClip
	{
		public var IconLoader_mc:UILoader;
		public var slotIcon_frame_mc:MovieClip;
		public var slotIcon_bg_mc:MovieClip;
		public var bNeedVisible:Boolean = false;
		
		public function RemoveAll()
		{
//			IconLoader_mc.unload();
			IconLoader_mc=null;
			slotIcon_frame_mc=null;
			slotIcon_bg_mc = null;
		}
	}
}