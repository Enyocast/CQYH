/**
*	MMODayTimeHelper.cpp
*/

#include "stdafx.h"

IMPLEMENT_CLASS(AMMODayTimeHelper)

void AMMODayTimeHelper::PostBeginPlay()
{
	if (!GWorld)
	{
		return;
	}

	if (GWorld->DominantDirectionalLight)
	{
		MainLight = Cast<ADominantDirectionalLight>(GWorld->DominantDirectionalLight->GetOwner());
		MainLightColor = MainLight->LightComponent->LightColor;
		MainLightIntensity = 1.0f;
	}

	for (FActorIterator iter; iter; ++iter)
	{
		ADirectionalLightToggleable* Light = Cast<ADirectionalLightToggleable>(*iter);
		if (Light)
		{
			DirectionalLights.Push(Light);
			DirectionalLightColors.Push(Light->LightComponent->LightColor);
			DirectionalLightIntensities.Push(1.0f);
		}

		AMMOTorchLight* pTorchLight = Cast<AMMOTorchLight>(*iter);
		if ( pTorchLight )
		{
			DefaultTorchLightBrightness = TorchLightBrightness = pTorchLight->LightComponent->Brightness;
			InsetTorchLight(pTorchLight);
		}
	}

	LightMapScale = FColor(255, 255, 255, 255);
}

void AMMODayTimeHelper::ForceUpdateComponents(UBOOL bCollisionUpdate,UBOOL bTransformOnly)
{
	if (GIsEditor)
	{
		if (WorldInfo)
		{
			WorldInfo->LightMapScale = LightMapScale;
			//WorldInfo->LuminanceThreshold = LuminanceThreshold;	// zhaojun@snda
			//shanling@snda
			WorldInfo->NewLimitLuminance  = NewLimitLuminance;
			WorldInfo->NewMiddleLuminance = NewMiddleLuminance;
			WorldInfo->NewWhiteLuminance  = NewWhiteLuminance;
			WorldInfo->NewAvgLuminanceParameter = NewAvgLuminanceParameter;
			//shanling@snda
		}
	}

	GetTorchLights();
	UpdateTorchLightsBrightness();
	Super::ForceUpdateComponents(bCollisionUpdate, bTransformOnly);
}

void AMMODayTimeHelper::TickSpecial(FLOAT DeltaTime)
{
	if (WorldInfo)
	{
		WorldInfo->LightMapScale = LightMapScale;
		//WorldInfo->LuminanceThreshold = LuminanceThreshold;	// zhaojun@snda

		//shanling@snda
// 		WorldInfo->NewLimitLuminance  = NewLimitLuminance;
// 		WorldInfo->NewMiddleLuminance = NewMiddleLuminance;
// 		WorldInfo->NewWhiteLuminance  = NewWhiteLuminance;
// 		WorldInfo->NewAvgLuminanceParameter = NewAvgLuminanceParameter;
		//shanling@snda
	}
	
	UpdateTorchLightsBrightness();
	
}

void AMMODayTimeHelper::GetTorchLights()
{
	ClearTorchLights();
	for (FActorIterator iter; iter; ++iter)
	{
		AMMOTorchLight* pTorchLight = Cast<AMMOTorchLight>(*iter);
		if ( pTorchLight )
		{
			InsetTorchLight( pTorchLight );
		}
	}
}

void AMMODayTimeHelper::InsetTorchLight( AMMOTorchLight *plithgt )
{
	TorchLights.Push(plithgt);
}

void AMMODayTimeHelper::ClearTorchLights()
{
	TorchLights.Empty();
}

void AMMODayTimeHelper::UpdateTorchLightsBrightness()
{
	if ( DefaultTorchLightBrightness != TorchLightBrightness )
	{
		for ( int i = 0 ; i < TorchLights.Num() ; ++i )
		{
			TorchLights( i )->SetCurrentBrightness(TorchLightBrightness);// LightComponent->Brightness = TorchLightBrightness;

		}
		DefaultTorchLightBrightness = TorchLightBrightness;
	}
}