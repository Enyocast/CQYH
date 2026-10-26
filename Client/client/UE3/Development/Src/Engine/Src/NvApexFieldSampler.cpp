/*=============================================================================
	NvApexFieldSampler.cpp : Handles APEX FieldSampler objects.
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

#if WITH_APEX_FIELD_SAMPLERS
#include <NxApexSDK.h>
#include <NxApexAsset.h>
#include <NxApexActor.h>
#include <NxApexNameSpace.h>
#endif

namespace physx {
namespace apex {
	class NxApexAsset;
	class NxApexActor;
}}
using namespace physx;
using namespace physx::apex;

#include "EngineApexFieldSamplerClasses.h"
#include "UnNovodexSupport.h"

// NVCHANGE_BEGIN: JCAO - Remove ApexFieldSamplerActor
// NVCHANGE_END: JCAO - Remove ApexFieldSamplerActor

// NVCHANGE_BEGIN: JCAO - US10286 Add ApexAttactorActor, ApexJetActor and ApexGridActor
/*-----------------------------------------------------------------------------
AApexGridActor
-----------------------------------------------------------------------------*/
IMPLEMENT_CLASS(AApexGridActor);

void AApexGridActor::AttachGridComponent()
{
	// NVCHANGE_BEGIN: JCAO - create ApexJetComponent ApexGridComponent and ApexAttractorComponent
	if (GridComponent != NULL && !GridComponent->IsAttached())
	{
		AttachComponent(GridComponent);
	}
	// NVCHANGE_END: JCAO - create ApexJetComponent ApexGridComponent and ApexAttractorComponent
}
void AApexGridActor::DetachGridComponent()
{
	// NVCHANGE_BEGIN: JCAO - create ApexJetComponent ApexGridComponent and ApexAttractorComponent
	if (GridComponent != NULL && GridComponent->IsAttached())
	{
		DetachComponent(GridComponent);
	}
	// NVCHANGE_END: JCAO - create ApexJetComponent ApexGridComponent and ApexAttractorComponent
}

void AApexGridActor::PreEditChange(UProperty *PropertyAboutToChange)
{
	// NVCHANGE_BEGIN: JCAO - create ApexJetComponent ApexGridComponent and ApexAttractorComponent
	if (appStrstr(*(PropertyAboutToChange->GetName()), TEXT("GridComponent")) != NULL)
	{
		DetachGridComponent();
	}
	// NVCHANGE_END: JCAO - create ApexJetComponent ApexGridComponent and ApexAttractorComponent

	Super::PreEditChange(PropertyAboutToChange);
}

void AApexGridActor::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	UProperty* PropertyThatChanged = PropertyChangedEvent.Property;
	if (PropertyThatChanged)
	{
		// NVCHANGE_BEGIN: JCAO - create ApexJetComponent ApexGridComponent and ApexAttractorComponent
		if (appStrstr(*(PropertyThatChanged->GetName()), TEXT("GridComponent")) != NULL)
		{
			AttachGridComponent();
		}
		// NVCHANGE_END: JCAO - create ApexJetComponent ApexGridComponent and ApexAttractorComponent
	}
}

void AApexGridActor::Spawned()
{
	Super::Spawned();

	AttachGridComponent();
}


void AApexGridActor::InitRBPhys()
{
	AttachGridComponent();

	Super::InitRBPhys();
}

void AApexGridActor::InitRBPhysEditor()
{
	AttachGridComponent();

	Super::InitRBPhysEditor();
}

/*-----------------------------------------------------------------------------
AApexJetActor
-----------------------------------------------------------------------------*/
IMPLEMENT_CLASS(AApexJetActor);

void AApexJetActor::AttachJetComponent()
{
	// NVCHANGE_BEGIN: JCAO - create ApexJetComponent ApexGridComponent and ApexAttractorComponent
	if (JetComponent != NULL && !JetComponent->IsAttached())
	{
		AttachComponent(JetComponent);
	}
	// NVCHANGE_END: JCAO - create ApexJetComponent ApexGridComponent and ApexAttractorComponent
}
void AApexJetActor::DetachJetComponent()
{
	// NVCHANGE_BEGIN: JCAO - create ApexJetComponent ApexGridComponent and ApexAttractorComponent
	if (JetComponent != NULL && JetComponent->IsAttached())
	{
		DetachComponent(JetComponent);
	}
	// NVCHANGE_END: JCAO - create ApexJetComponent ApexGridComponent and ApexAttractorComponent
}

void AApexJetActor::PreEditChange(UProperty *PropertyAboutToChange)
{
	// NVCHANGE_BEGIN: JCAO - create ApexJetComponent ApexGridComponent and ApexAttractorComponent
	if (appStrstr(*(PropertyAboutToChange->GetName()), TEXT("JetComponent")) != NULL)
	{
		DetachJetComponent();
	}
	// NVCHANGE_END: JCAO - create ApexJetComponent ApexGridComponent and ApexAttractorComponent

	Super::PreEditChange(PropertyAboutToChange);
}

