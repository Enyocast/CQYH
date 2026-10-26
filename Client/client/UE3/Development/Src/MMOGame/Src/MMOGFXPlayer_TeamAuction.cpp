#include "stdafx.h"
#include "MMOGameUIClasses.h"
#include "MMOFacade.h"
#include "TeamManager.h"

IMPLEMENT_CLASS(UMMOGFXPlayer_TeamAuction)


void UMMOGFXPlayer_TeamAuction::Init()
{
	Super::Init();

	check(FALSE && "UMMOGFXPlayer_TeamAuction::Init()");
	//MMOUI::RegisterMoviePlayer(this, MMOUI::GetUIManager()->MoviePlayer_TeamAuction);
}

void UMMOGFXPlayer_TeamAuction::UnInit()
{
	Super::UnInit();

	//FScriptDelegate nullDelgate(EC_EventParm);
	//MMOUI::GetUIManager()->SetInviteAddTeamDelegate(nullDelgate);
	//MMOUI::GetUIManager()->SetLeaveTeamDelegate(nullDelgate);
	//MMOUI::GetUIManager()->SetMoveLeaderDelegate(nullDelgate);
	//MMOUI::GetUIManager()->SetInviteTeamRequestDelegate(nullDelgate);
	//MMOUI::GetUIManager()->SetAddTeamRequestDelegate(nullDelgate);
}

void UMMOGFXPlayer_TeamAuction::ASTeamAuctionBid( INT bidMoney )
{
	if(TeamAuction)
	{
		TeamAuction->AuctionBid(bidMoney);
	}
}

void UMMOGFXPlayer_TeamAuction::ASTeamAuctionGiveup()
{
	//if(TeamAuction)
	//{
	//	TeamAuction->AuctionGiveupCurItem();
	//}
	TeamManager::getSingleton().RequestGiveUpCurrentItem();
}

void UMMOGFXPlayer_TeamAuction::ASTeamAuctionClickItemList()
{
	MMOUI::GetUIManager()->ToggleShowPanelEx( MMOUI::GetUIManager()->Panel_TeamAuctionList , TEXT("") );
}

void UMMOGFXPlayer_TeamAuction::ASTeamAuctionClickBidMoneyUp( INT bidMoney )
{
	if(TeamAuction)
	{
		TeamAuction->AuctionBidUp(bidMoney);
	}
}

void UMMOGFXPlayer_TeamAuction::ASTeamAuctionClickBidMoneyDown( INT bidMoney )
{
	if(TeamAuction)
	{
		TeamAuction->AuctionBidDown(bidMoney);
	}
}

void UMMOGFXPlayer_TeamAuction::ASTeamAuctionGiveUpAll()
{
	TeamManager::getSingleton().RequestGiveUpAll();
}

void UMMOGFXPlayer_TeamAuction::ASTeamAuctionListGiveUp( INT index )
{
	TeamManager::getSingleton().RequestGiveUp( index );
}