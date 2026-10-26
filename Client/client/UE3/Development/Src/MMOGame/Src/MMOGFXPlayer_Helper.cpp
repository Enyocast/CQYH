#include "stdafx.h"
#include "MMOGameUIClasses.h"
#include "MMOFacade.h"
#include "EngineAudioDeviceClasses.h"
#include "MMOHelperManager.h"

IMPLEMENT_CLASS(UMMOGFXPlayer_Helper)

void UMMOGFXPlayer_Helper::Init()
{
	Super::Init();

	check(FALSE && "UMMOGFXPlayer_Helper::Init()");
	//MMOUI::RegisterMoviePlayer(this, MMOUI::GetUIManager()->MoviePlayer_Helper);
}

void UMMOGFXPlayer_Helper::UnInit()
{
	Super::UnInit();
}

void UMMOGFXPlayer_Helper::PostAdvance(FLOAT dt)
{
	if (_HelperPanel && _HelperPanel->IsVisible)
	{
//		_HelperPanel->UpdateHelperPos();
	}
}

void UMMOGFXPlayer_Helper::ASUpdateHelperDetail(INT baseClass, INT subClass)
{
	if (_HelperPanel)
	{
		_HelperPanel->UpdateHelperDetail(baseClass, subClass);
	}
}

void UMMOGFXPlayer_Helper::ASPlayHelperSound()
{
	if (_HelperPlayerPanel && _HelperPlayerPanel->_CurSound)
	{
		MMOFacade::getSingleton().GetMainActor()->PlaySound(_HelperPlayerPanel->_CurSound);
		_HelperPlayerPanel->UpdateHelperSoundData(TRUE);
		MMOHelperManager::getSingleton().OnShowPlayer(_HelperPlayerPanel->_CurSound->Duration);
	}
}

void UMMOGFXPlayer_Helper::ASPauseHelperSound()
{
	if (_HelperPlayerPanel)
	{
		_HelperPlayerPanel->StopCurSound();
		_HelperPlayerPanel->UpdateHelperSoundData(FALSE);
	}
}
