#include "stdafx.h"
#include "MMOCrowd.h"
#include "EngineSplineClasses.h"

IMPLEMENT_CLASS(UMMOSteeringBehavior);

//------------------------------------------------------------------------
// UMMOSteeringBehavior
//------------------------------------------------------------------------

inline FVector PointToWorldSpace(const FVector &point,
	const FVector &AgentHeading,
	const FVector &AgentSide,
	const FVector &AgentPosition)
{
	//make a copy of the point
	FVector TransPoint;

	//create a transformation matrix
	FMatrix matTransform = FRotationMatrix(AgentHeading.Rotation()) * FTranslationMatrix(AgentPosition);

	////rotate
	//matTransform.Rotate(AgentHeading, AgentSide);

	////and translate
	//matTransform.Translate(AgentPosition.x, AgentPosition.y);

	//now transform the vertices
	//matTransform.TransformVector2Ds(TransPoint);
	TransPoint = matTransform.TransformFVector(point);

	return TransPoint;
}

void UMMOSteeringBehavior::Init(class UMMOCrowdInstance* inst)
{

	CrowdInstance = inst;
	//FlockingOn();

	FLOAT theta = RandFloat() * PI * 2;

	//create a vector to a target position on the wander circle
	WanderTarget = FVector(WanderRadius * appCos(theta),
		WanderRadius * appSin(theta), 0);

}

//UMMOSteeringBehavior::UMMOSteeringBehavior(UMMOCrowdInstance* agent) :
//             CrowdInstance(agent),
//             Flags(0),
//             DBoxLength(40/*Prm_MinDetectionBoxLength*/),
//             WeightCohesion(/*Prm_CohesionWeight*/2),
//             WeightAlignment(/*Prm_AlignmentWeight*/1),
//             WeightSeparation(/*Prm_SeparationWeight*/1),
//             WeightObstacleAvoidance(10/*Prm_ObstacleAvoidanceWeight*/),
//             WeightWander(/*Prm_WanderWeight*/1),
//             WeightWallAvoidance(/*Prm_WallAvoidanceWeight*/10),
//             ViewDistance(/*Prm_ViewDistance*/50),
//             WallDetectionFeelerLength(40),
//             Feelers(3),
//             Deceleration(normal),
//             TargetAgent1(NULL),
//             TargetAgent2(NULL),
//             WanderDistance(WanderDist),
//             WanderJitter(WanderJitterPerSec),
//             WanderRadius(WanderRad),
//             WaypointSeekDistSq(WaypointSeekDist*WaypointSeekDist),
//             WeightSeek(/*Prm_SeekWeight*/1),
//             WeightFlee(/*Prm_FleeWeight*/1),
//             WeightArrive(/*Prm_ArriveWeight*/1),
//             WeightPursuit(/*Prm_PursuitWeight*/1),
//             WeightOffsetPursuit(/*Prm_OffsetPursuitWeight*/1),
//             WeightInterpose(/*Prm_InterposeWeight*/1),
//             WeightHide(/*Prm_HideWeight*/1),
//             WeightEvade(/*Prm_EvadeWeight*/0.01),
//             WeightFollowPath(0.05),
//             CellSpaceOn(false),
//             SummingMethod(prioritized)
//
//
//{
//  //stuff for the wander behavior
//  FLOAT theta = RandFloat() * PI * 2;
//
//  //create a vector to a target position on the wander circle
//  WanderTarget = FVector(WanderRadius * appCos(theta),
//                              WanderRadius * appSin(theta), 0);
//
//  //create a Path
//  //Path = new Path();
//  //Path->LoopOn();
//
//}

/////////////////////////////////////////////////////////////////////////////// CALCULATE METHODS 


//----------------------- Calculate --------------------------------------
//
//  calculates the accumulated steering force according to the method set
//  in SummingMethod
//------------------------------------------------------------------------
FVector UMMOSteeringBehavior::Calculate()
{ 
	//reset the steering force
	SteeringForce.Set(0, 0, 0);

	//use space partitioning to calculate the neighbours of this UMMOCrowdInstance
	//if switched on. If not, use the standard tagging system
	if (!isSpacePartitioningOn())
	{
		//tag neighbors if any of the following 3 group behaviors are switched on
		if (On(separation) || On(allignment) || On(cohesion))
		{
			CrowdInstance->GetOwner()->TagVehiclesWithinViewRange(CrowdInstance, ViewDistance);
		}
	}
	else
	{
		//calculate neighbours in cell-space if any of the following 3 group
		//behaviors are switched on
		if (On(separation) || On(allignment) || On(cohesion))
		{
			//CrowdInstance->GetOwner()->CellSpace()->CalculateNeighbors(CrowdInstance->GetLocation(), ViewDistance);
		}
	}

	//   switch (SummingMethod)
	//   {
	//   //case ESM_WeightedAverage:
	//   //  
	//   //  SteeringForce = CalculateWeightedSum(); break;
	// 
	//   case prioritized:
	// 
	SteeringForce = CalculatePrioritized();
	//break;

	//case dithered:

	//SteeringForce = CalculateDithered();break;

	//   default:SteeringForce = FVector(0,0,0); 
	// 
	//   }//end switch

	return SteeringForce;
}

