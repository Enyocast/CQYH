class IUICommand 
	extends Object
	native(UI);

var int CmdID;
var int SlotID;
var MMOPlayerController PC;

event Use()
{

}

event OnRelease()
{

}

event SetData( int InCmdID, int InSlotID, MMOPlayerController InPC )
{
    CmdID = InCmdID;
    SlotID = InSlotID;
    PC = InPC;
}

native function int GetID();
native function int GetSlotID();

defaultproperties
{
	CmdID=-1
	SlotID=-1
}
