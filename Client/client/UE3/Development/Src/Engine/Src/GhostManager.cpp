
//qin@snda
#include "EnginePrivate.h"
#include "EngineAnimClasses.h"

IMPLEMENT_CLASS(AGhostManager)

//void AGhostManager::AddGhostActor(AActor* Actor, USkeletalMeshComponent* BaseMeshComponent,
//	INT MaxGhosts, const FColor& GhostColor, float GhostInterval, FLOAT GhostLife)
//{
//	if (!Actor || !BaseMeshComponent)
//	{
//		return;
//	}
//	for (INT i = 0; i < ActiveGhosts.Num(); ++i)
//	{
//		if (ActiveGhosts(i).BaseActor == Actor)
//		{
//			return;
//		}
//	}
//
//	FActiveGhostInfo GhostInfo;
//	GhostInfo.BaseActor = Actor;
//	GhostInfo.ParentAnimComponent = BaseMeshComponent->ParentAnimComponent;
//	GhostInfo.BaseMeshComponent = BaseMeshComponent;
//
//	FVector Location = Actor->Location;
//	FRotator Rotation = Actor->Rotation;
//	for (INT i = 0; i < 2/*MaxGhosts*/; ++i)
//	{
//		ASkeletalMeshActorSpawnable* GhostActor = Cast<ASkeletalMeshActorSpawnable>(GWorld->SpawnActor(
//			ASkeletalMeshActorSpawnable::StaticClass(), NAME_None, Location, Rotation, NULL, TRUE));
//		if (GhostActor)
//		{
//			GhostActor->ClearComponents();
//
//			USkeletalMeshComponent* SkeletalMeshComponent = GhostActor->SkeletalMeshComponent;
//			SkeletalMeshComponent->AnimTreeTemplate = NULL;
//			SkeletalMeshComponent->Animations = NULL;
//			SkeletalMeshComponent->AnimTickArray.Empty();
//			SkeletalMeshComponent->AnimAlwaysTickArray.Empty();
//			SkeletalMeshComponent->AnimTickRelevancyArray.Empty();
//			SkeletalMeshComponent->AnimTickWeightsArray.Empty();
//			SkeletalMeshComponent->SkelControlTickArray.Empty();
//			SkeletalMeshComponent->SkeletalMesh = BaseMeshComponent->SkeletalMesh;
//			SkeletalMeshComponent->ParentBoneMap = BaseMeshComponent->ParentBoneMap;
//
//			//for( INT j = 0; j < BaseMeshComponent->Materials.Num(); ++j )
//			//{
//			//	UMaterialInstance* pIns = CastChecked<UMaterialInstanceConstant>( StaticConstructObject(
//			//		UMaterialInstanceConstant::StaticClass(), GetOuter() ) );
//			//	pIns->SetParent( GhostMaterialTemplate );
//			//	SkeletalMeshComponent->Materials.Push(pIns);
//			//}
//
//			ASkeletalMeshActorSpawnable* ParentActor = Cast<ASkeletalMeshActorSpawnable>(GWorld->SpawnActor(
//				ASkeletalMeshActorSpawnable::StaticClass(), NAME_None, Location, Rotation, NULL, TRUE));
//			USkeletalMeshComponent* ParentAnimComponent = ParentActor->SkeletalMeshComponent;
//			ParentAnimComponent->SkeletalMesh = BaseMeshComponent->SkeletalMesh;
//			//ParentAnimComponent->SpaceBases = BaseMeshComponent->SpaceBases;
//			//ParentAnimComponent->LocalAtoms = BaseMeshComponent->LocalAtoms;
//			//ParentAnimComponent->CachedLocalAtoms = BaseMeshComponent->CachedLocalAtoms;
//			//ParentAnimComponent->CachedSpaceBases = BaseMeshComponent->CachedSpaceBases;
//			//ParentAnimComponent->RequiredBones = BaseMeshComponent->RequiredBones;
//			//ParentAnimComponent->ComposeOrderedRequiredBones = BaseMeshComponent->ComposeOrderedRequiredBones;
//			//ParentAnimComponent->BoneVisibilityStates = BaseMeshComponent->BoneVisibilityStates;
//			//ParentAnimComponent->SkelControlIndex = BaseMeshComponent->SkelControlIndex;
//			//for (INT j = 0; j < BaseMeshComponent->Attachments.Num(); ++j)
//			//{
//			//	const FAttachment& Attachment = BaseMeshComponent->Attachments(j);
//			//	UStaticMeshComponent* Component = Cast<UStaticMeshComponent>(Attachment.Component);
//			//	if (!Component)
//			//	{
//			//		continue;
//			//	}
//
//			//	UStaticMeshComponent* NewComponent = Cast<UStaticMeshComponent>(StaticConstructObject(
//			//		UStaticMeshComponent::StaticClass(), GetTransientPackage(), NAME_None, RF_Transient));
//			//	if (NewComponent)
//			//	{
//			//		NewComponent->SetStaticMesh(Component->StaticMesh);
//			//		ParentAnimComponent->AttachComponent(NewComponent, Attachment.BoneName, Attachment.RelativeLocation,
//			//			Attachment.RelativeRotation, Attachment.RelativeScale);
//
//			//		for( INT k = 0; k < Max(1, Component->Materials.Num()); ++k )
//			//		{
//			//			UMaterialInstance* pIns = CastChecked<UMaterialInstanceConstant>( StaticConstructObject(
//			//				UMaterialInstanceConstant::StaticClass(), GetOuter() ) );
//			//			pIns->SetParent( GhostMaterialTemplate );
//			//			NewComponent->Materials.Push(pIns);
//			//		}
//			//	}
//			//}
//
//			GhostActor->SkeletalMeshComponent->ParentAnimComponent = ParentAnimComponent;
//			GhostActor->ConditionalUpdateComponents();
//
//			//ParentActor->SetHidden(TRUE);
//			ParentActor->SetTickIsDisabled(TRUE);
//			GhostInfo.ParentActors.Push(ParentActor);
//			GhostInfo.GhostActors.Push(GhostActor);
//			//GhostInfo.LifeRemaining.Push(GhostLifeSpan);
//		}
//	}
//	ActiveGhosts.Push(GhostInfo);
//}
//
//void AGhostManager::RemoveGhostActor(AActor* Actor)
//{
//	if (!Actor)
//	{
//		return;
//	}
//
//	for (INT i = 0; i < ActiveGhosts.Num(); ++i)
//	{
//		if (ActiveGhosts(i).BaseActor == Actor)
//		{
//			ActiveGhosts.Remove(i);
//			break;
//		}
//	}
//}
//
//void AGhostManager::ClearGhostActors()
//{
//	ActiveGhosts.Empty();
//}
//
//void AGhostManager::TickSpecial(FLOAT DeltaTime)
//{
//	//BOOL Follow = TRUE;
//	//AccumulatedTime += DeltaTime;
//	//if (AccumulatedTime < 0.03f)
//	//{
//	//	Follow = FALSE;
//	//}
//	//else
//	//{
//	//	AccumulatedTime = 0.0f;
//	//}
//
//	for (INT i = 0; i < ActiveGhosts.Num(); ++i)
//	{
//		const FActiveGhostInfo& GhostInfo = ActiveGhosts(i);
//		//for (INT j = 0; j < GhostInfo.LifeRemaining.Num(); ++j)
//		//{
//		//	GhostInfo.LifeRemaining(j) -= DeltaTime;
//		//	if (GhostInfo.LifeRemaining(j) < 0.0f)
//		//	{
//
//		//	}
//		//}
//
//		//FLOAT Distance = GhostInfo.ParentActors(0)->Location.Distance(GhostInfo.BaseActor->Location);
//		//FLOAT Intensity = Clamp(Distance / 200.0f, 0.0f, 1.0f);
//		//FLOAT Scale = 1.0f - Clamp(Distance / 400.0f, 0.0f, 1.0f);
//		////if (Follow)
//		//{
//		//	//GhostInfo.ParentActors(0)->SetLocation(GhostInfo.BaseActor->Location);
//		//	//GhostInfo.ParentActors(0)->SetRotation(GhostInfo.BaseActor->Rotation);
//		//	//GhostInfo.ParentActors(0)->SetDrawScale(GhostInfo.BaseActor->DrawScale * Scale);
//		//	//GhostInfo.GhostActors(0)->SetHidden(TRUE);
//		//}
//		GhostInfo.GhostActors(0)->SkeletalMeshComponent->ParentAnimComponent->SpaceBases = GhostInfo.ParentAnimComponent->SpaceBases;
//		GhostInfo.GhostActors(0)->SkeletalMeshComponent->ParentAnimComponent->LocalAtoms = GhostInfo.ParentAnimComponent->LocalAtoms;
//		GhostInfo.GhostActors(0)->SkeletalMeshComponent->ParentAnimComponent->CachedLocalAtoms = GhostInfo.ParentAnimComponent->CachedLocalAtoms;
//		GhostInfo.GhostActors(0)->SkeletalMeshComponent->ParentAnimComponent->CachedSpaceBases = GhostInfo.ParentAnimComponent->CachedSpaceBases;
//		GhostInfo.GhostActors(0)->SkeletalMeshComponent->ParentAnimComponent->RequiredBones = GhostInfo.ParentAnimComponent->RequiredBones;
//		GhostInfo.GhostActors(0)->SkeletalMeshComponent->ParentAnimComponent->ComposeOrderedRequiredBones = GhostInfo.ParentAnimComponent->ComposeOrderedRequiredBones;
//		GhostInfo.GhostActors(0)->SkeletalMeshComponent->ParentAnimComponent->BoneVisibilityStates = GhostInfo.ParentAnimComponent->BoneVisibilityStates;
//		GhostInfo.GhostActors(0)->SkeletalMeshComponent->ParentAnimComponent->SkelControlIndex = GhostInfo.ParentAnimComponent->SkelControlIndex;
//
//		//for( INT j = 0; j < GhostInfo.GhostActors(0)->SkeletalMeshComponent->Materials.Num(); ++j )
//		//{
//		//	UMaterialInstance* pIns = Cast<UMaterialInstance>(GhostInfo.GhostActors(0)->SkeletalMeshComponent->Materials(j));
//		//	if (pIns)
//		//	{
//		//		pIns->SetScalarParameterValue( "Intensity", Intensity );
//		//	}
//		//}
//		//for (INT j = 0; j < GhostInfo.GhostActors(0)->SkeletalMeshComponent->ParentAnimComponent->Attachments.Num(); ++j)
//		//{
//		//	const FAttachment& Attachment = GhostInfo.GhostActors(0)->SkeletalMeshComponent->ParentAnimComponent->Attachments(j);
//		//	UStaticMeshComponent* Component = Cast<UStaticMeshComponent>(Attachment.Component);
//		//	if (!Component)
//		//	{
//		//		continue;
//		//	}
//
//		//	for( INT k = 0; k < Max(1, Component->Materials.Num()); ++k )
//		//	{
//		//		UMaterialInstance* pIns = Cast<UMaterialInstance>(Component->Materials(k));
//		//		if (pIns)
//		//		{
//		//			pIns->SetScalarParameterValue( "Intensity", Intensity );
//		//		}
//		//	}
//		//}
//
//		for (INT j = GhostInfo.GhostActors.Num() - 1; j > 0; --j)
//		{
//			//FLOAT Distance = GhostInfo.ParentActors(j)->Location.Distance(GhostInfo.BaseActor->Location);
//			//FLOAT Intensity = Clamp(Distance / 200.0f, 0.0f, 1.0f);
//			//FLOAT Scale = 1.0f - Clamp(Distance / 400.0f, 0.0f, 1.0f);
//			////if (Follow)
//			//{
//			//	//GhostInfo.ParentActors(j)->SetLocation(GhostInfo.ParentActors(j - 1)->Location);
//			//	//GhostInfo.ParentActors(j)->SetRotation(GhostInfo.ParentActors(j - 1)->Rotation);
//			//	//GhostInfo.ParentActors(j)->SetDrawScale(GhostInfo.BaseActor->DrawScale * Scale);
//
//				USkeletalMeshComponent* ParentAnimComponent = GhostInfo.ParentActors(j)->SkeletalMeshComponent;
//				if (GhostInfo.ParentActors(j)->Location == GhostInfo.BaseActor->Location &&
//					GhostInfo.ParentActors(j)->Rotation == GhostInfo.BaseActor->Rotation)
//				{
//					GhostInfo.GhostActors(j)->SetHidden(TRUE);
//					for (INT k = 0; k < ParentAnimComponent->Attachments.Num(); ++k)
//					{
//						UStaticMeshComponent* MeshComponent = Cast<UStaticMeshComponent>(ParentAnimComponent->Attachments(k).Component);
//						if (MeshComponent)
//						{
//							MeshComponent->SetHiddenGame(TRUE);
//							MeshComponent->SetHiddenEditor(TRUE);
//						}
//					}
//				}
//				else
//				{
//					GhostInfo.GhostActors(j)->SetHidden(FALSE);
//					for (INT k = 0; k < ParentAnimComponent->Attachments.Num(); ++k)
//					{
//						UStaticMeshComponent* MeshComponent = Cast<UStaticMeshComponent>(ParentAnimComponent->Attachments(k).Component);
//						if (MeshComponent)
//						{
//							MeshComponent->SetHiddenGame(FALSE);
//							MeshComponent->SetHiddenEditor(FALSE);
//						}
//					}
//				}
//			//}
//			GhostInfo.GhostActors(j)->SkeletalMeshComponent->ParentAnimComponent->SpaceBases = GhostInfo.GhostActors(j - 1)->SkeletalMeshComponent->ParentAnimComponent->SpaceBases;
//			GhostInfo.GhostActors(j)->SkeletalMeshComponent->ParentAnimComponent->LocalAtoms = GhostInfo.GhostActors(j - 1)->SkeletalMeshComponent->ParentAnimComponent->LocalAtoms;
//			GhostInfo.GhostActors(j)->SkeletalMeshComponent->ParentAnimComponent->CachedLocalAtoms = GhostInfo.GhostActors(j - 1)->SkeletalMeshComponent->ParentAnimComponent->CachedLocalAtoms;
//			GhostInfo.GhostActors(j)->SkeletalMeshComponent->ParentAnimComponent->CachedSpaceBases = GhostInfo.GhostActors(j - 1)->SkeletalMeshComponent->ParentAnimComponent->CachedSpaceBases;
//			GhostInfo.GhostActors(j)->SkeletalMeshComponent->ParentAnimComponent->RequiredBones = GhostInfo.GhostActors(j - 1)->SkeletalMeshComponent->ParentAnimComponent->RequiredBones;
//			GhostInfo.GhostActors(j)->SkeletalMeshComponent->ParentAnimComponent->ComposeOrderedRequiredBones = GhostInfo.GhostActors(j - 1)->SkeletalMeshComponent->ParentAnimComponent->ComposeOrderedRequiredBones;
//			GhostInfo.GhostActors(j)->SkeletalMeshComponent->ParentAnimComponent->BoneVisibilityStates = GhostInfo.GhostActors(j - 1)->SkeletalMeshComponent->ParentAnimComponent->BoneVisibilityStates;
//			GhostInfo.GhostActors(j)->SkeletalMeshComponent->ParentAnimComponent->SkelControlIndex = GhostInfo.GhostActors(j - 1)->SkeletalMeshComponent->ParentAnimComponent->SkelControlIndex;
//
//			//for( INT k = 0; k < GhostInfo.GhostActors(j)->SkeletalMeshComponent->Materials.Num(); ++k )
//			//{
//			//	UMaterialInstance* pIns = Cast<UMaterialInstance>(GhostInfo.GhostActors(j)->SkeletalMeshComponent->Materials(k));
//			//	if (pIns)
//			//	{
//			//		pIns->SetScalarParameterValue( "Intensity", Intensity );
//			//	}
//			//}
//			//for (INT k = 0; k < GhostInfo.GhostActors(j)->SkeletalMeshComponent->ParentAnimComponent->Attachments.Num(); ++k)
//			//{
//			//	const FAttachment& Attachment = GhostInfo.GhostActors(j)->SkeletalMeshComponent->ParentAnimComponent->Attachments(k);
//			//	UStaticMeshComponent* Component = Cast<UStaticMeshComponent>(Attachment.Component);
//			//	if (!Component)
//			//	{
//			//		continue;
//			//	}
//
//			//	for( INT m = 0; m < Max(1, Component->Materials.Num()); ++m )
//			//	{
//			//		UMaterialInstance* pIns = Cast<UMaterialInstance>(Component->Materials(m));
//			//		if (pIns)
//			//		{
//			//			pIns->SetScalarParameterValue( "Intensity", Intensity );
//			//		}
//			//	}
//			//}
//		}
//	}
//}

