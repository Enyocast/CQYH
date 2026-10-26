/*=============================================================================
	SwordCommandlets.cpp: Various commmandlets.
	Copyright 1998-2010 Epic Games, Inc. All Rights Reserved.
=============================================================================*/

#include "UnrealEd.h"
#include "PackageHelperFunctions.h"
#include "SwordGame.h"
#include "SwordCommandlets.h"
#include "Factories.h"
#include "Editor.h"
#include "UnObjectTools.h"
#include "UnPackageTools.h"
#include "UnString.h"

#include "ImageUtils.h"

#if WITH_EDITOR
#include "SourceControl.h"
#endif // #if WITH_EDITOR


static UBOOL bAllowNonPowerOfTwo;

IMPLEMENT_CLASS(UCheckItemsCommandlet);
IMPLEMENT_CLASS(UMakeIconPageCommandlet);
IMPLEMENT_CLASS(USplitIconPageCommandlet);

void VerifyInventory(const TArray<class USwordInventoryItem*> &Inventory, TArray<FString> &MeshPackages, TArray<FString> &IconPackages)
{
	// Verify all the inventory paths are valid
	for( INT i = 0; i < Inventory.Num(); i++ )
	{
		USwordInventoryItem* Item = Inventory(i);
		check(Item);

		// Try to load the mesh
		//FString PackageName = Item->MeshPath.Left( Item->MeshPath.InStr(TEXT(".")) );
		//UPackage* Package = UObject::LoadPackage( NULL, *PackageName, 0 );
		UObject* Mesh = NULL;
		if( Item->MeshPath.Len() && Item->eventShouldLoadMesh() )
		{
			Mesh = UObject::StaticLoadObject(USkeletalMesh::StaticClass(), NULL, *Item->MeshPath, NULL, LOAD_None, NULL);
			if( Mesh == NULL )
			{
				warnf(NAME_Warning, TEXT("Inventory item '%s' has invalid MeshPath '%s'"), *Item->GetName(), *Item->MeshPath);
			}
			else if( Mesh->GetPathName() != Item->MeshPath )
			{
				warnf(NAME_Warning, TEXT("Inventory item '%s' has invalid MeshPath '%s' - should be '%s'"), *Item->GetName(), *Item->MeshPath, *Mesh->GetPathName());
			}
		}
		else
		{
			if( Item->MeshPath.Len() && !Item->eventShouldLoadMesh() )
			{
				warnf(NAME_Warning, TEXT("Inventory item '%s' does not use a mesh and should not have any MeshPath"), *Item->GetName());
			}
			else if( Item->eventShouldLoadMesh() )
			{
				warnf(NAME_Warning, TEXT("Inventory item '%s' needs to have a MeshPath"), *Item->GetName(), *Item->MeshPath);
			}
		}

		// Try to load the icon
		UObject* Icon = NULL;
		if( Item->IconPath.Len() && Item->eventShouldLoadIcon() )
		{
			Icon = UObject::StaticLoadObject(UTexture2D::StaticClass(), NULL, *Item->IconPath, NULL, LOAD_None, NULL);
			if( Icon == NULL )
			{
				warnf(NAME_Warning, TEXT("Inventory item '%s' has invalid IconPath '%s'"), *Item->GetName(), *Item->IconPath);
			}
			else if( Icon->GetPathName() != Item->IconPath )
			{
				warnf(NAME_Warning, TEXT("Inventory item '%s' has invalid IconPath '%s' - should be '%s'"), *Item->GetName(), *Item->IconPath, *Icon->GetPathName());
			}
		}
		else
		{
			if( Item->eventShouldLoadIcon() )
			{
				warnf(NAME_Warning, TEXT("Inventory item '%s' needs to have an IconPath"), *Item->GetName());
			}
		}

		if( (Icon || !Item->eventShouldLoadIcon()) && (Mesh || !Item->eventShouldLoadMesh()) )
		{
			warnf(NAME_Log, TEXT("Inventory item '%s' valid"), *Item->GetName());

			if( Icon )
			{
				IconPackages.AddUniqueItem(Icon->GetOutermost()->GetName());
			}

			if( Mesh )
			{
				MeshPackages.AddUniqueItem(Mesh->GetOutermost()->GetName());
			}
		}
	}
}

UBOOL VerifyInventoryItem(const TArray<class USwordInventoryItem*> &Inventory, TArray<FString> &MeshPackages, ASwordPawn* Pawn, const TCHAR* PropertyName, const TCHAR* IniFileName)
{
	if( Pawn != NULL )
	{
		UProperty* Property = FindField<UProperty>(Pawn->GetClass(), PropertyName);
		if( Property != NULL )
		{
			BYTE* BaseData = (BYTE*)Pawn + Property->Offset;
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

			for( INT PropIdx=0; PropIdx < ElementCount; PropIdx++ )
			{
				FName* NamePtr = (FName*)(BaseData + PropIdx * ExportProperty->ElementSize);
				FName ItemName = *NamePtr;

				for( INT i = 0; i < Inventory.Num(); i++ )
				{
					USwordInventoryItem* Item = Inventory(i);
					if( Item->GetFName() == ItemName )
					{
						FString PackageName;
						if( Item->MeshPath.Split(TEXT("."),&PackageName,NULL) )
							MeshPackages.AddUniqueItem(PackageName);
						return TRUE;
					}
				}

				warnf(NAME_Warning, TEXT("Could not find item '%s' referenced by %s.%s in %s"), *ItemName.ToString(), *Pawn->GetName(), PropertyName, IniFileName);
			}
		}
	}

	return FALSE;
}

INT UCheckItemsCommandlet::Main( const FString& Params )
{
	TArray<FString> MeshPackages, MeshPackagesMP;
	TArray<FString> IconPackages, IconPackagesMP;

	TArray<class USwordInventoryItem*> Inventory, InventoryGems, InventoryMP, InventorySP;	
	USwordEngine* SwordEngine = (USwordEngine*)(USwordEngine::StaticClass()->GetDefaultObject());

	// Load and check the single-player inventory (Items, Gems)
	SwordEngine->PopulateSwordInventoryItems(USwordInventoryItem::StaticClass(), Inventory);
	VerifyInventory(Inventory, MeshPackages, IconPackages);
	SwordEngine->PopulateSwordInventoryItems(USwordInventoryConsumable::StaticClass(), InventoryGems);
	VerifyInventory(InventoryGems, MeshPackages, IconPackages);

	// Load and check the multi-player inventory
	SwordEngine->PopulateSwordInventoryItems(USwordInventoryMPItem::StaticClass(), InventoryMP);
	VerifyInventory(InventoryMP, MeshPackagesMP, IconPackagesMP);

	// Load and check the survival inventory
	SwordEngine->PopulateSwordInventoryItems(USwordInventorySPItem::StaticClass(), InventorySP);
	VerifyInventory(InventorySP, MeshPackagesMP, IconPackagesMP);

	// Get the player pawn and see what is referenced there
	ASwordGame* Game = (ASwordGame*)(ASwordGame::StaticClass()->GetDefaultObject());
	ASwordPawn* Pawn = Cast<ASwordPawn>(Game->DefaultPawnArchetype);

	if( Pawn != NULL )
	{
		VerifyInventoryItem(Inventory, MeshPackagesMP, Pawn, TEXT("EquippedItemNames"), TEXT("DefaultItems.ini"));
		VerifyInventoryItem(Inventory, MeshPackagesMP, Pawn, TEXT("DarkSword"), TEXT("DefaultItems.ini"));
		VerifyInventoryItem(Inventory, MeshPackagesMP, Pawn, TEXT("DarkShield"), TEXT("DefaultItems.ini"));
		VerifyInventoryItem(Inventory, MeshPackagesMP, Pawn, TEXT("DarkArmor"), TEXT("DefaultItems.ini"));
		VerifyInventoryItem(Inventory, MeshPackagesMP, Pawn, TEXT("DarkHelmet"), TEXT("DefaultItems.ini"));
		VerifyInventoryItem(Inventory, MeshPackagesMP, Pawn, TEXT("DarkMagic"), TEXT("DefaultItems.ini"));

		VerifyInventoryItem(InventoryMP, MeshPackagesMP, Pawn, TEXT("MultiplayerStartingItemNames"), TEXT("DefaultItemsMP.ini"));

		VerifyInventoryItem(InventorySP, MeshPackagesMP, Pawn, TEXT("SurvialStartingItemNames"), TEXT("DefaultItemsSP.ini"));
	}

	if( ParseParam(*Params, TEXT("PrintPackages")) )
	{
		warnf(NAME_Log, TEXT("\nPackages used for Inventory"));
		warnf(NAME_Log, TEXT("------------------------------------"));
		for( INT i=0; i<IconPackages.Num(); i++ )
		{
			warnf(NAME_Log, TEXT("+Package=%s"), *IconPackages(i));
		}
		for( INT i=0; i<MeshPackages.Num(); i++ )
		{
			warnf(NAME_Log, TEXT("+Package=%s"), *MeshPackages(i));
		}

		warnf(NAME_Log, TEXT("\nPackages used for shared MP Inventory (Arena & Survivor)"));
		warnf(NAME_Log, TEXT("------------------------------------"));
		for( INT i=0; i<IconPackagesMP.Num(); i++ )
		{
			warnf(NAME_Log, TEXT("+Package=%s"), *IconPackagesMP(i));
		}
		for( INT i=0; i<MeshPackagesMP.Num(); i++ )
		{
			warnf(NAME_Log, TEXT("+Package=%s"), *MeshPackagesMP(i));
		}

		warnf(NAME_Log, TEXT("\nNon-Shared Inventory Packages"));
		warnf(NAME_Log, TEXT("------------------------------------"));
		for( INT i=0; i<MeshPackages.Num(); i++ )
		{
			if( !MeshPackagesMP.ContainsItem(MeshPackages(i)) )
			{
				warnf(NAME_Log, TEXT("+Package=%s"), *MeshPackages(i));
			}
		}
	}

	return 0;
}


