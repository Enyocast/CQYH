
package ActionScript3.Handbook
{
	import flash.display.MovieClip;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.external.ExternalInterface;
	import flash.filters.ColorMatrixFilter;
	import flash.geom.ColorTransform;
	import flash.text.TextField;
	
	import ActionScript3.Handbook.Common.Description;
	import ActionScript3.ItemSlot.MyItemSlot;
	
	import fl.motion.ColorMatrix;
	
	import scaleform.clik.controls.Button;
	import scaleform.clik.core.UIComponent;
	
	public class HandbookNpcPage extends UIComponent
	{
		public var npc_avatar_mc:MovieClip;
		public var npc_job_tf:TextField;
		public var npc_pos_tf:TextField;
		public var npc_desc_tf:TextField;
		
		public var avatar_mc:MovieClip;
		public var description_mc:Description;
		public var btn_decription_sound:Button;
		//add frame_mc for scrolling
		public var frame_mc:MovieClip;
		
		public var handbook_data:HandbookData;
		
		public function HandbookNpcPage()
		{
			// constructor code
		}
		
		override protected function configUI():void
		{
			super.configUI();
			npc_avatar_mc = avatar_mc['avatar'];
			npc_desc_tf = description_mc.desc_tf;
			btn_decription_sound = description_mc.btn_decription_sound;
			
			npc_job_tf.text = "";
		 	npc_pos_tf.text = "";
			npc_desc_tf.text = "";
			//npc_pos_tf.addEventListener(MouseEvent.CLICK, onGotoPositionClick, false, 0, true);
			btn_decription_sound.useHandCursor = true;
		}
		
		private function onGotoPositionClick(evt:MouseEvent):void
		{
			//var position:String = npc_pos_tf.text;
			//ExternalInterface.call(ConstansDefine.ASGotoPosition, position);
		}
		
		public function updateHandbookData(data:HandbookData)
		{
			handbook_data = data;
			if (handbook_data)
			{
				npc_job_tf.text = String(handbook_data.handbook_text0);
				npc_pos_tf.htmlText = String(handbook_data.handbook_text1);
				//sound avaliable
				description_mc.soundAvaliable = Boolean(handbook_data.handbook_sound);
				description_mc.updateDescription(handbook_data.handbook_text2);
			}
			updateFrameHeight();
		}
		
		public function updateFrameHeight():void
		{
			_height = frame_mc.height = description_mc.y + description_mc.height;
		}
	}
}
