
#include "EnginePrivate.h"
#include "EngineParticleClasses.h"
#include "EnginePhysicsClasses.h"
#include "EngineMeshClasses.h"
#include "ParticleEmitterInstances_Apex.h"

#if WITH_NOVODEX
	#include "UnNovodexSupport.h"
#endif		// WITH_NOVODEX

#if WITH_APEX_PARTICLES
#include "NvApexCommands.h"
// NVCHANGE_BEGIN: JCAO - Fix DE5806 Crash when clicking on a Required module in Cascade
#include "ApexEmitterNotifier.h"
// NVCHANGE_END: JCAO - Fix DE5806 Crash when clicking on a Required module in Cascade
#endif


/////////////////////////////////////////////////////////////////////////////////////////////

IMPLEMENT_CLASS(UParticleModuleTypeDataApex);
IMPLEMENT_CLASS(UParticleModuleTypeDataApexSprite);

#if WITH_APEX_PARTICLES
static UApexGenericAsset * CreateApexGenericAsset(UObject* apexGenericAsset,ApexAssetType assetType)
{
	// NVCHANGE_BEGIN: JCAO - Create Apex IOFX Asset and Apex Emitter Asset in the format of Package.Group.ParticleSystemName.ApexGeneratedAssetName
	FString DefaultAssetName;
	GApexCommands->GetUniqueAssetName(assetType,DefaultAssetName);

	return ConstructObject<UApexGenericAsset>(	UApexGenericAsset::StaticClass(), 
												apexGenericAsset->GetOuter(), 
												*DefaultAssetName,
												/* RF_Public|*/RF_Standalone );
	// NVCHANGE_END: JCAO - Create Apex IOFX Asset and Apex Emitter Asset in the format of Package.Group.ParticleSystemName.ApexGeneratedAssetName
}
#endif

FParticleEmitterInstance *UParticleModuleTypeDataApex::CreateInstance(UParticleEmitter *InEmitterParent, UParticleSystemComponent *InComponent)
{
#if WITH_APEX_PARTICLES
	SetToSensibleDefaults(InEmitterParent);

	if ( ApexIOFX == NULL )
	{
		ApexIOFX = CreateApexGenericAsset(this,IsSprite() ? AAT_IOFX_SPRITE : AAT_IOFX_MESH );
	}

	if ( ApexEmitter == NULL )
	{
		ApexEmitter = CreateApexGenericAsset(this,AAT_APEX_EMITTER);
	}

	if(ApexIOFX && !ApexIOFX->MApexAsset)
	{
		ApexIOFX->MarkPackageDirty();
		if ( IsSprite() )
		{
			ApexIOFX->CreateDefaultAssetType(AAT_IOFX_SPRITE,NULL);
		}
		else
		{
			ApexIOFX->CreateDefaultAssetType(AAT_IOFX_MESH,NULL);
		}
	}

	if(ApexEmitter && !ApexEmitter->MApexAsset)
	{
		ApexEmitter->MarkPackageDirty();
		ApexEmitter->CreateDefaultAssetType(AAT_APEX_EMITTER,ApexIOFX);
	}
	// NVCHANGE_BEGIN: JCAO - Apex Emitter Asset work with LODs
	if(ApexLODAssets.Num() == 0)
	{
		FApexLODAsset ApexLODAsset;
		ApexLODAsset.IOFXAsset = ApexIOFX;
		ApexLODAsset.EmitterAsset = ApexEmitter;
		ApexLODAssets.AddItem(ApexLODAsset);
	}
	{
		INT Level = ApexLODAssets.Num() - 1;
		while(ApexLODAssets.Num() < InEmitterParent->LODLevels.Num()) {
			GenerateLODAsset(Level, Level+1);
			Level++;
		}
	}
	// NVCHANGE_END: JCAO - Apex Emitter Asset work with LODs
	// NVCHANGE_BEGIN: JCAO - Fix DE5806 Crash when clicking on a Required module in Cascade
	if(EmitterNotifier == NULL)
	{
		EmitterNotifier = new ApexEmitterNotifier(*this);
	}

	FParticleApexEmitterInstance *Instance = new FParticleApexEmitterInstance(*this);
	check(Instance);
	Instance->InitParameters(InEmitterParent, InComponent);
	
	if(EmitterNotifier)
	{
		EmitterNotifier->SetEmitterInstance(Instance);
	}
	// NVCHANGE_END: JCAO - Fix DE5806 Crash when clicking on a Required module in Cascade

	return Instance;
#else
	return 0;
#endif
}

