/*=============================================================================
	NvApexScene.cpp : Implements the FIApexClothing interface and various utility methods.
	Copyright 1998-2013 Epic Games, Inc. All Rights Reserved.
=============================================================================*/


// This code contains NVIDIA Confidential Information and is disclosed
// under the Mutual Non-Disclosure Agreement.
//
// Notice
// ALL NVIDIA DESIGN SPECIFICATIONS, CODE ARE PROVIDED "AS IS.". NVIDIA MAKES
// NO WARRANTIES, EXPRESSED, IMPLIED, STATUTORY, OR OTHERWISE WITH RESPECT TO
// THE MATERIALS, AND EXPRESSLY DISCLAIMS ALL IMPLIED WARRANTIES OF NONINFRINGEMENT,
// MERCHANTABILITY, AND FITNESS FOR A PARTICULAR PURPOSE.
//
// Information and code furnished is believed to be accurate and reliable.
// However, NVIDIA Corporation assumes no responsibility for the consequences of use of such
// information or for any infringement of patents or other rights of third parties that may
// result from its use. No license is granted by implication or otherwise under any patent
// or patent rights of NVIDIA Corporation. Details are subject to change without notice.
// This code supersedes and replaces all information previously supplied.
// NVIDIA Corporation products are not authorized for use as critical
// components in life support devices or systems without express written approval of
// NVIDIA Corporation.
//
// Copyright 2009-2010 NVIDIA Corporation. All rights reserved.
// Copyright 2002-2008 AGEIA Technologies, Inc. All rights reserved.
// Copyright 2001-2006 NovodeX. All rights reserved.
#include "EnginePrivate.h"
#include "EngineAudioDeviceClasses.h"

#if WITH_NOVODEX

#if WITH_APEX

#include "UnNovodexSupport.h"
#include "EngineMeshClasses.h"
#include "NvApexScene.h"
#include "NvApexManager.h"
#include "NvApexCommands.h"
#include "NvApexRender.h"
#if WITH_APEX_PARTICLES
#include "NxApexEmitterActor.h"
#include <NxEmitterLodParamDesc.h>
// NVCHANGE_BEGIN: JCAO - Add field sampler group filter
#include <NxModuleFieldSampler.h>
// NVCHANGE_END: JCAO - Add field sampler group filter
#endif
#include <NxArray.h>
#include <NxActorDesc.h>
#include <NxApexAsset.h>
#include <NxDestructibleAsset.h>
#include <NxDestructibleActor.h>
#include <NxClothingAsset.h>
#include <NxClothingActor.h>
#include <NxApexSDK.h>
#include <NxParameterized.h>
// NVCHANGE_BEGIN: DJS - Clean up APEX includes
#include <foundation/PxQuat.h>
// NVCHANGE_END: DJS - Clean up APEX includes
#include <NxScene.h>
// NVCHANGE_BEGIN: DJS - Clean up APEX includes
#if WITH_APEX_PARTICLES
#include <NxApexRenderVolume.h>
#include <NxModuleIofx.h>
#include <NxIofxAsset.h>
#include <NxIofxActor.h>
#include <NxApexEmitterAsset.h>
#endif
#include "NvApexRender.h"
#include <pxtask/PxCudaContextManager.h>
#include <pxtask/PxTaskManager.h>
// NVCHANGE_END: DJS - Clean up APEX includes

#include "EngineAnimClasses.h"

#define USE_UE3_THREADPOOL (0)
#if USE_UE3_THREADPOOL
// NVCHANGE_BEGIN: DJS - Clean up APEX includes
#include <pxtask/PxTask.h>
// NVCHANGE_END: DJS - Clean up APEX includes
#endif


using namespace physx::apex;
#define FAKE_LAG 0 // introduces extreme fake lag into the system to help debug/identify physics lagging problems.  Off by default of course.

#if FAKE_LAG
#include "MinWindows.h"
// oscar@snda #include <windows.h>
#endif

#define HACK_GLOBAL_RENDER_VOLUME 0

// NVCHANGE_BEGIN: DJS - Add APEX stats
/** Apex Stats */
DECLARE_STATS_GROUP(TEXT("Apex"), STATGROUP_Apex);
DECLARE_CYCLE_STAT(TEXT("Apex before tick time"),STAT_ApexBeforeTickTime,STATGROUP_Apex);
DECLARE_CYCLE_STAT(TEXT("Apex during tick time"),STAT_ApexDuringTickTime,STATGROUP_Apex);
DECLARE_CYCLE_STAT(TEXT("Apex after tick time"),STAT_ApexAfterTickTime,STATGROUP_Apex);
DECLARE_CYCLE_STAT(TEXT("PhysX simulation time"),STAT_ApexPhysXSimTime,STATGROUP_Apex);
DECLARE_CYCLE_STAT(TEXT("PhysX fetchResults time"),STAT_ApexPhysXFetchTime,STATGROUP_Apex);
DECLARE_CYCLE_STAT(TEXT("User delayed fetchResults time"),STAT_ApexUserDelayedFetchTime,STATGROUP_Apex);
DECLARE_DWORD_COUNTER_STAT(TEXT("Total actors"),STAT_ApexNumActors,STATGROUP_Apex);
DECLARE_DWORD_COUNTER_STAT(TEXT("Total shapes"),STAT_ApexNumShapes,STATGROUP_Apex);
DECLARE_DWORD_COUNTER_STAT(TEXT("Awake shapes"),STAT_ApexNumAwakeShapes,STATGROUP_Apex);
DECLARE_DWORD_COUNTER_STAT(TEXT("CPU pairs"),STAT_ApexNumCPUPairs,STATGROUP_Apex);
#if WITH_APEX_GRB
DECLARE_CYCLE_STAT(TEXT("GRB simulation time"),STAT_ApexGrbSimTime,STATGROUP_Apex);
DECLARE_DWORD_COUNTER_STAT(TEXT("GRB pairs"),STAT_ApexNumGPUPairs,STATGROUP_Apex);
#endif
#if _WINDOWS
DECLARE_FLOAT_COUNTER_STAT(TEXT("GPU allocated memory (MB)"),STAT_ApexHeapGpu,STATGROUP_Apex);
DECLARE_FLOAT_COUNTER_STAT(TEXT("Pinned allocated memory (MB)"),STAT_ApexHeapPinned,STATGROUP_Apex);
#endif
// NVCHANGE_END: DJS - Add APEX stats


physx::PxU32	   GActiveApexSceneCount=0;

namespace APEX_SCENE
{
	const physx::PxF32 MIN_BENEFIT=0.001f;

class ApexScene;
class FApexActorCleanUp: public FApexCleanUp
{
public:
	// NVCHANGE_BEGIN : hlanker - fix apex rendering race condition
	FApexActorCleanUp(physx::apex::NxApexInterface* ApexObject, FIApexAsset *Asset, FIApexActor* Actor, NxApexRenderContext* Context, void (*CallbackFunc)(void*), void* CallbackData)
	// NVCHANGE_END : hlanker - fix apex rendering race condition
		:FApexCleanUp(ApexObject, Asset)
	{
		MApexActor = Actor;
		// NVCHANGE_BEGIN : hlanker - fix apex rendering race condition
		RenderContext = Context;
		// NVCHANGE_END : hlanker - fix apex rendering race condition

		MCallbackFunc = CallbackFunc;
		MCallbackData = CallbackData;
	}

	virtual ~FApexActorCleanUp()
	{

	}
	virtual void FinishCleanup()
	{
		// NVCHANGE_BEGIN : hlanker - fix apex rendering race condition
		if (RenderContext != NULL)
		{
			delete RenderContext;
			RenderContext = NULL;
		}
		// NVCHANGE_END : hlanker - fix apex rendering race condition

		if (MCallbackFunc != NULL)
		{
			(*MCallbackFunc)(MCallbackData);
		}

		check(ApexObject);
		ApexObject->release();
		ApexObject = NULL;
		if(ApexAsset)
		{
			ApexAsset->DecRefCount(MApexActor);
			delete MApexActor;
		}

		check(PendingObjects);
		appInterlockedDecrement(&PendingObjects);
		delete this;
	}
private:
	FIApexActor	*MApexActor;
	// NVCHANGE_BEGIN : hlanker - fix apex rendering race condition
	NxApexRenderContext* RenderContext;
	// NVCHANGE_END : hlanker - fix apex rendering race condition

