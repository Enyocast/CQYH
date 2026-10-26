/*=============================================================================
	AnimSetViewerMenus.cpp: AnimSet viewer menus
	Copyright 1998-2013 Epic Games, Inc. All Rights Reserved.
=============================================================================*/

#include "UnrealEd.h"
#include "EngineAnimClasses.h"
#include "AbilityEditor.h"
#include "PropertyWindow.h"
#include "DlgGenericComboEntry.h"
#include "DlgRename.h"
#include "BusyCursor.h"
#include "SoftBodyEditor.h"
#include "NvApexManager.h"
#include "PackageHelperFunctions.h"

#if WITH_SIMPLYGON
#include "DlgSimplifyLOD.h"
#include "SkeletalMeshSimplificationWindow.h"
#include "SimplygonMeshUtilities.h"
#endif // #if WITH_SIMPLYGON

#include <strsafe.h>

extern const char * gDebugCommands[IDM_ANIMSET_LAST-IDM_ANIMSET_PHYSX_CLEAR_ALL];
// const char * gDebugCommands[IDM_ANIMSET_LAST-IDM_ANIMSET_PHYSX_CLEAR_ALL] =
// {
// 	"PHYSX_CLEAR_ALL",
// 	"WORLD_AXES",
// 	"BODY_AXES",
// 	"BODY_MASS_AXES",
// 	"BODY_LIN_VELOCITY",
// 	"BODY_ANG_VELOCITY",
// 	"BODY_JOINT_GROUPS",
// 	"JOINT_LOCAL_AXES",
// 	"JOINT_WORLD_AXES",
// 	"JOINT_LIMITS",
// 	"CONTACT_POINT",
// 	"CONTACT_NORMAL",
// 	"CONTACT_ERROR",
// 	"CONTACT_FORCE",
// 	"ACTOR_AXES",
// 	"COLLISION_AABBS",
// 	"COLLISION_SHAPES",
// 	"COLLISION_AXES",
// 	"COLLISION_COMPOUNDS",
// 	"COLLISION_VNORMALS",
// 	"COLLISION_FNORMALS",
// 	"COLLISION_EDGES",
// 	"COLLISION_SPHERES",
// 	"COLLISION_STATIC",
// 	"COLLISION_DYNAMIC",
// 	"COLLISION_FREE",
// 	"COLLISION_CCD",
// 	"COLLISION_SKELETONS",
// 	"FLUID_EMITTERS",
// 	"FLUID_POSITION",
// 	"FLUID_VELOCITY",
// 	"FLUID_KERNEL_RADIUS",
// 	"FLUID_BOUNDS",
// 	"FLUID_PACKETS",
// 	"FLUID_MOTION_LIMIT",
// 	"FLUID_DYN_COLLISION",
// 	"FLUID_STC_COLLISION",
// 	"FLUID_MESH_PACKETS",
// 	"FLUID_DRAINS",
// 	"FLUID_PACKET_DATA",
// 	"CLOTH_MESH",
// 	"CLOTH_COLLISIONS",
// 	"CLOTH_SELFCOLLISIONS",
// 	"CLOTH_WORKPACKETS",
// 	"CLOTH_SLEEP",
// 	"CLOTH_SLEEP_VERTEX",
// 	"CLOTH_TEARABLE_VERTICES",
// 	"CLOTH_TEARING",
// 	"CLOTH_ATTACHMENT",
// 	"CLOTH_VALIDBOUNDS",
// 	"SOFTBODY_MESH",
// 	"SOFTBODY_COLLISIONS",
// 	"SOFTBODY_WORKPACKETS",
// 	"SOFTBODY_SLEEP",
// 	"SOFTBODY_SLEEP_VERTEX",
// 	"SOFTBODY_TEARABLE_VERTICES",
// 	"SOFTBODY_TEARING",
// 	"SOFTBODY_ATTACHMENT",
// 	"SOFTBODY_VALIDBOUNDS",
// #if WITH_APEX
// 	"APEX_CLEAR_ALL",
// 	"VISUALIZE_CLOTHING_SKINNED_POSITIONS",
// 	"VISUALIZE_CLOTHING_SPHERE_COLLISION",
// 	"VISUALIZE_CLOTHING_MAX_DISTANCE_OUT",
// 	"VISUALIZE_CLOTHING_MAX_DISTANCE_IN",
// 	"VISUALIZE_CLOTHING_ALL_SKIN_MAP",
// 	"VISUALIZE_CLOTHING_BAD_SKIN_MAP",
// 	"VISUALIZE_CLOTHING_SKIN_MAP",
// 	"VISUALIZE_CLOTHING_RENDER_NORMALS",
// 	"VISUALIZE_CLOTHING_RENDER_TANGENTS",
// 	"VISUALIZE_CLOTHING_PHYSICS_MESH_WIRE",
// 	"VISUALIZE_CLOTHING_PHYSICS_MESH_SOLID",
// 	"VISUALIZE_CLOTHING_SKELETON",
// 	"VISUALIZE_CLOTHING_BONE_FRAMES",
// 	"VISUALIZE_CLOTHING_BONE_NAMES",
// 	"VISUALIZE_CLOTHING_VELOCITIES",
// 	"VISUALIZE_CLOTHING_GRAPHICAL_VERTEX_BONES",
// 	"VISUALIZE_CLOTHING_PHYSICAL_VERTEX_BONES",
// 	"VISUALIZE_CLOTHING_ACOLLISION_UMBRELLAS",
// 
// 	"VISUALIZE_DESTRUCTIBLE_BOUNDS",
// 	"VISUALIZE_DESTRUCTIBLE_SUPPORT",
// 	"VISUALIZE_DESTRUCTIBLE_ACTOR_POSE",
// 	"VISUALIZE_DESTRUCTIBLE_FRAGMENT_ACTOR_POSE",
// 	"VISUALIZE_DESTRUCTIBLE_ACTOR_NAME",
// 	"LOD_DISTANCE_DESTRUCTIBLE_ACTOR_POSE",
// 	"LOD_DISTANCE_DESTRUCTIBLE_ACTOR_NAME",
// 	"LOD_DISTANCE_DESTRUCTIBLE_FRAGMENT_ACTOR_POSE",
// 
// 	"VISUALIZE_LOD_BENEFITS",
// 	"LOD_DISTANCE_SCALE",
// #if WITH_APEX_PARTICLES
// 	"VISUALIZE_TOTAL_INJECTED_AABB",
// 	"VISUALIZE_APEX_EMITTER_ACTOR_POSE",
// 	"THRESHOLD_DISTANCE_APEX_EMITTER_ACTOR_POSE",
// 	"VISUALIZE_APEX_EMITTER_ACTOR_NAME",
// 	"THRESHOLD_DISTANCE_APEX_EMITTER_ACTOR_NAME",
// 	"VISUALIZE_GROUND_EMITTER_SPHERE",
// 	"VISUALIZE_GROUND_EMITTER_GRID",
// 	"VISUALIZE_GROUND_EMITTER_RAYCAST",
// 	"VISUALIZE_GROUND_EMITTER_ACTOR_POSE",
// 	"VISUALIZE_GROUND_EMITTER_ACTOR_NAME",
// 	"VISUALIZE_IMPACT_EMITTER_RAYCAST",
// 	"VISUALIZE_IMPACT_EMITTER_ACTOR_NAME",
// 	"THRESHOLD_DISTANCE_IMPACT_EMITTER_ACTOR_NAME",
// 
// 	"VISUALIZE_IOFX_BOUNDING_BOX",
// 	"APEX_VISUALIZE_IOFX_ACTOR_NAME",
// #endif
// 
// #endif
// };

