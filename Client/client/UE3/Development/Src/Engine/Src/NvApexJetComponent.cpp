// NVCHANGE_BEGIN: JCAO - create ApexJetComponent ApexGridComponent and ApexAttractorComponent
/*=============================================================================
	NvApexJetComponent.cpp : Handles APEX Jet objects.
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
#include <NxUserRenderResourceManager.h>
#include "NvApexCommands.h"
#include <NxModuleBasicFS.h>
#include <NxBasicFSAsset.h>
#include <NxJetFSActor.h>
#include <NxResourceProvider.h>
#include "NxParamUtils.h"
#include "UnNovodexSupport.h"

using namespace physx::apex;

#else

namespace physx {
namespace apex {
	class NxApexAsset;
	class NxApexActor;
}}

#endif

#include "EngineApexFieldSamplerClasses.h"

#define ITERATE_ASSET_PARAMS() \
	PROCESS_ASSET_PARAM(TRUE,  F32,  physx::PxF32,  "fieldDirectionDeviationAngle", FieldDirectionDeviationAngle) \
	PROCESS_ASSET_PARAM(TRUE,  F32,  physx::PxF32,  "fieldDirectionOscillationPeriod", FieldDirectionOscillationPeriod) \
	PROCESS_ASSET_PARAM(FALSE, F32,  physx::PxF32,  "fieldStrength", FieldStrength * U2PScale) \
	PROCESS_ASSET_PARAM(TRUE,  F32,  physx::PxF32,  "fieldStrengthDeviationPercentage", FieldStrengthDeviationPercentage) \
	PROCESS_ASSET_PARAM(TRUE,  F32,  physx::PxF32,  "fieldStrengthOscillationPeriod", FieldStrengthOscillationPeriod) \
	PROCESS_ASSET_PARAM(TRUE,  F32,  physx::PxF32,  "gridShapeRadius", GridShapeRadius * U2PScale) \
	PROCESS_ASSET_PARAM(TRUE,  F32,  physx::PxF32,  "gridShapeHeight", GridShapeHeight * U2PScale) \
	PROCESS_ASSET_PARAM(TRUE,  F32,  physx::PxF32,  "gridBoundaryFadePercentage", GridBoundaryFadePercentage) \
	PROCESS_ASSET_PARAM(TRUE,  F32,  physx::PxF32,  "boundaryFadePercentage", BoundaryFadePercentage) \
	PROCESS_ASSET_PARAM(TRUE,  F32,  physx::PxF32,  "nearRadius", FieldSize * FieldNearRatio * U2PScale) \
	PROCESS_ASSET_PARAM(TRUE,  F32,  physx::PxF32,  "pivotRadius", FieldSize * (FieldNearRatio + (FieldFarRatio - FieldNearRatio)*(FieldPivot + 1.0)*0.5) * U2PScale) \
	PROCESS_ASSET_PARAM(TRUE,  F32,  physx::PxF32,  "farRadius", FieldSize * FieldFarRatio * U2PScale) \
	PROCESS_ASSET_PARAM(TRUE,  F32,  physx::PxF32,  "directionalStretch", DirectionalStretch) \
	PROCESS_ASSET_PARAM(TRUE,  F32,  physx::PxF32,  "averageStartDistance", FieldSize * AverageStartRatio * U2PScale) \
	PROCESS_ASSET_PARAM(TRUE,  F32,  physx::PxF32,  "averageEndDistance", FieldSize * AverageEndRatio * U2PScale) \
	PROCESS_ASSET_PARAM(TRUE,  F32,  physx::PxF32,  "noisePercentage", NoisePercentage) \
	PROCESS_ASSET_PARAM(TRUE,  F32,  physx::PxF32,  "noiseSpaceScale", NoiseSpaceScale * U2PScale) \
	PROCESS_ASSET_PARAM(TRUE,  F32,  physx::PxF32,  "noiseTimeScale", NoiseTimeScale) \
	PROCESS_ASSET_PARAM(TRUE,  U32,  physx::PxU32,  "noiseOctaves", NoiseOctaves) \

IMPLEMENT_CLASS(UApexJetComponent);

void UApexJetComponent::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	UProperty* PropertyThatChanged = PropertyChangedEvent.Property;
	if (PropertyThatChanged)
	{
		FLOAT CapsuleRadius = GridShapeRadius;
		FLOAT CapsuleHeight = GridShapeHeight;

		if (Cast<UDrawCapsuleComponent>(DrawComponent)->CapsuleHeight != CapsuleHeight)
		{
			Cast<UDrawCapsuleComponent>(DrawComponent)->CapsuleHeight = CapsuleHeight;
		}
		if (Cast<UDrawCapsuleComponent>(DrawComponent)->CapsuleRadius != CapsuleRadius)
		{
			Cast<UDrawCapsuleComponent>(DrawComponent)->CapsuleRadius = CapsuleRadius;
		}

#if WITH_APEX_FIELD_SAMPLERS
		if (ApexAssetParams != NULL)
		{
			UBOOL bRecreateAsset = FALSE;
			::NxParameterized::Interface* Params = (::NxParameterized::Interface*)ApexAssetParams;
#define PROCESS_ASSET_PARAM(_recreate, _typeName, _type, _paramName, _value) \
			{ \
				_type Value; NxParameterized::getParam##_typeName(*Params, _paramName, Value); \
				if (Value != _value) \
				{ \
					NxParameterized::setParam##_typeName(*Params, _paramName, _value); \
					bRecreateAsset |= _recreate; \
				} \
			}

			ITERATE_ASSET_PARAMS()
#undef PROCESS_ASSET_PARAM

			// NVCHANGE_BEGIN: JCAO - field samplers support UE3 collision channels
			if(PropertyThatChanged->GetFName() == FName(TEXT("CollisionChannel")) || PropertyThatChanged->Category == FName(TEXT("RBCollisionChannelContainer")))
			{
				bRecreateAsset |= true;
			}
			// NVCHANGE_END: JCAO - field samplers support UE3 collision channels

			if (bRecreateAsset)
			{
				RecreateApexObjects();
			}
			else
			{
				UpdateApexActor();
			}
		}
#endif
	}
}

void UApexJetComponent::SetTransformedToWorld()
{
	Super::SetTransformedToWorld();

#if WITH_APEX_FIELD_SAMPLERS
	NxJetFSActor* ApexFSActor = (NxJetFSActor*)ApexActor;
	if (ApexFSActor != NULL)
	{
		FMatrix Transform;
		GetTransform(Transform);

		physx::PxMat34Legacy Pose = U2NTransformApex(Transform);
		ApexFSActor->setCurrentPose(Pose);
	}
#endif
}

const char* UApexJetComponent::GetApexAssetObjTypeName()
{
#if WITH_APEX_FIELD_SAMPLERS
	return NX_JET_FS_AUTHORING_TYPE_NAME;
#else
	return 0;
#endif
}

void UApexJetComponent::SetupApexAssetParams()
{
#if WITH_APEX_FIELD_SAMPLERS
	::NxParameterized::Interface* Params = (::NxParameterized::Interface*)ApexAssetParams;
	if (Params != NULL)
	{
		::NxParameterized::setParamF32(*Params, "defaultScale", 1.0f);
		::NxParameterized::setParamVec3(*Params, "fieldDirection", physx::PxVec3(1, 0, 0));

#define PROCESS_ASSET_PARAM(_recreate, _typeName, _type, _paramName, _value) \
		NxParameterized::setParam##_typeName(*Params, _paramName, _value);

		ITERATE_ASSET_PARAMS()
#undef PROCESS_ASSET_PARAM
		// NVCHANGE_BEGIN: JCAO - Add field sampler group filter
		NxParameterized::setParamString(*Params, "fieldSamplerFilterDataName", "FSfieldSamplerFilter");
		// NVCHANGE_END: JCAO - Add field sampler group filter
	}
#endif
}

void UApexJetComponent::SetupApexActorParams(void* ActorParams)
{
#if WITH_APEX_FIELD_SAMPLERS
	::NxParameterized::Interface* Params = (::NxParameterized::Interface*)ActorParams;
	if (Params != NULL)
	{
		FMatrix Transform;
		GetTransform(Transform);

		physx::PxMat34Legacy Pose = U2NTransformApex(Transform);
		::NxParameterized::setParamMat34(*Params, "initialPose", Pose);
	}
#endif
}

void UApexJetComponent::UpdateApexActor()
{
#if WITH_APEX_FIELD_SAMPLERS
	NxJetFSActor* ApexFSActor = (NxJetFSActor*)ApexActor;
	if (ApexFSActor != NULL)
	{
		ApexFSActor->setEnabled(bEnabled);

		ApexFSActor->setFieldStrength(FieldStrength * U2PScale);
	}
#endif
}

#undef ITERATE_ASSET_PARAMS
// NVCHANGE_END: JCAO - create ApexJetComponent ApexGridComponent and ApexAttractorComponent
