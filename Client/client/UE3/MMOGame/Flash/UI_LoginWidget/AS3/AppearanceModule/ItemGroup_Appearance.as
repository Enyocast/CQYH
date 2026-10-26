package UI_LoginWidget.AS3.AppearanceModule
{
	import flash.display.MovieClip;
	import flash.external.ExternalInterface;
	
	import ActionScript3.Common.ItemGrid;
	
	import scaleform.clik.controls.RadioButton;
	import scaleform.clik.core.UIComponent;
	import scaleform.clik.events.ButtonEvent;
	import scaleform.clik.events.ListEvent;
	
	public class ItemGroup_Appearance extends UIComponent
	{
		private static const CATEGORY_HAIR_STYLE:int = 0;
		private static const CATEGORY_FACE_STYLE:int = 1;
		private static const CATEGORY_HAIR_COLOR:int = 2;
		private static const CATEGORY_SKIN_COLOR:int = 3;
		
		private static const MARGIN:Number = 6;
		
		public var item_head_mc:RadioButton;
		public var item_grid_mc:ItemGrid;
		
		protected var _groupData:GroupData_Appearance;
		protected var _type:int;
		
		protected var _activated:Boolean;
		
		protected var _index:int = -1;
		
		public function ItemGroup_Appearance()
		{
			super();
		}
		
		public function get index():int
		{
			return _index;
		}

		public function set index(value:int):void
		{
			_index = value;
		}

		public function set activated(value:Boolean):void
		{
			_activated = value;
			item_head_mc.selected = _activated;
			item_grid_mc.visible = _activated;
			if(_activated){
				item_head_mc.textField.textColor = 0xffeac5;
				_height =  (item_grid_mc.y + item_grid_mc.height - item_head_mc.y) + MARGIN;  
			}else{
				item_head_mc.textField.textColor = 0xa3c0cf;
				_height = item_head_mc.height; 
			}
			invalidateSize();
		}

		override protected function configUI():void
		{
			super.configUI();
			item_head_mc.addEventListener(ButtonEvent.CLICK, onButtonClick, false, 0, true);
			
			item_grid_mc.addEventListener(ListEvent.ITEM_CLICK, onItemClick, false, 0, true);
		}
		
		protected function onButtonClick():void
		{
			activated = !_activated;
			(parent as OperationList).resetPosition(_index);
		}
		
		protected function onItemClick(evt:ListEvent):void
		{
			//trace("onItemClick", evt.itemData, evt.index, item_grid_mc.selectedIndex);
			if(evt.index != item_grid_mc.selectedIndex){
				if(_groupData == null){
					return;
				}
				var type:int = _groupData.type;
				var id:int 	 = (evt.itemData as ItemData_Appearance).id;
				ExternalInterface.call("ASCallUpdateAppearance", type, id);
			}
		}
		
/*		override public function get height():Number 
		{ 
			if(_activated){
				return item_grid_mc.y + item_grid_mc.height;  
			}
			if(item_head_mc){
				return item_head_mc.height; 
			}
			return 0;
		}*/
		
		public function updateData(groupdata:GroupData_Appearance):void
		{
			_groupData = groupdata;
			if(_groupData == null){
				return;
			}
			_type = _groupData.type;
			item_head_mc.label = _groupData.title;
			//
			if(_type == CATEGORY_HAIR_COLOR || _type == CATEGORY_SKIN_COLOR)
			{
				item_grid_mc.gridItemRenderer = "AppearanceSlot_28";
				item_grid_mc.startPosX = 22;
				item_grid_mc.startPosY = MARGIN;
				item_grid_mc.numH = 3;
				item_grid_mc.marginH = 19
				item_grid_mc.marginV = 6;
			}
			else if(_type == CATEGORY_HAIR_STYLE || _type == CATEGORY_FACE_STYLE)
			{
				item_grid_mc.gridItemRenderer = "AppearanceSlot_64";
				item_grid_mc.startPosX = 24;
				item_grid_mc.startPosY = MARGIN;
				item_grid_mc.numH = 2;
				item_grid_mc.marginH = item_grid_mc.marginV = 13;
			}
			
			item_grid_mc.setData(_groupData.itemsData);
			item_grid_mc.selectedIndex = _groupData.selectedIndex;
		}
		
		public function resetData():void
		{
			item_grid_mc.selectedIndex = _groupData.selectedIndex;
		}
		
		public function getRandomResult():Object
		{
			if(_groupData == null || _groupData.itemsData == null){
				return null;
			}
			var randomIndex:int = _groupData.itemsData.length * Math.random();
			var type:int = _groupData.type;
			var id:int 	 = (_groupData.itemsData[randomIndex] as ItemData_Appearance).id;
			item_grid_mc.selectedIndex = randomIndex;
			var result:Object = {};
			result['type'] 	= type;
			result['id'] 	= id;
			return result;
		}
	}
}