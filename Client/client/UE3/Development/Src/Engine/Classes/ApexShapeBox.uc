/*=============================================================================
	ApexShapeBox.uc: APEX integration.
	Copyright 2008-2011 NVIDIA Corporation.
=============================================================================*/

class ApexShapeBox extends ApexShape
	native(ApexFieldSampler)
	;

var DrawBoxComponent Shape;


cpptext
{
	virtual void* CreateApexShape();
}

defaultproperties
{
	Begin Object Class=DrawBoxComponent Name=DrawBox0
		BoxExtent=(X=200.0, Y=200.0, Z=200.0)
	End Object

	Shape = DrawBox0
}
