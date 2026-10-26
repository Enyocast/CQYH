
#ifndef __GRIDEDITOR_H__
#define __GRIDEDITOR_H__

#include "UnrealEd.h"
#include "UnTerrain.h"
#include "TrackableWindow.h"
#include "ICommandX.h"

class wxButton;
class wxBitmapButton;
class wxStaticBitmap;
class wxStaticText;
class wxComboBox;
class wxCheckBox;
class wxSpinCtrl;
class wxSlider;

extern class FEdModeGridEditing* g_gridEditMode;

enum EPaintGridBlockingType
{
	// "不可移动" "不可跳越" "挡Missile" "挡Bullet" "不阻挡角色"
	EPGBT_BlockMove = 0,
	EPGBT_BlockLeap,
	EPGBT_BlockMissile,
	EPGBT_BlockBullet,
	EPGBT_NotBlockChar,
	EPGBT_CanStallArea,
	EPGBT_NotType,
};

/*-----------------------------------------------------------------------------
	WxGridEditor
-----------------------------------------------------------------------------*/
/**
 *	WxGridEditor
 */
class WxGridEditor
	: public wxFrame
	, public ICommandXExecuteObserver
{
protected:
	wxPanel* _GridEditorPanel;
	wxStaticText* _BrushSizeLabel;
	wxRadioBox* _BrushTypeRadio;
	wxButton* _UndoBtn;
	wxButton* _RedoBtn;

	/** Hides the terrain editor and changes the editor mode to camera mode. */
	void OnClose( wxCloseEvent& In );

	/** Updates the terrain wireframe color dialog box */
	void OnActivate(wxActivateEvent& In);

	void HideAndChangeMode();

	virtual void OnCommandExecuted(const CommandHistory* cmdHist);
	void UpdateUI();

public:
	/**
	 *	Constructor
	 */
	WxGridEditor(wxWindow* InParent);

	/**
	 *	Destructor
	 */
	~WxGridEditor();

	virtual void Create( INT DockID, const TCHAR* FriendlyName, wxWindow* Parent );


	DECLARE_EVENT_TABLE()

	void OnUndo( wxCommandEvent& In );
	void OnRedo( wxCommandEvent& In );
	void OnBrushType( wxCommandEvent& In );
	void OnBrushSizeUpdate( wxScrollEvent& In );
};



/*------------------------------------------------------------------------------
	Grid Editing.
------------------------------------------------------------------------------*/

/**
 * Allows editing of grid attribute
 */
class FEdModeGridEditing : public FEdMode
{
public:
	FEdModeGridEditing();

	virtual const FToolSettings* GetSettings() const;

	virtual void Enter();
	virtual void Exit();
	
	virtual UBOOL AllowWidgetMove()	{ return FALSE;	}


	virtual void Render(const FSceneView* View,FViewport* Viewport,FPrimitiveDrawInterface* PDI);

	virtual UBOOL InputKey(FEditorLevelViewportClient* ViewportClient,FViewport* Viewport,FName Key,EInputEvent Event);
	virtual UBOOL MouseMove(FEditorLevelViewportClient* ViewportClient,FViewport* Viewport,INT x, INT y);

	UBOOL UpdateBrushLocation( FEditorLevelViewportClient* ViewportClient, INT x, INT y );

	virtual UBOOL CapturedMouseMove( FEditorLevelViewportClient* InViewportClient, FViewport* InViewport, INT InMouseX, INT InMouseY );

	bool CanUndo();
	bool CanRedo();

	void Undo();
	void Redo();

	class CommandHistory* GetCommandHistory();

	void SetBrushType(EPaintGridBlockingType brushType) { _CurrentBrushType = brushType; }
	void SetBrushSize(INT val) { _BrushSize = val; }

protected:

	UBOOL			bPerToolSettings;
	UTexture2D*		BallTexture;

	class CommandHistory* _CmdHistory;
	IActiveEditPtr	_ActiveEdit;
	bool _LeftMouseDown;
	bool _RightMouseDown;
	EPaintGridBlockingType _CurrentBrushType;
	INT _BrushSize;

	UBOOL _IsBrushTraceValid;
	FVector _BrushLocation;
	FVector2D _BrushOnServer;
	float     _Length;
	//TArray<float> _BrushHeight;

	FCriticalSection	BrushFinishSection;


	void BeginActiveEdit(IActiveEditPtr activeEdit);
	void CommitActiveEdit();
	bool IsActiveEditing() const;
	void ExecuteActiveEdit(const Any& contex);
	void PaintGridBlockAttribute(INT val);
	bool IsGridMatchBrushType(GRID_DATA* gridData, INT val) const;
	INT SetGridMatchBrushType(GRID_DATA* gridData, INT val);
	UBOOL RayCastServerGrid( INT &x, INT &y, float &OutZ );
	FColor GetBrushTypeColor( EPaintGridBlockingType BrushType );
};

#endif // __GRIDEDITOR_H__
