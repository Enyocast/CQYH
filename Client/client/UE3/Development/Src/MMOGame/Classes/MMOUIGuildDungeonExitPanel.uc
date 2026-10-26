class MMOUIGuildDungeonExitPanel extends MMOUIBase
	native(UI);

event InitLoad(MMOGFXPlayer pl)
{
	super.InitLoad(pl);
}

// UC->AS


native final function ASLeaveGuildDungeonEx();

DefaultProperties
{
	IsDynamicLoad=true
	DefaultVisible=false
}