///////////////////// MENU HANDLERS

/**
 *	Called when a SIZE event occurs on the window
 *
 *	@param	In		The size event information
 */
void WxModelViewer::OnSize( wxSizeEvent& In )
{
	In.Skip();
	Refresh();
	UpdatePreviewWindow();
}

void WxModelViewer::OnWeaponTypeComboChanged(wxCommandEvent& In)
{
	SetWeaponIdx(In.GetInt());
}


void WxModelViewer::OnAnimSetUse( wxCommandEvent& In )
{
	//if( bSearchAllAnimSequences )
	//{
	//	// If the user is searching all AnimSets, then the AnimSet combo 
	//	// was disabled. Enable it so the user can interact with it. 
	//	AnimSetCombo->Enable();

	//	// Disable 'Search All' mode since we are filtering by a specific AnimSet. 
	//	bSearchAllAnimSequences = FALSE;
	//}

	//GCallbackEvent->Send(CALLBACK_LoadSelectedAssetsIfNeeded);
	//UAnimSet* SelectedAnimSet = GEditor->GetSelectedObjects()->GetTop<UAnimSet>();
	//if(SelectedAnimSet)
	//{
	//	SetSelectedAnimSet(SelectedAnimSet, TRUE);
	//}
}

void WxModelViewer::OnAnimSetListChanged( wxCommandEvent& In )
{
	SetAnimSet(In.GetInt());
}
void WxModelViewer::OnAnimSeqListChanged( wxCommandEvent& In )
{
	SetAnimSeq(In.GetInt());
}

