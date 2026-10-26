/*=============================================================================
	Copyright 1998-2014 Bruce@snda, Inc. All Rights Reserved.
=============================================================================*/

#include "UnrealEd.h"
#include "DlgMapSearch.h"
#include "ScopedTransaction.h"
#include "BusyCursor.h"
#include "LevelUtils.h"
#include "FileHelpers.h"

BEGIN_EVENT_TABLE( WxDlgMapSearch, wxDialog )
	EVT_TIMER( MAPSEARCH_TIMER_ID, WxDlgMapSearch::OnTimer )
END_EVENT_TABLE()

WxDlgMapSearch::WxDlgMapSearch( wxWindow* InParent )
{
	const bool bSuccess = wxXmlResource::Get()->LoadDialog( this, InParent, TEXT("ID_DLG_ACTOR_SEARCH") );
	check( bSuccess );

	SearchForEdit = (wxTextCtrl*)FindWindow( XRCID( "ID_SEARCH_FOR" ) );
	check( SearchForEdit != NULL );
	StartsWithRadio = (wxRadioButton*)FindWindow( XRCID( "ID_STARTING_WITH" ) );
	check( StartsWithRadio != NULL );
	ContainingRadio = (wxRadioButton*)FindWindow( XRCID( "ID_CONTAINING" ) );
	check( ContainingRadio != NULL );
	ResultsList = (wxListCtrl*)FindWindow( XRCID( "ID_RESULTS" ) );
	check( ResultsList != NULL );
	ResultsLabel = (wxStaticText*)FindWindow( XRCID( "ID_RESULTS_TEXT" ) );
	check( ResultsLabel != NULL );
	InsideOfCombo = (wxComboBox*)FindWindow( XRCID( "IDCB_INSIDEOF" ) );
	check( InsideOfCombo != NULL );

	ResultsList->InsertColumn( ASF_MapDisplayName, *LocalizeUnrealEdMMO("MapDisplayName"), wxLIST_FORMAT_LEFT, 128 );
	ResultsList->InsertColumn( ASF_ShortName, *LocalizeUnrealEdMMO("ShortName"), wxLIST_FORMAT_LEFT, 128 );
	ResultsList->InsertColumn( ASF_ServerID, *LocalizeUnrealEdMMO("ServerID"), wxLIST_FORMAT_LEFT, 128 );
	ResultsList->InsertColumn( ASF_MapName, *LocalizeUnrealEdMMO("MapName"), wxLIST_FORMAT_LEFT, 300 );

	ADDEVENTHANDLER( XRCID("ID_SEARCH_FOR"), wxEVT_COMMAND_TEXT_UPDATED, &WxDlgMapSearch::OnSearchTextChanged );
	wxEvtHandler* eh = GetEventHandler();
	eh->Connect( XRCID("ID_RESULTS"), wxEVT_COMMAND_LIST_COL_CLICK, wxListEventHandler(WxDlgMapSearch::OnColumnClicked) );
	eh->Connect( XRCID("ID_RESULTS"), wxEVT_COMMAND_LIST_ITEM_ACTIVATED, wxListEventHandler(WxDlgMapSearch::OnItemActivated) );
	ADDEVENTHANDLER( XRCID("IDPB_GOTOACTOR"), wxEVT_COMMAND_BUTTON_CLICKED, &WxDlgMapSearch::OnGoTo )
	eh->Connect( this->GetId(), wxEVT_ACTIVATE, wxActivateEventHandler(WxDlgMapSearch::OnActivate) );

	FWindowUtil::LoadPosSize( TEXT("DlgActorSearch"), this, 256, 256, 450, 400 );
	
	//Guard around this window not existing yet and therefore doesn't have a world to reference
	if (GWorld)
	{
		UpdateResults();
	}	
		
	ShowWindow( GetDlgItem( (HWND)this->m_hWnd, XRCID( "wxID_InsideOf" ) ), SW_HIDE );	
	ShowWindow( GetDlgItem( (HWND)this->m_hWnd, XRCID( "ID_RESULTS_TEXT" ) ), SW_HIDE );	

	ShowWindow( GetDlgItem( (HWND)this->m_hWnd, XRCID( "ID_CONTAINING" ) ), SW_HIDE );	
	ShowWindow( GetDlgItem( (HWND)this->m_hWnd, XRCID( "ID_STARTING_WITH" ) ), SW_HIDE );	
	ShowWindow( GetDlgItem( (HWND)this->m_hWnd, XRCID( "IDPB_DELETEACTOR" ) ), SW_HIDE );	
	ShowWindow( GetDlgItem( (HWND)this->m_hWnd, XRCID( "IDPB_PROPERTIES" ) ), SW_HIDE );	
	ShowWindow( GetDlgItem( (HWND)this->m_hWnd, XRCID( "IDCB_INSIDEOF" ) ), SW_HIDE );	

	::SetWindowText( (HWND)this->m_hWnd, *LocalizeUnrealEdMMO("MapSearchCaptionName") );
	//FLocalizeWindow( this );

	_updateResultsTimer.SetOwner(this, MAPSEARCH_TIMER_ID);
}

