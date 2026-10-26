#include "stdafx.h"
#include "MMOGameUIClasses.h"
#include "MMOFacade.h"
#include "MMOMsgBoxManager.h"


IMPLEMENT_CLASS(UMMOGFXPlayer_Hero)


void UMMOGFXPlayer_Hero::Init()
{
	Super::Init();

	check(FALSE && "UMMOGFXPlayer_Hero::Init()");
	//MMOUI::RegisterMoviePlayer(this, MMOUI::GetUIManager()->MoviePlayer_Hero);	

	MMOUI::GetUIManager()->SetRefreshHeroAttributeDelegate(FScriptDelegate(this, TEXT("RefreshAttribute")));
	MMOUI::GetUIManager()->SetRefreshHeroSlotDelegate(FScriptDelegate(this, TEXT("RefreshSlot")));
	MMOUI::GetUIManager()->SetRefreshHeroDelegate(FScriptDelegate(this, TEXT("RefreshHero")));
	MMOUI::GetUIManager()->SetRefreshSummonDelegate(FScriptDelegate(this, TEXT("RefreshSummon")));

}

void UMMOGFXPlayer_Hero::UnInit()
{
	Super::UnInit();

	FScriptDelegate nullDelgate(EC_EventParm) ;
	MMOUI::GetUIManager()->SetRefreshHeroAttributeDelegate(nullDelgate);
	MMOUI::GetUIManager()->SetRefreshHeroSlotDelegate(nullDelgate);
	MMOUI::GetUIManager()->SetRefreshHeroDelegate(nullDelgate);
	MMOUI::GetUIManager()->SetRefreshSummonDelegate(nullDelgate);
}


void UMMOGFXPlayer_Hero::Test()
{
	check(FALSE && "UMMOGFXPlayer_Hero::Init()");
	//MMOUI::CloseMoviePlayersByName(MMOUI::GetUIManager()->MoviePlayer_Hero);	
}
//------------------------------------------------------------------------------------------------------------------------
void UMMOGFXPlayer_Hero::PostAdvance ( FLOAT DeltaTime )
{
	UGFxMoviePlayer::PostAdvance(DeltaTime);

	FRotator newRot;

	if( TurnButton == TBS_Left && ShowAvatar)
	{
		newRot = ShowAvatar->Rotation;
		newRot.Yaw -= 200;
		ShowAvatar->SetRotation(newRot);
	}
	else	if( TurnButton == TBS_Right && ShowAvatar)
	{
		newRot = ShowAvatar->Rotation;
		newRot.Yaw += 200;
		ShowAvatar->SetRotation(newRot);
	}

}

void UMMOGFXPlayer_Hero::ShowHero()
{
	AMMOPlayer* player = MMOFacade::getSingleton().GetMainPlayer();
	if(player ) //&& player->ServerHeroID>0)
	{
		if(Hero)Hero->Show(TRUE);// >ToogleVisible();
	}
}
////------------------------------------------------------------------------------------------------------------------------
void UMMOGFXPlayer_Hero::ASHeroSummon()
{
	AMMOPlayer* player = MMOFacade::getSingleton().GetMainPlayer();
	if(player&&player->ItemManager){
		if(player->ItemManager->EquippedItemList_Hero.Num()>0)
		{
			UEquip* tEquip = player->ItemManager->EquippedItemList_Hero(E_NES_MAIN_HAND);
			if(tEquip==NULL)
			{
				MMOUI::GetUIManager()->delegateAddScreenMessage( MMOUI::ParseLocalizedPropertyPath(TEXT("MMOGame.Hero.HeroPrompt1")) ,MsgInfoType_Table,TEXT("MMOGame.Hero.HeroPrompt1"));
			}
		}
	}

	CMessageHandler::GetInstance().Send_HeroSummon();
}

void UMMOGFXPlayer_Hero::ASHeroUncall()
{
	CMessageHandler::GetInstance().Send_HeroUncall();
}
void UMMOGFXPlayer_Hero::ASHeroFire()
{
	UGFxObject* MsgBox = NULL;
	//FString InputText = FString::Printf( TEXT("%s%s"),
	//	*MMOUI::ParseLocalizedPropertyPath( TEXT("MMOGame.GamePlay.PleaseInput")),
	//	*MMOUI::ParseLocalizedPropertyPath( TEXT("MMOGame.GamePlay.DestroyAffirmText") ) );

	FScriptDelegate Fun(EC_EventParm);
	Fun.Object = this;

	FScriptDelegate FunNone(EC_EventParm);

	Fun.FunctionName = TEXT("OnHeroFireOk");
	MMOMsgBoxManager::getSingleton().AddMessageBox(
		MMOUI::ParseLocalizedPropertyPath( TEXT("MMOGame.GamePlay.HeroFire") ),
		0, Fun, FunNone );

}

void UMMOGFXPlayer_Hero::OnHeroFireOk(class UGFxObject* mc)
{
	CMessageHandler::GetInstance().Send_HeroFire();
}


void UMMOGFXPlayer_Hero::ASHeroRename()
{

}

void UMMOGFXPlayer_Hero::ASHeroBag()
{

}