////////////////////////////////////////////////////////////////////////////////////////////
// Loop though textures in a directory and create one or more texture pages
// and output data to INI file.  Data can also be saved to game package and INI.
////////////////////////////////////////////////////////////////////////////////////////////
INT UMakeIconPageCommandlet::Main( const FString& Params )
{
#if HAVE_SCC
	FSourceControl::Init();
#endif

	// Allow non-power of two textures during icon import
	bAllowNonPowerOfTwo = FALSE;
	GConfig->GetBool( TEXT("TextureImporter"), TEXT("AllowNonPowerOfTwoTextures"), bAllowNonPowerOfTwo, GEditorIni );
	GConfig->SetBool( TEXT("TextureImporter"), TEXT("AllowNonPowerOfTwoTextures"), TRUE, GEditorIni );

	FString ClassName;
	IconPage = NULL;
	IconPageClass = NULL;
	if (!Parse(*Params, TEXT("Class="), ClassName))
	{
		ClassName = TEXT("SwordIcons");
	}

	if (!UseIconPageClass(ClassName))
	{
		Close();
		return 1;
	}

	warnf(NAME_Log, TEXT("Building standalone icon pages for [%s]."), *IconPageClass->GetName());
	FString ConfigName = IconPage->GetClass()->GetConfigName();

	// Read in the default settings from the DefaultIcons.ini file
	FString BuildCommandLine = GConfig->GetStr(TEXT("MainAtlasSettings"), TEXT("BuildCommandLine"), *ConfigName);
	TArray<FString> Keys;
	BuildCommandLine.ParseIntoArray(&Keys, TEXT(" "), false);

	FString DefaultSettings;
	for (INT KeyIdx = 0; KeyIdx < Keys.Num(); KeyIdx++)
	{
		DefaultSettings += GConfig->GetStr(TEXT("MainAtlasSettings"), *Keys(KeyIdx), *ConfigName) + TEXT(" ");
	}
	FString CommandLine = Params + TEXT(" ") + DefaultSettings + TEXT(" ");
	TArray<FString> IconPages;
	GConfig->GetArray(TEXT("MainAtlasSettings"), TEXT("IconPages"), IconPages, *ConfigName);

	IconPage->Icons.Empty();
	for (INT PageIdx = 0; PageIdx < IconPages.Num(); PageIdx++)
	{
		TArray<FString> PageSources;
		GConfig->GetArray(*IconPages(PageIdx), TEXT("Source"), PageSources, *ConfigName);

		// Moved this outside of ImportTextures() because it was getting reset
		// and causing Min/Max to get set to too large when there are multiple
		// source directories.
		MinWidth = MAXINT;
		MinHeight = MAXINT;

		// Import all the textures for this page from various source directories
		for (INT SourceIdx = 0; SourceIdx < PageSources.Num(); SourceIdx++)
		{
			if (!Init(CommandLine, PageSources(SourceIdx)))
			{
				warnf(NAME_Error, TEXT("Error in command line arguments!"));
				Close();
				return 1;
			}
			if (!ImportTextures())
			{
				warnf(NAME_Error, TEXT("Error Importing textures!"));
				Close();
				return 1;
			}
		}

		// Add border
		MinWidth += BorderSize;
		MinHeight += BorderSize;

		// Calculate the atlas and create the textures
		if (!Make(CommandLine, IconPages(PageIdx)))
		{
			warnf(NAME_Error, TEXT("Make failed with %s"), *SourcePath);
			Close();
			return 1;
		}
	}

	if (bSavePagesInPackage)
	{
		// Now save INI data.
		FString ConfigName = appGameConfigDir() + TEXT("Default") + IconPageClass->ClassConfigName.ToString() + TEXT(".ini");
		ConfigName = appConvertRelativePathToFull(ConfigName);
		warnf( NAME_Log, TEXT("Saving Class Config:  [%s]."), *ConfigName );
#if HAVE_SCC
		TArray<FString> NameArray;
		NameArray.AddItem(ConfigName);
		FSourceControl::CheckOut(NULL, NameArray, TRUE);
#endif
		FString Unused;
		GPackageFileCache->SplitPath( *RootPackageFileName, Unused, IconPage->PackageName, Unused );
		// Save the default config file
		IconPage->SaveConfig(CPF_Config, *ConfigName);
		// Save the game derived config file as well
		IconPage->SaveConfig(CPF_Config);
		warnf( NAME_Log, TEXT("\tDone!\n"));
	}

	warnf( NAME_Log, TEXT("MakeIconPage has completed!"));
	Close();
	return 0;
}

void UMakeIconPageCommandlet::Close()
{
	// Set bAllowNonPowerOfTwo back to normal
	GConfig->SetBool( TEXT("TextureImporter"), TEXT("AllowNonPowerOfTwoTextures"), bAllowNonPowerOfTwo, GEditorIni );

#if HAVE_SCC
	FSourceControl::Close();
#endif
}

/* Specify IconPage class to define make and ini file to save results in */
UBOOL UMakeIconPageCommandlet::UseIconPageClass(const FString& ClassName)
{
	warnf(NAME_Log, TEXT("Creating IconPage for %s"), *ClassName);
	IconPageClass = FindObject<UClass>(ANY_PACKAGE, *ClassName);
	if (IconPageClass == NULL)
	{
		warnf(NAME_Error, TEXT("Unable to find class %s"), *ClassName);
		return FALSE;
	}
	IconPage = Cast<UIconPage>(IconPageClass->ClassDefaultObject);
	return TRUE;
}


/** Start making after all variables are setup */
UBOOL UMakeIconPageCommandlet::Make(const FString& Params, const FString& ConfigSection)
{
	if (!Init(Params, ConfigSection))
	{
		warnf(NAME_Error, TEXT("Error in command line arguments!"));
		return FALSE;
	}

	// Find best method.
	INT BestSortTexturesBy = 0;
	INT BestSortSpacesBy = 0;

	warnf(NAME_Log, TEXT("Calculating Texture Pages..."));
	// Slow will try more combinations to see if there is a better fit - Most likely there will not be.
	if (!bFast)
	{
		INT LeastTextureSpace = MAXINT;
		for (SortTexturesBy = 0; SortTexturesBy < 2; SortTexturesBy++)
		{
			for (SortSpacesBy = 0; SortSpacesBy < 2; SortSpacesBy++)
			{
				INT TextureSpace = CalculateTexturePage();
				if (TextureSpace < LeastTextureSpace)
				{
					LeastTextureSpace = TextureSpace;
					BestSortSpacesBy = SortSpacesBy;
					BestSortTexturesBy = SortTexturesBy;
				}
			}
		}
	}

	// Do it for real now.
	SortSpacesBy = BestSortSpacesBy ;
	SortTexturesBy = BestSortTexturesBy;
	CalculateTexturePage();
	warnf(NAME_Log, TEXT("Done!\n"));

	MakeIconPages();
	SaveIni();
	SavePackage();

	// Clean up textures in case this is called again with new data.
	Textures.Empty(Textures.Num() + Textures.GetSlack());

	return TRUE;
}

namespace
{
	INT ParamToNum(const FString & Num)
	{
		INT Ret;

		if (Num.InStr("0x", FALSE, TRUE) >= 0)
			appSSCANF(*Num, TEXT("%x"), &Ret);
		else
			Ret = appAtoi(*Num);
		return Ret;
	}
}

/* Each make is re-initialized */
UBOOL UMakeIconPageCommandlet::Init(const FString& CommandLine, const FString& ConfigSection)
{
	FString SectionSettings = CommandLine + GConfig->GetStr(*ConfigSection, TEXT("Settings"), *IconPage->GetClass()->GetConfigName());

	GConfig->GetArray(*ConfigSection, TEXT("PerIconSetting"), PerIconSettings, *IconPage->GetClass()->GetConfigName());

	return Init(SectionSettings, FALSE);
}

