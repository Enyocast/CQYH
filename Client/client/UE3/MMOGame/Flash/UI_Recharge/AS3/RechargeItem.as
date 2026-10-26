package UI_Recharge.AS3 {
	
	import flash.display.MovieClip;
	import scaleform.clik.core.UIComponent;
	import flash.text.TextField;
	import scaleform.clik.controls.Button;
	import flash.events.MouseEvent;
	import flash.external.ExternalInterface;
	import scaleform.clik.controls.RadioButton;
	
	
	public class RechargeItem extends RadioButton
	{
/*		public var txt_timer:TextField;
		public var txt_gold:TextField;
		public var btn_ok:Button;*/
		
		public var idx:int=0;
		override protected  function configUI():void 
		{
			super.configUI();
		}
		
		public function updateData(_idx:int,dat:Object):void
		{
			idx=_idx;
/*          txt_timer.text=dat.Time;
			txt_gold.text=dat.Cost;*/
		}
		
/*		public function BtnEneable(bl:Boolean):void
		{
			btn_ok.enabled=bl;
		}*/

/*		private function clickHandler(evt:MouseEvent):void
		{
			ExternalInterface.call("ASTryRecharge",idx);
		}*/
	}
	
}