//void AGhostManager::AddGhostActor(AActor* Actor, USkeletalMeshComponent* BaseMeshComponent,
//	INT MaxGhosts, const FColor& GhostColor, float GhostInterval, FLOAT GhostLife)
//{
//	if (!Actor || !BaseMeshComponent)
//	{
//		return;
//	}
//	for (INT i = 0; i < ActiveGhosts.Num(); ++i)
//	{
//		if (ActiveGhosts(i).BaseActor == Actor)
//		{
//			return;
//		}
//	}
//
//	FActiveGhostInfo GhostInfo;
//	GhostInfo.MaxGhosts = 100;
//	GhostInfo.GhostColor;
//	GhostInfo.GhostInterval = 0.3f;
//	GhostInfo.GhostLife = 1.0f;
//	GhostInfo.AccumulatedTime = 0.0f;
//
//	GhostInfo.BaseActor = Actor;
//	GhostInfo.ParentAnimComponent = BaseMeshComponent->ParentAnimComponent;
//	GhostInfo.BaseMeshComponent = BaseMeshComponent;
//	ActiveGhosts.Push(GhostInfo);
//}
//
//void AGhostManager::RemoveGhostActor(AActor* Actor)
//{
//	if (!Actor)
//	{
//		return;
//	}
//
//	for (INT i = 0; i < ActiveGhosts.Num(); ++i)
//	{
//		if (ActiveGhosts(i).BaseActor == Actor)
//		{
//			ActiveGhosts.Remove(i);
//			break;
//		}
//	}
//}
//
//void AGhostManager::ClearGhostActors()
//{
//	ActiveGhosts.Empty();
//}
//
//void AGhostManager::TickSpecial(FLOAT DeltaTime)
//{
//	for (INT i = 0; i < ActiveGhosts.Num(); ++i)
//	{
//		FActiveGhostInfo& GhostInfo = ActiveGhosts(i);
//		for (INT j = 0; j < GhostInfo.LifeRemaining.Num(); ++j)
//		{
//			if (GhostInfo.LifeRemaining(j) <= 0.0f)
//			{
//				continue;
//			}
//
//			GhostInfo.LifeRemaining(j) -= DeltaTime;
//			if (GhostInfo.LifeRemaining(j) < 0.0f)
//			{
//				GhostInfo.GhostActors(j)->SetHidden(TRUE);
//				GhostInfo.ParentActors(j)->SetHidden(TRUE);
//			}
//			else
//			{
//				FLOAT Intensity = GhostInfo.LifeRemaining(j) / GhostInfo.GhostLife;
//				for( INT k = 0; k < GhostInfo.ParentActors(j)->SkeletalMeshComponent->Materials.Num(); ++k )
//				{
//					UMaterialInstance* pIns = Cast<UMaterialInstance>(GhostInfo.ParentActors(j)->SkeletalMeshComponent->Materials(k));
//					if (pIns)
//					{
//						pIns->SetScalarParameterValue( "Intensity", Intensity );
//					}
//				}
//				for (INT k = 0; k < GhostInfo.ParentActors(j)->SkeletalMeshComponent->Attachments.Num(); ++k)
//				{
//					const FAttachment& Attachment = GhostInfo.ParentActors(j)->SkeletalMeshComponent->Attachments(k);
//					UStaticMeshComponent* Component = Cast<UStaticMeshComponent>(Attachment.Component);
//					if (!Component)
//					{
//						continue;
//					}
//
//					for( INT m = 0; m < Max(1, Component->Materials.Num()); ++m )
//					{
//						UMaterialInstance* pIns = Cast<UMaterialInstance>(Component->Materials(m));
//						if (pIns)
//						{
//							pIns->SetScalarParameterValue( "OpacityMultiply", Intensity );
//						}
//					}
//				}
//			}
//		}
//
//		if (GhostInfo.GhostActors.Num() < GhostInfo.MaxGhosts)
//		{
//			GhostInfo.AccumulatedTime += DeltaTime;
//			if (GhostInfo.AccumulatedTime < GhostInfo.GhostInterval)
//			{
//				continue;
//			}
//
//			// Spawn
//			AActor* BaseActor = GhostInfo.BaseActor;
//			FVector Location = GhostInfo.BaseActor->Location;
//			FRotator Rotation = GhostInfo.BaseActor->Rotation;
//
//			ASkeletalMeshActorSpawnable* GhostActor = Cast<ASkeletalMeshActorSpawnable>(GWorld->SpawnActor(
//				ASkeletalMeshActorSpawnable::StaticClass(), NAME_None, Location, Rotation, NULL, TRUE));
//			if (GhostActor)
//			{
//				GhostActor->ClearComponents();
//				GhostActor->SkeletalMeshComponent->AnimTreeTemplate = NULL;
//				GhostActor->SkeletalMeshComponent->Animations = NULL;
//				GhostActor->SkeletalMeshComponent->AnimTickArray.Empty();
//				GhostActor->SkeletalMeshComponent->AnimAlwaysTickArray.Empty();
//				GhostActor->SkeletalMeshComponent->AnimTickRelevancyArray.Empty();
//				GhostActor->SkeletalMeshComponent->AnimTickWeightsArray.Empty();
//				GhostActor->SkeletalMeshComponent->SkelControlTickArray.Empty();
//				GhostActor->SkeletalMeshComponent->SkeletalMesh = GhostInfo.BaseMeshComponent->SkeletalMesh;
//				GhostActor->SkeletalMeshComponent->ParentBoneMap = GhostInfo.BaseMeshComponent->ParentBoneMap;
//
//				ASkeletalMeshActorSpawnable* ParentActor = Cast<ASkeletalMeshActorSpawnable>(GWorld->SpawnActor(
//					ASkeletalMeshActorSpawnable::StaticClass(), NAME_None, Location, Rotation, NULL, TRUE));
//				USkeletalMeshComponent* ParentAnimComponent = ParentActor->SkeletalMeshComponent;
//				ParentAnimComponent->AnimTreeTemplate = NULL;
//				ParentAnimComponent->Animations = NULL;
//				ParentAnimComponent->SkeletalMesh = GhostInfo.BaseMeshComponent->SkeletalMesh;
//				//ParentAnimComponent->AnimTickArray = GhostInfo.ParentAnimComponent->AnimTickArray;
//				//ParentAnimComponent->AnimAlwaysTickArray = GhostInfo.ParentAnimComponent->AnimAlwaysTickArray;
//				//ParentAnimComponent->AnimTickRelevancyArray = GhostInfo.ParentAnimComponent->AnimTickRelevancyArray;
//				//ParentAnimComponent->AnimTickWeightsArray = GhostInfo.ParentAnimComponent->AnimTickWeightsArray;
//				//ParentAnimComponent->SkelControlTickArray = GhostInfo.ParentAnimComponent->SkelControlTickArray;
//				//ParentAnimComponent->SpaceBases = GhostInfo.ParentAnimComponent->SpaceBases;
//				//ParentAnimComponent->LocalAtoms = GhostInfo.ParentAnimComponent->LocalAtoms;
//				//ParentAnimComponent->CachedLocalAtoms = GhostInfo.ParentAnimComponent->CachedLocalAtoms;
//				//ParentAnimComponent->CachedSpaceBases = GhostInfo.ParentAnimComponent->CachedSpaceBases;
//				//ParentAnimComponent->RequiredBones = GhostInfo.ParentAnimComponent->RequiredBones;
//				//ParentAnimComponent->ComposeOrderedRequiredBones = GhostInfo.ParentAnimComponent->ComposeOrderedRequiredBones;
//				//ParentAnimComponent->BoneVisibilityStates = GhostInfo.ParentAnimComponent->BoneVisibilityStates;
//				//ParentAnimComponent->SkelControlIndex = GhostInfo.ParentAnimComponent->SkelControlIndex;
//				for( INT j = 0; j < GhostInfo.BaseMeshComponent->Materials.Num(); ++j )
//				{
//					UMaterialInstance* pIns = CastChecked<UMaterialInstanceConstant>( StaticConstructObject(
//						UMaterialInstanceConstant::StaticClass(), GetOuter() ) );
//					if (pIns)
//					{
//						pIns->SetParent( GhostMaterialTemplate );
//						//ParentActor->SkeletalMeshComponent->Materials.Push(pIns);
//						GhostActor->SkeletalMeshComponent->Materials.Push(pIns);
//					}
//				}
//				for (INT j = 0; j < GhostInfo.ParentAnimComponent->Attachments.Num(); ++j)
//				{
//					const FAttachment& Attachment = GhostInfo.ParentAnimComponent->Attachments(j);
//					UStaticMeshComponent* Component = Cast<UStaticMeshComponent>(Attachment.Component);
//					if (!Component)
//					{
//						continue;
//					}
//
//					UStaticMeshComponent* NewComponent = Cast<UStaticMeshComponent>(StaticConstructObject(
//						UStaticMeshComponent::StaticClass(), GetTransientPackage(), NAME_None, RF_Transient));
//					if (NewComponent)
//					{
//						NewComponent->SetStaticMesh(Component->StaticMesh);
//						//ParentAnimComponent->AttachComponent(NewComponent, Attachment.BoneName, Attachment.RelativeLocation,
//						//	Attachment.RelativeRotation, Attachment.RelativeScale);
//						GhostActor->SkeletalMeshComponent->AttachComponent(NewComponent, Attachment.BoneName,
//							Attachment.RelativeLocation, Attachment.RelativeRotation, Attachment.RelativeScale);
//
//						for( INT k = 0; k < Max(1, Component->Materials.Num()); ++k )
//						{
//							UMaterialInstance* pIns = CastChecked<UMaterialInstanceConstant>( StaticConstructObject(
//								UMaterialInstanceConstant::StaticClass(), GetOuter() ) );
//							if (pIns)
//							{
//								pIns->SetParent( GhostMaterialTemplate );
//								NewComponent->Materials.Push(pIns);
//							}
//						}
//					}
//				}
//				//ParentActor->SetHidden(TRUE);
//
//				GhostActor->SkeletalMeshComponent->ParentAnimComponent = ParentAnimComponent;
//				GhostActor->MarkComponentsAsDirty(FALSE);
//				ParentActor->MarkComponentsAsDirty(FALSE);
//				GhostActor->ConditionalUpdateComponents();
//				ParentActor->ConditionalUpdateComponents();
//
//				ParentAnimComponent->AnimTickArray = GhostInfo.ParentAnimComponent->AnimTickArray;
//				ParentAnimComponent->AnimAlwaysTickArray = GhostInfo.ParentAnimComponent->AnimAlwaysTickArray;
//				ParentAnimComponent->AnimTickRelevancyArray = GhostInfo.ParentAnimComponent->AnimTickRelevancyArray;
//				ParentAnimComponent->AnimTickWeightsArray = GhostInfo.ParentAnimComponent->AnimTickWeightsArray;
//				ParentAnimComponent->SkelControlTickArray = GhostInfo.ParentAnimComponent->SkelControlTickArray;
//				ParentAnimComponent->SpaceBases = GhostInfo.ParentAnimComponent->SpaceBases;
//				ParentAnimComponent->LocalAtoms = GhostInfo.ParentAnimComponent->LocalAtoms;
//				ParentAnimComponent->CachedLocalAtoms = GhostInfo.ParentAnimComponent->CachedLocalAtoms;
//				ParentAnimComponent->CachedSpaceBases = GhostInfo.ParentAnimComponent->CachedSpaceBases;
//				ParentAnimComponent->RequiredBones = GhostInfo.ParentAnimComponent->RequiredBones;
//				ParentAnimComponent->ComposeOrderedRequiredBones = GhostInfo.ParentAnimComponent->ComposeOrderedRequiredBones;
//				ParentAnimComponent->BoneVisibilityStates = GhostInfo.ParentAnimComponent->BoneVisibilityStates;
//				ParentAnimComponent->SkelControlIndex = GhostInfo.ParentAnimComponent->SkelControlIndex;
//
//				ParentActor->SetLocation(GhostInfo.BaseActor->Location);
//				ParentActor->SetRotation(GhostInfo.BaseActor->Rotation);
//				ParentActor->SetDrawScale(GhostInfo.BaseActor->DrawScale);
//				GhostActor->SetTickIsDisabled(TRUE);
//				ParentActor->SetTickIsDisabled(TRUE);
//				GhostInfo.ParentActors.Push(ParentActor);
//				GhostInfo.GhostActors.Push(GhostActor);
//				GhostInfo.LifeRemaining.Push(GhostInfo.GhostLife);
//			}
//
//			GhostInfo.AccumulatedTime = 0.0f;
//		}
//	}
//}

