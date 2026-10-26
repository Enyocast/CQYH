class MMOUIMasterCongratulationSub extends MMOUIBase
	dependson(UIKeyMapManager)
	native(UI)
	config(UIVisibleMask);

native function NativeInitOnce();
native function PostAdvance(float DeltaTime);
native function PostOnShow(bool v);

event CallSetWindowContent(string wTitle,string wContent)
{
	ActionScriptVoid("UCSetWindowContent");
}

DefaultProperties
{
	IsDynamicLoad=true
}
