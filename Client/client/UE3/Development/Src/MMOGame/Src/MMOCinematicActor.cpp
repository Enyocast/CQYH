#include "..\stdafx.h"

IMPLEMENT_CLASS(AMMOActorCinematicActor)

#define M_USE_SKMAT_UPDATE 1

BYTE AMMOActorCinematicActor::GetWeaponType()
{	
	return CurrentCinematicWeaponType;
}


void AMMOActorCinematicActor::SetSilhouetteEx( UBOOL show, FVector sc)
{
	// nothing to do
}

void AMMOActorCinematicActor::SetVisibleByAbility(UBOOL InVisible)
{
}


/** 
 * PreviewBeginAnimControl 
 */
void AMMOActorCinematicActor::PreviewBeginAnimControl(UInterpGroup* InInterpGroup)
{
#if !M_USE_SKMAT_UPDATE
	MAT_BeginAnimControl(InInterpGroup);

	Mesh->InitAnimTree();

	// Toggle on cinematic weighting for the skeletal mesh while previewing
	for ( INT LODIdx = 0; LODIdx < Mesh->LODInfo.Num(); ++LODIdx )
	{
		if ( Mesh->LODInfo(LODIdx).InstanceWeightUsage == IWU_FullSwap )
		{
			Mesh->ToggleInstanceVertexWeights( TRUE, LODIdx );
		}
	}
#else
	// We need an AnimTree in Matinee in the editor to preview the animations, so instance one now if we don't have one.
	// This function can get called multiple times, but this is safe - will only instance the first time.
	if( !Mesh->Animations && Mesh->AnimTreeTemplate )
	{
		Mesh->Animations = Mesh->AnimTreeTemplate->CopyAnimTree(Mesh);
	}

	// In the editor we don't have access to Script, so cache slot nodes here :(
	SlotNodes.Empty();
	if( Mesh->Animations )
	{
		TArray<UAnimNode*> Nodes;
		Mesh->Animations->GetNodesByClass(Nodes, UAnimNodeSlot::StaticClass());

		for(INT i=0; i<Nodes.Num(); i++)
		{
			UAnimNodeSlot* SlotNode = Cast<UAnimNodeSlot>(Nodes(i));
			if( SlotNode )
			{
				SlotNodes.AddItem(SlotNode);
			}
		}
	}
	else
	{
		debugf(TEXT("PreviewBeginAnimControl, no AnimTree, couldn't cache slots!") );
	}

	//Super::PreviewBeginAnimControl(InInterpGroup);

	MAT_BeginAnimControl(InInterpGroup);

	Mesh->InitAnimTree();

	// Toggle on cinematic weighting for the skeletal mesh while previewing
	for ( INT LODIdx = 0; LODIdx < Mesh->LODInfo.Num(); ++LODIdx )
	{
		if ( Mesh->LODInfo(LODIdx).InstanceWeightUsage == IWU_FullSwap )
		{
			Mesh->ToggleInstanceVertexWeights( TRUE, LODIdx );
		}
	}
#endif
}

// [ming@snda
/**
* Start AnimControl.
*/
void AMMOActorCinematicActor::MAT_BeginAnimControl(UInterpGroup* InInterpGroup)
{
#if M_USE_SKMAT_UPDATE
	// We need an AnimTree in Matinee in the editor to preview the animations, so instance one now if we don't have one.
	// This function can get called multiple times, but this is safe - will only instance the first time.
	if( !Mesh->Animations && Mesh->AnimTreeTemplate )
	{
		Mesh->Animations = Mesh->AnimTreeTemplate->CopyAnimTree(Mesh);
	}

	// In the editor we don't have access to Script, so cache slot nodes here :(
	SlotNodes.Empty();
	if( Mesh->Animations )
	{
		TArray<UAnimNode*> Nodes;
		Mesh->Animations->GetNodesByClass(Nodes, UAnimNodeSlot::StaticClass());

		for(INT i=0; i<Nodes.Num(); i++)
		{
			UAnimNodeSlot* SlotNode = Cast<UAnimNodeSlot>(Nodes(i));
			if( SlotNode )
			{
				SlotNodes.AddItem(SlotNode);
			}
		}
	}
	else
	{
		debugf(TEXT("PreviewBeginAnimControl, no AnimTree, couldn't cache slots!") );
	}
#endif
	
	InterpGroupList.AddUniqueItem(InInterpGroup);

	// Update AnimSet list.
	UpdateAnimSetList();

	//Super::MAT_BeginAnimControl(InInterpGroup);
}
// ming@snda]


