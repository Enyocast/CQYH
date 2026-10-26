class AbilitySkeletalMeshActor extends Actor
	native;

var int InstanceId;

var	SkeletalMeshComponent			SkeletalMeshComponent;
var LightEnvironmentComponent       LightEnvironment;

DefaultProperties
{
	InstanceId=0
	Begin Object Class=DynamicLightEnvironmentComponent Name=MyLightEnvironment
		bEnabled=TRUE
		TickGroup=TG_DuringAsyncWork
	End Object
	Components.Add(MyLightEnvironment)
	LightEnvironment=MyLightEnvironment

	Begin Object Class=SkeletalMeshComponent Name=SkeletalMeshComponent0
		bUpdateSkelWhenNotRendered=FALSE
		CollideActors=FALSE
		BlockActors=FALSE
		BlockZeroExtent=FALSE
		BlockNonZeroExtent=FALSE
		BlockRigidBody=FALSE
		LightEnvironment=MyLightEnvironment
	End Object
	SkeletalMeshComponent=SkeletalMeshComponent0
	Components.Add(SkeletalMeshComponent0)

	Physics=PHYS_None
	bStatic=FALSE
	bCollideActors=false
	bBlockActors=FALSE
	bWorldGeometry=FALSE
	bCollideWorld=FALSE
	bNoEncroachCheck=TRUE
	bProjTarget=TRUE
	bUpdateSimulatedPosition=FALSE
	RemoteRole=ROLE_None
	bNoDelete=FALSE
}
