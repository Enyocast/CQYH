#include "stdafx.h"
#include "MMOGameUIClasses.h"
#include "MMOFacade.h"
#include "MMOStats.h"
#include "UMMOUIEquipRemakePanel.h"
#include "MMOMsgBoxManager.h"
#include "MMOEquipRemakeMgr.h"

IMPLEMENT_CLASS(UMMOUIEquipRemakePanel)

void UMMOUIEquipRemakePanel::Init()
{

}

void UMMOUIEquipRemakePanel::NativeInitOnce()
{
	check(EventAdapter == NULL);
	if(NULL == EventAdapter)
	{
		TArray<EGameEvent> evts;
		evts.AddItem(GameEvent_EquipRemakeResult);
		EventAdapter = new TGameEventAdapter<UMMOUIEquipRemakePanel>(this, evts);
	}
}

void UMMOUIEquipRemakePanel::PostOnShow(UBOOL v)
{
	Super::PostOnShow(v);
	if (v)
	{
		ASOnSelectEquipType(_CurSelectEquipType);
	}
}


 void UMMOUIEquipRemakePanel::OnNativeGameEvent(struct MMOGameEvent* evt)
 {
	 MMOGameEvent_RemakeResult* pResultEvt = (MMOGameEvent_RemakeResult*)evt;
	 if(pResultEvt == NULL)
		 return;

	 if (pResultEvt->GetEventType() == GameEvent_EquipRemakeResult)
	 {
		EquipRemakeResult(pResultEvt->_Result , pResultEvt->_ItemID);
	 }
 }

 void UMMOUIEquipRemakePanel::ASOnEquipRemake(INT nItemSubType)
 {
	 MMOEquipRemakeManager::getSingleton().OnRemake((UINT8)nItemSubType , 0); 
 }

 void UMMOUIEquipRemakePanel::ASOnSelectEquipType(INT nItemSubType)
 {
	 INT nItemID,nCostCount;
	 if (MMOEquipRemakeManager::getSingleton().GetMaterialIDAndCost((UINT8)nItemSubType , 0, nItemID, nCostCount) == TRUE )
	 {
		 UpdateMaterialInfo(nItemID , nCostCount);
		 _CurSelectEquipType = nItemSubType;
	 } 
 }

 void UMMOUIEquipRemakePanel::UpdateMaterialInfo(INT nItemID,INT nCostCount)
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
		 ASOnSelectEquipType(_CurSelectEquipType);
	 }
 }

 void UMMOUIEquipRemakePanel::EquipRemakeResult(INT nResult,INT nItemID)
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

