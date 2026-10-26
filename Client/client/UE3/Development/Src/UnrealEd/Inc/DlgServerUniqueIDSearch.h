
#ifndef __DLGSERVERUNIQUEIDSEARCH_H__
#define __DLGSERVERUNIQUEIDSEARCH_H__

/**
* wxWidgets timer ID
*/
#define SERVERUNIQUEIDSEARCH_TIMER_ID 99980

/** delay after a new character is entered into the search dialog to wait before updating the list (to give them time to enter a whole string instead of useless updating every time a char is put in) **/
#define SEARCH_TEXT_UPDATE_DELAY 750

class WxDlgServerUniqueIDSearch : public wxDialog, public FSerializableObject
{
public:
	enum EActorSearchFields
	{
		SUIDSF_Name,		// Search by name
		SUIDSF_Tag,			// Search by tag
		SUIDSF_ServerUniqueID,// Search by server unique ID
		SUIDSF_Level,		// Search by level
		SUIDSF_PathName,	// Search by path name
		SUIDSF_Layer,		// Search by layer
	};

	WxDlgServerUniqueIDSearch( wxWindow* InParent );
	virtual ~WxDlgServerUniqueIDSearch();

	/**
	 * Empties the search list, releases actor references, etc.
	 */
	void Clear();

	/** Updates the results list using the current filter and search options set. */
	void UpdateResults();

	/** Serializes object references to the specified archive. */
	virtual void Serialize(FArchive& Ar);

	class FActorSearchOptions
	{
	public:
		FActorSearchOptions()
			: Column( SUIDSF_Name )
			, bSortAscending( TRUE )
		{}
		/** The column currently being used for sorting. */
		EActorSearchFields Column;
		/** Denotes ascending/descending sort order. */
		UBOOL bSortAscending;
	};

	/**
	 * Utility method for getting the correct string to search by for a given actor in a specified search field
	 *
	 * @param	InActor		Actor to find a search string for
	 * @param	SearchField	Search field to retrieve a search string for
	 *
	 * @return String representing the actor's search string for the given search field
	 */
	static FString GetActorSearchString( AActor* InActor, EActorSearchFields SearchField );

	void CenterActorByCondition( FString &Cond1, FString &Value1, FString &Cond2, FString &Value2 );
protected:
	INT ConditionStr2Enum( FString Condition );
	AActor* FindActorByCondition( FString &Cond1, FString &Value1, FString &Cond2, FString &Value2 );

	/** Maximum number of results viewable in the Find Actors dialog */
	static const int MaxViewableResuts = 1000;

	wxTextCtrl *SearchForEdit;
	wxRadioButton *StartsWithRadio;
	wxRadioButton *ContainingRadio;
	wxComboBox *InsideOfCombo;
	wxListCtrl *ResultsList;
	wxStaticText *ResultsLabel;

	TArray<AActor*> ReferencedActors;

	FActorSearchOptions SearchOptions;

	/** timer to handle updating of search items **/
	wxTimer _updateResultsTimer;

	/** Wx Event Handlers */
	void OnTimer( wxTimerEvent& event );
	void OnSearchTextChanged( wxCommandEvent& In );
	void OnColumnClicked( wxListEvent& In );
	void OnItemActivated( wxListEvent& In );
	void OnGoTo( wxCommandEvent& In );
	void OnDelete( wxCommandEvent& In );
	void OnProperties( wxCommandEvent& In );

	/** Refreshes the results list when the window gets focus. */
	void OnActivate( wxActivateEvent& In);

	/** Called after the user interacts with the "Inside Of" combo box */
	void OnInsideOfComboBoxChanged( wxCommandEvent& In );

	DECLARE_EVENT_TABLE()
};

#endif // __DLGSERVERUNIQUEIDSEARCH_H__
