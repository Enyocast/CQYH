#include "stdafx.h"
#include "MMOGameUIClasses.h"
#include "MMOFacade.h"
#include "EquipDecomposeManager.h"

IMPLEMENT_CLASS(UMMOUIEquipDecomposePanel)

void UMMOUIEquipDecomposePanel::NativeInitOnce()
{

}

void UMMOUIEquipDecomposePanel::Init()
{
	Super::Init();
}

void UMMOUIEquipDecomposePanel::PostOnShow(UBOOL v)
{
	Super::PostOnShow(v);
	if(v)
	{
		UpdateResultUI();
	}
	else
	{
		//ClearUI();
	}
}

void UMMOUIEquipDecomposePanel::UpdateResultUI()
{
	TArray<DecomposeResult>& Ret = EquipDecomposeManager::getSingleton().GetDecomposeResult();
	//check(Ret.Num() <= DECOMPOSE_MAX_COUNT);
	if(Ret.Num() > DECOMPOSE_MAX_COUNT)
		return;
	//if(Ret.Num() > 0)
	{
		for(INT i = 0; i < DECOMPOSE_MAX_COUNT; ++i)
		{
			UGFxObject* ret_mc = GetObject(FString::Printf(TEXT("RetMat_%d"),i));
			//check(ret_mc != NULL);
			if(ret_mc == NULL)
				continue;
			/*UGFxObject* cnt_mc = ret_mc->GetObject(TEXT("cnt_mc"));
			check(cnt_mc != NULL);*/
			if(i < Ret.Num())
			{
				UItem* pItem = MMOFacade::getSingleton().FindItemTemplate(Ret(i).itemId);
				//check(pItem != NULL);
				if(pItem == NULL)
					continue;
				GFXPlayer->SetItemSlotData(ret_mc,pItem,ESPType_Bag);

				ret_mc->GetObject(TEXT("valueAmount"))->SetText(FString::Printf(TEXT("%d"),Ret(i).cnt));
				//GFXPlayer->SetIconShowByItem(ret_mc, pItem);
				//cnt_mc->SetText(appItoa(Ret(i).cnt));
			}
			else
			{
				GFXPlayer->SetItemSlotData(ret_mc,NULL,ESPType_Bag);
				/*GFXPlayer->SetIconShowByItem(ret_mc, NULL);
				cnt_mc->SetText(TEXT(""));*/
			}
		}
	}
}

void UMMOUIEquipDecomposePanel::ClearUI()
{
	for(INT i = 0; i < DECOMPOSE_MAX_COUNT; ++i)
	{
		UGFxObject* ret_mc = GetObject(FString::Printf(TEXT("RetMat_%d"),i));
		//check(ret_mc != NULL);
		if(ret_mc == NULL)
			continue;

		GFXPlayer->SetItemSlotData(ret_mc,NULL,ESPType_Bag);
		/*GFXPlayer->SetIconShowByItem(ret_mc, NULL);
		UGFxObject* cnt_mc = ret_mc->GetObject(TEXT("cnt_mc"));
		check(cnt_mc != NULL);
		cnt_mc->SetText(TEXT(""));*/
	}
}

UBOOL UMMOUIEquipDecomposePanel::OnLeftMouseClick(class UGFxObject* mc,BYTE SlotType,BYTE ContainerID,INT SlotID,UBOOL bDefault)
{
	if(bDefault)return FALSE;
	return FALSE;
}

UBOOL UMMOUIEquipDecomposePanel::OnRightMouseClick(class UGFxObject* mc,BYTE SlotType,BYTE ContainerID,INT SlotID,UBOOL bDefault)
{
	if(bDefault)return FALSE;
	return FALSE;
}

UBOOL UMMOUIEquipDecomposePanel::OnDragDrop(class UGFxObject* SrcSlotMC,class UGFxObject* DestSlotMC,BYTE SrcSlotType,BYTE SrcContainerID,INT SrcSlotID,BYTE DestSlotType,BYTE DestContainerID,INT DestSlotID)
{
	return FALSE;
}

UBOOL UMMOUIEquipDecomposePanel::OnLeftMousePress(class UGFxObject* mc,BYTE SlotType,BYTE ContainerID,INT SlotID,UBOOL bDefault)
{
	if(bDefault)return FALSE;
	return FALSE;
}

//===============================================================================================================
//===============================================================================================================
void UMMOUIEquipDecomposePanel::ASDecomposeOk()
{
	UMMOUIEquipDecomposeHintPanel* hintPanel = Cast<UMMOUIEquipDecomposeHintPanel>(MMOUI::FindUIPanel(MMOUI::GetUIManager()->Panel_EquipDecomposeHint));
	if(hintPanel)
	{
		hintPanel->DecomposeOk();
	}

	MMOUI::GetUIManager()->ShowPanelEx(MMOUI::GetUIManager()->Panel_EquipDecomposeHint, FALSE, "");
}

void UMMOUIEquipDecomposePanel::ASDecomposeCancel()
{
	MMOUI::GetUIManager()->ShowPanelEx(MMOUI::GetUIManager()->Panel_EquipDecomposeHint, FALSE, "");
}
//===============================================================================================================
//===============================================================================================================