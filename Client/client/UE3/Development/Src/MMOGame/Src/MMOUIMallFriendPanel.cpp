#include "stdafx.h"
#include "MMOGameUIClasses.h"
#include "MMOFacade.h"
#include "FriendManager.h"
#include "UILayout.h"
#include "MallController.h"

IMPLEMENT_CLASS(UMMOUIMallFriendPanel)


void UMMOUIMallFriendPanel::Init()
{
	Super::Init();
	
}

void UMMOUIMallFriendPanel::NativeInitLoad()
{	
	Super::NativeInitLoad();

	g_layoutList.push_back(new UILayoutLeftRight(this, MMOUI::GetUIManager()->Panel_MallBuyGoods));
}


void UMMOUIMallFriendPanel::PostOnShow(UBOOL v)
{
	Super::PostOnShow(v);


}

void UMMOUIMallFriendPanel::OnShowFriendPanel(INT nGoodsID, INT nNum)
{
	UGFxObject* dataProvider =GFXPlayer->CreateArray();
	if(dataProvider == NULL)
		return;

	const TArray<MMOFriendGroup>& friendGroup = FriendManager::getSingleton().GetAllFriendList();
	INT nIndex = 0;
	for (INT n = 0; n < friendGroup.Num(); ++n)
	{
		for (INT i = 0; i < friendGroup(n).FriendList.Num(); ++i)
		{
			const MMOFriendMember& member = friendGroup(n).FriendList(i);
			UGFxObject* object = GFXPlayer->CreateObject(TEXT("ActionScript3.Mall.MallFriendListItemData"));
			if(object == NULL)
				continue;
			object->SetInt("RoleID",member.RoleId);
			object->SetString("RoleName",member.ActorName);
			object->SetString("RoleJob",MMOUI::ParseLocalizedPropertyPath( FString( TEXT("MMOGame.School.SchoolName") ) + appItoa( member.ClassId)));
			object->SetString("RoleLevel",FString::Printf(TEXT("%d"),member.Lv));
			dataProvider->SetElementObject(nIndex++,object);
		}
	}
	eventCallUpdateFriendList(dataProvider);
	eventCallSetGoodsInfo(nGoodsID,nNum);
	if(listFriend)
		listFriend->SetInt("selectedIndex",-1);
}

//////////////////////////////////////////////////////////////////////////

void UMMOUIMallFriendPanel::ASClickGiveFriendGoods(const FString& roleName,INT nGoodsID,INT nNum)
{
	UMMOUIMallBuyPanel* mallBuyPanel = (UMMOUIMallBuyPanel*)MMOUI::FindUIPanelEx(MMOUI::GetUIManager()->Panel_MallBuyGoods);
	if (!mallBuyPanel)
	{
		return;
	}

	if(friendName.IsEmpty())
	{
		if(mallBuyPanel->giveBtn)
			mallBuyPanel->giveBtn->SetString( TEXT("label") ,MMOUI::ParseLocalizedPropertyPath( TEXT("MMOGame.Mall.GiveFriendBtnText2"))); 
		if(mallBuyPanel->buyBtn)
			mallBuyPanel->buyBtn->SetString( TEXT("label"),MMOUI::ParseLocalizedPropertyPath( TEXT("MMOGame.Mall.BuyBtnText2")));
	}
	friendName = roleName;
	mallBuyPanel->friendName = roleName;
	mallBuyPanel->eventCallSetBuyAimPlayerName(friendName);
	
	Show(FALSE);
	//ConfirmMallGiveFriendHint();
}

void UMMOUIMallFriendPanel::ConfirmMallGiveFriend(class UGFxObject* mc)
{
	if(mc == NULL)
		return;

	UMMOUIMallPanel* mallPanel = (UMMOUIMallPanel*)MMOUI::FindUIPanelEx(MMOUI::GetUIManager()->Panel_Mall);
	UMMOUIMallBuyPanel* buyPanel = (UMMOUIMallBuyPanel*)MMOUI::FindUIPanelEx(MMOUI::GetUIManager()->Panel_MallBuyGoods);
	if (mallPanel && buyPanel)
	{
		if (mallPanel->GoodsID > 0)
		{
			MallController::getSingleton().SendGiveFriendGoods(friendName, mallPanel->GoodsID, buyPanel->GetGoodsNum());
		}
	}

	MallGiveFriendConfirmBox = NULL;
}

void UMMOUIMallFriendPanel::CancelMallGiveFriend(class UGFxObject* mc)
{
	if(mc == NULL)
		return;
	MallGiveFriendConfirmBox = NULL;
}