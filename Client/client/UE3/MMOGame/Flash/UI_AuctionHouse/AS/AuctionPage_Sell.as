package UI_AuctionHouse.AS 
{
	import flash.external.ExternalInterface;
	import ActionScript3.MyPanel;
	import flash.display.MovieClip;
	import scaleform.clik.controls.TextInput;
	import scaleform.clik.controls.DropdownMenu;
	import scaleform.clik.controls.Button;
	import scaleform.clik.controls.ScrollingList;
	import flash.events.MouseEvent;
	import scaleform.clik.events.ListEvent;
	import scaleform.clik.core.UIComponent;
	import flash.events.Event;
	import scaleform.clik.data.DataProvider;
	import scaleform.clik.interfaces.IDataProvider;
	import scaleform.clik.data.TreeDataProvider;
	import ActionScript3.TreeListData;
	import flash.text.TextField;
	import scaleform.clik.controls.RadioButton;
	import scaleform.clik.controls.CheckBox;
	import ActionScript3.Slot.MySlot;
	import ActionScript3.Slot.ItemSlotData;
	import ActionScript3.controls.ListItemHeader;
	import ActionScript3.Common.MoneyInputNew;
	import ActionScript3.Common.Events.ParamEvent;
	
	
	public class AuctionPage_Sell extends UIComponent 
	{						
		public var item_slot_icon:MySlot;
		public var txt_item_name:TextField;
		
		public var txt_auction_time:TextField;
		
		public var auction_total_price:MoneyInputNew;
		public var auction_unit_price:MoneyInputNew;
		public var auction_total_fixed_price:MoneyInputNew;
		public var auction_manage_price:MoneyInputNew;
		
		public var current_money:MoneyInputNew;
		
		
		public var txt_manage_info:TextField;
		public var txt_tax_info:TextField;
		
		public var txt_hint:TextField;//text:取消寄售后， 物品将以邮件的形式退还。
		
		public var sell_list:ScrollingList;
		
		
		public var btn_sell:Button;
		public var btn_reset:Button;
		
		
/*		public var hdr_item_name:Button;
		public var hdr_item_lv:Button;
		public var hdr_time_left:Button;
		public var hdr_seller_name:Button;
		public var hdr_price_current:Button;
		public var hdr_price_fixed:Button;*/
		
		public var chk_show_unit_price:CheckBox;
		public var btn_cancel_sell:Button;
		public var tabTitle:MovieClip;
		var _auctionListContrl:AuctionListItem_Control;
		
		//var _containerId:int = -1;
		//var _slotId:int = -1;
		
		var _slotType:int = -1;
		
		var _lastActionTotalPrice:int = 0;
		var _lastTotalFixedPrice:int = 0;
		var _lastSellInfoData:SellInfoData = null;
		
		var MAX_MONEY:uint = 1000000000;
		
		public var sort_sell:Auction_Sort;
		public var btn_sort_sell:Button;
		
		public const AUCTION:int = 4;
		public const FIXED:int = 5;
		
		public function AuctionPage_Sell() 
		{
			// constructor code
		}
		
		override protected function configUI():void
		{
			super.configUI();
			this.tabTitle.tf_name.text="竞标者";
			chk_show_unit_price.addEventListener(MouseEvent.CLICK, onShowUnitPriceClick);
			btn_cancel_sell.addEventListener(MouseEvent.CLICK, onCancelSellClick);
			
			btn_sell.addEventListener(MouseEvent.CLICK, onSellClick);
			btn_reset.addEventListener(MouseEvent.CLICK, onResetClick);
			auction_total_price.addEventListener(ParamEvent.INPUT_CHANGE, onTotalInputChange);
			auction_total_fixed_price.addEventListener(ParamEvent.INPUT_CHANGE, onFixedInputChange);
			//tabTitle.hdr_price_current.addEventListener(MouseEvent.CLICK,onPrice_Current);
			resetSellInfoData();
			
			var headerArr:Array = new Array();
			//headerArr.push(tabTitle.hdr_item_name);
			//headerArr.push(tabTitle.hdr_item_lv);
			//headerArr.push(tabTitle.hdr_time_left);
			//headerArr.push(tabTitle.hdr_seller_name);
			//headerArr.push(hdr_price_current);
			//headerArr.push(hdr_price_fixed);
			headerArr.push(sort_sell.rdo_sortAuction);
			headerArr.push(sort_sell.rdo_sortFixed);
			
			_auctionListContrl = new AuctionListItem_Control(sell_list, headerArr, onSellListItemClick, null, true,tabTitle.hdr_price_current,sort_sell);
			
			sort_sell.rdo_sortAuction.itemid = AUCTION;
			sort_sell.rdo_sortFixed.itemid = FIXED;
			
			//sort_sell.setButton(btn_sort_sell);
			updateUI(-1);
			
			sort_sell.resetSort();
			
		}
		
		function onTotalInputChange(evt:ParamEvent):void
		{
			var money:int=evt.param as int;
			
			if(money < this._lastSellInfoData.DefaultPrice)
			{
				this.auction_total_price.setMoney(_lastSellInfoData.DefaultPrice);
				return;
			}
			
			auction_unit_price.setMoney(money / _lastSellInfoData.ItemData.quantity);
			
			if(auction_unit_price.getMoney() >= MAX_MONEY)
			{
				auction_unit_price.setMoney(MAX_MONEY);
			}

			if(money >= MAX_MONEY)
			{
				//btn_sell.enabled = false;
				auction_total_price.setMoney(MAX_MONEY);
				
			}
			else
			{
				if(money > auction_total_fixed_price.getMoney() && auction_total_fixed_price.getMoney() > 0)
				{
					btn_sell.enabled = false;
				}
				else
				{
					btn_sell.enabled = true;
				}
			}

		}
		function onFixedInputChange(evt:ParamEvent):void
		{
			var money:int=evt.param as int;
			if (money<= 0)
			{
				btn_sell.enabled = true;
				return;
			}
			if(money >= MAX_MONEY)
			{
				//btn_sell.enabled = false;
				auction_total_fixed_price.setMoney(MAX_MONEY);
				
			}
			if(money < auction_total_price.getMoney())
			{
				btn_sell.enabled = false;
			}
			else
			{
				btn_sell.enabled = true;
			}
			
		}

		public function UCSetSellingItemList(dat:Array):void
		{
			ExternalInterface.call("ASTrace", "------------------------------------UCSetSellingItemList:" + dat.length);
			_auctionListContrl.updateAuctionItemListData(dat);
			updateUI(-1);
		}
		
		public function setSellingItemInfo(dat:SellInfoData):void
		{			
			_lastSellInfoData = dat;
			
			var itemDat:ItemSlotData = dat.ItemData;
			if(itemDat == null)
			{				
				itemDat = new ItemSlotData();
				itemDat.slotID = 0;
				itemDat.slotType = this._slotType;
				
				// 注意更新这个
				_lastSellInfoData.ItemData = itemDat;
			}
												
			item_slot_icon.SetDataObj(itemDat);
			
			//ExternalInterface.call( "ASTrace", "setSellingItemInfo "  + itemDat.containerID.toString()
			//					   + " " + itemDat.slotID.toString() + " " + itemDat.slotType.toString());								   

			//ExternalInterface.call( "ASTrace", "setSellingItemInfo1 "  + item_slot_icon.SlotType.toString());
								   
			item_slot_icon.SetSlotType(_slotType);
			item_slot_icon.SetSlotIndex(0);
			
			//ExternalInterface.call( "ASTrace", "setSellingItemInfo2 "  + item_slot_icon.SlotType.toString());
			
			txt_item_name.htmlText = dat.ItemName;
			
		//	txt_auction_time.text = dat.AuctionTime.toString();			
			auction_total_price.setMoney(dat.ActionTotalPrice);
			auction_unit_price.setMoney(dat.ActionUnitPrice);
			auction_total_fixed_price.setMoney(dat.TotalFixedPrice);
			auction_manage_price.setMoney(dat.ManagePrice);
			
			//txt_manage_info.text = dat.ManageInfo;
			//txt_tax_info.text = dat.TaxInfo;
			_lastActionTotalPrice = dat.ActionTotalPrice;
			_lastTotalFixedPrice = dat.TotalFixedPrice;
			btn_sell.enabled = true;
		}
		
		public function UCSetSellInfo(dat:SellInfoData):void
		{			
			setSellingItemInfo(dat);
			
			ExternalInterface.call( "ASTrace", "UCSetSellInfo "  + dat.ItemData.containerID.toString() + " " + dat.ItemData.slotID.toString());
	
			
			//_containerId = dat.ContainerID;
			//_slotId = dat.SlotID;
			
			chk_show_unit_price.selected = dat.ShowUnitPrice;						
			//current_money.setMoney(dat.CurrentPlayerMoney);
		}
		
		function onShowUnitPriceClick():void
		{
			_auctionListContrl.toggleUnitPriceShow(chk_show_unit_price.selected);
		}
		
		function onCancelSellClick():void
		{
			var obj:AuctionItemData = this._auctionListContrl.getSelectedData();
			if(obj != null)
			{
				ExternalInterface.call( "ASSellPage_CancelSellClick", obj.AuctionID);
			}
		}
		
		public function updateUI(selIdx:int)
		{			
			btn_cancel_sell.enabled = selIdx != -1;
		}
		
		public function onSellListItemClick(event:ListEvent):void
		{
			updateUI(event.index);
		}
		
		public function onSellClick():void
		{
			var dat:SellActionData = new SellActionData();
			
			dat.ContainerID = item_slot_icon.containerID;
			dat.SlotID = item_slot_icon.slotID;
			
			//dat.ContainerID = this._containerId;
			//dat.SlotID = this._slotId;
			
			dat.AuctionTime = parseInt(txt_auction_time.text);
			dat.ActionTotalPrice = auction_total_price.getMoney();
			dat.ActionUnitPrice = auction_unit_price.getMoney();
			dat.TotalFixedPrice = auction_total_fixed_price.getMoney();
			
			ExternalInterface.call( "ASSellPage_AuctionSellItemClick", dat);
		}
		
		public function resetSellInfoData():void
		{
			var dat:SellInfoData = new SellInfoData();			
			setSellingItemInfo(dat);
		}
		
		public function resetPrice():void
		{
			auction_total_price.setMoney(_lastSellInfoData.ActionTotalPrice);
			auction_total_fixed_price.setMoney(_lastSellInfoData.TotalFixedPrice);
			auction_unit_price.setMoney(_lastSellInfoData.ActionUnitPrice);
			btn_sell.enabled = true;
		}
		
		public function onResetClick():void
		{
			//var dat:SellInfoData = new SellInfoData();			
			//setSellingItemInfo(dat);
			resetPrice();
		}
		
		public function UCResetSlot(slotType:int):void
		{
			_slotType = slotType;
			//onResetClick();
			resetSellInfoData();
			btn_sell.enabled = true;
		}
		
		function hideSortPanel():void
		{
			sort_sell.resetSort();
			tabTitle.tf_price.text = "价格(竞拍价)";
			_auctionListContrl.resetSortType();
		}
		
		function onPrice_Current(evt:MouseEvent):void
		{
			_auctionListContrl.sortPrice(tabTitle.hdr_price_current.selected);
			_auctionListContrl.hideOtherButton();
		}

	}
	
}
