// NVCHANGE_BEGIN: JCAO - create ApexJetComponent ApexGridComponent and ApexAttractorComponent
/*=============================================================================
	NvApexGridComponent.cpp : Handles APEX Grid objects.
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
#include <NxModuleTurbulenceFS.h>
#include <NxTurbulenceFSAsset.h>
#include <NxTurbulenceFSActor.h>
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
	PROCESS_ASSET_PARAM_ENUM(TRUE,  "gridXRange.min", GridMinResolutionEnum) \
	PROCESS_ASSET_PARAM_ENUM(TRUE,  "gridXRange.max", GridMaxResolutionEnum) \
	PROCESS_ASSET_PARAM_ENUM(TRUE,  "gridYRange.min", GridMinResolutionEnum) \
	PROCESS_ASSET_PARAM_ENUM(TRUE,  "gridYRange.max", GridMaxResolutionEnum) \
	PROCESS_ASSET_PARAM_ENUM(TRUE,  "gridZRange.min", GridMinResolutionEnum) \
	PROCESS_ASSET_PARAM_ENUM(TRUE,  "gridZRange.max", GridMaxResolutionEnum) \
	PROCESS_ASSET_PARAM(TRUE,  Vec3, physx::PxVec3, "gridSizeWorld", physx::PxVec3(GridSize * GridSize3D.X * U2PScale, GridSize * GridSize3D.Y * U2PScale, GridSize * GridSize3D.Z * U2PScale)) \
	PROCESS_ASSET_PARAM(TRUE,  F32,  physx::PxF32,  "updatesPerFrameRange.min", UpdatesPerFrameRange.Min) \
	PROCESS_ASSET_PARAM(TRUE,  F32,  physx::PxF32,  "updatesPerFrameRange.max", UpdatesPerFrameRange.Max) \
	PROCESS_ASSET_PARAM(FALSE, F32,  physx::PxF32,  "fluidVelocityMultiplier", FluidVelocityMultiplier) \
	PROCESS_ASSET_PARAM(FALSE, F32,  physx::PxF32,  "fluidVelocityClamp", FluidVelocityClamp * U2PScale) \
	PROCESS_ASSET_PARAM(TRUE,  F32,  physx::PxF32,  "boundaryFadePercentage", BoundaryFadePercentage) \
	PROCESS_ASSET_PARAM(TRUE,  F32,  physx::PxF32,  "boundarySizePercentage", BoundarySizePercentage) \
	PROCESS_ASSET_PARAM(TRUE,  U32,  physx::PxU32,  "maxCollidingObjects", MaxCollidingObjects) \
	PROCESS_ASSET_PARAM(TRUE,  U32,  physx::PxU32,  "maxHeatSources", MaxHeatSources) \
	PROCESS_ASSET_PARAM(TRUE,  F32,  physx::PxF32,  "dragCoeff", DragCoeff) \
	PROCESS_ASSET_PARAM(TRUE,  F32,  physx::PxF32,  "dragCoeffForRigidBody", DragCoeffForRigidBody) \
	PROCESS_ASSET_PARAM(TRUE,  F32,  physx::PxF32,  "fluidViscosity", FluidViscosity) \

IMPLEMENT_CLASS(UApexGridComponent);

static char* EnumValFromGridResolutionEnum(EGridResolution GridResolutionEnum)
{
	static char* TurbulenceRangeEnum[] = { "EGR_12", "EGR_16", "EGR_24", "EGR_32", "EGR_48", "EGR_64", "EGR_96", "EGR_128" };
	check((INT)GridResolutionEnum < sizeof(TurbulenceRangeEnum) / sizeof(TurbulenceRangeEnum[0]));
	return TurbulenceRangeEnum[GridResolutionEnum];
}

void UApexGridComponent::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	UProperty* PropertyThatChanged = PropertyChangedEvent.Property;
	if (PropertyThatChanged != NULL)
	{
		// clean up invalid inputs
		if (PropertyThatChanged->GetFName() == FName(TEXT("GridMinResolution")))
		{
			if (GridMinResolution > GridMaxResolution)
			{
				GridMinResolution = GridMaxResolution;
			}
		}
		else if (PropertyThatChanged->GetFName() == FName(TEXT("GridMaxResolution")))
		{
			if (GridMaxResolution < GridMinResolution)
			{
				GridMaxResolution = GridMinResolution;
			}
		}

		const char* GridMinResolutionEnum = EnumValFromGridResolutionEnum((EGridResolution)GridMinResolution);
		const char* GridMaxResolutionEnum = EnumValFromGridResolutionEnum((EGridResolution)GridMaxResolution);

		FVector BoxExtent = GridSize3D * (GridSize * 0.5);

		if (Cast<UDrawBoxComponent>(DrawComponent)->BoxExtent != BoxExtent)
		{
			Cast<UDrawBoxComponent>(DrawComponent)->BoxExtent = BoxExtent;
		}

#if WITH_APEX_FIELD_SAMPLERS
		if (ApexAssetParams != NULL)
		{
			UBOOL bRecreateAsset = FALSE;
			::NxParameterized::Interface* Params = (::NxParameterized::Interface*)ApexAssetParams;
#define PROCESS_ASSET_PARAM_ENUM(_recreate, _paramName, _value) \
			{	\
				const char* Value; NxParameterized::getParamEnum(*Params, _paramName, Value); \
				if (strcmp(Value, _value) != 0) \
				{ \
					NxParameterized::setParamEnum(*Params, _paramName, _value); \
					bRecreateAsset |= _recreate; \
				} \
			}

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

#undef PROCESS_ASSET_PARAM_ENUM

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

void UApexGridComponent::SetTransformedToWorld()
{
	Super::SetTransformedToWorld();

#if WITH_APEX_FIELD_SAMPLERS
	NxTurbulenceFSActor* ApexFSActor = (NxTurbulenceFSActor*)ApexActor;
	if (ApexFSActor != NULL)
	{
		FMatrix Transform;
		GetTransform(Transform);

		physx::PxMat34Legacy Pose = U2NTransformApex(Transform);
		ApexFSActor->setPose(Pose);
	}
#endif
}

const char* UApexGridComponent::GetApexAssetObjTypeName()
{
#if WITH_APEX_FIELD_SAMPLERS
	return NX_TURBULENCE_FS_AUTHORING_TYPE_NAME;
#else
	return 0;
#endif
}

void UApexGridComponent::SetupApexAssetParams()
{
#if WITH_APEX_FIELD_SAMPLERS
	::NxParameterized::Interface* Params = (::NxParameterized::Interface*)ApexAssetParams;
	if (Params != NULL)
	{
		const char* GridMinResolutionEnum = EnumValFromGridResolutionEnum((EGridResolution)GridMinResolution);
		const char* GridMaxResolutionEnum = EnumValFromGridResolutionEnum((EGridResolution)GridMaxResolution);

#define PROCESS_ASSET_PARAM_ENUM(_recreate, _paramName, _value) \
		NxParameterized::setParamEnum(*Params, _paramName, _value);

#define PROCESS_ASSET_PARAM(_recreate, _typeName, _type, _paramName, _value) \
		NxParameterized::setParam##_typeName(*Params, _paramName, _value);

		ITERATE_ASSET_PARAMS()
#undef PROCESS_ASSET_PARAM
#undef PROCESS_ASSET_PARAM_ENUM
		// NVCHANGE_BEGIN: JCAO - field samplers support UE3 collision channels
		NxParameterized::setParamString(*Params, "collisionFilterDataName", "FSCollisionFilter");
		// NVCHANGE_END: JCAO - field samplers support UE3 collision channels
		// NVCHANGE_BEGIN: JCAO - Add field sampler group filter
		NxParameterized::setParamString(*Params, "fieldSamplerFilterDataName", "FSfieldSamplerFilter");
		// NVCHANGE_END: JCAO - Add field sampler group filter
	}
#endif
}

void UApexGridComponent::SetupApexActorParams(void* ActorParams)
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

void UApexGridComponent::UpdateApexActor()
{
#if WITH_APEX_FIELD_SAMPLERS
	NxTurbulenceFSActor* ApexFSActor = (NxTurbulenceFSActor*)ApexActor;
	if (ApexFSActor != NULL)
	{
		ApexFSActor->setEnabled(bEnabled);

		ApexFSActor->setVelocityScaleAndClamp(FluidVelocityMultiplier, FluidVelocityClamp * U2PScale);
		ApexFSActor->setAngularVelocityMultiplierAndClamp(AngularVelocityMultiplier, AngularVelocityClamp * U2PScale);
		ApexFSActor->setLinearVelocityMultiplierAndClamp(LinearVelocityMultiplier, LinearVelocityClamp * U2PScale);

		ApexFSActor->setExternalVelocity(physx::PxVec3(ExternalVelocity.X * U2PScale, ExternalVelocity.Y * U2PScale, ExternalVelocity.Z * U2PScale));

		ApexFSActor->setFieldVelocityMultiplier(FieldVelocityMultiplier);
		ApexFSActor->setFieldVelocityWeight(FieldVelocityWeight);

		ApexFSActor->setAutoVelocityParameters(AutoVelocityEnabled, AutoVelocityTeleportValue * U2PScale, AutoVelocityImpulseClamp * U2PScale, AutoVelocitySmoothingTimeConstant);

		ApexFSActor->setNoiseParameters(NoiseStrength, physx::PxVec3(NoiseSpacePeriod * U2PScale), NoiseTimePeriod, NoiseOctaves);
	}
#endif
}

#undef ITERATE_ASSET_PARAMS
// NVCHANGE_END: JCAO - create ApexJetComponent ApexGridComponent and ApexAttractorComponent
