/*
native functions of the MoveController class

*/

//#pragma once
#include "stdafx.h"
#include "MMOFacade.h"
#include "net/message_handler.h"
#include "scene_def.h"

IMPLEMENT_CLASS(AMoveController);
IMPLEMENT_CLASS(AMoveController_Chess);

void AMoveController::OnLeftMouseKey(AActor* srcActor,UBOOL bRelease,FVector StartTrace,FVector EndTrace)
{
	//ANPC* tNpc = Cast<ANPC>(Pawn);
	//AMMOPlayer* tPlyer = Cast<AMMOPlayer>(srcActor);
	//if(tNpc && tNpc->m_bIsMonster  )
	//{
	//	MMOFacade::getSingleton().GetAbilityProcessor()->AddNewBuff( tPlyer->ServerID, tNpc->ServerID, 123456, 1009, 1, 5000, 0);
	//}
}

void AMoveController_Chess::OnLeftMouseKey(AActor* srcActor,UBOOL bRelease,FVector StartTrace,FVector EndTrace)
{

	//FCheckResult* HitR = MMO::PickPoint(StartTrace, EndTrace, srcActor);
	//if(HitR)
	//{
	//	if(Pawn !=	HitR->Actor)
	//	{
	//		warnf(NAME_Warning, TEXT("_________ OnLeftMouseKey:1"));
	//		return;
	//	}
	//	else
	//	{
	//		warnf(NAME_Warning, TEXT("_________ OnLeftMouseKey:2"));
	//		return;
	//	}

	//}

}
