#include "stdafx.h"
#include "MMOGameUIClasses.h"
#include "MMOFacade.h"
#include "UITextParser.h"
#include "MMOMsgBoxManager.h"
#include "WebHtmlManager.h"
#include "MallManager.h"

IMPLEMENT_CLASS(UMMOUIRecharge)

//================================================================================================
void UMMOUIRecharge::PreOnShow(UBOOL show)
{
	Super::PreOnShow( show );

	if( IsInitialized == FALSE ){
		return;
	}

	//
	if( show ){
		UpdatePanel();
		UpdateMyYuanBao();
	}
	else{
		CloseAllPopUpPanel();
		_LastRechargeMoney = 0;
	}
}
//========================================================================================
void UMMOUIRecharge::OnNativeGameEvent(struct MMOGameEvent* evt)
{
	if(evt == NULL){
		return;
	}

	switch(evt->GetEventType())
	{
	case GameEvent_RealMoneyChange:
		{
			//MMOGameEvent_GoldStore_UpdateMoney* gsEvt = (MMOGameEvent_GoldStore_UpdateMoney*) evt;
			UpdateMyYuanBao();
		}
		break;
	}
}
//
void UMMOUIRecharge::UpdatePanel()
{
	CMessageHandler::GetInstance().Send_MallAskRealMoney();
}
////========================================================================================================================================
//void UMMOUIRecharge::PlayerMoneyChange( BYTE MoneyType, int Money, INT OldMoney )
//{
//	if( IsVisible && MoneyType == E_MONEYTYPE_04 ){
//		UpdateMyYuanBao();
//	}
//}
//===============================================================================================================
void UMMOUIRecharge::UpdateMyYuanBao()
{
	INT curDianQuan = MallManager::getSingleton().GetRealMoney();

	eventCallAsSetCurYuanBao( curDianQuan );
}
//===============================================================================================================
void UMMOUIRecharge::InitRechargeInfo()
{
	UGFxObject* dataProvider = GFXPlayer->CreateArray();
	INT itemIdx = 0;
	FString sectionName = TEXT("Recharge");
	FString rechargeTime = TEXT("RechargeTime");
	FString rechargeCost = TEXT("RechargeCost");
	FString hourStr = MMOUI::ParseLocalizedPropertyPath( TEXT("MMOGame.Time.CountDown4") );

	for( INT i = 0; i < 3; ++i ){
		FString strTemp;

		INT timeVal = 0;
		strTemp = rechargeTime + appItoa( i );
		GConfig->GetInt( *sectionName, *strTemp, timeVal, GGameIni );

		INT costVal = 0;
		strTemp = rechargeCost + appItoa( i );
		GConfig->GetInt( *sectionName, *strTemp, costVal, GGameIni );
		//
		if( timeVal <= 0 ){
			continue;
		}

		UGFxObject* itemObj = GFXPlayer->CreateObject(TEXT("Object"));//GFXPlayer->CreateObject( TEXT("UI_Recharge.AS3.RechargeItem") );

		strTemp = appItoa( timeVal );
		strTemp += hourStr;
		itemObj->SetString( TEXT("Time"), strTemp );
		itemObj->SetString( TEXT("Cost"), UITextParser::HTMLMoneyIconString( MONEYTYPE_04, costVal ) );

		eventCallAsSetRechargeInfo( i, itemObj );
	}
}
//========================================================================================================================================
void UMMOUIRecharge::Init()
{
	Super::Init();
	check(NULL == EventAdapter);
	if (NULL == EventAdapter){
		TArray<EGameEvent> evts;
		evts.AddItem(GameEvent_RealMoneyChange);
		EventAdapter = new TGameEventAdapter<UMMOUIRecharge>(this, evts);
	}

	InitRechargeInfo();
}
void UMMOUIRecharge::CloseAllPopUpPanel()
{
	if( _ConfirmBox != NULL ){
		MMOMsgBoxManager::getSingleton().DispatchMsgBoxButtonNo( _ConfirmBox );
		_ConfirmBox = NULL;
	}
}
void UMMOUIRecharge::NotifyRechargeResult( INT result )
{
	//if( _LastRechargeMoney < 0 ){
	//	warnf( NAME_Error, TEXT("UMMOUIRecharge::NotifyRechargeResult error Idx") );
	//	return;
	//}
	//eventCallAsEneableRecharge( _LastRechargeMoney, TRUE );

	FString hintMsgName;
	FString hintMsg;
	if( result ){
		//FString rechargeTimeStr = TEXT("RechargeTime");
		//INT rechargeTime = _LastRechargeMoney;
		//rechargeTimeStr += appItoa( rechargeTime );

		INT sec = _LastRechargeMoney * 6000;
		INT hour = sec / 3600;
		INT minu = sec % 3600 / 60;

		FString timeStr = TEXT("");
		if( hour > 0 ){
			timeStr += appItoa( hour );
			timeStr += MMOUI::ParseLocalizedPropertyPath( TEXT("MMOGame.Time.CountDown4") );
		}
		if( minu > 0 ){
			timeStr += appItoa( minu );
			timeStr += MMOUI::ParseLocalizedPropertyPath( TEXT("MMOGame.Time.CountDown5") );
		}

		//GConfig->GetInt( TEXT("Recharge"), *rechargeTimeStr, timeVal, GGameIni );

		hintMsgName = TEXT("MMOGame.Recharge.RechargeSuccess");
		hintMsg = FString::Printf( *MMOUI::ParseLocalizedPropertyPath( hintMsgName ), *timeStr );
		
	}
	else{
		hintMsgName = TEXT("MMOGame.Recharge.RechargeFailed");
		hintMsg = MMOUI::ParseLocalizedPropertyPath( hintMsgName );
	}

	MMOUI::GetUIManager()->delegateAddScreenMessage( hintMsg, MsgInfoType_Table, hintMsgName );
}
//===============================================================================================================
//===============================================================================================================
void UMMOUIRecharge::ASTryRecharge( INT rechargeMoney )
{
	if( _ConfirmBox != NULL ){
		MMOMsgBoxManager::getSingleton().DispatchMsgBoxButtonNo( _ConfirmBox );
		_ConfirmBox = NULL;

		//eventCallAsEneableRecharge( _LastRechargeMoney, TRUE );
	}

	FScriptDelegate funYes(EC_EventParm);
	funYes.Object = this;
	funYes.FunctionName = TEXT( "ConfirmRecharge" );

	FScriptDelegate funNo(EC_EventParm);
	funNo.Object = this;
	funNo.FunctionName = TEXT( "CancelRecharge" );

	FString strTitle = TEXT("");//MMOUI::ParseLocalizedPropertyPath( TEXT("MMOGame.EquipLevelUp.ConfirmLevelUpTitle") );
	FString strContent = MMOUI::ParseLocalizedPropertyPath( TEXT("MMOGame.Recharge.ConfirmRechargeHint") );

	_ConfirmBox = MMOMsgBoxManager::getSingleton().AddMessageBox( strContent, rechargeMoney, funYes, funNo );
	//
	_LastRechargeMoney = rechargeMoney;
	//eventCallAsEneableRecharge( _LastRechargeMoney, FALSE );
}
//---------------------------------------------------------------------------------------------------------------
void UMMOUIRecharge::ConfirmRecharge( UGFxObject *pMc )
{
	if( _ConfirmBox == NULL ){
		return;
	}
	INT rechargeMoney = pMc->GetInt( TEXT("iteminfoid") );
	_ConfirmBox = NULL;
	//
	INT curDianQuan = rechargeMoney * DIAN_QUAN_TO_YUAN_BAO_FACTOR;
	CMessageHandler::GetInstance().Send_RechargeGameTime( curDianQuan );
}

//---------------------------------------------------------------------------------------------------------------
void UMMOUIRecharge::CancelRecharge( UGFxObject *pMc )
{
	_ConfirmBox = NULL;
	_LastRechargeMoney = 0;
	//eventCallAsEneableRecharge( _LastRechargeMoney, TRUE );
}
//===================================================================================
void UMMOUIRecharge::ASRechargeForYuanBao()
{
	WebHtmlManager::getSingleton().OpenRechargeYuanBao();
	//WebHtmlManager::getSingleton().OpenRechargeYuanBaoByIE();
}
//===============================================================================================================
//===============================================================================================================