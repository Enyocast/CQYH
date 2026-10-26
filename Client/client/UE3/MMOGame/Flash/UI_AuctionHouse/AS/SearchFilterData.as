package UI_AuctionHouse.AS {
	
	public class SearchFilterData 
	{

		// 物品名称
		public var item_name:String = "";		
		
		// 职位
		public var player_class_idx:int = 0;
		public var player_class_list:Array = new Array();
		
		// 等级
		public var lv_min:int = 0;
		public var lv_max:int = 100;
		
		// 品质
		public var item_color_idx:int;
		public var item_color_list:Array = new Array();
		
		// 状态
		public var auction_status:int;
		public var auction_status_list:Array = new Array();
	}
	
}
