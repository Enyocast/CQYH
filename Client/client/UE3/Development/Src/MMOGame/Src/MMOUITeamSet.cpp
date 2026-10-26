#include "stdafx.h"
#include "MMOGameUIClasses.h"
#include "MMOFacade.h"
#include "CommonGameEvents.h"
#include "TeamManager.h"
#include "MMOMsgBoxManager.h"
#include "MMOMapDataManager.h"
#include "FSMIO.h"


IMPLEMENT_CLASS(UMMOUITeamSet)



void UMMOUITeamSet::OnNativeGameEvent(struct MMOGameEvent* evt)
{
	
}


void UMMOUITeamSet::Init()
{
	Super::Init();

	
}

void UMMOUITeamSet::ASTeamSettingAssignTyp(INT index)
{
	if (TeamManager::getSingleton().GetTargetRoleTeam())
	{
		CMessageHandler::GetInstance().Send_TeamInvite(TeamManager::getSingleton().GetTeamTargetRoldId(),index);
	}
	else
	{
		CMessageHandler::GetInstance().Send_TeamInvite(Player->ServerID,index);
	}

	TeamManager::getSingleton().ResetTeamTarget();
	
	//CMessageHandler::GetInstance().Send_ChangeTeamActivity(TeamManager::getSingleton().GetTeamTargetId(), TeamManager::getSingleton().GetTeamTargetType());
	this->SetVisible(FALSE);
}


void UMMOUITeamSet::PostOnShow(UBOOL show)
{
	Super::PostOnShow(show);
	this->SetVisible(show);
	eventCallRestTeamSet();
}

