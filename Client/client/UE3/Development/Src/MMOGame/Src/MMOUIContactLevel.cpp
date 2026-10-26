#include "stdafx.h"
#include "MMOGameUIClasses.h"
#include "MMOFacade.h"
#include "FriendChatManager.h"
#include "FriendManager.h"
#include "MMOChatManager.h"
#include "ScaleformEngine.h"

IMPLEMENT_CLASS(UMMOUIContactLevel)

//----------------------------
/*
//重新整理好友聊天
*/

/*
DispatchChatContent

分三种情况:
	1对方在自己的聊天列表内 

	2对方在自己的聊天列表内 并且当前正在聊天中的

	3对方不在自己的聊天列表内
*/

void UMMOUIContactLevel::DispatchChatContent(INT nRoleID,FString& strContent)
{
	MMOFriendMember FriendInfo;

	if( Player && Player->ServerID == nRoleID) 
	{
		FriendInfo.RoleId = nRoleID;
		FriendInfo.ActorName = Player->ActorName;
	}
	else
	{
		FriendInfo = FriendManager::getSingleton().GetFriendInfoByRoleId(nRoleID);
	}

	FriendManager::getSingleton().UpdateFriendMemberInfo(FriendInfo,nRoleID);

	if( FriendInfo.RoleId != nRoleID ) 
	{
		return;
	}

	FriendChatManager::getSingleton().AddNewChatLogList(nRoleID,FriendInfo.ActorName,strContent,Player->ServerID == nRoleID);

	if(GetVisible()&&FriendChatManager::getSingleton().IsInRoleChatList(nRoleID))
	{
		FriendChatManager::getSingleton().AddNewChatReadLog(nRoleID,FriendInfo.ActorName,strContent,Player->ServerID == nRoleID);
		if(nRoleID == nCurRoleID)
		{
			SetRoleChatContent(nRoleID);
		}
		else
		{
			INT nIndex = FriendChatManager::getSingleton().GetRoleIndexByChatList(nRoleID);
			if (nIndex >= 0)
			{
				//页签闪烁
				eventCallUCShowRoleItemEffect(nIndex);
			}
			
		}
	}
	else
	{
		FriendChatManager::getSingleton().AddNewChatUnReadLog(nRoleID,FriendInfo.ActorName,strContent,Player->ServerID != nRoleID);
		MMOFacade::getSingleton().NotifyUnReadFriendChatMsgChange( );
	}
}
void UMMOUIContactLevel::SendFriendChat(int nRoleID, FString strContent)
{
	if(nRoleID <= 0)
		return;

	MMOFriendMember FriendInfo = FriendManager::getSingleton().GetFriendInfoByRoleId( nRoleID );

	FriendManager::getSingleton().UpdateFriendMemberInfo(FriendInfo,nRoleID);
	
	if( FriendInfo.RoleId != nRoleID) 
	{
		return; // 非法
	}
	

	MMOUI::ReplaceCensoredWord(strContent,CensoredWord_Chat);

	CMessageHandler::GetInstance().SendFriendChat(nRoleID,strContent);

	FriendChatManager::getSingleton().AddNewChatLogList(nRoleID,FriendInfo.ActorName,strContent,true);
	FriendChatManager::getSingleton().AddNewChatReadLog(nRoleID,FriendInfo.ActorName,strContent,true);

	if(nRoleID == nCurRoleID)
		SetRoleChatContent(nRoleID);
}
void  UMMOUIContactLevel::SetRoleChatContent(INT nRoleID)
{
	nCurRoleID = nRoleID;

	UGFxObject* ShowArea = GetObject( TEXT("TextShowArea_mc") );
	if( !ShowArea)
		return;
	if(nRoleID == 0)
	{
		ShowArea->SetText(TEXT(""));
		return;
	}
	
	MMOFriendMember FriendInfo = FriendManager::getSingleton().GetFriendInfoByRoleId( nRoleID );

	//或者来自摆摊
	FriendManager::getSingleton().UpdateFriendMemberInfo(FriendInfo,nRoleID);

	FString Msg = TEXT("");
	const TArray<ContactLogStruct>& showList = FriendChatManager::getSingleton().GetLogList();

	for( INT i = 0 ; i < showList.Num() ; i++ )
	{		
		if( showList(i).PlayerName == FriendInfo.ActorName)
		{
			INT listNum = Min( FriendChatManager::ShowMaxLog , showList(i).LogList.Num() );
			for( INT j = 0 ; j < listNum ; j++ )
			{
				Msg += FString::Printf( TEXT("<FONT COLOR='%s'>%s</FONT><br>") , *MMOUI::GetUIManager()->TotalChannelFontColorString , *showList(i).LogList(j) );
			}
			break;
		}		
	}

	TArray<struct FASValue> Arguments;
	FASValue ASValue(EC_EventParm);
	ASValue.S =  Msg;
	ASValue.Type = AS_String;

	Arguments.AddItem(ASValue);
	ShowArea->Invoke( TEXT("NewAppendHtml") , Arguments );
}
void  UMMOUIContactLevel::CloseRoleChat(int nRoleID)
{
	FriendChatManager::getSingleton().RemoveRoleIDChatList(nRoleID);
	if(nRoleID == nCurRoleID)
	{
		nCurRoleID = 0;
		SetRoleChatContent(0);
	}
	UpdateRoleChatList();

	const TArray<int>& curChatList = FriendChatManager::getSingleton().GetChatList();
	if(curChatList.Num() == 0)
	{
		MMOGameEvent_Any evt( GameEvent_HideFriendChatHint );
		MMOUI::PostGameEvent(&evt);
	}
}
void UMMOUIContactLevel::UpdateRoleChatList()
{
	const TArray<int>& curChatList = FriendChatManager::getSingleton().GetChatList();
	if(curChatList.Num() == 0)
	{
		nCurRoleID = 0;
		Show(FALSE);
	}

	UGFxObject* dataProvider = GFXPlayer->CreateArray();
	if(dataProvider == NULL)
		return;
	for (int n = 0; n < curChatList.Num(); ++n)
	{
		UGFxObject* itemObj = GFXPlayer->CreateObject(TEXT("ActionScript3.Friend.FriendNameListItemData"));
		if( itemObj != NULL )
		{
			MMOFriendMember member = FriendManager::getSingleton().GetFriendInfoByRoleId( curChatList(n) );
			FriendManager::getSingleton().UpdateFriendMemberInfo(member,curChatList(n));
			if(member.RoleId != 0)
			{
				//性别
				itemObj->SetInt(TEXT("RoleID"), member.RoleId );
				//职业
				itemObj->SetString(TEXT("RoleName"), member.ActorName);
				// 角色ID
				itemObj->SetInt(_T("OnLine"), member.Online);

				if(nCurRoleID > 0&& nCurRoleID == member.RoleId )
				{
					itemObj->SetBool(_T("Selected"), TRUE);
				}
				else if(nCurRoleID == 0&& n==0)
					itemObj->SetBool(_T("Selected"), TRUE);
			}
			dataProvider->SetElementObject( n, itemObj );
		}
	}
	eventCallUCDataFriendChatList(dataProvider);
}

