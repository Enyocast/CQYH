
package UI_AuctionHouse.AS {

	import ActionScript3.Slot.ItemSlotData;
	public class AuctionItemData extends Object
	{
		public var AuctionID:int; // ID号
		public var ItemData:ItemSlotData;// = new ItemSlotData();
		public var ItemName:String = "";
		public var ItemLevel:int = 0;
		public var Seller:String = "";
		public var SellerID:int = -1;
		
		public var Buyer:String = "";
		public var BuyerID:int = -1;
		public var ForceDisplayBuyer:Boolean = false;
		
		public var StackCount:int = 1; // 堆叠数量，用于显示单价时切换
		public var ShowUnitPrice:Boolean = false;
		public var CurrentAuctionPrice:int = 0;
		public var FixedPrice:int = 0; // 一口价		
		public var TimeLeft:int = 0;
		
		public var ItemColor:int = 0;
		public var AuctionMainType:int = 0;
		public var AuctionSubType:int = 0;		
		public var ItemTemplateID:int = 0;
		
		public var IsAuction:Boolean = false;//是否已经竞价
		public var IsMyAuction:Boolean = false;//我的竞价是最高
		public var CurrentTabPage = 0;
		
		public var UnitPrice_Auction:int = 0;
		public var UnitPrice_Fixed:int = 0;
		
		function inc5Percent(price:int):int
		{
			if(IsAuction)
			{
				return Math.ceil(price*1.05);
			}
			else
			{
				return price;
			}
			
			//if(price <= 0)
			//{
				//return 1;
			//}
	
			//if (price < 20)
				//return price + 1;
			//else
				//return price + Math.ceil(price / 20);
		}
		
	
		public function getNextAuctionPrice():int
		{
			var nextprice:int = inc5Percent(CurrentAuctionPrice);

			if (FixedPrice > 0 && nextprice > FixedPrice)
				return FixedPrice;
			else
				return nextprice;
		}
	};
}