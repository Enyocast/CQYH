/*============================================================================
	AnimSetViewer.h: AnimSet viewer
	Copyright 1998-2013 Epic Games, Inc. All Rights Reserved.
=============================================================================*/

#ifndef __MODELEDITOR_H__
#define __MODELEDITOR_H__

#include "SocketManager.h"
#include "TrackableWindow.h"
#include "AnimationUtils.h"

#include "NvApexManager.h"
#include "AnimSetViewer.h"

// Forward declarations.
class UAnimNodeMirror;
class UAnimNodeSequence;
class UAnimSequence;
class UAnimSet;
class UAnimTree;
class UMorphNodeMultiPose;
class UMorphTarget;
class UMorphTargetSet;
class WxModelViewer;
class WxModelPreview;
class WxDlgAnimationCompression;
class WxPropertyWindow;
class WxSocketManager;
class WxSkeletalMeshSimplificationWindow;
class UAvatarData;
class UDataCheck;
enum  EMorphImportError;

/**
 * Viewport client for the AnimSet viewer.
 */
struct FEditorModelViewportClient: public FEditorLevelViewportClient
{
	//////////////////////////////////////////////////////////////////////////

	FPreviewScene				PreviewScene;
	FEditorCommonDrawHelper		DrawHelper;

	WxModelViewer*				ModelViewer;

	UBOOL						bShowBoneNames;
	UBOOL						bShowFloor;
	UBOOL						bShowSockets;
	UBOOL						bShowWindDir;
	UBOOL						bShowMorphKeys;
	UBOOL						bTriangleSortMode;

	UBOOL						bManipulating;
	EAxis						SocketManipulateAxis;
	EAxis						BoneManipulateAxis;
	FLOAT						DragDirX;
	FLOAT						DragDirY;
	FVector						WorldManDir;
	FVector						LocalManDir;
	ULineBatchComponent*		LineBatcher; // used by NVIDIA PhysX to draw debug visualization info even when inside the ANIM set viewer

	UBOOL						bDraggingTrackPos;
	INT							DraggingNotifyIndex;
	UBOOL						bDraggingNotifyTail;
	INT							DraggingMetadataIndex;
	INT							DraggingMetadataKeyIndex;

#if WITH_SIMPLYGON
	UTexture2D*					SimplygonLogo;
#endif // #if WITH_SIMPLYGON


	// 0~3 : front, left, back, right
	INT PositionType;
	DOUBLE CameraStartTime;

	UAvatarData* ViewObj;


	

	FEditorModelViewportClient(WxModelViewer* InASV);
	virtual ~FEditorModelViewportClient();


	void SetViewModel(UObject* InObj);

	void AttachSkeletalMesh( USkeletalMeshComponent* InParent, USkeletalMesh* ChildMesh, const FTranslationMatrix& ftm );

	void SetCameraPosition(int InPositionType);
	void SetCameraPosition(FVector& InLocation, FRotator& InRotation);

	
	//////////////////////////////////////////////////////////////////////////
	// FEditorLevelViewportClient interface

	virtual FSceneInterface* GetScene() { return PreviewScene.GetScene(); }
	virtual FLinearColor GetBackgroundColor();
	virtual void Draw(const FSceneView* View,FPrimitiveDrawInterface* PDI);
	virtual void Draw(FViewport* Viewport, FCanvas* Canvas);
	virtual void Tick(FLOAT DeltaSeconds);

	virtual UBOOL InputKey(FViewport* Viewport, INT ControllerId, FName Key, EInputEvent Event,FLOAT AmountDepressed = 1.f,UBOOL bGamepad=FALSE);
	virtual UBOOL InputAxis(FViewport* Viewport, INT ControllerId, FName Key, FLOAT Delta, FLOAT DeltaTime, UBOOL bGamepad=FALSE);
	virtual void MouseMove(FViewport* Viewport,INT x, INT y);

	virtual void Serialize(FArchive& Ar);

	// FEditorAbilityViewportClient interface
	void DrawWindDir(FViewport* Viewport, FCanvas* Canvas);
};

