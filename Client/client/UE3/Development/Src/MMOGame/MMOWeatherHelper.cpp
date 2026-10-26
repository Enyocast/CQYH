/**
*	MMOWeatherManager.cpp
*/

#include "stdafx.h"
#include "UnEdViewport.h"
#include "MMOWeatherManager.h"
#include "EngineFoliageClasses.h"

IMPLEMENT_CLASS(AMMOWeatherHelper)

void FWeatherParameters::Interpolate(const FWeatherParameters& SourceParameters, const FWeatherParameters& DestParameters, FLOAT Factor)
{
	PrecipitationIntensity = Lerp(SourceParameters.PrecipitationIntensity, DestParameters.PrecipitationIntensity, Factor);

	RayleighFactor = Lerp(SourceParameters.RayleighFactor, DestParameters.RayleighFactor, Factor);
	MieFactor = Lerp(SourceParameters.MieFactor, DestParameters.MieFactor, Factor);
	RayleighScale = Lerp(SourceParameters.RayleighScale, DestParameters.RayleighScale, Factor);
	MieScale = Lerp(SourceParameters.MieScale, DestParameters.MieScale, Factor);

	WindDirection = Lerp(SourceParameters.WindDirection, DestParameters.WindDirection, Factor);
	WindStrength = Lerp(SourceParameters.WindStrength, DestParameters.WindStrength, Factor);
}

void AMMOWeatherHelper::PostBeginPlay()
{
	RainParticleSystem = NULL;
	SnowParticleSystem = NULL;
	StormMaterialEffect = NULL;
	StormMaterialInstance = NULL;

	bEnableWeather = TRUE;
	bRaining = FALSE;
	bSnowing = FALSE;
	bStorming = FALSE;
	bLightning = FALSE;
	bStormFadingIn = FALSE;
	bStormFadingOut = FALSE;
	StormIntensity = 1.0f;

	MaxRainCount = 100;
	MaxSnowCount = 100;
	StormOpacity = 0.08f;

	if( LightningStartTime < 0.001f )
		LightningStartTime = 0.001f;
	if( LightningFinishTime < 0.001f )
		LightningFinishTime = 0.001f;

	if (GWorld)
	{
		if (GWorld->DominantDirectionalLight)
		{
			MainLight = Cast<ADominantDirectionalLight>(GWorld->DominantDirectionalLight->GetOwner());
			MainLightColor = MainLight->LightComponent->LightColor;
			MainLightIntensity = MainLight->LightComponent->Brightness;
		}

		for (FActorIterator It; It; ++It)
		{
			ADirectionalLightToggleable* Light = Cast<ADirectionalLightToggleable>(*It);
			if (Light)
			{
				DirectionalLights.Push(Light);
				DirectionalLightColors.Push(Light->LightComponent->LightColor);
				DirectionalLightIntensities.Push(Light->LightComponent->Brightness);
				continue;
			}

			AInstancedFoliageActor* Foliage = Cast<AInstancedFoliageActor>(*It);
			if( Foliage )
			{
				InstancedFoliages.Push( Foliage );
				continue;
			}
		}
	}
}

