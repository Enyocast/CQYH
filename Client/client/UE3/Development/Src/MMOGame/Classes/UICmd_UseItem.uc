//
//
class UICmd_UseItem extends IUICommand
	native(UI);

native function Use ();
native function NativeRelease();

event OnRelease()
{
	NativeRelease();
}

DefaultProperties
{
	
}
