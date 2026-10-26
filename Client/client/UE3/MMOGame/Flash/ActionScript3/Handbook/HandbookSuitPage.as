
package ActionScript3.Handbook
{
	import flash.display.MovieClip;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.external.ExternalInterface;
	import flash.filters.ColorMatrixFilter;
	import flash.geom.ColorTransform;
	import flash.text.TextField;
	
	import ActionScript3.ItemSlot.MyItemSlot;
	
	import fl.motion.ColorMatrix;
	
	import scaleform.clik.controls.Button;
	import scaleform.clik.core.UIComponent;
	import scaleform.clik.events.ButtonEvent;
	
	public class HandbookSuitPage extends UIComponent
	{
		public var suit_avatar_mc:MovieClip;
		public var suit_item_title_tf:TextField;
		public var suit_item_0_mc:MyItemSlot;
		public var suit_item_1_mc:MyItemSlot;
		public var suit_item_2_mc:MyItemSlot;
		public var suit_item_3_mc:MyItemSlot;
		public var suit_item_4_mc:MyItemSlot;
		public var suit_item_5_mc:MyItemSlot;
		public var suit_item_6_mc:MyItemSlot;
		public var suit_item_7_mc:MyItemSlot;
		public var suit_item_8_mc:MyItemSlot;
		public var suit_item_9_mc:MyItemSlot;
		public static const suit_item_max_count = 10;
		public var btn_rotate_left:Button;
		public var btn_rotate_right:Button;
		public var bottom_tf:TextField;
		
		public var handbook_data:HandbookData;
		
		public function HandbookSuitPage()
		{
			// constructor code
		}
		
		override protected function configUI():void
		{
			super.configUI();
			
			btn_rotate_left.addEventListener(MouseEvent.MOUSE_DOWN, onRotateToLeft, false, 0, true);
			btn_rotate_left.addEventListener(MouseEvent.MOUSE_UP, onReleaseLeft, false, 0, true);
			btn_rotate_right.addEventListener(MouseEvent.MOUSE_DOWN, onRotateToRight, false, 0, true);
			btn_rotate_right.addEventListener(MouseEvent.MOUSE_UP, onReleaseRight, false, 0, true);
			_height = bottom_tf.y + bottom_tf.height;
			
			
			suit_item_0_mc.addEventListener(ButtonEvent.CLICK, onItemCLick, false, 0, true);
			suit_item_1_mc.addEventListener(ButtonEvent.CLICK, onItemCLick, false, 0, true);
			suit_item_2_mc.addEventListener(ButtonEvent.CLICK, onItemCLick, false, 0, true);
			suit_item_3_mc.addEventListener(ButtonEvent.CLICK, onItemCLick, false, 0, true);
			suit_item_4_mc.addEventListener(ButtonEvent.CLICK, onItemCLick, false, 0, true);
			suit_item_5_mc.addEventListener(ButtonEvent.CLICK, onItemCLick, false, 0, true);
			suit_item_6_mc.addEventListener(ButtonEvent.CLICK, onItemCLick, false, 0, true);
			suit_item_7_mc.addEventListener(ButtonEvent.CLICK, onItemCLick, false, 0, true);
			suit_item_8_mc.addEventListener(ButtonEvent.CLICK, onItemCLick, false, 0, true);
			suit_item_9_mc.addEventListener(ButtonEvent.CLICK, onItemCLick, false, 0, true);
			
			btn_rotate_left.visible = true;
			btn_rotate_right.visible = true;
		}
		
		private function onRotateToLeft(evt:MouseEvent):void
		{
			ExternalInterface.call(ConstansDefine.ASPlayerRotate, 0);
		}
		
		private function onReleaseLeft(evt:MouseEvent):void
		{
			ExternalInterface.call(ConstansDefine.ASReleaseRotate);
		}
		
		private function onRotateToRight(evt:MouseEvent):void
		{
			ExternalInterface.call(ConstansDefine.ASPlayerRotate, 1);
		}
		
		private function onReleaseRight(evt:MouseEvent):void
		{
			ExternalInterface.call(ConstansDefine.ASReleaseRotate);
		}
		
		private function onItemCLick(evt:ButtonEvent):void
		{
			var item_mc:MyItemSlot = evt.currentTarget as MyItemSlot;
			if (item_mc)
			{
				ExternalInterface.call(ConstansDefine.ASGotoEquipPage, item_mc.itemIndex);
			}
		}
		
		public function updateHandbookData(data:HandbookData)
		{
			handbook_data = data;
			if (handbook_data)
			{
				var i:int = 0;
				var item_list:Array = handbook_data.handbook_data0;
				suit_item_title_tf.visible = item_list.length > 0;
				for (i = 0; i < suit_item_max_count; i ++)
				{
					var item_mc:MyItemSlot = this["suit_item_" + i + "_mc"] as MyItemSlot;
					if (i < item_list.length)
					{
						item_mc.SetData(0, item_list[i].item_icon, item_list[i].item_id, "", 0, -1, -1);
						item_mc.visible = true;
					}
					else
					{
						item_mc.visible = false;
					}
				}
			}
			_height = bottom_tf.y + bottom_tf.height;
		}
	}
}
