/** 
* PreviewFinishAnimControl 
*/
void AMMOActorCinematicActor::PreviewFinishAnimControl(UInterpGroup* InInterpGroup)
{
#if !M_USE_SKMAT_UPDATE
	MAT_FinishAnimControl(InInterpGroup);

	// In editor free up AnimSets.
	// In-game, we'll keep the references until the SkelMeshActor is streamed out.
	// Take out our group from the list
	InterpGroupList.RemoveItem(InInterpGroup);

	// Update AnimSet list.
	UpdateAnimSetList();

	// Update space bases to reset it back to ref pose
	Mesh->UpdateSkelPose(0.f, FALSE);
	Mesh->ConditionalUpdateTransform();

	// Toggle off cinematic weighting when done previewing
	for ( INT LODIdx = 0; LODIdx < Mesh->LODInfo.Num(); ++LODIdx )
	{
		if ( Mesh->LODInfo(LODIdx).InstanceWeightUsage == IWU_FullSwap )
		{
			Mesh->ToggleInstanceVertexWeights( FALSE, LODIdx );
		}
	}
#else
	MAT_FinishAnimControl(InInterpGroup);

	// Take out our group from the list
	InterpGroupList.RemoveItem(InInterpGroup);

	// Update AnimSet list.
	UpdateAnimSetList();

	// When done in Matinee in the editor, drop the AnimTree instance.
	Mesh->Animations = NULL;

	// before free up, clears root motion
	// Clear references to AnimSets which were added.
	FAnimSlotInfo SlotNodeInfo;
	// clear the weight
	SlotNodeInfo.ChannelWeights.AddItem(0.0f);

	for(INT SlotIdx=0; SlotIdx<SlotNodes.Num(); SlotIdx++)
	{
		UAnimNodeSlot* SlotNode = SlotNodes(SlotIdx);
		if( SlotNode )
		{	
			SlotNode->MAT_SetAnimWeights(SlotNodeInfo);
			//unset root motion
			SlotNode->SetRootBoneAxisOption(RBA_Default, RBA_Default, RBA_Default);
			SlotNode->bIsBeingUsedByInterpGroup = FALSE;
		}
	}

	// In the editor, free up the slot nodes.
	SlotNodes.Empty();

	// Update space bases to reset it back to ref pose
	Mesh->UpdateSkelPose(0.f, FALSE);
	Mesh->ConditionalUpdateTransform();
#endif
}

// [ming@snda
/**
* End AnimControl.
*/
void AMMOActorCinematicActor::MAT_FinishAnimControl(UInterpGroup* InInterpGroup)
{
#if !M_USE_SKMAT_UPDATE
	// remove arrow component that might have been attached via playing animation
	if (GIsEditor && !GIsGame && Mesh)
	{
		Mesh->DetachAnyOf(UArrowComponent::StaticClass());
	}

	// Take out our group from the list
	InterpGroupList.RemoveItem(InInterpGroup);
#else
	Super::MAT_FinishAnimControl(InInterpGroup);

	// before free up, clears root motion
	// Clear references to AnimSets which were added.
	FAnimSlotInfo SlotNodeInfo;
	// clear the weight
	SlotNodeInfo.ChannelWeights.AddItem(0.0f);

	for(INT SlotIdx=0; SlotIdx<SlotNodes.Num(); SlotIdx++)
	{
		UAnimNodeSlot* SlotNode = SlotNodes(SlotIdx);
		if( SlotNode )
		{	
			SlotNode->MAT_SetAnimWeights(SlotNodeInfo);
			//unset root motion
			SlotNode->SetRootBoneAxisOption(RBA_Default, RBA_Default, RBA_Default);
			SlotNode->bIsBeingUsedByInterpGroup = FALSE;
		}
	}

	// In the editor, free up the slot nodes.
	SlotNodes.Empty();
#endif
}
// ming@snda]

