#include "stdafx.h"
#include "MMOGameUIClasses.h"
#include "MMOFacade.h"
#include "MMOQuestManager.h"
#include "UITextParser.h"
#include "LinkManager.h"
#include "MMOMapDataManager.h"
#include "DoodadManager.h"
#include "ClientActionConditionCheck.h"

IMPLEMENT_CLASS(UMMOUIQuestItemCollectionPanel)

void UMMOUIQuestItemCollectionPanel::Init()
{
	Super::Init();

	check(EventAdapter == NULL);
	TArray<EGameEvent> evts;
	evts.AddItem(GameEvent_Quest);
	EventAdapter = new TGameEventAdapter<UMMOUIQuestItemCollectionPanel>(this, evts);

	_ItemSlot = GetObject(TEXT("quest_collection_item_mc"));
	if (_ItemSlot)
	{
		_ItemSlot->SetInt(TEXT("SlotType"), ESPType_ItemCollection);
	}
}

void UMMOUIQuestItemCollectionPanel::PostOnShow(UBOOL v)
{
	Super::PostOnShow(v);

	if (v)
	{
	}

	ClearCollectionItem();
}

void UMMOUIQuestItemCollectionPanel::OnNativeGameEvent(struct MMOGameEvent* evt)
{
	if (!IsVisible)
	{
		return;
	}

	switch(evt->GetEventType())
	{
	case GameEvent_Quest:
		{
			MMOGameEvent_Quest* questEvt = (MMOGameEvent_Quest*)evt;
			if(questEvt == NULL)
			{
				return;
			}

			switch(questEvt->EventType)
			{
			case MMOGameEvent_Quest::EQET_AcceptQuest:
			case MMOGameEvent_Quest::EQET_UpdateQuest:
			case MMOGameEvent_Quest::EQET_AbandonQuest:
			case MMOGameEvent_Quest::EQET_CompleteQuest:
				break;
			}
		}
		break;
	}
}

void UMMOUIQuestItemCollectionPanel::ItemChange(INT ContainerID, INT SlotID)
{
	if (EGameState_InGame == MMO::GetCurrentGameState())
	{
	}
}

void UMMOUIQuestItemCollectionPanel::ItemDelete(INT ContainerID, INT SlotID)
{
	if (EGameState_InGame == MMO::GetCurrentGameState())
	{
	}
}

void UMMOUIQuestItemCollectionPanel::ShowItemCollectionPanel(INT questId)
{
	const UQuest* quest = MMOQuestData::getSingleton().GetQuestData(questId);
	if (!quest)
	{
		return;
	}

	UGFxObject* object = GFXPlayer->CreateObject(TEXT("Object"));
	if (object)
	{
		object->SetInt(TEXT("quest_id"), questId);
		object->SetString(TEXT("quest_desc"), quest->CompleteQuestDialog);
		eventCallUpdateQuestData(object);
	}

	Show(TRUE);
}

