
package UI_GoldStore.AS {

	public class GoldStoreItemData extends Object
	{
		public var GoldStoreID:int = 0;
		public var GoldStoreID_High:int = 0; // ID号
		public var GoldStoreID_Low:int = 0;
		public var Coupon:int = 0;          //点卷
		public var Count:int = 0;		//数量
		public var times:int = 0;		//交易时间或下单时间
		public var ExchangeType:int = 0;//交易种类  1.购买 2.卖出
		public var ExchangeTypeStr:String = "";
		public var dealTime:int;		//成交时间
		public var orderTime:int;		//下单时间
		public var orderState:int = 0;	//订单状态
		public var CurCount:int = 0; //已经成交量

	};
}