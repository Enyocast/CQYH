class MMOUISpecialExpApply extends MMOUIBase
	native(UI)
	dependson(TypeDefine)
	config(UIVisibleMask);

var GFxObject _ConfirmMsgBox;
var float _CurConvertRate;

var int _TotalAppliedSpclExp;
var int _CurSpecialExpAccessable;
//
native function PlayerMoneyChange( EMONEY_TYPE MoneyType, int DeltaMoney);

native function ConfirmRechargeGameTime( GFxObject mc );
native function CancelRechargeGameTime( GFxObject mc );

native function ConfirmGetAllCurSpecialExp( GFxObject mc );
native function CancelGetAllCurSpecialExp( GFxObject mc );
//
event CallAsSetCurCost( string curCostStr )
{
	ActionScriptVoid( "UCSetCurCost" );
}

event CallAsSetCurMoney( string curMoneyStr )
{
	ActionScriptVoid( "UCSetCurMoney" );
}

event CallAsSetAnnouncement( string hintStr )
{
	ActionScriptVoid( "UCSetAnnouncement" );
}

event int CallAsGetCurApplyCnt()
{
	return ActionScriptInt( "UCGetCurApplyCnte" );
}
//===============================================================================================================
//===============================================================================================================
native function ASApplyCntChanged( int curInput );
native function ASTryToApply();
//===============================================================================================================
//===============================================================================================================

DefaultProperties
{
	//FriendlyName=Vip
	_CurConvertRate=0.2
	IsDynamicLoad=true
	CloseOnEsc=true
}
