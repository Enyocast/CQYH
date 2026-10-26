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
	import scaleform.clik.controls.CheckBox;

	public class QuestListItem extends ListItemTreeRenderer
	{
		public var quest_data:QuestData;
		public var quest_list_item_group_mc:QuestListItemGroup;
		public var quest_list_item_title_mc:QuestListItemTitle;

		public function QuestListItem()
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
			quest_data = data as QuestData;
			if (quest_data)
			{
				visible = true;
				this.enabled = true;

				quest_list_item_group_mc.visible = false;
				quest_list_item_title_mc.visible = false;
				
				if (quest_data.quest_item_type == QuestData.quest_item_type_group)
				{
					quest_list_item_group_mc.visible = true;
					quest_list_item_group_mc.updateData(data);
					quest_list_item_group_mc.selected = quest_data.quest_is_expanded;
					quest_list_item_group_mc.updateColor();
				}
				else if (quest_data.quest_item_type == QuestData.quest_item_type_item)
				{
					quest_list_item_title_mc.visible = true;
					quest_list_item_title_mc.updateData(data);
					quest_list_item_title_mc.selected = quest_data.quest_is_select;
					quest_list_item_title_mc.updateColor();
				}
			}
			else
			{
				visible = false;
			}
		}
		
		protected override function handleMouseRollOver(event:MouseEvent):void
		{
			super.handleMouseRollOver(event);
		}

		protected override function handleMouseRollOut(event:MouseEvent):void
		{
			super.handleMouseRollOut(event);
		}

		protected override function handleMousePress(event:MouseEvent):void
		{
			super.handleMousePress(event);
		}

		protected override function handleMouseRelease(event:MouseEvent):void
		{
			if(event.target && event.target is CheckBox){
				//trace("handleMouseRelease2"+quest_list_item_title_mc.quest_trace_check_mc.selected);
				//quest_list_item_title_mc.quest_trace_check_mc.selected=!quest_list_item_title_mc.quest_trace_check_mc.selected;
				quest_list_item_title_mc.quest_data.quest_is_traced=quest_list_item_title_mc.quest_trace_check_mc.selected;
                ExternalInterface.call("ASTraceQuest", quest_list_item_title_mc.quest_data.quest_id, quest_list_item_title_mc.quest_trace_check_mc.selected);
			}
			super.handleMouseRelease(event);
		}

		protected override function handleReleaseOutside(event:MouseEvent):void
		{
			super.handleReleaseOutside(event);
		}

		override public function set selected(value:Boolean):void
		{
			super.selected = value;
			quest_list_item_group_mc.selected = value;
		}
	}
}