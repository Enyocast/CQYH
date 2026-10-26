class MMOUIGuildWelfareUpgradePanel extends MMOUIBase
	native(UI);

event InitLoad(MMOGFXPlayer pl)
{
	super.InitLoad(pl);
}

// UC->AS
event CallUpdateGuildWelfareData(GFxObject dataProvider)
{
	ActionScriptVoid("UCUpdateGuildWelfareData");
}

native final function ASUpgradeWelfare(int id);

DefaultProperties
{
	IsDynamicLoad=true
	DefaultVisible=false
}
