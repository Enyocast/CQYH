#include "stdafx.h"
#include "FSMIO.h"
#include "MMOGuildData.h"
#include "MMOGuildManager.h"
#include "MMOMapDataManager.h"

void AMMOVolume_GuildBattle::OnActive(class AMMOActor* actor,UBOOL bOn)
{
	// fix bug  #23525
	// todo:12月10日测试前发现在公会属地里也有这个Volume，
	// 但是不确定服务器是不是在用这个Volume的数据，所以就没让LD删掉，客户端临时保护下
	INT curMapId = MMOMapDataManager::getSingleton().GetCurMap().ServerID;
	if (curMapId != SABAC_MAP_ID)
	{
		return;
	}

	if (actor && actor->IsA(AMMOPlayer::StaticClass()))
	{
		if (bOn)
		{
			actor->inSabacZoneCount ++;
		} 
		else
		{ 
			actor->inSabacZoneCount --;
		}

		MMOUI::GetUIManager()->delegateUpdateHintText(actor);

		if (actor->IsMainPlayer())
		{
			// 缺陷：#14676
			if (MMOGuildManager::getSingleton().GetSabacState() > 0)
			{
				FString curSabacOccupyGuildName = TEXT("");
				MMOGuildManager::getSingleton().GetSabacOccupyGuildName(curSabacOccupyGuildName);

				UMMOUIGuildWarHintPanel* panel = (UMMOUIGuildWarHintPanel*)MMOUI::FindUIPanelEx(MMOUI::GetUIManager()->Panel_Guild_WarHint);
				if (panel)
				{
					AMMOPlayer* mainPlayer = MMOFacade::getSingleton().GetMainPlayer();
					//panel->Show(mainPlayer != NULL && mainPlayer->inSabacZoneCount > 0);
					panel->Show(FALSE);
					panel->UpdateGuildWarHintInfo(TEXT(""), curSabacOccupyGuildName, TEXT("争霸战结束还有:"), MMOGuildManager::getSingleton().GetGuildWarTime());
				}
			}
		}
	}
}