UBOOL UMakeIconPageCommandlet::Init(const FString& CommandLine, UBOOL bAppendToCurrentCommandline)
{
	FString NewCommandLine = CommandLine;
	if (bAppendToCurrentCommandline)
		NewCommandLine = CurrentCommandLine + TEXT(" ") + CommandLine;
	else
		CurrentCommandLine = CommandLine;

	FString Params = NewCommandLine.Replace(TEXT("/"), TEXT("\\"));

	warnf(NAME_Log, TEXT("CommandLine:[%s]\n"), *Params);
	if (TextureFactory == NULL)
	{
		TextureFactory = ConstructObject<UTextureFactory>(UTextureFactory::StaticClass());
		TextureFactory->Blending = BLEND_Opaque;
		TextureFactory->LightingModel = MLM_Unlit;
		TextureFactory->bDeferCompression = TRUE;
	}

	RootPackageFileName = "";
	RootPackage = NULL;
	SourcePath = "";
	bRecurseDirs = FALSE;

	bFast = FALSE;
	bSavePagesInPackage = FALSE;
	bSaveSourcePackage = FALSE;
	bCompressTexture = FALSE;

	MinTextureSize = 256;
	MaxTextureSize = 2048;
	BorderSize = 1;
	UVGutterSize = 0.f;
	TransparentColor = 0;
	InitialColor = 0;
	DefaultScale = FVector2D(1.f, 1.f);

	// Parse command line args.
	TArray<FString> Tokens;
	TArray<FString> Switches;
	ParseCommandLine(*Params, Tokens, Switches);

	for (INT Lp = 0; Lp < Tokens.Num(); Lp++)
	{
		FString Token = Tokens(Lp);
		FString ParseStr;
		FLOAT ParseFloat;
		if (Parse(*Token, TEXT("Package="), ParseStr))
		{
			FString PackageName, Unused;
			RootPackageFileName = appConvertRelativePathToFull(ParseStr);
			GPackageFileCache->SplitPath( *RootPackageFileName, Unused, PackageName, Unused );
			RootPackage = UObject::LoadPackage( NULL, *PackageName, LOAD_None);
			if (RootPackage == NULL)
			{
				warnf(NAME_Warning, TEXT("Unable to find package %s - attempting to create"), *RootPackageFileName);
				RootPackage = GEngine->CreatePackage(NULL, *PackageName);
				if (RootPackage == NULL)
				{
					warnf(NAME_Error, TEXT("Unable to create package %s"), *RootPackageFileName);
					return false;
				}
			}
			RootPackage->FullyLoad();
			bSavePagesInPackage = TRUE;
			warnf(NAME_Log, TEXT("Package=[%s]"), *RootPackageFileName);
		}
		else if (Parse(*Token, TEXT("Source="), ParseStr) || Parse(*Token, TEXT("Dest="), ParseStr))
		{
			SourcePath = ParseStr;
			if (SourcePath.EndsWith(TEXT("\\")))
			{
				SourcePath = SourcePath.Left(SourcePath.Len() - 1);
			}
			SourcePath = appConvertRelativePathToFull(SourcePath);
			warnf(NAME_Log, TEXT("Source=[%s]"), *SourcePath);
		}
		else if (Parse(*Token, TEXT("MinSize="), MinTextureSize))
		{
			warnf(NAME_Log, TEXT("MinSize=[%d]"), MinTextureSize);
		}
		else if (Parse(*Token, TEXT("MaxSize="), MaxTextureSize))
		{
			warnf(NAME_Log, TEXT("MaxSize=[%d]"), MaxTextureSize);
		}
		else if (ParseUBOOL(*Token, TEXT("Compress="), bCompressTexture))
		{
			warnf(NAME_Log, TEXT("Compress=[%d]"), bCompressTexture);
		}
		else if (Parse(*Token, TEXT("Border="), BorderSize))
		{
			warnf(NAME_Log, TEXT("Border=[%d]"), BorderSize);
		}
		else if (Parse(*Token, TEXT("Gutter="), UVGutterSize))
		{
			warnf(NAME_Log, TEXT("UVGutterSize=[%.2f]"), UVGutterSize);
		}
		else if (Parse(*Token, TEXT("InitialColor="), ParseStr))
		{
			InitialColor = ParamToNum(ParseStr);
			warnf(NAME_Log, TEXT("InitialColor=[%x]"), InitialColor);
		}
		else if (Parse(*Token, TEXT("Scale="), ParseFloat))
		{
			DefaultScale.X = ParseFloat;
			DefaultScale.Y = ParseFloat;
			warnf(NAME_Log, TEXT("DefaultScale=[%s]"), *DefaultScale.ToString());
		}
		else if (Parse(*Token, TEXT("ScaleX="), ParseFloat))
		{
			DefaultScale.X = ParseFloat;
			warnf(NAME_Log, TEXT("DefaultScale=[%s]"), *DefaultScale.ToString());
		}
		else if (Parse(*Token, TEXT("ScaleY="), ParseFloat))
		{
			DefaultScale.Y = ParseFloat;
			warnf(NAME_Log, TEXT("DefaultScale=[%s]"), *DefaultScale.ToString());
		}
		else if (Parse(*Token, TEXT("TransparentColor="), ParseStr))
		{
			TransparentColor = ParamToNum(ParseStr);
			warnf(NAME_Log, TEXT("TransparentColor=[%x]"), TransparentColor);
		}
		else if (Parse(*Token, TEXT("Class="), ParseStr))
		{
			// Handled elsewhere
			warnf(NAME_Log, TEXT("Class=[%s]"), *ParseStr);
		}
		else
		{
			warnf(NAME_Warning, TEXT("Unkown Command=[%s]"), *Token);
		}
	}

	for (INT Lp = 0; Lp < Switches.Num(); Lp++)
	{
		FString Switch = Switches(Lp);
		if (appStricmp(TEXT("Recurse"),*Switch) == 0)
		{
			bRecurseDirs = TRUE;
			warnf(NAME_Log, TEXT("Recurse=TRUE"));
		}
		else if (appStricmp(TEXT("Fast"),*Switch) == 0)
		{
			bFast = TRUE;
			warnf(NAME_Log, TEXT("Fast=TRUE"));
		}
		else if (appStricmp(TEXT("SaveSource"),*Switch) == 0)
		{
			bSaveSourcePackage = TRUE;
			warnf(NAME_Log, TEXT("SaveSource=TRUE"));
		}
		else
		{
			warnf(NAME_Warning, TEXT("Unkown Command=[%s]"), *Switch);
		}
	}

	if (RootPackage == NULL)
	{
		RootPackage = GEngine->CreatePackage(NULL, TEXT("TEMP_MakeIconPage_"));
		ImportPackage = RootPackage;
		if (bSavePagesInPackage)
		{
			warnf(NAME_Error, TEXT("-SaveSource specified without Package"));
			return FALSE;
		}
	} 
	else
	{
		if (bSaveSourcePackage)
		{
			ImportPackage = GEngine->CreatePackage(RootPackage, TEXT("MakeIconPage"));
		}
		else
		{
			ImportPackage = GEngine->CreatePackage(NULL, TEXT("TEMP_MakeIconPage_"));
		}
	}
	return TRUE;
}

/* Import source textures from SourcePath */
UBOOL UMakeIconPageCommandlet::ImportTextures()
{
	// FStrings required by AssembleListOfImportFactores.  We don't use them here.
	FString FileTypes, FileExtensions;

	warnf(NAME_Log, TEXT("Importing textures from %s - %srecursed."), *SourcePath, bRecurseDirs ? TEXT("") : TEXT("Not "));

	// Get a list of files, and ask the user if its ok to proceed with importing the files.  Last chance to back out!
	TArray<FString> FoundFiles;
	if (bRecurseDirs)
	{
		appFindFilesInDirectory(FoundFiles, *SourcePath, FALSE, TRUE);
	}
	else
	{
		FString Wildcard = SourcePath * TEXT("*.*");
		GFileManager->FindFiles(FoundFiles, *Wildcard, TRUE, FALSE);
		INT NumFiles = FoundFiles.Num();
		for (INT FileIdx = 0; FileIdx < NumFiles; FileIdx++)
		{
			FoundFiles(FileIdx) = SourcePath * FoundFiles(FileIdx);
		}
	}

	INT NumFiles = FoundFiles.Num();
	if( NumFiles == 0)
	{
		warnf(NAME_Error, TEXT("No files found in %s"), *SourcePath);
		return FALSE;
	}

	UClass* Class = TextureFactory->ResolveSupportedClass();
	UBOOL bUsedPerIconSetting = FALSE;

	GUglyHackFlags |= HACK_AllowAnySizeTextureImport;
	TextureFactory->NoCompression = TRUE;
	for (INT FileIdx = 0; FileIdx < NumFiles; FileIdx++)
	{
		const FString FullName = FoundFiles(FileIdx);
		const FFilename FileName = FullName;
		const FString FileExtension = FileName.GetExtension();
		INT NumFormats = TextureFactory->Formats.Num();
		UTexture2D* AsTexture = NULL;

		for( INT FormatIndex = 0; FormatIndex < NumFormats; FormatIndex++ )
		{
			const FString& FactoryFormat = TextureFactory->Formats(FormatIndex);
			if( FactoryFormat.Left( FileExtension.Len() ) == FileExtension )
			{
				FString TextureName = FileName.GetBaseFilename();
				TextureFactory->SuppressImportOverwriteDialog();
				UObject* Result = UFactory::StaticImportObject(Class, ImportPackage, FName( *TextureName ), RF_Public|RF_Standalone, *FullName, NULL, TextureFactory );
				AsTexture = Cast< UTexture2D >(Result);
				if (AsTexture != NULL)
				{
					OrigTexture	Orig;
					Orig.Name = FileName.GetBaseFilename();

					FString Settings;
					for( INT i=0; i<PerIconSettings.Num(); i++ )
					{
						if( PerIconSettings(i).InStr(Orig.Name + TEXT(" ")) == 0)
						{
							Settings = PerIconSettings(i).Mid(Orig.Name.Len() + 1);
							Init(Settings, TRUE);

							INT Sharpen;
							if (Parse(*PerIconSettings(i), TEXT("Sharpen="), Sharpen))
							{
								if (Sharpen >= 0)
									AsTexture->MipGenSettings = TMGS_Sharpen0 + Clamp(Sharpen, 0, (INT)TMGS_Sharpen10 - (INT)TMGS_Sharpen0);
								else
									AsTexture->MipGenSettings = TMGS_Blur1 + Clamp(Abs(Sharpen+1), 0, (INT)TMGS_Blur5 - (INT)TMGS_Blur1);
							}

							// We found this texture's settings, skip the rest
							bUsedPerIconSetting = TRUE;
							break;
						}
					}

					// Reset default if we used a PerIconSetting last time but not this time
					if( bUsedPerIconSetting && Settings.Len() == 0 )
					{
						// Calling Init like this with an empty string will reset it to the desired directory settings
						Init(Settings, TRUE);
						bUsedPerIconSetting = FALSE;
					}

					// Scale the actual texture data here too
					//AsTexture->SRGB = FALSE;
					AsTexture->bPreserveBorderA = TRUE;
					AsTexture->bPreserveBorderR = TRUE;
					AsTexture->bPreserveBorderG = TRUE;
					AsTexture->bPreserveBorderB = TRUE;
					AsTexture->ResizeTexture(DefaultScale);

					Orig.Texture = AsTexture;
					Orig.Size.X = AsTexture->SizeX;
					Orig.Size.Y = AsTexture->SizeY;
					Orig.Scale.X = 1.f / DefaultScale.X;
					Orig.Scale.Y = 1.f / DefaultScale.Y;
					Orig.Position.X = -1;
					Orig.Position.Y = -1;
					Orig.UVGutterSize = UVGutterSize;
					Orig.SetArea();
					Orig.TexturePageIdx = -1;
					Textures.Push(Orig);

					MinWidth = Min(MinWidth, Orig.Size.X);
					MinHeight = Min(MinHeight, Orig.Size.Y);
					warnf(NAME_Log, TEXT("\t%s"), *TextureName);
					break;
				}
			}
		}
		if (AsTexture == NULL)
		{
			warnf(NAME_Warning, TEXT("\tUnable to import file:%s"), *FullName);
		}
	}
	GUglyHackFlags &= ~HACK_AllowAnySizeTextureImport;
	TextureFactory->NoCompression = FALSE;

	warnf(NAME_Log, TEXT("Done!\n"));

	return Textures.Num() > 0;
}

