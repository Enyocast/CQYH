#include "stdafx.h"
#include "MMOVipManager.h"
#include "MMOFacade.h"
#include "CommonGameEvents.h"
#include "MMOAchievementManager.h"
#include "MMOGuildManager.h"
#include "MMOChatManager.h"
#include "MallManager.h"

#define Player_Free_LV (7)
//==========================================================================================================================
MMOVipManager::MMOVipManager()
{
	_VipItemID[eVIPTyp_LV1] = 2101;
	_VipItemID[eVIPTyp_LV2] = 2102;
	_VipItemID[eVIPTyp_LV3] = 2103;

	SetMyLeftGameTime( 0 );
	_MyCurGameMode = 0;

	_MyInGameDayCnt = 0;
	_LastSelectedRole = FALSE;
}

//==========================================================================================================================
MMOVipManager::~MMOVipManager()
{
}

//==========================================================================================================================
void MMOVipManager::OnNativeGameEvent(struct MMOGameEvent* evt)
{
	if(evt == NULL){
		return;
	}

	switch(evt->GetEventType())
	{
	case GameEvent_VipStateChanged:
		{
			MMOGameEvent_OneInt *vipStateEvt = (MMOGameEvent_OneInt*)evt;

			AMMOActor* actor = MMOFacade::getSingleton().GetCharacter( vipStateEvt->IntData );
			if (actor == NULL){
				break;
			}

			//
			AMMOPlayer *pPlayer = Cast<AMMOPlayer>(actor);
			if( pPlayer == NULL ){
				break;
			}

			//ToDo::
		}
		break;
	case GameEvent_SyncGameLeftTime:
		{
			MMOGameEvent_OneInt *gameTimeEvt = (MMOGameEvent_OneInt*)evt;
			SetMyLeftGameTime( (UINT32)gameTimeEvt->IntData );

			//刷新游戏时间
			CheckGameTime();
		}
		break;
	case GameEvent_GamePlayStateChange:
		{
			MMOGameEvent_OneInt *gamePlayStateChangeEvt = (MMOGameEvent_OneInt*)evt;
			SetCurGameMode( gamePlayStateChangeEvt->IntData );

			HintForGameLimitedMode();
		}
		break;
	case GameEvent_EnterSelectingRole:
		{
			Clear();

			NotifyEnterSelectRoleTime();

			_LastSelectedRole = TRUE;
		}
		break;
	case GameEVent_SceneLoadFinish:
		{
			if( _LastSelectedRole ){
				//游戏状态提示
				HintForGameLimitedMode();

				//游戏剩余时间提示
				UINT32 leftSec = GetMyLeftGameTimeInSec();

				FString hintMsg = MMOUI::ParseLocalizedPropertyPath( TEXT("MMOGame.Recharge.HintLeftTime") );
				hintMsg += appItoa( ( leftSec + 59 ) / 60 );
				hintMsg += MMOUI::ParseLocalizedPropertyPath( TEXT("MMOGame.Time.CountDown5") );
				MMOChatManager::getSingleton().AddSystemMessage( hintMsg );
				//MMOUI::GetUIManager()->delegateAddScreenMessage( *hintMsg, MsgInfoType_Table, hintMsgName );
			}
			_LastSelectedRole = FALSE;
		}
		break;
	}
}
//==========================================================================================================================
UINT32 MMOVipManager::GetMyVipLeftSecond( INT vipType )
{
	if( vipType < eVIPTyp_LV1 || vipType >= eVIPTyp_LVMax ){
		return 0;
	}

	MMOFacade &mmoFacade = MMOFacade::getSingleton();

	//当前本地时间
	SYSTEMTIME curTime;
	::GetLocalTime(&curTime);
	UINT32 curTimeSec = mmoFacade.ConvertSystemTimeToTmTSecond( curTime );

	//本地与服务器的时间差
	INT32 secDiff = mmoFacade.GetClientToSceneSecondDiff();
	//
	UINT32 serverExpireTime = (UINT32)_MyVipTime[vipType]._ExpireTime;
	UINT32 leftSecond = 0;
	if( serverExpireTime > secDiff + curTimeSec ){
		leftSecond = serverExpireTime - ( secDiff + curTimeSec );
	}

	return leftSecond;
}
//==========================================================================================================================
void MMOVipManager::SetMyVipLeftSecondByServerTime( INT vipType, __time32_t serverTime )
{
	if( vipType < eVIPTyp_LV1 || vipType >= eVIPTyp_LVMax ){
		return;
	}

	_MyVipTime[vipType]._ExpireTime = serverTime;

	if (serverTime > 0)
	{
		// 成就获取
		MMOGameEvent_Achievement evtAch(adVip, 1, 0, 0);
		MMOUI::PostGameEvent(&evtAch);
	}

	MMOGameEvent_Guild evt(MMOGameEvent_Guild::EGET_UpdateGuildWelfareList);
	MMOUI::PostGameEvent(&evt);
}
////==========================================================================================================================
//UINT32 MMOVipManager::GetMyVipLeftSecond( INT vipType )
//{
//	if( vipType < eVIPTyp_LV1 || vipType >= eVIPTyp_LVMax ){
//		return 0;
//	}
//
//	MMOFacade &mmoFacade = MMOFacade::getSingleton();
//
//	//当前本地时间
//	SYSTEMTIME curTime;
//	::GetLocalTime(&curTime);
//	UINT32 curTimeSec = mmoFacade.ConvertSystemTimeToTmTSecond( curTime );
//
//	//本地与服务器的时间差
//	INT secDiff = mmoFacade.GetClientToSceneSecondDiff();
//	//
//	UINT32 curSecondLeft = _MyVipTime[vipType]._ScenodLeft;
//	INT32 pastSecond = ( curTimeSec - _MyVipTime[vipType]._LocalTimeStart );
//	if( pastSecond >= 0 ){
//		if( curSecondLeft > (UINT)pastSecond ){
//			curSecondLeft = (UINT)( curSecondLeft - (UINT)pastSecond );
//		}
//		else{
//			curSecondLeft = 0;
//		}
//	}
//
//	return curSecondLeft;
//}
////==========================================================================================================================
//void MMOVipManager::SetMyVipLeftSecondByServerTime( INT vipType, __time32_t serverTime )
//{
//	MMOFacade &mmoFacade = MMOFacade::getSingleton();
//
//	//本地的开始时间
//	__time32_t localTime = serverTime;
//	_localtime32(&localTime);
//
//	//本地与服务器的时间差
//	INT32 secDiff = mmoFacade.GetClientToSceneSecondDiff();
//	localTime += secDiff;
//
//	//
//	SetMyVipLeftSecond( vipType, second, localTime );
//}
////==========================================================================================================================
//void MMOVipManager::SetMyVipLeftSecondByClientTime( INT vipType, UINT32 second )
//{
//	MMOFacade &mmoFacade = MMOFacade::getSingleton();
//
//	//当前本地时间
//	SYSTEMTIME curTime;
//	::GetLocalTime(&curTime);
//	UINT32 curTimeSec = mmoFacade.ConvertSystemTimeToTmTSecond( curTime );
//
//	//
//	SetMyVipLeftSecond( vipType, second, (__time32_t)curTimeSec );
//}
////==========================================================================================================================
//void MMOVipManager::SetMyVipLeftSecond( INT vipType, __time32_t localTime )
//{
//	if( vipType < eVIPTyp_LV1 || vipType >= eVIPTyp_LVMax ){
//		return;
//	}
//
//	_MyVipTime[vipType]._ScenodLeft = second;
//	_MyVipTime[vipType]._LocalTimeStart = localTime;
//}
//==========================================================================================================================
eVipType MMOVipManager::GetMyCurrentVipType()
{
	INT curMaxLv = eVIPTyp_LVMax - 1;
	for( ; curMaxLv > eVIPTyp_None; --curMaxLv ){
		UINT32 leftTimeSec = GetMyVipLeftSecond( curMaxLv );
		if( leftTimeSec > 0 ){
			break;
		}
	}

	return (eVipType)curMaxLv;
}
//==
INT MMOVipManager::GetVipItemID( INT vipType )
{
	if( vipType < eVIPTyp_LV1 || vipType >= eVIPTyp_LVMax ){
		return 0 ;
	}

	return _VipItemID[vipType];
}
//==========================================================================================================================
void MMOVipManager::ReadVipPrivilege()
{
	INT privilegeCnt = appAtoi( *MMOUI::ParseLocalizedPropertyPath( TEXT("MMOGame.VipPrivilege.TotalCnt") ) );
	if( privilegeCnt <= 0 ){
		return;
	}
	//
	INT curCnt = _VipPrivilege[eVIPTyp_None].Num();
	if( curCnt == privilegeCnt ){
		//已经载入过了
		return;
	}

	FString lookUpStrFormat = TEXT("MMOGame.VipPrivilege.");
	FString lookUpStr;
	for( INT i = 0; i < eVIPTyp_LVMax; ++i ){
		_VipPrivilege[i].Empty();
		_VipPrivilege[i].AddZeroed( privilegeCnt );

		for( INT j = 0; j < privilegeCnt; ++j ){
			lookUpStr = lookUpStrFormat;
			lookUpStr += appItoa( i );
			lookUpStr += TEXT("_");
			lookUpStr += appItoa( j );

			//
			_VipPrivilege[i](j) = MMOUI::ParseLocalizedPropertyPath( lookUpStr );
		}
	}
}

