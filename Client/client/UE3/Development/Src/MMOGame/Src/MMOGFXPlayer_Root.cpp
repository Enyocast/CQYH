#include "stdafx.h"
#include "MMOGameUIClasses.h"
#include "MMOFacade.h"
#include "MMOMsgBoxManager.h"

IMPLEMENT_CLASS(UMMOGFXPlayer_Root)
IMPLEMENT_CLASS(AMMOCameraAnchorPoint)

UMMOGFXPlayer_RootBase* g_rootGFXPlayer = 0;

extern TArray<struct FGFxWidgetBinding> g_WidgetBindings;

TArray<UMMOGFXPlayer_RootBase*> g_rootGFXPlayerList;

UBOOL IsViewLoaded(FName panelName)
{
	for (INT i = 0; i < g_rootGFXPlayerList.Num(); ++i)
	{
		if(g_rootGFXPlayerList(i)->IsViewLoaded(panelName))
		{
			return TRUE;
		}
	}

	return FALSE;
}


UMMOGFXPlayer_RootBase* FindViewLoader(FName panelName)
{
	for (INT i = 0; i < g_rootGFXPlayerList.Num(); ++i)
	{
		UMMOGFXPlayer_RootBase* player = g_rootGFXPlayerList(i);
		for (INT j = 0; j < player->ViewData.Num(); ++j)
		{
			if ( player->ViewData(j).ViewName == panelName)
			{
				return player;
			}
		}		
	}

	return 0;
}

void UMMOGFXPlayer_Root::PostInit()
{
}

void UMMOGFXPlayer_Root::BindingWidgetsInfo()
{
	g_rootGFXPlayer = this;
	
	Super::BindingWidgetsInfo();
}

void UMMOGFXPlayer_Root::Init()
{
 	Super::Init();

	MMOMsgBoxManager::getSingleton().init(this);
	MMOUI::GetUIManager()->SetCommonUIComponentMoviePlayer(this);
}

void UMMOGFXPlayer_Root::UnInit()
{
	Super::UnInit();
}