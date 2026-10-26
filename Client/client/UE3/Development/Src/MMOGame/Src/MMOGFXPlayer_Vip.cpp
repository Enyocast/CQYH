#include "stdafx.h"
#include "MMOGameUIClasses.h"
#include "MMOVipManager.h"

IMPLEMENT_CLASS(UMMOGFXPlayer_Vip)


//===================================================================================
void UMMOGFXPlayer_Vip::ASBuyVipLevel( INT level )
{
	INT itemID = MMOVipManager::getSingleton().GetVipItemID( level );
	if( itemID <= 0 ){
		return;
	}

	//
	CMessageHandler::GetInstance().Send_MallBuyGoods( itemID, 1 );

}

//===================================================================================
void UMMOGFXPlayer_Vip::ASBugYuanBao()
{

}

//===================================================================================
void UMMOGFXPlayer_Vip::ASVIPTips( UGFxObject *hintMc )
{
	if( hintMc == NULL ){
		return;
	}

	MMOVipManager &mmoVipMgr = MMOVipManager::getSingleton();

	eVipType curMyVip = mmoVipMgr.GetMyCurrentVipType();
	//
	FString vipHintStr;
	for( INT i = eVIPTyp_LV1; i < eVIPTyp_LVMax; ++i ){
		if( curMyVip == i ){
			continue;
		}
		if( mmoVipMgr.GetMyVipLeftSecond( i ) <= 0 ){
			continue;
		}

		//
		FString thisVipHintStr;
		FString vipName;
		UINT leftDay;
		UINT leftHour;
		mmoVipMgr.GetVipDescriptionString( i, vipName, leftDay, leftHour );

		thisVipHintStr = FString::Printf( *MMOUI::ParseLocalizedPropertyPath( TEXT("MMOGame.Vip.VipTipsFormat") ), *vipName );

		if( leftDay > 0 ){
			thisVipHintStr += FString::Printf( *MMOUI::ParseLocalizedPropertyPath( TEXT("MMOGame.Vip.VipLeftDay") ), leftDay );
		}

		if( leftHour > 0 ){
			thisVipHintStr += FString::Printf( *MMOUI::ParseLocalizedPropertyPath( TEXT("MMOGame.Vip.VipLeftHour") ), leftHour );
		}

		vipHintStr += thisVipHintStr;
		vipHintStr += TEXT("<br>");
	}

	//
	if( vipHintStr.Len() <= 0 ){
		vipHintStr = MMOUI::ParseLocalizedPropertyPath( TEXT("MMOGame.Vip.HasNoVipTips") );
	}

	//
	hintMc->SetString( TEXT("tipsHtml"), vipHintStr );
	MMOUI::GetUIManager()->delegateShowTipsHTML( TFT_AutoSizeTips, hintMc );
}
//===================================================================================
void UMMOGFXPlayer_Vip::ASHideVIPTips()
{
	MMOUI::GetUIManager()->delegateHideTips();
}
//===================================================================================
void UMMOGFXPlayer_Vip::Init()
{
	Super::Init();

	check(FALSE && "UMMOGFXPlayer_Vip::Init()");
	//MMOUI::RegisterMoviePlayer(this, MMOUI::GetUIManager()->MoviePlayer_Vip);
}

void UMMOGFXPlayer_Vip::UnInit()
{
	Super::UnInit();
}

void UMMOGFXPlayer_Vip::ASVipShopClick(int type)
{
	MMOVipManager::getSingleton().ShowVipShopByType((eVipShopType)type);
}