// NVCHANGE_BEGIN: JCAO - US9845 Implement ActorFactoryApexGrid & ActorFactoryApexJet
/*=============================================================================
	ActorFactoryApexGrid.uc: Implement APEX Grid Actor Factory
	Copyright 2008-2011 NVIDIA corporation..
=============================================================================*/
class ActorFactoryApexGrid extends ActorFactory
	config(Editor)
	native(ApexFieldSampler)
	DontCollapseCategories
	dependson(ApexGridComponent);

/** Min resolution of grid for fluid simulation */
var(Grid)	EGridResolution		GridMinResolution;

/** Max resolution of grid for fluid simulation */
var(Grid)	EGridResolution		GridMaxResolution;
/** Grid scale */
var(Grid)	float		GridSize <DisplayName=Grid Scale>;
/** Grid size */
var(Grid)	vector		GridSize3D <DisplayName=Grid Size>;

/** Multiply the velocity of the grid */
var(Grid)	float		FluidVelocityMultiplier;
/** Clamp the velocity of the grid */
var(Grid)	float		FluidVelocityClamp;

/** Fraction of distance from boundary to center where grid falloff starts. Effect of grid is 0 outside the boundary. */
var(Grid)	float		BoundaryFadePercentage <ClampMin=0.0 | ClampMax=1.0>;
/** Boundary size as a percentage of grid size */
var(Grid)	float		BoundarySizePercentage <ClampMin=0.0 | ClampMax=1.0>;

/** Constant fluid velocity */
var(Grid)	vector		ExternalVelocity;

/** Keep the same forces but multiply the force vectors */
var(Grid)	float		FieldVelocityMultiplier;

var(Grid)	float		FieldVelocityWeight <ClampMin=0.0 | ClampMax=1.0>;

/** When enabled, the Grid velocity is automatically calculated from a change of the Grid position in time */
var(Grid)	bool		AutoVelocityEnabled;
/** If calculated Grid velocity is equal or greater than this value, then the Grid is assumed to be teleported, and the Grid velocity is kept from the last frame */
var(Grid)	float		AutoVelocityTeleportValue;
/** This value defines the maximum magnitude for a change of the Grid velocity, which is helpfull to avoid jerks in the fluid behaviour */
var(Grid)	float		AutoVelocityImpulseClamp;
/** This value controls the smoothing of the Grid velocity, it is proportional to a delay in time of the Grid velocity change, set to 0 to disable the smoothing (produce no delay) */
var(Grid)	float		AutoVelocitySmoothingTimeConstant;

/** Coefficient for mixing slip (=0) and no-slip (=1) boundary condition on rigid bodies */
var(Grid)	float		DragCoeffForRigidBody <ClampMin=0.0 | ClampMax=1.0>;
/** Viscosity is the coefficient for velocity diffusion, if it equals to 0 then there is no diffusion */
var(Grid)	float		FluidViscosity <ClampMin=0.0>;

/** Multiply the effect of rigid body angular velocity on the grid simulation */
var(RBCollision)	float		AngularVelocityMultiplier;
/** Clamp the effect of rigid body angular velocity on the grid simulation */
var(RBCollision)	float		AngularVelocityClamp;

/** Multiply the effect of rigid body linear velocity on the grid simulation */
var(RBCollision)	float		LinearVelocityMultiplier;
/** Clamp the effect of rigid body linear velocity on the grid simulation */
var(RBCollision)	float		LinearVelocityClamp;

/** Maximum number of colliding objects (affects performance) */
var(RBCollision)		int			MaxCollidingObjects <ClampMin=0>;


/** Enable/Disable Field Sampler */
var(FieldSampler) bool	bEnabled;
// NVCHANGE_BEGIN: JCAO - Grid Actor Factory support UE3 collision channels
var(FieldSampler)	const RBCollisionChannelContainer CollideWithChannels;
var(FieldSampler)	const ERBCollisionChannel	CollisionChannel;
// NVCHANGE_END: JCAO - Grid Actor Factory support UE3 collision channels

// NVCHANGE_BEGIN: JCAO - Add noise settings to Grid actor factory
/** Noise strength */
var(Noise)	float		NoiseStrength <ClampMin=0.0>;
/** Somewhat controls the size of the turbulent vortices caused by the noise */
var(Noise)	float		NoiseSpacePeriod;
/** Somewhat controls the frequency of occurrence of the turbulent vortices caused by the noise */
var(Noise)	float		NoiseTimePeriod;
/** More octaves give more turbulent noise, but increase computational time */
var(Noise)	int			NoiseOctaves <ClampMin=0>;
// NVCHANGE_END: JCAO - Add noise settings to Grid actor factory

cpptext
{
	virtual AActor* CreateActor( const FVector* const Location, const FRotator* const Rotation, const class USeqAct_ActorFactory* const ActorFactoryData );
	virtual FString GetMenuName();
}

defaultproperties
{
	GridMinResolution=EGR_16
	GridMaxResolution=EGR_32
	GridSize = 700.0
	GridSize3D = (X=1.0, Y=1.0, Z=1.0)
	FluidVelocityMultiplier = 1.0
	FluidVelocityClamp = 1000000.0
	BoundaryFadePercentage = 0.1
	BoundarySizePercentage = 1.0
	MaxCollidingObjects = 8

	ExternalVelocity = (X=0, Y=0, Z=0)

	AngularVelocityMultiplier = 1.0
	AngularVelocityClamp = 1000000.0
	LinearVelocityMultiplier = 1.0
	LinearVelocityClamp = 1000000.0

	FieldVelocityMultiplier = 1.0
	FieldVelocityWeight = 1.0

	AutoVelocityEnabled = TRUE
	AutoVelocityTeleportValue = 1000000.0
	AutoVelocityImpulseClamp = 1000000.0
	AutoVelocitySmoothingTimeConstant = 0.1
	bEnabled = TRUE

	DragCoeffForRigidBody = 0
	FluidViscosity = 0

	// NVCHANGE_BEGIN: JCAO - Grid Actor Factory support UE3 collision channels
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
	// NVCHANGE_END: JCAO - Grid Actor Factory support UE3 collision channels
	// NVCHANGE_BEGIN: JCAO - Add noise settings to Grid actor factory
	NoiseStrength = 0.0
	NoiseSpacePeriod = 0.9
	NoiseTimePeriod = 10.0
	NoiseOctaves = 1
	// NVCHANGE_END: JCAO - Add noise settings to Grid actor factory
	MenuName="Add ApexGridActor"
	NewActorClass=class'Engine.ApexGridActor'
}
// NVCHANGE_END: JCAO - US9845 Implement ActorFactoryApexGrid & ActorFactoryApexJet