//
//////////////////////////////////////////////////////////////////////////

void WxModelViewer::OnTimeScrub(wxScrollEvent& In)
{
	if(SelectedAnimSeq)
	{
		const INT NewIntPosition = In.GetPosition();
		const FLOAT NewPosition = (FLOAT)NewIntPosition/(FLOAT)ASV_SCRUBRANGE;
		PreviewAnimNode->SetPosition( NewPosition * SelectedAnimSeq->SequenceLength, false );
	}
}

void WxModelViewer::OnViewFloor(wxCommandEvent& In)
{
	FEditorModelViewportClient* ASVPreviewVC = GetPreviewVC();
	check( ASVPreviewVC );

	ASVPreviewVC->bShowFloor = In.IsChecked();

	UpdateFloorComponent();
}

void WxModelViewer::OnViewCollision(wxCommandEvent& In)
{
	//FEditorModelViewportClient* ASVPreviewVC = GetPreviewVC();
	//check( ASVPreviewVC );

	//if( In.IsChecked() )
	//{
	//	ASVPreviewVC->ShowFlags |= SHOW_Collision;
	//}
	//else
	//{
	//	ASVPreviewVC->ShowFlags &= ~SHOW_Collision;
	//}
}

void WxModelViewer::OnSpeed(wxCommandEvent& In)
{
	const INT Id = In.GetId();
	switch (Id)
	{
	case IDM_ANIMSET_SPEED_1:
		PlaybackSpeed = 0.01f;
		break;
	case IDM_ANIMSET_SPEED_10:
		PlaybackSpeed = 0.1f;
		break;
	case IDM_ANIMSET_SPEED_25:
		PlaybackSpeed = 0.25f;
		break;
	case IDM_ANIMSET_SPEED_50:
		PlaybackSpeed = 0.5f;
		break;
	case IDM_ANIMSET_SPEED_100:
		PlaybackSpeed = 1.f;
		break;
	case IDM_ANIMSET_SPEED_125:
		PlaybackSpeed = 1.25;
		break;
	case IDM_ANIMSET_SPEED_150:
		PlaybackSpeed = 1.50;
		break;
	case IDM_ANIMSET_SPEED_175:
		PlaybackSpeed = 1.75;
		break;
	case IDM_ANIMSET_SPEED_200:
		PlaybackSpeed = 2.0;
		break;
	default:
		PlaybackSpeed = 1.0f;
		break;
	};
}

