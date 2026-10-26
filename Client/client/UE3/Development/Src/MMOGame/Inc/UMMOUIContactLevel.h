
virtual void PostOnShow(UBOOL v);
virtual void OnNativeGameEvent(struct MMOGameEvent* evt);

virtual void UnInit();
virtual void Init();

/*
//好友聊天重整

INT GetWindowIdByRoleId( INT roleId );
void SetChildWindow( UGFxObject* Window , INT ChildId , UBOOL Visible , UBOOL CloseVisible , FString PlayerName = TEXT("") , INT roleId = 0 ); 
void SetChildTabHint( UGFxObject* Window , INT ChildId , UBOOL openHint );
void SetNewWindowText( UGFxObject* window );

FString _GetShowText( const FString& playerName , const FString& content , UBOOL myWord );

void ChangeToTab(INT nRoleID);

*/
/*
 重整好友聊天
*/

void  DispatchChatContent(INT nRoleID,FString& strContent);
void  SendFriendChat(INT nRoleID, FString strContent);
void  SetRoleChatContent(INT nRoleID);
void  CloseRoleChat(INT nRoleID);
void  UpdateRoleChatList();

//void  UpdateFriendMemberInfo(MMOFriendMember &FriendInfo,INT nRoleID);
//void  SelectNewRoleChat(INT nRoleID);
