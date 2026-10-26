
#include "EnginePrivate.h"
#include "EngineMeshClasses.h"
#include "EngineParticleClasses.h"
#include "EnginePhysicsClasses.h"

#if WITH_APEX_PARTICLES

#include "ParticleEmitterInstances_Apex.h"
#include "NvApexScene.h"
#include "NvApexRender.h"
#include "NvApexCommands.h"
#include "UnNovodexSupport.h"
#include "NvApexRenderClasses.h"
// NVCHANGE_BEGIN: JCAO - Fix DE5806 Crash when clicking on a Required module in Cascade
#include "ApexEmitterNotifier.h"
// NVCHANGE_END: JCAO - Fix DE5806 Crash when clicking on a Required module in Cascade

#if WITH_APEX_EDITOR
#include "PxEditorWidgetManager.h"
#include "NxParamUtils.h"
#endif


IMPLEMENT_PARTICLEEMITTERINSTANCE_TYPE(FParticleApexEmitterInstance);

/** Constructor	*/
FParticleApexEmitterInstance::FParticleApexEmitterInstance(class UParticleModuleTypeDataApex &TypeData) :
	ApexTypeData(TypeData)
{
	// NVCHANGE_BEGIN: LRR - Update APEX Scene with the view and projection matrices when in cascade
	ViewMatrix.SetIdentity();
	ProjectionMatrix.SetIdentity();
	FOV = 90.0f;
	SizeX = 800.0f;
	SizeY = 600.0f;
	// NVCHANGE_END: LRR - Update APEX Scene with the view and projection matrices when in cascade

	ApexEmitter  = NULL;
	CascadeScene = NULL;
	// NVCHANGE_BEGIN: JCAO - Fix safe release Apex Emitter
	ApexSceneHolder = NULL;
	DeferredActions = 0;
	// NVCHANGE_END: JCAO - Fix safe release Apex Emitter
}

void FParticleApexEmitterInstance::Init()
{
	FParticleEmitterInstance::Init();

	// NVCHANGE_BEGIN: JCAO - Fix DE5813 Emitter Loops property can't be set to anything other than 1 in APEX Required Module
	//this have to be setted to 1 in order to HasCompleted to be called
	//CurrentLODLevel->RequiredModule->EmitterLoops = 1;
	// NVCHANGE_END: JCAO - Fix DE5813 Emitter Loops property can't be set to anything other than 1 in APEX Required Module
	//bKillOnCompleted = TRUE;

	InitDependencies(FALSE);
}

/** Destructor	*/
FParticleApexEmitterInstance::~FParticleApexEmitterInstance(void)
{
	RemovedFromScene();
	// NVCHANGE_BEGIN: JCAO - Fix safe release Apex Emitter
	ApexSceneHolder = NULL;
	DeferredActions = 0;
	// NVCHANGE_END: JCAO - Fix safe release Apex Emitter
}

UBOOL FParticleApexEmitterInstance::HasCompleted()
{
	// NVCHANGE_BEGIN: JCAO - Fix DE5811 & DE5812: Emitter Duration property and Emitter Delay property have no effect in APEX Required Module
	// If it hasn't finished looping or if it loops forever, not completed.
	UParticleLODLevel* LODLevel = SpriteTemplate->GetCurrentLODLevel(this);
	check(LODLevel);
	if ((LODLevel->RequiredModule->EmitterLoops == 0) || 
		(SecondsSinceCreation < (EmitterDuration * LODLevel->RequiredModule->EmitterLoops)))
	{
		return FALSE;
	}
	// NVCHANGE_END: JCAO - Fix DE5811 & DE5812: Emitter Duration property and Emitter Delay property have no effect in APEX Required Module

	if (ApexEmitter == NULL)
	{
		return TRUE;
	}

	if (ApexEmitter->IsEmitting())
	{
		return FALSE;
	}

	// If there are active particles, not completed
	if (ActiveParticles > 0)
	{
		return FALSE;
	}

	return TRUE;
}