	void (*MCallbackFunc)(void*);
	void *MCallbackData;
};
// NVCHANGE_BEGIN : hlanker - fix apex rendering race condition
class ApexActor : public FIApexActor, public NxUserRenderer
// NVCHANGE_END : hlanker - fix apex rendering race condition
{
public:

  ApexActor(ApexScene *parentScene,
   			FIApexAsset *apexAsset,
   			const ::NxParameterized::Interface *params);

  virtual ~ApexActor(void)
  {
  }

  virtual void NotifyAssetModified(void)
  {
	  mNeedsRebuild = TRUE;
  }

  virtual UBOOL	NeedsRebuild(void) const 
  {
	  UBOOL ret = FALSE;
	  if ( mNeedsRebuild || MActor == NULL )
	  {
		  ret = TRUE;
	  }
	  return ret;
  }

  UBOOL Recreate(ApexScene *parentScene,const ::NxParameterized::Interface *params);

  virtual void *              GetUserData(void)
  {
    void *ret = NULL;
    if ( MActor )
    {
      ret = MActor->userData;
    }
    return ret;
  }

  virtual void Release(void (*CallbackFunc)(void*) = 0, void* CallbackData = 0);

	virtual void	ProcessTweakable(NxParameterized::Interface *iface,const char *tweakable)
	{
		if  ( !MActor ) return;
		if ( tweakable == NULL )
		{
			mNeedsRebuild = TRUE;
			return;
		}
#if WITH_APEX_PARTICLES
		switch ( MApexAsset->GetType() )
		{
			case AAT_APEX_EMITTER:
			{
				NxApexEmitterActor *a = static_cast< NxApexEmitterActor *>(MActor);
				if ( strcmp(tweakable,"rateRange") == 0 )
				{
					NxRange< physx::PxF32 > r;
					NxParameterized::getParamF32(*iface,"rateRange.min",r.minimum);
					NxParameterized::getParamF32(*iface,"rateRange.max",r.maximum);
					a->setRateRange(r);
				}
				else if ( strcmp(tweakable,"densityRange") == 0 )
				{
					NxRange< physx::PxF32 > r;
					NxParameterized::getParamF32(*iface,"densityRange.min",r.minimum);
					NxParameterized::getParamF32(*iface,"densityRange.max",r.maximum);
					a->setDensityRange(r);
				}
				else if ( strcmp(tweakable,"lifetimeRange") == 0 )
				{
					NxRange< physx::PxF32 > r;
					NxParameterized::getParamF32(*iface,"lifetimeRange.min",r.minimum);
					NxParameterized::getParamF32(*iface,"lifetimeRange.max",r.maximum);
					a->setLifetimeRange(r);
				}
				else if ( strcmp(tweakable,"velocityRange") == 0 )
				{
					NxRange< physx::PxVec3 > r;
					NxParameterized::getParamVec3(*iface,"velocityRange.min",r.minimum);
					NxParameterized::getParamVec3(*iface,"velocityRange.max",r.maximum);
					a->setVelocityRange(r);
				}
				else if ( strcmp(tweakable,"lodParamDesc") == 0 )
				{
					physx::NxEmitterLodParamDesc desc;
					NxParameterized::getParamF32(*iface,"lodParamDesc.maxDistance",desc.maxDistance);
					NxParameterized::getParamF32(*iface,"lodParamDesc.distanceWeight",desc.distanceWeight);
					NxParameterized::getParamF32(*iface,"lodParamDesc.speedWeight",desc.speedWeight);
					NxParameterized::getParamF32(*iface,"lodParamDesc.lifeWeight",desc.lifeWeight);
					NxParameterized::getParamF32(*iface,"lodParamDesc.separationWeight",desc.separationWeight);
					NxParameterized::getParamF32(*iface,"lodParamDesc.bias",desc.bias);
					a->setLodParamDesc(desc);
				}
			}
			break;
	  }
#endif
  }

  UBOOL IsOk(void) const
  {
	  return MActor ? TRUE : FALSE;
  }

  virtual void	UpdateRenderResources(void* ApexUserData)
  {

	  if ( MActor && GApexCommands->IsShowApex() )
	  {
  		  switch ( MApexAsset->GetType() )
		  {
			case AAT_DESTRUCTIBLE:
			  {
        		NxDestructibleActor *da = static_cast< NxDestructibleActor *>(MActor);
				da->lockRenderResources();
				da->updateRenderResources();
				da->unlockRenderResources();

				mUpdateRenderResource	= TRUE;

			  }
			  break;
			case AAT_CLOTHING:
			  {
				NxClothingActor *da = static_cast< NxClothingActor *>(MActor);

				da->lockRenderResources();
				// NVCHANGE_BEGIN : hlanker - fix apex rendering race condition
				// all data provided through callbacks gets copied and
				// queued to be processed in render thread
				da->updateRenderResources( false, ApexUserData );
				da->unlockRenderResources();

				// create object that is given to render thread
				RenderContext = new NxApexRenderContext();
				da->dispatchRenderResources(*this); // calls renderResource

				// copy in render thread
				ENQUEUE_UNIQUE_RENDER_COMMAND_TWOPARAMETER(
					RenderContextCopy,
					ApexActor*, ApexActor, this,
					NxApexRenderContext*, RenderContext, RenderContext,
				{
					ApexActor->CopyRenderContexts_RenderThread(RenderContext);
				}
				);
				// NVCHANGE_END : hlanker - fix apex rendering race condition

				//GApexNormalSign = 1;
				//GReverseCulling = TRUE;
				
				mUpdateRenderResource	= TRUE;

			  }
			  break;
		  }

	  }
  }

  // NxUserRenderer interface
  virtual void renderResource(const NxApexRenderContext& Context)
  {
	  check(IsInGameThread());
	  check (MApexAsset != NULL && MApexAsset->GetType() == AAT_CLOTHING); // right now this is implemented for clothing only

	  check (RenderContext != NULL); // we must have allocated this before the UpdateRenderResources call
	  *RenderContext = Context;
  }


  void CopyRenderContexts_RenderThread(NxApexRenderContext* Context)
  {
	  check(RenderContext != NULL);
	  delete RenderContextRT; // delete old data

	  RenderContextRT = Context;
  }


  virtual void Render(NxUserRenderer &renderer)
  {
	  check(IsInRenderingThread());

	  if ( !mUpdateRenderResource )
		  return;

	  if ( MActor && GApexCommands->IsShowApex() )
	  {
		  switch ( MApexAsset->GetType() )
		  {
			case AAT_DESTRUCTIBLE:
			  {
        		NxDestructibleActor *da = static_cast< NxDestructibleActor *>(MActor);
        		da->dispatchRenderResources(renderer);
			  }
			  break;
			case AAT_CLOTHING:
			  {
				  if (RenderContextRT != NULL)
				  {
					renderer.renderResource(*RenderContextRT);
				  }
			  }
			  break;
		  }
	  }
  }

  FIApexAsset * GetApexAsset(void) const { return MApexAsset; };

  virtual NxApexActor * GetNxApexActor(void) const { return MActor; };

  virtual ApexActorType::Enum GetApexActorType(void) const
  {
    return MType;
  }

  virtual void				  NotifyAssetGone(void) // notify the actor that the asset which is was created with is now gone.
  {
  	if ( MActor )
  	{
  		MActor->release();
		if ( MApexAsset )
		{
			MApexAsset->DecRefCount(this);
		}
  		MActor = NULL;
  	}
  }

  virtual void				  NotifyAssetImport(void) // notify the actor that a fresh asset has been imported and the actor can be re-created.
  {
  }

//private:
	ApexActorType::Enum     MType;
	NxApexActor      		*MActor;
	FIApexAsset      		*MApexAsset;
	ApexScene        		*MParent;
	UBOOL					mNeedsRebuild;
	UBOOL					mUpdateRenderResource;
	// renderResorce buffering:
	NxApexRenderContext* RenderContext; // buffer during dispatchRenderResource, created in game thread, handed over to RT
	NxApexRenderContext* RenderContextRT; // render thread
};

class ApexClothing;

static UBOOL GetParam(::NxParameterized::Interface *pm,const char *name,physx::PxF32 &value)
{
	if ( !pm ) return FALSE;
	UBOOL ret = TRUE;
#if NX_APEX_SDK_RELEASE >= 100
	::NxParameterized::Handle handle(*pm);
#else
	::NxParameterized::Handle handle;
#endif
	if ( pm->getParameterHandle(name,handle) == ::NxParameterized::ERROR_NONE )
	{
#if NX_APEX_SDK_RELEASE >= 100
		handle.getParamF32(value);
#else
		pm->getParamF32(handle,value);
#endif
	}
	else
	{
		ret = FALSE;
	}

	return ret;
}

struct BaseBoneRef
{
	BaseBoneRef(void)
	{
		MTransform = physx::PxMat44::createIdentity();
		MBaseIndex = 0;
	}
	physx::PxMat44			MTransform;
	physx::PxU32			MBaseIndex;
};

typedef NxArray< BaseBoneRef > TBaseBoneRefArray;
typedef NxArray< physx::PxU32 > TPxU32Array;

class ApexClothingPiece : public FIApexClothingPiece
{
public:
	ApexClothingPiece(FIApexAsset *asset,ApexClothing *parent,::NxParameterized::Interface *np,physx::PxU32 materialIndex, USkeletalMeshComponent* skeletalMeshComp)
	{
		MClothingIndex = materialIndex;
		MSimulateCount = 0;
		MAsset		= asset;
		MParent     = parent;
		MSkeletalMeshComponent = skeletalMeshComp;
		MActor  	= NULL;
		MReady		= FALSE;
		MWasVisible = FALSE;
		MParameterized = NULL;
		MContinuousRotationThreshold = 0.1f;
		mContinousDistanceThreshold = 1.0f;
		MRootPose = physx::PxMat44::createIdentity();
		MGraphicalLODNum = 0;
		bForcedHidden = FALSE;
		MLODTotalDecayTime = -1.0f;
		MCurrDecayTime = 0.0f;
		UApexClothingAsset *cue = CastChecked< UApexClothingAsset>(asset->GetUE3Object());
		if ( np )
		{
			NxApexSDK *sdk = GApexManager->GetApexSDK();
			::NxParameterized::Traits *traits = sdk->getParameterizedTraits();
			if ( traits )
			{
				MParameterized = traits->createNxParameterized( np->className() );
				if ( MParameterized )
				{
					MParameterized->copy(*np);
					MContinuousRotationThreshold = cosf(NxMath::degToRad(cue->ContinuousRotationThreshold));
					mContinousDistanceThreshold = cue->ContinuousDistanceThreshold*U2PScale;
					// Decay clothing benefit when it is not visible
					MLODTotalDecayTime = cue->LODDecayTime;
        			GetParam(MParameterized,"lodWeights.maxDistance",MLodWeightsMaxDistance);
        			GetParam(MParameterized,"lodWeights.distanceWeight",MLodWeightsDistanceWeight);
        			GetParam(MParameterized,"lodWeights.bias",MLodWeightsBias);
        			GetParam(MParameterized,"lodWeights.benefitsBias",MLodWeightsBenefitsBias);
					NxParameterized::Handle handle(*MParameterized);
					handle.getParameter("graphicalLods");
					handle.getArraySize(MGraphicalLODNum);

					// NVCHANGE_BEGIN: APEX 1.2
					MTeleportationMode = (cue->bResetAfterTeleport)? ClothingTeleportMode::TeleportAndReset : ClothingTeleportMode::Teleport;
					// NVCHANGE_END: APEX 1.2
				}
			}
		}

		mContinousDistanceThreshold*=mContinousDistanceThreshold;
		MPrevLOD = 0.0f;
		MGraphicalLODAvailable = TRUE;
		MPrevVelocity = 0;
		bIsClothMoving = FALSE;
		MAudioOnMove = 0;
		MAudioOnRest = 0;
		MAudioWhileMoving = 0;
		bWasOnMovePlayed = FALSE;
		bWasMovingNeedsPlaying = FALSE;
		bWasOnRestNeedsPlaying = FALSE;

		// Attach the three sound components to the actor
		if (skeletalMeshComp->GetOwner() != NULL)
		{
			// must create audio component and attach it to skeletalmesh
			if(cue->SoundOnMove)
			{
				MAudioOnMove = UAudioDevice::CreateComponent(cue->SoundOnMove, skeletalMeshComp->GetScene(), skeletalMeshComp->GetOwner(), 0);
				skeletalMeshComp->GetOwner()->AttachComponent(MAudioOnMove);
			}
			if(cue->SoundOnRest)
			{
				MAudioOnRest = UAudioDevice::CreateComponent(cue->SoundOnRest, skeletalMeshComp->GetScene(), skeletalMeshComp->GetOwner(), 0);
				skeletalMeshComp->GetOwner()->AttachComponent(MAudioOnRest);
			}
			if(cue->SoundWhileMoving)
			{
				MAudioWhileMoving = UAudioDevice::CreateComponent(cue->SoundWhileMoving, skeletalMeshComp->GetScene(), skeletalMeshComp->GetOwner(), 0);
				skeletalMeshComp->GetOwner()->AttachComponent(MAudioWhileMoving);
			}
			bIgnoreInitialTrigger = cue->IgnoreInitialTrigger;
		
		}

		// Find material to use for clothing
		bUseOverride = FALSE;
		UMaterialInterface* ClothingMat = NULL;
		USkeletalMesh* SkelMesh = NULL;
		if( MSkeletalMeshComponent && MSkeletalMeshComponent->SkeletalMesh )
		{
			SkelMesh = MSkeletalMeshComponent->SkeletalMesh;
		}
		if( SkelMesh
			&& (SkelMesh->ClothingAssets.Num() > static_cast<INT>(MClothingIndex))
			&& SkelMesh->ClothingAssets(MClothingIndex) )
		{
			UApexClothingAsset* ClothingAsset = SkelMesh->ClothingAssets(MClothingIndex);
			MClothingLODInfo =  SkelMesh->ClothingLodMap(MClothingIndex).ClothingLODInfo;
			bUseOverride = ClothingAsset->SupportsMaterialOverride();		
			if ( bUseOverride )
			{
				INT LodLevel = MSkeletalMeshComponent->PredictedLODLevel;
				// NVCHANGE_BEGIN : hlanker - prevent crash when clothing asset does not have same number of lod levels as skeletal mesh component
				NxClothingAsset* nxClothingAsset = static_cast<NxClothingAsset*>(MAsset->GetNxApexAsset());
				if (LodLevel >= (INT)nxClothingAsset->getNumGraphicalLodLevels())
				{
					// use highest level available
					LodLevel = nxClothingAsset->getNumGraphicalLodLevels() - 1;
				}				
				const NxRenderMeshAsset* RenderMeshAsset =  nxClothingAsset->getRenderMeshAsset(LodLevel);
				// NVCHANGE_END : hlanker - prevent crash when clothing asset does not have same number of lod levels as skeletal mesh component
				for(UINT SubmeshID = 0; SubmeshID < RenderMeshAsset->getSubmeshCount(); ++SubmeshID)
				{
					if ( SkelMesh->bUseClothingAssetMaterial )
					{
						// Optionally use the material from the clothing asset instead of the one from the skeletal mesh
						if ( ClothingAsset && (ClothingAsset->Materials.Num() > 0) )
						{
							ClothingMat = ClothingAsset->Materials(ClothingAsset->LodMaterialInfo(LodLevel).LODMaterialMap(SubmeshID));
						}
					}
					else if ( SkelMesh->Materials.Num() > static_cast<INT>(MClothingIndex) )
					{
						INT SectionIndex = MClothingLODInfo(LodLevel).ClothingSectionInfo(SubmeshID);
						SectionIndex = Clamp(SectionIndex, 0, MSkeletalMeshComponent->SkeletalMesh->LODModels(LodLevel).Chunks.Num() - 1);
						INT MaterialIndex = SectionIndex;
						if(LodLevel > 0)
						{
							MaterialIndex = MSkeletalMeshComponent->SkeletalMesh->LODInfo(LodLevel).LODMaterialMap(SectionIndex);
						}
						else
						{
							MaterialIndex = MSkeletalMeshComponent->SkeletalMesh->LODModels(0).Sections(SectionIndex).MaterialIndex;
						}
						if(MaterialIndex != -1)
						{
							ClothingMat = MSkeletalMeshComponent->GetMaterial(MaterialIndex);
						}
						else
						{
							ClothingMat = GEngine->DefaultMaterial;
						}
					}
					// Ensure that the material is usable for APEX clothing
					InitMaterialForApex(ClothingMat);
					MOverrideMats.AddItem( ClothingMat );
				}
			}
		}
	}
	~ApexClothingPiece(void);

	virtual FIApexAsset	* GetApexAsset(void)
	{
		return MAsset;
	}
	INT GetMaterialIndex(INT LodLevel, INT SubmeshIndex) const
	{
		INT MaterialIndex = 0;
		USkeletalMesh* SkelMesh = MSkeletalMeshComponent->SkeletalMesh;
		UApexClothingAsset* ClothingAsset =  CastChecked<UApexClothingAsset>(MAsset->GetUE3Object());
		if ( SkelMesh->bUseClothingAssetMaterial )
		{
			MaterialIndex = ClothingAsset->LodMaterialInfo(LodLevel).LODMaterialMap(SubmeshIndex);
		}
		else
		{
			MaterialIndex =  MClothingLODInfo(LodLevel).ClothingSectionInfo(SubmeshIndex);
		}
		return MaterialIndex;
	}

	UMaterialInterface* GetMaterial(INT LodLevel, INT SubmeshIndex) const
	{
		INT MaterialIndex = GetMaterialIndex(LodLevel, SubmeshIndex);
		UApexClothingAsset* ClothingAsset =  CastChecked<UApexClothingAsset>(MAsset->GetUE3Object());
		UMaterialInterface* Material = GEngine->DefaultMaterial;
		if ( MSkeletalMeshComponent->SkeletalMesh->bUseClothingAssetMaterial )
		{
			Material = ClothingAsset->Materials(ClothingAsset->LodMaterialInfo(LodLevel).LODMaterialMap(SubmeshIndex));
		}
		else
		{
			INT SectionIndex = MClothingLODInfo(LodLevel).ClothingSectionInfo(SubmeshIndex);
			SectionIndex = Clamp(SectionIndex, 0, MSkeletalMeshComponent->SkeletalMesh->LODModels(LodLevel).Chunks.Num() - 1);
			INT MaterialIndex = SectionIndex;
			if(LodLevel > 0)
			{
				MaterialIndex = MSkeletalMeshComponent->SkeletalMesh->LODInfo(LodLevel).LODMaterialMap(SectionIndex);
			}
			else
			{
				MaterialIndex = MSkeletalMeshComponent->SkeletalMesh->LODModels(0).Sections(SectionIndex).MaterialIndex;
			}
			if(MaterialIndex != -1)
			{
				Material = MSkeletalMeshComponent->GetMaterial(MaterialIndex);
			}
		}
		return Material;
	}
	INT	GetNumVertices(INT LodIndex, INT SectionIndex)
	{
		INT NumVertices = 0;
		if (!MGraphicalLODAvailable)
			return 0;

		for(INT SubmeshIndex = 0; SubmeshIndex < MClothingLODInfo(LodIndex).ClothingSectionInfo.Num(); ++SubmeshIndex)
		{
			INT ClothingSectionIndex = MClothingLODInfo(LodIndex).ClothingSectionInfo(SubmeshIndex);
			if(ClothingSectionIndex == SectionIndex)
			{
				NxClothingAsset* ClothingAsset = static_cast<NxClothingAsset*>(MAsset->GetNxApexAsset());
				const NxRenderMeshAsset* RenderMeshAsset = ClothingAsset->getRenderMeshAsset(LodIndex);
				NumVertices = RenderMeshAsset->getSubmesh(SubmeshIndex).getVertexBuffer().getVertexCount();
				break;
			}
		}
		return NumVertices;
	}
	void SyncPieceTransforms(const physx::PxMat44 *transforms,UBOOL previouslyVisible, const physx::PxMat44& LocalToWorld, UBOOL bForceTeleportAndReset, UBOOL bForceTeleport);
	void UpdateRenderResources(void);
// NVCHANGE_BEGIN: APAN - Fix build error for APEX 1.2
	virtual bool velocityShader(physx::PxVec3* Velocities, const physx::PxVec3* /*positions*/, physx::PxU32 NumOfParticles)
	{
		if(MAsset == NULL || MSkeletalMeshComponent->GetOwner() == NULL)
		{
			return false;
		}
		UApexClothingAsset *ClothingAsset = CastChecked< UApexClothingAsset>(MAsset->GetUE3Object());
		// Calculate average velocity of cloth
		const UINT NoOfClothingParticles = NumOfParticles / 2;
		const UINT CalculationTestStride = Max<UINT>(1, NumOfParticles / NoOfClothingParticles);

		FLOAT TotalVelocity = 0;

		for ( physx::PxU32 VertIndex = 0; VertIndex < NumOfParticles; VertIndex += CalculationTestStride )
		{
			FVector ParticleVelocity = N2UPositionApex(Velocities[VertIndex]);
			FVector Direction;
			FLOAT	Speed;
			ParticleVelocity.ToDirectionAndLength(Direction, Speed);
			TotalVelocity += Speed;
		}

		FLOAT AverageVelocity = TotalVelocity / NoOfClothingParticles;
		// round down to 1 decimal place
		AverageVelocity = appFloor(AverageVelocity * 10) / 10.0f;
	
		// If the increase in velocity is high enough, cloth is "OnMove"
		if (AverageVelocity >= ClothingAsset->SpeedThresholdOnMove 
			&& MPrevVelocity < ClothingAsset->SpeedThresholdOnMove
			&& !bIsClothMoving)
		{
			bIsClothMoving = TRUE;
			bWasMovingNeedsPlaying = TRUE;
			// Play OnMove sound
			if(MAudioOnMove != NULL && !MAudioOnMove->IsPlaying())
			{
				if(!bIgnoreInitialTrigger)
				{
					MAudioOnMove->Play();
				}
				else
				{
					bWasMovingNeedsPlaying = FALSE;
				}
			}

			// Stop OnRest sound
			if (MAudioOnRest != NULL)
			{
				MAudioOnRest->Stop();
			}
		}
		// Cloth is moving
		else if (AverageVelocity > ClothingAsset->SpeedThresholdOnMove && bWasMovingNeedsPlaying)
		{
			if(MAudioOnMove == NULL || !MAudioOnMove->IsPlaying())
			{
				bWasMovingNeedsPlaying = FALSE;
				if(MAudioWhileMoving!= NULL)
				{
						MAudioWhileMoving->Play();
				}
			}
		}
		// If the decrease in velocity is high enough, cloth is "OnRest"
		else if (AverageVelocity <= ClothingAsset->SpeedThresholdOnRest 
			&& MPrevVelocity > ClothingAsset->SpeedThresholdOnRest 
			&& bIsClothMoving)
		{
			bIsClothMoving = FALSE;
			bWasOnRestNeedsPlaying = !bIgnoreInitialTrigger;
			if(MAudioWhileMoving!= NULL)
			{
				MAudioWhileMoving->Stop();
			}

			if(!bWasMovingNeedsPlaying)
			{
				if(MAudioOnRest != NULL && !bIgnoreInitialTrigger)
				{
					MAudioOnRest->Play();
				}
				bWasOnRestNeedsPlaying = FALSE;
			}
			bIgnoreInitialTrigger = FALSE;
		}
		// Start playing WhileMoving Sound After OnMove sound has been played
		if ( bWasMovingNeedsPlaying && MAudioOnMove!=NULL && !MAudioOnMove->IsPlaying())
		{
			bWasMovingNeedsPlaying = FALSE;
			if (MAudioWhileMoving != NULL)
			{
				MAudioWhileMoving->Play();
			}
		}
		// Start playing OnRest sound after OnMove sound has been played
		if (bWasOnRestNeedsPlaying && !bWasMovingNeedsPlaying)
		{
			bWasOnRestNeedsPlaying = FALSE;
			if(MAudioWhileMoving!= NULL)
			{
				MAudioWhileMoving->Stop();
			}
			if(MAudioOnRest != NULL)
			{
				MAudioOnRest->Play();
			}
		}

		// If the moving sound is yet to be played, play it when OnMove sound finishes playing
		MPrevVelocity = AverageVelocity;

		return false;
	}
// NVCHANGE_END: APAN - Fix build error for APEX 1.2

