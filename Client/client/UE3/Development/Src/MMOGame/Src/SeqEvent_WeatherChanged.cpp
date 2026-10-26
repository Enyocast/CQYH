#include "..\stdafx.h"
#include "MMOFacade.h"
#include "MMOWeatherManager.h"

IMPLEMENT_CLASS(USeqEvent_WeatherChanged);

void USeqEvent_WeatherChanged::Activated()
{
	UINT8 curWeatherType = MMOWeatherManager::getSingleton().GetCurWeatherType();
	if (curWeatherType > swtInvalid && curWeatherType < swtTotal)
	{
		ForceActivateOutput(curWeatherType);
	}

    Super::Activated();
}