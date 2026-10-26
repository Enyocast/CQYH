class MMOGFXPlayer_Mail extends MMOGFXPlayer
	native(UI);

var MMOUIMailPanel _MailListPanel;
var MMOUIMailReadPanel _MailReadPanel;

function ASRegisterMailListPanel( MMOUIMailPanel mc )
{
	_MailListPanel = mc;
	RegisterUI( mc, class'MMOUIManager'.default.Panel_Mail);
}

function ASRegisterReadMailPanel( MMOUIMailReadPanel mc )
{
	_MailReadPanel = mc;
	RegisterUI( mc, class'MMOUIManager'.default.Panel_Mail_MailRead);
}

native final function ASReadMail(int mailID);//moved
native final function ASReplyMail(int mailID);//moved
native final function ASDeleteMail(int mailID);//moved
native final function ASAcquireMailItems(int mailID);//moved

native final function ASSendMail(string toPlayer, string title, string content);//moved


native final function ASReadAll();//moved
native final function ASSelectAll();//moved
native final function ASDeleteSelected();//moved
native final function ASSelectMail(int mailID, bool select);//moved
native final function ASMessageMailContentTooLong();//moved
native final function OnDeleteMail(GFxObject mc);//moved
native final function ASSelectMailType(int nType);//moved

DefaultProperties
{
	MovieInfoStr="UI_MailWidget.MailWidget"
	Priority=5
}
