// NVCHANGE_BEGIN: JCAO - create ApexJetComponent ApexGridComponent and ApexAttractorComponent
/*=============================================================================
	ApexJetComponent.uc: APEX integration.
	Copyright 2008-2011 NVIDIA Corporation.
=============================================================================*/

class ApexJetComponent extends ApexFieldSamplerComponent 
	hidecategories(PrimitiveComponent)
	native(ApexFieldSampler);

/** Radius of sphere or capsule shape INSIDE the grid */
var(Grid)	float	GridShapeRadius <ClampMin=0.0>;
/** Height of capsule shape INSIDE the grid */
var(Grid)	float	GridShapeHeight <ClampMin=0.0>;
/** Fraction of distance from boundary of the grid shape to center where jet falloff starts. Strength is 0 outside the grid.  */
var(Grid)	float	GridBoundaryFadePercentage <ClampMin=0.0 | ClampMax=1.0>;

/** Field strength */
var(FieldSampler)	float	FieldStrength;

/** Noise level in percentage of Field Strength */
var(OutOfGrid)	float	NoisePercentage <ClampMin=0.0 | ClampMax=1.0>;
/** Somewhat controls the size of the turbulent vortices caused by the noise */
var(OutOfGrid)	float	NoiseSpaceScale;
/** Somewhat controls the frequency of occurrence of the turbulent vortices caused by the noise */
var(OutOfGrid)	float	NoiseTimeScale;
/** More octaves give more turbulent noise, but increase computational time */
var(OutOfGrid)	int		NoiseOctaves <ClampMin=0>;
/** Field direction deviation angle in degrees */
var(OutOfGrid)	float	FieldDirectionDeviationAngle <ClampMin=0.0 | ClampMax=90.0>;
/** Field direction oscillation period in seconds */
var(OutOfGrid)	float	FieldDirectionOscillationPeriod <ClampMin=0.0>;
/** Field strength deviation percentage. For example, a value of 0.5 would result in the FieldStrength deviating between 50% and 150% */
var(OutOfGrid)	float	FieldStrengthDeviationPercentage <ClampMin=0.0 | ClampMax=1.0>;
/** Field strength oscillation period in seconds */
var(OutOfGrid)	float	FieldStrengthOscillationPeriod <ClampMin=0.0>;
/** Size of the toroidal field */
var(OutOfGrid)	float	FieldSize <ClampMin=0.0>;
/** Near radius ratio of the toroidal field. The field is strongest inside this radius */
var(OutOfGrid)	float	FieldNearRatio <ClampMin=0.0>;
/** Far radius ratio of the toroidal field. The field is empty outside this radius */
var(OutOfGrid)	float	FieldFarRatio <ClampMin=0.0>;
/** Center of the field where it reaches zero */
var(OutOfGrid)	float	FieldPivot <ClampMin=-0.99999 | ClampMax=0.99999>;
/** Stretch of the toroidal field along the direction, relative to Field Size. If set to 1, the cross-section of the toroid is a circle. */
var(OutOfGrid)	float	DirectionalStretch <ClampMin=0.0>;
/** Start distance ratio of blending between averaged & oscillating fields, relative to Field Size */
var(OutOfGrid)	float	AverageStartRatio <ClampMin=0.0>;
/** End distance ratio of blending between averaged & oscillating fields, relative to Field Size */
var(OutOfGrid)	float	AverageEndRatio <ClampMin=0.0>;
/** Fraction of distance from boundary of the toroidal field to center where jet falloff starts. Strength is 0 outside the toroid. */
var(OutOfGrid)	float	BoundaryFadePercentage <ClampMin=0.0 | ClampMax=1.0>;


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
	TickGroup = TG_PreAsyncWork

	FieldDirectionDeviationAngle = 0.0
	FieldDirectionOscillationPeriod = 0.0
	FieldStrength = 75.0
	FieldStrengthDeviationPercentage = 0.0
	FieldStrengthOscillationPeriod = 0.0
	
	FieldSize = 10.0
	FieldNearRatio = 1.0
	FieldFarRatio = 4.0
	FieldPivot = 0.0
	DirectionalStretch = 1.0
	AverageStartRatio = 1.0
	AverageEndRatio = 5.0
	BoundaryFadePercentage = 0.1

	GridShapeRadius = 100.0
	GridShapeHeight = 200.0
	GridBoundaryFadePercentage = 0.01
	
	NoisePercentage = 0.0
	NoiseSpaceScale = 1.0
	NoiseTimeScale = 1.0
	NoiseOctaves = 1
	

	Begin Object Class=DrawCapsuleComponent Name=DrawCapsule0
		CapsuleRadius = 100.0 //=GridShapeRadius
		CapsuleHeight = 200.0 //=GridShapeHeight
		Rotation = (Pitch = 0, Yaw = 16384, Roll = 0) //make it x upwards, instead of y
	End Object
	DrawComponent = DrawCapsule0
}
// NVCHANGE_END: JCAO - create ApexJetComponent ApexGridComponent and ApexAttractorComponent
