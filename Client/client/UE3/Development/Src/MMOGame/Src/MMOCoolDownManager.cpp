#include "stdafx.h"
#include "MMOFacade.h"
#include "MMOCoolDownManager.h"
//#include "MMOHintButtonCommand.h"

//static MMOHintButtonCommand_ArenaQueue Command_ArenaQueue;

MMOCoolDownManager::MMOCoolDownManager()
{
	//const FString IconPath = GConfig->GetStr( TEXT("MMOGame.HintButtonIcon") , TEXT("ArenaQueueHintIcon") , GGameIni );
	//_HintIconMap.insert( std::make_pair( EHintButtonType_ArenaQueueHint , IconPath )  );

	//_HintCommandMap.insert( std::make_pair( EHintButtonType_ArenaQueueHint , &Command_ArenaQueue ) );
}

MMOCoolDownManager::~MMOCoolDownManager()
{

}

void MMOCoolDownManager::ClearAllCD()
{
	CDList.Empty();
}

void MMOCoolDownManager::TickCD( FLOAT time )
{
	CTRL_TICK("MMOCoolDownManager::TickCD");

	time = Clamp<FLOAT>( time , 0 , 2 );

	for ( INT idx = CDList.Num()-1 ; idx >= 0 ; idx-- )
	{
		CDList(idx).CurValue -= time*1000;
		if( CDList(idx).CurValue <= 0 )
		{
			CDList.Remove(idx);
		}
	}
}

void MMOCoolDownManager::AddNewCD( INT InType, INT32 InId, INT32 InValue )
{
	for ( INT idx = 0 ; idx < CDList.Num() ; idx++ )
	{
		if( CDList(idx).CDType == InType && CDList(idx).Id == InId )
		{
			CDList(idx).CurValue = InValue;
			CDList(idx).MaxValue = InValue;
			return;
		}
	}

	CoolDownData cdData;
	cdData.CDType = InType;
	cdData.Id = InId;
	cdData.CurValue = InValue;
	cdData.MaxValue = InValue;
	CDList.AddItem(cdData);

	MMOGameEvent_NewCD evt( GameEvent_NewCD , InType , InId );
	MMOUI::PostGameEvent( &evt );

}

CoolDownData* MMOCoolDownManager::GetCDData( COOLDOWN_TYPE InType, INT32 InId )
{
	for ( INT idx = 0 ; idx < CDList.Num() ; idx++ )
	{
		if( CDList(idx).CDType == InType && CDList(idx).Id == InId )
		{
			
			return &CDList(idx);
		}
	}
	return NULL;
}