/* Calculate what texture pages to create and where to put icons */
INT UMakeIconPageCommandlet::CalculateTexturePage()
{
	FreeSpaces.Empty(FreeSpaces.Num() + FreeSpaces.GetSlack());
	Pages.Empty(Pages.Num());
	SortTextures();

	for (INT TextureIdx = 0; TextureIdx < Textures.Num(); TextureIdx++)
	{
		OrigTexture & Texture = Textures(TextureIdx);

		// FreeSpaces can get very big, so quickly do binary search to skip over spaces that will not work.
		INT FreeIdx = 0;
		INT First = 0, Last = FreeSpaces.Num() - 1;
		while (First <= Last)
		{
			FreeIdx = (First + Last) / 2;
			FreeSpace& Space = FreeSpaces(FreeIdx);
			if (Texture.Area > Space.Area)
				First = FreeIdx + 1;
			else if (Texture.Area < Space.Area)
				Last = FreeIdx - 1;
			else
				break;
		}

		UBOOL bSpaceFound = FALSE;
		for (; FreeIdx < FreeSpaces.Num(); FreeIdx++)
		{
			FreeSpace& Space = FreeSpaces(FreeIdx);
			if (Space.Area >= Texture.Area)
			{
				TexturePage& Page = Pages(Space.TexturePageIdx);
				INT TexWidth = Texture.Size.X;
				INT TextHeight = Texture.Size.Y;

				// If space not on right/bottom, we need to add the border as well.
				if ((Space.Position.X + TexWidth) < Page.Size)
				{
					TexWidth += BorderSize;
				}
				if ((Space.Position.Y + TextHeight) < Page.Size)
				{
					TextHeight += BorderSize;
				}

				if ((Space.Size.X >= TexWidth) && (Space.Size.Y >= TextHeight))
				{
					bSpaceFound = true;
					AddTextureToSpace(Texture, Space);
					break;
				}
			}
		}

		// If no location was found, add a new texture page.  
		if (!bSpaceFound)
		{
			// If, after adding a new page, there are 4 texture pages with the same size but smaller that MaxTextureSize,
			// combine pages those and start over again.
			// Returns false if 4 pages were turned into 1 vs a new page really being added.
			if (AddNewPage(Texture.Size.X, Texture.Size.Y))
			{
				// Now add the same texture again...it should fit.
				TextureIdx--;
			}
			else
			{
				// If a new page was not added (it was instead combined) start over.
				TextureIdx = -1;
			}
		}
	}

	INT SpaceUsed = 0;
	for (INT PageIdx = 0; PageIdx < Pages.Num(); PageIdx++)
	{
		TexturePage &Page = Pages(PageIdx);
		SpaceUsed += Square(Page.Size);
	}
	return SpaceUsed;
}

/*
 * Add a new texture page, but, after adding it, if there are 4 texture pages this size,
 * remove the other three and make this one 4x the size (2x per dimension).  
 * False is returned if texture pages were removed.
 */
UBOOL UMakeIconPageCommandlet::AddNewPage(INT TextureW, INT TextureH)
{
	INT PageSize = Max(MinTextureSize, Max(TextureW, TextureH));;
	PageSize = appRoundUpToPowerOfTwo(PageSize);

	UBOOL AddedSameSizePage = TRUE;
	if ((Pages.Num() >= 3) && (PageSize < MaxTextureSize))
	{
		TArray<INT>	SameSizePages;

		for (INT PageIdx = 0; PageIdx < Pages.Num(); PageIdx++)
		{
			TexturePage &Page = Pages(PageIdx);
			if (Page.Size == PageSize)
			{
				SameSizePages.AddItem(PageIdx);
			}
		}

		// Already 3 of same size, can we add a 4th and make it one page?
		if (SameSizePages.Num() == 3)
		{
			while (SameSizePages.Num() > 0)
			{
				Pages.Remove(SameSizePages.Pop());
			}
			PageSize *= 2;
			AddedSameSizePage = FALSE;
		}
	}

	TexturePage NewPage;
	NewPage.Size = PageSize;
	Pages.AddItem(NewPage);

	if (!AddedSameSizePage)
	{
		// Rebuild all pages -- and all free spaces since we will start over.
		FreeSpaces.Empty(FreeSpaces.Num() + FreeSpaces.GetSlack());
		for (INT PageIdx = 0; PageIdx < Pages.Num(); PageIdx++)
		{
			TexturePage &Page = Pages(PageIdx);
			
			FreeSpace NewSpace;
			NewSpace.Position.X = 0;
			NewSpace.Position.Y = 0;
			NewSpace.Size.X = Page.Size;
			NewSpace.Size.Y = Page.Size;
			NewSpace.SetArea();
			NewSpace.TexturePageIdx = PageIdx;
			FreeSpaces.AddItem(NewSpace);
		}
	}
	else
	{
		// Just add new space for the new page.
		FreeSpace NewSpace;
		NewSpace.Position.X = 0;
		NewSpace.Position.Y = 0;
		NewSpace.Size.X = PageSize;
		NewSpace.Size.Y = PageSize;
		NewSpace.SetArea();
		NewSpace.TexturePageIdx = Pages.Num() - 1;
		FreeSpaces.AddItem(NewSpace);
	}

	SortSpaces();

	return AddedSameSizePage;
}

/* 
 * Adds a texture to an empty space and converts then finds all spaces it overlaps and shrink them.
 */
