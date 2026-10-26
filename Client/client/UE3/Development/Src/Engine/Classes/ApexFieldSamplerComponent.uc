/*=============================================================================
	ApexFieldSamplerComponent.uc: APEX integration.
	Copyright 2008-2011 NVIDIA Corporation.
=============================================================================*/

class ApexFieldSamplerComponent extends PrimitiveComponent
	native(ApexFieldSampler)
	hidecategories(Collision,Lighting,Physics,Rendering,Object)
	editinlinenew
	abstract;

/** Enable/Disable Field Sampler */
var(FieldSampler) bool	bEnabled;

// NVCHANGE_BEGIN: JCAO - field samplers support UE3 collision channels
/** Which types of object to apply this field sampler to */
var(FieldSampler)	const RBCollisionChannelContainer CollideWithChannels;

/** enum indicating what collision filtering channel this field sampler should be in */
var(FieldSampler)	const ERBCollisionChannel	CollisionChannel;
// NVCHANGE_END: JCAO - field samplers support UE3 collision channels

var	PrimitiveComponent	DrawComponent;

var native duplicatetransient pointer ApexAssetParams { void };
var native duplicatetransient pointer ApexAsset { physx::apex::NxApexAsset };
var native duplicatetransient pointer ApexActor { physx::apex::NxApexActor };

/** Physics scene index. */
var	native const int	PhysSceneIndex;

native function DoInitRBPhys();

native final function SetEnabled(bool enabled);

cpptext
{
	virtual void InitComponentRBPhys(UBOOL bFixed);
	virtual void TermComponentRBPhys(FRBPhysScene *InScene);

	virtual void UpdateChildComponents();

	virtual void Attach();
	virtual void Detach( UBOOL bWillReattach );

protected:
	virtual void InitFieldSampler();
	virtual void TermFieldSampler();

	virtual const char* GetApexAssetObjTypeName() { return 0; }
	virtual void SetupApexAssetParams() {}

	virtual void SetupApexActorParams(void* ActorParams) {}
	virtual void UpdateApexActor() {}

	virtual void GetTransform(FMatrix& OutTransform)
	{
		FVector OutScale;
		GetTransformAndScale(OutTransform, OutScale);
	}

	void CreateApexObjects(UBOOL bRecreate = FALSE);
	void DestroyApexObjects(UBOOL bRecreate = FALSE);

	void RecreateApexObjects()
	{
		DestroyApexObjects(TRUE);
		CreateApexObjects(TRUE);
	}
}

defaultproperties
{
	TickGroup=TG_PreAsyncWork
	
	// NVCHANGE_BEGIN: JCAO - field samplers support UE3 collision channels
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
	// NVCHANGE_END: JCAO - field samplers support UE3 collision channels

	bEnabled = TRUE
}
