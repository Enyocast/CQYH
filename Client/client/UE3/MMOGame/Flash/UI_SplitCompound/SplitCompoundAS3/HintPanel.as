package UI_SplitCompound.SplitCompoundAS3
{
	import ActionScript3.MyPanel;
	import scaleform.clik.controls.Button;
	import ActionScript3.ItemSlot.MyItemSlot;
	import flash.text.TextField;
	import ActionScript3.MyWindowsFrame;
	import flash.external.ExternalInterface;
	import flash.events.MouseEvent;
	
	public class HintPanel extends MyPanel
	{
		public var HintText:TextField;
		public var ConfirmBtn:Button;
		public var CancelBtn:Button;
		//public var WindowFrm:MyWindowsFrame;
		
		override protected function configUI():void
		{
			super.configUI();
			SetWindowTitle("提示");
			ConfirmBtn.addEventListener(MouseEvent.CLICK,ClickOk);
			CancelBtn.addEventListener(MouseEvent.CLICK,ClickCancel);
		}
		
		private function ClickOk(evt:MouseEvent):void
		{
			ExternalInterface.call("ASDecomposeOk");
		}
		
		private function ClickCancel(evt:MouseEvent):void
		{
			ExternalInterface.call( "ASOnPanelClose" , this.name );
			//ExternalInterface.call("ASDecomposeCancel");
		}
		
		public function SetHintText(tData:Object):void
		{
			HintText.text = tData.Text;
		}
	}
}