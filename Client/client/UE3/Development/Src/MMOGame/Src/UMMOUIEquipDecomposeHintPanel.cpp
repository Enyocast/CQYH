#include "stdafx.h"
#include "MMOGameUIClasses.h"
#include "MMOFacade.h"
#include "EquipDecomposeManager.h"


IMPLEMENT_CLASS(UMMOUIEquipDecomposeHintPanel)

void UMMOUIEquipDecomposeHintPanel::DecomposeOk()
{
	EquipDecomposeManager::getSingleton().RealDecompose(iConId,iSlotId);
}

void UMMOUIEquipDecomposeHintPanel::SetDecomposedEquipPos(INT cid,INT sid)
{
	iConId = cid;
	iSlotId = sid;
}

void UMMOUIEquipDecomposeHintPanel::SetContent(const FString& str)
{
	strContent = str;
	UpdateUI();
}

void UMMOUIEquipDecomposeHintPanel::PostOnShow(UBOOL v)
{
	Super::PostOnShow(v);
	if(v)
	{
		UpdateUI();
	}
}

void UMMOUIEquipDecomposeHintPanel::UpdateUI()
{
	UGFxObject* mc = GetObject(TEXT("HintText"));
	if(mc)
	{
		mc->SetString( TEXT("htmlText") , strContent );
	}
}