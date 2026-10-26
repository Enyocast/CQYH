#include "stdafx.h"
#include "MMOGameUIClasses.h"
#include "MMOFacade.h"
#include "RankListManager.h"
#include "MMOChatManager.h"
#include "MMOGuildManager.h"
#include "MMOArenaManager.h"
#include "MasterStudentManager.h"
#include "../net/message_handler_RankList.h"
#include "MMOAchievementData.h"


IMPLEMENT_CLASS(UMMOUIHeroRank)

#define SHOW_TIME 0.3

//==================================================Total()====================================================== 
void UMMOUIHeroRank::NativeInitLoad()
{
	UMMOUIBase::NativeInitLoad();
	
}

void UMMOUIHeroRank::NativeInitOnce()
{
	UMMOUIBase::NativeInitOnce();
	check(NULL == EventAdapter);
	if (NULL == EventAdapter)
	{
		TArray<EGameEvent> evts;
		evts.AddItem(GameEvent_RankList);
		evts.AddItem(GameEvent_RankList_RefreshList);
		EventAdapter = new TGameEventAdapter<UMMOUIHeroRank>(this, evts);
	}

	if( GFXPlayer ){
		GFXPlayer->AddBeforeViewUpdateDelegate( FScriptDelegate(this, TEXT("BeforeViewUpdate")) );
	}
	refresh = FALSE;
}

void UMMOUIHeroRank::PostOnShow(UBOOL v)
{
	UMMOUIBase::PostOnShow(v);
	if (v)
	{
		CMessageHandler::GetInstance().Send_QueryRanklist((INT32)rlActivity01, 0);
		RankListManager::getSingleton().SetPageIndex(rlActivity01, 0);
		FString myRank = FString::FormatAsNumber(RankListManager::getSingleton().GetMyHeroNum());
		eventCallUCUpdateMyHeroRank(myRank);
	
	}
}

void UMMOUIHeroRank::OnNativeGameEvent(struct MMOGameEvent* evt)
{
	if (NULL != evt)
	{
		switch(evt->GetEventType())
		{
		case GameEvent_RankList:
			{
				UpdateRankList();
			}
			break;
		case GameEvent_RankList_RefreshList:
			{
				refresh = TRUE;
			}
			break;
		}
	}
}

void UMMOUIHeroRank::UpdateRankList()
{
	INT myRank = RankListManager::getSingleton().GetSelfRank();
	UpdateHeroRankList();
	UpdateMaxPage(RankListManager::getSingleton().GetPageIndex(),RankListManager::getSingleton().GetPageTotal());

	FString strRank = TEXT("");
	if (0 == myRank)
	{
		strRank = MMOUI::ParseLocalizedPropertyPath(TEXT("MMOGame.Rank.NotRank"));
		eventCallUpdateMyRank(strRank,0,0);
	}
	else
	{
		strRank = FString::Printf(*MMOUI::ParseLocalizedPropertyPath(TEXT("MMOGame.Rank.RankIndex")), RankListManager::getSingleton().GetSelfRank());
		eventCallUpdateMyRank(strRank,RankListManager::getSingleton().GetSelfRank(),RankListManager::getSingleton().GetSelfLastRank());
	}
}
void UMMOUIHeroRank::UpdateHeroRankList()
{
	UGFxObject* dataProvider = GFXPlayer->CreateArray();
	if(NULL == dataProvider)
		return;

	//dataProvider->SetElementInt(0, (INT32)rlActivity01);

	INT index = 0;
	const RankVec& rankVec = RankListManager::getSingleton().GetRankVec();
	for (RankVec::const_iterator it = rankVec.begin(); it != rankVec.end(); ++it)
	{
		PlayerBaseInfo* pPlayerBaseInfo = MMOFacade::getSingleton().RequestPlayerBaseInfo((*it)->Id);
		if ( pPlayerBaseInfo )
		{
			//if ((*it)->Value <= 0)
				//continue;

			UGFxObject* itemObj = GFXPlayer->CreateObject(TEXT("ActionScript3.RankList.ActiveBZItemData"));
			itemObj->SetInt(TEXT("Id"), (*it)->Id);
			INT currentIndex = index + RankListManager::getSingleton().GetPageIndex()*MAX_RANK_NODE_NUM_PER_PAGE;
			itemObj->SetString(TEXT("RankIndex"), appItoa(currentIndex));
			itemObj->SetString(TEXT("RoleName"), pPlayerBaseInfo->_RoleName);
			FString Job = MMOUI::ParseLocalizedPropertyPath( FString("MMOGame.School.SchoolName") + appItoa(pPlayerBaseInfo->_RoleClass));
			itemObj->SetString(TEXT("Job"), Job);
			//itemObj->SetInt(TEXT("Ranking"),GetRanking((*it)->LastRank,currentIndex));
			BOOL isPlayer = MMOFacade::getSingleton().GetMainPlayer()->ServerID == (*it)->Id?TRUE:FALSE;
			itemObj->SetBool(TEXT("IsPlayer"),isPlayer);
			itemObj->SetInt(TEXT("num"),(*it)->Value);
			dataProvider->SetElementObject(index, itemObj);
			index++;
		}
	}
	eventCallUCUpdateHeroRankData(dataProvider);
}