void WxModelViewer::OnViewWireframe(wxCommandEvent& In)
{
	//FEditorModelViewportClient* ASVPreviewVC = GetPreviewVC();
	//check( ASVPreviewVC );

	//// Cycle through viewmodes.
	//WireframeCycleCounter++;
	//if( WireframeCycleCounter > 2 )
	//{
	//	WireframeCycleCounter = 0;
	//}

	//switch( WireframeCycleCounter )
	//{
	//	case 0 : // show mesh lit
	//		ASVPreviewVC->ShowFlags &= ~SHOW_ViewMode_Mask;
	//		ASVPreviewVC->ShowFlags |= SHOW_ViewMode_Lit;
	//		PreviewSkelComp->bDrawMesh = TRUE;
	//		break;
	//	case 1 : // show mesh wireframe
	//		ASVPreviewVC->ShowFlags &= ~SHOW_ViewMode_Mask;
	//		ASVPreviewVC->ShowFlags |= SHOW_ViewMode_Wireframe;
	//		PreviewSkelComp->bDrawMesh = TRUE;
	//		break;
	//	case 2 : // hide mesh
	//		ASVPreviewVC->ShowFlags &= ~SHOW_ViewMode_Mask;
	//		ASVPreviewVC->ShowFlags |= SHOW_ViewMode_Lit;
	//		PreviewSkelComp->bDrawMesh = FALSE;
	//		break;
	//}

	////// Toggle socket visibility as well
	////for(INT i=0; i<SocketPreviews.Num(); i++)
	////{
	////	UPrimitiveComponent* PrimComp = SocketPreviews(i).PreviewComp;
	////	if( PrimComp )
	////	{
	////		PrimComp->SetHiddenEditor(!PreviewSkelComp->bDrawMesh);
	////	}
	////}

	//MenuBar->Check( IDM_ANIMSET_VIEWWIREFRAME, (WireframeCycleCounter != 0) );
	//ToolBar->ToggleTool( IDM_ANIMSET_VIEWWIREFRAME, (WireframeCycleCounter != 0) );
}


void WxModelViewer::OnViewGrid( wxCommandEvent& In )
{
	FEditorModelViewportClient* ASVPreviewVC = GetPreviewVC();
	check( ASVPreviewVC );

	if( In.IsChecked() )
	{
		ASVPreviewVC->ShowFlags |= SHOW_Grid;
	}
	else
	{
		ASVPreviewVC->ShowFlags &= ~SHOW_Grid;
	}
}

void WxModelViewer::OnLoopAnim(wxCommandEvent& In)
{
	PreviewAnimNode->bLooping = !(PreviewAnimNode->bLooping);
	bLooping = PreviewAnimNode->bLooping;

	RefreshPlaybackUI();
}

void WxModelViewer::OnPlayAnim(wxCommandEvent& In)
{
	if(!PreviewAnimNode->bPlaying)
	{
		PreviewAnimNode->PlayAnim(PreviewAnimNode->bLooping, 1.f);
	}
	else
	{
		PreviewAnimNode->StopAnim();
	}

	bPlaying = PreviewAnimNode->bPlaying;
	RefreshPlaybackUI();
}

/**
 * Fixes up names by removing tabs and replacing spaces with underscores.
 *
 * @param	InOldName	The name to fixup.
 * @param	OutResult	[out] The fixed up name.
 * @return				TRUE if the name required fixup, FALSE otherwise.
 */
static UBOOL FixupName(const TCHAR* InOldName, FString& OutResult)
{
	// Replace spaces with underscores.
	OutResult = FString( InOldName ).Replace( TEXT(" "), TEXT("_") );

	// Remove tabs by recursively splitting the string at a tab and merging halves.
	FString LeftStr;
	FString RightStr;

	while ( TRUE )
	{
		const UBOOL bSplit = OutResult.Split( TEXT("\t"), &LeftStr, &RightStr );
		if ( !bSplit )
		{
			break;
		}
		OutResult = LeftStr + RightStr;
	}

	const UBOOL bNewNameDiffersFromOld = ( OutResult != InOldName );
	return bNewNameDiffersFromOld;
}

static FLOAT DistFromPlane(FVector& Point, BYTE Axis)
{
	if(Axis == AXIS_X)
	{
		return Point.X;
	}
	else if(Axis == AXIS_Y)
	{
		return Point.Y;
	}
	else if(Axis == AXIS_Z)
	{
		return Point.Z;
	}
	else
	{
		return 0.f;
	}
}

static void MirrorPointByPlane(FVector& Point, BYTE Axis)
{
	if(Axis == AXIS_X)
	{
		Point.X *= -1.f;
	}
	else if(Axis == AXIS_Y)
	{
		Point.Y *= -1.f;
	}
	else if(Axis == AXIS_Z)
	{
		Point.Z *= -1.f;
	}
}

static const FLOAT NoSwapThreshold = 0.2f;
static const FLOAT MatchBoneThreshold = 0.1f;

