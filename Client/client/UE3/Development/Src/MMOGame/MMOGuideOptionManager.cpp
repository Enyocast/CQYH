#include "MMOGuideOptionManager.h"
#include "FSMState.h"

MMOGuideOptionManager::MMOGuideOptionManager()
{
	MMOUI::RegisterEventHandler(this, GameEvent_FinishLoading);
}

MMOGuideOptionManager::~MMOGuideOptionManager()
{
	MMOUI::UnRegisterEventHandler(this, GameEvent_FinishLoading);
}

void MMOGuideOptionManager::Init()
{
}

void MMOGuideOptionManager::OnNativeGameEvent(struct MMOGameEvent* evt)
{
	switch(evt->GetEventType())
	{
	case GameEvent_FinishLoading:
		{
			OnEnterScene();
		}
		break;
	}
}

void MMOGuideOptionManager::OnEnterScene()
{
	if (UMMOKeyManager::getSingleton()->GetClientVariablesVersion() == 0)
	{
		if (MMOUI::GetUIManager())
		{
			MMOUI::GetUIManager()->ShowPanelEx(MMOUI::GetUIManager()->Panel_GuideOption, TRUE, "");
		}
		SetGameControlType(GC_MIR2);
	}
}

void MMOGuideOptionManager::SetGameControlType(GAME_CONTROL_TYPE type)
{
	UMMOKeyManager::getSingleton()->ASSetContralType(type);
	UMMOKeyManager::getSingleton()->DefaultBarAllType(TRUE);
	UMMOKeyManager::getSingleton()->OnApplyByUI();
	UMMOKeyManager::getSingleton()->SaveKeyword();
	MMOFacade::getSingleton().GCTType = type;
}