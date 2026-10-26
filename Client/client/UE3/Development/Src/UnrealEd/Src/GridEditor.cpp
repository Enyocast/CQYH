/**
 *	TerrainEditor.cpp
 *	Terrain editing dialog
 *
 *	Copyright 1998-2013 Epic Games, Inc. All Rights Reserved.
 */

#include "UnrealEd.h"
#include "Factories.h"
#include "EngineMaterialClasses.h"
#include "FileHelpers.h"
#include "PropertyWindow.h"
#include "GridEditor.h"

#include "ICommandX.h"

#define CLIENT_GRID_WIDTH  128.0f
#define CLIENT_GRID_HEIGHT  128.0f

extern CEditorScene g_ReviseScene;
extern void DrawWireBoxByMatrix(FPrimitiveDrawInterface* PDI,const FMatrix& M,FColor Color,BYTE DepthPriority);

class FEdModeGridEditing* g_gridEditMode = 0;


class Cmd_PaintGridBlocking : public ICommandX
{
	GRID_DATA* _GridData;
	EPaintGridBlockingType _BlockType;
	unsigned int _Val;
public:

	Cmd_PaintGridBlocking(GRID_DATA* gridData, EPaintGridBlockingType blkType, unsigned int val)
		: _GridData(gridData)
		, _BlockType(blkType)
		, _Val(val)
	{
	}

	virtual ICommandXPtr Execute()
	{
		unsigned int oldVal = 0;
		
		switch(_BlockType)
		{
		case EPGBT_BlockMove:
			oldVal = _GridData->bBlockMove;
			_GridData->bBlockMove = _Val;
			break;

		case EPGBT_BlockLeap:
			oldVal = _GridData->bBlockLeap;
			_GridData->bBlockLeap = _Val;
			break;

		case EPGBT_BlockMissile:
			oldVal = _GridData->bBlockMissile;
			_GridData->bBlockMissile = _Val;
			break;

		case EPGBT_BlockBullet:
			oldVal = _GridData->bBlockBullet;
			_GridData->bBlockBullet = _Val;
			break;

		case EPGBT_NotBlockChar:
			oldVal = _GridData->bNotBlockChar;
			_GridData->bNotBlockChar = _Val;
			break;
		case EPGBT_CanStallArea:
			oldVal = _GridData->uStallLevel;
			_GridData->uStallLevel = _Val;
			break;
		}

		return new Cmd_PaintGridBlocking(_GridData, _BlockType, oldVal);
	}
};

/*-----------------------------------------------------------------------------
	WxGridEditor
-----------------------------------------------------------------------------*/
/** Event map													*/
BEGIN_EVENT_TABLE(WxGridEditor, wxFrame)
	EVT_ACTIVATE(WxGridEditor::OnActivate)
	EVT_CLOSE( WxGridEditor::OnClose )
END_EVENT_TABLE()

/**
 *	WxGridEditor
 */
/**
 *	Constructor
 */
WxGridEditor::WxGridEditor(wxWindow* InParent) :
//	  wxWindow(InParent, -1, wxDefaultPosition, wxDefaultSize)
	  wxFrame(InParent, wxID_ANY, wxString(*LocalizeUnrealEd("GridEdit_Title")))
{
	Create(-1, TEXT("GridEditorFrame"), InParent);

	if(g_gridEditMode)
	{
		g_gridEditMode->GetCommandHistory()->AddCommandExecuteObserver(this);
	}
}

/**
 *	Destructor
 */
WxGridEditor::~WxGridEditor()
{
}

