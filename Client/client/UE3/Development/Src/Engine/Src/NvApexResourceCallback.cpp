/*=============================================================================
	NvApexResourceCallback.cpp : Manages resource requests from APEX
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

#if WITH_NOVODEX

#include "NvApexManager.h"

#if WITH_APEX


#include "NvApexResourceCallback.h"
#include "EnginePhysicsClasses.h"
#include "EngineSequenceClasses.h"
#include "EngineParticleClasses.h"
#include "EngineClasses.h"
#include "EngineMeshClasses.h"

#include "UnNovodexSupport.h"
#include <NxApexSDK.h>
#include <NxResourceCallback.h>
#include <NxUserRenderResourceManager.h>
#include <NxModuleDestructible.h>
#include <NxModuleClothing.h>
#include <NxRendermeshAsset.h>
#include <NxDestructibleAsset.h>
#include <NxClothingAsset.h>
// NVCHANGE_BEGIN: DJS - Apex 1.2 Remove old particle module
#if WITH_APEX_PARTICLES
#include <NxApexEmitterAsset.h>
#include <NxGroundEmitterAsset.h>
#include <NxImpactEmitterAsset.h>
#include <NxBasicIosAsset.h>
// NVCHANGE_BEGIN: JCAO - Use WITH_APEX_FLUID_IOS to control whether to load Fluid IOS Module and create Fluid IOS Asset
#if WITH_APEX_FLUID_IOS
#include <NxModuleFluidIos.h>
#endif // WITH_APEX_FLUID_IOS
// NVCHANGE_END: JCAO - Use WITH_APEX_FLUID_IOS to control whether to load Fluid IOS Module and create Fluid IOS Asset
#include <NxIofxAsset.h>
#endif
// NVCHANGE_END: DJS - Apex 1.2 Remove old particle module
#include "NvApexScene.h"
#include <NxActorDesc.h>
#include <NxStream.h>
#include <stdarg.h>
#include <NxSerializer.h>
#include <NxUserOpaqueMesh.h>
#include "NvApexCommands.h"

physx::apex::NxResourceCallback *GApexResourceCallback=NULL;

using namespace physx::apex;

/**
 * Helper function to find an APEX asset from the object containing it
**/
template< class T >
// NVCHANGE_BEGIN: APAN - Code review, improve performance
static void* FindApexAsset( const FString& UnrealName )
// NVCHANGE_END: APAN - Code review, improve performance
{
	UBOOL               bIsValidName = IsValidObjectPathName(UnrealName);

	if( !IsInGameThread() )
	{
		debugf( NAME_DevPhysics, TEXT("NvApexResourceCallback: Attempting to load resource %s in a thread other than the game thread.  Returning NULL."), *UnrealName );
	}
	else
	{
		T* ObjectToLoad = NULL;
		if(bIsValidName)
		{
			ObjectToLoad = FindObject<T>(0, *UnrealName);
			if ( ObjectToLoad && ObjectToLoad->MApexAsset )
			{
				return ObjectToLoad->MApexAsset->GetNxApexAsset();
			}
		}
	}

	return NULL;
}

namespace NI_APEX_RESOURCE_CALLBACK
{

class NvApexResourceCallback : public NxResourceCallback
{
public:
	NvApexResourceCallback(void)
	{
		GApexResourceCallback = this;
	}
	~NvApexResourceCallback(void)
	{
		GApexResourceCallback = NULL;
	}

