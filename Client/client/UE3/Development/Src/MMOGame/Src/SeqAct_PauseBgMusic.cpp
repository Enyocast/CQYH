#include "..\stdafx.h"
#include "MMOFacade.h"
#include "MMOGuideManager.h"
#include "MMOFacade.h"

IMPLEMENT_CLASS(USeqAct_PauseBgMusic)


void USeqAct_PauseBgMusic::Activated()
{
	MMOFacade::getSingleton().PauseBackSound(bPause);
	Super::Activated();
}
