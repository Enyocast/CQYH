#include "stdafx.h"
#include "message_handler.h"
#include "MMOFacade.h"

using namespace ExternalMessage;

void CMessageHandler::Parse_m2c_h5_url(const char* buf, UINT32 size)
{
	M2C_H5_URL* msg = (M2C_H5_URL*)buf;
	AMMOPlayer* player = MMOFacade::getSingleton().GetMainPlayer();
	if( !player )
	{
		return;
	}
	
	ShellExecute(NULL,"open", "..\\..\\chrome32_60.0.3112.78\\chrome.exe", "--app=http://www.bilibili.com", NULL, SW_SHOWNORMAL);
	/*INT GroupNum = msg->byGroupCount;
	for ( INT i = 0 ; i < GroupNum ; i++ ) //
	{
		INT GroupId = msg->stGroupInfo[i].byGroupID;
		if( FriendManager::getSingleton().GetFriendGroup(GroupId) )
		{
			FriendManager::getSingleton().GetFriendGroup(GroupId)->GroupName = UTF8_TO_TCHAR( msg->stGroupInfo[i].szGroupName);
		}		

		MMOGameEvent_OneInt evt( GameEvent_UpdateFriendGroup , GroupId );
		MMOUI::PostGameEvent( &evt );
	}*/
	
}