//void AGhostManager::AddGhostActor(AActor* Actor, USkeletalMeshComponent* BaseMeshComponent,
//	INT MaxGhosts, const FColor& GhostColor, float GhostInterval, FLOAT GhostLife)
//{
//	if (!Actor || !BaseMeshComponent)
//	{
//		return;
//	}
//	for (INT i = 0; i < ActiveGhosts.Num(); ++i)
//	{
//		if (ActiveGhosts(i).BaseActor == Actor)
//		{
//			return;
//		}
//	}
//
//	FActiveGhostInfo GhostInfo;
//	GhostInfo.MaxGhosts = 100;
//	GhostInfo.GhostColor;
//	GhostInfo.GhostInterval = 0.3f;
//	GhostInfo.GhostLife = 1.0f;
//	GhostInfo.AccumulatedTime = 0.0f;
//
//	GhostInfo.BaseActor = Actor;
//	GhostInfo.ParentAnimComponent = BaseMeshComponent->ParentAnimComponent;
//	GhostInfo.BaseMeshComponent = BaseMeshComponent;
//	ActiveGhosts.Push(GhostInfo);
//}
//
//void AGhostManager::RemoveGhostActor(AActor* Actor)
//{
//	if (!Actor)
//	{
//		return;
//	}
//
//	for (INT i = 0; i < ActiveGhosts.Num(); ++i)
//	{
//		if (ActiveGhosts(i).BaseActor == Actor)
//		{
//			ActiveGhosts.Remove(i);
//			break;
//		}
//	}
//}
//
//void AGhostManager::ClearGhostActors()
//{
//	ActiveGhosts.Empty();
//}
//
//void AGhostManager::TickSpecial(FLOAT DeltaTime)
//{
//	for (INT i = 0; i < ActiveGhosts.Num(); ++i)
//	{
//		FActiveGhostInfo& GhostInfo = ActiveGhosts(i);
//		for (INT j = 0; j < GhostInfo.LifeRemaining.Num(); ++j)
//		{
//			if (GhostInfo.LifeRemaining(j) <= 0.0f)
//			{
//				continue;
//			}
//
//			GhostInfo.LifeRemaining(j) -= DeltaTime;
//			if (GhostInfo.LifeRemaining(j) < 0.0f)
//			{
//				GhostInfo.GhostActors(j)->SetHidden(TRUE);
//				GhostInfo.ParentActors(j)->SetHidden(TRUE);
//			}
//			else
//			{
//				FLOAT Intensity = GhostInfo.LifeRemaining(j) / GhostInfo.GhostLife;
//				for( INT k = 0; k < GhostInfo.ParentActors(j)->SkeletalMeshComponent->Materials.Num(); ++k )
//				{
//					UMaterialInstance* pIns = Cast<UMaterialInstance>(GhostInfo.ParentActors(j)->SkeletalMeshComponent->Materials(k));
//					if (pIns)
//					{
//						pIns->SetScalarParameterValue( "Intensity", Intensity );
//					}
//				}
//				for (INT k = 0; k < GhostInfo.ParentActors(j)->SkeletalMeshComponent->Attachments.Num(); ++k)
//				{
//					const FAttachment& Attachment = GhostInfo.ParentActors(j)->SkeletalMeshComponent->Attachments(k);
//					UStaticMeshComponent* Component = Cast<UStaticMeshComponent>(Attachment.Component);
//					if (!Component)
//					{
//						continue;
//					}
//
//					for( INT m = 0; m < Max(1, Component->Materials.Num()); ++m )
//					{
//						UMaterialInstance* pIns = Cast<UMaterialInstance>(Component->Materials(m));
//						if (pIns)
//						{
//							pIns->SetScalarParameterValue( "OpacityMultiply", Intensity );
//						}
//					}
//				}
//			}
//		}
//
//		if (GhostInfo.GhostActors.Num() < GhostInfo.MaxGhosts)
//		{
//			GhostInfo.AccumulatedTime += DeltaTime;
//			if (GhostInfo.AccumulatedTime < GhostInfo.GhostInterval)
//			{
//				continue;
//			}
//
//			// Spawn
//			AActor* BaseActor = GhostInfo.BaseActor;
//			FVector Location = GhostInfo.BaseActor->Location;
//			FRotator Rotation = GhostInfo.BaseActor->Rotation;
//
//			ASkeletalMeshActorSpawnable* GhostActor = Cast<ASkeletalMeshActorSpawnable>(GWorld->SpawnActor(
//				ASkeletalMeshActorSpawnable::StaticClass(), NAME_None, Location, Rotation, NULL, TRUE));
//			if (GhostActor)
//			{
//				GhostActor->ClearComponents();
//				GhostActor->SkeletalMeshComponent->AnimTreeTemplate = NULL;
//				GhostActor->SkeletalMeshComponent->Animations = NULL;
//				GhostActor->SkeletalMeshComponent->AnimTickArray.Empty();
//				GhostActor->SkeletalMeshComponent->AnimAlwaysTickArray.Empty();
//				GhostActor->SkeletalMeshComponent->AnimTickRelevancyArray.Empty();
//				GhostActor->SkeletalMeshComponent->AnimTickWeightsArray.Empty();
//				GhostActor->SkeletalMeshComponent->SkelControlTickArray.Empty();
//				GhostActor->SkeletalMeshComponent->SkeletalMesh = GhostInfo.BaseMeshComponent->SkeletalMesh;
//				GhostActor->SkeletalMeshComponent->ParentBoneMap = GhostInfo.BaseMeshComponent->ParentBoneMap;
//
//				ASkeletalMeshActorSpawnable* ParentActor = Cast<ASkeletalMeshActorSpawnable>(GWorld->SpawnActor(
//					ASkeletalMeshActorSpawnable::StaticClass(), NAME_None, Location, Rotation, NULL, TRUE));
//				USkeletalMeshComponent* ParentAnimComponent = ParentActor->SkeletalMeshComponent;
//				ParentAnimComponent->AnimTreeTemplate = NULL;
//				ParentAnimComponent->Animations = NULL;
//				ParentAnimComponent->SkeletalMesh = GhostInfo.BaseMeshComponent->SkeletalMesh;
//				//ParentAnimComponent->AnimTickArray = GhostInfo.ParentAnimComponent->AnimTickArray;
//				//ParentAnimComponent->AnimAlwaysTickArray = GhostInfo.ParentAnimComponent->AnimAlwaysTickArray;
//				//ParentAnimComponent->AnimTickRelevancyArray = GhostInfo.ParentAnimComponent->AnimTickRelevancyArray;
//				//ParentAnimComponent->AnimTickWeightsArray = GhostInfo.ParentAnimComponent->AnimTickWeightsArray;
//				//ParentAnimComponent->SkelControlTickArray = GhostInfo.ParentAnimComponent->SkelControlTickArray;
//				//ParentAnimComponent->SpaceBases = GhostInfo.ParentAnimComponent->SpaceBases;
//				//ParentAnimComponent->LocalAtoms = GhostInfo.ParentAnimComponent->LocalAtoms;
//				//ParentAnimComponent->CachedLocalAtoms = GhostInfo.ParentAnimComponent->CachedLocalAtoms;
//				//ParentAnimComponent->CachedSpaceBases = GhostInfo.ParentAnimComponent->CachedSpaceBases;
//				//ParentAnimComponent->RequiredBones = GhostInfo.ParentAnimComponent->RequiredBones;
//				//ParentAnimComponent->ComposeOrderedRequiredBones = GhostInfo.ParentAnimComponent->ComposeOrderedRequiredBones;
//				//ParentAnimComponent->BoneVisibilityStates = GhostInfo.ParentAnimComponent->BoneVisibilityStates;
//				//ParentAnimComponent->SkelControlIndex = GhostInfo.ParentAnimComponent->SkelControlIndex;
//				for( INT j = 0; j < GhostInfo.BaseMeshComponent->Materials.Num(); ++j )
//				{
//					UMaterialInstance* pIns = CastChecked<UMaterialInstanceConstant>( StaticConstructObject(
//						UMaterialInstanceConstant::StaticClass(), GetOuter() ) );
//					if (pIns)
//					{
//						pIns->SetParent( GhostMaterialTemplate );
//						//ParentActor->SkeletalMeshComponent->Materials.Push(pIns);
//						GhostActor->SkeletalMeshComponent->Materials.Push(pIns);
//					}
//				}
//				for (INT j = 0; j < GhostInfo.ParentAnimComponent->Attachments.Num(); ++j)
//				{
//					const FAttachment& Attachment = GhostInfo.ParentAnimComponent->Attachments(j);
//					UStaticMeshComponent* Component = Cast<UStaticMeshComponent>(Attachment.Component);
//					if (!Component)
//					{
//						continue;
//					}
//
//					UStaticMeshComponent* NewComponent = Cast<UStaticMeshComponent>(StaticConstructObject(
//						UStaticMeshComponent::StaticClass(), GetTransientPackage(), NAME_None, RF_Transient));
//					if (NewComponent)
//					{
//						NewComponent->SetStaticMesh(Component->StaticMesh);
//						//ParentAnimComponent->AttachComponent(NewComponent, Attachment.BoneName, Attachment.RelativeLocation,
//						//	Attachment.RelativeRotation, Attachment.RelativeScale);
//						GhostActor->SkeletalMeshComponent->AttachComponent(NewComponent, Attachment.BoneName,
//							Attachment.RelativeLocation, Attachment.RelativeRotation, Attachment.RelativeScale);
//
//						for( INT k = 0; k < Max(1, Component->Materials.Num()); ++k )
//						{
//							UMaterialInstance* pIns = CastChecked<UMaterialInstanceConstant>( StaticConstructObject(
//								UMaterialInstanceConstant::StaticClass(), GetOuter() ) );
//							if (pIns)
//							{
//								pIns->SetParent( GhostMaterialTemplate );
//								NewComponent->Materials.Push(pIns);
//							}
//						}
//					}
//				}
//				//ParentActor->SetHidden(TRUE);
//
//				GhostActor->SkeletalMeshComponent->ParentAnimComponent = ParentAnimComponent;
//				GhostActor->MarkComponentsAsDirty(FALSE);
//				ParentActor->MarkComponentsAsDirty(FALSE);
//				GhostActor->ConditionalUpdateComponents();
//				ParentActor->ConditionalUpdateComponents();
//
//				ParentAnimComponent->AnimTickArray = GhostInfo.ParentAnimComponent->AnimTickArray;
//				ParentAnimComponent->AnimAlwaysTickArray = GhostInfo.ParentAnimComponent->AnimAlwaysTickArray;
//				ParentAnimComponent->AnimTickRelevancyArray = GhostInfo.ParentAnimComponent->AnimTickRelevancyArray;
//				ParentAnimComponent->AnimTickWeightsArray = GhostInfo.ParentAnimComponent->AnimTickWeightsArray;
//				ParentAnimComponent->SkelControlTickArray = GhostInfo.ParentAnimComponent->SkelControlTickArray;
//				ParentAnimComponent->SpaceBases = GhostInfo.ParentAnimComponent->SpaceBases;
//				ParentAnimComponent->LocalAtoms = GhostInfo.ParentAnimComponent->LocalAtoms;
//				ParentAnimComponent->CachedLocalAtoms = GhostInfo.ParentAnimComponent->CachedLocalAtoms;
//				ParentAnimComponent->CachedSpaceBases = GhostInfo.ParentAnimComponent->CachedSpaceBases;
//				ParentAnimComponent->RequiredBones = GhostInfo.ParentAnimComponent->RequiredBones;
//				ParentAnimComponent->ComposeOrderedRequiredBones = GhostInfo.ParentAnimComponent->ComposeOrderedRequiredBones;
//				ParentAnimComponent->BoneVisibilityStates = GhostInfo.ParentAnimComponent->BoneVisibilityStates;
//				ParentAnimComponent->SkelControlIndex = GhostInfo.ParentAnimComponent->SkelControlIndex;
//
//				ParentActor->SetLocation(GhostInfo.BaseActor->Location);
//				ParentActor->SetRotation(GhostInfo.BaseActor->Rotation);
//				ParentActor->SetDrawScale(GhostInfo.BaseActor->DrawScale);
//				GhostActor->SetTickIsDisabled(TRUE);
//				ParentActor->SetTickIsDisabled(TRUE);
//				GhostInfo.ParentActors.Push(ParentActor);
//				GhostInfo.GhostActors.Push(GhostActor);
//				GhostInfo.LifeRemaining.Push(GhostInfo.GhostLife);
//			}
//
//			GhostInfo.AccumulatedTime = 0.0f;
//		}
//	}
//}

