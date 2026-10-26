class MMOUIMsgButtonBar extends MMOUIBase	
	native(UI);

const msgButtonCount = 5;
var GFxObject _MsgButton[msgButtonCount];

event InitOnce()
{
//	local int i;

	super.InitOnce();

// 	for( i = 0 ; i < msgButtonCount ; i++ )
// 	{
// 		_MsgButton[i] = GetObject("MsgButton"$i);
// 		_MsgButton[i].SetVisible(false);
// 	}

	//class'MMOUIManager'.static.SetSetMsgButtonNumDelegate(SetButtonNum);
	//class'MMOUIManager'.static.SetSetMsgButtonIconDelegate(SetButtonIcon);
}

native final function OpenMailPanel();
native final function OpenMasterStudentPanel();
native final function OpenCongUpLevelPanel();
native final function OpenGuildWarStartPanelAttack();
native final function OpenGuildWarStartPanelDefend();
native final function OpenGuildMainPanelApplyAlly();
native final function OpenNewSurvey();
native final function OpenDailySignInPanel();
native final function OpenJigsawPanel();

native function SetButtonNum( int num );
native function SetButtonIcon( int index , int frame );

event CallAddNewButton( GFxObject data )
{
	ActionScriptVoid("addNewButton");
}

event CallRemoveButton( int pos )
{
	ActionScriptVoid("removeButton");
}

event CallUpdateMsgScrolingList( GFxObject data )
{
	ActionScriptVoid("updateMsgScrolingList");
}

event CallToggleMsgScrolingList( int type )
{
	ActionScriptVoid("toggleMsgScrolingList");
}

native function ClearUI();

native function ASMsgButtonClick( int idx);
native function ASMsgListClick( int idx , int type );

DefaultProperties
{
	CloseOnEsc=false
}
