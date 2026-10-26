class MMOGFXPlayer_EquipLevelUp extends MMOGFXPlayer
	native(UI)
	config(MMOGame);

var MMOUIEquipLevelUp _EquipLevelUp;
var MMOUIMutiLineMsgBox _MutiLineMsgBox;

function RegisterEquipLevelUp( MMOUIEquipLevelUp mc )
{
	_EquipLevelUp = mc;
	RegisterUI( mc, class'MMOUIManager'.default.Panel_EquipLevelUp);
}

function RegisteMutiLineMsgBox( MMOUIMutiLineMsgBox mc )
{
	_MutiLineMsgBox = mc;
	RegisterUI( mc, class'MMOUIManager'.default.Panel_MutiLineMsgBox);
}

//
final native function ASConfirmUpgrade();
final native function ASCancelUpgrade();

final native function ASShowResultConfirmBox( bool isToShow );
final native function ASConfirmMessage();

//end
//
DefaultProperties
{
	MovieInfoStr="UI_EquipLevelUp.EquipLevelUp"
	Priority=5
}
