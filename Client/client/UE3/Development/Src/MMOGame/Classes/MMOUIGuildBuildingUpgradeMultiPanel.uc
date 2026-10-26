class MMOUIGuildBuildingUpgradeMultiPanel extends MMOUIBase
	native(UI);

var int _BuildingIdHigh;
var int _BuildingIdLow;

var GFxObject DeleteConfirmBox;
native function AgreeDeleteNow(GFxObject mc);
native function RefuseDeleteNow(GFxObject mc);

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

native final function ASUpdateGuildBuildingUpgradeData(int buildingIdHigh, int buildingIdLow);
native final function ASUpgradeBuildingMulti(int buildingIdHigh, int buildingIdLow);
native final function ASDestroyBuildingMulti(int buildingIdHigh, int buildingIdLow);

DefaultProperties
{
	IsDynamicLoad=true
	DefaultVisible=false
}
