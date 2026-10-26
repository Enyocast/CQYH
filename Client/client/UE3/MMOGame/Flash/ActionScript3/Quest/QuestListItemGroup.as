package ActionScript3.Quest
{
	import flash.display.MovieClip;
	import scaleform.clik.core.UIComponent;
	import flash.text.TextField;
	import scaleform.clik.controls.ListItemTreeRenderer;
	import scaleform.clik.controls.Button;
	import flash.events.MouseEvent;
	import flash.external.ExternalInterface;
	import fl.motion.easing.Back;
	import scaleform.clik.core.CLIK;
	import scaleform.gfx.MouseEventEx;
	import scaleform.clik.events.ButtonEvent;
	import flash.events.Event;
	import ActionScript3.controls.StateUIComponent;

	public class QuestListItemGroup extends StateUIComponent
	{
		public var quest_data:QuestData;
		public var quest_group_name_tf:TextField;

		public function QuestListItemGroup()
		{
		}

		override protected function configUI():void
		{
			super.configUI();
		}
		
		public function updateData(data:Object):void
		{
			quest_data = data as QuestData;
			if (quest_data)
			{
				quest_group_name_tf.htmlText = quest_data.quest_caption;
			}
		}
		
		public function updateColor():void
		{
			if(this.selected==true)
			{
				quest_group_name_tf.textColor=0xfff5de;
			}
			else
			{
				quest_group_name_tf.textColor=0xBFDAE8;
			}
		}
	}
}