void UMMOUIContactLevel::SelectNewRoleChat(INT RoleId,const FString& PlayerName)
{
	/** 去掉好友限制
	/*if( !FriendManager::getSingleton().IsMyFriend(RoleId))
		return;*/

	if(RoleId <= 0)
		return;
	FriendChatManager::getSingleton().RemoveUnReadChatContent(RoleId);

	if(RoleId == nCurRoleID)
	{
		if(!GetVisible())
			Show(TRUE);
		return;
	}
	nCurRoleID = RoleId;

	FriendChatManager::getSingleton().AddNewRoleIDChatList(RoleId);
	UpdateRoleChatList();
	if(!GetVisible())
		Show(TRUE);
}

void UMMOUIContactLevel::UnInit()
{
	Super::UnInit();
	FScriptDelegate nullDelgate(EC_EventParm);


	MMOUI::GetUIManager()->SetSelectFriendChatDelegate(nullDelgate);
	MMOUI::GetUIManager()->SetMoveUnReadMsgToReadDelegate(nullDelgate);
}

void UMMOUIContactLevel::OnNativeGameEvent(struct MMOGameEvent* evt)
{
	switch( evt->GetEventType() )
	{
	case GameEvent_FriendInfoChange:
		{
			MMOGameEvent_OneInt* msg = (MMOGameEvent_OneInt*)evt;
			if(msg)
			{
				UpdateRoleChatList();
			}
		}
		break;

	case GameEvent_ChangeRole:
		{
			FriendChatManager::getSingleton().ClearRoleIDChatList();
		}
		break;
	}

}
void UMMOUIContactLevel::Init()
{
	Super::Init();

	check(EventAdapter == NULL);
	TArray<EGameEvent> evts;
	evts.AddItem(GameEvent_FriendInfoChange);
	evts.AddItem(GameEvent_ChangeRole);
	EventAdapter = new TGameEventAdapter<UMMOUIContactLevel>(this, evts);
}
void UMMOUIContactLevel::PostOnShow(UBOOL v)
{
	Super::PostOnShow(v);

	INT faceNum = 0;
	GConfig->GetInt( TEXT("Chat"), TEXT("FaceNum") , faceNum , GGameIni );
	UGFxObject* popFace = GetObject( TEXT("PopFacePanel") );
	if( popFace )
	{
		for ( INT i = 0 ; i < faceNum ; i++ )
		{
			UGFxObject* face = popFace->GetObject( FString( TEXT("FaceButton") ) + appItoa(i) );
			if(face)
			{
				face->SetString( TEXT("label") , MMOUI::ParseLocalizedPropertyPath( FString( TEXT("MMOGame.Chat.face") ) + appItoa(i) ) );
			}
		}

	}

	if(FriendChatManager::getSingleton().GetChatList().Num() == 0)
		nCurRoleID = 0;

	if(v)
	{
		UpdateRoleChatList();
	}
}
void UMMOUIContactLevel::OpenUnReadChatContent(INT RoleId,const FString& PlayerName)
{
	FriendChatManager::getSingleton().RemoveUnReadChatContent(RoleId);
	MMOFacade::getSingleton().NotifyUnReadFriendChatMsgChange( );

	if(!GetVisible())
		Show(TRUE);
	nCurRoleID = RoleId;

	FriendChatManager::getSingleton().AddNewRoleIDChatList(RoleId);
	UpdateRoleChatList();
}
void UMMOUIContactLevel::FriendChatMsg(INT RoleId,const FString& Content)
{

	FString strCC = Content;
	MMOUI::ReplaceCensoredWord(strCC, CensoredWord_ChatRecive);
	DispatchChatContent(RoleId,strCC);
}
// 重整好友聊天

