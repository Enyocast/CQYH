class MMOUIVSReward extends MMOUIBase
	native(UI);

var int _TotalRwd;
var int _AvgRwd;
var int _ToTryTimes;

//
native function UpdatePanel();

//
event CallAsShowReward( string totalRwd, string avgRwd, int toTryTimes )
{
	ActionScriptVoid( "UCShowReward" );
}
//===============================================================================================================
//===============================================================================================================
final native function ASOnGetReward();
//===============================================================================================================
//===============================================================================================================

DefaultProperties
{
}
