
package UI_AuctionHouse.AS 
{
	import ActionScript3.TreeListData;

	
	public class AuctionItemCategoryData extends TreeListData
	{
		public static const C_TypeLv1 = 0;
		public static const C_TypeLv2 = 1;
		public static const C_TypeLv3 = 2;
				
		public var categoryType:int;
		//public var Caption:String;
		public var isSelected:Boolean;
		public var mainTypeValue:int;
		public var subTypeValue:int;
		

		public function get isExpanded():Boolean
		{
			return type == TreeListData.C_Type_Branch_Opened;
		}
		
		public override function toString():String 
		{
            return "[AuctionItemCategoryData " + index + ", " + label
			+ ", type:" + type + ", MK:" + mainTypeValue + ", SK:" + subTypeValue +"]";
        }
	};
}