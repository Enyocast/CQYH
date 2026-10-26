// NVCHANGE_BEGIN: JCAO - create ApexJetComponent ApexGridComponent and ApexAttractorComponent
/*=============================================================================
	ApexAttractorComponent.uc: APEX integration.
	Copyright 2008-2011 NVIDIA Corporation.
=============================================================================*/

class ApexAttractorComponent extends ApexFieldSamplerComponent 
	native(ApexFieldSampler);

/** Percentage of distance from boundary to center where fade out starts */
var(AttractorFS)	float	BoundaryFadePercentage <ClampMin=0.0 | ClampMax=1.0>;
/** Attraction radius */
var(AttractorFS)	float	Radius <ClampMin=0.0>;
/** Const attracting force */
var(AttractorFS)	float	ConstFieldStrength;
/** Field strength coefficient for inverse square part of the formula*/
var(AttractorFS)	float	SqrFieldStrength;



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

	
	BoundaryFadePercentage = 0.1
	Radius = 0.0
	ConstFieldStrength = 0.0
	SqrFieldStrength = 0.0
	
	Begin Object Class=DrawSphereComponent Name=DrawSphere0
		SphereRadius=0
	End Object

	DrawComponent = DrawSphere0
}
// NVCHANGE_END: JCAO - create ApexJetComponent ApexGridComponent and ApexAttractorComponent
