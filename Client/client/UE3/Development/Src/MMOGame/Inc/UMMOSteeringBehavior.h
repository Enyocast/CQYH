#ifndef _UMMOSTEERINGBEHAVIOR_H_
#define _UMMOSTEERINGBEHAVIOR_H_

enum behavior_type
{
	none               = 0x00000,
	seek               = 0x00002,
	flee               = 0x00004,
	arrive             = 0x00008,
	wander             = 0x00010,
	cohesion           = 0x00020,
	separation         = 0x00040,
	allignment         = 0x00080,
	obstacle_avoidance = 0x00100,
	wall_avoidance     = 0x00200,
	follow_path        = 0x00400,
	pursuit            = 0x00800,
	evade              = 0x01000,
	interpose          = 0x02000,
	hide               = 0x04000,
	flock              = 0x08000,
	offset_pursuit     = 0x10000,
};

  void Init(class UMMOCrowdInstance* inst);

  //this function tests if a specific bit of Flags is set
  bool      On(behavior_type bt){return (Flags & bt) == bt;}

  bool      AccumulateForce(FVector &sf, FVector ForceToAdd);

  //creates the antenna utilized by the wall avoidance behavior
  void      CreateFeelers();



   /* .......................................................

                    BEGIN BEHAVIOR DECLARATIONS

      .......................................................*/


  //this behavior moves the agent towards a target position
  FVector Seek(const FVector& TargetPos);

  //this behavior returns a vector that moves the agent away
  //from a target position
  FVector Flee(const FVector& TargetPos);

  //this behavior is similar to seek but it attempts to arrive 
  //at the target position with a zero velocity
  FVector Arrive(const FVector&     TargetPos,
                  BYTE deceleration);

  //this behavior predicts where an agent will be in time T and seeks
  //towards that point to intercept it.
  FVector Pursuit(const UMMOCrowdInstance* agent);

  //this behavior maintains a position, in the direction of offset
  //from the target UMMOCrowdInstance
  FVector OffsetPursuit(const UMMOCrowdInstance* agent, const FVector& offset);

  //this behavior attempts to evade a pursuer
  FVector Evade(const UMMOCrowdInstance* agent);

  //this behavior makes the agent wander about randomly
  FVector Wander();

  //this returns a steering force which will attempt to keep the agent 
  //away from any obstacles it may encounter
  //FVector ObstacleAvoidance(const TArray<class UMMOCrowdInstance*>& obstacles);

  //this returns a steering force which will keep the agent away from any
  //walls it may encounter
 // FVector WallAvoidance(const std::vector<Wall2D> &walls);

  
  //given a series of FVectors, this method produces a force that will
  //move the agent along the waypoints in order
  FVector FollowPath();

  //this results in a steering force that attempts to steer the UMMOCrowdInstance
  //to the center of the vector connecting two moving agents.
  FVector Interpose(const UMMOCrowdInstance* MMOCrowdInstanceA, const UMMOCrowdInstance* MMOCrowdInstanceB);

  //given another agent position to hide from and a list of MMOCrowdInstances this
  //method attempts to put an obstacle between itself and its opponent
  FVector Hide(const UMMOCrowdInstance* hunter, const TArray<class UMMOCrowdInstance*>& obstacles);


  // -- Group Behaviors -- //

  FVector Cohesion(const TArray<class UMMOCrowdInstance*> &agents);
  
  FVector Separation(const TArray<class UMMOCrowdInstance*> &agents);

  FVector Alignment(const TArray<class UMMOCrowdInstance*> &agents);

  //the following three are the same as above but they use cell-space
  //partitioning to find the neighbors
  FVector CohesionPlus(const TArray<class UMMOCrowdInstance*> &agents);
  FVector SeparationPlus(const TArray<class UMMOCrowdInstance*> &agents);
  FVector AlignmentPlus(const TArray<class UMMOCrowdInstance*> &agents);

    /* .......................................................

                       END BEHAVIOR DECLARATIONS

      .......................................................*/

  //calculates and sums the steering forces from any active behaviors
  //FVector CalculateWeightedSum();
  FVector CalculatePrioritized();
  //FVector CalculateDithered();

  //helper method for Hide. Returns a position located on the other
  //side of an obstacle to the pursuer
  FVector GetHidingPosition(const FVector& posOb,
                              const FLOAT     radiusOb,
                              const FVector& posHunter);



  
  
public:

  //calculates and sums the steering forces from any active behaviors
  FVector Calculate();

  //calculates the component of the steering force that is parallel
  //with the UMMOCrowdInstance heading
  FLOAT    ForwardComponent();

  //calculates the component of the steering force that is perpendicuar
  //with the UMMOCrowdInstance heading
  FLOAT    SideComponent();



  //renders visual aids and info for seeing how each behavior is
  //calculated
  //void      RenderAids();

  void      SetTarget(const FVector& t){Target = t;}

  void      SetTargetAgent1(UMMOCrowdInstance* Agent){TargetAgent1 = Agent;}
  void      SetTargetAgent2(UMMOCrowdInstance* Agent){TargetAgent2 = Agent;}

  void      SetOffset(const FVector& offset){Offset = offset;}
  const FVector&  GetOffset()const{return Offset;}