void FParticleApexEmitterInstance::Tick(FLOAT DeltaTime, UBOOL bSuppressSpawning)
{
	// NVCHANGE_BEGIN: JCAO - If no hardware acceleration, turbulence effects won't be created.
	if ( GEngine->GetPhysXLevel() == 0 )
	{
		return;
	}
	// NVCHANGE_END: JCAO - If no hardware acceleration, turbulence effects won't be created.

	{
		SCOPE_LOCK_REF(CriticalSection);

		// NVCHANGE_BEGIN: JCAO - Fix safe release Apex Emitter
		if(DeferredActions & DEFERRED_RELEASE_EMITTER)
		{
			if(ApexEmitter)
			{
				ApexEmitter->release();
				ApexEmitter = NULL;
			}
			DeferredActions &= ~DEFERRED_RELEASE_EMITTER;
		}

		if(DeferredActions & DEFERRED_RELEASE_SCENE)
		{
			if(CascadeScene)
			{
				DestroyRBPhysScene(CascadeScene);
				CascadeScene = NULL;
			}
			DeferredActions &= ~DEFERRED_RELEASE_SCENE;
		}
		// NVCHANGE_END: JCAO - Fix safe release Apex Emitter
	}

	if (!Component)
	{
		return;
	}

	// NVCHANGE_BEGIN: JCAO - Fix DE5811 & DE5812: Emitter Duration property and Emitter Delay property have no effect in APEX Required Module
	{
		SCOPE_LOCK_REF(CriticalSection);

		// NVCHANGE_BEGIN: JCAO - Fix safe release Apex Emitter
		if (ApexEmitter == NULL)
		{
			FIApexScene  *ApexScene = NULL;

			if(CascadeScene == NULL)
			{
				FRBPhysScene *InRBPhysScene = GetScene();
				ApexScene     = InRBPhysScene ? InRBPhysScene->ApexScene : 0;
			}
			else
			{
				ApexScene = ApexSceneHolder;
			}

			if(ApexScene)
			{
				UApexGenericAsset* EmitterAsset = ApexTypeData.GetApexLODEmitterAsset(CurrentLODLevelIndex);
				if( EmitterAsset && EmitterAsset->MApexAsset )
				{
					ApexEmitter = ApexScene->CreateApexEmitter(EmitterAsset->MApexAsset,Component->LocalToWorld);
					if ( ApexEmitter )
					{
						InitDependencies(TRUE);
						ApexSceneHolder = ApexEmitter->GetApexScene();
					}
				}
			}
		}

		if ( ApexEmitter && ApexEmitter->NeedsRebuild() )
		{
			FIApexScene *scene = ApexEmitter->GetApexScene();
			check(scene);
			// NVCHANGE_BEGIN: JCAO - Apex Emitter Asset work with LODs
			UApexGenericAsset* EmitterAsset = ApexTypeData.GetApexLODEmitterAsset(CurrentLODLevelIndex);
			if(EmitterAsset && EmitterAsset->MApexAsset)
			// NVCHANGE_END: JCAO - Apex Emitter Asset work with LODs
			{
				FIApexAsset *aa = EmitterAsset->MApexAsset;
				check(aa);
				if ( aa->IsValidForActorCreation(scene) )
				{
					DeferredActions |= DEFERRED_RELEASE_EMITTER;
				}
			}
		}
		// NVCHANGE_END: JCAO - Fix safe release Apex Emitter

		UParticleLODLevel* LODLevel = SpriteTemplate->GetCurrentLODLevel(this);
		check(LODLevel);

		// Handle EmitterTime setup, looping, etc.
		FLOAT EmitterDelay = Tick_EmitterTimeSetup(DeltaTime, LODLevel);

		bool bNeedEmit = false;
		// If not suppressing spawning...
		if (!bHaltSpawning && !bSuppressSpawning && (EmitterTime >= 0.0f))
		{
			if ((LODLevel->RequiredModule->EmitterLoops == 0) || 
				(LoopCount < LODLevel->RequiredModule->EmitterLoops) ||
				(SecondsSinceCreation < (EmitterDuration * LODLevel->RequiredModule->EmitterLoops)))
			{
				bNeedEmit = true;
			}
		}

		if ( ApexEmitter )
		{
			// NVCHANGE_BEGIN: JCAO - DE6060 fix Apex particle rendering crash in UE3 and Fix Emitter only display once in Cascade when Emitter loop set 1
			if(!ApexEmitter->IsEmpty())
			{
				if ( ActiveParticles == 0 )
					ActiveParticles = 1;
			}
			else
			{
				ActiveParticles = 0;
			}
			// NVCHANGE_END: JCAO - DE6060 fix Apex particle rendering crash in UE3 and Fix Emitter only display once in Cascade when Emitter loop set 1

			ApexEmitter->SetPose(Component->LocalToWorld);
			ApexEmitter->SetSpawning(bNeedEmit);
		}

		// Calculate bounding box and simulate velocity.
		UpdateBoundingBox(DeltaTime);
	}

	//Super::Tick(DeltaTime, bSuppressSpawning); // TODO: should we just override any default behavior?
	if(GIsEditor == TRUE && GIsGame == FALSE && CascadeScene) //cascade mode
	{
		// NVCHANGE_BEGIN: LRR - Update APEX Scene with the view and projection matrices when in cascade
		FIApexScene* ApexScene = CascadeScene->ApexScene;
		if( ApexScene )
		{
			ApexScene->UpdateProjection( ProjectionMatrix, FOV, SizeX, SizeY, GNearClippingPlane );
			ApexScene->UpdateView( ViewMatrix );
		}
		// NVCHANGE_END: LRR - Update APEX Scene with the view and projection matrices when in cascade

		AWorldInfo* Info = (AWorldInfo*)(AWorldInfo::StaticClass()->GetDefaultObject());
		FLOAT MaxDeltaTime = Info->MaxPhysicsDeltaTime;
		FLOAT PhysXDT = ::Min(DeltaTime, MaxDeltaTime);
		TickRBPhysScene(CascadeScene, PhysXDT);
		WaitRBPhysScene(CascadeScene);
	}

	// 'Reset' the emitter time so that the delay functions correctly
	EmitterTime += CurrentDelay;
	// NVCHANGE_END: JCAO - Fix DE5811 & DE5812: Emitter Duration property and Emitter Delay property have no effect in APEX Required Module
}

