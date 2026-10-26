package UI_VIP.AS3
{
	import flash.external.ExternalInterface;
	import ActionScript3.MyPanel;
	import scaleform.clik.controls.Button;
	import flash.events.MouseEvent;
	import ActionScript3.Common.Events.ParamEvent;
	import scaleform.clik.core.UIComponent;
	
	public class VIPPage_Shop extends UIComponent 
	{			
		public var btn_Warehouse:Button;
		public var btn_Shop:Button;
		public var btn_Soul:Button;
		public var btn_Inscription:Button;
		public var btn_Auction:Button;
		
		public var currentVipType:int = 0;
		
		public function VIPPage_Shop() 
		{
			// constructor code
		}
		
		override protected function configUI():void
		{
			super.configUI();
			btn_Warehouse.addEventListener(MouseEvent.CLICK, onWarehouseClick);
			btn_Shop.addEventListener(MouseEvent.CLICK,onShopClick);
			btn_Soul.addEventListener(MouseEvent.CLICK,onSoulClick);
			btn_Inscription.addEventListener(MouseEvent.CLICK,onInscriptionClick);
			btn_Auction.addEventListener(MouseEvent.CLICK,onAuctionClick);
			
		}
		
		public function onWarehouseClick(e:MouseEvent):void
		{
			onVipShopClick(0);
		}
		public function onShopClick(e:MouseEvent):void
		{
			onVipShopClick(1);
		}
		public function onSoulClick(e:MouseEvent):void
		{
			onVipShopClick(2);
		}
		public function onInscriptionClick(e:MouseEvent):void
		{
			onVipShopClick(3);
		}
		public function onAuctionClick(e:MouseEvent):void
		{
			onVipShopClick(4);
		}

		public function onVipShopClick(type:int)
		{
			ExternalInterface.call("ASVipShopClick",type);
		}
		
		public function updateShopBtnState(dat:int)
		{
			btn_Warehouse.enabled = (dat >= 1);
			btn_Shop.enabled = (dat >= 1);
			btn_Soul.enabled = (dat >= 2);
			btn_Inscription.enabled = (dat >= 2);
			btn_Auction.enabled = (dat >= 3);
		}
		
	}
	
}
