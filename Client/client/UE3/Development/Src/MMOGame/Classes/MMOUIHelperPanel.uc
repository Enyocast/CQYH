class MMOUIHelperPanel extends MMOUIBase
	native(UI);

var string _TargetPanelName;

event InitLoad(MMOGFXPlayer pl)
{
	super.InitLoad(pl);
}

event CallUpdateHelperList(GFxObject dataProvider)
{
	ActionScriptVoid("UCUpdateHelperList");
}

event CallUpdateHelperDetail(GFxObject dataProvider)
{
	ActionScriptVoid("UCUpdateHelperDetail");
}

native final function ASUpdateHelperDetail(int baseClass, int subClass);

DefaultProperties
{
	IsDynamicLoad=true
	DefaultVisible = false
}
