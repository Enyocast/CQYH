package ActionScript3.Widget
{
	import ActionScript3.MyPanel;
	import flash.external.ExternalInterface;

	import flash.display.MovieClip;
	import flash.text.TextField;

	public class DropItemTipsWidget extends MyPanel
	{
		public var hintScene_mc:MovieClip;

		override protected function configUI():void
		{
			super.configUI();
			ExternalInterface.call( "registerDropItemTips", this);
		}
	}
}