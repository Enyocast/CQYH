#include "stdafx.h"
#include "MMOFacade.h"

void UWeaponEffectStaticMeshComponent::SetHiddenGame(UBOOL NewHidden)
{
	if (!NewHidden)
	{
		return;
	}
	else
	{
		Super::SetHiddenGame(NewHidden);
	}

}

void UEquipMesh::SetSilhouette( UBOOL show, FVector sc )
{
	//if( PrimComponent != NULL )
	//{
	//	PrimComponent->ShowSilhouette = show;
	//	PrimComponent->SilhouetteColor = sc;
	//}
}

//void UEquipMesh::InitAnimation(class USkeletalMeshComponent* InSkeletalMesh,class AMMOActor* Target)
//{
//	//if (!InSkeletalMesh)
//	//{
//	//	return;
//	//}
//
//	//if (AnimationController)
//	//{
//	//	AnimationController->MarkPendingKill();
//	//	AnimationController = NULL;
//	//}
//
//	//AnimationController = ConstructObject<UMMOActorAT>(UMMOActorAT::StaticClass(), this);
//	//check(AnimationController);
//
//	//AnimationController->InitAnim(InSkeletalMesh, NULL);
//
//	//if (Target)
//	//{
//	//	AnimationController->SetIdleAnim(Target->GetIdleAnim());
//	//}
//
//
//}

