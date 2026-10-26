package UI_PopUpHintBox.PopUpHintBoxAS3
{
	import flash.events.MouseEvent;
	import flash.external.ExternalInterface;
	
	import ActionScript3.MyPanel;
	import scaleform.clik.controls.Button;
	import flash.text.TextField;
	import ActionScript3.ItemSlot.MyItemSlot;
	import ActionScript3.Common.Events.ParamEvent;
	
	public class EquipGainHintBox extends MyPanel
	{
		public var GainedEquipIconSlot:MyItemSlot;
		public var EquipScoreTf:TextField;
		public var HintBoxMsgTf:TextField;
		public var CloseHintBtn:Button;
		public var CheckEquipBtn:Button;
		
		override protected function configUI():void
		{
			ShowMode = "TRB";
			super.configUI();
			//
			CheckEquipBtn.addEventListener( MouseEvent.CLICK, onClickCheckEquipButton );
			CloseHintBtn.addEventListener( MouseEvent.CLICK, onClickCloseHintButton );
			stageChangeHandler(null);
		}
		
		override protected function stageChangeHandler(evt:ParamEvent):void
		{
			super.stageChangeHandler(evt);
			this.x=cavasWidth-257;
			this.y=cavasHeight-254;
		}
		//
		public function onClickCheckEquipButton( e:MouseEvent ):void
		{
			ExternalInterface.call( "ASCheckNewEquipment");
		}
		//
		public function onClickCloseHintButton( e:MouseEvent):void
		{
			ExternalInterface.call( "ASCloseNewEquipmentHintBox");
		}
	}
}