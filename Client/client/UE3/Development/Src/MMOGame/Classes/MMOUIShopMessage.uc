class MMOUIShopMessage extends MMOUIBase
	native(UI);

event InitLoad(MMOGFXPlayer pl)
{
	super.InitLoad(pl);
}

event CallResetShopMessage()
{
	ActionScriptVoid("UCResetShopMessage");
}

event CallUpdateShopMessageMoney(string moneyCount1,string moneyCount2)
{
	ActionScriptVoid("UCUpdateShopMessageMoney");
}

event CallSelectFilter(int shopId)
{
	ActionScriptVoid("UCSelectFilter");
}

//--------------moved-----------------
native function ASShopMsgAck(bool agree,int count);
//{
	//_NPCShop.ShopMsgAck( agree , count );
//}

native function ASShopMsgNumChange(int num);
//{
	//_NPCShop.NumChange(num);
//}

DefaultProperties
{
	IsDynamicLoad=true
	CloseOnEsc=false;
}
