/**
 * Copyright 1998-2010 Epic Games, Inc. All Rights Reserved.
 */

#include "SwordEditor.h"
#include "SwordCookerHelper.h"

const FLOAT BossCommonPercentage = 0.75f;

UBOOL FSwordGameCookerHelper::AddSeekfreePackage( const FString& PackageName, class UCookPackagesCommandlet* Commandlet, TArray<FPackageCookerInfo>& StandaloneSeekfreeFilenamePairs, DOUBLE FileCheckTime, UBOOL bRealPackage)
{
	FString PackageFilename = PackageName;
	if( !bRealPackage || GPackageFileCache->FindPackageFile(*PackageName, NULL, PackageFilename) )
	{
		// Don't add the package twice
		for( INT i=0; i<StandaloneSeekfreeFilenamePairs.Num(); i++ )
		{
			if(	StandaloneSeekfreeFilenamePairs(i).SrcFilename == PackageFilename )
			{
				return TRUE;
			}
		}

		FPackageCookerInfo CookerInfo;

		// Source filename of temp package to be cooked (may be used later to find object to cook)
		CookerInfo.SrcFilename = PackageFilename;
		// Destination filename for cooked seekfree package (must be derived from the SrcFilename)
		CookerInfo.DstFilename = Commandlet->GetCookedPackageFilename(CookerInfo.SrcFilename);

		// Do our own tests to see if dest file is out of date if we are creating new packages from archetypes
		FFilename ActualDstName;

		if( bRealPackage )
		{
			ActualDstName = CookerInfo.DstFilename;
		}
		else
		{
			// Determine actual source file name and store in PackageFileName
			FString SourceFileName = PackageName.Left(PackageName.InStr(TEXT(".")));		// Get the actual package name without the object name
			SourceFileName = SourceFileName.Right(SourceFileName.Len() - SourceFileName.InStr(TEXT("_")) - 1);	// Chop off the prefix
			GPackageFileCache->FindPackageFile(*SourceFileName, NULL, PackageFilename);

			// Determine actual dest file name
			if( PackageName.InStr(TEXT(".")) > 0 )
			{
				// This is an archetype name, so grab the object name to use as the package name
				ActualDstName = PackageName.Right(PackageName.Len() - PackageName.InStr(TEXT("."), TRUE) - 1);	// Get the object name
				FString Prefix = PackageName.Left(PackageName.InStr(TEXT("_")) + 1);							// Get the prefix
				ActualDstName = Prefix + ActualDstName;
			}
			else
			{
				// The real package was sent in, just use it as is
				ActualDstName = PackageName;
			}

			// Destination filename for cooked seekfree package
			ActualDstName = Commandlet->GetCookedPackageFilename(ActualDstName);
		}

		// Add the _SF suffix to the package name
		ActualDstName = ActualDstName.GetBaseFilename(FALSE) + STANDALONE_SEEKFREE_SUFFIX;
		ActualDstName += FString(TEXT(".")) + CookerInfo.DstFilename.GetExtension();

		DOUBLE SourceFileTime = GFileManager->GetFileTimestamp(*PackageFilename);
		DOUBLE DestFileTime = GFileManager->GetFileTimestamp(*ActualDstName);

		if (FileCheckTime < 0 || DestFileTime < FileCheckTime || DestFileTime < SourceFileTime)
		{
			// setup flags to cook as seekfree standalone package
			CookerInfo.bShouldBeSeekFree = TRUE;
			CookerInfo.bIsNativeScriptFile = FALSE;
			CookerInfo.bIsCombinedStartupPackage = FALSE;
			CookerInfo.bIsStandaloneSeekFreePackage = TRUE;
			CookerInfo.bShouldOnlyLoad = FALSE;

			StandaloneSeekfreeFilenamePairs.AddItem(CookerInfo);
		}

		return TRUE;
	}

	return FALSE;
}

UBOOL FSwordGameCookerHelper::AddSeekfreePackageFromProperty( UObject* Obj, const TCHAR* PropertyName, enum EObjectPropertyType PropertyType, FString& PackageName, class UCookPackagesCommandlet* Commandlet, TArray<FPackageCookerInfo>& StandaloneSeekfreeFilenamePairs, DOUBLE FileCheckTime, UBOOL bCheckExists)
{
	UBOOL bAddedPackage = FALSE;

	if( Obj != NULL )
	{
		UProperty* Property = FindField<UProperty>(Obj->GetClass(), PropertyName);
		if( Property != NULL )
		{
			BYTE* BaseData = (BYTE*)Obj + Property->Offset;
			INT ElementCount = Property->ArrayDim;
			UProperty* ExportProperty = Property;

			if( Cast<UArrayProperty>(Property) != NULL )
			{
				FScriptArray* Array = (FScriptArray*)BaseData;
				UArrayProperty* ArrayProp = Cast<UArrayProperty>(Property);

				BaseData = (BYTE*)Array->GetData();
				ElementCount = Array->Num();
				ExportProperty = ArrayProp->Inner;
			}

			// Create a package for each custom FX (if any)
			for( INT PropIdx=0; PropIdx < ElementCount; PropIdx++ )
			{
				FName CustomName;
				switch( PropertyType )
				{
					case OPT_Name:
						{
							FName* NamePtr = (FName*)(BaseData + PropIdx * ExportProperty->ElementSize);
							CustomName = *NamePtr;
						}
						break;
					case OPT_MagicSpell:
						{
							FSwordMagicSpell* Spell = (FSwordMagicSpell*)(BaseData + PropIdx * ExportProperty->ElementSize);
							if( Spell != NULL && Spell->CustomFX != NAME_None )
								CustomName = Spell->CustomFX;
						}
						break;
				};
				if( CustomName != NAME_None )
				{
					FString CustomPackageName = FString::Printf(TEXT("%s.%s"), *PackageName, *CustomName.ToString());
					AddSeekfreePackage(CustomPackageName, Commandlet, StandaloneSeekfreeFilenamePairs, FileCheckTime, FALSE);
					bAddedPackage = TRUE;
				}
			}
		}
	}

	return bAddedPackage;
}

/**
 *	Initialize the cooker helpr and process any command line params
 *
 *	@param	Commandlet		The cookpackages commandlet being run
 *	@param	Tokens			Command line tokens parsed from app
 *	@param	Switches		Command line switches parsed from app
 */
