#include "stdafx.h"
#include "MMOGameUIClasses.h"
#include "MMOFacade.h"
#include "EquipDecomposeManager.h"
extern bool g_lockMouseCursorForUI;
IMPLEMENT_CLASS(UItemSlotActionListener_Decompose)


UBOOL UItemSlotActionListener_Decompose::OnLeftMousePress( class UGFxObject* mc,BYTE SlotType,BYTE ContainerID,INT SlotID,UBOOL bDefault ) 
{ 
	if(bDefault)return FALSE;
	return FALSE; 
} 

UBOOL UItemSlotActionListener_Decompose::OnLeftMouseClick( class UGFxObject* mc,BYTE SlotType,BYTE ContainerID,INT SlotID,UBOOL bDefault )
{
	if(bDefault)
	{
		return FALSE;
	}

	//if(EquipDecomposeManager::getSingleton().IsDecomposeEquip())
	if(E_CONSLOT_DEFAULT == ContainerID)
	{
		EquipDecomposeManager::getSingleton().Decompose(ContainerID,SlotID);
		//MMOUI::GetUIManager()->ClearCurrentItemSlotActionListener();

		//return TRUE;
	}
	else
	{
		if (E_CONSLOT_RESOURCE == ContainerID)
		{
			MMOUI::GetUIManager()->delegateAddScreenMessage(
				MMOUI::ParseLocalizedPropertyPath(TEXT("MMOGame.Decompose.CannotDecompose")));
			
		}
		else
		{
			MMOUI::GetUIManager()->delegateAddScreenMessage(
				MMOUI::ParseLocalizedPropertyPath(TEXT("MMOGame.Decompose.OnlyInBag")));
		}
		
	}

	return TRUE;
}

UBOOL UItemSlotActionListener_Decompose::OnRightMouseClick( class UGFxObject* mc,BYTE SlotType,BYTE ContainerID,INT SlotID,UBOOL bDefault )
{
	if(bDefault)return FALSE;
	MMOUI::GetUIManager()->ClearCurrentItemSlotActionListener();// SetCurrentItemSlotActionListener( LastItemActionListener );	
	return TRUE;
}

UBOOL UItemSlotActionListener_Decompose::OnDragDrop( class UGFxObject* SrcSlotMC, class UGFxObject* DestSlotMC, BYTE SrcSlotType, BYTE SrcContainerID, INT SrcSlotID, BYTE DestSlotType, BYTE DestContainerID, INT DestSlotID )
{
	return FALSE;
}

void UItemSlotActionListener_Decompose::NativeOnSubscribeItemSlotAction()
{
	MMOFacade::getSingleton().SetMouseCursor( EMC_GrabHand );
	g_lockMouseCursorForUI = true;
}

void UItemSlotActionListener_Decompose::NativeOnUnSubscribeItemSlotAction()
{
	g_lockMouseCursorForUI = false;
	MMOFacade::getSingleton().SetMouseCursor( EMC_Arrow );
}

INT  UItemSlotActionListener_Decompose::GetSlotType()
{
	return (INT)E_CONSLOT_EQUIPPED;
}

UBOOL UItemSlotActionListener_Decompose::OnDoubleClickSlot(class UGFxObject* SrcSlotMC,BYTE SrcSlotType,BYTE SrcContainerID,INT SrcSlotID,UBOOL bDefault)
{
	return FALSE;
}