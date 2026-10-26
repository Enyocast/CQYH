#include "stdafx.h"
#include "MMOGameUIClasses.h"
#include "MMOFacade.h"
#include "MMOJourneyManager.h"
#include "UMMOUIJourneyViewPanel.h"

IMPLEMENT_CLASS(UMMOGFXPlayer_JourneyTrace)

void UMMOGFXPlayer_JourneyTrace::Init()
{
	Super::Init();
	check(FALSE && "UMMOGFXPlayer_JourneyTrace::Init()");
	//MMOUI::RegisterMoviePlayer(this, MMOUI::GetUIManager()->MoviePlayer_JourneyTrace);
}


void UMMOGFXPlayer_JourneyTrace::UnInit()
{
	Super::UnInit();
}

void UMMOGFXPlayer_JourneyTrace::ASGotoChapter(int journeyId)
{
	if (_JourneyTracePanel)
	{
		_JourneyTracePanel->_CurJourneyId = journeyId;
		_JourneyTracePanel->UpdateJourneyTraceInfo(journeyId, JT_STORY);
	}
}

void UMMOGFXPlayer_JourneyTrace::ASUpdateNPCTips(int index)
{
	if (_JourneyTracePanel)
	{
		_JourneyTracePanel->PlayJourneySound(index);
	}
}

void UMMOGFXPlayer_JourneyTrace::ASShowAwardsPanel(int journeyId)
{
	JourneyData data;
	if (MMOJourneyData::getSingleton().GetJourneyData(journeyId, data))
	{
		ReputationTemp* reputationTemp = MMOFacade::getSingleton().GetReputationTempByForceID(data.ForceId);
		if (reputationTemp)
		{
			int curReputation = 0;
			int minReputation = 0;
			int maxReputation = 1;
			if (reputationTemp->ListLevel > 0)
			{
				curReputation = MMOFacade::getSingleton().GetPlayerReputation(MMOFacade::getSingleton().GetMainPlayer(), reputationTemp->ForceID);
				minReputation = reputationTemp->InitValue;
				maxReputation = reputationTemp->MaxValue;
			}

			if (curReputation >= maxReputation)
			{
				if (MMOFacade::getSingleton().GetPlayerAwardState(MMOFacade::getSingleton().GetMainPlayer(), reputationTemp->ForceID))
				{
					UMMOUIJourneyViewPanel* panel = (UMMOUIJourneyViewPanel*)MMOUI::FindUIPanelEx(MMOUI::GetUIManager()->Panel_JourneyView);
					if (panel)
					{
						panel->SetCurJourneyId(journeyId);
						panel->Show(TRUE);
					}
				}
				else
				{
					CMessageHandler::GetInstance().Send_ReceiveReputationAward(data.ForceId);
				}
			}
			else
			{
				UMMOUIJourneyViewPanel* panel = (UMMOUIJourneyViewPanel*)MMOUI::FindUIPanelEx(MMOUI::GetUIManager()->Panel_JourneyView);
				if (panel)
				{
					panel->SetCurJourneyId(journeyId);
					panel->Show(TRUE);
				}
			}
		}
	}
}

void UMMOGFXPlayer_JourneyTrace::ASSetCurItemState(int journeyType, UBOOL expand)
{
	if (_JourneyTracePanel)
	{
		if (expand)
		{
			if (_JourneyTracePanel->_CurExpandType != journeyType)
			{
				_JourneyTracePanel->_CurExpandType = journeyType;
			}
		}
		else
		{
			if (_JourneyTracePanel->_CurExpandType == journeyType)
			{
				_JourneyTracePanel->_CurExpandType = -1;
			}
		}
	}
}
