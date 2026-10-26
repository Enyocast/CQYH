//=============================================================================
// Copyright 1998-2010 Epic Games, Inc. All Rights Reserved.
// This is where you would extend the editor with game-specific dependencies
// and functionality
//=============================================================================

#include "UnrealEd.h"
#include "SwordEditorClasses.h"
#include "SwordGame.h"
#include "BSPOps.h"
#include "ScopedTransaction.h"

#define STATIC_LINKING_MOJO 1

// Register things.
#define NAMES_ONLY
#define AUTOGENERATE_NAME(name) FName SWORDEDITOR_##name;
#define AUTOGENERATE_FUNCTION(cls,idx,name) IMPLEMENT_FUNCTION(cls,idx,name)
#include "SwordEditorClasses.h"
#undef AUTOGENERATE_NAME

#undef AUTOGENERATE_FUNCTION
#undef NAMES_ONLY

// Register natives.
#define NATIVES_ONLY
#define NAMES_ONLY
#define AUTOGENERATE_NAME(name)
#define AUTOGENERATE_FUNCTION(cls,idx,name)
#include "SwordEditorClasses.h"
#undef AUTOGENERATE_NAME

#undef AUTOGENERATE_FUNCTION
#undef NATIVES_ONLY
#undef NAMES_ONLY

/**
 * Initialize registrants, basically calling StaticClass() to create the class and also 
 * populating the lookup table.
 *
 * @param	Lookup	current index into lookup table
 */
void AutoInitializeRegistrantsSwordEditor( INT& Lookup )
{
	AUTO_INITIALIZE_REGISTRANTS_SWORDEDITOR;
}

/**
 * Auto generates names.
 */
void AutoGenerateNamesSwordEditor()
{
	#define NAMES_ONLY
    #define AUTOGENERATE_NAME(name) SWORDEDITOR_##name = FName(TEXT(#name));
		#include "SwordEditorNames.h"
	#undef AUTOGENERATE_NAME

	#define AUTOGENERATE_FUNCTION(cls,idx,name)
	#include "SwordEditorClasses.h"
	#undef AUTOGENERATE_FUNCTION
	#undef NAMES_ONLY
}



IMPLEMENT_CLASS(USwordEditorEngine);
IMPLEMENT_CLASS(USwordUnrealEdEngine);

void UpdateVolume(AVolume* Volume, FBox& Box)
{
	if( Volume )
	{
		// Change the builder brush to match the bounding box
		FVector extent = Box.GetExtent();
		UCubeBuilder* CubeBuilder = ConstructObject<UCubeBuilder>( UCubeBuilder::StaticClass() );
		CubeBuilder->X = extent.X * 2;
		CubeBuilder->Y = extent.Y * 2;
		CubeBuilder->Z = extent.Z * 2;
		CubeBuilder->eventBuild();

		GWorld->GetBrush()->Location = Box.GetCenter();

		GWorld->GetBrush()->ClearComponents();
		GWorld->GetBrush()->ConditionalUpdateComponents();


		// Update the volume to match the builder brush

		Volume->PreEditChange(NULL);

		FBSPOps::csgCopyBrush
		(
			Volume,
			GWorld->GetBrush(),
			0,
			RF_Transactional,
			1,
			TRUE
		);

		// Set the texture on all polys to NULL.  This stops invisible texture
		// dependencies from being formed on volumes.
		if( Volume->Brush )
		{
			for( INT poly = 0 ; poly < Volume->Brush->Polys->Element.Num() ; ++poly )
			{
				FPoly* Poly = &(Volume->Brush->Polys->Element(poly));
				Poly->Material = NULL;
			}
		}
		Volume->PostEditChange();
	}
}

void ASwordBossSpawnPoint::UpdateVisibilityVolumes(UBOOL bLoading)
{
	// Adjust the extents of the precomputed visibility volume to cover the different battle areas

	// The size of the boxes around each player position (cameras should not go outside this extent)
	FVector Extent = CameraExtent;
	FVector ExtentZ(0.f,0.f,Extent.Z);

	// First, gather all the possible player positions and lump them into rough spatial groupings
	TArray<FBox> LocationGroups;
	for( INT ClassIdx=0; ClassIdx<BossClasses.Num(); ClassIdx++ )
	{
		for( INT TransIdx=0; TransIdx < UCONST_MaxBossTransitions; TransIdx++ )
		{
			FVector Loc = LocalToWorld().TransformFVector( BossClasses(ClassIdx).TransitionLocations[TransIdx] + ExtentZ );
			FBox NewBounds(Loc - Extent, Loc + Extent);

			// Find a bucket that this location is near
			INT GroupIdx = 0;
			for( ; GroupIdx<LocationGroups.Num(); GroupIdx++ )
			{
				if( LocationGroups(GroupIdx).ComputeSquaredDistanceToPoint(Loc) < VisibilityVolumeMergeDistance )
					break;
			}

			// Add it to the bucket or add a new bucket if needed
			if( GroupIdx >= LocationGroups.Num() )
			{
				LocationGroups.AddItem(NewBounds);
			}
			else
			{
				LocationGroups(GroupIdx) += NewBounds;
			}
		}
	}

	const FScopedTransaction Transaction( TEXT("SwordBrush AddVisVolumes") );

	// If we have any bad volumes, just reset all of them
	if( HasMissingVisibilityVolumes() )
	{
		for( INT i=0; i<PCVVolumes.Num(); i++ )
		{
			if( PCVVolumes(i) != NULL )
			{
				GWorld->DestroyActor(PCVVolumes(i));
				PCVVolumes(i) = NULL;
			}
		}
		PCVVolumes.Empty(LocationGroups.Num());
	}

	// Make sure there are the correct number of volumes
	if( PCVVolumes.Num() > LocationGroups.Num() )
	{
		// Get rid of excess volumes
		for( INT i=LocationGroups.Num(); i<PCVVolumes.Num(); i++ )
		{
			if( PCVVolumes(i) != NULL )
			{
				GWorld->DestroyActor(PCVVolumes(i));
				PCVVolumes(i) = NULL;
			}
		}
		PCVVolumes.Remove(PCVVolumes.Num() - LocationGroups.Num());
	}
	if( LocationGroups.Num() > PCVVolumes.Num() )
	{
		// Create new volumes
		PCVVolumes.AddZeroed(LocationGroups.Num() - PCVVolumes.Num());
		for( INT i=0; i<PCVVolumes.Num(); i++ )
		{
			if( PCVVolumes(i) == NULL )
			{
				FString VolumeName = FString::Printf(TEXT("VisVol_%s_%i"), *GetName(), i);
				PCVVolumes(i) = (ASwordPrecomputedVisibilityVolume*)GWorld->SpawnActor(ASwordPrecomputedVisibilityVolume::StaticClass(), *VolumeName, Location);
				check( PCVVolumes(i) != NULL );
			}
		}

		// A new volume actor was added, update the volumes visibility.
		GUnrealEd->UpdateVolumeActorVisibility( ASwordPrecomputedVisibilityVolume::StaticClass() );
	}
	check(PCVVolumes.Num() == LocationGroups.Num());

	// Make sure all the volumes are in the right spot, or add new volumes
	for( INT i=0; i<LocationGroups.Num(); i++ )
	{
		UpdateVolume(PCVVolumes(i), LocationGroups(i)); 
	}

	// Refresh the editor
	if( !bLoading )
	{
		GUnrealEd->RedrawLevelEditingViewports();
		GCallbackEvent->Send( CALLBACK_LevelDirtied );
		GCallbackEvent->Send( CALLBACK_RefreshEditor_LevelBrowser );
	}
}