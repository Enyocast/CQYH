/*=============================================================================
USetMaterialUsageCommandlet.cpp - Commandlet which finds what types of geometry a material is used on.
Copyright 1998-2013 Epic Games, Inc. All Rights Reserved.
=============================================================================*/

#include "UnrealEd.h"
#include "EngineMaterialClasses.h"
#include "EngineParticleClasses.h"
#include "EngineSequenceClasses.h"
#include "EngineAnimClasses.h"
#include "UnTerrain.h"
#include "EngineFoliageClasses.h"
#include "SpeedTree.h"
#include "EngineDecalClasses.h"
#include "UnFracturedStaticMesh.h"
#include "EngineMeshClasses.h"

#include "SourceControl.h"

struct FPackageMaterialInfo
{
	TArray<FString> SkeletalMeshMaterials;
	TArray<FString> FracturedMeshMaterials;
	TArray<FString> ParticleSpriteMaterials;
	TArray<FString> BeamTrailMaterials;
	TArray<FString> ParticleSubUVMaterials;
	TArray<FString> DecalMaterials;
	TArray<FString> StaticLightingMaterials;
	TArray<FString> FluidSurfacesMaterials;
	TArray<FString> MaterialEffectMaterials;
	TArray<FString> InstancedMeshMaterials;
	TArray<FString> SplineMeshMaterials;
	TArray<FString> ScreenDoorFadeMaterials;
	TArray<FString> ApexMeshMaterials;
	TArray<FString> ApexSpritesMaterials;
	// ming@snda
	TArray<FString>	DistortionMaterials;
};

static void SetMaterialUsage(
	TMap<FName,FPackageMaterialInfo>& PackageInfoMap,
	UMaterialInterface* MaterialInterface,
	UBOOL bUsedWithSkeletalMesh,
	UBOOL bUsedWithFracturedStaticMeshes,
	UBOOL bUsedWithParticleSprites,
	UBOOL bUsedWithBeamTrails,
	UBOOL bUsedWithParticleSubUV,
	UBOOL bUsedWithDecals,
	UBOOL bUsedWithStaticLighting,
	UBOOL bUsedWithFluidSurfaces,
	UBOOL bUsedWithMaterialEffect,
	UBOOL bUsedWithInstancedMeshes,
	UBOOL bUsedWithSplineMeshes,
	UBOOL bUsedWithScreenDoorFade,
	UBOOL bUsedWithApexMesh = FALSE,
	UBOOL bUsedWithApexSprites = FALSE
	// ming@snda
	, UBOOL bUsedAsDistortion = FALSE
	)
{
	UMaterial* Material = MaterialInterface ? MaterialInterface->GetMaterial() : NULL;
	if(Material)
	{
		FPackageMaterialInfo* PackageInfo = PackageInfoMap.Find(Material->GetOutermost()->GetFName());
		if(!PackageInfo)
		{
			PackageInfo = &PackageInfoMap.Set(Material->GetOutermost()->GetFName(),FPackageMaterialInfo());
		}
		if(bUsedWithSkeletalMesh && !Material->bUsedWithSkeletalMesh)
		{
			PackageInfo->SkeletalMeshMaterials.AddUniqueItem(Material->GetPathName());
		}
		if(bUsedWithFracturedStaticMeshes && !Material->bUsedWithFracturedMeshes)
		{
			PackageInfo->FracturedMeshMaterials.AddUniqueItem(Material->GetPathName());
		}
		if(bUsedWithParticleSprites)
		{
			PackageInfo->ParticleSpriteMaterials.AddUniqueItem(Material->GetPathName());
		}
		if(bUsedWithBeamTrails)
		{
			PackageInfo->BeamTrailMaterials.AddUniqueItem(Material->GetPathName());
		}
		if(bUsedWithParticleSubUV)
		{
			PackageInfo->ParticleSubUVMaterials.AddUniqueItem(Material->GetPathName());
		}
		if(bUsedWithDecals)
		{
			PackageInfo->DecalMaterials.AddUniqueItem(Material->GetPathName());
		}
		if(bUsedWithStaticLighting && !Material->bUsedWithStaticLighting)
		{
			PackageInfo->StaticLightingMaterials.AddUniqueItem(Material->GetPathName());
		}
		if(bUsedWithFluidSurfaces && !Material->bUsedWithFluidSurfaces)
		{
			PackageInfo->FluidSurfacesMaterials.AddUniqueItem(Material->GetPathName());
		}
		if(bUsedWithMaterialEffect && !Material->bUsedWithMaterialEffect)
		{
			PackageInfo->MaterialEffectMaterials.AddUniqueItem(Material->GetPathName());
		}
		if(bUsedWithInstancedMeshes && !Material->bUsedWithInstancedMeshes)
		{
			PackageInfo->InstancedMeshMaterials.AddUniqueItem(Material->GetPathName());
		}
		if(bUsedWithSplineMeshes && !Material->bUsedWithSplineMeshes)
		{
			PackageInfo->SplineMeshMaterials.AddUniqueItem(Material->GetPathName());
		}		
		if(bUsedWithScreenDoorFade && !Material->bUsedWithScreenDoorFade)
		{
			PackageInfo->ScreenDoorFadeMaterials.AddUniqueItem(Material->GetPathName());
		}
		if(bUsedWithApexMesh && !Material->bUsedWithAPEXMeshes)
		{
			PackageInfo->ApexMeshMaterials.AddUniqueItem(Material->GetPathName());
		}
		if(bUsedWithApexSprites && !Material->bUsedWithApexSprites)
		{
			PackageInfo->ApexSpritesMaterials.AddUniqueItem(Material->GetPathName());
		}
		// [ming@snda
		if( bUsedAsDistortion && !Material->bUseOneLayerDistortion )
		{
			PackageInfo->DistortionMaterials.AddUniqueItem(Material->GetPathName());
		}
	}
}

