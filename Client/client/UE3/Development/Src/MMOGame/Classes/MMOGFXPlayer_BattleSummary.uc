class MMOGFXPlayer_BattleSummary extends MMOGFXPlayer
	native(UI)
	config(MMOGame);

var MMOUIBattleSummary _BattleSummary;
var MMOUIBattleScoreBoard _BattleScoreBoard;
//var MMOUIFightingScreenHint _FightingScreenHint;

event bool SkipCaptureInputKey(const string key, EInputEvent eIE, const string strHoverControllerName, Vector2D ClickPosInMovieSpace)
{
	if( (_BattleScoreBoard != none && _BattleScoreBoard.IsVisible) && (strHoverControllerName == "BtlScoreBoardPanel_mc" || strHoverControllerName == "minute_mc" 
		|| strHoverControllerName == "second_mc" || strHoverControllerName == "timeGap_mc") ){
		return false;
	}

	return super.SkipCaptureInputKey(key, eIE, strHoverControllerName, ClickPosInMovieSpace);
}

//
function RegisterBattleSummary( MMOUIBattleSummary mc )
{
	_BattleSummary = mc;
	RegisterUI( mc, class'MMOUIManager'.default.Panel_BattleSummary_BattleSummary);
}

function RegisterBattleScoreBoard( MMOUIBattleScoreBoard mc )
{
	_BattleScoreBoard = mc;
	RegisterUI( mc, class'MMOUIManager'.default.Panel_BattleSummary_BattleScoreBoard);
}

////
//function RegisterFightingScreenHint( MMOUIFightingScreenHint mc )
//{
//	_FightingScreenHint = mc;
//	RegisterUI( mc, class'MMOUIManager'.default.Panel_FightingScreenHint);
//}

//
//native function PlayTenSecCountDownAfter();
//
native function ToggleBattleSummary();
//
native function ASUpdateBattleSummary( int tabIdx );
//
native function ASLeaveBattle();
//
native function ASNotifyBattleTimesUp();
//
DefaultProperties
{
	MovieInfoStr="UI_BattleSummary.BattleSummary"
	Priority=6
}