void FSwordGameCookerHelper::Init(class UCookPackagesCommandlet* Commandlet, 
	const TArray<FString>& Tokens, const TArray<FString>& Switches)
{
	warnf(NAME_Log, TEXT("Initializing SwordGameCookerHelper..."));

	bSkipBossCommon = (Switches.FindItemIndex(TEXT("NOBOSSCOMMON")) != INDEX_NONE);
	if (bSkipBossCommon == TRUE)
	{
		warnf(NAME_Log, TEXT("BOSS COMMON package generation disabled..."));
	}

	bShowBossPackageDetails = (Switches.FindItemIndex(TEXT("SHOWBOSSDETAILS")) != INDEX_NONE);

	CurrentBossGroupPackageObjects = NULL;
	BossHelper.Init();
}

/** 
 *	Generate the package list that is specific for the game being cooked.
 *
 *	@param	Commandlet							The cookpackages commandlet being run
 *	@param	Platform							The platform being cooked for
 *	@param	ShaderPlatform						The shader platform being cooked for
 *	@param	NotRequiredFilenamePairs			The package lists being filled in...
 *	@param	RegularFilenamePairs				""
 *	@param	MapFilenamePairs					""
 *	@param	ScriptFilenamePairs					""
 *	@param	StartupFilenamePairs				""
 *	@param	StandaloneSeekfreeFilenamePairs		""
 *	
 *	@return	UBOOL		TRUE if successful, FALSE is something went wrong.
 */
