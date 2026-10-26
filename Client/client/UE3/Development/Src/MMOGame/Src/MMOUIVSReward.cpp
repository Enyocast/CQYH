#include "stdafx.h"
#include "MMOGameUIClasses.h"
#include "net/message_handler.h"
#include "MMOGameEvent.h"
#include "MMOFacade.h"
#include "UITextParser.h"
#include "MMOArenaManager.h"

IMPLEMENT_CLASS(UMMOUIVSReward)

//========================================================================================================================================
void UMMOUIVSReward::PreOnShow( UBOOL show )
{
	Super::PreOnShow( show );

	if( show ){
		UpdatePanel();
	}
	else{
		//ResetUI();
	}
}
//========================================================================================================================================
void UMMOUIVSReward::OnNativeGameEvent( struct MMOGameEvent* evt )
{
	if( evt == NULL ){
		return;
	}

	//switch( evt->GetEventType() )
	//{
	////case GameEvent_VSOneOnOneGetRewardResult:
	////	{

	////	}
	////	break;
	//}
}
//========================================================================================================================================
void UMMOUIVSReward::UpdatePanel()
{
	UpdateRewardInfo();
}
//========================================================================================================================================
void UMMOUIVSReward::UpdateRewardInfo()
{
	INT64 nTotalRwd = MMOArenaManager::getSingleton().GetVSOneOnOneTotalRwd();
	FString totalRwd;
	totalRwd = UITextParser::HTMLMoneyIconString( MONEYTYPE_02, nTotalRwd );

	INT64 nAvgRwd = MMOArenaManager::getSingleton().GetVSOneOnOneAvgRwd();
	FString avgRwd;
	avgRwd = UITextParser::HTMLMoneyIconString( MONEYTYPE_02, nAvgRwd );

	_ToTryTimes = MMOArenaManager::getSingleton().GetVSOneOnOneRwdCanTryCnt();
	eventCallAsShowReward( totalRwd, avgRwd, _ToTryTimes );
}
//========================================================================================================================================
void UMMOUIVSReward::Init()
{
	Super::Init();

	SetTitleName();

	//
	check( EventAdapter == NULL );
	TArray<EGameEvent> evts;
	//evts.AddItem( GameEvent_VSOneOnOneRewardInfo );
	//evts.AddItem( GameEvent_VSOneOnOneGetRewardResult );
	EventAdapter = new TGameEventAdapter<UMMOUIVSReward>( this, evts );
}
//========================================================================================================================================
void UMMOUIVSReward::SetTitleName()
{
	TArray<struct FASValue> asFunArgs;
	FASValue asTitleName(EC_EventParm);
	asTitleName.Type = AS_String;

	asTitleName.S = MMOUI::ParseLocalizedPropertyPath( TEXT("MMOGame.VSReward.UITitleName") );

	asFunArgs.AddItem( asTitleName );
	this->Invoke( TEXT("SetWindowTitle"), asFunArgs );
}
//========================================================================================================================================
//========================================================================================================================================
void UMMOUIVSReward::ASOnGetReward()
{
	CMessageHandler::GetInstance().Send_TryGetVSOneOnOneReward();
}
//========================================================================================================================================
//========================================================================================================================================