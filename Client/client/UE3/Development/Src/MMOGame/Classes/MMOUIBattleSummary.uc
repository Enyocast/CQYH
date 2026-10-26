class MMOUIBattleSummary extends MMOUIBase
	native(UI);

enum EBattleSummary
{
	EBSUM_ScorePanel,
	EBSUM_PlayDescPanel,
};

var EBattleSummary CurTabPanel;

//var GFxObject TeamScore_tf[3];
var GFxObject TeamScore_mc;
var GFxObject TeamScore0_mc;
var GFxObject TeamScore1_mc;
var GFxObject LeaveBattle_btn;
var GFxObject HideBattle_btn;
//
var GFxObject BattleScorePanelMC;
var const int BtlScoreColumnMax;//6
var GFxObject ColTitle_tf[6];

//
var GFxObject BattleDescPanelMC;
var GFxObject WinDesc_tf;
var GFxObject PlayDesc_tf;
var GFxObject BattlePlayImg_ld;

var bool IsNeedToShow;
//
native function bool IsNeedShow();
//
native function ClearUI();
native function TryToShow();
native function NeedToShow();
native function QueryData();
native function ResetBattleSummaryData();
native function ResetBattleSummaryShow();

event ShowContent( int tabIdx )
{
	ActionScriptVoid( "UCShowContent" );
}
native function UpdateBattleSummary( int tabIdx );
native function UpdateAllTeamScore();
native function UpdateTeamScore( enumBattleTeamSide teamID );
event UCSetScore( int teamIdx, int score )
{
	ActionScriptVoid( "UCSetScore" );
}
native function UpdateBattleScoreList();
event FlashBattleScoreList( GFxObject Provider )
{
	ActionScriptVoid( "UCFlashBattleScoreList" );
}
native function UpdateBattlePlayDesc();

native function NotifyBattlePlayerChange();
native function NotifyBattleEnd();

native function LeaveBattle();

//===============================================================================================================
//===============================================================================================================
////
//function RegisterBattleSummary( MMOUIBattleSummary mc )
//{
//	_BattleSummary = mc;
//	RegisterUI( mc, class'MMOUIManager'.default.Panel_BattleSummary_BattleSummary);
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
//===============================================================================================================
//===============================================================================================================

//
defaultproperties
{
	//FriendlyName=BattleSummary
	CurTabPanel=EBSUM_ScorePanel
	BtlScoreColumnMax=6
}