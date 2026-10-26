/*=============================================================================
	Copyright 1998-2013 Epic Games, Inc. All Rights Reserved.
=============================================================================*/

#include "UnrealEd.h"
#include "RemoteControlTickPage.h"
#include "RemoteControlGame.h"


#if STATS
extern TMap<FString, UBOOL> g_TickCtrlMap;

/** Wrapper object around the tree item's stats data */
class WxTickTreeItem :
	public wxTreeItemData
{
	/** Hide this ctor*/
	WxTickTreeItem()
	{
	}

	/** Indicates the type of item being held */
// 	const EStatTreeItemType ItemType;
	/** Pointer to the group if it's this type */
// 	FStatGroup* Group;
	/** Pointer to the stat if it's this type */
// 	FStatCommonData* Stat;

	FString TickName;
public:
	/**
	 * Sets the wrapper values
	 *
	 * @param InItemType the type of item being held
	 * @param InGroup the group pointer if this is a group wrapper
	 * @param InStat the stat pointer if this is a stat wrapper
	 */
	WxTickTreeItem(const FString& inTickName) :
		TickName(inTickName)
	{
	}

	/** Does nothing as we allocate no state */
	virtual ~WxTickTreeItem(void)
	{
	}

	/** Returns the text for this item */
	const TCHAR* GetText(void) const
	{
		return *TickName;
	}

	/** Determines if the item is checked or not */
	UBOOL IsChecked(void) const
	{
		UBOOL* val = g_TickCtrlMap.Find(TickName);
		if(val)
		{
			return *val;
		}

		return FALSE;
	}

	/**
	 * Toggles the checked status for the item that is wrapped
	 *
	 * @return the new checked state
	 */
	UBOOL ToggleCheck(void)
	{
		UBOOL* val = g_TickCtrlMap.Find(TickName);
		if(val)
		{
			g_TickCtrlMap.Set(TickName, !*val);
			return *val;
		}

		return FALSE;
	}
};

#endif

/**
 * Class that handles displaying stats in the tree view
 */
class WxTickTreeCtrl :
	public wxTreeCtrl
{
	/** The list of images to use */
	wxImageList ImageList;

	/**
	 * Handles the user clicking on the tree item. If it's within the check
	 * box, it changes the state of the object and updates the UI
	 *
	 * @param In the event that needs processing
	 */
	void OnMouseEvent(wxMouseEvent &In)
	{
		if (In.LeftDown())
		{
#if STATS
			INT HitFlags = 0;
			// Figure out what was hit
			wxTreeItemId ItemId = HitTest(In.GetPosition(), HitFlags);
			// If the user has hit the check box
			if (HitFlags & wxTREE_HITTEST_ONITEMICON)
			{
				// Get the item for the specified id
				WxTickTreeItem* Item = (WxTickTreeItem*)GetItemData(ItemId);
				if (Item != NULL)
				{
					// Toggle checked state
					UBOOL bIsChecked = Item->ToggleCheck();
					// Update image list setting
					SetItemImage(ItemId,(INT)bIsChecked);
				}
				else
				{
					In.Skip();
				}
			}
			else
#endif
			{
				In.Skip();
			}
		}
		else
		{
			In.Skip();
		}
	}

public:
	/** Builds the tree data from the stats data */
	void InitTree(void)
	{
		DeleteAllItems();

		// Create a root node for the groups to be children of
		wxTreeItemId GroupsId = AddRoot(TEXT("Ticks"),-1);

#if STATS
		TLookupMap<FString> keys;
		INT cnt = g_TickCtrlMap.GetKeys(keys);

		std::vector<FString> keysArr;
		for (INT i = 0; i < keys.Num(); ++i)
		{
			keysArr.push_back(*keys.GetItem(i));
		}	

		std::sort(keysArr.begin(), keysArr.end(), ComparFString());
		
		for (size_t i = 0; i < keysArr.size(); ++i)
		{
			const FString& k = keysArr[i];
			WxTickTreeItem* GroupItem = new WxTickTreeItem(k);

			wxTreeItemId GroupId = AppendItem(GroupsId,GroupItem->GetText(),
				(INT)GroupItem->IsChecked());
			// Associate the stats tree item data with the id
			SetItemData(GroupId,GroupItem);
		}
#endif
		// Expand the root so all groups are shown
		Expand(GroupsId);
	}

	DECLARE_EVENT_TABLE();

	/**
	 * Recursively updates the children of the node passed in
	 */
	void UpdateCheckedState(const wxTreeItemId& Id)
	{
#if STATS
		WxTickTreeItem* Item = (WxTickTreeItem*)GetItemData(Id);
		if (Item != NULL)
		{
			SetItemImage(Id,(INT)Item->IsChecked());
		}
		wxTreeItemIdValue Cookie;
		// Tell each child to update
		for (wxTreeItemId ChildId = GetFirstChild(Id,Cookie); ChildId.IsOk();
			ChildId = GetNextChild(Id,Cookie))
		{
			UpdateCheckedState(ChildId);
		}
#endif // STATS
	}

public:
	/** Constructs the tree control and builds the image list */
	WxTickTreeCtrl(wxWindow *InParent,wxWindowID InID,
        const wxPoint& InPos = wxDefaultPosition,
		const wxSize& InSize = wxDefaultSize,long InStyle = wxTR_HAS_BUTTONS,
		const wxValidator& InValidator = wxDefaultValidator,
		const wxString& InName = TEXT("WxTickTreeCtrl")) :
		wxTreeCtrl(InParent, InID, InPos, InSize, InStyle, InValidator, InName),
		ImageList(16,16,TRUE)
	{
		ImageList.Add(WxBitmap(TEXT("CheckBox_Off")), wxColor(192,192,192));
		ImageList.Add(WxBitmap(TEXT("CheckBox_On")), wxColor(192,192,192));

		SetImageList(&ImageList);

		InitTree();
	}

	/** For each item in the tree it refreshes the checked state */
	void UpdateCheckedState(void)
	{
		UpdateCheckedState(GetRootItem());
	}
};

