/*=============================================================================
	Copyright 1998-2013 Epic Games, Inc. All Rights Reserved.
=============================================================================*/

#include "UnrealEd.h"
#include "GMExec.h"
#include "GMFrame.h"
#include "GMGamePC.h"

FGMExec::FGMExec()
	:	Frame(NULL)
{
	GamePC = new FGMGamePC;
}

FGMExec::~FGMExec()
{
	// wxWindows will clean up the frame; no need to delete.
	delete GamePC;
}

/**
 * Exec override for handling the GM toggle command.
 */
UBOOL FGMExec::Exec(const TCHAR *Cmd, FOutputDevice &Ar)
{
	UBOOL bHandled = FALSE;

	if( ParseCommand( &Cmd, TEXT("RC") ) || ParseCommand( &Cmd, TEXT("GM") ) )
	{
		extern UBOOL GUsewxWindows;
		if( GUsewxWindows && ParseParam(appCmdLine(), TEXT("GM")))
		{
			if ( IsShown() )
			{
				Show( FALSE );
			}
			else
			{
				// Allow GM to activate only when a game is running.
				if ( GIsGame )
				{
					Show( TRUE );
				}
			}
		}
		else
		{
			warnf(TEXT("You need to start the game with -WXWINDOWS on the command line for remote control support"));
		}
		bHandled = TRUE;
	}

	return bHandled;
}

/**
 * Called when PIE begins.
 */
void FGMExec::OnPlayInEditor(UWorld *PlayWorld)
{
	// Keep track of the play world.
	GamePC->SetPlayWorld( PlayWorld );
	GamePC->RepositionGM();
	SetFocusToGame();
}

/**
 * Called when PIE ends.
 */
void FGMExec::OnEndPlayMap()
{
	Show( FALSE );
	GamePC->DestroyPropertyWindows();
	GamePC->SetPlayWorld( NULL );
}

/**
 * Called by the game engine, entry point for GM's game viewport rendering.
 */
void FGMExec::RenderInGame()
{
	GamePC->RenderInGame();
}

/**
 * Clean-up function for cleaning up after a PIE session.
 */
void FGMExec::CleanUpAfterPIE()
{
	if ( GLogConsole )
	{
	    GLogConsole->Show( FALSE );
	}
}

/**
 * @return	TRUE	If GM is shown.
 */
UBOOL FGMExec::IsShown() const
{
	return Frame && Frame->IsShown();
}

/**
 * @return	TRUE	If GM has been shown at least once since app startup.
 */
UBOOL FGMExec::HasEverBeenShown() const
{
	return Frame != NULL;
}

/**
 * Show or hide GM.
 */
void FGMExec::Show(UBOOL bShow)
{
	if( bShow )
	{
		CreateGM();
		check( Frame );
		Frame->Show( TRUE );
		Frame->Raise();
		Frame->SetFocus();
	}
	else
	{
		if( Frame )
		{
			Frame->Show( FALSE );
		}
	}
}

/**
 *  Set window focus to the game.
 */
void FGMExec::SetFocusToGame()
{
	if ( IsShown() )
	{
		GamePC->SetFocusToGame();
	}
}

/**
 * Create GM if not already created.
 */
void FGMExec::CreateGM()
{
	if( Frame == NULL )
	{
		Frame = new WxGMFrame( GamePC, NULL, -1 );
		GamePC->SetFrame( Frame );
	}
}