UBOOL UMMOUIQuestItemCollectionPanel::SetCollectionItem(INT containerId, INT slotId)
{
	if (!_ItemSlot)
	{
		return FALSE;
	}

	// 清空
	if (containerId < 0 || slotId < 0)
	{
		if (_ItemBagPos._ConID >= 0 && _ItemBagPos._SlotID >= 0)
		{
			MMOFacade::getSingleton().LockItem(_ItemBagPos._ConID, _ItemBagPos._SlotID, -1);
			GFXPlayer->eventCallSetItemData(_ItemSlot, 0, TEXT(""), -1, ESPType_ItemCollection, TEXT(""), ITEMCOLOR_INVALID, -1, -1);
		}

		_ItemBagPos._ConID = -1;
		_ItemBagPos._SlotID = -1;
		_ItemTempId = 0;
		return TRUE;
	}

	// 检查道具
	FClientItemInfo* itemInfo = MMOFacade::getSingleton().FindItem(containerId, slotId);
	if (!itemInfo)
	{
		MMOUI::GetUIManager()->delegateAddScreenMessage(MMOUI::ParseLocalizedPropertyPath(TEXT("MMOGame.EnhanceGeneral.ERROR_ITEM_NOT_FOUND")), 
			MsgInfoType_Table, 
			TEXT("MMOGame.EnhanceGeneral.ERROR_ITEM_NOT_FOUND"));
		return FALSE;
	}

	// 是否是装备
	UItem* pItem = MMOFacade::getSingleton().FindItemTemplate(itemInfo->m_nTemplateID);
	UEquip* pEquip = Cast<UEquip>(pItem);
	if (pEquip == NULL)
	{
		MMOUI::GetUIManager()->delegateAddScreenMessage( MMOUI::ParseLocalizedPropertyPath( TEXT("MMOGame.EnhanceGeneral.ERROR_NOT_A_EQUIP") ) ,MsgInfoType_Table,TEXT("MMOGame.EnhanceGeneral.ERROR_NOT_A_EQUIP"));
		return FALSE;
	}

	//检查是否在界面中(本界面或是其他操作界面)
	ClientActionCondition_ItemCollection checker;
	FClientActionConditionContex contex;
	contex.Item = itemInfo;
	if (!checker.CheckClientActionCondition(contex))
	{
		return FALSE;
	}

	// 解锁背包内原先放置的装备
	if (_ItemBagPos._ConID >= 0 && _ItemBagPos._SlotID >= 0)
	{
		MMOFacade::getSingleton().LockItem(_ItemBagPos._ConID, _ItemBagPos._SlotID, -1);
	}

	// 新的装备
	_ItemBagPos._ConID = containerId;
	_ItemBagPos._SlotID = slotId;

	//设置界面ItemSlot
	GFXPlayer->eventCallSetItemData(_ItemSlot, 1, MMOFacade::getSingleton().GetItemIconNamePersonalized( pItem, itemInfo ), pItem->ItemId, ESPType_ItemCollection, TEXT(""), pItem->ItemColor + 1, _ItemBagPos._ConID, _ItemBagPos._SlotID);
	MMOFacade::getSingleton().LockItem(_ItemBagPos._ConID, _ItemBagPos._SlotID, ESPType_ItemCollection);
	_ItemTempId = itemInfo->m_nTemplateID;

	UGFxObject* object = GFXPlayer->CreateObject(TEXT("Object"));
	if (object)
	{
		object->SetInt(TEXT("quest_item_id"), _ItemTempId);
		object->SetInt(TEXT("quest_item_index"), slotId);
		object->SetString(TEXT("quest_item_icon_name"), MMOFacade::getSingleton().GetItemIconNamePersonalized( pItem ));
		object->SetString(TEXT("quest_item_name"), pItem->GetDisplayName());
		eventCallUpdateItemData(object);
	}

	return TRUE;
}

UBOOL UMMOUIQuestItemCollectionPanel::ClearCollectionItem()
{
	return SetCollectionItem(-1, -1);
}

UBOOL UMMOUIQuestItemCollectionPanel::OnLeftMousePress(class UGFxObject* mc,BYTE SlotType,BYTE ContainerID,INT SlotID,UBOOL bDefault) 
{ 
	if (bDefault)
	{
		return FALSE;
	}
	return FALSE; 
} 

UBOOL UMMOUIQuestItemCollectionPanel::OnLeftMouseClick(class UGFxObject* mc,BYTE SlotType,BYTE ContainerID,INT SlotID,UBOOL bDefault)
{
	if (bDefault)
	{
		return FALSE;
	}
	return FALSE;
}

UBOOL UMMOUIQuestItemCollectionPanel::OnRightMouseClick(class UGFxObject* mc,BYTE SlotType,BYTE ContainerID,INT SlotID,UBOOL bDefault)
{
	if (bDefault)
	{
		return FALSE;
	}

	MMOFacade &mmoFacade = MMOFacade::getSingleton();

	switch (SlotType)
	{
	case ESPType_Bag:
		{
			return SetCollectionItem(ContainerID, SlotID);
		}
		break;
	case ESPType_ItemCollection:
		{
			return ClearCollectionItem();
		}
		break;
	}

	return FALSE;
}

