class MMOUIVip extends MMOUIBase
	native(UI)
	dependson(TypeDefine)
	config(UIVisibleMask);

var int MaxVipPrivilege;
var MMOUIVip _VipPanel;

event FlashVipPrivilegeList( GFxObject Provider )
{
	ActionScriptVoid( "UCSetVIPPanelPage_Data" );
}

event CallAsSetVipItem( GFxObject itemsData )
{
	ActionScriptVoid( "UCSetVipItem" );
}

event CallAsSetVipTitle( string curVipTitle )
{
	ActionScriptVoid( "UCupdateVIPTitle" );
}

//event CallAsSetVipsHint( string vipsHint )
//{
//	ActionScriptVoid( "UCSetVipTip" );
//}

event CallAsSetCurYuanBao( string curYuanBao )
{
	ActionScriptVoid( "UCupdateMoney" );
}

event CallAsUpdateVIPShop(int vipType)
{
	ActionScriptVoid( "UCupdateVIPShop" );
}

native function PlayerMoneyChange( EMONEY_TYPE MoneyType, int DeltaMoney);

//===============================================================================================================
//===============================================================================================================
//function RegisterVIPPanel( MMOUIVip mc )
//{
//	_VipPanel = mc;
//	RegisterUI( mc, class'MMOUIManager'.default.Panel_Vip );
//}

//
native function ASBuyVipLevel( int level );
native function ASBugYuanBao();
native function ASVIPTips( GFxObject hintMc );
native function ASHideVIPTips();
native function ASVipShopClick(int type);
//===============================================================================================================
//===============================================================================================================

DefaultProperties
{
	//FriendlyName=Vip
	IsDynamicLoad=true
	CloseOnEsc=true
}
