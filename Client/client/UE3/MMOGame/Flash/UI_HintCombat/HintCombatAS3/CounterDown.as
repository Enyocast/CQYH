package UI_HintCombat.HintCombatAS3
{

	import flash.external.ExternalInterface;
	import scaleform.clik.core.UIComponent;
	import flash.display.MovieClip;

	public class CounterDown extends UIComponent
	{
		public var num_mc:MovieClip;
		override protected function configUI():void
		{
			super.configUI();
		}
		
		public function SetCounterDown(count:int):void
		{
			gotoAndPlay("count"+count);
		}
		
		public function DoCounterDown():void
		{
			stop();
			ExternalInterface.call( "AsCloseBossQTEPanel" );
		}		

	}
}