WxDlgMapSearch::~WxDlgMapSearch()
{
	FWindowUtil::SavePosSize( TEXT("DlgActorSearch"), this );
	_updateResultsTimer.Stop();
}

void WxDlgMapSearch::OnTimer( wxTimerEvent& event )
{
	UpdateResults();
}

void WxDlgMapSearch::OnSearchTextChanged( wxCommandEvent& In )
{
	// if the timer was already running, reset the timer and start over
	if(_updateResultsTimer.IsRunning())
	{
		_updateResultsTimer.Stop();		
	}
	_updateResultsTimer.Start(SEARCH_TEXT_UPDATE_DELAY_EXT, wxTIMER_ONE_SHOT);
}

void WxDlgMapSearch::OnColumnClicked( wxListEvent& In )
{
	const INT Column = In.GetColumn();

	if( Column > -1 )
	{
		if( Column == SearchOptions.Column )
		{
			// Clicking on the same column will flip the sort order
			SearchOptions.bSortAscending = !SearchOptions.bSortAscending;
		}
		else
		{
			// Clicking on a new column will set that column as current and reset the sort order.
			SearchOptions.Column = static_cast<EActorSearchFields>( In.GetColumn() );
			SearchOptions.bSortAscending = TRUE;
		}
	}

	UpdateResults();
}

void WxDlgMapSearch::OnItemActivated( wxListEvent& In )
{
	wxCommandEvent Event;
	OnGoTo( Event );
}

/**
 * Empties the search list, releases actor references, etc.
 */
void WxDlgMapSearch::Clear()
{
	ResultsList->DeleteAllItems();
}

/**
 * Updates the contents of the results list.
 */
void WxDlgMapSearch::UpdateResults()
{
	const FScopedBusyCursor BusyCursor;
	ResultsList->Freeze();
	{
		TMap<PTRINT, LONG> ExistingResultValues;
		const INT NumItems = ResultsList->GetItemCount();
		for ( INT ItemIndex = 0; ItemIndex < NumItems; ++ItemIndex )
		{
			ExistingResultValues.Set( ResultsList->GetItemData( ItemIndex ), ResultsList->GetItemState( ItemIndex, wxLIST_STATE_SELECTED | wxLIST_STATE_FOCUSED ) );
		}

		Clear();

		FString SearchText = (const TCHAR*)SearchForEdit->GetValue();
		SearchText = SearchText.ToUpper();

		UGlobalMapInfo* GlobalMapSingleton = UGlobalMapInfo::GetSingleton();
		if (GlobalMapSingleton)
		{
			for (INT i = 0; i < GlobalMapSingleton->ExportMaps.Num(); ++i)
			{
				UBOOL bFoundItem = FALSE;

				FString MapDisplayNString = GlobalMapSingleton->ExportMaps(i).MapDisplayName;
				FString ShortNameString = GlobalMapSingleton->ExportMaps(i).ShortName;
				FString CompString = GlobalMapSingleton->ExportMaps(i).MapName;
				FString ServerIDString = appItoa( GlobalMapSingleton->ExportMaps(i).ServerID );

				if ( SearchText.Len() == 0 || MapDisplayNString.ToUpper().InStr( SearchText ) != INDEX_NONE ||
					ShortNameString.ToUpper().InStr( SearchText ) != INDEX_NONE ||
					CompString.ToUpper().InStr( SearchText ) != INDEX_NONE || 
					ServerIDString.ToUpper().InStr( SearchText ) != INDEX_NONE )
				{
					bFoundItem = TRUE;
				}

				if( bFoundItem )
				{
					if ( ResultsList->GetItemCount() < MaxViewableResuts )
					{
						const LONG Idx = ResultsList->InsertItem( ASF_MapDisplayName, *MapDisplayNString );
						ResultsList->SetItem( Idx, ASF_ShortName, *ShortNameString );
						ResultsList->SetItem( Idx, ASF_ServerID, *ServerIDString );
						ResultsList->SetItem( Idx, ASF_MapName, *CompString );
					}					
				}
			}
		}
	}
	ResultsList->Thaw();	
}

