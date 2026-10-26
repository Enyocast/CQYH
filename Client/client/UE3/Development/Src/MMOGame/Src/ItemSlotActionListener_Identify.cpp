#include "stdafx.h"
#include "MMOGameUIClasses.h"
#include "MMOFacade.h"
#include "MMOQuestManager.h"
#include "MMOMsgBoxManager.h"
#include "UITextParser.h"
extern bool g_lockMouseCursorForUI;
IMPLEMENT_CLASS(UItemSlotActionListener_Identify)


UBOOL UItemSlotActionListener_Identify::OnLeftMousePress( class UGFxObject* mc,BYTE SlotType,BYTE ContainerID,INT SlotID,UBOOL bDefault ) 
{ 
	if(bDefault)return FALSE;
	return FALSE; 
} 


UBOOL UItemSlotActionListener_Identify::OnLeftMouseClick( class UGFxObject* mc,BYTE SlotType,BYTE ContainerID,INT SlotID,UBOOL bDefault )
{
	if(bDefault)return FALSE;

	if( ContainerID != CONSLOT_DEFAULT )
	{
		MMOUI::GetUIManager()->delegateAddScreenMessage( MMOUI::ParseLocalizedPropertyPath(TEXT("MMOErrorInfo.ERROR_CODE_DEF.errItemEquipped")),MsgInfoType_Table,TEXT("MMOErrorInfo.ERROR_CODE_DEF.errItemEquipped") );
		MMOUI::GetUIManager()->ClearCurrentItemSlotActionListener();
		return TRUE;
	}

	ItemInfo* itemDymcData = MMOFacade::getSingleton().FindItem( ContainerID, SlotID );
	if( itemDymcData )
	{
		UItem *itemTempLate = MMOFacade::getSingleton().FindItemTemplate( itemDymcData->m_nTemplateID );
		UEquip* equip = Cast<UEquip>( itemTempLate );

		if( equip == NULL )
		{
			//not an equip
			MMOUI::GetUIManager()->delegateAddScreenMessage( MMOUI::ParseLocalizedPropertyPath(TEXT("MMOGame.Bag.ErrorIdentifyNotEquip")) ,MsgInfoType_Table,TEXT("MMOGame.Bag.ErrorIdentifyNotEquip"));	
			MMOUI::GetUIManager()->ClearCurrentItemSlotActionListener();
			return TRUE;
		}

		//
		if( itemDymcData->m_byIdentified != IDENTIFY_TYPE_NO )
		{
			//already evaluated
			MMOUI::GetUIManager()->delegateAddScreenMessage( MMOUI::ParseLocalizedPropertyPath(TEXT("MMOErrorInfo.ERROR_CODE_DEF.errItemAlreadyIdentified")),MsgInfoType_Table,TEXT("MMOErrorInfo.ERROR_CODE_DEF.errItemAlreadyIdentified") );
		}
		else
		{
			FString txt = MMOUI::ParseLocalizedPropertyPath(TEXT("MMOGame.Bag.IdentifyCost")) + UITextParser::HTMLMoneyIconString( MONEYTYPE_02 , equip->IdentifyCost );
			UGFxObject* msg = MMOMsgBoxManager::getSingleton().AddModalMessageBoxEvent( txt , ContainerID , GameEvent_MsgBoxItemIdentifyAsk );
			if( msg )
			{
				msg->SetInt( TEXT("itemdataid") , SlotID );
			}
			
		}
	}
	MMOUI::GetUIManager()->ClearCurrentItemSlotActionListener();

	return TRUE;
}

UBOOL UItemSlotActionListener_Identify::OnRightMouseClick( class UGFxObject* mc,BYTE SlotType,BYTE ContainerID,INT SlotID,UBOOL bDefault )
{
	if(bDefault)return FALSE;

	MMOUI::GetUIManager()->ClearCurrentItemSlotActionListener();//
	//MMOUI::GetUIManager()->SetCurrentItemSlotActionListener( LastItemActionListener );	
	return TRUE;
}

UBOOL UItemSlotActionListener_Identify::OnDragDrop( class UGFxObject* SrcSlotMC, class UGFxObject* DestSlotMC, BYTE SrcSlotType, BYTE SrcContainerID, INT SrcSlotID, BYTE DestSlotType, BYTE DestContainerID, INT DestSlotID )
{
	return FALSE;
}

void UItemSlotActionListener_Identify::NativeOnSubscribeItemSlotAction()
{
	MMOFacade::getSingleton().SetMouseCursor( EMC_Identify );
	g_lockMouseCursorForUI = true;
}

void UItemSlotActionListener_Identify::NativeOnUnSubscribeItemSlotAction()
{
	g_lockMouseCursorForUI = false;
	MMOFacade::getSingleton().SetMouseCursor( EMC_Arrow );
}

INT  UItemSlotActionListener_Identify::GetSlotType()
{
	return (INT)E_CONSLOT_EQUIPPED;
}

UBOOL UItemSlotActionListener_Identify::OnDoubleClickSlot(class UGFxObject* SrcSlotMC,BYTE SrcSlotType,BYTE SrcContainerID,INT SrcSlotID,UBOOL bDefault)
{
	return FALSE;
}