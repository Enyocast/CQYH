//
// 死亡后隐藏尸体
//
class MMOStatusProc_HideBody extends Object implements(IMMOStatusProc)
	native
	editinlinenew
	hidecategories(Object);

// 如果设置了消失时间，则不会直接隐藏
var() int BodyLifeSpan;

event OnExecute(MMOActor actor)
{
	if(BodyLifeSpan > 0)
	{
		actor.LifeSpan = BodyLifeSpan;
	}
	else
	{
		//actor.SetHidden(true);
		actor.SetVisibleByAbility(false);
	}
}
native function Update(MMOActor actor);


defaultproperties
{
	BodyLifeSpan=0
}