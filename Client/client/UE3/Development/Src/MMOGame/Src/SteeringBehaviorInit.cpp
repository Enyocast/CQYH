#include "stdafx.h"
#include "MMOCrowd.h"

IMPLEMENT_CLASS(UIMMOSteeringBehaviorInitProc);

IMPLEMENT_CLASS(UMMOSteeringBehaviorInitProc_Alignment);

void UMMOSteeringBehaviorInitProc_Alignment::OnProcess(class UMMOSteeringBehavior* Behavior)
{
	if(on)
	{
		Behavior->AlignmentOn();
	}
	else
	{
		Behavior->AlignmentOff();
	}
}

//------------------------------------------------------------------------

IMPLEMENT_CLASS(UMMOSteeringBehaviorInitProc_Arrive);

void UMMOSteeringBehaviorInitProc_Arrive::OnProcess(class UMMOSteeringBehavior* Behavior)
{
	if(on)
	{
		Behavior->ArriveOn();
	}
	else
	{
		Behavior->ArriveOff();
	}
}

//------------------------------------------------------------------------

IMPLEMENT_CLASS(UMMOSteeringBehaviorInitProc_Cohesion);

void UMMOSteeringBehaviorInitProc_Cohesion::OnProcess(class UMMOSteeringBehavior* Behavior)
{
	if(on)
	{
		Behavior->CohesionOn();
	}
	else
	{
		Behavior->CohesionOff();
	}
}

//------------------------------------------------------------------------

IMPLEMENT_CLASS(UMMOSteeringBehaviorInitProc_Evade);

void UMMOSteeringBehaviorInitProc_Evade::OnProcess(class UMMOSteeringBehavior* Behavior)
{
	if(on)
	{
		UMMOCrowdInstance* inst = Behavior->CrowdInstance->Owner->GetInstanceByID(TargetCrowdInstanceID);
		Behavior->EvadeOn(inst);
	}
	else
	{
		Behavior->EvadeOff();
	}
}

//------------------------------------------------------------------------

IMPLEMENT_CLASS(UMMOSteeringBehaviorInitProc_Flee);

void UMMOSteeringBehaviorInitProc_Flee::OnProcess(class UMMOSteeringBehavior* Behavior)
{
	if(on)
	{
		Behavior->FleeOn();
	}
	else
	{
		Behavior->FleeOff();
	}
}

//------------------------------------------------------------------------

IMPLEMENT_CLASS(UMMOSteeringBehaviorInitProc_Flocking);

void UMMOSteeringBehaviorInitProc_Flocking::OnProcess(class UMMOSteeringBehavior* Behavior)
{
	if(on)
	{
		Behavior->FlockingOn();
	}
	else
	{
		Behavior->FlockingOff();
	}
}

//------------------------------------------------------------------------

IMPLEMENT_CLASS(UMMOSteeringBehaviorInitProc_FollowPath);

void UMMOSteeringBehaviorInitProc_FollowPath::OnProcess(class UMMOSteeringBehavior* Behavior)
{
	if(on)
	{
		Behavior->FollowPathOn();
	}
	else
	{
		Behavior->FollowPathOff();
	}
}

//------------------------------------------------------------------------

IMPLEMENT_CLASS(UMMOSteeringBehaviorInitProc_Hide);

void UMMOSteeringBehaviorInitProc_Hide::OnProcess(class UMMOSteeringBehavior* Behavior)
{
	if(on)
	{
		UMMOCrowdInstance* inst = Behavior->CrowdInstance->Owner->GetInstanceByID(TargetCrowdInstanceID);
		Behavior->HideOn(inst);
	}
	else
	{
		Behavior->HideOff();
	}
}

//------------------------------------------------------------------------

IMPLEMENT_CLASS(UMMOSteeringBehaviorInitProc_Interpose);

void UMMOSteeringBehaviorInitProc_Interpose::OnProcess(class UMMOSteeringBehavior* Behavior)
{
	if(on)
	{
		UMMOCrowdInstance* inst1 = Behavior->CrowdInstance->Owner->GetInstanceByID(TargetCrowdInstanceID1);
		UMMOCrowdInstance* inst2 = Behavior->CrowdInstance->Owner->GetInstanceByID(TargetCrowdInstanceID2);
		Behavior->InterposeOn(inst1, inst2);
	}
	else
	{
		Behavior->InterposeOff();
	}
}

//------------------------------------------------------------------------

IMPLEMENT_CLASS(UMMOSteeringBehaviorInitProc_ObstacleAvoidance);

void UMMOSteeringBehaviorInitProc_ObstacleAvoidance::OnProcess(class UMMOSteeringBehavior* Behavior)
{
	if(on)
	{
		Behavior->ObstacleAvoidanceOn();
	}
	else
	{
		Behavior->ObstacleAvoidanceOff();
	}
}

//------------------------------------------------------------------------

IMPLEMENT_CLASS(UMMOSteeringBehaviorInitProc_OffsetPursuit);

void UMMOSteeringBehaviorInitProc_OffsetPursuit::OnProcess(class UMMOSteeringBehavior* Behavior)
{
	if(on)
	{
		UMMOCrowdInstance* inst = Behavior->CrowdInstance->Owner->GetInstanceByID(TargetCrowdInstanceID);
		Behavior->OffsetPursuitOn(inst, Offset);
	}
	else
	{
		Behavior->OffsetPursuitOff();
	}
}

//------------------------------------------------------------------------

IMPLEMENT_CLASS(UMMOSteeringBehaviorInitProc_Pursuit);

void UMMOSteeringBehaviorInitProc_Pursuit::OnProcess(class UMMOSteeringBehavior* Behavior)
{
	if(on)
	{
		UMMOCrowdInstance* inst = Behavior->CrowdInstance->Owner->GetInstanceByID(TargetCrowdInstanceID);
		Behavior->PursuitOn(inst);
	}
	else
	{
		Behavior->PursuitOff();
	}
}

//------------------------------------------------------------------------

IMPLEMENT_CLASS(UMMOSteeringBehaviorInitProc_Seek);

void UMMOSteeringBehaviorInitProc_Seek::OnProcess(class UMMOSteeringBehavior* Behavior)
{
	if(on)
	{
		Behavior->SeekOn();
	}
	else
	{
		Behavior->SeekOff();
	}
}

//------------------------------------------------------------------------

IMPLEMENT_CLASS(UMMOSteeringBehaviorInitProc_Separation);

void UMMOSteeringBehaviorInitProc_Separation::OnProcess(class UMMOSteeringBehavior* Behavior)
{
	if(on)
	{
		Behavior->SeparationOn();
	}
	else
	{
		Behavior->SeparationOff();
	}
}

//------------------------------------------------------------------------

IMPLEMENT_CLASS(UMMOSteeringBehaviorInitProc_WallAvoidance);

void UMMOSteeringBehaviorInitProc_WallAvoidance::OnProcess(class UMMOSteeringBehavior* Behavior)
{
	if(on)
	{
		Behavior->WallAvoidanceOn();
	}
	else
	{
		Behavior->WallAvoidanceOff();
	}
}

//------------------------------------------------------------------------

IMPLEMENT_CLASS(UMMOSteeringBehaviorInitProc_Wander);

void UMMOSteeringBehaviorInitProc_Wander::OnProcess(class UMMOSteeringBehavior* Behavior)
{
	if(on)
	{
		Behavior->WanderOn();
	}
	else
	{
		Behavior->WanderOff();
	}
}

//------------------------------------------------------------------------

