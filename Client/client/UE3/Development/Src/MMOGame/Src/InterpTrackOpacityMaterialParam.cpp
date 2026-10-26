#include "stdafx.h"

IMPLEMENT_CLASS(UInterpTrackOpacityMaterialParam);
IMPLEMENT_CLASS(UInterpTrackInstOpacityMaterialParam);


/*-----------------------------------------------------------------------------
	UInterpTrackOpacityMaterialParam
-----------------------------------------------------------------------------*/

void UInterpTrackOpacityMaterialParam::PreSave()
{
	Super::PreSave();

// #if WITH_EDITORONLY_DATA
// 	PreSaveMaterialParamTrack(this, Materials);
// #endif // WITH_EDITORONLY_DATA
}

void UInterpTrackOpacityMaterialParam::PostLoad()
{
	Super::PostLoad();
// 	//@compatibility: update deprecated single Material property
// 	if (Material_DEPRECATED != NULL)
// 	{
// 		INT Index = Materials.AddZeroed();
// 		Materials(Index).TargetMaterial = Material_DEPRECATED;
// 	}
// 	//@compatibility: format of MaterialReferenceList has changed
// 
// 	if (GetLinker() != NULL && GetLinker()->Ver() < VER_CHANGED_MATPARAMTRACK_MATERIAL_REFERENCES && !IsTemplate())
// 	{
// 		bNeedsMaterialRefsUpdate = TRUE;
// 	}
}

void UInterpTrackOpacityMaterialParam::PreEditChange(UProperty* PropertyThatWillChange)
{
// 	PreEditChangeMaterialParamTrack();

	Super::PreEditChange(PropertyThatWillChange);
}

void UInterpTrackOpacityMaterialParam::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

// 	ULevel* MyLevel = GetTypedOuter<ULevel>();
// 	UInterpData* OwnerData = GetTypedOuter<UInterpData>();
// 	for (INT i = 0; i < Materials.Num(); i++)
// 	{
// 		Materials(i).AffectedMaterialRefs.Reset();
// 		Materials(i).AffectedPPChainMaterialRefs.Reset();
// 		if (!IsTemplate() && MyLevel != NULL && OwnerData != NULL)
// 		{
// 			MyLevel->GetMaterialRefs(Materials(i));
// 		}
// 	}
// 
// 	PostEditChangeMaterialParamTrack();
}

/** Add a new keyframe at the speicifed time. Returns index of new keyframe. */
INT UInterpTrackOpacityMaterialParam::AddKeyframe(FLOAT Time, UInterpTrackInst* TrInst, EInterpCurveMode InitInterpMode)
{
	INT NewKeyIndex = FloatTrack.AddPoint( Time, 0.f );
	FloatTrack.Points(NewKeyIndex).InterpMode = InitInterpMode;

	FloatTrack.AutoSetTangents(CurveTension);

	return NewKeyIndex;
}

/** 
*	Function which actually updates things based on the new position in the track. 
*  This is called in the editor, when scrubbing/previewing etc.
*/
void UInterpTrackOpacityMaterialParam::PreviewUpdateTrack(FLOAT NewPosition, UInterpTrackInst* TrInst)
{
	UpdateTrack(NewPosition, TrInst, FALSE);
}

