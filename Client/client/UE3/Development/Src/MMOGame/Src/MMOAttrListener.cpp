#include "stdafx.h"
#include "MMOGameUIClasses.h"
#include "MMOFacade.h"

#include "MMOAttrListener.h"
#include "MMOPlayerInfoManager.h"
#include "MMOPowerManager.h"

INT MMOAttrListener_Mine::GetAttribute( INT attrId )
{
	AMMOPlayer* player = MMOFacade::getSingleton().GetMainPlayer();
	if( player && player->ActorAttributes )
	{
		return player->ActorAttributes->GetAttribute(attrId);
	}
	return 0;
}

INT MMOAttrListener_Mine::GetPkValue()
{
	AMMOPlayer* player = MMOFacade::getSingleton().GetMainPlayer();
	if( player && player->ActorAttributes )
	{
		return player->ActorAttributes->GetPkValue();
	}

	return 0;
	
}

INT MMOAttrListener_Mine::GetLevel()
{
	AMMOPlayer* player = MMOFacade::getSingleton().GetMainPlayer();
	if(player)
	{
		return player->GetActorLevel();
	}
	return 0;
}

INT MMOAttrListener_Mine::GetClassId()
{
	AMMOPlayer* player = MMOFacade::getSingleton().GetMainPlayer();
	if(player)
	{
		return player->GetClassId();
	}

	return 0;
}

INT MMOAttrListener_Mine::GetFatigue()
{
	 return MMOFacade::getSingleton().GetPlayerMoney(E_MONEYTYPE_FATIGUE);
}

INT MMOAttrListener_Mine::GetPower()
{
	return MMOPowerManager::getSingleton().GetPower();
}

//-----------------------------------------------------------

INT MMOAttrListener_OtherPlayer::GetAttribute( INT attrId )
{
	PlayerDetailInfo* di = MMOPlayerInfoManager::getSingleton().FindCurPlayerDetailInfo( );
	if( di )
	{
		return di->AttrList[attrId];
	}
	return 0;
}

INT MMOAttrListener_OtherPlayer::GetPkValue()
{
	INT roleId = MMOPlayerInfoManager::getSingleton().GetCurRole();

	AMMOActor* actor = MMOFacade::getSingleton().GetCharacter(roleId);

	if (actor && actor->ActorAttributes)
	{
		return actor->ActorAttributes->GetPkValue();
	}
	
	return 0;
}

INT MMOAttrListener_OtherPlayer::GetLevel()
{
	PlayerDetailInfo* di = MMOPlayerInfoManager::getSingleton().FindCurPlayerDetailInfo( );
	if( di )
	{
		return di->Level;
	}
	return 0;
}

INT MMOAttrListener_OtherPlayer::GetClassId()
{
	PlayerDetailInfo* di = MMOPlayerInfoManager::getSingleton().FindCurPlayerDetailInfo( );
	if( di )
	{
		return di->ClassId;
	}
	return 0;
}

INT MMOAttrListener_OtherPlayer::GetFatigue()
{
	PlayerDetailInfo* di = MMOPlayerInfoManager::getSingleton().FindCurPlayerDetailInfo( );
	if( di )
	{
		return di->Fatigue;
	}
	
	return 0;
}

INT MMOAttrListener_OtherPlayer::GetPower()
{
	return 0;
}