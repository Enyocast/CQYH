#ifndef __WXTELEPORTGRAPHTREECTRL_H__
#define __WXTELEPORTGRAPHTREECTRL_H__

#include "UnrealEd.h"
#include "UnLinkedObjEditor.h"

/*-----------------------------------------------------------------------------
	WxTeleportGraphToolBar
-----------------------------------------------------------------------------*/

class WxTeleportGraphToolBar : public WxToolBar
{
public:
	WxTeleportGraphToolBar( wxWindow* InParent, wxWindowID InID );
	~WxTeleportGraphToolBar();

	WxBitmap BmpRefreshAll, BmpDelete, BmpSave, BmpExport, BmpImport;
// 	WxBitmap ParentSequenceB;
// 	WxMaskedBitmap RenameSequenceB, HideB, ShowB, CurvesB, SearchB, CreateSeqObjB, ZoomToFitB, UpdateB, OpenB, ClearBreakPointsB;

	DECLARE_EVENT_TABLE()
};

/*-----------------------------------------------------------------------------
	WxTeleportGraphStatusBar
-----------------------------------------------------------------------------*/

class WxTeleportGraphStatusBar : public wxStatusBar
{
public:
	WxTeleportGraphStatusBar( wxWindow* InParent, wxWindowID InID);
	~WxTeleportGraphStatusBar();
};

/* ==========================================================================================================
	WxTeleportGraphTreeCtrl
========================================================================================================== */
/**
 * This tree control displays the list of sequences opened for edit
 */ 
class WxTeleportGraphTreeCtrl : public WxTreeCtrl, public FSerializableObject
{
	DECLARE_DYNAMIC_CLASS(WxTeleportGraphTreeCtrl)

public:
	/** Default constructor for use in two-stage dynamic window creation */
	WxTeleportGraphTreeCtrl();
	virtual ~WxTeleportGraphTreeCtrl();



	/**
	 * Initialize this control when using two-stage dynamic window creation.  Must be the first function called after creation.
	 *
	 * @param	InParent	the window that opened this dialog
	 * @param	InID		the ID to use for this dialog
	 * @param	InEditor	pointer to the editor window that contains this control
	 * @param   InStyle		Style of this tree control.
	 */
	void Create( wxWindow* InParent, wxWindowID InID, class WxTeleportGraph* InEditor, LONG InStyle = wxTR_HAS_BUTTONS );
private:
	using WxTreeCtrl::Create;		// Hide parent implementation

	/**
	 * Used to restore the expanded state of the tree items when the tree is refreshed
	 */
	void FindExpandedNodes(wxTreeItemId NodeItem, TArray<FString>& NodeList, UBOOL GenerateList);
	
public:

	/**
	 * Repopulates the tree control with the sequences of all levels in the world.
	 */
	virtual void RefreshTree();

	/**
	 * Deletes all tree items from the list and clears the Sequence-ItemId map.
	 */
	void ClearTree();

	/**
	 * Recursively adds all subsequences of the specified sequence to the tree control.
	 */
// 	virtual void AddChildren( USequence* ParentSeq, wxTreeItemId ParentId );

	/**
	 * De/selects the tree item corresponding to the specified object
	 *
	 * @param	SeqObj		the sequence object to select in the tree control
	 * @param	bSelect		whether to select or deselect the sequence
	 *
	 * @param	True if the specified sequence object was found
	 */
// 	virtual UBOOL SelectObject( USequenceObject* SeqObj, UBOOL bSelect=TRUE );

	/** FSerializableObject interface */
	virtual void Serialize( FArchive& Ar );

protected:
	/** the kismet editor window that contains this tree control */
	class WxTeleportGraph* KismetEditor;

	///** maps the sequence objects to their corresponding tree id */
	//TMap<USequenceObject*, wxTreeItemId> TreeMap;

	///**
	// * Adds the root sequence of the specified level to the sequence tree, if a sequence exists for the specified level.
	// *
	// * @param	Level		The level whose root sequence should be added.  Can be NULL.
	// * @param	RootId		The ID of the tree's root node.
	// */
	//void AddLevelToTree(ULevel* Level, wxTreeItemId RootId);

private:
	/** Hide this constructor */
	WxTeleportGraphTreeCtrl( wxWindow* parent, wxWindowID id, wxMenu* InMenu ) {}
};

#endif