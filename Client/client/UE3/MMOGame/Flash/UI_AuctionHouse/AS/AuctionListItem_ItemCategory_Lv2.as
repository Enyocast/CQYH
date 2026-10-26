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
	import ActionScript3.TreeListData;
	import ActionScript3.ExpandIcon;
	
	public class AuctionListItem_ItemCategory_Lv2 extends StateUIComponent 
	{				
		public var txt_caption:TextField;
		public var expand_icon:ExpandIcon;
		
		var _dat:AuctionItemCategoryData;
				
		public function AuctionListItem_ItemCategory_Lv2()
		{
			// constructor code
		}
		
		override protected function configUI():void
		{
			super.configUI();
		}
		
		function onClick(e:Event)
		{
			
		}
		
		public function updateData(dat:AuctionItemCategoryData):void
		{			
			_dat = dat;
			//visible = dat.visible;
			expand_icon.isExpanded = dat.isExpanded;
			txt_caption.text = dat.label;
		}
	}
	
}
