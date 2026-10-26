package UI_AuctionHouse.AS
{
	import flash.display.MovieClip;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.external.ExternalInterface;
	import flash.text.TextField;
	import flash.text.TextFormat;
	import flash.text.TextFormatAlign;
	
	import ActionScript3.MoneyInput;
	import ActionScript3.Slot.MySlot;
	
	import scaleform.clik.controls.Button;
	import scaleform.clik.controls.ListItemTreeRenderer;
	import scaleform.gfx.MouseEventEx;
	
	public class AuctionListItem_TreeView extends AuctionListItemBase 
	{
		public var item_icon:MySlot;
		public var txt_item_name:TextField;
		
		private const TEXT_HIGHT_CENTER:int = 24;
		private const TEXT_HIGHT_LEFT:int = 15;
		
		//enum
		public static const TEXT_ITEM_NAME:int = 1;
		public static const TEXT_SELL_NAME:int = 2;
		public static const TEXT_ACUTION:int = 3;
		public static const TEXT_FIXED_PRICE:int = 4;
		
		public function AuctionListItem_TreeView()
		{
			// constructor code
		}
		
		override protected function configUI():void
		{
			super.configUI();
			txt_item_name.multiline = true;
			txt_item_name.wordWrap = true;
		}
		
		override function onClick(e:Event)
		{
			
		}
		
		override function updateData(dat:Object):void
		{	
			var itemData:AuctionItemData = dat as AuctionItemData;
			if(itemData != null)
			{
				visible = true;
				item_icon.SetDataObj(itemData.ItemData);
				item_icon.SetSlotType(itemData.ItemData.slotType);
				item_icon.SetSlotIndex(itemData.ItemData.slotIndex);
				
				txt_item_name.htmlText = itemData.ItemName;
				CheckItemName(TEXT_ITEM_NAME);
			}
			else
			{
				visible = false;
			}
		}
		
		public function CheckItemName(flag:int):void
		{
			var txt_text:String = "";
			switch(flag)
			{
			case TEXT_ITEM_NAME:
				txt_text = txt_item_name.text;
				txt_item_name.y = GetTxt_Y(txt_text);
				break;
			}
		}
		
		public function GetTxt_Y(txt_text:String):int
		{
			var text_Y:int = TEXT_HIGHT_CENTER;
			if( txt_text.length > 8)
			{
				text_Y = TEXT_HIGHT_LEFT;
			}
			else
			{
				text_Y = TEXT_HIGHT_CENTER;
			}
			return text_Y;
		}
		
		protected override function handleMouseRollOver(event:MouseEvent):void
		{
			super.handleMouseRollOver(event);
		}
		
		protected override function handleMouseRollOut(event:MouseEvent):void
		{
			super.handleMouseRollOut(event);
		}
		
/*		protected var _itemTextColor:int = 0xE2D1BD;
		
		public override function set selected(value:Boolean):void {
			if(value && !_selected){
				_itemTextColor = txt_item_name.textColor;
				txt_item_name.textColor = 0xffedc5;
			}else if(_selected){
				txt_item_name.textColor = _itemTextColor;
			}
			super.selected = value;
		}*/
	}
	
}
