class MMOGFXPlayer_GoldStore extends MMOGFXPlayer
	native(UI)
	config(MMOGame);

var MMOUIGoldStore _goldStorePanel;
var GFxObject ConfirmMsgBox;

function ASRegisterGoldStore(MMOUIGoldStore mc)
{
	_goldStorePanel = mc;
	RegisterUI( mc, class'MMOUIManager'.default.Panel_GoldStore);
}

native final function ASGoldStoreClickTabPage(int nIndex, int type); //moved
native final function ASFreshListView(int type);//moved
native final function ASGoldStoreBuy(GFxObject dt);//moved
native final function ASGoldStoreSell(GFxObject dt);//moved
native final function ASGoldStoreShowMyOrder(int type);//moved
native final function ASGoldStoreCancelSell(int type,int id);//moved
native final function ASBuyMoney();//moved

native final function OnGoldStoreMsg_Cancel_Ok(GFxObject mc);//moved
native final function OnGoldStoreMsg_Cancel(GFxObject mc);//moved
native final function OnGoldStoreMsg_Buy_Ok(GFxObject mc);//moved
native final function OnGoldStoreMsg_Buy_No(GFxObject mc);//moved
native final function OnGoldStoreMsg_Sell_Ok(GFxObject mc);//moved
native final function OnGoldStoreMsg_Sell_No(GFxObject mc);//moved

DefaultProperties
{
	MovieInfoStr="UI_GoldStore.UI_GoldStore"
	Priority=5
}