void WxGridEditor::Create( INT DockID, const TCHAR* FriendlyName, wxWindow* Parent )
{
	verify(wxFrame::Create(NULL,-1, FriendlyName, wxDefaultPosition, wxSize(121, 313)));

	_GridEditorPanel =
		wxXmlResource::Get()->LoadPanel(
		this,								// Parent window
		TEXT( "ID_GridEdit" ) );	// Object name
	check( _GridEditorPanel != NULL );
	_GridEditorPanel->Fit();

// 	wxImage	TempImage;
// 	TempImage.LoadFile(*FString::Printf(TEXT("%swxres\\TerrainProp_Properties.bmp"), *GetEditorResourcesDir()), wxBITMAP_TYPE_BMP);
// 	TempBitmap = new WxBitmap(TempImage);




#undef  AddWxEventHandler
#undef	AddWxListEventHandler
#undef	AddNotebookEventHandler
#undef	AddWxSpinEventHandler
#undef	AddWxScrollEventHandler

#define AddWxEventHandler( id, event, func )\
	{\
	wxEvtHandler* eh = GetEventHandler();\
	eh->Connect( id, event, wxCommandEventHandler(func) );\
	}

#define AddWxListEventHandler( id, event, func )\
	{\
	wxEvtHandler* eh = GetEventHandler();\
	eh->Connect( id, event, wxListEventHandler(func) );\
	}

#define AddNotebookEventHandler( id, event, func )\
	{\
	wxEvtHandler* eh = GetEventHandler();\
	eh->Connect( id, event, wxNotebookEventHandler(func) );\
	}

#define AddWxSpinEventHandler( id, event, func )\
	{\
	wxEvtHandler* eh = GetEventHandler();\
	eh->Connect( id, event, wxSpinEventHandler(func) );\
	}

#define AddWxScrollEventHandler( id, event, func )\
	{\
	wxEvtHandler* eh = GetEventHandler();\
	eh->Connect( id, event, wxScrollEventHandler(func) );\
	}

	_BrushSizeLabel = static_cast< wxStaticText* >( FindWindow( XRCID( "brush_txt_size" ) ) );
	check( _BrushSizeLabel != NULL );

	_BrushTypeRadio = static_cast< wxRadioBox* >( FindWindow( XRCID( "radio_brush_type" ) ) );
	check( _BrushTypeRadio != NULL );

	_UndoBtn = static_cast< wxButton* >( FindWindow( XRCID( "toolbar_undo" ) ) );
	_RedoBtn = static_cast< wxButton* >( FindWindow( XRCID( "toolbar_redo" ) ) );

	AddWxEventHandler( XRCID( "radio_brush_type" ), wxEVT_COMMAND_RADIOBOX_SELECTED, WxGridEditor::OnBrushType );
	AddWxScrollEventHandler( XRCID( "slider_brush_size" ), wxEVT_SCROLL_CHANGED, WxGridEditor::OnBrushSizeUpdate );

	AddWxEventHandler( XRCID( "toolbar_undo" ), wxEVT_COMMAND_BUTTON_CLICKED, WxGridEditor::OnUndo );
	AddWxEventHandler( XRCID( "toolbar_redo" ), wxEVT_COMMAND_BUTTON_CLICKED, WxGridEditor::OnRedo );

	_UndoBtn->Enable(false);
	_RedoBtn->Enable(false);

	HWND WindowHnd = (HWND)this->GetHandle();
	if ( WindowHnd )
	{
		SetWindowPos( WindowHnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE );
		//SetWindowPos( WindowHnd, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE );
	}

}


/** Hides the terrain editor and changes the editor mode to camera mode. */
void WxGridEditor::HideAndChangeMode()
{
	// Hide the terrain editor.
	Show( false );

	// Change over to camera mode.
	wxCommandEvent StubEvent;
	check(GApp);
	if (GApp->EditorFrame)
	{
		if (GApp->EditorFrame->ButtonBar)
		{
			if (GApp->EditorFrame->ButtonBar->ButtonGroups(0))
			{
				GApp->EditorFrame->ButtonBar->ButtonGroups(0)->OnModeCamera(StubEvent);
			}
		}
	}
}

/** Hides the terrain editor and changes the editor mode to camera mode. */
void WxGridEditor::OnClose( wxCloseEvent& In )
{
	HideAndChangeMode();
}

/** Updates the terrain wireframe color dialog box */
void WxGridEditor::OnActivate(wxActivateEvent& In)
{
}

void WxGridEditor::OnBrushType( wxCommandEvent& In )
{
	g_gridEditMode->SetBrushType((EPaintGridBlockingType)_BrushTypeRadio->GetSelection());
}

void WxGridEditor::OnBrushSizeUpdate( wxScrollEvent& In )
{
	g_gridEditMode->SetBrushSize(In.GetPosition());
	wxString str;
	str << In.GetPosition();
	_BrushSizeLabel->SetLabel(str);
}

