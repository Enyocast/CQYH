#include "stdafx.h"
//#include "MMOGameClasses.h"
#include "MMOUtil.h"

IMPLEMENT_CLASS(ADoodadSpawnPoint)

FVector ADoodadSpawnPoint::GetServerPosition()
{
	FVector result = Location;
	ConvertCoordC2S(result);
	result.X = (INT32)result.X / GRID_WIDTH * GRID_WIDTH + GRID_WIDTH / 2;
	result.Y = (INT32)result.Y / GRID_WIDTH * GRID_WIDTH + GRID_WIDTH / 2;
	return result;
}