UBOOL FSwordGameCookerHelper::GeneratePackageList( 
	class UCookPackagesCommandlet* Commandlet, 
	UE3::EPlatformType Platform,
	EShaderPlatform ShaderPlatform,
	TArray<FPackageCookerInfo>& NotRequiredFilenamePairs,
	TArray<FPackageCookerInfo>& RegularFilenamePairs,
	TArray<FPackageCookerInfo>& MapFilenamePairs,
	TArray<FPackageCookerInfo>& ScriptFilenamePairs,
	TArray<FPackageCookerInfo>& StartupFilenamePairs,
	TArray<FPackageCookerInfo>& StandaloneSeekfreeFilenamePairs)
{
	UBOOL bSuccess=TRUE;

	if (FGameCookerHelper::GeneratePackageList(
		Commandlet,
		Platform,
		ShaderPlatform,
		NotRequiredFilenamePairs,
		RegularFilenamePairs,
		MapFilenamePairs,
		ScriptFilenamePairs,
		StartupFilenamePairs,
		StandaloneSeekfreeFilenamePairs
		) == FALSE)
	{
		bSuccess = FALSE;
	}

	// Add in all the boss packages that have not been created yet
	INT NumBossPackages = 0;
	for( INT MapIdx=0; MapIdx<MapFilenamePairs.Num(); MapIdx++ )
	{
		FString PackageFilename;
		if( GPackageFileCache->FindPackageFile(*MapFilenamePairs(MapIdx).SrcFilename, NULL, PackageFilename))
		{
			// read the package file summary of the package to get a list of sublevels
			FArchive* PackageFile = GFileManager->CreateFileReader(*PackageFilename);
			if (PackageFile)
			{
				// read the package summary, which has list of sub levels
				FPackageFileSummary Summary;
				(*PackageFile) << Summary;

				// close the map
				delete PackageFile;

				// Make sure this is a map
				if ( (Summary.PackageFlags&PKG_ContainsMap) != 0 )
				{
					for (INT AdditionalPackageIndex = 0; AdditionalPackageIndex < Summary.AdditionalPackagesToCook.Num(); AdditionalPackageIndex++)
					{
						// check if it's a boss character package
						FString BaseFilename = Summary.AdditionalPackagesToCook(AdditionalPackageIndex);
						if( BaseFilename.StartsWith(BOSS_CHARACTER_PACKAGE_PREFIX) )
						{
							// 							INT NumFiles = StandaloneSeekfreeFilenamePairs.Num();
							// 							AddSeekfreePackage(BaseFilename, Commandlet, StandaloneSeekfreeFilenamePairs, -1, FALSE);
							// 							if( StandaloneSeekfreeFilenamePairs.Num() > NumFiles )
							{
								if (BossPackageNamesFromMaps.FindItemIndex(BaseFilename) == INDEX_NONE)
								{
									warnf(NAME_Log, TEXT("%d - Added boss package %s referenced in %s"), NumBossPackages++, *BaseFilename, *PackageFilename);
									BossPackageNamesFromMaps.AddUniqueItem(BaseFilename);
								}
							}
						}
					}
				}
			}
		}
	}

	// Load all the boss names for the generation of the common and group packages.
	if (bSkipBossCommon == FALSE)
	{
		for (INT GroupIdx = 0; GroupIdx < BossHelper.GetNumGroups(); GroupIdx++)
		{
			TArray<FString> GroupBosses;
			if (BossHelper.GetGroup(GroupIdx, GroupBosses) == TRUE)
			{
				BossPackageNames += GroupBosses;
			}
			else
			{
				warnf(NAME_Warning, TEXT("Failed to get boss group %d of %d"), GroupIdx, BossHelper.GetNumGroups());
			}
		}
	}
	else
	{
		BossPackageNames = BossPackageNamesFromMaps;
	}

	CreateBossPackages(Commandlet, StandaloneSeekfreeFilenamePairs);

	InventoryPackageNames.Empty();

	DOUBLE CheckTime = GFileManager->GetFileTimestamp(*(appGameConfigDir() + TEXT("SwordItems.ini")));

	// Get the icon packages from the ini file
	FString ConfigFileName = USwordInventoryItem::StaticClass()->GetConfigName();
	if( GConfig->GetArray( TEXT("IconPackages"), TEXT("Packages"), IconPackageNames, *ConfigFileName ) <= 0 )
	{
		warnf(NAME_Warning, TEXT("Failed to find any icon packages. You must have an [IconPackages] section in DefaultItems.ini"));
	}
	INT NumIconPaks = IconPackageNames.Num();
	for (INT i=0; i<NumIconPaks; i++)
	{
		IconPackageNames.AddItem(IconPackageNames(i) + STANDALONE_SEEKFREE_SUFFIX);
	}

	// Generate packages for character mesh parts
	TArray<class USwordInventoryItem*> Inventory;
	USwordEngine* SwordEngine = (USwordEngine*)(USwordEngine::StaticClass()->GetDefaultObject());
	ASwordBasePC* PC = (ASwordBasePC*)(ASwordBasePC::StaticClass()->GetDefaultObject());

	// The source package name for custom FX
	FString CustomFXPackageName = FString::Printf(CUSTOMFX_PACKAGE_PREFIX TEXT("%s"), *PC->DefaultCustomItemFXPackageName);

	SwordEngine->PopulateSwordInventoryItems(USwordInventoryItem::StaticClass(), Inventory);
	for( INT i = 0; i < Inventory.Num(); i++ )
	{
		USwordInventoryItem* Item = Inventory(i);
		check(Item);

		// Find the package for this mesh
		FString PackageName = Item->MeshPath.Left( Item->MeshPath.InStr(TEXT(".")) );
		if( AddSeekfreePackage(PackageName, Commandlet, StandaloneSeekfreeFilenamePairs, CheckTime) )
		{
			InventoryPackageNames.AddItem(PackageName);
			InventoryPackageNames.AddItem(PackageName + STANDALONE_SEEKFREE_SUFFIX);
		}
		else
		{
			// Warn if there is no mesh, except for Rings (type=5) which have no mesh
			if( Item->ItemType != 5 )
			{
				warnf(NAME_Warning, TEXT("Failed to find a package for mesh '%s' in inventory item '%s'"), *Item->MeshPath, *Item->GetName());
			}
		}

		// Find the package for the icon
		PackageName = Item->IconPath.Left( Item->IconPath.InStr(TEXT(".")) );
		if( IconPackageNames.ContainsItem(PackageName) )
		{
			if( AddSeekfreePackage(PackageName, Commandlet, StandaloneSeekfreeFilenamePairs, CheckTime) )
			{
				IconTextureNames.AddItem(Item->IconPath);
			}
			else
			{
				warnf(NAME_Warning, TEXT("Failed to find a package for icon '%s' in inventory item '%s'"), *Item->IconPath, *Item->GetName());
			}
		}
		else
		{
			warnf(NAME_Warning, TEXT("Failed to find the package '%s' in the [IconPackages] ini section for icon '%s' in inventory item '%s'"), *PackageName, *Item->IconPath, *Item->GetName());
		}

		// Create a package for any custom FX
		if( Item->CustomFX != NAME_None )
		{
			FString PackageName = FString::Printf(TEXT("%s.%s"), *CustomFXPackageName, *Item->CustomFX.ToString());
			AddSeekfreePackage(PackageName, Commandlet, StandaloneSeekfreeFilenamePairs, CheckTime, FALSE);
		}
	}

	//get customfx from consumables
	SwordEngine->PopulateSwordInventoryItems(USwordInventoryConsumable::StaticClass(), Inventory);
	for( INT i = 0; i < Inventory.Num(); i++ )
	{
		USwordInventoryConsumable* Item = (USwordInventoryConsumable*)Inventory(i);
		check(Item);

		// Create a package for any custom FX
		if( Item->CustomFX != NAME_None )
		{
			FString PackageName = FString::Printf(TEXT("%s.%s"), *CustomFXPackageName, *Item->CustomFX.ToString());
			AddSeekfreePackage(PackageName, Commandlet, StandaloneSeekfreeFilenamePairs, CheckTime, FALSE);
		}

		// Check for customfx for different types
		for( INT j = 0; j < Item->CustomFXTypeList.Num(); j++ )
		{
			FString PackageName = FString::Printf(TEXT("%s.%s"), *CustomFXPackageName, *Item->CustomFXTypeList(j).ToString());
			AddSeekfreePackage(PackageName, Commandlet, StandaloneSeekfreeFilenamePairs, CheckTime, FALSE);
		}
	}


	// Add in any custom FX packages referenced in the player pawn
	ASwordGame* SwordGame = (ASwordGame*)(ASwordGame::StaticClass()->GetDefaultObject());
	ASwordPawn* PlayerPawn = Cast<ASwordPawn>(SwordGame->DefaultPawnArchetype);

	if( PlayerPawn != NULL )
	{
		// Magic spell effects
		AddSeekfreePackageFromProperty(PlayerPawn, TEXT("MagicSpells"), OPT_MagicSpell, CustomFXPackageName, Commandlet, StandaloneSeekfreeFilenamePairs, CheckTime, FALSE);

		// Default weapon class effects
		AddSeekfreePackageFromProperty(PlayerPawn, TEXT("DefaultCustomFX_TwoHanded"),		OPT_Name, CustomFXPackageName, Commandlet, StandaloneSeekfreeFilenamePairs, CheckTime, FALSE);
		AddSeekfreePackageFromProperty(PlayerPawn, TEXT("DefaultCustomFX_TwoWeapon"),		OPT_Name, CustomFXPackageName, Commandlet, StandaloneSeekfreeFilenamePairs, CheckTime, FALSE);
		AddSeekfreePackageFromProperty(PlayerPawn, TEXT("DefaultCustomFX_SwordAndShield"),	OPT_Name, CustomFXPackageName, Commandlet, StandaloneSeekfreeFilenamePairs, CheckTime, FALSE);
	}

	// Add all the possible random boss elemental FX
	TArray<FString> PotentialCustomFX;
	if( GConfig->GetArray(TEXT("AdditionalCustomFXNames"), TEXT("CustomFXName"), PotentialCustomFX, GGameIni) )
	{
		for( INT i=0; i<PotentialCustomFX.Num(); i++ )
		{
			if( PotentialCustomFX(i).Len() )
			{
				FString CustomFxPackage = FString::Printf(CUSTOMFX_PACKAGE_PREFIX TEXT("%s"), *PotentialCustomFX(i));
				AddSeekfreePackage(CustomFxPackage, Commandlet, StandaloneSeekfreeFilenamePairs, 0, FALSE);
			}
		}
	}

	// Add all the possible generic stand alone packages
	TArray<FString> StandAlonePackages;
	if( GConfig->GetArray(TEXT("AdditionalStandAlonePackages"), TEXT("StandAlonePackageName"), StandAlonePackages, GGameIni) )
	{
		for( INT i=0; i<StandAlonePackages.Num(); i++ )
		{
			if( StandAlonePackages(i).Len() )
				AddSeekfreePackage(*StandAlonePackages(i), Commandlet, StandaloneSeekfreeFilenamePairs, 0, FALSE);
		}
	}

#if USE_ITEMOBJECT_PACKAGES
	//add inventory items to seekfree list
	USwordInventoryItem* ItemClass = Cast<USwordInventoryItem>(USwordInventoryItem::StaticClass()->GetDefaultObject());
	CheckTime = GFileManager->GetFileTimestamp(*ItemClass->GetClass()->GetConfigName());
	AddSeekfreePackage(ItemClass->ItemPackageName, Commandlet, StandaloneSeekfreeFilenamePairs, CheckTime, FALSE);

	ItemClass = Cast<USwordInventoryItem>(USwordInventoryBossItem::StaticClass()->GetDefaultObject());
	CheckTime = GFileManager->GetFileTimestamp(*ItemClass->GetClass()->GetConfigName());
	AddSeekfreePackage(ItemClass->ItemPackageName, Commandlet, StandaloneSeekfreeFilenamePairs, CheckTime, FALSE);

	ItemClass = Cast<USwordInventoryItem>(USwordInventoryMPItem::StaticClass()->GetDefaultObject());
	CheckTime = GFileManager->GetFileTimestamp(*ItemClass->GetClass()->GetConfigName());
	AddSeekfreePackage(ItemClass->ItemPackageName, Commandlet, StandaloneSeekfreeFilenamePairs, CheckTime, FALSE);

	ItemClass = Cast<USwordInventoryItem>(USwordInventorySPItem::StaticClass()->GetDefaultObject());
	CheckTime = GFileManager->GetFileTimestamp(*ItemClass->GetClass()->GetConfigName());
	AddSeekfreePackage(ItemClass->ItemPackageName, Commandlet, StandaloneSeekfreeFilenamePairs, CheckTime, FALSE);

	ItemClass = Cast<USwordInventoryItem>(USwordInventoryConsumable::StaticClass()->GetDefaultObject());
	CheckTime = GFileManager->GetFileTimestamp(*ItemClass->GetClass()->GetConfigName());
	AddSeekfreePackage(ItemClass->ItemPackageName, Commandlet, StandaloneSeekfreeFilenamePairs, CheckTime, FALSE);
#endif

	return bSuccess;
}