void AApexJetActor::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	UProperty* PropertyThatChanged = PropertyChangedEvent.Property;
	if (PropertyThatChanged)
	{
		// NVCHANGE_BEGIN: JCAO - create ApexJetComponent ApexGridComponent and ApexAttractorComponent
		if (appStrstr(*(PropertyThatChanged->GetName()), TEXT("JetComponent")) != NULL)
		{
			AttachJetComponent();
		}
		// NVCHANGE_END: JCAO - create ApexJetComponent ApexGridComponent and ApexAttractorComponent
	}
}

void AApexJetActor::Spawned()
{
	Super::Spawned();

	AttachJetComponent();
}


void AApexJetActor::InitRBPhys()
{
	AttachJetComponent();

	Super::InitRBPhys();
}

void AApexJetActor::InitRBPhysEditor()
{
	AttachJetComponent();

	Super::InitRBPhysEditor();
}

/*-----------------------------------------------------------------------------
AApexAttractorActor
-----------------------------------------------------------------------------*/
IMPLEMENT_CLASS(AApexAttractorActor);

void AApexAttractorActor::AttachAttractorComponent()
{
	// NVCHANGE_BEGIN: JCAO - create ApexJetComponent ApexGridComponent and ApexAttractorComponent
	if (AttractorComponent != NULL && !AttractorComponent->IsAttached())
	{
		AttachComponent(AttractorComponent);
	}
	// NVCHANGE_END: JCAO - create ApexJetComponent ApexGridComponent and ApexAttractorComponent
}
void AApexAttractorActor::DetachAttractorComponent()
{
	// NVCHANGE_BEGIN: JCAO - create ApexJetComponent ApexGridComponent and ApexAttractorComponent
	if (AttractorComponent != NULL && AttractorComponent->IsAttached())
	{
		DetachComponent(AttractorComponent);
	}
	// NVCHANGE_END: JCAO - create ApexJetComponent ApexGridComponent and ApexAttractorComponent
}

void AApexAttractorActor::PreEditChange(UProperty *PropertyAboutToChange)
{
	// NVCHANGE_BEGIN: JCAO - create ApexJetComponent ApexGridComponent and ApexAttractorComponent
	if (appStrstr(*(PropertyAboutToChange->GetName()), TEXT("AttractorComponent")) != NULL)
	{
		DetachAttractorComponent();
	}
	// NVCHANGE_END: JCAO - create ApexJetComponent ApexGridComponent and ApexAttractorComponent

	Super::PreEditChange(PropertyAboutToChange);
}

void AApexAttractorActor::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	UProperty* PropertyThatChanged = PropertyChangedEvent.Property;
	if (PropertyThatChanged)
	{
		// NVCHANGE_BEGIN: JCAO - create ApexJetComponent ApexGridComponent and ApexAttractorComponent
		if (appStrstr(*(PropertyThatChanged->GetName()), TEXT("AttractorComponent")) != NULL)
		{
			AttachAttractorComponent();
		}
		// NVCHANGE_END: JCAO - create ApexJetComponent ApexGridComponent and ApexAttractorComponent
	}
}

void AApexAttractorActor::Spawned()
{
	Super::Spawned();

	AttachAttractorComponent();
}


void AApexAttractorActor::InitRBPhys()
{
	AttachAttractorComponent();

	Super::InitRBPhys();
}

void AApexAttractorActor::InitRBPhysEditor()
{
	AttachAttractorComponent();

	Super::InitRBPhysEditor();
}
// NVCHANGE_END: JCAO - US10286 Add ApexAttactorActor, ApexJetActor and ApexGridActor

IMPLEMENT_CLASS(UApexFieldSamplerComponent);

void UApexFieldSamplerComponent::DoInitRBPhys()
{
	InitFieldSampler();
}

void UApexFieldSamplerComponent::InitComponentRBPhys(UBOOL bFixed)
{
	Super::InitComponentRBPhys(bFixed);

	InitFieldSampler();
}

void UApexFieldSamplerComponent::InitFieldSampler()
{
	FRBPhysScene *Scene = GWorld->RBPhysScene;
	if (Scene != NULL)
	{
		PhysSceneIndex = Scene->NovodexSceneIndex;

		CreateApexObjects();
	}
}
void UApexFieldSamplerComponent::TermFieldSampler()
{
	DestroyApexObjects();
}