//void UEquipMesh::InitComponent(class AMMOActor* target)
//{
//	//USkeletalMeshComponent* tSkeComponent = 0;
//	//USkeletalMeshComponent* BaseComponent = 0;
//	//UStaticMeshComponent* tStaComponent = 0;
//	//UParticleSystemComponent* tParComponent = 0;
//
//	//if( target == NULL )
//	//	return;
//
//	//if( PrimComponent != NULL )
//	//{
//	//	warnf(NAME_Error, TEXT("EquipMesh already initilized:%s -> %s"), *GetName(), *target->GetName() );
//	//	return;
//	//}
//
//	//if(ResourceType == ECRT_SkeletalMesh)
//	//{
//	//	if(SkeletalMesh == NULL)
//	//	{
//	//		warnf(NAME_Error, TEXT("EquipMesh SkeletaMesh is NULL:%s -> %s"), *GetName(), *target->GetName());
//	//		return;
//	//	}
//	//	else
//	//	{
//	//		BaseComponent = target->GetMasterComponent();
//	//		if(BaseComponent == NULL)
//	//		{
//	//			warnf(NAME_Error,  TEXT("EquipMesh Master component is NULL:%s -> %s"), *GetName(), *target->GetName());
//	//			return;
//	//		}
//
//	//		// [test code
//	//		//if( SkeletalMesh->GetName() == "MA_F_Cap" )
//	//		//{ // this specific mesh crashes
//	//		//	warnf( NAME_Error, TEXT("Debug code: MA_F_Cap") );
//	//		//}
//	//		// test code]
//
//	//		tSkeComponent = ConstructObject<USkeletalMeshComponent>(USkeletalMeshComponent::StaticClass(), this);
//	//		tSkeComponent->SetSkeletalMesh(SkeletalMesh);
//
//	//		if(AnimationType ==  EUAT_BaseAnimation)
//	//		{
//	//			tSkeComponent->SetParentAnimComponent(BaseComponent);
//
//	//			//`log( "Set parent anim comp:"@outer@tSkeComponent@Target->outer@BaseComponent );
//	//		}
//	//		else if(AnimationType == EUAT_SelfAnimation)
//	//		{
//	//			tSkeComponent->SetAnimTreeTemplate(AnimTree);
//	//			tSkeComponent->AnimSets.Remove(0, tSkeComponent->AnimSets.Num());
//	//			tSkeComponent->AnimSets.AddItem(AnimSet);
//
//	//			InitAnimation(tSkeComponent, target);
//
//	//			//WeaponActionLoopBlendNode = Cast<UAnimNodeBlend>(tSkeComponent->FindAnimNode(TEXT("WeaponActionLoopBlendNode")));
//	//			//ActionNode = Cast<UAnimNodeSequence>(tSkeComponent->FindAnimNode(TEXT("Action")));
//	//			//LoopNode = Cast<UAnimNodeSequence>(tSkeComponent->FindAnimNode(TEXT("Idle")));
//
//	//			//if (WeaponActionLoopBlendNode && ActionNode &&  LoopNode)
//	//			//{
//	//			//	WeaponActionLoopBlendNode->SetBlendTarget(1.0, 0.f);
//	//			//	LoopNode->SetAnim(IdleAnim);
//	//			//	LoopNode->PlayAnim(TRUE, 1.0, 0.f);
//	//			//}
//	//		}
//
//	//		//tSkeComponent->RebulidMeshMaterialList(FALSE);
//
//	//		//if( MeshType == EBMT_Hair )
//	//		//{	// only hair need this, to change its color.
//	//		//	for(int i = 0; i < SkeletalMesh->Materials.Num(); i++)
//	//		//	{
//	//		//		UMaterialInstanceConstant* pMaterialInstance = CastChecked<UMaterialInstanceConstant>( StaticConstructObject(
//	//		//			UMaterialInstanceConstant::StaticClass(), GetOuter() ) );
//	//		//		pMaterialInstance->SetParent(SkeletalMesh->Materials(i));
//	//		//		tSkeComponent->SetMaterial(i, pMaterialInstance);
//	//		//	}
//	//		//}
//
//	//		PrimComponent = tSkeComponent;
//	//		
//	//	}
//	//}
//	//else if(ResourceType == ECRT_StaticMesh)
//	//{
//	//	if(StaticMesh == NULL)
//	//	{
//	//		warnf( NAME_Error, TEXT("EquipMesh StaticMesh is NULL:%s -> %s"), *GetName(), *target->GetName());
//	//		return;
//	//	}
//	//	else
//	//	{
//	//		//tStaComponent = new UStaticMeshComponent;
//	//		tStaComponent = Cast<UStaticMeshComponent>(
//	//			StaticConstructObject( UStaticMeshComponent::StaticClass(),
//	//				/*GetTransientPackage()*/target, NAME_None, RF_Public | RF_Transactional ) );
//	//		tStaComponent->SetStaticMesh(StaticMesh);
//	//		//if(target->LightEnvironment!=NULL)
//	//		//{
//	//		//	tStaComponent->SetLightEnvironment(target->LightEnvironment);
//	//			//tStaComponent.SetLightingChannels(BaseComponent.LightingChannels);
//
//	//			//`log( "Set light environment comp:"@tStaComponent@Target->LightEnvironment );
//	//		//}
//
//	//		//tSkeComponent->RebulidMeshMaterialList(FALSE);
//	//		PrimComponent = tStaComponent;
//
//
//	//		if ((MeshType == EBMT_Weapon || MeshType == EBMT_Weapon2) && !target->IsA(ANPC::StaticClass()))
//	//		{
//	//			FString subRes = StaticMesh->GetPathName() + FString(TEXT("_Shell"));
//	//			if (StaticMesh->IsInExportedPackage())
//	//			{
//	//				FString OldName = StaticMesh->GetName();
//	//				FString NewName = StaticMesh->GetName() + FString(TEXT("_Shell"));
//
//	//				FString OuterName = StaticMesh->GetOuter()->GetName();
//	//				OuterName = OuterName.LeftChop(OldName.Len());
//	//				subRes = OuterName + NewName + TEXT(".") + NewName;
//	//			}
//	//			UStaticMesh* SubStaticMesh = Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, *subRes, NULL, LOAD_NoWarn|LOAD_Quiet, NULL));
//	//			if (SubStaticMesh)
//	//			{
//	//				UStaticMeshComponent* NewSubComponent = Cast<UStaticMeshComponent>(StaticConstructObject( UWeaponEffectStaticMeshComponent::StaticClass(), target));
//	//				if (NewSubComponent)
//	//				{
//	//					NewSubComponent->SetStaticMesh(SubStaticMesh);
//	//					SubPrimComponent = NewSubComponent;
//	//					SubPrimComponent->bIgnoreOwnerHidden = TRUE;
//	//					SubPrimComponent->SetHiddenGame(TRUE);
//	//				}
//	//			}
//	//		}
//	//	}
//	//}
//	//else if(ResourceType == ECRT_Particle)
//	//{
//	//	if(ParticleSystem == NULL)
//	//	{
//	//		warnf( NAME_Error, TEXT("EquipMesh  ParticleSystem is NULL:%s -> %s"), *GetName(), *target->GetName());
//	//		return;
//	//	}
//	//	else
//	//	{
//	//		tParComponent = ConstructObject<UParticleSystemComponent>(UParticleSystemComponent::StaticClass(), this);
//	//		check(tParComponent);
//	//		tParComponent->SetTemplate(ParticleSystem);
//	//		tParComponent->ActivateSystem(true);
//	//		PrimComponent = tParComponent;
//	//	}
//	//}
//
//	//if (PrimComponent)
//	//{
//	//	PrimComponent->Scale = Clamp<FLOAT>(this->Scale, 0.1, 5.0);
//	//	if (SubPrimComponent)
//	//	{
//	//		SubPrimComponent->Scale = PrimComponent->Scale;
//	//	}
//
//	//	// disable decals
//	//	PrimComponent->bAcceptsStaticDecals = FALSE;
//	//	PrimComponent->bAcceptsDynamicDecals = FALSE;
//	//}
//}

