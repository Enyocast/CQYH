/*=============================================================================
	Copyright 1998-2013 Epic Games, Inc. All Rights Reserved.
=============================================================================*/

#ifndef __GMCOMMANDPAGE_H__
#define __GMCOMMANDPAGE_H__

#include "GMPage.h"

// Forward declarations.
class wxNotebook;
class wxChoice;
class wxComboBox;
class wxCheckBox;
class wxCommandEvent;

/**
 * Standard GM render page
 */
class WxGMCommandPage : public WxGMPage
{
public:
	WxGMCommandPage(FGMGame* Game, wxNotebook* Notebook);

	/**
	 * Return's the page's title, displayed on the notebook tab.
	 */
	virtual const TCHAR *GetPageTitle() const;

	/**
	 * Refreshes page contents.
	 */
	virtual void RefreshPage(UBOOL bForce = FALSE);

protected:
	void ProcessCommand( wxCommandEvent& event );

private:
	wxStaticText* GMCommandTitle;
	wxComboBox* GMCommandComboBox;

	/**
	 * Helper function for refreshing the value of Slomo text field.
	 */
	void UpdateCommandCtrl(const FString& commandStr);

	///////////////////////////////////////
	// Wx event handlers.

	void OnEnterCommand(wxCommandEvent& In);
	void OnApplyFOV(wxCommandEvent& In);

	DECLARE_EVENT_TABLE()
};

#endif // __GMCOMMANDPAGE_H__