//==========================================================================================================================
const TArray<FString> &MMOVipManager::GetVipPrivilege( eVipType vipType )
{
	check( vipType >= eVIPTyp_None && vipType < eVIPTyp_LVMax );

	return _VipPrivilege[vipType];
}

//==========================================================================================================================
void MMOVipManager::Initialize()
{
	MMOUI::RegisterEventHandler( this, GameEvent_VipStateChanged );
	MMOUI::RegisterEventHandler( this, GameEvent_SyncGameLeftTime );
	MMOUI::RegisterEventHandler( this, GameEvent_GamePlayStateChange );
	MMOUI::RegisterEventHandler( this, GameEVent_SceneLoadFinish );
	MMOUI::RegisterEventHandler( this, GameEvent_EnterSelectingRole );
	GConfig->GetInt( TEXT("VipShop") , TEXT("VipShopId") , _VipShopId , GDefaultGameIni );
	
}

//==========================================================================================================================
void MMOVipManager::Shutdown()
{
	MMOUI::UnRegisterEventHandler( this, GameEvent_EnterSelectingRole );
	MMOUI::UnRegisterEventHandler( this, GameEVent_SceneLoadFinish );
	MMOUI::UnRegisterEventHandler( this, GameEvent_GamePlayStateChange );
	MMOUI::UnRegisterEventHandler( this, GameEvent_SyncGameLeftTime );
	MMOUI::UnRegisterEventHandler( this, GameEvent_VipStateChanged );
}

