// NVCHANGE_BEGIN: JCAO - Implement ActorFactoryApexAttractor
/*=============================================================================
	ActorFactoryApexAttractor.uc: Implement APEX Attractor Actor Factory
	Copyright 2008-2011 NVIDIA corporation..
=============================================================================*/
class ActorFactoryApexAttractor extends ActorFactory
	config(Editor)
	native(ApexFieldSampler)
	DontCollapseCategories
	dependson(ApexAttractorComponent);

/** Percentage of distance from boundary to center where fade out starts */
var(AttractorFS)	float	BoundaryFadePercentage <ClampMin=0.0 | ClampMax=1.0>;
/** Attraction radius */
var(AttractorFS)	float	Radius <ClampMin=0.0>;
/** Const attracting force */
var(AttractorFS)	float	ConstFieldStrength;
/** Field strength coefficient for inverse square part of the formula*/
var(AttractorFS)	float	SqrFieldStrength;

/** Enable/Disable Field Sampler */
var(FieldSampler) bool	bEnabled;
var(FieldSampler)	const RBCollisionChannelContainer CollideWithChannels;
var(FieldSampler)	const ERBCollisionChannel	CollisionChannel;

cpptext
{
	virtual AActor* CreateActor( const FVector* const Location, const FRotator* const Rotation, const class USeqAct_ActorFactory* const ActorFactoryData );
	virtual FString GetMenuName();
}

defaultproperties
{
	BoundaryFadePercentage = 0.1
	Radius = 0.0
	ConstFieldStrength = 0.0
	SqrFieldStrength = 0.0

	bEnabled = TRUE
	CollideWithChannels={(
        Default=True,
        Pawn=True,
        Vehicle=True,
        Water=True,
        GameplayPhysics=True,
        EffectPhysics=True,
        Untitled1=True,
        Untitled2=True,
        Untitled3=True,
        FluidDrain=True,
        Cloth=True,
        SoftBody=True
        )}

    CollisionChannel=RBCC_Nothing

	MenuName="Add ApexAttractorActor"
	NewActorClass=class'Engine.ApexAttractorActor'
}
// NVCHANGE_END: JCAO - Implement ActorFactoryApexAttractor
