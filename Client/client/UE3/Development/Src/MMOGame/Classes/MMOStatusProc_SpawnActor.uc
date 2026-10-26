//
// 生成对象
//
class MMOStatusProc_SpawnActor extends Object implements(IMMOStatusProc)
	native
	editinlinenew
	hidecategories(Object);

var() Actor ActorTemplate;
var() int SpawnCount;
var() Vector2d PositionOffsetRange;

// 如果不随机朝向则与角色朝向一致
var() bool EnableRandomRotation;

event OnExecute(MMOActor actor)
{	
	local int i;
	local Vector spawnLocationt;
	local float ofx, ofy;
	local Rotator oyaw;

	for(i = 0; i < SpawnCount; ++i)
	{
		ofx = RandRange(-PositionOffsetRange.X, PositionOffsetRange.X);
		ofy = RandRange(-PositionOffsetRange.Y, PositionOffsetRange.Y);
		spawnLocationt = actor.Location;
		spawnLocationt.X += ofx;
		spawnLocationt.Y += ofy;
		
		if(EnableRandomRotation)
		{
			oyaw.Yaw = FRand() * 360.0 * DegToUnrRot;
		}
		else
		{
			oyaw.Yaw = actor.Rotation.Yaw;
		}

		actor.Spawn(ActorTemplate.Class,,, spawnLocationt,
			oyaw, ActorTemplate, true);
		//Location + vect(RandRange(-100, 100), RandRange(-100, 100), 0)
	}
}
native function Update(MMOActor actor);


defaultproperties
{
	PositionOffsetRange=(X=100,Y=100)
	EnableRandomRotation=true
}