/*-----------------------------------------------------------------------------
	WxASVToolBar
-----------------------------------------------------------------------------*/

class WxMVToolBar : public WxToolBar
{
public:
	WxMVToolBar( wxWindow* InParent, wxWindowID InID );


private:
	//WxMaskedBitmap SocketMgrB;
	//WxMaskedBitmap ShowBonesB;
	//WxMaskedBitmap ShowBoneNamesB;
	//WxMaskedBitmap ShowWireframeB;
	//WxMaskedBitmap ShowRefPoseB;
	//WxMaskedBitmap ShowMirrorB;
	//WxMaskedBitmap NewNotifyB;
	//WxMaskedBitmap ClothB;
	//WxMaskedBitmap SoftBodyGenerateB;
	//WxMaskedBitmap SoftBodyToggleSimB;

	//WxMaskedBitmap ShowRawAnimationB;
	//WxMaskedBitmap ShowCompressedAnimationB;

	//WxMaskedBitmap LODAutoB;
	//WxMaskedBitmap LODBaseB;
	//WxMaskedBitmap LOD1B;
	//WxMaskedBitmap LOD2B;
	//WxMaskedBitmap LOD3B;

	WxMaskedBitmap Speed1B;
	WxMaskedBitmap Speed10B;
	WxMaskedBitmap Speed25B;
	WxMaskedBitmap Speed50B;
	WxMaskedBitmap Speed100B;
	WxMaskedBitmap Speed125B;
	WxMaskedBitmap Speed150B;
	WxMaskedBitmap Speed175B;
	WxMaskedBitmap Speed200B;

	WxBitmap	Refresh;
	WxBitmap	ResetCameraPostion;
	WxBitmap	RotateCamera;

	WxMaskedBitmap ShowCollision;

	WxBitmap	ExportData;

	//WxMaskedBitmap GoreMode;
	//WxMaskedBitmap TangentMode;
	//WxMaskedBitmap NormalMode;
	//WxMaskedBitmap TriangleSortMode;

	//WxBitmap ActiveListenBitmap;
	//WxBitmap FOVResetBitmap;

	//wxSlider* ProgressiveDrawingSlider;

public:
	//wxSlider* FOVSlider;
	//WxMaskedBitmap TriangleSortModeL;
	//WxMaskedBitmap TriangleSortModeR;

	//WxComboBox* ChunkComboBox;
	//WxComboBox* SectionComboBox;

	DECLARE_EVENT_TABLE()
};


/*-----------------------------------------------------------------------------
	WxASVMenuBar
-----------------------------------------------------------------------------*/

class WxMEMenuBar : public wxMenuBar
{
public:
	WxMEMenuBar();

	wxMenu*	ViewMenu;
	wxMenu* EditMenu;
	wxMenu*	CheckMenu;
};




/*-----------------------------------------------------------------------------
	WxASVPreview
-----------------------------------------------------------------------------*/

/**
 * A wxWindows container for FCascadePreviewViewportClient.
 */
class WxModelPreview : public wxWindow
{
public:
	FEditorModelViewportClient* ASVPreviewVC;

	WxModelPreview(wxWindow* InParent, wxWindowID InID, class WxModelViewer* InASV);
	~WxModelPreview();

	/**
	 * Calls DestoryViewport(), then creates a new viewport client and associated viewport.
	 */
	void CreateViewport(class WxModelViewer* InASV);

	/**
	 * Destroys any existing viewport client and associated viewport.
	 */
	void DestroyViewport();

	void SetViewModel(UObject* InObj);

private:
	void OnSize( wxSizeEvent& In );	
	DECLARE_EVENT_TABLE()
};


class WxModelViewer : public WxTrackableFrame, public FNotifyHook, public FSerializableObject, public FDockingParent, public FCallbackEventDevice
{
	// new property
public:
	WxPropertyWindowHost*	MasterProperty;
	WxPropertyWindowHost*	SecondProperty;

