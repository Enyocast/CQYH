//
// HUD接口，需要显示HUD的Actor可以实现相应的此类接口
//
interface IMMOActorHUD
	native;

native function bool DrawMyHUD( MMOHud H );
native function DrawHUDPostGFx( HUD H);

/** whether to only draw the HUD if the Pawn whose viewport we're drawing is the Owner of this Actor */
function bool OnlyDrawHUDForOwner();