	void SetNonVisible(void)
	{
		if ( MWasVisible )
		{
			//debugf(TEXT("CLOTHING NO LONGER VISIBLE"));
			MWasVisible = FALSE;
			NxClothingActor *Act = static_cast< NxClothingActor *>(MActor->GetNxApexActor());
			if ( Act )
			{
				NxParameterized::Interface* ActorDesc = Act->getActorDesc();
				NxParameterized::setParamF32(*ActorDesc, "lodWeights.bias", 0);
				if( !bForcedHidden )
				{
					Act->setVisible(false);
				}

				if (MSkeletalMeshComponent->bAutoFreezeApexClothingWhenNotRendered)
				{
					Act->setFrozen(true);
				}
			}
		}
	}

	void SetVisible(UBOOL bEnable)
	{
		bForcedHidden = !bEnable;
		if (MActor)
		{
			NxClothingActor *Act = static_cast< NxClothingActor *>(MActor->GetNxApexActor());
			if ( Act )
			{
				Act->setVisible(bEnable ? true : false);
			}
		}
	}

	void Pump(void);

	UBOOL IsReady(const physx::PxF32 *eyePos);

	virtual void Render(NxUserRenderer &renderer);

	virtual void RefreshApexClothingPiece(FIApexAsset * /*asset*/,::NxParameterized::Interface *np)
	{
		NxApexSDK *sdk = GApexManager->GetApexSDK();
		::NxParameterized::Traits *traits = sdk->getParameterizedTraits();
		if ( traits )
		{
			MParameterized = traits->createNxParameterized( np->className() );
			if ( MParameterized )
			{
				MParameterized->copy(*np);
       			GetParam(MParameterized,"lodWeights.maxDistance",MLodWeightsMaxDistance);
       			GetParam(MParameterized,"lodWeights.distanceWeight",MLodWeightsDistanceWeight);
       			GetParam(MParameterized,"lodWeights.bias",MLodWeightsBias);
       			GetParam(MParameterized,"lodWeights.benefitsBias",MLodWeightsBenefitsBias);
			}
		}
	}

	void BuildBoneMapping(void);
	void InitGraphicalLOD(void);
	void SetGraphicalLOD(physx::PxU32 lod);
	void NotifySceneGone(void);

	virtual UBOOL UsesMaterialIndex(physx::PxU32 materialIndex) const
	{
		UBOOL bUseMaterialIndex = FALSE;
		if(MActor)
		{
			NxClothingActor *Act = static_cast< NxClothingActor *>(MActor->GetNxApexActor());
			INT CurrentLod = 0;
			if(Act)
			{
				CurrentLod = Act->getGraphicalLod();
			}
			for(INT SectionID = 0; SectionID < MClothingLODInfo(CurrentLod).ClothingSectionInfo.Num(); ++SectionID)
			{
				if(GetMaterialIndex(CurrentLod, SectionID) == materialIndex)
				{
					bUseMaterialIndex = TRUE;
					break;
				}
			}
		}
		
		return bUseMaterialIndex;
	}

	void DisableSimulateThisFrame(void)
	{
		if ( MActor )
		{
    		NxClothingActor *act = static_cast< NxClothingActor *>(MActor->GetNxApexActor());
    		if ( act )
    		{
				NxParameterized::Interface*	actorDesc	= act->getActorDesc();
				NxParameterized::setParamF32(*actorDesc, "lodWeights.maxDistance", 0);
				NxParameterized::setParamF32(*actorDesc, "lodWeights.distanceWeight", 0);
				NxParameterized::setParamF32(*actorDesc, "lodWeights.bias", MIN_BENEFIT);
				NxParameterized::setParamF32(*actorDesc, "lodWeights.benefitsBias", MLodWeightsBenefitsBias);
    		}
		}
	}

	void SetWind(physx::PxF32 adaptTime,const physx::PxF32 *windVec)
	{
		if ( MActor )
		{
			physx::PxVec3 w;
			w.x = windVec[0];
			w.y = windVec[1];
			w.z = windVec[2];
			physx::apex::NxClothingActor *a = static_cast< physx::apex::NxClothingActor *>(MActor->GetNxApexActor());
			if ( a )
			{
				NxParameterized::Interface*	actorDesc	= a->getActorDesc();
				NxParameterized::setParamF32(*actorDesc, "windParams.Adaption", adaptTime);
				NxParameterized::setParamVec3(*actorDesc, "windParams.Velocity", w);
			}
		}
	}

	void SetMaxDistanceScale(physx::PxF32 scale, INT ScaleMode)
	{
		if ( MActor )
		{
			physx::apex::NxClothingActor *a = static_cast< physx::apex::NxClothingActor *>(MActor->GetNxApexActor());
			if ( a )
			{
				a->updateMaxDistanceScale(scale, (ScaleMode == MDSM_Multiply) ? true : false);
			}
		}
	}

	virtual void ToggleClothingPieceSimulation(const UBOOL& bEnableSimulation)
	{
		if ( MActor )
		{
    		NxClothingActor *Act = static_cast< NxClothingActor *>(MActor->GetNxApexActor());
    		if ( Act )
    		{
				Act->setFrozen(!bEnableSimulation);
    		}
		}
	}

	virtual UBOOL GetBounds(FBoxSphereBounds& Bounds)
	{
		if ( MActor )
		{
			NxClothingActor* ClothingActor = static_cast< NxClothingActor *>(MActor->GetNxApexActor());

			if ( ClothingActor )
			{
				physx::PxBounds3 nApexClothingBounds = ClothingActor->getBounds();
				if (!nApexClothingBounds.isEmpty())
				{
					FBox ClothBox = FBox( N2UPositionApex(nApexClothingBounds.minimum), N2UPositionApex(nApexClothingBounds.maximum) );
					Bounds = ClothBox;
					return TRUE;
				}
			}
		}

		return FALSE;
	}
	void SetDistanceWeightLODMultiplier( const physx::PxF32 Multiplier );
	void Tick( FLOAT DeltaTime );
	virtual void SetMaterial(INT MaterialIndex, UMaterialInterface *Material)
	{
		USkeletalMesh* SkelMesh = NULL;
		if( MSkeletalMeshComponent && MSkeletalMeshComponent->SkeletalMesh )
		{
			SkelMesh = MSkeletalMeshComponent->SkeletalMesh;
		}
		if(bUseOverride && !SkelMesh->bUseClothingAssetMaterial && MOverrideMats.Num() != 0)
		{
			InitMaterialForApex(Material);
			if ( MActor )
			{
				NxClothingActor *Act = static_cast< NxClothingActor *>(MActor->GetNxApexActor());
				if ( Act )
				{
					// find which submesh to override
					INT LodLevel = Act->getGraphicalLod();
					for(INT SectionID = 0; SectionID < MClothingLODInfo(LodLevel).ClothingSectionInfo.Num(); SectionID++)
					{
						if(GetMaterialIndex(LodLevel, SectionID) == MaterialIndex)
						{
							Act->setOverrideMaterial(SectionID, TCHAR_TO_ANSI(*Material->GetPathName()));
							break;
						}
					}
				}
			}
		}
	}

	UBOOL			 			MReady;
	UBOOL						MWasVisible;
	FIApexAsset					*MAsset;
	FIApexActor				   	*MActor;
	ApexClothing			   	*MParent;
	USkeletalMeshComponent		*MSkeletalMeshComponent;
	physx::PxMat44			    MRootPose;
	physx::PxU32						MSimulateCount;
	physx::PxF32						MContinuousRotationThreshold;
	physx::PxF32						mContinousDistanceThreshold;
    physx::PxF32						MLodWeightsMaxDistance;
    physx::PxF32						MLodWeightsDistanceWeight;
    physx::PxF32						MLodWeightsBias;
    physx::PxF32						MLodWeightsBenefitsBias;

	::NxParameterized::Interface *MParameterized;
	TBaseBoneRefArray			MBoneMapping;
	physx::PxU32						MClothingIndex;
	physx::PxF32						MPrevLOD;
	UBOOL								MGraphicalLODAvailable;
	physx::PxI32				MGraphicalLODNum;
	UAudioComponent				*MAudioOnMove;
	UAudioComponent				*MAudioOnRest;
	UAudioComponent				*MAudioWhileMoving;
	physx::PxF32				MPrevVelocity;
	UBOOL						bIsClothMoving;
	UBOOL						bWasOnMovePlayed;
	UBOOL						bWasMovingNeedsPlaying;
	UBOOL						bWasOnRestNeedsPlaying;
	UBOOL						bIgnoreInitialTrigger;
	TArray<UMaterialInterface*>			MOverrideMats;
	UBOOL								bUseOverride;
	// NVCHANGE_BEGIN: APEX 1.2
	ClothingTeleportMode::Enum MTeleportationMode;
	// NVCHANGE_END: APEX 1.2
	// No Longer needed
	// UBOOL						bIsFirstFrame;
	UBOOL						bForcedHidden;
	/** Determines how fast to reduce the benefit of the clothing*/
	physx::PxF32				MLODTotalDecayTime;
	/** Used to determine how much to reduce the benefit of the clothing */
	physx::PxF32				MCurrDecayTime;
	TArray<FApexClothingLodInfo> MClothingLODInfo;
};

typedef NxArray< ApexClothingPiece * > TApexClothingPieceVector;

struct BoneRef
{
	BoneRef(const char *BoneName)
	{
		MBoneName  = BoneName;
		bUsed      = FALSE;
	}

	const char		*MBoneName;      // The normalized name of the bone
	UBOOL		     bUsed;          // Indicates whether this bone is actively used by any piece of clothing.
};

typedef NxArray< BoneRef > TBoneRefVector;

#define VISIBLE_FRAME_COUNT 4

//** support for the apex clothing class, which associates multiple pieces of clothing with a single set of transforms.
class ApexClothing : public FIApexClothing
{
public:
	ApexClothing(FIApexScene *scene)
  	{
  		MUpdateReady = 0; // semaphore indicating that the rendering resources have been updated this frames
  		MReadyToRender = 0; // semaphore indicating that the rendering pipeline wanted to render the clothing this frame; true whether it actually rendered it or not.
  		MNeedsRefresh = FALSE;
  		MMatrices 	= NULL;
  		MBoneCount 	= 0;
		MSyncReady	= FALSE;
		MApexScene = scene;
		MPumpCount = 0;
		MVisibleFrame = (physx::PxU32)(-1) - VISIBLE_FRAME_COUNT;
		MPreviouslyVisible = FALSE; // by default not previously visible.
		MMaxDistanceScale = 1.0f;
		MMaxDistanceScaleTarget = 1.0f;
		MMaxDistanceScaleChangeVel = 0.0f;
		MMaxDistanceScaleMode = MDSM_Multiply;

		bForceTeleport = FALSE;
		bForceTeleportAndReset = FALSE;
		MActorScale = 1.0f;
 	}

 	~ApexClothing(void)
 	{
		Cleanup();
 	}

	void Cleanup()
	{
		for (TApexClothingPieceVector::iterator i=MPieces.begin(); i!=MPieces.end(); ++i)
		{
			ApexClothingPiece *ap = (*i);
			delete ap;
		}
		MPieces.clear();
		if ( MMatrices )
		{
			appFree(MMatrices);
			MMatrices = 0;
		}
	}

	virtual UBOOL UsesMaterialIndex(physx::PxU32 materialIndex) const
	{
		UBOOL ret = FALSE;
		for (TApexClothingPieceVector::const_iterator i=MPieces.begin(); i!=MPieces.end(); ++i)
		{
			ApexClothingPiece *ap = (*i);
			ret = ap->UsesMaterialIndex(materialIndex);
			if ( ret == TRUE )
			{
				break;
			}
		}
		return ret;
	}

	void Release(void);


	void NotifySceneGone(void)
	{
		MApexScene = NULL;
 		for (TApexClothingPieceVector::iterator i=MPieces.begin(); i!=MPieces.end(); ++i)
 		{
 			ApexClothingPiece *ap = (*i);
 			ap->NotifySceneGone();
 		}
	}

	virtual void Render(NxUserRenderer &renderer)
	{
 		for (TApexClothingPieceVector::iterator i=MPieces.begin(); i!=MPieces.end(); ++i)
 		{
 			ApexClothingPiece *ap = (*i);
 			ap->Render(renderer);
 		}
	}
	virtual FIApexClothingPiece * AddApexClothingPiece(FIApexAsset *asset,::NxParameterized::Interface *np,physx::PxU32 materialIndex, USkeletalMeshComponent* skeletalMeshComp)
	{
		ApexClothingPiece *ap = new ApexClothingPiece(asset,this,np,materialIndex, skeletalMeshComp);
		UBOOL found = FALSE;
		// look for an empty slot.
		for (TApexClothingPieceVector::iterator i=MPieces.begin(); i!=MPieces.end(); ++i)
		{
			if ( ap == NULL )
			{
				(*i) = ap;
				found = TRUE;
				break;
			}
		}
		if ( !found )
		{
			MPieces.push_back(ap);
		}
		return static_cast< FIApexClothingPiece *>(ap);
	}

	virtual void RemoveApexClothingPiece(FIApexClothingPiece *p)
	{
		ApexClothingPiece *ap = static_cast< ApexClothingPiece *>(p);
		if ( ap )
		{
			for (TApexClothingPieceVector::iterator i=MPieces.begin(); i!=MPieces.end(); ++i)
			{
				if ( ap == (*i) )
				{
					delete ap;
					(*i) = NULL;
					break;
				}
			}
		}
	}