/** 
*	Function which actually updates things based on the new position in the track. 
*  This is called in the game, when USeqAct_Interp is ticked
*  @param bJump	Indicates if this is a sudden jump instead of a smooth move to the new position.
*/
void UInterpTrackOpacityMaterialParam::UpdateTrack(FLOAT NewPosition, UInterpTrackInst* TrInst, UBOOL bJump)
{
	FLOAT NewFloatValue = FloatTrack.Eval(NewPosition, 0.f);
	UInterpTrackInstOpacityMaterialParam* ParamTrackInst = Cast<UInterpTrackInstOpacityMaterialParam>(TrInst);
	if (ParamTrackInst != NULL)
	{
		AActor* actor = ParamTrackInst->GetGroupActor();

		if(actor->IsA(AMMOActor::StaticClass()))
		{
			AMMOActor* mmoActor = Cast<AMMOActor>(actor);
			mmoActor->SetOpacity(ParamName, NewFloatValue);
			//if(mmoActor && mmoActor->ItemManager && mmoActor->ItemManager->MaterialController)
			{
				//mmoActor->ItemManager->MaterialController->SetOpacity(NewFloatValue);
			}
		}
// 		else if(actor->IsA(ASkeletalMeshActor::StaticClass()))
// 		{
// 			ASkeletalMeshActor* skActor = Cast<ASkeletalMeshActor>(actor);
// 			if(skActor && skActor->SkeletalMeshComponent)
// 			{
// 				skActor->SkeletalMeshComponent->SetOpacity(ParamName, NewFloatValue);
// 			}
// 		}

		/*for (INT i = 0; i < ParamTrackInst->MICInfos.Num(); i++)
		{
		for (INT j = 0; j < ParamTrackInst->MICInfos(i).MICs.Num(); j++)
		{
		if (ParamTrackInst->MICInfos(i).MICs(j) != NULL)
		{
		ParamTrackInst->MICInfos(i).MICs(j)->SetScalarParameterValue(ParamName, NewFloatValue);
		}
		}
		}*/
	}
}

void UInterpTrackOpacityMaterialParam::PostDuplicate()
{
// 	for (INT MaterialIndex = 0; MaterialIndex < Materials.Num(); ++MaterialIndex )
// 	{
// 		Materials(MaterialIndex).AffectedMaterialRefs.Reset();
// 		Materials(MaterialIndex).AffectedPPChainMaterialRefs.Reset();
// 	}
// 
// 	bNeedsMaterialRefsUpdate = TRUE;
}

/*-----------------------------------------------------------------------------
	UInterpTrackInstOpacityMaterialParam
-----------------------------------------------------------------------------*/

/**
 * Saves off the current float of the given parameter if one 
 * exists on the MIC. Otherwise, a zero float is saved.
 *
 * @param	ParameterName	The name of the MIC float parameter.
 * @param	MICInfo			The MIC data containing the reset float to set.
 * @param	MICIndex		The index of the MIC from the given MIC data for accessing the param float. 
 */
//extern void SaveResetFloatForMIC( const FName& ParameterName, FFloatMaterialParamMICData& MICInfo, INT MICIndex );

