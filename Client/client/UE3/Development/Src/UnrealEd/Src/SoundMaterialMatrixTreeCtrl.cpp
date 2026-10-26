
#include "SoundMaterialMatrixTreeCtrl.h"

/*-----------------------------------------------------------------------------
	SoundMaterialMatrixToolBar.
-----------------------------------------------------------------------------*/

BEGIN_EVENT_TABLE( SoundMaterialMatrixToolBar, WxToolBar )
END_EVENT_TABLE()

SoundMaterialMatrixToolBar::SoundMaterialMatrixToolBar( wxWindow* InParent, wxWindowID InID )
	: WxToolBar( InParent, InID, wxDefaultPosition, wxDefaultSize, wxTB_HORIZONTAL | wxTB_FLAT | wxTB_3DBUTTONS )
{
	// create the return to parent sequence button
	//ParentSequenceB.Load(TEXT("UpArrow.png"));
	//RenameSequenceB.Load(TEXT("KIS_Rename"));
	//HideB.Load(TEXT("KIS_HideConnectors"));
	//ShowB.Load(TEXT("KIS_ShowConnectors"));
	//CurvesB.Load(TEXT("KIS_DrawCurves"));
	//SearchB.Load( TEXT("KIS_Search") );
	//ZoomToFitB.Load( TEXT("KIS_ZoomToFit") );
	//UpdateB.Load(TEXT("KIS_Update"));
	//OpenB.Load(TEXT("Kismet"));
	//CreateSeqObjB.Load( TEXT("UnlitMovement") );
	//ClearBreakPointsB.Load( TEXT("KIS_ClearBreakpoints") );
	//
	SetToolBitmapSize( wxSize( 24, 24 ) );

	BmpRefreshAll.Load( TEXT("112_RefreshArrow_Green_24x24_72.png") );
	BmpSave.Load( TEXT("Save24.png") );
	BmpHitSounds.Load( TEXT("SoundMaterialMatrix.png") );
	BmpFootstepSounds.Load( TEXT("SoundMaterialMatrix.png") );

	AddTool(IDM_SOUNDMATMATRIX_REFRESHALL, BmpRefreshAll, *LocalizeUnrealEd("RefreshSoundMaterialMatrix"));
	AddTool(IDM_SOUNDMATMATRIX_SAVE, BmpSave, *LocalizeUnrealEd("Save"));
	
	AddSeparator();
	AddTool(IDM_SOUNDMATMATRIX_HITSOUNDS, BmpHitSounds, *LocalizeUnrealEd("HitSounds"));
	AddTool(IDM_SOUNDMATMATRIX_FOOTSTEPSOUNDS, BmpFootstepSounds, *LocalizeUnrealEd("FootstepSounds"));

	Realize();
}

SoundMaterialMatrixToolBar::~SoundMaterialMatrixToolBar()
{
}

/*-----------------------------------------------------------------------------
	SoundMaterialMatrixStatusBar.
-----------------------------------------------------------------------------*/

SoundMaterialMatrixStatusBar::SoundMaterialMatrixStatusBar( wxWindow* InParent, wxWindowID InID )
	: wxStatusBar( InParent, InID )
{
	INT Widths[2] = {-1, 150};

	SetFieldsCount(2, Widths);

	SetStatusText( *LocalizeUnrealEd("ObjectNone"), 0 );
}

SoundMaterialMatrixStatusBar::~SoundMaterialMatrixStatusBar()
{

}

/* ==========================================================================================================
	SoundMaterialMatrixTreeCtrl
========================================================================================================== */
IMPLEMENT_DYNAMIC_CLASS(SoundMaterialMatrixTreeCtrl,WxTreeCtrl)

//FArchive& operator<<(FArchive &Ar, wxTreeItemId &Id)
//{
//	return Ar;
//}

/** FSerializableObject interface */
void SoundMaterialMatrixTreeCtrl::Serialize( FArchive& Ar )
{
	//Ar << TreeMap;
}

/** Constructor */
SoundMaterialMatrixTreeCtrl::SoundMaterialMatrixTreeCtrl()
: KismetEditor(NULL)
{
}

/** Destructor */
SoundMaterialMatrixTreeCtrl::~SoundMaterialMatrixTreeCtrl()
{
}

/**
 * Initialize this control.  Must be the first function called after creation.
 *
 * @param	InParent	the window that opened this dialog
 * @param	InID		the ID to use for this dialog
 * @param	InEditor	pointer to the editor window that contains this control
 * @param   InStyle		Style of this tree control.
 */
