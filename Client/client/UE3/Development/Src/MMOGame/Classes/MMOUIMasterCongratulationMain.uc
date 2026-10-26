

class MMOUIMasterCongratulationMain extends MMOUIBase
	dependson(UIKeyMapManager)
	native(UI)
	config(UIVisibleMask);

var int currentRoleId;

native function NativeInitOnce();
native function PostAdvance(float DeltaTime);
native function PostOnShow(bool v);

event CallSetWindowContent(GFxObject data,int nRoleId)
{
	ActionScriptVoid("UCSetWindowContent");
}

event CallUCSetTargetName(string strTarget,string strCong)
{
	ActionScriptVoid("UCSetTargetName");
}

//-----------------moved------------------
native function ASSendCongratulation(int nType,int nRoleID,string strCon);

DefaultProperties
{
	IsDynamicLoad=true
}
