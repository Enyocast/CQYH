//
// 新手引导
//
package ActionScript3.Guide
{
	import flash.display.DisplayObject;
	import flash.external.ExternalInterface;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.events.KeyboardEvent;
	import flash.display.MovieClip;
	import flash.text.TextField;
	import flash.text.TextFieldAutoSize;
	import flash.utils.getDefinitionByName;

	import scaleform.clik.core.UIComponent;
	import scaleform.clik.constants.InvalidationType;
	import scaleform.clik.controls.Button;
	import scaleform.clik.controls.ScrollBar;
	import scaleform.clik.controls.ScrollingList;
	import scaleform.clik.controls.ListItemRenderer;
	import scaleform.clik.events.ButtonEvent;
	import scaleform.clik.events.ListEvent;
	import scaleform.clik.data.DataProvider;
	import scaleform.clik.data.TreeDataProvider;
	import scaleform.clik.utils.Padding;
	
	import ActionScript3.MyPanel;
	import ActionScript3.MyTipButton;
	import scaleform.clik.controls.CheckBox;

	public class GuideIllustrate extends MyPanel
	{
		public var guide_close_bt_mc:Button;
		//public var guide_close_small_bt_mc:Button;
		public var guide_title_tf:TextField;
		public var guide_content_mc:MovieClip;
		public var cur_guide_id:int = 0;
	
		override protected function configUI():void
		{
			super.configUI();
			trace(">>>>>>>>>>>>>>> GuideIllustrate::configUI");
			guide_close_bt_mc.addEventListener(MouseEvent.CLICK, onBtClickClose);
			//guide_close_small_bt_mc.addEventListener(MouseEvent.CLICK,onBtClickClose);
			guide_content_mc.mouseChildren=false;
			guide_content_mc.mouseEnabled=false;
		}
		
		public function onBtClickClose(e:MouseEvent):void
		{
			this.visible = false;
			ExternalInterface.call("ASCloseGuidePanel", cur_guide_id);
		}
		
		public function setIllustrate(title:String, name:String)
		{
			guide_title_tf.text = title;
			guide_content_mc.source = name;
		}
	}
}


























