/**
 *  Copyright 1998-2013 Epic Games, Inc. All Rights Reserved.
 */
class DynamicNavMeshObstacle extends NavMeshObstacle
	native;


enum EObstacleType
{
	ObstacleType_None,
	ObstacleType_Cycle,
	ObstacleType_Rectangle,
};


var EObstacleType ObstacleType;
var float Width;
var float Height;
var float Radius;
var int Sides;
var bool bAlignToRotation;

simulated function PostBeginPlay()
{
	super(Actor).PostBeginPlay();
}

event SetAsCycle(float InRadius, optional int InSides = 4)
{
	ObstacleType = ObstacleType_Cycle;
	Radius = InRadius;
	Sides = InSides;
}

event SetAsRectangle(float InWidth, float InHeight)
{
	ObstacleType = ObstacleType_Rectangle;
	Width = InWidth;
	Height = InHeight;
}

event bool GetObstacleBoudingShape(out array<vector> Shape)
{
	local Vector Offset;
	local int i, Angle;
	local Rotator R;

	if(ObstacleType == ObstacleType_Cycle)
	{
		Angle = 65536 / Sides;
		R = bAlignToRotation ? Rotation : Rot(0, 0, 0);
		Offset.X = Radius;
		Offset.Y = 0.f;
		for(i = 0; i < Sides; ++i)
		{
			Shape.AddItem(Location + (Offset >> R));
			R.Yaw += Angle;
		}
		return true;
	}
	else if(ObstacleType == ObstacleType_Rectangle)
	{
		if(bAlignToRotation)
		{
			Offset.X = Width;
			Offset.Y = Height;
			Shape.AddItem(Location + (Offset >> Rotation));

			Offset.X = -Width;
			Offset.Y = Height;
			Shape.AddItem(Location + (Offset >> Rotation));

			Offset.X = -Width;
			Offset.Y = -Height;
			Shape.AddItem(Location + (Offset >> Rotation));

			Offset.X = Width;
			Offset.Y = -Height;
			Shape.AddItem(Location + (Offset >> Rotation));
		}
		else
		{
			Offset.X = Width;
			Offset.Y = Height;
			Shape.AddItem(Location + Offset);

			Offset.X = -Width;
			Offset.Y = Height;
			Shape.AddItem(Location + Offset);

			Offset.X = -Width;
			Offset.Y = -Height;
			Shape.AddItem(Location + Offset);

			Offset.X = Width;
			Offset.Y = -Height;
			Shape.AddItem(Location + Offset);
		}

		return true;
	}

	return false;
}









defaultproperties
{
}