void WxGridEditor::OnUndo( wxCommandEvent& In )
{
	if(g_gridEditMode->GetCommandHistory()->IsUndoEnable())
	{
		g_gridEditMode->GetCommandHistory()->Undo();
	}
}

void WxGridEditor::OnRedo( wxCommandEvent& In )
{
	if(g_gridEditMode->GetCommandHistory()->IsRedoEnable())
	{
		g_gridEditMode->GetCommandHistory()->Redo();
	}
}

void WxGridEditor::OnCommandExecuted( const CommandHistory* cmdHist )
{
	_UndoBtn->Enable(cmdHist->IsUndoEnable());
	_RedoBtn->Enable(cmdHist->IsRedoEnable());
}

void WxGridEditor::UpdateUI()
{

}



/*------------------------------------------------------------------------------
	Grid Editing.
------------------------------------------------------------------------------*/

void CoverXYToServerGrid( float &X, float &Y )
{
	ConvertXYToServer( X, Y  );
	X = floor( X * POINT_PER_CM / GRID_WIDTH );
	Y = floor( Y * POINT_PER_CM / GRID_WIDTH );
}

FVector2D CoverServerGridToXY( FVector2D &GridIndx )
{
	FVector2D vTemp = ( GridIndx + FVector2D( .5f , .5f ) ) * GRID_WIDTH / POINT_PER_CM;
	ConvertXYToClient( vTemp.X, vTemp.Y );
	return vTemp;
};

FEdModeGridEditing::FEdModeGridEditing()
	: _LeftMouseDown(false)
	, _RightMouseDown(false)
	, _CurrentBrushType(EPGBT_BlockMove)
	, _BrushSize(2)
	, _IsBrushTraceValid(FALSE)
	, _CmdHistory(0)
{
	g_gridEditMode = this;

	ID = EM_GridEdit;
	Desc = TEXT("Grid Editing");
	bPerToolSettings = FALSE;
// 	bShowBallAndSticks = TRUE;
// 	ModeColor = FColor(255,255,255);
// 	CurrentTerrain = NULL;
// 
// 	ToolColor = FLinearColor(1.0f, 0.0f, 0.0f);
// 	MirrorColor = FLinearColor(1.0f, 0.0f, 1.0f);

	BallTexture = (UTexture2D*)UObject::StaticLoadObject(UTexture2D::StaticClass(), NULL, 
		TEXT("EditorMaterials.TerrainLayerBrowser.TerrainBallImage"),NULL,LOAD_None,NULL);

	//Settings = new FGridEditToolSettings;

}

extern bool g_bShowGrid;
extern bool g_bShowGridForeGround;


void FEdModeGridEditing::Enter()
{
	FEdMode::Enter();

	GEngine->Exec(TEXT("LoadGrid"));
	g_bShowGrid = true;
	g_bShowGridForeGround = true;
}

void FEdModeGridEditing::Exit()
{
	FEdMode::Exit();
	BrushFinishSection.Lock();
	g_ReviseScene.Save();
	BrushFinishSection.Unlock();
	g_bShowGrid = false;
	g_bShowGridForeGround = false;


	_ActiveEdit = 0;

	if(_CmdHistory)
	{
		delete _CmdHistory;
		_CmdHistory = NULL;
	}
}


const FToolSettings* FEdModeGridEditing::GetSettings() const
{
	if( bPerToolSettings )
	{
		return ((FEdModeGridEditing*)GetCurrentTool())->GetSettings();
	}
	else
	{
		return Settings;
	}
}
extern int g_nCenterZoneX;
extern int g_nCenterZoneY;
extern int g_nRange;

FColor FEdModeGridEditing::GetBrushTypeColor( EPaintGridBlockingType BrushType )
{
	switch( BrushType )
	{
	case EPGBT_BlockMove:
		return FColor(255, 0, 255);
	case  EPGBT_BlockBullet:
		return FColor(255, 255, 0);
	case  EPGBT_BlockMissile:
		return FColor(128, 128, 128 );
	case  EPGBT_BlockLeap:
		return FColor( 0, 0, 0 );
	case EPGBT_NotBlockChar:
		return FColor( 0, 255, 0 );
	case EPGBT_CanStallArea:
		return FColor( 0, 0, 255 );
	}
	return FColor( 255,255,255);
}

