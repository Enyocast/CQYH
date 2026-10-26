/*=============================================================================
	Kismet.h: Gameplay sequence editing
	Copyright 1998-2013 Epic Games, Inc. All Rights Reserved.
=============================================================================*/

#ifndef __TELEPORTGRAPH_H__
#define __TELEPORTGRAPH_H__

#include "UnrealEd.h"
#include "UnLinkedObjEditor.h"

//FIXME: change this to a configurable value maybe?
//#define KISMET_GRIDSIZE			8

class WxTeleportGraph : public WxLinkedObjEd, public FCallbackEventDevice
{
public:
	WxTeleportGraph( wxWindow* InParent, wxWindowID InID, const TCHAR* Title = TEXT("TeleportGraph") );
	virtual ~WxTeleportGraph();

	static wxFrame* OpenTeleportGraph(UBOOL bCreateNewWindow, class wxWindow* ParentWindow);

	// Initalization / Accessors
	virtual void		InitEditor();
	virtual void		CreateControls( UBOOL bTreeControl );

	/**
	 * @return Returns the name of the inherited class, so we can generate .ini entries for all LinkedObjEd instances.
	 */
	virtual const TCHAR* GetConfigName() const
	{
		return TEXT("TeleportGraph");
	}

	// LinkedObjEditor interface

	/**
	 * Creates the tree control for this linked object editor.  Only called if TRUE is specified for bTreeControl
	 * in the constructor.
	 *
	 * @param	TreeParent	the window that should be the parent for the tree control
	 */
	virtual void CreateTreeControl( wxWindow* TreeParent );

	void OnClose( wxCloseEvent& In );
	void OnSize(wxSizeEvent& In);

	virtual void DrawObjects(FViewport* Viewport, FCanvas* Canvas);

	virtual void UpdatePropertyWindow();

	virtual void EmptySelection();
	virtual void AddToSelection( UObject* Obj );
	virtual void RemoveFromSelection( UObject* Obj );
	virtual UBOOL IsInSelection( UObject* Obj ) const;
	virtual INT GetNumSelected() const;

protected:
	
	wxStatusBar* StatusBar;
	WxToolBar* ToolBar;
	// Currently selected SequenceObjects
	TArray<class UObject*> SelectedSeqObjs;
	class UGlobalMapInfo* GlobalMapSingleton;

	struct FMapTeleports* SelectedMap;
	struct FTeleportLink* SelectedLink;

	struct FMapTeleports* SelectedOrigMap;
	struct FTeleportObject* SelectedOrig;

	struct FMapTeleports* SelectedTargetMap;
	struct FTeleportObject* SelectedTarget;

	struct FMapTeleports* HighlightSelectedMap;
	struct FTeleportObject* HighlightSelectedTeleObj;
	struct FTeleportLink* HighlightSelectedLink;

	DECLARE_EVENT_TABLE()

	virtual FString GenerateNavigationHistoryString() const;
	virtual void EdHandleKeyInput(FViewport* Viewport, FName Key, EInputEvent Event);
	virtual void SetSelectedConnector( FLinkedObjectConnector& Connector );
	virtual void ClickedAnyObject(struct HAnyObjectProxy* proxy);
	virtual void CtrlClickedAnyObject(struct HAnyObjectProxy* proxy);
	virtual void HighlightAnyObject(struct HAnyObjectProxy* proxy);
	virtual void MoveSelectedObjects( INT DeltaX, INT DeltaY );
	virtual void DoubleClickedAnyObject(struct HAnyObjectProxy* proxy);
	virtual void ZoomSelectedAnyObject(FLOAT delta);

	void Draw_MapTeleports(struct FMapTeleports* map, FViewport* Viewport, FCanvas* Canvas, INT idx);

	FIntPoint ConvertToCanvasCoord( const FVector& worldLoc, FMapTeleports* map, const FVector2D& MapSz );

	void Draw_TeleportLink(struct FTeleportLink* lnk, FViewport* Viewport, FCanvas* Canvas, INT idx);

	struct FMapTeleports* GetMap(INT mapIdx) const;
	struct FMapTeleports* GetMap(const FString& mapName) const;

	void AddConnect(struct FMapTeleports* fromMap, struct FTeleportObject* fromOrig,
		struct FMapTeleports* toMap, struct FTeleportObject* toTarget);

	void MakePackageDirty();

	void OnButtonRefreshAllTeleportGraph( wxCommandEvent& In );
	void OnButtonSave( wxCommandEvent& In );
	void OnButtonDeleteSelected( wxCommandEvent& In );

	void DeleteSelected();

	void OnButtonExportServerMapInfos( wxCommandEvent& In );	
	void OnButtonImportServerMapInfos( wxCommandEvent& In );
	
};
//
///*-----------------------------------------------------------------------------
//	WxMBKismetConnectorOptions
//-----------------------------------------------------------------------------*/
//
//class WxMBKismetConnectorOptions : public wxMenu
//{
//public:
//	wxMenu *BreakLinkMenu;
//	WxMBKismetConnectorOptions(WxTeleportGraph* SeqEditor);
//	~WxMBKismetConnectorOptions();
//};
//
///*-----------------------------------------------------------------------------
//	WxMBKismetObjectOptions
//-----------------------------------------------------------------------------*/
//
//class WxMBKismetObjectOptions : public wxMenu
//{
//public:
//	WxMBKismetObjectOptions(WxTeleportGraph* SeqEditor);
//	~WxMBKismetObjectOptions();
//
//	wxMenu *NewVariableMenu;
//};

#endif	// __KISMET_H__
