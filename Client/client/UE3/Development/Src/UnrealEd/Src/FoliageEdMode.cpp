/*================================================================================
	FoliageEdMode.cpp: Foliage editing mode
	Copyright 1998-2013 Epic Games, Inc. All Rights Reserved.
================================================================================*/

#include "UnrealEd.h"
#include "UnObjectTools.h"
#include "FoliageEdMode.h"
#include "ScopedTransaction.h"
#include "EngineFoliageClasses.h"
// qin@snda
#include "LandscapeDataAccess.h"

#if WITH_MANAGED_CODE
#include "FoliageEditWindowShared.h"
#endif

#define FOLIAGE_SNAP_TRACE (10000.f)

//
// FEdModeFoliage
//

/** Constructor */
FEdModeFoliage::FEdModeFoliage() 
:	FEdMode()
,	bToolActive(FALSE)
,	SelectionIFA(NULL)
,	bCanAltDrag(FALSE)
{
	ID = EM_Foliage;
	Desc = TEXT( "Foliage" );

	// Load resources and construct brush component
	UMaterial* BrushMaterial = LoadObject<UMaterial>(NULL, TEXT("EditorLandscapeResources.FoliageBrushSphereMaterial"), NULL, LOAD_None, NULL);
	UStaticMesh* StaticMesh = LoadObject<UStaticMesh>(NULL,TEXT("EngineMeshes.Sphere"), NULL, LOAD_None, NULL);

	SphereBrushComponent = ConstructObject<UStaticMeshComponent>(UStaticMeshComponent::StaticClass());
	SphereBrushComponent->StaticMesh = StaticMesh;
	SphereBrushComponent->Materials.AddItem(BrushMaterial);
	SphereBrushComponent->AddToRoot();

	bBrushTraceValid = FALSE;
	BrushLocation = FVector(0,0,0);
}


/** Destructor */
FEdModeFoliage::~FEdModeFoliage()
{
	SphereBrushComponent->RemoveFromRoot();

	// Save UI settings to config file
	UISettings.Save();
}


/** FSerializableObject: Serializer */
void FEdModeFoliage::Serialize( FArchive &Ar )
{
	// Call parent implementation
	FEdMode::Serialize( Ar );
}

/** FEdMode: Called when the mode is entered */
void FEdModeFoliage::Enter()
{
	// Call parent implementation
	FEdMode::Enter();

	// Load UI settings from config file
	UISettings.Load();

#if WITH_MANAGED_CODE
	// Create the mesh paint window
	HWND EditorFrameWindowHandle = (HWND)GApp->EditorFrame->GetHandle();
	FoliageEditWindow.Reset( FFoliageEditWindow::CreateFoliageEditWindow( this, EditorFrameWindowHandle ) );
	check( FoliageEditWindow.IsValid() );
#endif

	// Force real-time viewports.  We'll back up the current viewport state so we can restore it when the
	// user exits this mode.
	const UBOOL bWantRealTime = TRUE;
	const UBOOL bRememberCurrentState = TRUE;
	ForceRealTimeViewports( bWantRealTime, bRememberCurrentState );
	
	// Reapply selection visualization on any foliage items
	if( UISettings.GetSelectToolSelected() || UISettings.GetLassoSelectToolSelected() )
	{
		SelectionIFA = AInstancedFoliageActor::GetInstancedFoliageActor();
		SelectionIFA->ApplySelectionToComponents(TRUE);
	}
	else
	{
		SelectionIFA = NULL;
	}
}

/** FEdMode: Called when the mode is exited */
void FEdModeFoliage::Exit()
{
	// Remove the brush
	SphereBrushComponent->ConditionalDetach();

	// Restore real-time viewport state if we changed it
	const UBOOL bWantRealTime = FALSE;
	const UBOOL bRememberCurrentState = FALSE;
	ForceRealTimeViewports( bWantRealTime, bRememberCurrentState );

	// Clear the cache (safety, should be empty!)
	LandscapeLayerCaches.Empty();

	// Save any settings that may have changed
#if WITH_MANAGED_CODE
	if( FoliageEditWindow.IsValid() )
	{
		FoliageEditWindow->SaveWindowSettings();
	}

	// Kill the mesh paint window
	FoliageEditWindow.Reset();
#endif

	// Save UI settings to config file
	UISettings.Save();

	// Clear the placed level info
	FoliageMeshList.Empty();

	// Clear selection visualization on any foliage items
	if( SelectionIFA && (UISettings.GetSelectToolSelected() || UISettings.GetLassoSelectToolSelected()) )
	{
		SelectionIFA->ApplySelectionToComponents(FALSE);
	}

	// Call parent implementation
	FEdMode::Exit();
}

/** When the user changes the active streaming level with the level browser */
void FEdModeFoliage::NotifyNewCurrentLevel()
{
	// Remove any selections in the old level and reapply for the new level
	if( UISettings.GetSelectToolSelected() || UISettings.GetLassoSelectToolSelected() )
	{
		if( SelectionIFA )
		{
			SelectionIFA->ApplySelectionToComponents(FALSE);
		}
		SelectionIFA = AInstancedFoliageActor::GetInstancedFoliageActor();
		SelectionIFA->ApplySelectionToComponents(TRUE);
	}
}

/** When the user changes the current tool in the UI */
void FEdModeFoliage::NotifyToolChanged()
{
	if( UISettings.GetSelectToolSelected() || UISettings.GetLassoSelectToolSelected() )
	{
		if( SelectionIFA == NULL )
		{
			SelectionIFA = AInstancedFoliageActor::GetInstancedFoliageActor();
			SelectionIFA->ApplySelectionToComponents(TRUE);
		}
	}
	// [qin@snda
	//else if( UISettings.GetDistributeToolSelected() )
	//{
	//	ApplyDistribution();
	//}
	// qin@snda]
	else
	{
		if( SelectionIFA )
		{
			SelectionIFA->ApplySelectionToComponents(FALSE);
		}
		SelectionIFA = NULL;
	}
}

/** FEdMode: Called once per frame */
void FEdModeFoliage::Tick(FEditorLevelViewportClient* ViewportClient,FLOAT DeltaTime)
{
	FEdMode::Tick(ViewportClient,DeltaTime);

	// Update the position and size of the brush component
	SphereBrushComponent->ConditionalDetach( TRUE );
	if( bBrushTraceValid && (UISettings.GetPaintToolSelected() || UISettings.GetReapplyToolSelected() || UISettings.GetLassoSelectToolSelected()) )
	{

		FMatrix BrushTransform = FScaleMatrix( UISettings.GetRadius() * 0.00625f );	// adjustment due to sphere SM size.
		BrushTransform *= FTranslationMatrix(BrushLocation);
		SphereBrushComponent->ConditionalAttach(GWorld->Scene,NULL,BrushTransform);
	}
}

/** Trace under the mouse cursor and update brush position */
void FEdModeFoliage::FoliageBrushTrace( FEditorLevelViewportClient* ViewportClient, INT MouseX, INT MouseY )
{
	bBrushTraceValid = FALSE;

	if( UISettings.GetPaintToolSelected() || UISettings.GetReapplyToolSelected() || UISettings.GetLassoSelectToolSelected() )
	{
		// Compute a world space ray from the screen space mouse coordinates
		FSceneViewFamilyContext ViewFamily(
			ViewportClient->Viewport, ViewportClient->GetScene(),
			ViewportClient->ShowFlags,
			GWorld->GetTimeSeconds(),
			GWorld->GetDeltaSeconds(),
			GWorld->GetRealTimeSeconds(),
			ViewportClient->IsRealtime()
			);
		FSceneView* View = ViewportClient->CalcSceneView( &ViewFamily );
		FViewportCursorLocation MouseViewportRay( View, ViewportClient, MouseX, MouseY );

		FVector Start = MouseViewportRay.GetOrigin();
		BrushTraceDirection = MouseViewportRay.GetDirection();
		FVector End = Start + WORLD_MAX * BrushTraceDirection;

		FCheckResult Hit;
		if( !GWorld->SingleLineCheck(Hit, NULL, End, Start, TRACE_World | TRACE_Level, FVector(0.f,0.f,0.f), NULL) )
		{
			// Check filters
			if( (Hit.Component &&		 
				(Hit.Component->GetOutermost() != GWorld->CurrentLevel->GetOutermost() ||
				(!UISettings.bFilterLandscape && Hit.Component->IsA(ULandscapeHeightfieldCollisionComponent::StaticClass())) ||
				(!UISettings.bFilterStaticMesh && Hit.Component->IsA(UStaticMeshComponent::StaticClass())) ||
				(!UISettings.bFilterTerrain && Hit.Component->IsA(UTerrainComponent::StaticClass())))) ||
				(Hit.Actor && Hit.Actor->IsA(AWorldInfo::StaticClass()) && (!UISettings.bFilterBSP || GWorld->Levels(Hit.LevelIndex) != GWorld->CurrentLevel)) )
			{
				bBrushTraceValid = FALSE;
			}
			else
			{
				// Adjust the sphere brush
				BrushLocation = Hit.Location;
				bBrushTraceValid = TRUE;
			}
		}
	}
}

/**
 * Called when the mouse is moved over the viewport
 *
 * @param	InViewportClient	Level editor viewport client that captured the mouse input
 * @param	InViewport			Viewport that captured the mouse input
 * @param	InMouseX			New mouse cursor X coordinate
 * @param	InMouseY			New mouse cursor Y coordinate
 *
 * @return	TRUE if input was handled
 */
UBOOL FEdModeFoliage::MouseMove( FEditorLevelViewportClient* ViewportClient, FViewport* Viewport, INT MouseX, INT MouseY )
{
	FoliageBrushTrace(ViewportClient, MouseX, MouseY );
	return FALSE;
}

/**
 * Called when the mouse is moved while a window input capture is in effect
 *
 * @param	InViewportClient	Level editor viewport client that captured the mouse input
 * @param	InViewport			Viewport that captured the mouse input
 * @param	InMouseX			New mouse cursor X coordinate
 * @param	InMouseY			New mouse cursor Y coordinate
 *
 * @return	TRUE if input was handled
 */
UBOOL FEdModeFoliage::CapturedMouseMove( FEditorLevelViewportClient* ViewportClient, FViewport* Viewport, INT MouseX, INT MouseY )
{
	FoliageBrushTrace(ViewportClient, MouseX, MouseY );

	if( IsCtrlDown(Viewport) && bToolActive )
	{
		ApplyBrush(ViewportClient);
	}
	return FALSE;
}

void FEdModeFoliage::GetRandomVectorInBrush( FVector& OutStart, FVector& OutEnd )
{
	// Find Rx and Ry inside the unit circle
	FLOAT Ru, Rv;
	do 
	{
		Ru = 2.f * appFrand() - 1.f;
		Rv = 2.f * appFrand() - 1.f;
	} while ( Square(Ru) + Square(Rv) > 1.f );
	
	// find random point in circle thru brush location parallel to screen surface
	FVector U, V;
	BrushTraceDirection.FindBestAxisVectors(U,V);
	FVector Point = Ru * U + Rv * V;

	// find distance to surface of sphere brush from this point
	FLOAT Rw = appSqrt( 1.f - (Square(Ru) + Square(Rv)) );

	OutStart = BrushLocation + UISettings.GetRadius() * (Ru * U + Rv * V - Rw * BrushTraceDirection);
	OutEnd   = BrushLocation + UISettings.GetRadius() * (Ru * U + Rv * V + Rw * BrushTraceDirection);
}


