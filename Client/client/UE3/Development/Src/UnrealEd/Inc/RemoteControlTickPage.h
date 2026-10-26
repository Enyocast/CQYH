/*=============================================================================
	Copyright 1998-2013 Epic Games, Inc. All Rights Reserved.
=============================================================================*/

#ifndef __WxRemoteControlTickPage_H__
#define __WxRemoteControlTickPage_H__

#include "RemoteControlPage.h"

/**
 * Standard RemoteControl stats page.
 */
class WxRemoteControlTickPage : public WxRemoteControlPage
{
public:
	WxRemoteControlTickPage(FRemoteControlGame *Game, wxNotebook *Notebook);

	/**
	 * Return's the page's title, displayed on the notebook tab.
	 */
	virtual const TCHAR *GetPageTitle() const;

	/**
	 * Refreshes page contents.
	 */
	virtual void RefreshPage(UBOOL bForce = FALSE);

private:
	/** The instance of the tree control for displaying stats */
	class WxTickTreeCtrl* TickTreeCtrl;
	class WxToolBar      *ToolBar;

	DECLARE_EVENT_TABLE()

	void OnStatUnit(wxCommandEvent &In);
	void OnStatStart(wxCommandEvent &In);
	void OnStatStop(wxCommandEvent &In);
	void OnGameProfilerStart(wxCommandEvent &In);
	void OnGameProfilerStop(wxCommandEvent &In);

};

#endif // __REMOTECONTROLSTATSPAGE_H__
