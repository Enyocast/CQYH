#ifndef _UMMOCROWDINSTANCE_H_
#define _UMMOCROWDINSTANCE_H_

void NativePostBeginPlay();

virtual void Update(FLOAT deltaTime);
const FVector& GetLocation() const { return Location; }
const FVector& GetDirection() const { return Direction; }
const FVector& GetScale() const { return DrawScale3D; }

void SetLocation(const FVector& location) { Location = location; }
void SetDirection(const FVector& dir );
void SetScale(const FVector& s) { DrawScale3D = s; }

FRotator GetRotation() const { return Direction.Rotation(); }
FMatrix GetTransform() const;

AMMOCrowdSystem* GetOwner() { return Owner; }

const FVector&  Heading()const{return Direction;}	
void SetHeading(const FVector& new_heading);

const FVector& Side() const { return SideVector; }

bool IsTagged() const { return IsTag; }
void Tag(){ IsTag = true;}	
void UnTag(){ IsTag = false;}

const FVector& GetVelocity()const{return Velocity;}
void SetVelocity(const FVector& NewVel){Velocity = NewVel;}

FLOAT GetMass()const{return Mass;}

FLOAT GetMaxSpeed()const{return MaxSpeed;}                       
void SetMaxSpeed(FLOAT new_speed){MaxSpeed = new_speed;}

FLOAT GetMaxForce()const{return MaxForce;}
void SetMaxForce(FLOAT mf){MaxForce = mf;}

bool IsSpeedMaxedOut()const{return MaxSpeed*MaxSpeed >= Velocity.SizeSquared();}
FLOAT GetSpeed()const{return Velocity.Size();}
FLOAT GetSpeedSq()const{return Velocity.SizeSquared();}

bool RotateHeadingToFacePosition(const FVector& target);

FLOAT GetMaxTurnRate()const{ return MaxTurnRate; }
void SetMaxTurnRate(FLOAT val){ MaxTurnRate = val; }

FLOAT        GetBRadius()const{return BoundingRadius;}
void         SetBRadius(FLOAT r){BoundingRadius = r;}

FLOAT GetTimeElapsed() const { return TimeElapsed; }

void WrapAround(FVector& pos, FLOAT MaxX, FLOAT MaxY, FLOAT MaxZ);

//protected:
//
//	AMMOCrowdSystem* _Owner;
//	SteeringBehavior* _SteeringBehavior;
//
//	FVector _Location;
//	FVector _Direction;
//	FVector _DrawScale3D;
//
//	FVector    Velocity;
//
//	//a vector perpendicular to the heading vector
//	FVector    Side; 
//
//	FLOAT       Mass;
//
//	//the maximum speed this entity may travel at.
//	FLOAT       MaxSpeed;
//
//	//the maximum force this entity can produce to power itself 
//	//(think rockets and thrust)
//	FLOAT        MaxForce;
//
//	//the maximum rate (radians per second)this vehicle can rotate         
//	FLOAT       MaxTurnRate;
//
//	bool m_bTag;
//
//	FLOAT    BoundingRadius;


#endif