/*-----------------------------------------------------------------------------
	WxASVToolBar
-----------------------------------------------------------------------------*/

BEGIN_EVENT_TABLE( WxMVToolBar, WxToolBar )
END_EVENT_TABLE()

WxMVToolBar::WxMVToolBar( wxWindow* InParent, wxWindowID InID )
: WxToolBar( InParent, InID, wxDefaultPosition, wxDefaultSize, wxTB_HORIZONTAL | wxTB_FLAT | wxTB_3DBUTTONS )
{
	//SocketMgrB.Load(TEXT("ASV_SocketMgr"));
	//ShowBonesB.Load(TEXT("AnimTree_ShowBones"));
	//ShowRawAnimationB.Load(TEXT("ASV_ShowRawAnimation"));
	//ShowCompressedAnimationB.Load(TEXT("ASV_ShowCompressedAnimation"));
	//ShowBoneNamesB.Load(TEXT("AnimTree_ShowBoneNames"));
	//ShowWireframeB.Load(TEXT("AnimTree_ShowWireframe"));
	//ShowRefPoseB.Load(TEXT("ASV_ShowRefPose"));
	//ShowMirrorB.Load(TEXT("ASV_ShowMirror"));

	//NewNotifyB.Load(TEXT("ASV_NewNotify"));
	//ClothB.Load(TEXT("ASV_Cloth"));
	//SoftBodyGenerateB.Load(TEXT("ASV_SoftBodyGenerate"));
	//SoftBodyToggleSimB.Load(TEXT("ASV_SoftBodyToggleSim"));

	//LODAutoB.Load(TEXT("AnimTree_LOD_Auto"));
	//LODBaseB.Load(TEXT("AnimTree_LOD_Base"));
	//LOD1B.Load(TEXT("AnimTree_LOD_1"));
	//LOD2B.Load(TEXT("AnimTree_LOD_2"));
	//LOD3B.Load(TEXT("AnimTree_LOD_3"));

	Speed1B.Load(TEXT("ASV_Speed_1"));
	Speed10B.Load(TEXT("ASV_Speed_10"));
	Speed25B.Load(TEXT("ASV_Speed_25"));
	Speed50B.Load(TEXT("ASV_Speed_50"));
	Speed100B.Load(TEXT("ASV_Speed_100"));
	Speed125B.Load(TEXT("ASV_Speed_125"));
	Speed150B.Load(TEXT("ASV_Speed_150"));
	Speed175B.Load(TEXT("ASV_Speed_175"));
	Speed200B.Load(TEXT("ASV_Speed_200"));

	ResetCameraPostion.Load(TEXT("Front"));
	RotateCamera.Load(TEXT("AbilityRotate"));
	Refresh.Load(TEXT("ModelRefresh"));

	ShowCollision.Load(TEXT("ShowCollision"));

	ExportData.Load(TEXT("ExportMergedData"));

	//GoreMode.Load(TEXT("ASV_ShowGoreMode"));

	//TangentMode.Load(TEXT("ASV_ShowTangents"));
	//NormalMode.Load(TEXT("ASV_ShowNormals"));

	//TriangleSortMode.Load(TEXT("ASV_TriangleSortMode"));
	//TriangleSortModeL.Load(TEXT("ASV_TriangleSortModeL"));
	//TriangleSortModeR.Load(TEXT("ASV_TriangleSortModeR"));

	SetToolBitmapSize( wxSize( 16, 16 ) );

	//wxStaticText* LODLabel = new wxStaticText(this, -1 ,*LocalizeUnrealEd("LODLabel") );
	//wxStaticText* ChunksLabel = new wxStaticText(this, -1 ,*LocalizeUnrealEd("AnimSetViewer_ChunksLabel") );
	//wxStaticText* SectionsLabel = new wxStaticText(this, -1 ,*LocalizeUnrealEd("AnimSetViewer_SectionsLabel") );

	//AddSeparator();
	//AddCheckTool(IDM_ANIMSET_VIEWBONES, *LocalizeUnrealEd("ToolTip_3"), ShowBonesB, wxNullBitmap, *LocalizeUnrealEd("ToolTip_3") );
	//AddCheckTool(IDM_ANIMSET_VIEWADDITIVEBASE, *LocalizeUnrealEd("ShowAdditiveBase"), ShowBonesB, wxNullBitmap, *LocalizeUnrealEd("ShowAdditiveBase") );
	//AddCheckTool(IDM_ANIMSET_VIEWBONENAMES, *LocalizeUnrealEd("ToolTip_4"), ShowBoneNamesB, wxNullBitmap, *LocalizeUnrealEd("ToolTip_4") );
	//AddCheckTool(IDM_ANIMSET_VIEWWIREFRAME, *LocalizeUnrealEd("ToolTip_5"), ShowWireframeB, wxNullBitmap, *LocalizeUnrealEd("ToolTip_5") );
	//AddCheckTool(IDM_ANIMSET_VIEWREFPOSE, *LocalizeUnrealEd("ShowReferencePose"), ShowRefPoseB, wxNullBitmap, *LocalizeUnrealEd("ShowReferencePose") );
	//AddCheckTool(IDM_ANIMSET_VIEWMIRROR, *LocalizeUnrealEd("ShowMirror"), ShowMirrorB, wxNullBitmap, *LocalizeUnrealEd("ShowMirror") );
	//AddSeparator();
	//AddCheckTool(IDM_ANIMSET_OPENSOCKETMGR, *LocalizeUnrealEd("ToolTip_6"), SocketMgrB, wxNullBitmap, *LocalizeUnrealEd("ToolTip_6") );
	//AddSeparator();
	//AddTool(IDM_ANIMSET_NOTIFYNEW, NewNotifyB, *LocalizeUnrealEd("NewNotify") );
	//AddSeparator();
	//AddCheckTool(IDM_ANIMSET_TOGGLECLOTH, *LocalizeUnrealEd("ToggleCloth"), ClothB, wxNullBitmap, *LocalizeUnrealEd("ToggleCloth") );
	//AddTool(IDM_ANIMSET_SOFTBODYGENERATE, *LocalizeUnrealEd("SoftBodyGenerate"), SoftBodyGenerateB, *LocalizeUnrealEd("SoftBodyGenerate") );
	//AddCheckTool(IDM_ANIMSET_SOFTBODYTOGGLESIM, *LocalizeUnrealEd("SoftBodyToggleSim"), SoftBodyToggleSimB, wxNullBitmap, *LocalizeUnrealEd("SoftBodyToggleSim") );
	//AddSeparator();
	//AddCheckTool(IDM_ANIMSET_ShowRawAnimation, *LocalizeUnrealEd("ShowUncompressedAnimation"), ShowRawAnimationB, wxNullBitmap, *LocalizeUnrealEd("ShowUncompressedAnimation") );
	//AddCheckTool(IDM_ANIMSET_OpenAnimationCompressionDlg, *LocalizeUnrealEd("AnimationCompressionSettings"), ShowCompressedAnimationB, wxNullBitmap, *LocalizeUnrealEd("AnimationCompressionSettings") );
	//AddSeparator();
	//AddControl(LODLabel);
	//AddRadioTool(IDM_ANIMSET_LOD_AUTO, *LocalizeUnrealEd("SetLODAuto"), LODAutoB, wxNullBitmap, *LocalizeUnrealEd("SetLODAuto") );
	//AddRadioTool(IDM_ANIMSET_LOD_BASE, *LocalizeUnrealEd("ForceLODBaseMesh"), LODBaseB, wxNullBitmap, *LocalizeUnrealEd("ForceLODBaseMesh") );
	//AddRadioTool(IDM_ANIMSET_LOD_1, *LocalizeUnrealEd("ForceLOD1"), LOD1B, wxNullBitmap, *LocalizeUnrealEd("ForceLOD1") );
	//AddRadioTool(IDM_ANIMSET_LOD_2, *LocalizeUnrealEd("ForceLOD2"), LOD2B, wxNullBitmap, *LocalizeUnrealEd("ForceLOD2") );
	//AddRadioTool(IDM_ANIMSET_LOD_3, *LocalizeUnrealEd("ForceLOD3"), LOD3B, wxNullBitmap, *LocalizeUnrealEd("ForceLOD3") );
	//ToggleTool(IDM_ANIMSET_LOD_AUTO, true);
	//AddSeparator();
	//AddControl(ChunksLabel);
	//ChunkComboBox = new WxComboBox( this, IDM_ANIMSET_CHUNKS, TEXT(""), wxDefaultPosition, wxSize( 40, -1 ), 0, NULL, wxCB_READONLY );
	//AddControl( ChunkComboBox );
	//AddControl(SectionsLabel);
	//SectionComboBox = new WxComboBox( this, IDM_ANIMSET_SECTIONS, TEXT(""), wxDefaultPosition, wxSize( 40, -1 ), 0, NULL, wxCB_READONLY );
	//AddControl( SectionComboBox );
	AddSeparator();
	AddRadioTool(IDM_ANIMSET_SPEED_200,	wxT(""), Speed200B, wxNullBitmap, wxT(""));
	AddRadioTool(IDM_ANIMSET_SPEED_175,	wxT(""), Speed125B, wxNullBitmap, wxT(""));
	AddRadioTool(IDM_ANIMSET_SPEED_150,	wxT(""), Speed125B, wxNullBitmap, wxT(""));
	AddRadioTool(IDM_ANIMSET_SPEED_125,	wxT(""), Speed125B, wxNullBitmap, wxT(""));
	AddRadioTool(IDM_ANIMSET_SPEED_100,	*LocalizeUnrealEd("FullSpeed"), Speed100B, wxNullBitmap, *LocalizeUnrealEd("FullSpeed") );
	AddRadioTool(IDM_ANIMSET_SPEED_50,	*LocalizeUnrealEd("50Speed"), Speed50B, wxNullBitmap, *LocalizeUnrealEd("50Speed") );
	AddRadioTool(IDM_ANIMSET_SPEED_25,	*LocalizeUnrealEd("25Speed"), Speed25B, wxNullBitmap, *LocalizeUnrealEd("25Speed") );
	AddRadioTool(IDM_ANIMSET_SPEED_10,	*LocalizeUnrealEd("10Speed"), Speed10B, wxNullBitmap, *LocalizeUnrealEd("10Speed") );
	AddRadioTool(IDM_ANIMSET_SPEED_1,	*LocalizeUnrealEd("1Speed"), Speed1B, wxNullBitmap, *LocalizeUnrealEd("1Speed") );
	ToggleTool(IDM_ANIMSET_SPEED_100, true);
	AddSeparator();

	//wxBitmapButton* ResetCameraPostionButton = new wxBitmapButton( this, IDM_RESET_CAMERA_POSITION, ResetCameraPostion);
	//AddControl(ResetCameraPostionButton);
	AddTool(IDM_RESET_CAMERA_POSITION, ResetCameraPostion, wxT(""));
	AddTool(IDM_ROTATE_CAMERA, RotateCamera, wxT("Rotate Camera"));
	AddSeparator();

	AddTool(IDM_MODEL_EDITOR_REFRESH, Refresh, wxT("Reload"));
	AddSeparator();

	AddCheckTool(IDM_MODEL_SHOW_COLLISION, wxT("Toggle Show Collision"), ShowCollision, wxNullBitmap);
	ToggleTool(IDM_MODEL_SHOW_COLLISION, TRUE);
	AddSeparator();

	AddTool(IDM_EXPORT_MERGED_DATA, ExportData, wxT("Export Data"));
	AddSeparator();


	//ProgressiveDrawingSlider = new wxSlider( this, IDM_ANIMSET_PROGRESSIVESLIDER, 10000, 0, 10000 );
	//AddControl(ProgressiveDrawingSlider);
	//AddSeparator();
	//AddCheckTool(IDM_ANIMSET_VIEWALTBONEWEIGHTINGMODE, *LocalizeUnrealEd("ShowAltBoneWeightingEdit"), GoreMode, wxNullBitmap, *LocalizeUnrealEd("ShowAltBoneWeightingEdit") );
	//AddSeparator();
	//wxStaticText* VertexInfo = new wxStaticText(this, -1 ,*LocalizeUnrealEd("ShowVertexInfo") );
	//AddControl(VertexInfo);
	//ChunkList = new wxComboBox( this, IDM_ANIMSET_SELECTCHUNKINDEX, TEXT(""), wxDefaultPosition, wxSize(30, 10), 0, NULL, wxCB_READONLY );
	//AddControl(ChunkList);
	//AddCheckTool(IDM_ANIMSET_VERTEX_SHOWTANGENT, *LocalizeUnrealEd("ShowTangent"), TangentMode, wxNullBitmap, *LocalizeUnrealEd("ShowTangent") );
	//AddCheckTool(IDM_ANIMSET_VERTEX_SHOWNORMAL, *LocalizeUnrealEd("ShowNormal"), NormalMode, wxNullBitmap, *LocalizeUnrealEd("ShowNormal") );
	//AddSeparator();
	
	//ColorOption = new wxComboBox( this, IDM_ANIMSET_VERTEX_COLOROPTION, TEXT(""), wxDefaultPosition, wxSize(50, 10), 0, NULL, wxCB_READONLY );
	//ColorOption->Append(TEXT("None"));
	//ColorOption->Append(TEXT("Tangent"));
	//ColorOption->Append(TEXT("Normal"));
	//ColorOption->Append(TEXT("Mirror"));
	//AddControl(ColorOption);

	//AddCheckTool(IDM_ANIMSET_TRIANGLESORTMODE, *LocalizeUnrealEd("TriangleSortMode"), TriangleSortMode, wxNullBitmap, *LocalizeUnrealEd("TriangleSortMode") );
	//AddCheckTool(IDM_ANIMSET_TRIANGLESORTMODELR, *LocalizeUnrealEd("TriangleSortModeLR"), TriangleSortModeL, wxNullBitmap, *LocalizeUnrealEd("TriangleSortModeLR") );
	//EnableTool(IDM_ANIMSET_TRIANGLESORTMODELR,FALSE);

	//AddSeparator();
	//ActiveListenBitmap.Load(TEXT("VisibilityEyeOn.png"));
	//AddCheckTool(IDM_ANIMSET_ACTIVELY_LISTEN_FOR_FILE_CHANGES, *LocalizeUnrealEd("AnimSetEditor_ActiveListen"), ActiveListenBitmap, wxNullBitmap, *LocalizeUnrealEd("AnimSetEditor_ActiveListen") );
	//ToggleTool(IDM_ANIMSET_ACTIVELY_LISTEN_FOR_FILE_CHANGES, GEditor->AccessUserSettings().bAutoReimportAnimSets);

	//AddSeparator();
	//FOVResetBitmap.Load(TEXT("FOVReset.png"));
	//AddTool(IDM_ANIMSET_FOVRESET, FOVResetBitmap, *LocalizeUnrealEd("FOVReset") );
	//FOVSlider = new wxSlider( this, IDM_ANIMSET_FOVSLIDER, ( GEditor ? ((INT)GEditor->FOVAngle) : 90 ), 5, 170, wxDefaultPosition, wxSize( 165, -1 ) );	// min/max limits enforced by unreal
	//AddControl(FOVSlider);

	Realize();
}
/**
 * @return		The size of the raw animation data in the specified animset.
 */
static INT GetRawSize(const UAnimSet& AnimSet)
{
	INT ResourceSize = 0;
	for( INT SeqIndex = 0 ; SeqIndex < AnimSet.Sequences.Num() ; ++SeqIndex )
	{
		ResourceSize += AnimSet.Sequences(SeqIndex)->GetApproxRawSize();
	}
	return ResourceSize;
}

/**
 * @return		The size of the compressed animation data in the specified animset.
 */
static INT GetCompressedSize(const UAnimSet& AnimSet)
{
	INT ResourceSize = 0;
	for( INT SeqIndex = 0 ; SeqIndex < AnimSet.Sequences.Num() ; ++SeqIndex )
	{
		ResourceSize += AnimSet.Sequences(SeqIndex)->GetApproxCompressedSize();
	}
	return ResourceSize;
}

/** Helper function */
static INT GetWxListSelectedItem(wxListBoxBase& ListBox)
{
	wxArrayInt Selection;
	ListBox.GetSelections(Selection);
	
	if( Selection.Count() > 0 )
	{
		return Selection.Item(0);
	}

	return INDEX_NONE;
}