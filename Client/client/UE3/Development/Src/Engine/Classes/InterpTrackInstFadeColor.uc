/**
 * Copyright 1998-2013 Epic Games, Inc. All Rights Reserved.
 */
class InterpTrackInstFadeColor extends InterpTrackInstProperty
	native(Interpolation);


cpptext
{
	virtual void TermTrackInst(UInterpTrack* Track);
}

var	Color		FadeToColor; 
