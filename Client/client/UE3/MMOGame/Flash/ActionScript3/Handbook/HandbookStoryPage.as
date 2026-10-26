
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
	
	public class HandbookStoryPage extends UIComponent
	{
		public var story_desc_tf:TextField;
		public var btn_decription_sound:Button;
		public var frame_mc:MovieClip;
		
		public var handbook_data:HandbookData;
		
		private static const MIN_HEIGHT:Number = 111;
		private static const MARGIN:Number = 13;
		
		public function HandbookStoryPage()
		{
			// constructor code
		}
		
		override protected function configUI():void
		{
			super.configUI();
			story_desc_tf.text = "";
			btn_decription_sound.addEventListener(MouseEvent.CLICK, onSoundButtonClick, false, 0, true);
		}
		
		private function onSoundButtonClick(evt:MouseEvent):void
		{
			ExternalInterface.call("ASPlayDesciptionSound");
		}
		
		public function updateHandbookData(data:HandbookData)
		{
			handbook_data = data;
			if (handbook_data)
			{
				var info:String = "\t" + handbook_data.handbook_text2;
				story_desc_tf.text = info;
				var bottom:Number = (story_desc_tf.getCharBoundaries(info.length - 1)).bottom;
				story_desc_tf.height = bottom + MARGIN;
				btn_decription_sound.y = story_desc_tf.y + bottom;
				_height = frame_mc.height =  Math.max(MIN_HEIGHT, btn_decription_sound.y + btn_decription_sound.height + MARGIN);
				btn_decription_sound.visible = handbook_data.handbook_sound != "";
			}
		}
	}
}
























