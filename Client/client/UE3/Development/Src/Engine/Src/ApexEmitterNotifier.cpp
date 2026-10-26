// NVCHANGE_BEGIN: JCAO - Fix DE5806 Crash when clicking on a Required module in Cascade
#include "EnginePrivate.h"
#include "EngineParticleClasses.h"
#include "ApexEmitterNotifier.h"

#if WITH_APEX_PARTICLES
#include "UnNovodexSupport.h"
#include "ParticleEmitterInstances_Apex.h"
#endif

#if WITH_APEX_EDITOR
#include "PxEditorWidgetManager.h"
#include "NxParamUtils.h"
#endif

ApexEmitterNotifier::ApexEmitterNotifier(class UParticleModuleTypeDataApex &TypeData)
	:ApexTypeData(TypeData)
{
#if WITH_APEX_PARTICLES
	EmitterInstance = NULL;
#endif
}

ApexEmitterNotifier::~ApexEmitterNotifier(void)
{
#if WITH_APEX_PARTICLES
	EmitterInstance = NULL;
#endif
}

#if WITH_APEX_PARTICLES
NxParameterized::Interface * ApexEmitterNotifier::GetNxParameterized(void)
{
	NxParameterized::Interface *ret = NULL;
#if WITH_APEX_EDITOR
	if ( GApexManager && ApexTypeData.IsSprite() )
	{
		physx::PxEditorWidgetManager *emgr = GApexManager->GetPxEditorWidgetManager();
		if ( emgr )
		{
			ret = emgr->createCustomInterface("CustomIOFXParams", GApexManager->GetApexSDK()->getParameterizedTraits());
			if ( ret )
			{
				NxParameterized::Handle handle(*ret);
				if ( NxParameterized::findParam(*ret,"subUV_Blend",handle))
				{
					handle.setParamBool( ApexTypeData.SubUVBlend ? true : false );
				}
				if ( NxParameterized::findParam(*ret,"subUV_Start",handle))
				{
					handle.setParamU32( (physx::PxU32) ApexTypeData.SubUVStart );
				}
				if ( NxParameterized::findParam(*ret,"subUV_Count",handle))
				{
					handle.setParamU32( (physx::PxU32) ApexTypeData.SubUVCount );
				}
				if ( NxParameterized::findParam(*ret,"Sub_Images_Horizontal",handle))
				{
					handle.setParamU32( (physx::PxU32) ApexTypeData.SubImagesHorizontal );
				}
				if ( NxParameterized::findParam(*ret,"Sub_Images_Vertical",handle))
				{
					handle.setParamU32( (physx::PxU32) ApexTypeData.SubImagesVertical );
				}
			}
		}
	}
#endif // endif WITH_APEX_EDITOR
	return ret;
}

UBOOL  ApexEmitterNotifier::OnPostPropertyEdit(NxParameterized::Interface *iface,NxParameterized::Handle &handle,const char *tweakable)
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

	if(EmitterInstance)
	{
		EmitterInstance->OnPostPropertyEdit(iface, handle, tweakable);
	}

	return TRUE;
}

UBOOL  ApexEmitterNotifier::NotifyEditorClosed(NxParameterized::Interface *iface)
{
	if(EmitterInstance)
	{
		EmitterInstance->NotifyEditorClosed(iface);
	}

	return TRUE;
}
#endif // WITH_APEX_PARTICLES

// NVCHANGE_END: JCAO - Fix DE5806 Crash when clicking on a Required module in Cascade