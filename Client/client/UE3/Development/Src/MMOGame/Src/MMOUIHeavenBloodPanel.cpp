#include "stdafx.h"
#include "MMOGameUIClasses.h"
#include "MMOHeavenManager.h"
#include "MMOFacade.h"

IMPLEMENT_CLASS(UMMOUIHeavenBloodPanel)

void UMMOUIHeavenBloodPanel::OnClickLevelState(INT nLevelIndex,INT nPanelIndex)
{
	const BloodSlot* pkSlot = MMOHeavenManager::getSingleton().GetBloodSlot(nPanelIndex,nLevelIndex);
	if (pkSlot == NULL)
		return;
	if(pkSlot->nValue < MAX_BLOODSEA_SLOT_NUMBER)
	{
		if(nLevelIndex > 1)
		{
			const BloodSlot* pkSlotLast = MMOHeavenManager::getSingleton().GetBloodSlot(nPanelIndex,nLevelIndex - 1);
			if(pkSlotLast&&pkSlotLast->nValue <= 0)
			{
				MMOUI::GetUIManager()->delegateAddScreenMessage(MMOUI::ParseLocalizedPropertyPath( TEXT("MMOGame.Heaven.BloodSlotLock")));
				return;
			}
		}
		CMessageHandler::GetInstance().Send_HeavenBloodLevel(nLevelIndex,nPanelIndex);
	}
	else
	{
		MMOUI::GetUIManager()->delegateAddScreenMessage(MMOUI::ParseLocalizedPropertyPath( TEXT("MMOGame.Heaven.BloodSlotOPHint0")),MsgInfoType_Table,TEXT("MMOGame.Heaven.BloodSlotOPHint0"));
	}
}
void UMMOUIHeavenBloodPanel::OnClickActivateBlood(INT nTypeIndex)
{
	if(nTypeIndex <= MAX_BLOODSEA_PAGE)
	{
		AMMOPlayer *mainPlayer = MMOFacade::getSingleton().GetMainPlayer();
		if(mainPlayer == NULL || mainPlayer->ActorAttributes == NULL)
			return;
		INT nLevel = mainPlayer->ActorAttributes->heavenAttributes.heavenLevel;

		const HeavenBloodConfig* pkBlood = 	MMOHeavenManager::getSingleton().GetHeavenBloodData(nTypeIndex,1,1);
		if(pkBlood == NULL)
			return;
		if(nLevel >= pkBlood->nPageLevelLimit)
			CMessageHandler::GetInstance().Send_HeavenBloodOpen(nTypeIndex);
		else
		{
			FString strCon = FString::Printf(*MMOUI::ParseLocalizedPropertyPath( TEXT("MMOGame.Heaven.OpenNeedHeavenLevel")),pkBlood->nPageLevelLimit);
			MMOUI::GetUIManager()->delegateAddScreenMessage(strCon);
		}
	}	
}
void UMMOUIHeavenBloodPanel::UpdateHeavenBloodPanel(UMMOGFXPlayer* gfxPlayer)
{
	if(!gfxPlayer)
		return;
	UGFxObject* dataProvider = gfxPlayer->CreateArray();
	if(!dataProvider)
		return;

	AMMOPlayer *mainPlayer = MMOFacade::getSingleton().GetMainPlayer();
	if(mainPlayer == NULL || mainPlayer->ActorAttributes == NULL)
		return;
	INT nLevel = mainPlayer->ActorAttributes->heavenAttributes.heavenLevel;

	for (INT i = 0;i < MAX_BLOODSEA_PAGE; ++i)
	{
		UGFxObject* data = gfxPlayer->CreateObject("UI_SkillTree.SkillTreeAS3.HeavenBloodData");
		if(!data)
			continue;
		const HeavenBloodConfig* pkBlood = 	MMOHeavenManager::getSingleton().GetHeavenBloodData(i+1,1,1);
		if(pkBlood == NULL)
			continue;
		BOOL bActive = MMOHeavenManager::getSingleton().GetBloodLockState(i);
		data->SetBool("bActivate",bActive);
		if(!bActive)
		{
			FString strCon = FString::Printf(*MMOUI::ParseLocalizedPropertyPath( TEXT("MMOGame.Heaven.OpenNeedHeavenLevel")),pkBlood->nPageLevelLimit);
			data->SetString("sConditionHint",strCon);
		}
		FString strCon = TEXT("MMOGame.Heaven.BloodName");
		strCon += appItoa(i+1);
		data->SetString("sName",MMOUI::ParseLocalizedPropertyPath(strCon));

		UGFxObject* InfoArray = gfxPlayer->CreateArray();
		UGFxObject* InfoArrayName = gfxPlayer->CreateArray();
		if(InfoArray == NULL || InfoArrayName == NULL)
			continue;
		INT nComplete = 0;
		for (INT n = 0; n < MAX_BLOODSEA_SLOT_PER_PAGE; ++n)
		{
			const BloodSlot* pkSlot = MMOHeavenManager::getSingleton().GetBloodSlot(i+1,n+1);
			if(pkSlot)
			{
				InfoArray->SetElementInt(n,pkSlot->nValue);
				InfoArrayName->SetElementString(n,pkSlot->sName);
				nComplete += pkSlot->nValue;
			}
			else
			{
				InfoArray->SetElementInt(n,0);
				InfoArrayName->SetElementString(n,TEXT(""));
			}
		}
		data->SetInt("nCompleteState", nComplete);
		data->SetObject("arrLevel",InfoArray);
		data->SetObject("arrSlotName",InfoArrayName);
		dataProvider->SetElementObject(i,data);
	}
	eventCallUpdateHeavenBloodInfo(dataProvider);
}