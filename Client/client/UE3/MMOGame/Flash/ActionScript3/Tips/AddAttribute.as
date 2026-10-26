/********************************************************************
Created:2013/06
Filename: AddAttribute
file ext:as
Author:hemu@snda
Purpose:Tips系统View AddAttribute控件
*********************************************************************/

package ActionScript3.Tips
{
	import flash.display.MovieClip;
	import flash.external.ExternalInterface;
	import flash.text.TextField;
	import flash.text.TextFieldAutoSize;

	public class AddAttribute extends MovieClip
	{
		public var tf_Text:TextField;
		public var tf_Title:TextField;
		public var TipHeight:int;
		public var nSpacing:int = 8;

		public function AddAttribute()
		{
			// constructor code
			tf_Text.autoSize = flash.text.TextFieldAutoSize.LEFT;
			tf_Text.wordWrap = true;
		}
		
		public function SetData(strText:String)
		{
			if(null == strText || strText == "" )
			{
				if(visible)
					visible = false;
			}
			else
			{
				if(!visible)
					visible = true;
				tf_Text.htmlText = strText;
			}
		}
		
		public function ReSize(startY:int, Spacing:int):int
		{
			y = startY;
			nSpacing = Spacing;
			return y + tf_Text.textHeight + nSpacing;
		}
		
		public function GetHeight():int
		{
			return tf_Text.textHeight + nSpacing;
		}
	}

}