// Number of buckets for layer weight histogram distribution.
#define NUM_INSTANCE_BUCKETS 10

// Struct to hold potential instances we've randomly sampled
struct FPotentialInstance
{
	FVector HitLocation;
	FVector HitNormal;
	UPrimitiveComponent* HitComponent;
	FLOAT HitWeight;
	
	FPotentialInstance(FVector InHitLocation, FVector InHitNormal, UPrimitiveComponent* InHitComponent, FLOAT InHitWeight)
	:	HitLocation(InHitLocation)
	,	HitNormal(InHitNormal)
	,	HitComponent(InHitComponent)
	,	HitWeight(InHitWeight)
	{}

	FFoliageInstance PlaceInstance(UInstancedFoliageSettings* MeshSettings)
	{
		FFoliageInstance Inst;

		if( MeshSettings->UniformScale )
		{
			FLOAT Scale = MeshSettings->ScaleMinX + appFrand() * (MeshSettings->ScaleMaxX - MeshSettings->ScaleMinX);
			Inst.DrawScale3D = FVector(Scale,Scale,Scale);
		}
		else
		{
			FLOAT LockRand = appFrand();
			Inst.DrawScale3D.X = MeshSettings->ScaleMinX + (MeshSettings->LockScaleX ? LockRand : appFrand()) * (MeshSettings->ScaleMaxX - MeshSettings->ScaleMinX);
			Inst.DrawScale3D.Y = MeshSettings->ScaleMinY + (MeshSettings->LockScaleY ? LockRand : appFrand()) * (MeshSettings->ScaleMaxY - MeshSettings->ScaleMinY);
			Inst.DrawScale3D.Z = MeshSettings->ScaleMinZ + (MeshSettings->LockScaleZ ? LockRand : appFrand()) * (MeshSettings->ScaleMaxZ - MeshSettings->ScaleMinZ);
		}

		Inst.ZOffset = MeshSettings->ZOffsetMin + appFrand() * (MeshSettings->ZOffsetMax - MeshSettings->ZOffsetMin);

		Inst.Location = HitLocation;

		// Random yaw and optional random pitch up to the maximum
		Inst.Rotation = FRotator(appRound(appFrand() * 65535.f * MeshSettings->RandomPitchAngle / 360.f),0,0);

		if( MeshSettings->RandomYaw )
		{
			Inst.Rotation.Yaw = appRound(appFrand() * 65535.f);
		}
		else
		{
			Inst.Flags |= FOLIAGE_NoRandomYaw;
		}

		if( MeshSettings->AlignToNormal )
		{
			Inst.AlignToNormal( HitNormal, MeshSettings->AlignMaxAngle );
		}

		// Apply the Z offset in local space
		if( Abs(Inst.ZOffset) > KINDA_SMALL_NUMBER )
		{
			Inst.Location = Inst.GetInstanceTransform().TransformFVector(FVector(0,0,Inst.ZOffset));
		}

		Inst.Base = HitComponent;

		return Inst;
	}
};

UBOOL CheckLocationForPotentialInstance(FFoliageMeshInfo& MeshInfo, const UInstancedFoliageSettings* MeshSettings, FLOAT DensityCheckRadius, const FVector& Location, const FVector& Normal, TArray<FVector>& PotentialInstanceLocations, FFoliageInstanceHash& PotentialInstanceHash )
{
	// Check slope
	if( (MeshSettings->GroundSlope > 0.f && Normal.Z <= appCos(PI * MeshSettings->GroundSlope / 180.f) ||
		MeshSettings->GroundSlope < 0.f && Normal.Z >= appCos(-PI * MeshSettings->GroundSlope / 180.f)) )
	{
		return FALSE;
	}

	// Check height range
	if( Location.Z < MeshSettings->HeightMin || Location.Z > MeshSettings->HeightMax )
	{
		return FALSE;
	}

	// Check existing instances. Use the Density radius rather than the minimum radius
	if( MeshInfo.CheckForOverlappingSphere(FSphere(Location, DensityCheckRadius)) )
		{
			return FALSE;
		}

	// Check if we're too close to any other instances
	if( MeshSettings->Radius > 0.f )
	{
		// Check with other potential instances we're about to add.
		UBOOL bFoundOverlapping = FALSE;
		FLOAT RadiusSquared = Square(DensityCheckRadius/*MeshSettings->Radius*/);

		TSet<INT> TempInstances;
		PotentialInstanceHash.GetInstancesOverlappingBox(FBox::BuildAABB(Location, FVector(MeshSettings->Radius,MeshSettings->Radius,MeshSettings->Radius)), TempInstances );
		for( TSet<INT>::TConstIterator It(TempInstances); It; ++It )
		{
			if( (PotentialInstanceLocations(*It) - Location).SizeSquared() < RadiusSquared )
			{
				bFoundOverlapping = TRUE;
				break;
			}
		}
		if( bFoundOverlapping )
		{
			return FALSE;
		}
	}				

	INT PotentialIdx = PotentialInstanceLocations.AddItem(Location);
	PotentialInstanceHash.InsertInstance( Location, PotentialIdx );
	return TRUE;
}


/** Add instances inside the brush to match DesiredInstanceCount */
void FEdModeFoliage::AddInstancesForBrush( AInstancedFoliageActor* IFA, UStaticMesh* StaticMesh, FFoliageMeshInfo& MeshInfo, INT DesiredInstanceCount, TArray<INT>& ExistingInstances, FLOAT Pressure )
{
	UInstancedFoliageSettings* MeshSettings = MeshInfo.Settings;

	if( DesiredInstanceCount > ExistingInstances.Num() )
	{
		INT ExistingInstanceBuckets[NUM_INSTANCE_BUCKETS];
		appMemzero(ExistingInstanceBuckets, sizeof(ExistingInstanceBuckets));

		// Cache store mapping between component and weight data
		TMap<ULandscapeComponent*, TArray<BYTE> >* LandscapeLayerCache = NULL;

		FName LandscapeLayerName = MeshSettings->LandscapeLayer;
		if( LandscapeLayerName != NAME_None )
		{
			LandscapeLayerCache = &LandscapeLayerCaches.FindOrAdd(LandscapeLayerName);

			// Find the landscape weights of existing ExistingInstances
			for( INT Idx=0;Idx<ExistingInstances.Num();Idx++ )
			{
				FFoliageInstance& Instance = MeshInfo.Instances(ExistingInstances(Idx));
				ULandscapeHeightfieldCollisionComponent* HitLandscapeCollision = Cast<ULandscapeHeightfieldCollisionComponent>(Instance.Base);
				if( HitLandscapeCollision )
				{
					ULandscapeComponent* HitLandscape = HitLandscapeCollision->GetLandscapeComponent();
					if( HitLandscape )
					{
						TArray<BYTE>* LayerCache = &LandscapeLayerCache->FindOrAdd(HitLandscape);
						FLOAT HitWeight = HitLandscape->GetLayerWeightAtLocation( Instance.Location, LandscapeLayerName, LayerCache );

						// Add count to bucket.
						ExistingInstanceBuckets[appRound(HitWeight * (FLOAT)(NUM_INSTANCE_BUCKETS-1))]++;
					}
				}							
			}
		}
		else
		{
			// When not tied to a layer, put all the ExistingInstances in the last bucket.
			ExistingInstanceBuckets[NUM_INSTANCE_BUCKETS-1] = ExistingInstances.Num();
		}

		// We calculate a set of potential ExistingInstances for the brush area.
		TArray<FPotentialInstance> PotentialInstanceBuckets[NUM_INSTANCE_BUCKETS];
		appMemzero(PotentialInstanceBuckets, sizeof(PotentialInstanceBuckets));

		// Quick lookup of potential instance locations, used for overlapping check.
		TArray<FVector> PotentialInstanceLocations;
		FFoliageInstanceHash PotentialInstanceHash(7);	// use 128x128 cell size, as the brush radius is typically small.
		PotentialInstanceLocations.Empty(DesiredInstanceCount);

		// Radius where we expect to have a single instance, given the density rules
		const FLOAT DensityCheckRadius = Max<FLOAT>( appSqrt( (1000.f*1000.f) / (PI * MeshSettings->Density) ), MeshSettings->Radius );

		for( INT DesiredIdx=0;DesiredIdx<DesiredInstanceCount;DesiredIdx++ )
		{
			FVector Start, End;

			GetRandomVectorInBrush(Start, End);
			
			FCheckResult Hit;
			if( !GWorld->SingleLineCheck(Hit, NULL, End, Start, TRACE_World | TRACE_Level, FVector(0.f,0.f,0.f), NULL) )
			{
				// Check filters
				if( (Hit.Component &&		 
					(Hit.Component->GetOutermost() != GWorld->CurrentLevel->GetOutermost() ||
					(!UISettings.bFilterLandscape && Hit.Component->IsA(ULandscapeHeightfieldCollisionComponent::StaticClass())) ||
					(!UISettings.bFilterStaticMesh && Hit.Component->IsA(UStaticMeshComponent::StaticClass())) ||
					(!UISettings.bFilterTerrain && Hit.Component->IsA(UTerrainComponent::StaticClass())))) ||
					(Hit.Actor && Hit.Actor->IsA(AWorldInfo::StaticClass()) && (!UISettings.bFilterBSP || GWorld->Levels(Hit.LevelIndex) != GWorld->CurrentLevel)) )
				{
					continue;
				}

				if( !CheckLocationForPotentialInstance( MeshInfo, MeshSettings, DensityCheckRadius, Hit.Location, Hit.Normal, PotentialInstanceLocations, PotentialInstanceHash ) )
				{
					continue;
				}

				// Check landscape layer
				FLOAT HitWeight = 1.f;
				if( LandscapeLayerName != NAME_None )
				{
					ULandscapeHeightfieldCollisionComponent* HitLandscapeCollision = Cast<ULandscapeHeightfieldCollisionComponent>(Hit.Component);
					if( HitLandscapeCollision )
					{
						ULandscapeComponent* HitLandscape = HitLandscapeCollision->GetLandscapeComponent();
						if( HitLandscape )
						{
							TArray<BYTE>* LayerCache = &LandscapeLayerCache->FindOrAdd(HitLandscape);
							HitWeight = HitLandscape->GetLayerWeightAtLocation( Hit.Location, LandscapeLayerName, LayerCache );

							// Reject instance randomly in proportion to weight
							if( HitWeight <= appFrand() )
							{
								continue;
							}
						}					
					}
				}

				new(PotentialInstanceBuckets[appRound(HitWeight * (FLOAT)(NUM_INSTANCE_BUCKETS-1))]) FPotentialInstance( Hit.Location, Hit.Normal, Hit.Component, HitWeight );
			}
		}

		for( INT BucketIdx = 0; BucketIdx < NUM_INSTANCE_BUCKETS; BucketIdx++ )
		{
			TArray<FPotentialInstance>& PotentialInstances = PotentialInstanceBuckets[BucketIdx];
			FLOAT BucketFraction = (FLOAT)(BucketIdx+1) / (FLOAT)NUM_INSTANCE_BUCKETS;

			// We use the number that actually succeeded in placement (due to parameters) as the target
			// for the number that should be in the brush region.
			INT AdditionalInstances = Clamp<INT>( appRound( BucketFraction * (FLOAT)(PotentialInstances.Num() - ExistingInstanceBuckets[BucketIdx]) * Pressure), 0, PotentialInstances.Num() );
			for( INT Idx=0;Idx<AdditionalInstances;Idx++ )
			{
				FFoliageInstance Inst = PotentialInstances(Idx).PlaceInstance(MeshSettings);
				MeshInfo.AddInstance( IFA, StaticMesh, Inst );
			}
		}
	}
}

