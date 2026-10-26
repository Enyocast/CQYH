class MMOUIFriendListContent extends MMOUIBase
	native(UI);

event CallSetFriendGroupListData( GFxObject data )
{
	ActionScriptVoid("SetFriendGroupListData");
}

event CallCreateNewGroup( String GroupName , int GroupId )
{
	ActionScriptVoid("CreateNewGroup");
}

event CallDeleteGroup( int groupId )
{
	ActionScriptVoid("DeleteGroup");
}

//------------moved--------------


DefaultProperties
{

}
