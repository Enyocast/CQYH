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
	import ActionScript3.Common.MoneyInputNew;
	import ActionScript3.Slot.MySlot;
	
	import scaleform.clik.controls.Button;
	import scaleform.clik.controls.ListItemTreeRenderer;
	import scaleform.gfx.MouseEventEx;
	
	public class AuctionListItem_View extends AuctionListItemBase 
	{
		private static const NUMBER_OF_TEXTFIELD_CHECK_LINE:int = 1;
		
		public var item_icon:MySlot;
		public var txt_item_name:TextField;
		public var txt_item_name_center:TextField;
		public var txt_item_lv:TextField;
		public var txt_time_left:TextField;
		public var txt_seller_name:TextField;
		public var icon_fixed_price_mc:MovieClip;
		
		public var price_current:MoneyInputNew;
		public var price_fixed:MoneyInputNew;
		
		public var auction_icon:MovieClip;
	//	public var price_icon:MovieClip;

		private const HOUR:int = 3600;
		private const MINUTE:int = 60;
		private const MINUTE_FLAG:int = 59;
		private const RED:uint = 0xFF0000;
		private const WHITE:uint = 0xFFFFFF;
		
		private const TEXT_HIGHT_LEFT:int = 6.5;
		private const TEXT_HIGHT_CENTER:int = 15.5;
		private const ICON:int = 4;
		private const MONEY_INPUT:int = 2;
		
		//enum
		public static const TEXT_ITEM_NAME:int = 1;
		public static const TEXT_SELL_NAME:int = 2;
		public static const TEXT_ACUTION:int = 3;
		public static const TEXT_FIXED_PRICE:int = 4;
		
		public function AuctionListItem_View()
		{
			// constructor code
		}
		
		override protected function configUI():void
		{
			super.configUI();
			txt_item_name.multiline = true;
			txt_item_name.wordWrap = true;
			txt_seller_name.multiline = true;
			txt_seller_name.wordWrap = true;
			//txt_price_static = new TextField();
			//auction_icon = new MovieClip();
			//price_icon = new MovieClip();
			visible = false;
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
				
				txt_item_lv.text = itemData.ItemLevel + "级";
				FormatTime(itemData.TimeLeft);
				//txt_time_left.text = itemData.TimeLeft.toString();
				
				//trace("-------updateData", itemData.ItemName, itemData.ForceDisplayBuyer);
				
				if(itemData.ForceDisplayBuyer )
				{				
					txt_seller_name.text = itemData.Buyer;
				}
				else
				{
					txt_seller_name.text = itemData.Seller;
				}
				
				if(itemData.CurrentTabPage == 2)
				{
					if(itemData.IsAuction == false)
					{
						txt_seller_name.text = "";
					}
					else
					{
						txt_seller_name.text = itemData.Buyer;
					}
				}
					
				
				
				CheckItemName(TEXT_SELL_NAME);
				
			//	price_fixed.visible = itemData.FixedPrice > 0; // 没有一口价时就不显示
				CheckItemName(TEXT_FIXED_PRICE);
				CheckIcon(itemData.IsAuction,itemData.IsMyAuction);
				
				if(itemData.ShowUnitPrice)
				{
					price_current.setMoney(Math.ceil(itemData.CurrentAuctionPrice / itemData.StackCount));					
					price_fixed.setMoney(Math.ceil(itemData.FixedPrice / itemData.StackCount));
				}
				else
				{
					price_current.setMoney(itemData.CurrentAuctionPrice);
					price_fixed.setMoney(itemData.FixedPrice);
				}
				//ExternalInterface.call("ASTrace", "------updateAuctionItemData Is OK" + itemData.ItemName);
			}
			else
			{
				//ExternalInterface.call("ASTrace", "------updateAuctionItemData Is Null" + itemData.ItemName);
				visible = false;
			}
		}
		
		public function CheckItemName(flag:int):void
		{
			switch(flag)
			{
			case TEXT_ITEM_NAME:
				txt_item_name.y = GetTxt_Y(txt_item_name);
				break;
			case TEXT_SELL_NAME:
				if(icon_fixed_price_mc)//this is AuctionListItem_ViewWide instance
					txt_seller_name.y =  GetTxt_Y(txt_seller_name);
				break;
			case TEXT_FIXED_PRICE:
					CheckFixedPrice();
				break;
			}
		}
		
		//TODO optimize
		public function GetTxt_Y(txt_text:TextField):int
		{
			var text_Y:int = TEXT_HIGHT_CENTER;
			if( txt_text.numLines > NUMBER_OF_TEXTFIELD_CHECK_LINE)
			{
				text_Y = TEXT_HIGHT_LEFT;
			}
			else
			{
				text_Y = TEXT_HIGHT_CENTER;
			}
			return text_Y;
		}
		
		public function CheckFixedPrice():void
		{
			if(price_fixed.visible == false)
			{
				//hard code
				if(icon_fixed_price_mc){
					icon_fixed_price_mc.visible = false;
					price_current.y = auction_icon.y = TEXT_HIGHT_CENTER;
					auction_icon.y -= 2;
				}
				//else condition means this is AuctionListItem_ViewWide instance
			}
			else
			{
				if(icon_fixed_price_mc){
					icon_fixed_price_mc.visible = true;
					auction_icon.y  = ICON;
					price_current.y = MONEY_INPUT;
				}
			}
			
		}
		
		public function CheckIcon(IsAuction:Boolean,IsMyprice:Boolean):void
		{
			
			if(IsAuction == true)
			{
				auction_icon.visible = true;
				if(IsMyprice == true)
				{
					auction_icon.gotoAndStop('bidding');
				}
				else
				{
					auction_icon.gotoAndStop('offer');
				}
			}
			else
			{
				//auction_icon.visible = false;
				auction_icon.gotoAndStop('offer');//default state
			}
		}
		
		public function FormatTime(timeLeft:int):void
		{
			var minutes:int = Math.floor(timeLeft/MINUTE);
			
			if(minutes > MINUTE_FLAG)
			{
				SetHour(timeLeft);
			}
			else if (minutes <= MINUTE_FLAG)
			{
				SetMinute(timeLeft);
			}
			
		}
		
		public function SetHour(timeLeft:int):void
		{
			var hour:int = (timeLeft/HOUR);
			var val:String = hour.toString()+"小时";
			SetTimeLeft(val,WHITE);
		}
		
		public function SetMinute(timeLeft:int):void
		{
			var minute:int = Math.ceil((timeLeft/MINUTE)%MINUTE);
			if(CheckMinute(minute))
			{
				var val:String = minute.toString()+"分钟"
				SetTimeLeft(val,RED);
			}
			else
			{
				SetHour(timeLeft);
			}
			
		}
		
		public function CheckMinute(minute:int):Boolean
		{
			if(minute > MINUTE_FLAG)
			{
				return false;
			}
			return true;
		}
		
		public function SetTimeLeft(val:String,color:uint):void
		{
			txt_time_left.text = val;
			txt_time_left.textColor =  color;
		}
		
		
	}
	
}
