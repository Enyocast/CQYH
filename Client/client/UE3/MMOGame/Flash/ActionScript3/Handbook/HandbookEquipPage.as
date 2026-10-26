
package ActionScript3.Handbook
{
	import flash.display.MovieClip;
	import flash.external.ExternalInterface;
	import flash.text.TextField;
	
	import ActionScript3.Achievement.AchievementPanel;
	import ActionScript3.Handbook.Common.Description;
	import ActionScript3.Handbook.EquipPage.SuitProperty_EquipPage;
	
	import scaleform.clik.controls.Button;
	import scaleform.clik.core.UIComponent;
	import scaleform.clik.events.ButtonEvent;
	
	public class HandbookEquipPage extends UIComponent
	{
		public var equip_icon_mc:MovieClip;
		public var equip_part_tf:TextField;
		public var equip_class_tf:TextField;
		public var equip_level_tf:TextField;
		public var equip_rune_title_tf:TextField;
		public var equip_rune_tf:TextField;
		public var equip_prop_tf:TextField;
		public var text_frame_mc:MovieClip;
		public var frame_mc:MovieClip;
		public var suit_prop_mc:SuitProperty_EquipPage;
		
		public var equip_suit_prop_title_tf:TextField;
		public var equip_suit_prop_tf:TextField;
		public var btn_gotoSuitPage:Button;
		
		public var description_mc:Description;
		
		public var handbook_data:HandbookData;
		
		private static const TEXT_HEIGHT_ONE_LINE:Number = 20;
		private static const TEXT_NO_PROPERTY:String = "未知\n";
		
		public function HandbookEquipPage()
		{
			// constructor code
		}
		
		public function LOG(info:String):void
		{
			(parent as HandbookPanel).LOG(info);
		}
		
		override protected function configUI():void
		{
			super.configUI();
			equip_suit_prop_title_tf = suit_prop_mc.equip_suit_prop_title_tf;
			equip_suit_prop_tf 		 = suit_prop_mc.equip_suit_prop_tf;
			btn_gotoSuitPage 		 = suit_prop_mc.btn_gotoSuitPage;
			
			description_mc.setTitle(ConstansDefine.LABLE_EQUIP_DESCRIPTION);
			description_mc.soundAvaliable = false;
			btn_gotoSuitPage.addEventListener(ButtonEvent.CLICK, onGotoSuitPage);
			
			btn_gotoSuitPage.visible = false;
		 	equip_rune_title_tf.visible = false;
		 	equip_rune_tf.visible = false;
		}
		
		private function onGotoSuitPage(evt:ButtonEvent):void
		{
			ExternalInterface.call(ConstansDefine.ASGotoSuitPage);
		}
		
		public function updateHandbookData(data:HandbookData)
		{
			handbook_data = data;
			if (handbook_data)
			{
				var data_list:Array = handbook_data.handbook_data0;
				if (data_list.length > 0)
				{
					var equip_data:Object = data_list[0] as Object;
					equip_icon_mc.SetData(0, equip_data.equip_icon, equip_data.equip_id, "", 0, -1, -1);
					equip_part_tf.htmlText = equip_data.equip_part;
					equip_class_tf.htmlText = equip_data.equip_class;
					equip_level_tf.htmlText = equip_data.equip_level;
					equip_rune_tf.htmlText = equip_data.equip_rune;
					equip_prop_tf.htmlText = equip_data.equip_prop;
					if(equip_prop_tf.text == "")
					{
						equip_prop_tf.htmlText = TEXT_NO_PROPERTY;
					}
					//dynamic height
					equip_prop_tf.height = TEXT_HEIGHT_ONE_LINE * equip_prop_tf.numLines;
					updateSuitPropText(equip_data.equip_suit_prop);
					//sound avaliable
					description_mc.soundAvaliable = Boolean(handbook_data.handbook_sound);
					updateSuitDescriptionText(handbook_data.handbook_text2);
				}
			}
			updateFrameHeight();
		}
		
		private function updateSuitPropText(info:String):void
		{
			var equip_prop_tf_bottom:Number = equip_prop_tf.y + equip_prop_tf.height;
			if(info){
				suit_prop_mc.visible = true;
				equip_suit_prop_tf.htmlText = info;
				equip_suit_prop_tf.height = TEXT_HEIGHT_ONE_LINE * equip_suit_prop_tf.numLines;
				suit_prop_mc.y = equip_prop_tf_bottom;
				text_frame_mc.height = suit_prop_mc.y + suit_prop_mc.height - text_frame_mc.y;
			}else{
				suit_prop_mc.visible = false;
				text_frame_mc.height = equip_prop_tf_bottom - text_frame_mc.y;
			}
		}
		
		private function updateSuitDescriptionText(info:String):void
		{
			if(info){
				description_mc.updateDescription(info);
			}else{
				//LOG("equip_data has not OwnProperty: equip_suit_prop");
			}
		}
		
		public function updateFrameHeight():void
		{
			description_mc.y = text_frame_mc.y + text_frame_mc.height;
			_height = frame_mc.height = description_mc.y + description_mc.height;
		}
	}
}
























