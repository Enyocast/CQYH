class MMOGFXPlayer_RClickMenu extends MMOGFXPlayer
	native(UI)
	config(MMOGame);

var MMOUIRClickMenu	        RClickMenu;




function RegisterRClickMenu( MMOUIRClickMenu mc )
{
	RClickMenu = mc;
	RegisterUI( mc , class'MMOUIManager'.default.Panel_RClickMenu );
}

native function ASClickRightMenuItem( int MenuLevel, int ItemId );//moved

DefaultProperties
{
	MovieInfoStr="UI_RClickWidget.RClickWidget"
	Priority=7 

	//bAllowFocus=false   //zhaojun@snda
	//bAllowInput=false   //zhaojun@snda
}
