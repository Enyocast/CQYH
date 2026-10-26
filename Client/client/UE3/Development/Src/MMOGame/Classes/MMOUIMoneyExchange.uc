class MMOUIMoneyExchange extends MMOUIBase
	dependson(ServerEnum)
	native(UI)
	config(UIVisibleMask);

var int curLogPage;

event CallUpdateCurMoney( GFxObject data )
{
	ActionScriptVoid("UpdateCurMoney");
}

event CallUpdateShowLog( string str )
{
	ActionScriptVoid("UpdateShowLog");
}

event CallUpdateExchangeGold( string str )
{
	ActionScriptVoid("UpdateExchangeGold");
}

native function ASMoneyExchangeOk();
native function ASMoneyExchangeInputChange();

DefaultProperties
{
	FriendlyName=MoneyExchange
}
