#include "stdafx.h"
#include "MMOGameUIClasses.h"
#include "MMOFacade.h"
#include "MMOArenaManager.h"

IMPLEMENT_CLASS(UMMOGFXPlayer_RankList)
IMPLEMENT_CLASS(UMMOUIRankConfigPanel)

void UMMOGFXPlayer_RankList::Init()
{
	Super::Init();

	check(FALSE && "UMMOGFXPlayer_RankList::Init()");
	//MMOUI::RegisterMoviePlayer(this, MMOUI::GetUIManager()->MoviePlayer_RankList );
}

void UMMOUIRankConfigPanel::OnTournamentConfigClick(INT Id)
{
	//const ArenaTeamInfo* pArenaTeamInfo = MMOArenaManager::getSingleton().FindAreanTeam(Id);
	//if (NULL == pArenaTeamInfo)
	//{
	//	if(Id > 0)
	//		CMessageHandler::GetInstance().Send_RequestBattleTeamInfo(Id);
	//}
	//else
	//{
	//	UGFxObject* dataProvider = GFXPlayer->CreateArray();
	//	ASSERT_CHECK_ERROR_RETURN(dataProvider);
	//	INT index = 0;
	//	ArenaTeamMemBaseInfoVec::const_iterator it = pArenaTeamInfo->ArenaMemBaseInfoVec.begin();
	//	while (it != pArenaTeamInfo->ArenaMemBaseInfoVec.end())
	//	{
	//		UGFxObject* itemObj = GFXPlayer->CreateObject(TEXT("ActionScript3.RankList.ConfigItemListData"));
	//		itemObj->SetString(TEXT("Name"), UTF8_TO_TCHAR(it->szRoleName));
	//		FString Job = MMOUI::ParseLocalizedPropertyPath( FString("MMOGame.School.SchoolName") + appItoa(it->byClass));
	//		itemObj->SetString(TEXT("Job"), Job);
	//		itemObj->SetString(TEXT("Level"), appItoa(it->byLevel));
	//		dataProvider->SetElementObject(index++, itemObj);
	//		++it;
	//	}
	//	eventCallUpdateRankConfigListData(dataProvider);
	//	Show(TRUE);
	//}
}