extern UBOOL VerifyAnimationMatchSkeletalMesh(UAnimSet * AnimSet, USkeletalMesh * SkeletalMesh);
extern UBOOL VerifyAnimationMatchSkeletalMesh(UAnimNodeSequence * AnimSeqNode, USkeletalMesh * SkeletalMesh);
extern UBOOL VerifyAnimationMatchSkeletalMesh(USkeletalMeshComponent * SkeletalComp);
extern UBOOL VerifyAnimationMatchSkeletalMesh(USkeletalMeshComponent * SkeletalComp);

/** 
* PreviewSetAnimPosition 
*/
void AMMOActorCinematicActor::PreviewSetAnimPosition(FName SlotName, INT ChannelIndex, FName InAnimSeqName, FLOAT InPosition, UBOOL bLooping, UBOOL bFireNotifies, UBOOL bEnableRootMotion, FLOAT DeltaTime)
{
#if !M_USE_SKMAT_UPDATE

// 	PlayAnimation(InAnimSeqName, 0, 1, TRUE);
// 	return;

	UAnimNodeSequence* SeqNode = Cast<UAnimNodeSequence>(Mesh->Animations);

	// Do nothing if no anim tree or its not an AnimNodeSequence
	if(!SeqNode)
	{
		return;
	}

	if(SeqNode->AnimSeqName != InAnimSeqName || SeqNode->AnimSeq == NULL )
	{
		SeqNode->SetAnim(InAnimSeqName);
		// first time jump on it
		SeqNode->SetPosition(InPosition, FALSE);
	}

	if (Mesh)
	{
		if ( bEnableRootMotion )
		{
			Mesh->RootMotionMode = RMM_Translate;
			SeqNode->SetRootBoneAxisOption(RBA_Translate, RBA_Translate, RBA_Translate);
			Mesh->RootMotionRotationMode = RMRM_RotateActor;
			SeqNode->SetRootBoneRotationOption(RRO_Extract, RRO_Extract, RRO_Extract);
		}
		else
		{
			Mesh->RootMotionMode = RMM_Ignore;
			SeqNode->SetRootBoneAxisOption(RBA_Default, RBA_Default, RBA_Default);
			Mesh->RootMotionRotationMode = RMRM_Ignore;
			SeqNode->SetRootBoneRotationOption(RRO_Default, RRO_Default, RRO_Default);
		}
	}

	// Verify if skeletalmesh can work with given animation
	if (VerifyAnimationMatchSkeletalMesh(SeqNode, Mesh->SkeletalMesh) == FALSE)
	{
		return;
	}

	SeqNode->bLooping = bLooping;
	// set previous time here before setting position
	SeqNode->PreviousTime = SeqNode->CurrentTime;
	SeqNode->SetPosition(InPosition, bFireNotifies);

	// Update space bases so new animation position has an effect.
	Mesh->UpdateSkelPose(DeltaTime, FALSE);
	Mesh->ConditionalUpdateTransform();
#else

	
	MAT_SetAnimPosition(SlotName, ChannelIndex, InAnimSeqName, InPosition, bFireNotifies, bLooping, bEnableRootMotion);

	// Update space bases so new animation position has an effect.
	Mesh->UpdateSkelPose(DeltaTime, FALSE);
	Mesh->ConditionalUpdateTransform();
#endif
}