	virtual void Pump(void)
	{
		MPumpCount++;
		for (TApexClothingPieceVector::iterator i=MPieces.begin(); i !=MPieces.end(); ++i)
		{
			ApexClothingPiece *ap = (*i);
			if ( ap )
			{
				ap->Pump();
			}
		}
	}
	virtual UBOOL IsReadyToRender(NxUserRenderer &renderer,const physx::PxF32 *eyePos, INT ClothingAssetIndex)
	{
		UBOOL ret = !MPieces.empty();
		if ( ret )
		{
       		check(MApexScene);
       		MVisibleFrame = MApexScene->GetSimulationCount();
			if(!MPieces[ClothingAssetIndex]->IsReady(eyePos))
			{
				return FALSE;
			}		
			MPieces[ClothingAssetIndex]->Render(renderer);
    	}
		return ret;
	}
	virtual void UpdateRenderResources(void)
	{
		if ( TRUE /*MReadyToRender*/ )
		{
			MReadyToRender--;
			MUpdateReady = 1; // set the resource update semaphore
   			for (TApexClothingPieceVector::iterator i=MPieces.begin(); i != MPieces.end(); ++i)
   			{
   				ApexClothingPiece *ap = (*i);
   				ap->UpdateRenderResources();
   			}
		}
		else
		{
			MUpdateReady = 0;
		}
	}

	// as 4x4 transforms
	virtual void SyncTransforms(physx::PxU32 boneCount,
                                const physx::PxF32 *matrices,
								physx::PxU32 stride,
								const FMatrix& LocalToWorld)
	{
		MSyncReady = TRUE;
		FVector ScaleVector = LocalToWorld.GetScaleVector();
		if(!ScaleVector.IsUniform())
		{
			debugf(NAME_Warning, TEXT("ClothingActor contains non uniform scale (Scale %s)"), *ScaleVector.ToString());
		}
		else
		{
			MActorScale = ScaleVector.X;
		}
		if ( boneCount == 0 ) return;

		if ( MMatrices == NULL )
		{
			MBoneCount = MBones.size();
			MMatrices = (physx::PxMat44 *)appMalloc(sizeof(physx::PxMat44)*MBoneCount);
		}


		const physx::PxU8 *scan = (const physx::PxU8 *)matrices;
		for (physx::PxU32 i=0; i<boneCount; i++)
		{
			physx::PxU32 index = MUsedBones[i];
			const physx::PxMat44 *pmat = (const physx::PxMat44 *)scan;
			MMatrices[index] = *pmat;
			scan+=stride;
		}

		for (TApexClothingPieceVector::iterator i=MPieces.begin(); i != MPieces.end(); ++i)
		{
			ApexClothingPiece *ap = (*i);
			ap->SyncPieceTransforms(MMatrices,MPreviouslyVisible, (physx::PxMat44&)LocalToWorld, bForceTeleportAndReset, bForceTeleport);
		}

		bForceTeleportAndReset = FALSE;
		bForceTeleport = FALSE;

		MPreviouslyVisible = IsVisible(false);

	}

	virtual void ForceNextUpdateTeleportAndReset()
	{
		bForceTeleportAndReset = TRUE;
	}

	virtual void ForceNextUpdateTeleport()
	{
		bForceTeleport = TRUE;
	}
	virtual void SetGraphicalLod(physx::PxU32 lod)
	{
		for (TApexClothingPieceVector::iterator i=MPieces.begin(); i != MPieces.end(); ++i)
		{
			ApexClothingPiece *ap = (*i);
			ap->SetGraphicalLOD(lod);
		}
	}
	virtual FIApexScene * GetApexScene(void)
	{
		return MApexScene;
	}

	virtual physx::PxU32 GetPumpCount(void) const { return MPumpCount; };


	virtual UBOOL NeedsRefreshAsset(void)  // semaphore, TRUE if any of the underlying assets have been released and need to be re-loaded.
	{
		UBOOL ret = MNeedsRefresh;
		MNeedsRefresh = FALSE;
		return ret;
	}

	virtual void RefreshApexClothingPiece(FIApexAsset *asset,::NxParameterized::Interface *iface)
	{
		for (TApexClothingPieceVector::iterator i=MPieces.begin(); i != MPieces.end(); ++i)
		{
			ApexClothingPiece *ap = (*i);
			ap->RefreshApexClothingPiece(asset,iface);
		}
	}

	void SetNeedsRefresh(UBOOL state)
	{
		MNeedsRefresh = state;
	}

	// configure the bone mapping.
	virtual void AddBoneName(const char *_boneName)
	{
		const char *boneName = GApexCommands->GetPersistentString(_boneName);
		BoneRef b(boneName);
		MBones.push_back(b);
	}

	virtual void BuildBoneMapping()
	{
		for (TApexClothingPieceVector::iterator i=MPieces.begin(); i!=MPieces.end(); ++i)
		{
			ApexClothingPiece *ap = (*i);
			ap->BuildBoneMapping();
		}
	}

	/****
	* Every time a child piece of clothing is created, we need to rebuild the master bone mapping table.
	***/
	void RefreshBoneMapping(void)
	{

		for (TBoneRefVector::iterator i=MBones.begin(); i!=MBones.end(); ++i)
		{
			(*i).bUsed = false;
		}

		MUsedBones.clear();

		for (TApexClothingPieceVector::iterator i=MPieces.begin(); i!=MPieces.end(); ++i)
		{
			ApexClothingPiece *ap = (*i);
			if ( ap )
			{
				// For each piece of clothing we iterate through the bones that it uses.
				for (TBaseBoneRefArray::iterator j=ap->MBoneMapping.begin(); j!= ap->MBoneMapping.end(); ++j)
				{
					BaseBoneRef &b = (*j);
					if ( !MBones[ b.MBaseIndex ].bUsed ) // if this bone is not already used, mark it as used.
					{
						MBones[b.MBaseIndex].bUsed = TRUE; // make it as used.
						MUsedBones.push_back( b.MBaseIndex ); // save the inverse lookup
					}
				}
			}
		}
		if ( MMatrices )
		{
			appFree(MMatrices);
			MMatrices = NULL;
		}
	}

	/**
	* Returns the number of bones actively used/referenced by clothing and
	* a pointer to an array of indices pointing back to the application source skeleton.
	*
	* @param : BoneCount a reference which returns the number of bones actively used.
	*
	* @return : A const pointer of indices mapping back to the original application skeleton.
	*/
	virtual const physx::PxU32 * GetBonesUsed(physx::PxU32 &BoneCount) const
	{
		BoneCount = MUsedBones.size();
		return BoneCount ? &MUsedBones[0] : NULL;
	}


	/***
	Returns the name of the used bone at this index number.
	*/
	virtual const char * GetBoneUsedName(physx::PxU32 BoneIndex) const
	{
		check( BoneIndex < MUsedBones.size() );
		physx::PxU32 idx = MUsedBones[BoneIndex];
		check( idx < MBones.size() );
		return MBones[idx].MBoneName;
	}

	void DisableSimulateThisFrame()
	{
		for (TApexClothingPieceVector::iterator i=MPieces.begin(); i!=MPieces.end(); ++i)
		{
			ApexClothingPiece *ap = (*i);
			if ( ap )
			{
				ap->DisableSimulateThisFrame();
			}
		}
	}

	/***
	Returns TRUE if this clothing is recently visible
	*/
	virtual UBOOL IsVisible(UBOOL updateBias)
	{
		UBOOL ret = FALSE;
		if ( MApexScene )
		{
			physx::PxU32 diff = MApexScene->GetSimulationCount() - MVisibleFrame;
			// NVCHANGE_BEGIN: hlanker - Initialize MVisibleFrame
			ret = diff < VISIBLE_FRAME_COUNT ? TRUE : FALSE; // it is considered 'visible' if it has been on screen within the past 4 frames.
			// NVCHANGE_END: hlanker - Initialize MVisibleFrame
		}
		if ( ret == FALSE && updateBias )
		{
			for (TApexClothingPieceVector::iterator i=MPieces.begin(); i!=MPieces.end(); ++i)
			{
				ApexClothingPiece *ap = (*i);
				if ( ap )
				{
					ap->SetNonVisible();
				}
			}
		}
		return ret;
	}

	virtual void SetWind(physx::PxF32 adaptTime,const physx::PxF32 *windVector)
	{
		for (TApexClothingPieceVector::iterator i=MPieces.begin(); i!=MPieces.end(); ++i)
		{
			ApexClothingPiece *ap = (*i);
			if ( ap )
			{
				ap->SetWind(adaptTime,windVector);
			}
		}
	}

	virtual void Tick(FLOAT DeltaTime)
	{
		if (MMaxDistanceScaleChangeVel != 0.0f)
		{
			FLOAT DeltaScale = MMaxDistanceScaleChangeVel * DeltaTime;
			MMaxDistanceScale += DeltaScale;
		}
		for (TApexClothingPieceVector::iterator i=MPieces.begin(); i!=MPieces.end(); ++i)
		{
			ApexClothingPiece *ap = (*i);
			if ( ap )
			{
				if (MMaxDistanceScaleChangeVel != 0.0f)
				{
					ap->SetMaxDistanceScale(MMaxDistanceScale, MMaxDistanceScaleMode);
				}
				ap->Tick(DeltaTime);
			}
		}
	}

	virtual void SetMaxDistanceScale(FLOAT StartScale, FLOAT EndScale, INT ScaleMode, FLOAT Duration)
	{
		MMaxDistanceScale = StartScale;
		MMaxDistanceScaleTarget = EndScale;
		MMaxDistanceScaleMode = static_cast<EMaxDistanceScaleMode>(ScaleMode);

		if (Duration > 0)
		{
			MMaxDistanceScaleChangeVel = (EndScale - StartScale) / Duration;
		}
		else
		{
			MMaxDistanceScale = EndScale;
			MMaxDistanceScaleChangeVel = 0;
			for (TApexClothingPieceVector::iterator i=MPieces.begin(); i!=MPieces.end(); ++i)
			{
				ApexClothingPiece *ap = (*i);
				if ( ap )
				{
					ap->SetMaxDistanceScale(MMaxDistanceScale, MMaxDistanceScaleMode);
				}
			}
		}
	}

	virtual UBOOL IsNewFrame(physx::PxU32 &NewFrame) const
	{
		UBOOL ret = FALSE;
		if ( MApexScene && NewFrame != MApexScene->GetSimulationCount() )
		{
			NewFrame = MApexScene->GetSimulationCount();
			ret = TRUE;
		}
		return ret;
	}
	virtual void ToggleClothingSimulation(const UBOOL& bEnableSimulation)
	{
		for (TApexClothingPieceVector::iterator i=MPieces.begin(); i!=MPieces.end(); ++i)
		{
			ApexClothingPiece *Ap = (*i);
			if ( Ap )
			{
				Ap->ToggleClothingPieceSimulation(bEnableSimulation);
			}
		}
	}

	virtual void SetVisible( UBOOL bEnable )
	{
		for (TApexClothingPieceVector::iterator i=MPieces.begin(); i!=MPieces.end(); ++i)
		{
			ApexClothingPiece* ClothingPiece = (*i);
			if ( ClothingPiece )
			{
				ClothingPiece->SetVisible( bEnable );
			}
		}
	}


	virtual UBOOL GetBounds(FBoxSphereBounds& NewBounds)
	{
		UBOOL bUpdated = FALSE;
		FBoxSphereBounds Bounds;

		for (TApexClothingPieceVector::iterator i=MPieces.begin(); i!=MPieces.end(); ++i)
		{
			UINT NoOfBounds = 0;
			ApexClothingPiece* ClothingPiece = (*i);
			if ( ClothingPiece )
			{
				FBoxSphereBounds PieceBounds;
				if (ClothingPiece->GetBounds(PieceBounds))
				{
					NoOfBounds++;
					if(NoOfBounds == 1)
					{
						Bounds = PieceBounds;
					}
					else
					{
						Bounds = Bounds + PieceBounds;
					}
					bUpdated = TRUE;
				}
			}
		}

		if (bUpdated)
			NewBounds = Bounds;

		return bUpdated;
	}
	virtual void SetMaterial(INT MaterialIndex, UMaterialInterface *Material )
	{
		for (TApexClothingPieceVector::const_iterator i=MPieces.begin(); i!=MPieces.end(); ++i)
		{
			ApexClothingPiece *ap = (*i);
			if (ap->UsesMaterialIndex(MaterialIndex))
			{
				ap->SetMaterial(MaterialIndex, Material);
				break;
			}
		}
	}
	virtual INT	GetNumVertices(INT LodIndex, INT SectionIndex)
	{
		INT NumVertices = 0;
		for (TApexClothingPieceVector::const_iterator i=MPieces.begin(); i!=MPieces.end(); ++i)
		{
			ApexClothingPiece *ClothingPiece = (*i);
			NumVertices += ClothingPiece->GetNumVertices(LodIndex, SectionIndex);
		}
		return NumVertices;
	}
//private:

	FIApexScene			   		*MApexScene;
	TApexClothingPieceVector 	MPieces;
	physx::PxU32						MBoneCount;
	UBOOL						MSyncReady;
	physx::PxMat44	    		*MMatrices;
	physx::PxU32						MPumpCount;
	UBOOL				    	MNeedsRefresh;
	TBoneRefVector				MBones;
	TPxU32Array					MUsedBones;
	physx::PxU32						MVisibleFrame;
	UBOOL						MPreviouslyVisible; // true if this clothing was previously visible on the last frame.
	physx::PxU32                       MUpdateReady;
	physx::PxU32						MReadyToRender;

	physx::PxF32				MMaxDistanceScale;
	physx::PxF32				MMaxDistanceScaleTarget;
	physx::PxF32				MMaxDistanceScaleChangeVel;
	EMaxDistanceScaleMode		MMaxDistanceScaleMode;

