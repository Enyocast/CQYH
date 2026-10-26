/*=============================================================================
	NvApexRenderVolumeComponent.cpp : Handles APEX render volumes
	Copyright 1998-2010 Epic Games, Inc. All Rights Reserved.
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

#if WITH_NOVODEX

#include "NvApexManager.h"

#endif

#include "EngineMeshClasses.h"
#include "EnginePhysicsClasses.h"
#include "EngineParticleClasses.h"
#include "EngineMaterialClasses.h"
//#include "MeshUtils.h"
#include "NvApexScene.h"
#include "UnNovodexSupport.h"
#include "NvApexManager.h"
#include "UnNovodexSupport.h"
#include "NvApexRenderClasses.h"

#if WITH_APEX

#include <NxApexSDK.h>
#include <NxUserRenderResourceManager.h>
#include "NvApexCommands.h"
#include <NxModuleDestructible.h>
#include <NxDestructibleAsset.h>
#include <NxDestructiblePreview.h>
#include <NxDestructibleActor.h>
#include <NxDestructibleActorJoint.h>
#include <NxResourceProvider.h>
// NVCHANGE_BEGIN: JCAO - PS3 Build
#if WITH_APEX_PARTICLES
#include <NxApexRenderVolume.h>
#include <NxModuleIofx.h>
#include <NxIofxAsset.h>
#include <NxIofxActor.h>
#include <NxApexEmitterAsset.h>
#include <NxApexEmitterActor.h>
#endif
// NVCHANGE_END: JCAO - PS3 Build
#include "NvApexRender.h"
#include <pxtask/PxCudaContextManager.h>
#include <pxtask/PxTaskManager.h>
#include <NxParamUtils.h>

using namespace physx::apex;

#endif

IMPLEMENT_CLASS(UApexRenderVolumeComponent)

// UPrimitiveComponent interface.
/**
 * Creates a proxy to represent the primitive to the scene manager in the rendering thread.
 * @return The proxy object.
*/
FPrimitiveSceneProxy* UApexRenderVolumeComponent::CreateSceneProxy()
{
#if WITH_APEX
	return new FApexRenderVolumeSceneProxy(*this);
#else
	return NULL;
#endif
}

void UApexRenderVolumeComponent::UpdateBounds()
{
#if WITH_APEX_PARTICLES
	if ( ApexRenderVolume )
	{
		physx::NxApexRenderVolume *volume = (physx::NxApexRenderVolume *)ApexRenderVolume;
		physx::PxBounds3 PhysXBounds = volume->getBounds();
		physx::PxVec3 Center, Extents;
		Center = PhysXBounds.getCenter();
		Extents = PhysXBounds.getExtents();
		Bounds = FBoxSphereBounds(FBox::BuildAABB(N2UPositionApex(Center), N2UPositionApex(Extents)));
	}
	else
	{
		Super::UpdateBounds();
	}
#endif
}

/** 
 * Retrieves the materials used in this component 
 * 
 * @param OutMaterials	The list of used materials.
*/
void UApexRenderVolumeComponent::GetUsedMaterials( TArray<UMaterialInterface*>& OutMaterials ) const
{

}

void UApexRenderVolumeComponent::ReleaseRenderVolume(void)
{
#if WITH_APEX_PARTICLES
	if ( ApexRenderVolume )
	{
		physx::NxApexRenderVolume *v = (physx::NxApexRenderVolume *)ApexRenderVolume;
		v->release();
		if ( ViewRelevance )
		{
			FMaterialViewRelevance *vr = (FMaterialViewRelevance *)ViewRelevance;
			delete vr;
			ViewRelevance = NULL;
		}
	}
#endif
}

