/*=============================================================================
	MMOGame.cpp
	Copyright 1998-2013 Epic Games, Inc. All Rights Reserved.
=============================================================================*/
#include "StdAfx.h"
#include "MMOGame.h"
#include "MMOFacade.h"

#include "MMOLogicCmd_Move.h"

#include "MMOGameUIClasses.h"
#include "MMOCommandlet.h"

/*-----------------------------------------------------------------------------
	The following must be done once per package.
-----------------------------------------------------------------------------*/

#define STATIC_LINKING_MOJO 1


// Register things.
#define NAMES_ONLY
#define AUTOGENERATE_NAME(name) FName MMOGAME_##name;
#define AUTOGENERATE_FUNCTION(cls,idx,name) IMPLEMENT_FUNCTION(cls,idx,name)
#include "MMOGameClasses.h"
#undef AUTOGENERATE_NAME

#include "MMOGameUIClasses.h"

#undef AUTOGENERATE_FUNCTION
#undef NAMES_ONLY


//------------------------------------------------------------------------

// Register natives.
#define NATIVES_ONLY
#define NAMES_ONLY
#define AUTOGENERATE_NAME(name)
#define AUTOGENERATE_FUNCTION(cls,idx,name)
#include "MMOGameClasses.h"
#undef AUTOGENERATE_NAME

//#include "MMOGamePlayerControllerClasses.h"
//#include "MMOGameFacadeClasses.h"
#include "MMOGameUIClasses.h"


#undef AUTOGENERATE_FUNCTION
#undef NATIVES_ONLY
#undef NAMES_ONLY

//#include "MMOGameUIClasses.h"

//------------------------------------------------------------------------

#if CHECK_NATIVE_CLASS_SIZES
#if _MSC_VER
#pragma optimize( "", off )
#endif

void AutoCheckNativeClassSizesMMOGame( UBOOL& Mismatch )
{
#define NAMES_ONLY
#define AUTOGENERATE_NAME( name )
#define AUTOGENERATE_FUNCTION( cls, idx, name )
#define VERIFY_CLASS_SIZES

#include "MMOGameClasses.h"
#include "MMOGameUIClasses.h"
//#include "MMOGamePlayerControllerClasses.h"
//#include "MMOGameFacadeClasses.h"

#undef AUTOGENERATE_FUNCTION
#undef AUTOGENERATE_NAME
#undef NAMES_ONLY
#undef VERIFY_CLASS_SIZES
}

#if _MSC_VER
#pragma optimize( "", on )
#endif
#endif

/**
 * Initialize registrants, basically calling StaticClass() to create the class and also
 * populating the lookup table.
 *
 * @param	Lookup	current index into lookup table
 */
void AutoInitializeRegistrantsMMOGame( INT& Lookup )
{
	AUTO_INITIALIZE_REGISTRANTS_MMOGAME
	AUTO_INITIALIZE_REGISTRANTS_MMOGAME_UI

		//M_REG_LOGIC_CMD_FACTORY(LCT_Move, LogicCmd_Move_Factory);
}

/**
 * Auto generates names.
 */
void AutoGenerateNamesMMOGame()
{
	#define NAMES_ONLY
    #define AUTOGENERATE_NAME(name) MMOGAME_##name = FName(TEXT(#name));		
		#include "MMOGameNames.h"
	#undef AUTOGENERATE_NAME

	#define AUTOGENERATE_FUNCTION(cls,idx,name)

	#include "MMOGameClasses.h"
	#include "MMOGameUIClasses.h"
	//#include "MMOGamePlayerControllerClasses.h"
	//#include "MMOGameFacadeClasses.h"

	#undef AUTOGENERATE_FUNCTION
	#undef NAMES_ONLY
}

/**
 * Game-specific code to handle DLC being added or removed
 *
 * @param bContentWasInstalled TRUE if DLC was installed, FALSE if it was removed
 */
void appOnDownloadableContentChanged(UBOOL bContentWasInstalled)
{
	// MMOGame doesn't care
}

FSystemSettings& GetSystemSettings()
{
	static FSystemSettings SystemSettingsSingleton;
	return SystemSettingsSingleton;
}

IMPLEMENT_CLASS(UAbilityComponent)
IMPLEMENT_CLASS(UAbilityWindSourceComponent)
IMPLEMENT_CLASS(UActorAttribute)
IMPLEMENT_CLASS(UAnimNodeBlendTwoSequences)
IMPLEMENT_CLASS(UWeaponEffectStaticMeshComponent)


IMPLEMENT_CLASS(UEquipMesh);
IMPLEMENT_CLASS(UItemManager)
IMPLEMENT_CLASS(UArmorResourceData)
IMPLEMENT_CLASS(AArmorActor)
IMPLEMENT_CLASS(UMMOAbility)
IMPLEMENT_CLASS(AMMOActor)
IMPLEMENT_CLASS(UTypeDefine)
IMPLEMENT_CLASS(UDataCheck)
IMPLEMENT_CLASS(AMMOPlayer)
IMPLEMENT_CLASS(AMMOStatue)
IMPLEMENT_CLASS(UMMOActorMaterialController)
IMPLEMENT_CLASS(UMMOAttackSlotManager)
IMPLEMENT_CLASS(UServerEnum)


IMPLEMENT_CLASS(AMMOPlayerController)
IMPLEMENT_CLASS(AMMOVolume_AmbientMusic)
IMPLEMENT_CLASS(AMMOVolume_AmbientSound)
IMPLEMENT_CLASS(AMMOVolume_CammeraNavigator)
IMPLEMENT_CLASS(AMMOVolume_Death)
IMPLEMENT_CLASS(AMMOVolume_Interactable)
IMPLEMENT_CLASS(AMMOVolume_DynamicBlocking)
IMPLEMENT_CLASS(AMMOVolume_PawnTracking)
IMPLEMENT_CLASS(AMMOVolume_SafeZone)
IMPLEMENT_CLASS(AMMOVolume_Teleport)
IMPLEMENT_CLASS(AMMOVolume_MapSize)
IMPLEMENT_CLASS(AMMOVolume_GuildBattle)

IMPLEMENT_CLASS(ANPC)
IMPLEMENT_CLASS(UDestructablePartAttachInfo)

IMPLEMENT_CLASS(AMMOGame)
IMPLEMENT_CLASS(AMMOFracturedStaticMeshActor)
IMPLEMENT_CLASS(AMMOKActor)

IMPLEMENT_CLASS(UIServerTrigger)
IMPLEMENT_CLASS(UIAbilityDamageable)
IMPLEMENT_CLASS(UIServerArea)
IMPLEMENT_CLASS(UMMOFootstepMaterialEditObject)
IMPLEMENT_CLASS(AMMOLoadingTrigger)
IMPLEMENT_CLASS(UIExcelable)
IMPLEMENT_CLASS(UAbilityPreviewResources)
IMPLEMENT_CLASS(UIReferenceID)
//IMPLEMENT_CLASS(USkeletalMeshComponentEx)
IMPLEMENT_CLASS(UIUniqueID)

IMPLEMENT_CLASS(ADynamicNavMeshObstacle)

IMPLEMENT_CLASS(UAnimNotify_ClothNoise)
IMPLEMENT_CLASS(UAnimNotify_DoodadLoopSound)

INT  UTypeDefine::ConvertToMS(const FIntervalTimeData& IntervalTime)
{
	return ((IntervalTime.Hours * 60 + IntervalTime.Minutes) * 60 + IntervalTime.Seconds) * 1000;
}