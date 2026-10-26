#include "stdafx.h"
#include "MMOGameUIClasses.h"
#include "MMOFacade.h"
#include "MMOQuestManager.h"
#include "MMOMsgBoxManager.h"
#include "UITextParser.h"
extern bool g_lockMouseCursorForUI;
IMPLEMENT_CLASS(UItemSlotActionListener_Waiting)


UBOOL UItemSlotActionListener_Waiting::OnLeftMousePress( class UGFxObject* mc,BYTE SlotType,BYTE ContainerID,INT SlotID,UBOOL bDefault ) 
{ 
	return FALSE; 
} 


UBOOL UItemSlotActionListener_Waiting::OnLeftMouseClick( class UGFxObject* mc,BYTE SlotType,BYTE ContainerID,INT SlotID,UBOOL bDefault )
{
	return TRUE;
}

UBOOL UItemSlotActionListener_Waiting::OnRightMouseClick( class UGFxObject* mc,BYTE SlotType,BYTE ContainerID,INT SlotID,UBOOL bDefault )
{
	return TRUE;
}

UBOOL UItemSlotActionListener_Waiting::OnDragDrop( class UGFxObject* SrcSlotMC, class UGFxObject* DestSlotMC, BYTE SrcSlotType, BYTE SrcContainerID, INT SrcSlotID, BYTE DestSlotType, BYTE DestContainerID, INT DestSlotID )
{
	return FALSE;
}

void UItemSlotActionListener_Waiting::NativeOnSubscribeItemSlotAction()
{
	//MMOFacade::getSingleton().SetMouseCursor( EMC_Busy );
	//g_lockMouseCursorForUI = true;
}

void UItemSlotActionListener_Waiting::NativeOnUnSubscribeItemSlotAction()
{
	//g_lockMouseCursorForUI = false;
	//MMOFacade::getSingleton().SetMouseCursor( EMC_Arrow );
}

INT  UItemSlotActionListener_Waiting::GetSlotType()
{
	return (INT)E_CONSLOT_EQUIPPED;
}

UBOOL UItemSlotActionListener_Waiting::OnDoubleClickSlot(class UGFxObject* SrcSlotMC,BYTE SrcSlotType,BYTE SrcContainerID,INT SrcSlotID,UBOOL bDefault)
{
	return FALSE;
}