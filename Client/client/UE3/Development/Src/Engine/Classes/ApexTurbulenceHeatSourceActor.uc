/*=============================================================================
	ApexTurbulenceHeatSourceActor.uc: APEX integration.
	Copyright 2008-2011 NVIDIA Corporation.
=============================================================================*/

/*** This class defines a single instance of a destructible asset */
class ApexTurbulenceHeatSourceActor extends Actor
	native(ApexFieldSampler)
	placeable
	dependson(ApexTurbulenceHeatSourceComponent);
	

cpptext
{
}

defaultproperties
{
	TickGroup=TG_PreAsyncWork

	Begin Object Class=ApexTurbulenceHeatSourceComponent Name=HeatSourceComponent
	End Object
	Components.Add(HeatSourceComponent)
}