	/** Used to indicate we should force 'teleport' during the next call to SyncPieceTransforms */
	UBOOL bForceTeleport;
	/** Used to indicate we should force 'teleport and reset' during the next call to SyncPieceTransforms */
	UBOOL bForceTeleportAndReset;
	/** The scale applied to the clothing actor. **/
	physx::PxF32				MActorScale;
};

ApexClothingPiece::~ApexClothingPiece(void)
{
	if ( MActor )
	{
		physx::apex::NxClothingActor *ClothingActor = static_cast< physx::apex::NxClothingActor *>(MActor->GetNxApexActor());
		if(ClothingActor)
		{
			ClothingActor->setVelocityCallback(NULL);
		}
		MActor->Release();
	}
}

void ApexClothingPiece::NotifySceneGone(void)
{
	if ( MActor )
	{
		MActor->Release();
		MActor = NULL;
	}
}

UBOOL ApexClothingPiece::IsReady(const physx::PxF32 *eyePos)
{
	if ( MAsset && !MAsset->IsReady() )
	{
		if(FALSE)
		{
			debugf(TEXT("CLOTHING NOT READY! MAsset=%x IsReady()=%d"), MAsset, MAsset->IsReady());
		}

		return FALSE;
	}
	UBOOL bHasLODChanged = FALSE;
	if(MActor)
	{
		NxClothingActor *Act = static_cast< NxClothingActor *>(MActor->GetNxApexActor());
		if(Act)
		{
			bHasLODChanged = (MPrevLOD > 0.0f && Act->getActivePhysicalLod() == 0.0f);
		}
	}

	UBOOL bIsReady = MReady && (MSimulateCount > 1 ? TRUE : FALSE) && !bHasLODChanged && MGraphicalLODAvailable;

	if(FALSE /*!bIsReady*/)
	{
		debugf(TEXT("CLOTHING NOT READY!  MReady=%d MSimulateCount=%d bHasLODChanged=%d MGraphicalLODAvailable=%d"), MReady, MSimulateCount, bHasLODChanged, MGraphicalLODAvailable);
	}

	return bIsReady;
};

/** Called to update the bone transforms of one piece of clothing */
void ApexClothingPiece::SyncPieceTransforms(const physx::PxMat44 *transforms,UBOOL previouslyVisible, const physx::PxMat44& LocalToWorld, UBOOL bForceTeleportAndReset, UBOOL bForceTeleport)
{
	if ( !MBoneMapping.empty() )
	{
		TBaseBoneRefArray::iterator i;
		for (i=MBoneMapping.begin(); i!=MBoneMapping.end(); i++)
		{
			BaseBoneRef &b = (*i);
			b.MTransform = transforms[b.MBaseIndex];
		}

		// NVCHANGE_BEGIN: PHATT - Cleanup and AnimSetViewer bug
		if ( MActor && MActor->GetNxApexActor() )
		// NVCHANGE_END: PHATT - Cleanup and AnimSetViewer bug
		{
			physx::PxMat44 CurrentTransform = transforms[ MBoneMapping[0].MBaseIndex ];
			physx::PxMat33 A( CurrentTransform.getBasis(0), CurrentTransform.getBasis(1), CurrentTransform.getBasis(2) );
			physx::PxMat33 B( MRootPose.getBasis(0), MRootPose.getBasis(1), MRootPose.getBasis(2) );
			physx::PxMat33 AInvB = A*B.getInverse();
			physx::PxF32 Trace = AInvB(0,0) + AInvB(1,1) + AInvB(2,2);
			physx::PxF32 CosineTheta = (Trace - 1.0f) / 2.0f;
			NxClothingActor *Act = static_cast< NxClothingActor *>(MActor->GetNxApexActor());
			// NVCHANGE_BEGIN: PHATT - Cleanup and AnimSetViewer bug
			check(Act != NULL);
			if(MGraphicalLODAvailable)
			{
				Act->forcePhysicalLod(-1);
			}
			else
			{
				Act->forcePhysicalLod(0);
			}
			// NVCHANGE_END: PHATT - Cleanup and AnimSetViewer bug
			// if visible, or want to not 
			if ( previouslyVisible || !MSkeletalMeshComponent->bAutoFreezeApexClothingWhenNotRendered)
			{
				if ( !MWasVisible )
				{
					//debugf(TEXT("WARP: Clothing is now visible but previously was not"));
					if( !bForcedHidden )
					{
						Act->setVisible(true);
					}
					Act->setFrozen(false);
					//debugf(TEXT("VIS/FROZEN"));
					MWasVisible = TRUE;
				}
				// NVCHANGE_END: PHATT - Cleanup and AnimSetViewer bug
				// NVCHANGE_BEGIN: APEX 1.2 teleport mode

				ClothingTeleportMode::Enum TeleMode = ClothingTeleportMode::Continuous;

				if(bForceTeleportAndReset)
				{
					TeleMode = ClothingTeleportMode::TeleportAndReset;
				}
				else if(bForceTeleport)
				{
					TeleMode = ClothingTeleportMode::Teleport;
				}
				else if ( CosineTheta < MContinuousRotationThreshold ) // has the root bone rotated too much.
				{
					TeleMode = MTeleportationMode;
					//debugf(TEXT("WARP: Continuous Rotation Threshold"));
				}
				// NVCHANGE_END: APEX 1.2 teleport mode
				else
				{
					physx::PxF32 dist =  (MRootPose.getPosition() - CurrentTransform.getPosition()).magnitudeSquared();
					if ( dist > mContinousDistanceThreshold ) // if it has traveled too far.
					{
						TeleMode = MTeleportationMode;
						//debugf(TEXT("WARP: Continuous Distance Threshold"));
					}
				}
				MRootPose = CurrentTransform;
				TBaseBoneRefArray::iterator i;
				for (i=MBoneMapping.begin(); i!=MBoneMapping.end(); i++)
				{
					BaseBoneRef &b = (*i);
					b.MTransform = transforms[b.MBaseIndex];
				}
		
				// NVCHANGE_BEGIN: PHATT - Cleanup and AnimSetViewer bug
				MPrevLOD = Act->getActivePhysicalLod();
				Act->updateState(LocalToWorld,&MBoneMapping[0].MTransform,sizeof(BaseBoneRef),(physx::PxU32)MBoneMapping.size(), TeleMode);
				//debugf(TEXT("  updateState %d"), (INT)TeleMode);

	#if 0
				// Debug code for drawing bone locations
				if(TeleMode == ClothingTeleportMode::TeleportAndReset)
				{
					for (i=MBoneMapping.begin(); i!=MBoneMapping.end(); i++)
					{
						BaseBoneRef &b = (*i);
						physx::PxMat44 PTM = transforms[b.MBaseIndex];
						physx::PxVec3 PBonePos = PTM.getPosition();
						FVector BonePos(PBonePos.x, PBonePos.y, PBonePos.z);
						debugf(TEXT("DrawBone %s"), *BonePos.ToString());
						GWorld->PersistentLineBatcher->DrawLine(FVector(0,0,0), P2UScale * BonePos, FColor(255,255,0), SDPG_World);
					}
				}
	#endif
				MReady = (Act->getActivePhysicalLod() > 0);
			}
			else
			{
				if ( MWasVisible )
				{
					//debugf(TEXT("CLOTHING NO LONGER VISIBLE"));
					MWasVisible = FALSE;
					MPrevLOD = Act->getActivePhysicalLod();
				}
				MReady = TRUE;
			}
		}
		else if (MParameterized)
		{
			NxParameterized::ErrorType Error = NxParameterized::ERROR_NONE;
			NxParameterized::Handle arrayHandle( MParameterized );
			Error = MParameterized->getParameterHandle( "boneMatrices", arrayHandle ); checkf(Error == NxParameterized::ERROR_NONE, TEXT("Error code: %i"), Error);
			Error = arrayHandle.resizeArray(MBoneMapping.size()); checkf(Error == NxParameterized::ERROR_NONE, TEXT("Error code: %i"), Error);
			for (UINT i = 0; i < MBoneMapping.size(); ++i)
			{
				Error = arrayHandle.set( i ); checkf(Error == NxParameterized::ERROR_NONE, TEXT("Error code: %i"), Error);
				Error = arrayHandle.setParamMat44( MBoneMapping[i].MTransform ); checkf(Error == NxParameterized::ERROR_NONE, TEXT("Error code: %i"), Error);
				arrayHandle.popIndex();
			}
			physx::PxF32 scale = LocalToWorld.column0.magnitude();
			physx::PxF32 eps = 0.0001;
			physx::PxF32 scale1 = LocalToWorld.column1.magnitude();
			physx::PxF32 scale2 = LocalToWorld.column2.magnitude();
			if (
				abs(scale - scale1) > eps ||
				abs(scale - scale2) > eps
				)
			{
				debugf( TEXT("APEX Clothing does not support non-uniform scales."));
			}
			NxParameterized::setParamF32(*MParameterized, "actorScale", scale);
		}
	}
}

void ApexClothingPiece::Render(NxUserRenderer &renderer)
{
	if ( MActor )
	{
		MActor->Render(renderer);
	}
}

void ApexClothingPiece::UpdateRenderResources(void)
{
	if ( MActor )
	{
		MActor->UpdateRenderResources( NULL );
	}
}
void ApexClothingPiece::SetGraphicalLOD( physx::PxU32 lod )
{
	if (MActor)
	{
		NxClothingActor *Act = static_cast< NxClothingActor *>(MActor->GetNxApexActor());
		//MCurrGraphicalLOD = lod;

		if(Act)
		{
			if((physx::PxU32)MGraphicalLODNum > lod)
			{	
				MGraphicalLODAvailable = TRUE;
				if(Act->isVisible())
				{
					Act->setFrozen(FALSE);
				}
				Act->setGraphicalLOD(lod);
				USkeletalMesh* SkelMesh = MSkeletalMeshComponent->SkeletalMesh;
				UApexClothingAsset* ClothingAsset = static_cast<UApexClothingAsset*>(MAsset->GetUE3Object());
				for(INT SubmeshIndex = 0; SubmeshIndex< MClothingLODInfo(lod).ClothingSectionInfo.Num(); SubmeshIndex++)
				{
					UMaterialInterface* Material = GetMaterial(lod, SubmeshIndex);
					SetMaterial(GetMaterialIndex(lod, SubmeshIndex), Material);
				}
			}
			else
			{
				MGraphicalLODAvailable = FALSE;
				if(MSkeletalMeshComponent->bAutoFreezeApexClothingWhenNotRendered)
				{
					Act->setFrozen(TRUE);
				}
			}
		}
	}
}

void ApexClothingPiece::Pump(void)
{

	if ( MActor == 0 ) // if we haven't created an actor yet....
	{
		if ( MParent->MSyncReady ) // and our parent has received live transform data...
		{
			setParamF32(*MParameterized, "actorScale", MParent->MActorScale);
			MActor = MParent->GetApexScene()->CreateApexActor(MAsset,MParameterized);
			if ( MParameterized )
			{
				MParameterized->destroy();
				MParameterized = NULL;
			}
			physx::apex::NxClothingActor *clothingActor = static_cast< physx::apex::NxClothingActor *>(MActor->GetNxApexActor());
			clothingActor->setVelocityCallback(this);
			NxClothingAsset* ClothingAsset = static_cast<NxClothingAsset*>(MAsset->GetNxApexAsset());
			MGraphicalLODNum = ClothingAsset->getNumGraphicalLodLevels();
			NxResourceProvider* ApexResourceProvider = GApexManager->GetApexSDK()->getNamedResourceProvider();
			for(UINT LodLevel = 0; LodLevel < ClothingAsset->getNumGraphicalLodLevels(); ++LodLevel)
			{
				const NxRenderMeshAsset* RenderMeshAsset = ClothingAsset->getRenderMeshAsset(LodLevel);
				for(UINT SubmeshID = 0; SubmeshID < RenderMeshAsset->getSubmeshCount(); SubmeshID++)
				{
					UApexClothingAsset* ClothingAsset = static_cast<UApexClothingAsset*>(MAsset->GetUE3Object());
					UMaterialInterface* ClothingMaterial = ClothingAsset->GetMaterial(ClothingAsset->LodMaterialInfo(LodLevel).LODMaterialMap(SubmeshID));
					ApexResourceProvider->setResource( "ApexMaterials", RenderMeshAsset->getMaterialName(SubmeshID), ClothingMaterial, true );
				}
			}
			for(INT LodLevel = 0; LodLevel < MOverrideMats.Num(); LodLevel++)
			{
				clothingActor->setOverrideMaterial(LodLevel, TCHAR_TO_ANSI(*MOverrideMats(LodLevel)->GetPathName()));
			}
		}
	}
	else if ( MActor->GetNxApexActor() == 0  && MParent->MMatrices)
	{
		if(MParameterized == 0)
		{
			MParent->SetNeedsRefresh(TRUE);
		}
		else
		{
			setParamF32(*MParameterized, "actorScale", MParent->MActorScale);
			MParent->GetApexScene()->RecreateApexActor(MActor,MParameterized);
			MParameterized->destroy();
			MParameterized = NULL;
			BuildBoneMapping();
			physx::apex::NxClothingActor *clothingActor = static_cast< physx::apex::NxClothingActor *>(MActor->GetNxApexActor());
			clothingActor->setVelocityCallback(this);
			NxClothingAsset* ClothingAsset = static_cast<NxClothingAsset*>(MAsset->GetNxApexAsset());
			MGraphicalLODNum = ClothingAsset->getNumGraphicalLodLevels();
			NxResourceProvider* ApexResourceProvider = GApexManager->GetApexSDK()->getNamedResourceProvider();
			for(UINT LodLevel = 0; LodLevel < ClothingAsset->getNumGraphicalLodLevels(); ++LodLevel)
			{
				const NxRenderMeshAsset* RenderMeshAsset = ClothingAsset->getRenderMeshAsset(LodLevel);
				for(UINT SubmeshID = 0; SubmeshID < RenderMeshAsset->getSubmeshCount(); SubmeshID++)
				{
					UApexClothingAsset* ClothingAsset = static_cast<UApexClothingAsset*>(MAsset->GetUE3Object());
					UMaterialInterface* ClothingMaterial = ClothingAsset->GetMaterial(ClothingAsset->LodMaterialInfo(LodLevel).LODMaterialMap(SubmeshID));
					ApexResourceProvider->setResource( "ApexMaterials", RenderMeshAsset->getMaterialName(SubmeshID), ClothingMaterial, true );
				}
			}
			for(INT LodLevel = 0; LodLevel < MOverrideMats.Num(); LodLevel++)
			{
				clothingActor->setOverrideMaterial(LodLevel, TCHAR_TO_ANSI(*MOverrideMats(LodLevel)->GetPathName()));
			}
		}
	}
	else if ( MActor )
	{
		if ( MActor->GetNxApexActor() )
		{
			MSimulateCount++;
		}
		else
		{
			MParent->SetNeedsRefresh(TRUE);
			MSimulateCount = 0;
			MReady = FALSE;
		}
	}
}
void ApexClothingPiece::SetDistanceWeightLODMultiplier( const physx::PxF32 Multiplier )
{
	if(MActor)
	{
		NxClothingActor *Act = static_cast< NxClothingActor *>(MActor->GetNxApexActor());
		if(Act)
		{
			physx::PxF32 DecayMultiplier =  physx::PxClamp(Multiplier, 0.0f, 1.0f);
			physx::PxF32 Benefit = MLodWeightsDistanceWeight * DecayMultiplier;
			if(Benefit < MIN_BENEFIT)
			{
				Benefit = MIN_BENEFIT;
			}
			NxParameterized::Interface* ActorDesc = Act->getActorDesc();
			NxParameterized::setParamF32(*ActorDesc, "lodWeights.distanceWeight", Benefit);
		}
	}
}

void ApexClothingPiece::Tick( FLOAT DeltaTime )
{
	if(MParent->IsVisible(FALSE))
	{
		MCurrDecayTime = 0.0f;
		SetDistanceWeightLODMultiplier(1.0f);
	}
	else
	{
		MCurrDecayTime += DeltaTime;
		SetDistanceWeightLODMultiplier(1.0f - (MCurrDecayTime/MLODTotalDecayTime));
	}
	
}

static void GetBoneName(const char *bone,char *dest)
{
	for (physx::PxU32 i=0; i<255; i++)
	{
		char c = *bone++;
		if ( c == 0 )
		{
		    break;
		}
		if ( c >= 'A' && c <= 'Z' )
		{
		    c+=32;
		}
		if ( c == 32 )
		{
		    c = '-';
		}
		if ( c == '_' )
		{
		    c = '-';
		}
		*dest++ = c;
	}
	*dest = 0;
}
static UBOOL SameBoneName(const char *a,const char *b)
{
	char bone1[256];
	char bone2[256];
	GetBoneName(a,bone1);
	GetBoneName(b,bone2);
	return strcmp(bone1,bone2) == 0 ? TRUE : FALSE;
}

void ApexClothingPiece::BuildBoneMapping(void)
{

	MBoneMapping.clear();

	if ( MAsset )
	{
		NxApexAsset *apexAsset = MAsset->GetNxApexAsset();
		NxClothingAsset *clothingAsset = static_cast< NxClothingAsset *>(apexAsset);
		physx::PxU32 usedCount = clothingAsset->getNumUsedBones();

		for (physx::PxU32 i=0; i<usedCount; i++)
		{
			const char *boneName = clothingAsset->getBoneName(i);
			UBOOL found = FALSE;
			physx::PxU32 refIndex = 0;
			physx::PxMat44 worldBindPose;
			if ( MParent->MBones.empty() )
			{
				refIndex = i;
				found = TRUE;
			}
			else
			{
    			TBoneRefVector::iterator j;
    			for (j=MParent->MBones.begin(); j!=MParent->MBones.end(); ++j)
    			{
    				BoneRef &b = (*j);
    				if ( SameBoneName(b.MBoneName, boneName) )
    				{
    					found = TRUE;
    					break;
    				}
    				refIndex++;
    			}
			}
			// Handling of applying a clothing asset to the wrong skeletal mesh
			if ( !found )
			{
				// This probably indicates a clothing asset has been applied to the wrong skeletal mesh
				debugf( NAME_DevPhysics, TEXT("BuildBoneMapping() unable to find bone %s"), ANSI_TO_TCHAR(boneName) );
			    refIndex = 0;
			}
			BaseBoneRef b;
			b.MBaseIndex = refIndex;
			clothingAsset->getBoneBasePose(i,b.MTransform);
			MBoneMapping.push_back(b);
		}
	}
	MParent->RefreshBoneMapping();
}


typedef NxArray< ApexClothing * >	TApexClothingVector;
typedef NxArray< ApexActor * > 		TApexActorVector;

class ApexScene;

#if WITH_APEX_PARTICLES
class ApexEmitter;
typedef NxArray< ApexEmitter * >	TApexEmitterVector;


class ApexEmitter : public FApexEmitter
{
	static void ReleaseCallback(void* CallbackData)
	{
		NxApexRenderVolume* RenderVolume = static_cast<NxApexRenderVolume*>(CallbackData);
		if (RenderVolume != NULL)
		{
			NxModuleIofx *iofx = GApexManager->GetModuleIofx();
			iofx->releaseRenderVolume(*RenderVolume);
		}
	}

public:

