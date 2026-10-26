#include "stdafx.h"
#include "MMOGameClasses.h"

IMPLEMENT_CLASS(UMMOSoundManager);

UMMOSoundManager* UMMOSoundManager::GetSoundManager()
{
	AMMOGame* game = Cast<AMMOGame>(GWorld->GetGameInfo());
	check(game != 0);
	return game->SoundManager;
}