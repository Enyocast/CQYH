package UI_AuctionHouse.AS 
{
	import flash.display.MovieClip;
	import flash.events.Event;
	import flash.events.FocusEvent;
	import flash.events.MouseEvent;
	import flash.external.ExternalInterface;
	import flash.text.TextField;
	
	import ActionScript3.MyPanel;
	import ActionScript3.TreeListData;
	import ActionScript3.Common.MoneyInputNew;
	import ActionScript3.Common.Events.ParamEvent;
	import ActionScript3.Slot.ItemSlotData;
	import ActionScript3.UndergroundTrade.SearchPanel;
	import ActionScript3.controls.ListItemHeader;
	
	import scaleform.clik.controls.Button;
	import scaleform.clik.controls.CheckBox;
	import scaleform.clik.controls.DropdownMenu;
	import scaleform.clik.controls.RadioButton;
	import scaleform.clik.controls.ScrollingList;
	import scaleform.clik.controls.TextInput;
	import scaleform.clik.core.UIComponent;
	import scaleform.clik.data.DataProvider;
	import scaleform.clik.data.TreeDataProvider;
	import scaleform.clik.events.ListEvent;
	import scaleform.clik.interfaces.IDataProvider;
	import scaleform.clik.managers.FocusHandler;
	
	
	public class AuctionPage_View extends UIComponent 
	{		
		private static const VIEW_TYPE_CATEGORY_LIST:int 	= 0;
		private static const VIEW_TYPE_RESULT_LIST:int 	    = 1;
		private static const VIEW_TYPE_ADVANCED_SEARCH:int  = 2;
		
		public var search_page:Auction_SearchPage;		
		public var btn_reset:Button;
		public var btn_refresh:Button;
		
		public var item_category_list:ScrollingList;
		public var item_list:ScrollingList;
		
		public var current_money:MoneyInputNew;
		public var auction_money:MoneyInputNew;
		
		public var txt_page_num:TextField;
		public var btn_goto_page:Button;
		public var cur_page:int;
		public var max_page:int;
		public var txt_noItem:TextField;
		public var txt_noItem_right:TextField;
		
		public var btn_auction:Button;
		public var btn_fixedprice_buy:Button;
		
		public var chk_show_unit_price:CheckBox;
		
		public var page_ctrl:MovieClip;
		
		//public var tabTitle_left:MovieClip;
		
		/*public var hdr_item_name:Button;
		public var hdr_item_lv:Button;
		public var hdr_time_left:Button;
		public var hdr_seller_name:Button;
		public var hdr_price_current:Button;
		public var hdr_price_fixed:Button;*/
		
		public var sort_view:Auction_Sort;
	//	public var btn_sort_view:Button;
		public var tabTitle:MovieClip;
		var _auctionListContrl:AuctionListItem_Control;
		
		public const SINGLEPRICE:int = 6;
		public const SINGLEPRICE_BUYOUT:int = 7;
		public const AUCTION:int = 4;
		public const FIXED:int = 5;
		
		var MAX_MONEY:uint = 1000000000;
		
		public var btn_head:Button;
		
		public var treeView:AuctionPage_TreeList;
		
		//add by wph for new edition
		public var head_search_mc:Auction_SearchHead;
		protected var _leftListViewType:int;
		
		public var txt_debugInfo:TextField;
		protected var _logEnable:Boolean = false;
		
		public function LOG(info:String):void
		{
			if(_logEnable){
				if(txt_debugInfo.numLines > 30){
					txt_debugInfo.text = "";
				}
				txt_debugInfo.appendText(info  + "\n");
			}
		}
		
		public function AuctionPage_View() 
		{
			// constructor code
		}
		
		function getPrevPageButton():Button
		{
			var prevPage:Button = page_ctrl.getChildByName("btn_prev") as Button;
			return prevPage;
		}
		
		function getNextPageButton():Button
		{
			var prevPage:Button = page_ctrl.getChildByName("btn_next") as Button;
			return prevPage;
		}
		
		override protected function configUI():void
		{
			super.configUI();
			if(txt_debugInfo){
				txt_debugInfo.mouseEnabled = false;
			}
			LOG('configUI: ' + txt_debugInfo);
			
			this.tabTitle.tf_name.text="出售者";
			var prevPage:Button = getPrevPageButton();
			if(null != prevPage)
				prevPage.addEventListener(MouseEvent.CLICK, onPrevPageClick, false, 0, true);
				
			var nextPage:Button = getNextPageButton();
			if(null != nextPage)
				nextPage.addEventListener(MouseEvent.CLICK, onNextPageClick, false, 0, true);				
				
			setPageNumber(1,5);
						
			btn_goto_page.addEventListener(MouseEvent.CLICK, onGotoPage, false, 0, true);
			chk_show_unit_price.addEventListener(MouseEvent.CLICK, onShowUnitPriceClick, false, 0, true);
			btn_auction.addEventListener(MouseEvent.CLICK, onAuctionClick, false, 0, true);
			
			btn_refresh.addEventListener(MouseEvent.CLICK, onFresh, false, 0, true);
			
			btn_fixedprice_buy.addEventListener(MouseEvent.CLICK, onAuctionFixedPriceClick, false, 0, true);
			auction_money.addEventListener(ParamEvent.INPUT_CHANGE, onAuctionPriceInputChange, false, 0, true);
			
			item_category_list.addEventListener(ListEvent.ITEM_CLICK, onCategoryListItemClick, false, 0, true);
			item_category_list.addEventListener(ListEvent.INDEX_CHANGE, onCategoryListChange, false, 0, true);
			//txt_page_num.addEventListener( Event.CHANGE, handlePageTextChange, false, 0, true );
			//txt_page_num.addEventListener(FocusEvent.FOCUS_IN,onTxtPageFocusIn);
			//txt_page_num.addEventListener(FocusEvent.FOCUS_OUT,onTxtPageFocusOut);
			
			var headerArr:Array = new Array();
			//headerArr.push(tabTitle.hdr_item_name);
			//headerArr.push(tabTitle.hdr_item_lv);
			//headerArr.push(tabTitle.hdr_time_left);
			//headerArr.push(tabTitle.hdr_seller_name);
			//headerArr.push(hdr_price_current);
			//headerArr.push(hdr_price_fixed);
			headerArr.push(sort_view.rdo_sortAuction);
			headerArr.push(sort_view.rdo_sortFixed);
			
			_auctionListContrl = new AuctionListItem_Control(item_list, headerArr, onItemListItemClick, onClickHeader,false,tabTitle.hdr_price_current,sort_view);
			
			this.addEventListener(Event_Search.RESET, onResetSearchFilter, false, 0, true);
			
			//tabTitle.hdr_price_current.addEventListener(MouseEvent.CLICK, onPriceSort);
			//txt_noItem.visible = false;
			//Test();
			
			//sort_view.setButton(btn_sort_view);
			
			updateUI(-1, 0);
			
			btn_head.addEventListener(MouseEvent.CLICK,onReturn);
			//UCUpdateTreeList(_auctionListContrl.createTestItemList());
			
			sort_view.rdo_sortAuction.itemid = AUCTION;
			sort_view.rdo_sortFixed.itemid = FIXED;
			
			btn_reset.addEventListener(MouseEvent.CLICK, onReset);
			
			sort_view.resetSort();
			switchLeftListViewType(VIEW_TYPE_CATEGORY_LIST);
			onReset();
		}
		
		public function switchLeftListViewType(viewType:int):void
		{
			switch(viewType)
			{
				case VIEW_TYPE_CATEGORY_LIST:
				{
					btn_head.label = "高级搜索";
					treeView.visible = false;
					search_page.visible = false;
					item_category_list.visible = true;
					head_search_mc.visible = true;
					txt_noItem.visible= false;
					head_search_mc.onReset();
					break;
				}
				case VIEW_TYPE_RESULT_LIST:
				{
					btn_head.label = "返回";
					treeView.visible = true;
					search_page.visible = false;
					item_category_list.visible = false;
					head_search_mc.visible = true;
					break;
				}
				case VIEW_TYPE_ADVANCED_SEARCH:
				{
					btn_head.label = "返回";
					treeView.visible = false;
					search_page.visible = true;
					item_category_list.visible = false;
					head_search_mc.visible = false;
					txt_noItem.visible= false;
					break;
				}
			}
			_leftListViewType = viewType;
		}
		
		function onTxtPageFocusIn(evt:FocusEvent):void
		{
			ExternalInterface.call( "ASFocusInTextInput" , true );
		}
		
		function onTxtPageFocusOut(evt:FocusEvent):void
		{
			ExternalInterface.call( "ASFocusInTextInput" , false );
		}
		
		public function onFresh():void
		{
			ExternalInterface.call("ASAuction_Fresh");
		}
		
		 protected function handlePageTextChange(evt:Event):void
		 {
			 var pgNum:int = getPageNumber();
			if(pgNum > max_page)
			{
				txt_page_num.text = max_page.toString();
			}			
			else if(pgNum < 1)
			{
				txt_page_num.text = "1";
			}
		 }

		function onResetSearchFilter(evt:Event_Search):void
		{
			//item_category_list.selectedIndex = 0;
			
		}
		
		function onClickHeader(evt:MouseEvent):void
		{
			var btn:Button = evt.target as Button;
			if(btn != null)
			{
				//btn.selected=!btn.selected;
				var select:Boolean = btn.selected;
				var itemId = btn.itemid;
				var isUnitPrice = chk_show_unit_price.selected;
				switch(btn.itemid)
				{
				case 4:
					if(isUnitPrice)
					{
						itemId = SINGLEPRICE;
					}
					select = !btn.selected
					break;
				case 5:
					if(isUnitPrice)
					{
						itemId = SINGLEPRICE_BUYOUT;
					}
					select = !btn.selected
					break;
				}
				_auctionListContrl.toggleHeaderSortStatus(btn.itemid, btn.selected);
				ExternalInterface.call( "ASViewPage_ClickHeaderSort", itemId, select);
				
			}
		}
		
		
		function onShowUnitPriceClick():void
		{
			_auctionListContrl.toggleUnitPriceShow(chk_show_unit_price.selected);
		}
		
		function onAuctionClick():void
		{
			var dp:DataProvider = item_list.dataProvider as DataProvider;
			var dat:AuctionItemData = dp[item_list.selectedIndex];
			if((dat.FixedPrice > 0) && (dat.FixedPrice <= auction_money.getMoney()))
			{
				//竞标价大于一口价
				ExternalInterface.call( "ASViewPage_AuctionClick", dat.AuctionID, dat.FixedPrice,1);
			}
			else
			{
				ExternalInterface.call( "ASViewPage_AuctionClick", dat.AuctionID, auction_money.getMoney(),0);
			}
			
		}
		
		function onAuctionFixedPriceClick():void
		{
			var dp:DataProvider = item_list.dataProvider as DataProvider;
			var dat:AuctionItemData = dp[item_list.selectedIndex];
			ExternalInterface.call( "ASViewPage_AuctionFixedPriceClick", dat.AuctionID, dat.FixedPrice);
		}
		
		function onPrevPageClick():void
		{
			trace("onPrevPageClick:", cur_page, max_page);
			
			if(cur_page - 1 >= 0)
			{
				--cur_page;
				updatePageText();
				
				ExternalInterface.call( "ASViewPage_PrevPageClick", getCurrentPageNumber());
			}
		}
		
		function onNextPageClick():void
		{
			trace("onNextPageClick:", cur_page, max_page);
			
			if(cur_page + 1 < max_page)
			{
				++cur_page;
				updatePageText();
				
				ExternalInterface.call( "ASViewPage_NextPageClick", getCurrentPageNumber());
			}
		}
		
		function onGotoPage():void
		{
			ExternalInterface.call( "ASViewPage_GotoPageClick", Math.max(0, getPageNumber() - 1));
		}
		
		function setPageNumber(cur:int, total:int):void
		{
			cur_page = cur;
			max_page = total;
			
			updatePageText();
		}
		
		function updatePageText():void
		{
			var tF_pageNum:TextField = page_ctrl.getChildByName("tF_pageNum") as TextField;
			
			if(null != tF_pageNum)
				tF_pageNum.text = (cur_page + 1).toString() + "/" + max_page.toString();
			
			//this.txt_page_num.text = "1";
			this.getNextPageButton().enabled = cur_page + 1 < max_page;
			this.getPrevPageButton().enabled = cur_page - 1 >= 0;
		}
		
		function getCurrentPageNumber():int
		{			
			return cur_page;
		}
		
		function getPageNumber():int
		{
			trace("-----------" + txt_page_num.text);
			return parseInt(txt_page_num.text);
		}
		
		function Test()
		{
			if(1)
			{
				TestCategoryList();	
			}
		}
		
		function TestCategoryList()
		{					
			var itemsData:Array = new Array();
			
			var dat:AuctionItemCategoryData = new AuctionItemCategoryData();
			dat.label = "标题0";
			dat.index = 0;							
			dat.mainTypeValue = 0;				
			dat.subTypeValue = 0;
			dat.categoryType = AuctionItemCategoryData.C_TypeLv1;				
			dat.isSelected = false;								
			dat.deepth = dat.categoryType;
			dat.type = TreeListData.C_Type_Branch_Closed;
			dat.visible = true;				
			itemsData.push(dat);
			
			dat = new AuctionItemCategoryData();
			dat.label = "汉字1";
			dat.index = 1;				
			dat.mainTypeValue = 0;				
			dat.subTypeValue = 1;
			dat.categoryType = AuctionItemCategoryData.C_TypeLv2;				
			dat.isSelected = false;								
			dat.deepth = dat.categoryType;
			dat.type = TreeListData.C_Type_Leaf;
			dat.visible = true;				
			itemsData.push(dat);
			
			dat = new AuctionItemCategoryData();
			dat.label = "汉字2";
			dat.index = 2;
			dat.mainTypeValue = 0;				
			dat.subTypeValue = 2;
			dat.categoryType = AuctionItemCategoryData.C_TypeLv2;				
			dat.isSelected = false;								
			dat.deepth = dat.categoryType;
			dat.type = TreeListData.C_Type_Leaf;
			dat.visible = true;				
			itemsData.push(dat);
			
			dat = new AuctionItemCategoryData();
			dat.label = "标题3";
			dat.index = 3;
			dat.mainTypeValue = 1;				
			dat.subTypeValue = 0;
			dat.categoryType = AuctionItemCategoryData.C_TypeLv1;
			dat.isSelected = false;								
			dat.deepth = dat.categoryType;
			dat.type = TreeListData.C_Type_Branch_Closed;
			dat.visible = true;				
			itemsData.push(dat);
			
			dat = new AuctionItemCategoryData();
			dat.label = "汉字4";
			dat.index = 4;
			dat.mainTypeValue = 1;				
			dat.subTypeValue = 1;
			dat.categoryType = AuctionItemCategoryData.C_TypeLv2;				
			dat.isSelected = false;								
			dat.deepth = dat.categoryType;
			dat.type = TreeListData.C_Type_Leaf;
			dat.visible = true;				
			itemsData.push(dat);
			
			dat = new AuctionItemCategoryData();
			dat.label = "标题5";
			dat.index = 5;
			dat.mainTypeValue = 2;				
			dat.subTypeValue = 0;
			dat.categoryType = AuctionItemCategoryData.C_TypeLv1;
			dat.isSelected = false;								
			dat.deepth = dat.categoryType;
			dat.type = TreeListData.C_Type_Branch_Closed;
			dat.visible = true;				
			itemsData.push(dat);
			
			dat = new AuctionItemCategoryData();
			dat.label = "汉字6";
			dat.index = 6;
			dat.mainTypeValue = 2;				
			dat.subTypeValue = 1;
			dat.categoryType = AuctionItemCategoryData.C_TypeLv2;				
			dat.isSelected = false;								
			dat.deepth = dat.categoryType;
			dat.type = TreeListData.C_Type_Leaf;
			dat.visible = true;				
			itemsData.push(dat);
			
			dat = new AuctionItemCategoryData();
			dat.label = "汉字7";
			dat.index = 7;
			dat.mainTypeValue = 2;				
			dat.subTypeValue = 2;
			dat.categoryType = AuctionItemCategoryData.C_TypeLv2;				
			dat.isSelected = false;								
			dat.deepth = dat.categoryType;
			dat.type = TreeListData.C_Type_Leaf;
			dat.visible = true;				
			itemsData.push(dat);
			
			UCSetAuctionItemCategoryListData(itemsData);
		}
		
		public function updateUI(selectedIdx:int, fixedPrice:int)
		{
			btn_auction.enabled = selectedIdx != -1;
			btn_fixedprice_buy.enabled = (selectedIdx != -1) && (fixedPrice != 0);
			//trace("------- Page_View:updateUI" + selectedIdx);
		}
		
		
		public function UCSetAuctionItemListData( data:Array ):void
		{
			
			_auctionListContrl.updateAuctionItemListData(data);
			//updatePageText();
			updateAuctionPrice();
			
			_auctionListContrl.toggleUnitPriceShow(chk_show_unit_price.selected);
			
		}
		
		public function UCShowItemNotice(v:Boolean)
		{
			txt_noItem_right.visible = v;
		}
		
		public function UCSetAuctionItemCategoryListData( data:Array ):void
		{
			item_category_list.dataProvider = new TreeDataProvider(data);
			item_category_list.validateNow();
			item_category_list.invalidateData();
		}			
		
		function onCategoryListChange( event:ListEvent ):void
		{
			//trace("------- Page_View:onCategoryListChange" + event.index);
			
			var targetList:ScrollingList = event.target as ScrollingList;
			if (targetList != null)
			{
				targetList.invalidateData();
			}
		}
		
		public function onCategoryListItemClick(event:ListEvent):void
		{
			var list:ScrollingList = event.target as ScrollingList;
			if (list != null)
			{
				var provider:TreeDataProvider = list.dataProvider as TreeDataProvider;
				if (provider!=null)
				{
					provider.handleListItemClick(event);
					//provider.handleListItemClick( event );
					var obj:AuctionItemCategoryData = provider.requestItemAt(event.index) as AuctionItemCategoryData;
					

					if(obj.type == TreeListData.C_Type_Branch_Closed)
					{
						ExternalInterface.call( "ASViewPage_CategoryClick",  obj.mainTypeValue, 0);
					}
					else
					{
						ExternalInterface.call( "ASViewPage_CategoryClick", obj.mainTypeValue, obj.subTypeValue);
					}
			
					//TestTreeItemView();
					
					// 只要有一个展开
					for(var i:int = 0; i < provider.getRoot().length; ++i)
					{
						var dat:AuctionItemCategoryData = provider.getRoot()[i] as AuctionItemCategoryData;
						//trace("---", dat, i, provider.getRoot().length);
						
						if ((dat != null)
							&& (dat.type > TreeListData.C_Type_Leaf)
							&& ((dat.mainTypeValue != obj.mainTypeValue)) )
						{
							trace("---onCategoryListItemClick:", dat, i, provider.getRoot().length);
							dat.type = TreeListData.C_Type_Branch_Closed;							
						}
					}					
				}				
				
				list.invalidateData();
				updateUI(-1, 0);
			}
		}
		
		public function onItemListItemClick(event:ListEvent):void
		{			
			var list:ScrollingList = event.target as ScrollingList;
			if (list != null)
			{
				var provider:DataProvider = list.dataProvider as DataProvider;
				var fixedPrice:int = 0;
				if (provider!=null)
				{
					//provider.handleListItemClick( event );
					var obj:AuctionItemData = provider.requestItemAt(event.index) as AuctionItemData;
					
					if(obj.SellerID > 0)
					{
						this.auction_money.setMoney(obj.getNextAuctionPrice());
					}
					else
					{
						this.auction_money.setMoney(obj.CurrentAuctionPrice);
					}
					
					fixedPrice = obj.FixedPrice;
				}
				
				//trace("------- Page_View:ItemClick before invalidateData" + item_list.selectedIndex);
				updateUI(event.index, fixedPrice);
				list.invalidateData();
				//trace("------- Page_View:ItemClick after invalidateData" + item_list.selectedIndex);
			}
		}
		
		
		function onAuctionPriceInputChange(evt:ParamEvent):void
		{	
			var money:int=evt.param as int;
			var dp:DataProvider = item_list.dataProvider as DataProvider;
			var dat:AuctionItemData = dp[item_list.selectedIndex];			
			if(dat){
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
			sort_view.resetSort();
			_auctionListContrl.resetSortType();
			tabTitle.tf_price.text = "价格(竞拍价)"
		}
		
		function onPriceSort(evt:MouseEvent):void
		{
			var btn:Button = evt.target as Button;
			if(btn != null)
			{
				//_auctionListContrl.sortPrice(btn.selected);
				_auctionListContrl.hideOtherButton();
				var itemId = _auctionListContrl._auction_Type;
				if(chk_show_unit_price.selected)
				{
					switch(_auctionListContrl._auction_Type)
					{
					case 4:
						itemId = SINGLEPRICE;
						break;
					case 5:
						itemId = SINGLEPRICE_BUYOUT;
						break;
					}
				}
				ExternalInterface.call( "ASViewPage_ClickHeaderSort", itemId, btn.selected);
			}
		}
		
		function updateAuctionPrice():void
		{
			var dat:AuctionItemData = getCurrentSelectData();
			if(dat != null)
			{
				if(dat.SellerID > 0)
				{
					this.auction_money.setMoney(dat.getNextAuctionPrice());
				}
				else
				{
					this.auction_money.setMoney(dat.CurrentAuctionPrice);
				}
					
				updateUI(dat.AuctionID, dat.FixedPrice);
			}
		}
		
		function getCurrentSelectData():AuctionItemData
		{			
			var dat:AuctionItemData = null;
			
			if(item_list)
			{
				var dp:DataProvider = item_list.dataProvider as DataProvider;
				if(item_list.selectedIndex >= 0 && item_list.selectedIndex < dp.length)
				{
					dat = dp[item_list.selectedIndex];
				}				
			}
			return dat;
		}
		
		function onReturn():void
		{
			//resetTreeList(false);
			if(_leftListViewType == VIEW_TYPE_ADVANCED_SEARCH)
			{
				switchLeftListViewType(VIEW_TYPE_CATEGORY_LIST);
			}
			else
			{
				ExternalInterface.call("ASAuction_ReturnLastList");
				if(_leftListViewType == VIEW_TYPE_CATEGORY_LIST)
				{
					switchLeftListViewType(VIEW_TYPE_ADVANCED_SEARCH);
				}
				else if(_leftListViewType == VIEW_TYPE_RESULT_LIST)
				{
					switchLeftListViewType(VIEW_TYPE_CATEGORY_LIST);
				}
			}
		}
				
/*		function resetTreeList(v:Boolean)
		{
			search_page.visible = v;
			btn_return.visible = v;
			treeView.visible = v;
			txt_noItem.visible = v;
			tabTitle_left.visible = v;
			item_category_list.visible = !v;
			tabTitle_left.visible = v;
			txt_noItem_right.visible = false;
			filter_item_name_txt.visible = true;
		}*/
		
		public function UCUpdateTreeList(dat:Array):void
		{
			LOG('UCUpdateTreeList: ' + dat.length);
			//ExternalInterface.call("ASTrace*****************************************"+dat.length);
			treeView.UCUpdateTreeList(dat);
			switchLeftListViewType(VIEW_TYPE_RESULT_LIST);
			//resetTreeList(true);
			
			
			if(dat.length > 0 )
			{
				txt_noItem.visible = false;
			}
			else
			{
				txt_noItem.visible = true;
				//tabTitle_left.visible = false;
			}
			
		}
		
		public function TestTreeItemView()
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
			UCUpdateTreeList(itemsData);
		}
		
		public function onReset()
		{
		//	txt_noItem.visible = false;
			txt_noItem_right.visible = false;
			search_page.onReset();
			onResetListView();
			switchLeftListViewType(VIEW_TYPE_CATEGORY_LIST);
		}
		
		public function onResetListView()
		{
			var itemsData:Array = new Array();
			UCSetAuctionItemListData(itemsData);
		}
		
		public function SetSearchName(name:String):void
		{
			head_search_mc.SetSearchName(name);
		}

	}
	
}