INT USetMaterialUsageCommandlet::Main( const FString& Params )
{
	const TCHAR* Parms = *Params;

	// oscar@snda
	extern bool g_forceKeepAllMaterialQualityLevelsLoaded;
	g_forceKeepAllMaterialQualityLevelsLoaded = true;
	// oscar@snda

	// Retrieve list of all packages in .ini paths.
	TArray<FString> PackageList;
	//PackageList = GPackageFileCache->GetPackageFileList();

	// figure out what packages to iterate over
	FString SinglePackage;
	bool useSpecifiedPackage = false; // oscar@snda
	if (Parse(*Params, TEXT("PACKAGE="), SinglePackage))
	{
		useSpecifiedPackage = true;
		FString PackagePath;
		if (!GPackageFileCache->FindPackageFile(*SinglePackage, NULL, PackagePath))
		{
			SET_WARN_COLOR(COLOR_RED);
			warnf(NAME_Error, TEXT("Failed to find file %s"), *SinglePackage);
			CLEAR_WARN_COLOR();
			return 1;
		}
		else
		{
			PackageList.AddItem(PackagePath);
		}
	}
	else
	{
		PackageList = GPackageFileCache->GetPackageFileList();

		// oscar@snda
		TArray<FString> cfgPkgs;
		TArray<FString> cfgDirs;		
		GConfig->GetArray(TEXT("Cook.DataPath"), TEXT("Path"), cfgDirs, GEditorIni);
		for(INT k = 0; k < cfgDirs.Num(); ++k)
		{
			TArray<FString> pkgs;
			appFindFilesInDirectory(pkgs, *cfgDirs(k), TRUE, FALSE);

			warnf(NAME_Log, TEXT("==== Adding found %d upks"), pkgs.Num());

			cfgPkgs += pkgs;
		}

		if(ParseParam(Parms, TEXT("onlycfgpkgs")))
		{
			PackageList = cfgPkgs;
		}
		else
		{
			for (INT m = 0; m < cfgPkgs.Num(); ++m)
			{
				PackageList.AddUniqueItem(cfgPkgs(m));
			}
		}
	}
	// oscar@snda


	if( !PackageList.Num() )
	{
		warnf( TEXT( "Found no packages to fun SetMaterialUsageCommandlet on!" ) );
		return 0;
	}
	// oscar@snda
	else
	{
		SET_WARN_COLOR(COLOR_PURPLE);
		warnf(TEXT("==== Total Packages: %d ===="), PackageList.Num());
#if 0
		for (INT i = 0; i < PackageList.Num(); ++i)
		{
			warnf(TEXT("====%s"), *PackageList(i));
		}
#endif
		CLEAR_WARN_COLOR();
	}

	const UBOOL skipMapFile = ParseParam(appCmdLine(),TEXT("skipmap"));
	// oscar@snda

	const UBOOL bAutoCheckOut = ParseParam(appCmdLine(),TEXT("AutoCheckOutPackages"));
#if HAVE_SCC
	// Ensure source control is initialized and shut down properly
	FScopedSourceControl SourceControl;
#endif

	// oscar@snda GEngine->Exec( TEXT("DumpShaderStats") );

	// Iterate over all packages.
	TMap<FName,FPackageMaterialInfo> PackageInfoMap;
	for( INT PackageIndex = 0; PackageIndex < PackageList.Num(); PackageIndex++ )
	{
		FFilename Filename = PackageList(PackageIndex);

		if(skipMapFile && INDEX_NONE != Filename.InStr(TEXT(".udk")))
		{
			continue;
		}
#if HAVE_SCC
		if ( bAutoCheckOut && FSourceControl::ForceGetStatus( Filename ) == SCC_NotCurrent )
		{
			warnf(NAME_Log, TEXT("Skipping %s (Not at head source control revision)"), *Filename);
			continue;
		}
#endif

		// oscar@snda
		SET_WARN_COLOR(COLOR_GREEN);
		warnf(TEXT("Loading[%d/%d] %s"), PackageIndex + 1, PackageList.Num(), *Filename);
		CLEAR_WARN_COLOR();

		if(0 == GFileManager->FileSize(*Filename))
		{
			continue;
		}
		// oscar@snda

		UPackage* Package = UObject::LoadPackage( NULL, *Filename, 0 );
		if (Package != NULL)
		{
			// Iterate over all objects in the package.
			for(FObjectIterator ObjectIt;ObjectIt;++ObjectIt)
			{
				if(ObjectIt->IsIn(Package))
				{
					USkeletalMeshComponent* SkeletalMeshComponent = Cast<USkeletalMeshComponent>(*ObjectIt);
					USkeletalMesh* SkeletalMesh = Cast<USkeletalMesh>(*ObjectIt);
					UFracturedStaticMeshComponent* FracturedComponent = Cast<UFracturedStaticMeshComponent>(*ObjectIt);
					UFracturedStaticMesh* FracturedMesh = Cast<UFracturedStaticMesh>(*ObjectIt);
					UParticleSpriteEmitter* SpriteEmitter = Cast<UParticleSpriteEmitter>(*ObjectIt);
					UModelComponent* ModelComponent = Cast<UModelComponent>(*ObjectIt);
					UStaticMeshComponent* StaticMeshComponent = Cast<UStaticMeshComponent>(*ObjectIt);
					UTerrainMaterial* TerrainMaterial = Cast<UTerrainMaterial>(*ObjectIt);
					UDecalMaterial* DecalMaterial = Cast<UDecalMaterial>(*ObjectIt);
					USpeedTreeComponent* SpeedTreeComponent = Cast<USpeedTreeComponent>(*ObjectIt);
					UDecalComponent* DecalComponent = Cast<UDecalComponent>(*ObjectIt);
					UMaterialEffect* MaterialEffect = Cast<UMaterialEffect>(*ObjectIt);
					UInstancedStaticMeshComponent* InstancedStaticMeshComponent = Cast<UInstancedStaticMeshComponent>(*ObjectIt);
					USplineMeshComponent* SplineMeshComponent = Cast<USplineMeshComponent>(*ObjectIt);

					// oscar@snda
					UStaticMesh* staticMeshRes = Cast<UStaticMesh>(*ObjectIt);
					USkeletalMesh* skelMeshRes = Cast<USkeletalMesh>(*ObjectIt);
					UParticleSystem* parRes = Cast<UParticleSystem>(*ObjectIt);
					UPostProcessChain* postProcess = Cast<UPostProcessChain>(*ObjectIt);

					UApexAsset* apexAsset = Cast<UApexAsset>(*ObjectIt);

					UMaterial* matRes = Cast<UMaterial>(*ObjectIt);

					if(matRes)
					{
						FString matName = matRes->GetFullName();
						if(matName.InStr(TEXT("_FadeInOut")) != INDEX_NONE)
						{
							SET_WARN_COLOR(COLOR_PURPLE);
							warnf(NAME_Log, TEXT("Setup FadeInOut material:%s"), *matName);
							CLEAR_WARN_COLOR();

							if(matName.InStr(TEXT("foliage")) != INDEX_NONE)
							{
								SetMaterialUsage(PackageInfoMap,matRes,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,TRUE,FALSE,FALSE,FALSE,FALSE,FALSE);
							}
							else
							{
								SetMaterialUsage(PackageInfoMap,matRes,TRUE,FALSE,FALSE,FALSE,FALSE,FALSE,TRUE,FALSE,FALSE,FALSE,FALSE,FALSE);
							}
						}

						// automatically set one layer distortion if the material is to be distorted
						if( matRes->HasDistortion() )
						{
							//SetMaterialUsage(PackageInfoMap,matRes,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,TRUE);
						}
					}

					if(apexAsset)
					{
						for (UINT i = 0; i < apexAsset->GetNumMaterials(); ++i)
						{
							UMaterialInterface* mat = apexAsset->GetMaterial(i);
							SetMaterialUsage(PackageInfoMap,mat,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,TRUE,FALSE);
						}
					}

					if(postProcess)
					{
						for (INT i = 0; i < postProcess->Effects.Num(); ++i)
						{
							UPostProcessEffect* eff = postProcess->Effects(i);
							if(eff && eff->IsA(UMaterialEffect::StaticClass()))
							{
								UMaterialEffect* matEff = Cast<UMaterialEffect>(eff);
								SetMaterialUsage(PackageInfoMap,matEff->Material,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,TRUE,FALSE,FALSE,FALSE);
							}
						}
					}

					if(staticMeshRes)
					{
						for (INT i = 0; i < staticMeshRes->LODInfo.Num(); ++i)
						{
							for (INT j = 0; j < staticMeshRes->LODInfo(i).Elements.Num(); ++j)
							{
								const FStaticMeshLODElement& lodElm = staticMeshRes->LODInfo(i).Elements(j);
								if(lodElm.Material)
								{
									SetMaterialUsage(PackageInfoMap,lodElm.Material,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,TRUE,FALSE,FALSE,FALSE,FALSE,FALSE);
								}
							}
						}
					}

					if(skelMeshRes)
					{
						for(INT MaterialIndex = 0;MaterialIndex < skelMeshRes->Materials.Num();MaterialIndex++)
						{
							UMaterialInterface* Material = skelMeshRes->Materials(MaterialIndex);
							SetMaterialUsage(PackageInfoMap,Material,TRUE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE);
						}
					}

					if(parRes)
					{
						UBOOL bSpriteEmitter = FALSE;
						UBOOL bBeamTrailEmitter = FALSE;
						UBOOL bSubUVEmitter = FALSE;
						UBOOL bStaticLighting = FALSE;
						UBOOL bApexMesh = FALSE;
						UBOOL bApexSprite = FALSE;

						for (INT i = 0; i < parRes->Emitters.Num(); ++i)
						{
							for (INT LODIndex = 0; LODIndex < parRes->Emitters(i)->LODLevels.Num(); LODIndex++)
							{
								UParticleLODLevel* LODLevel = parRes->Emitters(i)->LODLevels(LODIndex);
								if (LODLevel && LODLevel->RequiredModule && LODLevel->RequiredModule->Material)
								{
									// oscar@snda
									if (LODLevel->TypeDataModule
										&& (LODLevel->TypeDataModule->IsA(UParticleModuleTypeDataBeam2::StaticClass())
										|| LODLevel->TypeDataModule->IsA(UParticleModuleTypeDataTrail2::StaticClass())
										|| LODLevel->TypeDataModule->IsA(UParticleModuleTypeDataRibbon::StaticClass())
										|| LODLevel->TypeDataModule->IsA(UParticleModuleTypeDataAnimTrail::StaticClass())))
									{
										//if the LOD has a data type module and it is a beam or trail module, then material is used with beams or trails
										//don't set anything for mesh emitters, the material is used by the mesh and not the emitter
										bBeamTrailEmitter = TRUE;
									}
									else if(LODLevel->TypeDataModule
										&& LODLevel->TypeDataModule->IsA(UParticleModuleTypeDataMesh::StaticClass()))
									{
										bStaticLighting = TRUE;
									}
									else if(LODLevel->TypeDataModule
										&& LODLevel->TypeDataModule->IsA(UParticleModuleTypeDataApexSprite::StaticClass()))
									{
										bStaticLighting = TRUE;
										bApexMesh = TRUE;
										bApexSprite = TRUE;
									}
									else if(LODLevel->TypeDataModule
										&& LODLevel->TypeDataModule->IsA(UParticleModuleTypeDataApex::StaticClass()))
									{
										bStaticLighting = TRUE;
										bApexMesh = TRUE;
									}
									else if (LODLevel->RequiredModule->InterpolationMethod != PSUVIM_None)
									{
										//LODLevel->RequiredModule->InterpolationMethod being anything other than PSUVIM_None indicates that the material is used with the Sub UV vertex factory
										bSubUVEmitter = TRUE;
									}
									else 
									{
										//otherwise it must be a sprite emitter
										bSpriteEmitter = TRUE;
									}

									// oscar@snda

									SetMaterialUsage(PackageInfoMap,LODLevel->RequiredModule->Material,FALSE,FALSE,bSpriteEmitter,bBeamTrailEmitter,bSubUVEmitter,FALSE,bStaticLighting,FALSE,FALSE,FALSE,FALSE,FALSE,bApexMesh, bApexSprite);
								}
							}
						}
					}
					// oscar@snda

					if(SkeletalMeshComponent)
					{
						// Mark all the materials referenced by the skeletal mesh component as being used with a skeletal mesh.
						for(INT MaterialIndex = 0;MaterialIndex < SkeletalMeshComponent->Materials.Num();MaterialIndex++)
						{
							UMaterialInterface* Material = SkeletalMeshComponent->Materials(MaterialIndex);
							SetMaterialUsage(PackageInfoMap,Material,TRUE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE);
						}
					}
					else if(SkeletalMesh)
					{
						// Mark all the materials referenced by the skeletal mesh as being used with a skeletal mesh.
						for(INT MaterialIndex = 0;MaterialIndex < SkeletalMesh->Materials.Num();MaterialIndex++)
						{
							UMaterialInterface* Material = SkeletalMesh->Materials(MaterialIndex);
							SetMaterialUsage(PackageInfoMap,Material,TRUE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE);
						}
					}
					else if (FracturedComponent)
					{
						// Mark all the materials referenced by the fractured mesh component as being used with a fractured mesh.
						for(INT MaterialIndex = 0;MaterialIndex < FracturedComponent->Materials.Num();MaterialIndex++)
						{
							UMaterialInterface* Material = FracturedComponent->Materials(MaterialIndex);
							SetMaterialUsage(PackageInfoMap,Material,FALSE,TRUE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE);
						}
					}
					else if(FracturedMesh)
					{
						for(INT LODIndex = 0; LODIndex < FracturedMesh->LODInfo.Num(); LODIndex++)
						{
							for(INT ElementIndex = 0; ElementIndex < FracturedMesh->LODInfo(LODIndex).Elements.Num(); ElementIndex++)
							{
								UMaterialInterface* Material = FracturedMesh->LODInfo(LODIndex).Elements(ElementIndex).Material;
								SetMaterialUsage(PackageInfoMap,Material,FALSE,TRUE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE);
							}
						}
					}
					else if(SpriteEmitter)
					{
						UBOOL bSpriteEmitter = FALSE;
						UBOOL bBeamTrailEmitter = FALSE;
						UBOOL bSubUVEmitter = FALSE;
						UBOOL bStaticLighting = FALSE; // oscar@snda
						UBOOL bApexMesh = FALSE;
						UBOOL bApexSprite = FALSE;

						//check each LOD
						for (INT LODIndex = 0; LODIndex < SpriteEmitter->LODLevels.Num(); LODIndex++)
						{
							UParticleLODLevel* LODLevel = SpriteEmitter->LODLevels(LODIndex);
							if (LODLevel && LODLevel->RequiredModule && LODLevel->RequiredModule->Material)
							{
								// oscar@snda
								if (LODLevel->TypeDataModule
									&& (LODLevel->TypeDataModule->IsA(UParticleModuleTypeDataBeam2::StaticClass())
									|| LODLevel->TypeDataModule->IsA(UParticleModuleTypeDataTrail2::StaticClass())
									|| LODLevel->TypeDataModule->IsA(UParticleModuleTypeDataRibbon::StaticClass())
									|| LODLevel->TypeDataModule->IsA(UParticleModuleTypeDataAnimTrail::StaticClass())))
								{
									//if the LOD has a data type module and it is a beam or trail module, then material is used with beams or trails
									//don't set anything for mesh emitters, the material is used by the mesh and not the emitter
									bBeamTrailEmitter = TRUE;
								}
								else if(LODLevel->TypeDataModule
									&& (LODLevel->TypeDataModule->IsA(UParticleModuleTypeDataMesh::StaticClass())
									))
								{
									bStaticLighting = TRUE;
								}
								else if(LODLevel->TypeDataModule
									&& LODLevel->TypeDataModule->IsA(UParticleModuleTypeDataApexSprite::StaticClass()))
								{
									bStaticLighting = TRUE;
									bApexMesh = TRUE;
									bApexSprite = TRUE;
								}
								else if(LODLevel->TypeDataModule
									&& LODLevel->TypeDataModule->IsA(UParticleModuleTypeDataApex::StaticClass()))
								{
									bStaticLighting = TRUE;
									bApexMesh = TRUE;
								}
								else if (LODLevel->RequiredModule->InterpolationMethod != PSUVIM_None)
								{
									//LODLevel->RequiredModule->InterpolationMethod being anything other than PSUVIM_None indicates that the material is used with the Sub UV vertex factory
									bSubUVEmitter = TRUE;
								}
								else 
								{
									//otherwise it must be a sprite emitter
									bSpriteEmitter = TRUE;
								}

								// oscar@snda

								SetMaterialUsage(PackageInfoMap,LODLevel->RequiredModule->Material,FALSE,FALSE,bSpriteEmitter,bBeamTrailEmitter,bSubUVEmitter,FALSE,bStaticLighting,FALSE,FALSE,FALSE,FALSE,FALSE,bApexMesh,bApexMesh);
							}
						}
						//don't handle SpriteEmitter->Material, since it is deprecated
					}
					else if(ModelComponent)
					{
						// Check each of the model's elements for static lighting, and if present mark the element's material as being used with static lighting.
						for(INT ElementIndex = 0;ElementIndex < ModelComponent->GetElements().Num();ElementIndex++)
						{
							const FModelElement& Element = ModelComponent->GetElements()(ElementIndex);
							const UBOOL bHasStaticLighting = Element.LightMap != NULL || Element.ShadowMaps.Num();
							if(bHasStaticLighting)
							{
								SetMaterialUsage(PackageInfoMap,Element.Material,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,TRUE,FALSE,FALSE,FALSE,FALSE,FALSE);
							}
						}
					}
					else if(StaticMeshComponent && StaticMeshComponent->IsValidComponent())
					{
						if(StaticMeshComponent->HasStaticShadowing())
						{
							// Mark the element's material as being used with static lighting.
							for(INT ElementIndex = 0;ElementIndex < StaticMeshComponent->GetNumElements();ElementIndex++)
							{
								UMaterialInterface* Material = StaticMeshComponent->GetMaterial(ElementIndex);
								SetMaterialUsage(PackageInfoMap,Material,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,TRUE,FALSE,FALSE,FALSE,FALSE,FALSE);
							}
						}
					}
					else if(TerrainMaterial)
					{
						// handle decal material usage with terrain materials
						DecalMaterial = Cast<UDecalMaterial>(TerrainMaterial->Material);
					}
					else if(SpeedTreeComponent && SpeedTreeComponent->IsValidComponent())
					{
						if(SpeedTreeComponent->HasStaticShadowing())
						{
							// Mark the SpeedTreeComponent's materials as being used with static lighting.
							for (BYTE MeshTypeIdx = STMT_MinMinusOne + 1; MeshTypeIdx < STMT_Max; MeshTypeIdx++)
							{
								SetMaterialUsage(PackageInfoMap,SpeedTreeComponent->GetMaterial(MeshTypeIdx),FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,TRUE,FALSE,FALSE,FALSE,FALSE,FALSE);
							}
						}
					}
					else if( DecalComponent )
					{
						// Make sure that all materials used with decals have decal usage 
						SetMaterialUsage(PackageInfoMap,DecalComponent->GetDecalMaterial(),FALSE,FALSE,FALSE,FALSE,FALSE,TRUE,TRUE,FALSE,FALSE,FALSE,FALSE,FALSE);
					}
					else if(MaterialEffect)
					{
						SetMaterialUsage(PackageInfoMap,MaterialEffect->Material,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,TRUE,FALSE,FALSE,FALSE);
					}
					else if(InstancedStaticMeshComponent)
					{
						// Mark the element's material as being used with static lighting.
						for(INT ElementIndex = 0;ElementIndex < InstancedStaticMeshComponent->GetNumElements();ElementIndex++)
						{
							UMaterialInterface* Material = InstancedStaticMeshComponent->GetMaterial(ElementIndex);
							SetMaterialUsage(PackageInfoMap,Material,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,TRUE,FALSE,FALSE,TRUE,FALSE,FALSE);
						}
					}
					else if(SplineMeshComponent)
					{
						// Mark the element's material as being used with spline mesh.
						for(INT ElementIndex = 0;ElementIndex < SplineMeshComponent->GetNumElements(); ElementIndex++)
						{
							UMaterialInterface* Material = SplineMeshComponent->GetMaterial(ElementIndex);
							SetMaterialUsage(PackageInfoMap,Material,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,TRUE,FALSE,FALSE,FALSE,TRUE,FALSE);
						}
					}
					else if(!appStricmp(*ObjectIt->GetClass()->GetName(),TEXT("SeqAct_SetMaterial")))
					{
						// Extract the value of the script NewMaterial property.
						UProperty* MaterialProperty = CastChecked<UProperty>(ObjectIt->FindObjectField(FName(TEXT("NewMaterial"))));
						UMaterialInterface* Material = *(UMaterialInterface**)((BYTE*)*ObjectIt + MaterialProperty->Offset);
						USequenceAction* SequenceAction = CastChecked<USequenceAction>(*ObjectIt);
						// If the SetMaterial targets include a skeletal mesh, mark the material as being used with a skeletal mesh.
						for(INT TargetIndex = 0;TargetIndex < SequenceAction->Targets.Num();TargetIndex++)
						{
							ASkeletalMeshActor* SkeletalMeshActor = Cast<ASkeletalMeshActor>(SequenceAction->Targets(TargetIndex));
							if(SkeletalMeshActor)
							{
								SetMaterialUsage(PackageInfoMap,Material,TRUE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE);
								break;
							}
						}
					}

					if( DecalMaterial )
					{
						// Make sure that all materials used with decals have decal usage 
						SetMaterialUsage(PackageInfoMap,DecalMaterial,TRUE,TRUE,FALSE,FALSE,FALSE,TRUE,TRUE,TRUE,FALSE,FALSE,FALSE,FALSE);
					}


					// here we give the specific game a chance to set flags based on info it maybe has (e.g. gears has physical materials that have semi complicated organization OF data and we want to find materials in there that are decals)
					{
						TArray<UMaterialInterface*> DecalMaterials = GEditor->GetDecalMaterialsFromGame( *ObjectIt );

						// now set the DecalMaterial settings
						for( INT Idx = 0; Idx < DecalMaterials.Num(); ++Idx )
						{
							UMaterialInterface* DecalMaterial = DecalMaterials(Idx);
							SetMaterialUsage(PackageInfoMap,DecalMaterial,TRUE,TRUE,FALSE,FALSE,FALSE,TRUE,TRUE,TRUE,FALSE,FALSE,FALSE,FALSE);
						}
					}
				}
			}
		}

		UObject::CollectGarbage(RF_Native);
		// oscar@snda SaveLocalShaderCaches();
	}

	UINT NumStaticLightingMaterials = 0;
	UINT NumDecalMaterials = 0;
	UINT NumTotalMaterials = 0;

	// oscar@snda
	INT MaxPkgCnt = PackageInfoMap.Num();
	INT CurProcIdx = 1;
	// oscar@snda

	for(TMap<FName,FPackageMaterialInfo>::TConstIterator PackageIt(PackageInfoMap);PackageIt;++PackageIt)
	{
		const FPackageMaterialInfo& PackageInfo = PackageIt.Value();

		// Only save dirty packages.
		if(PackageInfo.SkeletalMeshMaterials.Num() 
			|| PackageInfo.FracturedMeshMaterials.Num() 
			|| PackageInfo.ParticleSpriteMaterials.Num() 
			|| PackageInfo.BeamTrailMaterials.Num() 
			|| PackageInfo.ParticleSubUVMaterials.Num() 
			|| PackageInfo.StaticLightingMaterials.Num()
			|| PackageInfo.DecalMaterials.Num()
			|| PackageInfo.FluidSurfacesMaterials.Num()
			|| PackageInfo.MaterialEffectMaterials.Num()
			|| PackageInfo.InstancedMeshMaterials.Num()
			|| PackageInfo.SplineMeshMaterials.Num()
			|| PackageInfo.ScreenDoorFadeMaterials.Num()
			|| PackageInfo.ApexMeshMaterials.Num()
			|| PackageInfo.ApexSpritesMaterials.Num()
			// ming@snda
			|| PackageInfo.DistortionMaterials.Num()
			)
		{
			// oscar@snda
			SET_WARN_COLOR(COLOR_GREEN);
			warnf(
				// ming@snda
				TEXT("Package[%d/%d] %s is dirty(SK %u, FM %u, PS %u, Be %u, SUV %u, SM %u, Dec %u, Flu %u, MEf %u, InstM %u, Spl %u, Door %u, ApxM %u, ApxP %u, Distor %u)"),
				CurProcIdx, MaxPkgCnt,
				*PackageIt.Key().ToString(),
				PackageInfo.SkeletalMeshMaterials.Num(),
				PackageInfo.FracturedMeshMaterials.Num(),
				PackageInfo.ParticleSpriteMaterials.Num(),
				PackageInfo.BeamTrailMaterials.Num(),
				PackageInfo.ParticleSubUVMaterials.Num(),
				PackageInfo.StaticLightingMaterials.Num(),
				PackageInfo.DecalMaterials.Num(),
				PackageInfo.FluidSurfacesMaterials.Num(),
				PackageInfo.MaterialEffectMaterials.Num(),
				PackageInfo.InstancedMeshMaterials.Num(),
				PackageInfo.SplineMeshMaterials.Num(),
				PackageInfo.ScreenDoorFadeMaterials.Num(),
				PackageInfo.ApexMeshMaterials.Num(),
				PackageInfo.ApexSpritesMaterials.Num()
				// ming@snda
				, PackageInfo.DistortionMaterials.Num()
				);

			CLEAR_WARN_COLOR();
			// oscar@snda

			FString Filename;
			if(GPackageFileCache->FindPackageFile(*PackageIt.Key().ToString(),NULL,Filename))
			{
				// oscar@snda
				if(0 == GFileManager->FileSize(*Filename))
				{
					continue;
				}
				// oscar@snda

				UPackage* Package = UObject::LoadPackage( NULL, *Filename, 0 );
				if(Package)
				{
					UObject::ResetLoaders(Package);

					// Count the materials in the package.
					for(TObjectIterator<UMaterial> MaterialIt;MaterialIt;++MaterialIt)
					{
						if (MaterialIt->IsIn(Package))
						{
							NumTotalMaterials++;

							UMaterial* CurrentMaterial = *MaterialIt;
							FString CurrentMaterialName = CurrentMaterial->GetPathName();
							if (CurrentMaterialName != TEXT("EngineMaterials.DefaultParticle"))
							{
								UBOOL bResetUsageFlags = FALSE;

								if (CurrentMaterial->bUsedWithParticleSprites
									&& !PackageInfo.ParticleSpriteMaterials.ContainsItem(CurrentMaterialName))
								{
									bResetUsageFlags = TRUE;
								}
								else if (CurrentMaterial->bUsedWithBeamTrails
									&& !PackageInfo.BeamTrailMaterials.ContainsItem(CurrentMaterialName))
								{
									bResetUsageFlags = TRUE;
								}
								else if (CurrentMaterial->bUsedWithParticleSubUV
									&& !PackageInfo.ParticleSubUVMaterials.ContainsItem(CurrentMaterialName))
								{
									bResetUsageFlags = TRUE;
								}

#if 0 // oscar@snda
								if (bResetUsageFlags)
								{
									//set particle usage flags on existing materials to FALSE
									CurrentMaterial->bUsedWithParticleSprites = FALSE;
									CurrentMaterial->bUsedWithBeamTrails = FALSE;
									CurrentMaterial->bUsedWithParticleSubUV = FALSE;
									CurrentMaterial->MarkPackageDirty();
								}

								// Reset incorrectly set bUsedWithMaterialEffect
								if (CurrentMaterial->bUsedWithMaterialEffect
									&& !PackageInfo.MaterialEffectMaterials.ContainsItem(CurrentMaterialName))
								{
									CurrentMaterial->bUsedWithMaterialEffect = FALSE;
									CurrentMaterial->MarkPackageDirty();
								}
#endif // oscar@snda
							}
							else
							{
								warnf(TEXT("Skipped clearing flags on EngineMaterials.DefaultParticle"));
							}
						}
					}

					for(INT MaterialIndex = 0;MaterialIndex < PackageInfo.SkeletalMeshMaterials.Num();MaterialIndex++)
					{
						UMaterial* Material = FindObjectChecked<UMaterial>(NULL,*PackageInfo.SkeletalMeshMaterials(MaterialIndex));
						Material->CheckMaterialUsage(MATUSAGE_SkeletalMesh);
					}

					for(INT MaterialIndex = 0;MaterialIndex < PackageInfo.FracturedMeshMaterials.Num();MaterialIndex++)
					{
						UMaterial* Material = FindObjectChecked<UMaterial>(NULL,*PackageInfo.FracturedMeshMaterials(MaterialIndex));
						Material->CheckMaterialUsage(MATUSAGE_FracturedMeshes);
					}

					for(INT MaterialIndex = 0;MaterialIndex < PackageInfo.ParticleSpriteMaterials.Num();MaterialIndex++)
					{
						UMaterial* Material = FindObjectChecked<UMaterial>(NULL,*PackageInfo.ParticleSpriteMaterials(MaterialIndex));
						Material->CheckMaterialUsage(MATUSAGE_ParticleSprites);
					}

					for(INT MaterialIndex = 0;MaterialIndex < PackageInfo.BeamTrailMaterials.Num();MaterialIndex++)
					{
						UMaterial* Material = FindObjectChecked<UMaterial>(NULL,*PackageInfo.BeamTrailMaterials(MaterialIndex));
						Material->CheckMaterialUsage(MATUSAGE_BeamTrails);
					}

					for(INT MaterialIndex = 0;MaterialIndex < PackageInfo.ParticleSubUVMaterials.Num();MaterialIndex++)
					{
						UMaterial* Material = FindObjectChecked<UMaterial>(NULL,*PackageInfo.ParticleSubUVMaterials(MaterialIndex));
						Material->CheckMaterialUsage(MATUSAGE_ParticleSubUV);
					}

					for(INT MaterialIndex = 0;MaterialIndex < PackageInfo.StaticLightingMaterials.Num();MaterialIndex++)
					{
						UMaterial* Material = FindObjectChecked<UMaterial>(NULL,*PackageInfo.StaticLightingMaterials(MaterialIndex));
						Material->CheckMaterialUsage(MATUSAGE_StaticLighting);
						NumStaticLightingMaterials++;
					}
					for(INT MaterialIndex = 0;MaterialIndex < PackageInfo.DecalMaterials.Num();MaterialIndex++)
					{
						UMaterial* Material = FindObjectChecked<UMaterial>(NULL,*PackageInfo.DecalMaterials(MaterialIndex));
						Material->CheckMaterialUsage(MATUSAGE_Decals);
						NumDecalMaterials++;
					}
					for(INT MaterialIndex = 0;MaterialIndex < PackageInfo.FluidSurfacesMaterials.Num();MaterialIndex++)
					{
						UMaterial* Material = FindObjectChecked<UMaterial>(NULL,*PackageInfo.FluidSurfacesMaterials(MaterialIndex));
						Material->CheckMaterialUsage(MATUSAGE_FluidSurface);
					}
					for(INT MaterialIndex = 0;MaterialIndex < PackageInfo.MaterialEffectMaterials.Num();MaterialIndex++)
					{
						UMaterial* Material = FindObjectChecked<UMaterial>(NULL,*PackageInfo.MaterialEffectMaterials(MaterialIndex));
						Material->CheckMaterialUsage(MATUSAGE_MaterialEffect);
					}
					for(INT MaterialIndex = 0;MaterialIndex < PackageInfo.InstancedMeshMaterials.Num();MaterialIndex++)
					{
						UMaterial* Material = FindObjectChecked<UMaterial>(NULL,*PackageInfo.InstancedMeshMaterials(MaterialIndex));
						Material->CheckMaterialUsage(MATUSAGE_InstancedMeshes);
					}
					for(INT MaterialIndex = 0;MaterialIndex < PackageInfo.SplineMeshMaterials.Num();MaterialIndex++)
					{
						UMaterial* Material = FindObjectChecked<UMaterial>(NULL,*PackageInfo.SplineMeshMaterials(MaterialIndex));
						Material->CheckMaterialUsage(MATUSAGE_SplineMesh);
					}
					for(INT MaterialIndex = 0;MaterialIndex < PackageInfo.ScreenDoorFadeMaterials.Num();MaterialIndex++)
					{
						UMaterial* Material = FindObjectChecked<UMaterial>(NULL,*PackageInfo.ScreenDoorFadeMaterials(MaterialIndex));
						Material->CheckMaterialUsage(MATUSAGE_ScreenDoorFade);
					}

					for(INT MaterialIndex = 0;MaterialIndex < PackageInfo.ApexMeshMaterials.Num();MaterialIndex++)
					{
						UMaterial* Material = FindObjectChecked<UMaterial>(NULL,*PackageInfo.ApexMeshMaterials(MaterialIndex));
						Material->CheckMaterialUsage(MATUSAGE_APEXMesh);
					}
					for(INT MaterialIndex = 0;MaterialIndex < PackageInfo.ApexSpritesMaterials.Num();MaterialIndex++)
					{
						UMaterial* Material = FindObjectChecked<UMaterial>(NULL,*PackageInfo.ApexSpritesMaterials(MaterialIndex));
						Material->CheckMaterialUsage(MATUSAGE_VTF);
					}
					// [ming@snda
					for(INT MaterialIndex = 0;MaterialIndex < PackageInfo.DistortionMaterials.Num();MaterialIndex++)
					{
						UMaterial* Material = FindObjectChecked<UMaterial>(NULL,*PackageInfo.DistortionMaterials(MaterialIndex));
						Material->SetUseOneLayerDistortion();
					}
					// ming@snda]

					if(Package->IsDirty())
					{
#if HAVE_SCC
						if( (GFileManager->IsReadOnly(*Filename)) && ( bAutoCheckOut == TRUE ) )
						{
							FSourceControl::CheckOut(Package);
						}
#endif
						if (!GFileManager->IsReadOnly(*Filename))
						{
							// resave the package
							UWorld* World = FindObject<UWorld>( Package, TEXT("TheWorld") );
							if( World )
							{	
								UObject::SavePackage( Package, World, 0, *Filename, GWarn );
							}
							else
							{
								UObject::SavePackage( Package, NULL, RF_Standalone, *Filename, GWarn );
							}
						}
						else
						{
							warnf(NAME_Error, TEXT("Failed to checkout:%s"), *Filename);
						}
					}
				}
			}

			UObject::CollectGarbage(RF_Native);
			// oscar@snda SaveLocalShaderCaches();
		}
		else
		{
			// oscar@snda
			SET_WARN_COLOR(COLOR_DARK_GREEN);
			warnf(
				TEXT("Package[%d/%d] %s not changed(SK %u, FM %u, PS %u, Be %u, SUV %u, SM %u, Dec %u, Flu %u, MEf %u, InstM %u, Spl %u, Door %u, ApxM %u, ApxP %u)"),
				CurProcIdx, MaxPkgCnt,
				*PackageIt.Key().ToString(),
				PackageInfo.SkeletalMeshMaterials.Num(),
				PackageInfo.FracturedMeshMaterials.Num(),
				PackageInfo.ParticleSpriteMaterials.Num(),
				PackageInfo.BeamTrailMaterials.Num(),
				PackageInfo.ParticleSubUVMaterials.Num(),
				PackageInfo.StaticLightingMaterials.Num(),
				PackageInfo.DecalMaterials.Num(),
				PackageInfo.FluidSurfacesMaterials.Num(),
				PackageInfo.MaterialEffectMaterials.Num(),
				PackageInfo.InstancedMeshMaterials.Num(),
				PackageInfo.SplineMeshMaterials.Num(),
				PackageInfo.ScreenDoorFadeMaterials.Num(),
				PackageInfo.ApexMeshMaterials.Num(),
				PackageInfo.ApexSpritesMaterials.Num()
				);

			CLEAR_WARN_COLOR();
		}


		++CurProcIdx; // oscar@snda
	}

	SaveLocalShaderCaches(); // oscar@snda 

	warnf(TEXT("%u decal materials out of %u total materials."),NumDecalMaterials,NumTotalMaterials); 
	warnf(TEXT("%u static lighting materials out of %u total materials."),NumStaticLightingMaterials,NumTotalMaterials); 

	// oscar@snda GEngine->Exec( TEXT("DumpShaderStats") );

	return 0;
}

IMPLEMENT_CLASS(USetMaterialUsageCommandlet);
