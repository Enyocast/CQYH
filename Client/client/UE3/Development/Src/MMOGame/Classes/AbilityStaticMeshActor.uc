class AbilityStaticMeshActor extends Actor
	native;

var int InstanceId;

var	StaticMeshComponent			MainStaticMeshComponent;
var LightEnvironmentComponent       LightEnvironment;


var transient AbilityStaticMeshComponent MeshData;
var transient float CurrentMoveTime;
var transient Actor BaseActor;
var transient Vector TargetPoint;
var transient Vector MoveSpeed;

cpptext
{
	virtual void TickSpecial( FLOAT DeltaSeconds );
}

DefaultProperties
{
	InstanceId=0
	Begin Object Class=DynamicLightEnvironmentComponent Name=MyLightEnvironment
		bEnabled=TRUE
		TickGroup=TG_DuringAsyncWork
	End Object
	Components.Add(MyLightEnvironment)
	LightEnvironment=MyLightEnvironment

	Begin Object Class=StaticMeshComponent Name=StaticMeshComponent0
		CollideActors=FALSE
		CastShadow=false
		BlockActors=FALSE
		BlockZeroExtent=FALSE
		BlockNonZeroExtent=FALSE
		BlockRigidBody=FALSE
		LightEnvironment=MyLightEnvironment
	End Object
	MainStaticMeshComponent=StaticMeshComponent0
	Components.Add(StaticMeshComponent0)

	Physics=PHYS_None
	bStatic=FALSE
	bCollideActors=false
	bBlockActors=FALSE
	bWorldGeometry=FALSE
	bCollideWorld=FALSE
	bNoEncroachCheck=TRUE
	bProjTarget=TRUE
	bUpdateSimulatedPosition=FALSE
}
