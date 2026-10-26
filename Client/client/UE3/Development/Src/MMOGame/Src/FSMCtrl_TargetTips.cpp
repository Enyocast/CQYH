

#include "StdAfx.h"
#include "FSMState.h"
#include "FSMCtrl_TargetTips.h"
#include "MMOGameClasses.h"
#include "MMOGameUIClasses.h"
#include "MMOFacade.h"
#include "AbilityProcessor.h"
#include "MMONavigationManager.h"
#include "ScaleformEngine.h"
#include "UITextParser.h"

using namespace FSM;
extern bool g_disableAllInput;

//FSM控制类注册-------------------------------------------------------------------------------------------------------------------------------------------------
ADD_FSM_CTRL(FSMCtrl_TargetInfoHUD)
	ADD_FSM_CTRL(FSMCtrl_TeleportTips)
	ADD_FSM_CTRL(FSMCtrl_DoodadTips)


	//目标的头像条--------------------------------------------------------------------------------------------------------------------------------------------------
	UBOOL FSMCtrl_TargetInfoHUD::Update(FLOAT DelTime)
{
	if (MMO::GetCurrentGameState() != EGameState_InGame)
	{
		return FALSE;
	}
	if (g_disableAllInput)
	{
		return FALSE;
	}
	//当前目标
	if(FSM::Target.CurTargetMMOActor!= FSM::Target.LastTargetActor)
	{
		return TRUE;
	}
	return FALSE;
}
void FSMCtrl_TargetInfoHUD::Action()
{
	//触碰目标
	if(	FSM::Target.LastTargetMMOActor!=FSM::Target.CurTargetMMOActor )
	{
		MMOGameEvent_TargetEvent evt(MMOGameEvent_TargetEvent::ETCT_CurrentTarget, FSM::Target.CurTargetMMOActor, FSM::Target.SelectMMOActor);
		MMOUI::PostGameEvent(&evt);
	}
}


//Teleport tips--------------------------------------------------------------------------------------------------------------------------------------------------
FSMCtrl_TeleportTips::FSMCtrl_TeleportTips(void)
{
	IsShowTips = FALSE;
}
UBOOL FSMCtrl_TeleportTips::Update(FLOAT DelTime)
{
	if (MMO::GetCurrentGameState() != EGameState_InGame)
	{
		return FALSE;
	}
	//当前目标
	if(FSM::Target.CurTargetActor!= FSM::Target.LastTargetActor)
	{
		return TRUE;
	}
	return FALSE;
}
void FSMCtrl_TeleportTips::Action()
{
	ATeleportOrig* pTeleportOrig		=   Cast<ATeleportOrig>(FSM::Target.CurTargetActor);
	if (pTeleportOrig && MMOUI::GetUIManager()->delegateIsTipsShow()==FALSE)
	{
		FVector posOffset( 0, 0, 0 );
		if( pTeleportOrig->TeleportStaticEffect ){
			posOffset = pTeleportOrig->TeleportStaticEffect->LocalToWorld.TransformFVector( pTeleportOrig->TeleportStaticEffect->Translation + pTeleportOrig->TipsPosOffset );
		}
		else{
			posOffset = pTeleportOrig->Location + pTeleportOrig->TipsPosOffset; 
		}
		FVector tipsPos = posOffset;
		//MMOUI::GetUIManager()->delegateShowFreeStyleTips( MMOUI::ParseLocalizedPropertyPath(TEXT("MMOGame.TeleportOrig.Name") ), pTeleportOrig->ToSceneName );
		MMOUI::GetUIManager()->delegateShowFreeStyleTips( TEXT(""), pTeleportOrig->ToSceneName, CM_TIPS_Style2, 1 );
		MMOUI::GetUIManager()->delegateAnchorTips( tipsPos, TRUE );
		//显示特效
		pTeleportOrig->ActiveFoucsEffect( TRUE );
		IsShowTips = TRUE;
	}
	else if(IsShowTips)
	{
		MMOUI::GetUIManager()->delegateHideTips();
		IsShowTips = FALSE;

		//处理跳转点特效关闭
		ATeleportOrig *lastTeleportOrig	= Cast<ATeleportOrig>(FSM::Target.LastTargetActor);
		if( lastTeleportOrig )
		{
			lastTeleportOrig->ActiveFoucsEffect( FALSE );
		}
	}
}


//Doodad tips--------------------------------------------------------------------------------------------------------------------------------------------------
FSMCtrl_DoodadTips::FSMCtrl_DoodadTips(void)
{
	IsShowTips = FALSE;
}
UBOOL FSMCtrl_DoodadTips::Update(FLOAT DelTime)
{
	if (MMO::GetCurrentGameState() != EGameState_InGame)
	{
		return FALSE;
	}

	if(FSM::Target.CurTargetActor!= FSM::Target.LastTargetActor)
	{
		return TRUE;
	}
	return FALSE;
}
void FSMCtrl_DoodadTips::Action()
{
	AMMODoodadActor* pDoodadActor	=	Cast<AMMODoodadActor>(FSM::Target.CurTargetActor);
	if(pDoodadActor)
	{
		const UDoodad* doodadTemp = pDoodadActor->DoodadTemplate;
		if(doodadTemp && doodadTemp->DoododNameDisplay)
		{
			//FString doodadTips;
			//// 提示道具需求
			//if(doodadTemp->RequireItemID > 0)
			//{
			//	FString locReqItem;
			//	if(doodadTemp->CostItem)
			//	{
			//		locReqItem = MMOUI::ParseLocalizedPropertyPath(TEXT("Doodad.RequireItem"));
			//	}
			//	else
			//	{
			//		locReqItem = MMOUI::ParseLocalizedPropertyPath(TEXT("Doodad.CostItem"));
			//	}

			//	locReqItem = locReqItem.TrimQuotes();
			//	doodadTips += locReqItem + TEXT("<br>");

			//	UItem* item = MMOFacade::getSingleton().FindItemTemplate(doodadTemp->RequireItemID);
			//	if(item)
			//	{
			//		doodadTips += UITextParser::HTMLFormatItemColorString(item);
			//	}
			//	else
			//	{
			//		doodadTips += FString::Printf(TEXT("Item:%d"), doodadTemp->RequireItemID);
			//	}
			//}
			//// 有开启限制，不管能否开启，也就是VarValue不管是否正确时，都要显示到TIPS
			//if(pDoodadActor->IsVarRequired() && !doodadTemp->TipsText.IsEmpty())
			//{
			//	doodadTips += MMOUI::ParseLocalizedPropertyPath(TEXT("Doodad.RequireVar"));
			//	doodadTips += TEXT("<br>");
			//	doodadTips += doodadTemp->TipsText;
			//}

			//MMOUI::GetUIManager()->delegateShowFreeStyleTips( MMOUI::TrimNumber(doodadTemp->DoodadName.ToString()), doodadTips );
			MMOUI::GetUIManager()->delegateShowFreeStyleTips( TEXT(""), MMOUI::TrimNumber(doodadTemp->DoodadName.ToString()), CM_TIPS_Style3, 1 );

			FVector posOffset = doodadTemp->TipsPosOffset;
			if( pDoodadActor->CylinderComponent ){
				posOffset.Z += pDoodadActor->CylinderComponent->CollisionHeight;
			}
			FVector tipsPos = pDoodadActor->Location + posOffset;
			MMOUI::GetUIManager()->delegateAnchorTips( tipsPos, TRUE );

			IsShowTips = TRUE;
		}
	}
	else if(IsShowTips)
	{
		MMOUI::GetUIManager()->delegateHideTips();
		IsShowTips = FALSE;
	}
}