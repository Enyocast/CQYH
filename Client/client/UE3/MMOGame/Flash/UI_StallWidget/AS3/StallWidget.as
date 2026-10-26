package UI_StallWidget.AS3
{
	import flash.external.ExternalInterface;
	
	import ActionScript3.MyPanel;
	
	import UI_StallWidget.AS3.StallItemSetting;
	
	import scaleform.clik.controls.Button;
	import scaleform.clik.controls.TextInput;
	import scaleform.clik.events.ButtonEvent;


	public class StallWidget extends MyPanel
	{
		public var itemSetting:StallItemSetting;
		
		override protected function configUI():void
		{
			super.configUI();
			btn_close.RemoveAddedEventListener();
			btn_close.addEventListener(ButtonEvent.CLICK, onCloseButtonClick);
		}
		
		public function UpdateStallSettingWidget( tData:Object )
		{
			SetWindowTitle(tData.WidgetName);
		}

		public function UCSetFocus()
		{
			itemSetting.setFocus();
		}
		
		public function UCUpdateMoney( tData:Object )
		{
			itemSetting.UpdateMoney(tData);
		}
		
		public function UCUpdateButtonState( tData:Object )
		{
			itemSetting.UpdateButtonState(tData);
		}
		
		public function UCCheckSettingItem(slotIndex:int):void
		{
			itemSetting.checkItemGoldText(slotIndex);
		}
		
		public function UCUpdateNameAndAdd( tData:Object )
		{
			itemSetting.UpdateNameAndAdd( tData );
		}
		
		public function UCSetUpdateTimeLeft(info:String, over:Boolean):void
		{
			itemSetting.setUpdatIimeLeft(info, over);
		}
		
		public function UCSetRecordListData(data:Array):void
		{
			itemSetting.setRecordListData(data);
		}
		
		private function onCloseButtonClick(evt:ButtonEvent):void
		{
			ExternalInterface.call( "ASCloseStallPanel");
		}
	}

}