	WxModelPreview*	PreviewWindow;
	wxSplitterWindow*	BaseWindow;
	wxSplitterWindow*	LeftArea;
	wxSplitterWindow*	RightArea;

	wxStaticText*	AvatarNameText;
	wxStaticText*	SkelMeshText;
	wxStaticText*	AnimTreeText;
	wxStaticText*	PhyAssetText;
	wxComboBox*		WeaponTypeComboBox;
	wxListBox*		AnimSetListBox;
	wxListBox*		AnimSeqListBox;




	wxMenu*				AddMenu;

	UObject*			ModelObject;
	UAvatarData*		AvatarObject;
	UDataCheck*			CheckData;

	FLOAT	CurrentPlayTime;

	UBOOL bPlaying;
	UBOOL bLooping;

private:

	// 0~3 : front, left, back, right
	int CameraPositionType;


public:
	
	WxModelViewer(wxWindow* InParent, wxWindowID InID, UObject* EditObj);

	void ResetObject(UObject* InObject);
	void UpdateMaterial();
	void UpdateAnimInfos();
	void UpdateAttachment();
	void SetWeaponIdx(int idx);
	void SetAnimSet(int idx);
	void SetAnimSeq(int idx);

	UAnimSet* GetCurrentAnimSet();
	UAnimSequence* GetCurrentAnimSeq();

	void SetSelectedSkelMesh(USkeletalMesh* InSkelMesh, UBOOL bClearMorphTarget, UBOOL bReselectAnimSet = TRUE);

	void OnSpeed(wxCommandEvent& In);

	void OnLoopAnim(wxCommandEvent& In);
	void OnPlayAnim(wxCommandEvent& In);

	void OnResetCameraPosition(wxCommandEvent& In);
	void OnRotateCamera(wxCommandEvent& In);
	void OnRefreshData(wxCommandEvent& In);
	void OnTimeScrub( wxScrollEvent& In );
	void OnWeaponTypeComboChanged( wxCommandEvent& In );
	void OnAnimSetListChanged( wxCommandEvent& In );
	void OnAnimSeqListChanged( wxCommandEvent& In );

	// menu event
	void OnGenerateCollision( wxCommandEvent& In );
	void OnDuplicateDeadEffects(wxCommandEvent& In);
	void OnResizeToMaleWarrior(wxCommandEvent& In);
	void OnShowCollision( wxCommandEvent& In );
	void OnCheckAnim( wxCommandEvent& In );
	void OnCheckPhysic( wxCommandEvent& In );
	void OnCheckSocketCommon( wxCommandEvent& In );
	void OnCheckSocketHand( wxCommandEvent& In );
	void OnCheckSocketWeapon( wxCommandEvent& In );

	void OnExportData( wxCommandEvent& In );

	// 
	void GenerateCollision(); 

	void ReplacateComponents(BYTE* InAddr, UObject* InTemplate);
	void DuplicateComponents(UProperty* InProperty, BYTE* InAddr);

public:
	WxMVToolBar*			ToolBar;
	WxMEMenuBar*			MenuBar;

	USkeletalMesh*			SelectedSkelMesh;
	UAnimSet*				SelectedAnimSet;
	UAnimSequence*			SelectedAnimSeq;
	UMorphTargetSet*		SelectedMorphSet;
	USkeletalMeshSocket*	SelectedSocket;
	TArray<UMorphTarget*>	SelectedMorphTargets;
	
	/** The main preview SkeletalMeshComponent.  Always plays compressed animation, if present. */
	USkeletalMeshComponent*		PreviewSkelComp;
	USkeletalMeshComponent* PreviewMergedComp;
	UCylinderComponent*		CollisionBoxComponent;
	UAnimTree*				PreviewAnimTree;
	UAnimNodeSequence*		PreviewAnimNode;
	UAnimNodeMirror*		PreviewAnimMirror;
	UMorphNodeMultiPose*	PreviewMorphPose;

	TArray<USkeletalMeshComponent*> BaseSkelMeshCompList;

	FMatrix					TargetLocalToWorld;