//------------------------- ForwardComponent -----------------------------
//
//  returns the forward oomponent of the steering force
//------------------------------------------------------------------------
FLOAT UMMOSteeringBehavior::ForwardComponent()
{
	return CrowdInstance->Heading() | (SteeringForce);
}

//--------------------------- SideComponent ------------------------------
//  returns the side component of the steering force
//------------------------------------------------------------------------
FLOAT UMMOSteeringBehavior::SideComponent()
{
	return CrowdInstance->Side() | (SteeringForce);
}


//--------------------- AccumulateForce ----------------------------------
//
//  This function calculates how much of its max steering force the 
//  UMMOCrowdInstance has left to apply and then applies that amount of the
//  force to add.
//------------------------------------------------------------------------
bool UMMOSteeringBehavior::AccumulateForce(FVector &RunningTot,
	FVector ForceToAdd)
{
	if(!CrowdInstance)
	{
		return true;
	}

	//calculate how much steering force the UMMOCrowdInstance has used so far
	FLOAT MagnitudeSoFar = RunningTot.Size();

	//calculate how much steering force remains to be used by this UMMOCrowdInstance
	FLOAT MagnitudeRemaining = CrowdInstance->GetMaxForce() - MagnitudeSoFar;

	//return false if there is no more force left to use
	if (MagnitudeRemaining <= 0.0) return false;

	//calculate the magnitude of the force we want to add
	FLOAT MagnitudeToAdd = ForceToAdd.Size();

	//if the magnitude of the sum of ForceToAdd and the running total
	//does not exceed the maximum force available to this UMMOCrowdInstance, just
	//add together. Otherwise add as much of the ForceToAdd vector is
	//possible without going over the max.
	if (MagnitudeToAdd < MagnitudeRemaining)
	{
		RunningTot += ForceToAdd;
	}

	else
	{
		//add it to the steering force
		RunningTot += ((ForceToAdd).SafeNormal() * MagnitudeRemaining); 
	}

	return true;
}



//---------------------- CalculatePrioritized ----------------------------
//
//  this method calls each active steering behavior in order of priority
//  and acumulates their forces until the max steering force magnitude
//  is reached, at which time the function returns the steering force 
//  accumulated to that  point
//------------------------------------------------------------------------
FVector UMMOSteeringBehavior::CalculatePrioritized()
{       
	FVector force;

	if (On(wall_avoidance))
	{
		//force = WallAvoidance(CrowdInstance->GetOwner()->Walls()) *
		//        WeightWallAvoidance;

		//if (!AccumulateForce(SteeringForce, force)) return SteeringForce;
	}

	if (On(obstacle_avoidance))
	{
		//force = ObstacleAvoidance(CrowdInstance->GetOwner()->Obstacles()) * 
		//        WeightObstacleAvoidance;

		//if (!AccumulateForce(SteeringForce, force)) return SteeringForce;
	}

	if (On(evade))
	{
		//check(TargetAgent1 && "Evade target not assigned");

		force = Evade(TargetAgent1) * WeightEvade;

		if (!AccumulateForce(SteeringForce, force)) return SteeringForce;
	}


	if (On(flee))
	{
		force = Flee(/*CrowdInstance->GetOwner()->Crosshair()*/Target) * WeightFlee;

		if (!AccumulateForce(SteeringForce, force)) return SteeringForce;
	}



	//these next three can be combined for flocking behavior (wander is
	//also a good behavior to add into this mix)
	if (!isSpacePartitioningOn())
	{
		if (On(separation))
		{
			force = Separation(CrowdInstance->GetOwner()->CrowdInstanceData) * WeightSeparation;

			if (!AccumulateForce(SteeringForce, force)) return SteeringForce;
		}

		if (On(allignment))
		{
			force = Alignment(CrowdInstance->GetOwner()->CrowdInstanceData) * WeightAlignment;

			if (!AccumulateForce(SteeringForce, force)) return SteeringForce;
		}

		if (On(cohesion))
		{
			force = Cohesion(CrowdInstance->GetOwner()->CrowdInstanceData) * WeightCohesion;

			if (!AccumulateForce(SteeringForce, force)) return SteeringForce;
		}
	}

	else
	{

		if (On(separation))
		{
			force = SeparationPlus(CrowdInstance->GetOwner()->CrowdInstanceData) * WeightSeparation;

			if (!AccumulateForce(SteeringForce, force)) return SteeringForce;
		}

		if (On(allignment))
		{
			force = AlignmentPlus(CrowdInstance->GetOwner()->CrowdInstanceData) * WeightAlignment;

			if (!AccumulateForce(SteeringForce, force)) return SteeringForce;
		}

		if (On(cohesion))
		{
			force = CohesionPlus(CrowdInstance->GetOwner()->CrowdInstanceData) * WeightCohesion;

			if (!AccumulateForce(SteeringForce, force)) return SteeringForce;
		}
	}

	if (On(seek))
	{
		force = Seek(Target) * WeightSeek;

		if (!AccumulateForce(SteeringForce, force)) return SteeringForce;
	}


	if (On(arrive))
	{
		force = Arrive(Target, Deceleration) * WeightArrive;

		if (!AccumulateForce(SteeringForce, force)) return SteeringForce;
	}


	if (On(wander))
	{
		force = Wander() * WeightWander;

		if (!AccumulateForce(SteeringForce, force)) return SteeringForce;
	}

	if (On(pursuit))
	{
		//check(TargetAgent1 && "pursuit target not assigned");

		force = Pursuit(TargetAgent1) * WeightPursuit;

		if (!AccumulateForce(SteeringForce, force)) return SteeringForce;
	}

	if (On(offset_pursuit))
	{
		//check (TargetAgent1 && "pursuit target not assigned");
		//check (!Offset.IsZero() && "No offset assigned");

		force = OffsetPursuit(TargetAgent1, Offset);

		if (!AccumulateForce(SteeringForce, force)) return SteeringForce;
	}

	if (On(interpose))
	{
		//check (TargetAgent1 && TargetAgent2 && "Interpose agents not assigned");

		force = Interpose(TargetAgent1, TargetAgent2) * WeightInterpose;

		if (!AccumulateForce(SteeringForce, force)) return SteeringForce;
	}

	if (On(hide))
	{
		//     check(TargetAgent1 && "Hide target not assigned");
		// 
		//     force = Hide(TargetAgent1, CrowdInstance->GetOwner()->Obstacles()) * WeightHide;
		// 
		//     if (!AccumulateForce(SteeringForce, force)) return SteeringForce;
	}


	if (On(follow_path))
	{
		force = FollowPath() * WeightFollowPath;

		if (!AccumulateForce(SteeringForce, force)) return SteeringForce;
	}

	return SteeringForce;
}