/** Remove instances inside the brush to match DesiredInstanceCount */
void FEdModeFoliage::RemoveInstancesForBrush( AInstancedFoliageActor* IFA, FFoliageMeshInfo& MeshInfo, INT DesiredInstanceCount, TArray<INT>& ExistingInstances, FLOAT Pressure )
{
	INT InstancesToRemove = appRound( (FLOAT)(ExistingInstances.Num() - DesiredInstanceCount) * Pressure);
	INT InstancesToKeep = ExistingInstances.Num() - InstancesToRemove;
	if( InstancesToKeep > 0 )
	{						
		// Remove InstancesToKeep random ExistingInstances from the array to leave those ExistingInstances behind, and delete all the rest
		for( INT i=0;i<InstancesToKeep;i++ )
		{
			ExistingInstances.RemoveSwap(appRand() % ExistingInstances.Num());
		}
	}

	if( !UISettings.bFilterLandscape || !UISettings.bFilterStaticMesh || !UISettings.bFilterTerrain || !UISettings.bFilterBSP )
	{
		// Filter ExistingInstances
		for( INT Idx=0;Idx<ExistingInstances.Num();Idx++ )
		{
			UActorComponent* Base = MeshInfo.Instances(ExistingInstances(Idx)).Base;

			// Check if instance is candidate for removal based on filter settings
			if( (Base && 
				((!UISettings.bFilterLandscape && Base->IsA(ULandscapeHeightfieldCollisionComponent::StaticClass())) ||
				(!UISettings.bFilterStaticMesh && Base->IsA(UStaticMeshComponent::StaticClass())) ||
				(!UISettings.bFilterTerrain && Base->IsA(UTerrainComponent::StaticClass())))) ||
				(!UISettings.bFilterBSP && !Base) )
			{
				// Instance should not be removed, so remove it from the removal list.
				ExistingInstances.RemoveSwap(Idx);
				Idx--;
			}
		}
	}

	// Remove ExistingInstances to reduce it to desired count
	if( ExistingInstances.Num() > 0 )
	{
		MeshInfo.RemoveInstances( IFA, ExistingInstances );
	}
}

/** Reapply instance settings to exiting instances */
void FEdModeFoliage::ReapplyInstancesForBrush( AInstancedFoliageActor* IFA, FFoliageMeshInfo& MeshInfo, TArray<INT>& ExistingInstances )
{
	UInstancedFoliageSettings* MeshSettings = MeshInfo.Settings;
	UBOOL bUpdated=FALSE;

	TArray<INT> UpdatedInstances;
	TSet<INT> InstancesToDelete;

	// Setup cache if we're reapplying landscape layer weights
	FName LandscapeLayerName = MeshSettings->LandscapeLayer;
	TMap<ULandscapeComponent*, TArray<BYTE> >* LandscapeLayerCache = NULL;
	if( MeshSettings->ReapplyLandscapeLayer && LandscapeLayerName != NAME_None )
	{
		LandscapeLayerCache = &LandscapeLayerCaches.FindOrAdd(LandscapeLayerName);
	}

	for( INT Idx=0;Idx<ExistingInstances.Num();Idx++ )
	{
		INT InstanceIndex = ExistingInstances(Idx);
		FFoliageInstance& Instance = MeshInfo.Instances(InstanceIndex);

		if( (Instance.Flags & FOLIAGE_Readjusted) == 0 )
		{
			// record that we've made changes to this instance already, so we don't touch it again.
			Instance.Flags |= FOLIAGE_Readjusted;

			UBOOL bReapplyLocation = FALSE;

			// remove any Z offset first, so the offset is reapplied to any new 
			if( Abs(Instance.ZOffset) > KINDA_SMALL_NUMBER )
			{
				MeshInfo.InstanceHash->RemoveInstance(Instance.Location, InstanceIndex);
				Instance.Location = Instance.GetInstanceTransform().TransformFVector(FVector(0,0,-Instance.ZOffset));
				bReapplyLocation = TRUE;
			}

			// Defer normal reapplication 
			UBOOL bReapplyNormal = FALSE;

			// Reapply normal alignment
			if( MeshSettings->ReapplyAlignToNormal )
			{
				if( MeshSettings->AlignToNormal )
				{
					if( (Instance.Flags & FOLIAGE_AlignToNormal) == 0 )
					{
						bReapplyNormal = TRUE;
						bUpdated = TRUE;
					}
				}
				else
				{
					if( Instance.Flags & FOLIAGE_AlignToNormal )
					{
						Instance.Rotation = Instance.PreAlignRotation;
						Instance.Flags &= (~FOLIAGE_AlignToNormal);
						bUpdated = TRUE;
					}
				}
			}

			// Reapply random yaw
			if( MeshSettings->ReapplyRandomYaw )
			{
				if( MeshSettings->RandomYaw )
				{
					if( Instance.Flags & FOLIAGE_NoRandomYaw )
					{
						// See if we need to remove any normal alignment first
						if( !bReapplyNormal && (Instance.Flags & FOLIAGE_AlignToNormal) )
						{
							Instance.Rotation = Instance.PreAlignRotation;
							bReapplyNormal = TRUE;
						}
						Instance.Rotation.Yaw = appRound(appFrand() * 65535.f);
						Instance.Flags &= (~FOLIAGE_NoRandomYaw);
						bUpdated = TRUE;
					}
				}
				else
				{
					if( (Instance.Flags & FOLIAGE_NoRandomYaw)==0 )
					{
						// See if we need to remove any normal alignment first
						if( !bReapplyNormal && (Instance.Flags & FOLIAGE_AlignToNormal) )
						{
							Instance.Rotation = Instance.PreAlignRotation;
							bReapplyNormal = TRUE;
						}
						Instance.Rotation.Yaw = 0;
						Instance.Flags |= FOLIAGE_NoRandomYaw;
						bUpdated = TRUE;
					}
				}
			}

			// Reapply random pitch angle
			if( MeshSettings->ReapplyRandomPitchAngle )
			{
				// See if we need to remove any normal alignment first
				if( !bReapplyNormal && (Instance.Flags & FOLIAGE_AlignToNormal) )
				{
					Instance.Rotation = Instance.PreAlignRotation;
					bReapplyNormal = TRUE;
				}

				Instance.Rotation.Pitch = appRound(appFrand() * 65535.f * MeshSettings->RandomPitchAngle / 360.f);
				Instance.Flags |= FOLIAGE_NoRandomYaw;

				bUpdated = TRUE;
			}

			// Reapply scale
			if( MeshSettings->UniformScale )
			{
				if( MeshSettings->ReapplyScaleX )
				{
					FLOAT Scale = MeshSettings->ScaleMinX + appFrand() * (MeshSettings->ScaleMaxX - MeshSettings->ScaleMinX);
					Instance.DrawScale3D = FVector(Scale,Scale,Scale);
					bUpdated = TRUE;
				}
			}
			else
			{
				FLOAT LockRand;
				// If we're doing axis scale locking, get an existing scale for a locked axis that we're not changing, for use as the locked scale value.
				if( MeshSettings->LockScaleX && !MeshSettings->ReapplyScaleX && (MeshSettings->ScaleMaxX - MeshSettings->ScaleMinX) > KINDA_SMALL_NUMBER )
				{
					LockRand = (Instance.DrawScale3D.X - MeshSettings->ScaleMinX) / (MeshSettings->ScaleMaxX - MeshSettings->ScaleMinX);
				}
				else
				if( MeshSettings->LockScaleY && !MeshSettings->ReapplyScaleY && (MeshSettings->ScaleMaxY - MeshSettings->ScaleMinY) > KINDA_SMALL_NUMBER )
				{
					LockRand = (Instance.DrawScale3D.Y - MeshSettings->ScaleMinY) / (MeshSettings->ScaleMaxY - MeshSettings->ScaleMinY);
				}
				else
				if( MeshSettings->LockScaleZ && !MeshSettings->ReapplyScaleZ && (MeshSettings->ScaleMaxZ - MeshSettings->ScaleMinZ) > KINDA_SMALL_NUMBER )
				{
					LockRand = (Instance.DrawScale3D.Z - MeshSettings->ScaleMinZ) / (MeshSettings->ScaleMaxZ - MeshSettings->ScaleMinZ);
				}
				else
				{
					LockRand = appFrand();
				}

				if( MeshSettings->ReapplyScaleX )
				{
					Instance.DrawScale3D.X = MeshSettings->ScaleMinX + (MeshSettings->LockScaleX ? LockRand : appFrand()) * (MeshSettings->ScaleMaxX - MeshSettings->ScaleMinX);
					bUpdated = TRUE;
				}

				if( MeshSettings->ReapplyScaleY )
				{
					Instance.DrawScale3D.Y = MeshSettings->ScaleMinY + (MeshSettings->LockScaleY ? LockRand : appFrand()) * (MeshSettings->ScaleMaxY - MeshSettings->ScaleMinY);
					bUpdated = TRUE;
				}

				if( MeshSettings->ReapplyScaleZ )
				{
					Instance.DrawScale3D.Z = MeshSettings->ScaleMinZ + (MeshSettings->LockScaleZ ? LockRand : appFrand()) * (MeshSettings->ScaleMaxZ - MeshSettings->ScaleMinZ);
					bUpdated = TRUE;
				}
			}

			if( MeshSettings->ReapplyZOffset )
			{
				Instance.ZOffset = MeshSettings->ZOffsetMin + appFrand() * (MeshSettings->ZOffsetMax - MeshSettings->ZOffsetMin);
				bUpdated = TRUE;
			}

			// Find a ground normal for either normal or ground slope check.
			if( bReapplyNormal || MeshSettings->ReapplyGroundSlope || (MeshSettings->ReapplyLandscapeLayer && LandscapeLayerName != NAME_None) )
			{
				FCheckResult Hit;
				FVector Start = Instance.Location + FVector(0.f,0.f,16.f);
				FVector End   = Instance.Location - FVector(0.f,0.f,16.f);
				if( !GWorld->SingleLineCheck(Hit, NULL, End, Start, TRACE_World | TRACE_Level, FVector(0.f,0.f,0.f), NULL) ) 
				{
					// Reapply the normal
					if( bReapplyNormal )
					{
						Instance.PreAlignRotation = Instance.Rotation;
						Instance.AlignToNormal( Hit.Normal, MeshSettings->AlignMaxAngle );
					}

					// Cull instances that don't meet the ground slope check.
					if( MeshSettings->ReapplyGroundSlope )
					{
						if( (MeshSettings->GroundSlope > 0.f && Hit.Normal.Z <= appCos(PI * MeshSettings->GroundSlope / 180.f) ||
							MeshSettings->GroundSlope < 0.f && Hit.Normal.Z >= appCos(-PI * MeshSettings->GroundSlope / 180.f)) )
						{
							InstancesToDelete.Add(ExistingInstances(Idx));
							continue;
						}
					}

					// Cull instances for the landscape layer
					if( MeshSettings->ReapplyLandscapeLayer )
					{
						FLOAT HitWeight = 1.f;
						ULandscapeHeightfieldCollisionComponent* HitLandscapeCollision = Cast<ULandscapeHeightfieldCollisionComponent>(Hit.Component);
						if( HitLandscapeCollision )
						{
							ULandscapeComponent* HitLandscape = HitLandscapeCollision->GetLandscapeComponent();
							if( HitLandscape )
							{
								TArray<BYTE>* LayerCache = &LandscapeLayerCache->FindOrAdd(HitLandscape);
								HitWeight = HitLandscape->GetLayerWeightAtLocation( Hit.Location, LandscapeLayerName, LayerCache );

								// Reject instance randomly in proportion to weight
								if( HitWeight <= appFrand() )
								{
									InstancesToDelete.Add(ExistingInstances(Idx));
									continue;
								}
							}					
						}
					}
				}
			}

			// Cull instances that don't meet the height range
			if( MeshSettings->ReapplyHeight )
			{
				if( Instance.Location.Z < MeshSettings->HeightMin || Instance.Location.Z > MeshSettings->HeightMax )
				{
					InstancesToDelete.Add(ExistingInstances(Idx));
					continue;
				}
			}

			if( bUpdated && Abs(Instance.ZOffset) > KINDA_SMALL_NUMBER )
			{
				// Reapply the Z offset in new local space
				Instance.Location = Instance.GetInstanceTransform().TransformFVector(FVector(0,0,Instance.ZOffset));
			}

			// Readd to the hash
			if( bReapplyLocation )
			{
				MeshInfo.InstanceHash->InsertInstance(Instance.Location, InstanceIndex);
			}

			// Cull overlapping based on radius
			if( MeshSettings->ReapplyRadius && MeshSettings->Radius > 0.f )
			{
				INT InstanceIndex = ExistingInstances(Idx);
				if( MeshInfo.CheckForOverlappingInstanceExcluding(InstanceIndex, MeshSettings->Radius, InstancesToDelete) )
				{
					InstancesToDelete.Add(InstanceIndex);
					continue;
				}
			}

			if( bUpdated )
			{
				UpdatedInstances.AddItem(ExistingInstances(Idx));
			}		
		}
	}

	if( UpdatedInstances.Num() > 0 )
	{
		MeshInfo.PostUpdateInstances(IFA, UpdatedInstances);
		IFA->ConditionalUpdateComponents();
	}
	
	if( InstancesToDelete.Num() )
	{
		MeshInfo.RemoveInstances(IFA, InstancesToDelete.Array());
	}
}