FRBPhysScene *FParticleApexEmitterInstance::GetScene(void)
{
	FRBPhysScene* Scene = NULL;

	//check that we are really in Cascade
	UBOOL bIsCascade = (Component->GetClass()->GetName() == TEXT("CascadeParticleSystemComponent"));

	if(GIsEditor == TRUE && GIsGame == FALSE && bIsCascade) //cascade mode
	{
		if(!CascadeScene)
		{
			AWorldInfo *pInfo = (AWorldInfo*)AWorldInfo::StaticClass()->GetDefaultObject();
			check(pInfo);
			FVector Gravity(0, 0, pInfo->DefaultGravityZ * pInfo->RBPhysicsGravityScaling);
			CascadeScene = CreateRBPhysScene(Gravity);
			check(CascadeScene);

			NxPlaneShapeDesc PlaneShape;
			NxActorDesc Actor;
			PlaneShape.normal.set(0.0f, 0.0f, 1.0f);
			PlaneShape.d = -5.0f;
			FRBCollisionChannelContainer CollidesWith(0);
			CollidesWith.SetChannel(RBCC_Default, TRUE);
			PlaneShape.groupsMask = CreateGroupsMask(RBCC_Default, &CollidesWith);
			Actor.shapes.pushBack(&PlaneShape);
			NxScene* SceneNx = CascadeScene->GetNovodexPrimaryScene();
			check(SceneNx);
			SceneNx->createActor(Actor);
		}
		Scene = CascadeScene;
	
	}
	else
	{
		check(GWorld && GWorld->RBPhysScene);
		Scene = GWorld->RBPhysScene;
	}
	return Scene;
}

FDynamicEmitterDataBase* FParticleApexEmitterInstance::GetDynamicData(UBOOL bSelected)
{
	// NVCHANGE_BEGIN: JCAO - Fix DE5811 & DE5812: Emitter Duration property and Emitter Delay property have no effect in APEX Required Module
	UParticleLODLevel* LODLevel = SpriteTemplate->GetCurrentLODLevel(this);
	if (IsDynamicDataRequired(LODLevel) == FALSE)
	{
		return NULL;
	}
	// NVCHANGE_END: JCAO - Fix DE5811 & DE5812: Emitter Duration property and Emitter Delay property have no effect in APEX Required Module

	// NVCHANGE_BEGIN: JCAO - DE6060 fix Apex particle rendering crash in UE3 and Fix Emitter only display once in Cascade when Emitter loop set 1
	if( ApexEmitter == NULL )
	{
		return NULL;
	}

	if( ApexEmitter && ApexEmitter->IsEmpty() )
	{
		return NULL;
	}
	// NVCHANGE_END: JCAO - DE6060 fix Apex particle rendering crash in UE3 and Fix Emitter only display once in Cascade when Emitter loop set 1
	// NVCHANGE_BEGIN: JCAO - Fix safe release Apex Emitter
	if( DeferredActions & DEFERRED_RELEASE_EMITTER )
	{
		return NULL;
	}
	// NVCHANGE_END: JCAO - Fix safe release Apex Emitter

	FDynamicEmitterDataBase*ret = NULL;
	FRBPhysScene *InRBPhysScene = GetScene();
	FIApexScene  *ApexScene     = InRBPhysScene ? InRBPhysScene->ApexScene : 0;
	if(ApexScene)
	{
		FDynamicApexEmitterDataBase *EmitterDataBase = new FDynamicApexEmitterDataBase(CurrentLODLevel->RequiredModule,ApexScene,this);
		ret = EmitterDataBase;
	}
	return ret;
}

