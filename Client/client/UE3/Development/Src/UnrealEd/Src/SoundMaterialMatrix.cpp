/*=============================================================================
	Kismet.cpp: Gameplay sequence editing
	Copyright 1998-2013 Epic Games, Inc. All Rights Reserved.

@todo UI integration tasks:
- SoundMaterialMatrix::RebuildTreeControl (only grabs sequences from the level)
- SoundMaterialMatrix::FindOutputLinkTo (needs to use interface for retrieving the objects contained by the current sequencecontainer)
- SoundMaterialMatrix::CenterViewOnSeqObj (see General notes below)
- SoundMaterialMatrix::OpenKismet/OpenSequenceInKismet (assumes that we always want to use the SoundMaterialMatrix class for the editor)
- SoundMaterialMatrix::OnOpenNewWindow (calls static function to open a new kismet window, which doesn't use the correct SoundMaterialMatrix class)

General:
- all code that attempts to find the SequenceObject's ParentSequence by either directly accessing ParentSequence or casting the object's outer to Sequence is unsafe for UI sequence objects
=============================================================================*/

#include "UnrealEd.h"
#include "Factories.h"
#include "UnLinkedObjEditor.h"
#include "SoundMaterialMatrix.h"
#include "EngineSequenceClasses.h"
#include "EnginePrefabClasses.h"
#include "EngineAudioDeviceClasses.h"
#include "UnLinkedObjDrawUtils.h"
#include "ScopedTransaction.h"
#include "PropertyWindow.h"
#include "LevelBrowser.h"
#include "DlgRename.h"
#include "ScopedObjectStateChange.h"
#include "InterpEditor.h"

#include "GFxUIClasses.h"
#include "GFxUIUISequenceClasses.h"

#include "SoundMaterialMatrixTreeCtrl.h"
#include "FileHelpers.h"

#include "../../Engine/Inc/EngineClasses.h"
#include "../../Engine/Inc/EngineMeshClasses.h"
#include "../../Engine/Inc/EngineAnimClasses.h"
#include "../../Engine/Inc/EngineAIClasses.h"
#include "../../GameFramework/Inc/GameFrameworkClasses.h"
#include "../../MMOGame/Inc/MMOGameClasses.h"

#include "SoundMatEditState_HitSounds.h"
#include "SoundMatEditState_Footstep.h"

//static INT	MultiEventSpacing = 100;
//static INT	PasteOffset = 30;
//static INT	FitCommentToSelectedBorder = 30;
//
///** Maximum region that is valid for sequence objects to exist in. */
//static INT	MaxSequenceSize = 10000;
//
//static const FColor SelectedColor( 255, 255, 0 );
//static const FColor BorderColor( 0, 0, 0 );
//static const FColor TitleBgColor( 112, 112, 112 );
//static const FColor HighlightColor( 0, 255, 0);
//static const FLOAT MapCoordScale(0.01f);
//static const FLOAT DegToUnrRot = 182.0444;
//
//FColor TeleOrigClr(0, 0, 255);
//FColor TeleTargetClr(0, 128, 0);

/*-----------------------------------------------------------------------------
	SoundMaterialMatrix
-----------------------------------------------------------------------------*/

enum ESoundMatEditState
{
	eSMES_HitSounds,
	eSMES_FootstepSounds
};


BEGIN_EVENT_TABLE( SoundMaterialMatrix, WxLinkedObjEd )
	EVT_CLOSE( SoundMaterialMatrix::OnClose )
	EVT_SIZE( SoundMaterialMatrix::OnSize )

	EVT_TOOL(IDM_SOUNDMATMATRIX_REFRESHALL, SoundMaterialMatrix::OnButtonRefreshAllData)	
	EVT_TOOL(IDM_SOUNDMATMATRIX_SAVE, SoundMaterialMatrix::OnButtonSave)

	EVT_TOOL(IDM_SOUNDMATMATRIX_HITSOUNDS, SoundMaterialMatrix::OnButtonHitSounds)	
	EVT_TOOL(IDM_SOUNDMATMATRIX_FOOTSTEPSOUNDS, SoundMaterialMatrix::OnButtonFootstepSounds)

