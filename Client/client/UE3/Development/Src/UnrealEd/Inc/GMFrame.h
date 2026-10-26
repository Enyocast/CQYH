/*=============================================================================
	Copyright 1998-2013 Epic Games, Inc. All Rights Reserved.
=============================================================================*/

#ifndef __GMFRAME_H__
#define __GMFRAME_H__

// Forward declarations.
class FGMGame;

class WxGMFrame : public wxFrame
{
	/** FGMPageFactory is a friend so that it can call RegisterPageFactory. */
	friend class FGMPageFactory;

public:
	WxGMFrame(FGMGame *InGame, wxWindow *InParent, wxWindowID InID);
	virtual ~WxGMFrame();

	/**
	 * Override of show so we notify FGMGame of visibility state.
	 */
	virtual bool Show(bool bShow);

	/**
	 * Repositions GM so its locked to upper right of game window.
	 */
	void Reposition();

private:
	FGMGame*	Game;
	wxPanel*			MainPanel;
	wxSizer*			MainSizer;
	wxNotebook*			Notebook;

	/**
	 * Register a GM page factory.
	 */
	static void RegisterPageFactory(FGMPageFactory *pPageFactory);

	/**
	 * Helper function to refresh the selected page.
	 * @param bForce - forces an update, even if the page thinks it's already up to date
	 */
	void RefreshSelectedPage(UBOOL bForce = FALSE);

	///////////////////////////////////////////////////
	// Wx events.

	/**
	 * Selected when user decides to refresh a page.
	 */
	void OnSwitchToGame(wxCommandEvent &In);

	/**
	 * Close event -- prevents window destruction; instead, hides the GM window.
	 */
	void OnClose(wxCloseEvent &In);

	/**
	 * Selected when user decides to refresh the active page.
	 */
	void OnPageRefresh(wxCommandEvent &In);

	/**
	 * Selected when the window is activated; refreshes the current page and updates property windows.
	 */
	void OnActivate(wxActivateEvent &In);

	/**
	 * Called when the active page changes.
	 */
	void OnPageChanged(wxNotebookEvent &In);

	/**
	 * Saves the window position and size to the game .ini
	 */
	void SaveToINI();

	DECLARE_EVENT_TABLE()
};

#endif // __GMFRAME_H__