INT AGhostManager::AddGhostObject(AActor* Actor, USkeletalMeshComponent* BaseMeshComponent, const FColor& GhostColor, FLOAT GhostLife)
{
	if (!Actor || !BaseMeshComponent)
	{
		return -1;
	}

	INT Index = -1;
	for (INT i = 0; i < ActiveGhosts.Num(); ++i)
	{
		if (!ActiveGhosts(i).BaseActor)
		{
			Index = i;
			break;
		}
	}
	if (Index == -1)
	{
		return -1;
	}

	FActiveGhostInfo GhostInfo;
	GhostInfo.GhostColor = GhostColor;
	GhostInfo.GhostLife = GhostLife;
	GhostInfo.BaseActor = Actor;
	GhostInfo.ParentAnimComponent = BaseMeshComponent->ParentAnimComponent;
	GhostInfo.BaseMeshComponent = BaseMeshComponent;
	GhostInfo.LifeRemaining = GhostLife;

	// Spawn
	AActor* BaseActor = GhostInfo.BaseActor;
	FVector Location = GhostInfo.BaseActor->Location;
	FRotator Rotation = GhostInfo.BaseActor->Rotation;

	ASkeletalMeshActorSpawnable* GhostActor = Cast<ASkeletalMeshActorSpawnable>(GWorld->SpawnActor(
		ASkeletalMeshActorSpawnable::StaticClass(), NAME_None, Location, Rotation, NULL, TRUE));
	if (GhostActor)
	{
		GhostActor->ClearComponents();
		GhostActor->SkeletalMeshComponent->AnimTreeTemplate = NULL;
		GhostActor->SkeletalMeshComponent->Animations = NULL;
		GhostActor->SkeletalMeshComponent->AnimTickArray.Empty();
		GhostActor->SkeletalMeshComponent->AnimAlwaysTickArray.Empty();
		GhostActor->SkeletalMeshComponent->AnimTickRelevancyArray.Empty();
		GhostActor->SkeletalMeshComponent->AnimTickWeightsArray.Empty();
		GhostActor->SkeletalMeshComponent->SkelControlTickArray.Empty();
		GhostActor->SkeletalMeshComponent->SkeletalMesh = GhostInfo.BaseMeshComponent->SkeletalMesh;
		GhostActor->SkeletalMeshComponent->ParentBoneMap = GhostInfo.BaseMeshComponent->ParentBoneMap;

		ASkeletalMeshActorSpawnable* ParentActor = Cast<ASkeletalMeshActorSpawnable>(GWorld->SpawnActor(
			ASkeletalMeshActorSpawnable::StaticClass(), NAME_None, Location, Rotation, NULL, TRUE));
		USkeletalMeshComponent* ParentAnimComponent = ParentActor->SkeletalMeshComponent;
		ParentAnimComponent->AnimTreeTemplate = NULL;
		ParentAnimComponent->Animations = NULL;
		ParentAnimComponent->SkeletalMesh = GhostInfo.BaseMeshComponent->SkeletalMesh;
		for( INT j = 0; j < GhostInfo.BaseMeshComponent->Materials.Num(); ++j )
		{
			UMaterialInstance* pIns = CastChecked<UMaterialInstanceConstant>( StaticConstructObject(
				UMaterialInstanceConstant::StaticClass(), GetOuter() ) );
			if (pIns)
			{
				pIns->SetParent( GhostMaterialTemplate );
				GhostActor->SkeletalMeshComponent->Materials.Push(pIns);
			}
		}
		for (INT j = 0; j < GhostInfo.ParentAnimComponent->Attachments.Num(); ++j)
		{
			const FAttachment& Attachment = GhostInfo.ParentAnimComponent->Attachments(j);
			UStaticMeshComponent* Component = Cast<UStaticMeshComponent>(Attachment.Component);
			if (!Component)
			{
				continue;
			}

			UStaticMeshComponent* NewComponent = Cast<UStaticMeshComponent>(StaticConstructObject(
				UStaticMeshComponent::StaticClass(), GetTransientPackage(), NAME_None, RF_Transient));
			if (NewComponent)
			{
				NewComponent->SetStaticMesh(Component->StaticMesh);
				GhostActor->SkeletalMeshComponent->AttachComponent(NewComponent, Attachment.BoneName,
					Attachment.RelativeLocation, Attachment.RelativeRotation, Attachment.RelativeScale);

				for( INT k = 0; k < Max(1, Component->Materials.Num()); ++k )
				{
					UMaterialInstance* pIns = CastChecked<UMaterialInstanceConstant>( StaticConstructObject(
						UMaterialInstanceConstant::StaticClass(), GetOuter() ) );
					if (pIns)
					{
						pIns->SetParent( GhostMaterialTemplate );
						NewComponent->Materials.Push(pIns);
					}
				}
			}
		}
		ParentActor->SetHidden(TRUE);

		GhostActor->SkeletalMeshComponent->ParentAnimComponent = ParentAnimComponent;
		GhostActor->MarkComponentsAsDirty(FALSE);
		ParentActor->MarkComponentsAsDirty(FALSE);
		GhostActor->ConditionalUpdateComponents();
		ParentActor->ConditionalUpdateComponents();

		ParentAnimComponent->AnimTickArray = GhostInfo.ParentAnimComponent->AnimTickArray;
		ParentAnimComponent->AnimAlwaysTickArray = GhostInfo.ParentAnimComponent->AnimAlwaysTickArray;
		ParentAnimComponent->AnimTickRelevancyArray = GhostInfo.ParentAnimComponent->AnimTickRelevancyArray;
		ParentAnimComponent->AnimTickWeightsArray = GhostInfo.ParentAnimComponent->AnimTickWeightsArray;
		ParentAnimComponent->SkelControlTickArray = GhostInfo.ParentAnimComponent->SkelControlTickArray;
		ParentAnimComponent->SpaceBases = GhostInfo.ParentAnimComponent->SpaceBases;
		ParentAnimComponent->LocalAtoms = GhostInfo.ParentAnimComponent->LocalAtoms;
		ParentAnimComponent->CachedLocalAtoms = GhostInfo.ParentAnimComponent->CachedLocalAtoms;
		ParentAnimComponent->CachedSpaceBases = GhostInfo.ParentAnimComponent->CachedSpaceBases;
		ParentAnimComponent->RequiredBones = GhostInfo.ParentAnimComponent->RequiredBones;
		ParentAnimComponent->ComposeOrderedRequiredBones = GhostInfo.ParentAnimComponent->ComposeOrderedRequiredBones;
		ParentAnimComponent->BoneVisibilityStates = GhostInfo.ParentAnimComponent->BoneVisibilityStates;
		ParentAnimComponent->SkelControlIndex = GhostInfo.ParentAnimComponent->SkelControlIndex;

		ParentActor->SetLocation(GhostInfo.BaseActor->Location);
		ParentActor->SetRotation(GhostInfo.BaseActor->Rotation);
		ParentActor->SetDrawScale(GhostInfo.BaseActor->DrawScale);
		GhostActor->SetTickIsDisabled(TRUE);
		ParentActor->SetTickIsDisabled(TRUE);
		GhostInfo.ParentActor = ParentActor;
		GhostInfo.GhostActor = GhostActor;
	}

	ActiveGhosts(Index) = GhostInfo;
	return Index;
}

