package UI_AuctionHouse.AS
{
	import flash.events.MouseEvent;
	import flash.external.ExternalInterface;
	import flash.text.TextField;
	
	import ActionScript3.Slot.ItemSlotData;
	
	import scaleform.clik.controls.Button;
	import scaleform.clik.controls.ScrollingList;
	import scaleform.clik.data.DataProvider;
	import scaleform.clik.events.ListEvent;
	
	public class AuctionListItem_Control extends Object 
	{				
		public static const C_Header_Name_String = 0;
		public static const C_Header_Lv_Int = 1;
		public static const C_Header_TimeLeft_Int = 2;
		public static const C_Header_Seller_String = 3;
		public static const C_Header_PriceCurrent_Int = 4;
		public static const C_Header_PriceFixed_Int = 5;
		
		public static const C_Header_Price = 100;
		
		protected var _list_view:ScrollingList;
		protected var _headerList:Array;
		protected var _itemClickHandler:Function;
		protected var _headerClickHandler:Function;
		
		protected var _needUpdateHeadText:Boolean = false;
		
		public var _forceDisplayBuyer:Boolean;
		
		public var _showUnitPrice:Boolean = false;
		
		public var _price_Label:String;
		
		public var _price:Button;
		
		public var _auction_Sort:Auction_Sort;
		
		public var _auction_Type:int = C_Header_Price;
		
		public function AuctionListItem_Control(listView:ScrollingList, 
												headerList:Array, 
												itemClickHandler:Function, 
												headerClickHandler:Function = null, 
												forceDisplayBuyer:Boolean = false,
												priceBtn=null,
												auctionSort=null,
												needUpdateHeadText:Boolean = true)
		{
			_forceDisplayBuyer = forceDisplayBuyer;
			_list_view = listView;
			_itemClickHandler = itemClickHandler;
			_headerClickHandler = headerClickHandler;			
			_headerList = headerList;
			
			_price = priceBtn;
			
			_auction_Sort = auctionSort;
			
			_needUpdateHeadText = needUpdateHeadText;
			
			if(itemClickHandler != null)
			{
				listView.addEventListener(ListEvent.ITEM_CLICK, itemClickHandler, false, 0, true);
			}
						
			for(var i:int = 0; i < headerList.length; ++i)
			{
				var btn:Button = headerList[i];
				btn.itemid = i;
				btn.selected=false;
				if(headerClickHandler != null)
				{
					btn.addEventListener(MouseEvent.CLICK, headerClickHandler);
				}
				else
				{
					btn.addEventListener(MouseEvent.CLICK, onClickHeader);
				}
			}			
		}
		
		function onClickHeader(evt:MouseEvent):void
		{
			var btn:Button = evt.target as Button;
			if(btn != null)
			{
				//btn.selected=!btn.selected;
				sortList(btn.itemid, !btn.selected);
			}
		}
		
		public function createTestItemList():Array
		{					
			var itemsData:Array = new Array();
			
			for (var i:int = 1; i < 15; i++)
			{
				var dat:AuctionItemData = new AuctionItemData();
				dat.SellerID = i % 6;
				dat.BuyerID = i % 6;
				
				if (i%2 == 0)
				{
					
					dat.AuctionID = i;
					dat.ItemName = "神奇的道具" + i.toString();
					dat.ItemLevel = i;
					dat.FixedPrice = 0;
					dat.CurrentAuctionPrice = (i - 1) % 8;
					dat.ItemData = new ItemSlotData();
					dat.Seller = "卖家姓名八个字八个字卖家姓名八个字八个字" + i.toString();
					dat.Buyer = "当前出价" + dat.BuyerID.toString();
					dat.IsAuction = true;
					dat.IsMyAuction = true;
				}
				else
				{
					
					dat.AuctionID = i;
					dat.ItemName = "神奇的道具" + i.toString();
					dat.ItemLevel = i;
					dat.FixedPrice = i;
					dat.CurrentAuctionPrice = (i - 1) % 8;
					dat.ItemData = new ItemSlotData();
					dat.Seller = "卖家姓名八个字八个字" + i.toString();
					dat.Buyer = "当前出价当前出价当前出价当前出价" + dat.BuyerID.toString();
					dat.IsAuction = false;
					dat.IsMyAuction = false;
					dat.CurrentTabPage = 2;
				}
				
				dat.ItemData.slotType = 46;
				dat.TimeLeft = 60 + 2 - (i % 7);
				dat.StackCount = i + 1;
				
				dat.ItemColor = i % 5;
				
				switch(dat.ItemColor)
				{
				case 0:
					dat.ItemName = "<font color='#F2FBFF'>白品</font>";
					break;
				case 1:
					dat.ItemName = "<font color='#1EFF00'>绿品</font>";
					break;
				case 2:
					dat.ItemName = "<font color='#0070DD'>蓝品</font>";
					break;
				case 3:
					dat.ItemName = "<font color='#A335EE'>紫品</font>";
					break;
				case 4:
					dat.ItemName = "<font color='#FF8000'>橙品</font>";
					break;
				}
				
				dat.AuctionMainType = i % 3;
				dat.AuctionSubType = i % 4;
				dat.ItemTemplateID = i + 5;				
				
				itemsData.push(dat);
			}
			return itemsData;
		}
		
		public function updateAuctionItemListData( data:Array ):void
		{
			
			for(var i:int = 0; i < data.length; ++i)
			{
				var dat:AuctionItemData = data[i] as AuctionItemData;
				dat.ForceDisplayBuyer = this._forceDisplayBuyer;
				dat.UnitPrice_Auction = dat.CurrentAuctionPrice / dat.StackCount;
				dat.UnitPrice_Fixed = dat.FixedPrice / dat.StackCount;
			}
			
			_list_view.dataProvider = new DataProvider(data);
			_list_view.validateNow();
			_list_view.invalidateData();
		}
		
		public function toggleUnitPriceShow(showUnitPrice:Boolean)
		{
			toggleUnitPriceShowEx(_list_view, showUnitPrice);
		}
					
		public function toggleUnitPriceShowEx(list:ScrollingList, showUnitPrice:Boolean)
		{
			var provider:DataProvider = list.dataProvider as DataProvider;
			if (provider!=null)
			{
				for(var i:int = 0; i < provider.length; ++i)
				{
					var obj:AuctionItemData = provider[i] as AuctionItemData;
					obj.ShowUnitPrice = showUnitPrice;
				}
			}
			
			list.invalidateData();
			_showUnitPrice = showUnitPrice;
		}
		
		
		public function toggleHeaderSortStatus(idx:int, sortDescending:Boolean):void
		{
			for(var i:int = 0; i < _headerList.length; ++i)
			{
				var btn:Button = _headerList[i];
				if(idx == i)
				{
					btn.selected = sortDescending;
				}
				else
				{
					if(btn.itemid == C_Header_PriceCurrent_Int || btn.itemid == C_Header_PriceFixed_Int)
					{
						continue;
					}
					btn.selected = false;
				}
			}
			setPrice(idx,sortDescending);
		}
		
		public function setPrice(idx:int, sortDescending:Boolean)
		{
			_price.selected = !sortDescending;
			switch(idx)
			{
			case C_Header_PriceCurrent_Int:
				if(_needUpdateHeadText){
					(_price.parent.getChildByName("tf_price") as TextField).text = "价格(竞拍价)";
				}
				_auction_Type = C_Header_PriceCurrent_Int;
				break;
			case C_Header_PriceFixed_Int:
				if(_needUpdateHeadText){
					(_price.parent.getChildByName("tf_price") as TextField).text = "价格(一口价)";
				}
				_auction_Type = C_Header_PriceFixed_Int;
				break;
			default:
				//_price_Label = "价格"
				//_auction_Type = C_Header_Price;
				_price.selected = false;
				break;
			}
			//_auction_Sort.hideSort();
			//_price.label = _price_Label;
			
		}
		
		public function sortList(idx:int, sortDescending:Boolean):void
		{
			toggleHeaderSortStatus(idx, sortDescending);
			
			sortListEx(this._list_view, idx, sortDescending);
		}
		
		function sortByString(a:String, b:String):Number
		{
			//trace("sortByString", a, b);
			
			if(a.length < b.length)
			{
				//trace("sortByString len:-1", a, b);
				return -1;
			}
			
			if(a.length > b.length)
			{
				//trace("sortByString len:1", a, b);
				return 1;
			}
			
			if(a < b)
			{
				//trace("sortByString len a<b :-1", a, b);
				return -1;
			}
			
			if(a > b)
			{
				//trace("sortByString len a>b :1", a, b);
				return 1;
			}
			
			trace("sortByString len 0", a, b);
			return 0;
		}
		
		function sortByStringDescending(a:String, b:String):Number
		{
			//trace("sortByStringDescending", a, b);
			
			if(a.length < b.length)
			{
				return 1;
			}
			
			if(a.length > b.length)
			{
				return -1;
			}
			
			
			if(a < b)
			{
				return 1;
			}
			
			if(a > b)
			{
				return -1;
			}
			
			return 0;
		}
		
		
		function sortBySellerString(a:AuctionItemData, b:AuctionItemData):Number
		{
			return sortByString(a.BuyerID == 0 ? a.Seller : a.Buyer, b.BuyerID == 0 ? b.Seller : b.Buyer);
		}
		
		function sortBySellerStringDescending(a:AuctionItemData, b:AuctionItemData):Number
		{
			return sortByStringDescending(a.BuyerID == 0 ? a.Seller : a.Buyer, b.BuyerID == 0 ? b.Seller : b.Buyer);
		}
		
		function sortByItemString(a:AuctionItemData, b:AuctionItemData):Number
		{
			return sortByString(a.ItemName, b.ItemName);
		}
		
		function sortByItemStringDescending(a:AuctionItemData, b:AuctionItemData):Number
		{
			return sortByStringDescending(a.ItemName, b.ItemName);
		}
		
		function sortItem(a:AuctionItemData, b:AuctionItemData):Number
		{
			// 品质
			if(a.ItemColor > b.ItemColor)
			{
				return -1;
			}
			
			if(a.ItemColor < b.ItemColor)
			{
				return 1;
			}
			
			// 类型
			if(a.AuctionMainType > b.AuctionMainType)
			{
				return -1;
			}
			
			if(a.AuctionMainType < b.AuctionMainType)
			{
				return 1;
			}
			
			// 子类型
			if(a.AuctionSubType > b.AuctionSubType)
			{
				return -1;
			}
			
			if(a.AuctionSubType < b.AuctionSubType)
			{
				return 1;
			}
				
			// 等级
			if(a.ItemLevel > b.ItemLevel)
			{
				return -1;
			}
			
			if(a.ItemLevel < b.ItemLevel)
			{
				return 1;
			}
			
			// ID
			if(a.ItemTemplateID > b.ItemTemplateID)
			{
				return -1;
			}
			
			if(a.ItemTemplateID < b.ItemTemplateID)
			{
				return 1;
			}
			
			return 0;
		}
		
		function sortItemDescending(a:AuctionItemData, b:AuctionItemData):Number
		{
			// 品质
			if(a.ItemColor > b.ItemColor)
			{
				return 1;
			}
			
			if(a.ItemColor < b.ItemColor)
			{
				return -1;
			}
			
			// 类型
			if(a.AuctionMainType > b.AuctionMainType)
			{
				return 1;
			}
			
			if(a.AuctionMainType < b.AuctionMainType)
			{
				return -1;
			}
			
			// 子类型
			if(a.AuctionSubType > b.AuctionSubType)
			{
				return 1;
			}
			
			if(a.AuctionSubType < b.AuctionSubType)
			{
				return -1;
			}
				
			// 等级
			if(a.ItemLevel > b.ItemLevel)
			{
				return 1;
			}
			
			if(a.ItemLevel < b.ItemLevel)
			{
				return -1;
			}
			
			// ID
			if(a.ItemTemplateID > b.ItemTemplateID)
			{
				return 1;
			}
			
			if(a.ItemTemplateID < b.ItemTemplateID)
			{
				return -1;
			}
			
			return 0;
		}
		
		public function sortListEx(list:ScrollingList, idx:int, sortDescending:Boolean)
		{
			var provider:DataProvider = list.dataProvider as DataProvider;
			if (provider!=null)
			{
				trace("----sortList" + idx + sortDescending);
				switch(idx)
				{
					case C_Header_Name_String:
					//provider.sortOn("ItemName", sortDescending ? Array.DESCENDING :  0);
					if(sortDescending)
					{
						provider.sort(sortItemDescending);
					}
					else
					{
						provider.sort(sortItem);
					}
					break;
					
					case C_Header_Lv_Int:
					provider.sortOn("ItemLevel", sortDescending ? Array.DESCENDING | Array.NUMERIC : Array.NUMERIC);
					break;
					
					case C_Header_TimeLeft_Int:
					provider.sortOn("TimeLeft", sortDescending ? Array.DESCENDING | Array.NUMERIC : Array.NUMERIC);
					break;
					
					case C_Header_Seller_String:
					//provider.sortOn("Seller", sortDescending ? Array.DESCENDING :  0);
					if(sortDescending)
					{
						provider.sort(sortBySellerStringDescending);
					}
					else
					{
						provider.sort(sortBySellerString);
					}
					break;
					
					case C_Header_PriceCurrent_Int:
						sortPriceByAuction(provider,!sortDescending);
					break;
					
					case C_Header_PriceFixed_Int:
						sortPriceByFixed(provider,!sortDescending);
					break;
				}
			}
			
			list.invalidateData();
		}		
		
		public function getSelectedData():AuctionItemData
		{
			var provider:DataProvider = _list_view.dataProvider as DataProvider;
			if(_list_view.selectedIndex >= 0 && _list_view.selectedIndex < provider.length)
			{
				return provider.requestItemAt(_list_view.selectedIndex) as AuctionItemData;
			}
			
			return null;
		}
		
		public function setPlayerName(playerID:int, playerName:String):void
		{
			var provider:DataProvider = _list_view.dataProvider as DataProvider;
			if (provider!=null)
			{
				for(var i:int = 0; i < provider.length; ++i)
				{
					var obj:AuctionItemData = provider[i] as AuctionItemData;
					if(obj.SellerID == playerID)
					{
						obj.Seller = playerName;
					}
					else if(obj.BuyerID == playerID)
					{
						obj.Buyer = playerName;
					}
				}
			}
			
			_list_view.invalidateData();
		}
		
		public function sortPrice(select:Boolean):void
		{
			var provider:DataProvider = this._list_view.dataProvider as DataProvider;
			var isSort:Boolean = false;
			
			if (provider!=null)
			{
				switch(_auction_Type)
				{
				case C_Header_PriceCurrent_Int:
					sortPriceByAuction(provider,select);
					isSort = true;
				break;
					
				case C_Header_PriceFixed_Int:
					sortPriceByFixed(provider,select);
					isSort = true;
				break;
				}
			}
			if(isSort)
			{
				this._list_view.invalidateData();
			}
			
		}
		
		public function sortPriceByAuction(provider:DataProvider,sortDescending:Boolean):void
		{
			if(_showUnitPrice)
			{
				provider.sortOn("UnitPrice_Auction",  Array.NUMERIC );
			}
			else
			{
				provider.sortOn("CurrentAuctionPrice", Array.NUMERIC );
			}
		}
		
		public function sortPriceByFixed(provider:DataProvider,sortDescending:Boolean):void
		{
			if(_showUnitPrice)
			{
				provider.sortOn("UnitPrice_Fixed",  Array.NUMERIC );
			}
			else
			{
				provider.sortOn("FixedPrice", Array.NUMERIC);
						
			}
			
		}
		
		
		public function resetSortType()
		{
			_auction_Type = C_Header_PriceCurrent_Int;
			//sortPrice(false);
		}
		
		public function hideOtherButton()
		{
			for(var i:int = 0; i < _headerList.length; ++i)
			{
				var btn:Button = _headerList[i];
				if(btn.itemid == C_Header_PriceCurrent_Int || btn.itemid == C_Header_PriceFixed_Int)
				{
						continue;
				}
				else
				{
					btn.selected = false;
				}
				
			}
		}
		
	}
	
}
