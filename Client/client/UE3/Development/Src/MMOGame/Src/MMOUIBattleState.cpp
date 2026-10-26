#include "stdafx.h"
#include "MMOGameUIClasses.h"
#include "MMOFacade.h"

IMPLEMENT_CLASS(UMMOUIBattleState)



void UMMOUIBattleState::Init()
{
	Super::Init();

}

void UMMOUIBattleState::UnInit()
{
	Super::UnInit();
}

void UMMOUIBattleState::ShowEnterBattle(UBOOL Enter)
{
	
	GotoAndPlayI(2);

	

	UGFxObject* tfObj = GetObject( TEXT("BattleState") );

	if( Enter )
	{
		//tfObj->SetText( MMOUI::ParseLocalizedPropertyPath( TEXT("MMOGame.BattleState.EnterBattle") ) );
		if(tfObj)
		{
			tfObj->GotoAndStopI(1);
		}
	}
	else
	{
		if(tfObj)
		{
			tfObj->GotoAndStopI(2);
		}
		//tfObj->SetText( MMOUI::ParseLocalizedPropertyPath( TEXT("MMOGame.BattleState.LeaveBattle") ) );
	}

	
}