BEGIN_EVENT_TABLE(WxTickTreeCtrl, wxTreeCtrl)
	EVT_LEFT_DOWN(WxTickTreeCtrl::OnMouseEvent)
END_EVENT_TABLE()

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// WxRemoteControlTickPage
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BEGIN_EVENT_TABLE(WxRemoteControlTickPage, WxRemoteControlPage)
	EVT_TOOL(ID_REMOTECONTROL_TICKSPAGE_StatUnit, WxRemoteControlTickPage::OnStatUnit)
	EVT_TOOL(ID_REMOTECONTROL_TICKSPAGE_StatStart, WxRemoteControlTickPage::OnStatStart)
	EVT_TOOL(ID_REMOTECONTROL_TICKSPAGE_StatStop, WxRemoteControlTickPage::OnStatStop)
	EVT_TOOL(ID_REMOTECONTROL_TICKSPAGE_GameProfilerStart, WxRemoteControlTickPage::OnGameProfilerStart)
	EVT_TOOL(ID_REMOTECONTROL_TICKSPAGE_GameProfilerStop, WxRemoteControlTickPage::OnGameProfilerStop)
END_EVENT_TABLE()

WxRemoteControlTickPage::WxRemoteControlTickPage(FRemoteControlGame *InGame, wxNotebook *InNotebook)
	:	WxRemoteControlPage(InGame)
{
	Create(InNotebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL|wxNO_BORDER|wxCLIP_CHILDREN);

	wxBoxSizer *NewMainSizer = new wxBoxSizer(wxVERTICAL);


	ToolBar = new WxToolBar(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTB_FLAT | wxTB_HORIZONTAL);

	ToolBar->SetToolBitmapSize(wxSize(16,16));

	// Temporary variable for loading bitmaps.
	WxBitmap TempBitmap;

	// Refresh button.
	LoadMaskedBitmap( TEXT("RCRefresh"), TempBitmap );
	ToolBar->AddTool(ID_REMOTECONTROL_REFRESH_PAGE
		, TempBitmap
		, TEXT("Refresh the Tick list"));

	ToolBar->AddSeparator();

	LoadMaskedBitmap( TEXT("DistributionToggle"), TempBitmap );
	ToolBar->AddTool(ID_REMOTECONTROL_TICKSPAGE_StatUnit
		, TempBitmap
		, TEXT("Stat Unit & FPS"));

	ToolBar->AddSeparator();

	LoadMaskedBitmap( TEXT("ASV_Play"), TempBitmap );
	ToolBar->AddTool(ID_REMOTECONTROL_TICKSPAGE_StatStart
		, TempBitmap
		, TEXT("Stat Start"));

	LoadMaskedBitmap( TEXT("ASV_Stop"), TempBitmap );
	ToolBar->AddTool(ID_REMOTECONTROL_TICKSPAGE_StatStop
		, TempBitmap
		, TEXT("Stat Stop"));


	ToolBar->AddSeparator();

	LoadMaskedBitmap( TEXT("MAT_Play"), TempBitmap );
	ToolBar->AddTool(ID_REMOTECONTROL_TICKSPAGE_GameProfilerStart
		, TempBitmap
		, TEXT("GameProfiler Start"));

	LoadMaskedBitmap( TEXT("MAT_Stop"), TempBitmap );
	ToolBar->AddTool(ID_REMOTECONTROL_TICKSPAGE_GameProfilerStop
		, TempBitmap
		, TEXT("GameProfiler Stop"));


	// Finalize the toolbar.
	ToolBar->Realize();
	NewMainSizer->Add(ToolBar, 0, wxALL|wxEXPAND|wxALIGN_LEFT);
	NewMainSizer->AddSpacer(2);

	TickTreeCtrl = new WxTickTreeCtrl(this,ID_REMOTECONTROL_STATSPAGE_LIST);
	NewMainSizer->Add(TickTreeCtrl, 1, wxALL|wxEXPAND);

	SetSizer(NewMainSizer);
	NewMainSizer->Fit(this);
	NewMainSizer->SetSizeHints(this);
}

/**
 * Return's the page's title, displayed on the notebook tab.
 */
const TCHAR *WxRemoteControlTickPage::GetPageTitle() const
{
	return TEXT("Ticks");
}

/**
 * Refreshes page contents.
 */
void WxRemoteControlTickPage::RefreshPage(UBOOL bForce)
{
	TickTreeCtrl->Freeze();
	TickTreeCtrl->InitTree();
	TickTreeCtrl->UpdateCheckedState();
	TickTreeCtrl->Thaw();
}

void WxRemoteControlTickPage::OnStatUnit( wxCommandEvent &In )
{
	GEngine->Exec(TEXT("STAT UNIT"));
	GEngine->Exec(TEXT("STAT FPS"));
}

void WxRemoteControlTickPage::OnStatStart( wxCommandEvent &In )
{
	GEngine->Exec(TEXT("STAT STARTFILE"));
}

void WxRemoteControlTickPage::OnStatStop( wxCommandEvent &In )
{
	GEngine->Exec(TEXT("STAT STOPFILE"));
}

void WxRemoteControlTickPage::OnGameProfilerStart( wxCommandEvent &In )
{
	GEngine->Exec(TEXT("GameProfiler Start"));
}

void WxRemoteControlTickPage::OnGameProfilerStop( wxCommandEvent &In )
{
	GEngine->Exec(TEXT("GameProfiler Stop"));
}
