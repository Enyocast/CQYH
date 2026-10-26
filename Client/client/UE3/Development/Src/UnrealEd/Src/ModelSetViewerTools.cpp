/*=============================================================================
	AnimSetViewerMain.cpp: AnimSet viewer main
	Copyright 1998-2013 Epic Games, Inc. All Rights Reserved.
=============================================================================*/

#include "UnrealEd.h"
#include "EngineAnimClasses.h"
#include "ModelEditor.h"
#include "PropertyWindow.h"
#include "DlgGenericComboEntry.h"
#include "DlgRename.h"
#include "DlgRotateAnimSequence.h"
#include "BusyCursor.h"
#include "AnimationUtils.h"
#include "SkelImport.h"
#include "Factories.h"
#include "UnSkelRenderPublic.h"
#include "UnMeshBuild.h"
#include "DlgCheckBoxList.h"

#include "../../Engine/Inc/EngineClasses.h"
#include "../../Engine/Inc/EngineMeshClasses.h"
#include "../../Engine/Inc/EngineAnimClasses.h"
#include "../../Engine/Inc/EngineAIClasses.h"
#include "../../GameFramework/Inc/GameFrameworkClasses.h"
#include "../../MMOGame/Inc/MMOGameClasses.h"

#if WITH_COLLADA
#include "UnColladaImporter.h"
#endif

#if WITH_FBX
#include "UnFbxImporter.h"
#include "UnFbxExporter.h"
#endif // WITH_FBX

#if WITH_SIMPLYGON
#include "SkeletalMeshSimplificationWindow.h"
#endif // #if WITH_SIMPLYGON

/** Comparison function for sorting INTs smallest to largest */
IMPLEMENT_COMPARE_CONSTREF( BYTE, AnimSetViewerTools, { return (A - B); } )
IMPLEMENT_COMPARE_CONSTREF( INT, SortINTSAscending, { return (A - B); } )

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Static helpers
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace {
	/**
	 * Recompresses the sequences in specified anim set by applying each sequence's compression scheme.
	 * 
	 */
	static void RecompressSet(UAnimSet* AnimSet, USkeletalMesh* SkeletalMesh)
	{
		for( INT SequenceIndex = 0 ; SequenceIndex < AnimSet->Sequences.Num() ; ++SequenceIndex )
		{
			UAnimSequence* Seq = AnimSet->Sequences( SequenceIndex );
			FAnimationUtils::CompressAnimSequence(Seq, SkeletalMesh, FALSE, FALSE);
		}
	}

	/**
	 * Recompresses the specified sequence in anim set by applying the sequence's compression scheme.
	 * 
	 */
	static void RecompressSequence(UAnimSequence* Seq, USkeletalMesh* SkeletalMesh)
	{
		FAnimationUtils::CompressAnimSequence(Seq, SkeletalMesh, FALSE, FALSE);
	}
}