/** 
* Update AnimTree from track info 
*/
void AMMOActorCinematicActor::MAT_SetAnimPosition(FName SlotName, INT ChannelIndex, FName InAnimSeqName, FLOAT InPosition, UBOOL bFireNotifies, UBOOL bLooping, UBOOL bEnableRootMotion)
{
	// Ensure anims are updated correctly in cinematics even when the mesh isn't rendered.
	Mesh->LastRenderTime = GWorld->GetTimeSeconds();

	// Forward animation positions to slots. They will forward to relevant channels.
	for(INT i=0; i<SlotNodes.Num(); i++)
	{
		UAnimNodeSlot* SlotNode = SlotNodes(i);
		if( SlotNode && SlotNode->NodeName == SlotName )
		{	
			// Verify if skeletalmesh can work with given animation		
			if ( VerifyAnimationMatchSkeletalMesh(Mesh) == FALSE)
			{
				return;
			}

			if ( bEnableRootMotion )
			{
				Mesh->RootMotionMode = RMM_Translate;
				SlotNode->SetRootBoneAxisOption(RBA_Translate, RBA_Translate, RBA_Translate);
				Mesh->RootMotionRotationMode = RMRM_RotateActor;
				SlotNode->SetRootBoneRotationOption(RRO_Extract, RRO_Extract, RRO_Extract);
			}
			else
			{
				Mesh->RootMotionMode = RMM_Ignore;
				SlotNode->SetRootBoneAxisOption(RBA_Default, RBA_Default, RBA_Default);
				Mesh->RootMotionRotationMode = RMRM_Ignore;
				SlotNode->SetRootBoneRotationOption(RRO_Default, RRO_Default, RRO_Default);
			}


			SlotNode->MAT_SetAnimPosition(ChannelIndex, InAnimSeqName, InPosition, bFireNotifies, bLooping, bEnableRootMotion);
		}
	}
}

/** 
 * PreviewSetAnimWeights 
 */
void AMMOActorCinematicActor::PreviewSetAnimWeights(TArray<FAnimSlotInfo>& SlotInfos)
{
	MAT_SetAnimWeights(SlotInfos);
}


/** Called each from while the Matinee action is running, to set the animation weights for the actor. */
void AMMOActorCinematicActor::SetAnimWeights( const TArray<struct FAnimSlotInfo>& SlotInfos )
{
	MAT_SetAnimWeights( SlotInfos );
}

/** 
 * Update AnimTree from track weights 
 */
void AMMOActorCinematicActor::MAT_SetAnimWeights(const TArray<FAnimSlotInfo>& SlotInfos)
{
#if 0
	debugf( TEXT("-- SET ANIM WEIGHTS ---") );
	for(INT i=0; i<SlotInfos.Num(); i++)
	{
		debugf( TEXT("SLOT: %s"), *(SlotInfos(i).SlotName) );
		for(INT j=0; j<SlotInfos(i).ChannelWeights.Num(); j++)
		{
			debugf( TEXT("   CHANNEL %d: %1.3f"), j, SlotInfos(i).ChannelWeights(j) );
		}
	}
#endif

	// Forward channel weights to relevant slot(s)
	for(INT SlotInfoIdx=0; SlotInfoIdx<SlotInfos.Num(); SlotInfoIdx++)
	{
		const FAnimSlotInfo& SlotInfo = SlotInfos(SlotInfoIdx);

		for(INT SlotIdx=0; SlotIdx<SlotNodes.Num(); SlotIdx++)
		{
			UAnimNodeSlot* SlotNode = SlotNodes(SlotIdx);
			if( SlotNode && SlotNode->NodeName == SlotInfo.SlotName )
			{	
				SlotNode->MAT_SetAnimWeights(SlotInfo);
				SlotNode->bIsBeingUsedByInterpGroup = TRUE;
			}
			else
			{
				SlotNode->bIsBeingUsedByInterpGroup = FALSE;
			}
		}
	}
}

