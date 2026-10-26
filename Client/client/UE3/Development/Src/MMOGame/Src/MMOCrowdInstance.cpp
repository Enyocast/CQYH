#include "stdafx.h"
#include "MMOCrowd.h"

IMPLEMENT_CLASS(UMMOCrowdInstance);
//------------------------------------------------------------------------
// MMOCrowdInstance
//------------------------------------------------------------------------
void UMMOCrowdInstance::NativePostBeginPlay()
{
	//MaxForce *= Owner->SteeringForceTweaker;
}
//------------------------------------------------------------------------
FMatrix UMMOCrowdInstance::GetTransform() const
{
	FMatrix InstanceTransform = FScaleMatrix(DrawScale3D);
	InstanceTransform *= FRotationMatrix(GetRotation());
	InstanceTransform *= FTranslationMatrix(Location);
	check( !InstanceTransform.ContainsNaN() );
	return InstanceTransform;
}
//------------------------------------------------------------------------
void UMMOCrowdInstance::SetHeading( const FVector& new_heading )
{
	check( (new_heading.SizeSquared() - 1.0) < 0.00001);

	Direction = new_heading;

	//the side vector must always be perpendicular to the heading
	SideVector = Direction ^ FVector(0, 0, 1);
}
//------------------------------------------------------------------------
void UMMOCrowdInstance::WrapAround(FVector& pos, FLOAT MaxX, FLOAT MaxY, FLOAT MaxZ)
{
	if (pos.X > MaxX + Owner->Location.X) {pos.X = Owner->Location.X;}

	if (pos.X < Owner->Location.X)    {pos.X = (double)MaxX + Owner->Location.X;}

	if (pos.Y < Owner->Location.Y)    {pos.Y = (double)MaxY + Owner->Location.Y;}

	if (pos.Y > Owner->Location.Y + MaxY) {pos.Y = Owner->Location.Y;}

	if (pos.Z < Owner->Location.Z)    {pos.Z = (double)MaxZ + Owner->Location.Z;}

	if (pos.Z > Owner->Location.Z + MaxZ) {pos.Z = Owner->Location.Z;}
}

void UMMOCrowdInstance::Update(FLOAT time_elapsed)
{    
	//update the time elapsed
	TimeElapsed = time_elapsed;

	//do nothing if behavior not set
	if( !SteeringBehavior )
		return;

	//keep a record of its old position so we can update its cell later
	//in this method
	FVector OldPos = GetLocation();


	//calculate the combined force from each steering behavior in the 
	//vehicle's list
	FVector SteeringForce = SteeringBehavior->Calculate();

	//Acceleration = Force/Mass
	FVector acceleration = SteeringForce / Mass;

	//update velocity
	Velocity += acceleration * time_elapsed; 

	//make sure vehicle does not exceed maximum velocity
	if(Velocity.Size() > MaxSpeed)
	{
		Velocity = Velocity.SafeNormal() * MaxSpeed;
	}

	//update the position
	Location += Velocity * time_elapsed;

	//update the heading if the vehicle has a non zero velocity
	if (Velocity.SizeSquared() > 0.00000001)
	{    
		Direction = Velocity.SafeNormal();

		SideVector = Direction ^ FVector(0, 0, 1);
	}

	//EnforceNonPenetrationConstraint(this, World()->Agents());

	//treat the screen as a toroid
	//WrapAround(Location, Owner->WrapBoundingExtent.X, Owner->WrapBoundingExtent.Y, Owner->WrapBoundingExtent.Z);

	//update the vehicle's current cell if space partitioning is turned on
	if (SteeringBehavior->isSpacePartitioningOn())
	{
		//World()->CellSpace()->UpdateEntity(this, OldPos);
	}

// 	if (isSmoothingOn())
// 	{
// 		SmoothedHeading = HeadingSmoother->Update(Heading());
// 	}
}