// NVCHANGE_BEGIN: HL - Apex Emitter Asset Copy
void UParticleModuleTypeDataApex::CopyAndReplaceApexRefs()
{
#if WITH_APEX_PARTICLES
	if(ApexLODAssets.Num() == 0)
	{
		UApexGenericAsset* NewApexIOFX = CreateApexGenericAsset(this,IsSprite() ? AAT_IOFX_SPRITE : AAT_IOFX_MESH );
		UApexGenericAsset* NewApexEmitter = CreateApexGenericAsset(this,AAT_APEX_EMITTER );

		ApexIOFX->CopyApexAsset(NewApexIOFX, NULL);
		ApexEmitter->CopyApexAsset(NewApexEmitter, NewApexIOFX);

		ApexIOFX = NewApexIOFX;
		ApexEmitter = NewApexEmitter;

		// do we need to mark it dirty?
		ApexIOFX->MarkPackageDirty();
		ApexEmitter->MarkPackageDirty();

		FApexLODAsset ApexLODAsset;
		ApexLODAsset.IOFXAsset = ApexIOFX;
		ApexLODAsset.EmitterAsset = ApexEmitter;
		ApexLODAssets.AddItem(ApexLODAsset);
	}
	else
	{
		for(INT i = 0; i < ApexLODAssets.Num(); i++)
		{
			UApexGenericAsset* NewApexIOFX = CreateApexGenericAsset(this,IsSprite() ? AAT_IOFX_SPRITE : AAT_IOFX_MESH );
			UApexGenericAsset* NewApexEmitter = CreateApexGenericAsset(this,AAT_APEX_EMITTER );

			ApexLODAssets(i).IOFXAsset->CopyApexAsset(NewApexIOFX, NULL);
			ApexLODAssets(i).EmitterAsset->CopyApexAsset(NewApexEmitter, NewApexIOFX);

			ApexLODAssets(i).IOFXAsset = NewApexIOFX;
			ApexLODAssets(i).EmitterAsset = NewApexEmitter;

			ApexLODAssets(i).IOFXAsset->MarkPackageDirty();
			ApexLODAssets(i).EmitterAsset->MarkPackageDirty();

			if(i == 0)
			{
				ApexIOFX = ApexLODAssets(i).IOFXAsset;
				ApexEmitter = ApexLODAssets(i).EmitterAsset;
			}
		}
	}
#endif
}
// NVCHANGE_END: HL - Apex Emitter Asset Copy

void UParticleModuleTypeDataApex::SetToSensibleDefaults(UParticleEmitter *Owner)
{
	Super::SetToSensibleDefaults(Owner);
	
	// TODO...
}

void UParticleModuleTypeDataApex::PreEditChange(UProperty *PropertyAboutToChange)
{
	// TODO...
	
	Super::PreEditChange(PropertyAboutToChange);
}

void UParticleModuleTypeDataApex::PostEditChangeProperty(FPropertyChangedEvent &PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	// TODO...
}

void UParticleModuleTypeDataApex::FinishDestroy()
{
	// NVCHANGE_BEGIN: JCAO - Fix DE5806 Crash when clicking on a Required module in Cascade
#if WITH_APEX_PARTICLES
	if(EmitterNotifier)
	{
		delete EmitterNotifier;
		EmitterNotifier = NULL;
	}
#endif
	// NVCHANGE_END: JCAO - Fix DE5806 Crash when clicking on a Required module in Cascade

	Super::FinishDestroy();
}

