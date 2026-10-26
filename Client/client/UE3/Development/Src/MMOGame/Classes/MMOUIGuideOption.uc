class MMOUIGuideOption extends MMOUIBase
	native(UI);

event InitLoad(MMOGFXPlayer pl)
{
	super.InitLoad(pl);
}

native final function ASShowGuideOptionTips(GFxObject mc);
native final function ASHideGuideOptionTips();

native final function ASApplyGuideOption(int optionType);
native final function ASGuideOptionPanelClose();

DefaultProperties
{
	DefaultVisible=false
	CloseOnEsc=false
}