void SwordGameCooker_MarkObjectCooked(UObject* InObject)
{
	InObject->ClearFlags(RF_ForceTagExp);
	InObject->SetFlags(RF_MarkedByCooker);
	UObject* MarkOuter = InObject->GetOuter();
	while (MarkOuter)
	{
		MarkOuter->ClearFlags(RF_ForceTagExp);
		MarkOuter->SetFlags(RF_MarkedByCooker);
		MarkOuter = MarkOuter->GetOuter();
	}
}

/**
 * Cooks passed in object if it hasn't been already.
 *
 *	@param	Commandlet					The cookpackages commandlet being run
 *	@param	Package						Package going to be saved
 *	@param	Object						Object to cook
 *	@param	bIsSavedInSeekFreePackage	Whether object is going to be saved into a seekfree package
 *
 *	@return	UBOOL						TRUE if the object should continue the 'normal' cooking operations.
 *										FALSE if the object should not be processed any further.
 */
UBOOL FSwordGameCookerHelper::CookObject(class UCookPackagesCommandlet* Commandlet, UPackage* Package, UObject* Object, UBOOL bIsSavedInSeekFreePackage)
{
	FString PackageName = Package->GetName();
	// Make sure the MICs for the inventory get set up correctly
	if( InventoryPackageNames.ContainsItem(PackageName) )
	{
		UMaterialInstanceConstant* MIC = Cast<UMaterialInstanceConstant>(Object);
		if( MIC )
		{
			UTexture* Texture;

			// Set the base texture to the Diffuse parameter if needed
			if( MIC->MobileBaseTexture == NULL && MIC->GetTextureParameterValue(FName(TEXT("Diffuse")), Texture) )
			{
				MIC->MobileBaseTexture = Texture;
			}

			// Set the normal texture to the Normal parameter if needed
			if( MIC->MobileNormalTexture == NULL && MIC->GetTextureParameterValue(FName(TEXT("Normal")), Texture) )
			{
				MIC->MobileNormalTexture = Texture;
			}

			// Set the emissive texture to the Emissive parameter if needed
			if( MIC->MobileEmissiveTexture == NULL && MIC->GetTextureParameterValue(FName(TEXT("Emissive")), Texture) )
			{
				MIC->MobileEmissiveTexture = Texture;
			}
		}
	}
	else if (IconPackageNames.ContainsItem(PackageName))
	{
		// Cull textures that are not being used in the inventory ini
		if (Object->IsA(UTexture::StaticClass()) && !IconTextureNames.ContainsItem(Object->GetPathName()))
		{
			SwordGameCooker_MarkObjectCooked(Object);
			return FALSE;
		}
	}
	else if (PackageName.StartsWith(BOSS_CHARACTER_PACKAGE_PREFIX))
	{
		if (PackageName.StartsWith(BossHelper.GetBossCommonPackageName()) == FALSE)
		{
			if (
				//(Object->IsA(UClass::StaticClass()) == FALSE) &&
				(Object->IsA(UPackage::StaticClass()) == FALSE) &&
				(Object->HasAnyFlags(RF_ClassDefaultObject|RF_Transient) == FALSE)
				)
			{
				// This is a non-common boss package...
				FString ObjFullName = Object->GetFullName();
				FLOAT* Percentage = BossCommonPackageObjects.Find(ObjFullName);
				if (Percentage != NULL)
				{
					debugf(TEXT("Marking %5.2f BOSS_COMMON object cooked: %s"), *Percentage, *ObjFullName);
					SwordGameCooker_MarkObjectCooked(Object);
					return FALSE;
				}

				if (CurrentBossGroupPackageObjects != NULL)
				{
					if (CurrentBossGroupPackageObjects->Find(ObjFullName) != NULL)
					{
						// It is in the current group package.
						debugf(NAME_Log, TEXT("Marking BOSS GROUP object cooked: %s"), *ObjFullName);
						SwordGameCooker_MarkObjectCooked(Object);
						return FALSE;
					}
					else
					{
						UObject* OuterObj = Object->GetOuter();
						if (OuterObj != NULL)
						{
							if (OuterObj->IsA(UPackage::StaticClass()) == FALSE)
							{
								FString OuterFullName = OuterObj->GetFullName();
								if (CurrentBossGroupPackageObjects->Find(OuterFullName) != NULL)
								{
									debugf(TEXT("Outer of object is in marked list: %s"), *OuterFullName);
								}
							}
						}
					}
				}
			}
		}
	}

	return FGameCookerHelper::CookObject(Commandlet, Package, Object, bIsSavedInSeekFreePackage);
}

