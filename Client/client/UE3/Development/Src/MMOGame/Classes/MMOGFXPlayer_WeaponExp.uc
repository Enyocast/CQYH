class MMOGFXPlayer_WeaponExp extends MMOGFXPlayer
	native(UI)
	config(MMOGame);

var MMOUIWeaponExpPanel WeaponExp;

function RegisterWeaponExpPanel( MMOUIWeaponExpPanel mc )
{
	WeaponExp = mc;
	RegisterUI( mc, class'MMOUIManager'.default.Panel_WeaponExp);
}

// event UnRegister()
// {
// 	super.UnRegister();
// 	RegisterUI( none, class'MMOUIManager'.default.Panel_WeaponExp);
// 	MMOUI::RegisterMoviePlayer(class'MMOUIManager'.default.MoviePlayer_WeaponExp);
// 
// }

function ASGetWeaponExp()
{
	WeaponExp.GetWeaponExp();
}

DefaultProperties
{
	MovieInfoStr="UI_WeaponExpWidget.WeaponExpWidget"
	Priority=5

}
