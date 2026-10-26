package ActionScript3.Quest{
	import flashx.textLayout.formats.Float;
	
	public class SoulData extends Object
	{
		public static const SoulColor_Red = 0;
		public static const SoulColor_Yellow = 1;
		public static const SoulColor_Blue = 2;
		public static const SoulColor_RainBow = 3;
		
		public var soul_id:int		
		public var soul_name:String
		public var soul_type_name:String;
		public var soul_add_counter:Float;
		public var soul_add_percent:Float;
		public var soul_level:int;
		public var soul_quality:int;
		public var soul_skill_desc:String;
		
		
		public function toString():String
		{
			return "[" + soul_id.toString() + " " + soul_name + "]";
		}
		
	}

}