/////////////////////////////////////////////////////////////////////////////// START OF BEHAVIORS

//------------------------------- Seek -----------------------------------
//
//  Given a target, this behavior returns a steering force which will
//  direct the agent towards the target
//------------------------------------------------------------------------
FVector UMMOSteeringBehavior::Seek(const FVector& TargetPos)
{
	FVector DesiredVelocity = (TargetPos - CrowdInstance->GetLocation()).SafeNormal()
		* CrowdInstance->GetMaxSpeed();

	return (DesiredVelocity - CrowdInstance->GetVelocity());
}

//----------------------------- Flee -------------------------------------
//
//  Does the opposite of Seek
//------------------------------------------------------------------------
FVector UMMOSteeringBehavior::Flee(const FVector& TargetPos)
{
	//only flee if the target is within 'panic distance'. Work in distance
	//squared space.
	/* const FLOAT PanicDistanceSq = 100.0f * 100.0;
	if (Vec2DDistanceSq(CrowdInstance->GetLocation(), target) > PanicDistanceSq)
	{
	return FVector(0,0);
	}
	*/

	FVector DesiredVelocity = (CrowdInstance->GetLocation() - TargetPos).SafeNormal()
		* CrowdInstance->GetMaxSpeed();

	return (DesiredVelocity - CrowdInstance->GetVelocity());
}

//--------------------------- Arrive -------------------------------------
//
//  This behavior is similar to seek but it attempts to arrive at the
//  target with a zero velocity
//------------------------------------------------------------------------
FVector UMMOSteeringBehavior::Arrive(const FVector&     TargetPos,
	BYTE deceleration)
{
	FVector ToTarget = TargetPos - CrowdInstance->GetLocation();

	//calculate the distance to the target
	FLOAT dist = ToTarget.Size();

	if (dist > 0)
	{
		//because Deceleration is enumerated as an int, this value is required
		//to provide fine tweaking of the deceleration..
		const FLOAT DecelerationTweaker = 0.3;

		//calculate the speed required to reach the target given the desired
		//deceleration
		FLOAT speed =  dist / ((FLOAT)deceleration * DecelerationTweaker);     

		//make sure the velocity does not exceed the max
		speed = Min(speed, CrowdInstance->GetMaxSpeed());

		//from here proceed just like Seek except we don't need to normalize 
		//the ToTarget vector because we have already gone to the trouble
		//of calculating its length: dist. 
		FVector DesiredVelocity =  ToTarget * speed / dist;

		return (DesiredVelocity - CrowdInstance->GetVelocity());
	}

	return FVector(0,0,0);
}