extern void CalculateBoneWeightInfluences(USkeletalMesh* SkeletalMesh, TArray<FBoneIndexPair>& BonePairs, EBoneBreakOption Option);



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// WxModelViewer
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void WxModelViewer::SetSelectedSkelMesh(USkeletalMesh* InSkelMesh, UBOOL bClearMorphTarget, UBOOL bReselectAnimSet/* = TRUE*/)
{
	check(InSkelMesh);

	//// Before we change mesh, clear any component we using for previewing attachments.
	//ClearSocketPreviews();

	//SelectedSkelMesh = InSkelMesh;
	//
	//// Set up for undo/redo!
	//SelectedSkelMesh->SetFlags(RF_Transactional);

	////Remove materials saved from previous mesh
	//PreviewSkelComp->SkelMaterials.Empty();
	//
	//PreviewSkelComp->SetSkeletalMesh(SelectedSkelMesh);
	//PreviewSkelCompRaw->SetSkeletalMesh(SelectedSkelMesh);

	// Update the Socket Manager
	//UpdateSocketList();
	//SetSelectedSocket(NULL);
	//RecreateSocketPreviews();

//	//SkelMeshCombo->Freeze();
//	//SkelMeshCombo->Clear();
//	//for(TObjectIterator<USkeletalMesh> It; It; ++It)
//	//{
//	//	USkeletalMesh* SkelMesh = *It;
//
//	//	if( !(SkelMesh->GetOutermost()->PackageFlags & PKG_Trash) )
//	//	{
//	//		SkelMeshCombo->Append( *SkelMesh->GetName(), SkelMesh );
//	//	}
//	//}
//	//SkelMeshCombo->Thaw();
//
//	//// Set combo box to reflect new selection.
//	//for(UINT i=0; i<SkelMeshCombo->GetCount(); i++)
//	//{
//	//	if( SkelMeshCombo->GetClientData(i) == SelectedSkelMesh )
//	//	{
//	//		SkelMeshCombo->SetSelection(i); // This won't cause a new IDM_ANIMSET_SKELMESHCOMBO event.
//	//	}
//	//}
//
//	//// turn off alt bone editing mode and toggle off mesh weights
//	//EnableAltBoneWeighting(FALSE);
//	//ToggleMeshWeights(FALSE);
//
//	//Remove selected bone manipulation
//	PreviewSkelComp->BonesOfInterest.Empty();
//
//	// clear all about vertex info tool
//	appMemzero(&VertexInfo, sizeof(VertexInfo));
//	UpdateVertexMode();
//	
//	//Remove bone influences being rendered
//	BoneInfluenceLODInfo.Empty(SelectedSkelMesh->LODModels.Num());
//	BoneInfluenceLODInfo.AddZeroed(SelectedSkelMesh->LODModels.Num());
//
//	//Remove materials saved from previous mesh
//	PreviewSkelComp->SkelMaterials.Empty();
//
//	PreviewSkelComp->SetSkeletalMesh(SelectedSkelMesh);
//	PreviewSkelCompRaw->SetSkeletalMesh(SelectedSkelMesh);
//
//	// When changing primary skeletal mesh - reset all extra ones.
//	SkelMeshAux1Combo->SetSelection(0);
//	PreviewSkelCompAux1->SetSkeletalMesh(NULL);
//	PreviewSkelCompAux1->UpdateParentBoneMap();
//
//	SkelMeshAux2Combo->SetSelection(0);
//	PreviewSkelCompAux2->SetSkeletalMesh(NULL);
//	PreviewSkelCompAux2->UpdateParentBoneMap();
//
//	SkelMeshAux3Combo->SetSelection(0);
//	PreviewSkelCompAux3->SetSkeletalMesh(NULL);
//	PreviewSkelCompAux3->UpdateParentBoneMap();
//
//	MeshProps->SetObject( NULL, EPropertyWindowFlags::ShouldShowCategories );
//	MeshProps->SetObject( SelectedSkelMesh, EPropertyWindowFlags::ShouldShowCategories );
//
//	// Update the Socket Manager
//	UpdateSocketList();
//	SetSelectedSocket(NULL);
//	RecreateSocketPreviews();
//
//	if( bReselectAnimSet )
//	{
//		// Try and re-select the select AnimSet with the new mesh.
//		SetSelectedAnimSet(SelectedAnimSet, false);
//	}
//
//	// Select no morph target.
//	if(bClearMorphTarget)
//	{
//		UBOOL bRefreshMorphSet = SelectedSkelMesh->PreviewMorphSets.Num() >  0 && 
//			(SelectedMorphSet==NULL || SelectedSkelMesh->PreviewMorphSets.ContainsItem(SelectedMorphSet)==FALSE);
//
//		// if preview  morph set exists, 
//		// and current morphset doens't belong to preview morphsets, and refresh to new item
//		if ( bRefreshMorphSet )
//		{
//			for (INT I=0; I<SelectedSkelMesh->PreviewMorphSets.Num(); ++I)
//			{
//				SetSelectedMorphSet(SelectedSkelMesh->PreviewMorphSets(I), FALSE);
//			}
//		}
//		else
//		{
//			SetSelectedMorphSet(NULL, FALSE);
//		}
//	}
//
//	// Reset LOD to Auto mode.
//	PreviewSkelComp->ForcedLodModel = 0;
//	PreviewSkelCompRaw->ForcedLodModel = 0;
//	MenuBar->Check( IDM_ANIMSET_LOD_AUTO, true );
//	ToolBar->ToggleTool( IDM_ANIMSET_LOD_AUTO, true );
//
//	// Update the buttons used for changing the desired LOD.
//	UpdateForceLODButtons();
//	UpdateAltBoneWeightingMenu();
//
//	// Turn off cloth sim when we change mesh.
//	ToolBar->ToggleTool( IDM_ANIMSET_TOGGLECLOTH, false );
//	PreviewSkelComp->TermClothSim(NULL);
//	PreviewSkelComp->bEnableClothSimulation = FALSE;
//	
//	// Turn off soft-body sim when we change mesh. Reinitialize data buffers for previewing if we already have generated tetras.
//	ToolBar->ToggleTool(IDM_ANIMSET_SOFTBODYTOGGLESIM, FALSE);
//	PreviewSkelComp->TermSoftBodySim(NULL);
//	PreviewSkelComp->bEnableSoftBodySimulation = FALSE;
//	if(InSkelMesh->SoftBodyTetraVertsUnscaled.Num() > 0)
//	{
//		FlushRenderingCommands();
//		PreviewSkelComp->InitSoftBodySimBuffers();
//	}
//	
//	// update chunk list
//	UpdateMaterialList();
//	UpdateStatusBar();
//
//	FEditorModelViewportClient* ASVPreviewVC = GetPreviewVC();
//	check( ASVPreviewVC );
//	ASVPreviewVC->Viewport->Invalidate();
//
//
//	// Remember we want to use this mesh with the current anim/morph set.
//	if(SelectedSkelMesh && SelectedAnimSet)
//	{
//		FString MeshName = SelectedSkelMesh->GetPathName();
//		SelectedAnimSet->PreviewSkelMeshName = FName( *MeshName );
//	}
//
//	// Fill Skeleton Tree.
//	FillSkeletonTree();
//
//	// Refresh the toolbar chunks and sections controls
//	UpdateChunkPreview();
//	UpdateSectionPreview();
//
//#if WITH_SIMPLYGON
//	SimplificationWindow->UpdateControls();
//#endif // #if WITH_SIMPLYGON
}


