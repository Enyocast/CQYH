/**
 * Copyright 1998-2013 Epic Games, Inc. All Rights Reserved.
 */
//=============================================================================
// VolumetricBuilder: Builds a volumetric brush (criss-crossed sheets).
//=============================================================================
class ExportServerDataCommandlet
	extends Commandlet
	native;

cpptext
{
	virtual INT Main(const FString& Params);
}

defaultproperties
{	
}
