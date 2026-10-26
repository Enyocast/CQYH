#include "stdafx.h"
#include "MMOGameUIClasses.h"
#include "MMOFacade.h"
#include "CommonGameEvents.h"
#include "TeamManager.h"
#include "UITextParser.h"


IMPLEMENT_CLASS(UMMOUITeamAuctionList)

void UMMOUITeamAuctionList::Init()
{
	Super::Init();

	check(EventAdapter == NULL);
	TArray<EGameEvent> evts;
	evts.AddItem(GameEvent_TeamAuctionListChange);
	evts.AddItem(GameEvent_TeamLeave);

	EventAdapter = new TGameEventAdapter<UMMOUITeamAuctionList>(this, evts);
}

void UMMOUITeamAuctionList::UnInit()
{
	Super::UnInit();
}

void UMMOUITeamAuctionList::OnNativeGameEvent(struct MMOGameEvent* evt)
{
	switch( evt->GetEventType() )
	{		
	case GameEvent_TeamAuctionListChange:
		{
			UpdateList();
		}
		break;
	case GameEvent_TeamLeave:
		{
			this->SetVisible(FALSE);
		}
		break;
	}
}

void UMMOUITeamAuctionList::PostOnShow(UBOOL v)
{
	if(v)
	{
		UpdateList();
	}
}

void UMMOUITeamAuctionList::UpdateList()
{
	if( !GFXPlayer )
	{
		return;
	}
	UGFxObject* listArray = GFXPlayer->CreateArray();
	if( !listArray )
	{
		return;
	}

	TArray<MMOTeamAuctionItem>& auctionItemList = TeamManager::getSingleton().GetTeamAuctionItemList();
	MMOTeamAuctionItem* curItem = TeamManager::getSingleton().GetCurAuctionItem();
	for ( INT i = 0 ; i < auctionItemList.Num() ; i++ )
	{
		UGFxObject* itemData = GFXPlayer->CreateObject(TEXT("Object"));
		UItem* itemTemp = MMOFacade::getSingleton().FindItemTemplate( auctionItemList(i).Item.m_nTemplateID );
		if( itemData && itemTemp )
		{
			itemData->SetString( TEXT("label") ,TEXT("Item") );
			itemData->SetInt( TEXT("index") , i );
			itemData->SetInt( TEXT("itemId") , auctionItemList(i).Index );
			itemData->SetInt( TEXT("type") ,0 );
			itemData->SetInt( TEXT("deepth") ,0 );
			itemData->SetBool( TEXT("visible") , TRUE );

			itemData->SetString( TEXT("itemPrice") , TEXT("") );
			itemData->SetString( TEXT("itemName") , UITextParser::HTMLFormatItemName(itemTemp) );	
			itemData->SetInt( TEXT("itemIndex") , i+1 );

			UGFxObject* slotData = GFXPlayer->CreateObject(TEXT("ActionScript3.Slot.ItemSlotData"));
			if(slotData)
			{
				slotData->SetString(TEXT("SlotRenderClassName"),  TEXT("NormalItemSlotRender"));
			}
			if( slotData )
			{
				slotData->SetInt( TEXT("slotType"), ESPType_TeamAuctionList );
				slotData->SetInt( TEXT("slotIndex"), i );
				slotData->SetBool( TEXT("HaveData"), TRUE );
				slotData->SetInt( TEXT("EquipID"), ESBarSlotTp_Item );										
				slotData->SetInt( TEXT("quantity"), 1 );
				FString cs = FString(TEXT("img://")) + MMOFacade::getSingleton().GetItemIconNamePersonalized( itemTemp );
				slotData->SetString( TEXT("iconName"), cs );
				slotData->SetInt( TEXT("itemTemplateID"), itemTemp->GetTemplateID() );
				slotData->SetInt( TEXT("itemColor"), itemTemp->ItemColor );

				itemData->SetObject( TEXT("slotData") , slotData );
			}

			switch( auctionItemList(i).BidState )
			{
			case ETAIS_NoPermit:
				{
					itemData->SetBool( TEXT("giveup") , FALSE );
					itemData->SetString( TEXT("acutionStateText") , MMOUI::ParseLocalizedPropertyPath( TEXT("MMOGame.TeamAuction.NoLimit") ) );
				}
				break;
			case ETAIS_CanBid:
				{
					itemData->SetBool( TEXT("giveup") , TRUE );
					if( curItem && curItem->Index == auctionItemList(i).Index )
					{
						itemData->SetString( TEXT("acutionStateText") , MMOUI::ParseLocalizedPropertyPath( TEXT("MMOGame.TeamAuction.Bidding") ) );
					}
					else
					{
						itemData->SetString( TEXT("acutionStateText") , MMOUI::ParseLocalizedPropertyPath( TEXT("MMOGame.TeamAuction.Wait") ) );
					}
				}
				break;
			case ETAIS_GiveUp:
				{
					itemData->SetBool( TEXT("giveup") , FALSE );
					itemData->SetString( TEXT("acutionStateText") , MMOUI::ParseLocalizedPropertyPath( TEXT("MMOGame.TeamAuction.Giveup") ) );
				}
				break;
			}
						
			itemData->SetString( TEXT("state") , TEXT("") );
	
			listArray->SetElementObject( i , itemData );
		}
	}

	eventCallUpdateData(listArray);
}

void UMMOUITeamAuctionList::ASTeamAuctionGiveUpAll()
{
	TeamManager::getSingleton().RequestGiveUpAll();
}

