class MMOUIContactLevel extends MMOUIBase
	native(UI);


/*
好友聊天重整
*/
 var int nCurRoleID;
// var int CurWindowId;
// var const int WindowChatNum; //每个窗口的控件数: 4
// 
// 
// var native pointer FriendChatMgr{class FriendChatManager};
// 
//  struct native ContactWindowStruct
// {
// 	var string WindowName;
// 	var GFxObject Widget;
// 	var string PlayerName[4];
// 	var int RoleId[4];
// 	var int ActiveId;
// 	var int WindowId;
// };
// 
// 
// 
// 
// 
// //窗口的列表
// var array<ContactWindowStruct> ContactWindowList;
// 
// //加入未读列表，addLog:是否加入log内容
// native function AddtoUnReadContactLog( int RoleId , string PlayerName , string Content , optional bool addLog = true );
// native function AddtoReadContactLog( int RoleId , string PlayerName , string Content , optional bool fromSelf = false );
// //把每个好友的聊天按RoleId加入loglist保存
// native function AddtoContactLog( int RoleId , string PlayerName , string Content , optional bool fromSelf = false );
// 
// 
// native function FriendChatMsg( int RoleId , string Content );
// 
// native function NativeInit();
// native function ClearUI();
/*
好友聊天重整
*/

event InitOnce()
{
	super.InitOnce();
	
// 	class'MMOUIManager'.static.SetSelectFriendChatDelegate(SelectFriendChat);
// 	class'MMOUIManager'.static.SetMoveUnReadMsgToReadDelegate(MoveUnReadMsgToRead);

	class'MMOUIManager'.static.SetSelectFriendChatDelegate(SelectNewRoleChat);
	class'MMOUIManager'.static.SetMoveUnReadMsgToReadDelegate(OpenUnReadChatContent);
	//NativeInit();
}

native function OpenUnReadChatContent(int RoleId , string PlayerName );
native function SelectNewRoleChat(int RoleId , string PlayerName);
native function FriendChatMsg( int RoleId , string Content );
// 
// native function AddContactMessage( GFxObject Window , string PlayerName /*, string Content*/ );
// 
// native function ContactWindowTab(GFxObject Window , int Tab);
// 
// native function CreateNewWindow( string PlayerName , int RoleId );
// 
// native function ActiveChildWindow( GFxObject Window , int ChildId );
// //选择好友聊天，也可能是激活
// native function SelectFriendChat( int RoleId , string RoleName );
// 
// native function MoveUnReadMsgToRead( int RoleId , string PlayerName );
// 
// 
// 
// native function MiniMizeWindow( string WindowName);
// 
// 
// //native function SetChildWindow( GFxObject Window , int ChildId , bool Visible , bool CloseVisible , optional string PlayerName = "" ); 
// 
// native function SendFriendChatMessage( int WindowId , string MsgContent );
// 
// native function WindowTabClose( GFxObject Window , GFxObject Tab );
// 
// native function int GetWindowOpenChildNum( int WindowId );
// 
// native function UpdateWindowTab( int WindowId );
// 
// native function RemoveWindow( string WindowName );



/*
	重新整理好友聊天
*/
event CallUCDataFriendChatList(GFxObject data)
{
	ActionScriptVoid("UCDataFriendChatList");
}

event CallUCShowRoleItemEffect(int index)
{
	ActionScriptVoid("UCShowRoleItemEffec");
}

native function ASContactWidgetClose( string WindowName );//moved

//function ASContactWidgetMiniMize(string WindowName)//moved
//{
	//ContactLevel.MiniMizeWindow( WindowName );
//}

native function ASSendFriendChatByRoleID( int nRoleID , string ChatMsg );

native function ASSelectRoleChatWnd(int nRoleID);

native function ASCloseRoleChatWnd(int nRoleID);

native function ASContactWidgetMiniMize(string WindowName);

native function ASShowFriendChatList();

native function ASOnPanelClose( string PanelName );

DefaultProperties
{
	IsDynamicLoad=true
	CloseOnEsc=false
	DefaultVisible=false
	//CurWindowId=0
	//WindowChatNum=4
	CanMoveTop=false
}
