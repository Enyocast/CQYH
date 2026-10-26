class MMOUIFightingScreenHint extends MMOUIBase
	native(UI);


var GFxObject TenSecCountDownMc;

//
event UCCallPlayTenSecCountDown( int realCountDownSec )
{
	ActionScriptVoid("PlayTenSecCountDown");
}

event CallASPlayLoseAnim( int leftTimeSec )
{
	ActionScriptVoid("UCShowBattleLoseMovie");
}

event CallASPlayWinAnim()
{
	ActionScriptVoid("UCShowBattleWinMovie");
}

//===============================================================================================================
//===============================================================================================================
native function ASBeforeFightTenSecCountDownEnd();
native function ASOnExitCountDownTimeOver();
//===============================================================================================================
//===============================================================================================================

//
defaultproperties
{
	//FriendlyName=FightingScreenHint
}