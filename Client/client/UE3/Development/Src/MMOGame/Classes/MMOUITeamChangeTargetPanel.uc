class MMOUITeamChangeTargetPanel extends MMOUIBase
	native(UI)
	config(UIVisibleMask);

var int CurTab;
var int CurDifficulty;
event UpdateTargetList(GFxObject data)
{
	ActionScriptVoid("UCUpdateTargetList");
}

event UpdateDifficultyFilterDropDown(GFxObject data)
{
	ActionScriptVoid("UCUpdateDifficultyFilterDropDown");
}

//---------moved--------
native function ASClickChangeTargetOk(int targetType, int targetId);

native function ASCancelChangeTarget();

native function ASShowActivityFBTargetList();

native function ASShowActivityTargetList();

native function ASShowFBTargetList(int nDifficulty);

defaultproperties
{
	CurTab = -1;
	CurDifficulty = 0;
}