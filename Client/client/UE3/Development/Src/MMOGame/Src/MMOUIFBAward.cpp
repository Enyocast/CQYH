#include "stdafx.h"
#include "MMOGameUIClasses.h"
#include "MMOFacade.h"
#include "MMOMapDataManager.h"
#include "UITextParser.h"
#include "MMOGuideManager.h"

IMPLEMENT_CLASS(UMMOUIFBAward)

//
void UMMOUIFBAward::PostOnShow( UBOOL show )
{
	Super::PostOnShow(show);

	if( show ){
		FExportMap &mapInfo = MMOMapDataManager::getSingleton().GetCurMap();
		if( EGameState_InGame != MMO::GetCurrentGameState() || mapInfo.ServerMapType != E_est_Dungeon ){
			//在loading时，或是不在副本，不显示
			Show( FALSE );
			return;
		}

		MoveCenterToScreenCenter( 0, 0 );

		//
		InitFBAwardMode();
		UpdateMyAward();
		UpdateMemberAward();

		MMOGameEvent_Guide evtGuide(EGUET_ShowDungeonAward);
		MMOUI::PostGameEvent(&evtGuide);
	}
	else{
	}
}

//
void UMMOUIFBAward::ResetData()
{
	MyClickAwardIdx.Empty();
}