//-------------------------该类2个核心函数之一，别人给你发消息走这个分发，另一个是点击好友聊天信息请看SelectFriendChat--------------------------------------------------
// void UMMOUIContactLevel::FriendChatMsg(INT RoleId,const FString& Content)
// {
// 	//重新整理好友聊天
// 	return;
// 
// 	MMOFriendMember FriendInfo;
// 	
// 	if( Player && Player->ServerID == RoleId) 
// 	{
// 		//自己发给自己的情况
// 		FriendInfo.RoleId = RoleId;
// 		FriendInfo.ActorName = Player->ActorName;
// 	}
// 	else
// 	{
// 		FriendInfo = FriendManager::getSingleton().GetFriendInfoByRoleId(RoleId);
// 	}
// 	
// 	if( FriendInfo.RoleId != RoleId ) 
// 	{
// 		return; // 非法
// 	}
// 
// 	FString FriendName = FriendInfo.ActorName;
// 	AddtoContactLog( RoleId , FriendName , Content ); //不管是否有窗口，先加入Log
// 
// 	for ( INT i = 0 ; i < ContactWindowList.Num() ; i++ )
// 	{
// 		for ( INT j = 0 ; j < WindowChatNum ; j++ )
// 		{
// 			if( ContactWindowList(i).RoleId[j] == RoleId )
// 			{
// 				//与来消息的玩家间有创建出的窗口		
// 
// 				AddtoReadContactLog( RoleId , FriendName , Content );
// 
// 				if( ContactWindowList(i).ActiveId == j )
// 				{				
// 					//当前窗口正是激活的那个
// 					AddContactMessage( ContactWindowList(i).Widget , FriendName  );
// 				}
// 				else
// 				{
// 					//未激活的话要给个激活提示
// 					SetChildTabHint( ContactWindowList(i).Widget , j , TRUE );
// 				}
// 
// 				return;
// 			}
// 		}
// 	}	
// 
// 	//无现成窗口，加到未读列表里
// 	AddtoUnReadContactLog( RoleId , FriendInfo.ActorName , Content );
// 
// 	MMOFacade::getSingleton().NotifyUnReadFriendChatMsgChange( );
// }
// 
// void UMMOUIContactLevel::UnInit()
// {
// 	Super::UnInit();
// 	FScriptDelegate nullDelgate(EC_EventParm);
// 
// 
// 	MMOUI::GetUIManager()->SetSelectFriendChatDelegate(nullDelgate);
// 	MMOUI::GetUIManager()->SetMoveUnReadMsgToReadDelegate(nullDelgate);
// }
// 
// void UMMOUIContactLevel::OnNativeGameEvent(struct MMOGameEvent* evt)
// {
// 	switch( evt->GetEventType() )
// 	{
// 	case GameEvent_FriendInfoChange:
// 		{
// 			MMOGameEvent_OneInt* msg = (MMOGameEvent_OneInt*)evt;
// 			if(msg)
// 			{
// 				INT windowId = GetWindowIdByRoleId(msg->IntData);
// 				UpdateWindowTab( windowId );
// 			}
// 		}
// 		break;
// 	}
// 
// }
// 
// //-------------------------------------------------------------------------------------
// void UMMOUIContactLevel::NativeInit()
// {
// 	FriendChatMgr = &FriendChatManager::getSingleton();
// 
// 	SetVisible(TRUE);
// }
// 
// //-------------------------------------------------------------------------------------
// void UMMOUIContactLevel::ClearUI()
// {
// 	//重新整理好友聊天
// 	return;
// 
// 	FriendChatMgr = &FriendChatManager::getSingleton();
// 	if(!FriendChatMgr)
// 	{
// 		return;
// 	}
// 	//清空所有窗口
// 	for ( INT i = 0 ; i < ContactWindowList.Num() ; i++ )
// 	{
// 		FASValue AsVal(EC_EventParm);	
// 		AsVal.S = ContactWindowList(i).WindowName;
// 		AsVal.Type = AS_String;
// 
// 		TArray<struct FASValue> Arguments;
// 		Arguments.AddItem(AsVal);
// 
// 		Invoke( TEXT("RemoveWindow") , Arguments );
// 	}
// 	ContactWindowList.Empty();
// }
// //-------------------------------------------------------------------------------------
// void UMMOUIContactLevel::AddtoReadContactLog(INT RoleId,const FString& PlayerName,const FString& Content,UBOOL fromSelf)
// {
// 	//重新整理好友聊天
// 	return;
// 
// 	ContactLogStruct CL(EC_EventParm);
// 	
// 	FString senderName;
// 	if(fromSelf)
// 	{
// 		senderName = Player->ActorName;
// 	}
// 	else
// 	{
// 		senderName = PlayerName;
// 	}
// 		
// 	FString Msg = _GetShowText( senderName , Content , fromSelf );
// 
// 	for(INT i = 0 ; i< FriendChatMgr->ReadContactLogList.Num() ;i++ ) 
// 	{
// 		if( FriendChatMgr->ReadContactLogList(i).RoleId == RoleId )
// 		{
// 			FriendChatMgr->ReadContactLogList(i).LogList.AddItem( Msg );
// 			return;
// 		}
// 	}
// 	CL.RoleId = RoleId;
// 	CL.PlayerName = PlayerName;
// 	CL.LogList.AddItem( Msg );
// 	FriendChatMgr->ReadContactLogList.AddItem(CL);
// }
// 
// //-------------------------------------------------------------------------------------
// void UMMOUIContactLevel::AddtoUnReadContactLog(INT RoleId,const FString& PlayerName,const FString& Content,UBOOL addLog )
// {
// 	//重新整理好友聊天
// 	return;
// 
// 	if(!FriendChatMgr)
// 	{
// 		return;
// 	}
// 	AMMOPlayer* player = MMOFacade::getSingleton().GetMainPlayer();
// 	if(!player)
// 	{
// 		return;
// 	}
// 
// 	ContactLogStruct CL(EC_EventParm);
// 		
// 	FString Msg = _GetShowText( PlayerName , Content , player->ServerID == RoleId ); 
// 
// 	for(INT i = 0 ; i< FriendChatMgr->UnReadContactLogList.Num() ;i++ ) 
// 	{
// 		if( FriendChatMgr->UnReadContactLogList(i).RoleId == RoleId )
// 		{
// 			if(addLog)
// 			{
// 				FriendChatMgr->UnReadContactLogList(i).LogList.AddItem( Msg );
// 			}
// 			return;
// 		}
// 	}
// 	CL.RoleId = RoleId;
// 	CL.PlayerName = PlayerName;
// 	if(addLog)
// 	{
// 		CL.LogList.AddItem( Msg );
// 	}
// 	FriendChatMgr->UnReadContactLogList.AddItem(CL);
// }

