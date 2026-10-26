#include "stdafx.h"
#include "MMOGameUIClasses.h"
#include "MMOFacade.h"
#include "TeamManager.h"

IMPLEMENT_CLASS(UMMOGFXPlayer_Team)


void UMMOGFXPlayer_Team::Init()
{
	Super::Init();

	check(FALSE && "UMMOGFXPlayer_Team::Init()");
	//MMOUI::RegisterMoviePlayer(this, MMOUI::GetUIManager()->MoviePlayer_Team);
}

void UMMOGFXPlayer_Team::UnInit()
{
	Super::UnInit();

	FScriptDelegate nullDelgate(EC_EventParm);
	//MMOUI::GetUIManager()->SetInviteAddTeamDelegate(nullDelgate);
	//MMOUI::GetUIManager()->SetLeaveTeamDelegate(nullDelgate);
	//MMOUI::GetUIManager()->SetMoveLeaderDelegate(nullDelgate);
	//MMOUI::GetUIManager()->SetInviteTeamRequestDelegate(nullDelgate);
	//MMOUI::GetUIManager()->SetAddTeamRequestDelegate(nullDelgate);
}

void UMMOGFXPlayer_Team::ASAutoTeam( UBOOL sel )
{
	TeamManager::getSingleton().setAutoTeam(sel);

	//
	MMOUI::GetUIManager()->delegateHideTips();
}

//========================================================================================================
void UMMOGFXPlayer_Team::ASTeamMemberRightClick( INT x , INT y , INT index )
{	
	MMOUI::GetUIManager()->delegateOpenRClickMenu( ERCMType_TeamMember, x , y , 0 , "" , index );
}


void UMMOGFXPlayer_Team::ASClickChangeTeamTarget()
{
	MMOUI::GetUIManager()->ShowPanelEx(MMOUI::GetUIManager()->Panel_TeamTarget, TRUE, "");
}

void UMMOGFXPlayer_Team::ASClickClearTeamTarget()
{
	if(TeamManager::getSingleton().HasTeam())
	{
		CMessageHandler::GetInstance().Send_ChangeTeamActivity(-1, etaatInvalid);
	}
	else
	{
		TeamManager::getSingleton().SetTeamTargetId(-1);
		MMOGameEvent_TeamCommon evt(MMOGameEvent_TeamCommon::ETeamEventType_TargetChange);
		MMOUI::PostGameEvent(&evt);
	}
}


void UMMOGFXPlayer_Team::ASClickShowTeamInvite()
{
	if(TeamManager::getSingleton().HasTeam())
		MMOUI::GetUIManager()->ShowPanelEx(MMOUI::GetUIManager()->Panel_TeamInvite, TRUE, "");
	else
	{
		MMOUI::GetUIManager()->delegateAddScreenMessage(MMOUI::ParseLocalizedPropertyPath(TEXT("MMOErrorInfo.ERROR_CODE_DEF.errTeamNotInTeam")),MsgInfoType_Table,TEXT("MMOErrorInfo.ERROR_CODE_DEF.errTeamNotInTeam"));
	}
}

void UMMOGFXPlayer_Team::ASClickSelectPlayer(int playerId)
{
	TeamManager::getSingleton().AddInvitedPlayer(playerId);
}

void UMMOGFXPlayer_Team::ASClickUnSelectPlayer(int playerId)
{
	TeamManager::getSingleton().RemoveInvitedPlayer(playerId);
}

void UMMOGFXPlayer_Team::ASShowInviteFriendList()
{
	if(Team_Invite)
	{
		Team_Invite->UpdateFriendsList();
	}
}

void UMMOGFXPlayer_Team::ASShowInviteRecentList()
{
	if(Team_Invite)
	{
		Team_Invite->UpdateRecentsList();
	}
}

void UMMOGFXPlayer_Team::ASShowInviteGuiderList()
{
	if(Team_Invite)
	{
		Team_Invite->UpdateGuildsList();
	}
}

void UMMOGFXPlayer_Team::ASClickInviteOk()
{
	TeamManager::getSingleton().InvitePlayers();
	MMOUI::GetUIManager()->ShowPanelEx(MMOUI::GetUIManager()->Panel_TeamInvite, FALSE, "");
}

void UMMOGFXPlayer_Team::ASClickInviteCancel()
{
	MMOUI::GetUIManager()->ShowPanelEx(MMOUI::GetUIManager()->Panel_TeamInvite, FALSE, "");
}

void UMMOGFXPlayer_Team::ASClickChangeTargetOk(INT targetType, INT targetId)
{
	if(targetId >= 0 && targetType >= 0)
	{
		if(TeamManager::getSingleton().HasTeam())
		{
			CMessageHandler::GetInstance().Send_ChangeTeamActivity(targetId, targetType + 1);
		}
		else
		{
			TeamManager::getSingleton().SetTeamTargetType(targetType + 1);
			TeamManager::getSingleton().SetTeamTargetId(targetId);
			MMOGameEvent_TeamCommon evt(MMOGameEvent_TeamCommon::ETeamEventType_TargetChange);
			MMOUI::PostGameEvent(&evt);
		}
		
	}
	MMOUI::GetUIManager()->ShowPanelEx(MMOUI::GetUIManager()->Panel_TeamTarget, FALSE, "");
}

void UMMOGFXPlayer_Team::ASCancelChangeTarget()
{
	MMOUI::GetUIManager()->ShowPanelEx(MMOUI::GetUIManager()->Panel_TeamTarget, FALSE, "");
}

void UMMOGFXPlayer_Team::ASShowActivityFBTargetList()
{
	if(Team_TargetChange)
	{
		Team_TargetChange->UpdateTeamTargetListActivityFB();
	}
}

void UMMOGFXPlayer_Team::ASShowActivityTargetList()
{
	if(Team_TargetChange)
	{
		Team_TargetChange->UpdateTeamTargetListActivity();
	}
}

void UMMOGFXPlayer_Team::ASShowFBTargetList(INT nDifficulty)
{
	if(Team_TargetChange)
	{
		Team_TargetChange->UpdateTeamTargetListFB(nDifficulty);
	}
}


void UMMOGFXPlayer_Team::ASTeamAuctionLimitChange( INT sel )
{
	
	if( TeamManager::getSingleton().HasTeam() && TeamManager::getSingleton().IsTeamLeader() )
	{
		INT colorLimit = TeamManager::getSingleton().GetTeamAuctionItemColorByIdx( sel );
		TeamManager::getSingleton().SendOperateTeam( TeamManager::getSingleton().GetAssignType() , TeamManager::getSingleton().GetMemberLimit() , TeamManager::getSingleton().GetTeamName() , colorLimit );
	}
}