//
void UMMOUIFBAward::UpdateMyAward()
{
	UGFxObject *pAwardsSlot = NULL;
	FBMemberAwardData *pAwardData = NULL;
	AMMOPlayerController* plyerCtrl = MMOFacade::getSingleton().GetMainController();
	INT iPortraitID = 0;
	//
	pAwardData = MMOFacade::getSingleton().GetFBAward(0);
	//portrait
	FString classNameLookupKey = GFXPlayer->GetASHeadIconFrame( Player->GetClassId(), Player->GetSex() == EGT_Female );
	MyPortrait_mc->GotoAndStop( classNameLookupKey );
	//name
	MyName_mc->SetText( GetPlayerRoleName() );
	//Score
	MyScore_mc->GotoAndStopI( pAwardData->m_uiFBGradedPt );
	//Set all award from server
	UItem *pItem = NULL;
	UGFxObject *pAwardsMny = NULL;
	INT clickCnt = MyClickAwardIdx.Num();
	INT awardIdx = 0;
	for( INT i = 0; i < MAX_FB_Award; ++i )
	{
		pAwardsSlot = MyFBAward[i]->GetObject( TEXT("AnimSlotShow_mc") );

		//取得抽奖顺序，因为服务器不传这数据，客户端自己记录
		bool isGotAward = false;
		INT dataIdx = 0;
		INT prevClickIdx = -1;
		for( INT j = 0; j < clickCnt; ++j ){
			INT curClickIdx = MyClickAwardIdx(j);
			//
			if( i == curClickIdx ){
				isGotAward = true;
				break;
			}
			//
			if( prevClickIdx != curClickIdx ){
				++dataIdx;
				prevClickIdx = curClickIdx;
			}
		}

		//越界检查
		if( dataIdx >= MAX_FB_AWARDS_CNT ){
			warnf( NAME_Error, TEXT("Update FBAward(%d) dataIdx Overflow[%d]"), i, dataIdx );
			continue;
		}

		//隐藏提示
		if( MyAwardHintTf[i] != NULL ){
			MyAwardHintTf[i]->SetVisible( !isGotAward );
		}
		//loop all getted awards
		if( isGotAward ){
			//if( (UINT)j >= pAwardData->m_uiFBAwardCount || pAwardData->m_Award[j].isValid != TRUE ){
			if( pAwardData->m_Award[dataIdx].isValid != TRUE ){
				MyBtnAward[i]->SetBool( TEXT("enabled"), true );
				MyBtnAward[i]->SetBool( TEXT("selected"), false );
				MyFBAward[i]->SetVisible( false );
				continue;
			}

			INT rewardCnt = pAwardData->m_Award[dataIdx].uiItemCnt;
			INT itemID = pAwardData->m_Award[dataIdx].uiItemID;
			if( itemID < E_MONEYTYPE_MAX ){//说明是钱
				if( itemID >= E_MONEYTYPE_01 ){
					FString moneyName;
					FString moneyIcon = UITextParser::GetMoneyIconImgAndName( moneyName, itemID );

					FString iconDesc;
					if( rewardCnt >= 1 ){
						iconDesc = moneyName;
						iconDesc += TEXT("X");
						iconDesc += appItoa( rewardCnt );
					}
					//warnf( NAME_Warning, TEXT("===UpdateMyAward->ItemID:%d,Icon:%s"), itemID, *moneyIcon );
					GFXPlayer->SetNoninteractiveIconSlot( pAwardsSlot, itemID, moneyIcon, iconDesc, ESPType_FBAwards );
				}
			}
			else{//此为装备
				pItem = MMOFacade::getSingleton().FindItemTemplate( itemID );
				
				//设置奖品
				FString strName;
				if( pItem != NULL ){
					strName = pItem->GetDisplayName();
				}
				strName += TEXT("X");
				strName += appItoa(rewardCnt);
				GFXPlayer->SetNoninteractiveIconSlotByItem( pAwardsSlot, pItem, strName, ESPType_FBAwards );
			}
			//隐藏抽奖
			//MyFBAward[i]->GetObject("awardMask_mc")->SetVisible( false );
			//屏蔽抽奖
			MyBtnAward[i]->SetBool( TEXT("enabled"), false );
			
			//开始宝箱
			MyBtnAward[i]->SetBool( TEXT("selected"), true );
			//显示奖品
			MyFBAward[i]->SetVisible( true );
			//播放获得奖品动画
			if( !bAwardAnimPlayed[i] ){
				//pAwardsSlot->GotoAndPlayI( 1 );
				MyFBAward[i]->GotoAndPlayI( 1 );
				bAwardAnimPlayed[i] = TRUE;
			}
		}
		else{//no awards,hide it
			//MyFBAward[i]->GetObject("awardMask_mc")->SetVisible( true );
			MyBtnAward[i]->SetBool( TEXT("enabled"), true );
			MyBtnAward[i]->SetBool( TEXT("selected"), false );
			MyFBAward[i]->SetVisible( false );
		}
	}//end of for
}
//
void UMMOUIFBAward::UpdateMemberAward()
{
	UGFxObject* pAwardsMc = NULL;
	FBMemberAwardData *pAwardData = NULL;
	AMMOActor* pMate = NULL;
	bool bIsTeammate = false;
	//all 4 teammate,first one is myself
	UBOOL hasTeammateAwarded = FALSE;
	for( INT i = 1; i < 5; ++i ){
		pAwardsMc = MemFBAwards[i-1];
		pAwardData = MMOFacade::getSingleton().GetFBAward(i);
		//if no data, next loop
		if( pAwardData == NULL ){
			continue;
		}
		//is this player in this FB 
		bIsTeammate = (pAwardData->m_uiMemberID != 0);
		//member portrait and name
		if( bIsTeammate ){
			hasTeammateAwarded = TRUE;
			//Get this player
			pMate = MMOFacade::getSingleton().GetCharacter( pAwardData->m_uiMemberID );
			if( pMate != NULL ){
				INT iPortraitID = 0;
				switch( pMate->GetSex() )
				{
				case EGT_Male: iPortraitID = 2; break;
				case EGT_Female: iPortraitID = 1; break;
				default: iPortraitID = 1; break;
				}
				pAwardsMc->SetVisible( TRUE );
				FString classNameLookupKey = GFXPlayer->GetASHeadIconFrame( pMate->GetClassId(), pMate->GetSex() == EGT_Female );
				pAwardsMc->GetObject("portrait_mc")->GotoAndStop( classNameLookupKey );
				pAwardsMc->GetObject("tf_Name")->SetText( pMate->GetActorName() );
			}
		}
		else{//no this teammate
			pAwardsMc->SetVisible( FALSE );
			//pAwardsMc->GetObject("portrait_mc")->GotoAndStop("none");
			pAwardsMc->GetObject("tf_Name")->SetText( TEXT("") );
			continue;
		}
		//show FB score, if has this teammate
		if( bIsTeammate ){
			pAwardsMc->GetObject("score_mc")->GotoAndStopI( pAwardData->m_uiFBGradedPt+1 );
			//pAwardsMc->GetObject("score_mc")->SetVisible( true );
		}
		else{//没这号人
			pAwardsMc->GetObject("score_mc")->SetVisible( false );
		}
		//show 3 awarded items, if has
		UGFxObject* pAwardsSlot = NULL;
		UGFxObject *pAwardsMny = NULL;
		UItem *pItem = NULL;
		for( INT j = 0; j < MAX_FB_Award; ++j ){
			////奖励钱设空
			//pAwardsMny = pAwardsMc->GetObject( TEXT("awardMny_mc") );
			//pAwardsMny->SetVisible( false );
			//按得到的奖品数量设置
			pAwardsSlot = pAwardsMc->GetObject( FString::Printf( TEXT("awardSlot_mc%d"), j ) );
			if( (UINT)j < pAwardData->m_uiFBAwardCount && bIsTeammate ){//有这人，有这奖品
				pAwardsSlot->SetVisible( true );
				
				INT rewardCnt = pAwardData->m_Award[j].uiItemCnt;
				INT itemID = pAwardData->m_Award[j].uiItemID;
				if( itemID < E_MONEYTYPE_MAX ){//说明是钱
					if( itemID >= E_MONEYTYPE_01 ){
						FString moneyName;
						FString moneyIcon = UITextParser::GetMoneyIconImgAndName( moneyName, itemID );

						FString iconDesc = TEXT("");
						if( rewardCnt > 1 ){
							iconDesc = appItoa( rewardCnt );
							iconDesc += moneyName;
						}
						else{
							iconDesc = moneyName;
						}

						GFXPlayer->SetNoninteractiveIconSlot( pAwardsSlot, itemID, moneyIcon, appItoa(rewardCnt), ESPType_FBAwards );
					}
				}
				else{//此为装备
					pItem = MMOFacade::getSingleton().FindItemTemplate( itemID );

					//设置奖品
					FString strName;
					if( pItem != NULL ){
						strName = pItem->GetDisplayName();
					}
					GFXPlayer->SetNoninteractiveIconSlotByItem( pAwardsSlot, pItem, appItoa(rewardCnt), ESPType_FBAwards );
				}
			}
			else{//没此奖品或是没这号人
				pAwardsSlot->SetVisible( false );
				//SetAwardSlotInfo( pAwardsSlot, NULL, 0 );
			}
		}//end of for 3
	}//end of for 5 teammate awards

	//
	if( MemberInfoMc != NULL ){
		MemberInfoMc->SetVisible( hasTeammateAwarded );
	}
}

