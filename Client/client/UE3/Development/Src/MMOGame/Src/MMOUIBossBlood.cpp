#include "stdafx.h"
#include "MMOGameUIClasses.h"
#include "MMOFacade.h"
#include "MMOBossBloodManager.h"
#include "MMOGameEvent.h"

IMPLEMENT_CLASS(UMMOUIBossBlood)

void UMMOUIBossBlood::Init()
{
	Super::Init();
	check(EventAdapter == NULL);
	TArray<EGameEvent> evts;
	evts.AddItem(GameEvent_DynamicBossBlood);
	EventAdapter = new TGameEventAdapter<UMMOUIBossBlood>(this, evts);
	if( GFXPlayer ){
		GFXPlayer->AddPostAdvanceDelegate( FScriptDelegate(this, TEXT("PostAdvance")) );
	}
}

void UMMOUIBossBlood::UnInit()
{
	Super::UnInit();
	if( GFXPlayer ){
		GFXPlayer->RemovePostAdvanceDelegate( FScriptDelegate(EC_EventParm) );
	}
}

void UMMOUIBossBlood::PostOnShow(UBOOL show)
{
	Super::PostOnShow(show);
	

	//if(MMOFacade::getSingleton().GetMainPlayer()->IsInMatinee)
	//{
	//	this->LastVisible = IsVisible;
	//	SetVisible(FALSE);
	//}
}
void UMMOUIBossBlood::NPCHpChange(class ANPC* npc,INT hp)
{
	if(npc == NULL)
		return;
	INT nBossID = MMOBossBloodManager::getSingleton().GetBossID();
	if(npc->ServerID == nBossID)
	{
		eventCallUpdateBlood(hp);
		if(hp <= 0)
			MMOBossBloodManager::getSingleton().SetBossID(0);
	}
}

void UMMOUIBossBlood::OnNativeGameEvent(struct MMOGameEvent* evt)
{
	if(evt == NULL)
		return;

	if(evt->GetEventType() == GameEvent_DynamicBossBlood)
	{
		
		MMOGameEvent_BossBlood* pkEvent =( MMOGameEvent_BossBlood*)evt;
		if(pkEvent->eventBoss == MMOGameEvent_BossBlood::EBossBlood_Event_Appear)
		{
			eventCallSetInitBlood(pkEvent->title,pkEvent->nCurHp,pkEvent->nMaxHp,pkEvent->nLevel,pkEvent->byteQuality);
			SetVisible(FALSE);
		}
		else if(pkEvent->eventBoss == MMOGameEvent_BossBlood::EBossBlood_Event_Destroy)
		{
			MMOBossBloodManager::getSingleton().SetBossID(0);
			eventCallUpdateBlood(0);
		}
	}
}
UBOOL UMMOUIBossBlood::SkipCaptureInputKey(const FString& key,BYTE eIE,const FString& strHoverControllerName,FVector2D ClickPosInMovieSpace)
{
	if( IsVisible )
	{
		if(strHoverControllerName==TEXT("_BossBlood"))
		{
			return TRUE;
		}
	}
	return Super::SkipCaptureInputKey(key, eIE, strHoverControllerName, ClickPosInMovieSpace);
}

void UMMOUIBossBlood::TickForDistance(float deltaTime)
{

	INT nBossID = MMOBossBloodManager::getSingleton().GetBossID();
	if(nBossID > 0)
	{
		if(MMOFacade::getSingleton().GetMainPlayer()->IsInMatinee)
		{
			if (IsVisible)
			{
				this->LastVisible = IsVisible;
				SetVisible(FALSE);
			}
			return;
		}

		AMMOActor* actor = MMOFacade::getSingleton().GetCharacter(nBossID);
		if(actor)
		{
			INT CurDistance = (actor->Location-MMOFacade::getSingleton().GetMainController()->Pawn->Location).Size2D();
			if(!IsVisible&&(CurDistance < 2500))
				SetVisible(TRUE);
			else if (IsVisible&&(CurDistance >= 2600))
				SetVisible(FALSE);
			return;
		}
	}

	if (IsVisible)
	{
		SetVisible(FALSE);
	}
}

void UMMOUIBossBlood::PostAdvance(float DeltaTime)
{
	//if( !IsVisible ){
	//	return;
	//}

	if (MMO::GetCurrentGameState() == EGameState_InGame)
	{
		TickForDistance(DeltaTime);
	}
}