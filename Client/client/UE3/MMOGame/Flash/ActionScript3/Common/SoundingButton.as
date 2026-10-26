package ActionScript3.Common
{
	import flash.events.MouseEvent;
	
	import scaleform.clik.controls.Button;
	
	public class SoundingButton extends Button
	{
		public static const SOUND_EVENT_MENU_HIGH_LIGHT:String 		= "menu_highlight";
		public static const SOUND_EVENT_MENU_CLICK:String 			= "menu_click";
		
		public function SoundingButton()
		{
			super();
		}
		
		override protected function handleMouseRollOver(event:MouseEvent):void 
		{
			super.handleMouseRollOver(event);
			playSound(SOUND_EVENT_MENU_HIGH_LIGHT, _soundTheme);
		}
		
		override protected function handleMousePress(event:MouseEvent):void
		{
			super.handleMousePress(event);
			playSound(SOUND_EVENT_MENU_CLICK, _soundTheme);
		}
	}
}