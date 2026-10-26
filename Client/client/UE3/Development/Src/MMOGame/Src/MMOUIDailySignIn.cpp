#include "stdafx.h"
#include "MMOGameUIClasses.h"
#include "MMOFacade.h"
#include "MMODailySignInManager.h"
#include "MMOMsgButtonManager.h"

IMPLEMENT_CLASS(UMMOUIDailySignIn)

//================================================================================================
void UMMOUIDailySignIn::PreOnShow(UBOOL show)
{
	Super::PreOnShow( show );

	if( IsInitialized == FALSE ){
		return;
	}

	//
	if( show ){
		UpdatePanel();
	}
	else{
	}

	if( MMODailySignInManager::getSingleton().IsCurShowingHintForSignIn() ){
		MMODailySignInManager::getSingleton().RemoveHintForSignInIf();
	}
}
//========================================================================================
void UMMOUIDailySignIn::OnNativeGameEvent(struct MMOGameEvent* evt)
{
	if(evt == NULL){
		return;
	}

	//switch(evt->GetEventType())
	//{
	//}
}
//
void UMMOUIDailySignIn::UpdatePanel()
{
	InitDailySignInRewards();
}
//===============================================================================================================
void UMMOUIDailySignIn::InitDailySignInRewards()
{
	UGFxObject* dataProvider = GFXPlayer->CreateArray();
	if( dataProvider == NULL ){
		warnf(NAME_Error, TEXT("======!!!!======= [UMMOUIDailySignIn::InitDailySignInRewards cannot create AS array]") );
		return;
	}

	MMOFacade &mmoFacade = MMOFacade::getSingleton();
	MMODailySignInManager &dailySignInMgr = MMODailySignInManager::getSingleton();

	const SSignInRewardState &curSignInState = dailySignInMgr.GetMyCurSignInState();
	//
	if( curSignInState._CanSignIn ){
		eventCallAsSetCurSignInDay( curSignInState._CurSignInDay );
	}
	else{
		eventCallAsSetCurSignInDay( -1 );
	}

	//
	INT loopAddedCnt = 0;
	for( INT i = 1; i <= MMODailySignInManager::SIGN_IN_TOTAL; ++i ){
		FString strTemp;

		UGFxObject* itemSingleObj = GFXPlayer->CreateObject( TEXT("UI_DailySignIn.AS3.DailySignInRewardItemData") );
		if( itemSingleObj == NULL ){
			warnf(NAME_Error, TEXT("======!!!!======= [UMMOUIDailySignIn::InitDailySignInRewards cannot create AS Object]") );
			continue;
		}

		const SSignInReward * rewardData = dailySignInMgr.GetSignInRewardAtDay( i );
		if( rewardData == NULL ){
			continue;
		}

		//
		itemSingleObj->SetInt( TEXT("SignInIdx"), i );
		//
		itemSingleObj->SetInt( TEXT("ItemID"), rewardData->_ItemID );
		//
		itemSingleObj->SetInt( TEXT("ItemNum"), rewardData->_ItemCnt );
		//
		UItem *pRewardItem = mmoFacade.FindItemTemplate( rewardData->_ItemID );
		itemSingleObj->SetString( TEXT("IconName"), pRewardItem != NULL ? mmoFacade.GetItemIconNamePersonalized( pRewardItem ) : TEXT("") );
		//
		UBOOL isSignedIn = ( i == curSignInState._CurSignInDay ) ? !curSignInState._CanSignIn : i < curSignInState._CurSignInDay;
		itemSingleObj->SetBool( TEXT("IsGotten"), isSignedIn );
		
		dataProvider->SetElementObject( loopAddedCnt, itemSingleObj );
		++loopAddedCnt;
	}

	eventCallAsSetRewardDatas( dataProvider );
	
	//
	FString curSignedInDaysFormatStr = MMOUI::ParseLocalizedPropertyPath( TEXT("MMOGame.DailySignIn.CurrentSignedInDays") );
	INT signedDay = curSignInState._CurSignInDay;
	if( curSignInState._CanSignIn ){
		signedDay -= 1;
	}
	FString curSignedInDays = FString::Printf( *curSignedInDaysFormatStr, signedDay );
	eventCallAsSetCurrentSignedIn( curSignedInDays );
}
//========================================================================================================================================
void UMMOUIDailySignIn::Init()
{
	Super::Init();
	check(NULL == EventAdapter);
	if (NULL == EventAdapter){
		//TArray<EGameEvent> evts;
		//evts.AddItem(GameEvent_GoldStore_UpdatePlayerRealMoney);
		//EventAdapter = new TGameEventAdapter<UMMOUIRecharge>(this, evts);
	}
	//
	InitMc();

	//InitDailySignInRewards();
}
//
void UMMOUIDailySignIn::InitMc()
{
	eventCallAsInitSignInRewardSlot( ESPType_DailySignIn );
	//
	FString signRequiresFormatStr = MMOUI::ParseLocalizedPropertyPath( TEXT("MMOGame.DailySignIn.SignInRequires") );
	FString signRequiresStr = FString::Printf( *signRequiresFormatStr, MMODailySignInManager::SIGN_IN_LV_REQUIRE );
	eventCallAsSetSignInRequires( signRequiresStr );
}
//
void UMMOUIDailySignIn::NotifyGetDailySignInRewardResult( INT signInDay )
{
	//const SSignInRewardState &curSignInState = MMODailySignInManager::getSingleton().GetMyCurSignInState();

	FString hintMsgName = TEXT("MMOGame.DailySignIn.SignInTodaySuccess");
	FString hintMsg = MMOUI::ParseLocalizedPropertyPath( hintMsgName );
	MMOUI::GetUIManager()->delegateAddScreenMessage( hintMsg, MsgInfoType_Table, hintMsgName );
	//
	UpdatePanel();
}
//===============================================================================================================
//===============================================================================================================
void UMMOUIDailySignIn::ASTryGetSignReward( int signInIdx )
{
	const SSignInRewardState &curSignInState = MMODailySignInManager::getSingleton().GetMyCurSignInState();
	if( !curSignInState._CanSignIn ){
		FString hintMsgName = TEXT("MMOGame.DailySignIn.ErrorTodaySignedIn");
		FString hintMsg = MMOUI::ParseLocalizedPropertyPath( hintMsgName );
		MMOUI::GetUIManager()->delegateAddScreenMessage( hintMsg, MsgInfoType_Table, hintMsgName );
		return;
	}

	CMessageHandler::GetInstance().Send_SignInToday();
}
//===============================================================================================================
//===============================================================================================================