/**
 * Updates the visibility and collision of the floor
 */
void WxModelViewer::UpdateFloorComponent(void)
{
	FEditorModelViewportClient* ASVPreviewVC = GetPreviewVC();
	check(ASVPreviewVC);
	check(EditorFloorComp);

	// Turn on/off the ground box
	EditorFloorComp->SetHiddenEditor(!ASVPreviewVC->bShowFloor);
	EditorFloorComp->SetBlockRigidBody(ASVPreviewVC->bShowFloor);
}


void WxModelViewer::DisplayError(EMorphImportError &ImportError, FFilename &Filename)
{
	switch( ImportError )
	{
	    case MorphImport_AlreadyExists:
		    //appMsgf( AMT_OK, *LocalizeUnrealEd("Error_MorphImport_AlreadyExists") );
		    break;
	    case MorphImport_CantLoadFile:
		    appMsgf( AMT_OK, LocalizeSecure(LocalizeUnrealEd("Error_MorphImport_CantLoadFile"), *Filename) );
		    break;
	    case MorphImport_InvalidMeshFormat:
		    appMsgf( AMT_OK, *LocalizeUnrealEd("Error_MorphImport_InvalidMeshFormat") );
		    break;
	    case MorphImport_MismatchBaseMesh:
		    appMsgf( AMT_OK, *LocalizeUnrealEd("Error_MorphImport_MismatchBaseMesh") );
		    break;
	    case MorphImport_ReimportBaseMesh:
		    appMsgf( AMT_OK, *LocalizeUnrealEd("Error_MorphImport_ReimportBaseMesh") );
		    break;
	    case MorphImport_MissingMorphTarget:
		    appMsgf( AMT_OK, *LocalizeUnrealEd("Error_MorphImport_MissingMorphTarget") );
		    break;
	    case MorphImport_InvalidLODIndex:
		    appMsgf( AMT_OK, *LocalizeUnrealEd("Error_MorphImport_InvalidLODIndex") );
		    break;
	}
}


