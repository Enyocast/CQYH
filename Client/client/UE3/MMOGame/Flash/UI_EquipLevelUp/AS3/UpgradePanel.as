package UI_EquipLevelUp.AS3
{
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.external.ExternalInterface;
	import flash.text.TextField;
	
	import ActionScript3.MyPanel;
	import ActionScript3.Common.MoneyInputNew;
	import ActionScript3.ItemSlot.MyItemSlot;
	
	import scaleform.clik.controls.Button;
	import scaleform.clik.managers.PopUpManager;
	import scaleform.gfx.InteractiveObjectEx;
	
	public class UpgradePanel extends MyPanel
	{
		public var weapon_slot_mc:MyItemSlot;
		
		public var ironstone_slot_0:MyItemSlot;
		public var ironstone_slot_1:MyItemSlot;
		public var ironstone_slot_2:MyItemSlot;
		public var ironstone_slot_3:MyItemSlot;
		
		public var ironstone_slot_4:MyItemSlot;
		
		public var jewelry_slot_0:MyItemSlot;
		public var jewelry_slot_1:MyItemSlot;
		public var jewelry_slot_2:MyItemSlot;
		public var jewelry_slot_3:MyItemSlot;
		public var jewelry_slot_4:MyItemSlot;
		
		public var txt_cost_money:TextField;
		
		public var btn_upgrade:Button;
		public var btn_cancel:Button;
		
		//reference
		private var _messageBox:MessageBox_Upgrade;
		
		public function UpgradePanel()
		{
			super();
		}
		
		public function set messageBox(value:MessageBox_Upgrade):void
		{
			_messageBox = value;
		}
		
		override public function OnFocusGained():void
		{
			super.OnFocusGained();
			//(parent as MoviePlayer_WeaponUpgrade).setPanelToTop(this);
		}
		
		override protected function configUI():void
		{
			super.configUI();
			btn_upgrade.addEventListener(MouseEvent.CLICK, onUpgradeButtonClick);
			btn_cancel.addEventListener(MouseEvent.CLICK, onCancelButtonClick);
			
			ExternalInterface.call( "RegisterEquipLevelUp", this );
		}
		
		override public function UCGetWidth():int
		{
			if(MyWindowsFrame_mc){
				return MyWindowsFrame_mc.width;//fix new window use mask in background 
			}
			return super.UCGetWidth();
		}
		
		private function onUpgradeButtonClick(evt:Event):void
		{
			ExternalInterface.call("ASConfirmUpgrade");
		}
		
		private function onCancelButtonClick(evt:Event):void
		{
			ExternalInterface.call("ASCancelUpgrade");
		}
		
		//set cost money
		public function UCSetUpgradeCostMoney(valueStr:String):void
		{
			txt_cost_money.htmlText = valueStr;
		}
		
		//set data to message box
		public function UCSetUpgradeResultData(data:UpgradeResultData = null):void
		{
			if(_messageBox)
			{
				_messageBox.UCSetUpgradeResultData(data);
			}
		}
		
		public function UCShowLevelUpResult( isToShow:Boolean ):void
		{
			if(_messageBox)
			{
				_messageBox.visible = isToShow;
			}
		}
	}
}