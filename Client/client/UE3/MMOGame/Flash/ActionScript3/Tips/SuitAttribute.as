package ActionScript3.Tips {
	
	import flash.display.MovieClip;
	import flash.text.TextField;
	
	public class SuitAttribute extends MovieClip
	{
		public var tf_Text:TextField;
		public var mc_SuitBg:MovieClip;
		public var TipHeight:int = 0;
		public var TipWidth:int = 0;
		
		public function SuitAttribute()
		{
			// constructor code
			tf_Text.autoSize = flash.text.TextFieldAutoSize.LEFT;
			tf_Text.wordWrap = true;
		}
		
		public function ReSize()
		{
			mc_SuitBg.height = tf_Text.textHeight + 12;
			TipHeight = mc_SuitBg.height;
			TipWidth = mc_SuitBg.width;
		}
		
		public function SetData(strText:String)
		{
			//trace("@@@@@@@@@@@@@@@", name, strText);
			if("" == strText || strText == null)
			{
				if(visible)
					visible = false;
			}
			else
			{
				if(!visible)
					visible = true;
				tf_Text.htmlText = strText;
				
				ReSize();
			}
		}
		
		public function GetHeight():int
		{
			return tf_Text.textHeight + 12;
		}
	}
	
}
