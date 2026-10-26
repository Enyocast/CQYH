//
// 行为初始化处理接口
//
class MMOSteeringBehaviorInitProc_Hide extends object implements(IMMOSteeringBehaviorInitProc)
	native
	editinlinenew
	hidecategories(Object);

var() bool on;
var() int TargetCrowdInstanceID;

native function OnProcess(MMOSteeringBehavior behavior);


defaultproperties
{
	On=1
}
