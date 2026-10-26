#include "stdafx.h"
#include "MMOGameUIClasses.h"
#include "MMOFacade.h"

IMPLEMENT_CLASS(UMMOUIBattleTeamCreate)

#define CombineIcon( x , y )  ((x)*1000+(y))

void UMMOUIBattleTeamCreate::CreateTeam( )
{
	if(InputText)
	{
		FString teamName = InputText->GetText();
		INT IconID = CombineIcon( FlagBgIndex , FlagIconIndex );
		CMessageHandler::GetInstance().Send_CreateBattleTeam(teamName,IconID);

		Show(FALSE);
	}
	
}

void UMMOUIBattleTeamCreate::NativeInitOnce()
{
	UGFxObject* mc = NULL;
	mc = GetObject( TEXT("ConfirmButton") );
	if( mc )
		mc->SetString( TEXT("label") , MMOUI::ParseLocalizedPropertyPath( TEXT("MMOGame.BattleTeam.Create") ) );

	mc = GetObject( TEXT("CancelButton") );
	if( mc )
		mc->SetString( TEXT("label") , MMOUI::ParseLocalizedPropertyPath( TEXT("MMOGame.BattleTeam.Cancel") ) );

	mc = GetObject( TEXT("CheckName") );
	if( mc )
		mc->SetString( TEXT("label") , MMOUI::ParseLocalizedPropertyPath( TEXT("MMOGame.BattleTeam.Check") ) );
}

void UMMOUIBattleTeamCreate::FlagBgChange( INT index )
{
	FlagBgIndex = index;
	//todo
}


void UMMOUIBattleTeamCreate::FlagIconChange( INT index )
{

	FlagIconIndex = index;
	//todo
}