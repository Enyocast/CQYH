class MMOUIKillCountPanel extends MMOUIBase
	native(UI)
	config(UIVisibleMask);

event CallUCSetNewKillCount(int nType,int nCount)
{
	ActionScriptVoid("UCSetNewKillCount");
}

event CallUCCloseCountPanel()
{
	ActionScriptVoid("UCCloseCountPanel");
}

DefaultProperties
{
	IsDynamicLoad=true
	DefaultVisible=false
	CloseOnEsc=false
	PanelAllowFocus=false
}