	//A floor for interacting with physics
	UStaticMeshComponent*	EditorFloorComp;

	FRBPhysScene*			RBPhysScene;
	FRotator				WindRot;
	FLOAT					WindStrength;
#if WITH_APEX
	FLOAT					WindVelocityBlendTime;
#endif
	/** Bone manipulation */
	EASVSocketMoveMode		BoneMoveMode;

	struct FLODInfluenceInfo
	{
		/** Gore mesh / bone influence swapping */
		TSet<INT> 				InfluencedBoneVerts;
		/** Vertex indices weighted by a given bone but not part of the vertex influence swap */
		TSet<INT>				NonInfluencedBoneVerts;
		/** Mapping of all bones and the verts weighted to them */
		TArray< TArray<INT> >   BoneVertices;
	};

	TArray<FLODInfluenceInfo> BoneInfluenceLODInfo;

	/** Animation playback speed, in [0.01f,1.0f]. */
	FLOAT					PlaybackSpeed;

	/** Wireframe cycle counter */
	INT						WireframeCycleCounter;
	/** Show Additive Base */
	UBOOL					bShowAdditiveBase;
	/** Whether to actively listen for file changes or not */
	UBOOL					bListenForFileChanges;

	/** Show Vertex Info */
	struct VertexInfoList
	{
		INT		SelectedMaterialIndex;
		UBOOL	bShowTangent;
		UBOOL	bShowNormal;
		INT		ColorOption; // 0-none, 1-tangent, 2-normal, 3-mirror
		INT		SelectedVertexIndex;
		FVector	SelectedVertexPosition;
		TArray<INT>		BoneIndices;
		TArray<FLOAT>	BoneWeights;
	};

	VertexInfoList			VertexInfo;

	/** If TRUE, show per-vertex scaling of how far a cloth vert can move from its animated vertex pos. */
	UBOOL					bShowClothMovementScale;

	// Various wxWindows controls
	WxBitmap				AddComponentB, AbilityTimeAdd, AbilityTimeSub, SpellImage, CastImage, StopB, PlayB, LoopB, NoLoopB, UseButtonB, SearchAllB, ClearB, ClearDisabledB;

	wxComboBox*				AnimSetCombo;
	wxBitmapButton*			AnimSeqSearchAllButton;
	wxTextCtrl*				AnimSeqFilter;
	wxListBox*				AnimSeqList;
	wxTimer					AnimSeqFilterTimer;
	
	wxComboBox*				MorphSetCombo;
	
	WxMorphTargetPane*		MorphTargetPanel;

	wxNotebook*				PropNotebook;
	wxNotebook*				ResourceNotebook;
	wxSlider*				TimeSlider;
	wxBitmapButton*			PlayButton;
	wxBitmapButton*			LoopButton;

	WxPropertyWindowHost*		MeshProps;
	WxPropertyWindowHost*		AnimSetProps;
	WxPropertyWindowHost*		AnimSeqProps;
	WxPropertyWindowHost*		MorphTargetProps;

#if WITH_SIMPLYGON
	WxSkeletalMeshSimplificationWindow* SimplificationWindow;
#endif // #if WITH_SIMPLYGON

	WxSocketManager*				SocketMgr;
	//TArray<FASVSocketPreview>		SocketPreviews;

	WxDlgAnimationCompression*		DlgAnimationCompression;

	/** Toggle usage of instance weights on the preview mesh */
	UBOOL					bPreviewInstanceWeights;
	/** Toggle visibility of all vertices on mesh while editing bone influences */
	UBOOL					bDrawAllBoneInfluenceVertices;
	/** The UV Set index we are currently displaying.  -1 if we should not display any UVs. */
	INT						UVSetToDisplay;

	/** Stores the currently selected sort strip */
	INT		SelectedSortStripIndex;
	INT		SelectedSortStripLodIndex;
	INT		SelectedSortStripSectionIndex;
	INT		MouseOverSortStripIndex;
	UBOOL	bSortStripMoveForward;
	UBOOL	bSortStripMoveBackward;