//------------------------------------加到对话框里-------------------------------------------------
// void UMMOUIContactLevel::AddContactMessage( UGFxObject* Window , const FString& PlayerName /*,const FString& Content*/)
// {
// 	//重新整理好友聊天
// 	return;
// 
// 	if( !Window )
// 	{
// 		return;
// 	}
// 	UGFxObject* ShowArea = Window->GetObject( TEXT("TextShowArea_mc") );
// 	if( !ShowArea)
// 	{
// 		return;
// 	}
// 	
// 
// 	FString Msg;
// 
// 	//原来使用ReadContactLogList，后来改成log了	
// 	TArray<ContactLogStruct>& showList = FriendChatMgr->ContactLogList;
// 	for( INT i = 0 ; i < showList.Num() ; i++ )
// 	{		
// 		if( showList(i).PlayerName == PlayerName)
// 		{
// 			INT listNum = Min( ShowMaxLog , showList(i).LogList.Num() );
// 			for( INT j = 0 ; j < listNum ; j++ )
// 			{
// 				Msg += FString::Printf( TEXT("<FONT COLOR='%s'> %s</FONT><br>") , *MMOUI::GetUIManager()->TotalChannelFontColorString , *showList(i).LogList(j) );
// 			}
// 
// 			break;
// 		}		
// 	}
// 
// 	TArray<struct FASValue> Arguments;
// 	FASValue ASValue(EC_EventParm);
// 
// 	ASValue.S =  Msg;
// 	ASValue.Type = AS_String;
// 
// 	Arguments.AddItem(ASValue);
// 	ShowArea->Invoke( TEXT("NewAppendHtml") , Arguments );
// 
// }
// 
// 
// 
// //-------------------------------------------------------------------------------------
// void UMMOUIContactLevel::ContactWindowTab(UGFxObject* Window,INT Tab)
// {
// 	//重新整理好友聊天
// 	return;
// 
// 	if( Tab >= WindowChatNum || !Window )
// 	{
// 		return;//非法
// 	}
// 
// 	INT WindowId = Window->GetInt(TEXT("WindowId"));
// 	for (INT i = 0 ; i < ContactWindowList.Num() ; i++ )
// 	{
// 		if( ContactWindowList(i).WindowId == WindowId )
// 		{
// 			AddContactMessage( Window , ContactWindowList(i).PlayerName[Tab] );
// 			break;
// 		}
// 	}
// 	
// }
// //-------------------------------------------------------------------------------------
// void UMMOUIContactLevel::CreateNewWindow(const FString& PlayerName , INT RoleId )
// {
// 	//重新整理好友聊天
// 	return;
// 
// 		FASValue AsVal(EC_EventParm);
// 		FString WindowName = FString::Printf( TEXT("ContactWidget%d") , CurWindowId );
// 		AsVal.S =  WindowName;
// 		AsVal.Type = AS_String;
// 		
// 		TArray<struct FASValue> Arguments;
// 		Arguments.AddItem(AsVal);
// 
// 		Invoke( TEXT("AddWindow") , Arguments );
// 
// 		UGFxObject* mc = GetObject( WindowName );
// 		
// 		if( !mc )
// 		{
// 			return;
// 		}
// 
// 		mc->SetInt( TEXT("WindowId"),CurWindowId );
// 
// 		FContactWindowStruct CW(EC_EventParm);
// 		CW.Widget = mc;
// 		CW.ActiveId = 0;
// 		CW.PlayerName[0] = PlayerName;
// 		CW.WindowName = WindowName;
// 		CW.WindowId = CurWindowId;
// 		CW.RoleId[0] = RoleId;
// 
// 		ContactWindowList.AddItem( CW);
// 
// 		//ActiveContactPlayer ( mc, 0 ,CW.WindowName );
// 
// 		UGFxObject* Tab = NULL;
// 		
// 		SetChildWindow(mc,1,FALSE,FALSE);
// 		SetChildWindow(mc,2,FALSE,FALSE);
// 		SetChildWindow(mc,3,FALSE,FALSE);
// 		SetChildWindow(mc,0,TRUE,FALSE,PlayerName,RoleId);
// 
// 		ActiveChildWindow( mc , 0 );
// 
// 		SetNewWindowText( mc );
// 
// 		CurWindowId++;
// }
// 
// //--------------------------
// void UMMOUIContactLevel::SetNewWindowText( UGFxObject* window )
// {
// 	//重新整理好友聊天
// 	return;
// 
// 	INT faceNum = 0;
// 	GConfig->GetInt( TEXT("Chat"), TEXT("FaceNum") , faceNum , GGameIni );
// 	UGFxObject* popFace = window->GetObject( TEXT("PopFacePanel") );
// 	if( popFace )
// 	{
// 		for ( INT i = 0 ; i < faceNum ; i++ )
// 		{
// 			UGFxObject* face = popFace->GetObject( FString( TEXT("FaceButton") ) + appItoa(i) );
// 			if(face)
// 			{
// 				face->SetString( TEXT("label") , MMOUI::ParseLocalizedPropertyPath( FString( TEXT("MMOGame.Chat.face") ) + appItoa(i) ) );
// 			}
// 		}
// 
// 	}
// }
// 
// //-----------------------------------------把未显示列表的移到出来------------------------
// void UMMOUIContactLevel::MoveUnReadMsgToRead(INT RoleId,const FString& PlayerName)
// {
// 
// 	//重新整理好友聊天
// 	return;
// 
// 	if(!FriendChatMgr)
// 	{
// 		return;
// 	}
// 
// 	INT ReadIndex = -1;
// 	INT UnReadIndex = -1;
// 
// 	for ( INT i = 0 ; i < FriendChatMgr->ReadContactLogList.Num() ; i++ )
// 	{
// 		if( FriendChatMgr->ReadContactLogList(i).RoleId == RoleId )
// 		{
// 			ReadIndex = i;
// 		}
// 	}
// 	for ( INT j = 0 ; j < FriendChatMgr->UnReadContactLogList.Num() ; j++ )
// 	{
// 		if( FriendChatMgr->UnReadContactLogList(j).RoleId == RoleId )
// 		{
// 			UnReadIndex = j;
// 		}
// 	}
// 	if( UnReadIndex < 0 )
// 	{
// 		//没有未读
// 		return;
// 	}
// 	if( ReadIndex < 0 ) //没有这个人，就新建一个
// 	{
// 		ContactLogStruct NewContackLog(EC_EventParm);
// 		NewContackLog.RoleId = RoleId;
// 		NewContackLog.PlayerName = PlayerName;
// 		ReadIndex = FriendChatMgr->ReadContactLogList.AddItem(NewContackLog);		
// 	}
// 	//复制数据
// 	for ( INT k = 0 ; k < FriendChatMgr->UnReadContactLogList(UnReadIndex).LogList.Num() ; k++ )
// 	{
// 		FriendChatMgr->ReadContactLogList( ReadIndex ).LogList.AddItem( FriendChatMgr->UnReadContactLogList(UnReadIndex).LogList(k) );
// 	}
// 	//把原来的删掉
// 	FriendChatMgr->UnReadContactLogList(UnReadIndex).LogList.Empty();
// 	FriendChatMgr->UnReadContactLogList.Remove(UnReadIndex);
// 	return;
// 
// }
// 
// void UMMOUIContactLevel::Init()
// {
// 	Super::Init();
// 
// 	check(EventAdapter == NULL);
// 	TArray<EGameEvent> evts;
// 	evts.AddItem(GameEvent_FriendInfoChange);
// 	EventAdapter = new TGameEventAdapter<UMMOUIContactLevel>(this, evts);
// }
// 
// INT UMMOUIContactLevel::GetWindowIdByRoleId( INT roleId )
// {
// 	//重新整理好友聊天
// 	return;
// 
// 	for ( INT i = 0 ; i < ContactWindowList.Num() ; i++ )
// 	{
// 		for ( INT j = 0 ; j < WindowChatNum ; j++ )
// 		{
// 			if( ContactWindowList(i).RoleId[j] == roleId ) 
// 			{
// 				
// 				return ContactWindowList(i).WindowId;
// 			}
// 		}		
// 	}
// 
// 	return -1;
// }
// 
// //-------------------------------------------点击好友的聊天，该类最核心的2个功能函数之一，另一个是分发消息FriendChatMsg-------------------
// void UMMOUIContactLevel::SelectFriendChat(INT RoleId,const FString& RoleName)
// {
// 	//重新整理好友聊天
// 	return;
// 
// 	if( !FriendManager::getSingleton().IsMyFriend(RoleId))
// 	{
// 		return;
// 	}
// 
// 	//如果有未读的话，就把未读信息转到已读
// 	MoveUnReadMsgToRead( RoleId , RoleName );
// 
// 	//先看有没有这个对话窗口打开
// 	for ( INT i = 0 ; i < ContactWindowList.Num() ; i++ )
// 	{
// 		for ( INT j = 0 ; j < WindowChatNum ; j++ )
// 		{
// 			if( ContactWindowList(i).RoleId[j] == RoleId ) 
// 			{
// 				//有这个窗口，激活之
// 				ContactWindowList(i).ActiveId = j ;
// 				ActiveChildWindow( ContactWindowList(i).Widget , j );
// 				return;
// 			}
// 		}		
// 	}
// 
// 	//没有现成窗口，寻找大窗口中是否有空闲可以打开
// 	for ( INT i = 0 ; i < ContactWindowList.Num() ; i++ )
// 	{
// 		for ( INT j = 0 ; j < WindowChatNum ; j++ )
// 		{
// 			if( ContactWindowList(i).RoleId[j] == 0 ) //有窗口空着就显示，然后激活
// 			{
// 				
// 				ContactWindowList(i).RoleId[j] = RoleId;
// 				ContactWindowList(i).PlayerName[j] = RoleName;
// 				UpdateWindowTab( ContactWindowList(i).WindowId );
// 
// 				ActiveChildWindow( ContactWindowList(i).Widget , j );
// 				return;
// 			}
// 		}		
// 	}
// 
// 	//没有空闲，创建新的大窗口
// 	CreateNewWindow( RoleName , RoleId );
// 
// 	
// 	
// }
// 
// //-------------------------------------------------------------------------------------
// void UMMOUIContactLevel::ActiveChildWindow(class UGFxObject* Window,INT ChildId)
// {
// 	//重新整理好友聊天
// 	return;
// 
// 	if( Window )
// 	{
// 		SetChildTabHint( Window , ChildId , FALSE );
// 		//todo 高亮
// 		ContactWindowTab( Window , ChildId );
// 
// 		if(GFXPlayer)
// 			FGFxEngine::GetEngine()->SetFocusMovie(GFXPlayer->pMovie);
// 
// 		TArray<	FASValue> args;
// 		Window->Invoke( TEXT("setFocus"),args );
// 
// 		FASValue AsVal(EC_EventParm);	
// 		AsVal.I = ChildId;
// 		AsVal.Type = AS_Int;
// 
// 		TArray<struct FASValue> Arguments;
// 		Arguments.AddItem(AsVal);
// 
// 		Window->Invoke( TEXT("AutoClickTabIndex") , Arguments );
// 
// 
// 		AMMOPlayerController* Ctrl = MMOFacade::getSingleton().GetMainController();
// 		if(Ctrl)
// 			Ctrl->SetInTextInput(TRUE);
// 	}
// 	
// }
// 
// //-------------------------------------------------------------------------------------
// void UMMOUIContactLevel::AddtoContactLog(INT RoleId,const FString& PlayerName,const FString& Content,UBOOL fromSelf)
// {
// 	//重新整理好友聊天
// 	return;
// 
// 	if(!FriendChatMgr)
// 	{
// 		return;
// 	}
// 
// 	//注意：自己联系对方和对方联系自己都会添加在这里，roleid和name总是对方的
// 
// 	//告知管理器最新联系人
// 	FriendManager::getSingleton().NotifyNewContact(RoleId);
// 	
// 	ContactLogStruct CL(EC_EventParm);
// 
// 	
// 	FString senderName;
// 	if(fromSelf)
// 	{
// 		senderName = Player->ActorName;
// 	}
// 	else
// 	{
// 		senderName = PlayerName;
// 	}
// 
// 	FString Msg = _GetShowText( senderName , Content , fromSelf );
// 
// 	//已有此人的消息队列，就加入之前队列
// 	for(INT i = 0 ; i< FriendChatMgr->ContactLogList.Num() ;i++ ) 
// 	{
// 		if( FriendChatMgr->ContactLogList(i).RoleId == RoleId )
// 		{
// 			FriendChatMgr->ContactLogList(i).LogList.AddItem( Msg );
// 			if( FriendChatMgr->ContactLogList(i).LogList.Num() > MaxFriendChatLogNum )
// 			{
// 				FriendChatMgr->ContactLogList(i).LogList.Remove(0);
// 			}
// 			return;
// 		}
// 	}
// 	//否则就新建
// 	CL.RoleId = RoleId;
// 	CL.PlayerName = PlayerName;
// 	CL.LogList.AddItem( Msg );
// 	FriendChatMgr->ContactLogList.AddItem(CL);
// }
// 
// 
// 
// //-------------------------------------------------------------------------------------
// void UMMOUIContactLevel::SendFriendChatMessage(INT WindowId,const FString& MsgContent)
// {
// 	//重新整理好友聊天
// 	return;
// 	
// 	for ( INT i = 0 ; i < ContactWindowList.Num() ; i++ )
// 	{
// 		if( ContactWindowList(i).WindowId == WindowId )
// 		{
// 			INT TargetId = ContactWindowList(i).RoleId[ ContactWindowList(i).ActiveId ];
// 			CMessageHandler::GetInstance().SendFriendChat(TargetId,MsgContent);
// 
// 			//说完话，把话加到自己的框里
// 			MMOFriendMember FriendInfo = FriendManager::getSingleton().GetFriendInfoByRoleId( TargetId );
// 		
// 			if( FriendInfo.RoleId != TargetId ) 
// 			{
// 				return; // 非法
// 			}
// 			FString FriendName = FriendInfo.ActorName;
// 			AddtoContactLog( TargetId , FriendName , MsgContent , true );
// 			AddtoReadContactLog( TargetId , FriendName , MsgContent ,true);
// 			AddContactMessage( ContactWindowList(i).Widget , FriendName  );
// 
// 			return;
// 		}
// 	}
// }
// 
// //---------------------------设置窗口提醒---------------
// void UMMOUIContactLevel::SetChildTabHint( UGFxObject* Window , INT ChildId , UBOOL openHint )
// {
// 	//重新整理好友聊天
// 	return;
// 
// 	if( !Window )
// 	{
// 		return;
// 	}
// 
// 	UGFxObject* Tab = Window->GetObject( FString::Printf(TEXT("tab%d"),ChildId) );
// 	if( !Tab )
// 	{
// 		return;
// 	}
// 
// 	UGFxObject* hint = Tab->GetObject( TEXT("alertAnimation") );
// 	if(hint)
// 	{
// 		if( openHint )
// 		{
// 			hint->GotoAndPlayI(1);
// 		}
// 		else
// 		{
// 			hint->GotoAndStopI(1);
// 		}
// 	}
// }
// void UMMOUIContactLevel::ChangeToTab(INT nRoleID)
// {
// 	//重新整理好友聊天
// 	return;
// 
// 	for ( INT i = 0 ; i < ContactWindowList.Num() ; i++ )
// 	{
// 		for ( INT j = 0 ; j < WindowChatNum ; j++ )
// 		{
// 			if( ContactWindowList(i).RoleId[j] == nRoleID ) 
// 			{
// 				//有这个窗口，激活之
// 				ContactWindowList(i).ActiveId = j ;
// 				ActiveChildWindow( ContactWindowList(i).Widget , j );
// 				return;
// 			}
// 		}		
// 	}
// }
// //---------------------------设置子窗口----------------------------------------------------------
// void UMMOUIContactLevel::SetChildWindow(UGFxObject* Window , INT ChildId , UBOOL Visible , UBOOL CloseVisible , FString PlayerName , INT roleId )
// {
// 	//重新整理好友聊天
// 	return;
// 
// 	if( !Window )
// 	{
// 		return;
// 	}
// 	UGFxObject* Tab = Window->GetObject( FString::Printf(TEXT("tab%d"),ChildId) );
// 	UGFxObject* Close = Window->GetObject( FString::Printf(TEXT("tabclose%d"),ChildId) );
// 	if( Close )
// 	{
// 		Close->SetVisible(CloseVisible);
// 	}
// 	if( !Tab )
// 	{
// 		return;
// 	}
// 	if( !Visible )
// 	{
// 		Tab->SetVisible(FALSE);
// 	}
// 	else
// 	{
// 		Tab->SetVisible(TRUE);
// 		Tab->SetInt("tabId",ChildId);
// 		Tab->SetInt("roleId",roleId);
// 
// 		UGFxObject* TF_TabName = Tab->GetObject( TEXT("tF_playerName") );
// 		if( TF_TabName )
// 		{
// 			TF_TabName->SetText( PlayerName );
// 		}
// 
// 		UGFxObject* OnlineStatClip = Tab->GetObject( TEXT("ContactStatus") );
// 		if( OnlineStatClip )
// 		{
// 			INT stat = 0;
// 			MMOFriendMember member = FriendManager::getSingleton().GetFriendInfoByRoleId( roleId );
// 			if( member.RoleId != 0 )
// 			{
// 				stat = member.Online;				
// 			}
// 			else
// 			{
// 				stat = E_FS_OFFLINE;
// 			}
// 
// 			switch(stat)
// 			{
// 			case E_FS_OFFLINE:
// 				OnlineStatClip->GotoAndStop( TEXT("offline") );
// 				break;
// 			case E_FS_ONLINE:
// 				OnlineStatClip->GotoAndStop( TEXT("online") );
// 				break;
// 			case E_FS_BUSY:
// 				OnlineStatClip->GotoAndStop( TEXT("busy") );
// 				break;
// 			case E_FS_AFK:
// 				OnlineStatClip->GotoAndStop( TEXT("afk") );
// 				break;	
// 					
// 			}
// 
// 		}
// 	}
// 
// }
// //-------------------------------------------------------------------------------------
// void UMMOUIContactLevel::RemoveWindow(const FString& WindowName)
// {
// 	//重新整理好友聊天
// 	return;
// 
// 	FASValue AsVal(EC_EventParm);	
// 	AsVal.S =  WindowName;
// 	AsVal.Type = AS_String;
// 
// 	TArray<struct FASValue> Arguments;
// 	Arguments.AddItem(AsVal);
// 
// 	Invoke( TEXT("RemoveWindow") , Arguments );
// 
// 	for( INT i = 0 ; i< ContactWindowList.Num() ; i++ )
// 	{
// 		if( ContactWindowList(i).WindowName == WindowName )
// 		{
// 			//删掉ReadLog的相关
// 			for ( INT j = 0 ; j < WindowChatNum ; j++ )
// 			{
// 				for ( INT k = FriendChatMgr->ReadContactLogList.Num()-1 ; k >= 0 ; k-- )
// 				{
// 					if( ContactWindowList(i).RoleId[j] != 0 && ContactWindowList(i).RoleId[j] == FriendChatMgr->ReadContactLogList(k).RoleId )
// 					{
// 						FriendChatMgr->ReadContactLogList(k).LogList.Empty();
// 						FriendChatMgr->ReadContactLogList.Remove(k);
// 					}
// 				}
// 			}
// 			//删除窗口
// 			ContactWindowList.Remove(i,1);
// 		}
// 	}
// }
// 
// //-------------------------------------------------------------------------------------
// void UMMOUIContactLevel::WindowTabClose(class UGFxObject* Window,class UGFxObject* Tab)
// {
// 	//重新整理好友聊天
// 	return;
// 
// 	if( !Window || !Tab )
// 	{
// 		return;
// 	}
// 
// 	INT WindowId = Window->GetInt(TEXT("WindowId"));
// 	INT TabId = Tab->GetInt(TEXT("itemid"));
// 
// 	for ( INT i = 0 ; i < ContactWindowList.Num() ; i++ )
// 	{
// 		if( ContactWindowList(i).WindowId == WindowId ) // 找到该窗口
// 		{
// 			INT OpenChildWindowNum = GetWindowOpenChildNum(ContactWindowList(i).WindowId);
// 
// 			if( ContactWindowList(i).ActiveId == TabId ) //关闭的是激活显示的那个
// 			{
// 				if( TabId == 0  )
// 				{
// 					if( OpenChildWindowNum > 1 )
// 					{
// 						ContactWindowTab( ContactWindowList(i).Widget , TabId+1 );
// 					}
// 				}
// 				else
// 				{
// 					ContactWindowTab( ContactWindowList(i).Widget , TabId-1 );
// 				}
// 			}
// 
// 			for ( INT j = TabId ; j < OpenChildWindowNum ; j++ )
// 			{
// 				if( j != OpenChildWindowNum-1 ) //前移
// 				{
// 					ContactWindowList(i).RoleId[j] = ContactWindowList(i).RoleId[j+1];
// 					ContactWindowList(i).PlayerName[j] = ContactWindowList(i).PlayerName[j+1];
// 				}
// 				else//排在最后的一个子窗口就不管了
// 				{
// 					ContactWindowList(i).RoleId[j] = 0 ;
// 					ContactWindowList(i).PlayerName[j] = TEXT("");
// 
// 				}					
// 			}
// 			if( ContactWindowList(i).ActiveId > TabId )
// 			{
// 				ContactWindowList(i).ActiveId --;
// 			}
// 			UpdateWindowTab(WindowId);
// 
// 		}
// 	}
// 
// }
// 
// //-------------------------------------------------------------------------------------
// INT UMMOUIContactLevel::GetWindowOpenChildNum(INT WindowId)
// {
// 	//重新整理好友聊天
// 	return;
// 
// 	INT Num = 0;
// 	for ( INT i = 0 ; i < ContactWindowList.Num() ; i++ )
// 	{
// 		if( ContactWindowList(i).WindowId == WindowId )
// 		{
// 			for ( INT j = 0 ; j < WindowChatNum ; j++ )
// 			{
// 				if( ContactWindowList(i).RoleId[j] != 0 )
// 				{
// 					Num++;
// 				}
// 			}
// 			break;
// 		}
// 
// 	}
// 	return Num;
// }
// 
// //-------------------------------------------------------------------------------------
// void UMMOUIContactLevel::UpdateWindowTab(INT WindowId)
// {
// 	//重新整理好友聊天
// 	return;
// 
// 	for ( INT i = 0 ; i < ContactWindowList.Num() ; i++ )
// 	{
// 		if( ContactWindowList(i).WindowId == WindowId )
// 		{
// 			INT OpenNum = GetWindowOpenChildNum( WindowId );
// 
// 			for ( INT j = 0 ; j < WindowChatNum ; j++ )
// 			{
// 				if( OpenNum == 1 && j == 0 )
// 				{ 
// 					//只有一个的话，是特殊的，是不能X掉的
// 					SetChildWindow( ContactWindowList(i).Widget , 0 , TRUE , FALSE , ContactWindowList(i).PlayerName[0] , ContactWindowList(i).RoleId[0] );
// 					continue;
// 				}
// 				UBOOL Visible = (ContactWindowList(i).RoleId[j] != 0) ;
// 				SetChildWindow( ContactWindowList(i).Widget , j , Visible , Visible , ContactWindowList(i).PlayerName[j] , ContactWindowList(i).RoleId[j] );				
// 			}
// 			
// 			break;
// 		}
// 	}
// }
// 
// //-------------------------------------------------------------------------------------
// void UMMOUIContactLevel::MiniMizeWindow(const FString& WindowName)
// {
// 	//重新整理好友聊天
// 	return;
// 
// 	for( INT i = 0 ; i< ContactWindowList.Num() ; i++ )
// 	{	
// 
// 		if( ContactWindowList(i).WindowName == WindowName )
// 		{
// 			//删掉ReadLog的相关
// 			for ( INT j = 0 ; j < WindowChatNum ; j++ )
// 			{
// 				if( ContactWindowList(i).RoleId[j] != 0 )
// 				{
// 					AddtoUnReadContactLog( ContactWindowList(i).RoleId[j] , ContactWindowList(i).PlayerName[j] , TEXT("") , FALSE );
// 
// 				}
// 
// 				
// 			}
// 
// 		}
// 	}
// 	MMOFacade::getSingleton().NotifyUnReadFriendChatMsgChange( );
// 	
// 	RemoveWindow( WindowName );
// }
// 
// void UMMOUIContactLevel::PostOnShow(UBOOL v)
// {
// 	//重载掉，因为不要movetop
// }
// 
// FString UMMOUIContactLevel::_GetShowText( const FString& playerName , const FString& content , UBOOL myWord )
// {
// 	//appSystemTime( INT& Year, INT& Month, INT& DayOfWeek, INT& Day, INT& Hour, INT& Min, INT& Sec, INT& MSec );
// 	_SYSTEMTIME SystemTime;
// 	::GetLocalTime(&SystemTime);
// 	FString sender = playerName + FString::Printf( TEXT(": %02d:%02d:%02d ") , SystemTime.wHour , SystemTime.wMinute , SystemTime.wSecond );
// 	FString color = myWord?(MMOChatManager::getSingleton().FriendChatMyContentColorString):(MMOChatManager::getSingleton().FriendChatOtherPlayerContentColorString);
// 
// 	return FString::Printf( TEXT("<FONT Color='%s'>%s</FONT><br><FONT Color='%s'>%s</FONT>") , *MMOChatManager::getSingleton().FriendChatSenderColorString , *sender ,
// 		*color , *content);
// }


