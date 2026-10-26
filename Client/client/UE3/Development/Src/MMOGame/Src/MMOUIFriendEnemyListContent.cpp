#include "stdafx.h"
#include "MMOGameUIClasses.h"
#include "MMOFacade.h"
#include "FriendManager.h"

IMPLEMENT_CLASS(UMMOUIFriendEnemyListContent)

void UMMOUIFriendEnemyListContent::Init()
{
	Super::Init();

	//check(EventAdapter == NULL);
	//TArray<EGameEvent> evts;
	//evts.AddItem(GameEvent_UpdateNearContact);
	////evts.AddItem(GameEvent_PlayerBaseInfo);
	//EventAdapter = new TGameEventAdapter<UMMOUIFriendNearContactContent>(this, evts);

}

void UMMOUIFriendEnemyListContent::OnNativeGameEvent(struct MMOGameEvent* evt)
{
	//if(evt->GetEventType() == GameEvent_UpdateNearContact )
	//{
	//	UpdateNearContactList();
	//}

}

void UMMOUIFriendEnemyListContent::ClearUI()
{

}

void UMMOUIFriendEnemyListContent::UpdateEnemyList()
{
	TArray<MMOFriendMember>& enemyList = FriendManager::getSingleton().EnemyList;
	if(!GFXPlayer)
	{
		return;
	}
	UGFxObject *data = GFXPlayer->CreateArray();
	for ( INT i = 0 ; i < enemyList.Num() ; i++ )
	{
		MMOFriendMember& enemyContact = enemyList(i);
		UGFxObject* item = GFXPlayer->CreateObject( TEXT("Object") );
		item->SetString( TEXT("name") , enemyContact.ActorName );
		item->SetInt( TEXT("lv") , enemyContact.Lv );
		item->SetString( TEXT("classTxt") , MMOUI::ParseLocalizedPropertyPath( FString( TEXT("MMOGame.School.SchoolName") ) + appItoa(enemyContact.ClassId)  ) );
		item->SetString( TEXT("location") , enemyContact.Location );
		item->SetString( TEXT("sign") , enemyContact.Sign );
		item->SetInt( TEXT("roleId") , enemyContact.RoleId );
		item->SetInt( TEXT("stats") , enemyContact.Online );
		item->SetString( TEXT("iconPath") , MMOFacade::getSingleton().GetPlayerIcon(enemyContact.ClassId,enemyContact.Sex) );

		data->SetElementObject( i , item );
	}

	eventCallSetEnemyListData( data );
}