EPaintGridBlockingType GridHasAnyType( GRID_DATA* pData )
{
	if ( pData->bBlockMove )
		return EPGBT_BlockMove;

	if ( pData->bBlockLeap )
		return EPGBT_BlockLeap;

	if ( pData->bBlockBullet )
		return EPGBT_BlockBullet;

	if ( pData->bNotBlockChar )
		return EPGBT_NotBlockChar;

	if ( pData->bBlockMissile )
		return EPGBT_BlockMissile;

	if ( pData->uStallLevel )
		return EPGBT_CanStallArea;

	return EPGBT_NotType;
}
void FEdModeGridEditing::Render(const FSceneView* View,FViewport* Viewport,FPrimitiveDrawInterface* PDI)
{
	FEdMode::Render(View,Viewport,PDI);

	if(_IsBrushTraceValid)
	{
		FVector vTemp2;
		FMatrix rotationM, translateM, finalM;
		INT		brushSq = (_BrushSize - 1) * (_BrushSize - 1);
		FVector2D	vTemp, ViewOrigin( -View->ViewMatrix.M[3][1], -View->ViewMatrix.M[3][0] );
		FRotator	rotation = FRotator::MakeFromEuler( FVector( 0, 0, FEditorConstraints::RotationAngle ) );
		FVector		v1( 0, .8f, 0 ), v2( 0, -.8f, 0 ), v3( .8f, 0, 0 ), v4( -.8f, 0, 0 );

		float fCenterZoneX = (g_nCenterZoneX * ZONE_WIDTH + ZONE_WIDTH / 2) / POINT_PER_CM;
		float fCenterZoneY = (g_nCenterZoneY * ZONE_WIDTH + ZONE_WIDTH / 2) / POINT_PER_CM;
		ConvertXYToServer(fCenterZoneX, fCenterZoneY);
		INT32 nCenterZoneX = fCenterZoneX * POINT_PER_CM / ZONE_WIDTH;
		INT32 nCenterZoneY = fCenterZoneY * POINT_PER_CM / ZONE_WIDTH;
		bool  hasGrid   = false;
		bool  bdrawling = true;
		FColor color;

		translateM.SetIdentity();
		rotationM.SetIdentity();
		rotationM = FRotationMatrix( rotation );
		CoverXYToServerGrid( ViewOrigin.X, ViewOrigin.Y );
		translateM.M[0][0] = translateM.M[1][1] = translateM.M[2][2] = CLIENT_GRID_WIDTH*0.5f;
		finalM = rotationM * translateM;
		translateM.M[0][0] = translateM.M[1][1] = translateM.M[2][2] = 0.5f;
		translateM = translateM * finalM;
		{
			v1 = finalM.TransformFVector( v1 );
			v2 = finalM.TransformFVector( v2 );
			v3 = finalM.TransformFVector( v3 );
			v4 = finalM.TransformFVector( v4 );
		}

		BrushFinishSection.Lock();
		for ( INT x = -g_nRange; x <= g_nRange ; ++x )
		{
			for ( INT y = -g_nRange; y <= g_nRange; ++y )
			{
				float ZoneBeginX = ( nCenterZoneX + x ) * ZONE_WIDTH / GRID_WIDTH;
				float ZoneBeginY = ( nCenterZoneY + y ) * ZONE_WIDTH / GRID_WIDTH;
				{
					for (int nGridX = 0; nGridX < GRID_PER_ZONE; nGridX++)
					{
						for (int nGridY = 0; nGridY < GRID_PER_ZONE; nGridY++)
						{
							hasGrid   = false;
							bdrawling = true;
							vTemp.X = ZoneBeginX + nGridX;
							vTemp.Y = ZoneBeginY + nGridY;
							GRID_DATA* pData = g_ReviseScene.GetGroundGrid( ( ZoneBeginX + nGridX ) * GRID_WIDTH,
								( ZoneBeginY + nGridY ) * GRID_WIDTH );

							do{
								if ( pData )
								{
									
									if ( IsGridMatchBrushType( pData, 1 ) )
									{
										hasGrid = true;
										color   = GetBrushTypeColor( _CurrentBrushType );
										vTemp   = CoverServerGridToXY( vTemp );
										vTemp2.X = vTemp.X;
										vTemp2.Y = vTemp.Y;
										vTemp2.Z = ( pData->uLowLayer + pData->uHighLayer ) * 0.5f * GRID_LAYER_HEIGHT / POINT_PER_CM ;
										break;
										
									}
									else
									{
										EPaintGridBlockingType curType = GridHasAnyType( pData );
										if ( curType != EPGBT_NotType || !hasGrid )
										{
											hasGrid = true;
											bdrawling = curType != EPGBT_NotType;
											color   = GetBrushTypeColor( curType );
											vTemp   = CoverServerGridToXY( vTemp );
											vTemp2.X = vTemp.X;
											vTemp2.Y = vTemp.Y;
											vTemp2.Z = ( pData->uLowLayer + pData->uHighLayer ) * 0.5f * GRID_LAYER_HEIGHT / POINT_PER_CM ;
										}
										
									}
									
								}
								else
									break;
							}while( ( pData = g_ReviseScene.GetGridByIndex( vTemp.X * GRID_WIDTH, vTemp.Y * GRID_WIDTH, pData->uNextGrid ) ) != NULL );

							if ( hasGrid )
							{
								if( bdrawling )
								{
									PDI->DrawLine( v1 + vTemp2, v2 +vTemp2, color, SDPG_UnrealEdForeground );
									PDI->DrawLine( v3 + vTemp2, v4 +vTemp2, color, SDPG_UnrealEdForeground );
								}
								else
								{
									translateM.M[3][0] = vTemp2.X;
									translateM.M[3][1] = vTemp2.Y;
									translateM.M[3][2] = vTemp2.Z;
									DrawWireBoxByMatrix(PDI, translateM, color, SDPG_UnrealEdForeground);
								}
							}

						}
					}
				}
				
			}
		}
		BrushFinishSection.Unlock();

		for (INT x = -_BrushSize + 1; x < _BrushSize; ++x)
		{
			for (INT y = -_BrushSize + 1; y < _BrushSize; ++y)
			{
				INT d = x * x + y * y;
				if(d <= brushSq)
				{
					vTemp = _BrushOnServer + FVector2D( x, y );
					vTemp = CoverServerGridToXY( vTemp );
					finalM.M[3][0] = vTemp.X;
					finalM.M[3][1] = vTemp.Y;
					finalM.M[3][2] = _BrushLocation.Z;
					DrawWireBoxByMatrix(PDI, finalM, FColor(255, 0, 0), SDPG_UnrealEdForeground);
				}
			}
		}
	}
}

