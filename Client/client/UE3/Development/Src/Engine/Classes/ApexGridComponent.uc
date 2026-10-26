// NVCHANGE_BEGIN: JCAO - create ApexJetComponent ApexGridComponent and ApexAttractorComponent
/*=============================================================================
	ApexGridComponent.uc: APEX integration.
	Copyright 2008-2011 NVIDIA Corporation.
=============================================================================*/

class ApexGridComponent extends ApexFieldSamplerComponent 
	hidecategories(PrimitiveComponent)
	//showcategories(Collision)	// no point enabling this until collision groups actually work
	native(ApexFieldSampler);


struct native SGridFloatRange
{
	var() float Min, Max;
};
struct native SGridIntRange
{
	var() float Min, Max;
};

enum EGridResolution
{
	EGR_12,
	EGR_16,
	EGR_24,
	EGR_32,
	EGR_48,
	EGR_64,
	EGR_96,
	EGR_128,
};

/** Min resolution of grid for fluid simulation */
var(Grid)	EGridResolution		GridMinResolution;

/** Max resolution of grid for fluid simulation */
var(Grid)	EGridResolution		GridMaxResolution;

var deprecated 	SGridIntRange	GridXRange <DisplayName=Grid X Range>;
var deprecated 	SGridIntRange	GridYRange <DisplayName=Grid Y Range>;
var deprecated 	SGridIntRange	GridZRange <DisplayName=Grid Z Range>;

/** TBD */
var(Grid)				SGridFloatRange	UpdatesPerFrameRange;

/** Grid scale */
var(Grid)	float		GridSize <DisplayName=Grid Scale>;
/** Grid size */
var(Grid)	vector		GridSize3D <DisplayName=Grid Size>;

/** Multiply the velocity of the grid */
var(Grid)	float		FluidVelocityMultiplier;
/** Clamp the velocity of the grid */
var(Grid)	float		FluidVelocityClamp;

/** Multiply the effect of rigid body angular velocity on the grid simulation */
var(RBCollision)	float		AngularVelocityMultiplier;
/** Clamp the effect of rigid body angular velocity on the grid simulation */
var(RBCollision)	float		AngularVelocityClamp;

/** Multiply the effect of rigid body linear velocity on the grid simulation */
var(RBCollision)	float		LinearVelocityMultiplier;
/** Clamp the effect of rigid body linear velocity on the grid simulation */
var(RBCollision)	float		LinearVelocityClamp;

/** Fraction of distance from boundary to center where grid falloff starts. Effect of grid is 0 outside the boundary. */
var(Grid)	float		BoundaryFadePercentage <ClampMin=0.0 | ClampMax=1.0>;
/** Boundary size as a percentage of grid size */
var(Grid)	float		BoundarySizePercentage <ClampMin=0.0 | ClampMax=1.0>;

/** Maximum number of colliding objects (affects performance) */
var(RBCollision)		int			MaxCollidingObjects <ClampMin=0>;
/** Maximum number of heat sources (affects performance) */
/** Note: removed from UI for now, until heat sources are implemented */
var			int 		MaxHeatSources <ClampMin=0>;

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

/** Coefficient for deriving drag force from the field velocity (if equals to zero, direct field velocity is used) */
var(Grid)	float		DragCoeff <ClampMin=0.0>;

/** Coefficient for mixing slip (=0) and no-slip (=1) boundary condition on rigid bodies */
var(Grid)	float		DragCoeffForRigidBody <ClampMin=0.0 | ClampMax=1.0>;
/** Viscosity is the coefficient for velocity diffusion, if it equals to 0 then there is no diffusion */
var(Grid)	float		FluidViscosity <ClampMin=0.0>;


/** Noise strength */
var(Noise)	float		NoiseStrength <ClampMin=0.0>;
/** Somewhat controls the size of the turbulent vortices caused by the noise */
var(Noise)	float		NoiseSpacePeriod;
/** Somewhat controls the frequency of occurrence of the turbulent vortices caused by the noise */
var(Noise)	float		NoiseTimePeriod;
/** More octaves give more turbulent noise, but increase computational time */
var(Noise)	int			NoiseOctaves <ClampMin=0>;

cpptext
{
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent);

	virtual void SetTransformedToWorld();

protected:
	virtual const char* GetApexAssetObjTypeName();
	virtual void SetupApexAssetParams();

	virtual void SetupApexActorParams(void* ActorParams);
	virtual void UpdateApexActor();
}

defaultproperties
{
	TickGroup=TG_PreAsyncWork

	GridMinResolution=EGR_16
	GridMaxResolution=EGR_32
	GridXRange = (Min=32, Max=64)
	GridYRange = (Min=32, Max=64)
	GridZRange = (Min=32, Max=64)
	UpdatesPerFrameRange = (Min=0.0, Max=1.0)
	GridSize = 700.0
	GridSize3D = (X=1.0, Y=1.0, Z=1.0)
	FluidVelocityMultiplier = 1.0
	FluidVelocityClamp = 1000000.0
	BoundaryFadePercentage = 0.1
	BoundarySizePercentage = 1.0
	MaxCollidingObjects = 8
	MaxHeatSources = 4

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

	DragCoeff = 0
	DragCoeffForRigidBody = 0
	FluidViscosity = 0

	NoiseStrength = 0.0
	NoiseSpacePeriod = 0.9
	NoiseTimePeriod = 10.0
	NoiseOctaves = 1

	Begin Object Class=DrawBoxComponent Name=DrawBox0
		BoxColor=(R=64, G=70, B=255, A=255)
		BoxExtent=(X=350.0, Y=350.0, Z=350.0) //= GridSize3D * GridSize * 0.5;
	End Object
	DrawComponent=DrawBox0
}
// NVCHANGE_END: JCAO - create ApexJetComponent ApexGridComponent and ApexAttractorComponent
