class MMOUIGuildSupportPanel extends MMOUIBase
	native(UI);

event InitLoad(MMOGFXPlayer pl)
{
	super.InitLoad(pl);
}

// UC->AS
event CallUpdateGuildSupportList(GFxObject dataProvider)
{
	ActionScriptVoid("UCUpdateGuildTerritoryList");
}

native final function ASEnterTerritory(int id);

DefaultProperties
{
	IsDynamicLoad=true
	DefaultVisible=false
}
