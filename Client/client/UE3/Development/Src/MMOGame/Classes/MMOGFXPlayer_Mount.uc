class MMOGFXPlayer_Mount extends MMOGFXPlayer
	native(UI)
	config(MMOGame);


var MMOUIMountPanel            Mount;

function RegisterMount( MMOUIMountPanel mc )
{        
	Mount = mc;
	RegisterUI( mc, class'MMOUIManager'.default.Panel_Mount);
}

native function PostAdvance(float DeltaTime );

native function ASUnEquipMount();//moved
native function ASEquipMount(int MountID);//moved



function RefreshMount()//moved
{
	Mount.UpdateMount();
}

function RefreshEquipedMount()//moved
{
	Mount.UpdateEquipedMount();
}

DefaultProperties
{
	MovieInfoStr="UI_Mount.Mount"
	//TurnButton=TBS_None
}
