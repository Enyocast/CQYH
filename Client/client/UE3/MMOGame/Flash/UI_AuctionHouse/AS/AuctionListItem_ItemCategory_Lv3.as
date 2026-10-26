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
	
	public class AuctionListItem_ItemCategory_Lv3 extends StateUIComponent
	{				
		public var txt_caption:TextField;
		var _dat:AuctionItemCategoryData;
		
		public function AuctionListItem_ItemCategory_Lv3()
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
			//visible = dat.visible;
			_dat = dat;
			txt_caption.text = dat.label;
		}
	}
	
}
