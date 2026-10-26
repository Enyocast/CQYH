#include "stdafx.h"
#include "MMOGameUIClasses.h"
#include "MMOFacade.h"

IMPLEMENT_CLASS(UMMOGFXPlayer_Shop)

//------------------------------------------------------------------------------------------------------------------------
void UMMOGFXPlayer_Shop::ASNPCShopRepair()
{
	if( _NPCShop )
	{
		_NPCShop->eventClickRepair();
		//_NPCShop->eventClickSpecRepair();
	}
}

//------------------------------------------------------------------------------------------------------------------------
void UMMOGFXPlayer_Shop::ASNPCShopRepairAll()
{
	if( _NPCShop )
	{
		_NPCShop->ClickRepairAll();
	}
}
//------------------------------------------------------------------------
void UMMOGFXPlayer_Shop::ASNPCShopClose()
{
	
}


void UMMOGFXPlayer_Shop::Init()
{
	Super::Init();

	check(FALSE && "UMMOGFXPlayer_Shop::Init()");
	//MMOUI::RegisterMoviePlayer(this, MMOUI::GetUIManager()->MoviePlayer_Shop);
}

void UMMOGFXPlayer_Shop::UnInit()
{
	Super::UnInit();

	FScriptDelegate nullDelgate(EC_EventParm);
	MMOUI::GetUIManager()->SetOpenShopDelegate(nullDelgate);	
}

void UMMOGFXPlayer_Shop::ASShowTips_RepairAll( UGFxObject* butt )
{
	MMOUI::GetUIManager()->delegateShowTipsHTML( TFT_RepairAll , butt );
}

void UMMOGFXPlayer_Shop::ASHideTips_RepairAll( UGFxObject* butt )
{
	MMOUI::GetUIManager()->delegateHideTips();
}

UBOOL UMMOGFXPlayer_Shop::OnDragDropOnPanel(class UGFxObject* SrcSlotMC,class UGFxObject* DestSlotMC,BYTE SrcSlotType,BYTE SrcContainerID,INT SrcSlotID,BYTE DestSlotType,BYTE DestContainerID,INT DestSlotID)
{
	if(_NPCShop)
	{
		return _NPCShop->OnDragDropOnPanel(SrcSlotMC, DestSlotMC, SrcSlotType, SrcContainerID, SrcSlotID, DestSlotType, DestContainerID, DestSlotID);
	}

	return FALSE;
}