void AGhostManager::RemoveGhostObject(INT Id)
{
	if (Id < 0 || Id >= MaxActiveGhosts)
	{
		return;
	}

	ActiveGhosts(Id).BaseActor = NULL;
	ActiveGhosts(Id).ParentAnimComponent = NULL;
	ActiveGhosts(Id).BaseMeshComponent = NULL;
	ActiveGhosts(Id).ParentActor = NULL;
	ActiveGhosts(Id).GhostActor = NULL;
}

void AGhostManager::ClearGhostObjects()
{
	for (INT i = 0; i < ActiveGhosts.Num(); ++i)
	{
		ActiveGhosts(i).BaseActor = NULL;
		ActiveGhosts(i).ParentAnimComponent = NULL;
		ActiveGhosts(i).BaseMeshComponent = NULL;
		ActiveGhosts(i).ParentActor = NULL;
		ActiveGhosts(i).GhostActor = NULL;
	}
}

void AGhostManager::PostBeginPlay()
{
	ActiveGhosts.SetNum(MaxActiveGhosts);
	for (INT i = 0; i < MaxActiveGhosts; ++i)
	{
		ActiveGhosts(i).BaseActor = NULL;
		ActiveGhosts(i).ParentAnimComponent = NULL;
		ActiveGhosts(i).BaseMeshComponent = NULL;
		ActiveGhosts(i).ParentActor = NULL;
		ActiveGhosts(i).GhostActor = NULL;
	}
}

