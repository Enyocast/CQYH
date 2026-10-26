class MMOUIDynamicPassword extends MMOUIBase
	native(UI);


event InitLoad(MMOGFXPlayer pl)
{
	super.InitLoad(pl);
}

native function NativeInitOnce();

native final function ASDynamicPwdData(GFxObject mc);

native final function ASLinkKeeperCallBack();

native final function ASLinkHelpCallBack();


event CallUCSetData(string idx)
{
	ActionScriptVoid("UCSetData");
}

DefaultProperties
{
	
}