	/** Flag to indicate the AnimNotify data needs to be resampled */
	UBOOL bResampleAnimNotifyData;

	/** Determines if the user can search through all anim sequences in the sequence combo box. */
	UBOOL bSearchAllAnimSequences;
	/** Flag to indicate if the user turned on the option to view all anim sequences at least once. */
	UBOOL bPromptUserToLoadAllAnimSets;

	virtual ~WxModelViewer();

	/**
	 * This function is called when the window has been selected from within the ctrl + tab dialog.
	 */
	virtual void OnSelected();

	/**
	* Called once to load AnimSetViewer settings, including window position.
	*/
	void LoadSettings();

	/**
	* Writes out values we want to save to the INI file.
	*/
	void SaveSettings();

	/**
	 * Returns a handle to the anim set viewer's preview viewport client.
	 */
	FEditorModelViewportClient* GetPreviewVC();

	/** Returns the current LOD index being viewed. */
	INT GetCurrentLODIndex() const;

	// FSerializableObject interface
	void Serialize(FArchive& Ar);

	// Menu handlers
	/**
	 *	Called when a SIZE event occurs on the window
	 *
	 *	@param	In		The size event information
	 */
	void OnSize( wxSizeEvent& In );
	void OnMenuEditUndo( wxCommandEvent& In );
	void OnMenuEditRedo( wxCommandEvent& In );

	void OnSkelMeshUse( wxCommandEvent& In );
	void OnAnimSetUse( wxCommandEvent& In );

	void OnViewFloor( wxCommandEvent& In );
	void OnViewGrid( wxCommandEvent& In );
	void OnViewCollision( wxCommandEvent& In );
	void OnViewWireframe(wxCommandEvent& In);

	void ClearSocketPreviews();
	void RecreateSocketPreviews();
	void UpdateSocketPreviews();

	// update LOD menu based on PreviewSkelComp->ForcedLODModel
	// enable/disable some menu sets for alternative bone weighting
	void UpdateForceLODMenu();
	void UpdateAltBoneWeightingMenu();

	/**
	 * Refreshes the chunk preview toolbar combo box w/ a listing of chunks belonging to the current LOD
	 */
	void UpdateChunkPreview();
	/**
	 * Sets the index of the chunk to preview
	 */
	void PreviewChunk(INT ChunkIdx);
	/**
	 * Refreshes the section preview toolbar combo box w/ a listing of sections belonging to the current LOD
	 */
	void UpdateSectionPreview();
	/**
	 * Sets the index of the section to preview
	 */
	void PreviewSection(INT SectionIdx);

	// Skeleton Tree Manager
	void FillSkeletonTree();
	void OnFillSkeletonTree(wxCommandEvent &In);
	void OnSkeletonTreeItemRightClick(wxTreeEvent& In);
	/*
	 * Callback when the skeleton tree control items are selected/deselected
	 * @param In - Event parameter data
	 */
	void OnSkeletonTreeSelectionChange(wxTreeEvent& In);
	void OnSkeletonTreeMenuHandleCommand(wxCommandEvent &In);

	/*
	 *  Update the bones of interest in the viewer for blendweight viewing/bone manipulation
	 *  @param NewBoneIndex - bone clicked on in the tree view (since GetSelections isn't always accurate at time of calling)
	 */
	void UpdateBoneManipulationControl(INT NewBoneIndex);

	/*
	 * Get a list of vertex indices that reference equivalent vertex positions in the skeletal mesh
	 * @param LODIdx - mesh LOD to compare against
	 * @param InfluenceIdx - influence track to compare against
	 * @param VertCheckIndex - vertex index to check against
	 * @param EquivalentVertices - array of vertex indices to fill in
	 * @return Count of vertices found to be equivalent
	 */
	INT GetEquivalentVertices(INT LODIdx, INT InfluenceIdx, INT VertCheckIndex, TArray<INT>& EquivalentVertices);
	
