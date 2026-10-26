/********************************************************************
Created:2013/06
Filename: TextWithTipControl
file ext:as
Author:hemu@snda
Purpose:Tips系统View 用于显示文字且带有Tip的控件
*********************************************************************/

package ActionScript3.Tips
{
	
	import flash.display.MovieClip;
	import flash.events.Event;
	import flash.events.MouseEvent;
	

	import scaleform.clik.core.UIComponent;
	import scaleform.clik.controls.RadioButton;
	import scaleform.clik.controls.UILoader;

	import flash.external.ExternalInterface;
	import flash.text.TextField;

	public class TextWithTipControl extends UIComponent
	{
		public var tf_Text:TextField;
		public var tipsHtml:String;
		
		override protected function configUI():void 
		{
			super.configUI();
			
			var strSource:String =  "MMOGame.Character." + this.name;
			ExternalInterface.call("ASGetStringByID", this, "tipsHtml", strSource );
		
			this.addEventListener( MouseEvent.ROLL_OVER, ShowTips);
			this.addEventListener( MouseEvent.ROLL_OUT, HideTips);
		}
		
		function ShowTips(e:Event)
		{
			ExternalInterface.call("ASShowTips_PlainText", this);

		}
		
		function HideTips(e:Event)
		{
			ExternalInterface.call("ASHideTips_PlainText", this);

		}
	}

}