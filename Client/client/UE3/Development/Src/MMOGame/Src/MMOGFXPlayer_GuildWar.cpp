#include "stdafx.h"
#include "MMOGameUIClasses.h"
#include "MMOFacade.h"
#include "MMOGuildManager.h"

IMPLEMENT_CLASS(UMMOGFXPlayer_GuildWar)

void UMMOGFXPlayer_GuildWar::PostAdvance(FLOAT dt)
{
}

void UMMOGFXPlayer_GuildWar::Init()
{
	Super::Init();
	check(FALSE && "UMMOGFXPlayer_GuildWar::Init()");
	//MMOUI::RegisterMoviePlayer(this, MMOUI::GetUIManager()->MoviePlayer_GuildWar);
}

void UMMOGFXPlayer_GuildWar::UnInit()
{
	Super::UnInit();
}

void UMMOGFXPlayer_GuildWar::ASJoinWar()
{
	GuildBaseInfo baseInfo = MMOGuildData::getSingleton().GetGuildBaseInfo();
	if (baseInfo.Id > 0)
	{
		CMessageHandler::GetInstance().Send_EnterGuildMap(GUILD_ENTER_OWNER, baseInfo.Id);
	}
}