//==========================================================================================================================
void MMOVipManager::Clear()
{
	SetCurGameMode( 0 );
}

//==========================================================================================================================
void MMOVipManager::GetVipDescriptionString( INT vipType, FString &vipName, UINT &leftDay, UINT &leftHour )
{
	if( vipType <= eVIPTyp_None || vipType >= eVIPTyp_LVMax ){
		vipName = TEXT("");
		leftDay = 0;
		leftDay = 0;
		return;
	}

	//
	FString vipNameLookUp = TEXT("MMOGame.Vip.VipName");
	vipNameLookUp += appItoa( vipType );
	vipName = MMOUI::ParseLocalizedPropertyPath( vipNameLookUp );

	//
	UINT curVipLeftSecond = GetMyVipLeftSecond( vipType );
	curVipLeftSecond += 3599;
	leftDay = curVipLeftSecond / 86400;
	leftHour = curVipLeftSecond % 86400 / 3600;
}

void MMOVipManager::ShowVipShopByType(eVipShopType type)
{
	FName panelName;
	FString asTabChangeFuncName;
	switch(type)
	{
	case eVipShopType_Warehouse:
		panelName = MMOUI::GetUIManager()->Panel_Warehouse;
		break;
	case eVipShopType_Shop:
		panelName = MMOUI::GetUIManager()->Panel_Shop;
		MMOUI::GetUIManager()->ShowNpcShop(_VipShopId);
		break;
	case eVipShopType_Soul:
		panelName = MMOUI::GetUIManager()->Panel_SoulEmbed;
		break;
	case eVipShopType_Inscription:
		panelName = MMOUI::GetUIManager()->Panel_WeaponSkill;
		asTabChangeFuncName = TEXT("ChangeToTab0");
		break;
	case eVipShopType_Auction:
		panelName = MMOUI::GetUIManager()->Panel_AuctionView;
		break;
	}
	MMOUI::GetUIManager()->ShowPanelEx(panelName,TRUE,asTabChangeFuncName);
	MMOUI::GetUIManager()->ShowPanelEx(MMOUI::GetUIManager()->Panel_Vip,FALSE,"");
	MMOUI::GetUIManager()->SetPanelShowWithOutTarget(panelName);

}