void UMMOUIHeroRank::UpdateMaxPage(INT curPage, INT maxPage)
{
	UBOOL preEnable = TRUE;
	UBOOL nextEnable = TRUE;
	if( curPage == 0 )
	{
		preEnable = FALSE;
	}
	if( curPage + 1 >= maxPage )
	{
		nextEnable = FALSE;
	}

	if( GFXPlayer )
	{
		UGFxObject* data = GFXPlayer->CreateObject( TEXT("Object") );
		if(data)
		{
			data->SetBool( TEXT("preEnable") , preEnable );
			data->SetBool( TEXT("nextEnable") , nextEnable );
			data->SetString( TEXT("PageNumTxt") , FString::Printf( TEXT("%d/%d") , curPage + 1 , maxPage ) );
			data->SetInt(TEXT("MaxPage"),maxPage);
			eventCallUpdateHeroRankPage( data );
		}
	}
}

void UMMOUIHeroRank::BeforeViewUpdate(float DeltaTime)
{
	if ( this->GetVisible())
	{
		if ( currentTime >= SHOW_TIME  && refresh)
		{
			currentTime = 0;
			refresh = FALSE;
			UpdateHeroRankList();
		}

		if (currentRefreshTime >= RankListManager::getSingleton().getHeroRankMaxTime())
		{
			CMessageHandler::GetInstance().Send_QueryRanklist((INT32)rlActivity01, RankListManager::getSingleton().GetPageIndex());
			currentRefreshTime = 0;
		}

		currentTime += DeltaTime;
		currentRefreshTime += DeltaTime;
	}
}

void UMMOUIHeroRank::ASPrevHeroRankPageClick()
{
	INT nCurPage = RankListManager::getSingleton().GetPageIndex();
	if (nCurPage-- > 0)
	{
		RANK_LIST totalType = RankListManager::getSingleton().GetTotalType();
		RankListManager::getSingleton().SetPageIndex(totalType, nCurPage);
		CMessageHandler::GetInstance().Send_QueryRanklist(totalType, nCurPage);
	}
}

void UMMOUIHeroRank::ASNextHeroRankPageClick()
{
	INT nCurPage = RankListManager::getSingleton().GetPageIndex();
	if (++nCurPage <= RankListManager::getSingleton().GetPageTotal() - 1)
	{
		RANK_LIST totalType = RankListManager::getSingleton().GetTotalType();
		RankListManager::getSingleton().SetPageIndex(totalType, nCurPage);
		CMessageHandler::GetInstance().Send_QueryRanklist(totalType, nCurPage);
	}
}