#include "EnginePrivate.h"
#include "EngineParticleClasses.h"
#include "EngineAudioDeviceClasses.h"

/*-----------------------------------------------------------------------------
	UParticleModuleSound implementation.
-----------------------------------------------------------------------------*/
IMPLEMENT_CLASS(UParticleModuleSoundBase);
IMPLEMENT_CLASS(UParticleModuleSound);

#define SUPPORT_PARTICLE_SOUND 0

void UParticleModuleSound::UpdateCurveValue(UDistributionFloatConstantCurve* StartPlayTimeDist)
{
#if SUPPORT_PARTICLE_SOUND
	if (StartPlayTimeDist)
	{
		while(StartPlayTimeDist->GetNumKeys() > 2)
		{
			StartPlayTimeDist->DeleteKey(0);
		}

		while (StartPlayTimeDist->GetNumKeys() < 2)
		{
			StartPlayTimeDist->CreateNewKey(
				StartPlayTimeDist->GetNumKeys());
		}

		// Add two points, one at time 0.0f and one at 1.0f
		for (INT Key = 0; Key < 2; Key++)
		{
			if (Key == 0)
			{
				StartPlayTimeDist->SetKeyIn(Key, StartPlayTime);
				StartPlayTimeDist->SetKeyOut(0, Key, 0.5f);
			}
			else
			{
				FLOAT val = StartPlayTimeDist->GetKeyIn(Key - 1);
				if(SoundFX)
				{
					val += SoundFX->GetCueDuration();
				}
				StartPlayTimeDist->SetKeyIn(Key, val);
				StartPlayTimeDist->SetKeyOut(0, Key, 0.5f);
			}
		}
	}

#endif
}
//------------------------------------------------------------------------
void UParticleModuleSound::OnCurveKeyMoved()
{
#if SUPPORT_PARTICLE_SOUND
	UDistributionFloatConstantCurve* StartPlayTimeDist = Cast<UDistributionFloatConstantCurve>(StartPlayTimeEdit.Distribution);
	if(StartPlayTimeDist && StartPlayTimeDist->GetNumKeys() > 0)
	{
		StartPlayTime = StartPlayTimeDist->GetKeyIn(0);
	}
#endif
}
//------------------------------------------------------------------------
void UParticleModuleSound::PostLoad()
{
	Super::PostLoad();
}
//------------------------------------------------------------------------
void UParticleModuleSound::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
#if SUPPORT_PARTICLE_SOUND
	UProperty* PropertyThatChanged = PropertyChangedEvent.Property;
	if (PropertyThatChanged)
	{
		if ((PropertyThatChanged->GetFName() == FName(TEXT("StartPlayTime")))
			|| (PropertyThatChanged->GetFName() == FName(TEXT("SoundFX")))
			|| (PropertyThatChanged->GetFName() == FName(TEXT("Distribution"))))
		{
			//StartPlayTimeEdit.Distribution = Cast<UDistributionFloatConstantCurve>(StaticConstructObject(UDistributionFloatConstantCurve::StaticClass(), this));
			UDistributionFloatConstantCurve* StartPlayTimeDist = Cast<UDistributionFloatConstantCurve>(StartPlayTimeEdit.Distribution);
			UpdateCurveValue(StartPlayTimeDist);
		}
	}

