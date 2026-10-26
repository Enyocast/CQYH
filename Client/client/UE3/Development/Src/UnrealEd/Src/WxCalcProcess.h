#pragma once

#include "UnrealEd.h"
#include "UnLinkedObjEditor.h"
#include "EngineSequenceClasses.h"
//#include "UnObjBas.h"
#include "../../MMOGame/Inc/MMOGameClasses.h"

class WxCalcProcess : public WxLinkedObjEd
{
public:
	WxCalcProcess(wxWindow* InParent, wxWindowID InID, const TCHAR* Title = TEXT("CalcProcess"));
	virtual ~WxCalcProcess(void);

	static void OpenEditor(UBOOL bCreateNewWindow, class wxWindow* ParentWindow, USeqAct_Modifier* SM= NULL);

	// Initalization / Accessors
	virtual void		InitEditor();
	virtual void		CreateControls( UBOOL bTreeControl );
	void LoadModifier(USeqAct_Modifier* SM);

	virtual void OpenNewObjectMenu();
	virtual const TCHAR* GetConfigName() const
	{
		return TEXT("CalcProcess");
	}
	void OnClose( wxCloseEvent& In );
	void OnSize(wxSizeEvent& In);
	virtual void DrawObjects(FViewport* Viewport, FCanvas* Canvas);
	virtual void MoveSelectedObjects( INT DeltaX, INT DeltaY );
	virtual INT GetNumSelected() const;
	virtual void SetSelectedConnector( FLinkedObjectConnector& Connector );
	FIntPoint GetSelectedConnLocation(FCanvas* Canvas);
	virtual void MakeConnectionToConnector( FLinkedObjectConnector& Connector );
	void MakeLogicConnection(class USequenceOp* OutOp, INT OutConnIndex, class USequenceOp* InOp, INT InConnIndex);
	void ClickedLine(FLinkedObjectConnector &Src, FLinkedObjectConnector &Dest);

	virtual UBOOL IsInSelection( UObject* Obj ) const;
	virtual void RemoveFromSelection( UObject* Obj );
	virtual void AddToSelection( UObject* Obj );
	virtual void EmptySelection();
	virtual void UpdatePropertyWindow();
	virtual void DeleteSelected(UBOOL bSilent=FALSE);
	//virtual void EdHandleKeyInput(FViewport* Viewport, FName Key, EInputEvent Event);

protected:

	//wxStatusBar* StatusBar;
	//WxToolBar* ToolBar;

	//CalcProcessState* ActiveEditState;

	//typedef std::map<int, CalcProcessState*> EditStateMap;
	//TArray<CalcProcessState*> EditStates;
	TArray<USeqAct_Modifier*> ModifierDrawList;
	USeqAct_Modifier*	RootModifier;
	
	// Currently selected SequenceObjects
	TArray<class USequenceObject*> SelectedSeqObjs;

	class USequenceOp* ConnSeqOp;
	INT ConnType;
	INT ConnIndex;
	//EditStateMap EditStates;

	//UPackage* GamePlayDataPackage;
	//class UGamePlayDataManager* DataManager;

	//void ActiveState(INT StateID);

	DECLARE_EVENT_TABLE()

	//virtual FString GenerateNavigationHistoryString() const;
	virtual void EdHandleKeyInput(FViewport* Viewport, FName Key, EInputEvent Event);
	//virtual void SetSelectedConnector( FLinkedObjectConnector& Connector );
	//virtual void ClickedAnyObject(struct HAnyObjectProxy* proxy);
	//virtual void CtrlClickedAnyObject(struct HAnyObjectProxy* proxy);
	//virtual void HighlightAnyObject(struct HAnyObjectProxy* proxy);
	//virtual void MoveSelectedObjects( INT DeltaX, INT DeltaY );
	//virtual void DoubleClickedAnyObject(struct HAnyObjectProxy* proxy);


	//void OnButtonRefreshAllData( wxCommandEvent& In );
	//void OnButtonSave( wxCommandEvent& In );
	//void OnButtonHitSounds( wxCommandEvent& In );
	//void OnButtonFootstepSounds( wxCommandEvent& In );
};