UBOOL FEdModeGridEditing::InputKey( FEditorLevelViewportClient* ViewportClient,FViewport* Viewport,FName Key,EInputEvent Event )
{
	if(IsCtrlDown(Viewport) && (Event == IE_Pressed) && (Key == KEY_LeftMouseButton))
	{
		_LeftMouseDown = true;
		CommitActiveEdit();

		GetCommandHistory()->BeginBatch();

		//PaintGridBlockAttribute(x, y, 1);
		return TRUE;
	}

	if(IsCtrlDown(Viewport) && (Event == IE_Released) && (Key == KEY_LeftMouseButton))
	{
		CommitActiveEdit();

		_LeftMouseDown = false;

		GetCommandHistory()->EndBatch();
		return TRUE;
	}


	if(IsCtrlDown(Viewport) && (Event == IE_Pressed) && (Key == KEY_RightMouseButton))
	{
		_RightMouseDown = true;
		CommitActiveEdit();

		GetCommandHistory()->BeginBatch();

		//PaintGridBlockAttribute(x, y, 0);
		return TRUE;
	}

	if(IsCtrlDown(Viewport) && (Event == IE_Released) && (Key == KEY_RightMouseButton))
	{
		CommitActiveEdit();

		_RightMouseDown = false;

		GetCommandHistory()->EndBatch();

		return TRUE;
	}


	return FALSE;
}

