#include "stdafx.h"
#include "MMOGameUIClasses.h"
#include "MMOGameClasses.h"
#include "MMOFacade.h"
#include "MMOMsgBoxManager.h"
extern bool g_lockMouseCursorForUI;
IMPLEMENT_CLASS(UItemSlotActionListener_Signature)


UBOOL UItemSlotActionListener_Signature::OnLeftMousePress( class UGFxObject* mc,BYTE SlotType,BYTE ContainerID,INT SlotID,UBOOL bDefault ) 
{ 
	return FALSE; 
} 

UBOOL UItemSlotActionListener_Signature::OnLeftMouseClick( class UGFxObject* mc,BYTE SlotType,BYTE ContainerID,INT SlotID,UBOOL bDefault )
{
	ItemInfo* itemDymcData = MMOFacade::getSingleton().FindItem( ContainerID, SlotID );

	if( itemDymcData )
	{
		UItem *itemTempLate = MMOFacade::getSingleton().FindItemTemplate( itemDymcData->m_nTemplateID );
		UEquip* equip = Cast<UEquip>( itemTempLate );
		if( equip == NULL )
		{
			MMOUI::GetUIManager()->delegateAddScreenMessage( MMOUI::ParseLocalizedPropertyPath(TEXT("MMOGame.Bag.ErrorSignatureNotEquip")) ,MsgInfoType_Table,TEXT("MMOGame.Bag.ErrorSignatureNotEquip"));	
			MMOUI::GetUIManager()->ClearCurrentItemSlotActionListener();
			return TRUE;
		}

		if(0 == itemDymcData->m_dwRoleID )
		{
			if (SIGN_ITEM_COST > MMOFacade::getSingleton().GetPlayerMoney(E_MONEYTYPE_02))
			{
				MMOUI::GetUIManager()->delegateAddScreenMessage( MMOUI::ParseLocalizedPropertyPath(TEXT("MMOGame.Bag.ErrorSignatureNotEnoughMoney")) ,MsgInfoType_Table,TEXT("MMOGame.Bag.ErrorSignatureNotEnoughMoney"));	
			}
			else
			{
				FString SignText = FString::Printf( *MMOUI::ParseLocalizedPropertyPath( TEXT("MMOGame.Bag.ItemSignText") ), SIGN_ITEM_COST);
				UGFxObject* MsgBox = MMOMsgBoxManager::getSingleton().AddMessageBox(SignText, ContainerID ,FScriptDelegate(this, TEXT("OnSignOK")) , FScriptDelegate(this, TEXT("OnSignCancel")));
				if( MsgBox != NULL )
				{
					MsgBox->SetInt( TEXT("iteminfoid") , ContainerID );
					MsgBox->SetInt( TEXT("itemdataid") , SlotID );
				}
			}
		}
		else
		{
			MMOUI::GetUIManager()->delegateAddScreenMessage( MMOUI::ParseLocalizedPropertyPath(TEXT("MMOGame.Bag.ErrorSignatureAlready")),MsgInfoType_Table,TEXT("MMOGame.Bag.ErrorSignatureAlready") );	
		}
	}
	
	MMOUI::GetUIManager()->ClearCurrentItemSlotActionListener();

	return TRUE;
}

UBOOL UItemSlotActionListener_Signature::OnRightMouseClick( class UGFxObject* mc,BYTE SlotType,BYTE ContainerID,INT SlotID,UBOOL bDefault )
{
	if(bDefault)return FALSE;
	MMOUI::GetUIManager()->ClearCurrentItemSlotActionListener();//
	//MMOUI::GetUIManager()->SetCurrentItemSlotActionListener( LastItemActionListener );	
	return TRUE;
}

UBOOL UItemSlotActionListener_Signature::OnDragDrop( class UGFxObject* SrcSlotMC, class UGFxObject* DestSlotMC, BYTE SrcSlotType, BYTE SrcContainerID, INT SrcSlotID, BYTE DestSlotType, BYTE DestContainerID, INT DestSlotID )
{
	return FALSE;
}

void UItemSlotActionListener_Signature::NativeOnSubscribeItemSlotAction()
{
	MMOFacade::getSingleton().SetMouseCursor( EMC_Hand );//EMC_Signature
	g_lockMouseCursorForUI = true;
}

void UItemSlotActionListener_Signature::NativeOnUnSubscribeItemSlotAction()
{
	g_lockMouseCursorForUI = false;
	MMOFacade::getSingleton().SetMouseCursor( EMC_Arrow );
}

INT  UItemSlotActionListener_Signature::GetSlotType()
{
	return (INT)E_CONSLOT_EQUIPPED;
}

void UItemSlotActionListener_Signature::OnSignOK(UGFxObject* mc)
{
	if (NULL != mc)
		CMessageHandler::GetInstance().Send_SignatureItem( mc->GetInt(TEXT("iteminfoid")), mc->GetInt(TEXT("itemdataid")) );

	MMOUI::GetUIManager()->ClearCurrentItemSlotActionListener();//
	//MMOUI::GetUIManager()->SetCurrentItemSlotActionListener(LastItemActionListener);
}

void UItemSlotActionListener_Signature::OnSignCancel(UGFxObject* mc)
{
	MMOUI::GetUIManager()->ClearCurrentItemSlotActionListener();//
	//MMOUI::GetUIManager()->SetCurrentItemSlotActionListener(LastItemActionListener);
}

UBOOL UItemSlotActionListener_Signature::OnDoubleClickSlot(class UGFxObject* SrcSlotMC,BYTE SrcSlotType,BYTE SrcContainerID,INT SrcSlotID,UBOOL bDefault)
{
	return FALSE;
}
