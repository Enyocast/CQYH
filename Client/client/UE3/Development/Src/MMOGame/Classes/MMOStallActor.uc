class MMOStallActor extends Actor
	native;

var	StaticMeshComponent	StallMeshComponent;

cpptext
{
	virtual void TickSpecial(FLOAT DeltaSeconds);
}

DefaultProperties
{
	Begin Object Class=StaticMeshComponent Name=StallMeshComponent0
		CollideActors=FALSE
		CastShadow=true
		BlockActors=FALSE
		BlockZeroExtent=FALSE
		BlockNonZeroExtent=FALSE
		BlockRigidBody=FALSE
	End Object
	StallMeshComponent=StallMeshComponent0
	Components.Add(StallMeshComponent0)

	Physics=PHYS_None
	bStatic=FALSE
	bCollideActors=false
	bBlockActors=FALSE
	bWorldGeometry=FALSE
	bCollideWorld=FALSE
	bNoEncroachCheck=TRUE
	bProjTarget=TRUE
}
