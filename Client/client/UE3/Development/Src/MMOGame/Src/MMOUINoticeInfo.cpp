#include "stdafx.h"
#include "MMOGameUIClasses.h"
#include "MMOFacade.h"
#include "CommonGameEvents.h"

IMPLEMENT_CLASS(UMMOUINoticeInfo)
//IMPLEMENT_CLASS(UMMOGFXPlayer_NoticeInfo)

//void UMMOGFXPlayer_NoticeInfo::PostAdvance(float DeltaTime )
//{
//
//}

void UMMOUINoticeInfo::Init()
{
	//eventCallAddNoticeInfo( string notice , int movieTime , int repeatTimes , int noticeColor )
	Super::Init();
	TArray<EGameEvent> evts;
	evts.AddItem(GameEvent_MarqueeNoticeInfo);
	evts.AddItem(GameEvent_RollingNoticeInfo);
	EventAdapter = new TGameEventAdapter<UMMOUINoticeInfo>(this, evts);

}

void UMMOUINoticeInfo::UnInit()
{
	Super::UnInit();
}

void UMMOUINoticeInfo::OnNativeGameEvent(struct MMOGameEvent* evt)
{
	switch( evt->GetEventType() )
	{
	case GameEvent_MarqueeNoticeInfo:
		{
			MMOGameEvent_MarqueeNoticeInfo* marqueeEvt = (MMOGameEvent_MarqueeNoticeInfo*)evt;
			if( marqueeEvt )
			{
				eventCallAddMarqueeNoticeInfo( marqueeEvt->NoticeText , marqueeEvt->ShowSpeed , marqueeEvt->RepeatTimes , marqueeEvt->TextColor );
			}
		}
		break;
	case GameEvent_RollingNoticeInfo:
		{
			MMOGameEvent_RollingNoticeInfo* rollingEvt = (MMOGameEvent_RollingNoticeInfo*)evt;
			if( rollingEvt )
			{
				eventCallAddRollingNoticeInfo( rollingEvt->NoticeText , rollingEvt->TextColor );
			}
		}
		break;

	}
}

UBOOL UMMOUINoticeInfo::SkipCaptureInputKey(const FString& key,BYTE eIE,const FString& strHoverControllerName,FVector2D ClickPosInMovieSpace)
{
	if( IsVisible )
	{

		if(	strHoverControllerName==TEXT("MarqueeNotice")||
			strHoverControllerName==TEXT("marquee_bg") ||
			strHoverControllerName==TEXT("textField_Notice") ||
			strHoverControllerName==TEXT("RollingNotice1") ||
			strHoverControllerName==TEXT("RollingNotice0") )
		{
			return TRUE;
		}
	}
	return Super::SkipCaptureInputKey(key, eIE, strHoverControllerName, ClickPosInMovieSpace );
}