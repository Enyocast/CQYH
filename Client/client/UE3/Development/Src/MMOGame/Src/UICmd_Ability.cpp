#include "stdafx.h"
#include "FSMIO.h"
IMPLEMENT_CLASS(UUICmd_Ability);

void UUICmd_Ability::Use()
{
	if(CmdAbility == NULL  )
	{
		//`log("UICmd_Ability : Used but no Ability data");
		return;
	}

	//if( CmdAbility->SpellCommonAttribute.PrepareType == ES_PT_Type5 || CmdAbility->SpellCommonAttribute.PrepareType == ES_PT_Type1 )
	//{
	//	MMOUI::GetUIManager()->delegateAddScreenMessage( MMOUI::ParseLocalizedPropertyPath(TEXT("MMOGame.GamePlay.TargetSkillNotMouseClick")) );		
	//	return;
	//}

	if(PC)
	{
		if(CmdAbility)
		{
			UBOOL isManaOK = CmdAbility->CanUseManaCheck( PC->GetPlayer() );
			if( isManaOK == FALSE )
			{
				FString localMsg = TEXT("MMOErrorInfo.ERROR_CODE_DEF.errSpellOutOfMana");
				MMOUI::GetUIManager()->delegateAddScreenMessage( MMOUI::ParseLocalizedPropertyPath( localMsg ), MsgInfoType_Table, localMsg );
			}
			else
			{
				//warnf( NAME_Error, TEXT("===================================UUICmd_Ability::Use") );
				PC->PressAbilityKey( CmdAbility, PC->GetTraceActor(), FALSE);
				FSMIO::getSingleton().Target.SetDesireFClassAbility(CmdAbility,TRUE);

			}
		}
		MMOUI::GetUIManager()->delegateUpdateSkillBarKeyDown( FALSE, CmdID,  SlotID);

	}
}

void UUICmd_Ability::NativeRelease()
{
	MMOUI::GetUIManager()->delegateUpdateSkillBarKeyDown( TRUE, CmdID,  SlotID);
	if(CmdAbility){
		FSMIO::getSingleton().Target.SetDesireFClassAbility(CmdAbility,FALSE);
	}
}