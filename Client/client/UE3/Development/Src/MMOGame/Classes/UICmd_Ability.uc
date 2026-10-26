//
// 
//
class UICmd_Ability extends IUICommand
	native(UI);

var MMOAbility CmdAbility;
var bool bCancelAbility;

event MMOAbility GetBindAbilityData()
{
	return CmdAbility;
}

native function Use();
native function NativeRelease();

function OnRelease()
{
	if(CmdAbility == none)
	{
		`log("UICmd_Ability : OnRelease but no Ability data");
		return;
	}

	NativeRelease();
	PC.PressAbilityKey(CmdAbility, PC.GetTraceActor(), true);
	//if(CmdAbility.ClientCommonAttribute.bRequestCancelOnRelease)
	//{
	//	PC.PressAbilityKey(CmdAbility, PC.TraceActor,true);
	//	//PC.AddCmdCancelAbility(CmdAbility);
	//}
}

event SetData( int InCmdID, int InSlotID, MMOPlayerController InPC)
{
	local MMOActor OwnerActor;
	super.SetData(InCmdID, InSlotID, InPC);

	OwnerActor = MMOActor(PC.Pawn);
	CmdAbility = OwnerActor.GetEquipedAbilityById(InCmdID);
	if(CmdAbility != none)
	{
		CmdAbility.SlotHotKeyID = InSlotID;
	}
	else
	{
		`warn("can not find ability data by Id="$InCmdID);
	}
}

DefaultProperties
{
}
