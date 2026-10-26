class MMOUIGuildWarViewPanel extends MMOUIBase
	native(UI);

event InitLoad(MMOGFXPlayer pl)
{
	super.InitLoad(pl);
}

// UC->AS
event CallSetWindowTitle(string title)
{
	ActionScriptVoid("UCSetWindowTitle");
}

event CallUpdateGuildViewInfo(GFxObject dataProvider)
{
	ActionScriptVoid("UCUpdateGuildViewInfo");
}

event CallUpdateGuildBuildingList(GFxObject dataProvider)
{
	ActionScriptVoid("UCUpdateGuildBuildingList");
}

native final function ASMatchChallenge(int id);

DefaultProperties
{
	IsDynamicLoad=true
	DefaultVisible=false
}