void AMMOWeatherHelper::TickSpecial(FLOAT DeltaTime)
{
	if (!GWorld || !bEnableWeather)
	{
		return;
	}

	FLOAT TotalTime = GCurrentTime;
	FLOAT Factor = 1.0f;
	if (WeatherTransitionTime > 0.0f)
	{
		Factor = Min(1.0f, (TotalTime - WeatherStartTime) / WeatherTransitionTime);
	}
	CurRainParameters.Interpolate(SrcRainParameters, DstRainParameters, Factor);
	CurSnowParameters.Interpolate(SrcSnowParameters, DstSnowParameters, Factor);
	
	if (RainParticleSystem)
	{
		for (INT EmitterIndex = 0; EmitterIndex < RainParticleSystem->EmitterInstances.Num(); EmitterIndex++)
		{
			FParticleEmitterInstance* Instance = RainParticleSystem->EmitterInstances(EmitterIndex);

			if (Instance && Instance->SpriteTemplate)
			{
				//check(Instance->SpriteTemplate->LODLevels.Num() > 0);
				if(Instance->SpriteTemplate->LODLevels.Num()<= 0)
					continue;

				UParticleLODLevel* LODLevel = Instance->SpriteTemplate->GetCurrentLODLevel(Instance);
				if (LODLevel && LODLevel->bEnabled)
				{
					if (LODLevel->RequiredModule)
					{
						LODLevel->RequiredModule->bUseMaxDrawCount = TRUE;
						LODLevel->RequiredModule->MaxDrawCount = MaxRainCount * CurRainParameters.PrecipitationIntensity;
					}
				}
			}
		}

		if (CurRainParameters.PrecipitationIntensity < 0.00001f)
		{
			RainParticleSystem->DeactivateSystem();

			AEmitterPool* EmitterPool = GWorld->GetWorldInfo()->MyEmitterPool;
			if (EmitterPool)
			{
				EmitterPool->ReturnToPool( RainParticleSystem );
			}
			RainParticleSystem = NULL;
		}
	}

	if (SnowParticleSystem)
	{
		for (INT EmitterIndex = 0; EmitterIndex < SnowParticleSystem->EmitterInstances.Num(); EmitterIndex++)
		{
			FParticleEmitterInstance* Instance = SnowParticleSystem->EmitterInstances(EmitterIndex);

			if (Instance && Instance->SpriteTemplate)
			{
				//check(Instance->SpriteTemplate->LODLevels.Num() > 0);
				if(Instance->SpriteTemplate->LODLevels.Num() <= 0)
					continue;

				UParticleLODLevel* LODLevel = Instance->SpriteTemplate->GetCurrentLODLevel(Instance);
				if (LODLevel && LODLevel->bEnabled)
				{
					if (LODLevel->RequiredModule)
					{
						LODLevel->RequiredModule->bUseMaxDrawCount = TRUE;
						LODLevel->RequiredModule->MaxDrawCount = MaxSnowCount * CurSnowParameters.PrecipitationIntensity;
					}
				}
			}
		}

		if (CurSnowParameters.PrecipitationIntensity < 0.00001f)
		{
			SnowParticleSystem->DeactivateSystem();

			AEmitterPool* EmitterPool = GWorld->GetWorldInfo()->MyEmitterPool;
			if (EmitterPool)
			{
				EmitterPool->ReturnToPool( SnowParticleSystem );
			}
			SnowParticleSystem = NULL;
		}
	}

	if (bStormFadingIn || bStormFadingOut)
	{
		if (bStormFadingIn)
		{
			StormIntensity = (TotalTime - StormStartTime) / StormTransitionTime;
		}
		else
		{
			StormIntensity = 1.0f - (TotalTime - StormStartTime) / StormTransitionTime;
		}

		if (StormMaterialInstance)
		{
			StormMaterialInstance->SetScalarParameterValue("OpacityMultiply", StormOpacity * StormIntensity);
		}

		if (bStormFadingIn)
		{
			if (StormIntensity >= 1.0f)
			{
				bStormFadingIn = FALSE;
			}
		}
		else
		{
			if (StormIntensity < 0.00001f)
			{
				for(INT PlayerIndex = 0;PlayerIndex < GEngine->GamePlayers.Num();PlayerIndex++)
				{
					ULocalPlayer* Player = GEngine->GamePlayers(PlayerIndex);
					if (Player->Actor && Player->PlayerPostProcess)
					{
						for (INT EffectIdx = 0; EffectIdx < Player->PlayerPostProcess->Effects.Num(); ++EffectIdx)
						{
							UMaterialEffect* MaterialEffect = Cast<UMaterialEffect>(Player->PlayerPostProcess->Effects(EffectIdx));
							if (MaterialEffect && MaterialEffect->Material)
							{
								if (MaterialEffect->EffectName == FName(*SandEffectName))
								{
									MaterialEffect->bShowInGame = FALSE;
									StormMaterialInstance = NULL;
								}
							}
						}
					}
				}

				bStorming = FALSE;
				bStormFadingOut = FALSE;
			}
		}
	}

	if( bLightning )
	{
		TickLightning( DeltaTime );
	}
}

