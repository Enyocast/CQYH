/*=============================================================================
UFindUnusedResCommandlet.cpp - Commandlet which finds what types of geometry a material is used on.
Copyright 1998-2013 Epic Games, Inc. All Rights Reserved. by Bruce@snda
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

#include "FileHelpers.h"

#include <ShellAPI.h>  

struct FUdkActorsReferenceAndUpkObjectsInfo
{
	TArray<FString> StaticMeshs;
	TArray<FString> SkeletalMeshs;
	TArray<FString> ParticleSprites;
	TArray<FString> Materials;
	TArray<FString> MaterialInstances;
	TArray<FString> Textures;

	//TArray<FLOAT> StaticMeshsResSize;
	//TArray<FLOAT> SkeletalMeshsResSize;
	//TArray<FLOAT> ParticleSpritesResSize;
	//TArray<FLOAT> MaterialsResSize;
	//TArray<FLOAT> MaterialInstanceResSize;
	//TArray<FLOAT> TexturesResSize;
};

INT UFindUnusedResCommandlet::Main( const FString& Params )
{
	const TCHAR* Parms = *Params;

	extern bool g_forceKeepAllMaterialQualityLevelsLoaded;
	g_forceKeepAllMaterialQualityLevelsLoaded = true;

	// Retrieve list of all packages in .ini paths.
	TArray<FString> PackageList;

	// figure out what packages to iterate over
	FString SinglePackage;
	bool useSpecifiedPackage = false; 
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
		TArray<FString> cfgPkgs;
		TArray<FString> cfgDirs;		
		GConfig->GetArray( TEXT("CheckUnusedRes"), TEXT("Path"), cfgDirs, GEditorIni );
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

	if( !PackageList.Num() )
	{
		warnf( TEXT( "Found no packages to fun SetMaterialUsageCommandlet on!" ) );
		return 0;
	}
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

	const UBOOL bAutoCheckOut = ParseParam(appCmdLine(),TEXT("AutoCheckOutPackages"));
#if HAVE_SCC
	// Ensure source control is initialized and shut down properly
	FScopedSourceControl SourceControl;
#endif
	
	FUdkActorsReferenceAndUpkObjectsInfo UdkActorReferenceInfoMap, UpkObjectsArray;

	for( INT PackageIndex = 0; PackageIndex < PackageList.Num(); PackageIndex++ )
	{
		FFilename Filename = PackageList(PackageIndex);

#if HAVE_SCC
		if ( bAutoCheckOut && FSourceControl::ForceGetStatus( Filename ) == SCC_NotCurrent )
		{
			warnf(NAME_Log, TEXT("Skipping %s (Not at head source control revision)"), *Filename);
			continue;
		}
#endif

		if(0 == GFileManager->FileSize(*Filename))
		{
			continue;
		}	

		if( Filename.GetExtension() == TEXT("udk") )
		{
			SET_WARN_COLOR( COLOR_PURPLE );
			warnf(TEXT("UDK Loading[%d/%d] %s"), PackageIndex + 1, PackageList.Num(), *Filename);
			CLEAR_WARN_COLOR();

			UPackage* UdkFile = UObject::LoadPackage( NULL, *Filename, LOAD_None );
			if ( UdkFile == NULL )
			{
				warnf( NAME_Error, TEXT("Unable to load %s"), *Filename );
				continue;
			}
			else 
			{
				if( !( UdkFile->IsFullyLoaded() ) )
				{
					UdkFile->FullyLoad();
				}

				for( FObjectIterator It; It; ++It )
				{
					if  ( It->IsA( AStaticMeshActor::StaticClass() ) )
					{
						AStaticMeshActor* SMActor = CastChecked<AStaticMeshActor>( *It );

						if ( SMActor && SMActor->StaticMeshComponent && SMActor->StaticMeshComponent->StaticMesh )
						{
							UdkActorReferenceInfoMap.StaticMeshs.AddUniqueItem( SMActor->StaticMeshComponent->StaticMesh->GetFullName() );
						}
					}

					if  ( It->IsA( ASkeletalMeshActor::StaticClass() ) )
					{
						ASkeletalMeshActor* SkMActor = CastChecked<ASkeletalMeshActor>( *It ); 

						if ( SkMActor && SkMActor->SkeletalMeshComponent && SkMActor->SkeletalMeshComponent->SkeletalMesh )
						{
							UdkActorReferenceInfoMap.SkeletalMeshs.AddUniqueItem( SkMActor->SkeletalMeshComponent->SkeletalMesh->GetFullName() );
						}
					}

					if  ( It->IsA( UParticleSystem::StaticClass() ) )
					{
						UParticleSystem* actorPS = CastChecked<UParticleSystem>( *It ); 

						if ( actorPS )
						{
							UdkActorReferenceInfoMap.ParticleSprites.AddUniqueItem( *( actorPS->GetFullName() ) );														
						}
					}

					if  ( It->IsA( UMaterial::StaticClass() ) )
					{
						UMaterial* matRes = CastChecked<UMaterial>( *It ); 

						if ( matRes )
						{
							UdkActorReferenceInfoMap.Materials.AddUniqueItem( matRes->GetFullName() );
						}
					}		

					if  ( It->IsA( UMaterialInstance::StaticClass() ) )
					{
						UMaterialInstance* MtrlInst = Cast<UMaterialInstance>( *It  );

						if ( MtrlInst )
						{
							UdkActorReferenceInfoMap.MaterialInstances.AddUniqueItem( MtrlInst->GetFullName() );
						}
					}	

// 					if  ( It->IsA( UTexture::StaticClass() ) )
// 					{
// 						UTexture* texturesRes = Cast<UTexture>( *It );
// 
// 						if ( texturesRes )
// 						{
// 							UdkActorReferenceInfoMap.Textures.AddUniqueItem( texturesRes->GetFullName() );
// 						}
// 					}
				}
			}
		}			

		UObject::CollectGarbage(RF_Native);
	}

	for( INT PackageIndex = 0; PackageIndex < PackageList.Num(); PackageIndex++ )
	{
		FFilename Filename = PackageList(PackageIndex);

#if HAVE_SCC
		if ( bAutoCheckOut && FSourceControl::ForceGetStatus( Filename ) == SCC_NotCurrent )
		{
			warnf(NAME_Log, TEXT("Skipping %s (Not at head source control revision)"), *Filename);
			continue;
		}
#endif

		if(0 == GFileManager->FileSize(*Filename))
		{
			continue;
		}			

		if ( Filename.GetExtension() == TEXT("upk") )
		{
			SET_WARN_COLOR( COLOR_GREEN );
			warnf(TEXT("UPK Loading[%d/%d] %s"), PackageIndex + 1, PackageList.Num(), *Filename);
			CLEAR_WARN_COLOR();

			FString PackageName = Filename.GetBaseFilename();

			INT Pos = PackageName.InStr( TEXT( "ShaderCache" ), FALSE, TRUE );
			if ( Pos != INDEX_NONE )
			{
				continue;
			}

			UPackage* NativePackage = UObject::CreatePackage( NULL, *PackageName, TRUE );
			UPackage* Package = UObject::LoadPackage( NativePackage, *Filename, LOAD_None );

			ULinkerLoad* Linker = UObject::GetPackageLinker( Package, *Filename, LOAD_NoWarn|LOAD_NoVerify|LOAD_RemappedPackage, NULL, NULL );
			check(Linker);

			if( ( Package == NULL ) || ( Linker == NULL ) )
			{
				warnf( NAME_Error, TEXT("Unable to load %s"), *Filename );
				continue;
			}
			else 
			{
				if( !( Package->IsFullyLoaded() ) )
				{
					Package->FullyLoad();
				}

				INT maxCnt = Package->NetObjects.Num();

				for (INT i = 0; i < maxCnt; ++i)
				{
					UObject* ObjectIt = Package->NetObjects(i);

					if ( ObjectIt != NULL )
					{
						if  ( ObjectIt->IsA( UStaticMesh::StaticClass() ) )
						{
							UStaticMesh* staticMeshRes = CastChecked<UStaticMesh>( ObjectIt );
							if ( staticMeshRes && ( *staticMeshRes->GetFullName() ) )
							{
								UpkObjectsArray.StaticMeshs.AddUniqueItem( *( staticMeshRes->GetFullName() ) );	
								//UpkObjectsArray.StaticMeshsResSize.AddItem( staticMeshRes->GetResourceSize() );
							}
						}

						if  ( ObjectIt->IsA( USkeletalMesh::StaticClass() ) )
						{
							USkeletalMesh* skelMeshRes = CastChecked<USkeletalMesh>( ObjectIt );
							if ( skelMeshRes && ( *skelMeshRes->GetFullName() ) )
							{
								UpkObjectsArray.SkeletalMeshs.AddUniqueItem( *( skelMeshRes->GetFullName() ) );	
								//UpkObjectsArray.SkeletalMeshsResSize.AddItem( skelMeshRes->GetResourceSize() );
							}
						}

						if  ( ObjectIt->IsA( UParticleSystem::StaticClass() ) )
						{
							UParticleSystem* parRes = CastChecked<UParticleSystem>( ObjectIt );
							if ( parRes && ( *( parRes->GetFullName() ) ) )
							{
								UpkObjectsArray.ParticleSprites.AddUniqueItem( *( parRes->GetFullName() ) );	
								//UpkObjectsArray.ParticleSpritesResSize.AddItem( parRes->GetResourceSize() );
							}
						}

						if  ( ObjectIt->IsA( UMaterial::StaticClass() ) )
						{
							UMaterial* matRes = CastChecked<UMaterial>( ObjectIt ); 

							if ( matRes )
							{
								UpkObjectsArray.Materials.AddUniqueItem( *( matRes->GetFullName() ) );	
								//UpkObjectsArray.MaterialsResSize.AddItem( matRes->GetResourceSize() );
							}
						}		

						if  ( ObjectIt->IsA( UMaterialInstance::StaticClass() ) )
						{
							UMaterialInstance* MtrlInst = Cast<UMaterialInstance>( ObjectIt  );

							if ( MtrlInst )
							{
								UpkObjectsArray.MaterialInstances.AddUniqueItem( *( MtrlInst->GetFullName() ) );	
								//UpkObjectsArray.MaterialInstanceResSize.AddItem( MtrlInst->GetResourceSize() );
							}
						}	

						//if  ( ObjectIt->IsA( UTexture::StaticClass() ) )
						//{
						//	UTexture* texturesRes = Cast<UTexture>( ObjectIt );

						//	if ( texturesRes )
						//	{
						//		UpkObjectsArray.Textures.AddUniqueItem( *( texturesRes->GetFullName() ) );	
						//		//UpkObjectsArray.TexturesResSize.AddItem( texturesRes->GetResourceSize() );
						//	}
						//}
					}
				}
			}
		}	

		UObject::CollectGarbage(RF_Native);
	}

	FString FindUnusedResTxtFile;

	GConfig->GetString( TEXT("FindUnusedResIni"), TEXT("FindUnusedResTXT"), FindUnusedResTxtFile, GEditorIni );
	
	//FLOAT TotalSizeSM = 0.0f;
	//FLOAT TotalSizeSkelMesh = 0.0f;
	//FLOAT TotalSizePS = 0.0f;
	//FLOAT TotalSizeMtl = 0.0f;
	//FLOAT TotalSizeMtlIns = 0.0f;
	//FLOAT TotalSizeTex = 0.0f;

	UBOOL HasIt;

	FUdkActorsReferenceAndUpkObjectsInfo DontHaveTheseInfo;
	for( INT i = 0; i < UpkObjectsArray.StaticMeshs.Num(); ++i )
	{
		HasIt = FALSE;
		for( INT T = 0; T < UdkActorReferenceInfoMap.StaticMeshs.Num(); ++T )
		{
			if ( UpkObjectsArray.StaticMeshs( i ) == UdkActorReferenceInfoMap.StaticMeshs( T ) )
			{
				HasIt = TRUE;
				break;
			}			
		}	

		if ( !HasIt )
		{
			DontHaveTheseInfo.StaticMeshs.AddUniqueItem( UpkObjectsArray.StaticMeshs( i ) );	
			//TotalSizeSM += UpkObjectsArray.StaticMeshsResSize(i);
		}
	}

	for( INT i = 0; i < UpkObjectsArray.SkeletalMeshs.Num(); ++i )
	{
		HasIt = FALSE;

		for( INT T = 0; T < UdkActorReferenceInfoMap.SkeletalMeshs.Num(); ++T )
		{
			if ( UpkObjectsArray.SkeletalMeshs( i ) == UdkActorReferenceInfoMap.SkeletalMeshs( T ) )
			{
				HasIt = TRUE;
				break;
			}			
		}	

		if ( !HasIt )
		{
			DontHaveTheseInfo.SkeletalMeshs.AddUniqueItem( UpkObjectsArray.SkeletalMeshs( i ) );	
			//TotalSizeSkelMesh += UpkObjectsArray.SkeletalMeshsResSize(i);
		}
	}		

	for( INT i = 0; i < UpkObjectsArray.ParticleSprites.Num(); ++i )
	{
		HasIt = FALSE;
		for( INT T = 0; T < UdkActorReferenceInfoMap.ParticleSprites.Num(); ++T )
		{
			if ( UpkObjectsArray.ParticleSprites( i ) == UdkActorReferenceInfoMap.ParticleSprites( T ) )
			{
				HasIt = TRUE;
				break;
			}			
		}		

		if ( !HasIt )
		{
			DontHaveTheseInfo.ParticleSprites.AddUniqueItem( UpkObjectsArray.ParticleSprites( i ) );	
			//TotalSizePS += UpkObjectsArray.ParticleSpritesResSize(i);
		}
	}

	for( INT i = 0; i < UpkObjectsArray.Materials.Num(); ++i )
	{
		HasIt = FALSE;
		for( INT T = 0; T < UdkActorReferenceInfoMap.Materials.Num(); ++T )
		{
			if ( UpkObjectsArray.Materials( i ) == UdkActorReferenceInfoMap.Materials( T ) )
			{
				HasIt = TRUE;
				break;
			}			
		}		

		if ( !HasIt )
		{
			DontHaveTheseInfo.Materials.AddUniqueItem( UpkObjectsArray.Materials( i ) );	
			//TotalSizeMtl += UpkObjectsArray.MaterialsResSize(i);
		}
	}

	for( INT i = 0; i < UpkObjectsArray.MaterialInstances.Num(); ++i )
	{
		HasIt = FALSE;
		for( INT T = 0; T < UdkActorReferenceInfoMap.MaterialInstances.Num(); ++T )
		{
			if ( UpkObjectsArray.MaterialInstances( i ) == UdkActorReferenceInfoMap.MaterialInstances( T ) )
			{
				HasIt = TRUE;
				break;
			}			
		}		

		if ( !HasIt )
		{
			DontHaveTheseInfo.MaterialInstances.AddUniqueItem( UpkObjectsArray.MaterialInstances( i ) );	
			//TotalSizeMtlIns += UpkObjectsArray.MaterialInstanceResSize(i);
		}
	}

	//for( INT i = 0; i < UpkObjectsArray.Textures.Num(); ++i )
	//{
	//	HasIt = FALSE;
	//	for( INT T = 0; T < UdkActorReferenceInfoMap.Textures.Num(); ++T )
	//	{
	//		if ( UpkObjectsArray.Textures( i ) == UdkActorReferenceInfoMap.Textures( T ) )
	//		{
	//			HasIt = TRUE;
	//			break;
	//		}			
	//	}		

	//	if ( !HasIt )
	//	{
	//		DontHaveTheseInfo.Textures.AddUniqueItem( UpkObjectsArray.Textures( i ) );	
	//		//TotalSizeTex += UpkObjectsArray.TexturesResSize(i);
	//	}
	//}

	/*FLOAT TotalSize = TotalSizeSM + TotalSizeSkelMesh + TotalSizePS + TotalSizeMtl + TotalSizeMtlIns + TotalSizeTex;
	FString TotalTmp = FString::Printf( TEXT("\r\n\r\nTotal Size: %f  MB  /  %f GB\r\n\r\n\r\n"),
		TotalSize / 1024 / 1024, TotalSize / 1024 / 1024 / 1024 );
	mapList.Add( TotalTmp );

	FString SMTmp = FString::Printf( TEXT("Total Static Meshs: %d --------Total Size: %f  KB  /  %f MB\r\n\r\n\r\n"),
		DontHaveTheseInfo.StaticMeshs.Num(), TotalSizeSM / 1024, TotalSizeSM / 1024 / 1024 );
	mapList.Add( SMTmp );

	FString SkelMTmp = FString::Printf( TEXT("Total Skeletal Meshs: %d --------Total Size: %f  KB  /  %f MB\r\n\r\n\r\n"),
		DontHaveTheseInfo.SkeletalMeshs.Num(), TotalSizeSkelMesh / 1024, TotalSizeSkelMesh / 1024 / 1024 );
	mapList.Add( SkelMTmp );

	FString PSTmp = FString::Printf( TEXT("Total Particle Sprites: %d --------Total Size: %f  KB  /  %f MB\r\n\r\n\r\n"),
		DontHaveTheseInfo.ParticleSprites.Num(), TotalSizePS / 1024, TotalSizePS / 1024 / 1024 );
	mapList.Add( PSTmp );

	FString MtlTmp = FString::Printf( TEXT("Total Materials: %d --------Total Size: %f  KB  /  %f MB\r\n\r\n\r\n"),
		DontHaveTheseInfo.Materials.Num(), TotalSizeMtl / 1024, TotalSizeMtl / 1024 / 1024 );
	mapList.Add( MtlTmp );

	FString MtlInsTmp = FString::Printf( TEXT("Total Material Instances: %d --------Total Size: %f  KB  /  %f MB\r\n\r\n\r\n"),
		DontHaveTheseInfo.MaterialInstances.Num(), TotalSizeMtlIns / 1024, TotalSizeMtlIns / 1024 / 1024 );
	mapList.Add( MtlInsTmp );

	FString TexTmp = FString::Printf( TEXT("Total Textures: %d --------Total Size: %f  KB  /  %f MB\r\n\r\n\r\n"),
		DontHaveTheseInfo.Textures.Num(), TotalSizeTex / 1024, TotalSizeTex / 1024 / 1024 );
	mapList.Add( TexTmp );*/

	//FString FirstmapName = TEXT("\r\n\r\n\r\n [ Static Meshs ] \r\n\r\n\r\n");
	//mapList.Add( FirstmapName );

	FString AllItems;

	for(INT i = 0; i < DontHaveTheseInfo.StaticMeshs.Num(); ++i)
	{
		AllItems += DontHaveTheseInfo.StaticMeshs( i ) + TEXT("\r\n");
	}

	//FirstmapName = TEXT("\r\n\r\n\r\n [ Skeletal Meshs ] \r\n\r\n\r\n");
	//mapList.Add( FirstmapName );
	for(INT i = 0; i < DontHaveTheseInfo.SkeletalMeshs.Num(); ++i)
	{
		AllItems += DontHaveTheseInfo.SkeletalMeshs( i ) + TEXT("\r\n");
	}

	//FirstmapName = TEXT("\r\n\r\n\r\n [ Particle Sprites ] \r\n\r\n\r\n");
	//mapList.Add( FirstmapName );
	for(INT i = 0; i < DontHaveTheseInfo.ParticleSprites.Num(); ++i)
	{
		AllItems += DontHaveTheseInfo.ParticleSprites( i ) + TEXT("\r\n");
	}

	//FirstmapName = TEXT("\r\n\r\n\r\n [ Materials ] \r\n\r\n\r\n");
	//mapList.Add( FirstmapName );
	for( INT i = 0; i < DontHaveTheseInfo.Materials.Num(); ++i )
	{
		AllItems += DontHaveTheseInfo.Materials( i ) + TEXT("\r\n");
	}

	//FirstmapName = TEXT("\r\n\r\n\r\n [ Material Instances ] \r\n\r\n\r\n");
	//mapList.Add( FirstmapName );
	for( INT i = 0; i < DontHaveTheseInfo.MaterialInstances.Num(); ++i )
	{
		AllItems += DontHaveTheseInfo.MaterialInstances( i ) + TEXT("\r\n");
	}

	//FirstmapName = TEXT("\r\n\r\n\r\n [ Textures ] \r\n\r\n\r\n");
	//mapList.Add( FirstmapName );
	//for( INT i = 0; i < DontHaveTheseInfo.Textures.Num(); ++i )
	//{
	//	AllItems += DontHaveTheseInfo.Textures( i ) + TEXT("\r\n");
	//}

	appSaveStringToFile( AllItems, *FindUnusedResTxtFile );

	//if ( FindUnusedResTxtFile.Len() && GFileManager->FileSize( *FindUnusedResTxtFile ) != INDEX_NONE )
	//{
	//	ShellExecuteW( NULL, TEXT("open"), TEXT("notepad.EXE"), *FindUnusedResTxtFile, TEXT(""), SW_SHOWNORMAL );
	//}

	return 0;
}

IMPLEMENT_CLASS(UFindUnusedResCommandlet);

