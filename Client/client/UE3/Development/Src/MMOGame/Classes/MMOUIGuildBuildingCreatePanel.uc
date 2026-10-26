class MMOUIGuildBuildingCreatePanel extends MMOUIBase
	native(UI);

var int _NpcId;

event InitLoad(MMOGFXPlayer pl)
{
	super.InitLoad(pl);
}

// UC->AS
event CallUpdateGuildBuildingList(GFxObject dataProvider)
{
	ActionScriptVoid("UCUpdateGuildBuildingList");
}

event CallUpdateGuildBuildingData(GFxObject dataProvider)
{
	ActionScriptVoid("UCUpdateGuildBuildingData");
}

native final function ASUpdateGuildBuildingCreateData(int buildingType);
native final function ASCreateGuildBuilding(int buildingType);

DefaultProperties
{
	IsDynamicLoad=true
	DefaultVisible=false
}
