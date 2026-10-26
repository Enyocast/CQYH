#include "stdafx.h"
#include "MMOGameUIClasses.h"

IMPLEMENT_CLASS(UMMOUIGameAnnouncement)

//================================================================================================
void UMMOUIGameAnnouncement::PreOnShow(UBOOL show)
{
	Super::PreOnShow( show );

	if( IsInitialized == FALSE ){
		return;
	}
}
//================================================================================================
void UMMOUIGameAnnouncement::InitContent()
{
	UpdateContent( 0 );
}
//================================================================================================
void UMMOUIGameAnnouncement::UpdateContent( INT textIdx )
{
	FString lookUpKey = TEXT("MMOGame.GameAnnouncement.BodyText");
	lookUpKey += appItoa( textIdx );
	FString contentText = MMOUI::ParseLocalizedPropertyPath( lookUpKey );
	if( contentText.IsEmpty() ){
		contentText = MMOUI::ParseLocalizedPropertyPath( TEXT("MMOGame.GameAnnouncement.BodyText0") );
	}

	eventCallASSetAnnouncemment( contentText );
}
//================================================================================================
void UMMOUIGameAnnouncement::Init()
{
	Super::Init();

	TArray<struct FASValue> asFunArgs;
	FASValue asTitleName(EC_EventParm);
	asTitleName.Type = AS_String;
	asTitleName.S = MMOUI::ParseLocalizedPropertyPath( TEXT("MMOGame.GameAnnouncement.UITitleName") );
	asFunArgs.AddItem( asTitleName );
	this->Invoke( TEXT("SetWindowTitle"), asFunArgs );
}