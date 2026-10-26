class MMOUIEquipDecomposeHintPanel extends MMOUIBase
	native(UI)
	config(UIVisibleMask);

var int iConId;
var int iSlotId;
var string strContent;

native function SetDecomposedEquipPos(int cid, int sid);
native function SetContent(string str);
native function DecomposeOk();

native function UpdateUI();

event CallSetHintText(GFxObject data)
{
	ActionScriptVoid("SetHintText");
}