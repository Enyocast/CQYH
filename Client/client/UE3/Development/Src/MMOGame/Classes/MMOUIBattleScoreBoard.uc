class MMOUIBattleScoreBoard extends MMOUIBase
	native(UI);

enum enumBattleTeamSide
{
	EBTLTMS_None,
	EBTLTMS_Team1,
	EBTLTMS_Team2
};

var GFxObject TeamScoreMc[2];
var GFxObject BattleTimeMC;

native function ResetShow();
native function UpdateScore( enumBattleTeamSide teamID );
event UCSetScore( int teamIdx, int score )
{
	ActionScriptVoid( "UCSetScore" );
}
//
final native function bool IsTimeCountDown();

event BeginBattleTime( int timeInSecond )
{
	ActionScriptVoid( "UCBeginTime" );
}
//
event ForceStopBattleTime()
{
	ActionScriptVoid( "UCForceStopBattleTime" );
}

//===============================================================================================================
//===============================================================================================================
native function bool SkipCaptureInputKey( string key, EInputEvent eIE, string strHoverControllerName, Vector2D ClickPosInMovieSpace);

//function RegisterBattleScoreBoard( MMOUIBattleScoreBoard mc )
//{
//	_BattleScoreBoard = mc;
//	RegisterUI( mc, class'MMOUIManager'.default.Panel_BattleSummary_BattleScoreBoard);
//}
//===============================================================================================================
//===============================================================================================================

defaultproperties
{
	//FriendlyName=BattleScoreBoard
	CloseOnEsc=false
}