IMPLEMENT_COMPARE_POINTER( UAnimSequence, AnimSetViewer, { return appStricmp(*A->SequenceName.ToString(),*B->SequenceName.ToString()); } );

/**
 * Populates all the anim sequences in the given anim set to the anim sequence list. 
 *
 * @param	SetToAdd	The anim set containing sequences to add. 
 */
void WxModelViewer::AddAnimSequencesToList( UAnimSet* SetToAdd )
{
	//// Add each anim. sequence of the currently selected animset to the listbox if they pass the search filter (or if the filter is empty)
	//const FString FilterString = AnimSeqFilter->GetValue().c_str();

	//for ( TArray<UAnimSequence*>::TConstIterator AnimSeqIter(SetToAdd->Sequences); AnimSeqIter; ++AnimSeqIter )
	//{
	//	UAnimSequence* CurSeq = *AnimSeqIter;
	//	const FString SeqString = FString::Printf( TEXT("%s [%.4gs]"), *CurSeq->SequenceName.ToString(), CurSeq->SequenceLength );
	//	if ( FilterString.Len() == 0 || SeqString.InStr( FilterString, FALSE, TRUE ) != INDEX_NONE )
	//	{
	//		AnimSeqList->Append(*SeqString, CurSeq);
	//	}
	//}
}

void WxModelViewer::UpdateAnimSeqList()
{
	//AnimSeqList->Freeze();
	//AnimSeqList->Clear();

	//// If this mode is on, it is assumed that all anim sets were 
	//// loaded. So, we can just iterate over the anim sets in memory. 
	//if(bSearchAllAnimSequences)
	//{
	//	for(TObjectIterator<UAnimSet> It; It; ++It)
	//	{
	//		AddAnimSequencesToList(*It);
	//	}
	//}
	//else if(SelectedAnimSet)
	//{
	//	AddAnimSequencesToList(SelectedAnimSet);
	//}

	//AnimSeqList->Thaw();
}


IMPLEMENT_COMPARE_POINTER( UMorphTarget, AnimSetViewer, { return appStricmp(*A->GetName(), *B->GetName()); } );



// Update the UI to match the current animation state (position, playing, looping)
void WxModelViewer::RefreshPlaybackUI()
{
	if (!PlayButton || !LoopButton)
	{
		return;
	}
	// Update scrub bar (can only do if we have an animation selected.
	if( PreviewAnimNode->AnimSeq)
	{
		FLOAT CurrentPos = PreviewAnimNode->CurrentTime / PreviewAnimNode->AnimSeq->SequenceLength;
		TimeSlider->SetValue( appRound(CurrentPos * (FLOAT)ASV_SCRUBRANGE) );
	}

	//FLOAT CurrentPos = CurrentPlayTime / MaxTrackLength;
	//TimeSlider->SetValue(appRound(CurrentPos * (FLOAT)ASV_SCRUBRANGE));

	// Update Play/Stop button
	if(bPlaying)
	{
		// Only set the bitmap label if we actually are changing state.
		const wxBitmap& CurrentBitmap = PlayButton->GetBitmapLabel();

		if(CurrentBitmap.GetHandle() != StopB.GetHandle())
		{
			PlayButton->SetBitmapLabel( StopB );
			PlayButton->Refresh();
		}
	}
	else
	{
		// Only set the bitmap label if we actually are changing state.
		const wxBitmap& CurrentBitmap = PlayButton->GetBitmapLabel();

		if(CurrentBitmap.GetHandle() != PlayB.GetHandle())
		{
			PlayButton->SetBitmapLabel( PlayB );
			PlayButton->Refresh();
		}
	}


	// Update Loop toggle
	if(bLooping)
	{
		// Only set the bitmap label if we actually are changing state.
		const wxBitmap& CurrentBitmap = LoopButton->GetBitmapLabel();

		if(CurrentBitmap.GetHandle() != LoopB.GetHandle())
		{
			LoopButton->SetBitmapLabel( LoopB );
			LoopButton->Refresh();
		}
	}
	else
	{
		// Only set the bitmap label if we actually are changing state.
		const wxBitmap& CurrentBitmap = LoopButton->GetBitmapLabel();

		if(CurrentBitmap.GetHandle() != NoLoopB.GetHandle())
		{
			LoopButton->SetBitmapLabel( NoLoopB );
			LoopButton->Refresh();
		}
	}
}

