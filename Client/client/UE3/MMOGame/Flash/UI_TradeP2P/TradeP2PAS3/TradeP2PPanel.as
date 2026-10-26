package UI_TradeP2P.TradeP2PAS3
{
	import flash.external.ExternalInterface;
	import ActionScript3.MyPanel;
	import scaleform.clik.controls.Button;
	import flash.text.TextField;
	import flash.events.MouseEvent;
	
	import UI_TradeP2P.TradeP2PAS3.TradeItemSlotContainer;
	
	public class TradeP2PPanel extends MyPanel
	{
		public var myTrade_mc:TradeItemSlotContainer;
		public var tgTrade_mc:TradeItemSlotContainer;
		
		public var tf_tradeTex:TextField;
		public var tf_tradeTexRate:TextField;
		
		public var btnConfirmTrade:Button;
		public var btnCancelTrade:Button;
		public var btnLockTrade:Button;

		override protected  function configUI():void
		{
			super.configUI();
			//myTrade_mc.tradeLock_mc.visible = false;
			//myTrade_mc.btnInputMny.addEventListener( "click", InputTradeMoney );
			
			//tgTrade_mc.tradeLock_mc.visible = false;
			tgTrade_mc.btnInputMny.enabled = false;
			btnConfirmTrade.addEventListener(MouseEvent.CLICK, Confirm );
			btnCancelTrade.addEventListener(MouseEvent.CLICK, Cancel );
			btnLockTrade.addEventListener(MouseEvent.CLICK, Lock );
		}
		//
		private function Confirm( e:MouseEvent ):void
		{
			ExternalInterface.call( "ASConfirmP2PTrade" );
		}
		//
		private function Cancel( e:MouseEvent ):void
		{
			ExternalInterface.call( "ASCancelP2PTrade" );
		}
		//
		private function Lock( e:MouseEvent ):void
		{
			ExternalInterface.call( "ASLockP2PTrade" );
		}
	}
}