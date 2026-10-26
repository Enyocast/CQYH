class MMOStatue extends MMOActor implements(IMMOActorHUD, IInteractableActor)
	dependson(NPC)
	placeable
	config(MMOGame)
	native
	hidecategories(Object,Advanced,Attachment,Display,Debug,Camera,AI);

function bool OnlyDrawHUDForOwner() { return false; }
native function DrawHUDPostGFx(HUD hud);
native function bool DrawMyHUD(MMOHud hud);
native function DoInteract();
native function bool CanInteract() const;
native function vector GetInteractActorLocation();
native function float GetMaxInteractRadius();
native function SetSilhouette(bool show, Vector sc = vect( 1.f, 1.f, 0.f ));

DefaultProperties
{
}