// qin@snda
void FEdModeFoliage::AddInstanceForDistribution( AInstancedFoliageActor* IFA, INT Index, FLOAT Density )
{
	//UStaticMesh* StaticMesh = LoadObject<UStaticMesh>( NULL, *MeshName, NULL, LOAD_None, NULL );
	const TArray<UProceduralFoliage*>& ProceduralFoliages = UProceduralFoliage::GetSingleton();
	if (Index < 0 || Index >= ProceduralFoliages.Num())
	{
		return;
	}
	const TArrayNoInit<struct FProceduralFoliageLayerInfo>& ProceduralFoliageLayerInfos = ProceduralFoliages(Index)->ProceduralFoliageLayerInfos;
	const TArrayNoInit<struct FProceduralFoliageMeshInfo>& ProceduralFoliageMeshInfos = ProceduralFoliages(Index)->ProceduralFoliageMeshInfos;

	TMap<ULandscapeComponent*, TArray<BYTE> >* LandscapeLayerCache = NULL;
	if (!GWorld || !GWorld->GetWorldInfo())
	{
		return;
	}

	for (FActorIterator It; It; ++It)
	{
		ALandscapeProxy* Proxy = Cast<ALandscapeProxy>(*It);
		if (!Proxy)
		{
			continue;
		}

		for (TArray<ULandscapeHeightfieldCollisionComponent*>::TIterator It(Proxy->CollisionComponents); It; ++It)
		{
			ULandscapeHeightfieldCollisionComponent* Comp = *It;
			if (!Comp)
			{
				continue;
			}

			ULandscapeComponent* Landscape = Comp->GetLandscapeComponent();
			if( !Landscape )
			{
				continue;
			}

			UMaterialInterface* Material = Landscape->MaterialInstance;
			if (Material == NULL)
			{
				Material = GEngine->DefaultMaterial;
			}

			UTexture* Tex = NULL; 
			FString TextureNames[5];
			TextureNames[0] = TextureNames[1] = TextureNames[2] = TextureNames[3] = TextureNames[4] = "";
			if (Material->GetTextureParameterValue(FName(TEXT("Texture_1")), Tex))
			{
				UTexture2D* Tex2D = CastChecked<UTexture2D>(Tex);
				TextureNames[0] = Tex2D->GetName();
			}
			if (Material->GetTextureParameterValue(FName(TEXT("Texture_2")), Tex))
			{
				UTexture2D* Tex2D = CastChecked<UTexture2D>(Tex);
				TextureNames[1] = Tex2D->GetName();
			}
			if (Material->GetTextureParameterValue(FName(TEXT("Texture_3")), Tex))
			{
				UTexture2D* Tex2D = CastChecked<UTexture2D>(Tex);
				TextureNames[2] = Tex2D->GetName();
			}
			if (Material->GetTextureParameterValue(FName(TEXT("Texture_4")), Tex))
			{
				UTexture2D* Tex2D = CastChecked<UTexture2D>(Tex);
				TextureNames[3] = Tex2D->GetName();
			}
			if (Material->GetTextureParameterValue(FName(TEXT("Texture_5")), Tex))
			{
				UTexture2D* Tex2D = CastChecked<UTexture2D>(Tex);
				TextureNames[4] = Tex2D->GetName();
			}

			const FBoxSphereBounds& CachedBoxSphereBounds = Comp->CachedBoxSphereBounds;
			FLOAT TraceExtentSize = CachedBoxSphereBounds.SphereRadius * 2.f + 10.f;
			FVector TraceVector = Comp->LocalToWorld.GetAxis(2).SafeNormal() * TraceExtentSize;

			FLOAT MinX = CachedBoxSphereBounds.Origin.X - CachedBoxSphereBounds.BoxExtent.X;
			FLOAT MaxX = CachedBoxSphereBounds.Origin.X + CachedBoxSphereBounds.BoxExtent.X;
			FLOAT MinY = CachedBoxSphereBounds.Origin.Y - CachedBoxSphereBounds.BoxExtent.Y;
			FLOAT MaxY = CachedBoxSphereBounds.Origin.Y + CachedBoxSphereBounds.BoxExtent.Y;
			FLOAT Area = (MaxX - MinX) * (MaxY - MinY);
			INT Count = Area * Density / (1000.0f * 1000.0f);
			for (INT i = 0; i < Count; ++i)
			{
				FLOAT X = MinX + appFrand() * (MaxX - MinX);
				FLOAT Y = MinY + appFrand() * (MaxY - MinY);
				FVector Start(X, Y, 100000.0f);
				FVector End(X, Y, -100000.0f);

				//Bruce@snda

				FCheckResult Hit;
				if( !Comp->LineCheck(Hit, End, Start, FVector(0.f,0.f,0.f), 0) )
				{
					FLOAT MaxHitWeight = 0.0f;
					FName LayerNameTemp = NAME_None; 
					for (INT j = 0; j < Landscape->WeightmapLayerAllocations.Num(); ++j)
					{
						FName LayerName = Landscape->WeightmapLayerAllocations(j).LayerName;
						LandscapeLayerCache = &LandscapeLayerCaches.FindOrAdd(LayerName);

						TArray<BYTE>* LayerCache = &LandscapeLayerCache->FindOrAdd(Landscape);
						FLOAT HitWeight = Landscape->GetLayerWeightAtLocation( Hit.Location, LayerName, LayerCache );
						if (HitWeight > MaxHitWeight)
						{
							MaxHitWeight = HitWeight;
							LayerNameTemp = LayerName; 
						}
					}
					if ( LayerNameTemp == NAME_None )
					{
						continue;
					}

					FString TextureName; 

					if ( LayerNameTemp == TEXT("s1") )  
						TextureName = TextureNames[0];
					else if ( LayerNameTemp == TEXT("s2") )  
						TextureName = TextureNames[1];
					else if ( LayerNameTemp == TEXT("s3") )  
						TextureName = TextureNames[2];
					else if ( LayerNameTemp == TEXT("s4") )  
						TextureName = TextureNames[3];
					else if ( LayerNameTemp == TEXT("s5") )  
						TextureName = TextureNames[4];

					INT LayerIndex = -1;
					for (INT k = 0; k < ProceduralFoliageLayerInfos.Num(); ++k)
					{
						UTexture2D* LayerTexture = ProceduralFoliageLayerInfos(k).LayerTexture;
						if (LayerTexture->GetName() == TextureName)
						{
							LayerIndex = k;
							break;
						}
					}
					if (LayerIndex == -1)
					{
						continue;
					}

					const TArrayNoInit<struct FProceduralFoliageInfo>& FoliageInfos = ProceduralFoliageLayerInfos(LayerIndex).FoliageInfos;
					if(FoliageInfos.Num() == 0)
					{
						continue;
					}

					INT Idx = RandRange(0, FoliageInfos.Num() - 0.1f);
					const FProceduralFoliageInfo& FoliageInfo = FoliageInfos(Idx);
					FLOAT Weight = appFrand();

					if ( FoliageInfo.LayerGenerator )
					{
						Weight = FoliageInfo.LayerGenerator->GetWeight(FVector(X, Y, 0.0f));
					}
					
					if (Weight > FoliageInfo.Probability)
					{
						continue;
					}

					UStaticMesh* StaticMesh = FoliageInfo.MeshAsset;

					TArray<struct FSubProceduralFoliageInfo> SubMeshAssetInfo; 
					TArray<UStaticMesh*> SubMeshAssets;
					TArray<FVector> SubMeshOffsets;

					for (INT k = 0; k < ProceduralFoliageMeshInfos.Num(); ++k)
					{
						if (ProceduralFoliageMeshInfos(k).MeshAsset == StaticMesh)
						{
							if (ProceduralFoliageMeshInfos(k).MeshGenerator)
							{
								ProceduralFoliageMeshInfos(k).MeshGenerator->Generate( SubMeshAssetInfo, SubMeshAssets, SubMeshOffsets );
							}
							break;
						}
					}

					if (StaticMesh)
					{
						FFoliageMeshInfo* MeshInfo = IFA->FoliageMeshes.Find(StaticMesh);
						if (!MeshInfo)
						{
							IFA->AddMesh(StaticMesh);
							MeshInfo = IFA->FoliageMeshes.Find(StaticMesh);
						}

						MaxHitWeight = pow( MaxHitWeight, FoliageInfo.WeightPow );

						if ( MeshInfo )
						{
							UInstancedFoliageSettings* MeshSettings = MeshInfo->Settings;
							MeshSettings->ScaleMinX = FoliageInfo.ScaleMinX * MaxHitWeight;
							MeshSettings->ScaleMinY = FoliageInfo.ScaleMinY * MaxHitWeight;
							MeshSettings->ScaleMinZ = FoliageInfo.ScaleMinZ * MaxHitWeight;
							MeshSettings->ScaleMaxX = FoliageInfo.ScaleMaxX * MaxHitWeight;
							MeshSettings->ScaleMaxY = FoliageInfo.ScaleMaxY * MaxHitWeight;
							MeshSettings->ScaleMaxZ = FoliageInfo.ScaleMaxZ * MaxHitWeight;
							MeshSettings->GroundSlope = FoliageInfo.GroundSlope;
							MeshSettings->HeightMin = FoliageInfo.HeightMin;
							MeshSettings->HeightMax = FoliageInfo.HeightMax;
							MeshSettings->AlignToNormal = FoliageInfo.AlignToNormal;
							MeshSettings->RandomYaw = FoliageInfo.RandomYaw;
							MeshSettings->UniformScale = FoliageInfo.UniformScale;
							MeshSettings->RandomPitchAngle = FoliageInfo.RandomPitchAngle;
							MeshSettings->ZOffsetMin = FoliageInfo.ZOffsetMin;
							MeshSettings->ZOffsetMax = FoliageInfo.ZOffsetMax;

							FPotentialInstance PotentialInstance( Hit.Location, Hit.Normal, Hit.Component, MaxHitWeight );
							FFoliageInstance Inst = PotentialInstance.PlaceInstance(MeshSettings);
							MeshInfo->AddInstance( IFA, StaticMesh, Inst );
						}

						for (INT k = 0; k < SubMeshAssets.Num(); ++k)
						{
							UStaticMesh* StaticMesh = SubMeshAssets(k);
							if (!StaticMesh)
							{
								continue;
							}

							FVector Offset = SubMeshOffsets(k);
							FVector Start(X + Offset.X, Y + Offset.Y, 100000.0f);
							FVector End(X + Offset.X, Y + Offset.Y, -100000.0f);
							FCheckResult SubHit;
							if( !Comp->LineCheck(SubHit, End, Start, FVector(0.f,0.f,0.f), 0) )
							{
								FFoliageMeshInfo* MeshInfo = IFA->FoliageMeshes.Find(StaticMesh);
								if (!MeshInfo)
								{
									IFA->AddMesh(StaticMesh);
									MeshInfo = IFA->FoliageMeshes.Find(StaticMesh);
								}	

								FLOAT SubMaxHitWeight = 0.0f;
								for (INT j = 0; j < Landscape->WeightmapLayerAllocations.Num(); ++j)
								{
									FName LayerName = Landscape->WeightmapLayerAllocations(j).LayerName;
									LandscapeLayerCache = &LandscapeLayerCaches.FindOrAdd(LayerName);

									TArray<BYTE>* LayerCache = &LandscapeLayerCache->FindOrAdd(Landscape);
									FLOAT SubHitWeight = Landscape->GetLayerWeightAtLocation( SubHit.Location, LayerName, LayerCache );
									if ( SubHitWeight > SubMaxHitWeight )
									{
										SubMaxHitWeight = SubHitWeight;
									}
								}

								SubMaxHitWeight = pow( SubMaxHitWeight, FoliageInfo.WeightPow );

								if (MeshInfo)
								{
									UInstancedFoliageSettings* MeshSettings = MeshInfo->Settings;
									MeshSettings->ScaleMinX = SubMeshAssetInfo(k).ScaleMinX * SubMaxHitWeight;
									MeshSettings->ScaleMinY = SubMeshAssetInfo(k).ScaleMinY * SubMaxHitWeight;
									MeshSettings->ScaleMinZ = SubMeshAssetInfo(k).ScaleMinZ * SubMaxHitWeight;
									MeshSettings->ScaleMaxX = SubMeshAssetInfo(k).ScaleMaxX * SubMaxHitWeight;
									MeshSettings->ScaleMaxY = SubMeshAssetInfo(k).ScaleMaxY * SubMaxHitWeight;
									MeshSettings->ScaleMaxZ = SubMeshAssetInfo(k).ScaleMaxZ * SubMaxHitWeight;
									MeshSettings->GroundSlope = SubMeshAssetInfo(k).GroundSlope;
									MeshSettings->HeightMin = SubMeshAssetInfo(k).HeightMin;
									MeshSettings->HeightMax = SubMeshAssetInfo(k).HeightMax;
									MeshSettings->AlignToNormal = SubMeshAssetInfo(k).AlignToNormal;
									MeshSettings->RandomYaw = SubMeshAssetInfo(k).RandomYaw;
									MeshSettings->UniformScale = SubMeshAssetInfo(k).UniformScale;
									MeshSettings->RandomPitchAngle = SubMeshAssetInfo(k).RandomPitchAngle;
									MeshSettings->ZOffsetMin = SubMeshAssetInfo(k).ZOffsetMin;
									MeshSettings->ZOffsetMax = SubMeshAssetInfo(k).ZOffsetMax;

									FPotentialInstance PotentialInstance( SubHit.Location, SubHit.Normal, SubHit.Component, MaxHitWeight );
									FFoliageInstance Inst = PotentialInstance.PlaceInstance( MeshSettings );
									MeshInfo->AddInstance( IFA, StaticMesh, Inst );
								}
								//Bruce@snda
							}
						}
					}
				}
			}
		}
	}
}