void UInterpTrackInstOpacityMaterialParam::InitTrackInst(UInterpTrack* Track)
{
	Super::InitTrackInst( Track );

	UInterpTrackOpacityMaterialParam* ParamTrack = Cast<UInterpTrackOpacityMaterialParam>(Track);
	if (ParamTrack != NULL)
	{
		if (GIsEditor && !GIsGame)
		{
			// remember track so we can be reinitialized if the track's material info changes
			InstancedTrack = ParamTrack;
		}

		AActor* actor = GetGroupActor();

		if(actor->IsA(AMMOActor::StaticClass()))
		{
			AMMOActor* mmoActor = Cast<AMMOActor>(actor);
			mmoActor->RebuildMaterialControllerList();
#pragma warning(push)
#pragma warning(disable:4302)
			mmoActor->SetToNewMaterialEffect(EMET_LoadOpacityMaterial, (INT)this, TRUE);			
#pragma warning(pop)
			//mmoActor->SetToNewMaterialEffect(EMET_ChangeMaterialProperty, (INT)this, TRUE);
			//if(mmoActor && mmoActor->ItemManager && mmoActor->ItemManager->MaterialController)
			{
				//mmoActor->ItemManager->MaterialController->SetOpacity(NewFloatValue);
			}
		}
// 		else if(actor->IsA(ASkeletalMeshActor::StaticClass()))
// 		{
// 			ASkeletalMeshActor* skActor = Cast<ASkeletalMeshActor>(actor);
// 			if(skActor && skActor->SkeletalMeshComponent)
// 			{
// 				//skActor->SkeletalMeshComponent->RebulidMeshMaterialList();
// 			}
// 		}
// 
// 		InitMaterialParamTrackInst(ParamTrack, ParamTrack->Materials, GetGroupActor(), ParamTrack->bNeedsMaterialRefsUpdate);
// 		ParamTrack->bNeedsMaterialRefsUpdate = FALSE;
// 			
// 		MICInfos.Reset();
// 		MICInfos.AddZeroed(ParamTrack->Materials.Num());
// 		for (INT i = 0; i < ParamTrack->Materials.Num(); i++)
// 		{
// 			FMaterialReferenceList& CurrentMaterial = ParamTrack->Materials(i);
// 			MICInfos(i).MICs.AddZeroed(CurrentMaterial.AffectedMaterialRefs.Num() + CurrentMaterial.AffectedPPChainMaterialRefs.Num());
// 			MICInfos(i).MICResetFloats.AddZeroed(CurrentMaterial.AffectedMaterialRefs.Num() + CurrentMaterial.AffectedPPChainMaterialRefs.Num());
// 			for (INT j = 0; j < CurrentMaterial.AffectedMaterialRefs.Num(); j++)
// 			{
// 				if (CurrentMaterial.AffectedMaterialRefs(j).Primitive != NULL)
// 				{
// 					UMaterialInterface* Material = CurrentMaterial.AffectedMaterialRefs(j).Primitive->GetElementMaterial(CurrentMaterial.AffectedMaterialRefs(j).MaterialIndex);
// 					if (Material != NULL)
// 					{
// 						// if the material is already a runtime-generated MIC, don't make the chain larger
// 						//NOTE - the check for standalone is to catch new material/MICs that have not been saved yet.  Otherwise the removal of TermTrackInst function will set the meshes material to the base material
// 						if (Material->GetNetIndex() == INDEX_NONE && !Material->HasAnyFlags(RF_Standalone) && Material->IsA(UMaterialInstanceConstant::StaticClass()))
// 						{
// 							MICInfos(i).MICs(j) = (UMaterialInstanceConstant*)Material;
// 						}
// 						else
// 						{
// 							MICInfos(i).MICs(j) = ConstructObject<UMaterialInstanceConstant>(UMaterialInstanceConstant::StaticClass(), this);
// 							MICInfos(i).MICs(j)->SetParent(Material);
// 							CurrentMaterial.AffectedMaterialRefs(j).Primitive->SetElementMaterial(CurrentMaterial.AffectedMaterialRefs(j).MaterialIndex, MICInfos(i).MICs(j));
// 						}
// 					}
// 
// 					SaveResetFloatForMIC( ParamTrack->ParamName, MICInfos(i), j );
// 				}
// 			}
// 			// evaluate the post process MIC refs... these refs should only exist in game
// 			INT ArrayOffset = CurrentMaterial.AffectedMaterialRefs.Num();
// 			for (INT k = 0; k < CurrentMaterial.AffectedPPChainMaterialRefs.Num(); k++)
// 			{
// 				if (CurrentMaterial.AffectedPPChainMaterialRefs(k).Effect != NULL)
// 				{
// 					UMaterialInterface* Material = CurrentMaterial.AffectedPPChainMaterialRefs(k).Effect->Material;
// 					if (Material != NULL)
// 					{
// 						// if the material is already a runtime-generated MIC, don't make the chain larger
// 						//NOTE - the check for standalone is to catch new material/MICs that have not been saved yet.  Otherwise the removal of TermTrackInst function will set the meshes material to the base material
// 						if (Material->GetNetIndex() == INDEX_NONE && !Material->HasAnyFlags(RF_Standalone) && Material->IsA(UMaterialInstanceConstant::StaticClass()))
// 						{
// 							MICInfos(i).MICs(ArrayOffset + k) = (UMaterialInstanceConstant*)Material;
// 						}
// 						else
// 						{
// 							MICInfos(i).MICs(ArrayOffset + k) = ConstructObject<UMaterialInstanceConstant>(UMaterialInstanceConstant::StaticClass(), this);
// 							MICInfos(i).MICs(ArrayOffset + k)->SetParent(Material);
// 							CurrentMaterial.AffectedPPChainMaterialRefs(k).Effect->Material = MICInfos(i).MICs(ArrayOffset + k);
// 						}
// 					}
// 
// 					SaveResetFloatForMIC( ParamTrack->ParamName, MICInfos(i), ArrayOffset + k );
// 				}
// 			}
// 		}
	}
}