	/*
	 *   Calculate the bone to vert list mapping and clear out related data
	 * @param SelectedSkelMesh - mesh of interest
	 */
	void InitBoneWeightInfluenceData(const USkeletalMeshComponent* SkelComp);

	/*
	 *   Update the state of a single vertex in the skeletal mesh
	 * @param LODIdx - LOD this vertex applies to 
	 * @param InfluenceIdx - Influence track to swap
	 * @param VertIdx - Vertex Index to swap
	 * @param bContributingInfluence - whether to swap in (TRUE) or swap back (FALSE)
	 */
	void UpdateInfluenceWeight(INT LODIdx, INT InfluenceIdx, INT VertIndex, UBOOL bContributingInfluence);

	/*
	 * Update the bone influence weights on the skeletal mesh for bone pairs specified
	 * @BonesOfInterest - array of bone indices to update
	 */
	void UpdateInfluenceWeights(const TArray<INT>& BonesOfInterest);

	/** Toggles the modal animation Animation compression dialog. */
	void OnOpenAnimationCompressionDlg(wxCommandEvent& In);

	/** Updates the contents of the status bar, based on e.g. the selected set/sequence. */
	void UpdateStatusBar();

	/** Updates the contents of the status bar, based on e.g. the selected set/sequence. */
	void UpdateMaterialList();

	/** Slides the progressive drawing slider */
	void OnProgressiveSliderChanged(wxScrollEvent & In);

	/** Resets the FOV slider */
	void OnFOVReset( wxCommandEvent& In );

	/** Slides the FOV slider */
	void OnFOVSliderChanged(wxScrollEvent & In);

	/** Sets the FOV and updated the icons */
	void SetFOV(const INT iFOV);

	// Tools
	void SetSelectedMorphSet(UMorphTargetSet* InMorphSet, UBOOL bAutoSelectMesh);
	void UpdateSelectedMorphTargets();

	void ImportPSA();

#if WITH_FBX
	void ImportFbxAnim();
	void ExportFbxAnim();
#endif // WITH_FBX
	void ImportMeshLOD();
	UBOOL ImportMeshLOD(USkeletalMesh* InSkeletalMesh,INT DesiredLOD);
	void ImportMeshWeights();
	
	/**
	* Displays and handles dialogs necessary for importing 
	* a new morph target mesh from file. The new morph
	* target is placed in the currently selected MorphTargetSet
	*
	* @param bImportToLOD - if TRUE then new files will be treated as morph target LODs 
	* instead of new morph target resources
	*/
	void ImportMorphTarget(UBOOL bImportToLOD, UBOOL UseImportName);
	
	void CreateNewAnimSet();
	void UpdateAnimSeqList();
	void UpdateAnimSetCombo();
	void UpdateMorphTargetList();
	void UpdateMorphSetCombo();
	void RefreshPlaybackUI();
	FLOAT GetCurrentSequenceLength();
	void TickViewer(FLOAT DeltaSeconds);
	void EmptySelectedSet();
	void DeleteTrackFromSelectedSet();
	void DeleteMorphTrackFromSelectedSet();
	void CopyTranslationBoneNamesToAnimSet();
	void AnalyzeAnimSet();
	void RenameSelectedSeq();
	void RemovePrefixFromSequences();
	void DeleteSelectedSequence();
	UBOOL VerifyAdditiveSequencesToMove(TArray<UAnimSequence*>& Sequences, UAnimSet* DestAnimSet, UBOOL bMove);
	INT RemoveAdditiveSequences(TArray<UAnimSequence*>& Sequences, TArray<UAnimSequence*>& SequencesToRemove, UBOOL bRemoveAdditive=TRUE, UBOOL bRemoveBase=TRUE);
	void CopySelectedSequence();
	void MoveSelectedSequence();
	void MakeSelectedSequencesAdditive();
	void RebuildAdditiveAnimation();
	void AddAdditiveAnimationToSelectedSequence(UBOOL bPerformSubtraction);
	UBOOL AddAdditiveAnimation(UAnimSequence* SourceAnimSeq, UAnimSequence* AdditiveAnimSeq, UAnimSequence* DestAnimSeq, USkeletalMesh* SkelMesh, FName AnimationName, EAddAdditive BuildMethod, UBOOL bPerformSubtraction);
	UBOOL CopyAnimSequence(UAnimSequence* SourceAnimSeq, UAnimSequence *DestAnimSeq, UAnimSet* SourceAnimSet, UAnimSet* DestAnimSet, USkeletalMesh* FillInMesh);
	void SequenceApplyRotation();
	void SequenceReZeroToCurrent();
	void SequenceCrop(UBOOL bFromStart=true);
	void SequenceCrop(FLOAT RemoveTimeLen, UBOOL bFromStart=true);
	void UpdateMeshBounds();
	void UpdateSkelComponents();
	void UpdateForceLODButtons();
	void RenameMorphTarget(const INT Index, const TCHAR * NewName);
	void UpdateMorphTargetWeight(const INT Index, const FLOAT Weight);
	void ResetMorphTargets();
	void DeleteSelectedMorphTarget();
	void RemapVerticesSelectedMorphTarget();
	void UpdateClothWind();

