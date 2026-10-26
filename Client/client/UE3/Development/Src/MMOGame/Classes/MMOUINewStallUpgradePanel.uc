class MMOUINewStallUpgradePanel extends MMOUIBase
	config(MMOGame)
	native(UI);

var config int UpgradeCost1;
var config int UpgradeCost2;
var config int UpgradeCost3;

var int _CurTimeType;

event InitLoad(MMOGFXPlayer pl)
{
	super.InitLoad(pl);
}

function InitWidget()
{
}

// UC->AS
event CallUpdateHintText(string text)
{
	ActionScriptVoid("UCSetStallUpdateHintText");
}

event CallUpdateTimeList(GFxObject data)
{
	ActionScriptVoid("UCSetUpdateTimeListData");
}

event CallUpdateCost(int cost)
{
	ActionScriptVoid("UCSetUpdateCost");
}

// AS->UC
final native function ASOnConfirmStallUpdate();
final native function ASOnTimeListChangeSelect(int timeType);

DefaultProperties
{
	IsDynamicLoad=true
	DefaultVisible=false
	_CurTimeType=0
}
