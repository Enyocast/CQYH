/**
 * Copyright 1998-2011 Epic Games, Inc. All Rights Reserved.
 */

#ifndef __SWORDEDITORCOOKERHELPER_H__
#define __SWORDEDITORCOOKERHELPER_H__

#include "SwordGameBossHelper.h"

enum EObjectPropertyType
{
	OPT_Name,
	OPT_MagicSpell,
	OPT_Max
};

class FSwordGameCookerHelper : public FGameCookerHelper
{
	// Remember which packages are used for the inventory items
	TArray<FString> InventoryPackageNames;
	TArray<FString> IconPackageNames;
	TArray<FString> IconTextureNames;

	/** Boss helper class */
	FSwordGameBossHelper BossHelper;

	/** The Boss packages to create/cook */
	TArray<FString> BossPackageNamesFromMaps;
	/** All possible boss packages */
	TArray<FString> BossPackageNames;

	/** Map of objects to BOSS packages they are contained in */
	TMap<FString, TArray<FString> > BossPackageObjects;
	/** Map of boss common objects */
	TMap<FString, FLOAT> BossCommonPackageObjects;
	/** Map of boss group objects */
	TMap<FString, TMap<FString,UBOOL> > BossGroupPackageObjects;
	/** Current boss group objects */
	TMap<FString,UBOOL>* CurrentBossGroupPackageObjects;
	/** Map of boss package to objects that should *not* be cooked out */
	TMap<FString, TMap<FString,UBOOL> > BossPackageSkipObjectMaps;

	/** If FALSE, skip the BossCommon generation */
	UBOOL bSkipBossCommon;
	/** Print all the objects cooked into the common boss packages while cooking */
	UBOOL bShowBossPackageDetails;

public:

	/**
	 *	Initialize the cooker helpr and process any command line params
	 *
	 *	@param	Commandlet		The cookpackages commandlet being run
	 *	@param	Tokens			Command line tokens parsed from app
	 *	@param	Switches		Command line switches parsed from app
	 */
	virtual void Init(
		class UCookPackagesCommandlet* Commandlet, 
		const TArray<FString>& Tokens, 
		const TArray<FString>& Switches );

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
	 *	@return	UBOOL		TRUE if successfull, FALSE is something went wrong.
	 */
	virtual UBOOL GeneratePackageList( 
		class UCookPackagesCommandlet* Commandlet, 
		UE3::EPlatformType Platform,
		EShaderPlatform ShaderPlatform,
		TArray<FPackageCookerInfo>& NotRequiredFilenamePairs,
		TArray<FPackageCookerInfo>& RegularFilenamePairs,
		TArray<FPackageCookerInfo>& MapFilenamePairs,
		TArray<FPackageCookerInfo>& ScriptFilenamePairs,
		TArray<FPackageCookerInfo>& StartupFilenamePairs,
		TArray<FPackageCookerInfo>& StandaloneSeekfreeFilenamePairs);

	/** Utility function for adding a package to the seekfree pairs list */
	UBOOL AddSeekfreePackage( const FString& PackageName, class UCookPackagesCommandlet* Commandlet, TArray<FPackageCookerInfo>& StandaloneSeekfreeFilenamePairs, DOUBLE FileCheckTime, UBOOL bCheckExists=TRUE);

	/** Utility function for adding a package to the seekfree pairs list from a property in a UObject */
	UBOOL AddSeekfreePackageFromProperty( UObject* Obj, const TCHAR* PropertyName, enum EObjectPropertyType PropertyType, FString& PackageName, class UCookPackagesCommandlet* Commandlet, TArray<FPackageCookerInfo>& StandaloneSeekfreeFilenamePairs, DOUBLE FileCheckTime, UBOOL bCheckExists);

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
	UPackage* LoadPackageForCookingCallback(class UCookPackagesCommandlet* Commandlet, const TCHAR* Filename);

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
	virtual UBOOL CookObject(class UCookPackagesCommandlet* Commandlet, UPackage* Package, UObject* Object, UBOOL bIsSavedInSeekFreePackage);

protected:
	/**
	 *
	 *	@param	Commandlet							The cookpackages commandlet being run
	 *	@param	StandaloneSeekfreeFilenamePairs		The package array to put them into 
	 *
	 *	@return	UBOOL			TRUE if successful, FALSE if failed
	 */
	virtual UBOOL CreateBossPackages(class UCookPackagesCommandlet* Commandlet, TArray<FPackageCookerInfo>& StandaloneSeekfreeFilenamePairs);

	/**
	 *
	 *	@param	Commandlet				The cookpackages commandlet being run
	 *	@param	BossFilename			The filename of the Boss package
	 *
	 *	@return	UPackage*				The boss package, NULL if failed.
	 */
	virtual UPackage* CreateBossPackage(class UCookPackagesCommandlet* Commandlet, FFilename& BossFilename, UBOOL bFillObjMap);
};

#endif