void RecursiveObjectCollection(UObject* InStartObject, INT InCurrDepth, INT InMaxDepth, TArray<UObject*>& OutCollectedReferences)
{
	// Serialize object with reference collector.
	TArray<UObject*> LocalCollectedReferences;
	FArchiveObjectReferenceCollector ObjectReferenceCollector(&LocalCollectedReferences, NULL, FALSE, TRUE, TRUE, TRUE);
	InStartObject->Serialize(ObjectReferenceCollector);
	if (InCurrDepth < InMaxDepth)
	{
		InCurrDepth++;
		for (INT ObjRefIdx = 0; ObjRefIdx < LocalCollectedReferences.Num(); ObjRefIdx++)
		{
			UObject* InnerObject = LocalCollectedReferences(ObjRefIdx);
			if( (InnerObject != NULL) &&
				//(InnerObject->IsA(UClass::StaticClass()) == FALSE) &&
				(InnerObject->IsA(UPackage::StaticClass()) == FALSE) &&
				!InnerObject->HasAnyFlags(RF_ClassDefaultObject|RF_Transient) &&
				!OutCollectedReferences.ContainsItem(InnerObject) )
			{
				OutCollectedReferences.AddItem(InnerObject);
				RecursiveObjectCollection(InnerObject, InCurrDepth, InMaxDepth, OutCollectedReferences);
			}
		}
		InCurrDepth--;
	}
}

/** 
 *	LoadPackageForCookingCallback
 *	This function will be called in LoadPackageForCooking, allowing the cooker
 *	helper to handle the package creation as they wish.
 *
 *	@param	Commandlet		The cookpackages commandlet being run
 *	@param	Filename		The name of the package to load.
 *
 *	@return	UPackage*		The package generated/loaded
 *							NULL if the commandlet should load the package normally.
 */
UPackage* FSwordGameCookerHelper::LoadPackageForCookingCallback(class UCookPackagesCommandlet* Commandlet, const TCHAR* Filename)
{
	UPackage* Result = NULL;
	
	// load package for standalone seekfree game content for the given filename
	Result = FGameCookerHelper::LoadPackageForCookingCallback(Commandlet,Filename);

	if( Result == NULL )
	{
		FString BaseFilename = FFilename(Filename).GetBaseFilename();
		// check if it's a boss character package
		if( BaseFilename.StartsWith(BOSS_CHARACTER_PACKAGE_PREFIX) )
		{
			FFilename BossFilename = FFilename(Filename);
			debugf(TEXT("Request for boss package: %s"), *BossFilename);
			CurrentBossGroupPackageObjects = NULL;
			Result = CreateBossPackage(Commandlet, BossFilename, FALSE);
			FString BossGroupName;
			if (BossHelper.GetBossGroup(BossFilename, BossGroupName) == TRUE)
			{
				// Set the current boss group content
				if (bShowBossPackageDetails)
				{
					warnf(NAME_Log, TEXT("\tGroup package is %s"), *BossGroupName);
				}
				CurrentBossGroupPackageObjects = BossGroupPackageObjects.Find(BossGroupName);
			}
		}
		// check if it's a custom FX package
		else if( BaseFilename.StartsWith(CUSTOMFX_PACKAGE_PREFIX) )
		{
			// Create a package for this object and all its data
			BaseFilename = Filename;
			FString ArchetypePath = BaseFilename.Right(BaseFilename.Len() - appStrlen(CUSTOMFX_PACKAGE_PREFIX));
			FString NewFilename = FString::Printf(CUSTOMFX_PACKAGE_PREFIX TEXT("%s"), *ArchetypePath.Right(ArchetypePath.Len() - ArchetypePath.InStr(TEXT("."), TRUE) - 1) );
			debugf(TEXT("Loading archetype %s to create package %s"), *ArchetypePath, *NewFilename);
			USwordCustomFX* Archetype = LoadObject<USwordCustomFX>( NULL, *ArchetypePath, NULL, LOAD_NoWarn | LOAD_Quiet, NULL );
			if( Archetype != NULL )
			{
				// create the package and object that will hold the references
				Result = UObject::CreatePackage(NULL, *NewFilename);
				UObjectReferencer* RefHolder = ConstructObject<UObjectReferencer>(UObjectReferencer::StaticClass(), Result, FName(TEXT("Referencer")));
				RefHolder->SetFlags(RF_Standalone);

				// Save the archetype in the package (along with everything it references)
				RefHolder->ReferencedObjects.AddItem(Archetype);
			}
			else
			{
#if USE_ITEMOBJECT_PACKAGES
				//hacky, but check for and make our faked inventory class packages, also tag on PKG_StoreFullyCompressed so these are the only things compress...
				if(Cast<USwordInventoryItem>(USwordInventoryItem::StaticClass()->GetDefaultObject())->ItemPackageName == Filename)
				{
					Result = Cast<ASwordBasePC>(ASwordBasePC::StaticClass()->GetDefaultObject())->CreateSwordInventoryPackage(USwordInventoryItem::StaticClass(), false);
				}
				else if(Cast<USwordInventoryItem>(USwordInventoryBossItem::StaticClass()->GetDefaultObject())->ItemPackageName == Filename)
				{
					Result = Cast<ASwordBasePC>(ASwordBasePC::StaticClass()->GetDefaultObject())->CreateSwordInventoryPackage(USwordInventoryBossItem::StaticClass(), false);
				}
				else if(Cast<USwordInventoryItem>(USwordInventoryMPItem::StaticClass()->GetDefaultObject())->ItemPackageName == Filename)
				{
					Result = Cast<ASwordBasePC>(ASwordBasePC::StaticClass()->GetDefaultObject())->CreateSwordInventoryPackage(USwordInventoryMPItem::StaticClass(), false);
				}
				else if(Cast<USwordInventoryItem>(USwordInventorySPItem::StaticClass()->GetDefaultObject())->ItemPackageName == Filename)
				{
					Result = Cast<ASwordBasePC>(ASwordBasePC::StaticClass()->GetDefaultObject())->CreateSwordInventoryPackage(USwordInventorySPItem::StaticClass(), false);
				}
				else if(Cast<USwordInventoryItem>(USwordInventoryConsumable::StaticClass()->GetDefaultObject())->ItemPackageName == Filename)
				{
					Result = Cast<ASwordBasePC>(ASwordBasePC::StaticClass()->GetDefaultObject())->CreateSwordInventoryPackage(USwordInventoryConsumable::StaticClass(), false);
				}
				else
#endif
				{
					warnf(NAME_Warning, TEXT("   *Failed to load custom fx archetype %s"), *ArchetypePath);
				}
			}
		}
	}

	return Result;
}

