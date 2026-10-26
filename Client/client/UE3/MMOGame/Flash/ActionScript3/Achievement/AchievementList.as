//
// 成就系统个人成就列表
//
package ActionScript3.Achievement
{
	import flash.display.MovieClip;
	import flash.events.Event;
	import flash.events.KeyboardEvent;
	import flash.events.MouseEvent;
	import flash.external.ExternalInterface;
	import flash.text.TextField;
	
	import ActionScript3.MyPanel;
	import ActionScript3.MyScrollBar;
	import ActionScript3.MyScrollPanel;
	import ActionScript3.MyTipButton;
	import ActionScript3.Common.CustomScrollBar;
	
	import scaleform.clik.controls.Button;
	import scaleform.clik.controls.ListItemRenderer;
	import scaleform.clik.controls.ScrollingList;
	import scaleform.clik.core.UIComponent;
	import scaleform.clik.data.DataProvider;
	import scaleform.clik.data.TreeDataProvider;
	import scaleform.clik.events.ListEvent;
	import scaleform.clik.events.SliderEvent;

	public class AchievementList extends MyScrollPanel
	{
		private static const LIST_BOTTOM_POS_Y:int = 423;
		
		public var frame_mc:MovieClip;
		public var achievement_scrollbar_mc:CustomScrollBar;
		public var achievement_list:Array;
		public var achievement_list_height:int;
		public var achievement_list_y:int;
		
		protected var _scrollBarDisabled:Boolean = false;
		protected var _availableItems:Vector.<AchievementListItem>;

		public function AchievementList()
		{
			// constructor code
		}
		
		protected function LOG(info:String):void
		{
			(parent as AchievementListPanel).LOG(info);
		}

		override protected function configUI():void
		{
			super.configUI();
			achievement_list = new Array();
			_availableItems = new Vector.<AchievementListItem>();
			this.addEventListener(MouseEvent.MOUSE_WHEEL, onWheelScroll);
		}

		public function setListPos(pos_y:int)
		{
			achievement_list_y = pos_y;
		}
		
		public function setListHeight(list_height:int)
		{
			achievement_list_height = list_height;
			if (achievement_scrollbar_mc){
				achievement_scrollbar_mc.height = list_height;
			}
		}

		public function setScrollBar(scrollbar:CustomScrollBar, scrollbar_height:int)
		{
			achievement_scrollbar_mc = scrollbar;
			if (achievement_scrollbar_mc)
			{
				//need confirm
				if(achievement_scrollbar_mc.enabled){
					achievement_scrollbar_mc.scrollTarget = this;
					addEventListener(SliderEvent.VALUE_CHANGE, onScrollChange);
					achievement_scrollbar_mc.height = scrollbar_height;
					achievement_scrollbar_mc.position = 0;
				}
			}
		}

		function onWheelScroll(e:MouseEvent)
		{
			if (achievement_scrollbar_mc && achievement_scrollbar_mc.enabled)
			{
				achievement_scrollbar_mc.position -= e.delta;
			}
		}
		
		public function syncScrollPosition(pecent:Number):void
		{
			if (achievement_scrollbar_mc && achievement_scrollbar_mc.enabled)
			{
				this.y = -1 *  pecent * (this.height - achievement_list_height);
				achievement_scrollbar_mc.position = pecent * 100;
			}
		}
		
		function onScrollChange(evt:SliderEvent)
		{
			if (achievement_scrollbar_mc && achievement_scrollbar_mc.enabled)
			{
				var percent:Number = evt.value / 100;
			
				if(percent == 0.01)
				{
					percent = 0;
				}
				else if(percent == 1)
				{
					percent = 1.001;
				}
			
				this.y = -percent * (this.height - achievement_list_height);
			}
		}

		public function updateList(data:Array):void
		{
			if(data == null)
			{
				return;
			}
			validListItemInstance(data.length);
			achievement_list = [];

			var item_pos_y:int = achievement_list_y;
			for (var i:int = 0; i < data.length; i ++)
			{
				var list_item:AchievementListItem = _availableItems[i];
				if(list_item.achievement_item_expand)
				{
					list_item.switchItemExpandState();
				}
				list_item.updateItemData(data[i]);
				achievement_list.push(list_item);
				list_item.y = item_pos_y;
				item_pos_y +=  list_item.getItemHeight();
			}
			
			this.scaleX = 1;
			this.scaleY = 1;
			frame_mc.height = this.height = item_pos_y - achievement_list_y;
			this.y = 0;
			if (achievement_scrollbar_mc)
			{

				if(this.height > achievement_list_height){
					if(achievement_scrollbar_mc.enabled == false){
						achievement_scrollbar_mc.enabled = true;
						achievement_scrollbar_mc.scrollTarget = this;
					}
					achievement_scrollbar_mc.position = 0;
				}else{
					if(achievement_scrollbar_mc.enabled == true){
						achievement_scrollbar_mc.scrollTarget = null;
						achievement_scrollbar_mc.position = NaN;
						achievement_scrollbar_mc.enabled = false;
					}
				}
			//	trace("AchievementList::updateList: " +　this.height + " " + frame_mc.height + " " + achievement_list_height);
			}
		}
		
		private function validListItemInstance(data_len:int):void
		{
			var items_num:int = _availableItems.length;
			if(items_num < data_len)
			{
				_availableItems.length = items_num;
				for(var i:int = items_num; i < data_len; i++)
				{
					_availableItems[i] = new AchievementListItem();
					_availableItems[i].validateNow();
					addChild(_availableItems[i]);
					_availableItems[i].achievement_item_parent = this;
				}
			}
			else if(items_num > data_len)
			{
				for(i = data_len; i < items_num; i++)
				{
					_availableItems[i].visible = false;
					_availableItems[i].y = achievement_list_y;
				}
			}
		}
		
		public function updateListData(data:Array):void
		{
			for (var i:int = 0; i < achievement_list.length; i ++)
			{
				var list_item:AchievementListItem = achievement_list[i] as AchievementListItem;
				list_item.updateItemData(data[i]);
			}
		}
		
		public function updateListLayout(id:int = -1, resetPostion:Boolean = false):void
		{
			var item_pos_y:int = achievement_list_y;
			var focusItem:AchievementListItem;
			var lastItem:AchievementListItem;
			
			for (var i:int = 0; i < achievement_list.length; i ++)
			{
				var list_item:AchievementListItem = achievement_list[i] as AchievementListItem;
				if(list_item.achievement_item_data.achievement_id == id)
				{
					focusItem = list_item;
				}
				if(i == achievement_list.length -1)
				{
					lastItem = list_item;
				}
				list_item.y = item_pos_y;
				item_pos_y +=  list_item.getItemHeight();
			}

			this.scaleX = 1;
			this.scaleY = 1;
			frame_mc.height = this.height = item_pos_y - achievement_list_y;
			if (achievement_scrollbar_mc)
			{
				if(this.height > achievement_list_height)
				{
					if(achievement_scrollbar_mc.enabled == false)
					{
						achievement_scrollbar_mc.enabled = true;
						achievement_scrollbar_mc.scrollTarget = this;
					}
				}
				else
				{
					achievement_scrollbar_mc.scrollTarget = null;
					achievement_scrollbar_mc.position = NaN;
					achievement_scrollbar_mc.enabled = false;
					
					if(this.y < 0)
					{
						this.y = 0;
					}
				}
			}
			var offset:Number;
			var pecent:Number = 0;
			if(resetPostion)
			{
				offset = 0;
				if(this.height > achievement_list_height)
				{
					if(focusItem != null)
					{
						offset = -1 * Math.min(this.height - achievement_list_height, focusItem.y - achievement_list_y);
					}
				}
			}
			else
			{
				offset = this.y;
				if(focusItem != null)
				{
					if(this.y + focusItem.y + focusItem.getItemHeight() > LIST_BOTTOM_POS_Y)
					{
						offset = LIST_BOTTOM_POS_Y - (focusItem.y + focusItem.getItemHeight());
					}
				}
				if(lastItem != null)
				{
					if((this.y + lastItem.y + lastItem.getItemHeight() < LIST_BOTTOM_POS_Y) && (this.height > LIST_BOTTOM_POS_Y))
					{
						offset = LIST_BOTTOM_POS_Y - (lastItem.y + lastItem.getItemHeight());
					}
				}
			}
			pecent = -1 * offset / (this.height - achievement_list_height);
			if(achievement_scrollbar_mc && achievement_scrollbar_mc.enabled)
			{
				achievement_scrollbar_mc.position = pecent * 100;
			}
			this.y = offset;
		}
		
		public function scrollList(id:int):void
		{
			for (var i:int = 0; i < achievement_list.length; i ++)
			{
				var list_item:AchievementListItem = achievement_list[i] as AchievementListItem;
				if (list_item)
				{
					if (list_item.achievement_item_data.achievement_id == id)
					{
						if(list_item.canExpand && !list_item.achievement_item_expand)
						{
							list_item.switchItemExpandState();
						}
						list_item.updateListLayout(true);
						break;
					}
				}
			}
		}
	}
}