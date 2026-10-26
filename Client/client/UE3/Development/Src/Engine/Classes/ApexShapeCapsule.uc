/*=============================================================================
	ApexShapeCapsule.uc: APEX integration.
	Copyright 2008-2011 NVIDIA Corporation.
=============================================================================*/

class ApexShapeCapsule extends ApexShape
	native(ApexFieldSampler)
	;

var DrawCapsuleComponent Shape;


cpptext
{
	virtual void* CreateApexShape();
}

defaultproperties
{
	Begin Object Class=DrawCapsuleComponent Name=DrawCapsule0
		CapsuleRadius=200.0
		CapsuleHeight=200.0
		Rotation=(Pitch=0, Yaw=0, Roll=16384)//make it z upwards like cylinder
	End Object

	Shape = DrawCapsule0
}