void WxDlgMapSearch::OnGoTo( wxCommandEvent& In )
{
	long ItemIndex = ResultsList->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );

	TArray<FString> AllListStr;

	FString SearchText = (const TCHAR*)SearchForEdit->GetValue();
	SearchText = SearchText.ToUpper();

	UGlobalMapInfo* GlobalMapSingleton = UGlobalMapInfo::GetSingleton();
	if (GlobalMapSingleton)
	{
		for ( INT i = GlobalMapSingleton->ExportMaps.Num() - 1; i >= 0; --i )
		{
			UBOOL bFoundItem = FALSE;

			FString MapDisplayNString = GlobalMapSingleton->ExportMaps(i).MapDisplayName;
			FString ShortNameString = GlobalMapSingleton->ExportMaps(i).ShortName;
			FString CompString = GlobalMapSingleton->ExportMaps(i).MapName;
			FString ServerIDString = appItoa( GlobalMapSingleton->ExportMaps(i).ServerID );

			if ( SearchText.Len() == 0 || MapDisplayNString.ToUpper().InStr( SearchText ) != INDEX_NONE ||
				ShortNameString.ToUpper().InStr( SearchText ) != INDEX_NONE ||
				CompString.ToUpper().InStr( SearchText ) != INDEX_NONE || 
				ServerIDString.ToUpper().InStr( SearchText ) != INDEX_NONE )
			{
				bFoundItem = TRUE;
			}

			if( bFoundItem )
			{
				if ( ResultsList->GetItemCount() < MaxViewableResuts )
				{
					AllListStr.AddItem( GlobalMapSingleton->ExportMaps(i).MapName );					
				}					
			}
		}
	}

	UBOOL bPromptUserToSave = TRUE;
	UBOOL bSaveMapPackages = TRUE;
	UBOOL bSaveContentPackages = FALSE;
	if( FEditorFileUtils::SaveDirtyPackages(bPromptUserToSave, bSaveMapPackages, bSaveContentPackages) == FALSE )
	{
		// something went wrong or the user pressed cancel.  Return to the editor so the user doesn't lose their changes		
		return;
	}

	FString mapName = AllListStr( ItemIndex ) + TEXT(".udk");
	FString fullMapName = GFileManager->ConvertToAbsolutePath(*mapName);
	FEditorFileUtils::LoadMap( fullMapName );
}

/** Refreshes the results list when the window gets focus. */
void WxDlgMapSearch::OnActivate(wxActivateEvent& In)
{
	const UBOOL bActivated = In.GetActive();
	
	if( bActivated )
	{
		// Find which index in the list control is currently visible as the top entry in the control
		INT HitTestResultFlags = 0;
		const INT TopmostVisibleIndex = ResultsList->HitTest( wxPoint( 0, 0 ), HitTestResultFlags );

		// Find the bounds of the item in the list control in order to help restore scroll position after an update
		wxRect ItemBounds;
		if ( TopmostVisibleIndex != wxNOT_FOUND )
		{
			ResultsList->GetItemRect( TopmostVisibleIndex, ItemBounds, wxLIST_RECT_LABEL );
		}

		// Cache where the scroll bar is currently positioned in order to restore scroll position after an update
		const INT ScrollBarPos = ResultsList->GetScrollPos( wxVERTICAL );
	
		UpdateResults();
		
		// Restore the scroll bar position, if possible, by scrolling the list control by a number of pixels equal to
		// the height of one item multiplied by the cached scroll bar position
		if ( ScrollBarPos <= ResultsList->GetItemCount() && TopmostVisibleIndex != wxNOT_FOUND )
		{
			ResultsList->ScrollList( 0, ScrollBarPos * ItemBounds.GetHeight() );
		}

		// Grant focus to the results list if any of its items are selected
		if ( ResultsList->GetSelectedItemCount() > 0 )
		{
			ResultsList->SetFocus();
		}
	}
}

void WxDlgMapSearch::Serialize(FArchive& Ar)
{

}