// qin@snda
void FEdModeFoliage::ClearInstancesForDistribution( AInstancedFoliageActor* IFA, UStaticMesh* StaticMesh, FFoliageMeshInfo& MeshInfo )
{
	UInstancedFoliageSettings* MeshSettings = MeshInfo.Settings;

	TArray<INT> InstancesToRemove;
	for (INT i = MeshInfo.Instances.Num() - 1; i >= 0; --i)
	{
		BOOL Found = false;
		for (INT j = 0; j < MeshInfo.FreeInstanceIndices.Num(); ++j)
		{
			if (i == MeshInfo.FreeInstanceIndices(j))
			{
				Found = true;
				break;
			}
		}
		if (!Found)
		{
			InstancesToRemove.AddItem(i);
		}
	}
	MeshInfo.RemoveInstances(IFA, InstancesToRemove);
}

void FEdModeFoliage::ApplyBrush( FEditorLevelViewportClient* ViewportClient )
{
	if( !bBrushTraceValid )
	{
		return;
	}

	AInstancedFoliageActor* IFA = AInstancedFoliageActor::GetInstancedFoliageActor();

	FLOAT BrushArea = PI * Square(UISettings.GetRadius());

	// Tablet pressure
	FLOAT Pressure = ViewportClient->Viewport->IsPenActive() ? ViewportClient->Viewport->GetTabletPressure() : 1.f;

	for( TMap<class UStaticMesh*, struct FFoliageMeshInfo>::TIterator MeshIt(IFA->FoliageMeshes); MeshIt; ++MeshIt )
	{
		FFoliageMeshInfo& MeshInfo = MeshIt.Value();
		UInstancedFoliageSettings* MeshSettings = MeshInfo.Settings;

		if( MeshSettings->IsSelected )
		{
			// Find the instances already in the area.
			TArray<INT> Instances;
			FSphere BrushSphere(BrushLocation,UISettings.GetRadius());
			MeshInfo.GetInstancesInsideSphere( BrushSphere, Instances );

			if( UISettings.GetLassoSelectToolSelected() )
			{
				// Shift unpaints
				MeshInfo.SelectInstances( IFA, !IsShiftDown(ViewportClient->Viewport), Instances);
			}
			else
			if( UISettings.GetReapplyToolSelected() )
			{
				if( MeshSettings->ReapplyDensity )
				{
					// Adjust instance density
					FMeshInfoSnapshot* SnapShot = InstanceSnapshot.Find(MeshIt.Key());
					if( SnapShot ) 
					{
						// Use snapshot to determine number of instances at the start of the brush stroke
						INT NewInstanceCount = appRound( (FLOAT)SnapShot->CountInstancesInsideSphere(BrushSphere) * MeshSettings->ReapplyDensityAmount );
						if( MeshSettings->ReapplyDensityAmount > 1.f && NewInstanceCount > Instances.Num() )
						{
							AddInstancesForBrush( IFA, MeshIt.Key(), MeshInfo, NewInstanceCount, Instances, Pressure );
						}
						else
						if( MeshSettings->ReapplyDensityAmount < 1.f && NewInstanceCount < Instances.Num() )			
						{
							RemoveInstancesForBrush( IFA, MeshInfo, NewInstanceCount, Instances, Pressure );
						}
					}
				}

				// Reapply any settings checked by the user
				ReapplyInstancesForBrush( IFA, MeshInfo, Instances );
			}
			else
			if( UISettings.GetPaintToolSelected() )
			{	
				// Shift unpaints
				if( IsShiftDown(ViewportClient->Viewport) )
				{
					INT DesiredInstanceCount =  appRound(BrushArea * MeshSettings->Density * UISettings.GetUnpaintDensity() / (1000.f*1000.f));

					if( DesiredInstanceCount < Instances.Num() )
					{
						RemoveInstancesForBrush( IFA, MeshInfo, DesiredInstanceCount, Instances, Pressure );
					}
				}
				else
				{
					// This is the total set of instances disregarding parameters like slope, height or layer.
					FLOAT DesiredInstanceCountFloat = BrushArea * MeshSettings->Density * UISettings.GetPaintDensity() / (1000.f*1000.f);

					// Allow a single instance with a random chance, if the brush is smaller than the density
					INT DesiredInstanceCount = DesiredInstanceCountFloat > 1.f ? appRound(DesiredInstanceCountFloat) : appFrand() < DesiredInstanceCountFloat ? 1 : 0;

					AddInstancesForBrush( IFA, MeshIt.Key(), MeshInfo, DesiredInstanceCount, Instances, Pressure );
				}
			}
		}
	}
	if( UISettings.GetLassoSelectToolSelected() )
	{
		IFA->CheckSelection();
		FEditorModeTools& Tools = GEditorModeTools();
		Tools.PivotLocation = Tools.SnappedLocation = IFA->GetSelectionLocation();
		IFA->ConditionalUpdateComponents();
	}
}

struct FFoliagePaintBucketTriangle
{
	FFoliagePaintBucketTriangle(const FStaticMeshTriangle InSMTriangle, const FMatrix& InLocalToWorld)
	{
		Vertex = InLocalToWorld.TransformFVector(InSMTriangle.Vertices[0]);
		Vector1 = InLocalToWorld.TransformFVector(InSMTriangle.Vertices[1]) - Vertex;
		Vector2 = InLocalToWorld.TransformFVector(InSMTriangle.Vertices[2]) - Vertex;
		VertexColor[0] = InSMTriangle.Colors[0];
		VertexColor[1] = InSMTriangle.Colors[1];
		VertexColor[2] = InSMTriangle.Colors[2];

		WorldNormal = Vector2 ^ Vector1;
		FLOAT WorldNormalSize = WorldNormal.Size();
		Area = WorldNormalSize * 0.5f;
		if( WorldNormalSize > SMALL_NUMBER )
		{
			WorldNormal /= WorldNormalSize;
		}
	}

	FVector GetRandomPoint()
	{
		// Sample parallelogram
		FLOAT x = appFrand();
		FLOAT y = appFrand();

		// Flip if we're outside the triangle
		if ( x + y > 1.f )
		{ 
			x = 1.f-x;
			y = 1.f-y;
		}

		return Vertex + x * Vector1 + y * Vector2;
	}

	FVector	Vertex;
	FVector Vector1;
	FVector Vector2;
	FVector WorldNormal;
	FLOAT Area;
	FColor VertexColor[3];
};