FDynamicApexEmitterDataBase::FDynamicApexEmitterDataBase(const UParticleModuleRequired *required,FIApexScene *apexScene,FParticleApexEmitterInstance *emitterInstance) : FDynamicEmitterDataBase(required)
{
	ApexScene = apexScene;
	EmitterInstance = emitterInstance;
}

FDynamicApexEmitterDataBase::~FDynamicApexEmitterDataBase(void)
{
}

// Render thread only draw call
INT FDynamicApexEmitterDataBase::Render(FParticleSystemSceneProxy* Proxy, FPrimitiveDrawInterface* PDI,const FSceneView* View,UINT DPGIndex)
{
	if ( !View->IsPerspectiveProjection() ) return 0;
	if ( !EmitterInstance ) return 0;

	SCOPE_LOCK_REF(EmitterInstance->GetCriticalSection());


	// NVCHANGE_BEGIN: LRR - Update APEX Scene with the view and projection matrices
	{
		EmitterInstance->ProjectionMatrix = View->ProjectionMatrix;
		EmitterInstance->FOV = 90.0f; // TODO: where can I find this?
		EmitterInstance->SizeX = View->SizeX;
		EmitterInstance->SizeY = View->SizeY;
		EmitterInstance->ViewMatrix = View->ViewMatrix;
	}
	// NVCHANGE_END: LRR - Update APEX Scene with the view and projection matrices

	FApexEmitter *emitter = EmitterInstance->GetApexEmitter();
	if ( emitter && !emitter->IsEmpty() )
	{
		physx::apex::NxUserRenderer *Renderer = GApexRender->CreateDynamicRenderer( PDI,FALSE,FALSE,FALSE,View,DPGIndex);

		ApexSpriteSubUV subUV;
		subUV.Blend			= this->EmitterInstance->ApexTypeData.SubUVBlend;
		subUV.FrameCount	= this->EmitterInstance->ApexTypeData.SubUVCount;
		subUV.StartFrame	= this->EmitterInstance->ApexTypeData.SubUVStart;
		subUV.Width			= this->EmitterInstance->ApexTypeData.SubImagesHorizontal;
		subUV.Height		= this->EmitterInstance->ApexTypeData.SubImagesVertical;
		GApexRender->SetApexSpriteSubUV(subUV);

		emitter->Render(*Renderer);
		EmitterInstance->ActiveParticles = GApexRender->getParticleCount(true);

		GApexRender->ReleaseDynamicRenderer(Renderer);
	}
	return 1;
}

const FMaterialRenderProxy*		FDynamicApexEmitterDataBase::GetMaterialRenderProxy(UBOOL bSelected)
{
	return NULL;
}

// [ming@snda
#if NV_ENABLE_LOW_RES_PARTICLES
// NVCHANGE_BEGIN: Add Particle Downsampling & Blur
UBOOL FDynamicApexEmitterDataBase::IsSoftParticles() const
{
	if (EmitterInstance)
	{
		UMaterialInterface* MaterialInterface = EmitterInstance->CurrentMaterial;
		if (MaterialInterface)
		{
			const UMaterial* Material = MaterialInterface->GetMaterial();
			if (Material)
			{
				const FMaterial* MaterialResource = Material->MaterialResources[0];
				if (MaterialResource)
				{
					UBOOL UsesAlphaBlending = (MaterialResource->GetBlendMode() == BLEND_Translucent);
					UBOOL UsesSoftwareDepthTest = (MaterialResource->GetUsesSceneDepth() || MaterialResource->GetUsesSceneColor());
					return UsesAlphaBlending && UsesSoftwareDepthTest;
				}
			}
		}
	}
	return FALSE;
}