//==============================================================================================================================================
void UMMOUIFBAward::InitFBAwardMode()
{
	FBSummaryData *SumData = MMOFacade::getSingleton().GetFBSummary();
	//
	UBOOL bCanFreeGet1 = CheckAwardQualificationAndHint( enumAOGFbAwardType1, FALSE );
	//
	bCanFreeGet2 = CheckAwardQualificationAndHint( enumAOGFbAwardType2, FALSE );
	//
	bCanFreeGet3 = CheckAwardQualificationAndHint( enumAOGFbAwardType3, FALSE );
}

//==============================================================================================================================================
//抽奖按钮被点击
void UMMOUIFBAward::ClickAward( INT iIdx )
{
	UBOOL isOK = CheckAwardQualificationAndHint( iIdx, TRUE );
	if( !isOK ){
		return;
	}

	//send server message
	GetAward( iIdx );
}

//
UBOOL UMMOUIFBAward::CheckAwardQualificationAndHint( INT iIdx, UBOOL isNeedScreenHint )
{
	if( iIdx < 0 || iIdx >= MAX_FB_Award || Player == NULL ){
		return FALSE;
	}

	//FExportMap mapInfo = MMOMapDataManager::getSingleton().GetCurMap();
	FBSummaryData *mySumData = MMOFacade::getSingleton().GetFBSummary();

	MMOMapDataManager &mmmoMapDataMgr = MMOMapDataManager::getSingleton();
	const FDungeonInfo *fbInfo = mmmoMapDataMgr.GetDungeonInfo( mmmoMapDataMgr.GetCurMap().ServerID, mmmoMapDataMgr.GetCurFBDiff() );
	if( fbInfo == NULL ){
		warnf(NAME_Error, TEXT("======!!!!======= CheckQualificationOfAward[GetDungeonInfo(%d, %d)]"), mmmoMapDataMgr.GetCurMap().ServerID, mmmoMapDataMgr.GetCurFBDiff() );
		return FALSE;
	}

	UBOOL canFree = FALSE;
	switch( iIdx )
	{
	//第一个奖
	case enumAOGFbAwardType1:
		{
			canFree = TRUE;
			MyAwardHintTf[enumAOGFbAwardType1]->SetString( TEXT("htmlText"), MMOUI::ParseLocalizedPropertyPath( TEXT( "MMOGame.FBGeneral.FBAwardHint1" ) ) );
		}
		break;
	//第二个奖
	case enumAOGFbAwardType2:
		{
			if( fbInfo->Reward2_free > (INT)mySumData->m_uiGradedPt ){
				INT64 nowMny = Player->GetMoney( E_MONEYTYPE_01 );

				FString textHint = UITextParser::HTMLMoneyIconString( E_MONEYTYPE_01 , fbInfo->Reward2_cost );
				canFree = FALSE;
				MyAwardHintTf[enumAOGFbAwardType2]->SetString( TEXT("htmlText"), textHint );

				//if( fbInfo->Reward2_cost > nowMny ){
				//	if( isNeedScreenHint ){
				//		FString hint = FString::Printf( *MMOUI::ParseLocalizedPropertyPath( TEXT( "MMOGame.FBGeneral.FBGeneral3" ) ), fbInfo->Reward2_cost );
				//		MMOUI::GetUIManager()->delegateAddScreenMessage( hint, MsgInfoType_Table, TEXT( "MMOGame.FBGeneral.FBGeneral3" ));
				//	}

				//	return FALSE;
				//}
			}
			else{
				canFree = TRUE;
				MyAwardHintTf[enumAOGFbAwardType2]->SetString( TEXT("htmlText"), MMOUI::ParseLocalizedPropertyPath( TEXT( "MMOGame.FBGeneral.FBAwardHint1" ) ) );
			}
		}
		break;
	//第三个奖
	case enumAOGFbAwardType3:
		{
			BOOL bVip = ( Player->GetVipType() > 0 );
			if( !bVip ){
				//如果不是Vip
				INT64 nowVipAwardMny = Player->GetMoney( E_MONEYTYPE_02 );
				FString awardHint = UITextParser::HTMLMoneyIconString( E_MONEYTYPE_02 , fbInfo->Reward3_cost );
				canFree = FALSE;
				MyAwardHintTf[enumAOGFbAwardType3]->SetString( TEXT("htmlText"), awardHint );

				//if( fbInfo->Reward3_cost > nowVipAwardMny ){
				//	//非Vip玩家所需金币不够
				//	if( isNeedScreenHint ){
				//		FString hint = MMOUI::ParseLocalizedPropertyPath( TEXT( "MMOGame.FBGeneral.FBAward3Condition" ) );
				//		MMOUI::GetUIManager()->delegateAddScreenMessage( FString::Printf( *hint, fbInfo->Reward3_cost ) ,MsgInfoType_Table,TEXT( "MMOGame.FBGeneral.FBAward3Condition" ));
				//	}
				//	return FALSE;
				//}
			}
			else{
				canFree = TRUE;
				MyAwardHintTf[enumAOGFbAwardType3]->SetString( TEXT("htmlText"), MMOUI::ParseLocalizedPropertyPath( TEXT( "MMOGame.FBGeneral.FBAwardHint1" ) ) );
			}
		}
		break;
	}

	return TRUE;
}
//==============================================================================================================================================
//时间到，打开所有可以打开的奖励
void UMMOUIFBAward::TimeUpToShowAll()
{
	UBOOL bOpened;

	FBSummaryData *mySumData = MMOFacade::getSingleton().GetFBSummary();

	//if not opened this free award1, show award 1
	bOpened = MyBtnAward[0]->GetBool( TEXT("enabled") );
	if( bOpened ){
		GetAward( 0 );
	}

	//if not opened this free award2, show award 3
	MMOMapDataManager &mmmoMapDataMgr = MMOMapDataManager::getSingleton();
	const FDungeonInfo *fbInfo = mmmoMapDataMgr.GetDungeonInfo( mmmoMapDataMgr.GetCurMap().ServerID, mmmoMapDataMgr.GetCurFBDiff() );
	bOpened = MyBtnAward[1]->GetBool( TEXT("enabled") );
	if( bOpened && ( fbInfo && fbInfo->Reward2_free <= (INT)mySumData->m_uiGradedPt ) ){
		GetAward( 1 );
	}

	//if not opened this free award3, show award 3
	bOpened = MyBtnAward[2]->GetBool( TEXT("enabled") );
	BOOL bVip = ( Player != NULL && Player->GetVipType() > 0 );
	if( bOpened && bVip ){
		GetAward( 2 );
	}
	//
	bPlayed = true;
}

