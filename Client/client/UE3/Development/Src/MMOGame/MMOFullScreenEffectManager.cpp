#include "stdafx.h"
#include "FileHelpers.h"
#include "MMOGameUIClasses.h"
#include "MMOFacade.h"
#include "MMOFullScreenEffectManager.h"


MMOFullScreenEffectManager::MMOFullScreenEffectManager()
{
	ZeroMemory(_FullScreenEffectTypeOpen,sizeof(_FullScreenEffectTypeOpen));
	_FullScreenEffectTypeName[FSET_LowHP] = TEXT("HitEffect");
}

MMOFullScreenEffectManager::~MMOFullScreenEffectManager()
{
}

void MMOFullScreenEffectManager::Init()
{
	Clear();
}

void MMOFullScreenEffectManager::Shutdown()
{
	Clear();
}

void MMOFullScreenEffectManager::Clear()
{
	StopAllEffect();
}


void MMOFullScreenEffectManager::StopAllEffect()
{
	for(INT i=0;i<FSET_Total;i++)
	{
		StopEffect((FullScreenEffectType)i);
	}
}

void MMOFullScreenEffectManager::StartEffect(FullScreenEffectType EffectType)
{
	if(_FullScreenEffectTypeOpen[EffectType] == TRUE)
		return;

	MMOFacade::getSingleton().GetMainController()->eventPlayLowHPWarningSound(TRUE);

	for(INT PlayerIndex = 0;PlayerIndex < GEngine->GamePlayers.Num();PlayerIndex++)
	{
		ULocalPlayer* Player = GEngine->GamePlayers(PlayerIndex);
		if (Player->Actor && Player->PlayerPostProcess)
		{
			for (INT EffectIdx = 0; EffectIdx < Player->PlayerPostProcess->Effects.Num(); ++EffectIdx)
			{
				UMaterialEffect* MaterialEffect = Cast<UMaterialEffect>(Player->PlayerPostProcess->Effects(EffectIdx));

				if (MaterialEffect)
				{
					if (MaterialEffect->EffectName == FName(*_FullScreenEffectTypeName[EffectType]))
					{
						MaterialEffect->bShowInGame = TRUE;
						_FullScreenEffectTypeOpen[EffectType] = TRUE;


						//if(MaterialEffect->Material==NULL)
						//{
						//	UMaterialInstance* StormMaterialInstance =CastChecked<UMaterialInstanceConstant>(UObject::StaticConstructObject(UMaterialInstanceConstant::StaticClass(), UObject::GetTransientPackage()));
						//	if (StormMaterialInstance)
						//	{
						//		StormMaterialInstance->SetParent(MaterialEffect->Material);
						//		MaterialEffect->Material = StormMaterialInstance;
						//		_FullScreenEffectTypeOpen[EffectType] = TRUE;
						//	}

						//}

						//MaterialEffect->bShowInGame = TRUE;


						//UMaterialInstance* StormMaterialInstance =CastChecked<UMaterialInstanceConstant>(UObject::StaticConstructObject(UMaterialInstanceConstant::StaticClass(), UObject::GetTransientPackage()));
						//if (!StormMaterialInstance)
						//{
						//	StormMaterialInstance->SetParent(MaterialEffect->Material);
						//	MaterialEffect->Material = StormMaterialInstance;
						//	_FullScreenEffectTypeOpen[EffectType] = TRUE;
						//}
						break;
					}
				}
			}
		}
	}
}

void MMOFullScreenEffectManager::StopEffect(FullScreenEffectType EffectType)
{
	if(_FullScreenEffectTypeOpen[EffectType] == FALSE)
		return;

	MMOFacade::getSingleton().GetMainController()->eventPlayLowHPWarningSound(FALSE);

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
					if (MaterialEffect->EffectName ==  FName(*_FullScreenEffectTypeName[EffectType]))
					{
						MaterialEffect->bShowInGame = FALSE;
						//MaterialEffect->Material = NULL;
						_FullScreenEffectTypeOpen[EffectType] = FALSE;
						break;
					}
				}
			}
		}
	}
}