void UApexFieldSamplerComponent::TermComponentRBPhys(FRBPhysScene *Scene)
{
	Super::TermComponentRBPhys(Scene);

	// If the force field is not in the scene we want, do nothing.
	if ((Scene != NULL) && (PhysSceneIndex != Scene->NovodexSceneIndex))
	{
		return;
	}

	TermFieldSampler();
}

void UApexFieldSamplerComponent::UpdateChildComponents()
{
	Super::UpdateChildComponents();

	if (DrawComponent)
	{
		FMatrix Transform;
		GetTransform(Transform);

		DrawComponent->UpdateComponent(Scene, Owner, Transform);
	}
}
void UApexFieldSamplerComponent::Attach()
{
	Super::Attach();

	InitFieldSampler();
}

void UApexFieldSamplerComponent::Detach( UBOOL bWillReattach )
{
	Super::Detach( bWillReattach );

	if (!bWillReattach)
	{
		if (DrawComponent)
		{
			DrawComponent->ConditionalDetach( bWillReattach );
		}
		TermFieldSampler();
	}
}

void UApexFieldSamplerComponent::CreateApexObjects(UBOOL bRecreate)
{
#if WITH_APEX_FIELD_SAMPLERS
	// NVCHANGE_BEGIN: JCAO - If no hardware acceleration, turbulence effects won't be created.
	if ( GEngine->GetPhysXLevel() == 0 )
	{
		return;
	}
	// NVCHANGE_END: JCAO - If no hardware acceleration, turbulence effects won't be created.

	if (ApexActor == NULL)
	{
		InitializeApex();
		if (!GApexManager)
		{
			return;
		}
		physx::apex::NxApexSDK* ApexSDK = GApexManager->GetApexSDK();
		// NVCHANGE_BEGIN: JCAO - field samplers support UE3 collision channels
		if (ApexSDK)
		{
			NxGroupsMask mask = CreateGroupsMask( CollisionChannel, &CollideWithChannels );
			ApexSDK->getNamedResourceProvider()->setResource(APEX_COLLISION_GROUP_NAME_SPACE, "FSCollisionFilter", (void*)CollisionChannel);
			ApexSDK->getNamedResourceProvider()->setResource(APEX_COLLISION_GROUP_128_NAME_SPACE, "FSCollisionFilter", (void*)(&mask));

			NxGroupsMask64 mask64 = CreateGroupsMask64( CollisionChannel, &CollideWithChannels );
			ApexSDK->getNamedResourceProvider()->setResource(APEX_COLLISION_GROUP_64_NAME_SPACE, "FSfieldSamplerFilter", (void*)(&mask64));
		}
		// NVCHANGE_END: JCAO - field samplers support UE3 collision channels

		// create asset
		if (ensure(ApexAsset == NULL))
		{
			if (ApexAssetParams == NULL)
			{
				const char* AssetObjTypeName = GetApexAssetObjTypeName();
				physx::apex::NxApexAssetAuthoring *Authoring = ApexSDK->createAssetAuthoring(AssetObjTypeName);
				check(Authoring);
				if (Authoring)
				{
					ApexAssetParams = Authoring->releaseAndReturnNxParameterizedInterface();
				}
				SetupApexAssetParams();
			}

			::NxParameterized::Interface* AssetParams = (::NxParameterized::Interface*)ApexAssetParams;
			if (AssetParams)
			{
				ApexAsset = ApexSDK->createAsset(AssetParams, 0);
			}
		}

		physx::apex::NxApexScene *ApexScene = GWorld && GWorld->RBPhysScene ? GWorld->RBPhysScene->GetApexScene() : 0;
		check(ApexScene && ApexAsset);
		if (ApexScene && ApexAsset)
		{
			::NxParameterized::Interface* ActorParams = ApexAsset->getDefaultActorDesc();
			check(ActorParams);
			if (ActorParams)
			{
				SetupApexActorParams(ActorParams);
				ApexActor = ApexAsset->createApexActor(*ActorParams, *ApexScene);
				UpdateApexActor();
			}
		}
	}
#endif
}

void UApexFieldSamplerComponent::DestroyApexObjects(UBOOL bRecreate)
{
#if WITH_APEX_FIELD_SAMPLERS
	if (ApexActor != NULL)
	{
		ApexActor->release();
		ApexActor = NULL;
	}
	if (ApexAsset != NULL)
	{
		ApexAssetParams = ApexAsset->releaseAndReturnNxParameterizedInterface();
		ApexAsset = NULL;
	}
	if (!bRecreate)
	{
		::NxParameterized::Interface* AssetParams = (::NxParameterized::Interface*)ApexAssetParams;
		if (AssetParams)
		{
			AssetParams->destroy();
		}
		ApexAssetParams = NULL;
	}
#endif
}

void UApexFieldSamplerComponent::SetEnabled(UBOOL Enabled)
{
	bEnabled = Enabled;
	UpdateApexActor();
}

