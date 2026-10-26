package UI_AuctionHouse.AS
{
	import scaleform.clik.controls.ListItemTreeRenderer;
	import scaleform.clik.controls.Button;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.text.TextField;
	import flash.external.ExternalInterface;
	import scaleform.gfx.MouseEventEx;
	import ActionScript3.Slot.MySlot;
	import ActionScript3.MoneyInput;
	import ActionScript3.controls.StateUIComponent;
	
	public class AuctionListItem_ItemCategory extends ListItemTreeRenderer 
	{						
		public var list_item_lv1:AuctionListItem_ItemCategory_Lv1;
		//public var list_item_lv2:AuctionListItem_ItemCategory_Lv2;
		public var list_item_lv2:AuctionListItem_ItemCategory_Lv3; // 特殊命名注意
		
		public function AuctionListItem_ItemCategory()
		{
			// constructor code
		}
		
		override protected function configUI():void
		{
			super.configUI();

			setUpdateDataCallBack(updateData);
		}
		
		function onClick(e:Event)
		{
			
		}
		
		function showItem(itemType:int)
		{			
			list_item_lv1.visible = itemType == AuctionItemCategoryData.C_TypeLv1;
			list_item_lv2.visible = itemType == AuctionItemCategoryData.C_TypeLv2;
			//list_item_lv1.selected = this.selected;
			list_item_lv2.selected = this.selected;
			//list_item_lv3.visible = itemType == AuctionItemCategoryData.C_TypeLv3;
			
			/*trace("-------- showItem" + itemType
				   + "," + list_item_lv1.visible
				    + "," + list_item_lv2.visible
					 + "," + list_item_lv3.visible);
			*/

		}
		
		function updateData(dat:Object):void
		{			
			var catDat:AuctionItemCategoryData = dat as AuctionItemCategoryData;			
			if(catDat != null)
			{
				visible = true;
				showItem(catDat.categoryType);
				//list_item_lv1.updateData(catDat);
				//list_item_lv2.updateData(catDat);
				//list_item_lv3.updateData(catDat);
				
				switch(catDat.categoryType)
				{
					case AuctionItemCategoryData.C_TypeLv1:
						list_item_lv1.updateData(catDat);
						break;
						
					case AuctionItemCategoryData.C_TypeLv2:
						list_item_lv2.updateData(catDat);
						break;
						
					//case AuctionItemCategoryData.C_TypeLv3:
					//	list_item_lv3.updateData(catDat);
					//	break;
				}
			}
			else
			{
				list_item_lv1.visible = false;
				list_item_lv2.visible = false;
				visible = false;
			}
		}
	}
	
}
