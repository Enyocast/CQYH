#include "stdafx.h"
#include "MMOFacade.h"
#include "MMOUtil.h"

IMPLEMENT_CLASS(AMMOVolume_ChangeMoveSpeed)

void AMMOVolume_ChangeMoveSpeed::RegisterToFacade()
{
	//MMOFacade::getSingleton().RegisterTriggerVolume(this);
}
//------------------------------------------------------------------------
FBox AMMOVolume_ChangeMoveSpeed::GetObjectServerBounds()
{
	FBox box = GetComponentsBoundingBox();
	ConvertBoxToServer(box);
	return box;
}
//------------------------------------------------------------------------
FVector AMMOVolume_ChangeMoveSpeed::GetObjectServerPosition()
{
	FVector result = Location;
	ConvertCoordC2S(result);
	result.X = (INT32)result.X / GRID_WIDTH * GRID_WIDTH + GRID_WIDTH / 2;
	result.Y = (INT32)result.Y / GRID_WIDTH * GRID_WIDTH + GRID_WIDTH / 2;
	return result;
}