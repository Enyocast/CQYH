/*=============================================================================
	Copyright 1998-2013 Bruce@snda, Inc. All Rights Reserved.
=============================================================================*/

#ifndef __DLGMAPSEARCH_H__
#define __DLGMAPSEARCH_H__

#include "../../Engine/Inc/EngineClasses.h"
#include "../../Engine/Inc/EngineMeshClasses.h"
#include "../../Engine/Inc/EngineAnimClasses.h"
#include "../../Engine/Inc/EngineAIClasses.h"
#include "../../GameFramework/Inc/GameFrameworkClasses.h"
#include "../../MMOGame/Inc/MMOGameClasses.h"
/**
* wxWidgets timer ID
*/
#define MAPSEARCH_TIMER_ID 99981

/** delay after a new character is entered into the search dialog to wait before updating the list (to give them time to enter a whole string instead of useless updating every time a char is put in) **/
#define SEARCH_TEXT_UPDATE_DELAY_EXT 751

class WxDlgMapSearch : public wxDialog, public FSerializableObject
{
public:
	enum EActorSearchFields
	{
		ASF_MapDisplayName,		
		ASF_ShortName,		
		ASF_ServerID,		
		ASF_MapName	
	};

	WxDlgMapSearch( wxWindow* InParent );
	virtual ~WxDlgMapSearch();

	/**
	 * Empties the search list, releases actor references, etc.
	 */
	void Clear();

	/** Updates the results list using the current filter and search options set. */
	void UpdateResults();

	virtual void Serialize(FArchive& Ar);

	class FActorSearchOptions
	{
	public:
		FActorSearchOptions()
			: Column( ASF_MapDisplayName )
			, bSortAscending( TRUE )
		{}
		/** The column currently being used for sorting. */
		EActorSearchFields Column;
		/** Denotes ascending/descending sort order. */
		UBOOL bSortAscending;
	};

protected:	

	/** Maximum number of results viewable in the Find Actors dialog */
	static const int MaxViewableResuts = 2000;

	wxRadioButton *StartsWithRadio;
	wxRadioButton *ContainingRadio;
	wxTextCtrl *SearchForEdit;
	wxListCtrl *ResultsList;
	wxStaticText *ResultsLabel;
	wxComboBox *InsideOfCombo;

	//TArray<AActor*> ReferencedActors;

	FActorSearchOptions SearchOptions;

	/** timer to handle updating of search items **/
	wxTimer _updateResultsTimer;

	/** Wx Event Handlers */
	void OnTimer( wxTimerEvent& event );
	void OnSearchTextChanged( wxCommandEvent& In );
	void OnColumnClicked( wxListEvent& In );
	void OnItemActivated( wxListEvent& In );
	void OnGoTo( wxCommandEvent& In );

	/** Refreshes the results list when the window gets focus. */
	void OnActivate( wxActivateEvent& In);

	DECLARE_EVENT_TABLE()
};

#endif // __DLGMAPSEARCH_H__
