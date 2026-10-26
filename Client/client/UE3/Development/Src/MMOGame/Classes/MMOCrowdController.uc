//
// MMOCrowdController
//
class MMOCrowdController extends ActorComponent
	native
	editinlinenew
	hidecategories(Object)
	ClassGroup(__Crowd__);

function MMOCrowdSystem GetCrowdSys()
{
	return MMOCrowdSystem(Owner);
}


event PostBeginPlay()
{
}

event PostInitCrowdInstances()
{
}

native final function NativePostInitCrowdInstance();


defaultproperties
{
	bTickInEditor=true
	//InstanceCount=100
}