//   void      SetPath(std::list<FVector> new_path){Path->Set(new_path);}
//   void      CreateRandomPath(int num_waypoints, int mx, int my, int cx, int cy)const
//             {Path->CreateRandomPath(num_waypoints, mx, my, cx, cy);}

  const FVector& Force()const{return SteeringForce;}

  void      ToggleSpacePartitioningOnOff(){CellSpaceOn = !CellSpaceOn;}
  bool      isSpacePartitioningOn()const{return CellSpaceOn;}

  void      SetSummingMethod(ESummingMethod sm){SummingMethod = sm;}


  void FleeOn(){Flags |= flee;}
  void SeekOn(){Flags |= seek;}
  void ArriveOn(){Flags |= arrive;}
  void WanderOn(){Flags |= wander;}
  void PursuitOn(UMMOCrowdInstance* v){Flags |= pursuit; TargetAgent1 = v;}
  void EvadeOn(UMMOCrowdInstance* v){Flags |= evade; TargetAgent1 = v;}
  void CohesionOn(){Flags |= cohesion;}
  void SeparationOn(){Flags |= separation;}
  void AlignmentOn(){Flags |= allignment;}
  void ObstacleAvoidanceOn(){Flags |= obstacle_avoidance;}
  void WallAvoidanceOn(){Flags |= wall_avoidance;}
  void FollowPathOn(){Flags |= follow_path; CurrentTargetPathNode = TheFollowPath; }
  void InterposeOn(UMMOCrowdInstance* v1, UMMOCrowdInstance* v2){Flags |= interpose; TargetAgent1 = v1; TargetAgent2 = v2;}
  void HideOn(UMMOCrowdInstance* v){Flags |= hide; TargetAgent1 = v;}
  void OffsetPursuitOn(UMMOCrowdInstance* v1, const FVector& offset){Flags |= offset_pursuit; Offset = offset; TargetAgent1 = v1;}
  void FlockingOn(){CohesionOn(); AlignmentOn(); SeparationOn(); WanderOn();}

  void FleeOff()  {if(On(flee))   Flags ^=flee;}
  void SeekOff()  {if(On(seek))   Flags ^=seek;}
  void ArriveOff(){if(On(arrive)) Flags ^=arrive;}
  void WanderOff(){if(On(wander)) Flags ^=wander;}
  void PursuitOff(){if(On(pursuit)) Flags ^=pursuit;}
  void EvadeOff(){if(On(evade)) Flags ^=evade;}
  void CohesionOff(){if(On(cohesion)) Flags ^=cohesion;}
  void SeparationOff(){if(On(separation)) Flags ^=separation;}
  void AlignmentOff(){if(On(allignment)) Flags ^=allignment;}
  void ObstacleAvoidanceOff(){if(On(obstacle_avoidance)) Flags ^=obstacle_avoidance;}
  void WallAvoidanceOff(){if(On(wall_avoidance)) Flags ^=wall_avoidance;}
  void FollowPathOff(){if(On(follow_path)) Flags ^=follow_path;}
  void InterposeOff(){if(On(interpose)) Flags ^=interpose;}
  void HideOff(){if(On(hide)) Flags ^=hide;}
  void OffsetPursuitOff(){if(On(offset_pursuit)) Flags ^=offset_pursuit;}
  void FlockingOff(){CohesionOff(); AlignmentOff(); SeparationOff(); WanderOff();}

  bool isFleeOn(){return On(flee);}
  bool isSeekOn(){return On(seek);}
  bool isArriveOn(){return On(arrive);}
  bool isWanderOn(){return On(wander);}
  bool isPursuitOn(){return On(pursuit);}
  bool isEvadeOn(){return On(evade);}
  bool isCohesionOn(){return On(cohesion);}
  bool isSeparationOn(){return On(separation);}
  bool isAlignmentOn(){return On(allignment);}
  bool isObstacleAvoidanceOn(){return On(obstacle_avoidance);}
  bool isWallAvoidanceOn(){return On(wall_avoidance);}
  bool isFollowPathOn(){return On(follow_path);}
  bool isInterposeOn(){return On(interpose);}
  bool isHideOn(){return On(hide);}
  bool isOffsetPursuitOn(){return On(offset_pursuit);}

  FLOAT GetDBoxLength()const{return DBoxLength;}
  //const std::vector<FVector>& GetFeelers()const{return Feelers;}
  
  FLOAT GetWanderJitter()const{return WanderJitter;}
  FLOAT GetWanderDistance()const{return WanderDistance;}
  FLOAT GetWanderRadius()const{return WanderRadius;}

  FLOAT GetSeparationWeight()const{return WeightSeparation;}
  FLOAT GetAlignmentWeight()const{return WeightAlignment;}
  FLOAT GetCohesionWeight()const{return WeightCohesion;}

#endif