//void UEquipMesh::SetVisible(UBOOL bVisible)
//{
//	//if (PrimComponent)
//	//{
//	//	PrimComponent->SetHiddenGame(!bVisible);
//	//}
//
//	//for (INT i = 0; i < AttachedEmitters.Num(); ++i)
//	//{
//	//	if (AttachedEmitters(i))
//	//	{
//	//		AttachedEmitters(i)->SetHidden(!bVisible);
//	//	}
//	//}
//}

//void UEquipMesh::AddAttachedEmitter(class AMMOEmitter* InEmitter)
//{
//	if (!InEmitter)
//	{
//		debugf(TEXT("Add a null Emitter"));
//		return;
//	}
//
//	AttachedEmitters.AddItem(InEmitter);
//}
//
//void UEquipMesh::DestroyAttachedEmitters()
//{
//	for (INT i = 0; i < AttachedEmitters.Num(); ++i)
//	{
//		if (AttachedEmitters(i))
//		{
//			GWorld->DestroyActor(AttachedEmitters(i));
//		}
//	}
//
//	AttachedEmitters.Empty();
//}



UBOOL UEquipMesh::OnTakeOn(class AMMOActor* Target, UBOOL UseMergedMesh)
{
	//check(Target);
	if( Target == NULL )
	{
		debugf( TEXT("UEquipMesh::OnTakeOn failed: no target.") );
		return FALSE;
	}

	USkeletalMeshComponent* BaseComponent = Target->GetMasterComponent();
	if (BaseComponent == NULL)
	{
		debugf(TEXT("BaseComponent is none, check!!!!"));
		return FALSE;
	}

	// do nothing for To-Be-Merged meshes
	if (MeshType < EBMT_NoMerge && !UseMergedMesh)
	{
		return TRUE;
	}

	if (MeshType == EBMT_Weapon || MeshType == EBMT_Weapon2 || MeshType == EBMT_LShoulder || MeshType == EBMT_RShoulder || MeshType == EBMT_BackOrnamental)
	{
		if (!ArmorTemplate)
		{
			warnf(TEXT("ArmorTemplate is null, %s"), *(GetPathName()));
			return FALSE;
		}

		AArmorActor* ArmorActor = Cast<AArmorActor>(GWorld->SpawnActor(AArmorActor::StaticClass()));
		if (!ArmorActor)
		{
			return FALSE;
		}
		
		ArmorActor->OnTakeOn(Target, this);
		Target->AttachEquip(MeshType, ArmorActor, !Target->bHidden);
	
	}
	else
	{
		// temp check
		if (ResourceType != ECRT_SkeletalMesh || ComponentAddingType != ECAT_AddToBaseActor || AnimationType != EUAT_BaseAnimation || SkeletalMesh == NULL)
		{
			return FALSE;
		}
		else
		{
			USkeletalMeshComponent* NewComponent = ConstructObject<USkeletalMeshComponent>(USkeletalMeshComponent::StaticClass(), Target);
			if (!NewComponent)
			{
				warnf(TEXT("construct UskeletalMeshComponent failed, %s"), *(GetFullName()));
				return FALSE;
			}

			NewComponent->SetSkeletalMesh(SkeletalMesh);
			NewComponent->SetParentAnimComponent(BaseComponent);

			NewComponent->RebulidMeshMaterialList();

			// disable decals
			NewComponent->bAcceptsStaticDecals = FALSE;
			NewComponent->bAcceptsDynamicDecals = FALSE;
			Target->AttachEquip( MeshType, NewComponent, true );

			NewComponent->SetLightingChannels(BaseComponent->LightingChannels);
			NewComponent->SetLightEnvironment(Target->LightEnvironment);
			NewComponent->bAllowShadowFade = TRUE;
			NewComponent->SetHiddenGame( FALSE );


			if( MeshType == EBMT_Helmet )
			{
				if( Target->ItemManager->bHelmetHidden )
				{
					// the helmet has been hidden by logic
					// hide self
					NewComponent->SetHiddenGame(TRUE);
					Target->SetEquipVisibleFlag( EBMT_Helmet, FALSE );
				}
				else
				{
					// show self
					NewComponent->SetHiddenGame(FALSE);
					Target->SetEquipVisibleFlag( EBMT_Helmet, TRUE );
				}
			}

			if( MeshType == EBMT_Hair && Target->ItemManager)
			{
				Target->ItemManager->ApplyHairColor( Target->ItemManager->CurrentHairColorIdx );
			}

			DoHideCheck(Target, TRUE);

			if (Target->IsBaseMeshHidden())
			{
				NewComponent->SetHiddenGame(TRUE);
			}
		}
	}
	return TRUE;
}

