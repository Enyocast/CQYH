
package ActionScript3.Handbook
{
	import flash.display.MovieClip;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.external.ExternalInterface;
	import flash.text.TextField;
	
	import ActionScript3.Handbook.Common.Description;
	import ActionScript3.Handbook.MonsterPage.Detail_Monster;
	
	import scaleform.clik.controls.Button;
	import scaleform.clik.controls.CheckBox;
	import scaleform.clik.core.UIComponent;
	
	public class HandbookMonsterPage extends UIComponent
	{
		public var monster_avatar_mc:MovieClip;
		//public var monster_level_tf:TextField;
		public var monster_map_tf:TextField;
		public var monster_desc_tf:TextField;
		
		public var monster_skill_title_tf:TextField;
		public var monster_skill_0_mc:HandbookSkillIcon;
		public var monster_skill_1_mc:HandbookSkillIcon;
		public var monster_skill_2_mc:HandbookSkillIcon;
		public var monster_skill_3_mc:HandbookSkillIcon;
		public var monster_skill_4_mc:HandbookSkillIcon;
		public static const monster_skill_max_count = 5;
		
		public var monster_drop_title_tf:TextField;
		
		public var btn_goto_map:Button;
		public var btn_decription_sound:Button;
		public var check_useable_only:CheckBox;
		
		public var handbook_data:HandbookData;
		
		public var avatar_mc:MovieClip;
		public var detail_mc:Detail_Monster;
		public var description_mc:Description;
		
		//add frame_mc for scrolling
		public var frame_mc:MovieClip;
		
		public var btn_rotate_left:Button;
		public var btn_rotate_right:Button;
		
		public function HandbookMonsterPage()
		{
			// constructor code
		}
		
		override protected function configUI():void
		{
			super.configUI();
			
			monster_avatar_mc = avatar_mc['avatar'];
			//monster_level_tf = detail_mc.monster_level_tf;
			monster_map_tf = detail_mc.monster_map_tf;
			btn_goto_map = detail_mc.btn_goto_map;
			monster_skill_title_tf = detail_mc.skill_list_mc.monster_skill_title_tf;
			monster_skill_0_mc = detail_mc.skill_list_mc.monster_skill_0_mc;
			monster_skill_1_mc = detail_mc.skill_list_mc.monster_skill_1_mc;
			monster_skill_2_mc = detail_mc.skill_list_mc.monster_skill_2_mc;
			monster_skill_3_mc = detail_mc.skill_list_mc.monster_skill_3_mc;
			monster_skill_4_mc = detail_mc.skill_list_mc.monster_skill_4_mc;
			monster_drop_title_tf = detail_mc.drop_list_mc.monster_drop_title_tf;
			check_useable_only = detail_mc.drop_list_mc.check_useable_only;
			monster_desc_tf = description_mc.desc_tf;
			btn_decription_sound = description_mc.btn_decription_sound;
			
			//monster_level_tf.text = "";
			monster_map_tf.text = "";
			monster_desc_tf.text = "";
			btn_goto_map.addEventListener(MouseEvent.CLICK, onGotoMapClick, false, 0, true);
			check_useable_only.addEventListener(Event.SELECT, onCheckButtonSelect, false, 0, true);
			
			btn_rotate_left.addEventListener(MouseEvent.MOUSE_DOWN, onRotateToLeft, false, 0, true);
			btn_rotate_left.addEventListener(MouseEvent.MOUSE_UP, onReleaseLeft, false, 0, true);
			btn_rotate_left.addEventListener(MouseEvent.MOUSE_OUT, onReleaseLeft, false, 0, true);
			btn_rotate_right.addEventListener(MouseEvent.MOUSE_DOWN, onRotateToRight, false, 0, true);
			btn_rotate_right.addEventListener(MouseEvent.MOUSE_UP, onReleaseRight, false, 0, true);
			btn_rotate_right.addEventListener(MouseEvent.MOUSE_OUT, onReleaseRight, false, 0, true);
		}
		
		private function onRotateToLeft(evt:MouseEvent):void
		{
			ExternalInterface.call(ConstansDefine.ASNpcRotate, 0);
		}
		
		private function onReleaseLeft(evt:MouseEvent):void
		{
			ExternalInterface.call(ConstansDefine.ASReleaseRotate);
		}
		
		private function onRotateToRight(evt:MouseEvent):void
		{
			ExternalInterface.call(ConstansDefine.ASNpcRotate, 1);
		}
		
		private function onReleaseRight(evt:MouseEvent):void
		{
			ExternalInterface.call(ConstansDefine.ASReleaseRotate);
		}
		
		private function onGotoMapClick(evt:MouseEvent):void
		{
			var mapName:String = monster_map_tf.text;
			ExternalInterface.call(ConstansDefine.ASGotoMapPage, mapName);
		}
		
		private function onCheckButtonSelect(evt:Event):void
		{
			var useableOnly:Boolean = (evt.currentTarget as CheckBox).selected;
			ExternalInterface.call(ConstansDefine.ASCheckUseableOnly, useableOnly);
		}
		
		public function updateHandbookData(data:HandbookData)
		{
			handbook_data = data;
			if (handbook_data)
			{
				//monster_level_tf.text = String(handbook_data.handbook_text0);
				monster_map_tf.text = String(handbook_data.handbook_text1);
				//sound avaliable
				description_mc.soundAvaliable = Boolean(handbook_data.handbook_sound);
				description_mc.updateDescription(handbook_data.handbook_text2);
				var i:int = 0;
				var monster_skill:Array = handbook_data.handbook_data0;
				var len:int = monster_skill.length;
				detail_mc.skill_list_mc.visible = len > 0;
				if(len > 0){
					var skill_mc:HandbookSkillIcon;
					detail_mc.skill_list_mc.visible = true;
					for (i = 0; i < monster_skill_max_count; i ++)
					{
						skill_mc = this["monster_skill_" + i + "_mc"] as HandbookSkillIcon;
						if (i < len){
							skill_mc.SetData(monster_skill[i].skill_id, monster_skill[i].skill_icon);
							skill_mc.visible = true;
						}else{
							skill_mc.visible = false;
						}
					}
				}
				if(handbook_data.handbook_data1 && handbook_data.handbook_data1.length > 0)
				{
					detail_mc.drop_list_mc.visible = true;
					//update drop list data.
					detail_mc.drop_list_mc.dropItemGrid_mc.setData(handbook_data.handbook_data1);
				}else{
					detail_mc.drop_list_mc.visible = false;
				}
				
				// 临时处理, 只有boss显示按钮
				btn_goto_map.visible = false;
				if (handbook_data.handbook_type == 3)
				{
					btn_goto_map.visible = true;
				}
			}
			detail_mc.updateFrameHeight();
			updateFrameHeight();
		}
		
		public function updateFrameHeight():void
		{
		 	description_mc.y = detail_mc.y + detail_mc.frame_mc.height;
			_height = frame_mc.height = description_mc.y + description_mc.height;
		}
	}
}

