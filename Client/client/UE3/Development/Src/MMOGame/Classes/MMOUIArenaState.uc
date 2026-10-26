class MMOUIArenaState extends MMOUIBase
	native(UI);

var int PanelWidth;

final native function UpdatePanel();
final native function TryNextRound();

//设置竞技场倒计时
event CallASSetArenaTimeCntDown( int countDownTime )
{
	ActionScriptVoid( "UCSetBattleTimeLeftText" );
}

//战绩
event CallASSetArenaWin( String winCntText )
{
	ActionScriptVoid( "UCSetTipsRecordText" );
}

//
event CallASSetArenaRoundTime( String title, int countDownTime )
{
	ActionScriptVoid( "UCSetProgressText" );
}

//操作按钮设置
event CallASShowOperateBtn( String btnText, bool isToShow )
{
	ActionScriptVoid( "UCSetFightButton" );
}

//设置界面提示文字
event CallASSetPanelHintTxt( String strHint, int roundLeftTime = -1 )
{
	ActionScriptVoid( "UCSetProgressText" );
}

////
//event CallASSetArenaState( int stateType )
//{
//	ActionScriptVoid( "UCSetArenaState" );
//}

//===============================================================================================================
//===============================================================================================================
//function RegisterArenaState( MMOUIArenaState mc )
//{
//	_ArenaState = mc;
//	RegisterUI( mc, class'MMOUIManager'.default.Panel_Arena_ArenaState);
//}

native function bool SkipCaptureInputKey( string key, EInputEvent eIE, string strHoverControllerName, Vector2D ClickPosInMovieSpace);

native function ASOnFightingButtonClick();
//===============================================================================================================
//===============================================================================================================

DefaultProperties
{
	//FriendlyName=ArenaState
	PanelWidth=220
	IsDynamicLoad=true
	CloseOnEsc=false
}
