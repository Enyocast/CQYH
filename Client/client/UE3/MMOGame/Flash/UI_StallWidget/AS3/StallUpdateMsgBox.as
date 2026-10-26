package UI_StallWidget.AS3
{
	import flash.events.Event;
	import flash.external.ExternalInterface;
	import flash.text.TextField;
	
	import ActionScript3.MyPanel;
	import ActionScript3.Common.MoneyInputNew;
	import ActionScript3.Common.Utils.ConfigConstants;
	
	import scaleform.clik.controls.Button;
	import scaleform.clik.controls.DropdownMenu;
	import scaleform.clik.events.ButtonEvent;
	import scaleform.clik.events.ListEvent;
	
	public class StallUpdateMsgBox extends MyPanel
	{
		public var txt_hint:TextField;
		public var ddm_stall_update_time:DropdownMenu;
		public var money_cost:TextField;
		public var btn_stall_update:Button;
		
		public function StallUpdateMsgBox()
		{
			super();
		}
		
		override protected function configUI():void
		{
			ShowMode = ConfigConstants.PANEL_SHOW_MODE_BC;
			super.configUI();
			txt_hint.mouseEnabled = false;
			btn_stall_update.addEventListener(ButtonEvent.CLICK, onConfirmStallUpdate);
			ddm_stall_update_time.addEventListener(ListEvent.INDEX_CHANGE, onTimeListChangeSelect);
			SetWindowTitle("摊位升级");
		//	UCSetUpdateTimeListData(["1d","2d",'3d',"14d"]);
		}
		
		public function UCSetStallUpdateHintText(txt:String):void
		{
			txt_hint.text = txt;
		}
		
		public function UCSetUpdateTimeListData(data:Array):void
		{
			ddm_stall_update_time.dataList = data;
			ddm_stall_update_time.SplitData();
			ddm_stall_update_time.menuRowCount = Math.min(data.length, 5);
			ddm_stall_update_time.selectedIndex = 0;
		}
		
		public function UCSetUpdateCost(cost:int):void
		{
			money_cost.text = cost.toString();
		}
		
		private function onConfirmStallUpdate(evt:ButtonEvent):void
		{
			ExternalInterface.call("ASOnConfirmStallUpdate");
		}
		
		private function onTimeListChangeSelect(evt:ListEvent):void
		{
			ExternalInterface.call("ASOnTimeListChangeSelect", ddm_stall_update_time.selectedIndex);
		}
	}
}