/** Apply paint bucket to actor */
void FEdModeFoliage::ApplyPaintBucket(AActor* Actor, UBOOL bRemove)
{
	// Apply only to current world
	if( Actor->GetOutermost() != GWorld->CurrentLevel->GetOutermost() )
	{
		return;
	}

	if( bRemove )
	{
		// Remove all instances of the selected meshes
		AInstancedFoliageActor* IFA = AInstancedFoliageActor::GetInstancedFoliageActor();

		for( INT ComponentIdx=0;ComponentIdx<Actor->Components.Num();ComponentIdx++ )
		{
			for( TMap<class UStaticMesh*, struct FFoliageMeshInfo>::TIterator MeshIt(IFA->FoliageMeshes); MeshIt; ++MeshIt )
			{
				FFoliageMeshInfo& MeshInfo = MeshIt.Value();
				UInstancedFoliageSettings* MeshSettings = MeshInfo.Settings;

				if( MeshSettings->IsSelected )
				{
					FFoliageComponentHashInfo* ComponentHashInfo = MeshInfo.ComponentHash.Find(Actor->Components(ComponentIdx));
					if( ComponentHashInfo )
					{
						TArray<INT> InstancesToRemove = ComponentHashInfo->Instances.Array();
						MeshInfo.RemoveInstances( IFA, InstancesToRemove );
					}
				}
			}
		}
	}
	else
	{
		TMap<UPrimitiveComponent*, TArray<FFoliagePaintBucketTriangle> > ComponentPotentialTriangles;

		FMatrix LocalToWorld = Actor->LocalToWorld();
		// Check all the components of the hit actor
		for( INT ComponentIdx=0;ComponentIdx<Actor->Components.Num();ComponentIdx++ )
		{
			UStaticMeshComponent* StaticMeshComponent = Cast<UStaticMeshComponent>(Actor->Components(ComponentIdx));
			if( StaticMeshComponent && UISettings.bFilterStaticMesh && StaticMeshComponent->StaticMesh )
			{
				UStaticMesh* StaticMesh = StaticMeshComponent->StaticMesh;
				TArray<FFoliagePaintBucketTriangle>& PotentialTriangles = ComponentPotentialTriangles.Set(StaticMeshComponent, TArray<FFoliagePaintBucketTriangle>() );

				// Get the raw triangle data for this static mesh
				const FStaticMeshTriangle* RawTriangleData = (FStaticMeshTriangle*)StaticMesh->LODModels(0).RawTriangles.Lock(LOCK_READ_ONLY);
				for(INT TriangleIndex = 0;TriangleIndex < StaticMesh->LODModels(0).RawTriangles.GetElementCount();TriangleIndex++)
				{
					new(PotentialTriangles) FFoliagePaintBucketTriangle(RawTriangleData[TriangleIndex], LocalToWorld);
				}

				StaticMesh->LODModels(0).RawTriangles.Unlock();	
			}
		}

		// Place foliage
		AInstancedFoliageActor* IFA = AInstancedFoliageActor::GetInstancedFoliageActor();

		for( TMap<class UStaticMesh*, struct FFoliageMeshInfo>::TIterator MeshIt(IFA->FoliageMeshes); MeshIt; ++MeshIt )
		{
			FFoliageMeshInfo& MeshInfo = MeshIt.Value();
			UInstancedFoliageSettings* MeshSettings = MeshInfo.Settings;

			if( MeshSettings->IsSelected )
			{
				// Quick lookup of potential instance locations, used for overlapping check.
				TArray<FVector> PotentialInstanceLocations;
				FFoliageInstanceHash PotentialInstanceHash(7);	// use 128x128 cell size, as the brush radius is typically small.
				TArray<FPotentialInstance> InstancesToPlace;

				// Radius where we expect to have a single instance, given the density rules
				const FLOAT DensityCheckRadius = Max<FLOAT>( appSqrt( (1000.f*1000.f) / (PI * MeshSettings->Density * UISettings.GetPaintDensity() ) ), MeshSettings->Radius );

				for( TMap<UPrimitiveComponent*, TArray<FFoliagePaintBucketTriangle> >::TIterator ComponentIt(ComponentPotentialTriangles); ComponentIt; ++ComponentIt )
				{
					UPrimitiveComponent* Component = ComponentIt.Key();
					TArray<FFoliagePaintBucketTriangle>& PotentialTriangles = ComponentIt.Value();

					for( INT TriIdx=0;TriIdx<PotentialTriangles.Num();TriIdx++ )
					{
						FFoliagePaintBucketTriangle& Triangle = PotentialTriangles(TriIdx);

						// Check if we can reject this triangle based on normal.
						if( (MeshSettings->GroundSlope > 0.f && Triangle.WorldNormal.Z <= appCos(PI * MeshSettings->GroundSlope / 180.f) ||
							MeshSettings->GroundSlope < 0.f && Triangle.WorldNormal.Z >= appCos(-PI * MeshSettings->GroundSlope / 180.f)) )
						{
							continue;
						}

						// This is the total set of instances disregarding parameters like slope, height or layer.
						FLOAT DesiredInstanceCountFloat = Triangle.Area * MeshSettings->Density * UISettings.GetPaintDensity() / (1000.f*1000.f);

						// Allow a single instance with a random chance, if the brush is smaller than the density
						INT DesiredInstanceCount = DesiredInstanceCountFloat > 1.f ? appRound(DesiredInstanceCountFloat) : appFrand() < DesiredInstanceCountFloat ? 1 : 0;
				
						for( INT Idx=0;Idx<DesiredInstanceCount;Idx++ )
						{
							FVector InstLocation = Triangle.GetRandomPoint();

							// Check filters at this location
							if( !CheckLocationForPotentialInstance( MeshInfo, MeshSettings, DensityCheckRadius, InstLocation, Triangle.WorldNormal, PotentialInstanceLocations, PotentialInstanceHash ) )
							{
								continue;
							}

							new(InstancesToPlace) FPotentialInstance( InstLocation, Triangle.WorldNormal, Component, 1.f );
						}
						}
					}

				// Place instances
				for( INT Idx=0;Idx<InstancesToPlace.Num();Idx++ )
				{
					FFoliageInstance Inst = InstancesToPlace(Idx).PlaceInstance(MeshSettings);
					MeshInfo.AddInstance( IFA, MeshIt.Key(), Inst );
				}
			}
		}
	}
}

// qin@snda
void FEdModeFoliage::ApplyDistribution(INT Index, FLOAT Density)
{
	AInstancedFoliageActor* IFA = AInstancedFoliageActor::GetInstancedFoliageActor();

	for( TMap<class UStaticMesh*, struct FFoliageMeshInfo>::TIterator MeshIt(IFA->FoliageMeshes); MeshIt; ++MeshIt )
	{
		FFoliageMeshInfo& MeshInfo = MeshIt.Value();
		ClearInstancesForDistribution(IFA, MeshIt.Key(), MeshInfo);
	}

	AddInstanceForDistribution(IFA, Index, Density);
	UpdateFoliageMeshList();
}

//shanling@snda
void FEdModeFoliage::ReBuildFoligeComponent()
{
	AInstancedFoliageActor* IFA = AInstancedFoliageActor::GetInstancedFoliageActor();
	IFA->ReBluildFoliagBaseComponent( UISettings.bFilterLandscape,
		UISettings.bFilterStaticMesh,
		UISettings.bFilterBSP,
		UISettings.bFilterTerrain);
}

IMPLEMENT_COMPARE_CONSTREF( FFoliageMeshUIInfo, FoliageEdMode, { return A.MeshInfo->Settings->DisplayOrder - B.MeshInfo->Settings->DisplayOrder; } );

/** Get list of meshs for current level for UI */

TArray<struct FFoliageMeshUIInfo>& FEdModeFoliage::GetFoliageMeshList()
{
	UpdateFoliageMeshList(); 
	return FoliageMeshList;
}

void FEdModeFoliage::UpdateFoliageMeshList()
{
	FoliageMeshList.Empty();

	AInstancedFoliageActor* IFA = AInstancedFoliageActor::GetInstancedFoliageActor();

	for( TMap<class UStaticMesh*, struct FFoliageMeshInfo>::TIterator MeshIt(IFA->FoliageMeshes); MeshIt; ++MeshIt )
	{
		new(FoliageMeshList) FFoliageMeshUIInfo(MeshIt.Key(), &MeshIt.Value());
	}

	Sort<USE_COMPARE_CONSTREF(FFoliageMeshUIInfo,FoliageEdMode)>( &FoliageMeshList(0), FoliageMeshList.Num() );
}

/** Add a new mesh */
void FEdModeFoliage::AddFoliageMesh(UStaticMesh* StaticMesh)
{
	AInstancedFoliageActor* IFA = AInstancedFoliageActor::GetInstancedFoliageActor();
	if( IFA->FoliageMeshes.Find(StaticMesh) == NULL )
	{
		IFA->AddMesh(StaticMesh);

		// Update mesh list.
		UpdateFoliageMeshList();
	}
}

/** Remove a mesh */
void FEdModeFoliage::RemoveFoliageMesh(UStaticMesh* StaticMesh)
{
	AInstancedFoliageActor* IFA = AInstancedFoliageActor::GetInstancedFoliageActor();
	FFoliageMeshInfo* MeshInfo = IFA->FoliageMeshes.Find(StaticMesh);
	if( MeshInfo != NULL )
	{
		INT InstancesNum = MeshInfo->Instances.Num() - MeshInfo->FreeInstanceIndices.Num();
		if( InstancesNum == 0 ||
			appMsgf(AMT_YesNo, LocalizeSecure(LocalizeUnrealEd("FoliageMode_DeleteMesh"), InstancesNum, *StaticMesh->GetName() )) == ART_Yes )
		{
			GEditor->BeginTransaction( *LocalizeUnrealEd("FoliageMode_RemoveMeshTransaction") );
			IFA->RemoveMesh(StaticMesh);
			GEditor->EndTransaction();
		}		

		// Update mesh list.
		UpdateFoliageMeshList();
	}
}

/** Bake instances to StaticMeshActors */
void FEdModeFoliage::BakeFoliage(UStaticMesh* StaticMesh, UBOOL bSelectedOnly)
{
	AInstancedFoliageActor* IFA = AInstancedFoliageActor::GetInstancedFoliageActor();
	FFoliageMeshInfo* MeshInfo = IFA->FoliageMeshes.Find(StaticMesh);
	if( MeshInfo != NULL )
	{
		TArray<INT> InstancesToConvert;
		if( bSelectedOnly )
		{
			InstancesToConvert = MeshInfo->SelectedIndices;	
		}
		else
		{
			for( INT InstanceIdx=0;InstanceIdx<MeshInfo->Instances.Num();InstanceIdx++ )
			{
				InstancesToConvert.AddItem(InstanceIdx);
			}
		}

		// Convert
		for( INT Idx=0;Idx<InstancesToConvert.Num();Idx++ )
		{
			FFoliageInstance& Instance = MeshInfo->Instances(InstancesToConvert(Idx));
			AStaticMeshActor* SMA = Cast<AStaticMeshActor>(GWorld->SpawnActor(AStaticMeshActor::StaticClass(), NAME_None, Instance.Location, Instance.Rotation));
			SMA->StaticMeshComponent->StaticMesh = StaticMesh;
			SMA->DrawScale3D = Instance.DrawScale3D;		
			SMA->ConditionalUpdateComponents();
		}

		// Remove
		MeshInfo->RemoveInstances(IFA, InstancesToConvert);
	}
}