void AMMOWeatherHelper::TickLightning( FLOAT DeltaTime )
{
	LightningTimer += DeltaTime;

	switch( LightningState )
	{
	case 0:
		if( LightningTimer > NextLightningInterval )
		{
			LightningTimer = 0.f;
			LightningState = 1;

			if( LightningCount == 0 )
			{
				KeepOldLightingValues();

				// disable lightmaps
				if( GWorld && GWorld->GetWorldInfo() )
				{
					GWorld->GetWorldInfo()->LightMapScale = FColor( 0, 0, 0 );
				}

				// shut down all other lights
				for( INT i = 0; i < DirectionalLights.Num(); ++i )
				{
					DirectionalLights(i)->LightComponent->SetLightProperties( 0.f,
						DirectionalLights(i)->LightComponent->LightColor,
						DirectionalLights(i)->LightComponent->Function );
				}

				LightningBrightness = MainLightIntensity;
			}

			LightningFadeRate = ( NextLightningBrightness - LightningBrightness ) / LightningStartTime;

			++LightningCount;
		}
		break;
	case 1:
		if( LightningTimer > LightningStartTime )
		{
			LightningTimer = 0.f;
			LightningState = 2;

			LightningBrightness = NextLightningBrightness;
		}
		else
		{	// fadein
			LightningBrightness += DeltaTime * LightningFadeRate;
		}

		MainLight->LightComponent->SetLightProperties( LightningBrightness,
			LightningColor,
			MainLight->LightComponent->Function );

		break;
	case 2:
		if( LightningTimer > LightningHoldTime )
		{
			LightningTimer = 0.f;
			LightningState = 3;

			LightningFadeRate = ( LightningBrightness - MainLightIntensity ) / LightningFinishTime;
		}
		break;
	case 3:
		LightningBrightness -= LightningFadeRate * DeltaTime;

		if( LightningCount < NextLightningNumber )
		{
			MainLight->LightComponent->SetLightProperties( LightningBrightness,
				MainLightColor,
				MainLight->LightComponent->Function );

			if( LightningTimer > 0.02f )
			{
				LightningTimer = 0.f;
				LightningState = 0;

				// for continous lightning
				NextLightningInterval = 0.02f;
			}
		}
		else if( LightningTimer > LightningFinishTime )
		{
			LightningTimer = 0.f;
			LightningState = 0;
			LightningCount = 0;

			MainLight->LightComponent->SetLightProperties( MainLightIntensity,
				MainLightColor,
				MainLight->LightComponent->Function );

			// open lights
			for( INT i = 0; i < DirectionalLights.Num(); ++i )
			{
				DirectionalLights(i)->LightComponent->SetLightProperties( DirectionalLightIntensities(i),
					DirectionalLights(i)->LightComponent->LightColor,
					DirectionalLights(i)->LightComponent->Function );
			}

			// restore lightmaps
			if( GWorld && GWorld->GetWorldInfo() )
			{
				GWorld->GetWorldInfo()->LightMapScale = OldLightmapScale;
			}

			NextLightningInterval = appFrand() * ( LightningIntervalMax - LightningIntervalMin ) + LightningIntervalMin;
			NextLightningBrightness = appFrand() * ( LightningBrightnessMax - LightningBrightnessMin ) + LightningBrightnessMin;
			NextLightningNumber = appFrand() > 0.5f ? 1 : 2;
		}
		else
		{	// fadeout
			MainLight->LightComponent->SetLightProperties( LightningBrightness,
				LightningColor,
				MainLight->LightComponent->Function );
		}
		break;
	default:
		// should not reach here
		LightningTimer = 0.f;
		LightningState = 0;
		break;
	}
}

/**
* note: must stop lightning before day-night changes!
*/
void AMMOWeatherHelper::KeepOldLightingValues()
{
	if( MainLight )
	{
		MainLightColor = MainLight->LightComponent->LightColor;
		MainLightIntensity = MainLight->LightComponent->Brightness;
	}
	for( INT i = 0; i < DirectionalLights.Num(); ++i )
	{
		DirectionalLightColors(i) = DirectionalLights(i)->LightComponent->LightColor;
		DirectionalLightIntensities(i) = DirectionalLights(i)->LightComponent->Brightness;
	}

	if( GWorld && GWorld->GetWorldInfo() )
		OldLightmapScale = GWorld->GetWorldInfo()->LightMapScale;
}

BOOL AMMOWeatherHelper::IsRaining() const
{
	return bRaining;
}

void AMMOWeatherHelper::StartRain(INT level)
{
	if (!bEnableWeather)
	{
		return;
	}

	WeatherStartTime = GCurrentTime;
	WeatherTransitionTime = 5.0f;

	MaxRainCount = 100 * (level + 1);
	DstRainParameters.PrecipitationIntensity = 1.0f;
	if (!RainParticleSystem)
	{
		AEmitterPool* EmitterPool = GWorld->GetWorldInfo()->MyEmitterPool;
		if (EmitterPool && RainEffect)
		{
			RainParticleSystem = EmitterPool->SpawnEmitter( RainEffect, FVector::ZeroVector );
		}
	}
	bRaining = TRUE;
}

void AMMOWeatherHelper::StopRain()
{
	if (!bEnableWeather)
	{
		return;
	}

	WeatherStartTime = GCurrentTime;
	WeatherTransitionTime = 5.0f;

	SrcRainParameters = DstRainParameters;
	DstRainParameters.PrecipitationIntensity = 0.0f;
	bRaining = FALSE;
}

BOOL AMMOWeatherHelper::IsSnowing() const
{
	return bSnowing;
}