void AGhostManager::TickSpecial(FLOAT DeltaTime)
{
	for (INT i = 0; i < ActiveGhosts.Num(); ++i)
	{
		FActiveGhostInfo& GhostInfo = ActiveGhosts(i);
		if (!GhostInfo.BaseActor || GhostInfo.LifeRemaining <= 0.0f)
		{
			continue;
		}

		GhostInfo.LifeRemaining -= DeltaTime;
		if (GhostInfo.LifeRemaining < 0.0f)
		{
			GhostInfo.BaseActor = NULL;
			GhostInfo.ParentAnimComponent = NULL;
			GhostInfo.BaseMeshComponent = NULL;
			GhostInfo.ParentActor = NULL;
			GhostInfo.GhostActor = NULL;
		}
		else
		{
			FLOAT Intensity = GhostInfo.LifeRemaining / GhostInfo.GhostLife;
			for( INT j = 0; j < GhostInfo.GhostActor->SkeletalMeshComponent->Materials.Num(); ++j )
			{
				UMaterialInstance* pIns = Cast<UMaterialInstance>(GhostInfo.GhostActor->SkeletalMeshComponent->Materials(j));
				if (pIns)
				{
					pIns->SetScalarParameterValue( "Intensity", Intensity );
				}
			}
			for (INT j = 0; j < GhostInfo.GhostActor->SkeletalMeshComponent->Attachments.Num(); ++j)
			{
				const FAttachment& Attachment = GhostInfo.GhostActor->SkeletalMeshComponent->Attachments(j);
				UStaticMeshComponent* Component = Cast<UStaticMeshComponent>(Attachment.Component);
				if (!Component)
				{
					continue;
				}

				for( INT k = 0; k < Max(1, Component->Materials.Num()); ++k )
				{
					UMaterialInstance* pIns = Cast<UMaterialInstance>(Component->Materials(k));
					if (pIns)
					{
						pIns->SetScalarParameterValue( "OpacityMultiply", Intensity );
					}
				}
			}
		}
	}
}