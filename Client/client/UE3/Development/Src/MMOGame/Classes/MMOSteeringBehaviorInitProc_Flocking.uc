//
// 行为初始化处理接口
//
class MMOSteeringBehaviorInitProc_Flocking extends object implements(IMMOSteeringBehaviorInitProc)
	native
	editinlinenew
	hidecategories(Object);

var() bool on;

native function OnProcess(MMOSteeringBehavior behavior);


defaultproperties
{
	On=1
}