UBOOL FEdModeGridEditing::MouseMove( FEditorLevelViewportClient* ViewportClient,FViewport* Viewport,INT x, INT y )
{
	UBOOL spoils = UpdateBrushLocation(ViewportClient, x, y);


	if(IsCtrlDown(Viewport) && _LeftMouseDown)
	{
		PaintGridBlockAttribute(1);
		return TRUE;
	}

	if(IsCtrlDown(Viewport) && _RightMouseDown)
	{
		PaintGridBlockAttribute(0);
		return TRUE;
	}
	if ( spoils )
		ViewportClient->Invalidate( FALSE, FALSE );
	return FALSE;
}

bool FEdModeGridEditing::CanUndo()
{
	return GetCommandHistory()->IsUndoEnable();
}

bool FEdModeGridEditing::CanRedo()
{
	return GetCommandHistory()->IsRedoEnable();
}

void FEdModeGridEditing::Undo()
{
	GetCommandHistory()->Undo();
}

void FEdModeGridEditing::Redo()
{
	GetCommandHistory()->Redo();
}

void FEdModeGridEditing::BeginActiveEdit( IActiveEditPtr activeEdit )
{
	_ActiveEdit = activeEdit;
}

void FEdModeGridEditing::CommitActiveEdit()
{
	if(_ActiveEdit)
	{
		GetCommandHistory()->AddCommand(_ActiveEdit->GetCommand(), false);
		_ActiveEdit = 0;
	}
}

bool FEdModeGridEditing::IsActiveEditing() const
{
	return _ActiveEdit != 0;
}

void FEdModeGridEditing::ExecuteActiveEdit( const Any& contex )
{
	if(_ActiveEdit)
	{
		_ActiveEdit->Execute(contex);
	}
}

class CommandHistory* FEdModeGridEditing::GetCommandHistory()
{
	if(!_CmdHistory)
	{
		_CmdHistory = new CommandHistory();
	}

	return _CmdHistory;
}

UBOOL FEdModeGridEditing::RayCastServerGrid( INT &x, INT &y, float &OutZ )
{
	FVector2D grid( x, y );
	grid = CoverServerGridToXY( grid );

	FVector Start( grid.X, grid.Y, _BrushLocation.Z + _Length );
	FVector End = Start + WORLD_MAX * FVector( 0, 0, -1 );

	FCheckResult Hit;
	if( !GWorld->SingleLineCheck(Hit, NULL, End, Start, TRACE_World | TRACE_Level, FVector(0.f,0.f,0.f), NULL) )
	{
		// Check filters
		if(Hit.Actor || Hit.Component)
		{
			OutZ = Hit.Location.Z;
			return TRUE;
		}
	}
	return FALSE;
}

void FEdModeGridEditing::PaintGridBlockAttribute( INT val )
{
	INT brushSq = (_BrushSize - 1) * (_BrushSize - 1);


	INT gridX = _BrushOnServer.X;
	INT gridY = _BrushOnServer.Y;
	float  fheight;
	BrushFinishSection.Lock();
	for (INT x = -_BrushSize + 1; x < _BrushSize; ++x)
	{
		for (INT y = -_BrushSize + 1; y < _BrushSize; ++y)
		{
			INT d = x * x + y * y;
			if(d <= brushSq)
			{
				INT gridXC = gridX + x;
				INT gridYC = gridY + y;

				if ( RayCastServerGrid( gridXC, gridYC, fheight ) )
				{
					GRID_DATA* gridData = g_ReviseScene.GetGrid( gridXC * GRID_WIDTH, gridYC * GRID_WIDTH, fheight * POINT_PER_CM + GRID_LAYER_HEIGHT * 05.f );
					if ( !gridData )
						gridData = g_ReviseScene.CreateGrid(gridXC * GRID_WIDTH, gridYC * GRID_WIDTH, fheight * POINT_PER_CM , fheight * POINT_PER_CM + GRID_LAYER_HEIGHT );
					if(gridData && !IsGridMatchBrushType(gridData, val))
					{
						g_ReviseScene.SetModified();
						//INT value = SetGridMatchBrushType( gridData, val );
						GetCommandHistory()->AddCommand(new Cmd_PaintGridBlocking(gridData, _CurrentBrushType, val));
					}
				}
			}
		}
	}
	BrushFinishSection.Unlock();
}

