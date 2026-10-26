package UI_SkillTree.SkillTreeAS3
{
	import flash.geom.Rectangle;
	
	import scaleform.clik.core.UIComponent;

	public class ActiveSkillListItem extends UIComponent
	{
		private const MAX_ITEM_NUMBER_OF_LINE:int = 3;
		private const SINGLE_ITEM_AREA:Rectangle = new Rectangle(38,0,168, 75);
		public var ListItemTitleMc:ActiveSkillListItemTitle;
		public var ListItemData:ActiveSkillListItemData;
		
		private var _listSingleItems:Vector.<ActiveSkillListSingleItem>;
		
		private var _selectedItemId:int = -1;
		
		override protected function configUI():void
		{
			super.configUI();
			
			this.mouseChildren = true;
		}
		
		internal function updateData(data:ActiveSkillListItemData):void
		{
			ListItemData = data;
			if(ListItemData == null){
				visible = false;
				return;
			}
			visible = true;
			var dataCount:int = ListItemData.DataCnt;
			ListItemTitleMc.UpdateData(ListItemData.TitleType, ListItemData.TitleString, dataCount > MAX_ITEM_NUMBER_OF_LINE);
			validItemsInstance(dataCount);
			var singleItemsDataLen:int = ListItemData.SingleItemsData.length;
			for(var i:int = 0; i < dataCount; i++)
			{
				_listSingleItems[i].visible = true;
				_listSingleItems[i].x = SINGLE_ITEM_AREA.x + SINGLE_ITEM_AREA.width * int(i % MAX_ITEM_NUMBER_OF_LINE);
				_listSingleItems[i].y = SINGLE_ITEM_AREA.y + SINGLE_ITEM_AREA.height * int(i / MAX_ITEM_NUMBER_OF_LINE);
				if(i < singleItemsDataLen ){
					_listSingleItems[i].UpdateData(ListItemData.SingleItemsData[i]);
				}
			}
		}
		
		override public function get height():Number 
		{ 
			if(ListItemData && ListItemData.DataCnt > 0){
				return SINGLE_ITEM_AREA.height * Math.ceil(ListItemData.DataCnt / MAX_ITEM_NUMBER_OF_LINE); 
			}
			return super.height; 
		}
		
		public function get skillGroupType():int
		{
			if(ListItemData){
				return ListItemData.TitleType;
			}
			return -1;
		}
		
		private function validItemsInstance(dataCount:int):void
		{
			if(_listSingleItems == null){
				_listSingleItems = new Vector.<ActiveSkillListSingleItem>();
			}
			var numOfItems:int = _listSingleItems.length;
			if(numOfItems < dataCount){
				_listSingleItems.length = dataCount;
				for(var i:int = numOfItems; i < dataCount; i++)
				{
					_listSingleItems[i] = new ActiveSkillListSingleItem();
					_listSingleItems[i].itemid = i;
					this.addChild(_listSingleItems[i]);
				}
			}else if(numOfItems > dataCount){
				for(i = dataCount; i < numOfItems; i++)
				{
					_listSingleItems[i].visible = false;
				}
			}
		}
		
		public function setSelectedItemId(itemId:int):void
		{
			if(_selectedItemId != itemId){
				unSelectItem(_selectedItemId);
				_selectedItemId = itemId;
			}
		}
		
		private function unSelectItem(itemIndex:int):void
		{
			if(itemIndex>=0 && itemIndex <　_listSingleItems.length){
				_listSingleItems[itemIndex].selected = false;
			}
		}
	}
}