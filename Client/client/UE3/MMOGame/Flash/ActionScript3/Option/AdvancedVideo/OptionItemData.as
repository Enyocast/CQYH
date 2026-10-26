package ActionScript3.Option.AdvancedVideo
{
	public class OptionItemData
	{
		//字段settingName
		public var optionKey:String;
		//数据类型
		public var type:int;
		//汉字显示名
		public var title:String;

/*
slider 可能需要显示最小值MinValue和最大值MaxValue 拖动最小步byDetalStep (==0时是直接滑动 没有最小步限制)
整形和浮点型都用sliderValue这个字段
*/
		public var sliderValue:Number;
		public var MaxValue:Number;
		public var MinValue:Number;
		public var byDetalStep:Number;
		
		//combox类型下拉列表
		public var ddmListData:Array;
		//选择的索引
		public var ddmSelectedIndex:int;
		
		//Bool数据
		public var checkButtonSelected:Boolean;
	}
}