void AMMOWeatherHelper::StartSnow(INT level)
{
	if (!bEnableWeather)
	{
		return;
	}

	WeatherStartTime = GCurrentTime;
	WeatherTransitionTime = 5.0f;

	MaxRainCount = 100 * (level + 1);
	DstSnowParameters.PrecipitationIntensity = 1.0f;
	if (!SnowParticleSystem)
	{
		AEmitterPool* EmitterPool = GWorld->GetWorldInfo()->MyEmitterPool;
		if (EmitterPool && SnowEffect)
		{
			SnowParticleSystem = EmitterPool->SpawnEmitter( SnowEffect, FVector::ZeroVector );
		}
	}

	bSnowing = TRUE;
}

void AMMOWeatherHelper::StopSnow()
{
	if (!bEnableWeather)
	{
		return;
	}

	WeatherStartTime = GCurrentTime;
	WeatherTransitionTime = 5.0f;

	SrcSnowParameters = DstSnowParameters;
	DstSnowParameters.PrecipitationIntensity = 0.0f;
	bSnowing = FALSE;
}

BOOL AMMOWeatherHelper::IsStorming() const
{
	return bStorming;
}

void AMMOWeatherHelper::StartStorm(INT level)
{
	if (!bEnableWeather)
	{
		return;
	}

	for(INT PlayerIndex = 0;PlayerIndex < GEngine->GamePlayers.Num();PlayerIndex++)
	{
		ULocalPlayer* Player = GEngine->GamePlayers(PlayerIndex);
		if (Player->Actor && Player->PlayerPostProcess)
		{
			for (INT EffectIdx = 0; EffectIdx < Player->PlayerPostProcess->Effects.Num(); ++EffectIdx)
			{
				UMaterialEffect* MaterialEffect = Cast<UMaterialEffect>(Player->PlayerPostProcess->Effects(EffectIdx));

				if (MaterialEffect && MaterialEffect->Material)
				{
					if (MaterialEffect->EffectName == *SandEffectName)
					{
						MaterialEffect->bShowInGame = TRUE;

						if (!StormMaterialInstance)
						{
							StormMaterialInstance = CastChecked<UMaterialInstanceConstant>(StaticConstructObject(UMaterialInstanceConstant::StaticClass(), GetOuter()));
							if (StormMaterialInstance)
							{
								StormMaterialInstance->SetParent(MaterialEffect->Material);
							}
						}

						if (StormMaterialInstance)
						{
							MaterialEffect->Material = StormMaterialInstance;
						}
						break;
					}
				}
			}
		}
	}

	StormStartTime = GCurrentTime;
	StormTransitionTime = 1.0f;
	bStorming = TRUE;
	bStormFadingIn = TRUE;
	bStormFadingOut = FALSE;
	StormOpacity = 0.08f * (level + 1);
	StormIntensity = 0.0f;
}

void AMMOWeatherHelper::StopStorm()
{
	if (!bEnableWeather)
	{
		return;
	}

	StormStartTime = GCurrentTime;
	StormTransitionTime = 1.0f;
	bStormFadingIn = FALSE;
	bStormFadingOut = TRUE;
}

BOOL AMMOWeatherHelper::IsLightning() const
{
	return bLightning;
}

void AMMOWeatherHelper::StartLightning(INT level)
{
	if (!bEnableWeather)
	{
		return;
	}

	LightningState = 0;
	LightningTimer = 0.f;
	LightningLevel = level;

	NextLightningInterval = appFrand() * ( LightningIntervalMax - LightningIntervalMin ) + LightningIntervalMin;
	NextLightningBrightness = appFrand() * ( LightningBrightnessMax - LightningBrightnessMin ) + LightningBrightnessMin;
	NextLightningNumber = appFrand() > 0.5f ? 1 : 2;
	LightningCount = 0;

	// scale interval with level
	NextLightningInterval *= (FLOAT)WeatherLevel::WL_Total / ( WeatherLevel::WL_Total + LightningLevel + 1 );
	
	bLightning = TRUE;
}

void AMMOWeatherHelper::StopLightning()
{
	if (!bEnableWeather)
	{
		return;
	}

	bLightning = FALSE;
}

void AMMOWeatherHelper::EnableWeather()
{
	bEnableWeather = TRUE;
}

void AMMOWeatherHelper::DisableWeather()
{
	if (bEnableWeather)
	{
		bEnableWeather = FALSE;

		StopRain();
		StopSnow();
		StopStorm();
		StopLightning();
	}
}

void AMMOWeatherHelper::SetFire( const FVector& Center, FLOAT Radius )
{
	for( INT i = 0; i < InstancedFoliages.Num(); ++i )
	{
		InstancedFoliages(i)->SetFire( Center, Radius );
	}
}