/** Copy the settings object for this static mesh */
void FEdModeFoliage::CopySettingsObject(UStaticMesh* StaticMesh)
{
	AInstancedFoliageActor* IFA = AInstancedFoliageActor::GetInstancedFoliageActor();
	FFoliageMeshInfo* MeshInfo = IFA->FoliageMeshes.Find(StaticMesh);
	if( MeshInfo )
	{
		GEditor->BeginTransaction( *LocalizeUnrealEd("FoliageMode_SettingsObjectTransaction") );
		IFA->Modify();
		MeshInfo->Settings = Cast<UInstancedFoliageSettings>(UObject::StaticDuplicateObject(MeshInfo->Settings,MeshInfo->Settings,IFA,TEXT("None")));
		MeshInfo->Settings->ClearFlags(RF_Standalone|RF_Public);
		GEditor->EndTransaction();
	}
}

/** Replace the settings object for this static mesh with the one specified */
void FEdModeFoliage::ReplaceSettingsObject(UStaticMesh* StaticMesh, UInstancedFoliageSettings* NewSettings)
{
	AInstancedFoliageActor* IFA = AInstancedFoliageActor::GetInstancedFoliageActor();
	FFoliageMeshInfo* MeshInfo = IFA->FoliageMeshes.Find(StaticMesh);

	if( MeshInfo )
	{
		GEditor->BeginTransaction( *LocalizeUnrealEd("FoliageMode_SettingsObjectTransaction") );
		IFA->Modify();
		MeshInfo->Settings = NewSettings;
		GEditor->EndTransaction();
	}
}

/** Save the settings object */
void FEdModeFoliage::SaveSettingsObject(UStaticMesh* StaticMesh)
{
	AInstancedFoliageActor* IFA = AInstancedFoliageActor::GetInstancedFoliageActor();
	FFoliageMeshInfo* MeshInfo = IFA->FoliageMeshes.Find(StaticMesh);

	if( MeshInfo )
	{
		// pop up the factory new dialog so the user can pick name/package
		FString DefaultPackage = *StaticMesh->GetOutermost()->GetName();
		FString DefaultGroup = TEXT("");
		FString DefaultName = StaticMesh->GetName() + TEXT("_FoliageSettings");

		WxDlgPackageGroupName dlg;
		if( dlg.ShowModal(DefaultPackage, DefaultGroup, DefaultName) == wxID_OK )
		{
			UPackage* NewPackage = NULL;
			FString NewObjName;
			UBOOL bValidPackage = dlg.ProcessNewAssetDlg(&NewPackage, &NewObjName, FALSE, UInstancedFoliageSettings::StaticClass());
			if(bValidPackage)
			{
				GEditor->BeginTransaction( *LocalizeUnrealEd("FoliageMode_SettingsObjectTransaction") );
				IFA->Modify();
				MeshInfo->Settings = Cast<UInstancedFoliageSettings>(UObject::StaticDuplicateObject(MeshInfo->Settings,MeshInfo->Settings,NewPackage,*NewObjName));
				MeshInfo->Settings->SetFlags(RF_Standalone|RF_Public);
				GEditor->EndTransaction();

				// Notify the content browser of the newly created asset
				GCallbackEvent->Send( FCallbackEventParameters( NULL, CALLBACK_RefreshContentBrowser, CBR_ObjectCreated, MeshInfo->Settings ) );
			}
		}		
	}
}


/** Replace a mesh with another one */
void FEdModeFoliage::ReplaceStaticMesh(UStaticMesh* OldStaticMesh, UStaticMesh* NewStaticMesh)
{
	AInstancedFoliageActor* IFA = AInstancedFoliageActor::GetInstancedFoliageActor();
	FFoliageMeshInfo* OldMeshInfo = IFA->FoliageMeshes.Find(OldStaticMesh);

	if( OldMeshInfo != NULL && OldStaticMesh != NewStaticMesh )
	{
		INT InstancesNum = OldMeshInfo->Instances.Num() - OldMeshInfo->FreeInstanceIndices.Num();

		// Look for the new mesh in the mesh list, and either create a new mesh or merge the instances.
		FFoliageMeshInfo* NewMeshInfo = IFA->FoliageMeshes.Find(NewStaticMesh);
		if( NewMeshInfo == NULL )
		{
			if( InstancesNum > 0 &&
				appMsgf(AMT_YesNo, LocalizeSecure(LocalizeUnrealEd("FoliageMode_ReplaceMesh"), InstancesNum, *OldStaticMesh->GetName(), *NewStaticMesh->GetName())) != ART_Yes )
			{
				return;
			}
			GEditor->BeginTransaction( *LocalizeUnrealEd("FoliageMode_ChangeStaticMeshTransaction") );
			IFA->Modify();
			NewMeshInfo = IFA->AddMesh(NewStaticMesh);
			NewMeshInfo->Settings->DisplayOrder          = OldMeshInfo->Settings->DisplayOrder;
			NewMeshInfo->Settings->ShowNothing          = OldMeshInfo->Settings->ShowNothing;
			NewMeshInfo->Settings->ShowPaintSettings    = OldMeshInfo->Settings->ShowPaintSettings;
			NewMeshInfo->Settings->ShowInstanceSettings = OldMeshInfo->Settings->ShowInstanceSettings;
		}
		else
		if( InstancesNum > 0 &&
			appMsgf(AMT_YesNo, LocalizeSecure(LocalizeUnrealEd("FoliageMode_ReplaceMeshMerge"), InstancesNum, *OldStaticMesh->GetName(), *NewStaticMesh->GetName())) != ART_Yes )
		{
			return;
		}
		else
		{
			GEditor->BeginTransaction( *LocalizeUnrealEd("FoliageMode_ChangeStaticMeshTransaction") );
			IFA->Modify();
		}

		if( InstancesNum > 0 )
		{
			// copy instances from old to new.
			for( INT Idx=0;Idx<OldMeshInfo->Instances.Num();Idx++ )
			{
				if( OldMeshInfo->Instances(Idx).ClusterIndex != -1 )
				{
					NewMeshInfo->AddInstance( IFA, NewStaticMesh, OldMeshInfo->Instances(Idx) );
				}
			}
		}

		// Remove the old mesh.
		IFA->RemoveMesh(OldStaticMesh);

		GEditor->EndTransaction();

		// Update mesh list.
		UpdateFoliageMeshList();
	}
}


/** FEdMode: Called when a key is pressed */
UBOOL FEdModeFoliage::InputKey( FEditorLevelViewportClient* ViewportClient, FViewport* Viewport, FName Key, EInputEvent Event )
{
	if( UISettings.GetPaintToolSelected() || UISettings.GetReapplyToolSelected() || UISettings.GetLassoSelectToolSelected() )
	{
		if( Key == KEY_LeftMouseButton && Event == IE_Pressed && IsCtrlDown(Viewport) )
		{
			if( !bToolActive )
			{
				GEditor->BeginTransaction( *LocalizeUnrealEd("FoliageMode_EditTransaction") );
				InstanceSnapshot.Empty();

				// Special setup beginning a stroke with the Reapply tool
				// Necessary so we don't keep reapplying settings over and over for the same instances.
				if( UISettings.GetReapplyToolSelected() )
				{
					AInstancedFoliageActor* IFA = AInstancedFoliageActor::GetInstancedFoliageActor();
					for( TMap<class UStaticMesh*, struct FFoliageMeshInfo>::TIterator MeshIt(IFA->FoliageMeshes); MeshIt; ++MeshIt )
					{
						FFoliageMeshInfo& MeshInfo = MeshIt.Value();
						if( MeshInfo.Settings->IsSelected )
						{
							// Take a snapshot of all the locations
							InstanceSnapshot.Set( MeshIt.Key(), FMeshInfoSnapshot(&MeshInfo) ) ;

							// Clear the "FOLIAGE_Readjusted" flag
							for( INT Idx=0;Idx<MeshInfo.Instances.Num();Idx++ )
							{
								MeshInfo.Instances(Idx).Flags &= (~FOLIAGE_Readjusted);
							}							
						}
					}
				}
			}
			ApplyBrush(ViewportClient);
			bToolActive = TRUE;
			return TRUE;
		}

		if( Event == IE_Released && bToolActive && (Key == KEY_LeftMouseButton || Key==KEY_LeftControl || Key==KEY_RightControl) )
		{
			GEditor->EndTransaction();
			InstanceSnapshot.Empty();
			LandscapeLayerCaches.Empty();
	#if WITH_MANAGED_CODE
			FoliageEditWindow->RefreshMeshListProperties();
	#endif
			bToolActive = FALSE;
			return TRUE;
		}
	}

	if( UISettings.GetSelectToolSelected() || UISettings.GetLassoSelectToolSelected() )
	{
		if( Event == IE_Pressed )
		{
			if( Key == KEY_Delete )
			{
				GEditor->BeginTransaction( *LocalizeUnrealEd("FoliageMode_EditTransaction") );
				AInstancedFoliageActor* IFA = AInstancedFoliageActor::GetInstancedFoliageActor();
				IFA->Modify();
				for( TMap<class UStaticMesh*, struct FFoliageMeshInfo>::TIterator MeshIt(IFA->FoliageMeshes); MeshIt; ++MeshIt )
				{
					FFoliageMeshInfo& Mesh = MeshIt.Value();
					if( Mesh.SelectedIndices.Num() > 0 )
					{
						TArray<INT> InstancesToDelete = Mesh.SelectedIndices;
						Mesh.RemoveInstances(IFA, InstancesToDelete);
					}
				}
				GEditor->EndTransaction();

#if WITH_MANAGED_CODE
				FoliageEditWindow->RefreshMeshListProperties();
#endif
				return TRUE;
			}
			else
			if( Key == KEY_End )
			{
				// Snap instances to ground
				AInstancedFoliageActor* IFA = AInstancedFoliageActor::GetInstancedFoliageActor();
				IFA->Modify();
				UBOOL bMovedInstance = FALSE;
				for( TMap<class UStaticMesh*, struct FFoliageMeshInfo>::TIterator MeshIt(IFA->FoliageMeshes); MeshIt; ++MeshIt )
				{
					FFoliageMeshInfo& Mesh = MeshIt.Value();
					
					Mesh.PreMoveInstances(IFA, Mesh.SelectedIndices);

					for( INT SelectionIdx=0;SelectionIdx<Mesh.SelectedIndices.Num();SelectionIdx++ )
					{
						INT InstanceIdx = Mesh.SelectedIndices(SelectionIdx);

						FFoliageInstance& Instance = Mesh.Instances(InstanceIdx);

						FVector Start = Instance.Location;
						FVector End = Instance.Location - FVector(0.f,0.f,FOLIAGE_SNAP_TRACE);

						FCheckResult Hit;
						if( !GWorld->SingleLineCheck(Hit, NULL, End, Start, TRACE_World | TRACE_Level, FVector(0.f,0.f,0.f), NULL) )
						{
							// Check current level
							if( (Hit.Component && Hit.Component->GetOutermost() == GWorld->CurrentLevel->GetOutermost()) ||
								(Hit.Actor && Hit.Actor->IsA(AWorldInfo::StaticClass()) || GWorld->Levels(Hit.LevelIndex) != GWorld->CurrentLevel) )
							{
								Instance.Location = Hit.Location;
								Instance.ZOffset = 0.f;
								Instance.Base = Hit.Component;

								if( Instance.Flags & FOLIAGE_AlignToNormal )
								{
									// Remove previous alignment and align to new normal.
									Instance.Rotation = Instance.PreAlignRotation;
									Instance.AlignToNormal( Hit.Normal, Mesh.Settings->AlignMaxAngle );
								}
							}
						}

						bMovedInstance = TRUE;
					}

					Mesh.PostMoveInstances(IFA, Mesh.SelectedIndices);
				}

				if( bMovedInstance )
				{
					FEditorModeTools& Tools = GEditorModeTools();
					Tools.PivotLocation = Tools.SnappedLocation = IFA->GetSelectionLocation();
					IFA->ConditionalUpdateComponents();
				}

				return TRUE;
			}
		}
	}

	return FALSE;
}

