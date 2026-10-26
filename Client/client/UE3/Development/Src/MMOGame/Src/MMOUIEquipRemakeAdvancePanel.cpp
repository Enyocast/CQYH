#include "stdafx.h"
#include "MMOGameUIClasses.h"
#include "MMOFacade.h"
#include "MMOStats.h"
#include "UMMOUIEquipRemakeAdvancePanel.h"
#include "MMOMsgBoxManager.h"
#include "MMOEquipRemakeMgr.h"

IMPLEMENT_CLASS(UMMOUIEquipRemakeAdvancePanel)

void UMMOUIEquipRemakeAdvancePanel::Init()
{

}

void UMMOUIEquipRemakeAdvancePanel::NativeInitOnce()
{
	check(EventAdapter == NULL);
	if(NULL == EventAdapter)
	{
		TArray<EGameEvent> evts;
		evts.AddItem(GameEvent_EquipRemakeResult);
		EventAdapter = new TGameEventAdapter<UMMOUIEquipRemakeAdvancePanel>(this, evts);
	}
}

void UMMOUIEquipRemakeAdvancePanel::PostOnShow(UBOOL v)
{
	Super::PostOnShow(v);
	if (v)
	{
		ASOnSelectEquipType_Advanced(_CurSelectEquipType);
	}
}


 void UMMOUIEquipRemakeAdvancePanel::OnNativeGameEvent(struct MMOGameEvent* evt)
 {
	 if (IsVisible == FALSE)
	 {
		 return;
	 }
	 MMOGameEvent_RemakeResult* pResultEvt = (MMOGameEvent_RemakeResult*)evt;
	 if(pResultEvt == NULL)
		 return;

	 if (pResultEvt->GetEventType() == GameEvent_EquipRemakeResult)
	 {
		EquipRemakeResult(pResultEvt->_Result , pResultEvt->_ItemID);
	 }
 }

 void UMMOUIEquipRemakeAdvancePanel::ASOnEquipRemake_Advanced(INT nItemSubType)
 {
	 MMOEquipRemakeManager::getSingleton().OnRemake((UINT8)nItemSubType , 1); 
 }

 void UMMOUIEquipRemakeAdvancePanel::ASOnSelectEquipType_Advanced(INT nItemSubType)
 {
	 INT nItemID,nCostCount;
	 if (MMOEquipRemakeManager::getSingleton().GetMaterialIDAndCost((UINT8)nItemSubType , 1, nItemID, nCostCount) == TRUE )
	 {
		 UpdateMaterialInfo(nItemID , nCostCount);
		 _CurSelectEquipType = nItemSubType;
	 } 
 }

 void UMMOUIEquipRemakeAdvancePanel::UpdateMaterialInfo(INT nItemID,INT nCostCount)
 {
	 UItem *pItem = MMOFacade::getSingleton().FindItemTemplate( nItemID );
	 if (pItem == NULL)
	 {
		 return;
	 }

	 UGFxObject* itemData = GFXPlayer->CreateObject(TEXT("ActionScript3.ItemSlotData"));
	 if (itemData)
	 {
		 INT nItemCount = MMOFacade::getSingleton().GetItemCountInBag(nItemID, E_CONSLOT_DEFAULT);
		 itemData->SetInt("quantity" , nItemCount);
		 itemData->SetInt("itemIndex" , nItemID);
		 itemData->SetInt("itemColor" , pItem->ItemColor);
		 itemData->SetString("iconName" , pItem->GetIconName());

		 eventCallUpdateMaterialInfo(itemData,nCostCount);
	 }
	 else
	 {
		 ASOnSelectEquipType_Advanced(_CurSelectEquipType);
	 }
 }

 void UMMOUIEquipRemakeAdvancePanel::EquipRemakeResult(INT nResult,INT nItemID)
 {
	 UGFxObject* obj = GFXPlayer->CreateObject(TEXT("Object"));
	 if (obj == NULL)
	 {
		 return ;
	 }

	 if (nResult == TRUE)
	 {
		 UItem *pItem =  MMOFacade::getSingleton().FindItemTemplate(nItemID);
		 if (pItem == NULL)
		 {
			 return ;
		 }

		 UGFxObject* itemData = GFXPlayer->CreateObject(TEXT("ActionScript3.ItemSlotData"));
		 if (itemData == NULL)
		 {
			 return ;
		 }

		 itemData->SetInt("quantity" , 1);
		 itemData->SetInt("itemIndex" , nItemID);
		 itemData->SetInt("itemColor" , pItem->ItemColor);
		 itemData->SetString("iconName" , pItem->GetIconName());

		 obj->SetObject("itemSlotData" , itemData);
		 obj->SetString("itemName" , pItem->GetDisplayName());
		 obj->SetBool("bExpensive" , pItem->Expensive);
	 }

	 eventCallEquipRemakeResult(nResult,obj);
 }

