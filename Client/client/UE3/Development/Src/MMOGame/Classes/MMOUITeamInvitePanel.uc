class MMOUITeamInvitePanel extends MMOUIBase
	native(UI)
	config(UIVisibleMask);

var int CurTab;

event UpdateInvitePlayerList(GFxObject data)
{
	ActionScriptVoid("UCUpdateInvitePlayerList");
}

event UpdateTitle(string title)
{
	ActionScriptVoid("UCUpdateTitle");
}

//------------moved--------------
native function ASShowInviteFriendList();//moved invite
native function ASShowInviteRecentList();//moved invite
native function ASShowInviteGuiderList();//moved invite
native function ASClickInviteOk();//moved invite
native function ASClickInviteCancel();//moved invite

defaultproperties
{
	CurTab = -1;
}