UBOOL UMMOUIQuestItemCollectionPanel::OnDragDrop(class UGFxObject* srcSlotMC, class UGFxObject* destSlotMC,
	BYTE srcSlotType, 
	BYTE srcContainerID,
	INT srcSlotID,
	BYTE destSlotType,
	BYTE destContainerID,
	INT destSlotID)
{
	if (destSlotMC == NULL || srcSlotMC == NULL)
	{
		return FALSE;
	}

	if (srcSlotType == ESPType_Bag && destSlotType == ESPType_ItemCollection)
	{
		SetCollectionItem(srcContainerID, srcSlotID);
	}

	if (srcSlotType == ESPType_ItemCollection && destSlotType == ESPType_Bag)
	{
		ClearCollectionItem();
	}

	return FALSE;
}

//////////////////////////////////////////////////////////////////////////

void UMMOUIQuestItemCollectionPanel::ASSubmitItem(INT questId, INT itemId, INT itemIndex)
{
	const UQuest* quest = MMOQuestData::getSingleton().GetQuestData(questId);
	if (!quest)
	{
		return;
	}

	// 获得需求属性
	INT itemColorReq = 0;
	INT itemLevelReq = 0;
	FString itemSubTypeReq = TEXT("");
	for (INT i = 0; i < quest->CheckVar.Num(); ++i)
	{
		FQuestCheckVar checkVar = quest->CheckVar(i);
		if (checkVar.CheckVarType == TEXT("vtItemRecycle") &&
			checkVar.CheckVarID >= 0 && 
			checkVar.CheckVarID < MAX_ROLE_VARIABLE_COUNT)
		{
			QuestRecycleDataList questRecycleList = MMOQuestData::getSingleton().GetQuestRecycleList();
			QuestRecycleDataList::iterator iter = questRecycleList.begin();
			for (; iter != questRecycleList.end(); ++ iter)
			{
				if (iter->VarIndex == checkVar.CheckVarID)
				{
					itemColorReq = iter->ItemColor;
					itemLevelReq = iter->ItemLevel;
					itemSubTypeReq = iter->ItemSubType;
					break;
				}
			}
			break;
		}
	}

	UItem* item = MMOFacade::getSingleton().FindItemTemplate(itemId);
	if (!item)
	{
		MMOUI::GetUIManager()->delegateAddScreenMessage(TEXT("道具不存在"), 
			MsgInfoType_Table, 
			TEXT("道具不存在"));
		return;
	}

	FClientItemInfo* itemInfo = MMOFacade::getSingleton().FindItem(E_CONSLOT_DEFAULT, itemIndex);
	if (!itemInfo)
	{
		FString text = TEXT("MMOGame.EnhanceGeneral.ERROR_ITEM_NOT_FOUND");
		MMOUI::GetUIManager()->delegateAddScreenMessage(MMOUI::ParseLocalizedPropertyPath(text), MsgInfoType_Table, text);
		return;
	}

	if (itemInfo->m_nTemplateID != itemId)
	{
		MMOUI::GetUIManager()->delegateAddScreenMessage(TEXT("道具不存在"), 
			MsgInfoType_Table, 
			TEXT("道具不存在"));
		return;
	}

	if (item->ItemColor != itemColorReq)
	{
		MMOUI::GetUIManager()->delegateAddScreenMessage(TEXT("道具品质不符合要求"), 
			MsgInfoType_Table, 
			TEXT("道具品质不符合要求"));
		return;
	}

	if (item->ItemLevel != itemLevelReq)
	{
		MMOUI::GetUIManager()->delegateAddScreenMessage(TEXT("道具等级不符合要求"), 
			MsgInfoType_Table, 
			TEXT("道具等级不符合要求"));
		return;
	}

	if (item->ItemSubType != itemSubTypeReq)
	{
		MMOUI::GetUIManager()->delegateAddScreenMessage(TEXT("道具类型不符合要求"), 
			MsgInfoType_Table, 
			TEXT("道具类型不符合要求"));
		return;
	}

	CMessageHandler::GetInstance().Send_Recycle(itemId, itemIndex);
}

