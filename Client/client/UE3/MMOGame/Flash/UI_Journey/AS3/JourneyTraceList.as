package UI_Journey.AS3
{
	import flash.display.MovieClip;
	import flash.utils.Dictionary;
	
	import UI_LoginWidget.AS3.AppearanceModule.GroupData_Appearance;
	import UI_LoginWidget.AS3.AppearanceModule.OperationPanel;
	
	import scaleform.clik.core.UIComponent;
	
	public class JourneyTraceList extends UIComponent
	{
		public var frame_mc:MovieClip;
		public var achievement_reward_mc:JourneyTraceAchievementReward;
		
		private var _itemGroup:Vector.<JourneyTraceItem>;
		private var _numOfGroup:int;
		
		private var _dicRef:Dictionary;
		
		private var _guide_mc_dic:Dictionary;
		
		//reference
		private var _guide_layer_mc:MovieClip;
		
		public function JourneyTraceList()
		{
			super();
		}
		
		override protected function configUI():void
		{
			super.configUI();
			_guide_mc_dic = new Dictionary(true);
			achievement_reward_mc.visible = false;
		}
		
		public function setPanelDicReference(dicRef:Dictionary):void
		{
			_dicRef = dicRef;
		}
		
		public function setGuideLayerReference(layerRef:MovieClip):void
		{
			_guide_layer_mc = layerRef;
		}
		
		internal function UCShowGuideArrow(bShow:Boolean, itemCategory:int, guideMCName:String):void
		{
			if(_guide_layer_mc == null)
			{
				return;
			}
			var guideMC:MovieClip = _guide_layer_mc.getChildByName(guideMCName) as MovieClip;
			if(guideMC == null)
			{
				return;
			}
			guideMC.visible = bShow;
			
			if(_numOfGroup > _itemGroup.length)
			{
				return;
			}
			var targetItem:JourneyTraceItem;
			for(var i:int = 0; i < _numOfGroup; i++)
			{
				if(itemCategory == _itemGroup[i].category)
				{
					targetItem = _itemGroup[i];
					break;
				}
			}
			if(targetItem)
			{
				if(bShow)
				{
					guideMC.x = 0;
					guideMC.y = targetItem.y - 9;
					_guide_mc_dic[targetItem] = guideMC;
				}
				targetItem.isShowingGuide = bShow;
			}
			
			if (!bShow)
			{
				_guide_layer_mc.removeChild(guideMC);
				_guide_mc_dic[targetItem] = null;
				delete _guide_mc_dic[targetItem];
			}
		}
		
		internal function updateLayout(foucusIndex:int = 0, toTop:Boolean = true):void
		{
			if(_numOfGroup > _itemGroup.length)
			{
				return;
			}
			var posY:Number = achievement_reward_mc.visible ? achievement_reward_mc.height : 0;
			for(var i:int = 0; i < _numOfGroup; i++)
			{
				if(foucusIndex != -1)
				{
					if(i != foucusIndex)
					{
						_itemGroup[i].activated = false;
					}
				}
				_itemGroup[i].y = posY;
				if(_itemGroup[i].isShowingGuide)
				{
					var guideMC:MovieClip = _guide_mc_dic[_itemGroup[i]];
					if(guideMC)
					{
						guideMC.y = posY - 9;
					}
				}
				posY += _itemGroup[i].height;
			}
			frame_mc.height 	=  height = posY;
			(parent as JourneyTracePanel).updateScrollingView(toTop);
			(parent as JourneyTracePanel).checkGuidePosition();
			
			// 为引导临时写的，以后重做
			for(i = 0; i < _numOfGroup; i++)
			{
				if(_itemGroup[i].isShowingGuide)
				{
					guideMC = _guide_mc_dic[_itemGroup[i]];
					guideMC.visible = _itemGroup[i].activated;
				}
			}
		}
		
		internal function updateAchievementAwardData(data:Object):void
		{
			if(data == null)
			{
				achievement_reward_mc.visible = false;
			}
			else
			{
				achievement_reward_mc.visible = true;
				achievement_reward_mc.updateAchievementRewardData(data);
			}
		}
		
		internal function updateListData($data:Array):void
		{
			if($data == null){
				validItemGroupInstance(0);
				(parent as JourneyTracePanel).updateScrollingView(true, false);
				return;
			}
			var posY:Number = achievement_reward_mc.visible ? achievement_reward_mc.height : 0;
			var dataLen:int = _numOfGroup = $data.length;
			validItemGroupInstance(dataLen);
			var itemData:JourneyTraceItemData;
			for(var i:int = 0; i < dataLen; i++)
			{
				itemData = $data[i] as JourneyTraceItemData;
				_itemGroup[i].updateItemData(itemData);
				_itemGroup[i].visible = true;
				_itemGroup[i].y = posY;
				_itemGroup[i].index = i;
				posY += _itemGroup[i].height;
			}
			frame_mc.height =  height = posY;
			(parent as JourneyTracePanel).updateScrollingView(true, true);
		}
		
		private function validItemGroupInstance(dataLen:int):void
		{
			if(_itemGroup == null){
				_itemGroup = new Vector.<JourneyTraceItem>();
			}
			var numOfGroup:int = _itemGroup.length;
			if(numOfGroup < dataLen){
				_itemGroup.length = numOfGroup;
				for(var i:int = numOfGroup; i < dataLen; i++)
				{
					_itemGroup[i] = new JourneyTraceItem();
					_itemGroup[i].setPanelDicReference(_dicRef);
					_itemGroup[i].validateNow();//configUI
					addChild(_itemGroup[i]);
				}
			}else if(numOfGroup > dataLen){
				for(i = dataLen; i < numOfGroup; i++)
				{
					_itemGroup[i].visible = false;
				}
			}
		}
	}
}