//=============================================================================
void MMOVipManager::SetMyLeftGameTime( UINT32 sec )
{
	//当前本地时间
	SYSTEMTIME curTime;
	::GetLocalTime(&curTime);
	_MyLeftGameTimeUpdateTime = MMOFacade::getSingleton().ConvertSystemTimeToTmTSecond( curTime );

	//
	_MyLeftGameTime = sec;
}
//------------------------------------------------------------------------------
UINT32 MMOVipManager::GetMyLeftGameTimeInSec()
{
	EGameState curGameState =  MMO::GetCurrentGameState();
	if( curGameState == EGameState_Selecting ){
		//人物选择界面不计时(每次进入人物选择界面会刷新此时间)
		return _MyLeftGameTime;
	}

	AMMOPlayer* mainPlayer = MMOFacade::getSingleton().GetMainPlayer();
	if( mainPlayer != NULL ){
		INT mainPlayerLv = mainPlayer->GetActorLevel();
		if( mainPlayerLv < Player_Free_LV ){
			//免费级别以下不计时
			return _MyLeftGameTime;
		}
	}
	//当前本地时间
	SYSTEMTIME curTime;
	::GetLocalTime(&curTime);
	UINT32 curTimeSec = MMOFacade::getSingleton().ConvertSystemTimeToTmTSecond( curTime );
	UINT32 pastedTimeSec = (UINT32)( curTimeSec - _MyLeftGameTimeUpdateTime );//如果时间不倒流，玩家不在游戏时调本地时间，一定是正数

	if( _MyLeftGameTime <= pastedTimeSec ){
		return 0;
	}

	return (UINT32)( _MyLeftGameTime - pastedTimeSec );
}
//==================================================================
void MMOVipManager::SetCurGameMode( INT modeType )
{ 
	_MyCurGameMode = modeType; 
}

