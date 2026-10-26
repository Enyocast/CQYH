class MMOUIKillRecordPanel extends MMOUIBase
	native(UI)
	config(UIVisibleMask);

event CallUCSetNewRecord(bool bNew,int nType,int nCount, int nReward)
{
	ActionScriptVoid("UCSetNewRecord");
}

DefaultProperties
{
	IsDynamicLoad=true
	DefaultVisible=false
	CloseOnEsc=false
	PanelAllowFocus=false
}