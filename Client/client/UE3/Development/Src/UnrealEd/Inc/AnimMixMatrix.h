/*=============================================================================
	hemu@snda 120416
	动画混合参数表，用于播放连击动作等情况下动作的平滑返回播放
=============================================================================*/

#ifndef __AnimMixMatrix_H__
#define __AnimMixMatrix_H__

#include "UnrealEd.h"
#include "UnLinkedObjEditor.h"
#include <map>

//动画混合参数表编辑总界面，用于数据，按键交互响应
class AnimMixMatrix : public WxLinkedObjEd
{
public:
	AnimMixMatrix( wxWindow* InParent, wxWindowID InID, const TCHAR* Title = TEXT("AnimMixMatrix") );
	virtual ~AnimMixMatrix();

	static void OpenEditor(UBOOL bCreateNewWindow, class wxWindow* ParentWindow);

	// Initalization / Accessors
	virtual void		InitEditor();
	virtual void		CreateControls( UBOOL bTreeControl );
	virtual const TCHAR* GetConfigName() const
	{
		return TEXT("AnimMixMatrix");
	}
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
	void Save();
protected:
	
	wxStatusBar* StatusBar;
	WxToolBar* ToolBar;

	class AnimMixEditState* ActiveEditState;

	typedef std::map<int, AnimMixEditState*> EditStateMap;
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
};

#endif	// __AnimMixMatrix_H__