void AMMOActorCinematicActor::PreviewSetMorphWeight(FName MorphNodeName, FLOAT MorphWeight)
{
	MAT_SetMorphWeight(MorphNodeName, MorphWeight);
	Mesh->UpdateSkelPose(0.f, FALSE);
	Mesh->ConditionalUpdateTransform();
}

void AMMOActorCinematicActor::PreviewSetSkelControlScale(FName SkelControlName, FLOAT Scale)
{
	MAT_SetSkelControlScale(SkelControlName, Scale);
	Mesh->UpdateSkelPose(0.f, FALSE);
	Mesh->ConditionalUpdateTransform();
}

void AMMOActorCinematicActor::SetSkelControlStrength(FName SkelControlName, FLOAT ControlStrength)
{
	MAT_SetSkelControlStrength(SkelControlName, ControlStrength);
	Mesh->UpdateSkelPose(0.f, FALSE);
	Mesh->ConditionalUpdateTransform();
}

void AMMOActorCinematicActor::AdjustInterpTrackMove(FVector& Pos, FRotator& Rot, FLOAT DeltaTime, UBOOL bIgnoreRotation)
{

}

/*-----------------------------------------------------------------------------
	AMMOActorCinematicActor
-----------------------------------------------------------------------------*/

#if WITH_EDITOR
void AMMOActorCinematicActor::CheckForErrors()
{
	Super::CheckForErrors();

	// Warn the user that SkeletalMeshActorMAT should have Animations set to None, and AnimTreeTemplate assigned to something
	if( Mesh->Animations )
	{
		GWarn->MapCheck_Add( MCTYPE_WARNING, this, *FString::Printf( LocalizeSecure( LocalizeUnrealEd( "MapCheck_Message_SkelMeshActorMATAnimationsAssigned" ), *GetName() ) ), TEXT( "SkelMeshActorMATAnimationsAssigned" ) );
	}
	if( Mesh->AnimTreeTemplate == NULL )
	{
		GWarn->MapCheck_Add( MCTYPE_WARNING, this, *FString::Printf( LocalizeSecure( LocalizeUnrealEd( "MapCheck_Message_SkelMeshActorMATAnimTreeTemplateNotAssigned" ), *GetName() ) ), TEXT( "SkelMeshActorMATAnimTreeTemplateNotAssigned" ) );
	}
}

void AMMOActorCinematicActor::EditorReplacedActor (AActor* OldActor)
{
	if(OldActor->IsA(ASkeletalMeshActor::StaticClass()))
	{
		ASkeletalMeshActor* skma = Cast<ASkeletalMeshActor>(OldActor);
		if(skma)
		{
			Mesh->SkeletalMesh = skma->SkeletalMeshComponent->SkeletalMesh;
			Mesh->AnimSets = skma->SkeletalMeshComponent->AnimSets;
			Mesh->AnimTreeTemplate = skma->SkeletalMeshComponent->AnimTreeTemplate;
			if(!Mesh->AnimTreeTemplate)
			{
				Mesh->AnimTreeTemplate = Cast<UAnimTree>(StaticLoadObject( UAnimTree::StaticClass(), NULL, TEXT("AnimTree'AT_Common.AT_Common'"), NULL, LOAD_NoWarn | LOAD_Quiet, NULL ));
			}

			FLightingChannelContainer lc = skma->SkeletalMeshComponent->LightingChannels;
			lc.Gameplay_1 = TRUE;
			Mesh->SetLightingChannels(lc);
			Mesh->RootMotionMode = skma->SkeletalMeshComponent->RootMotionMode;
			Mesh->RootMotionRotationMode = skma->SkeletalMeshComponent->RootMotionRotationMode;
			Mesh->AnimRotationOnly = skma->SkeletalMeshComponent->AnimRotationOnly;
			Mesh->PhysicsAsset = skma->SkeletalMeshComponent->PhysicsAsset;
		}
	}
}