//------------------------------ Pursuit ---------------------------------
//
//  this behavior creates a force that steers the agent towards the 
//  evader
//------------------------------------------------------------------------
FVector UMMOSteeringBehavior::Pursuit(const UMMOCrowdInstance* evader)
{
	//if the evader is ahead and facing the agent then we can just seek
	//for the evader's current position.
	if(!evader || !CrowdInstance)
	{
		return FVector::ZeroVector;
	}

	FVector ToEvader = evader->GetLocation() - CrowdInstance->GetLocation();

	FLOAT RelativeHeading = CrowdInstance->Heading() | (evader->Heading());

	if ( ((ToEvader | CrowdInstance->Heading()) > 0) &&  
		(RelativeHeading < -0.95))  //acos(0.95)=18 degs
	{
		return Seek(evader->GetLocation());
	}

	//Not considered ahead so we predict where the evader will be.

	//the lookahead time is propotional to the distance between the evader
	//and the pursuer; and is inversely proportional to the sum of the
	//agent's velocities
	FLOAT LookAheadTime = ToEvader.Size() / 
		(CrowdInstance->GetMaxSpeed() + evader->GetSpeed());

	//now seek to the predicted future position of the evader
	return Seek(evader->GetLocation() + evader->GetVelocity() * LookAheadTime);
}


//----------------------------- Evade ------------------------------------
//
//  similar to pursuit except the agent Flees from the estimated future
//  position of the pursuer
//------------------------------------------------------------------------
FVector UMMOSteeringBehavior::Evade(const UMMOCrowdInstance* pursuer)
{
	/* Not necessary to include the check for facing direction this time */
	if(!pursuer)
	{
		return FVector::ZeroVector;
	}


	FVector ToPursuer = pursuer->GetLocation() - CrowdInstance->GetLocation();

	//uncomment the following two lines to have Evade only consider pursuers 
	//within a 'threat range'
	const FLOAT ThreatRange = 100.0;
	if (ToPursuer.SizeSquared() > ThreatRange * ThreatRange) return FVector::ZeroVector;

	//the lookahead time is propotional to the distance between the pursuer
	//and the pursuer; and is inversely proportional to the sum of the
	//agents' velocities
	FLOAT LookAheadTime = ToPursuer.Size() / 
		(CrowdInstance->GetMaxSpeed() + pursuer->GetSpeed());

	//now flee away from predicted future position of the pursuer
	return Flee(pursuer->GetLocation() + pursuer->GetVelocity() * LookAheadTime);
}


//--------------------------- Wander -------------------------------------
//
//  This behavior makes the agent wander about randomly
//------------------------------------------------------------------------
FVector UMMOSteeringBehavior::Wander()
{ 
	//this behavior is dependent on the update rate, so this line must
	//be included when using time independent framerate.
	FLOAT JitterThisTimeSlice = WanderJitter * CrowdInstance->GetTimeElapsed();

	//first, add a small random vector to the target's position
	WanderTarget += FVector(RandomClamped() * JitterThisTimeSlice,
		RandomClamped() * JitterThisTimeSlice,
		RandomClamped() * JitterThisTimeSlice);

	//reproject this new vector back on to a unit circle
	WanderTarget.Normalize();

	//increase the length of the vector to the same as the radius
	//of the wander circle
	WanderTarget *= WanderRadius;

	//move the target into a position WanderDist in front of the agent
	FVector target = WanderTarget + FVector(WanderDistance, 0, 0);

	//project the target into world space
	FVector Target = PointToWorldSpace(target,
		CrowdInstance->Heading(),
		CrowdInstance->Side(), 
		CrowdInstance->GetLocation());

	//and steer towards it
	return Target - CrowdInstance->GetLocation(); 
}