	/**
	Will be called by the ApexSDK if a named resource is required but has not yet been provided.
	The resource pointer is returned directly, NxResourceProvider::setResource() should not be called.
	This function will be called at most once per named resource, unless an intermediate call to
	releaseResource() has been made.
	*/
    virtual void *requestResource( const char *pcNameSpace, const char *pcName )
    {
		FIApexManager *manager = GApexCommands ? GApexCommands->GetApexManager() : 0;
		if ( !manager )
		{
			return NULL;
		}
    	NxApexSDK* pkApexSDK = manager->GetApexSDK();
		if ( !pkApexSDK )
		{
			return NULL;
		}

        void *ret = NULL;

		if (  appStrcmpANSI(pcNameSpace,NX_DESTRUCTIBLE_AUTHORING_TYPE_NAME) == 0 )
		{
			ret = FindApexAsset<UApexDestructibleAsset>(ANSI_TO_TCHAR(pcName));
		}
		else if (  appStrcmpANSI(pcNameSpace,NX_CLOTHING_AUTHORING_TYPE_NAME) == 0 )
		{
			ret = FindApexAsset<UApexClothingAsset>(ANSI_TO_TCHAR(pcName));
		}
// NVCHANGE_BEGIN: DJS - Apex 1.2 Remove support for 0.9 Clothing Assets
// NVCHANGE_END: DJS - Apex 1.2 Remove support for 0.9 Clothing Assets
		else if ( appStrcmpANSI(pcNameSpace,APEX_MATERIALS_NAME_SPACE) == 0 )
		{
			if( !IsInGameThread() )
			{
				debugf( NAME_DevPhysics, TEXT("NvApexResourceCallback: Attempting to load resource %s in a thread other than the game thread.  Returning NULL."), ANSI_TO_TCHAR(pcName) );
			}
			else
			{
   				UMaterialInterface *MaterialInterface = FindMaterialForApex(pcName);
				ret = MaterialInterface;
			}
       	}
		else if ( appStrcmpANSI(pcNameSpace,APEX_OPAQUE_MESH_NAME_SPACE) == 0 )
		{
			if ( pcName == NULL )
			{
				pcName = "EngineApexResources.ApexParticleCube";
			}
			if ( appStrcmpANSI(pcName,"EngineApexResources.ApexParticleCube") == 0 )
			{
#if WITH_APEX_PARTICLES
				ret = GApexCommands->GetStaticMesh();
#endif
			}
			else
			{
				ret = FindObject<UStaticMesh>(0, ANSI_TO_TCHAR(pcName));
			}
		}
		else if ( appStrcmpANSI(pcNameSpace,APEX_COLLISION_GROUP_NAME_SPACE) == 0 )
		{
			if ( appStrcmpANSI(pcName,"PhysXFluidCollisionGroup") == 0 )
			{
				ret = (void *)UNX_GROUP_DEFAULT;
			}
			else
			{
				// set APEX_COLLISION_GROUP_NAME_SPACE for BasicIOS
				FString BasicIosAssetName = ANSI_TO_TCHAR(pcName);
				FString FileExt = TEXT(".apb");
				if(BasicIosAssetName.Right(FileExt.Len()) == FileExt)
				{
					BasicIosAssetName = BasicIosAssetName.LeftChop(FileExt.Len());
				}

				UApexGenericAsset* basicIOSAsset = FindObject<UApexGenericAsset>(0, *BasicIosAssetName);
				if(basicIOSAsset)
				{
					ret = (void*)basicIOSAsset->CollideChannel;
				}
				else
				{
					// if need set default APEX_COLLISION_GROUP_NAME_SPACE, write here.
				}
			}
		}
		else if ( appStrcmpANSI(pcNameSpace,APEX_COLLISION_GROUP_MASK_NAME_SPACE) == 0 )
		{
			// We can't fulfill this type of request yet
			check(0);
		}
		else if ( appStrcmpANSI(pcNameSpace,APEX_COLLISION_GROUP_128_NAME_SPACE) == 0 )
		{
			if ( appStrcmpANSI(pcName,"PhysXFluidCollisionGroup") == 0 )
			{
				FRBCollisionChannelContainer c;
				c.Bitfield = 0;
				c.Default = 1;
				c.GameplayPhysics = 1;
				c.FluidDrain = 1;
				static NxGroupsMask mask = CreateGroupsMask(UNX_GROUP_DEFAULT,&c);
				ret = &mask;
			}
			else
			{
				// set APEX_COLLISION_GROUP_128_NAME_SPACE for BasicIOS
				FString BasicIosAssetName = ANSI_TO_TCHAR(pcName);
				FString FileExt = TEXT(".apb");
				if(BasicIosAssetName.Right(FileExt.Len()) == FileExt)
				{
					BasicIosAssetName = BasicIosAssetName.LeftChop(FileExt.Len());
				}

				UApexGenericAsset* basicIOSAsset = FindObject<UApexGenericAsset>(0, *BasicIosAssetName);
				if(basicIOSAsset)
				{
					static NxGroupsMask mask = CreateGroupsMask( basicIOSAsset->CollideChannel, &basicIOSAsset->CollideWithChannels );
					ret = &mask;
				}
				else
				{
					// if need set default APEX_COLLISION_GROUP_128_NAME_SPACE, write here.
				}
			}
		}
		else if ( appStrcmpANSI(pcNameSpace,APEX_COLLISION_GROUP_64_NAME_SPACE) == 0 )
		{
			// set APEX_COLLISION_GROUP_64_NAME_SPACE for BasicIOS
			FString BasicIosAssetName = ANSI_TO_TCHAR(pcName);
			FString FileExt = TEXT(".apb");
			if(BasicIosAssetName.Right(FileExt.Len()) == FileExt)
			{
				BasicIosAssetName = BasicIosAssetName.LeftChop(FileExt.Len());
			}

			UApexGenericAsset* basicIOSAsset = FindObject<UApexGenericAsset>(0, *BasicIosAssetName);
			if(basicIOSAsset)
			{
				static NxGroupsMask64 mask64 = CreateGroupsMask64( basicIOSAsset->CollideChannel, &basicIOSAsset->CollideWithChannels );
				ret = &mask64;
			}
			else
			{
				// if need set default APEX_COLLISION_GROUP_64_NAME_SPACE, write here.
			}
		}
		else if(
// NVCHANGE_BEGIN: DJS - APEX particle support
#if WITH_APEX_PARTICLES
				 appStrcmpANSI(pcNameSpace,NX_APEX_EMITTER_AUTHORING_TYPE_NAME) == 0  ||
				 appStrcmpANSI(pcNameSpace,NX_GROUND_EMITTER_AUTHORING_TYPE_NAME) == 0 ||
				 appStrcmpANSI(pcNameSpace,NX_IMPACT_EMITTER_AUTHORING_TYPE_NAME) == 0 ||
				 appStrcmpANSI(pcNameSpace,NX_BASIC_IOS_AUTHORING_TYPE_NAME) == 0 ||
				 // NVCHANGE_BEGIN: JCAO - Use WITH_APEX_FLUID_IOS to control whether to load Fluid IOS Module and create Fluid IOS Asset
#if WITH_APEX_FLUID_IOS
				 appStrcmpANSI(pcNameSpace,NX_FLUID_IOS_AUTHORING_TYPE_NAME) == 0 ||
#endif
				 // NVCHANGE_END: JCAO - Use WITH_APEX_FLUID_IOS to control whether to load Fluid IOS Module and create Fluid IOS Asset
				 appStrcmpANSI(pcNameSpace,NX_IOFX_AUTHORING_TYPE_NAME) == 0 ||
#endif
// NVCHANGE_END: DJS - APEX particle support
				 appStrcmpANSI(pcNameSpace,NX_RENDER_MESH_AUTHORING_TYPE_NAME) == 0 ||
				 appStrcmpANSI(pcNameSpace,APEX_AUTHORABLE_ASSETS_TYPES_NAME_SPACE) == 0 ||
				 appStrcmpANSI(pcNameSpace,APEX_PHYSICS_MATERIAL_NAME_SPACE) == 0 )
		{
			FIApexAsset *asset = GApexCommands->GetApexAsset(pcName,FALSE);
			if ( asset )
			{
				ret = asset->GetNxApexAsset();
			}
			else
			{
#if WITH_APEX_PARTICLES
				if ( appStrcmpANSI(pcNameSpace,"NxBasicIosAsset") == 0 && appStrcmpANSI(pcName,"DefaultBasicIOS") == 0  )
				{
					asset = GApexCommands->CreateDefaultApexAsset(pcName,AAT_BASIC_IOS,NULL,NULL);
					check(asset);
					if ( asset )
					{
						ret = asset->GetNxApexAsset();
					}
				}
				// NVCHANGE_BEGIN: JCAO - Use WITH_APEX_FLUID_IOS to control whether to load Fluid IOS Module and create Fluid IOS Asset
#if WITH_APEX_FLUID_IOS
				else if ( appStrcmpANSI(pcNameSpace,"NxFluidIosAsset") == 0 && appStrcmpANSI(pcName,"DefaultFluidIOS") == 0  )
				{
					asset = GApexCommands->CreateDefaultApexAsset(pcName,AAT_FLUID_IOS,NULL,NULL);
					check(asset);
					if ( asset )
					{
						ret = asset->GetNxApexAsset();
					}
				}
#endif
				// NVCHANGE_END: JCAO - Use WITH_APEX_FLUID_IOS to control whether to load Fluid IOS Module and create Fluid IOS Asset

#endif
			}
			if (ret == NULL )
			{
				debugf( NAME_DevPhysics, TEXT("NvApexResourceCallback: Unable to located Apex resource %s!"), ANSI_TO_TCHAR(pcName) );
			}
		}
		else if( (appStrcmpANSI(pcNameSpace,APEX_CUSTOM_VB_NAME_SPACE) == 0) && (appStrcmpANSI(pcName, "DCC_INDEX") == 0) )
		{
			// Intentionally ignored. It's a custom vertex buffer semantic which tells which index
			// the vertex had in the DCC tools.
		}
		else if( (strcmp(pcNameSpace,APEX_CUSTOM_VB_NAME_SPACE) == 0) && (strcmp(pcName, "VERTEX_ORIGINAL_INDEX") == 0) )
		{
			// Intentionally ignored. It's a custom vertex buffer semantic which tells which index
			// the vertex had.
		}
        else
        {
			debugf( NAME_DevPhysics, TEXT("NvApexResourceCallback: Unknown resource type %s!"), ANSI_TO_TCHAR(pcNameSpace) );
			check(0);
        }
   		return ret;
    }

	/**
	Will be called by the ApexSDK when all internal references to a named resource have been released.
	If this named resource is required again in the future, a new call to requestResource() will be made.
	*/
    //---------------------------------------------------------------------------
    virtual void releaseResource( const char *pcNameSpace, const char *pcName, void *pvResource )
    {
    }

private:
};

}; // end of namespace

using namespace NI_APEX_RESOURCE_CALLBACK;


/**
 * Creates a resource callback function
 * @return	null if it fails, else returns a pointer to the resource callback. 
**/
NxResourceCallback * CreateResourceCallback(void)
{
	NvApexResourceCallback *nv = new NvApexResourceCallback;
	return static_cast< NxResourceCallback *>(nv);
}
/**
 * Release the resource callback function
 * @param [in,out]	Callback	The resource callback. 
**/
void ReleaseResourceCallback(NxResourceCallback *Callback)
{
	NvApexResourceCallback *nv = static_cast< NvApexResourceCallback *>(Callback);
	delete nv;
}

#endif

#endif
