class MMOUIGuildDungeonEnterPanel extends MMOUIBase
	native(UI);

event InitLoad(MMOGFXPlayer pl)
{
	super.InitLoad(pl);
}

// UC->AS
event CallUpdateGuildDungeonData(GFxObject dataProvider)
{
	ActionScriptVoid("UCUpdateGuildDungeonData");
}

native final function ASEnterDungeon(int dungeonId);

DefaultProperties
{
	IsDynamicLoad=true
	DefaultVisible=false
}
