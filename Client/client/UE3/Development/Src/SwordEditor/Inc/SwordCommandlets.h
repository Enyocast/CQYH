/*=============================================================================
	SwordCommandlets.h
	Copyright 1998-2010 Epic Games, Inc. All Rights Reserved.
  =============================================================================*/

#ifndef _INC_SWORD_EDITOR_COMMANDLETS
#define _INC_SWORD_EDITOR_COMMANDLETS


BEGIN_COMMANDLET(CheckItems,SwordEditor)
END_COMMANDLET

class UTextureFactory;
BEGIN_COMMANDLET(MakeIconPage,SwordEditor)

	struct FreeSpace
	{
		FIntPoint		Position;
		FIntPoint		Size;
		INT				Area;
		INT				Sort;
		INT				TexturePageIdx;		
		void SetArea()
		{
			Area = Size.X * Size.Y;
			// This will make wide or tall textures to be 'bigger'
			Sort = (Size.X * Size.X) + (Size.Y * Size.Y);
		}
	};
	struct OrigTexture : public FreeSpace
	{
		UTexture2D*		Texture;
		FString			Name;
		FVector2D		Scale;
		FLOAT			UVGutterSize;
	};

	struct TexturePage
	{
		// Only make square textures.
		INT				Size;
		FString			FileName;
		FString			BaseName;
		FString			FullName;
		UTexture2D*		Texture;
	};

private:
	// Textures, FreeSpaces, and Pages are used to calculate and save newly created icon pages.
	TArray<OrigTexture> Textures;
	TArray<FreeSpace>	FreeSpaces;
	TArray<TexturePage>	Pages;

	// Current sorts to try different possible packings.
	INT SortTexturesBy;
	INT SortSpacesBy;

	// Smallest texture so we ignore spaces too small
	INT MinWidth;
	INT MinHeight;

	// Used to load in textures and to create new textures.
	UTextureFactory* TextureFactory;

	/*
	 * The following are all set by command line arguments or, if Class= is used, then
	 * the can be set by IconPage.MakeDefault and Icon.MakeCommand.  They are set by Init().
	 */

	// Class and instance used to create the icon pages and defines ini to save new settings.
	UClass* IconPageClass;
	UIconPage* IconPage;
	
	// The package that texture pages are saved in - sub packages are created for each icon page
	UPackage* RootPackage;
	FString RootPackageFileName;

	// Package used to import single icons into - it may be RootPackage.MakeIconPage with -SaveSource.
	UPackage* ImportPackage;

	// Directory where source icons are located.
	FString SourcePath;
	UBOOL bRecurseDirs;

	// Does not test as many combinations, not much of a savings especially if saving packages.
	UBOOL bFast;

	// Are we saving Icon pages to a package? 
	UBOOL bSavePagesInPackage;

	// Should we also put individual icons in the package?
	UBOOL bSaveSourcePackage;

	// Min and Max Texture sizes to created.
	INT MinTextureSize;
	INT MaxTextureSize;

	// Compress the final texture
	UBOOL bCompressTexture;

	// Size of border around image.
	INT BorderSize;

	// Push in the UVs by this amount
	FLOAT UVGutterSize;

	// These can help visualizing sizes or help if we want to extract.
	// An example value might be 0x00010101.
	DWORD TransparentColor;	// Any fully transparent pixel will be replaced with this color.
	DWORD InitialColor;		// What to clear the Dest Texture to before we write.
	FVector2D DefaultScale;	// Scale the source icon before writing into Dest Texture.

	TArray<FString> PerIconSettings;
	TArray<UObject*> CleanPackages;

	FString CurrentCommandLine;

public:
	UBOOL UseIconPageClass(const FString& ClassName);
	UBOOL Make(const FString& Params, const FString& ConfigSection);

private:
	UBOOL Init(const FString& Params, const FString& ConfigSection);
	UBOOL Init(const FString& Params, UBOOL bAppendToCurrentCommandline=FALSE);
	void Close();
	UBOOL ImportTextures();
	INT CalculateTexturePage();
	void MakeIconPages();
	void SaveIni();
	void SavePackage();

	UBOOL AddNewPage(INT TextureW, INT TextureH);
	void AddTextureToSpace(OrigTexture& Texture, FreeSpace ToSpace);
	void SortSpaces();
	void SortTextures();
	
END_COMMANDLET

BEGIN_COMMANDLET(SplitIconPage,SwordEditor)
	FString TexturePagePath;
	UTexture2D* TexturePage;
	UTextureFactory* TextureFactory;
	UPackage* Package;

	UBOOL LoadTexturePage();
	void ExtractTextures();

END_COMMANDLET

BEGIN_CHILD_COMMANDLET(FixSwordMaps, ResavePackages, SwordEditor)
	struct AnimSetInfo
	{
		FString Name;
		FString MapName;
		INT UseCount;
		INT bWasSkipped;
	};
	TArray<AnimSetInfo> BattleAnims;
	TArray<AnimSetInfo> MapAnims;

	TArray<FString> DynamicallyLoadedAnimSets;

	virtual INT Main(const FString& Param);
	virtual void PerformAdditionalOperations( class UObject* Object, UBOOL& bSavePackage );
END_CHILD_COMMANDLET

BEGIN_CHILD_COMMANDLET(SwordMusicInfo, ResavePackages, SwordEditor)
	struct MusicInfo
	{
		FString TrackName;
		INT UseCount_PlayMusic;
		INT UseCount_Battle;
		INT bIsBattleMusicTag;
		TArray<FString> Maps;
	};
	TArray<MusicInfo> MusicInfo;

	USwordBattleMusicList* MusicList;
	TArray<FString> SubMaps;

	virtual INT Main(const FString& Param);
	virtual void PerformAdditionalOperations( class UObject* Object, UBOOL& bSavePackage );

	INT AddMusicInfo(FString& TrackName, UBOOL bIsFromPlayMusic, UObject* Level);
END_CHILD_COMMANDLET

#endif