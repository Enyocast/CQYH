class MMOCrowdInstance extends Object
	native
	editinlinenew
	hidecategories(Object)
	ClassGroup(__Crowd__);

var MMOCrowdSystem Owner;
var() editinline MMOSteeringBehavior SteeringBehavior;
var() vector Location;
var() vector DrawScale3D;
var vector Direction;
var vector SideVector;

var vector Velocity;
var() float Mass;
var() float MaxSpeed;
var() float MaxForce;
var() float MaxTurnRate;
var() float BoundingRadius;

var bool IsTag;
var float TimeElapsed;


event PostBeginPlay()
{
	//super.PostBeginPlay();

	SteeringBehavior = new class'MMOSteeringBehavior';
}

DefaultProperties
{
	IsTag=false
	Mass=1
	MaxSpeed=150
	MaxForce=2
	MaxTurnRate=3.14159265358979
	BoundingRadius=200
	DrawScale3D=(X=1,Y=1,Z=1)

// 	begin object class=MMOSteeringBehavior name=Steering0
// 		CrowdInstance=self
// 	end object
// 	SteeringBehavior=Steering0

}
