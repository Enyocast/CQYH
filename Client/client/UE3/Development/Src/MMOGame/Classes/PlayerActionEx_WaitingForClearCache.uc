//
// PlayerActionEx_WaitingToMove，等待清除技能缓存，发送移动
//
class PlayerActionEx_WaitingForClearCache extends PlayerActionEx_Base
	native;

var float DelayTime;
cpptext
{
	virtual FString Dump();

	virtual void Update(FLOAT DeltaTime);
	virtual void OnAction(UBOOL bOn);
	virtual UBOOL IsComplete();
	virtual UBOOL IsLatenAction();
}

defaultproperties
{
	DelayTime=-1.0
}