extern FParticleDataManager	GParticleDataManager;

void WxModelViewer::TickViewer(FLOAT DeltaSeconds)
{
	if (PreviewSkelComp->SkeletalMesh && SelectedAnimSeq)
	{
		// Tick the PreviewSkelComp to move animation forwards, then Update to update bone locations.
		PreviewSkelComp->TickAnimNodes(DeltaSeconds);

		if (PreviewSkelComp->UpdateLODStatus())
		{
			// whenever LOD has changed, update Alternate Bone weighting menu
			//UpdateAltBoneWeightingMenu();

			// Update the weights
			//FillSkeletonTree();
		}

		// update the instanced influence weights if needed
		for (INT LODIdx=0; LODIdx<PreviewSkelComp->LODInfo.Num(); LODIdx++)
		{
			if( PreviewSkelComp->LODInfo(LODIdx).bNeedsInstanceWeightUpdate )
			{
				PreviewSkelComp->UpdateInstanceVertexWeights(LODIdx);
			}
		}

		PreviewSkelComp->UpdateSkelPose();

		// Apply wind forces.
		PreviewSkelComp->UpdateClothWindForces(DeltaSeconds);
#if WITH_APEX
		PreviewSkelComp->TickApexClothing(DeltaSeconds);
#endif
		// Update any cloth attachment
		PreviewSkelComp->UpdateFixedClothVerts();
	}



	// Run physics
	TickRBPhysScene(RBPhysScene, DeltaSeconds);
	WaitRBPhysScene(RBPhysScene);

	DeferredRBResourceCleanup(RBPhysScene);

	FEditorModelViewportClient* vc = GetPreviewVC();
	if( NULL != vc->LineBatcher )
	{
		vc->LineBatcher->BatchedLines.Empty(); // remove the novodex debug line draws
#if WITH_NOVODEX
		RBPhysScene->AddNovodexDebugLines( vc->LineBatcher );
		vc->LineBatcher->BeginDeferredReattach();
#endif
	}

	// Update components
	PreviewSkelComp->ConditionalUpdateTransform();

	if (AvatarObject)
	{
		PreviewSkelComp->Scale = AvatarObject->MeshScale * AvatarObject->AvatarDrawScale;
		FTranslationMatrix ftm(FVector(0, 0, AvatarObject->CollisionHeight * AvatarObject->AvatarDrawScale));
		PreviewSkelComp->ConditionalUpdateTransform(ftm);
		//PreviewSkelComp->BeginDeferredUpdateTransform();

		CollisionBoxComponent->SetCylinderSize(AvatarObject->CollisionRadius * AvatarObject->AvatarDrawScale, AvatarObject->CollisionHeight * AvatarObject->AvatarDrawScale);
		CollisionBoxComponent->ConditionalUpdateTransform(ftm);
	}
	

	// Update any attached particle systems for previewing...
	UBOOL bHadPSysComponents = FALSE;
	for (INT AttachmentIndex = 0; AttachmentIndex < PreviewSkelComp->Attachments.Num(); AttachmentIndex++)
	{
		FAttachment& CheckAttachment = PreviewSkelComp->Attachments(AttachmentIndex);
		UParticleSystemComponent* PSysComp = Cast<UParticleSystemComponent>(CheckAttachment.Component);
		if (PSysComp)
		{
			PSysComp->Tick(DeltaSeconds);
			bHadPSysComponents = TRUE;
		}
	}
	if (bHadPSysComponents == TRUE)
	{
		GParticleDataManager.UpdateDynamicData();
	}

	for (INT i = 0; i < BaseSkelMeshCompList.Num(); ++i)
	{
		if (BaseSkelMeshCompList(i))
		{
			BaseSkelMeshCompList(i)->ConditionalUpdateTransform(PreviewSkelComp->LocalToWorld);
		}
	}

	if (PreviewMergedComp)
	{
		PreviewMergedComp->UpdateSkelPose();
		PreviewMergedComp->ConditionalUpdateTransform(PreviewMergedComp->CachedParentToWorld);
	}

	// Move scrubber to reflect current animation position etc.
	RefreshPlaybackUI();

	// tick merge
	if (PreviewWindow && PreviewWindow->ASVPreviewVC && PreviewWindow->ASVPreviewVC->ViewObj)
	{
		PreviewWindow->ASVPreviewVC->ViewObj->TickMerge(DeltaSeconds);
	}
	
}

