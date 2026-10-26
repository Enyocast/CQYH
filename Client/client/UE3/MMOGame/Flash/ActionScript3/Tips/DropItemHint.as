/********************************************************************
Created:2013/07
Filename: DropItemHint
file ext:as
Author:hemu@snda
Purpose:Tips系统 掉落拾取（其实是个按钮，并不是真正的Tip 延续习惯）
*********************************************************************/

package ActionScript3.Tips
{

	import ActionScript3.MyPanel;

	import flash.display.MovieClip;
	import flash.events.MouseEvent;
	import flash.external.ExternalInterface;
	import flash.text.TextField;
	import flash.text.TextFieldAutoSize;

	import scaleform.clik.controls.Button;
	import scaleform.clik.controls.ListItemTreeRenderer;
	import scaleform.clik.core.UIComponent;
	import scaleform.gfx.TextFieldEx;
	import ActionScript3.Tips.CommonTipData;
	import scaleform.clik.controls.UILoader;

	public class DropItemHint extends UIComponent
	{
		public var PickableItemId:Number;
		public var mc_hint:MovieClip;
		public var mc_icon:UILoader;
		
		public function DropItemHint()
		{
			mc_hint.addEventListener("click",ClickTip);

//			tf_Text.autoSize = flash.text.TextFieldAutoSize.CENTER;
//			tf_Text.wordWrap = false;
		}

		public function ClickTip()
		{
			ExternalInterface.call("Pickup",PickableItemId );
		}
		
		public function SetTipContent( id:int, str:String, txColor:int, strIcon:String )
		{
			PickableItemId = id;
			
			var title_tf:TextField = mc_hint.getChildByName("tf_Text") as TextField;
			title_tf.text =  str;
			title_tf.textColor = txColor;
			
			mc_icon.source = strIcon;
		}
	}

}