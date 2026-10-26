class MMOUIRankConfigPanel extends MMOUIBase
	dependson(UIKeyMapManager)
	native(UI)
	config(UIVisibleMask);


native function OnTournamentConfigClick(INT Id);

function ASTournamentConfigClick(int Id)
{
	OnTournamentConfigClick(Id);
}

event CallUpdateRankConfigListData(GFxObject Provider)
{
	ActionScriptVoid("UCUpdateConfigListData");
}

DefaultProperties
{
	IsDynamicLoad=true
}
