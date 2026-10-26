/*=============================================================================
	Copyright 1998-2013 Epic Games, Inc. All Rights Reserved.
=============================================================================*/

#include "UnrealEd.h"
#include "GMFrame.h"
#include "GMPageFactory.h"
#include "GMPage.h"
#include "GMGame.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// FGMPageFactory registration.
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * Convenience type definition for the GM page factory registry.
 */
typedef TArray<FGMPageFactory*> FactoryRegistryType;

/**
 * Retreives the GM factory registry singleton instance.
 */
static FactoryRegistryType &GetFactoryRegistry()
{
	static FactoryRegistryType SRegistry;
	return SRegistry;
}


/**
 * Register a GM page factory.
 */
void WxGMFrame::RegisterPageFactory(FGMPageFactory *InFactory)
{
	if ( InFactory )
	{
		FactoryRegistryType& FactoryRegistry = GetFactoryRegistry();
		FactoryRegistry.AddUniqueItem( InFactory );
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// WxGMFrame
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BEGIN_EVENT_TABLE(WxGMFrame, wxFrame)
	EVT_CLOSE(WxGMFrame::OnClose)
	EVT_MENU(ID_GM_SWITCH_TO_GAME, WxGMFrame::OnSwitchToGame)
	EVT_MENU(ID_GM_REFRESH_PAGE, WxGMFrame::OnPageRefresh)
	EVT_ACTIVATE(WxGMFrame::OnActivate)
	EVT_NOTEBOOK_PAGE_CHANGED(ID_GM_NOTEBOOK, WxGMFrame::OnPageChanged)
END_EVENT_TABLE()

WxGMFrame::WxGMFrame(FGMGame *InGame
									 , wxWindow *InParent
									 , wxWindowID InID)
	:	wxFrame(InParent
				, InID
				, TEXT("GM")
				, InGame->GetGMPosition()
				, wxDefaultSize
				, wxDEFAULT_FRAME_STYLE|wxCLIP_CHILDREN)
				, Game(InGame)
{
	// Allocate a panel and sizer.
	MainPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(430, 100), wxTAB_TRAVERSAL|wxNO_BORDER|wxCLIP_CHILDREN);
	MainSizer = new wxBoxSizer(wxVERTICAL);

	// Create a notebook.
	Notebook = new wxNotebook(MainPanel , ID_GM_NOTEBOOK, wxDefaultPosition, wxSize(430, 100), wxCLIP_CHILDREN);
	MainSizer->Add(Notebook, 1, wxALL|wxEXPAND);

	// Add all pages registered in the page factory.
	FactoryRegistryType &FactoryRegistry = GetFactoryRegistry();

	bool bSelectedPage = true;
	for(INT PageFactoryIndex = 0; PageFactoryIndex < FactoryRegistry.Num(); ++PageFactoryIndex)
	{
		FGMPageFactory* CurPageFactory = FactoryRegistry( PageFactoryIndex );
		WxGMPage *NewPage = CurPageFactory->CreatePage( Game, Notebook );
		if ( NewPage )
		{
			const TCHAR* PageTitle = NewPage->GetPageTitle();
			Notebook->AddPage( NewPage, PageTitle, bSelectedPage );
			// All other pages are deselected.
			bSelectedPage = false;
		}
	}

	// Register the sizer.
	MainPanel->SetSizer(MainSizer);

	// Set up accelerator table.
	//wxAcceleratorEntry Entries[2];
	//Entries[0].Set(wxACCEL_NORMAL, WXK_F4, ID_REMOTECONTROL_SWITCH_TO_GAME);
	//Entries[1].Set(wxACCEL_NORMAL, WXK_F5, ID_REMOTECONTROL_REFRESH_PAGE);
	//const wxAcceleratorTable Accel(sizeof(Entries)/sizeof(wxAcceleratorEntry), Entries);
	//SetAcceleratorTable(Accel);

	// Update UI for the active page.
	RefreshSelectedPage();

	// Finalize the window layout.
	MainSizer->Fit( this );
	MainSizer->SetSizeHints( this );

	// Initialize the RC's size and position from ini.
	if(GConfig)
	{
		INT PosX = 0;
		INT PosY = 0;
		INT Width = 0;
		INT Height = 0;

		GConfig->GetInt(TEXT("DebugWindows"), TEXT("GMX"), PosX, GGameIni);
		GConfig->GetInt(TEXT("DebugWindows"), TEXT("GMY"), PosY, GGameIni);
		GConfig->GetInt(TEXT("DebugWindows"), TEXT("GMWidth"), Width, GGameIni);
		GConfig->GetInt(TEXT("DebugWindows"), TEXT("GMHeight"), Height, GGameIni);

		SetSize(PosX, PosY, Width, Height);
	}
}

WxGMFrame::~WxGMFrame()
{
	SaveToINI();
}

/**
 * Saves the window position and size to the game .ini
 */
void WxGMFrame::SaveToINI()
{
	if(GConfig)
	{
		INT PosX = 0;
		INT PosY = 0;

		GetPosition(&PosX, &PosY);

		INT Width = 0;
		INT Height = 0;

		GetSize(&Width, &Height);

		GConfig->SetInt(TEXT("DebugWindows"), TEXT("GMX"), PosX, GGameIni);
		GConfig->SetInt(TEXT("DebugWindows"), TEXT("GMY"), PosY, GGameIni);
		GConfig->SetInt(TEXT("DebugWindows"), TEXT("GMWidth"), Width, GGameIni);
		GConfig->SetInt(TEXT("DebugWindows"), TEXT("GMHeight"), Height, GGameIni);
	}
}

/**
 * Override of show so we notify FGMGame of visibility state.
 */
bool WxGMFrame::Show(bool bShow)
{
	if( bShow )
	{
		if( !IsShown() )
		{
			Game->OnGMShow();
		}
	}
	else
	{
		SaveToINI();

		if( IsShown() )
		{
			Game->OnGMHide();
		}
	}
	return wxFrame::Show( bShow );
}

/**
 * Repositions GM so its locked to upper right of game window.
 */
void WxGMFrame::Reposition()
{
	const wxPoint Point( Game->GetGMPosition() );
	if( Point != wxDefaultPosition )
	{
		Move( Point );
	}
}

/**
 * Helper function to refresh the selected page.
 */
void WxGMFrame::RefreshSelectedPage(UBOOL bForce)
{
	const int SelectedPageIndex = Notebook->GetSelection();

	if( SelectedPageIndex != -1 )
	{
		WxGMPage *SelectedPage = static_cast<WxGMPage *>(Notebook->GetPage((size_t)SelectedPageIndex));
		check( SelectedPage );
		SelectedPage->RefreshPage(bForce);
	}
}

/**
 * Close event -- prevents window destruction; instead, hides the GM window.
 */
void WxGMFrame::OnClose(wxCloseEvent &In)
{
	Show(FALSE);
	Game->SetFocusToGame();
}

/**
 * Selected when user decides to refresh a page.
 */
void WxGMFrame::OnSwitchToGame(wxCommandEvent &In)
{
	Game->SetFocusToGame();
}

/**
 * Selected when user decides to refresh the active page.
 */
void WxGMFrame::OnPageRefresh(wxCommandEvent &In)
{
	RefreshSelectedPage(TRUE);
}

/**
 * Selected when the window is activated; refreshes the current page and updates property windows.
 */
void WxGMFrame::OnActivate(wxActivateEvent &In)
{
	if( In.GetActive() )
	{
		// Redraw the acitve page.
		RefreshSelectedPage();

		// Kill off any invalid property windows.
		Game->RefreshActorPropertyWindowList();
	}
}

/**
 * Called when the active page changes.
 */
void WxGMFrame::OnPageChanged(wxNotebookEvent &In)
{
	RefreshSelectedPage();
}
