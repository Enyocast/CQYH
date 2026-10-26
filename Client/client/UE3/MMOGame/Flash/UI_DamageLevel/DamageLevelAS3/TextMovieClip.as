package UI_DamageLevel.DamageLevelAS3
{
	import scaleform.clik.core.UIComponent;
	import flash.display.MovieClip;
	import flash.external.ExternalInterface;
	import ActionScript3.GravityObj;
	import fl.motion.Color;
	import flash.text.TextField;

	public class TextMovieClip extends UIComponent
	{
		public var tf_number:TextField;
		
		public function SetColorType(type:int)
		{
			if (type<4)
			{
				tf_number.textColor = 0xffff00;
			}
			else
			{
				tf_number.textColor = 0x00ffff;
			}
		}
		
		
		
	}
}