END_EVENT_TABLE()

/** Kismet constructor. Initialize variables, create toolbar and status bar, set view to supplied sequence and add to global list of Kismet windows. */
SoundMaterialMatrix::SoundMaterialMatrix( wxWindow* InParent, wxWindowID InID, const TCHAR* Title )
: WxLinkedObjEd( InParent, InID, *LocalizeUnrealEd(Title) )
, ActiveEditState(0)
, GamePlayDataPackage(0)
, DataManager(0)
{
	FString PackageName = TEXT("GamePlayData.upk");
	FString ExistingFile, SaveFileName;

	if( GPackageFileCache->FindPackageFile( *PackageName, NULL, ExistingFile ) )
	{
		// If the package already exists, save to the existing filename.
		SaveFileName = ExistingFile;
	}

	GamePlayDataPackage = UObject::LoadPackage( NULL, *PackageName, LOAD_NoWarn );
	if( !GamePlayDataPackage )
	{
		appErrorf( TEXT("Unable to load %s"), *PackageName );
	}

	if(!GamePlayDataPackage->IsFullyLoaded())
	{
		GamePlayDataPackage->FullyLoad();
	}

	for (INT j = 0; j < GamePlayDataPackage->GetNetObjectCount(0); ++j)
	{
		DataManager = Cast<UGamePlayDataManager>(GamePlayDataPackage->GetNetObjectAtIndex(j));
		if(DataManager)
		{
			break;
		}
	}
	
	EditStates[eSMES_HitSounds] = new SoundMatEditState_HitSounds(this);
	EditStates[eSMES_FootstepSounds] = new SoundMatEditState_Footstep(this);
}
//------------------------------------------------------------------------
/** Kismet destructor. Will remove itself from global list of Kismet windows. */
SoundMaterialMatrix::~SoundMaterialMatrix()
{
	EditStateMap::iterator it = EditStates.begin();
	for (; it != EditStates.end(); ++it)
	{
		delete it->second;
	}

	//GCallbackEvent->UnregisterAll(this);

	// Save out the window properties when the Kismet window is destroyed
	SaveProperties();

	//// Remove from global list of Kismet windows.
	check( GApp->SoundMaterialMatrixWindows.ContainsItem(this) );
	GApp->SoundMaterialMatrixWindows.RemoveItem(this);

	////GEditor->ResetTransaction( *LocalizeUnrealEd("QuitKismet") );
}
//------------------------------------------------------------------------
void SoundMaterialMatrix::InitEditor()
{
	//GlobalMapSingleton = UGlobalMapInfo::GetSingleton();

	CreateControls(TRUE);

	// Register the CALLBACK_RefreshEditor_Kismet event
	//GCallbackEvent->Register(CALLBACK_RefreshEditor_Kismet, this);
	//GCallbackEvent->Register(CALLBACK_Undo, this);
	
	LoadProperties();

	//PropertyWindow->SetObject( GlobalMapSingleton,
	//	EPropertyWindowFlags::Sorted | EPropertyWindowFlags::ShouldShowCategories);


	// Initialize the tree control.
	//RebuildTreeControl();

	ActiveState((INT)eSMES_HitSounds);
}
//------------------------------------------------------------------------
/**
 * Creates the controls for this window
 */
