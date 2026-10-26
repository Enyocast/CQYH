package ActionScript3.Widget{
	import ActionScript3.MyItemSlot;
	import ActionScript3.MyItemSlotShow;
	import ActionScript3.MyPanel;
	import flash.text.TextField;
	import scaleform.clik.controls.Button;
	import flash.events.MouseEvent;
	import flash.events.Event;
	import flash.external.ExternalInterface;
	
	public class UnEnhancePanel extends MyPanel
	{
		public var unEnhanceItem_mc:MyItemSlot;
		//辅助材料Icon
		public var unMatAuxiliary_mc:MyItemSlot;
		//消除强化费
		public var tf_mnyUnenhance:TextField;
		//当前强化等级
		public var tf_curDegree2:TextField;
		//最大强化等级
		public var tf_maxDegree2:TextField;
		//取消强化按钮
		public var btn_unEnhance:Button;
		//
		override protected function configUI():void
		{
			super.configUI();
			unEnhanceItem_mc.itemSlotBg.visible = false;
			//unMatAuxiliary_mc.itemSlotBg.visible = false;
			btn_unEnhance.textField.text = "装备回退";
			btn_unEnhance.addEventListener( "click", UnEnhanceItem );
		}

		function UnEnhanceItem()
		{
			ExternalInterface.call( "UnEnhanceItem" );
		}

	}
}