/*=============================================================================
	ApexShapeSphere.uc: APEX integration.
	Copyright 2008-2011 NVIDIA Corporation.
=============================================================================*/

class ApexShapeSphere extends ApexShape
	native(ApexFieldSampler)
	;

var DrawSphereComponent Shape;


cpptext
{
	virtual void* CreateApexShape();
}

defaultproperties
{
	Begin Object Class=DrawSphereComponent Name=DrawSphere0
		SphereRadius=200.0
	End Object

	Shape = DrawSphere0
}
