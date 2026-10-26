/*=============================================================================
	ApexTurbulenceHeatSourceComponent.uc: APEX integration.
	Copyright 2008-2011 NVIDIA Corporation.
=============================================================================*/

class ApexTurbulenceHeatSourceComponent extends PrimitiveComponent
	native(ApexFieldSampler)
	hidecategories(Collision,Lighting,Physics,Rendering,Object)
	collapsecategories
	editinlinenew
	;


var()	editinline ApexShape	Shape;

cpptext
{
}

defaultproperties
{
}