//---------------------- ObstacleAvoidance -------------------------------
//
//  Given a vector of CObstacles, this method returns a steering force
//  that will prevent the agent colliding with the closest obstacle
//------------------------------------------------------------------------
#if 0
FVector UMMOSteeringBehavior::ObstacleAvoidance(const TArray<class UMMOCrowdInstance*>& obstacles)
{
	//the detection box length is proportional to the agent's velocity
	DBoxLength = Prm_MinDetectionBoxLength + 
		(CrowdInstance->GetSpeed()/CrowdInstance->GetMaxSpeed()) *
		Prm_MinDetectionBoxLength;

	//tag all obstacles within range of the box for processing
	CrowdInstance->GetOwner()->TagObstaclesWithinViewRange(CrowdInstance, DBoxLength);

	//this will keep track of the closest intersecting obstacle (CIB)
	UMMOCrowdInstance* ClosestIntersectingObstacle = NULL;

	//this will be used to track the distance to the CIB
	FLOAT DistToClosestIP = MaxDouble;

	//this will record the transformed local coordinates of the CIB
	FVector LocalPosOfClosestObstacle;

	TArray<class UMMOCrowdInstance*>::const_iterator curOb = obstacles.begin();

	while(curOb != obstacles.end())
	{
		//if the obstacle has been tagged within range proceed
		if ((*curOb)->IsTagged())
		{
			//calculate this obstacle's position in local space
			FVector LocalPos = PointToLocalSpace((*curOb)->GetLocation(),
				CrowdInstance->Heading(),
				CrowdInstance->Side(),
				CrowdInstance->GetLocation());

			//if the local position has a negative x value then it must lay
			//behind the agent. (in which case it can be ignored)
			if (LocalPos.x >= 0)
			{
				//if the distance from the x axis to the object's position is less
				//than its radius + half the width of the detection box then there
				//is a potential intersection.
				FLOAT ExpandedRadius = (*curOb)->GetBRadius() + CrowdInstance->GetBRadius();

				if (fabs(LocalPos.y) < ExpandedRadius)
				{
					//now to do a line/circle intersection test. The center of the 
					//circle is represented by (cX, cY). The intersection points are 
					//given by the formula x = cX +/-sqrt(r^2-cY^2) for y=0. 
					//We only need to look at the smallest positive value of x because
					//that will be the closest point of intersection.
					FLOAT cX = LocalPos.x;
					FLOAT cY = LocalPos.y;

					//we only need to calculate the sqrt part of the above equation once
					FLOAT SqrtPart = sqrt(ExpandedRadius*ExpandedRadius - cY*cY);

					FLOAT ip = cX - SqrtPart;

					if (ip <= 0.0)
					{
						ip = cX + SqrtPart;
					}

					//test to see if this is the closest so far. If it is keep a
					//record of the obstacle and its local coordinates
					if (ip < DistToClosestIP)
					{
						DistToClosestIP = ip;

						ClosestIntersectingObstacle = *curOb;

						LocalPosOfClosestObstacle = LocalPos;
					}         
				}
			}
		}

		++curOb;
	}

	//if we have found an intersecting obstacle, calculate a steering 
	//force away from it
	FVector SteeringForce;

	if (ClosestIntersectingObstacle)
	{
		//the closer the agent is to an object, the stronger the 
		//steering force should be
		FLOAT multiplier = 1.0 + (DBoxLength - LocalPosOfClosestObstacle.x) /
			DBoxLength;

		//calculate the lateral force
		SteeringForce.y = (ClosestIntersectingObstacle->GetBRadius()-
			LocalPosOfClosestObstacle.y)  * multiplier;   

		//apply a braking force proportional to the obstacles distance from
		//the UMMOCrowdInstance. 
		const FLOAT BrakingWeight = 0.2;

		SteeringForce.x = (ClosestIntersectingObstacle->GetBRadius() - 
			LocalPosOfClosestObstacle.x) * 
			BrakingWeight;
	}

	//finally, convert the steering vector from local to world space
	return VectorToWorldSpace(SteeringForce,
		CrowdInstance->Heading(),
		CrowdInstance->Side());
}
#endif

//--------------------------- WallAvoidance --------------------------------
//
//  This returns a steering force that will keep the agent away from any
//  walls it may encounter
//------------------------------------------------------------------------
#if 0
FVector UMMOSteeringBehavior::WallAvoidance(const std::vector<Wall2D>& walls)
{
	//the feelers are contained in a std::vector, Feelers
	CreateFeelers();

	FLOAT DistToThisIP    = 0.0;
	FLOAT DistToClosestIP = MaxDouble;

	//this will hold an index into the vector of walls
	int ClosestWall = -1;

	FVector SteeringForce,
		point,         //used for storing temporary info
		ClosestPoint;  //holds the closest intersection point

	//examine each feeler in turn
	for (INT flr=0; flr<Feelers.Num(); ++flr)
	{
		//run through each wall checking for any intersection points
		for (INT w=0; w<walls.Num(); ++w)
		{
			if (LineIntersection2D(CrowdInstance->GetLocation(),
				Feelers[flr],
				walls[w].From(),
				walls[w].To(),
				DistToThisIP,
				point))
			{
				//is this the closest found so far? If so keep a record
				if (DistToThisIP < DistToClosestIP)
				{
					DistToClosestIP = DistToThisIP;

					ClosestWall = w;

					ClosestPoint = point;
				}
			}
		}//next wall


		//if an intersection point has been detected, calculate a force  
		//that will direct the agent away
		if (ClosestWall >=0)
		{
			//calculate by what distance the projected position of the agent
			//will overshoot the wall
			FVector OverShoot = Feelers[flr] - ClosestPoint;

			//create a force in the direction of the wall normal, with a 
			//magnitude of the overshoot
			SteeringForce = walls[ClosestWall].Normal() * OverShoot.Size();
		}

	}//next feeler

	return SteeringForce;
}
#endif
//------------------------------- CreateFeelers --------------------------
//
//  Creates the antenna utilized by WallAvoidance
//------------------------------------------------------------------------
// void UMMOSteeringBehavior::CreateFeelers()
// {
//   //feeler pointing straight in front
//   Feelers[0] = CrowdInstance->GetLocation() + WallDetectionFeelerLength * CrowdInstance->Heading();
// 
//   //feeler to left
//   FVector temp = CrowdInstance->Heading();
//   Vec2DRotateAroundOrigin(temp, HALF_PI * 3.5f);
//   Feelers[1] = CrowdInstance->GetLocation() + WallDetectionFeelerLength/2.0f * temp;
// 
//   //feeler to right
//   temp = CrowdInstance->Heading();
//   Vec2DRotateAroundOrigin(temp, HALF_PI * 0.5f);
//   Feelers[2] = CrowdInstance->GetLocation() + WallDetectionFeelerLength/2.0f * temp;
// }


