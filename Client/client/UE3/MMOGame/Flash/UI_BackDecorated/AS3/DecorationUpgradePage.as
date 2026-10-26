package UI_BackDecorated.AS3
{
	import flash.display.MovieClip;
	import flash.external.ExternalInterface;
	import flash.text.TextField;
	
	import ActionScript3.ItemSlot.MyItemSlot;
	
	import scaleform.clik.controls.Button;
	import scaleform.clik.core.UIComponent;
	import scaleform.clik.events.ButtonEvent;
	
	public class DecorationUpgradePage extends UIComponent
	{
		public var decoration_slot_mc:MyItemSlot;
		public var materials_slot_mc:MyItemSlot;
		public var upgrade_decoration_slot_mc:MyItemSlot;
		
		public var txt_success_rate:TextField;
		public var txt_cost_money:TextField;
		public var btn_upgrade:Button;
		
		public var upgrade_FX_mc:MovieClip;
		private var _canUpgrade:Boolean = false;
		private var _isPlaying:Boolean = false;
		
		public function DecorationUpgradePage()
		{
			super();
		}
		
		override protected function configUI():void
		{
			super.configUI();
			btn_upgrade.addEventListener(ButtonEvent.CLICK, onDecorationUpgrade);
			
			upgrade_FX_mc.mouseChildren = upgrade_FX_mc.mouseEnabled = upgrade_FX_mc.visible = false;
			upgrade_FX_mc.addFrameScript(upgrade_FX_mc.totalFrames - 1,  onAnimationPlayEnd);
		}
		
		private function onDecorationUpgrade(evt:ButtonEvent):void
		{
			if(!_isPlaying)
			{
				ExternalInterface.call("ASOnConfirmUpgrade");
				if(_canUpgrade)
				{
					playUpgradeFXAniamtion();
				}
			}
		}
		
		public function playUpgradeFXAniamtion():void
		{
			_isPlaying = true;
			upgrade_FX_mc.gotoAndPlay(1);
			upgrade_FX_mc.visible = true;
		}
		
		private function onAnimationPlayEnd():void
		{
			_isPlaying = false;
			upgrade_FX_mc.visible = false;
		}
		
		public function UCUpgradeConsumptionItem(iconName:String, itemID:int, colorIdx:int, curConsumptionCnt:int, needConsumptionCnt:int):void
		{
			materials_slot_mc.SetData(0, iconName, itemID, "", colorIdx, -1, -1);
			_canUpgrade = curConsumptionCnt >= needConsumptionCnt;
			var curCntColor:String = _canUpgrade ? "'#84ec60'" : "'#ff0000'";
			materials_slot_mc.valueAmount.htmlText = "<font color=" + curCntColor + ">"+ needConsumptionCnt.toString() +  "/" + curConsumptionCnt.toString() + "</font>";
		}
		
		public function UCSetUpgradedResultItem(iconName:String, itemID:int, colorIdx:int):void
		{
			upgrade_decoration_slot_mc.SetData(0, iconName, itemID, "", colorIdx, -1, -1);
		}
		
		public function UCSetUpgradeMoney(moneyStr:String):void
		{
			txt_cost_money.htmlText = moneyStr;
		}
		
		public function UCSetUpgradeSuccessRate(percent:int):void
		{
			txt_success_rate.htmlText = percent.toString() + "%";
		}
	}
}