/**
 *
 *	@param	Commandlet							The cookpackages commandlet being run
 *	@param	StandaloneSeekfreeFilenamePairs		The package array to put them into 
 *
 *	@return	UBOOL			TRUE if successful, FALSE if failed
 */
UBOOL FSwordGameCookerHelper::CreateBossPackages(class UCookPackagesCommandlet* Commandlet, TArray<FPackageCookerInfo>& StandaloneSeekfreeFilenamePairs)
{
	warnf(NAME_Log, TEXT("SwordGame: Generating boss packages..."));
	FString CookedContentPath;
	appGetCookedContentPath(Commandlet->Platform, CookedContentPath);
	FFilename BossSaveFolder = FString::Printf(TEXT("%sGeneratedBosses"), *CookedContentPath);
	GFileManager->MakeDirectory(*BossSaveFolder);

	if (bSkipBossCommon == FALSE)
	{
		FPackageCookerInfo CookerInfo;

		// Source filename of temp package to be cooked (may be used later to find object to cook)
		CookerInfo.SrcFilename = BossHelper.GetBossCommonPackageName();
		CookerInfo.DstFilename = Commandlet->GetCookedPackageFilename(BossHelper.GetBossCommonPackageName());

		// setup flags to cook as seekfree standalone package
		CookerInfo.bShouldBeSeekFree = TRUE;
		CookerInfo.bIsNativeScriptFile = FALSE;
		CookerInfo.bIsCombinedStartupPackage = FALSE;
		CookerInfo.bIsStandaloneSeekFreePackage = TRUE;
		CookerInfo.bShouldOnlyLoad = FALSE;

		StandaloneSeekfreeFilenamePairs.AddItem(CookerInfo);

		for (INT GroupIdx = 0; GroupIdx < BossHelper.GetNumGroups(); GroupIdx++)
		{
			FString GroupName;
			if (BossHelper.GetGroupName(GroupIdx, GroupName) == TRUE)
			{
				CookerInfo.SrcFilename = GroupName;
				CookerInfo.DstFilename = Commandlet->GetCookedPackageFilename(GroupName);
				// setup flags to cook as seekfree standalone package
				CookerInfo.bShouldBeSeekFree = TRUE;
				CookerInfo.bIsNativeScriptFile = FALSE;
				CookerInfo.bIsCombinedStartupPackage = FALSE;
				CookerInfo.bIsStandaloneSeekFreePackage = TRUE;
				CookerInfo.bShouldOnlyLoad = FALSE;
				StandaloneSeekfreeFilenamePairs.AddItem(CookerInfo);
			}
		}
	}

	for (INT BossIdx = 0; BossIdx < BossPackageNames.Num(); BossIdx++)
	{
		FFilename Filename = BossPackageNames(BossIdx);

		UPackage* BossPackage = NULL;
		if (bSkipBossCommon == FALSE)
		{
			BossPackage = CreateBossPackage(Commandlet, Filename, TRUE);
		}

		if ((bSkipBossCommon == TRUE) || (BossPackage != NULL))
		{
			// Only cook the bosses actually found in maps
			if (BossPackageNamesFromMaps.FindItemIndex(Filename) != INDEX_NONE)
			{
				// Comment this in to actually generate physical packages... debugging only
//				ULinkerLoad* Linker = BossPackage->GetLinker();
// 				FFilename BossSaveFilename = 
// 					FString::Printf(TEXT("%s\\%s.upk"), *BossSaveFolder, *(BossPackage->GetName()));
// 				UObject::SavePackage(BossPackage, NULL, RF_Standalone, *BossSaveFilename, GWarn);

				FPackageCookerInfo CookerInfo;

				// Source filename of temp package to be cooked (may be used later to find object to cook)
				CookerInfo.SrcFilename = Filename;
				// Destination filename for cooked seekfree package (must be derived from the SrcFilename)
				CookerInfo.DstFilename = Commandlet->GetCookedPackageFilename(Filename);

				// setup flags to cook as seekfree standalone package
				CookerInfo.bShouldBeSeekFree = TRUE;
				CookerInfo.bIsNativeScriptFile = FALSE;
				CookerInfo.bIsCombinedStartupPackage = FALSE;
				CookerInfo.bIsStandaloneSeekFreePackage = TRUE;
				CookerInfo.bShouldOnlyLoad = FALSE;

				StandaloneSeekfreeFilenamePairs.AddItem(CookerInfo);
			}
		}

		if (bSkipBossCommon == FALSE)
		{
			UObject::CollectGarbage(RF_Native);
		}
	}

	if (bSkipBossCommon == FALSE)
	{
		INT NumObjectsSharedByAll = 0;
		INT NumObjectsSharedBySome = 0;

		// Fill in BossCommonPackageObjects
		warnf(NAME_Log, TEXT("Filling in BossCommon object map..."));
		INT BossGroupCount = BossHelper.GetNumGroups();
		TArray<FString> GroupNames;
		TArray<TArray<FString> > GroupPackageNames;
		for (INT GroupIdx = 0; GroupIdx < BossGroupCount; GroupIdx++)
		{
			FString GroupName;
			BossHelper.GetGroupName(GroupIdx, GroupName);
			GroupNames.AddItem(GroupName);
			TArray<FString> LocalGroupPackages;
			BossHelper.GetGroup(GroupIdx, LocalGroupPackages);
			GroupPackageNames.AddItem(LocalGroupPackages);
		}

		FLOAT BossPackageCount = (FLOAT)(BossPackageNames.Num());
		for (TMap<FString, TArray<FString> >::TIterator CheckBossIt(BossPackageObjects); CheckBossIt; ++CheckBossIt)
		{
			FString ObjName = CheckBossIt.Key();
			TArray<FString>& ObjToPkgMap = CheckBossIt.Value();
			FLOAT Percentage = (FLOAT)(ObjToPkgMap.Num()) / BossPackageCount;
			if (Percentage >= BossCommonPercentage)
			{
				if (bShowBossPackageDetails)
				{
					warnf(NAME_Log, TEXT("\t%5.2f - %s"), Percentage, *ObjName);
				}
				BossCommonPackageObjects.Set(ObjName, Percentage);

				if (Percentage < 1.f)
					NumObjectsSharedBySome++;
				else
					NumObjectsSharedByAll++;
			}

			// We also need to fill in a GROUP obj mapping...
			for (INT GroupIdx = 0; GroupIdx < BossGroupCount; GroupIdx++)
			{
				TArray<FString>& GroupPackages = GroupPackageNames(GroupIdx);
				UBOOL bInAllGroupPackages = TRUE;
				for (INT PkgIdx = 0; PkgIdx < GroupPackages.Num(); PkgIdx++)
				{
					if (ObjToPkgMap.FindItemIndex(GroupPackages(PkgIdx)) == INDEX_NONE)
					{
						bInAllGroupPackages = FALSE;
						break;
					}
				}

				if (bInAllGroupPackages == TRUE)
				{
					FString& GroupName = GroupNames(GroupIdx);
					TMap<FString,UBOOL>* GroupObjMap = BossGroupPackageObjects.Find(GroupName);
					if (GroupObjMap == NULL)
					{
						TMap<FString,UBOOL> TempGroupObjMap;
						BossGroupPackageObjects.Set(GroupName, TempGroupObjMap);
						GroupObjMap = BossGroupPackageObjects.Find(GroupName);
					}
					check(GroupObjMap);
					GroupObjMap->Set(ObjName, TRUE);
				}
			}
		}

		warnf(NAME_Log, TEXT("\t%d objects are shared by all the Boss packages."), NumObjectsSharedByAll);
		warnf(NAME_Log, TEXT("\t%d objects are shared by over %.1f percent of the Boss packages."), NumObjectsSharedBySome, BossCommonPercentage * 100.f);

		if (bShowBossPackageDetails)
		{
			warnf(NAME_Log, TEXT("**********"));
			warnf(NAME_Log, TEXT("Boss groups..."));
			for (TMap<FString, TMap<FString,UBOOL> >::TIterator DumpIt(BossGroupPackageObjects); DumpIt; ++DumpIt)
			{
				FString& GroupName = DumpIt.Key();
				TMap<FString,UBOOL>& GroupContents = DumpIt.Value();
				warnf(NAME_Log, TEXT("\t%s"), *GroupName);
				for (TMap<FString,UBOOL>::TIterator ContentsIt(GroupContents); ContentsIt; ++ContentsIt)
				{
					FString& ObjName = ContentsIt.Key();
					warnf(NAME_Log, TEXT("\t\t%s"), *ObjName);
				}
			}
		}
	}

	return TRUE;
}

