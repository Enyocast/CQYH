class MMOUIProgressBarStrengthWidget extends MMOUIBase
	native(UI);

event Open(int time, int max)
{
	local array<ASValue> args;
	local ASValue asval;
	NativeShow(true);
	asval.Type = AS_Number;
	asval.n = time;
	args[0] = asval;
	asval.Type = AS_Number;
	asval.n = max;
	args[1] = asval;
	Invoke("ShowStrength",args);
}

event Close(int closeType)
{
	local array<ASValue> args;
	args.Length = 0;
	Invoke("CloseStrength",args);
}

native function bool SkipCaptureInputKey(const string key, EInputEvent eIE, const string strHoverControllerName, Vector2D ClickPosInMovieSpace);

native function ShowProgressBarStrength(int time, int max);
native function CloseProgressBarStrength(int closeType);


DefaultProperties
{
	DefaultVisible = false
	CloseOnEsc=false
}