/** FEdMode: Render the foliage edit mode */
void FEdModeFoliage::Render( const FSceneView* View, FViewport* Viewport, FPrimitiveDrawInterface* PDI )
{
	/** Call parent implementation */
	FEdMode::Render( View, Viewport, PDI );
}


/** FEdMode: Render HUD elements for this tool */
void FEdModeFoliage::DrawHUD( FEditorLevelViewportClient* ViewportClient, FViewport* Viewport, const FSceneView* View, FCanvas* Canvas )
{
}

UBOOL FEdModeFoliage::Select( AActor* InActor, UBOOL bInSelected )
{
	// return TRUE if you filter that selection
	return TRUE;
}

/** FEdMode: Called when the currently selected actor has changed */
void FEdModeFoliage::ActorSelectionChangeNotify()
{
}


/** Forces real-time perspective viewports */
void FEdModeFoliage::ForceRealTimeViewports( const UBOOL bEnable, const UBOOL bStoreCurrentState )
{
	// Force perspective views to be real-time
	for( INT CurViewportIndex = 0; CurViewportIndex < GApp->EditorFrame->ViewportConfigData->GetViewportCount(); ++CurViewportIndex )
	{
		WxLevelViewportWindow* CurLevelViewportWindow =
			GApp->EditorFrame->ViewportConfigData->AccessViewport( CurViewportIndex ).ViewportWindow;
		if( CurLevelViewportWindow != NULL )
		{
			if( CurLevelViewportWindow->ViewportType == LVT_Perspective )
			{				
				if( bEnable )
				{
					CurLevelViewportWindow->SetRealtime( bEnable, bStoreCurrentState );
				}
				else
				{
					CurLevelViewportWindow->RestoreRealtime(TRUE);
				}
			}
		}
	}
}

UBOOL FEdModeFoliage::HandleClick( HHitProxy *HitProxy, const FViewportClick &Click )
{
	AInstancedFoliageActor* IFA = AInstancedFoliageActor::GetInstancedFoliageActor();

	if( UISettings.GetSelectToolSelected() )
	{
		if( HitProxy && HitProxy->IsA(HInstancedStaticMeshInstance::StaticGetType()) )
		{
			HInstancedStaticMeshInstance* SMIProxy = ( ( HInstancedStaticMeshInstance* )HitProxy );

			IFA->SelectInstance( SMIProxy->Component, SMIProxy->InstanceIndex, Click.IsControlDown() );

			// Update pivot
			FEditorModeTools& Tools = GEditorModeTools();
			Tools.PivotLocation = Tools.SnappedLocation = IFA->GetSelectionLocation();
		}
		else
		{
			if( !Click.IsControlDown() )
			{
				// Select none if not trying to toggle
				IFA->SelectInstance( NULL, -1, FALSE );
			}
		}

		return TRUE;
	}
	else
	if( UISettings.GetPaintBucketToolSelected() || UISettings.GetReapplyPaintBucketToolSelected() )
	{
		if( HitProxy && HitProxy->IsA(HActor::StaticGetType()) && Click.IsControlDown() )
		{
			ApplyPaintBucket( ((HActor*)HitProxy)->Actor, Click.IsShiftDown() );
#if WITH_MANAGED_CODE
			FoliageEditWindow->RefreshMeshListProperties();
#endif
		}

		return TRUE;
	}

	return FEdMode::HandleClick(HitProxy, Click);
}

FVector FEdModeFoliage::GetWidgetLocation() const
{
	return FEdMode::GetWidgetLocation();
}

/** FEdMode: Called when a mouse button is pressed */
UBOOL FEdModeFoliage::StartTracking()
{
	if( UISettings.GetSelectToolSelected() || UISettings.GetLassoSelectToolSelected() )
	{
		// Update pivot
		AInstancedFoliageActor* IFA = AInstancedFoliageActor::GetInstancedFoliageActor();
		FEditorModeTools& Tools = GEditorModeTools();
		Tools.PivotLocation = Tools.SnappedLocation = IFA->GetSelectionLocation();

		GEditor->BeginTransaction( *LocalizeUnrealEd("FoliageMode_EditTransaction") );
		
		bCanAltDrag = TRUE;
	
		return TRUE;
	}
	return FEdMode::StartTracking();
}

/** FEdMode: Called when the a mouse button is released */
UBOOL FEdModeFoliage::EndTracking()
{
	if( UISettings.GetSelectToolSelected() || UISettings.GetLassoSelectToolSelected() )
	{
		GEditor->EndTransaction();
		return TRUE;
	}
	return FEdMode::EndTracking();
}

/** FEdMode: Called when mouse drag input it applied */
UBOOL FEdModeFoliage::InputDelta( FEditorLevelViewportClient* InViewportClient, FViewport* InViewport, FVector& InDrag, FRotator& InRot, FVector& InScale )
{
	UBOOL bFoundSelection = FALSE;
	
	UBOOL bAltDown = InViewport->KeyState(KEY_LeftAlt) || InViewport->KeyState(KEY_RightAlt);

	if( InViewportClient->Widget->GetCurrentAxis() != AXIS_None && (UISettings.GetSelectToolSelected() || UISettings.GetLassoSelectToolSelected()) )
	{
		AInstancedFoliageActor* IFA = AInstancedFoliageActor::GetInstancedFoliageActor();
		IFA->Modify();
		for( TMap<class UStaticMesh*, struct FFoliageMeshInfo>::TIterator MeshIt(IFA->FoliageMeshes); MeshIt; ++MeshIt )
		{
			FFoliageMeshInfo& MeshInfo = MeshIt.Value();
			bFoundSelection |= MeshInfo.SelectedIndices.Num() > 0;

			if( bAltDown && bCanAltDrag && (InViewportClient->Widget->GetCurrentAxis() & AXIS_XYZ)  )
			{
				MeshInfo.DuplicateInstances(IFA, MeshIt.Key(), MeshInfo.SelectedIndices);
#if WITH_MANAGED_CODE
				FoliageEditWindow->RefreshMeshListProperties();
#endif
			}
			
			MeshInfo.PreMoveInstances(IFA, MeshInfo.SelectedIndices);

			for( INT SelectionIdx=0;SelectionIdx<MeshInfo.SelectedIndices.Num();SelectionIdx++ )
			{
				INT InstanceIndex = MeshInfo.SelectedIndices(SelectionIdx);
				FFoliageInstance& Instance = MeshInfo.Instances(InstanceIndex);
				Instance.Location += InDrag;
				Instance.ZOffset = 0.f;
				Instance.Rotation += InRot;
				//Instance.DrawScale3D += InScale;
				Instance.DrawScale3D += InScale / 100;  //Bruce@snda
			}

			MeshInfo.PostMoveInstances(IFA, MeshInfo.SelectedIndices);
		}

		// Only allow alt-drag on first InputDelta
		bCanAltDrag = FALSE;

		if( bFoundSelection )
		{
			IFA->ConditionalUpdateComponents();
			return TRUE;
		}
	}

	return FEdMode::InputDelta(InViewportClient,InViewport,InDrag,InRot,InScale);
}

UBOOL FEdModeFoliage::AllowWidgetMove()
{
	return ShouldDrawWidget();
}

UBOOL FEdModeFoliage::UsesTransformWidget() const
{
	return ShouldDrawWidget();
}

UBOOL FEdModeFoliage::ShouldDrawWidget() const
{
	return (UISettings.GetSelectToolSelected() || UISettings.GetLassoSelectToolSelected()) && AInstancedFoliageActor::GetInstancedFoliageActor()->SelectedMesh != NULL;
}

INT FEdModeFoliage::GetWidgetAxisToDraw( FWidget::EWidgetMode InWidgetMode ) const
{
	switch(InWidgetMode)
	{
	case FWidget::WM_Translate:
		return AXIS_XYZ;
	case FWidget::WM_Rotate:
		return AXIS_XYZ;
	case FWidget::WM_Scale:
		return AXIS_XYZ;  //Bruce@snda
	case FWidget::WM_ScaleNonUniform:
		return AXIS_XYZ;
	default:
		return 0;
	}
}

/** Load UI settings from ini file */
void FFoliageUISettings::Load()
{
	FString WindowPositionString;
	if( GConfig->GetString( TEXT("FoliageEdit"), TEXT("WindowPosition"), WindowPositionString, GEditorUserSettingsIni ) )
	{
		TArray<FString> PositionValues;
		if( WindowPositionString.ParseIntoArray( &PositionValues, TEXT( "," ), TRUE ) == 4 )
		{
			WindowX = appAtoi( *PositionValues(0) );
			WindowY = appAtoi( *PositionValues(1) );
			WindowWidth = appAtoi( *PositionValues(2) );
			WindowHeight = appAtoi( *PositionValues(3) );
		}
	}

	GConfig->GetFloat( TEXT("FoliageEdit"), TEXT("Radius"), Radius, GEditorUserSettingsIni );
	GConfig->GetFloat( TEXT("FoliageEdit"), TEXT("PaintDensity"), PaintDensity, GEditorUserSettingsIni );
	GConfig->GetFloat( TEXT("FoliageEdit"), TEXT("UnpaintDensity"), UnpaintDensity, GEditorUserSettingsIni );
	GConfig->GetBool( TEXT("FoliageEdit"), TEXT("bFilterLandscape"), bFilterLandscape, GEditorUserSettingsIni );
	GConfig->GetBool( TEXT("FoliageEdit"), TEXT("bFilterStaticMesh"), bFilterStaticMesh, GEditorUserSettingsIni );
	GConfig->GetBool( TEXT("FoliageEdit"), TEXT("bFilterBSP"), bFilterBSP, GEditorUserSettingsIni );
	GConfig->GetBool( TEXT("FoliageEdit"), TEXT("bFilterTerrain"), bFilterTerrain, GEditorUserSettingsIni );
}

/** Save UI settings to ini file */
void FFoliageUISettings::Save()
{
	FString WindowPositionString = FString::Printf(TEXT("%d,%d,%d,%d"), WindowX, WindowY, WindowWidth, WindowHeight );
	GConfig->SetString( TEXT("FoliageEdit"), TEXT("WindowPosition"), *WindowPositionString, GEditorUserSettingsIni );

	GConfig->SetFloat( TEXT("FoliageEdit"), TEXT("Radius"), Radius, GEditorUserSettingsIni );
	GConfig->SetFloat( TEXT("FoliageEdit"), TEXT("PaintDensity"), PaintDensity, GEditorUserSettingsIni );
	GConfig->SetFloat( TEXT("FoliageEdit"), TEXT("UnpaintDensity"), UnpaintDensity, GEditorUserSettingsIni );
	GConfig->SetBool( TEXT("FoliageEdit"), TEXT("bFilterLandscape"), bFilterLandscape, GEditorUserSettingsIni );
	GConfig->SetBool( TEXT("FoliageEdit"), TEXT("bFilterStaticMesh"), bFilterStaticMesh, GEditorUserSettingsIni );
	GConfig->SetBool( TEXT("FoliageEdit"), TEXT("bFilterBSP"), bFilterBSP, GEditorUserSettingsIni );
	GConfig->SetBool( TEXT("FoliageEdit"), TEXT("bFilterTerrain"), bFilterTerrain, GEditorUserSettingsIni );
}
