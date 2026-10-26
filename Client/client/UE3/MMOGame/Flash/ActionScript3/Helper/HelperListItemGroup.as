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

	public class HelperListItemGroup extends StateUIComponent
	{
		public var help_group_name_tf:TextField;

		public function HelperListItemGroup()
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
				help_group_name_tf.htmlText = data.helper_class;
			}
		}
	}
}