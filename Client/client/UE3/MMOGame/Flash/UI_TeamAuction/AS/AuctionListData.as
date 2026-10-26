
package UI_TeamAuction.AS{

	import ActionScript3.TreeListData;
	public class AuctionListData extends TreeListData
	{					
		public var giveup:Boolean;
		public var itemPrice:int = 0;
		public var itemName:String = "";
		public var state:String = "";
		public var itemIndex:int = -1;
		public var slotData:Object = null;
	}
}