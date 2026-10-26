package UI_GoldStore.AS
{
	import flash.external.ExternalInterface;
	
	import scaleform.clik.controls.Button;
	import scaleform.clik.core.UIComponent;
	import scaleform.clik.events.ButtonEvent;
	
	public class GoldStoreNoticeTips extends UIComponent
	{
		public var btn_confirm:Button;
		public var btn_cancel:Button;
		
		public function GoldStoreNoticeTips()
		{
			super();
		}
		
		override protected function configUI():void
		{
			super.configUI();
			btn_confirm.addEventListener(ButtonEvent.CLICK, onConfirmButtonClick);
			btn_cancel.addEventListener(ButtonEvent.CLICK, onCancelButtonClick);
		}
		
		private function onConfirmButtonClick(evt:ButtonEvent):void
		{
			ExternalInterface.call("ASSoldMoney");
			(parent as GoldStorePanel).ASShowNoticeTips(false);
		}
		
		private function onCancelButtonClick(evt:ButtonEvent):void
		{
			(parent as GoldStorePanel).ASShowNoticeTips(false);
		}
	}
}