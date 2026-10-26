class MMOUIRecharge extends MMOUIBase
	native(UI)
	dependson(TypeDefine)
	config(UIVisibleMask);

//
var int _LastRechargeMoney;
var GFxObject _ConfirmBox;

event CallAsSetRechargeInfo( int idx, GFxObject itemsData )
{
	ActionScriptVoid( "UCSetRechargeType" );
}
event CallAsSetCurYuanBao( int curYuanBao )
{
	ActionScriptVoid( "UCupdateMoney" );
}
event CallAsEneableRecharge( int idx, bool isEnabled )
{
	ActionScriptVoid( "UCEneableRecharge" );
}
//native function PlayerMoneyChange( EMONEY_TYPE MoneyType, int Money, int OldMoney);

//===============================================================================================================
//===============================================================================================================
native function ASTryRecharge( int rechargeMoney );
native function ASRechargeForYuanBao();
native function ConfirmRecharge( GFxObject pMc );
native function CancelRecharge( GFxObject pMc );
//===============================================================================================================
//===============================================================================================================

DefaultProperties
{
	//FriendlyName=Vip
	IsDynamicLoad=true
	CloseOnEsc=true

	_LastRechargeMoney=0
}
