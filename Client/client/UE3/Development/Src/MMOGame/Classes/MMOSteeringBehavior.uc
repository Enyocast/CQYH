
class MMOSteeringBehavior extends object
	native
	hidecategories(Object)
	ClassGroup(__Crowd__);

 
enum ESummingMethod
{
	ESMD_WeightedAverage,
	ESMD_Prioritized,
	ESMD_Dithered
};

  
//a pointer to the owner of this instance
var MMOCrowdInstance     CrowdInstance;   
  
//the steering force created by the combined effect of all
//the selected behaviors
var vector    SteeringForce;
 
//these can be used to keep track of friends, pursuers, or prey
var MMOCrowdInstance     TargetAgent1;
var MMOCrowdInstance     TargetAgent2;

//the current target
var vector    Target;

var() editinline array<IMMOSteeringBehaviorInitProc> InitProc;

//length of the 'detection box' utilized in obstacle avoidance
var() float                 DBoxLength;


//a vertex buffer to contain the feelers rqd for wall avoidance  
//std::vector<vector> Feelers;
  
//the length of the 'feeler/s' used in wall detection
var() float                 WallDetectionFeelerLength;



//the current position on the wander circle the agent is
//attempting to steer towards
var vector     WanderTarget; 

//explained above
var() float        WanderJitter;
var() float        WanderRadius;
var() float        WanderDistance;


//multipliers. These can be adjusted to effect strength of the  
//appropriate behavior. Useful to get flocking the way you require
//for example.
var() float        WeightSeparation;
var() float        WeightCohesion;
var() float        WeightAlignment;
var() float        WeightWander;
var() float        WeightObstacleAvoidance;
var() float        WeightWallAvoidance;
var() float        WeightSeek;
var() float        WeightFlee;
var() float        WeightArrive;
var() float        WeightPursuit;
var() float        WeightOffsetPursuit;
var() float        WeightInterpose;
var() float        WeightHide;
var() float        WeightEvade;
var() float        WeightFollowPath;

//how far the agent can 'see'
var() float        ViewDistance;

//pointer to any current path
//Path*          Path;

//the distance (squared) a MMOCrowdInstance has to be from a path waypoint before
//it starts seeking to the next waypoint
var() float        WaypointSeekDistSq;


//any offset used for formations or offset pursuit
var() vector     Offset;



//binary flags to indicate whether or not a behavior should be active
var int           Flags;

  
//Arrive makes use of these to determine how quickly a MMOCrowdInstance
//should decelerate to its target
enum EDeceleration
{
	ED_Zero,
	ED_Fast,
	ED_Normal,
	ED_Slow,
};

//default
var() EDeceleration Deceleration;

//is cell space partitioning to be used or not?
var bool          CellSpaceOn;
 
//what type of method is used to sum any active behavior
var() ESummingMethod  SummingMethod;

enum EPathFollowMode
{
	EPFM_Loop,
	EPFM_Reverse
};

var EPathFollowMode FollowMode;
var() SplineActor TheFollowPath;
var SplineActor CurrentTargetPathNode;

native function NativePostBeginPlay();

event PostBeginPlay()
{
	local IMMOSteeringBehaviorInitProc proc;

	NativePostBeginPlay();

	foreach InitProc(proc)	
	{
		proc.OnProcess(self);
	}

}

DefaultProperties
{
	DBoxLength=40
    WeightCohesion=2
    WeightAlignment=1
    WeightSeparation=1
    WeightObstacleAvoidance=10
    WeightWander=1
    WeightWallAvoidance=10
    ViewDistance=150
    WallDetectionFeelerLength=40
    //Feelers=3
    Deceleration=ED_Normal
    WanderDistance=2
    WanderJitter=8.
    WanderRadius=1.2
    WaypointSeekDistSq=400
    WeightSeek=1
    WeightFlee=1
    WeightArrive=1
    WeightPursuit=1
    WeightOffsetPursuit=1
    WeightInterpose=1
    WeightHide=1
    WeightEvade=0.01
    WeightFollowPath=0.05
    //CellSpaceOn(false),
    SummingMethod=ESMD_Prioritized


}
