
#include "MMOHintButtonCommand.h"
#include "MMOArenaManager.h"
#include "MMOFacade.h"


void MMOHintButtonCommand_ArenaQueue::Click()
{
	MMOUI::FindUIPanel( TEXT("ArenaQueue") )->ToogleVisible();
	//MMOArenaManager::getSingleton().OpenArenaQueue(0);
}