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
	import ActionScript3.Slot.ItemSlotData;
	import scaleform.clik.controls.CheckBox;
	import ActionScript3.controls.ListItemHeader;
	import ActionScript3.Common.MoneyInputNew;
	import ActionScript3.Common.Events.ParamEvent;


	public class AuctionPage_Buy extends UIComponent
	{
		public var auction_list:ScrollingList;
		//public var auction_fail_list:ScrollingList;

		public var current_money:MoneyInputNew;
		public var auction_money:MoneyInputNew;

		public var btn_auction:Button;
		public var btn_fixedprice_buy:Button;

		public var chk_show_unit_price:CheckBox;

		public var hdr_item_name:Button;
		public var hdr_item_lv:Button;
		public var hdr_time_left:Button;
		public var hdr_seller_name:Button;
		public var hdr_price_current:Button;
		public var hdr_price_fixed:Button;

		//public var hdr_item_name_fail:Button;
		//public var hdr_item_lv_fail:Button;
		//public var hdr_time_left_fail:Button;
		//public var hdr_seller_name_fail:Button;
		//public var hdr_price_current_fail:Button;
		//public var hdr_price_fixed_fail:Button;

		var _auctionListContrl:AuctionListItem_Control;
		//var _auctionFailedListContrl:AuctionListItem_Control;
		//var _currentSelectBuyingList:Boolean; // 当前选择的是哪个表
		
		public var sort_buy:Auction_Sort;
	//	public var sort_failed:Auction_Sort;
		
		public var btn_sort_buy:Button;
		//public var btn_sort_failed:Button;
		public var tabTitle:MovieClip;
		public var btn_bidding:RadioButton;
		public var btn_beat:RadioButton;
		
		private var biddingList:Array;
		private var beatList:Array;
		
		var MAX_MONEY:uint = 1000000000;
		
		public const AUCTION:int = 4;
		public const FIXED:int = 5;
		
		public function AuctionPage_Buy()
		{
			// constructor code
		}

		override protected function configUI():void
		{
			super.configUI();
            biddingList=[];
			beatList=[];
			chk_show_unit_price.addEventListener(MouseEvent.CLICK, onShowUnitPriceClick, false, 0, true);
			btn_auction.addEventListener(MouseEvent.CLICK, onAuctionClick, false, 0, true);
			btn_fixedprice_buy.addEventListener(MouseEvent.CLICK, onAuctionFixedPriceClick, false, 0, true);
			btn_bidding.addEventListener(MouseEvent.CLICK,biddingHandler);
			btn_beat.addEventListener(MouseEvent.CLICK,beatHandler);
			auction_money.addEventListener(ParamEvent.INPUT_CHANGE, onAuctionPriceInputChange, false, 0, true);
			
			//tabTitle.hdr_price_current.addEventListener(MouseEvent.CLICK,onPrice_Current);
			//hdr_price_current_fail.addEventListener(MouseEvent.CLICK,onPrice_CurrentFail);
			btn_bidding.selected=true;
			
			var headerArr:Array = new Array();
			//headerArr.push(tabTitle.hdr_item_name);
			//headerArr.push(tabTitle.hdr_item_lv);
			//headerArr.push(tabTitle.hdr_time_left);
			//headerArr.push(tabTitle.hdr_seller_name);
			headerArr.push(sort_buy.rdo_sortAuction);
			headerArr.push(sort_buy.rdo_sortFixed);
			
			_auctionListContrl = new AuctionListItem_Control(this.auction_list, headerArr, onBuyingItemListItemClick, null,false,tabTitle.hdr_price_current,sort_buy, false);
/*
			var headerArr2:Array = new Array();
			headerArr2.push(hdr_item_name_fail);
			headerArr2.push(hdr_item_lv_fail);
			headerArr2.push(hdr_time_left_fail);
			headerArr2.push(hdr_seller_name_fail);
			headerArr2.push(sort_failed.rdo_sortAuction);
			headerArr2.push(sort_failed.rdo_sortFixed);
			
			_auctionFailedListContrl = new AuctionListItem_Control(this.auction_fail_list, headerArr2, onFailedItemListItemClick, null, true,hdr_price_current_fail,sort_failed);*/
			
			//sort_buy.setButton(btn_sort_buy);
			//sort_failed.setButton(btn_sort_failed);
			
			sort_buy.rdo_sortAuction.itemid = AUCTION;
			sort_buy.rdo_sortFixed.itemid = FIXED;
			
			updateUI(-1, true, 0);
			
			sort_buy.resetSort();
		}
		
		protected function biddingHandler(e:MouseEvent):void
		{
			update();
		}
		
		protected function beatHandler(e:MouseEvent):void
		{
			update();
		}
		
		public function createTestItemList(b:Boolean):Array
		{					
			var itemsData:Array = new Array();
			
			for (var i:int = 1; i < 15; i++)
			{
				var dat:AuctionItemData = new AuctionItemData();
				dat.SellerID = i % 6;
				dat.BuyerID = i % 6;
				
				if (b == true)
				{
					
					dat.AuctionID = i;
					dat.ItemName = "神奇的道具" + i.toString();
					dat.ItemLevel = i;
					dat.FixedPrice = 0;
					dat.CurrentAuctionPrice = (i - 1) % 8;
					dat.ItemData = new ItemSlotData();
					dat.Seller = "当前出价" + i.toString();
					dat.Buyer = "当前出价" + dat.BuyerID.toString();
					dat.IsAuction = true;
					dat.IsMyAuction = true;
				}
				else
				{
					
					dat.AuctionID = i;
					dat.ItemName = "神奇的道具神奇的道具" + i.toString();
					dat.ItemLevel = i;
					dat.FixedPrice = i;
					dat.CurrentAuctionPrice = (i - 1) % 8;
					dat.ItemData = new ItemSlotData();
					dat.Seller = "卖家" + i.toString();
					dat.Buyer = "当前出价" + dat.BuyerID.toString();
					dat.IsAuction = false;
					dat.IsMyAuction = false;
					dat.CurrentTabPage = 2;
				}
				
				dat.ItemData.slotType = 46;
				dat.TimeLeft = 60 + 2 - (i % 7);
				dat.StackCount = i + 1;
				
				dat.ItemColor = i % 5;
				dat.AuctionMainType = i % 3;
				dat.AuctionSubType = i % 4;
				dat.ItemTemplateID = i + 5;				
				
				itemsData.push(dat);
			}
			return itemsData;
		}
		

		public function updateUI(selIdx:int, buyingList:Boolean, fixedPrice:int)
		{
			btn_auction.enabled = selIdx != -1 && !buyingList; // 只有不是在拍卖列表中的才能再次拍卖
			btn_fixedprice_buy.enabled = (selIdx != -1) && (fixedPrice > 0);
		}
		
		public function onBuyingItemListItemClick(event:ListEvent):void
		{
			//_currentSelectBuyingList = true;
			
			//this.auction_fail_list.selectedIndex = -1;
			
			var list:ScrollingList = event.target as ScrollingList;
			if (list != null)
			{
				var provider:DataProvider = list.dataProvider as DataProvider;
				if (provider!=null)
				{
					//provider.handleListItemClick( event );
					var obj:AuctionItemData = provider.requestItemAt(event.index) as AuctionItemData;
					this.auction_money.setMoney(obj.getNextAuctionPrice());
					
					//判断当前状态
					if(btn_bidding.selected == true)
						updateUI(event.index, true, obj.FixedPrice);
					else
						updateUI(event.index, false, obj.FixedPrice);
				}

				list.invalidateData();
			}
		}
		
/*		public function onFailedItemListItemClick(event:ListEvent):void
		{
			_currentSelectBuyingList = false;
			
			this.auction_list.selectedIndex = -1;
			
			var list:ScrollingList = event.target as ScrollingList;
			if (list != null)
			{
				var provider:DataProvider = list.dataProvider as DataProvider;
				if (provider!=null)
				{
					//provider.handleListItemClick( event );
					var obj:AuctionItemData = provider.requestItemAt(event.index) as AuctionItemData;
					this.auction_money.setMoney(obj.getNextAuctionPrice());
					updateUI(event.index, _currentSelectBuyingList, obj.FixedPrice);
				}

				list.invalidateData();
			}
		}*/
		
		function onShowUnitPriceClick():void
		{
			//_auctionFailedListContrl.toggleUnitPriceShow(chk_show_unit_price.selected);
			_auctionListContrl.toggleUnitPriceShow(chk_show_unit_price.selected);
		}

		function onAuctionClick():void
		{
			var obj:AuctionItemData = this._auctionListContrl.getSelectedData();
			if(obj != null)
			{
				if(this.btn_bidding.selected==true)
				{
					if((obj.FixedPrice > 0) && (obj.FixedPrice <= auction_money.getMoney()))
					{
						ExternalInterface.call( "ASBuyPage_AuctionClick", obj.AuctionID, auction_money.getMoney(),1);
					}
					else
					{
						ExternalInterface.call( "ASBuyPage_AuctionClick", obj.AuctionID, auction_money.getMoney(),0);
					}
				}
				else
				{
					if((obj.FixedPrice > 0) && (obj.FixedPrice <= auction_money.getMoney()))
					{
						ExternalInterface.call( "ASBuyPage_AuctionFailedClick", obj.AuctionID, auction_money.getMoney(),1);
					}
					else
					{
						ExternalInterface.call( "ASBuyPage_AuctionFailedClick", obj.AuctionID, auction_money.getMoney(),0);
					}
					
				}
			}
		}

		function onAuctionFixedPriceClick():void
		{
			var obj:AuctionItemData=this._auctionListContrl.getSelectedData();
			if(obj != null)
			{
				if(this.btn_bidding.selected==true)
				{
					ExternalInterface.call( "ASBuyPage_AuctionFixedPriceClick", obj.AuctionID, obj.FixedPrice);
				}
				else
				{
					ExternalInterface.call( "ASBuyPage_AuctionFailedFixedPriceClick", obj.AuctionID, obj.FixedPrice);
				}
				
			}
		}
		
		public function updateAuctionItemListData( data:Array ):void
		{
			this.biddingList=data;
			update();
			//_auctionListContrl.updateAuctionItemListData(data);
			updateUI(-1, true, 0);
			updateAuctionPrice(true);
		}
		
		public function updateFailedAuctionItemListData( data:Array ):void
		{
			this.beatList=data;
			update();
			//_auctionFailedListContrl.updateAuctionItemListData(data);
			updateUI(-1, false, 0);
			updateAuctionPrice(false);
		}
		
		private function update():void
		{
			if(this.btn_bidding.selected==true){
				_auctionListContrl._forceDisplayBuyer=false;
				_auctionListContrl.updateAuctionItemListData(this.biddingList);
			}else{
				_auctionListContrl._forceDisplayBuyer=false;
				_auctionListContrl.updateAuctionItemListData(this.beatList);
			}
		}
		
		function getCurrentSelectData():AuctionItemData
		{			
			var dat:AuctionItemData = null;
			var dp:DataProvider = auction_list.dataProvider as DataProvider;
			if(auction_list.selectedIndex >= 0 && auction_list.selectedIndex < dp.length)
			{
				dat = dp[auction_list.selectedIndex];
			}				
/*			if(_currentSelectBuyingList)
			{
				var dp:DataProvider = auction_list.dataProvider as DataProvider;
				if(auction_list.selectedIndex >= 0 && auction_list.selectedIndex < dp.length)
				{
					dat = dp[auction_list.selectedIndex];
				}				
			}
			else
			{
				var dp2:DataProvider = this.auction_fail_list.dataProvider as DataProvider;
				if(auction_fail_list.selectedIndex >= 0 && auction_fail_list.selectedIndex < dp2.length)
				{
					dat = dp2[auction_fail_list.selectedIndex];
				}
			}*/
			
			return dat;
		}
		
		function onAuctionPriceInputChange(evt:ParamEvent):void
		{
			var money:int=evt.param as int;
			var dat:AuctionItemData = getCurrentSelectData();
			if(dat != null)
			{
				this.btn_auction.enabled = (money >= dat.getNextAuctionPrice());
				this.btn_fixedprice_buy.enabled = this.btn_auction.enabled && (dat.FixedPrice > 0);
			}
			if(money >= MAX_MONEY)
			{
				auction_money.setMoney(MAX_MONEY);
			}
		}
		
		function hideSortPanel():void
		{
			sort_buy.resetSort();
			//sort_failed.resetSort();
			tabTitle.tf_price.text = "价格(竞拍价)";
			//hdr_price_current_fail.label = "价格(竞拍价)";
			_auctionListContrl.resetSortType();
			//_auctionFailedListContrl.resetSortType();
		}
		
		function onPrice_Current(evt:MouseEvent):void
		{
			_auctionListContrl.sortPrice(tabTitle.hdr_price_current.selected);
			_auctionListContrl.hideOtherButton();
		}
		
/*		function onPrice_CurrentFail(evt:MouseEvent):void
		{
			_auctionFailedListContrl.sortPrice(hdr_price_current_fail.selected);
			_auctionFailedListContrl.hideOtherButton();
		}*/
		
		function updateAuctionPrice(isCurrent:Boolean):void
		{
			var fixedPrice:int = 0;
			var dat:AuctionItemData = getCurrentSelectData();
			if(dat != null)
			{
				this.auction_money.setMoney(dat.getNextAuctionPrice());
				updateUI(dat.AuctionID, isCurrent, dat.FixedPrice);
			}
		}
	}

}