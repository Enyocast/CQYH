//
// 死亡后隐藏尸体
//
class MMOStatusProc_EnabledCollision extends Object implements(IMMOStatusProc)
	native
	editinlinenew
	hidecategories(Object);

// 如果设置了消失时间，则不会直接隐藏
var() bool Enabled;

event OnExecute(MMOActor actor)
{
	if(Enabled)
	{
		actor.bEnabledCollsion = true;
	}
	else
	{
		actor.bEnabledCollsion = false;
	}
}
native function Update(MMOActor actor);

defaultproperties
{
	Enabled=true
}