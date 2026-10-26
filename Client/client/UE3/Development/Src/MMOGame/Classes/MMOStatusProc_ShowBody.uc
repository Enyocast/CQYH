//
// ËÀÍöºóÒş²ØÊ¬Ìå
//
class MMOStatusProc_ShowBody extends Object implements(IMMOStatusProc)
	native
	editinlinenew
	hidecategories(Object);


event OnExecute(MMOActor actor)
{
	//actor.SetHidden(false);
	actor.SetVisibleByAbility(true);
}
native function Update(MMOActor actor);


defaultproperties
{

}