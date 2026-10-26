#include "stdafx.h"
#include "MMOGameClasses.h"
//
//IMPLEMENT_CLASS(USkeletalMeshComponentEx)
//
//
//void  USkeletalMeshComponentEx::RefreshAnim(class AMMOActor* actor)
//{
//	//if(actor==NULL)return;
//
//	//if(actor->bDead)
//	//{
//	//	SetIdleAnim(PawnAnimInfo.DeadAnim);
//	//	SetMoveAnim(PawnAnimInfo.DeadAnim);
//	//}
//	//else
//	//{
//	//	SetIdleAnim(PawnAnimInfo.IdleAnim);
//	//	SetMoveAnim(PawnAnimInfo.RunAnim);
//	//}
//
//	//if(ActionLoopBlend != NULL)
//	//{
//	//	ActionLoopBlend->SetBlendTarget(0.f, 0.f);
//	//}
//
//	//if (!bHaveIdleAnim && ActionLoopBlend)
//	//{
//	//	ActionLoopBlend->SetBlendTarget(1.0f, 0.f);
//	//}
//
//}
//
//void USkeletalMeshComponentEx::SetIdleAnim(FName NewIdleLoopAnim)
//{
//	if(!NewIdleLoopAnim.IsValid())
//	{
//		warnf(TEXT("Set a null anim to IdleLoopAnim"));
//		return;
//	}
//
//	if(IdleLoopBlend == NULL)
//	{
//		return;
//	}
//
//	if(IdleLoopBlend->ActiveChildIdx == 0)
//	{
//		if(IdleLoop1->AnimSeqName != NewIdleLoopAnim)
//		{
//			IdleLoop2->SetAnim(NewIdleLoopAnim);
//		}
//	}
//	else if(IdleLoopBlend->ActiveChildIdx == 1)
//	{
//		if(IdleLoop2->AnimSeqName != NewIdleLoopAnim)
//		{
//			IdleLoop2->SetAnim(NewIdleLoopAnim);
//		}
//	}
//	else
//	{
//		//`warn(self$"IdleLoopBlend->ActiveChildIdx == -1");
//		IdleLoop1->SetAnim(NewIdleLoopAnim);
//	}
//
//	IdleLoopBlend->PlayAnimation(NewIdleLoopAnim,0, 1.0, 0.1, 0.1, TRUE, RBA_Default, RBA_Default, RBA_Default, TRUE);
//}
//
//
//void USkeletalMeshComponentEx::SetMoveAnim(FName NewMoveLoopAnim)
//{
//	if(!NewMoveLoopAnim.IsValid())
//	{
//		warnf(TEXT("Set a null anim to IdleLoopAnim"));
//		return;
//	}
//
//	if(MoveLoopBlend == NULL)
//	{
//		return;
//	}
//
//	if(MoveLoopBlend->ActiveChildIdx == 0)
//	{
//		if(MoveLoop2->AnimSeqName != NewMoveLoopAnim)
//		{
//			MoveLoop2->SetAnim(NewMoveLoopAnim);
//		}
//	}
//	else if(MoveLoopBlend->ActiveChildIdx == 1)
//	{
//		if(MoveLoop1->AnimSeqName != NewMoveLoopAnim)
//		{
//			MoveLoop1->SetAnim(NewMoveLoopAnim);
//		}
//	}
//	else
//	{
//		//`warn(self$"MoveLoopBlend->ActiveChildIdx == -1");
//		MoveLoop1->SetAnim(NewMoveLoopAnim);
//	}
//
//	MoveLoopBlend->PlayAnimation(NewMoveLoopAnim,0, 1.0, 0.1, 0.1, TRUE, RBA_Default, RBA_Default, RBA_Default,TRUE);
//
//}
