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

	public class QuestStoryStageListItem extends ListItemTreeRenderer
	{
		public var quest_data:Object;
		public var quest_story_stage_title_tf:TextField;

		public function QuestStoryStageListItem()
		{
		}

		override protected function configUI():void
		{
			super.configUI();

			// 这里一定要注意设置回调处理函数;
			setUpdateDataCallBack(updateData);
		}

		function updateData(data:Object):void
		{
			quest_data = data;
			if (quest_data)
			{
				visible = true;
				this.enabled = true;
				quest_story_stage_title_tf.text = quest_data.quest_stage_name;
			}
			else
			{
				visible = false;
			}
		}

		override public function set selected(value:Boolean):void
		{
			super.selected = value;
		}
	}
}