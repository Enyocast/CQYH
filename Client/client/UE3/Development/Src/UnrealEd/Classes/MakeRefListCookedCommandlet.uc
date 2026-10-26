/**
 * This commandlet generates a list of functions which aren't referenced by any code in the game.  This commandlet does not call the
 * event "Main".
 *
 * Copyright 1998-2013 Epic Games, Inc. All Rights Reserved.
 */
class MakeRefListCookedCommandlet extends Commandlet
	native;

cpptext
{
	virtual INT Main(const FString& Params);
}

DefaultProperties
{

}
