
package UI_AuctionHouse.AS
{
	import ActionScript3.MyPanel;
	import flash.display.DisplayObject;
	import flash.external.ExternalInterface;
	import flash.events.MouseEvent;
	import ActionScript3.MyTipButtonNew;
	import scaleform.clik.core.UIComponent;
	import scaleform.clik.constants.InvalidationType;
	import scaleform.clik.controls.Button;
	import scaleform.clik.controls.CheckBox;
	import scaleform.clik.controls.RadioButton;
	import scaleform.clik.events.ButtonEvent;
	import flash.display.MovieClip;


	public class AuctionHousePanel extends MyPanel
	{
		public var tab_view:RadioButton;
		public var tab_buy:RadioButton;
		public var tab_sell:RadioButton;
				
		public var page_view:AuctionPage_View;
		public var page_buy:AuctionPage_Buy;
		public var page_sell:AuctionPage_Sell;
				
		override protected  function configUI():void 
		{		
			ShowMode="BC";
			super.configUI();			
			this.SetWindowTitle("拍卖行");
			tab_view.addEventListener(MouseEvent.CLICK, onClickPage_View );
			tab_buy.addEventListener(MouseEvent.CLICK, onClickPage_Buy );
			tab_sell.addEventListener(MouseEvent.CLICK, onClickPage_Sell );

			//ExternalInterface.call("ASRegisterAuctionView", this);
			showPageByIndex(0);
		}
		
		public function onClickPage_View(e:MouseEvent):void
		{
			showPageByIndex(0);
		}
		
		public function onClickPage_Buy(e:MouseEvent):void
		{
			showPageByIndex(1);
		}
		
		public function onClickPage_Sell(e:MouseEvent):void
		{
			showPageByIndex(2);
		}
		
		public function showPageByIndex(idx:int)
		{
			page_view.visible = (idx == 0);
			page_buy.visible = (idx == 1);
			page_sell.visible = (idx == 2);
			
			tab_view.selected = (idx == 0);
			tab_buy.selected = (idx == 1);
			tab_sell.selected = (idx == 2);
			
			//page_view.hideSortPanel();
			//page_buy.hideSortPanel();
			//page_sell.hideSortPanel();
			
			ExternalInterface.call("ASClickTabPage", idx);
		}
		
		public function UCShowTabPage(idx:int)
		{
			showPageByIndex(idx);
		}
		
		public function UCSetAuctionViewPage_SearchFilterData(dat:SearchFilterData):void
		{
			this.page_view.search_page.UCSetFilterData(dat);
		}
		
		public function UCSetAuctionViewPage_ListData( dat:Array ):void
		{
			ExternalInterface.call("ASTrace", "UCSetAuctionViewPage_ListData" + dat.length);
			page_view.UCSetAuctionItemListData(dat);
		}
		
		public function UCSetAuctionViewPage_CategoryListData( dat:Array ):void
		{
			ExternalInterface.call("ASTrace", "UCSetAuctionViewPage_CategoryListData" + dat.length);
			page_view.UCSetAuctionItemCategoryListData(dat);
		}			
		
		
		
		public function UCSetAuctionBuyPage_ListData(dat:Array):void
		{
			ExternalInterface.call("ASTrace", "UCSetAuctionBuyPage_ListData" + dat.length);
			page_buy.updateAuctionItemListData(dat);
		}
		
		public function UCSetAuctionBuyPage_FailedListData(dat:Array):void
		{
			ExternalInterface.call("ASTrace", "UCSetAuctionBuyPage_FailedListData" + dat.length);
			page_buy.updateFailedAuctionItemListData(dat);
		}
		
		
		
		public function UCSetSellingPage_ListData(dat:Array):void
		{
			ExternalInterface.call("ASTrace", "UCSetSellingPage_ListData" + dat.length);
			page_sell.UCSetSellingItemList(dat);
		}		
		
		public function UCSetSellingPage_SellInfo(dat:SellInfoData):void
		{						
			page_sell.UCSetSellInfo(dat);
		}
		
		public function UCSetAuctionViewPage_PagesInfo(curPg:int, maxPgs:int):void
		{			
			this.page_view.setPageNumber(curPg, maxPgs);
		}
		
		public function UCSetPlayerMoney(money:int):void
		{			
			this.page_view.current_money.setMoney(money);
			this.page_buy.current_money.setMoney(money);
			this.page_sell.current_money.setMoney(money);
		}
		
		public function UCResetSellItem(slotType:int):void
		{
			this.page_sell.UCResetSlot(slotType);
		}
		
		public function UCSetPlayerName(dat:Object):void
		{
			var nameDat:PlayerNameData = dat as PlayerNameData;
			
			this.page_view._auctionListContrl.setPlayerName(nameDat.PlayerID, nameDat.PlayerName);
			this.page_sell._auctionListContrl.setPlayerName(nameDat.PlayerID, nameDat.PlayerName);
			this.page_buy._auctionFailedListContrl.setPlayerName(nameDat.PlayerID, nameDat.PlayerName);
			this.page_buy._auctionListContrl.setPlayerName(nameDat.PlayerID, nameDat.PlayerName);
		}
		public function UCUpdateTreeList(dat:Array):void
		{
			this.page_view.UCUpdateTreeList(dat);
		}
		
		public function UCShowItemNotice(v:Boolean)
		{
			this.page_view.UCShowItemNotice(v);
		}
		
		public function UCSetSearchName(n:String):void
		{
			this.page_view.SetSearchName(n);
		}
		
	}
}