class MMOGFXPlayer_NpcDialogNew extends MMOGFXPlayer
	native(UI)
	config(MMOGame);

var MMOUIDialogNew            _DialogPanel;

function RegisterDialog( MMOUIDialogNew mc )
{
	_DialogPanel = mc;
	//RegisterUI( mc, class'MMOUIManager'.default.Panel_DialogNew);

	//self.OnPostAdvance = _DialogPanel.TickForTestInteractNPCDistance;
	self.OnPostAdvance = _DialogPanel.CheckPendingRT;
}


native final function ASSelectDiagOption(int optionID);
native final function ASNPCDialogPage(int pageIndex);
native final function ASCloseDialog();

native final function ASSelectAward(GFxObject icon, int idx, int itemTemplateID);

native final function ASAcceptQuest(int questID, bool share, int shareSrcId);
native final function ASAbortQuest(int questID);
native final function ASSubmitQuest(int questID);

native final function AbortQuest(int questID);

function AbortQuestOK(GFxObject mc)
{
	local int questID;
	questID = mc.GetInt("iteminfoid");
	AbortQuest(questID);
}

function AbortQuestCanel(GFxObject mc)
{
}

DefaultProperties
{
	MovieInfoStr="UI_NPCDialog.NpcDialog"
	Priority=5
}
