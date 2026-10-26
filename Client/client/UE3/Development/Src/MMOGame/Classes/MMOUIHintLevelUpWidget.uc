class MMOUIHintLevelUpWidget extends MMOUIBase
	native(UI);


event Open(string levelUp,INT strengthAdd,INT agilityAdd,	INT intellectAdd,	INT staminaAdd, 	INT spiritAdd,	 INT maxHpAdd )
{
	local array<ASValue> args;
	local ASValue asval;
	NativeShow(true);

	asval.Type = AS_String;
	asval.s = levelUp;
	args[0] = asval;

	asval.Type = AS_Number;
	asval.n = strengthAdd;
	args[1] = asval;

	asval.Type = AS_Number;
	asval.n = agilityAdd;
	args[2] = asval;

	asval.Type = AS_Number;
	asval.n = intellectAdd;
	args[3] = asval;

	asval.Type = AS_Number;
	asval.n = staminaAdd;
	args[4] = asval;

	asval.Type = AS_Number;
	asval.n = spiritAdd;
	args[5] = asval;

	asval.Type = AS_Number;
	asval.n = maxHpAdd;
	args[6] = asval;
	Invoke("ShowLevelUp",args);
}

event Close()
{
	local array<ASValue> args;
	args.Length = 0;
	Invoke("CloseQTE",args);
}


DefaultProperties
{
}
