#include "stdafx.h"
#include "MMOGameUIClasses.h"
#include "MMOFacade.h"
#include "FriendManager.h"

IMPLEMENT_CLASS(UMMOUIFriendBlackListContent)

void UMMOUIFriendBlackListContent::Init()
{
	Super::Init();

	//check(EventAdapter == NULL);
	//TArray<EGameEvent> evts;
	//evts.AddItem(GameEvent_UpdateNearContact);
	////evts.AddItem(GameEvent_PlayerBaseInfo);
	//EventAdapter = new TGameEventAdapter<UMMOUIFriendNearContactContent>(this, evts);

}

void UMMOUIFriendBlackListContent::OnNativeGameEvent(struct MMOGameEvent* evt)
{
	//if(evt->GetEventType() == GameEvent_UpdateNearContact )
	//{
	//	UpdateNearContactList();
	//}

}

void UMMOUIFriendBlackListContent::UpdateBlackList()
{
	TArray<MMOFriendMember>& blackList = FriendManager::getSingleton().GetBlackList();
	if(!GFXPlayer)
	{
		return;
	}
	UGFxObject *data = GFXPlayer->CreateArray();
	for ( INT i = 0 ; i < blackList.Num() ; i++ )
	{
		MMOFriendMember& blackContact = blackList(i);
		UGFxObject* item = GFXPlayer->CreateObject( TEXT("Object") );
		item->SetString( TEXT("name") , blackContact.ActorName );
		item->SetInt( TEXT("lv") , blackContact.Lv );
		item->SetString( TEXT("classTxt") , MMOUI::ParseLocalizedPropertyPath( FString( TEXT("MMOGame.School.SchoolName") ) + appItoa(blackContact.ClassId)  ) );
		item->SetString( TEXT("location") , blackContact.Location );
		item->SetString( TEXT("sign") , blackContact.Sign );
		item->SetInt( TEXT("roleId") , blackContact.RoleId );
		item->SetInt( TEXT("stats") , blackContact.Online );
		item->SetString( TEXT("iconPath") , MMOFacade::getSingleton().GetPlayerIcon(blackContact.ClassId,blackContact.Sex) );

		data->SetElementObject( i , item );
	}

	eventCallSetBlackListData( data );
}

void UMMOUIFriendBlackListContent::ClearUI()
{

}