	ApexEmitter(FIApexScene *scene, FIApexAsset *asset, const FMatrix &pose)
	{
		mAsset = asset;
		mRenderVolume = NULL;
		mScene = scene;
		mApexActor = NULL;

		mPose = pose;
		mDeferredActions = 0;
		mIsSpawning = TRUE;
		mSetSpawningWasCalled = FALSE;
		mBoundBox.Init();

		// NVCHANGE_BEGIN: Add Opacity Shadows
#if NV_OPACITY_SHADOWS
		mShadowBoundBox.Init();
#endif
		// NVCHANGE_END: Add Opacity Shadows

		if (mScene->IsSimulating())
		{
			mDeferredActions = DEFERRED_CREATE;
			return;
		}
		doCreate();
	}

	~ApexEmitter(void)
	{
		if ( mApexActor )
		{
			mApexActor->Release(&ReleaseCallback, mRenderVolume);
		}
	}
	virtual void UpdateBoundingBox(FBox &box) 
	{
		box = mBoundBox;
	}

	// NVCHANGE_BEGIN: Add Opacity Shadows
#if NV_OPACITY_SHADOWS
	virtual void UpdateShadowBoundingBox(FBox &box)
	{
		box = mShadowBoundBox;
	}
#endif
	// NVCHANGE_END: Add Opacity Shadows

	virtual void SetPose(const FMatrix &pose) 
	{
		mPose = pose;
		if (mScene->IsSimulating())
		{
			mDeferredActions |= DEFERRED_SET_POSE;
			return;
		}
		doSetPose();
	}
	virtual void SetSpawning(UBOOL isSpawning)
	{
		mSetSpawningWasCalled = TRUE;
		if (mIsSpawning == isSpawning)
		{
			return;
		}
		mIsSpawning = isSpawning;

		if (mScene->IsSimulating())
		{
			mDeferredActions |= DEFERRED_SET_SPAWNING;
			return;
		}
		doSetSpawning();
	}

	// NVCHANGE_BEGIN: JCAO - Add interface to control the rate of Apex Emitter
	virtual void SetRate(FLOAT MinRate, FLOAT MaxRate)
	{
		doSetRate(MinRate, MaxRate);
	}
	// NVCHANGE_END: JCAO - Add interface to control the rate of Apex Emitter

	virtual void release(void)
	{
		// NVCHANGE_BEGIN: DJS - Work around crash when deleting an emitter while it's being rendered
		// For now we unconditionally perform deferred release because it's not safe to 
		// release something while it's being rendered. It's not yet known whether even 
		// this is safe.
		if (TRUE)
		{
			mDeferredActions |= DEFERRED_RELEASE;
			return;
		}
		else
		{
			doRelease();
		}
		// NVCHANGE_END: DJS - Work around crash when deleting an emitter while it's being rendered
	}

	virtual void notifySceneGone(void)
	{
		if ( mApexActor )
		{
			mApexActor->Release(&ReleaseCallback, mRenderVolume);
			mApexActor = NULL;
			mRenderVolume = NULL;
		}
		mScene = NULL;
	}

	virtual void Render(physx::apex::NxUserRenderer &Renderer) 
	{
		PX_FORCE_PARAMETER_REFERENCE(Renderer);
		if ( mRenderVolume )
		{
			//debugf(NAME_DevPhysics, TEXT("EmitterRender"));
			mRenderVolume->lockRenderResources();

			physx::PxU32 numIofxActors;
			physx::apex::NxIofxActor* const* iofxActors = mRenderVolume->getIofxActorList(numIofxActors);
			check(numIofxActors <= 1);
			if (iofxActors != NULL)
			{
				physx::apex::NxIofxActor* iofxActor = iofxActors[0];

				iofxActor->lockRenderResources();
				if (!iofxActor->getBounds().isEmpty())
				{
					iofxActor->updateRenderResources();
					iofxActor->dispatchRenderResources(Renderer);
				}
				iofxActor->unlockRenderResources();
			}

			mRenderVolume->unlockRenderResources();
		}
	}

  virtual UBOOL IsEmpty(void)
  {
	  return (mBoundBox.IsValid == 0) ? TRUE : FALSE;
  }

  virtual UBOOL IsEmitting(void)
  {
	  return (mApexActor && mApexActor->GetNxApexActor()) ? static_cast<NxApexEmitterActor*>(mApexActor->GetNxApexActor())->isEmitting() : ((mDeferredActions & DEFERRED_CREATE) != 0);
  }

  virtual void NotifyAssetModified(NxApexAsset *asset)
  {
	  if ( mApexActor && mApexActor->GetNxApexActor() )
	  {
		  NxApexEmitterActor *emitter = static_cast<NxApexEmitterActor *>(mApexActor->GetNxApexActor());
		  NxApexEmitterAsset *emitter_asset = emitter->getEmitterAsset();
		  UBOOL rebuild = FALSE;
		  if ( strcmp(asset->getObjTypeName(),NX_IOFX_AUTHORING_TYPE_NAME) == 0)
		  {
			  rebuild =  strcmp(emitter_asset->getInstancedObjectEffectsAssetName(),asset->getName()) == 0 ? TRUE : FALSE;
		  }
		  else
		  {
			  rebuild = strcmp(emitter_asset->getInstancedObjectSimulatorAssetName(),asset->getName()) == 0 && strcmp(emitter_asset->getInstancedObjectSimulatorTypeName(),asset->getObjTypeName()) == 0 ? TRUE : FALSE;
		  }
		  if ( rebuild )
		  {
			  // need to release the actor!
			  mApexActor->NotifyAssetModified();
		  }
	  }
  }

  void NotifyAssetGoingAway(NxApexAsset *asset)
  {
	  if ( mApexActor && mApexActor->GetNxApexActor() )
	  {
		  NxApexEmitterActor *emitter = static_cast<NxApexEmitterActor *>(mApexActor->GetNxApexActor());
		  NxApexEmitterAsset *emitter_asset = emitter->getEmitterAsset();
		  UBOOL rebuild = FALSE;
		  if ( strcmp(asset->getObjTypeName(),NX_IOFX_AUTHORING_TYPE_NAME) == 0)
		  {
			rebuild =  strcmp(emitter_asset->getInstancedObjectEffectsAssetName(),asset->getName()) == 0 ? TRUE : FALSE;
		  }
		  else
		  {
			  rebuild = strcmp(emitter_asset->getInstancedObjectSimulatorAssetName(),asset->getName()) == 0 && strcmp(emitter_asset->getInstancedObjectSimulatorTypeName(),asset->getObjTypeName()) == 0 ? TRUE : FALSE;
		  }
		  if ( rebuild )
		  {
			  // need to release the actor!
			  mApexActor->NotifyAssetGone();
		  }
	  }
  }
  // NVCHANGE_BEGIN: JCAO - Apex Emitter Asset work with LODs
  virtual void SwitchLOD(void)
  {
	  if ( mApexActor && mApexActor->GetNxApexActor() )
	  {
		  mApexActor->NotifyAssetGone();
	  }
  }
  // NVCHANGE_END: JCAO - Apex Emitter Asset work with LODs
  virtual UBOOL NeedsRebuild(void)
  {
	  if (mDeferredActions & DEFERRED_CREATE) return FALSE;
	  if ( mApexActor == NULL ) return TRUE;
	  return mApexActor->NeedsRebuild();
  }

  virtual const char * GetAssetName(void) 
  {
	  return mAsset ? mAsset->GetAssetName() : NULL;
  }
  virtual FIApexScene * GetApexScene(void) 
  {
	  return mScene;
  }

	void OnPostFetchResults()
	{
		if (mDeferredActions & DEFERRED_RELEASE)
		{
			if (true || IsEmpty())
			{
				doRelease();
				//this is deleted, so we don't need to zero mDeferredAction here
			}
			else
			{
				updateBoundingBox();
			}
			return;
		}
		if (mDeferredActions & DEFERRED_CREATE)
		{
			doCreate();
			//skip additional setPose on create
			mDeferredActions &= ~DEFERRED_SET_POSE;
		}
		if (mDeferredActions & DEFERRED_SET_POSE)
		{
			doSetPose();
		}
		if ((mDeferredActions & DEFERRED_SET_SPAWNING) != 0 || mSetSpawningWasCalled == FALSE)
		{
			// disable spawning if SetSpawning was not called
			if (mSetSpawningWasCalled == FALSE)
			{
				mIsSpawning = FALSE;
			}
			doSetSpawning();
		}
		mDeferredActions = 0;
		mSetSpawningWasCalled = FALSE;

		//update bounding box
		updateBoundingBox();
	}

	void doRelease(void);
	void doCreate(void)
	{
#if !WITH_APEX_SHIPPING
		mAsset->ApplyOutstandingEdits();
#endif
		NxParameterized::Interface *iface = mAsset->GetDefaultApexActorDesc();
		check(iface);
		if ( iface )
		{
// NVCHANGE_BEGIN: LRR - Let's just use the 44 interfaces now, we're fazing out the 34
			physx::PxMat44 pxPose44;
			FMatrixToPxMat44(mPose, pxPose44);
			NxParameterized::setParamMat44(*iface, "initialPose", pxPose44);
// NVCHANGE_END: LRR - Let's just use the 44 interfaces now, we're fazing out the 34

			mApexActor = mScene->CreateApexActor(mAsset, iface);
			NxModuleIofx *iofx = GApexManager->GetModuleIofx();
			if ( mApexActor && mApexActor->GetNxApexActor() && iofx )
			{
				
				physx::PxBounds3 b;
				b.setInfinite();
#if HACK_GLOBAL_RENDER_VOLUME
				static NxApexRenderVolume *gVolume=NULL;
				if ( gVolume == NULL )
				{
					mRenderVolume = iofx->createRenderVolume(*mScene->GetApexScene(), b, 0, true);
					gVolume = mRenderVolume;
				}
				else
				{
					mRenderVolume = gVolume;
				}
#else
				mRenderVolume = iofx->createRenderVolume(*mScene->GetApexScene(), b, 0, true);
#endif
				NxApexEmitterActor *aea = static_cast<NxApexEmitterActor *>(mApexActor->GetNxApexActor());
				aea->setPreferredRenderVolume(mRenderVolume);
			}
		}
	}

	void doSetPose(void)
	{
		if ( mApexActor && mApexActor->GetNxApexActor() )
		{
			physx::PxMat34Legacy pose = U2NTransformApex(mPose);
			physx::PxMat44 mat = pose;
			NxApexEmitterActor *ae = static_cast< NxApexEmitterActor *>(mApexActor->GetNxApexActor());
			ae->setCurrentPose(mat);
		}
	}
	void doSetSpawning(void)
	{
		if ( mApexActor && mApexActor->GetNxApexActor() )
		{
			NxApexEmitterActor *ae = static_cast< NxApexEmitterActor *>(mApexActor->GetNxApexActor());
			if (mIsSpawning)
			{
				ae->startEmit(false);
			}
			else
			{
				ae->stopEmit();
			}
		}
	}

	// NVCHANGE_BEGIN: JCAO - Add interface to control the rate of Apex Emitter
	void doSetRate( FLOAT MinRate, FLOAT MaxRate )
	{
		if ( mApexActor && mApexActor->GetNxApexActor() )
		{
			NxApexEmitterActor *ae = static_cast< NxApexEmitterActor *>(mApexActor->GetNxApexActor());
			if(ae)
			{
				NxRange< physx::PxF32 > r;
				r.minimum = MinRate;
				r.maximum = MaxRate;
				ae->setRateRange(r);
			}
		}
	}
	// NVCHANGE_END: JCAO - Add interface to control the rate of Apex Emitter

	NxApexRenderVolume	*mRenderVolume;
	FIApexScene *mScene;
	FIApexActor	*mApexActor;
	FIApexAsset *mAsset;

	FMatrix		mPose;

	enum
	{
		DEFERRED_CREATE = 0x01,
		DEFERRED_RELEASE = 0x02,
		DEFERRED_SET_POSE = 0x04,
		DEFERRED_SET_SPAWNING = 0x08
	};
	UINT		mDeferredActions;
	UBOOL		mIsSpawning;
	UBOOL		mSetSpawningWasCalled;

	FBox		mBoundBox;

	// NVCHANGE_BEGIN: Add Opacity Shadows
#if NV_OPACITY_SHADOWS
	FBox		mShadowBoundBox;
#endif
	// NVCHANGE_END: Add Opacity Shadows

private:
	void updateBoundingBox(void)
	{
		//update bounding box
		if ( mRenderVolume )
		{
			mBoundBox.Init();

			physx::PxBounds3 b = mRenderVolume->getBounds();
			if (!b.isEmpty())
			{
				mBoundBox.Min = N2UPositionApex(b.minimum);
				mBoundBox.Max = N2UPositionApex(b.maximum);
				mBoundBox.IsValid = 1;

				// NVCHANGE_BEGIN: Add Opacity Shadows
#if NV_OPACITY_SHADOWS
				// Should be as tight as possible for the opacity shadow maps to be allocated efficiently.
				mShadowBoundBox = mBoundBox;
#endif
				// NVCHANGE_END: Add Opacity Shadows

				if ( mApexActor )
				{
					FIApexAsset* EmitterAsset = mApexActor->GetApexAsset();
					if (EmitterAsset)
					{
						mBoundBox = mBoundBox.ExpandBy(EmitterAsset->GetBoundingBoxExpansion());
					}
				}
			}
		}
	}
};
#endif

// NVCHANGE_BEGIN: LRR - Be careful how we scale a perspective matrix, it's not a normal transform
static physx::PxMat44 U2N44Perspective( const FMatrix& InTransform )
{
	FMatrix tmp(InTransform);

	// fix zNear to be the proper units
	tmp.M[3][2] *= U2PScale;

	return *(reinterpret_cast<physx::PxMat44*>( &tmp ));
}
// NVCHANGE_END: LRR - Be careful how we scale a perspective matrix, it's not a normal transform

#if USE_UE3_THREADPOOL

class ApexTask : public FNonAbandonableTask
{
	friend class FAutoDeleteAsyncTask<ApexTask>;
	physx::pxtask::Task *Target;