//==============================================================================================================================================
void UMMOUIFBAward::GetAward( INT iIdx)
{
	MyClickAwardIdx.Push( iIdx );
	//
	SET_WARN_COLOR(COLOR_CYAN);
	warnf( NAME_Log, TEXT("======!!!!======= [UMMOUIFBAward::GetAward (%d)]"), iIdx );
	//
	CMessageHandler::GetInstance().Send_GetAward( (BYTE)iIdx );
}

//==============================================================================================================================================
void UMMOUIFBAward::Init()
{
	Super::Init();

	//
	bPlayed = false;

	//
	InitFBAwardMc();

	//初始化
	ResetUI();
}

//==============================================================================================================================================
void UMMOUIFBAward::InitFBAwardMc()
{
	//本人名字
	MyName_mc = GetObject( TEXT("tf_myName") );
	//本人头像
	MyPortrait_mc = GetObject( TEXT("ownPortrait_mc") );
	//本人得分
	MyScore_mc = GetObject( TEXT("myScore_mc") );
	//
	MyFBAward[0] = GetObject( TEXT("awardItemAni1_mc") );
	MyFBAward[1] = GetObject( TEXT("awardItemAni2_mc") );
	MyFBAward[2] = GetObject( TEXT("awardItemAni3_mc") );
	MyFBAward[0]->GetObject( TEXT("AnimSlotShow_mc") )->SetInt( TEXT("SlotType") , ESPType_FBAwards );
	MyFBAward[1]->GetObject( TEXT("AnimSlotShow_mc") )->SetInt( TEXT("SlotType") , ESPType_FBAwards );
	MyFBAward[2]->GetObject( TEXT("AnimSlotShow_mc") )->SetInt( TEXT("SlotType") , ESPType_FBAwards );

	//
	MyBtnAward[0] = GetObject( TEXT("FBGetAwardBtn1") );
	MyBtnAward[1] = GetObject( TEXT("FBGetAwardBtn2") );
	MyBtnAward[2] = GetObject( TEXT("FBGetAwardBtn3") );

	MyAwardHintTf[0] = GetObject( TEXT("AwardHintTf1") );
	MyAwardHintTf[1] = GetObject( TEXT("AwardHintTf2") );
	MyAwardHintTf[2] = GetObject( TEXT("AwardHintTf3") );
	//
	MemberInfoMc = GetObject( TEXT("memberInfoMc") );
	MemFBAwards[0] = GetObject( TEXT("member1Award_mc") );
	MemFBAwards[1] = GetObject( TEXT("member2Award_mc") );
	MemFBAwards[2] = GetObject( TEXT("member3Award_mc") );
	MemFBAwards[3] = GetObject( TEXT("member4Award_mc") );

	//
	for( INT i = 0; i < 4; ++i ){
		MemFBAwards[i]->GetObject( TEXT("awardSlot_mc0" ) )->SetFloat( TEXT("EquipID"), 1 );
		MemFBAwards[i]->GetObject( TEXT("awardSlot_mc1" ) )->SetFloat( TEXT("EquipID"), 1 );
		MemFBAwards[i]->GetObject( TEXT("awardSlot_mc2" ) )->SetFloat( TEXT("EquipID"), 1 );
		MemFBAwards[i]->GetObject( TEXT("awardSlot_mc0" ) )->SetInt( TEXT("SlotType") , ESPType_FBAwards );
		MemFBAwards[i]->GetObject( TEXT("awardSlot_mc1" ) )->SetInt( TEXT("SlotType") , ESPType_FBAwards );
		MemFBAwards[i]->GetObject( TEXT("awardSlot_mc2" ) )->SetInt( TEXT("SlotType") , ESPType_FBAwards );
	}
	//CloseFBAwardBtn = GetObject( TEXT("closeBtn_mc" );
	//BackFBSummaryBtn = GetObject( TEXT("backFBSummaryBtn_mc" );
}

