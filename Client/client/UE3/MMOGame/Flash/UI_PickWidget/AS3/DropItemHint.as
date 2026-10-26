/********************************************************************
Created:2013/07
Filename: DropItemHint
file ext:as
Author:hemu@snda
Purpose:Tips系统 掉落拾取（其实是个按钮，并不是真正的Tip 延续习惯）
*********************************************************************/

package UI_PickWidget.AS3
{

	import flash.display.MovieClip;
	import flash.events.MouseEvent;
	import flash.external.ExternalInterface;
	import flash.text.TextField;
	
	import scaleform.clik.controls.UILoader;
	import scaleform.clik.core.UIComponent;
	import scaleform.clik.events.ComponentEvent;
	import flash.text.TextFieldAutoSize;
	import scaleform.clik.controls.Button;
	import scaleform.clik.events.ButtonEvent;

	public class DropItemHint extends UIComponent
	{
		public var PickableItemId:int;
		//public var bk_mc:MovieClip;
		public var mc_hint:MovieClip;
		public var type:int=0;
		public function DropItemHint()
		{
			//mc_hint.addEventListener(ButtonEvent.CLICK,ClickTip);//单击事件
			//mc_hint.addEventListener(ComponentEvent.STATE_CHANGE,stateChange);
			//SetTipContent(1,"测试",2,"",2);
			mouseEnabled = false;
		}
		
//		private function stateChange(e:ComponentEvent):void
//		{
//			if(mc_hint.state=="over"){
//				(mc_hint.getChildByName("over") as MovieClip).gotoAndStop(type+1);
//			}
//		}

//		public function ClickTip(evt:ButtonEvent):void
//		{
//			ExternalInterface.call("Pickup",PickableItemId );
//		}
		
		public function SetTipContent( ThisObj:Object, id:int, str:String, txColor:int, strIcon:String,quality:int):void
		{
			PickableItemId = id;
			type=quality;
			var title_tf:TextField = mc_hint.getChildByName("tf_Pick_Text") as TextField;
			title_tf.text =  str;
			title_tf.autoSize=TextFieldAutoSize.LEFT;//自动向左对齐
			title_tf.x=-(title_tf.width>>1);
			title_tf.textColor = txColor;

		}
	}

}