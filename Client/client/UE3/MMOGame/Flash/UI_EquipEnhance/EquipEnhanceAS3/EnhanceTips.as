package UI_EquipEnhance.EquipEnhanceAS3 {
	
	import flash.display.MovieClip;
	import scaleform.clik.core.UIComponent;
	import flash.events.MouseEvent;

	import flash.external.ExternalInterface;
	
	
	public class EnhanceTips extends UIComponent {
		
		
		override protected function configUI():void 
		{
			super.configUI();
			this.addEventListener( MouseEvent.ROLL_OVER, ShowTips);
			this.addEventListener( MouseEvent.ROLL_OUT, HideTips);
		}
		

		private function ShowTips(e:MouseEvent):void
		{
			ExternalInterface.call("ASShowTips_EnhanceGuide", this);
		}
		
		private function HideTips(e:MouseEvent):void
		{
			ExternalInterface.call("ASHideTips_EnhanceGuide", this);
		}
	}
	
}