	ApexTask(physx::pxtask::Task *InTarget)
		: Target(InTarget)
	{
	}

	void DoWork()
	{
		Target->run();
		Target->release();
	}

	static const TCHAR *Name()
	{
		return TEXT("ApexTask");
	}
};

class ApexDispatcher : public physx::pxtask::CpuDispatcher
{
public:
	virtual void submitTask( physx::pxtask::Task& task )
	{
		(new FAutoDeleteAsyncTask<ApexTask>(&task))->StartHiPriorityTask();
	}
};

ApexDispatcher GApexDispatcher;

#endif

class ApexScene : public FIApexScene
{
public:

	ApexScene(NxScene *scene,FIApexManager *sdk,UBOOL useDebugRenderable)
  	{
  		MSimulateCount = 0;
		MUseDebugRenderable = useDebugRenderable;
	  	MScene = scene;
	  	MApexManager   = sdk;
	  	MApexSDK = sdk->GetApexSDK();
	  	MApexScene = NULL;
		mIsSimulating = FALSE;
	  	if ( MApexSDK )
	  	{
			NxApexSceneDesc apexSceneDesc;
#if USE_UE3_THREADPOOL
			apexSceneDesc.cpuDispatcher = GApexDispatcher;
#endif
			physx::pxtask::CudaContextManager *cudaContext = GApexManager->GetCudaContextManager();
			if ( cudaContext ) {
				apexSceneDesc.gpuDispatcher = cudaContext->getGpuDispatcher();
			}
		  	apexSceneDesc.scene = MScene;
		  	apexSceneDesc.useDebugRenderable = MUseDebugRenderable ? true : false;
#if WITH_APEX_GRB
			if(GApexManager->GetModuleDestructible())
			{
				if(!GIsGame)
				{
					apexSceneDesc.enableGrbPhysics = false;
				}
				else
				{
					apexSceneDesc.enableGrbPhysics = GSystemSettings.bEnableApexGRB ? true:false;
				}
			}
#endif
		  	MApexScene = MApexSDK->createScene(apexSceneDesc);
	  	}
	  	if ( MApexScene )
		{
			MApexScene->setUseDebugRenderable(MUseDebugRenderable ? true : false);
			physx::PxMat44 view = physx::PxMat44::createIdentity();
			// TODO: Is LOOK_AT_LH appropriate for all platforms?
			MViewID = MApexScene->allocViewMatrix( physx::apex::ViewMatrixType::LOOK_AT_LH );
			MApexScene->setViewMatrix(view,MViewID);
			MProjID = MApexScene->allocProjMatrix( physx::apex::ProjMatrixType::USER_CUSTOMIZED );
			MApexScene->setLODResourceBudget( GSystemSettings.ApexLODResourceBudget );

			// NVCHANGE_BEGIN: JCAO - Add field sampler group filter
#if WITH_APEX_PARTICLES
			physx::apex::NxModuleFieldSampler* moduleFieldSampler = GApexManager->GetModuleFieldSampler();
			if(moduleFieldSampler)
			{
				physx::apex::NxGroupsFilteringParams64 param;
				param.const0.bits0 = 0;
				param.const0.bits1 = 0;
				param.const1.bits0 = 0;
				param.const1.bits1 = 0;
				param.op0 = NxGroupsFilterOp::OR;
				param.op1 = NxGroupsFilterOp::OR;
				param.op2 = NxGroupsFilterOp::SWAP_AND;
				param.flag = true;

				moduleFieldSampler->setFieldSamplerGroupsFilteringParams(*MApexScene, param);
			}
#endif
			// NVCHANGE_END: JCAO - Add field sampler group filter
		}
	    GActiveApexSceneCount++;
		GApexCommands->AddApexScene(this);

		check( GSynchronizeFactory );
		RenderSyncEvent = GSynchronizeFactory->CreateSynchEvent();
		RenderSyncEvent->Trigger();
  	}

  ~ApexScene(void)
  {
	  // NVCHANGE_BEGIN: TSC - fix race condition with rendering commands & RenderSyncEvent
	  // Flush #1: do not touch the scene until all rendering commands in the pipeline are complete. 	  
	  FlushRenderingCommands();
	  // NVCHANGE_END: TSC - fix race condition with rendering commands & RenderSyncEvent

#if WITH_APEX_PARTICLES
	for (TApexEmitterVector::iterator i=MEmitters.begin(); i!=MEmitters.end(); ++i)
	{
		ApexEmitter *ae = (*i);
		if ( ae )
		{
			ae->notifySceneGone();
		}
	}
#endif
	for (TApexClothingVector::iterator i=MApexClothing.begin(); i != MApexClothing.end(); ++i)
	{
		ApexClothing *aa = (*i);
		if ( aa )
		{
			aa->NotifySceneGone();
		}
	}

	// NVCHANGE_BEGIN: TSC - fix race condition with rendering commands & RenderSyncEvent
	GApexCommands->RemoveApexScene(this);
	ENQUEUE_UNIQUE_RENDER_COMMAND_ONEPARAMETER
	(
		FEnqueData,
		FIApexRender *, e, GApexRender,
		{
			GApexRender->FlushFEnqueDataRenderingThread();
		}
	);

	// Flush #2: this also cleans up anything in PendingCleanupObjects, which is necessary after 
	//  the NotifySceneGone calls above
	FlushRenderingCommands();

	GApexRender->FlushFEnqueDataGameThread();

	if ( MApexScene )
	{
		MApexScene->release();
	}

	check( GSynchronizeFactory );
	GSynchronizeFactory->Destroy( RenderSyncEvent );
	// NVCHANGE_END: TSC - fix race condition with rendering commands & RenderSyncEvent

	  GActiveApexSceneCount--;
  }

  virtual UBOOL IsSimulating(void) const
  {
	  return mIsSimulating;
  }

  virtual void Simulate(physx::PxF32 dtime)
  {
	  CTRL_TICK("_ApexScene::Simulate");


		GApexCommands->Pump(); //  complete the 'force load' operation on outstanding APEX Assets from the Game Thread

		if ( GApexCommands->IsApexPaused() )
			return;

#if FAKE_LAG
		Sleep(60);
#endif

		if( GIsEditor && !GIsGame && (dtime > (1.0f/10.0f)) )
		{
			// if the simulation delta time is greater than 1/10th of a second, don't simulate clothing
			// Works around bad behavior in AnimSetViewer when holding down a button for a long time
			for (TApexClothingVector::iterator i=MApexClothing.begin(); i != MApexClothing.end(); ++i)
			{
				ApexClothing *aa = (*i);
				if ( aa )
				{
					// aa->DisableSimulateThisFrame();
				}
			}

		}

		if (MApexScene )
		{
			{
				DWORD IdleStart = appCycles();

				while(TRUE)
				{
					// Wait with a timeout for the event from the rendering thread; use a timeout to ensure that this doesn't deadlock
					// if the rendering thread crashes.
					if(RenderSyncEvent->Wait(100))
					{
						break;
					}

					// Break out of the loop with a fatal error if the rendering thread has crashed.
					CheckRenderingThreadHealth();
				}

				DWORD IdleTime = appCycles() - IdleStart;
				//appOutputDebugStringf(TEXT("ApexScene::Simulate IdleTime = %d\n"), IdleTime);
			}

// NVCHANGE_BEGIN: hlanker - clothing actor recording
			if (GApexCommands && GApexCommands->IsClothingRecording())
			{
				ClothingActorDump(dtime);
			}
// NVCHANGE_END: hlanker - clothing actor recording
			mIsSimulating = TRUE;
			MApexScene->simulate(dtime);
		}
		MSimulateCount++;
  }

	void OnRenderSyncCommand()
	{
		if (MApexScene)
		{
			MApexScene->prepareRenderResourceContexts();
		}
		// Trigger event to signal game thread.
		RenderSyncEvent->Trigger();
	}

  virtual UBOOL FetchResults(UBOOL forceSync,physx::PxU32 *errorState)
  {
	  UBOOL ret = TRUE;

	  if ( MApexScene && !GApexCommands->IsApexPaused() )
	  {
			ret = MApexScene->fetchResults(forceSync ? true : false,errorState);
			mIsSimulating = FALSE;

		    // ok, process clothing.
        	for (TApexClothingVector::iterator i=MApexClothing.begin(); i!=MApexClothing.end(); ++i)
        	{
        		ApexClothing *aa = (*i);
        		if ( aa )
        		{
        			aa->Pump();
        		}
        	}
#if WITH_APEX_PARTICLES
		    // process emitters.
        	for (TApexEmitterVector::iterator i=MEmitters.begin(); i!=MEmitters.end(); ++i)
        	{
        		ApexEmitter *ae = (*i);
        		if ( ae )
        		{
        			ae->OnPostFetchResults();
        		}
        	}
#endif
			{
				RenderSyncEvent->Reset();

				// Enqueue command to trigger event once the render thread executes it.
				ENQUEUE_UNIQUE_RENDER_COMMAND_ONEPARAMETER(
					ApexSceneRenderSyncCommand,
					ApexScene*,_ApexScene,this,
					{
						_ApexScene->OnRenderSyncCommand();
					});
			}
	  }
	  return ret;
  }

  virtual NxApexScene * GetApexScene(void) const { return MApexScene; };

  virtual FIApexActor   *CreateApexActor(FIApexAsset *ia,const ::NxParameterized::Interface *params)
  {
    FIApexActor *ret = NULL;

	if ( ia && params == NULL )
	{
		params = ia->GetDefaultApexActorDesc();
	}

    if ( ia && params )
    {
        ApexActor *aa = new ApexActor(this,ia,params);
        if ( aa->IsOk() )
        {
		  aa->MApexAsset->IncRefCount(aa);
          ret = static_cast< FIApexActor *>(aa);
        }
        else
        {
          delete aa;
        }
    }
    return ret;
  }

  virtual UBOOL			RecreateApexActor(FIApexActor *actor,const ::NxParameterized::Interface *params)
  {
	UBOOL ret = FALSE;

  	ApexActor *aa = static_cast< ApexActor *>(actor);
  	if ( aa )
  	{
  		ret = aa->Recreate(this,params);
  	}
  	return ret;
  }

  virtual NxApexScene *GetNxApexScene(void) const
  {
	  return MApexScene;
  }

  virtual const NxDebugRenderable * GetDebugRenderable(void)
  {
    const NxDebugRenderable *ret = NULL;
    if ( MApexScene && MUseDebugRenderable && GApexCommands->IsVisualizeApex() )
    {
		MApexScene->lockRenderResources();
		MApexScene->updateRenderResources();
		MApexScene->dispatchRenderResources(*GApexCommands->GetNxUserRenderer());
		MApexScene->unlockRenderResources();
		ret = MApexScene->getDebugRenderable();
    }
	  return ret;
  }

  virtual void SetDebugRenderState(physx::PxF32 visScale)
  {
	  PX_FORCE_PARAMETER_REFERENCE(visScale);
#if 0 // TODO:JWR
    if ( MApexSDK )
	  {
		  MApexSDK->setParameter(NxApexParam::VISUALIZATION_SCALE, visScale);
	  }
#endif
  }

	virtual	FIApexClothing * CreateApexClothing(void)
	{
		ApexClothing *ac = new ApexClothing(this);
		UBOOL found = FALSE;
		for (TApexClothingVector::iterator i=MApexClothing.begin(); i!=MApexClothing.end(); ++i)
		{
			if ( (*i) == NULL )
			{
				(*i) = ac;
				found = TRUE;
				break;
			}
		}
		if ( !found )
		{
			MApexClothing.push_back(ac);
		}

		return static_cast< FIApexClothing *>(ac);
	}

	virtual void ReleaseApexActor(FIApexActor &actor)
	{
		ApexActor *ac = static_cast< ApexActor *>(&actor);
		delete ac;
	}

	void ReleaseApexClothing(ApexClothing *ac)
	{
		for (TApexClothingVector::iterator i=MApexClothing.begin(); i!=MApexClothing.end(); ++i)
		{
			if ( ac == (*i) )
			{
				delete ac;
				(*i) = NULL;
				break;
			}
		}
	}

	virtual physx::PxU32 GetSimulationCount(void) const 
	{
		return MSimulateCount;
	}

#if WITH_APEX_PARTICLES
	virtual FApexEmitter * CreateApexEmitter(FIApexAsset *asset,const FMatrix &pose)
	{
		FApexEmitter *ret = NULL;
		check( asset && asset->GetType() == AAT_APEX_EMITTER );
		if ( asset && asset->GetType() == AAT_APEX_EMITTER )
		{
			ApexEmitter *ae = new ApexEmitter(this,asset,pose);
			ret = static_cast< FApexEmitter *>(ae);
			for (physx::PxU32 i=0; i<MEmitters.size(); i++)
			{
				if ( MEmitters[i] == NULL )
				{
					MEmitters[i] = ae;
					ae = NULL;
					break;
				}
			}
			if ( ae )
			{
				MEmitters.pushBack(ae);
			}
		}
		if ( !ret )
		{
			debugf(NAME_DevPhysics, TEXT("Failed to create Apex Emitter Actor"));
			check(0);
		}
		return ret;
	}

	void notifyEmitterGone(ApexEmitter *ae)
	{
		for (physx::PxU32 i=0; i<MEmitters.size(); i++)
		{
			if ( MEmitters[i] == ae )
			{
				MEmitters[i] = NULL;
			}
		}
	}
	virtual void NotifyAssetModified(FIApexAsset *asset) 
	{
		for (TApexEmitterVector::iterator i=MEmitters.begin(); i!=MEmitters.end(); ++i)
		{
			ApexEmitter *ae = *(i);
			if ( ae && asset->GetNxApexAsset() )
			{
				ae->NotifyAssetModified(asset->GetNxApexAsset());
			}
		}
	}

	virtual void NotifyAssetGoingAway(FIApexAsset *asset) 
	{
		for (TApexEmitterVector::iterator i=MEmitters.begin(); i!=MEmitters.end(); ++i)
		{
			ApexEmitter *ae = *(i);
			if ( ae && asset->GetNxApexAsset(false) )
			{
				ae->NotifyAssetGoingAway(asset->GetNxApexAsset(false));
			}
		}
	}

#endif

	virtual void UpdateProjection(const FMatrix& ProjMatrix, FLOAT FOV, FLOAT Width, FLOAT Height, FLOAT MinZ)
	{
		// LRR - be careful how we scale a perspective matrix, it's not a normal transform
		MApexScene->setProjMatrix( U2N44Perspective(ProjMatrix), MProjID );
		MApexScene->setProjParams( 
			U2PScale*MinZ, 
			MAX_FLT, 
			FOV, 
			appTrunc(Width), 
			appTrunc(Height),
			MProjID
			);
	}

	virtual void UpdateView(const FMatrix& ViewMatrix)
	{
		physx::PxMat44 pxmat44;
		FMatrixToPxMat44( ViewMatrix, pxmat44 );
		MApexScene->setViewMatrix( pxmat44, MViewID );
		// we know that view matrix is set after projection matrix! If it was otherwise, we'd have to move this call to UpdateProjection
		MApexScene->setUseViewProjMatrix(MViewID, MProjID);
	}