void ASkeletalMeshActor::EditorReplacedActor (AActor* OldActor)
{
	if(OldActor->IsA(AMMOActorCinematicActor::StaticClass()))
	{
		AMMOActorCinematicActor* skma = Cast<AMMOActorCinematicActor>(OldActor);
		if(skma)
		{
			SkeletalMeshComponent->SkeletalMesh = skma->Mesh->SkeletalMesh;
			SkeletalMeshComponent->AnimSets = skma->Mesh->AnimSets;
			SkeletalMeshComponent->AnimTreeTemplate = skma->Mesh->AnimTreeTemplate;
			if(!SkeletalMeshComponent->AnimTreeTemplate)
			{
				SkeletalMeshComponent->AnimTreeTemplate = Cast<UAnimTree>(StaticLoadObject( UAnimTree::StaticClass(), NULL, TEXT("AnimTree'AT_Common.AT_Common'"), NULL, LOAD_NoWarn | LOAD_Quiet, NULL ));
			}
			SkeletalMeshComponent->SetLightingChannels(skma->Mesh->LightingChannels);
			SkeletalMeshComponent->RootMotionMode = skma->Mesh->RootMotionMode;
			SkeletalMeshComponent->RootMotionRotationMode = skma->Mesh->RootMotionRotationMode;
			SkeletalMeshComponent->AnimRotationOnly = skma->Mesh->AnimRotationOnly;
			SkeletalMeshComponent->PhysicsAsset = skma->Mesh->PhysicsAsset;
		}
	} 
}

void ASkeletalMeshActorMAT::EditorReplacedActor (AActor* OldActor)
{
	if(OldActor->IsA(ASkeletalMeshActor::StaticClass()))
	{
		ASkeletalMeshActor* skma = Cast<ASkeletalMeshActor>(OldActor);
		if(skma)
		{
			SkeletalMeshComponent->SkeletalMesh = skma->SkeletalMeshComponent->SkeletalMesh;
			SkeletalMeshComponent->AnimSets = skma->SkeletalMeshComponent->AnimSets;
			SkeletalMeshComponent->AnimTreeTemplate = skma->SkeletalMeshComponent->AnimTreeTemplate;
			if(!SkeletalMeshComponent->AnimTreeTemplate)
			{
				SkeletalMeshComponent->AnimTreeTemplate = Cast<UAnimTree>(StaticLoadObject( UAnimTree::StaticClass(), NULL, TEXT("AnimTree'AT_Common.AT_Common'"), NULL, LOAD_NoWarn | LOAD_Quiet, NULL ));
			}

			FLightingChannelContainer lc = skma->SkeletalMeshComponent->LightingChannels;
			lc.Gameplay_1 = TRUE;
			SkeletalMeshComponent->SetLightingChannels(lc);
			SkeletalMeshComponent->RootMotionMode = skma->SkeletalMeshComponent->RootMotionMode;
			SkeletalMeshComponent->RootMotionRotationMode = skma->SkeletalMeshComponent->RootMotionRotationMode;
			SkeletalMeshComponent->AnimRotationOnly = skma->SkeletalMeshComponent->AnimRotationOnly;
			SkeletalMeshComponent->PhysicsAsset = skma->SkeletalMeshComponent->PhysicsAsset;
		}
	}
}

#endif

void AMMOActorCinematicActor::MAT_SetMorphWeight(FName MorphNodeName, FLOAT MorphWeight)
{
	if(Mesh)
	{
		UMorphNodeWeight* WeightNode = Cast<UMorphNodeWeight>(Mesh->FindMorphNode(MorphNodeName));
		if(WeightNode)
		{
			WeightNode->SetNodeWeight(MorphWeight);
		}
	}
}

void AMMOActorCinematicActor::MAT_SetSkelControlScale(FName SkelControlName, FLOAT Scale)
{
	if(Mesh)
	{
		USkelControlBase* Control = Mesh->FindSkelControl(SkelControlName);
		if(Control)
		{
			Control->BoneScale = Scale;
		}
	}
}