void UMakeIconPageCommandlet::AddTextureToSpace(OrigTexture& Texture, FreeSpace ToSpace)
{
	// NOTE: Changes to ToSpace will not persist since it is by value!

	// Put texture in top left of space...then proceed to divide up space.
	Texture.TexturePageIdx = ToSpace.TexturePageIdx;
	Texture.Position = ToSpace.Position;

	// NOTE: Add Border to account for an edge around textures
	const INT TexLeft = Texture.Position.X;
	const INT TexRight = (TexLeft + Texture.Size.X + BorderSize) - 1;
	const INT TexTop = Texture.Position.Y;
	const INT TexBottom = (TexTop + Texture.Size.Y + BorderSize) - 1;

	// Reserve spaces so we don't continually allocate more each add - assume each space will create 3 new ones and replace the FreeSpace...
	// In reality this is overkill, but who cares, mem is released when we leave function.
	TArray<FreeSpace> AddSpaces;
	AddSpaces.Empty(FreeSpaces.Num() * 3);

	for (INT FreeIdx = 0; FreeIdx < FreeSpaces.Num(); FreeIdx++)
	{
		FreeSpace & Space = FreeSpaces(FreeIdx);
		if (Space.TexturePageIdx == Texture.TexturePageIdx)
		{
			const INT SpaceLeft = Space.Position.X;
			if (SpaceLeft > TexRight)
				continue;

			const INT SpaceRight = (SpaceLeft + Space.Size.X) - 1;
			if (SpaceRight < TexLeft)
				continue;

			const INT SpaceTop = Space.Position.Y;
			if (SpaceTop > TexBottom)
				continue;

			const INT SpaceBottom = (SpaceTop + Space.Size.Y) - 1;
			if (SpaceBottom < TexTop)
				continue;

			// NOTE: Don't add any spaces that are too small to not have a border.
			// Add to left.
			FreeSpace NewSpace(Space);
			NewSpace.Size.X = TexLeft - SpaceLeft;
			if (NewSpace.Size.X >= MinWidth)
			{
				NewSpace.SetArea();
				AddSpaces.AddItem(NewSpace);
			}

			// Add to right
			NewSpace.Position.X = TexRight + 1;
			NewSpace.Size.X = SpaceRight - TexRight;  
			if (NewSpace.Size.X >= MinWidth)
			{
				NewSpace.SetArea();
				AddSpaces.AddItem(NewSpace);
			}

			// Restore...
			NewSpace.Position.X = SpaceLeft;
			NewSpace.Size.X = Space.Size.X;

			// Add Top
			NewSpace.Size.Y = TexTop - SpaceTop;
			if (NewSpace.Size.Y >= MinHeight)
			{
				NewSpace.SetArea();
				AddSpaces.AddItem(NewSpace);
			}

			// Add to Bottom
			NewSpace.Position.Y = TexBottom + 1;
			NewSpace.Size.Y = SpaceBottom - TexBottom; 
			if (NewSpace.Size.Y >= MinHeight)
			{
				NewSpace.SetArea();
				AddSpaces.AddItem(NewSpace);
			}

			// Rather than remove the free space we just replaced,
			// change it to the last one in FreeSpaces - much quicker.
			if (AddSpaces.Num() > 0)
			{
				FreeSpaces(FreeIdx) = AddSpaces.Pop();
			}
			else
			{
				FreeSpaces.Remove(FreeIdx);
				FreeIdx--;
			}
		}
	}
	// Often, new spaces are subsets of existing spaces, or visa versa - don't add those
	// because it makes searching/sorting that much more expensive.  
	// In one test case it made the max number of Spaces being tracked go from 31000 to less than 600,
	// a drastic change.
	for (INT AddIdx = 0; AddIdx < AddSpaces.Num(); AddIdx++)
	{
		FreeSpace & Add = AddSpaces(AddIdx);
		const INT AddLeft = Add.Position.X;
		const INT AddRight = AddLeft + Add.Size.X;
		const INT AddTop = Add.Position.Y;
		const INT AddBottom = AddTop + Add.Size.Y;

		for (INT FreeIdx = 0; FreeIdx < FreeSpaces.Num(); FreeIdx++)
		{
			FreeSpace & Space = FreeSpaces(FreeIdx);
			if (Space.TexturePageIdx == Add.TexturePageIdx)
			{
				const INT SpaceLeft = Space.Position.X;
				const INT SpaceRight = SpaceLeft + Space.Size.X;
				const INT SpaceTop = Space.Position.Y;
				const INT SpaceBottom = SpaceTop + Space.Size.Y;

				if ((SpaceLeft <= AddLeft) && (SpaceTop <= AddTop) && (SpaceBottom >= AddBottom) && (SpaceRight >= AddRight) )
				{
				}
				else if ((SpaceLeft >= AddLeft) &&(SpaceTop >= AddTop) && (SpaceBottom <= AddBottom) && (SpaceRight <= AddRight) )
				{
					Space = Add;
				}
				else
				{
					continue;
				}
				AddSpaces.Remove(AddIdx);
				AddIdx--;
				break;
			}
		}
	}

	FreeSpaces += AddSpaces;
	//warnf(NAME_Log, TEXT("FreeSpaces Size:%d %d"), FreeSpaces.Num(), AddSpaces.Num());
	SortSpaces();
}
/* Create the actual icon texture pages */
void UMakeIconPageCommandlet::MakeIconPages()
{
	TCHAR Str[MAX_SPRINTF]=TEXT("");

	warnf(NAME_Log, TEXT("Creating Icon Pages:"));

	TArray<FString> OldFiles;
	GFileManager->FindFiles(OldFiles, *FString::Printf(TEXT("%s_*.tga"), *SourcePath), TRUE, FALSE);

	FString Directory, Filename, BaseName, Extension, Unused;
	GPackageFileCache->SplitPath( *SourcePath, Directory, Unused, Unused );

	// Delete old files, important when we have less than previous time it was run.
	for (INT i = 0; i < OldFiles.Num(); i++)
	{
		Filename = Directory + TEXT("\\") + OldFiles(i);
		GFileManager->Delete(*Filename);
	}

	if( bSavePagesInPackage )
	{
		// Only do this once per RootPackage that comes in
		if( !CleanPackages.ContainsItem(RootPackage) )
		{
			CleanPackages.AddItem(RootPackage);

			warnf(NAME_Log, TEXT("\tDeleting old textures from %s"), *RootPackage->GetName());
			for( TObjectIterator<UTexture2D> It; It; ++It )
			{
				UTexture* Texture = *It;
				if( Texture->IsIn(RootPackage) )
				{
					Texture->ClearFlags(RF_Public);
					Texture->Rename(*Texture->GetName(), UObject::GetTransientPackage());
				}
			}
		}
	}

	UPackage* CreatePackage = GEngine->CreatePackage(NULL, TEXT("_CreateIconPage_"));
	UClass* Class = TextureFactory->ResolveSupportedClass();
	for (INT PageIdx = 0; PageIdx < Pages.Num(); PageIdx++)
	{
		TexturePage &Page = Pages(PageIdx);

		FString ExportFile = FString::Printf(TEXT("%s_%02d.tga"), *SourcePath, PageIdx );
		TextureFactory->CurrentFilename = ExportFile;
		Page.FileName = ExportFile;
		warnf(NAME_Log, TEXT("\t%s"), *ExportFile);

		GPackageFileCache->SplitPath( *ExportFile, Directory, Filename, Extension );
		GPackageFileCache->SplitPath( *SourcePath, Unused, BaseName, Unused );

		Page.BaseName = Filename;
		Page.FullName = RootPackage->GetPureName().ToString() + TEXT(".") + BaseName + TEXT(".") + Filename;

		UTexture2D* DestTexture = ConstructObject<UTexture2D>(UTexture2D::StaticClass(), CreatePackage);
		Page.Texture = DestTexture;
		DestTexture->LODGroup = TEXTUREGROUP_UI;
		DestTexture->AddressX = TA_Clamp;
		DestTexture->AddressY = TA_Clamp;
		DestTexture->Init(Page.Size, Page.Size, PF_A8R8G8B8);		// TODO - support PF_A4R4G4B4 to reduce size on iOS

		// Setup the texture and allocate the first mip level's worth of data
		DWORD* DestBuffer = (DWORD*)DestTexture->Mips(0).Data.Lock(LOCK_READ_WRITE);
		INT NumPixels = Square(Page.Size);
		if (InitialColor == 0)
		{
			appMemzero(DestBuffer, 4 * NumPixels);
		}
		else
		{
			INT Pixel=0;
			while (Pixel < NumPixels)
			{
				// Unroll loop - Page size will always be divisible by 8.
				DestBuffer[Pixel++] = InitialColor;	DestBuffer[Pixel++] = InitialColor; DestBuffer[Pixel++] = InitialColor;	DestBuffer[Pixel++] = InitialColor;
				DestBuffer[Pixel++] = InitialColor;	DestBuffer[Pixel++] = InitialColor;	DestBuffer[Pixel++] = InitialColor;	DestBuffer[Pixel++] = InitialColor;
			}
		}

		UTextureExporterTGA * TgaExporter = ConstructObject<UTextureExporterTGA>(UTextureExporterTGA::StaticClass());
		for (INT TextIdx = 0; TextIdx < Textures.Num(); TextIdx++)
		{
			OrigTexture & Orig = Textures(TextIdx);
			if (Orig.TexturePageIdx == PageIdx)
			{
				DWORD* SrcPtr = (DWORD*)Orig.Texture->Mips(0).Data.Lock(LOCK_READ_WRITE);
				INT StartPixel = (Orig.Position.Y * Page.Size) + Orig.Position.X;
				DWORD * DestPtr = DestBuffer + StartPixel;

				for (INT row = 0; row < Orig.Size.Y; row++)
				{
					if (TransparentColor == 0)
					{
						appMemcpy(DestPtr, SrcPtr, 4 * Orig.Size.X);
					}
					else
					{
						for (INT col = 0; col < Orig.Size.X; col++)
						{
							DWORD Pixel = SrcPtr[col];
							// Allows extracting from texture page to be more exact - make any fully transparent pixel have a slight color
							DestPtr[col] = ((Pixel & 0xFF000000) == 0) ? TransparentColor : Pixel;
						}
					}

					DestPtr += Page.Size;
					SrcPtr += Orig.Size.X;
				}

				Orig.Texture->Mips(0).Data.Unlock();
			}
		}

		DestTexture->Mips(0).Data.Unlock();
		DestTexture->UpdateResource();
		if (!UExporter::ExportToFile(Page.Texture, TgaExporter, *Page.FileName, FALSE, FALSE, FALSE))
		{
			warnf(NAME_Error, TEXT("\tFailed"), *Filename);
		}
		else if (bSavePagesInPackage)
		{
			UPackage *Package = GEngine->CreatePackage(RootPackage, *BaseName);
			warnf(NAME_Log, TEXT("\tImport to %s"), *Page.FullName);
			TextureFactory->SuppressImportOverwriteDialog();
			UTexture2D* FinalTexture = Cast<UTexture2D>(UFactory::StaticImportObject(Class, Package, FName( *Page.BaseName ), RF_Public|RF_Standalone, *Page.FileName, NULL, TextureFactory ));
			if (FinalTexture != NULL)
			{
				FinalTexture->LODGroup = TEXTUREGROUP_UI;
				FinalTexture->AddressX = TA_Wrap;
				FinalTexture->AddressY = TA_Wrap;
				if( bCompressTexture )
					FinalTexture->bForcePVRTC4 = TRUE;
				else
					FinalTexture->CompressionNone = TRUE;
				warnf(NAME_Log, TEXT("\tSuccess"));
			}
			else
			{
				warnf(NAME_Error, TEXT("\tFailed!"));
			}
		}
	}
}

