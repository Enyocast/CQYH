package ActionScript3
{
	public class TreeListData extends Object
	{
		public static const C_Type_Leaf = 0;
		public static const C_Type_Branch_Closed = 1;
		public static const C_Type_Branch_Opened = 2;
		
		public var label:String;
		public var index:int; // 数组中的索引值
		public var type:int; // 展开状态
		public var deepth:int; // 层级深度
		public var visible:Boolean;
		
		public function toString():String 
		{
            return "[TreeListData " + index + ", " + label + ", " + type + ", " + deepth + ", " + visible +"]";
        }
	}
}