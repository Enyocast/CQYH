class MMOUIJigsawPanel extends MMOUIBase
	dependson(TypeDefine)
	native(UI)
	config(UIVisibleMask);

event InitLoad(MMOGFXPlayer pl)
{
	super.InitLoad(pl);
}

event InitOnce()
{
	super.InitOnce();
}

native final function ASOnConfirmSelectedPart(int answer );

event CallSetJigsawCountingDown( int seconds)
{
	ActionScriptVoid("UCSetJigsawCountingDown");
}

event CallSetJigsawBlockOffSet( int OffsetX,int OffsetY)
{
	ActionScriptVoid("UCSetJigsawBlockOffSet");
}

DefaultProperties
{
	IsDynamicLoad=true
	CloseOnEsc=false
}
