#include "SoundMatEditState.h"
#include "../../Engine/Inc/EngineClasses.h"
#include "../../Engine/Inc/EngineMeshClasses.h"
#include "../../Engine/Inc/EngineAnimClasses.h"
#include "../../Engine/Inc/EngineAIClasses.h"
#include "../../GameFramework/Inc/GameFrameworkClasses.h"
#include "../../MMOGame/Inc/MMOGameClasses.h"

SoundMaterialEditState::SoundMaterialEditState( SoundMaterialMatrix* ed )
: SoundMaterialEditor(ed)
, BorderColor(0, 0, 0)
, BkgColor(112, 112, 112)
, BorderColorHighlight(255, 0, 0)
, BkgColorHighlight(255, 128, 128)
,YellowColor(255, 242, 0)
,GreenColor(0, 255, 64)
,WhiteColor(236, 236, 236)
,RedColor(255, 0, 0)
{
	EnumObj = FindObject<UEnum>(UTypeDefine::StaticClass(), TEXT("EItemMaterialType"), TRUE);
}
//------------------------------------------------------------------------
SoundMaterialEditState::~SoundMaterialEditState()
{

}
//------------------------------------------------------------------------
FString SoundMaterialEditState::GetEnumDisplayName( BYTE enumID )
{
	FString EnumValueName = EnumObj->GetEnum(enumID).ToString();
	const FString& AlternateEnumValueName = EnumObj->GetMetaData( TEXT("DisplayName"), enumID );
	if ( AlternateEnumValueName.Len() == 0 )
	{
		FString LocalizedName = LocalizeProperty( *(EnumObj->GetName()), *(EnumValueName) );	

		if(LocalizedName.Len() > 0)
		{
			return LocalizedName;
		}
		else
		{
			return EnumValueName;
		}
	}
	else
	{
		FString LocalizedName = LocalizeProperty( *(EnumObj->GetName()), *(AlternateEnumValueName) );
		if(LocalizedName.Len() > 0)
		{
			return LocalizedName;
		}
		else
		{
			return AlternateEnumValueName;
		}
	}
}


FString SoundMaterialEditState::GetEnumDisplayName(UEnum* InObject, INT InIdx)
{
	FString EnumValueName = InObject->GetEnum(InIdx).ToString();
	return EnumValueName;
	/*
	const FString& AlternateEnumValueName = InObject->GetMetaData( TEXT("DisplayName"), InIdx );
	if ( AlternateEnumValueName.Len() == 0 )
	{
		FString LocalizedName = LocalizeProperty( *(InObject->GetName()), *(EnumValueName) );	

		if(LocalizedName.Len() > 0)
		{
			return LocalizedName;
		}
		else
		{
			return EnumValueName;
		}
	}
	else
	{
		FString LocalizedName = LocalizeProperty( *(InObject->GetName()), *(AlternateEnumValueName) );
		if(LocalizedName.Len() > 0)
		{
			return LocalizedName;
		}
		else
		{
			return AlternateEnumValueName;
		}
	}
	*/


}
