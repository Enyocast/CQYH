class MMOUILoginRevertRolePanel extends MMOUIBase
native(UI)
config(UIVisibleMask);

native function funReverCancel();
native function funReverOk();
native function funDeleteCancel();
native function funDeleteOk();
native final function UpdateRevertPanelList();


event CallUCUpdateDelRoleList(GFxObject data)
{
	ActionScriptVoid("UCUpdateDelRoleList");
}

native function ASRequestFindRoleID(int nRoleID);
native function ASRequestDelectRole(int nRoleID);

DefaultProperties
{
	IsDynamicLoad=true
	DefaultVisible=true
}
