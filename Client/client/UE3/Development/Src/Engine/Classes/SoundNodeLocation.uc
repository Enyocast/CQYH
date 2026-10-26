/**
 * Copyright 1998-2013 Shanda Games, Inc. All Rights Reserved.
 */
 
/** 
 * Defines how a sound source locate 
 */
  
class SoundNodeLocation extends SoundNode
	native( Sound )
	hidecategories( Object )
	editinlinenew;

var( Location )			bool					bUseRandomLocation<ToolTip=true means use random location, false means use the owner location>;
var( Location )         bool                    bUseRelativeLocation<ToolTip=true means in listener space, false means in world space>;
var( Location )			float					RadiusMin<ToolTip=The lower bound of number of random radius>;
var( Location )			float					RadiusMax<ToolTip=The upper bound of number of random radius>;
var( Location )			float					ThetaMin<ToolTip=The lower bound of number of phase in polar coordinates>;
var( Location )			float					ThetaMax<ToolTip=The upper bound of number of phase in polar coordinates>;

var                     vector                  Location;

defaultproperties
{
	bUseRandomLocation=FALSE;
	bUseRelativeLocation=FALSE;
	
	RadiusMin = 100;
	RadiusMax = 200;
	
	ThetaMin = 0;
	ThetaMax = 360;

	Location = (X=0.0,Y=0.0,Z=0.0);
}