class MMOUIVSResult extends MMOUIBase
	native(UI);

enum EVSTimeCountState
{
	EVSTimeCntSta_Invalid,
	EVSTimeCntSta_On,
	EVSTimeCntSta_Exceed
};

var int _VSResult;
var int _Damage;
var int _vsMoneyDelta;
var int _ScoreDelta;
var int _LastSec;

var bool _IsTimeCntDownShow;
var int _MsgButtonIdx;
var GFxObject _ConfirmBox;
//
native function PlayerMoneyChange( EMONEY_TYPE MoneyType, int DeltaMoney );
//
native function UpdatePanel();
//
native function NotifyByWaitQueueMsgBtnClick();
//
event CallAsShowResult( int result, int pkPoints, int score, int lastSec, bool isTodayRwdMax )
{
	ActionScriptVoid( "UCShowResult" );
}
//
event CallAsShowTimeCountDown( int isToShow, int totalSec )
{
	ActionScriptVoid( "UCShowTimeCountDown" );
}
//
event CallAsShowWaitQueueTime( bool isToShow )
{
	_IsTimeCntDownShow = isToShow;
	ActionScriptVoid( "UCShowWaitQueueTime" );
}
//===============================================================================================================
//===============================================================================================================
final native function ASOnConfirmResult();
final native function ASConfirmTimeOut();

final native function ASHideWaitQueueWnd();

final native function ASTryQuitWaitQueue();
native function ConfirmedQuitWaitQueue( GFxObject pMc );
native function CancelQuitWaitQueue( GFxObject pMc );
//===============================================================================================================
//===============================================================================================================

DefaultProperties
{
	CloseOnEsc=false
}