	/**
	 *	Update the preview window.
	 */
	void UpdatePreviewWindow();

	// Notification hook.
	virtual void NotifyDestroy( void* Src );
	virtual void NotifyPreChange( void* Src, UProperty* PropertyAboutToChange );
	virtual void NotifyPostChange( void* Src, UProperty* PropertyThatChanged );
	virtual void NotifyExec( void* Src, const TCHAR* Cmd );

	// Undo/Redo support
	bool BeginTransaction(const TCHAR* pcTransaction);
	bool EndTransaction(const TCHAR* pcTransaction);
	void UndoTransaction();
	void RedoTransaction();
	bool TransactionInProgress();

	/**
	 * Event wrapper around copying selected animseq to the clipboard
	 */
	void OnCopySelectedAnimSeqToClipboard(wxCommandEvent& In);

	/** Handle global file changed events. */
	virtual void Send( ECallbackEventType InType, const FString& InString, UObject* InObject);

protected:
	/**
	 *	This function returns the name of the docking parent.  This name is used for saving and loading the layout files.
	 *  @return A string representing a name to use for this docking parent.
	 */
	virtual const TCHAR* GetDockingParentName() const;

	/**
	 * @return The current version of the docking parent, this value needs to be increased every time new docking windows are added or removed.
	 */
	virtual const INT GetDockingParentVersion() const;

	/**
	 * Populates all the anim sequences in the given anim set to the anim sequence list. 
	 *
	 * @param	SetToAdd	The anim set containing sequences to add. 
	 */
	void AddAnimSequencesToList( UAnimSet* SetToAdd );

	// Undo/Redo support
	bool	bTransactionInProgress;
	FString	kTransactionName;

private:

	/**
	 * Updates the visibility and collision of the floor
	 */
	void UpdateFloorComponent(void);

#if WITH_FBX
    /**
     * Import Morph Target and Target LOD from FBX file.
     * Compare to PSK file, we can import several meshes for FBX file in one time.
     * @param bImportToLOD - if TRUE then new files will be treated as morph target LODs instead of morph targets
     * @param bUseImportName - if TRUE then morph target will be named as file name. This option is meaningless when
     *                         import morph target LOD.
     * @param Filename - FBX file name
     * @param ImportError -
     */
    void ImportFbxMorphTarget(UBOOL bImportToLOD, UBOOL bUseImportName, FFilename Filename, EMorphImportError &ImportError);
#endif // WITH_FBX

    /**
     * Display Error when import Morph target or Morph target LODs
     * @param ImportError -
     * @param Filename -
     */
	void DisplayError(EMorphImportError &ImportError, FFilename &Filename);

	// ming@snda
	void CopyTexture( UTexture2DDynamic* SrcTex, UTexture2D* DstTex );

	DECLARE_EVENT_TABLE()
};

#endif // __ABILITYEDITOR_H__
