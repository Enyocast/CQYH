#include "stdafx.h"
#include "vehicle_slot.h"

CVehicleSlot::CVehicleSlot(void)
{
	m_poOwner = NULL;
	m_poPassenger = NULL;
	m_bMoveController = FALSE;
}

CVehicleSlot::~CVehicleSlot(void)
{

}

void CVehicleSlot::Init(CCharacter* poOwner, BOOL bIsMoveController)
{
	m_poOwner = poOwner;
	m_bMoveController = bIsMoveController;
}
