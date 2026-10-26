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
	import flash.events.Event;
	import ActionScript3.controls.StateUIComponent;
	import scaleform.clik.controls.CheckBox;

	public class QuestListItemTitle extends StateUIComponent
	{
		public var quest_data:QuestData;
		public var quest_trace_check_mc:CheckBox;
		public var quest_title_tf:TextField;
		public var quest_status_mc:MovieClip;
		public var quest_level_tf:TextField;
		
		public function QuestListItemTitle()
		{
		}

		override protected function configUI():void
		{
			super.configUI();
			//quest_trace_check_mc.addEventListener(MouseEvent.CLICK, onTraceQuest);
		}
		
		public function updateData(data:Object):void
		{
			quest_data = data as QuestData;
			if (quest_data)
			{
				quest_trace_check_mc.visible = quest_data.quest_is_traceable;
				quest_trace_check_mc.selected = quest_data.quest_is_traced;
				quest_title_tf.htmlText = quest_data.quest_caption;
				
				if (quest_data.quest_is_accepted)
				{
					quest_level_tf.visible = false;
					quest_status_mc.visible = true;
					
					if (quest_data.quest_is_available)
					{
						quest_status_mc.gotoAndStop("available");
					}
					else if (quest_data.quest_is_accepted && !quest_data.quest_is_compassable && !quest_data.quest_is_failed)
					{
						quest_status_mc.gotoAndStop("accepted");
					}
						else if (quest_data.quest_is_compassable)
					{
						quest_status_mc.gotoAndStop("compassable");
					}
					else if (quest_data.quest_is_failed)
					{
						quest_status_mc.gotoAndStop("failed");
					}
					else if (quest_data.quest_is_completed)
					{
						quest_status_mc.gotoAndStop("finished");
					}
				}
				else if (quest_data.quest_is_available)
				{
					quest_level_tf.visible = true;
					quest_status_mc.visible = false;
					
					quest_level_tf.htmlText = quest_data.quest_level;
				}
			}
		}
		
		function onTraceQuest(event:MouseEvent):void
		{
			if (quest_data)
			{
				quest_trace_check_mc.selected = !quest_trace_check_mc.selected;
				quest_data.quest_is_traced=quest_trace_check_mc.selected;
				ExternalInterface.call("ASTraceQuest", quest_data.quest_id, quest_trace_check_mc.selected);
			}
		}
		
		public function updateColor():void
		{
			if(this.selected==true)
			{
				quest_title_tf.textColor=0xffffff;
				quest_level_tf.textColor=0xffffff;
			}
			else
			{
				quest_title_tf.textColor=0xbfb19c;
				quest_level_tf.textColor=0xbfb19c;
			}
		}
	}
}