void WxModelViewer::UpdateSkelComponents()
{
	FComponentReattachContext ReattachContext1(PreviewSkelComp);
}

static INT NumTotalTracks = 0;
static INT NumAdditiveTracks = 0;
static INT NumNoTrackData = 0;
static INT NumTotalBones = 0;

static INT NumDeletedTracks = 0;
static INT NumDeletedAdditiveTracks = 0;
static INT NumDeletedRotationOnlyTracks = 0;

#define MAXPOSDIFF			(0.0001f)
#define MAXANGLEDIFF		(0.0003f)
#define TESTMAXPOSDIFF		(0.001f)
#define TESTMAXANGLEDIFF	(0.003f)



/** Tool for updating the bounding sphere/box of the selected skeletal mesh. Shouldn't generally be needed, except for fixing stuff up possibly. */
void WxModelViewer::UpdateMeshBounds()
{
	if(SelectedSkelMesh)
	{
		FBox BoundingBox(0);
		check(SelectedSkelMesh->LODModels.Num() > 0);
		FStaticLODModel& LODModel = SelectedSkelMesh->LODModels(0);

		for(INT ChunkIndex = 0;ChunkIndex < LODModel.Chunks.Num();ChunkIndex++)
		{
			const FSkelMeshChunk& Chunk = LODModel.Chunks(ChunkIndex);
			for(INT i=0; i<Chunk.RigidVertices.Num(); i++)
			{
				BoundingBox += Chunk.RigidVertices(i).Position;
			}
			for(INT i=0; i<Chunk.SoftVertices.Num(); i++)
			{
				BoundingBox += Chunk.SoftVertices(i).Position;
			}
		}

		const FBox Temp			= BoundingBox;
		const FVector MidMesh	= 0.5f*(Temp.Min + Temp.Max);
		BoundingBox.Min			= Temp.Min + 1.0f*(Temp.Min - MidMesh);
		BoundingBox.Max			= Temp.Max + 1.0f*(Temp.Max - MidMesh);

		// Tuck up the bottom as this rarely extends lower than a reference pose's (e.g. having its feet on the floor).
		BoundingBox.Min.Z	= Temp.Min.Z + 0.1f*(Temp.Min.Z - MidMesh.Z);
		SelectedSkelMesh->Bounds = FBoxSphereBounds(BoundingBox);

		SelectedSkelMesh->MarkPackageDirty();
	}
}

/** Update the external force on the cloth sim. */
void WxModelViewer::UpdateClothWind()
{
	const FVector WindDir = WindRot.Vector();
	PreviewSkelComp->ClothWind = WindDir * WindStrength;
	// Wind Parameters for ApexClothing
#if WITH_APEX
	PreviewSkelComp->WindVelocity = WindDir * WindStrength;
	PreviewSkelComp->WindVelocityBlendTime = WindVelocityBlendTime;
#endif
}