void SoundMaterialMatrix::CreateControls( UBOOL bTreeControl )
{
	//WxLinkedObjEd::CreateControls(bTreeControl);
	GraphWindow = new WxLinkedObjVCHolder( this, -1, this );
	LinkedObjVC = GraphWindow->LinkedObjVC;

	PropertyWindow = new WxPropertyWindowHost;
	PropertyWindow->Create( this, this );
	AddDockingWindow(PropertyWindow, FDockingParent::DH_Right, *LocalizeUnrealEd("Properties"));

	//if(bTreeControl)
	//{
	//	//PropertyWindow = new WxPropertyWindowHost;
	//	//PropertyWindow->Create( this, this );
	//	//AddDockingWindow(PropertyWindow, FDockingParent::DH_Bottom, *LocalizeUnrealEd("Properties"));

	//	CreateTreeControl(this);
	//	check(TreeControl);
	//	AddDockingWindow(TreeControl, FDockingParent::DH_Bottom, *LocalizeUnrealEd("Maps"));
	//}
	//else
	//{
	//	//PropertyWindow = new WxPropertyWindowHost;
	//	//PropertyWindow->Create( this, this );
	//	//AddDockingWindow(PropertyWindow, FDockingParent::DH_Bottom, *LocalizeUnrealEd("Properties"));
	//}

	// Add main docking pane.
	AddDockingWindow( GraphWindow, FDockingParent::DH_None, NULL );

	// Try to load a existing layout for the docking windows.
	LoadDockingLayout();

	wxMenuBar* MenuBar = new wxMenuBar();
	AppendWindowMenu(MenuBar);
	SetMenuBar(MenuBar);

	// activate the base sequence
// 	USequence* InitialActiveSequence = Sequence;
// 	Sequence = NULL;

	//ChangeActiveSequence( InitialActiveSequence, TRUE, FALSE );

	// Create toolbar
	ToolBar = new SoundMaterialMatrixToolBar( this, -1 );
	SetToolBar( ToolBar );

	// Attach the nav. history tools (back/forward/drop-down) to the toolbar
	//NavHistory.AttachToToolBar( ToolBar, FALSE, TRUE, 0 );

	// Bookmarks
// 	wxMenu* HistoryMenu = NavHistory.HistoryMenu;
// 	if ( HistoryMenu )
// 	{
// 		wxMenu* BookmarkMenu = new wxMenu();
// 		//BuildBookmarkMenu(BookmarkMenu, FALSE);
// 		HistoryMenu->AppendSubMenu( BookmarkMenu, *LocalizeUnrealEd("LevelViewportContext_Bookmarks"), *LocalizeUnrealEd("ToolTip_Bookmarks" ) );
// 		HistoryMenu->AppendSeparator();
// 	}

	// Create status bar
	StatusBar = new SoundMaterialMatrixStatusBar( this, -1 );
	SetStatusBar( StatusBar );

	// load the background texture
	BackgroundTexture = LoadObject<UTexture2D>(NULL, TEXT("EditorMaterials.KismetBackground"), NULL, LOAD_None, NULL);

	//InitSeqObjClasses();

	//TreeImages->Add( WxBitmap( "KIS_SeqTreeClosed" ), wxColor( 192,192,192 ) ); // 0
	//TreeImages->Add( WxBitmap( "KIS_SeqTreeOpen" ), wxColor( 192,192,192 ) ); // 1

	// Keep a list of all Kismets in case we need to close them etc.
	GApp->SoundMaterialMatrixWindows.AddItem(this);
}
//------------------------------------------------------------------------
/**
 * Creates the tree control for this linked object editor.  Only called if TRUE is specified for bTreeControl
 * in the constructor.
 *
 * @param	TreeParent	the window that should be the parent for the tree control
 */
