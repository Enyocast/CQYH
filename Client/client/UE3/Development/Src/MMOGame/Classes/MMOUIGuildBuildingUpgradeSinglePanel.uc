class MMOUIGuildBuildingUpgradeSinglePanel extends MMOUIBase
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
event CallUpdateGuildBuildingData(GFxObject dataProvider)
{
	ActionScriptVoid("UCUpdateGuildBuildingData");
}

native final function ASUpgradeBuildingSingle(int buildingIdHigh, int buildingIdLow, int npcId);
native final function ASDestroyBuildingSingle(int buildingIdHigh, int buildingIdLow, int npcId);

DefaultProperties
{
	IsDynamicLoad=true
	DefaultVisible=false
}
