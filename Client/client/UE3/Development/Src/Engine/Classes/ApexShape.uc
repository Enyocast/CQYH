/*=============================================================================
	ApexShape.uc: APEX integration.
	Copyright 2008-2011 NVIDIA Corporation.
=============================================================================*/

class ApexShape extends Object
	native(ApexFieldSampler)
	editinlinenew
	abstract;


cpptext
{
	virtual void* CreateApexShape() { return NULL; }
}

defaultproperties
{
}