void SoundMaterialMatrixTreeCtrl::Create( wxWindow* InParent, wxWindowID InID, SoundMaterialMatrix* InEditor, LONG InStyle)
{
	KismetEditor = InEditor;
	const UBOOL bSuccess = WxTreeCtrl::Create(InParent,InID,NULL, InStyle);
	check( bSuccess );
}

///**
// * Adds the root sequence of the specified level to the sequence tree, if a sequence exists for the specified level.
// *
// * @param	Level		The level whose root sequence should be added.  Can be NULL.
// * @param	RootId		The ID of the tree's root node.
// */
//void SoundMaterialMatrixTreeCtrl::AddLevelToTree(ULevel* Level, wxTreeItemId RootId)
//{
//	// Only add the level if it contains any sequences.
//	if ( Level && Level->GameSequences.Num() > 0 )
//	{
//		USequence* RootSeq = Level->GameSequences(0);
//		check(RootSeq); // Should not be able to open Kismet without the level having a Sequence.
//
//		const FString SeqTitle = FString::Printf(TEXT("%s - %s [%d]"),*RootSeq->GetOutermost()->GetName(),*RootSeq->ObjName, GetNumSequenceObjectsWithin(RootSeq));
//		const wxTreeItemId RootSeqId = AppendItem( RootId, *SeqTitle, 0, 0, new WxTreeObjectWrapper(RootSeq) );
//		TreeMap.Set( RootSeq, RootSeqId );
//
//		///AddChildren(RootSeq, RootSeqId);
//	}
//}

/**
 * Used to restore the expanded state of the tree items when the tree is refreshed
 */
void SoundMaterialMatrixTreeCtrl::FindExpandedNodes(wxTreeItemId NodeItem, TArray<FString>& NodeList, UBOOL GenerateList)
{
	// Return if the node is invalid or we're restoring the state of tree but the list of nodes is empty
	if (!NodeItem.IsOk() || (!GenerateList && (NodeList.Num() == 0)))
	{
		return;
	}

	// Note: this method does not take into account tree items with identical names
	
	FString NodeName;
	FString NodeText = FString(GetItemText(NodeItem));
	
	// Nodes are tracked via their name, but the name contains the number of items in the sequence,
	// which can change when the tree is refreshed, so that number needs to be removed from the name
	// before it can be used as an identifier
	if (appStrstr(*NodeText, TEXT(" [")))
	{
		NodeText.Split(TEXT(" ["), &NodeName, NULL);
	}
	else
	{
		NodeName = NodeText;
	}
	
	if (GenerateList)
	{
		if (IsExpanded(NodeItem))
		{
			NodeList.AddItem(NodeName);
		}
	}
	else // If we're not generating the list of expanded nodes, that means we're using said list to restore the state of the tree instead
	{
		if (NodeList.ContainsItem(NodeName))
		{
			Expand(NodeItem);
		}
	}

	wxTreeItemIdValue Cookie;
	wxTreeItemId ChildItem = GetFirstChild(NodeItem, Cookie);

	while (ChildItem.IsOk())
	{
		FindExpandedNodes(ChildItem, NodeList, GenerateList);

		ChildItem = GetNextChild(NodeItem, Cookie);
	}
}

/**
 * Repopulates the tree control with the sequences of all levels in the world.
 */
void SoundMaterialMatrixTreeCtrl::RefreshTree()
{
	// Save off a list of expanded tree items
	TArray<FString> ExpandedNodes;
	FindExpandedNodes(GetRootItem(), ExpandedNodes, TRUE);

	DeleteAllItems();
	//TreeMap.Empty();

	//@fixme localization
	wxTreeItemId RootId = AddRoot( TEXT("Maps"), 0, 0, NULL );

	// This should never be called while GWorld is a PIE world.
	check( !GIsPlayInEditorWorld );

	// Add the persistent level
//	AddLevelToTree( GWorld->PersistentLevel, RootId );

	// Add any streaming levels.
	AWorldInfo*	WorldInfo = GWorld->GetWorldInfo();
	for( INT LevelIndex = 0 ; LevelIndex < WorldInfo->StreamingLevels.Num() ; ++LevelIndex )
	{
		ULevelStreaming* CurStreamingLevel = WorldInfo->StreamingLevels( LevelIndex );
		if( CurStreamingLevel )
		{
//			AddLevelToTree( CurStreamingLevel->LoadedLevel, RootId );
		}
	}

	// Restore the expanded state of the tree
	FindExpandedNodes(RootId, ExpandedNodes, FALSE);
}

/**
 * Deletes all tree items from the list and clears the Sequence-ItemId map.
 */
void SoundMaterialMatrixTreeCtrl::ClearTree()
{
	//TreeMap.Empty();
	DeleteAllItems();
}