BYTE FDynamicApexEmitterDataBase::DownsampleFactor() const
{
	if (EmitterInstance)
	{
		UMaterialInterface* MaterialInterface = EmitterInstance->CurrentMaterial;
		if (MaterialInterface)
		{
			const UMaterial* Material = MaterialInterface->GetMaterial();
			if (Material)
			{
				switch (Material->ParticleDownsampling)
				{
					case PDS_Quarter:	return 4;	break;
					case PDS_Half:		return 2;	break;
					case PDS_Full:
					default:			return 0;	break;
				}
			}
		}
	}
	return 0;
}

FLOAT FDynamicApexEmitterDataBase::BlurRadius() const
{
	if (EmitterInstance)
	{
		UMaterialInterface* MaterialInterface = EmitterInstance->CurrentMaterial;
		if (MaterialInterface)
		{
			const UMaterial* Material = MaterialInterface->GetMaterial();
			if (Material)
			{
				return Material->ParticleBlurRadius;
			}
		}
	}
	return 0.f;
}
// NVCHANGE_END: Add Particle Downsampling & Blur
#endif	// NV_ENABLE_LOW_RES_PARTICLES
// ming@snda]

/**
 *	Called during FSceneRenderer::InitViews for view processing on scene proxies before rendering them
 *  Only called for primitives that are visible and have bDynamicRelevance
 *
 *	@param	Proxy			The 'owner' particle system scene proxy
 *	@param	ViewFamily		The ViewFamily to pre-render for
 *	@param	VisibilityMap	A BitArray that indicates whether the primitive was visible in that view (index)
 *	@param	FrameNumber		The frame number of this pre-render
 */
void FDynamicApexEmitterDataBase::PreRenderView(FParticleSystemSceneProxy* Proxy, const FSceneViewFamily* ViewFamily, const DWORD VisibilityMap, INT FrameNumber)
{
}

/** Returns the source data for this particle system */
const FDynamicEmitterReplayDataBase& FDynamicApexEmitterDataBase::GetSource(void) const
{
	return ReplaySource;
}

/** Release the resource for the data */
void FDynamicApexEmitterDataBase::ReleaseResource(void)
{

}

void FParticleApexEmitterInstance::UpdateBoundingBox(FLOAT DeltaTime)
{
	if ( ApexEmitter && !ApexEmitter->IsEmpty() )
	{
		ApexEmitter->UpdateBoundingBox(ParticleBoundingBox);
		ParticleBoundingBox.IsValid = TRUE;
	}
	else
	{
		ParticleBoundingBox.Min = Component->LocalToWorld.GetOrigin();
		ParticleBoundingBox.Max = Component->LocalToWorld.GetOrigin();
		ParticleBoundingBox.IsValid = TRUE;
	}

	// NVCHANGE_BEGIN: Add Opacity Shadows
#if NV_OPACITY_SHADOWS
	if ( ApexEmitter && !ApexEmitter->IsEmpty() )
	{
		ApexEmitter->UpdateShadowBoundingBox(ShadowBoundingBox);
		ShadowBoundingBox.IsValid = TRUE;
	}
	else
	{
		ShadowBoundingBox = ParticleBoundingBox;
	}
#endif
	// NVCHANGE_END: Add Opacity Shadows
}

void FParticleApexEmitterInstance::RemovedFromScene()
{
	// NVCHANGE_BEGIN: JCAO - Fix DE5806 Crash when clicking on a Required module in Cascade
	if( ApexTypeData.EmitterNotifier )
	{
		ApexTypeData.EmitterNotifier->RemoveEmitterInstance();
	}
	// NVCHANGE_END: JCAO - Fix DE5806 Crash when clicking on a Required module in Cascade
	if ( ApexEmitter )
	{
		ApexEmitter->release();
		ApexEmitter = NULL;
	}

	if(CascadeScene)
	{
		DestroyRBPhysScene(CascadeScene);
		CascadeScene = NULL;
	}
	// NVCHANGE_BEGIN: JCAO - Fix safe release Apex Emitter
	ActiveParticles = 0;
	// NVCHANGE_END: JCAO - Fix safe release Apex Emitter
	
	// NVCHANGE_BEGIN: DMS - Ensure the rendering thread is done with the emitter
	FlushRenderingCommands();
	// NVCHANGE_END: DMS - Ensure the rendering thread is done with the emitter
}