void SoundMaterialMatrix::CreateTreeControl( wxWindow* TreeParent )
{
	/*
	TreeImages = new wxImageList( 16, 15 );
	TreeControl = new SoundMaterialMatrixTreeCtrl;
	((SoundMaterialMatrixTreeCtrl*)TreeControl)->Create(TreeParent, IDM_LINKEDOBJED_TREE, this);
	TreeControl->AssignImageList(TreeImages);
	*/
}
//------------------------------------------------------------------------
/** Called when the window closes (but may be some time before actually destroyed) */
void SoundMaterialMatrix::OnClose( wxCloseEvent& In )
{
	// Clear out any navigation history
	//NavHistory.ClearHistory();

// 	SoundMaterialMatrixTreeCtrl* TreeCtrl = wxDynamicCast(TreeControl,SoundMaterialMatrixTreeCtrl);
// 	if ( TreeCtrl != NULL )
// 	{
// 		TreeCtrl->ClearTree();
// 	}
// 	else
// 	{
// 		TreeControl->DeleteAllItems();
// 	}

	// Save out the window properties when the Kismet window is closed
	SaveProperties();

	this->Destroy();
}
//------------------------------------------------------------------------
void SoundMaterialMatrix::OnSize(wxSizeEvent& In)
{
	RefreshViewport();
	In.Skip();
}
//------------------------------------------------------------------------
void SoundMaterialMatrix::OpenEditor( UBOOL bCreateNewWindow, class wxWindow* WindowParent )
{
	if ( bCreateNewWindow || GApp->SoundMaterialMatrixWindows.Num() == 0 )
	{
		// Create a new window if requested by the user or if none exist.
		SoundMaterialMatrix* editor = new SoundMaterialMatrix( WindowParent, -1);
		editor->InitEditor();
		editor->Show();

		// Add a new navigation history item for this action
		//TeleportGraphEditor->AddNewNavigationHistoryDataItem( TeleportGraphEditor->GenerateNavigationHistoryString() );
	}
	else
	{
		// Bring all kismet windows to focus.
		for (INT Idx = 0; Idx < GApp->SoundMaterialMatrixWindows.Num(); Idx++)
		{
			SoundMaterialMatrix* editorWindow = GApp->SoundMaterialMatrixWindows(Idx);
			editorWindow->Show();
			editorWindow->Restore();
			editorWindow->SetFocus();
		}
	}
}
//------------------------------------------------------------------------
FString SoundMaterialMatrix::GenerateNavigationHistoryString() const
{
	FString NavHistoryString;
	//if ( Sequence )
	//{
	//	// First compile the sequences name
	//	NavHistoryString += Sequence->GetOutermost()->GetName();
	//	NavHistoryString += TEXT(".");
	//	NavHistoryString += Sequence->GetSeqObjFullName();

	//	const INT NumSelectedObjects = SelectedSeqObjs.Num();

	//	// If only one object is selected, display its name
	//	if ( NumSelectedObjects == 1 )
	//	{
	//		NavHistoryString += TEXT(": ");
	//		NavHistoryString += SelectedSeqObjs(0)->GetName();
	//	}
	//	// If multiple objects are selected, display the number selected
	//	else if ( NumSelectedObjects > 1 )
	//	{
	//		NavHistoryString += TEXT(": ");
	//		NavHistoryString += FString::Printf( LocalizeSecure( LocalizeUnrealEd("Kismet_NavHistory_NodesSelected"), NumSelectedObjects ) );
	//	}
	//}
	return NavHistoryString; 
}
//------------------------------------------------------------------------
void SoundMaterialMatrix::EdHandleKeyInput( FViewport* Viewport, FName Key, EInputEvent Event )
{

}
//------------------------------------------------------------------------

