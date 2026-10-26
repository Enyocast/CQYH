class MMOUIHeavenBloodPanel extends GFxObject
	native(UI)
	config(UIVisibleMask);


event CallUpdateHeavenBloodInfo(GFxObject dataProvider)
{
	ActionScriptVoid("UCUpdateHeavenBloodInfo");
}

event CallUpdateHeavenBloodLock(int nPage,int nState)
{
	ActionScriptVoid("UCUpdateBloodPanelState");
}

event CallUpdateBloodSlotState(int nPanel,int nIndex,int nState)
{
	ActionScriptVoid("UCUpdateBloodSlotState");
}