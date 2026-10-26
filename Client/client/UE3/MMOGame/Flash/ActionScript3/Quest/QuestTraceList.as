package ActionScript3.Quest
{

	import flash.display.MovieClip;
	import scaleform.clik.core.UIComponent;
	import ActionScript3.MyScrollPanel;
	import ActionScript3.MyScrollBar;
	import scaleform.clik.events.SliderEvent;
	import flash.external.ExternalInterface;
    import flash.events.Event;
    import flash.events.MouseEvent;
	import scaleform.clik.interfaces.IScrollBar;
	import ActionScript3.MyPanel;


	public class QuestTraceList extends UIComponent
	{
		public var _traceScrollbar:MyScrollBar;
		public var quest_trace_list:Array;
		public var quest_trace_list_pos_y:int;
		public var quest_trace_list_view_height:int;		// 列表的试图高度
		public var quest_trace_list_max_height:int;

		override protected function configUI():void
		{
			super.configUI();
			quest_trace_list = new Array;
			quest_trace_list_pos_y = 0;
			quest_trace_list_view_height = 0;
			quest_trace_list_max_height = 300;
			
			this.focusable = false;
		}

		public function setupScrollBar(scrollBar:MyScrollBar)
		{
			_traceScrollbar = scrollBar;
		}
		
		public function updateListItemData(data:Object)
		{
			for (var i:int = 0; i < quest_trace_list.length; ++i)
			{
				var list_item:QuestTraceListItem = quest_trace_list[i];
				if (list_item)
				{
					if (list_item.quest_trace_data)
					{
						var item_data:QuestTraceData = data as QuestTraceData;
						if (list_item.quest_trace_data.quest_id == item_data.quest_id)
						{
							list_item.updateItemData(data);
							break;
						}
					}
				}
			}
			
			updateListLayout();
		}
		
		public function updateListData(data:Array)
		{
			var i:int = 0;
			for (i = 0; i < data.length; ++ i)
			{
				var list_item:QuestTraceListItem;
				if (i < quest_trace_list.length)
				{
					list_item = quest_trace_list[i];
				}
				else
				{
					list_item = new QuestTraceListItem();
					quest_trace_list.push(list_item);
					this.addChild(list_item);
				}
				
				list_item.updateItemData(data[i]);
				quest_trace_list[i].visible = true;
			}
			
			for(i = data.length; i < quest_trace_list.length; ++ i)
			{
				quest_trace_list[i].visible = false;
			}
			
			for (i = 0; i < data.length; ++ i)
			{
				list_item = quest_trace_list[i];
				if (list_item)
				{
					if (data.length > 3)
					{
						list_item.setExpand(false);
					}
					else
					{
						list_item.setExpand(true);
					}
				}
			}
			
			updateListLayout();
		}

		public function updateListLayout()
		{
			var item_pos_y:int = quest_trace_list_pos_y;
			for (var i:int = 0; i < quest_trace_list.length; ++i)
			{
				var list_item:QuestTraceListItem = quest_trace_list[i];
				if (list_item)
				{
					list_item.y = item_pos_y;
					item_pos_y +=  list_item.height;
				}
			}
			
			this.height = item_pos_y;
			if (this.height > quest_trace_list_max_height)
			{
				quest_trace_list_view_height = quest_trace_list_max_height;
			}
			else
			{
				quest_trace_list_view_height = this.height;
			}
			
			var parentPanel:MyPanel = this.parent as MyPanel;
			if (parentPanel)
			{
				var list_mask_mc:MovieClip = parentPanel.getChildByName("quest_trace_list_mask_mc") as MovieClip;
				if (list_mask_mc)
				{
					list_mask_mc.updateScrollBar();
				}
				
				var list_bg_mc:MovieClip = parentPanel.getChildByName("quest_trace_list_bg_mc") as MovieClip;
				if (list_bg_mc)
				{
					list_bg_mc.height = quest_trace_list_view_height;
					_traceScrollbar.height = quest_trace_list_view_height;
				}
			}
		}
		
		public function setExpandButtonAlpha(a:Number)
		{
			for (var i:int = 0; i < quest_trace_list.length; ++i)
			{
				var list_item:QuestTraceListItem = quest_trace_list[i];
				if (list_item)
				{
					list_item.quest_trace_expand_mc.alpha = a;
					list_item.quest_trace_reduce_mc.alpha = a;
				}
			}
		}
	}

}