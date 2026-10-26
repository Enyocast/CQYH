/*=============================================================================
	Kismet.h: Gameplay sequence editing
	Copyright 1998-2013 Epic Games, Inc. All Rights Reserved.
=============================================================================*/

#ifndef __SOUNDMATERIALMATRIX_H__
#define __SOUNDMATERIALMATRIX_H__

#include "UnrealEd.h"
#include "UnLinkedObjEditor.h"
#include <map>

//FIXME: change this to a configurable value maybe?
//#define KISMET_GRIDSIZE			8

class SoundMaterialMatrix : public WxLinkedObjEd
{
public:
	SoundMaterialMatrix( wxWindow* InParent, wxWindowID InID, const TCHAR* Title = TEXT("SoundMaterialMatrix") );
	virtual ~SoundMaterialMatrix();

	static void OpenEditor(UBOOL bCreateNewWindow, class wxWindow* ParentWindow);

	// Initalization / Accessors
	virtual void		InitEditor();
	virtual void		CreateControls( UBOOL bTreeControl );

	/**
	 * @return Returns the name of the inherited class, so we can generate .ini entries for all LinkedObjEd instances.
	 */
	virtual const TCHAR* GetConfigName() const
	{
		return TEXT("SoundMaterialMatrix");
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

	void MakePackageDirty();

	class UGamePlayDataManager* GetDataManager();

	void SetObjectToPropertyWindow(UObject* object);

protected:
	
	wxStatusBar* StatusBar;
	WxToolBar* ToolBar;

	class SoundMaterialEditState* ActiveEditState;

	typedef std::map<int, SoundMaterialEditState*> EditStateMap;
	EditStateMap EditStates;

	UPackage* GamePlayDataPackage;
	class UGamePlayDataManager* DataManager;

	void ActiveState(INT StateID);

	DECLARE_EVENT_TABLE()

	virtual FString GenerateNavigationHistoryString() const;
	virtual void EdHandleKeyInput(FViewport* Viewport, FName Key, EInputEvent Event);
	virtual void SetSelectedConnector( FLinkedObjectConnector& Connector );
	virtual void ClickedAnyObject(struct HAnyObjectProxy* proxy);
	virtual void CtrlClickedAnyObject(struct HAnyObjectProxy* proxy);
	virtual void HighlightAnyObject(struct HAnyObjectProxy* proxy);
	virtual void MoveSelectedObjects( INT DeltaX, INT DeltaY );
	virtual void DoubleClickedAnyObject(struct HAnyObjectProxy* proxy);


	void OnButtonRefreshAllData( wxCommandEvent& In );
	void OnButtonSave( wxCommandEvent& In );
	void OnButtonHitSounds( wxCommandEvent& In );
	void OnButtonFootstepSounds( wxCommandEvent& In );
};

#endif	// __SOUNDMATERIALMATRIX_H__
