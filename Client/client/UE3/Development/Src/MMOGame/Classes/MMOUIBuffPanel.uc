class MMOUIBuffPanel extends MMOUIBase
	native(UI);

function Open(int buffSlotID,string buffIcon, int buffMaxTime, int buffCurTime, int stackCount,int ownerID,int buffID,int showTimeUp,bool debuff)
{
	local array<ASValue> args;
	local ASValue asval;

	asval.Type = AS_Number;
	asval.n = buffSlotID;
	args[0] = asval;
	asval.Type = AS_String;
	asval.s = buffIcon;
	args[1] = asval;
	asval.Type = AS_Number;
	asval.n = buffMaxTime;
	args[2] = asval;
	asval.Type = AS_Number;
	asval.n = buffCurTime;
	args[3] = asval;
	asval.Type = AS_Number;
	asval.n = stackCount;
	args[4] = asval;
	asval.Type = AS_Number;
	asval.n = ownerID;
	args[5] = asval;
	asval.Type = AS_Number;
	asval.n = buffID;
	args[6] = asval;
	asval.Type = AS_Number;
	asval.n = showTimeUp;
	args[7] = asval;
	asval.Type = AS_Boolean;
	asval.B = debuff;
	args[8] = asval;
	Invoke("ShowBuff",args);
}

function Close(int buffSlotID)
{
	local array<ASValue> args;
	local ASValue asval;
	asval.Type = AS_Number;
	asval.n = buffSlotID;
	args[0] = asval;
	Invoke("HideBuff",args);
}

native function bool SkipCaptureInputKey(String key, EInputEvent eIE, const string strHoverControllerName, Vector2D ClickPosInMovieSpace);

//===============================================================================================================
//===============================================================================================================
event AddBuffPanel(int buffSlotID,string buffIcon,int buffMaxTime,int buffCurTime, int stackCount, int ownerID, int buffID,int showTimeUp,bool debuff)
{
	if(IsVisible)
	{
		Open( buffSlotID, buffIcon,  buffMaxTime, buffCurTime,stackCount,ownerID,buffID,showTimeUp,debuff);
	}
}
event DeleteBuffPanel(int buffSlotID)
{
	Close( buffSlotID );
}
//===============================================================================================================
//===============================================================================================================

DefaultProperties
{
	CloseOnEsc=false
}
