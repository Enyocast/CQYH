package ActionScript3.Widget
{
	import ActionScript3.MyPanel;
	import flash.display.MovieClip;
	import scaleform.clik.controls.Button;
	import flash.events.MouseEvent;
	import scaleform.gfx.MouseEventEx;
	import flash.external.ExternalInterface;
	import flash.geom.Point;
	import flash.events.Event;
	import flash.text.TextField;
	
	public class CombatMsg extends MyPanel
	{
		public var Msg_tf:TextField;
		
		override protected function configUI():void 
		{
			super.configUI();
			
			ExternalInterface.call( "RegisterCombatMsg", this );
		}
		
		
	}
}