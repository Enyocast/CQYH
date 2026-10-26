
class MMOUILoadingBar extends GFxObject
	native(UI);
	

event CallUpdateLoadingBar(float fBar)
{
	ActionScriptVoid("UCSetLoadingProgressBar_updateProgress");
}

event CallSetLoadTips(string tips)
{
	ActionScriptVoid("UCSetLoadingProgressBar_updateTitle");
}

event CallSet_PreEnter()
{
	ActionScriptVoid("UCSet_PreEnter");
}

event CallSet_AftEnter()
{
	ActionScriptVoid("UCSet_AftEnter");
}

event CallSet_PreLeave()
{
	ActionScriptVoid("UCSet_PreLeave");
}

event CallSet_Back(GFxObject back)
{
	ActionScriptVoid("UCSet_Back");
}

final native function NativeCallSet_Back(GFxObject back);
final native function PreEnterCompleted();
final native function PreLeaveCompleted();

defaultproperties
{
	
}