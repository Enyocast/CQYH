#include "UnrealEd.h"
#include "DataBrowserHost.h"
#include "PropertyWindow.h"

#if WITH_MANAGED_CODE
#include "DataBrowserShared.h"
#endif

BEGIN_EVENT_TABLE( MySplitterWindow, wxSplitterWindow)
EVT_SPLITTER_SASH_POS_CHANGED(wxID_ANY, MySplitterWindow::OnPostionChanged)
EVT_SPLITTER_SASH_POS_CHANGING(wxID_ANY, MySplitterWindow::OnPostionChanging)
END_EVENT_TABLE()

MySplitterWindow::MySplitterWindow(WxBrowser* parent):wxSplitterWindow(parent)
{
	m_Parent = parent;
}
MySplitterWindow::~MySplitterWindow()
{

}
void MySplitterWindow::OnPostionChanged( wxSplitterEvent& In )
{
	int nBorder = 5;
	int nPos = In.GetSashPosition();
	GetWindow1()->SetSize(0, 0, nPos, GetClientRect().GetSize().GetHeight());
	GetWindow2()->SetSize(nPos+nBorder, 0, GetClientRect().GetSize().GetWidth() - nPos-nBorder, GetClientRect().GetSize().GetHeight());

	((WxDataBrowserSplitter*)m_Parent)->UpdateSplitter(In.GetSashPosition());
	In.Skip();
}
void MySplitterWindow::OnPostionChanging( wxSplitterEvent& In )
{
//	((WxDataBrowserSplitter*)m_Parent)->UpdateSplitter(In.GetSashPosition());
//	In.Skip();
}


BEGIN_EVENT_TABLE( WxDataBrowserSplitter, WxBrowser )
EVT_SIZE( WxDataBrowserSplitter::OnSize )
EVT_SET_FOCUS( WxDataBrowserSplitter::OnReceiveFocus )
END_EVENT_TABLE()


/** Constructor */
WxDataBrowserSplitter::WxDataBrowserSplitter()
{
	bAreWindowsInitialized = FALSE;
}



/** Destructor */
WxDataBrowserSplitter::~WxDataBrowserSplitter()
{
}

/**
* Forwards the call to our base class to create the window relationship.
* Creates any internally used windows after that
*
* @param DockID the unique id to associate with this dockable window
* @param FriendlyName the friendly name to assign to this window
* @param Parent the parent of this window (should be a Notebook)
*/
void WxDataBrowserSplitter::Create( INT DockID, const TCHAR* FriendlyName, wxWindow* Parent )
{
	// Call parent implementation
	WxBrowser::Create( DockID, FriendlyName, Parent);

	// 	WxBrowser* browser = new WxBrowser();
	// 	browser->Create(InPaneID, *InFriendlyName,InParent);
// 	wxBoxSizer* topSizer = new wxBoxSizer(wxHORIZONTAL);
// 	SetSizer(topSizer);
	this->LoadWindowState(0);

 	SplitterWindow = new MySplitterWindow(this);
	bAreWindowsInitialized = TRUE;
 
 	wxScrolledWindow* left = new wxScrolledWindow(SplitterWindow);
 	//left->SetBackgroundColour(*wxRED);
 	wxScrolledWindow* right = new wxScrolledWindow(SplitterWindow);
 	//right->SetBackgroundColour(*wxBLUE);
  	
	PropertyWindowHost = new WxPropertyWindowHost;
  	check( PropertyWindowHost );
  	PropertyWindowHost->Create( right, GUnrealEd, -1 );
  	PropertyWindowHost->SetFlags(EPropertyWindowFlags::CanBeHiddenByPropertyWindowManager, TRUE);
  	//PropertyWindowHost->SetSize(wxRect(0,0,400,400));
  	PropertyWindowHost->Show();

	DataBrowser = new WxDataBrowserHost();
	DataBrowser->Create(DockID, FriendlyName, left);
	DataBrowser->LoadWindowState(0);
	DataBrowser->SetParentBrowserWindow(this);
// 
 	SplitterWindow->SplitVertically( left, right, -400);
 	SplitterWindow->SetSashGravity( 1.0 );
//	SplitterWindow->SetSashPosition(-400);
 	SplitterWindow->SetMinimumPaneSize( 100 );
	SplitterWindow->SetSashPosition(800);

	//topSizer->Add(SplitterWindow, 1, wxEXPAND);
	// 	browser->SetSizer(topSizer);
	// 	browser->SetAutoLayout( true );


#if WITH_MANAGED_CODE
	HWND BrowserTabHandle = (HWND)this->GetHandle();

	// Create the content browser object!
	//FDataBrowser* NewDataBrowser =
	//	FDataBrowser::CreateDataBrowser( this, BrowserTabHandle );
	//DataBrowser.Reset( NewDataBrowser );
#endif


	Update();
}