/* Save in external (non game) ini file located in root of source directory */
void UMakeIconPageCommandlet::SaveIni()
{
	for (INT TextIdx = 0; TextIdx < Textures.Num(); TextIdx++)
	{
		OrigTexture& Orig = Textures(TextIdx);
		TexturePage Page = Pages(Orig.TexturePageIdx);

		if (IconPage != NULL)
		{
			FIconConfigData ConfigData;

			ConfigData.Name = *Orig.Name;
			ConfigData.TextureName = *Page.FullName;
			ConfigData.UV.U = Orig.Position.X + Orig.UVGutterSize;
			ConfigData.UV.V = Orig.Position.Y + Orig.UVGutterSize;
			ConfigData.UV.UL = Orig.Size.X - 2.f * Orig.UVGutterSize;
			ConfigData.UV.VL = Orig.Size.Y - 2.f * Orig.UVGutterSize;
			ConfigData.UV.bCustomCoords = TRUE;
			ConfigData.Scale = Orig.Scale;
			ConfigData.Texture = NULL;
			IconPage->Icons.AddItem(ConfigData);
		}
	}
}

/* Save the package - may or may not contain source icons - but contains icon pages */
void UMakeIconPageCommandlet::SavePackage()
{
	if (bSavePagesInPackage)
	{
#if HAVE_SCC
		FSourceControl::CheckOut(RootPackage);
#endif
		// so now we need to see if we actually were able to check this file out
		// if the file is still read only then we failed and need to emit an error and go to the next package
		if( GFileManager->IsReadOnly( *RootPackageFileName ) == TRUE )
		{
			warnf( NAME_Error, TEXT("Unable to check out the Package: %s"), *RootPackageFileName );
		}

		warnf( NAME_Log, TEXT("Saving Package:  [%s]."), *RootPackageFileName );
		// make sure any resources that need preparing for mobile devices are up to date
		GAlwaysOptimizeContentForMobile = TRUE;
		::PreparePackageForMobile(RootPackage, FALSE);
		if( SavePackageHelper(RootPackage, RootPackageFileName) )
		{
			warnf( NAME_Log, TEXT("\tSuccess!"));
		}
		else
		{
			warnf( NAME_Error, TEXT("\tFailed!"));
		}
	}
}


typedef UMakeIconPageCommandlet::FreeSpace MakeIconPageFreeSpace;
// Sort Free Spaces smallest to largest.
IMPLEMENT_COMPARE_CONSTREF( MakeIconPageFreeSpace, SortSpaceByArea, { return (A.Area == B.Area) ? (A.TexturePageIdx - B.TexturePageIdx) : (A.Area - B.Area); })
IMPLEMENT_COMPARE_CONSTREF( MakeIconPageFreeSpace, SortSpaceBySort, { return (A.Sort == B.Sort) ? (A.TexturePageIdx - B.TexturePageIdx) : (A.Sort - B.Sort); })

void UMakeIconPageCommandlet::SortSpaces()
{
	switch(SortSpacesBy)
	{
	case 0:
		Sort<USE_COMPARE_CONSTREF(MakeIconPageFreeSpace, SortSpaceByArea)>( FreeSpaces.GetData(), FreeSpaces.Num() );
		break;
	case 1:
		Sort<USE_COMPARE_CONSTREF(MakeIconPageFreeSpace, SortSpaceBySort)>( FreeSpaces.GetData(), FreeSpaces.Num() );
		break;
	}

}

// Sort Textures Largest to smallest.
typedef UMakeIconPageCommandlet::OrigTexture MakeIconPageOrigTexture;
IMPLEMENT_COMPARE_CONSTREF( MakeIconPageOrigTexture, SortTexturesByArea, { return B.Area - A.Area; })
IMPLEMENT_COMPARE_CONSTREF( MakeIconPageOrigTexture, SortTexturesBySort, { return B.Sort - A.Sort; })

void UMakeIconPageCommandlet::SortTextures()
{
	switch (SortTexturesBy)
	{
	case 0:
		Sort<USE_COMPARE_CONSTREF(MakeIconPageOrigTexture, SortTexturesByArea)>( Textures.GetData(), Textures.Num() );
		break;
	case 1:
		Sort<USE_COMPARE_CONSTREF(MakeIconPageOrigTexture, SortTexturesBySort)>( Textures.GetData(), Textures.Num() );
		break;
	}	
}

////////////////////////////////////////////////////////////////////////////////////////////
// Take a texture page and split out all textures from it.
////////////////////////////////////////////////////////////////////////////////////////////
INT USplitIconPageCommandlet::Main( const FString& Params )
{
	TArray<FString> Tokens;
	TArray<FString> Switches;

	// Parse command line args.
	ParseCommandLine(*Params, Tokens, Switches);

	TexturePagePath = Tokens(0);

	TextureFactory = ConstructObject<UTextureFactory>(UTextureFactory::StaticClass());
	TextureFactory->Blending = BLEND_Opaque;
	TextureFactory->LightingModel = MLM_Unlit;
	TextureFactory->bDeferCompression = TRUE;
	TextureFactory->NoCompression = TRUE;

	Package = GEngine->CreatePackage(NULL, TEXT("SplitIconPage"));

	if (!LoadTexturePage())
		return 1;

	ExtractTextures();

	return 0;
}

UBOOL USplitIconPageCommandlet::LoadTexturePage()
{
	FString TextureName = "SplitIconPage-";
	const FFilename FileName = TexturePagePath;
	const FString FileExtension = FileName.GetExtension();
	TextureName += FileName.GetBaseFilename();

	UClass* Class = TextureFactory->ResolveSupportedClass();
	UObject* Result = UFactory::StaticImportObject(Class, Package, FName( *TextureName ), RF_Public|RF_Standalone, *TexturePagePath, NULL, TextureFactory );
	TexturePage = Cast< UTexture2D >(Result);
	return (TexturePage != NULL);
}

namespace SplitIconPage
{
	INT FindPixel(DWORD* Start, INT Iterations, INT Skip = 1)
	{
		for (INT Offset = 0; Offset < Iterations; Offset++)
		{
			if (*Start)
				return Offset;
			Start += Skip;
		}
		return -1;
	}
	inline DWORD* GetPixel(DWORD* Start, INT X, INT Y, INT Width)
	{
		return Start + (Y * Width) + X;
	}
}

void USplitIconPageCommandlet::ExtractTextures()
{
	using namespace SplitIconPage;

	UTextureExporterTGA * TgaExporter = ConstructObject<UTextureExporterTGA>(UTextureExporterTGA::StaticClass());

	FString Directory, Filename, Extension;
	GPackageFileCache->SplitPath( *TexturePagePath, Directory, Filename, Extension );

	INT TextureIdx = 0;
	INT TopRowWithPixel = 0; // All rows above this are blank.
	const INT TexW = TexturePage->SizeX;
	const INT TexH = TexturePage->SizeY;
	DWORD* SrcBuffer = (DWORD*)TexturePage->Mips(0).Data.Lock(LOCK_READ_WRITE);
	FString Out;

	while (TopRowWithPixel < TexturePage->SizeY)
	{
		// Search for first pixel...
		DWORD* CurPixel = GetPixel(SrcBuffer, 0, TopRowWithPixel, TexW);
		INT Left = FindPixel(CurPixel, TexW);
		if (Left < 0)
		{
			TopRowWithPixel++;
			continue;
		}

		INT Top = TopRowWithPixel;
		INT Right = Left + 1;
		INT Bottom = Top + 1;
		while (TRUE)
		{
			if (Bottom < TexH)
			{
				CurPixel = GetPixel(SrcBuffer, Left, Bottom, TexW);
				INT Col = FindPixel(CurPixel, Right - Left);
				if (Col >= 0)
				{
					Bottom++;
					continue;
				}
			}
			if (Right < TexW)
			{
				CurPixel = GetPixel(SrcBuffer, Right, Top, TexW);
				INT Row = FindPixel(CurPixel, Bottom - Top, TexW);
				if (Row >= 0)
				{
					Right++;
					continue;
				}
			}
			if (Left > 0)
			{
				CurPixel = GetPixel(SrcBuffer, Left - 1, Top, TexW);
				INT Row = FindPixel(CurPixel, Bottom - Top, TexW);
				if (Row >= 0)
				{
					Left--;
					continue;
				}
			}
			break;
		}

		FIntPoint Pos(Left, Top);
		FIntPoint Size(Right - Left, Bottom - Top);

		// Skip random pixels.
		if (Size.X > 0 && Size.Y > 0)
		{
			UTexture2D * DestTexture = ConstructObject<UTexture2D>(UTexture2D::StaticClass());;
			DestTexture->LODGroup = TEXTUREGROUP_UI;
			DestTexture->AddressX = TA_Clamp;
			DestTexture->AddressY = TA_Clamp;
			DestTexture->Init(Size.X, Size.Y, PF_A8R8G8B8);

			DWORD* DestPtr = (DWORD*)DestTexture->Mips(0).Data.Lock(LOCK_READ_WRITE);
			DWORD* SrcPtr = GetPixel(SrcBuffer, Pos.X, Pos.Y, TexW);

			for (INT lp = 0; lp < Size.Y; lp++)
			{
				appMemcpy(DestPtr, SrcPtr, 4 * Size.X);
				appMemzero(SrcPtr, 4 * Size.X);
				DestPtr += Size.X;
				SrcPtr += TexW;
			}

			DestTexture->Mips(0).Data.Unlock();

			// Skip random pixels...we still do above so pixels are cleared.
			if (Size.X * Size.Y > 3)
			{
				TCHAR BaseName[MAX_SPRINTF]=TEXT("");
				TCHAR DestName[MAX_SPRINTF]=TEXT("");
				appSprintf(BaseName, TEXT("%s_%002d"), *Filename, TextureIdx++);
				appSprintf(DestName, TEXT("%s\\%s.tga"), *Directory, BaseName);
				UExporter::ExportToFile(DestTexture, TgaExporter, DestName, FALSE, FALSE, FALSE);

				appSprintf(DestName, TEXT("Icons=(Name=%s,TextureName=%s,UV=(bCustomCoords=True,U=%d,V=%d,UL=%d,VL=%d))\r\n")
					,BaseName
					,*Filename
					,Pos.X
					,Pos.Y
					,Size.X
					,Size.Y
					);
				Out += FString(DestName);
			}
		}
	}
	TexturePage->Mips(0).Data.Unlock();

	FString ExportFile = Directory + "\\" + Filename + ".ini";
	appSaveStringToFile(Out, *ExportFile, TRUE);
}