#endif
	Super::PostEditChangeProperty(PropertyChangedEvent);
}
//------------------------------------------------------------------------
void UParticleModuleSound::AddModuleCurvesToEditor(UInterpCurveEdSetup* EdSetup)
{
#if SUPPORT_PARTICLE_SOUND

#if WITH_EDITORONLY_DATA
	// Iterate over object and find any InterpCurveFloats or UDistributionFloats
	for (TFieldIterator<UStructProperty> It(GetClass()); It; ++It)
	{
		// attempt to get a distribution from a random struct property
		UObject* Distribution = FRawDistribution::TryGetDistributionObjectFromRawDistributionProperty(*It, (BYTE*)this);
		if (Distribution)
		{
			if(Distribution->IsA(UDistributionFloat::StaticClass()))
			{
				// We are assuming that this is the alpha...
				//if (bClampAlpha == TRUE)
				//{
				//	EdSetup->AddCurveToCurrentTab(Distribution, It->GetName(), ModuleEditorColor, TRUE, TRUE, TRUE, 0.0f, 1.0f);
				//}
				//else
				{
					EdSetup->AddCurveToCurrentTab(Distribution, It->GetName(), ModuleEditorColor, TRUE, TRUE);
				}
			}
			else
			{
				// We are assuming that this is the color...
				//EdSetup->AddCurveToCurrentTab(Distribution, It->GetName(), ModuleEditorColor, TRUE, TRUE);
			}
		}
	}
#endif // WITH_EDITORONLY_DATA

#endif
}
//------------------------------------------------------------------------
void UParticleModuleSound::ProcessSound(UParticleSystemComponent* ParComponent, UBOOL Play)
{
#if SUPPORT_PARTICLE_SOUND
	SoundLifeTime = 0;
	bCanPlaySound = Play;

	if(AudioComp && (Play == FALSE))
	{
		AudioComp->Stop();
	}

	return;

#if 0
	if(!Play)
	{
		if(AudioComp)
		{
			AudioComp->Stop();
		}

		return;
	}

	UParticleSystemComponent* comp = ParComponent;
	AActor* actor = comp->GetOwner();
	FVector pos(0, 0, 0);
	if(actor)
	{
		if(bIgnoreIfActorHidden && actor->bHidden)
		{
			return;
		}

		pos = actor->Location;
	}


	if(!AudioComp && Play && SoundFX)
	{
		AudioComp = UAudioDevice::CreateComponent(SoundFX, comp->GetScene(), actor, 0 );
		if(AudioComp)
		{
			AudioComp->bAutoDestroy = (bLoop ? 0 : 1);

			if( bFollowActor && actor)
			{	
				AudioComp->bUseOwnerLocation = 1;
			}
			else
			{
				AudioComp->bUseOwnerLocation = 0;
			}
		}
	}

	if(AudioComp && Play)
	{
		AudioComp->Location = pos;
		PlaySoundCue();
	}
#endif
#endif
}
//------------------------------------------------------------------------
void UParticleModuleSound::Spawn(FParticleEmitterInstance* Owner, INT Offset, FLOAT SpawnTime)
{
//	SPAWN_INIT;
}
//------------------------------------------------------------------------
void UParticleModuleSound::PlaySoundCue()
{
#if SUPPORT_PARTICLE_SOUND
	if( AudioComp )
	{
		AudioComp->VolumeMultiplier		= VolumeMultiplier;
		AudioComp->PitchMultiplier			= PitchMultiplier;
		AudioComp->bAllowSpatialization	&= GIsGame;
		AudioComp->bIsUISound				= !GIsGame;
		AudioComp->PlaybackTime = SoundFX->GetCueDuration() * PercentToPlay;
		//AudioComponent->SubtitlePriority		= SUBTITLE_PRIORITY_ANIMNOTIFY;
		AudioComp->Play();
	}
#endif
}
//------------------------------------------------------------------------
void UParticleModuleSound::Update(FParticleEmitterInstance* Owner, INT Offset, FLOAT DeltaTime)
{
#if SUPPORT_PARTICLE_SOUND
	SoundLifeTime += DeltaTime;

	if(bCanPlaySound && (SoundLifeTime >= StartPlayTime))
	{
		bCanPlaySound = FALSE;

		UParticleSystemComponent* comp = Owner->Component;
		AActor* actor = comp->GetOwner();
		FVector pos(0, 0, 0);
		
		if(Owner && GIsGame)
		{
			pos = Owner->Location;
		}
		else if(actor)
		{
			if(bIgnoreIfActorHidden && actor->bHidden)
			{
				return;
			}

			pos = actor->Location;

		}

		if(!AudioComp && SoundFX)
		{
			AudioComp = UAudioDevice::CreateComponent(SoundFX, comp->GetScene(), actor, 0 );
			if(AudioComp)
			{
				AudioComp->bAutoDestroy = (bLoop ? 0 : 1);
				
				if(GIsGame)
				{
					// used emitter pool
					AudioComp->bUseOwnerLocation = 0;
				}
				else
				{
					if( bFollowActor && actor)
					{	
						AudioComp->bUseOwnerLocation = 1;
					}
					else
					{
						AudioComp->bUseOwnerLocation = 0;
					}
				}
			}
		}

		if(AudioComp && !AudioComp->IsPlaying())
		{
			AudioComp->SoundCue = SoundFX;
			AudioComp->Location = pos;
			PlaySoundCue();
		}
	}
#endif
}

/**
 *	Called when the module is created, this function allows for setting values that make
 *	sense for the type of emitter they are being used in.
 *
 *	@param	Owner			The UParticleEmitter that the module is being added to.
 */
void UParticleModuleSound::SetToSensibleDefaults(UParticleEmitter* Owner)
{
#if SUPPORT_PARTICLE_SOUND
	StartPlayTimeEdit.Distribution = Cast<UDistributionFloatConstantCurve>(StaticConstructObject(UDistributionFloatConstantCurve::StaticClass(), this));
	UDistributionFloatConstantCurve* StartPlayTimeDist = Cast<UDistributionFloatConstantCurve>(StartPlayTimeEdit.Distribution);
	if (StartPlayTimeDist)
	{
		UpdateCurveValue(StartPlayTimeDist);
		StartPlayTimeDist->bIsDirty = TRUE;
	}
#endif
}