UBOOL FEdModeGridEditing::CapturedMouseMove( FEditorLevelViewportClient* InViewportClient, FViewport* InViewport, INT x, INT y )
{
	UBOOL spoils = UpdateBrushLocation(InViewportClient, x, y) || _LeftMouseDown || _RightMouseDown;

	do
	{
		if(_LeftMouseDown)
		{
			PaintGridBlockAttribute(1);
			break;
		}

		if(_RightMouseDown)
		{
			PaintGridBlockAttribute(0);
			break;
		}
	}while(false);
	
	if ( spoils )
		InViewportClient->Invalidate( FALSE, FALSE );
	return TRUE;
}

UBOOL FEdModeGridEditing::UpdateBrushLocation( FEditorLevelViewportClient* ViewportClient, INT x, INT y )
{
	FVector2D vTemp;
	_IsBrushTraceValid = FALSE;

	FSceneViewFamilyContext ViewFamily(
		ViewportClient->Viewport, ViewportClient->GetScene(),
		ViewportClient->ShowFlags,
		GWorld->GetTimeSeconds(),
		GWorld->GetDeltaSeconds(),
		GWorld->GetRealTimeSeconds(),
		ViewportClient->IsRealtime()
		);
	FSceneView* View = ViewportClient->CalcSceneView( &ViewFamily );
	FViewportCursorLocation MouseViewportRay( View, ViewportClient, x, y );

	FVector Start = MouseViewportRay.GetOrigin();
	//BrushTraceDirection = MouseViewportRay.GetDirection();
	FVector End = Start + WORLD_MAX * MouseViewportRay.GetDirection();

	FCheckResult Hit;
	if( !GWorld->SingleLineCheck(Hit, NULL, End, Start, TRACE_World | TRACE_Level, FVector(0.f,0.f,0.f), NULL) )
	{
		// Check filters
		if(Hit.Actor || Hit.Component)
		{
			// Adjust the sphere brush
			_BrushLocation = Hit.Location;
			_IsBrushTraceValid = TRUE;
			vTemp.X = _BrushLocation.X;
			vTemp.Y = _BrushLocation.Y;
			_Length = Start.Z - _BrushLocation.Z;
			CoverXYToServerGrid( vTemp.X, vTemp.Y );
			if ( _BrushOnServer != vTemp )
			{
				_BrushOnServer = vTemp;
				return TRUE;
			}
		}
	}
	return FALSE;
}

bool FEdModeGridEditing::IsGridMatchBrushType( GRID_DATA* gridData, INT val ) const
{
	switch(_CurrentBrushType)
	{
	case EPGBT_BlockMove:
		return gridData->bBlockMove == val;
		break;

	case EPGBT_BlockLeap:
		return gridData->bBlockLeap == val;
		break;

	case EPGBT_BlockMissile:
		return gridData->bBlockMissile == val;
		break;

	case EPGBT_BlockBullet:
		return gridData->bBlockBullet == val;
		break;

	case EPGBT_NotBlockChar:
		return gridData->bNotBlockChar == val;
		break;
	case EPGBT_CanStallArea:
		return gridData->uStallLevel == val;
		break;
	}

	return false;
}


INT FEdModeGridEditing::SetGridMatchBrushType(GRID_DATA* gridData, INT val)
{
	INT oldValue = 0;
	switch(_CurrentBrushType)
	{
	case EPGBT_BlockMove:
		oldValue = gridData->bBlockMove;
		gridData->bBlockMove = val;
		break;

	case EPGBT_BlockLeap:
		oldValue = gridData->bBlockLeap;
		gridData->bBlockLeap = val;
		break;

	case EPGBT_BlockMissile:
		oldValue = gridData->bBlockMissile;
		gridData->bBlockMissile = val;
		break;

	case EPGBT_BlockBullet:
		oldValue = gridData->bBlockBullet;
		gridData->bBlockBullet = val;
		break;

	case EPGBT_NotBlockChar:
		oldValue = gridData->bNotBlockChar;
		gridData->bNotBlockChar = val;
		break;
	case EPGBT_CanStallArea:
		oldValue = gridData->uStallLevel;
		gridData->uStallLevel = val;
		break;
	default:
		break;
	}
	return oldValue;
}