class MMOUILoginQueuePanel extends MMOUIBase
native(UI)
config(UIVisibleMask);

event CallUpdateData(int pos,int time)
{
	ActionScriptVoid("UCUpdateData");
}

event CallUCUpdateTime(string txt)
{
	ActionScriptVoid("UCUpdateTime");
}

native function ASRequestCancelLoginQueue();

DefaultProperties
{
	DefaultVisible=false
}
