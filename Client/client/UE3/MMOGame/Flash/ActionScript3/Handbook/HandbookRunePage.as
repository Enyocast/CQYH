package ActionScript3.Handbook
{
	import flash.display.MovieClip;
	import flash.events.Event;
	import flash.text.TextField;
	import flash.events.MouseEvent;
	import flash.external.ExternalInterface;
	
	import ActionScript3.Handbook.Common.Description;
	
	import scaleform.clik.controls.DropdownMenu;
	import scaleform.clik.core.UIComponent;
	import scaleform.clik.data.DataProvider;
	
	public class HandbookRunePage extends UIComponent
	{
		public var frame_mc:MovieClip;
		public var text_frame_mc:MovieClip;
		public var rune_icon_mc:HandbookSkillIcon;
		public var rune_level_tf:TextField;
		public var rune_effect_tf:TextField;
		public var description_mc:Description;
		
		public var handbook_data:HandbookData;
		
		public function HandbookRunePage()
		{
			super();
		}
		
		override protected function configUI():void
		{
			super.configUI();
			description_mc.setTitle(ConstansDefine.LABLE_RUNE_DESCRIPTION);
			description_mc.soundAvaliable = false;
			
			rune_icon_mc.addEventListener("rollOver", handleSkillRollOver);
            rune_icon_mc.addEventListener("rollOut", handleSkillRollOut);
		}
		
		public function updateHandbookData(data:HandbookData)
		{
			handbook_data = data;
			if (handbook_data)
			{
				var rune_data:Object = handbook_data.handbook_data0[0];
				rune_icon_mc.SetData(rune_data.skill_id, rune_data.skill_icon);
				rune_level_tf.htmlText = "洗炼等级：" + handbook_data.handbook_text2;
				rune_effect_tf.htmlText = "技能效果：" + handbook_data.handbook_text0;
				
				rune_effect_tf.height = rune_effect_tf.numLines * ConstansDefine.TEXT_HEIGHT_ONE_LINE + ConstansDefine.MARGIN;
				
				text_frame_mc.height = rune_effect_tf.y + rune_effect_tf.height - text_frame_mc.y;
				
				description_mc.y = text_frame_mc.y + text_frame_mc.height + ConstansDefine.MARGIN;
				
				description_mc.updateDescription(handbook_data.handbook_text1);
			}
		}
		
		public function handleSkillRollOver(e:Event):void
		{
			var item_mc:HandbookSkillIcon = e.currentTarget as HandbookSkillIcon;
			if (item_mc)
			{
				//ExternalInterface.call("ASShowTips_MonsterSkill", item_mc);
			}
		}

		public function handleSkillRollOut(e:Event):void
		{
			//ExternalInterface.call("ASHideTips_MonsterSkill", this);
		}
	}
}