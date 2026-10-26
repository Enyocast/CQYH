#include "..\stdafx.h"
#include "MMOFacade.h"
#include "MMOWeatherManager.h"
#include "EngineInterpolationClasses.h"

IMPLEMENT_CLASS(USeqEvent_DayTimeChanged);


void USeqEvent_DayTimeChanged::Activated()
{
    Super::Activated();
}

void USeqEvent_DayTimeChanged::ActivatePlan()
{
	INT curTime = (INT)(MMOWeatherManager::getSingleton().GetCurTime());
	if (VariableLinks.Num() > 0)
	{
		for (INT i = 0; i < VariableLinks(0).LinkedVariables.Num(); ++i)
		{
			USeqVar_Int* var = Cast<USeqVar_Int>(VariableLinks(0).LinkedVariables(i));
			if (var)
			{
				if (curTime == var->IntValue)
				{
					ForceActivateOutput(0);
					break;
				}
			}
		}
	}
}

void USeqEvent_DayTimeChanged::ActivateDay()
{
	ForceActivateOutput(1);
}

void USeqEvent_DayTimeChanged::ActivateDayToNight()
{
	ForceActivateOutput(2);
}

void USeqEvent_DayTimeChanged::ActivateNight()
{
	ForceActivateOutput(3);
}

void USeqEvent_DayTimeChanged::ActivateNightToDay()
{
	ForceActivateOutput(4);
}