UBOOL  FParticleApexEmitterInstance::OnPostPropertyEdit(NxParameterized::Interface *iface,NxParameterized::Handle &handle,const char *tweakable)
{
	const NxParameterized::Definition *pd = handle.parameterDefinition();
	const char *name = pd->name();
	if ( strcmp(name,"subUV_Blend") == 0 )
	{
		bool v;
		handle.getParamBool(v);
		ApexTypeData.SubUVBlend = v ? TRUE : FALSE;
	}
	else if ( strcmp(name,"subUV_Start") == 0)
	{
		physx::PxU32 v;
		handle.getParamU32(v);
		ApexTypeData.SubUVStart = (INT)v;
	}
	else if ( strcmp(name,"subUV_Count") == 0 )
	{
		physx::PxU32 v;
		handle.getParamU32(v);
		ApexTypeData.SubUVCount = (INT)v;

	}
	else if ( strcmp(name,"Sub_Images_Horizontal")==0)
	{
		physx::PxU32 v;
		handle.getParamU32(v);
		ApexTypeData.SubImagesHorizontal = (INT)v;

	}
	else if ( strcmp(name,"Sub_Images_Vertical") == 0 )
	{
		physx::PxU32 v;
		handle.getParamU32(v);
		ApexTypeData.SubImagesVertical = (INT)v;
	}
	else
	{
		check(0);
	}
	ApexTypeData.MarkPackageDirty();
	return TRUE;
}

UBOOL  FParticleApexEmitterInstance::NotifyEditorClosed(NxParameterized::Interface *iface)
{
	return TRUE;
}

void FParticleApexEmitterInstance::InitDependencies(UBOOL IsChangeEvent)
{
	// This method makes sure that the UE3 object 'ApexTypeData' is properly assigned the current sprite material or static meshes associated with this
	// particle system.
	// NVCHANGE_BEGIN: JCAO - Apex Emitter Asset work with LODs
	UApexGenericAsset* IOFXAsset = ApexTypeData.GetApexLODIOFXAsset(CurrentLODLevelIndex);
	if( IOFXAsset && IOFXAsset->MApexAsset )
	{
		if ( ApexTypeData.IsSprite() && (IsChangeEvent || ApexTypeData.Materials.Num() == 0) )
		{
			CurrentMaterial = IOFXAsset->MApexAsset->GetCurrentMaterial();
			if ( CurrentMaterial )
			{
				ApexTypeData.Materials.Empty();
				ApexTypeData.Materials.AddItem(CurrentMaterial);
				Component->bIsViewRelevanceDirty = TRUE;
				Component->bRecacheViewRelevance = TRUE;
				Component->CacheViewRelevanceFlags(NULL);
			}
		}
		else if ( !ApexTypeData.IsSprite() && (IsChangeEvent || ApexTypeData.Meshes.Num() == 0) )
		{
			ApexTypeData.Meshes.Empty();
			physx::PxU32 MeshCount = IOFXAsset->MApexAsset->GetMeshCount();
			for (physx::PxU32 i=0; i<MeshCount; i++)
			{
				UStaticMesh *mesh = IOFXAsset->MApexAsset->GetMesh(i);
				if ( mesh )
				{
					ApexTypeData.Meshes.AddItem(mesh);
				}
			}
			Component->bIsViewRelevanceDirty = TRUE;
			Component->bRecacheViewRelevance = TRUE;
			Component->CacheViewRelevanceFlags(NULL);
		}
	}
	// NVCHANGE_END: JCAO - Apex Emitter Asset work with LODs
}

// NVCHANGE_BEGIN: JCAO - Apex Emitter Asset work with LODs
void FParticleApexEmitterInstance::SetCurrentLODIndex(INT InLODIndex, UBOOL bInFullyProcess)
{
	if(bInFullyProcess)
	{
		if(ApexEmitter)
		{
			ApexEmitter->SwitchLOD();
		}
	}

	FParticleEmitterInstance::SetCurrentLODIndex(InLODIndex, bInFullyProcess);
}
// NVCHANGE_END: JCAO - Apex Emitter Asset work with LODs

// NVCHANGE_BEGIN: JCAO - Add interface to control the rate of Apex Emitter
void FParticleApexEmitterInstance::SetRate(FLOAT MinRate, FLOAT MaxRate)
{
	if(ApexEmitter)
	{
		ApexEmitter->SetRate(MinRate, MaxRate);
	}
}
// NVCHANGE_END: JCAO - Add interface to control the rate of Apex Emitter
#endif // endif WITH_APEX_PARTICLES