//---------------------------- Separation --------------------------------
//
// this calculates a force repelling from the other neighbors
//------------------------------------------------------------------------
FVector UMMOSteeringBehavior::Separation(const TArray<UMMOCrowdInstance*> &neighbors)
{  
	FVector SteeringForce = FVector::ZeroVector;;

	for (INT a=0; a<neighbors.Num(); ++a)
	{
		//make sure this agent isn't included in the calculations and that
		//the agent being examined is close enough. ***also make sure it doesn't
		//include the evade target ***
		if(neighbors(a) && (neighbors(a) != CrowdInstance) && neighbors(a)->IsTagged() &&
			(neighbors(a) != TargetAgent1))
		{
			FVector ToAgent = CrowdInstance->GetLocation() - neighbors(a)->GetLocation();

			//scale the force inversely proportional to the agents distance  
			//from its neighbor.
			SteeringForce += (ToAgent).SafeNormal()/ToAgent.Size();
		}
	}

	return SteeringForce;
}


//---------------------------- Alignment ---------------------------------
//
//  returns a force that attempts to align this agents heading with that
//  of its neighbors
//------------------------------------------------------------------------
FVector UMMOSteeringBehavior::Alignment(const TArray<UMMOCrowdInstance*>& neighbors)
{
	//used to record the average heading of the neighbors
	FVector AverageHeading = FVector::ZeroVector;

	//used to count the number of MMOCrowdInstances in the neighborhood
	int    NeighborCount = 0;

	//iterate through all the tagged MMOCrowdInstances and sum their heading vectors  
	for (INT a=0; a<neighbors.Num(); ++a)
	{
		//make sure *this* agent isn't included in the calculations and that
		//the agent being examined  is close enough ***also make sure it doesn't
		//include any evade target ***
		if(neighbors(a) && (neighbors(a) != CrowdInstance) && neighbors(a)->IsTagged() &&
			(neighbors(a) != TargetAgent1))
		{
			AverageHeading += neighbors(a)->Heading();

			++NeighborCount;
		}
	}

	//if the neighborhood contained one or more MMOCrowdInstances, average their
	//heading vectors.
	if (NeighborCount > 0)
	{
		AverageHeading /= (FLOAT)NeighborCount;

		AverageHeading -= CrowdInstance->Heading();
	}

	return AverageHeading;
}

//-------------------------------- Cohesion ------------------------------
//
//  returns a steering force that attempts to move the agent towards the
//  center of mass of the agents in its immediate area
//------------------------------------------------------------------------
FVector UMMOSteeringBehavior::Cohesion(const TArray<UMMOCrowdInstance*> &neighbors)
{
	//first find the center of mass of all the agents
	FVector CenterOfMass = FVector::ZeroVector, SteeringForce = FVector::ZeroVector;

	int NeighborCount = 0;

	//iterate through the neighbors and sum up all the position vectors
	for (INT a=0; a<neighbors.Num(); ++a)
	{
		//make sure *this* agent isn't included in the calculations and that
		//the agent being examined is close enough ***also make sure it doesn't
		//include the evade target ***
		if(neighbors(a) && (neighbors(a) != CrowdInstance) && neighbors(a)->IsTagged() &&
			(neighbors(a) != TargetAgent1))
		{
			CenterOfMass += neighbors(a)->GetLocation();

			++NeighborCount;
		}
	}

	if (NeighborCount > 0)
	{
		//the center of mass is the average of the sum of positions
		CenterOfMass /= (FLOAT)NeighborCount;

		//now seek towards that position
		SteeringForce = Seek(CenterOfMass);
	}

	//the magnitude of cohesion is usually much larger than separation or
	//allignment so it usually helps to normalize it.
	return (SteeringForce).SafeNormal();
}


/* NOTE: the next three behaviors are the same as the above three, except
that they use a cell-space partition to find the neighbors
*/


//---------------------------- Separation --------------------------------
//
// this calculates a force repelling from the other neighbors
//
//  USES SPACIAL PARTITIONING
//------------------------------------------------------------------------
FVector UMMOSteeringBehavior::SeparationPlus(const TArray<UMMOCrowdInstance*> &neighbors)
{  
	FVector SteeringForce = FVector::ZeroVector;

	////iterate through the neighbors and sum up all the position vectors
	//for (UMMOCrowdInstance* pV = CrowdInstance->GetOwner()->CellSpace()->begin();
	//                       !CrowdInstance->GetOwner()->CellSpace()->end();     
	//                     pV = CrowdInstance->GetOwner()->CellSpace()->next())
	//{    
	//  //make sure this agent isn't included in the calculations and that
	//  //the agent being examined is close enough
	//  if(pV != CrowdInstance)
	//  {
	//    FVector ToAgent = CrowdInstance->GetLocation() - pV->GetLocation();

	//    //scale the force inversely proportional to the agents distance  
	//    //from its neighbor.
	//    SteeringForce += (ToAgent).SafeNormal()/ToAgent.Size();
	//  }

	//}

	return SteeringForce;
}
//---------------------------- Alignment ---------------------------------
//
//  returns a force that attempts to align this agents heading with that
//  of its neighbors
//
//  USES SPACIAL PARTITIONING
//------------------------------------------------------------------------
FVector UMMOSteeringBehavior::AlignmentPlus(const TArray<UMMOCrowdInstance*> &neighbors)
{
	//This will record the average heading of the neighbors
	FVector AverageHeading = FVector::ZeroVector;

	//This count the number of MMOCrowdInstances in the neighborhood
	FLOAT    NeighborCount = 0.0;
#if 0
	//iterate through the neighbors and sum up all the position vectors
	for (MovingEntity* pV = CrowdInstance->GetOwner()->CellSpace()->begin();
		!CrowdInstance->GetOwner()->CellSpace()->end();     
		pV = CrowdInstance->GetOwner()->CellSpace()->next())
	{
		//make sure *this* agent isn't included in the calculations and that
		//the agent being examined  is close enough
		if(pV != CrowdInstance)
		{
			AverageHeading += pV->Heading();

			++NeighborCount;
		}

	}

	//if the neighborhood contained one or more MMOCrowdInstances, average their
	//heading vectors.
	if (NeighborCount > 0.0)
	{
		AverageHeading /= NeighborCount;

		AverageHeading -= CrowdInstance->Heading();
	}
#endif
	return AverageHeading;
}