void SoundMaterialMatrix::DrawObjects( FViewport* Viewport, FCanvas* Canvas )
{
	WxLinkedObjEd::DrawObjects( Viewport, Canvas );

	if(ActiveEditState)
	{
		ActiveEditState->DrawObjects(Viewport, Canvas);
	}
}
//------------------------------------------------------------------------
void SoundMaterialMatrix::UpdatePropertyWindow()
{
	//PropertyWindow->SetObjectArray( GlobalMapSingleton,
	//	EPropertyWindowFlags::Sorted | EPropertyWindowFlags::ShouldShowCategories);
}
//------------------------------------------------------------------------
void SoundMaterialMatrix::EmptySelection()
{
	if(ActiveEditState)
	{
		ActiveEditState->EmptySelection();
	}
}
//------------------------------------------------------------------------
void SoundMaterialMatrix::AddToSelection( UObject* Obj )
{
	//checkSlow( Obj->IsA(UGlobalMapInfo::StaticClass()) );
	//if ( Obj->IsA(UGlobalMapInfo::StaticClass()) )
	//{
	//	//SelectedSeqObjs.AddUniqueItem( (USequenceObject*)Obj );
	//}
}
//------------------------------------------------------------------------
void SoundMaterialMatrix::RemoveFromSelection( UObject* Obj )
{
	//checkSlow( Obj->IsA(USequenceObject::StaticClass()) );
	/*if (Obj->IsA(USequenceObject::StaticClass()))
	{
		SelectedSeqObjs.RemoveItem( (USequenceObject*)Obj );
	}*/
}
//------------------------------------------------------------------------
UBOOL SoundMaterialMatrix::IsInSelection( UObject* Obj ) const
{
	//checkSlow( Obj->IsA(USequenceObject::StaticClass()) );
	//return (Obj->IsA(USequenceObject::StaticClass()) && SelectedSeqObjs.ContainsItem( (USequenceObject*)Obj ));
	return false;
}
//------------------------------------------------------------------------
INT SoundMaterialMatrix::GetNumSelected() const
{
	if(ActiveEditState)
	{
		return ActiveEditState->GetNumSelected();
	}
	return 0;
}
//------------------------------------------------------------------------
void SoundMaterialMatrix::SetSelectedConnector( FLinkedObjectConnector& Connector )
{
// 	switch(Connector.ConnType)
// 	{
// 	//case TeleMapType:
// 	//	{
// 	//		//SelectedMap = GetMap(Connector.ConnIndex);
// 	//		break;
// 	//	}
// 	}
}
//------------------------------------------------------------------------
void SoundMaterialMatrix::ClickedAnyObject( struct HAnyObjectProxy* proxy )
{
	if(ActiveEditState)
	{
		ActiveEditState->ClickedAnyObject(proxy);
	}
}
//------------------------------------------------------------------------
void SoundMaterialMatrix::CtrlClickedAnyObject( struct HAnyObjectProxy* proxy )
{
	if(ActiveEditState)
	{
		ActiveEditState->CtrlClickedAnyObject(proxy);
	}
}
//------------------------------------------------------------------------
void SoundMaterialMatrix::MoveSelectedObjects( INT DeltaX, INT DeltaY )
{	
}
//------------------------------------------------------------------------
void SoundMaterialMatrix::HighlightAnyObject( struct HAnyObjectProxy* proxy )
{
	if(ActiveEditState)
	{
		ActiveEditState->HighlightAnyObject(proxy);
	}
}
//------------------------------------------------------------------------
void SoundMaterialMatrix::DoubleClickedAnyObject( struct HAnyObjectProxy* proxy )
{
	if(ActiveEditState)
	{
		ActiveEditState->DoubleClickedAnyObject(proxy);
	}
}
//------------------------------------------------------------------------
void SoundMaterialMatrix::OnButtonRefreshAllData( wxCommandEvent& In )
{
	/*EmptySelection();

	GlobalMapSingleton->LoadTeleportsFromXML();

	MakePackageDirty();
*/
	RefreshViewport();
}
//------------------------------------------------------------------------
void SoundMaterialMatrix::OnButtonSave( wxCommandEvent& In )
{
	if(ActiveEditState)
	{
		ActiveEditState->SaveData();
	}

	TArray<UPackage*> Packages;
	Packages.AddItem(GamePlayDataPackage);
	FEditorFileUtils::PromptForCheckoutAndSave(Packages, TRUE, TRUE);
}
//------------------------------------------------------------------------
void SoundMaterialMatrix::MakePackageDirty()
{
	GamePlayDataPackage->MarkPackageDirty();
}
//------------------------------------------------------------------------
void SoundMaterialMatrix::ActiveState( INT StateID )
{
	if(ActiveEditState)
	{
		ActiveEditState->OnExit();
	}

	ActiveEditState = EditStates[StateID];

	if(ActiveEditState)
	{
		ActiveEditState->OnEnter();
	}

	RefreshViewport();
}
//------------------------------------------------------------------------
UGamePlayDataManager* SoundMaterialMatrix::GetDataManager()
{
	checkSlow(DataManager != 0);
	return DataManager;
}
//------------------------------------------------------------------------
void SoundMaterialMatrix::OnButtonHitSounds( wxCommandEvent& In )
{
	ActiveState((INT)eSMES_HitSounds);
}
//------------------------------------------------------------------------
void SoundMaterialMatrix::OnButtonFootstepSounds( wxCommandEvent& In )
{
	ActiveState((INT)eSMES_FootstepSounds);
}
//------------------------------------------------------------------------
void SoundMaterialMatrix::SetObjectToPropertyWindow( UObject* object )
{
	PropertyWindow->SetObject(object, EPropertyWindowFlags::Sorted);

	// | EPropertyWindowFlags::ShouldShowCategories
	//PropertyWindow->ExpandAllItems();
}
//------------------------------------------------------------------------