void WxDataBrowserSplitter::OnSize( wxSizeEvent& In )
{
	//debugf(TEXT("Wx; WM_SIZE: (%d, %d)"), In.GetSize().GetWidth() , In.GetSize().GetHeight());
	//m_SplitterWindow->Resize(NULL, 0, 0, In.GetSize().GetWidth(), In.GetSize().GetHeight());
	if(bAreWindowsInitialized)
	{
		int nPos = SplitterWindow->GetSashPosition();
		UpdateSplitter(nPos);
	}
#if WITH_MANAGED_CODE
	//if( DataBrowser != NULL )
	//{
	//	DataBrowser->Resize(NULL, 0, 0, In.GetSize().GetWidth(), In.GetSize().GetHeight());
	//}
#endif
}

void WxDataBrowserSplitter::OnReceiveFocus( wxFocusEvent& Event )
{
#if WITH_MANAGED_CODE
	//if ( DataBrowser != NULL )
	//{
	//	DataBrowser->SetFocus();
	//}
#endif
}

void WxDataBrowserSplitter::Activated()
{
	WxBrowser::Activated();
#if WITH_MANAGED_CODE
	//DataBrowser->SetFocus();
#endif
}

void WxDataBrowserSplitter::UpdateSplitter(int nPos)
{
	if(bAreWindowsInitialized)
	{
		int nBorder = 5;
		SplitterWindow->SetSize( GetClientRect() );
		DataBrowser->SetSize(SplitterWindow->GetWindow1()->GetClientRect());
		PropertyWindowHost->SetSize(SplitterWindow->GetWindow2()->GetClientRect());
	}
}


/**
* Make sure nothing is added to the accelerator table; we want to be able to handle our own keys.
*/
void WxDataBrowserSplitter::AddAcceleratorTableEntries(TArray<wxAcceleratorEntry>& Entries)
{
	// Add nothing to the accelerator table.
}

void WxDataBrowserSplitter::SetDockStateToFloating()
{ 
	DockState = BDS_Floating;
	DataBrowser->SetDockStateToFloating();
}

void WxDataBrowserSplitter::SetDockStateToDocked()
{
	DockState = BDS_Docked;
	DataBrowser->SetDockStateToDocked();
}




BEGIN_EVENT_TABLE( WxDataBrowserHost, WxBrowser )
EVT_SIZE( WxDataBrowserHost::OnSize )
EVT_SET_FOCUS( WxDataBrowserHost::OnReceiveFocus )
END_EVENT_TABLE()


/** Constructor */
WxDataBrowserHost::WxDataBrowserHost()
{
}



/** Destructor */
WxDataBrowserHost::~WxDataBrowserHost()
{
}





/**
* Forwards the call to our base class to create the window relationship.
* Creates any internally used windows after that
*
* @param DockID the unique id to associate with this dockable window
* @param FriendlyName the friendly name to assign to this window
* @param Parent the parent of this window (should be a Notebook)
*/
void WxDataBrowserHost::Create( INT DockID, const TCHAR* FriendlyName, wxWindow* Parent)
{
	// Call parent implementation
	WxBrowser::Create( DockID, FriendlyName, Parent);

#if WITH_MANAGED_CODE
	HWND BrowserTabHandle = (HWND)this->GetHandle();

	// Create the content browser object!
	FDataBrowser* NewDataBrowser =
		FDataBrowser::CreateDataBrowser( this, BrowserTabHandle );
	DataBrowser.Reset( NewDataBrowser );
#endif
	Update();
}


void WxDataBrowserHost::OnSize( wxSizeEvent& In )
{
	//debugf(TEXT("Wx; WM_SIZE: (%d, %d)"), In.GetSize().GetWidth() , In.GetSize().GetHeight());

#if WITH_MANAGED_CODE
	if( DataBrowser != NULL )
	{
		DataBrowser->Resize(NULL, 0, 0, In.GetSize().GetWidth(), In.GetSize().GetHeight());
	}
#endif
}

void WxDataBrowserHost::OnReceiveFocus( wxFocusEvent& Event )
{
#if WITH_MANAGED_CODE
	if ( DataBrowser != NULL )
	{
		DataBrowser->SetFocus();
	}
#endif
}

void WxDataBrowserHost::Activated()
{
	WxBrowser::Activated();
#if WITH_MANAGED_CODE
	DataBrowser->SetFocus();
#endif
}

/**
* Make sure nothing is added to the accelerator table; we want to be able to handle our own keys.
*/
void WxDataBrowserHost::AddAcceleratorTableEntries(TArray<wxAcceleratorEntry>& Entries)
{
	// Add nothing to the accelerator table.
}

#if WITH_MANAGED_CODE
/**
* Accessor for retrieving a reference to this browser window's associated FContentBrowser object.
* Useful in cases where you need to call methods in FContentBrowser and need to ensure that it is the one
* associated with a specific WxBrowser window.
*/
FDataBrowser* WxDataBrowserHost::GetDataBrowserInstance()
{
	return DataBrowser;
}
#endif


// EOF

