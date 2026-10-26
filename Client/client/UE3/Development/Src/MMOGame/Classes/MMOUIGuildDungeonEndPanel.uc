class MMOUIGuildDungeonEndPanel extends MMOUIBase
	native(UI);

event InitLoad(MMOGFXPlayer pl)
{
	super.InitLoad(pl);
}

// UC->AS
event CallUpdateGuildDungeonAwardList(GFxObject dataProvider)
{
	ActionScriptVoid("UCUpdateGuildDungeonAwardList");
}

event CallSetGuildDungeonBoss(string boss)
{
	ActionScriptVoid("UCSetGuildDungeonBoss");
}

native final function ASLeaveGuildDungeon();

DefaultProperties
{
	IsDynamicLoad=true
	DefaultVisible=false
}