void UMMOUIContactLevel::ASSendFriendChatByRoleID(INT nRoleID,const FString& ChatMsg)
{
	SendFriendChat(nRoleID,ChatMsg);
}
void UMMOUIContactLevel::ASSelectRoleChatWnd(INT nRoleID)
{
	SetRoleChatContent(nRoleID);
	MMOGameEvent_FriendChat_SetChatHintImg evt( nRoleID );
	MMOUI::PostGameEvent(&evt);
}
void UMMOUIContactLevel::ASCloseRoleChatWnd(INT nRoleID)
{
	CloseRoleChat(nRoleID);
}

void UMMOUIContactLevel::ASContactWidgetMiniMize(const FString& WindowName)
{
	MMOGameEvent_FriendChat_ShowChatHint evt( nCurRoleID );
	MMOUI::PostGameEvent(&evt);
	this->SetVisible(FALSE);
}

void UMMOUIContactLevel:: ASShowFriendChatList()
{
	this->SetVisible(TRUE);
	MMOGameEvent_Any evt( GameEvent_HideFriendChatHint );
	MMOUI::PostGameEvent(&evt);
}

void UMMOUIContactLevel:: ASOnPanelClose( const FString& PanelName )
{
	
}
void UMMOUIContactLevel::ASContactWidgetClose(const FString& PanelName)
{
	MMOGameEvent_Any evt( GameEvent_HideFriendChatHint );
	MMOUI::PostGameEvent(&evt);
}