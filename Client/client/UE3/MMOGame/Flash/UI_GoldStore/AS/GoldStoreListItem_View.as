package UI_GoldStore.AS
{
	import flash.display.MovieClip;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.external.ExternalInterface;
	import flash.text.TextField;
	import flash.text.TextFormat;
	import flash.text.TextFormatAlign;
	
	import ActionScript3.MoneyInput;
	import ActionScript3.Slot.MySlot;
	
	import scaleform.clik.controls.Button;
	import scaleform.clik.controls.ListItemTreeRenderer;
	import scaleform.gfx.MouseEventEx;
	import UI_GoldStore.AS.moneyTypeIcon.GoldStoreMoneyIcon;
	
	public class GoldStoreListItem_View extends GoldStoreListItemBase 
	{
		public var unitPrice_txt_mc_money_icon:GoldStoreMoneyIcon;
		public var txt_exchange_type:TextField;
		public var frame_mc:MovieClip;
		
		private var _exchangeType:int = 0;
		
		public function GoldStoreListItem_Buy()
		{
			// constructor code
		}
		
		override protected function configUI():void
		{
			super.configUI();
			this.mouseChildren = false;
			txt_exchange_type.mouseEnabled=false;
		}
		
		override function updateData(dat:Object):void
		{	
			var itemData:GoldStoreItemData = dat as GoldStoreItemData;
			if(itemData != null)
			{
				visible = true;
				unitPrice_txt_mc_money_icon.couponValue = itemData.Coupon;
				txt_num_of_sell.text 	= itemData.Count.toString() + GoldStoreUltils.MONEY_UNIT;
				txt_exchange_type.text 	= itemData.ExchangeTypeStr + GetTypeStr(itemData.GoldStoreID);
				if(_exchangeType != itemData.ExchangeType)
				{
					_exchangeType = itemData.ExchangeType;
					if(_exchangeType == GoldStoreUltils.EXCHANGE_TYPE_BUY)
					{
						txt_exchange_type.textColor = 0x84ec60;
					}
				}
			}
			else
			{
				visible = false;
			}
		}
		
		public function GetTypeStr(index:int):String
		{
			var res:String  = "";
			
			switch(index)
			{
				case 0:
					res = "一";
					break;
				case 1:
					res = "二";
					break;
				case 2:
					res = "三";
					break;
				case 3:
					res = "四";
					break;
				case 4:
					res = "五";
					break;
			}
			
			return res;
		}
		
		
	}
	
}
