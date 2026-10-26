#include "stdafx.h"
#include "EngineParticleClasses.h"

IMPLEMENT_CLASS(UMMOCrowdRenderComponentSM);

void UMMOCrowdRenderComponentSM::Attach()
{
	Super::Attach();

	OwnerSystem = Cast<AMMOCrowdSystem>( GetOwner() );
	if( OwnerSystem && Template )
		Init( OwnerSystem );
}

void UMMOCrowdRenderComponentSM::Tick( FLOAT DeltaTime )
{
	CTRL_TICK("MMOCrowdRenderComponentSM");

	Super::Tick( DeltaTime );

	if( !PSModule )
		return;
	for( int i = 0; i < OwnerSystem->CrowdInstanceData.Num(); ++i )
	{
		PSModule->ParticleLocations(i) = OwnerSystem->CrowdInstanceData(i)->Location;
		PSModule->ParticleRotations(i) = OwnerSystem->CrowdInstanceData(i)->Direction;
	}
}

// set particle parameters and fetch crowd system location module
void UMMOCrowdRenderComponentSM::Init( const AMMOCrowdSystem* cs )
{
	//for( UINT i = 0; i < EmitterInstances.Num(); ++i )
	INT i = 0;
	{	// by changing the template all instances will be changed too ?
		UParticleSpriteEmitter* pse = EmitterInstances(i)->SpriteTemplate;
		if( pse && pse->LODLevels.Num() )
		{
			for( INT j = 0; j < pse->LODLevels(0)->Modules.Num(); ++j )
			{
				UParticleModule* pm = pse->LODLevels(0)->Modules(j);
				if( pm->IsA( UParticleModuleSpawn::StaticClass() ) )
				{	// change spawn rate
					//UParticleModuleSpawn* pms = Cast<UParticleModuleSpawn>(pm);
					//pms->Rate = cs->InstanceCount;
				}
				else if( pm->IsA( UParticleModuleLocationCrowdSystem::StaticClass() ) )
				{
					PSModule = Cast<UParticleModuleLocationCrowdSystem>(pm);
					PSModule->ParticleLocations.SetNum( cs->CrowdInstanceData.Num() );
					PSModule->ParticleRotations.SetNum( cs->CrowdInstanceData.Num() );
				}
			}
		}
	}
}