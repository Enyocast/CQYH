class MMOGFXPlayer_EquipDecompose extends MMOGFXPlayer
	native(UI)
	config(MMOGame);

var MMOUIEquipComposePanel m_ComposePanel;
var MMOUIEquipDecomposePanel m_DecomposePanel;
var MMOUIEquipDecomposeHintPanel m_DecomposeHintPanel;

function ASRegisterEquipComposePanel(MMOUIEquipComposePanel panel)
{
	`log("#########################################################ASRegisterEquipComposePanel");
	m_ComposePanel = panel;
	RegisterUI(panel,class'MMOUIManager'.default.Panel_EquipCompose);
}

function ASRegisterEquipDecomposePanel(MMOUIEquipDecomposePanel panel)
{
	`log("#########################################################ASRegisterEquipDecomposePanel");
	m_DecomposePanel = panel;
	RegisterUI(panel,class'MMOUIManager'.default.Panel_EquipDecompose);
}

function ASRegisterDecomposeHintPanel(MMOUIEquipDecomposeHintPanel panel)
{
	`log("#########################################################ASRegisterDecomposeHintPanel");
	m_DecomposeHintPanel = panel;
	RegisterUI(panel,class'MMOUIManager'.default.Panel_EquipDecomposeHint);
}

native function ASCompose();

native function ASDecomposeOk();
native function ASDecomposeCancel();
native function ASNotifyComposeSuccessAnimPlayedOver();

defaultproperties
{
	MovieInfoStr="UI_EquipDecompose.EquipDecompose";
	Priority = 5;
}