void AMMOActorCinematicActor::MAT_SetSkelControlStrength(FName SkelControlName,FLOAT ControlStrength)
{
	if(Mesh)
	{
		USkelControlBase* Control = Mesh->FindSkelControl(SkelControlName);
		if(Control)
		{
			Control->SetSkelControlStrength(ControlStrength, 0.f);
		}
	}
}

void AMMOActorCinematicActor::RegistToCharacterMap(UBOOL bAdd)
{
	if (bAdd)
	{
		static INT i = -2;
		--i;
		this->ServerID = i;
		MMOFacade::getSingleton().AddToCharacterMap(this, i);
	}
	else
	{
		MMOFacade::getSingleton().RemoveFromCharacterMap(this->ServerID);
	}


}

/* This is where we add information on slots and channels to the array that was passed in. */
void AMMOActorCinematicActor::GetAnimControlSlotDesc(TArray<struct FAnimSlotDesc>& OutSlotDescs)
{
	if( !Mesh->Animations )
	{
		// fail
		appMsgf(AMT_OK, TEXT("SkeletalMeshActorMAT has no AnimTree Instance."));
		return;
	}

	// Find all AnimSlotNodes in the AnimTree
	for(INT i=0; i<SlotNodes.Num(); i++)
	{
		// Number of channels available on this slot node.
		const INT NumChannels = SlotNodes(i)->Children.Num() - 1;

		if( SlotNodes(i)->NodeName != NAME_None && NumChannels > 0 )
		{
			// Add a new element
			const INT Index = OutSlotDescs.Add(1);
			OutSlotDescs(Index).SlotName	= SlotNodes(i)->NodeName;
			OutSlotDescs(Index).NumChannels	= NumChannels;
		}
	}
}

void AMMOActorCinematicActor::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	__super::PostEditChangeProperty(PropertyChangedEvent);
	if (PropertyChangedEvent.Property && PropertyChangedEvent.Property->GetName() == FString(TEXT("UseingAvatar")))
	{
		RefreshAvatar();
	}
}


//------------------------------------------------------------------------------------------------
// Begin Movie Capture
//------------------------------------------------------------------------------------------------
IMPLEMENT_CLASS(USeqAct_BeginMovieCapture)
IMPLEMENT_CLASS(USeqAct_EndMovieCapture)

extern bool g_disableAllInput;

void USeqAct_BeginMovieCapture::Activated()
{
	Super::Activated();
	
	if(InputLinks(0).bHasImpulse)
	{
		GEngine->bSuppressMapWarnings = TRUE;
		if(!ShowUI)
		{
			GEngine->Exec(TEXT("UI 0"));
		}

		if(DisableInput)
		{
			g_disableAllInput = true;
		}
		else
		{
			g_disableAllInput = false;
		}

		if (ShowPlayerSelf)
		{
			MMOFacade::getSingleton().GetMainController()->SetShowMainPlayer(TRUE);
		}
		else
		{
			MMOFacade::getSingleton().GetMainController()->SetShowMainPlayer(FALSE);
		}

		GIsBenchmarking = TRUE;
		GEngine->MatineeCaptureFPS = MovieCaptureFPS;

		GEngine->Exec(TEXT("StartMovieCapture"));
		
		ActivateOutputLink(0);
	}
}

void USeqAct_EndMovieCapture::Activated()
{
	Super::Activated();

	if(InputLinks(0).bHasImpulse)
	{
		GEngine->Exec(TEXT("UI 1"));

		g_disableAllInput = false;
		GIsBenchmarking = FALSE;

		MMOFacade::getSingleton().GetMainController()->SetShowMainPlayer(TRUE);

		GEngine->Exec(TEXT("StopMovieCapture"));

		ActivateOutputLink(0);
	}
}