void UInterpTrackInstOpacityMaterialParam::TermTrackInst(UInterpTrack* Track)
{
	AActor* actor = GetGroupActor();

	if(actor && actor->IsA(AMMOActor::StaticClass()))
	{
		AMMOActor* mmoActor = Cast<AMMOActor>(actor);
#pragma warning(push)
#pragma warning(disable:4302)
		mmoActor->SetToNewMaterialEffect(EMET_LoadOpacityMaterial, (INT)this, FALSE);
#pragma warning(pop)
	}

	// in the editor, we want to revert Actors to their original state
	// in game, leave the MIC around as Matinee changes persist when it is stopped
// 	if (GIsEditor && !GIsGame)
// 	{
// 		UInterpTrackOpacityMaterialParam* ParamTrack = Cast<UInterpTrackOpacityMaterialParam>(Track);
// 		if (ParamTrack != NULL)
// 		{
// 			for (INT i = 0; i < ParamTrack->Materials.Num() && i < MICInfos.Num(); i++)
// 			{
// 				for (INT j = 0; j < ParamTrack->Materials(i).AffectedMaterialRefs.Num(); j++)
// 				{
// 					if (MICInfos(i).MICs(j) != NULL && ParamTrack->Materials(i).AffectedMaterialRefs(j).Primitive != NULL)
// 					{
// 						ParamTrack->Materials(i).AffectedMaterialRefs(j).Primitive->SetElementMaterial(ParamTrack->Materials(i).AffectedMaterialRefs(j).MaterialIndex, MICInfos(i).MICs(j)->Parent);
// 					}
// 				}
// 			}
// 			for (INT i = 0; i < ParamTrack->Materials.Num() && i < MICInfos.Num(); i++)
// 			{
// 				INT ArrayOffset = ParamTrack->Materials(i).AffectedMaterialRefs.Num();
// 				for (INT j = 0; j < ParamTrack->Materials(i).AffectedPPChainMaterialRefs.Num(); j++)
// 				{
// 					if (MICInfos(i).MICs(ArrayOffset + j) != NULL && ParamTrack->Materials(i).AffectedPPChainMaterialRefs(j).Effect != NULL)
// 					{
// 						ParamTrack->Materials(i).AffectedPPChainMaterialRefs(j).Effect->Material = MICInfos(i).MICs(ArrayOffset + j)->Parent;
// 					}
// 				}
// 			}
// 		}
// 	}
// 	MICInfos.Empty();

	Super::TermTrackInst( Track );
}

/** Called before Interp editing to put object back to its original state. */
void UInterpTrackInstOpacityMaterialParam::SaveActorState(UInterpTrack* Track)
{
// 	UInterpTrackOpacityMaterialParam* ParamTrack = Cast<UInterpTrackOpacityMaterialParam>(Track);
// 	if (ParamTrack != NULL)
// 	{
// 		for (INT i = 0; i < ParamTrack->Materials.Num() && i < MICInfos.Num(); i++)
// 		{
// 			MICInfos(i).MICResetFloats.Reset();
// 			MICInfos(i).MICResetFloats.Add(MICInfos(i).MICs.Num());
// 			for (INT j = 0; j < MICInfos(i).MICs.Num(); j++)
// 			{
// 				SaveResetFloatForMIC( ParamTrack->ParamName, MICInfos(i), j );
// 			}
// 		}
// 	}
}

/** Restore the saved state of this Actor. */
void UInterpTrackInstOpacityMaterialParam::RestoreActorState(UInterpTrack* Track)
{
// 	UInterpTrackOpacityMaterialParam* ParamTrack = Cast<UInterpTrackOpacityMaterialParam>(Track);
// 	if (ParamTrack != NULL)
// 	{
// 		for (INT i = 0; i < ParamTrack->Materials.Num() && i < MICInfos.Num(); i++)
// 		{
// 			for (INT j = 0; j < MICInfos(i).MICs.Num(); j++)
// 			{
// 				if (MICInfos(i).MICs(j) != NULL)
// 				{
// 					check (MICInfos(i).MICResetFloats.Num() > j);
// 					MICInfos(i).MICs(j)->SetScalarParameterValue(ParamTrack->ParamName, MICInfos(i).MICResetFloats(j));
// 				}
// 			}
// 		}
// 	}
}