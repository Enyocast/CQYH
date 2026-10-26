package UI_Journey.AS3
{
	import flash.events.Event;
	import flash.external.ExternalInterface;
	import flash.utils.Dictionary;
	
	import UI_LoginWidget.AS3.AppearanceModule.OperationList;
	
	import scaleform.clik.core.UIComponent;
	import scaleform.clik.events.ButtonEvent;
	
	public class JourneyTraceItem extends UIComponent
	{
		public var journey_trace_item_head_mc:JourneyTraceItemHead;
		public var journey_trace_item_content_mc:JourneyTraceItemContent;
		
		protected var _activated:Boolean;
		protected var _index:int = -1;
		protected var _itemData:JourneyTraceItemData;
		
		protected var _frameDic:Dictionary = new Dictionary(true);
		
		private var _dicRef:Dictionary;
		
		private var _isShowingGuide:Boolean;
		private var _categoryFrame:int  = 0;
		private var _recommandLevel:int = 0;
		
		public function JourneyTraceItem()
		{
			super();
		}
		
		public function get isShowingGuide():Boolean
		{
			return _isShowingGuide;
		}

		public function set isShowingGuide(value:Boolean):void
		{
			_isShowingGuide = value;
		}

		public function setPanelDicReference(dicRef:Dictionary):void
		{
			_dicRef = dicRef;
		}
		
		override protected function configUI():void
		{
			super.configUI();
			configCategoryToMovieFrame();
			journey_trace_item_head_mc.addEventListener(ButtonEvent.CLICK, onHeadClick, false, 0, true);
			journey_trace_item_content_mc.setPanelDicReference(_dicRef);
			
			_categoryFrame = _frameDic[ConstantsDefine.CATEGORY_STORY];
			journey_trace_item_head_mc.category_text_mc.gotoAndStop(_categoryFrame);
		}
		
		private function configCategoryToMovieFrame():void
		{
			_frameDic[ConstantsDefine.CATEGORY_STORY] = 1;
			_frameDic[ConstantsDefine.CATEGORY_MONSTER] = 2;
			_frameDic[ConstantsDefine.CATEGORY_ACHIEVEMENT] = 3;
			_frameDic[ConstantsDefine.CATEGORY_EMERGENCY] = 4;
			_frameDic[ConstantsDefine.CATEGORY_BOSS] = 5;
			_frameDic[ConstantsDefine.CATEGORY_ACTIVITY] = 6;
			_frameDic[ConstantsDefine.CATEGORY_GUIDE] = 7;
			_frameDic[ConstantsDefine.CATEGORY_GUILD] = 8;
		}
		
		public function get index():int
		{
			return _index;
		}
		
		public function set index(value:int):void
		{
			_index = value;
		}
		
		public function get category():int
		{
			if(_itemData)
			{
				return _itemData.category;
			}
			return -1;
		}
		
		protected function onHeadClick():void
		{
			activated = !_activated;
			(parent as JourneyTraceList).updateLayout(_index);
		}
		
		public function set activated(value:Boolean):void
		{
			_activated = value;
			journey_trace_item_head_mc.selected = _activated;
			journey_trace_item_content_mc.visible = _activated;
			resieze();
			
			if (_itemData)
			{
				ExternalInterface.call("ASSetCurItemState", _itemData.itemType, _activated);
			}
		}
		
		public function get activated():Boolean
		{
			return _activated;
		}
		
		private function resieze():void
		{
			if(_activated)
			{
				_height =  (journey_trace_item_content_mc.y + journey_trace_item_content_mc.height - journey_trace_item_head_mc.y);  
			}
			else
			{
				_height = journey_trace_item_head_mc.height; 
			}
			invalidateSize();
		}
		
		public function updateLayout(focusChanged:Boolean = true):void
		{
			resieze();
			if(focusChanged)
			{
				(parent as JourneyTraceList).updateLayout(_index, false);
			}
			else
			{
				(parent as JourneyTraceList).updateLayout(-1, false);
			}
		}
		
		public function updateItemData(data:JourneyTraceItemData):void
		{
			_itemData = data;
			if(_itemData)
			{
				if(_categoryFrame != _frameDic[_itemData.category])
				{
					_categoryFrame = _frameDic[_itemData.category];
					journey_trace_item_head_mc.category_text_mc.gotoAndStop(_categoryFrame);
				}
				if(_itemData.isComplete)
				{
					journey_trace_item_head_mc.quest_complete_txt.visible = true;
					journey_trace_item_head_mc.recommand_level_stars_mc.visible = false;
				}
				else
				{
					journey_trace_item_head_mc.quest_complete_txt.visible = false;
					journey_trace_item_head_mc.recommand_level_stars_mc.visible = true;
					if(_recommandLevel != _itemData.recommandLevel)
					{
						_recommandLevel =  _itemData.recommandLevel;
						journey_trace_item_head_mc.recommand_level_stars_mc.gotoAndStop(_recommandLevel + 1);//star number:0-5
					}
				}
				journey_trace_item_content_mc.updateHintText(_itemData.hintText);
				journey_trace_item_content_mc.updateItemData(_itemData.questTraceData, _itemData.category);
				activated = _itemData.isExpand;
			}
		}
	}
}