void MMOVipManager::NotifyPlayerLevelChange(INT curLevel)
{
	// 任务 #23813
	EGameState curGameState = MMO::GetCurrentGameState();
	if (curGameState == EGameState_InGame){
		AMMOPlayer* mainPlayer = MMOFacade::getSingleton().GetMainPlayer();
		if (mainPlayer != NULL){
			INT mainPlayerLv = mainPlayer->GetActorLevel();
			if (mainPlayerLv == Player_Free_LV){
				UINT32 leftSec = GetMyLeftGameTimeInSec();
				if (leftSec <= 0){
					UMMOUIRecharge* panel = (UMMOUIRecharge*)MMOUI::FindUIPanelEx(MMOUI::GetUIManager()->Panel_Recharge);
					if (panel){
						panel->Show(TRUE);
					}

					FString hintName = TEXT("MMOGame.Recharge.HintToRecharge");
					FString hintText = MMOUI::ParseLocalizedPropertyPath( hintName );
					MMOUI::GetUIManager()->delegateAddScreenMessage( hintText, MsgInfoType_Table, hintName );
					MMOChatManager::getSingleton().AddSystemMessage( hintText );
				}
			}
		}
	}
}
//==================================================================
void MMOVipManager::CheckGameTime()
{
	const UINT32 hint30MinLeft = 60 * 30;
	const UINT32 hint5MinLeft = 60 * 5;
	EGameState curGameState =  MMO::GetCurrentGameState();
	if( curGameState == EGameState_Selecting ){
		UMMOUISelectRolePanel *pRoleSelectingPanel = ( UMMOUISelectRolePanel* )MMOUI::FindUIPanel( MMOUI::GetUIManager()->Panel_Login_Select );
		if( pRoleSelectingPanel != NULL ){
			UINT32 leftSec = GetMyLeftGameTimeInSec();
			FString titleStr = MMOUI::ParseLocalizedPropertyPath( TEXT("MMOGame.Recharge.HintLeftTime") );
			pRoleSelectingPanel->eventCallASSetGameLeftTime( titleStr, (INT)leftSec );
		}
	}
	else if( curGameState == EGameState_InGame ){
		AMMOPlayer* mainPlayer = MMOFacade::getSingleton().GetMainPlayer();
		if( mainPlayer != NULL ){
			INT mainPlayerLv = mainPlayer->GetActorLevel();
			if( mainPlayerLv >= Player_Free_LV ){
				UINT32 leftSec = GetMyLeftGameTimeInSec();
				//UMMOUINoticeInfo *pNoticeInfo = (UMMOUINoticeInfo*)MMOUI::FindUIPanel( MMOUI::GetUIManager()->Panel_NoticeInfo );
				UMMOUIChat *pChatPanel = (UMMOUIChat*)MMOUI::FindUIPanel( MMOUI::GetUIManager()->Panel_Chat );
				if( leftSec <= 60 * 45 && pChatPanel != NULL ){
					//开始倒计时
					INT32 intervalSec = leftSec % 60;
					pChatPanel->eventCallASSetTimeEvent( eGameTimeHintType_init, leftSec, intervalSec );
				}//按剩余时间提示
			}//满足判断等级

			// 任务 #23813
			if (mainPlayerLv == Player_Free_LV){
				UINT32 leftSec = GetMyLeftGameTimeInSec();
				if (leftSec <= 0){
					UMMOUIRecharge* panel = (UMMOUIRecharge*)MMOUI::FindUIPanelEx(MMOUI::GetUIManager()->Panel_Recharge);
					if (panel){
						panel->Show(TRUE);
					}

					FString hintName = TEXT("MMOGame.Recharge.HintToRecharge");
					FString hintText = MMOUI::ParseLocalizedPropertyPath( hintName );
					MMOUI::GetUIManager()->delegateAddScreenMessage( hintText, MsgInfoType_Table, hintName );
					MMOChatManager::getSingleton().AddSystemMessage( hintText );
				}
			}
		}
	}
}
//==================================================================
void MMOVipManager::HintForGameLimitedMode()
{
	UBOOL isLimitedMode = IsLimitedGamePlayMode();
	if( isLimitedMode ){
		UMMOUICenterStaticNotice* noticePanel = (UMMOUICenterStaticNotice*)MMOUI::FindUIPanelEx( MMOUI::GetUIManager()->Panel_DynamicUI_CenterStaticNotice );
		if( noticePanel != NULL ){
			FString hintTextIdx = TEXT("MMOGame.Recharge.CurrentGameLimitedModeHint");
			noticePanel->eventCallASSetNoticeContents( 0,  MMOUI::ParseLocalizedPropertyPath( hintTextIdx ) );
			noticePanel->Show( TRUE );
		}
	}
	else{
		UMMOUICenterStaticNotice* noticePanel = (UMMOUICenterStaticNotice*)MMOUI::FindUIPanel( MMOUI::GetUIManager()->Panel_DynamicUI_CenterStaticNotice );
		if( noticePanel != NULL ){
			noticePanel->Show( FALSE );
		}
	}
}
//=============================================================================
void MMOVipManager::NotifyEnterSelectRoleTime()
{
	//当前本地时间
	SYSTEMTIME curTime;
	::GetLocalTime(&curTime);
	_LastSelectedRoleTime = MMOFacade::getSingleton().ConvertSystemTimeToTmTSecond( curTime );
}