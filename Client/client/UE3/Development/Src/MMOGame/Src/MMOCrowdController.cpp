#include "stdafx.h"
#include "MMOCrowd.h"

IMPLEMENT_CLASS(UMMOCrowdController);

void UMMOCrowdController::PostInitCrowdInstances()
{
}


void UMMOCrowdController::NativePostInitCrowdInstance()
{
	PostInitCrowdInstances();
}
//------------------------------------------------------------------------
void UMMOCrowdController::Attach()
{
	Super::Attach();

	AMMOCrowdSystem* CrowdSys = Cast<AMMOCrowdSystem>(GetOwner());

	if(!CrowdSys)
	{
		return;
	}
	
	if(!CrowdSys->CrowdInstanceConfig)
	{
		CrowdSys->CrowdInstanceConfig =
			ConstructObject<UMMOCrowdInstance>(UMMOCrowdInstance::StaticClass(), CrowdSys, NAME_None, RF_Public);
		
		CrowdSys->CrowdInstanceConfig->SteeringBehavior =
			ConstructObject<UMMOSteeringBehavior>(UMMOSteeringBehavior::StaticClass(), CrowdSys->CrowdInstanceConfig, NAME_None, RF_Public);
	}

	CrowdSys->eventPreInitCrowdInstance();
	eventPostBeginPlay();


	CrowdSys->CrowdInstanceData.Empty();
	CrowdSys->CrowdInstanceData.AddZeroed(CrowdSys->InstanceCount + CrowdSys->CustomCrowdInstanceData.Num());

	for (INT j = 0; j < CrowdSys->CustomCrowdInstanceData.Num(); ++j)
	{
		if(CrowdSys->CustomCrowdInstanceData(j))
		{
			UMMOCrowdInstance* inst = ConstructObject<UMMOCrowdInstance>(UMMOCrowdInstance::StaticClass(),
				CrowdSys, NAME_None, RF_Public|RF_Transient, CrowdSys->CustomCrowdInstanceData(j));
			inst->Owner = CrowdSys;
			if(!CrowdSys->CustomCrowdInstanceData(j)->SteeringBehavior)
			{
				CrowdSys->CustomCrowdInstanceData(j)->SteeringBehavior
					= ConstructObject<UMMOSteeringBehavior>(UMMOSteeringBehavior::StaticClass(),
					CrowdSys->CustomCrowdInstanceData(j), NAME_None, RF_Public);
			}

			inst->NativePostBeginPlay();
			CrowdSys->CrowdInstanceData(j) = inst;
		}
	}

	for (INT i = CrowdSys->CustomCrowdInstanceData.Num(); i < CrowdSys->InstanceCount + CrowdSys->CustomCrowdInstanceData.Num(); ++i)
	{
		UMMOCrowdInstance* inst = ConstructObject<UMMOCrowdInstance>(UMMOCrowdInstance::StaticClass(),
			CrowdSys, NAME_None, RF_Public|RF_Transient, CrowdSys->CrowdInstanceConfig);
		inst->Owner = CrowdSys;		
		inst->NativePostBeginPlay();

		inst->Location = FVector(CrowdSys->Location.X + RandFloat() * CrowdSys->InitOffsetExtent.X,
			CrowdSys->Location.Y + RandFloat() * CrowdSys->InitOffsetExtent.Y,
			CrowdSys->Location.Z + RandFloat() * CrowdSys->InitOffsetExtent.Z);

		inst->Direction = FRotator(0, appRand(), 0).Vector();


		CrowdSys->CrowdInstanceData(i) = inst;
	}


	CrowdSys->eventPostInitCrowdInstance();
// 	if(CrowdSys->CrowdController)
// 	{
// 		CrowdSys->CrowdController->SetOwner(CrowdSys);
// 		CrowdSys->CrowdController->NativePostInitCrowdInstance();
// 	}
// 
	for(INT j = 0; j < CrowdSys->Components.Num(); ++j)
	{
		if(CrowdSys->Components(j)->IsA(UMMOCrowdController::StaticClass()))
		{
			UMMOCrowdController* ctrl = Cast<UMMOCrowdController>(CrowdSys->Components(j));
			ctrl->NativePostInitCrowdInstance();
		}
	}
}
//------------------------------------------------------------------------
void UMMOCrowdController::Tick( FLOAT DeltaSeconds )
{
	CTRL_TICK("MMOCrowdController");

	AMMOCrowdSystem* sys = Cast<AMMOCrowdSystem>(GetOwner());

	if(!sys)
	{
		return;
	}

	for (INT i = 0; i < sys->CrowdInstanceData.Num(); ++i)
	{
		if(sys->CrowdInstanceData(i))
		{
			sys->CrowdInstanceData(i)->Update(DeltaSeconds);
		}
	}
}