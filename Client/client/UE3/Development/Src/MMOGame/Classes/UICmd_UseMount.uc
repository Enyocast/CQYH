//
//
class UICmd_UseMount extends IUICommand
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
