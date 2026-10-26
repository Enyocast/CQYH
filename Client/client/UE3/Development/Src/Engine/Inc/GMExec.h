/*=============================================================================
	Copyright 1998-2013 Epic Games, Inc. All Rights Reserved.
=============================================================================*/

#ifndef __GMEXEC_H__
#define __GMEXEC_H__

// Forward declarations.
class WxGMFrame;
class FGMGamePC;

/**
 * FExec handler for the remote control system.
 */
class FGMExec : public FExec
{
public:
	FGMExec();
	virtual ~FGMExec();

	/**
	 * Exec override for handling the GM toggle command.
	 */
	virtual UBOOL Exec(const TCHAR *Cmd, FOutputDevice &Ar);

	/**
	 * Called when PIE begins.
	 */
	void OnPlayInEditor(UWorld *PlayWorld);

	/**
	 * Called when PIE ends.
	 */
	void OnEndPlayMap();

	/**
	 * Called by the game engine, entry point for GM's game viewport rendering.
	 */
	void RenderInGame();

	/**
	 * Clean-up function for cleaning up after a PIE session.
	 */
	virtual void CleanUpAfterPIE();

	/**
	 * @return	TRUE	If GM is shown.
	 */
	UBOOL IsShown() const;

	/**
	 * @return	TRUE	If GM has been shown at least once since app startup.
	 */
	UBOOL HasEverBeenShown() const;

	/**
	 * Show or hide GM.
	 */
	void Show(UBOOL bShow);

	/**
	 *  Set window focus to the game.
	 */
	void SetFocusToGame();

private:
	/**
	 * Create GM if not already created.
	 */
	void CreateGM();

	WxGMFrame	*Frame;
	FGMGamePC	*GamePC;
};

#endif // __GMEXEC_H__
