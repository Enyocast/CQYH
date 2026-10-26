#include "stdafx.h"
#include "MMOGameUIClasses.h"
#include "MMOFacade.h"
#include "attribute_def.h"
#include "ClientActionConditionCheck.h"
#include "MMOMsgBoxManager.h"
#include "UStallManager.h"
#include "UITextParser.h"

IMPLEMENT_CLASS(UMMOUINewStallBuyMsgPanel)

void UMMOUINewStallBuyMsgPanel::PostOnShow(UBOOL v)
{
	Super::PostOnShow(v);
	if (v)
	{
	}
}

void UMMOUINewStallBuyMsgPanel::SetStallBuyMsgPanelData(INT stallSlot, INT bag, INT slot, INT price, INT count, INT maxCount)
{
	this->_StallSlot = stallSlot;
	this->_SrcBag = bag;
	this->_SrcSlot = slot;
	this->_Price = price;
	this->_Count = count;
	this->_MaxCount = maxCount;
	UpdatePanel();
}

void UMMOUINewStallBuyMsgPanel::UpdatePanel()
{
	UGFxObject* object = GFXPlayer->CreateObject(TEXT("Object"));
	if (!object)
	{
		return;
	}

	object->SetInt(TEXT("Price"), this->_Price);
	object->SetInt(TEXT("Count"), this->_Count);
	object->SetInt(TEXT("MaxCount"), this->_MaxCount);
	object->SetString(TEXT("ItemName"), TEXT(""));
	object->SetInt(TEXT("ConSlot"), this->_SrcBag);
	object->SetInt(TEXT("ItemSlot"), this->_SrcSlot);
	object->SetInt(TEXT("StallSlot"), this->_StallSlot);
	object->SetString(TEXT("TextOk"), MMOUI::ParseLocalizedPropertyPath(TEXT("MMOGame.Stall.Buy")));
	object->SetString(TEXT("TextCancel"), MMOUI::ParseLocalizedPropertyPath(TEXT("MMOGame.Stall.Cancel")));

	StallItemInfo stallItemInfo;
	if (UStallManager::getSingleton().GetStallBuyItem(_StallSlot, stallItemInfo))
	{
		if (stallItemInfo.ItemId > 0)
		{
			const UItem* item = MMOFacade::getSingleton().FindItemTemplate(stallItemInfo.ItemId);
			if (item)
			{
				object->SetString(TEXT("ItemName"), item->GetDisplayName());
				UGFxObject* itemSlot = GetObject(TEXT("BuyItem"));
				if (GFXPlayer && itemSlot != NULL)
				{
					GFXPlayer->SetItemSlotData(itemSlot, (UItem*)item, ESPType_StallBuy, E_CONSLOT_STALL_BUY, this->_StallSlot);
				}
			}
		}
	}

	eventCallInitPanel(object);
}

void UMMOUINewStallBuyMsgPanel::ASStallBuyYes(INT stallSlot, INT count)
{
	if (count < 1)
	{
		FString text = MMOUI::ParseLocalizedPropertyPath(TEXT("MMOGame.Stall.BuyItemCountError"));
		MMOUI::GetUIManager()->delegateAddScreenMessage(text, MsgInfoType_Table, text);
		return;
	}

	ConfirmBuyItem(stallSlot, count);
}

void UMMOUINewStallBuyMsgPanel::ASStallBuyNo()
{
	this->Show(FALSE);
}

void UMMOUINewStallBuyMsgPanel::ConfirmBuyItem(INT stallSlot, INT count)
{
	if (_ConfirmBuyBox)
	{
		return;
	}

	StallItemInfo stallItemInfo;
	if (!UStallManager::getSingleton().GetStallBuyItem(stallSlot, stallItemInfo))
	{
		return;
	}

	const UItem* item = MMOFacade::getSingleton().FindItemTemplate(stallItemInfo.ItemId);
	if (!item)
	{
		return;
	}

	FScriptDelegate funYes(EC_EventParm);
	funYes.Object = this;
	funYes.FunctionName = TEXT("AgreeBuyNow");

	FScriptDelegate funNo(EC_EventParm);
	funNo.Object = this;
	funNo.FunctionName = TEXT("RefuseBuyNow");

	FString text = FString::Printf(*MMOUI::ParseLocalizedPropertyPath(TEXT("MMOGame.Stall.BuyItemConfirm")),
		*UITextParser::HTMLMoneyIconString(MONEYTYPE_02, stallItemInfo.Price * count), 
		count, 
		*(item->GetDisplayName()));
	_ConfirmBuyBox = MMOMsgBoxManager::getSingleton().AddMessageBox(text, stallSlot, funYes, funNo);
	if (_ConfirmBuyBox)
	{
		_ConfirmBuyBox->SetInt(TEXT("itemdataid"), count);
	}

	this->Show(FALSE);
}

void UMMOUINewStallBuyMsgPanel::AgreeBuyNow(UGFxObject *mc)
{
	if (!mc)
	{
		return;
	}

	INT slot = mc->GetInt(TEXT("iteminfoid"));
	INT count = mc->GetInt(TEXT("itemdataid"));

	StallItemInfo stallItemInfo;
	if (UStallManager::getSingleton().GetStallBuyItem(slot, stallItemInfo))
	{
		CMessageHandler::GetInstance().Send_BuyStallItem(UStallManager::getSingleton().GetStallBuyPlayerId(), slot, count, stallItemInfo.ModifyTime);
	}

	_ConfirmBuyBox = NULL;
}

void UMMOUINewStallBuyMsgPanel::RefuseBuyNow(UGFxObject *mc)
{
	if (!mc)
	{
		return;
	}

	_ConfirmBuyBox = NULL;
}