/**
 * Allows the commandlet to perform any additional operations on the object before it is resaved.
 *
 * @param	Object			the object in the current package that is currently being processed
 * @param	bSavePackage	[in]	indicates whether the package is currently going to be saved
 *							[out]	set to TRUE to resave the package
 */
void UFixSwordMapsCommandlet::PerformAdditionalOperations( UObject* Object, UBOOL& bSavePackage )
{
	// Iterate over all interp groups in our same level and remove the preview anim sets
	if ( Object->GetClass() == UInterpData::StaticClass() )
	{
		UInterpData* InterpData = Cast<UInterpData>(Object);

		UObject* Level = Object->GetOutermost();
		UBOOL bIsBattleMap = Level->GetName().StartsWith(TEXT("Battle_"));

		TArray<AnimSetInfo>& Info = bIsBattleMap ? BattleAnims : MapAnims;

		// Mark all animsets to get pruned in the battle level, they are all preview anims
		// We will go back through and hand set any that should not be pruned
		// Mark every other matinee in normal levels to be Bake&Prune
		InterpData->bShouldBakeAndPrune = TRUE;
		for( INT i=0; i<InterpData->BakeAndPruneStatus.Num(); i++ )
		{
			// Gather info
			INT Idx = 0;
			for( Idx=0; Idx<Info.Num(); Idx++ )
			{
				if( Info(Idx).Name == InterpData->BakeAndPruneStatus(i).AnimSetName )
					break;
			}
			if( Idx == Info.Num() )
			{
				Info.AddZeroed();
				Info(Idx).Name = InterpData->BakeAndPruneStatus(i).AnimSetName;
				Info(Idx).MapName = Level->GetName();
				Info(Idx).UseCount = 1;
			}
			else
			{
				Info(Idx).MapName = TEXT("");
				Info(Idx).UseCount += 1;
			}

			// Prune out any dynamically loaded anim sets
			if( DynamicallyLoadedAnimSets.ContainsItem(InterpData->BakeAndPruneStatus(i).AnimSetName) )
			{
				InterpData->BakeAndPruneStatus(i).bSkipBakeAndPrune = TRUE;
				InterpData->BakeAndPruneStatus(i).bSkipCooking = TRUE;
				Info(Idx).bWasSkipped = 1;
			}
			else
			{
				InterpData->BakeAndPruneStatus(i).bSkipBakeAndPrune = FALSE;
				InterpData->BakeAndPruneStatus(i).bSkipCooking = FALSE;
			}
		}

		bSavePackage = TRUE;
	}
}

INT UFixSwordMapsCommandlet::Main( const FString& Params )
{
	GConfig->GetArray(TEXT("FixSwordMaps"), TEXT("DynamicAnimSet"), DynamicallyLoadedAnimSets, GEditorIni);

	// Load the bosses to discover additional dynamic anim sets that should get pruned from levels
	UPackage* Package = UObject::LoadPackage( NULL, TEXT("..\\..\\SwordGame\\Content\\GameObjs\\B_Boss_GameObjs.upk"), 0 );
	if (Package != NULL)
	{
		FString AnimSetName;
		for (TObjectIterator<ASwordPawn> It; It; ++It)
		{
			ASwordPawn* Pawn = *It;
			if (Pawn->IsIn(Package))
			{
				for( INT i=0; i<Pawn->PlayerAnimSets.Num(); i++ )
				{
					if( Pawn->PlayerAnimSets(i) != NULL )
					{
						AnimSetName = Pawn->PlayerAnimSets(i)->GetPathName();
						DynamicallyLoadedAnimSets.AddUniqueItem(AnimSetName);
					}
				}
				if( Pawn->Mesh )
				{
					for( INT i=0; i<Pawn->Mesh->AnimSets.Num(); i++ )
					{
						if( Pawn->Mesh->AnimSets(i) != NULL )
						{
							AnimSetName = Pawn->Mesh->AnimSets(i)->GetPathName();
							DynamicallyLoadedAnimSets.AddUniqueItem(AnimSetName);
						}
					}
				}
			}
		}
	}

	// Run
	INT Ret = Super::Main(Params);

	warnf(NAME_Log, TEXT("\nBattle Map animsets:"));
	for( INT i=0; i<BattleAnims.Num(); i++)
	{
		warnf(NAME_Log, TEXT("  %d: %d %d %s %s"), i, BattleAnims(i).bWasSkipped, BattleAnims(i).UseCount, *BattleAnims(i).Name, *BattleAnims(i).MapName);
	}

	warnf(NAME_Log, TEXT("\nRegular Map animsets:"));
	for( INT i=0; i<MapAnims.Num(); i++)
	{
		warnf(NAME_Log, TEXT("  %d: %d %d %s %s"), i, MapAnims(i).bWasSkipped, MapAnims(i).UseCount, *MapAnims(i).Name, *MapAnims(i).MapName);
	}

	return Ret;
}

IMPLEMENT_CLASS(UFixSwordMapsCommandlet);


/**
 * Allows the commandlet to perform any additional operations on the object before it is resaved.
 *
 * @param	Object			the object in the current package that is currently being processed
 * @param	bSavePackage	[in]	indicates whether the package is currently going to be saved
 *							[out]	set to TRUE to resave the package
 */
void USwordMusicInfoCommandlet::PerformAdditionalOperations( UObject* Object, UBOOL& bSavePackage )
{
	// Iterate over all interp groups in our same level and remove the preview anim sets
	if ( Object->GetClass() == USeqAct_PlayMusicTrack::StaticClass() )
	{
		USeqAct_PlayMusicTrack* Music = Cast<USeqAct_PlayMusicTrack>(Object);
		AddMusicInfo(Music->MusicTrack.MP3Filename, TRUE, Object->GetOutermost());
	}
	else if ( Object->GetClass() == ASwordBossSpawnPoint::StaticClass() )
	{
		ASwordBossSpawnPoint* SpawnPoint = Cast<ASwordBossSpawnPoint>(Object);
		for( INT i=0; i<SpawnPoint->BossClasses.Num(); i++ )
		{
			FString TrackName = SpawnPoint->BossClasses(i).ForcedBattleMusic.ToString();
			AddMusicInfo(TrackName, FALSE, Object->GetOutermost());

			for( INT j=0; j<SpawnPoint->BossClasses(i).BossLevels.Num(); j++ )
			{
				SubMaps.AddUniqueItem(SpawnPoint->BossClasses(i).BossLevels(j));
			}
		}
	}
	else if ( Object->GetClass() == AWorldInfo::StaticClass() )
	{
		AWorldInfo* WorldInfo = Cast<AWorldInfo>(Object);
		for( INT i=0; i<WorldInfo->StreamingLevels.Num(); i++ )
		{
			if( WorldInfo->StreamingLevels(i) != NULL )
			{
				SubMaps.AddUniqueItem(WorldInfo->StreamingLevels(i)->PackageName.ToString());
			}
		}
	}
}

