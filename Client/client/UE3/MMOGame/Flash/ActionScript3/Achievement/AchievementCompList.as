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
	import scaleform.clik.controls.ScrollingList;
	import scaleform.clik.core.UIComponent;
	import scaleform.clik.data.DataProvider;
	import scaleform.clik.data.TreeDataProvider;
	import scaleform.clik.events.ListEvent;
	import scaleform.clik.events.SliderEvent;

	public class AchievementCompList extends MyScrollPanel
	{
		public var frame_mc:MovieClip;
		public var achievement_scrollbar_mc:CustomScrollBar;
		public var achievement_list:Array;
		public var achievement_list_height:int;
		public var achievement_list_y:int;
		
		protected var _availableItems:Vector.<AchievementCompListItem>;

		public function AchievementCompList()
		{
			// constructor code
		}

		override protected function configUI():void
		{
			super.configUI();
			achievement_list = new Array();
			_availableItems = new Vector.<AchievementCompListItem>();
			this.addEventListener(MouseEvent.MOUSE_WHEEL, onWheelScroll);
		}
		
		protected function LOG(info:String):void
		{
			(parent.parent as AchievementListPanel).LOG(info);
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
				achievement_scrollbar_mc.scrollTarget = this;
				addEventListener(SliderEvent.VALUE_CHANGE, onScrollChange);
				achievement_scrollbar_mc.height = scrollbar_height;
				achievement_scrollbar_mc.position = 0;
			}
		}

		function onWheelScroll(e:MouseEvent)
		{
			if (achievement_scrollbar_mc && achievement_scrollbar_mc.enabled)
			{
				achievement_scrollbar_mc.position -= e.delta;
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
		
		public function syncScrollPosition(pecent:Number):void
		{
			if (achievement_scrollbar_mc && achievement_scrollbar_mc.enabled)
			{
				this.y = -1 *  pecent * (this.height - achievement_list_height);
				achievement_scrollbar_mc.position = pecent * 100;
			}
		}
		
		public function updateList(data:Array):void
		{
			validListItemInstance(data.length);
			achievement_list = [];
			
			var item_pos_y:int = achievement_list_y;
			for (var i:int = 0; i < data.length; i ++)
			{
				var list_item:AchievementCompListItem = _availableItems[i];
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
			//	LOG("comparelist updateList:　" +　this.height + " " + frame_mc.height + " " + achievement_list_height);
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
					_availableItems[i] = new AchievementCompListItem();
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
				var list_item:AchievementCompListItem = achievement_list[i] as AchievementCompListItem;
				list_item.updateItemData(data[i]);
			}
		}
		
		public function updateListLayout():void
		{
			var item_pos_y:int = achievement_list_y;
			for (var i:int = 0; i < achievement_list.length; i ++)
			{
				var list_item:AchievementCompListItem = achievement_list[i] as AchievementCompListItem;
				list_item.y = item_pos_y;
				item_pos_y +=  list_item.getItemHeight();
			}

			this.scaleX = 1;
			this.scaleY = 1;
			this.height = item_pos_y - achievement_list_y;
			
			if (achievement_scrollbar_mc)
			{
				//LOG("comparelist updateListLayout:　" +　this.height + " " + frame_mc.height + " " + achievement_list_height);
				if(this.height > achievement_list_height){
					if(achievement_scrollbar_mc.enabled == false){
						achievement_scrollbar_mc.enabled = true;
						achievement_scrollbar_mc.scrollTarget = this;
					}
				}else{
					if(achievement_scrollbar_mc.enabled == true){
						achievement_scrollbar_mc.scrollTarget = null;
						achievement_scrollbar_mc.position = NaN;
						achievement_scrollbar_mc.enabled = false;
					}
				}
			}
		}
	}
}