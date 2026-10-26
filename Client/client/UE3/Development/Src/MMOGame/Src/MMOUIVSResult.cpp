#include "stdafx.h"
#include "MMOGameUIClasses.h"
#include "net/message_handler.h"
#include "MMOGameEvent.h"
#include "MMOFacade.h"
#include "MMOArenaManager.h"
#include "MMOMsgBoxManager.h"

IMPLEMENT_CLASS(UMMOUIVSResult)

//========================================================================================================================================
void UMMOUIVSResult::PreOnShow( UBOOL show )
{
	Super::PreOnShow( show );

	if( show ){
	}
	else{
		ResetWaitQueueHintMsgBtns();
		ResetAllPopupBox();
	}
}
//========================================================================================================================================
void UMMOUIVSResult::OnNativeGameEvent( struct MMOGameEvent* evt )
{
	if( evt == NULL ){
		return;
	}

	//switch( evt->GetEventType() )
	//{
	//case GameEvent_ShowArenaWaitQueue:
	//	{
	//		eventCallAsShowWaitQueueTime( TRUE );
	//	}
	//	break;
	//}
}
//========================================================================================================================================
void UMMOUIVSResult::PlayerMoneyChange( BYTE MoneyType, INT DeltaMoney )
{
	//if( !IsVisible ){
	//	return;
	//}

	//if( MoneyType != MONEYTYPE_ARENA ){
	//	return;
	//}
	//if( MoneyType != MONEYTYPE_03 ){
	//	return;
	//}

	//UpdatePanel();
}
//========================================================================================================================================
void UMMOUIVSResult::UpdatePanel()
{
	UpdateResultInfo();
}
//========================================================================================================================================
void UMMOUIVSResult::UpdateResultInfo()
{
	AMMOPlayer* mainPlayer = MMOFacade::getSingleton().GetMainPlayer();

	//INT vsMoneyDelta = 0;
	//if( mainPlayer != NULL ){
	//	vsMoneyDelta = mainPlayer->GetMoney( MONEYTYPE_03 );
	//}

	//FString todayRwdMaxStr = TEXT("");
	UBOOL isTodayRwdMax = FALSE;
	INT curGetRwdCnt = MMOArenaManager::getSingleton().GetVSOneOnOneRwdCanTryCnt();
	if( curGetRwdCnt >= VS_ONE_ON_ONE_DAILY_RWD_MAX ){
		INT rwdCntAdded = MMOArenaManager::getSingleton().GetVSOneOnOneRwdTryCntDelta();
		if( rwdCntAdded <= 0 ){
			isTodayRwdMax = TRUE;
		}
	}

	eventCallAsShowResult( _VSResult, _vsMoneyDelta, _ScoreDelta, _LastSec, isTodayRwdMax );
}
//========================================================================================================================================
void UMMOUIVSResult::UpdateTimeOut( INT isToShowType )
{
	if( isToShowType == EVSTimeCntSta_Exceed ){
		if( _ConfirmBox != NULL ){
			MMOMsgBoxManager::getSingleton().DispatchMsgBoxButtonNo( _ConfirmBox );
		}
		_ConfirmBox = NULL;
		//
		ResetWaitQueueHintMsgBtns();
	}
	eventCallAsShowTimeCountDown( isToShowType, 4 * 60 );
}
//===============================================================================================================
void UMMOUIVSResult::ResetAllPopupBox()
{
	if( _ConfirmBox != NULL ){
		MMOMsgBoxManager::getSingleton().DispatchMsgBoxButtonNo( _ConfirmBox );
		_ConfirmBox = NULL;
	}
}
//===============================================================================================================
void UMMOUIVSResult::ResetWaitQueueHintMsgBtns()
{
	if( _MsgButtonIdx >= 0 ){
		MMOMsgButtonManager::getSingleton().RemoveOneTypeButtons( E_MsgBtnShow_ArenaWait );
	}
	_MsgButtonIdx = -1;
}
//===============================================================================================================
void UMMOUIVSResult::PopupConfirmQuitWaitQueue()
{
	if( _ConfirmBox != NULL ){
		MMOMsgBoxManager::getSingleton().DispatchMsgBoxButtonNo( _ConfirmBox );
		_ConfirmBox = NULL;
	}

	FScriptDelegate funYes(EC_EventParm);
	funYes.Object = this;
	funYes.FunctionName = TEXT( "ConfirmedQuitWaitQueue" );

	FScriptDelegate funNo(EC_EventParm);
	funNo.Object = this;
	funNo.FunctionName = TEXT( "CancelQuitWaitQueue" );

	FString msgText = MMOUI::ParseLocalizedPropertyPath(TEXT("MMOGame.Arena.ConfirmQuitWaitQueue"));
	_ConfirmBox = MMOMsgBoxManager::getSingleton().AddMessageBox( msgText, 0, funYes, funNo );
}
//---------------------------------------------------------------------------------------------------------------
void UMMOUIVSResult::ConfirmedQuitWaitQueue( UGFxObject *pMc )
{
	if( _ConfirmBox == NULL ){
		return;
	}

	_ConfirmBox = NULL;

	CMessageHandler::GetInstance().Send_QuitVSOneOnOneWaiting();
}