void UEquipMesh::DoHideCheck(class AMMOActor* Target,UBOOL TakeOn)
{
	if( Target == NULL || Target->ItemManager == NULL )
		return;

	if( MeshType == EBMT_Helmet )
	{	
		// the helmet has been hidden by logic
		if( TakeOn && Target->ItemManager->bHelmetHidden )
		{
			// moved to OnTakeOn to avoid the one frame flash
		}
		// put on the helmet should hide the hair
		else if( bHideFlag )
		{
			USkeletalMeshComponent* HairComponent = Cast<USkeletalMeshComponent>(Target->GetEquip(EBMT_Hair));
			if (HairComponent)
			{
				HairComponent->SetHiddenGame(TakeOn);
				Target->SetEquipVisibleFlag(EBMT_Hair, !TakeOn);
			}
		}
	}
	else if( MeshType == EBMT_Hair )
	{
		AArmorActor* Helmet = Cast<AArmorActor>(Target->GetEquip(EBMT_Helmet));
		if (Helmet && Helmet->Template->bHideFlag)
		{
			USkeletalMeshComponent* HairComponent = Cast<USkeletalMeshComponent>(Target->GetEquip(EBMT_Hair));
			if (HairComponent)
			{
				HairComponent->SetHiddenGame(TRUE);
				Target->SetEquipVisibleFlag(EBMT_Hair, FALSE);
			}
			
		}
	}
	// add other rules here
}

UBOOL UEquipMesh::OnTakeOff(class AMMOActor* Target, UBOOL UseMergedMesh)
{

	//local SkeletalMeshComponent BaseComponent;

	if( MeshType < EBMT_NoMerge && !UseMergedMesh )	// do nothing for To-Be-Merged meshes
		return TRUE;

	if( Target == NULL)
	{
		debugf(TEXT("OnTakeOff:Target == NULL"));
		return FALSE;
	}

	USkeletalMeshComponent* BaseComponent = Target->GetMasterComponent();
	if(BaseComponent == NULL)
	{
		debugf(TEXT("BaseComponent is none, check"));
		return FALSE;
	}

	Target->DetachEquip( MeshType );

	DoHideCheck(Target, FALSE);

	return TRUE;
}


//------------------------------------------------------------------------
void UEquipMesh::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
#if WITH_EDITOR
	_UpdatePropertyEdit();
#endif
	Super::PostEditChangeProperty(PropertyChangedEvent);
}

#if WITH_EDITOR
void UEquipMesh::PostLoad()
{
	Super::PostLoad();
	_UpdatePropertyEdit();
}

