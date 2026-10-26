#include "stdafx.h"
#include "MMOGameUIClasses.h"
#include "MMOFacade.h"
#include "FriendManager.h"

IMPLEMENT_CLASS(UMMOUIFriendNearContactContent)

void UMMOUIFriendNearContactContent::Init()
{
	Super::Init();

	check(EventAdapter == NULL);
	TArray<EGameEvent> evts;
	evts.AddItem(GameEvent_UpdateNearContact);
	//evts.AddItem(GameEvent_PlayerBaseInfo);
	EventAdapter = new TGameEventAdapter<UMMOUIFriendNearContactContent>(this, evts);

}

void UMMOUIFriendNearContactContent::OnNativeGameEvent(struct MMOGameEvent* evt)
{


}

void UMMOUIFriendNearContactContent::UpdateNearContactList()
{
	TArray<MMOFriendMember>& nearContactList = FriendManager::getSingleton().NearContactList;
	if(!GFXPlayer)
	{
		return;
	}
	UGFxObject *data = GFXPlayer->CreateArray();
	for ( INT i = 0 ; i < nearContactList.Num() ; i++ )
	{
		MMOFriendMember& nearContact = nearContactList(i);
		UGFxObject* item = GFXPlayer->CreateObject( TEXT("Object") );
		item->SetString( TEXT("name") , nearContact.ActorName );
		item->SetInt( TEXT("lv") , nearContact.Lv );
		item->SetString( TEXT("classTxt") , MMOUI::ParseLocalizedPropertyPath( FString( TEXT("MMOGame.School.SchoolName") ) + appItoa(nearContact.ClassId)  ) );
		item->SetString( TEXT("location") , nearContact.Location );
		item->SetString( TEXT("sign") , nearContact.Sign );
		item->SetInt( TEXT("roleId") , nearContact.RoleId );
		item->SetInt( TEXT("stats") , nearContact.Online );
		item->SetString( TEXT("iconPath") , MMOFacade::getSingleton().GetPlayerIcon(nearContact.ClassId,nearContact.Sex) );

		data->SetElementObject( i , item );
	}

	eventCallSetNearListData( data );
}

void UMMOUIFriendNearContactContent::ClearUI()
{

}

void UMMOUIFriendNearContactContent::ASNearContactDClick(class UGFxObject* mc)
{
	if( mc )
	{
		INT index = mc->GetInt(TEXT("itemid"));
		INT groupId = mc->GetInt(TEXT("itemdataid"));

		AMMOPlayer* player = MMOFacade::getSingleton().GetMainPlayer();
		if( player )
		{
			MMOFriendMember* member = FriendManager::getSingleton().GetNearContact( index );
			if( member )
			{
				MMOUI::GetUIManager()->delegateSelectFriendChat( member->RoleId , member->ActorName );
			}
		}
	}
}