#include "stdafx.h"
#include "MMOGameUIClasses.h"
#include "MMOFacade.h"

IMPLEMENT_CLASS(UMMOGFXPlayer_Soul)

//===============================================================================================================
//soul embed
void UMMOGFXPlayer_Soul::ASConfirmSoulEmbed()
{
	if( _SoulEmbedPanel == NULL ){
		return;
	}

	//
	_SoulEmbedPanel->ConfirmSoulEmbed();
}

//===============================================================================================================
void UMMOGFXPlayer_Soul::ASResetSoulEmbed()
{
	if( _SoulEmbedPanel == NULL ){
		return;
	}

	//
	_SoulEmbedPanel->ResetSoulEmbed();
}

//===============================================================================================================
void UMMOGFXPlayer_Soul::ASOnEmbedPanelTabBtnClick( int tabIdx )
{
	if( _SoulEmbedPanel == NULL ){
		return;
	}

	//
	_SoulEmbedPanel->OnTabBtnClick( tabIdx );
}

//===============================================================================================================
void UMMOGFXPlayer_Soul::ASConfirmUnEmbed()
{
	if( _SoulEmbedPanel == NULL ){
		return;
	}

	//
	_SoulEmbedPanel->ConfirmSoulUnEmbed();
}

//===============================================================================================================
void UMMOGFXPlayer_Soul::ASCancelUnEmbed()
{
	if( _SoulEmbedPanel == NULL ){
		return;
	}

	//
	_SoulEmbedPanel->ResetSoulUnEmbed();
}

//===============================================================================================================
void UMMOGFXPlayer_Soul::ASSelectUnEmbedSoul( int idx )
{
	if( _SoulEmbedPanel == NULL ){
		return;
	}

	//
	_SoulEmbedPanel->SelectSoulToUnEmbed( idx );
}

//===============================================================================================================
//soul level up
void UMMOGFXPlayer_Soul::ASConfirmSoulLevelUp()
{
	if( _SoulEmbedPanel == NULL ){
		return;
	}

	//
	_SoulEmbedPanel->ConfirmSoulLevelUp();
}

//===============================================================================================================
void UMMOGFXPlayer_Soul::ASResetSoulLevelUp()
{
	if( _SoulEmbedPanel == NULL ){
		return;
	}

	//
	_SoulEmbedPanel->ResetSoulLevelUp();
}

//===============================================================================================================
void UMMOGFXPlayer_Soul::Init()
{
	Super::Init();

	check(FALSE && "UMMOGFXPlayer_Soul::Init()");
	//MMOUI::RegisterMoviePlayer(this, MMOUI::GetUIManager()->MoviePlayer_Soul);
}

void UMMOGFXPlayer_Soul::UnInit()
{
	Super::UnInit();
}