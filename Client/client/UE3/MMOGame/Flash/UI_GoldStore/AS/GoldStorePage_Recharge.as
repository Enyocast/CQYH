package UI_GoldStore.AS
{
	import flash.events.MouseEvent;
	import flash.external.ExternalInterface;
	import flash.text.TextField;
	
	import scaleform.clik.controls.Button;
	import scaleform.clik.core.UIComponent;
	
	public class GoldStorePage_Recharge extends UIComponent 
	{				
		public var btn_recharge:Button;
		public var btn_sold:Button;
		public var txt_num_of_coins:TextField;
		public var txt_num_of_coupon:TextField;
		public var txt_num_of_cash:TextField;
		
		override protected function configUI():void
		{
			super.configUI();
			btn_recharge.addEventListener(MouseEvent.CLICK, onRechargeClick);
			btn_sold.addEventListener(MouseEvent.CLICK, onSoldClick);
			
			txt_num_of_cash.visible = false;//wph@2015-10-30 人民币交易暂时屏蔽
		}
		
		public function UCSetPlayerMoney(dat:int)
		{
			txt_num_of_coins.htmlText = GoldStoreUltils.formatNumString(dat);
		}
		
		public function UCSetPlayerRealMoney(dat:int)
		{
			txt_num_of_coupon.htmlText = GoldStoreUltils.couponToGold(dat);
		}
		
		public function UCSetPlayerRealCash(dat:Number)
		{
			txt_num_of_cash.htmlText = GoldStoreUltils.formatNumString(dat);
		}
		
		public function onRechargeClick(evt:MouseEvent):void
		{
			ExternalInterface.call("ASBuyMoney");
		}
		
		//TODO:
		public function onSoldClick(evt:MouseEvent):void
		{
			(parent as GoldStorePanel).ASShowNoticeTips(true);
		}
	}
}