void UEquipMesh::_UpdatePropertyEdit()
{

	//if(MeshType <= EBMT_NoMerge)
	//{
	//	ResourceType = ECRT_SkeletalMesh;
	//	ShowSkeletalMesh = TRUE;
	//	ShowStaticMesh = FALSE;
	//	ShowParticle = FALSE;
	//	ComponentAddingType = ECAT_AddToBaseActor;
	//	ShowTexture = TRUE;
	//	ShowSocket = FALSE;
	//	ShowCarrySocket = FALSE;
	//	ShowAnimsets = FALSE;
	//}
	//else if (MeshType == EBMT_Weapon)
	//{
	//	ComponentAddingType = ECAT_AttachToBaseSocket;
	//	ShowTexture = FALSE;
	//	ShowSocket = TRUE;
	//	ShowCarrySocket = TRUE;

	//	if (ResourceType == ECRT_StaticMesh)
	//	{
	//		ShowSkeletalMesh = FALSE;
	//		ShowStaticMesh = TRUE;
	//		ShowParticle = FALSE;
	//		ShowAnimsets = FALSE;
	//	}
	//	else if (ResourceType == ECRT_SkeletalMesh)
	//	{
	//		ShowSkeletalMesh = TRUE;
	//		ShowStaticMesh = FALSE;
	//		ShowParticle = FALSE;
	//		ShowAnimsets = TRUE;
	//	}
	//	else if (ResourceType == ECRT_Particle)
	//	{
	//		ShowSkeletalMesh = FALSE;
	//		ShowStaticMesh = FALSE;
	//		ShowParticle = TRUE;
	//		ShowAnimsets = FALSE;
	//	}
	//}
	//else 
	//{
	//	//ComponentAddingType = ECAT_AttachToBaseSocket;
	//	ShowTexture = FALSE;
	//	ShowSocket = TRUE;
	//	ShowCarrySocket = TRUE;

	//	ShowSkeletalMesh = TRUE;
	//	ShowStaticMesh = TRUE;
	//	ShowParticle = FALSE;
	//	ShowAnimsets = FALSE;
	//}
}
#endif


//FLOAT UEquipMesh::PlayAnimation(FName Anim,INT InKey,FLOAT Rate,UBOOL bLoop,BYTE RootBoneAxisX,BYTE RootBoneAxisY,BYTE RootBoneAxisZ,BYTE BlendType,FLOAT Position,FLOAT InBlendIn,FLOAT InBlendOut,BYTE InAnimLevel)
//{
//	if (AnimationController)
//	{
//		return AnimationController->PlayAnimation(Anim, InKey, Rate, bLoop, RootBoneAxisX, RootBoneAxisY, RootBoneAxisZ, BlendType, Position, InBlendIn, InBlendOut, InAnimLevel);
//	}
//
//	return 0.f;
//}

//void UEquipMesh::PlayAnim(FName Anim,UBOOL bLoop,FLOAT InRate, FLOAT InStartTime)
//{
//	if (WeaponActionLoopBlendNode && ActionNode && LoopNode)
//	{
//		USkeletalMeshComponent* sm = Cast<USkeletalMeshComponent>(PrimComponent);
//		if (sm == NULL || sm->FindAnimSequence(Anim) == FALSE)
//		{
//			warnf(TEXT("Play Weapon Anim, but the mesh does not have the anim : %s"), *(Anim.ToString()));
//			return;
//		}
//
//		WeaponActionLoopBlendNode->SetBlendTarget(0.f, 0.f);
//		ActionNode->SetAnim(Anim);
//		ActionNode->PlayAnim(bLoop, InRate, InStartTime);
//	}
//}

//void UEquipMesh::PlayAnimByKey(FName Anim,UBOOL bLoop,FLOAT InRate,FLOAT InStartTime,INT InKey)
//{
//	if (WeaponActionLoopBlendNode && ActionNode && LoopNode)
//	{
//		USkeletalMeshComponent* sm = Cast<USkeletalMeshComponent>(PrimComponent);
//		if (sm == NULL || sm->FindAnimSequence(Anim) == FALSE)
//		{
//			warnf(TEXT("Play Weapon Anim, but the mesh does not have the anim : %s"), *(Anim.ToString()));
//			return;
//		}
//
//		WeaponActionLoopBlendNode->SetBlendTarget(0.f, 0.f);
//		ActionNode->SetAnim(Anim);
//		ActionNode->PlayAnim(bLoop, InRate, InStartTime);
//		CurrentAnimKey = InKey;
//	}
//
//}
//void UEquipMesh::StopAnimByKey(INT InKey)
//{
//	if (WeaponActionLoopBlendNode && ActionNode && LoopNode && CurrentAnimKey == InKey)
//	{
//		ActionNode->StopAnim();
//		WeaponActionLoopBlendNode->SetBlendTarget(1.f, 0.f);
//		CurrentAnimKey = 0;
//	}
//}

//void UEquipMesh::OnAnimEnd(class UAnimNodeSequence* SeqNode,FLOAT PlayedTime,FLOAT ExcessTime)
//	{
//	if (WeaponActionLoopBlendNode && ActionNode && LoopNode)
//	{
//		if (SeqNode == ActionNode)
//		{
//			WeaponActionLoopBlendNode->SetBlendTarget(1.f, 0.1f);
//			CurrentAnimKey = 0;
//		}
//	}
//}