//---------------------------------------------------------------------------------------------------------------
void UMMOUIVSResult::CancelQuitWaitQueue( UGFxObject *pMc )
{
	_ConfirmBox = NULL;
}
//========================================================================================================================================
void UMMOUIVSResult::Init()
{
	Super::Init();

	//SetTitleName();
	_MsgButtonIdx = -1;
	//
	check( EventAdapter == NULL );
	TArray<EGameEvent> evts;
	//evts.AddItem( GameEvent_ShowArenaWaitQueue );
	//evts.AddItem( GameEvent_VSOneOnOneResult );
	EventAdapter = new TGameEventAdapter<UMMOUIVSResult>( this, evts );
}
//========================================================================================================================================
void UMMOUIVSResult::SetTitleName()
{
	TArray<struct FASValue> asFunArgs;
	FASValue asTitleName(EC_EventParm);
	asTitleName.Type = AS_String;

	asTitleName.S = MMOUI::ParseLocalizedPropertyPath( TEXT("MMOGame.VSResult.UITitleName") );

	asFunArgs.AddItem( asTitleName );
	this->Invoke( TEXT("SetWindowTitle"), asFunArgs );
}
//========================================================================================================================================
void UMMOUIVSResult::NotifyByWaitQueueMsgBtnClick()
{
	eventCallAsShowWaitQueueTime( TRUE );
}
//========================================================================================================================================
//========================================================================================================================================
void UMMOUIVSResult::ASOnConfirmResult()
{
	Show( FALSE );
}
//========================================================================================================================================
void UMMOUIVSResult::ASConfirmTimeOut()
{
	eventCallAsShowTimeCountDown( FALSE, 0 );

	Show( FALSE );
}
//========================================================================================================================================
void UMMOUIVSResult::ASTryQuitWaitQueue()
{
	PopupConfirmQuitWaitQueue();
}
//========================================================================================================================================
void UMMOUIVSResult::ASHideWaitQueueWnd()
{
	eventCallAsShowWaitQueueTime( FALSE );
	//
	FScriptDelegate funCallBack(EC_EventParm);
	funCallBack.Object = this;
	funCallBack.FunctionName = TEXT( "NotifyByWaitQueueMsgBtnClick" );

	MMOMsgButtonManager_Parms Parms(EC_EventParm);
	_MsgButtonIdx = MMOMsgButtonManager::getSingleton().AddNewButton( funCallBack, Parms, E_MsgBtnShow_ArenaWait );

	//FString hintText = MMOUI::ParseLocalizedPropertyPath( TEXT("MMOGame.Arena.StatePanelWaitingNextRoundHint") );
	//AMMOPlayer* mainPlayer = MMOFacade::getSingleton().GetMainPlayer();
	//_MsgButtonIdx = MMOMsgButtonManager::getSingleton().AddNewButton( hintText, 0, mainPlayer != NULL ? mainPlayer->GetActorName() : TEXT(""), GameEvent_ShowArenaWaitQueue , E_MsgBtnShow_ArenaWait );
}
//========================================================================================================================================
//========================================================================================================================================