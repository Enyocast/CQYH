package UI_GoldStore.AS
{
	import flash.globalization.DateTimeFormatter;
	import flash.text.TextField;

	public class GoldStoreListItem_RecordList extends GoldStoreListItemBase
	{
		public var txt_deal_date:TextField;
		public var txt_deal_time:TextField;
		public var txt_deal_type:TextField;
		
		public function GoldStoreListItem_RecordList()
		{
			super();
		}
		
		override protected function configUI():void
		{
			super.configUI();
		}
		
		override public function setData(data:Object):void
		{
			super.setData(data);
			var itemData:GoldStoreItemData = data as GoldStoreItemData;
			if(itemData != null)
			{
				visible = true;
				unitPrice_txt_mc.text = GoldStoreUltils.couponToGold(itemData.Coupon);
				txt_num_of_sell.text = itemData.Count.toString() + GoldStoreUltils.MONEY_UNIT;
				txt_deal_type.text = itemData.ExchangeTypeStr;
				txt_deal_type.textColor = (itemData.ExchangeType == GoldStoreUltils.EXCHANGE_TYPE_BUY) ? 0x84ec60 : 0xf64e1a;
				formatDealTime(itemData.dealTime * 1000);
			}
			else
			{
				visible = false;
			}
		}
		
		private function formatDealTime(GMT_Time:Number):void
		{
			var date:Date = new Date(GMT_Time);
			txt_deal_date.text = "" + date.fullYear + "/" + (date.month + 1) + "/" + date.date;
			if(txt_deal_time)
			{
				txt_deal_time.text = formatTimeStr(date.hours, date.minutes, date.seconds);
			}
		}
		
		private function formatTimeStr(hours:int, minutes:int, seconds:int):String
		{
			var result:String = "";
			result = result + int(hours / 10) + (hours % 10);
			result = result + ":" + int(minutes / 10) + (minutes % 10);
			result = result + ":" + int(seconds / 10) + (seconds % 10);
			return result;
		}
	}
}