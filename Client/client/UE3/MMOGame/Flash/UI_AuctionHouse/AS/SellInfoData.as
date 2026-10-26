
package UI_AuctionHouse.AS {
	import ActionScript3.Slot.ItemSlotData;

	
	public class SellInfoData extends Object
	{
		public var ItemData:ItemSlotData;// = new ItemSlotData();
		//public var ContainerID:int = -1;
		//public var SlotID:int = -1;
		public var ItemName:String = "";	
		
		public var AuctionTime:int;	// 拍卖时间	
		
		public var ActionTotalPrice:int; // 竞标总价
		public var ActionUnitPrice:int; // 竞标单价		
		public var TotalFixedPrice:int; // 一口总价
		public var ManagePrice:int; // 保管费
		public var DefaultPrice:int; // 默认价格
		
		public var ManageInfo:String = ""; // 保管信息提示
		public var TaxInfo:String = ""; // 税费提示
		
		//public var CurrentPlayerMoney:int; // 玩家当前金钱
		
		public var ShowUnitPrice:Boolean; // 显示单价
	};
}