//-------------------------------- Cohesion ------------------------------
//
//  returns a steering force that attempts to move the agent towards the
//  center of mass of the agents in its immediate area
//
//  USES SPACIAL PARTITIONING
//------------------------------------------------------------------------
FVector UMMOSteeringBehavior::CohesionPlus(const TArray<UMMOCrowdInstance*> &neighbors)
{
	//first find the center of mass of all the agents
	FVector CenterOfMass = FVector::ZeroVector, SteeringForce = FVector::ZeroVector;

	int NeighborCount = 0;
#if 0
	//iterate through the neighbors and sum up all the position vectors
	for (UMMOCrowdInstance* pV = CrowdInstance->GetOwner()->CellSpace()->begin();
		!CrowdInstance->GetOwner()->CellSpace()->end();     
		pV = CrowdInstance->GetOwner()->CellSpace()->next())
	{
		//make sure *this* agent isn't included in the calculations and that
		//the agent being examined is close enough
		if(pV != CrowdInstance)
		{
			CenterOfMass += pV->GetLocation();

			++NeighborCount;
		}
	}

	if (NeighborCount > 0)
	{
		//the center of mass is the average of the sum of positions
		CenterOfMass /= (FLOAT)NeighborCount;

		//now seek towards that position
		SteeringForce = Seek(CenterOfMass);
	}
#endif
	//the magnitude of cohesion is usually much larger than separation or
	//allignment so it usually helps to normalize it.
	return SteeringForce.SafeNormal();
}


//--------------------------- Interpose ----------------------------------
//
//  Given two agents, this method returns a force that attempts to 
//  position the UMMOCrowdInstance between them
//------------------------------------------------------------------------
FVector UMMOSteeringBehavior::Interpose(const UMMOCrowdInstance* AgentA,
	const UMMOCrowdInstance* AgentB)
{
	if(!(AgentA && AgentB))
	{
		return FVector::ZeroVector;
	}

	//first we need to figure out where the two agents are going to be at 
	//time T in the future. This is approximated by determining the time
	//taken to reach the mid way point at the current time at at max speed.
	FVector MidPoint = (AgentA->GetLocation() + AgentB->GetLocation()) / 2.0;

	FLOAT TimeToReachMidPoint = (CrowdInstance->GetLocation(), MidPoint).Size() /
		CrowdInstance->GetMaxSpeed();

	//now we have T, we assume that agent A and agent B will continue on a
	//straight trajectory and extrapolate to get their future positions
	FVector APos = AgentA->GetLocation() + AgentA->GetVelocity() * TimeToReachMidPoint;
	FVector BPos = AgentB->GetLocation() + AgentB->GetVelocity() * TimeToReachMidPoint;

	//calculate the mid point of these predicted positions
	MidPoint = (APos + BPos) / 2.0;

	//then steer to Arrive at it
	return Arrive(MidPoint, ED_Fast);
}

//--------------------------- Hide ---------------------------------------
//
//------------------------------------------------------------------------
FVector UMMOSteeringBehavior::Hide(const UMMOCrowdInstance*           hunter,
	const TArray<UMMOCrowdInstance*>& obstacles)
{
#if 1
	return FVector::ZeroVector;
#else
	FLOAT    DistToClosest = MaxDouble;
	FVector BestHidingSpot;

	TArray<class UMMOCrowdInstance*>::const_iterator curOb = obstacles.begin();
	TArray<class UMMOCrowdInstance*>::const_iterator closest;

	while(curOb != obstacles.end())
	{
		//calculate the position of the hiding spot for this obstacle
		FVector HidingSpot = GetHidingPosition((*curOb)->GetLocation(),
			(*curOb)->GetBRadius(),
			hunter->GetLocation());

		//work in distance-squared space to find the closest hiding
		//spot to the agent
		FLOAT dist = (HidingSpot, CrowdInstance->GetLocation()).DistanceSquared();

		if (dist < DistToClosest)
		{
			DistToClosest = dist;

			BestHidingSpot = HidingSpot;

			closest = curOb;
		}  

		++curOb;

	}//end while

	//if no suitable obstacles found then Evade the hunter
	if (DistToClosest == MaxFloat)
	{
		return Evade(hunter);
	}

	//else use Arrive on the hiding spot
	return Arrive(BestHidingSpot, fast);
#endif
}

