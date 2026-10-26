class MMOUIGoldStore extends MMOUIBase
	native(UI);

var GFxObject ConfirmMsgBox;

var bool bDefault;
var float freshTime;
var bool bFresh;

event InitLoad(MMOGFXPlayer pl)
{
	super.InitLoad(pl);
}

event UCSetGoldStore_ListBuying(GfxObject dat)
{
	ActionScriptVoid("UCSetGoldStore_ListBuying");
}

event UCSetGoldStore_ListSelling(GfxObject dat)
{
	ActionScriptVoid("UCSetGoldStore_ListSelling");
}

event UCSetGoldStore_AddOrder(GfxObject dat)
{
	ActionScriptVoid("UCSetGoldStore_AddOrder");
}
event UCSetGoldStore_CancelSell(GfxObject dat)
{
	ActionScriptVoid("UCSetGoldStore_CancelSell");
}

event UCSetGoldStore_ListBuying_My(GfxObject dat)
{
	ActionScriptVoid("UCSetGoldStore_ListBuying_My");
}

event UCSetGoldStore_ListSelling_My(GfxObject dat)
{
	ActionScriptVoid("UCSetGoldStore_ListSelling_My");
}

event UCSetGoldStore_RecordList(GfxObject dat)
{
	ActionScriptVoid("UCSetGoldStore_RecordList");
}

event UCSetPlayerMoney(string dat)
{
	ActionScriptVoid("UCSetPlayerMoney");
}
event UCSetPlayerRealMoney(int dat)
{
	ActionScriptVoid("UCSetPlayerRealMoney");
}

event UCSetAveragePrice(int dat)
{
	ActionScriptVoid("UCSetAveragePrice");
}

event UCSetMyOrderCount(int myOrder)
{
	ActionScriptVoid("UCSetMyOrderCount");
}

event UCSetMySellCount(int count)
{
	ActionScriptVoid("UCSetMySellCount");
}

event UCResetGoldStorePage()
{
	ActionScriptVoid("UCResetGoldStorePage");
}

event UCSetNoticeInfo(string info, string explan, string record,string orderExplan)
{
	ActionScriptVoid("UCSetNoticeInfo");
}

event UCShowPageByIndex(int idx)
{
	ActionScriptVoid("UCShowPageByIndex");
}

event CallUCSetDefaultPrice(int price,int count)
{
	ActionScriptVoid("UCSetDefaultPrice");
}

event CallUCSetGoldStore_OrderList(GfxObject dat)
{
	ActionScriptVoid("UCSetGoldStore_OrderList");
}

//---------------------moved-------------------------
native final function ASGoldStoreClickTabPage(int nIndex, int type); 
native final function ASFreshListView(int type);
native final function ASGoldStoreBuy(GFxObject dt);
native final function ASGoldStoreSell(GFxObject dt);
native final function ASGoldStoreShowMyOrder(int type);
native final function ASGoldStoreCancelSell(int index);
native final function ASBuyMoney();
native final function ASSoldMoney();

native final function OnGoldStoreMsg_Cancel_Ok(GFxObject mc);
native final function OnGoldStoreMsg_Cancel(GFxObject mc);
native final function OnGoldStoreMsg_Buy_Ok(GFxObject mc);
native final function OnGoldStoreMsg_Buy_No(GFxObject mc);
native final function OnGoldStoreMsg_Sell_Ok(GFxObject mc);
native final function OnGoldStoreMsg_Sell_No(GFxObject mc);

native final function ASOnExchangeTypeChanged(int type);

native final function ASOnExchangeTypeClick(int type);

native function BeforeViewUpdate(float DeltaTime);

native final function NativeSoldMoney();
native final function SoldMoneySuccess();

DefaultProperties
{
	IsDynamicLoad=true
	CloseOnEsc=true;
}
