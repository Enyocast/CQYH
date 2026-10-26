#include "stdafx.h"

IMPLEMENT_CLASS(AMMOCrowdRendererSM);

void AMMOCrowdRendererSM::Init()
{
	if( ParticleSystemComponent && ParticleSystemComponent->EmitterInstances.Num() )
	{
		FParticleEmitterInstance* inst = ParticleSystemComponent->EmitterInstances(0);
		UParticleSpriteEmitter* pse = inst->SpriteTemplate;
		if( pse && pse->LODLevels.Num() )
		{
			UParticleModule* pm;
			for( int i = 0; i < pse->LODLevels(0)->Modules.Num(); ++i )
			{
				pm = pse->LODLevels(0)->Modules(i);
				if( pm->IsA( UParticleModuleLocationCrowdSystem::StaticClass() ) )
				{
					PSModule = Cast<UParticleModuleLocationCrowdSystem>( pm );
					break;
				}
			}
		}
	}
}