void UApexRenderVolumeComponent::InitRenderVolume(void *apexActor,void *apexScene,UBOOL isCrumble)
{
#if WITH_APEX_PARTICLES
	physx::NxApexScene *scene = (physx::NxApexScene *)apexScene;
	physx::NxModuleIofx *iofx = GApexManager->GetModuleIofx();
	if ( scene && apexActor && iofx )
	{
		physx::PxBounds3 b;
		b.setInfinite();
		physx::NxApexRenderVolume *volume = iofx->createRenderVolume(*scene,b,0,true);
		ApexRenderVolume = volume;
		if ( volume )
		{
			NxDestructibleActor *dact = (NxDestructibleActor *)apexActor;
			dact->setPreferredRenderVolume(volume,isCrumble ? physx::NxDestructibleEmitterType::Crumble : NxDestructibleEmitterType::Dust );
			NxApexEmitterActor *eact = dact->getApexEmitter(isCrumble ? physx::NxDestructibleEmitterType::Crumble : NxDestructibleEmitterType::Dust);
			if ( eact )
			{
				NxApexAsset *emitterAsset = eact->getOwner();
				const NxParameterized::Interface *assetInterface = emitterAsset->getAssetNxParameterized();
				NxParameterized::Interface *iofxAssetNamedRef=NULL;
				NxParameterized::getParamRef(const_cast<NxParameterized::Interface&>(*assetInterface), "iofxAssetName", iofxAssetNamedRef);
				if ( iofxAssetNamedRef )
				{
					void *tmp = GApexManager->GetApexSDK()->getNamedResourceProvider()->getResource( NX_IOFX_AUTHORING_TYPE_NAME, iofxAssetNamedRef->name() );
					if ( tmp )
					{
						NxIofxAsset *iofxAsset = (NxIofxAsset*)tmp;
						const NxParameterized::Interface *iofxAssetInterface = iofxAsset->getAssetNxParameterized();
						NxParameterized::Interface *spriteMaterialNamedRef=NULL;
						NxParameterized::getParamRef(const_cast<NxParameterized::Interface&>(*iofxAssetInterface), "iofxType", spriteMaterialNamedRef);
						if( spriteMaterialNamedRef && !strcmp(spriteMaterialNamedRef->className(), "SpriteIofxParameters") )
						{
							NxParameterized::getParamRef(const_cast<NxParameterized::Interface&>(*iofxAssetInterface), "iofxType.spriteMaterialName", spriteMaterialNamedRef);
							tmp = GApexManager->GetApexSDK()->getNamedResourceProvider()->getResource( APEX_MATERIALS_NAME_SPACE, spriteMaterialNamedRef->name() );
							if ( tmp )
							{
								FMaterialViewRelevance *vr = new FMaterialViewRelevance;
								UMaterialInterface *m = (UMaterialInterface *)tmp;
								*vr = m->GetViewRelevance();
								ViewRelevance = vr;
							}
						}
					}
				}
			}
		}
	}
#endif
}

physx::apex::NxApexRenderable *UApexRenderVolumeComponent::GetApexRenderable(void) const
{
	physx::apex::NxApexRenderable *ret = NULL;
#if WITH_APEX_PARTICLES
	if ( ApexRenderVolume )
	{
		physx::NxApexRenderVolume *volume = (physx::NxApexRenderVolume *)ApexRenderVolume;
		ret = static_cast< physx::apex::NxApexRenderable * >(volume);

	}
#endif
	return ret;
}

/** Accesses the scene relevance information for the materials applied to the mesh. */
FMaterialViewRelevance UApexRenderVolumeComponent::GetMaterialViewRelevance() const
{
	FMaterialViewRelevance ret;
	ret.bOpaque = TRUE; // default view relevance is opaque
	if ( ViewRelevance )
	{
		FMaterialViewRelevance *vr = (FMaterialViewRelevance *)ViewRelevance;
		ret = *vr;
	}
	return ret;
}

void UApexRenderVolumeComponent::Tick(FLOAT DeltaTime)
{
	Super::Tick( DeltaTime );
	UpdateBounds();
	UpdateTransform();
}

UBOOL UApexRenderVolumeComponent::IsValidComponent() const
{
	return TRUE;
}

UBOOL UApexRenderVolumeComponent::ShouldComponentAddToScene() const
{
	return GIsGame;
}