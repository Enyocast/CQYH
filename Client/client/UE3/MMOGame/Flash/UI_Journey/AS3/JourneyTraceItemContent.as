package UI_Journey.AS3
{
	import flash.display.MovieClip;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.events.TextEvent;
	import flash.external.ExternalInterface;
	import flash.text.StyleSheet;
	import flash.text.TextField;
	import flash.text.TextFieldAutoSize;
	import flash.utils.Dictionary;
	
	import ActionScript3.Quest.QuestTraceData;
	import ActionScript3.Quest.QuestTraceListItem;
	
	import UI_LoginWidget.AS3.AppearanceModule.OperationPanel;
	
	import UI_TradeP2P.TradeP2PAS3.HtmlButton;
	
	import scaleform.clik.core.UIComponent;
	import scaleform.gfx.TextEventEx;
	import scaleform.gfx.TextFieldEx;
	
	public class JourneyTraceItemContent extends UIComponent
	{
		private static const HINT_TEXT_MARGIN_WITHOUT_ITEM:Number = 6;
		private static const ITEM_INIT_POS_X:Number = 15;
		
		public var hint_tf:TextField;
		public var frame_mc:MovieClip;
		
		private var _contentTraceItemsGroup:Vector.<JourneyTraceItemContentDetail>;
		private var _numOfGroup:int;
		private var _contentItemData:Array;
		
		private var _dicRef:Dictionary;
		private var _category:int = -1;
		private var _contentTraceItemDic:Dictionary = new Dictionary(true);
		
		public function JourneyTraceItemContent()
		{
			super();
		}
		
		public function setPanelDicReference(dicRef:Dictionary):void
		{
			_dicRef = dicRef;
		}
		
		override protected function configUI():void
		{
			super.configUI();
			
			hint_tf.autoSize = TextFieldAutoSize.LEFT;
			hint_tf.wordWrap = true;
			hint_tf.styleSheet = new StyleSheet  ;
			hint_tf.addEventListener(TextEvent.LINK, onLinkCallBack);
			hint_tf.addEventListener(scaleform.gfx.TextEventEx.LINK_MOUSE_OVER , onLinkOverCallBack);
			hint_tf.addEventListener(scaleform.gfx.TextEventEx.LINK_MOUSE_OUT, onLinkOutCallBack);
			
			addEventListener(MouseEvent.MOUSE_OVER, onMouseOverPanel);
			addEventListener(MouseEvent.MOUSE_OUT, onMouseOutPanel);
		}
		
		protected function onLinkCallBack(e:TextEvent)
		{
			var commandParameter:Array = e.text.split(",");//获取event:后面的内容的数组
			
			ExternalInterface.call( "ASTrace", "ASLinkCallBack:" + commandParameter.toString());
			ExternalInterface.call( "ASLinkCallBack", commandParameter);
		}
		
		
		protected function onLinkOverCallBack(e:TextEventEx)
		{
			var commandParameter:Array = e.text.split(",");//获取event:后面的内容的数组
			
			ExternalInterface.call( "ASTrace", "ASLinkOverCallBack:" + commandParameter.toString());
			ExternalInterface.call( "ASLinkOverCallBack", commandParameter);
			(parent.parent.parent as JourneyTracePanel).onMouseOverPanel(null);
		}
		
		protected function onLinkOutCallBack(e:TextEventEx)
		{
			var commandParameter:Array = e.text.split(",");//获取event:后面的内容的数组
			
			ExternalInterface.call( "ASTrace", "ASLinkOutCallBack:" + commandParameter.toString());
			ExternalInterface.call( "ASLinkOutCallBack", commandParameter);
			(parent.parent.parent as JourneyTracePanel).onMouseOutPanel(null);
		}
		
		public function updateHintText(info:String):void
		{
			hint_tf.htmlText = info;
			hint_tf.height = hint_tf.textHeight;
		}
		
		public function updateLayout(parentFocusChanged:Boolean):void
		{
			var posY:Number = hint_tf.y + hint_tf.height;
			if(_contentItemData == null || _contentItemData.length == 0)
			{
				if(_contentTraceItemsGroup != null)
				{
					for(var i:int = 0; i < _contentTraceItemsGroup.length; i++)
					{
						_contentTraceItemsGroup[i].visible = false;
					}
				}
				frame_mc.height =  height = posY + HINT_TEXT_MARGIN_WITHOUT_ITEM;
				(parent as JourneyTraceItem).updateLayout(parentFocusChanged);
				return;
			}

			for(i = 0; i < _numOfGroup; i++)
			{
				_contentTraceItemsGroup[i].y = posY;
				_contentTraceItemsGroup[i].visible = true;
				posY += _contentTraceItemsGroup[i].height;
			}
			frame_mc.height =  height = posY;
			(parent as JourneyTraceItem).updateLayout(parentFocusChanged);
		}
		
		public function updateItemData(itemData:Array, category:int):void
		{
			_contentItemData = itemData;
			if(_category != category)
			{
				if(_contentTraceItemDic[_category] != null)
				{
					validItemGroupInstance(0);
				}
				_category = category;
				if(_contentTraceItemDic[_category] == null)
				{
					_contentTraceItemDic[_category] = new Vector.<JourneyTraceItemContentDetail>();
				}
			}
			_contentTraceItemsGroup = _contentTraceItemDic[_category];
			var posY:Number = hint_tf.y + hint_tf.height;
			if(itemData == null || itemData.length == 0)
			{
				if(_contentTraceItemsGroup != null)
				{
					for(var i:int = 0; i < _contentTraceItemsGroup.length; i++)
					{
						_contentTraceItemsGroup[i].updateItemData(null);
						_contentTraceItemsGroup[i].visible = false;
					}
				}
				frame_mc.height =  height = posY + HINT_TEXT_MARGIN_WITHOUT_ITEM;
				_numOfGroup = 0;
				return;
			}
			var dataLen:int = _numOfGroup = itemData.length;
			validItemGroupInstance(dataLen);
			var contentItemData:Object;
			for(i = 0; i < dataLen; i++)
			{
				contentItemData = itemData[i];
				if(_contentTraceItemsGroup[i] != null)
				{
					if(contentItemData != null)
					{
						_contentTraceItemsGroup[i].updateItemData(contentItemData);
						//set data id to dictionary
						if(_dicRef != null && contentItemData.quest_id)
						{
							_dicRef[contentItemData.quest_id] = _contentTraceItemsGroup[i];
						}
						_contentTraceItemsGroup[i].x = ITEM_INIT_POS_X;
						_contentTraceItemsGroup[i].y = posY;
						_contentTraceItemsGroup[i].setExpand(i==0, false);
						_contentTraceItemsGroup[i].visible = true;
						posY += _contentTraceItemsGroup[i].height;
					}
					else
					{
						_contentTraceItemsGroup[i].visible = false;
					}
				}
			}
			frame_mc.height =  height = posY;
		}
		
		private function validItemGroupInstance(dataLen:int):void
		{
			if(_contentTraceItemsGroup == null){
				_contentTraceItemsGroup = new Vector.<JourneyTraceItemContentDetail>();
			}
			var numOfItems:int = _contentTraceItemsGroup.length;
			if(numOfItems < dataLen)
			{
			//	_contentTraceItemsGroup.length = numOfItems;
				for(var i:int = numOfItems; i < dataLen; i++)
				{
					if(_category == ConstantsDefine.CATEGORY_STORY || 
						_category == ConstantsDefine.CATEGORY_EMERGENCY||
						_category == ConstantsDefine.CATEGORY_GUILD||
						_category == ConstantsDefine.CATEGORY_ACTIVITY)
					{
						_contentTraceItemsGroup[i] = new JourneyTraceQuestItem();
					}
					else if(_category == ConstantsDefine.CATEGORY_ACHIEVEMENT)
					{
						_contentTraceItemsGroup[i] = new JourneyTraceAchievementItem();
					}
					
					if(_contentTraceItemsGroup[i] != null)
					{
						_contentTraceItemsGroup[i].validateNow();//configUI
						addChild(_contentTraceItemsGroup[i]);
					}
				}
			}
			else if(numOfItems > dataLen)
			{
				for(i = dataLen; i < numOfItems; i++)
				{
					_contentTraceItemsGroup[i].visible = false;
				}
			}
		}
		
		private function onMouseOverPanel(event:MouseEvent):void
		{
			setExpandButtonAlpha(1.0);
		}
		
		private function onMouseOutPanel(event:MouseEvent)
		{
			setExpandButtonAlpha(0.0);
		}
		
		public function setExpandButtonAlpha(a:Number)
		{
			if(_contentTraceItemsGroup == null)
			{
				return;
			}
			if(_category == ConstantsDefine.CATEGORY_STORY || 
				_category == ConstantsDefine.CATEGORY_EMERGENCY||
				_category == ConstantsDefine.CATEGORY_ACTIVITY)
			{
				for (var i:int = 0; i < _contentTraceItemsGroup.length; ++i)
				{
					var list_item:JourneyTraceQuestItem = _contentTraceItemsGroup[i] as JourneyTraceQuestItem;
					if (list_item && list_item.visible)
					{
						list_item.quest_trace_expand_mc.alpha = a;
						list_item.quest_trace_reduce_mc.alpha = a;
					}
				}
			}
		}
	}
}