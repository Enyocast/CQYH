/*
native functions of the MMOPlayerCamera class

*/
//#pragma once
#include "stdafx.h"
//#include "MMOGameClasses.h"
#include "DebugMMO.h"

//生成相关的Class信息
IMPLEMENT_CLASS(AMMOPlayerCamera)

//Pow函数，a为基数，b为指数
FLOAT  AMMOPlayerCamera::Pow(FLOAT A,FLOAT B)
{
	return appPow(A,B);
}

void AMMOPlayerCamera::UpdateDebug()
{
	return;
}

UBOOL AMMOPlayerCamera::HasHidden(class AActor* actor)
{
	for (INT i = 0; i < HiddenActorList.Num(); ++i)
	{
		if(HiddenActorList(i).HideActor == actor)
		{
			return TRUE;
		}
	}

	return FALSE;
}

UBOOL AMMOPlayerCamera::IsUnHiding(class AActor* actor, INT& idx)
{
	for (INT i = 0; i < UnHiddenActorList.Num(); ++i)
	{
		if(UnHiddenActorList(i).HideActor == actor)
		{
			idx = i;
			return TRUE;
		}
	}

	return FALSE;
}

void AMMOPlayerCamera::NativeTick(FLOAT deltaTime)
{
	if(MMO::GetCurrentGameState() != EGameState_InGame)
	{
		return;
	}

	CTRL_TICK("MMOPlayerCamera::NativeTick");

	for(INT i = 0; i < HiddenActorList.Num(); ++i)
	{
		HiddenActorList(i).MaterialCtrl->NativeTick(deltaTime);
	}

	for(INT i = 0; i < UnHiddenActorList.Num(); ++i)
	{
		UnHiddenActorList(i).MaterialCtrl->NativeTick(deltaTime);
	}


	CheckHiddenActorTime -= deltaTime;
	if(CheckHiddenActorTime <= 0.f)
	{
		CheckHiddenActorTime = 0.2f;
		CheckStaticMeshToHide(deltaTime);
	}

	if(g_tickOrder == ETO_AfterCameraTick)
	{
		_OnMMOTick(GDeltaTime);
		logTickOrderf(TEXT("ETO_AfterCameraTick"));
	}
}

void AMMOPlayerCamera::BeforeUpdateTick(FLOAT deltaTime)
{
	if(g_tickOrder == ETO_BeforeCameraUpdate)
	{
		_OnMMOTick(GDeltaTime);
		logTickOrderf(TEXT("ETO_BeforeCameraUpdate"));
	}
}

void AMMOPlayerCamera::AfterUpdateTick(FLOAT deltaTime)
{
	if(g_tickOrder == ETO_AfterCameraUpdate)
	{
		_OnMMOTick(GDeltaTime);
		logTickOrderf(TEXT("ETO_AfterCameraUpdate"));
	}
}



static INT CheckCount = 0;

void AMMOPlayerCamera::UnHiddenAll()
{
	for (INT i = 0; i < HiddenActorList.Num(); ++i)
	{
		HiddenActorList(i).MaterialCtrl->PlayOpacityFadeIn(BlockObjectFadeInOutSpeed);
	}
}

UBOOL AMMOPlayerCamera::IsInMatinee()
{
	do 
	{
		if(!PCOwner)
		{
			break;
		}

		if(!PCOwner->Pawn)
		{
			break;
		}

		AMMOPlayer* pp = Cast<AMMOPlayer>(PCOwner->Pawn);
		if (pp && pp->IsInMatinee)
		{
			return TRUE;
		}
	} while (FALSE);

	return FALSE;
}

