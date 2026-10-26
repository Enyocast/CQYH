class MMOGFXPlayer_Auction extends MMOGFXPlayer
	dependson(MMOUIBase)
	native(UI)
	config(MMOGame);

var MMOUIAuctionView _auctionPanel;

function ASRegisterAuctionView(MMOUIAuctionView mc)
{
	_auctionPanel = mc;
	RegisterUI( mc, class'MMOUIManager'.default.Panel_AuctionView);
}

// 搜索拍卖信息
native final function ASSearch(GFxObject dt);//moved
native final function ASSearch_ResetFilter();//moved

// 标签名发生变化
native final function ASClickTabPage(int idx);//moved


// 购买页面
native final function ASBuyPage_AuctionClick(int dwAuctionID, int price,int msgType);//moved
native final function ASBuyPage_AuctionFixedPriceClick(int dwAuctionID, int price);//moved

native final function ASBuyPage_AuctionFailedClick(int dwAuctionID, int price,int msgType);//moved
native final function ASBuyPage_AuctionFailedFixedPriceClick(int dwAuctionID, int price);//moved


// 出售页面
native final function ASSellPage_CancelSellClick(int dwAuctionID);//moved
native final function ASSellPage_AuctionSellItemClick(GFxObject dt);//moved


// 浏览页面
native final function ASViewPage_ClickHeaderSort(int colIdx, bool descending);//moved
native final function ASViewPage_AuctionClick(int dwAuctionID, int price,int msgType);//moved
native final function ASViewPage_AuctionFixedPriceClick(int dwAuctionID, int price);//moved
native final function ASViewPage_CategoryClick(BYTE mainType, BYTE subType);//moved


// page
native final function ASViewPage_PrevPageClick(int pgNum);//moved
native final function ASViewPage_NextPageClick(int pgNum);//moved
native final function ASViewPage_GotoPageClick(int pgNum);//moved

//close的时候取消物品锁定
native function ASOnPanelClose( string PanelName );//moved

native final function ASTreeListPage_ClickItem(int itemId);//moved
native final function ASAuction_Fresh();
native final function ASAuction_SearchItem(string itemName);//moved

native final function ASAuction_FilterTreeList(int type,GFxObject dt);//moved

native final function ASAuction_ReturnLastList();//moved
DefaultProperties
{
	MovieInfoStr="UI_AuctionHouse.UI_AuctionHouse"
	Priority=5
}