	// NVCHANGE_BEGIN: DJS - Add APEX stats
	virtual void UpdateStats()
	{
		// Only do stats when the game is actually running (this includes PIE though)
		if (GIsGame)
		{
#if _WINDOWS
			// CUDA heap is Windows-only
			FLOAT GpuHeapTotal = 0.0f;
			FLOAT PinnedHeapTotal = 0.0f;
			physx::pxtask::CudaContextManager* CtxMgr = GApexManager->GetCudaContextManager();
			if ( CtxMgr != NULL )
			{
				physx::pxtask::CudaMemoryManager* MemMgr = CtxMgr->getMemoryManager();
				if ( MemMgr != NULL )
				{
					GpuHeapTotal = GetPxtaskHeapSize(MemMgr, physx::pxtask::CudaBufferMemorySpace::T_GPU);
					PinnedHeapTotal = GetPxtaskHeapSize(MemMgr, physx::pxtask::CudaBufferMemorySpace::T_PINNED_HOST);
				}
			}
			SET_FLOAT_STAT(STAT_ApexHeapGpu,GpuHeapTotal);
			SET_FLOAT_STAT(STAT_ApexHeapPinned,PinnedHeapTotal);
#endif	// _WINDOWS
			// Get stats from APEX scene stats list
			SetApexCycleStat(STAT_ApexBeforeTickTime, "ApexBeforeTickTime");
			SetApexCycleStat(STAT_ApexDuringTickTime, "ApexDuringTickTime");
			SetApexCycleStat(STAT_ApexAfterTickTime, "ApexPostTickTime");
			SetApexCycleStat(STAT_ApexPhysXSimTime, "PhysXSimulationTime");
			SetApexCycleStat(STAT_ApexPhysXFetchTime, "PhysXFetchResultTime");
			SetApexCycleStat(STAT_ApexUserDelayedFetchTime, "UserDelayedFetchTime");
			SetApexDwordStat(STAT_ApexNumActors, "NumberOfActors");
			SetApexDwordStat(STAT_ApexNumShapes, "NumberOfShapes");
			SetApexDwordStat(STAT_ApexNumAwakeShapes, "NumberOfAwakeShapes");
			SetApexDwordStat(STAT_ApexNumCPUPairs, "NumberOfCpuShapePairs");
#if WITH_APEX_GRB
			SetApexCycleStat(STAT_ApexGrbSimTime, "GpuRbSimulationTime");
			SetApexDwordStat(STAT_ApexNumGPUPairs, "NumberOfGpuShapePairs");
#endif
		}
	}
	// NVCHANGE_END: DJS - Add APEX stats

private:
	// NVCHANGE_BEGIN: DJS - Add APEX stats
	FLOAT GetPxtaskHeapSize(physx::pxtask::CudaMemoryManager* MemMgr, 
							physx::pxtask::CudaBufferMemorySpace::Enum MemSpace)
	{
		FLOAT HeapTotal = 0.0f;

		struct physx::pxtask::CudaMemoryManagerStats MemMgrStats;
		physx::pxtask::CudaBufferType BufType(MemSpace, physx::pxtask::CudaBufferFlags::F_READ_WRITE);
		MemMgr->getStats(BufType, MemMgrStats);
		if ( MemMgrStats.maxAllocated != 0 )
		{
			// convert to MB to make it easier to read
			HeapTotal = (FLOAT)MemMgrStats.heapSize / (1024.0f * 1024.0f);
		}

		return HeapTotal;
	}

	void SetApexCycleStat(EApexStats CycleStat, const ANSICHAR* Name)
	{
		const physx::apex::ApexStatsInfo* Stat = GetStat(Name);
		if ( Stat != NULL )
		{
			// APEX times are measured in milliseconds
			SET_CYCLE_COUNTER(CycleStat, (DWORD)(Stat->StatCurrentValue.Float * 0.001f / GSecondsPerCycle), 1);
		}
		else
		{
			SET_CYCLE_COUNTER(CycleStat, 0, 0);
		}
	}

	void SetApexDwordStat(EApexStats CycleStat, const ANSICHAR* Name)
	{
		const physx::apex::ApexStatsInfo* Stat = GetStat(Name);
		if ( Stat != NULL )
		{
			SET_DWORD_STAT(CycleStat, Stat->StatCurrentValue.Int);
		}
		else
		{
			SET_DWORD_STAT(CycleStat, 0);
		}
	}

	const physx::apex::ApexStatsInfo* GetStat(const ANSICHAR* Name)
	{
		// APEX stats are stored in consistent positions in the stat list, so if overhead of 
		// collecting stats is a problem, we could cache the stat indices instead of 
		// searching the list each time.
		const physx::apex::ApexStatsInfo* FoundStat = NULL;

		const physx::apex::NxApexSceneStats* Stats = GetNxApexScene()->getStats();
		const physx::apex::ApexStatsInfo* CurStat = Stats->ApexStatsInfoPtr;
		const physx::apex::ApexStatsInfo* LastStat = CurStat + Stats->numApexStats;
		for (; CurStat != LastStat; ++CurStat)
		{
			if ( 0 == appStrcmpANSI(Name, CurStat->StatName) )
			{
				FoundStat = CurStat;
				break;
			}
		}

		return FoundStat;
	}
	// NVCHANGE_END: DJS - Add APEX stats

// NVCHANGE_BEGIN: hlanker - clothing actor recording
	void ClothingActorDump(float dtime)
	{
#if ALLOW_DEBUG_FILES
		NxReal MaxTimestep = 0.0f;
		NxU32 MaxIter = 0;
		NxTimeStepMethod TimeStepMethod = NX_TIMESTEP_VARIABLE;
		NxScene* PhysXScene = MApexScene->getPhysXScene();

		if (PhysXScene == NULL)
			return;

		PhysXScene->getTiming(MaxTimestep, MaxIter, TimeStepMethod);

		NxVec3 Gravity(0.0f);
		PhysXScene->getGravity(Gravity);

		int ActorIndex = 0;
		NxParameterized::Serializer* Serializer	= physx::NxGetApexSDK()->createSerializer(NxParameterized::Serializer::NST_XML);
		for (UINT i = 0; i < MApexClothing.size(); ++i)
		{
			ApexClothing* Clothing = MApexClothing[i];
			for (UINT j = 0; j < Clothing->MPieces.size(); ++j)
			{
				ApexClothingPiece* ClothingPiece = Clothing->MPieces[j];
				if (ClothingPiece == NULL || ClothingPiece->MAsset == NULL || ClothingPiece->MActor == NULL)
					continue;

				const char* assetName = ClothingPiece->MAsset->GetAssetName();
				FString OutputFileName = appGameLogDir() + FString(assetName) + FString::Printf( TEXT("_%i.xml"), ActorIndex );
				++ActorIndex;

				FArchive* OutputFile = GFileManager->CreateDebugFileWriter( *OutputFileName, FILEWRITE_Append );
				if( OutputFile == NULL )
					continue;

				if (OutputFile->Tell() == 0)
				{
					// at the beginning of the file, write out the asset
					NxApexAsset* ApexAsset = ClothingPiece->MAsset->GetNxApexAsset();
					if (ApexAsset != NULL)
					{
						const NxParameterized::Interface* AssetParams = ApexAsset->getAssetNxParameterized();
						if (AssetParams !=  NULL)
						{
							physx::general_PxIOStream2::PxFileBuf* WriteStream = GApexManager->GetApexSDK()->createMemoryWriteStream();
							if (WriteStream != NULL)
							{
								NxParameterized::Serializer::ErrorType SerError = Serializer->serialize(*WriteStream, (const ::NxParameterized::Interface **)&AssetParams, 1);

								physx::PxU32 bufLen = 0;
								const void* buf = GApexManager->GetApexSDK()->getMemoryWriteBuffer(*WriteStream, bufLen);
								OutputFile->Serialize( (void*)buf, bufLen );
								WriteStream->release();
							}
						}
					}
				}

				NxClothingActor* ClothingActor = (NxClothingActor*)ClothingPiece->MActor->GetNxApexActor();
				if (ClothingActor == NULL)
					continue;

				NxParameterized::Interface* ActorParams = ClothingActor->getActorDesc();

				physx::general_PxIOStream2::PxFileBuf* WriteStream = GApexManager->GetApexSDK()->createMemoryWriteStream();
				if (WriteStream == NULL)
					continue;

				NxParameterized::Serializer::ErrorType SerError = Serializer->serialize(*WriteStream, (const ::NxParameterized::Interface **)&ActorParams, 1);

				physx::PxU32 bufLen = 0;
				const void* buf = GApexManager->GetApexSDK()->getMemoryWriteBuffer(*WriteStream, bufLen);
				OutputFile->Serialize( (void*)buf, bufLen );

				OutputFile->Logf(TEXT("<Timing>"));
				OutputFile->Logf(TEXT("\t<MaxTimestep>%f</MaxTimestep>"), MaxTimestep);
				OutputFile->Logf(TEXT("\t<MaxIter>%i</MaxIter>"), MaxIter);
				OutputFile->Logf(TEXT("\t<TimeStepMethod>%i</TimeStepMethod>"), (INT)TimeStepMethod);
				OutputFile->Logf(TEXT("\t<Dt>%f</Dt>"), dtime);
				OutputFile->Logf(TEXT("</Timing>"));

				OutputFile->Logf(TEXT("<Gravity>%f %f %f</Gravity>"), Gravity.x, Gravity.y, Gravity.z);

				delete OutputFile;
				WriteStream->release();
			}
		}
		Serializer->release();
#endif
	}
// NVCHANGE_END: hlanker - clothing actor recording



	FIApexManager             *MApexManager;
	NxScene	              	  *MScene;
	NxApexSDK                 *MApexSDK;
	NxApexScene               *MApexScene;
	TApexClothingVector   	   MApexClothing;
#if WITH_APEX_PARTICLES
	TApexEmitterVector		   MEmitters;
#endif
	UBOOL					   MUseDebugRenderable;
	physx::PxU32			   MSimulateCount;
	physx::PxU32				MViewID;
	physx::PxU32				MProjID;

	UBOOL						mIsSimulating;
	FEvent						*RenderSyncEvent;
};

UBOOL ApexActor::Recreate(ApexScene *parentScene,const ::NxParameterized::Interface *params)
{
	check(MApexAsset);
	if ( MActor )
	{
		MActor->release();
		MActor = NULL;
	}

  MParent = parentScene;
  NxApexAsset *aa                = MApexAsset->GetNxApexAsset();
  NxApexScene *apexScene         = parentScene->GetNxApexScene();
  MType = ApexActorType::UNKNOWN;
  if ( params && apexScene )
  {
	MActor = aa->createApexActor(*params,*apexScene);
	if ( MActor )
	{
		switch ( MApexAsset->GetType() )
		{
			case AAT_DESTRUCTIBLE:
				MType = ApexActorType::DESTRUCTIBLE;
				break;
			case AAT_CLOTHING:
				MType =  ApexActorType::CLOTHING;
				break;
		}
	}
  }
  return MActor ? TRUE : FALSE;
}

// NVCHANGE_BEGIN : hlanker - fix apex rendering race condition
ApexActor::ApexActor(ApexScene *parentScene,
					FIApexAsset *apexAsset,
					const ::NxParameterized::Interface *params) :
RenderContext(NULL),
RenderContextRT(NULL)
// NVCHANGE_END : hlanker - fix apex rendering race condition
{
	mNeedsRebuild = FALSE;
  MParent = parentScene;
  MApexAsset = apexAsset;
  NxApexAsset *aa                = apexAsset->GetNxApexAsset();
  NxApexScene *apexScene         = parentScene->GetNxApexScene();
  MActor = NULL;
  MType = ApexActorType::UNKNOWN;
  mUpdateRenderResource			= FALSE;
  if ( params && apexScene )
  {
	MActor = aa->createApexActor(*params,*apexScene);
	if ( MActor )
	{
		switch ( apexAsset->GetType() )
		{
#if WITH_APEX_PARTICLES
			case AAT_APEX_EMITTER:
				MType = ApexActorType::EMITTER;
				{
					NxApexEmitterActor *a = static_cast< NxApexEmitterActor *>(MActor);
					a->startEmit(false);
				}
				break;
#endif
			case AAT_DESTRUCTIBLE:
				MType = ApexActorType::DESTRUCTIBLE;
				break;
			case AAT_CLOTHING:
				MType =  ApexActorType::CLOTHING;
				break;
		}
	}
  }
}


void ApexActor::Release(void (*CallbackFunc)(void*), void* CallbackData)
{
	if ( MActor )
	{
		// NVCHANGE_BEGIN : hlanker - fix apex rendering race condition
		BeginCleanup(new FApexActorCleanUp(MActor, MApexAsset, this, RenderContextRT, CallbackFunc, CallbackData));
		// NVCHANGE_END : hlanker - fix apex rendering race condition
		MActor = NULL;
	}
	else
	{
		if (CallbackFunc != NULL)
		{
			(*CallbackFunc)(CallbackData);
		}
		delete this;
	}
}


void ApexClothing::Release(void)
{
	if ( MApexScene )
	{
		ApexScene *as = static_cast< ApexScene *>(MApexScene);
		as->ReleaseApexClothing(this);
	}
	else
	{
		delete this;
	}
}

#if WITH_APEX_PARTICLES
void ApexEmitter::doRelease(void)
{
	if (mScene != NULL)
	{
		ApexScene *as = static_cast< ApexScene *>(mScene);
		as->notifyEmitterGone(this);
	}
	delete this;
}
#endif


}; // end of APEX_SCENE namespace

using namespace APEX_SCENE;

/**
 * Creates the APEX Scene
 * @param [in,out]	Scene - If non-null, the NxScene.
 * @param [in,out]	Sdk	- If non-null, the FIApexManager.
 * @param	bUseDebugRenderable - TRUE to use debug renderable.
 *
 * @return	null if it fails, else a pointer to the FIApexScene.
**/
FIApexScene * CreateApexScene(NxScene *scene,FIApexManager *manager,UBOOL useDebugRenderable)
{
#ifndef PS3
	scene;
	manager;
	useDebugRenderable;
#endif
  ApexScene *as = new ApexScene(scene,manager,useDebugRenderable);
  if ( as->GetApexScene() == NULL )
  {
	  delete as;
	  as = NULL;
  }
  return static_cast< FIApexScene *>(as);
}

/**
 * Releases the APEX Scene
 * @param [in,out]	scene	If non-null, the scene.
**/
void          ReleaseApexScene(FIApexScene *scene)
{
  ApexScene *as = static_cast< ApexScene *>(scene);
  delete as;
}
volatile INT FApexCleanUp::PendingObjects = 0;

FApexCleanUp::FApexCleanUp(physx::apex::NxApexInterface* ApexObject, FIApexAsset *Asset)
:ApexObject(ApexObject), ApexAsset(Asset)
{
	appInterlockedIncrement(&PendingObjects);
}

FApexCleanUp::~FApexCleanUp()
{

}

void FApexCleanUp::FinishCleanup()
{
	check(ApexObject);
	ApexObject->release();
	ApexObject = NULL;
	if(ApexAsset)
	{
		ApexAsset->DecRefCount(0);
	}
	check(PendingObjects);
	appInterlockedDecrement(&PendingObjects);
	delete this;
}
#endif //WITH_APEX

#endif //WITH_NOVODEX