/**
 *
 *	@param	Commandlet				The cookpackages commandlet being run
 *	@param	BossFilename			The filename of the Boss package
 *
 *	@return	UPackage*				The boss package, NULL if failed.
 */
UPackage* FSwordGameCookerHelper::CreateBossPackage(class UCookPackagesCommandlet* Commandlet, FFilename& BossFilename, UBOOL bFillObjMap)
{
	UPackage* Result = NULL;
	FString BaseFilename = FFilename(BossFilename).GetBaseFilename();
	// check if it's a boss character package
	if (BaseFilename.StartsWith(BOSS_CHARACTER_PACKAGE_PREFIX))
	{
		if (BossFilename.StartsWith(TEXT("BOSS_GROUP_")) == TRUE)
		{
			if (bSkipBossCommon == FALSE)
			{
				// Create a package for this boss and all its data
				BaseFilename = BossFilename;
				warnf(NAME_Log, TEXT("Generating BOSS GROUP package %s"), *BaseFilename);

				TMap<FString,UBOOL>* GroupPkgObjs = BossGroupPackageObjects.Find(BaseFilename);
				if (GroupPkgObjs != NULL)
				{
					// create the package and object that will hold the references
					Result = UObject::CreatePackage(NULL, *BaseFilename);
					UObjectReferencer* RefHolder = ConstructObject<UObjectReferencer>(UObjectReferencer::StaticClass(), Result, FName(TEXT("Referencer")));
					RefHolder->SetFlags(RF_Standalone);
					for (TMap<FString,UBOOL>::TIterator GroupIt(*GroupPkgObjs); GroupIt; ++GroupIt)
					{
						// Parse the class name off
						FString ObjName = GroupIt.Key();
						INT SpaceIndex = ObjName.InStr(TEXT(" "));
						FString ObjClassName = ObjName.Left(SpaceIndex);
						FString ObjPathName = ObjName.Right(ObjName.Len() - SpaceIndex - 1);

						debugf(TEXT("Loading BOSS GROUP object %s '%s'"), *ObjClassName, *ObjPathName);

						UClass* ObjClass = (UClass*)(UObject::StaticFindObject(UClass::StaticClass(), ANY_PACKAGE, *ObjClassName, TRUE));
						if (ObjClass != NULL)
						{
							UObject* Obj = UObject::StaticLoadObject(ObjClass, NULL, *ObjPathName, NULL, LOAD_None, NULL);
							if (Obj != NULL)
							{
								// Save the object in the package (along with everything it references)
								RefHolder->ReferencedObjects.AddItem(Obj);
							}
							else
							{
								warnf(NAME_Warning, TEXT("\tFailed to load object %s"), *ObjPathName);
							}
						}
						else
						{
							warnf(NAME_Warning, TEXT("\tFailed to find class %s"), *ObjClassName);
						}
					}
				}
				else
				{
					warnf(NAME_Warning, TEXT("\tFailed to find GROUP %s"), *BaseFilename);
				}
			}
		}
		else if (BossFilename.InStr(BossHelper.GetBossCommonPackageName()) == INDEX_NONE)
		{
			// Create a package for this boss and all its data
			BaseFilename = BossFilename;
			FString ArchetypePath = BaseFilename.Right(BaseFilename.Len() - appStrlen(BOSS_CHARACTER_PACKAGE_PREFIX));
			FString NewFilename = FString::Printf(BOSS_CHARACTER_PACKAGE_PREFIX TEXT("%s"), *ArchetypePath.Right(ArchetypePath.Len() - ArchetypePath.InStr(TEXT("."), TRUE) - 1) );
			debugf(TEXT("Loading boss archetype %s to create package %s"), *ArchetypePath, *NewFilename);
			ASwordPawn* BossArchetype = LoadObject<ASwordPawn>( NULL, *ArchetypePath, NULL, LOAD_NoWarn | LOAD_Quiet, NULL );
			if( BossArchetype != NULL )
			{
				// create the package and object that will hold the references
				Result = UObject::CreatePackage(NULL, *NewFilename);
				UObjectReferencer* RefHolder = ConstructObject<UObjectReferencer>(UObjectReferencer::StaticClass(), Result, FName(TEXT("Referencer")));
				RefHolder->SetFlags(RF_Standalone);

				// Save the archetype in the package (along with everything it references)
				RefHolder->ReferencedObjects.AddItem(BossArchetype);

				// Point the archetype to the defaults in order to get rid of unnecessary archetype objects (and everything they reference)
				if( BossArchetype->GetArchetype() != BossArchetype->GetClass()->GetDefaultObject() )
				{
					UObject* OldParent = BossArchetype->GetArchetype();
					BossArchetype->SetArchetype(BossArchetype->GetClass()->GetDefaultObject(),FALSE);
					for( INT i=0; i<BossArchetype->Components.Num(); i++ )
					{
						UComponent* Comp = BossArchetype->Components(i);
						if( Comp )
						{
							UComponent* RealArchetype = Comp->ResolveSourceDefaultObject();
							if ( RealArchetype != NULL )
							{
								Comp->SetArchetype(RealArchetype,FALSE);
							}
							else
							{
								Comp->SetArchetype(Comp->GetClass()->GetDefaultObject(),FALSE);
							}
						}
					}

					TMap<FString,UBOOL>* BossSkipObjectsMap = NULL;
					if (bSkipBossCommon == FALSE)
					{
						BossSkipObjectsMap = BossPackageSkipObjectMaps.Find(BossFilename);
						if (bFillObjMap == TRUE)
						{
							if (BossSkipObjectsMap == NULL)
							{
								TMap<FString,UBOOL> TempBossSkipObjectsMap;
								BossPackageSkipObjectMaps.Set(BossFilename, TempBossSkipObjectsMap);
								BossSkipObjectsMap = BossPackageSkipObjectMaps.Find(BossFilename);
							}
						}
						check(BossSkipObjectsMap);
					}

					// Get rid of everything that may have been referenced by the archetypes
					TArray<UObject*> ReferencedObjects;
					RecursiveObjectCollection(BossArchetype, 0, 5, ReferencedObjects);
					TArray<UObject*> OldReferencedObjects;
					RecursiveObjectCollection(OldParent, 0, 5, OldReferencedObjects);
					for( INT i=0; i<OldReferencedObjects.Num(); i++ )
					{
						UObject* Obj = OldReferencedObjects(i);
						if( !Obj->HasAnyFlags(RF_ClassDefaultObject|RF_Transient) )
						{
							if (!ReferencedObjects.ContainsItem(Obj))
							{
								if (bSkipBossCommon == FALSE)
								{
									if (bFillObjMap == TRUE)
									{
										BossSkipObjectsMap->Set(Obj->GetFullName(), TRUE);
									}
								}
								Obj->ClearFlags(RF_ForceTagExp);
								Obj->SetFlags(RF_MarkedByCooker);
							}
						}
					}

					if (bSkipBossCommon == FALSE)
					{
						if (bFillObjMap == TRUE)
						{
							// If we are creating the packages just for common object determination,
							// fill the BossPackageObjects list...
							for (INT RefIdx = 0; RefIdx < ReferencedObjects.Num(); RefIdx++)
							{
								UObject* RefObj = ReferencedObjects(RefIdx);
								FString RefObjName = RefObj->GetFullName();
								if (
									//(RefObj->IsA(UClass::StaticClass()) == FALSE) &&
									//(RefObj->IsA(UPackage::StaticClass()) == FALSE) &&
									!RefObj->HasAnyFlags(RF_ClassDefaultObject|RF_Transient))
								{
									TArray<FString>* BossPackageList = BossPackageObjects.Find(RefObjName);
									if (BossPackageList == NULL)
									{
										TArray<FString> TempBossPackageList;
										BossPackageObjects.Set(RefObjName, TempBossPackageList);
										BossPackageList = BossPackageObjects.Find(RefObjName);
									}
									check(BossPackageList);
									BossPackageList->AddUniqueItem(BaseFilename);
								}
							}
						}
					}
				}
			}
			else
			{
				warnf(NAME_Warning, TEXT("   *Failed to load boss archetype %s"), *ArchetypePath);
			}
		}
		else
		{
			if (bSkipBossCommon == FALSE)
			{
				// Create a package for this boss and all its data
				BaseFilename = BossFilename;
				warnf(NAME_Log, TEXT("Generating BOSS package %s"), *BaseFilename);
				// create the package and object that will hold the references
				Result = UObject::CreatePackage(NULL, *BaseFilename);
				UObjectReferencer* RefHolder = ConstructObject<UObjectReferencer>(UObjectReferencer::StaticClass(), Result, FName(TEXT("Referencer")));
				RefHolder->SetFlags(RF_Standalone);
				for (TMap<FString,FLOAT>::TIterator BossIt(BossCommonPackageObjects); BossIt; ++BossIt)
				{
					// Parse the class name off
					FString ObjName = BossIt.Key();
					INT SpaceIndex = ObjName.InStr(TEXT(" "));
					FString ObjClassName = ObjName.Left(SpaceIndex);
					FString ObjPathName = ObjName.Right(ObjName.Len() - SpaceIndex - 1);

					//warnf(NAME_Log, TEXT("Loading BOSS_COMMON object %s '%s'"), *ObjClassName, *ObjPathName);

					UClass* ObjClass = (UClass*)(UObject::StaticFindObject(UClass::StaticClass(), ANY_PACKAGE, *ObjClassName, TRUE));
					if (ObjClass != NULL)
					{
						UObject* Obj = UObject::StaticLoadObject(ObjClass, NULL, *ObjPathName, NULL, LOAD_None, NULL);
						if (Obj != NULL)
						{
							// Save the object in the package (along with everything it references)
							RefHolder->ReferencedObjects.AddItem(Obj);
						}
						else
						{
							warnf(NAME_Warning, TEXT("\tFailed to load object %s"), *ObjPathName);
						}
					}
					else
					{
						warnf(NAME_Warning, TEXT("\tFailed to find class %s"), *ObjClassName);
					}
				}
			}
		}
	}
	return Result;
}