INT USwordMusicInfoCommandlet::AddMusicInfo(FString& TrackName, UBOOL bIsFromPlayMusic, UObject* Level)
{
	// Look for an existing track
	INT Track = -1;
	for( INT i=0; i<MusicInfo.Num(); i++ )
	{
		if( MusicInfo(i).TrackName == TrackName )
		{
			Track = i;
			break;
		}
	}
	// Create a new one if none found
	if( Track < 0 )
	{
		Track = MusicInfo.AddZeroed(1);
		MusicInfo(Track).TrackName = TrackName;
	}

	// Add the additional stats to the track info
	if( bIsFromPlayMusic )
		MusicInfo(Track).UseCount_PlayMusic++;
	else
		MusicInfo(Track).UseCount_Battle++;

	FString MapName = Level ? Level->GetName() : TEXT("[Battle]");
	MusicInfo(Track).Maps.AddUniqueItem(MapName);

	return Track;
}

INT USwordMusicInfoCommandlet::Main( const FString& Params )
{
	const TCHAR* Parms = *Params;
	TArray<FString> Tokens, Switches;
	ParseCommandLine(Parms, Tokens, Switches);

	TArray<FString> Maps;
	if( !Switches.ContainsItem(TEXT("ALLMAPS")) )
	{
		GConfig->GetArray(TEXT("MapsToCook"), TEXT("Map"), Maps, GEditorIni);
	}

	TArray<FFilename> PackageNames;
	INT ResultCode = InitializeResaveParameters(Tokens, Switches, PackageNames);
	if ( ResultCode != 0 )
	{
		return ResultCode;
	}

	// Retrieve list of all packages in .ini paths.
	if( !PackageNames.Num() )
	{
		return 0;
	}

	// Load the music list
	MusicList = Cast<USwordBattleMusicList>(StaticLoadObject( USwordBattleMusicList::StaticClass(), NULL, TEXT("B_SoundClassesAndModes.BattleMusicList"), NULL, LOAD_NoWarn, NULL ));

	// Iterate over all packages.
	do
	{
		for( INT PackageIndex = 0; PackageIndex < PackageNames.Num(); PackageIndex++ )
		{
			const FFilename& Filename = PackageNames(PackageIndex);

			// we don't care about trying to resave the various shader caches so just skipz0r them
			if(	Filename.InStr( TEXT("LocalShaderCache") ) != INDEX_NONE
			|| Filename.InStr( TEXT("RefShaderCache") ) != INDEX_NONE )
			{
				continue;
			}

			// Process maps
			if( Filename.GetExtension() == TEXT("SWORD") && (Maps.Num() == 0 || Maps.ContainsItem(Filename.GetBaseFilename())) )
			{
				warnf(NAME_Log, TEXT("Loading %s"), *Filename);

				UBOOL bSavePackage = TRUE;

				// Get the package linker.
				UObject::BeginLoad();
				ULinkerLoad* Linker = UObject::GetPackageLinker(NULL,*Filename,LOAD_NoVerify,NULL,NULL);
				UObject::EndLoad();

				PerformPreloadOperations(Linker, bSavePackage);

				// Assert if package couldn't be opened so we have no chance of messing up saving later packages.
				UPackage* Package = UObject::LoadPackage( NULL, *Filename, 0 );
				if (Package == NULL)
				{
					warnf(NAME_Warning, TEXT("Failed to load package %s"), *Filename);
					continue;
				}

				// hook to allow performing additional checks without lumping everything into this one function
				PerformAdditionalOperations(Package,bSavePackage);

				// Check for any special per object operations
				for( FObjectIterator ObjectIt; ObjectIt; ++ObjectIt )
				{
					if( ObjectIt->IsIn( Package ) )
					{
						PerformAdditionalOperations( *ObjectIt, bSavePackage );
					}
				}

				UObject::CollectGarbage(RF_Native);
			}
		}

		Maps = SubMaps;
		SubMaps.Empty();
	}
	while( Maps.Num() > 0 );

	// Find all the MP3 files available
	TArray<FString> MP3List;
	GFileManager->FindFiles(MP3List, TEXT("..\\..\\SwordGame\\Build\\iPhone\\Resources\\Music\\*.mp3"), TRUE, FALSE);
	for( INT i=0; i<MP3List.Num(); i++)
	{
		MP3List(i) = FFilename(MP3List(i)).GetBaseFilename();
	}

	INT Num = 0;
	warnf(NAME_Log, TEXT("\nMusic Tracks:"));
	for( INT i=0; i<MusicInfo.Num(); i++)
	{
		if( MusicInfo(i).UseCount_PlayMusic > 0 && MusicInfo(i).UseCount_Battle == 0 )
		{
			Num++;
			warnf(NAME_Log, TEXT("  %d: %d %d %s"), Num, MusicInfo(i).UseCount_PlayMusic, MusicInfo(i).UseCount_Battle, *MusicInfo(i).TrackName);
			for( INT j=0; j<MusicInfo(i).Maps.Num(); j++ )
			{
				warnf(NAME_Log, TEXT("        - %d %s"), j+1, *MusicInfo(i).Maps(j));
			}
		}
	}
	for( INT i=0; i<MusicInfo.Num(); i++)
	{
		if( MusicInfo(i).UseCount_PlayMusic > 0 && MusicInfo(i).UseCount_Battle > 0 )
		{
			Num++;
			warnf(NAME_Log, TEXT("  %d: %d %d %s"), Num, MusicInfo(i).UseCount_PlayMusic, MusicInfo(i).UseCount_Battle, *MusicInfo(i).TrackName);
			for( INT j=0; j<MusicInfo(i).Maps.Num(); j++ )
			{
				warnf(NAME_Log, TEXT("        - %d %s"), j+1, *MusicInfo(i).Maps(j));
			}
		}
	}

	Num = 0;
	warnf(NAME_Log, TEXT("\nBattle Music Tracks:"));
	for( INT i=0; i<MusicInfo.Num(); i++)
	{
		if( MusicInfo(i).UseCount_PlayMusic == 0 && MusicInfo(i).UseCount_Battle > 0 )
		{
			MusicInfo(i).bIsBattleMusicTag = 1;

			FBattleMusicGroup* Info = NULL;
			if( MusicList != NULL )
			{
				// Look for the music tag in the Fixed list first
				for( INT j=0; j<MusicList->FixedBattleMusicList.Num(); j++ )
				{
					if( MusicList->FixedBattleMusicList(j).MusicTag.ToString() == MusicInfo(i).TrackName )
					{
						Info = &MusicList->FixedBattleMusicList(j);
						break;
					}
				}
				// Search in the Random list if we couldn't find it already
				if( Info == NULL )
				{
					for( INT j=0; j<MusicList->RandomBattleMusicList.Num(); j++ )
					{
						if( MusicList->RandomBattleMusicList(j).MusicTag.ToString() == MusicInfo(i).TrackName )
						{
							Info = &MusicList->RandomBattleMusicList(j);
							break;
						}
					}
				}
			}
			Num++;
			warnf(NAME_Log, TEXT("  %d: %d %d %s"), Num, MusicInfo(i).UseCount_PlayMusic, MusicInfo(i).UseCount_Battle, *MusicInfo(i).TrackName);
			if( Info == NULL )
			{
				warnf(NAME_Log, TEXT("      [This battle music tag does not exist!]"));
			}
			else
			{
				warnf(NAME_Log, TEXT("      Stage 1: %s, %s"), *Info->Stage1MusicIntro, *Info->Stage1MusicLoop);
				warnf(NAME_Log, TEXT("      Stage 2: %s, %s"), *Info->Stage2MusicIntro, *Info->Stage2MusicLoop);
				warnf(NAME_Log, TEXT("      Stage 3: %s, %s"), *Info->Stage3MusicIntro, *Info->Stage3MusicLoop);
				warnf(NAME_Log, TEXT("      Death: %s"), *Info->DeathMusic);

				AddMusicInfo(Info->Stage1MusicIntro, TRUE, NULL);
				AddMusicInfo(Info->Stage1MusicLoop, TRUE, NULL);
				AddMusicInfo(Info->Stage2MusicIntro, TRUE, NULL);
				AddMusicInfo(Info->Stage2MusicLoop, TRUE, NULL);
				AddMusicInfo(Info->Stage3MusicIntro, TRUE, NULL);
				AddMusicInfo(Info->Stage3MusicLoop, TRUE, NULL);
				AddMusicInfo(Info->DeathMusic, TRUE, NULL);
			}
			for( INT j=0; j<MusicInfo(i).Maps.Num(); j++ )
			{
				warnf(NAME_Log, TEXT("        - %d %s"), j+1, *MusicInfo(i).Maps(j));
			}
		}
	}

	Num = 0;
	warnf(NAME_Log, TEXT("\nAll Music Tracks:"));
	for( INT i=0; i<MusicInfo.Num(); i++)
	{
		if( MusicInfo(i).bIsBattleMusicTag != 1 )
		{
			Num++;
			FString Verified = MP3List.ContainsItem(MusicInfo(i).TrackName) ? TEXT("") : TEXT("[MP3 does not exist!]");
			MP3List.RemoveItem(MusicInfo(i).TrackName);
			warnf(NAME_Log, TEXT("  %d: %d %d %s %s"), Num, MusicInfo(i).UseCount_PlayMusic, MusicInfo(i).UseCount_Battle, *MusicInfo(i).TrackName, *Verified);
		}
	}

	warnf(NAME_Log, TEXT("\nUnused MP3 files:"));
	for( INT i=0; i<MP3List.Num(); i++)
	{
		warnf(NAME_Log, TEXT("  %d: %s"), i+1, *MP3List(i));
	}

	return 0;
}

IMPLEMENT_CLASS(USwordMusicInfoCommandlet);