void UParticleModuleTypeDataApex::ConditionalInitialize(void)
{
#if WITH_APEX_PARTICLES
	if(ApexIOFX && !ApexIOFX->MApexAsset)
	{
		ApexIOFX->MarkPackageDirty();
		if ( IsSprite() )
		{
			ApexIOFX->CreateDefaultAssetType(AAT_IOFX_SPRITE,NULL);
		}
		else
		{
			ApexIOFX->CreateDefaultAssetType(AAT_IOFX_MESH,NULL);
		}
	}
	if(ApexEmitter && !ApexEmitter->MApexAsset)
	{
		ApexEmitter->MarkPackageDirty();
		ApexEmitter->CreateDefaultAssetType(AAT_APEX_EMITTER,ApexIOFX);
	}
	// NVCHANGE_BEGIN: JCAO - Fix DE5953 APEX properties don't work with LODs in Cascade
	if(EmitterNotifier == NULL)
	{
		EmitterNotifier = new ApexEmitterNotifier(*this);
	}
	// NVCHANGE_END: JCAO - Fix DE5953 APEX properties don't work with LODs in Cascade
#endif
}

// NVCHANGE_BEGIN: JCAO - Apex Emitter Asset work with LODs
void UParticleModuleTypeDataApex::GenerateLODAsset(INT SrcLevel, INT DestLevel)
{
#if WITH_APEX_PARTICLES
	if(SrcLevel < ApexLODAssets.Num())
	{
		FApexLODAsset ApexLODAsset;

		UApexGenericAsset* NewApexIOFX = CreateApexGenericAsset(this,IsSprite() ? AAT_IOFX_SPRITE : AAT_IOFX_MESH );
		UApexGenericAsset* NewApexEmitter = CreateApexGenericAsset(this,AAT_APEX_EMITTER );

		ApexLODAssets(SrcLevel).IOFXAsset->CopyApexAsset(NewApexIOFX, NULL);
		ApexLODAssets(SrcLevel).EmitterAsset->CopyApexAsset(NewApexEmitter, NewApexIOFX);

		NewApexIOFX->MarkPackageDirty();
		NewApexEmitter->MarkPackageDirty();
		
		ApexLODAsset.IOFXAsset = NewApexIOFX;
		ApexLODAsset.EmitterAsset = NewApexEmitter;

		ApexLODAssets.InsertItem(ApexLODAsset, DestLevel);
	}
#endif
}

UParticleModule* UParticleModuleTypeDataApex::GenerateLODModule(UParticleLODLevel* SourceLODLevel, UParticleLODLevel* DestLODLevel, FLOAT Percentage, 
		UBOOL bGenerateModuleData, UBOOL bForceModuleConstruction)
{
#if WITH_APEX_PARTICLES
	if (bGenerateModuleData)
	{
		INT SrcLODLevel = SourceLODLevel->Level;
		INT DstLODLevel = DestLODLevel->Level;

		if(SourceLODLevel->Level > DestLODLevel->Level)
		{
			SrcLODLevel = SourceLODLevel->Level - 1;
		}

		GenerateLODAsset(SrcLODLevel, DstLODLevel);
	}
#endif
	
	return Super::GenerateLODModule(SourceLODLevel, DestLODLevel, Percentage, bGenerateModuleData, bForceModuleConstruction);
}

void UParticleModuleTypeDataApex::RemoveLODAsset(INT LODLevelIndex)
{
#if WITH_APEX_PARTICLES
	if(LODLevelIndex < ApexLODAssets.Num())
	{
		ApexLODAssets.Remove(LODLevelIndex);
	}
#endif
}

UApexGenericAsset* UParticleModuleTypeDataApex::GetApexLODEmitterAsset(INT LODLevelIndex)
{
#if WITH_APEX_PARTICLES
	if(LODLevelIndex < ApexLODAssets.Num())
	{
		return ApexLODAssets(LODLevelIndex).EmitterAsset;
	}
#endif

	return NULL;
}

UApexGenericAsset* UParticleModuleTypeDataApex::GetApexLODIOFXAsset(INT LODLevelIndex)
{
#if WITH_APEX_PARTICLES
	if(LODLevelIndex < ApexLODAssets.Num())
	{
		return ApexLODAssets(LODLevelIndex).IOFXAsset;
	}
#endif

	return NULL;
}

// NVCHANGE_END: JCAO - Apex Emitter Asset work with LODs