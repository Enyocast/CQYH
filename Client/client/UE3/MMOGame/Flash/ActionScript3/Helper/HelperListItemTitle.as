package ActionScript3.Helper
{
	import flash.display.MovieClip;
	import scaleform.clik.core.UIComponent;
	import flash.text.TextField;
	import scaleform.clik.controls.ListItemTreeRenderer;
	import scaleform.clik.controls.Button;
	import flash.events.MouseEvent;
	import flash.external.ExternalInterface;
	import fl.motion.easing.Back;
	import scaleform.clik.core.CLIK;
	import scaleform.gfx.MouseEventEx;
	import scaleform.clik.events.ButtonEvent;
	import flash.events.Event;
	import ActionScript3.controls.StateUIComponent;

	public class HelperListItemTitle extends StateUIComponent
	{
		public var help_title_tf:TextField;
		
		public function HelperListItemTitle()
		{
		}

		override protected function configUI():void
		{
			super.configUI();
		}
		
		public function updateData(data:Object):void
		{
			if (data)
			{
				help_title_tf.htmlText = data.helper_title;
			}
		}
	}
}