//void UEquipMesh::RefreshAnim()
//{
//	if (WeaponActionLoopBlendNode && ActionNode && LoopNode)
//	{
//		WeaponActionLoopBlendNode->SetBlendTarget(1.0, 0.1f);
//		LoopNode->SetAnim(IdleAnim);
//		LoopNode->PlayAnim(TRUE, 1.0, 0.f);
//	}
//}

#if WITH_EDITOR
void UEquipMesh::CheckForError(class UEquipAppearence* parent)
{
	//Super::CheckForErrors();

 	switch(ResourceType)
 	{
 	case ECRT_StaticMesh:
		if(ShowStaticMesh && !StaticMesh)
		{
			GWarn->MapCheck_Add(MCTYPE_ERROR,  parent,
				*LocalizeUnrealEdMMO(TEXT("CheckError_StaticMeshIsNull")), NULL);
		}
 		break;

 	case ECRT_SkeletalMesh:
		if(ShowSkeletalMesh && !SkeletalMesh)
		{
			GWarn->MapCheck_Add(MCTYPE_ERROR,  parent,
				*LocalizeUnrealEdMMO(TEXT("CheckError_SkeletalMeshIsNull")), NULL);
		}

 		break;

 	case ECRT_Particle:
		if(ShowParticle && !ParticleSystem)
		{
			GWarn->MapCheck_Add(MCTYPE_ERROR,  parent,
				*LocalizeUnrealEdMMO(TEXT("CheckError_ParticleSystemIsNull")), NULL);
		}
 		break;
 	}

 	switch(AnimationType)
	{
 	case EUAT_SelfAnimation:
		{
			if(ShowAnimsets && !AnimSet)
			{
				GWarn->MapCheck_Add(MCTYPE_ERROR,  parent,
					*LocalizeUnrealEdMMO(TEXT("CheckError_AnimSetIsNull")), NULL);
			}

			if(ShowAnimsets && !AnimTree)
			{
				GWarn->MapCheck_Add(MCTYPE_ERROR,  parent,
					*LocalizeUnrealEdMMO(TEXT("CheckError_AnimTreeIsNull")), NULL);
			}
		}
 		break;
	}

	if(MeshType == EBMT_Weapon)
	{
		if(ShowSocket && (SocketName == NAME_None))
		{
			GWarn->MapCheck_Add(MCTYPE_ERROR,  parent,
				*LocalizeUnrealEdMMO(TEXT("CheckError_SocketNameError")), NULL);
		}

		if(bSupportSwithAttachSocket && (CarrySocketName == NAME_None))
		{
			GWarn->MapCheck_Add(MCTYPE_ERROR,  parent,
				*LocalizeUnrealEdMMO(TEXT("CheckError_CarrySocketNameError")), NULL);
		}
	}

// 	if(ShowTexture && !BaseTexture)
// 	{
// 		GWarn->MapCheck_Add(MCTYPE_ERROR,  parent,
// 			*LocalizeUnrealEdMMO(TEXT("CheckError_BaseTextureError")), NULL);
// 	}
// 
// 	if(ShowTexture && !RegionTexture)
// 	{
// 		GWarn->MapCheck_Add(MCTYPE_ERROR,  parent,
// 			*LocalizeUnrealEdMMO(TEXT("CheckError_RegionTextureError")), NULL);
// 	}

}
#endif
//void UEquipMesh::SetMaterialInstanceParamValue(FLinearColor NewColor, FName Param)
//{
//	USkeletalMeshComponent* skeletalComponent = Cast<USkeletalMeshComponent>(PrimComponent);
//
//	if (!skeletalComponent)
//		return;
//
//	for(int i = 0; i < skeletalComponent->Materials.Num(); i++)
//	{
//		UMaterialInstance* pMaterialInstance = ( UMaterialInstance* ) skeletalComponent->Materials(i);
//		if(pMaterialInstance)
//			 pMaterialInstance->SetVectorParameterValue( Param,NewColor );
//	}
//
//}

//void UEquipMesh::SetSkeletMesh(USkeletalMesh* mesh)
//{
//	USkeletalMeshComponent* skeletalComponent = Cast<USkeletalMeshComponent>(PrimComponent);
//	if (skeletalComponent)
//	{
//		skeletalComponent->SetSkeletalMesh(mesh);
//		skeletalComponent->RebulidMeshMaterialList();
//	}
//}