//------------------------- GetHidingPosition ----------------------------
//
//  Given the position of a hunter, and the position and radius of
//  an obstacle, this method calculates a position DistanceFromBoundary 
//  away from its bounding radius and directly opposite the hunter
//------------------------------------------------------------------------
FVector UMMOSteeringBehavior::GetHidingPosition(const FVector& posOb,
	const FLOAT     radiusOb,
	const FVector& posHunter)
{
	//calculate how far away the agent is to be from the chosen obstacle's
	//bounding radius
	const FLOAT DistanceFromBoundary = 30.0;
	FLOAT       DistAway    = radiusOb + DistanceFromBoundary;

	//calculate the heading toward the object from the hunter
	FVector ToOb = (posOb - posHunter).SafeNormal();

	//scale it to size and add to the obstacles position to get
	//the hiding spot.
	return (ToOb * DistAway) + posOb;
}


//------------------------------- FollowPath -----------------------------
//
//  Given a series of FVectors, this method produces a force that will
//  move the agent along the waypoints in order. The agent uses the
// 'Seek' behavior to move to the next waypoint - unless it is the last
//  waypoint, in which case it 'Arrives'
//------------------------------------------------------------------------
FVector UMMOSteeringBehavior::FollowPath()
{ 
	if(!TheFollowPath)
	{
		return FVector::ZeroVector;
	}

	//move to next target if close enough to current target (working in
	//distance squared space)
	FLOAT dist = CurrentTargetPathNode->Location.DistanceSquared(CrowdInstance->GetLocation());
	if(dist < WaypointSeekDistSq)
	{
		if(CurrentTargetPathNode->Connections.Num() > 0)
		{
			CurrentTargetPathNode = CurrentTargetPathNode->Connections(0).ConnectTo;
		}
		else
		{
			CurrentTargetPathNode = TheFollowPath;
		}
	}

	//if (!Path->Finished())
	//{
		return Seek(CurrentTargetPathNode->Location);
	//}

	//else
	//{
	//	return Arrive(CurrentTargetPathNode->Location, ED_Normal);
	//}
}

//------------------------- Offset Pursuit -------------------------------
//
//  Produces a steering force that keeps a UMMOCrowdInstance at a specified offset
//  from a leader UMMOCrowdInstance
//------------------------------------------------------------------------
FVector UMMOSteeringBehavior::OffsetPursuit(const UMMOCrowdInstance*  leader,
	const FVector& offset)
{
	if(!leader)
	{
		return FVector::ZeroVector;
	}

	//calculate the offset's position in world space
	FVector WorldOffsetPos = PointToWorldSpace(offset,
		leader->Heading(),
		leader->Side(),
		leader->GetLocation());

	FVector ToOffset = WorldOffsetPos - CrowdInstance->GetLocation();

	//the lookahead time is propotional to the distance between the leader
	//and the pursuer; and is inversely proportional to the sum of both
	//agent's velocities
	FLOAT LookAheadTime = ToOffset.Size() / 
		(CrowdInstance->GetMaxSpeed() + leader->GetSpeed());

	//now Arrive at the predicted future position of the offset
	return Arrive(WorldOffsetPos + leader->GetVelocity() * LookAheadTime, ED_Fast);
}

//------------------------------------------------------------------------

void UMMOSteeringBehavior::NativePostBeginPlay()
{
	WeightSeparation *= CrowdInstance->Owner->SteeringForceTweaker;
	WeightAlignment *= CrowdInstance->Owner->SteeringForceTweaker;
	WeightCohesion *= CrowdInstance->Owner->SteeringForceTweaker;
	WeightObstacleAvoidance *= CrowdInstance->Owner->SteeringForceTweaker;
	WeightWallAvoidance *= CrowdInstance->Owner->SteeringForceTweaker;
	WeightWander *= CrowdInstance->Owner->SteeringForceTweaker;
	WeightSeek *= CrowdInstance->Owner->SteeringForceTweaker;
	WeightSeek *= CrowdInstance->Owner->SteeringForceTweaker;
	WeightFlee *= CrowdInstance->Owner->SteeringForceTweaker;
	WeightArrive *= CrowdInstance->Owner->SteeringForceTweaker;
	WeightPursuit *= CrowdInstance->Owner->SteeringForceTweaker;
	WeightOffsetPursuit *= CrowdInstance->Owner->SteeringForceTweaker;
	WeightInterpose *= CrowdInstance->Owner->SteeringForceTweaker;
	WeightHide *= CrowdInstance->Owner->SteeringForceTweaker;
	WeightEvade *= CrowdInstance->Owner->SteeringForceTweaker;
	WeightFollowPath *= CrowdInstance->Owner->SteeringForceTweaker;
}