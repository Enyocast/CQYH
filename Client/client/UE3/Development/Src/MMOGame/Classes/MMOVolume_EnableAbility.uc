//
// 相机导航碰撞框，当玩家与该碰撞框接触时，相机自动平滑过度到这个角度
//

class MMOVolume_EnableAbility extends Volume
	placeable;

// 进入时是否能使用技能
var(MMO) bool EnterEnableAbility;

// 退出时是否能使用技能
var(MMO) bool ExitEnableAbility;

simulated event PostBeginPlay()
{
	super.PostBeginPlay();
}

event Touch(Actor Other, PrimitiveComponent OtherComp, vector HitLocation, vector HitNormal)
{
	local MMOPlayer player;
	local MMOPlayerController pc;

	Super.Touch(Other,OtherComp,HitLocation,HitNormal);

	player = MMOPlayer(Other);

	if(player != none)
	{
		pc = MMOPlayerController(player.Controller);
		pc.ClientCanUseAbility = EnterEnableAbility;
	}
}

event UnTouch(Actor Other)
{
	local MMOPlayer player;
	local MMOPlayerController pc;

	super.UnTouch(Other);

	player = MMOPlayer(Other);

	if(player != none)
	{
		pc = MMOPlayerController(player.Controller);
		pc.ClientCanUseAbility = ExitEnableAbility;
	}
}

defaultproperties
{
	EnterEnableAbility=false
	ExitEnableAbility=true
}