//==============================================================================================================================================
void UMMOUIFBAward::ResetUI()
{
	//重置为未开启过开
	bPlayed = false;
	//打开抽奖按钮
	for( INT i = 0; i < MAX_FB_Award; ++i ){
		//重置动画播放
		bAwardAnimPlayed[i] = 0;
		MyFBAward[i]->SetVisible( false );
		MyBtnAward[i]->SetBool( TEXT("enabled"), true );
	}
	//初始化数据
	//InitFBAwardMode();
	//隐藏战友奖品
	FString objName = TEXT("awardSlot_mc");
	for( INT i = 0; i < 4; ++i ){
		for( INT j = 0; j < MAX_FB_Award; ++j ){	
			UGFxObject *obj = MemFBAwards[i]->GetObject(  objName + appItoa( j ) );
			if( obj != NULL ){
				obj->SetVisible( false );
			}
		}
	}

	//MyFBAward[2]->GetObject("awardMask_mc")->SetText( str );
	//隐藏按钮
	//CloseFBAwardBtn->SetVisible( false );
	//BackFBSummaryBtn->SetVisible( false );
}

//==============================================================================================================================================
//开始抽奖（抽奖？）
void UMMOUIFBAward::OpenToPlay( INT iTime )
{
	if( !bPlayed ){
		ResetData();
		//count down
		eventCallASStartPlayCountDown( iTime );
	}

	Show( TRUE );
}

//===============================================================================================================
//===============================================================================================================
void UMMOUIFBAward::ClickGetFBAward( int iIdx )
{
	ClickAward( iIdx );
}

//========================================================================================================
void UMMOUIFBAward::GetFBAward( int iIdx)
{
	ClickAward( iIdx );
}

//========================================================================================================
//Back to FBSummary from FBAward
void UMMOUIFBAward::FBAwardPlayTimeOver()
{
	TimeUpToShowAll();

	//open next window
	UMMOUIFBBattleComfirm *pFBBattleConfirm = (UMMOUIFBBattleComfirm*)MMOUI::FindUIPanelEx( MMOUI::GetUIManager()->Panel_FBEndAll_FBBattleComfirm );
	if( pFBBattleConfirm != NULL ){
		pFBBattleConfirm->OpenFBBattleComfirm();
	}
}
//===============================================================================================================
//===============================================================================================================