void AMMOPlayerCamera::CreateMaterial( UMeshComponent* MeshComp )
{
	UMaterial* mat = NULL;
	for( int i = 0; i < MeshComp->GetNumElements(); ++i )
	{
		UMaterialInstance* pInterface = Cast<UMaterialInstance>(MeshComp->GetMaterial(i));
		FString name, tempname;
		if( pInterface )
		{
			UObject *obj = pInterface->GetMaterial()->GetOuter();
			obj->GetName( name );
			while( obj->GetOuter() )
			{
				obj = obj->GetOuter();
				obj->GetName( tempname );
				name = tempname +"." + name;
			}
			pInterface->GetMaterial()->GetName(tempname);
			//pInterface->GetName( tempname );
			tempname += "_FadeInOut";

			name = name + "." + tempname ;

			for( int i = 0; i < MeshTranslucencyMaterials.Num() ; ++i )
			{
				FString temp;
				UMaterial *&ref = MeshTranslucencyMaterials.GetTypedData()[i];
				ref->GetName( temp );
				if ( temp == tempname )
					return;
			}

			mat = Cast<UMaterial>(UObject::StaticLoadObject( UMaterial::StaticClass(), NULL, *name, NULL, LOAD_NoWarn, NULL ));
			if ( mat )
			{
				INT index = MeshTranslucencyMaterials.Add(1);
				MeshTranslucencyMaterials.GetTypedData()[index] = mat;
			}
		}
	}
}
void AMMOPlayerCamera::CheckStaticMeshToHide(FLOAT deltaTime)
{
	if(!PCOwner)
	{
		return;
	}

	if(!PCOwner->Pawn)
	{
		return;
	}

	AMMOPlayer* pp = Cast<AMMOPlayer>(PCOwner->Pawn);
	if (pp && pp->IsInMatinee)
	{
		return;
	}

	++CheckCount;

	DWORD TraceFlags = TRACE_AllColliding | TRACE_ComplexCollision | TRACE_Visible;
	FMemMark Mark(GMainThreadMemStack);
	UClass* BaseClass = AActor::StaticClass();
	FVector vs = LastFrameCameraCache.POV.Location;
	FVector ve = PCOwner->Pawn->Location;
	FVector dir = (ve - vs);
	dir.Normalize();

	ve -= dir * TraceExtend.Size2D() * 0.75; // 往相机前多一点点
	//ve.Z -= TraceExtend.Z * 0.5; // 往下下多一点点

	//GWorld->bShowExtentLineChecks = TRUE;
	FCheckResult* Hit = GWorld->MultiLineCheck( GMainThreadMemStack, ve, vs, TraceExtend, TraceFlags, this );
	//GWorld->bShowExtentLineChecks = FALSE;

	//DrawDebugLine(vs, ve, 255,0,255, true);
	//DrawDebugBox(vs, FVector(256, 256, 256), 0, 0, 255, true);
	//DrawDebugBox(ve, FVector(256, 256, 256), 0, 255, 0, true);


	TArray<AActor*> TracedActors;
	//ClearHiddenList();


	while (Hit != NULL)
	{
		if ( Hit->Actor && 
			!Hit->Actor->bDeleteMe &&
			Hit->Actor->IsA(BaseClass))
		{
			TracedActors.AddItem(Hit->Actor);
			/*OutActor    = Hit->Actor;
			HitLocation = Hit->Location;
			HitNormal   = Hit->Normal;
			if(pHitInfo)
			{
				HitInfo.PhysMaterial = DetermineCorrectPhysicalMaterial(*Hit);

				HitInfo.Material = Hit->Material ? Hit->Material->GetMaterial() : NULL;

				HitInfo.Item = Hit->Item;
				HitInfo.LevelIndex = Hit->LevelIndex;
				HitInfo.BoneName = Hit->BoneName;
				HitInfo.HitComponent = Hit->Component;
			}*/
			Hit = Hit->GetNext();
		}
		else
		{
			Hit = Hit->GetNext();
			continue;
		}
	}

	Mark.Pop();

	TArray<FAutoHideBlockActor> newHide;

	//warnf(NAME_Error, TEXT("[MMOPlayerCamera] =============:%d"), CheckCount);

	//foreach TraceActors(class'StaticMeshActor', traced, loc, nor, ve, vs, vect(256,256,256), HitInfo, TRACEFLAG_Bullet) // 
	for(INT k = 0; k < TracedActors.Num(); ++k)
	{

		AStaticMeshActor* traced = Cast<AStaticMeshActor>(TracedActors(k));

		if(traced && traced->bCanHidden)
		{
			// 如果还没有在隐藏中
			if(!HasHidden(traced))
			{
				//warnf(NAME_Error, TEXT("[MMOPlayerCamera] 如果还没有在隐藏中:%s"), *traced->GetName());

				bool newToHide = true;

				// if new traced is in unhidden list, revert the fading for it
				INT idx = INDEX_NONE;
				if(IsUnHiding(traced, idx))
				{
					// 如果在反隐藏列表
					UnHiddenActorList(idx).MaterialCtrl->PlayOpacityFadeOut(BlockObjectFadeInOutSpeed);
					//UnHiddenActorList(idx).HideActor->SetCollisionType(COLLIDE_BlockAllButWeapons);
					//UnHiddenActorList(idx).HideActor->SetCollision(FALSE, FALSE, TRUE);
					newHide.AddItem(UnHiddenActorList(idx));
					UnHiddenActorList.Remove(idx, 1);
					//warnf(NAME_Error, TEXT("[MMOPlayerCamera]\t如果在反隐藏列表 CheckStaticMeshToHide() from UnHidden:%s"), *traced->GetName());
					newToHide = false;
				}

				//for(INT i = 0; i < UnHiddenActorList.Num(); ++i)
				//{
				//	if(UnHiddenActorList(i).HideActor == traced)
				//	{
				//		UnHiddenActorList(i).MaterialCtrl->PlayOpacityFadeOut(BlockObjectFadeInOutSpeed);
				//		UnHiddenActorList(i).HideActor->SetCollision(false, false, true);
				//		newHide.AddItem(UnHiddenActorList(i));
				//		UnHiddenActorList.Remove(i, 1);
				//		warnf(NAME_Error, TEXT("[MMOPlayerCamera]CheckStaticMeshToHide() from UnHidden:%s"), *traced->GetName());
				//		newToHide = false;
				//		break;
				//	}
				//}

				// find new actor to hide
				if(newToHide)
				{
					CreateMaterial( traced->StaticMeshComponent );
					// 如果是新加入的隐藏对象
					//traced->SetCollisionType(COLLIDE_BlockAllButWeapons);
					//traced->SetCollision(FALSE, FALSE, TRUE);
					FAutoHideBlockActor hidenActor;
					hidenActor.HideActor = traced;
					hidenActor.MaterialCtrl = Cast<UMMOActorMaterialController>(
						StaticConstructObject(UMMOActorMaterialController::StaticClass(), this));

					hidenActor.MaterialCtrl->eventSetMaterials( MeshTranslucencyMaterials );
					hidenActor.MaterialCtrl->eventInit(traced->StaticMeshComponent, TRUE);
					hidenActor.MaterialCtrl->PlayOpacityFadeOut(BlockObjectFadeInOutSpeed);				

					newHide.AddItem(hidenActor);
					HiddenActorList.AddItem((hidenActor));
					//warnf(NAME_Error, TEXT("[MMOPlayerCamera]\t如果是新加入的隐藏对象 CheckStaticMeshToHide() New add:%s"), *traced->GetName());
				}
			}
			else
			{
				//warnf(NAME_Error, TEXT("[MMOPlayerCamera] 如果不在隐藏列表中:%s"), *traced->GetName());
				for(INT i = 0; i < HiddenActorList.Num(); ++i)
				{
					// 如果在隐藏列表中
					if(HiddenActorList(i).HideActor == traced)
					{
						//warnf(NAME_Error, TEXT("[MMOPlayerCamera]\t如果在隐藏列表中 CheckStaticMeshToHide() New add:%s"), *traced->GetName());
						newHide.AddItem(HiddenActorList(i));
						break;
					}
				}
			}
		}
		else if(traced && traced->bCanHidden)
		{
			//warnf(NAME_Error, TEXT("[MMOPlayerCamera] 找到不可隐藏的对象 CheckStaticMeshToHide() HasHidden:%s"), *traced->GetName());
		}
	}

	// clear not traced actors
	for(INT j = 0; j < HiddenActorList.Num(); ++j)
	{
		INT idx = INDEX_NONE;
		for(INT i = 0; i < newHide.Num(); ++i)
		{

			if(newHide(i).HideActor == HiddenActorList(j).HideActor)
			{
				idx = j;
				//warnf(NAME_Error, TEXT("[MMOPlayerCamera] 新检测到的已经在隐藏列表中:%s"), *newHide(i).HideActor->GetName());
				break;
			}
		}

		// the actor is not traced now
		if(INDEX_NONE == idx)
		{
 			//warnf(NAME_Error, TEXT("[MMOPlayerCamera]  取消隐藏没阻挡相机的 CheckStaticMeshToHide() add to unhidden:%s"),
// 				*HiddenActorList(j).HideActor->GetName());

			UnHiddenActorList.AddItem(HiddenActorList(j));
			HiddenActorList(j).MaterialCtrl->PlayOpacityFadeIn(BlockObjectFadeInOutSpeed);
		}
	}

	//if(newHide.Num() >  0)
	// replace to new hide list
	HiddenActorList = newHide;

	// check the completed fade in actors and remove from the list
	INT i = 0;
	while(i < UnHiddenActorList.Num())
	{
		if(!UnHiddenActorList(i).MaterialCtrl->IsFading)
		{
 			//warnf(NAME_Error, TEXT("[MMOPlayerCamera] 移除淡出完成的 CheckStaticMeshToHide() unhidden completed:%s"), 
 			//	*UnHiddenActorList(i).HideActor->GetName());

			//UnHiddenActorList(i).HideActor->SetCollisionType(COLLIDE_TouchAllButWeapons);
			//UnHiddenActorList(i).HideActor->SetCollision(TRUE, TRUE, TRUE);
			UnHiddenActorList.Remove(i, 1);
			i = 0;
		}
		else
		{
			++i;
		}
	}
}

void AMMOPlayerCamera::ZoomIn()
{
	//if(!PreventCameraSpin)
	DistanceRatio = Max(DistanceRatio - 0.05f, 0.0f);
	PitchDirty = TRUE;
	g_updateMainPlayerHudName = true;
}

void AMMOPlayerCamera::ZoomOut()
{
	//if(!PreventCameraSpin)
	DistanceRatio = Min(DistanceRatio + 0.05f, 1.0f);
	PitchDirty = TRUE;
	g_updateMainPlayerHudName = true;
}

void AMMOPlayerCamera::EnableUpdatePlayerHUD(UBOOL on)
{
	g_updateMainPlayerHudName = (on == TRUE);
}

FLOAT AMMOPlayerCamera::GetCurrentDistance()
{
 	return TargetDistancePullPercent * (FarCameraDistance - NearCameraDistance) + NearCameraDistance;
}