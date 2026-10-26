#include "stdafx.h"
#include "MMOGameUIClasses.h"
#include "MMOFacade.h"

IMPLEMENT_CLASS(UMMOUIHeroInfo)

INT UMMOUIHeroInfo::GetMode(INT HeroAi)
{
	INT AiMode = 1;
	switch(HeroAi)
	{
	case hatActive:
		AiMode = 1;
		break;
	case hatPassive:
		AiMode = 2;
		break;
	case hatFollow:
		AiMode = 3;
		break;
	case hatStandstill:
		AiMode = 4;
		break;
	}
	return AiMode;
}

//-----------------------------------------------------
void UMMOUIHeroInfo::HeroUpdateData()
{
	AMMOPlayer *pMainPlayer = MMOFacade::getSingleton().GetMainPlayer();
	UGFxObject * HeroData = GFXPlayer->CreateObject("Object");
	if(HeroData && pMainPlayer && pMainPlayer->HeroAttributes ){
		HeroData->SetBool("HasHero", pMainPlayer->ServerHeroID>0 );
		HeroData->SetBool("IsSummon",pMainPlayer->HeroSummon );
		HeroData->SetInt("ClassID",pMainPlayer->HeroAttributes->ClassType );
		HeroData->SetInt("Level",  pMainPlayer->HeroAttributes->LevelAttributes.Level );
		HeroData->SetString("Name", pMainPlayer->HeroName);
		HeroData->SetInt("curHp", pMainPlayer->HeroAttributes->GetCurHp());
		HeroData->SetInt("maxHp", pMainPlayer->HeroAttributes->GetMaxHp());
		HeroData->SetInt("HeroAi", GetMode(pMainPlayer->HeroAi));

		FString path = TEXT("img://MMOUIFaceIcon.Player.class");
		path += appItoa( pMainPlayer->HeroAttributes->ClassType );
		if( pMainPlayer->HeroAttributes->GenderType == EGT_Male )
		{
			path += TEXT("man");
		}
		else
		{
			path += TEXT("fe");
		}
		HeroData->SetString("IconName", path);

	}
	eventCallSetHeroInfo(HeroData);

	if( pMainPlayer &&
		pMainPlayer->HeroSummon &&
		pMainPlayer->ServerHeroID>0 )
	{
		Show(TRUE);
	}
	else
	{
		Show(FALSE);
	}

}

void UMMOUIHeroInfo::OtherPlayerHpChange(class AMMOPlayer* pl,INT HP)
{
	AMMOPlayer *pMainPlayer = MMOFacade::getSingleton().GetMainPlayer();
	if(pl && pMainPlayer && pl->ServerID==pMainPlayer->ServerHeroID)
	{
		HeroUpdateData();
	}
}

void UMMOUIHeroInfo::ASHeroUncall()
{
	CMessageHandler::GetInstance().Send_HeroUncall();
}
void UMMOUIHeroInfo::ASHeroBag()
{

}

void UMMOUIHeroInfo::FunMode(INT Mode)
{
	INT AiMode = hatStandstill;
	switch(Mode)
	{
	case 1:
		AiMode = hatActive;
		break;
	case 2:
		AiMode = hatPassive;
		break;
	case 3:
		AiMode = hatFollow;
		break;
	case 4:
		AiMode = hatStandstill;
		break;
	}
	CMessageHandler::GetInstance().Send_ChangeHeroAi(AiMode);
}

UBOOL UMMOUIHeroInfo::SkipCaptureInputKey(const FString& key,BYTE eIE,const FString& strHoverControllerName,FVector2D ClickPosInMovieSpace)
{
	//if (strHoverControllerName != "uncall_btn" &&
	//	strHoverControllerName != "bag_btn" &&
	//	strHoverControllerName != "mode1_btn" &&
	//	strHoverControllerName != "mode2_btn" &&
	//	strHoverControllerName != "mode3_btn" &&
	//	strHoverControllerName != "mode4_btn" )
	if( IsVisible )
	{
		if(	strHoverControllerName=="bk_mc" || 
			strHoverControllerName=="heroProIcon" ||
			strHoverControllerName=="HeroName_mc"
			)
		{
			return TRUE;
		}
	}
	return Super::SkipCaptureInputKey(key, eIE, strHoverControllerName, ClickPosInMovieSpace );
}
