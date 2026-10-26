package UI_BackDecorated.AS3
{
	import flash.external.ExternalInterface;
	import flash.text.TextField;
	
	import ActionScript3.MyPanel;
	import ActionScript3.Common.Utils.ConfigConstants;
	import ActionScript3.ItemSlot.MyItemSlot;
	
	import scaleform.clik.controls.Button;
	import scaleform.clik.controls.RadioButton;
	import scaleform.clik.events.ButtonEvent;
	
	public class BackDecoratedPanel extends MyPanel
	{
		public var makeUpPage_mc:DecorationMakeUpPage;
		public var upgradePage_mc:DecorationUpgradePage
		
		public var tab_decoration_makeUp:RadioButton;
		public var tab_decoration_upgrade:RadioButton;
		
		private static const C_PAGE_TYPE_MAKEUP:int  = 1;
		private static const C_PAGE_TYPE_UPGRADE:int = 2;
		
		private var _curPageType:int = 0;
		
		public function BackDecoratedPanel()
		{
			super();
		}
		
		override protected function configUI():void
		{
			ShowMode = ConfigConstants.PANEL_SHOW_MODE_BC;
			super.configUI();
			SetWindowTitle("背饰熔炼");
			
			tab_decoration_makeUp.addEventListener(ButtonEvent.CLICK, onViewDecorationSmelting);
			tab_decoration_upgrade.addEventListener(ButtonEvent.CLICK, onViewDecorationUpgrade);
			tab_decoration_makeUp.selected = true;
			onViewDecorationSmelting(null);
			//
			//testInterface();
		}
		
		private function testInterface():void
		{
			UCSetMakeUpConsumptionInfo("3.tga", 1, 1, 100, 50);
			UCSetMakeUpResultItem("2.tga", 2, 1);
			UCSetMakeUpMoney("1000万");
			UCUpgradeConsumptionItem("2.tga", 3, 1, 350, 100);
			UCSetUpgradedResultItem("3.tga",4, 1);
			UCSetUpgradeMoney("200w");
			UCSetUpgradeSuccessRate(85);
		}
		
		private function onViewDecorationSmelting(evt:ButtonEvent):void
		{
			makeUpPage_mc.visible = true;
			upgradePage_mc.visible = false;
			_curPageType = C_PAGE_TYPE_MAKEUP;
			ExternalInterface.call("ASOnTabClick", _curPageType);
		}
		
		private function onViewDecorationUpgrade(evt:ButtonEvent):void
		{
			makeUpPage_mc.visible = false;
			upgradePage_mc.visible = true;
			_curPageType = C_PAGE_TYPE_UPGRADE;
			ExternalInterface.call("ASOnTabClick", _curPageType);
		}
		
		//获取当前显示的面板，1为背饰合成界面，2为背饰升级界面
		public function UCGetCurrentPanelType():int
		{
			return _curPageType;
		}
		
		//设置当前背饰的物品消耗slot
		public function UCSetMakeUpConsumptionInfo(iconName:String, itemID:int, colorIdx:int, curConsumptionCnt:int, needConsumptionCnt:int):void
		{
			makeUpPage_mc.UCSetMakeUpConsumptionInfo(iconName, itemID, colorIdx, curConsumptionCnt, needConsumptionCnt);
		}
		
		//设置最后合成的背饰slot
		public function UCSetMakeUpResultItem(iconName:String, itemID:int, colorIdx:int):void
		{
			makeUpPage_mc.UCSetMakeUpResultItem(iconName, itemID, colorIdx);
		}
		
		//------------------------------------------------------------------------------------------------------------------//
		//设置背饰合成的金币消耗
		public function UCSetMakeUpMoney(moneyStr:String):void
		{
			makeUpPage_mc.UCSetMakeUpMoney(moneyStr);
		}
		
		//设置当前背饰升级的物品消耗slot
		public function UCUpgradeConsumptionItem(iconName:String, itemID:int, colorIdx:int, curConsumptionCnt:int, needConsumptionCnt:int):void
		{
			upgradePage_mc.UCUpgradeConsumptionItem(iconName, itemID, colorIdx, curConsumptionCnt, needConsumptionCnt);
		}
		
		//设置升级后的背饰slot
		public function UCSetUpgradedResultItem(iconName:String, itemID:int, colorIdx:int):void
		{
			upgradePage_mc.UCSetUpgradedResultItem(iconName, itemID, colorIdx);
		}
		
		//设置背饰升级金币消耗
		public function UCSetUpgradeMoney(moneyStr:String):void
		{
			upgradePage_mc.UCSetUpgradeMoney(moneyStr);
		}
		
		//设置背饰升级成功率
		public function UCSetUpgradeSuccessRate(percent:int):void
		{
			upgradePage_mc.UCSetUpgradeSuccessRate(percent);
		}
	}
}