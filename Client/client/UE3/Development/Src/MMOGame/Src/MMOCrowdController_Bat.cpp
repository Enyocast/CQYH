#include "stdafx.h"
#include "MMOCrowd.h"

IMPLEMENT_CLASS(UMMOCrowdController_Bat);

void UMMOCrowdController_Bat::PostInitCrowdInstances()
{
	AMMOCrowdSystem* CrowdSys = Cast<AMMOCrowdSystem>(GetOwner());

	if(!CrowdSys)
	{
		return;
	}

	for (INT i = 1;  i < CrowdSys->CrowdInstanceData.Num(); ++i)
	{
		UMMOCrowdInstance* inst = CrowdSys->CrowdInstanceData(i);

		if((i - 1) % 8 != 0)
		{
			inst->SteeringBehavior->PursuitOn(CrowdSys->CrowdInstanceData((i - 1) / 8));
		}
		else
		{
			inst->SteeringBehavior->PursuitOn(CrowdSys->CrowdInstanceData(i - 1));
		}
	}
}
