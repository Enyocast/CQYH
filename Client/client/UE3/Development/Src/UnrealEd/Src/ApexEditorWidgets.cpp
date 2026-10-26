#include "ApexEditorWidgets.h"
#include "EnginePrivate.h"
#include "EngineMeshClasses.h"
// NVCHANGE_BEGIN: JCAO - US9197 Add functions for saving and restoring the expanded items
#include "PropertyWindowManager.h"
// NVCHANGE_END: JCAO - US9197 Add functions for saving and restoring the expanded items
// NVCHANGE_BEGIN: JCAO - US8900 BasicIOS collision channel support
#include "PropertyWindow.h"
// NVCHANGE_END: JCAO - US8900 BasicIOS collision channel support

#if WITH_APEX_EDITOR

#include "NvApexManager.h"
#pragma pack( push, 8 )
#include "PxEditorPanel.h"
#include "PxEditorWidgetManager.h"
#include "PxGenericPropertiesEditorPanel.h"
#include "PxGenericPropertiesEditorPanelDesc.h"
#include "PxCurveEditorPanel.h"
#include "NxParameterized.h"
// NVCHANGE_BEGIN: JCAO - Apex Emitter Asset work with LODs
#include "NxModule.h"
// NVCHANGE_END: JCAO - Apex Emitter Asset work with LODs
#pragma pack( pop )
// NVCHANGE_BEGIN: APAN - Removed Apex 1.2 Fix DE4948 UI button to link an IOS asset to a particle system in Cascade doesn't work anymore
// NVCHANGE_END: APAN - Removed Apex 1.2 Fix DE4948 UI button to link an IOS asset to a particle system in Cascade doesn't work anymore
//#include "GenericBrowser.h"	// zhaojun@snda ??? UE0714
#include "NvApexCommands.h"
#include "NxApexAsset.h"

/*************************
** ApexEditorIdleHandle **
*************************/

// this is just a dummy/invisible window setup to trap the idle event from wx widgets...
class ApexEditorIdleHandle : public wxFrame
{
	public:
		static void ConditionalInitialize(void)
		{
			if(!Instance)
			{
				new ApexEditorIdleHandle;
			}
		}
		
	private:
		ApexEditorIdleHandle(void) :
			wxFrame(0, wxID_ANY, wxT(""))
		{
			Instance = this;
		}
		
		virtual ~ApexEditorIdleHandle(void)
		{
			Instance = 0;
		}
		
		void OnIdle(wxIdleEvent &In)
		{
			physx::PxEditorWidgetManager *WidgetManager = GApexManager->GetPxEditorWidgetManager();
			check(WidgetManager);
			if(WidgetManager)
			{
				WidgetManager->update();
			}
		}
	
	private:
		static ApexEditorIdleHandle *Instance;
	
	private:
		DECLARE_EVENT_TABLE()
};
ApexEditorIdleHandle *ApexEditorIdleHandle::Instance = 0;

BEGIN_EVENT_TABLE(ApexEditorIdleHandle, wxFrame)
    EVT_IDLE(ApexEditorIdleHandle::OnIdle)
END_EVENT_TABLE()

/***************************
** ApexGenericEditorPanel **
***************************/

BEGIN_EVENT_TABLE(ApexGenericEditorPanel, wxPanel)
	EVT_SIZE(ApexGenericEditorPanel::OnSize)
END_EVENT_TABLE()



ApexGenericEditorPanel::ApexGenericEditorPanel(wxWindow &parent) :
	wxPanel(&parent)
{
	EditorPanel     = NULL;
	mNeedsReset		= FALSE;
	
	ApexEditorIdleHandle::ConditionalInitialize(); // make sure we process idle events...
	InitializeApex();
	
	physx::PxEditorWidgetManager *WidgetManager = GApexManager->GetPxEditorWidgetManager();
	check(WidgetManager);
	if(WidgetManager)
	{
		physx::PxGenericPropertiesEditorPanelDesc PanelDesc;
		PanelDesc.parentWindow = (HWND)GetHWND();
		PanelDesc.GameScale = 50;
		PanelDesc.callback     = this;
		EditorPanel = WidgetManager->createGenericPropertiesEditor(PanelDesc);
		check(EditorPanel);
	}

	AddCustomHints();

	mConvertedNameSize = 0;
	mConvertedName = NULL;
}

ApexGenericEditorPanel::~ApexGenericEditorPanel(void)
{
	if(EditorPanel)     EditorPanel->release();
	for (INT i=0; i<EditObjects.Num(); i++)
	{
		ApexEditObject &a = EditObjects(i);
		if ( a.AssetProperties )
		{
			UBOOL kill = TRUE;
			if ( a.EditNotify )
			{
				kill = a.EditNotify->NotifyEditorClosed(a.AssetProperties);
			}
			if ( kill )
			{
				a.AssetProperties->destroy();
			}
			// NVCHANGE_BEGIN: JCAO - Fix DE5806 Crash when clicking on a Required module in Cascade
			a.EditNotify = NULL;
			a.AssetProperties = NULL;
			// NVCHANGE_END: JCAO - Fix DE5806 Crash when clicking on a Required module in Cascade
		}
	}
	// NVCHANGE_BEGIN: JCAO - Fix DE5806 Crash when clicking on a Required module in Cascade
	EditObjects.Empty();
	// NVCHANGE_END: JCAO - Fix DE5806 Crash when clicking on a Required module in Cascade

	if (mConvertedName != NULL)
	{
		delete[] mConvertedName;
	}
}

void ApexGenericEditorPanel::ClearProperties(void)
{
	if(EditorPanel) EditorPanel->clearObjects();
	for (INT i=0; i<EditObjects.Num(); i++)
	{
		ApexEditObject &a = EditObjects(i);
		if ( a.AssetProperties )
		{
			UBOOL kill = true;
			if ( a.EditNotify )
			{
				kill = a.EditNotify->NotifyEditorClosed(a.AssetProperties);
			}
			if ( kill )
			{
				a.AssetProperties->destroy();
			}
			// NVCHANGE_BEGIN: JCAO - Fix DE5806 Crash when clicking on a Required module in Cascade
			a.EditNotify = NULL;
			// NVCHANGE_END: JCAO - Fix DE5806 Crash when clicking on a Required module in Cascade
			a.AssetProperties = NULL;
		}
	}
	EditObjects.Empty();
}

void ApexGenericEditorPanel::AddObject(UApexGenericAsset &ApexAsset)
{
	if(EditorPanel)
	{
		ApexEditObject ae;
		ae.AssetProperties = (NxParameterized::Interface*)ApexAsset.GetAssetNxParameterized();
		if(ae.AssetProperties)
		{
			ae.AssetObject = &ApexAsset;
			EditorPanel->addObject("ApexAsset", *ae.AssetProperties);
			EditObjects.AddItem(ae);
			ApexAsset.NotifyApexEditMode(this);
		}
	}
}

void ApexGenericEditorPanel::AddObject(NxParameterized::Interface *object,ApexEditNotify *callback)
{
	ApexEditObject ae;
	ae.AssetProperties = object;
	if(ae.AssetProperties)
	{
		ae.AssetObject = NULL;
		ae.EditNotify = callback;
		EditorPanel->addObject("ApexAsset", *ae.AssetProperties);
		EditObjects.AddItem(ae);
	}

}

void ApexGenericEditorPanel::SetCurveEditor(ApexCurveEditorPanel *CurveEditor)
{
	EditorPanel->setCurveEditor(CurveEditor ? CurveEditor->CurvePanel : 0);
}

void ApexGenericEditorPanel::SetApexEditNotify(UApexAsset *obj,ApexEditNotify *notify)
{
	for (INT i=0; i<EditObjects.Num(); i++)
	{
		ApexEditObject &ae = EditObjects(i);
		if ( ae.AssetObject == obj )
		{
			ae.EditNotify = notify;
			break;
		}
	}
}

void ApexGenericEditorPanel::NotifyObjectDestroy(UApexAsset *obj)
{
	for (INT i=0; i<EditObjects.Num(); i++)
	{
		ApexEditObject &ae = EditObjects(i);
		if ( ae.AssetObject == obj )
		{
			if ( EditorPanel )
			{
				EditorPanel->removeObject(*ae.AssetProperties);
				ae.AssetObject = NULL;
				UBOOL kill = TRUE;
				if ( ae.EditNotify )
				{
					kill = ae.EditNotify->NotifyEditorClosed(ae.AssetProperties);
				}
				if ( kill )
				{
					ae.AssetProperties->destroy();
					ae.AssetProperties = NULL;
				}
				ae.EditNotify = NULL;
			}
		}
	}
	UBOOL alive = FALSE;
	for (INT i=0; i<EditObjects.Num(); i++)
	{
		ApexEditObject &ae = EditObjects(i);
		if ( ae.AssetObject )
		{
			alive = TRUE;
			break;
		}
	}
	if ( !alive )
	{
		// James make the panel go away here!
	}

}


void ApexGenericEditorPanel::OnSize(wxSizeEvent &In)
{
	if(EditorPanel)
	{
		EditorPanel->onResize();
	}
}

//! called just after a property has been editted by the user.
physx::PxGenericPropertiesEditorCallback::RefreshAction ApexGenericEditorPanel::onPostPropertyEdit(NxParameterized::Handle &handle,const char *tweakable,NxParameterized::Interface *parentInterface)
{
	check(parentInterface);

	const NxParameterized::Definition *d = handle.parameterDefinition();
	const char *name = d->name();
	if ( name )
	{
		if (strcmp(name,"spriteMaterialName")==0 ||	strcmp(name,"meshAssetName") == 0 )
		{
			mNeedsReset = TRUE;
		}
	}

	for (INT i=0; i<EditObjects.Num(); i++)
	{
		ApexEditObject &ae = EditObjects(i);
		if ( ae.AssetProperties == parentInterface )
		{
			if ( ae.EditNotify )
			{
				ae.EditNotify->OnPostPropertyEdit(ae.AssetProperties,handle,tweakable);
				return REFRESH_NONE;
			}
		}
	}
	check(0); // should never fail to find the corresponding object...
	return REFRESH_NONE;
}

// NVCHANGE_BEGIN: JCAO - US9197 Add functions for saving and restoring the expanded items
void ApexGenericEditorPanel::SaveExpandedItems (void)
{
	if( EditObjects.Num() > 0 )
	{
		TArray<FString> WkExpandedItems;
		const char* expandedItems = EditorPanel->SaveExpandedState();
	
		// oscar@snda
		//FANSIToTCHAR_Convert ToTchar;
		//TCHAR * TcharExpandedItems = ToTchar.Convert(expandedItems, 0, 0);
		//check(TcharExpandedItems);
		//if(TcharExpandedItems)
		if(expandedItems)
		{
			//WkExpandedItems.AddItem(TcharExpandedItems);
			WkExpandedItems.AddItem(ANSI_TO_TCHAR(expandedItems));
			FString ExpansionName = TEXT("ApexGenericEditorPanel");
			GPropertyWindowManager->SetExpandedItems (ExpansionName, WkExpandedItems);
		}
		// oscar@snda
	}
}

void ApexGenericEditorPanel::RestoreExpandedItems (void)
{
	TArray<FString> WkExpandedItems;
	FString ExpansionName = TEXT("ApexGenericEditorPanel");
	GPropertyWindowManager->GetExpandedItems (ExpansionName, WkExpandedItems);
	if(WkExpandedItems.Num() != 0) {
		FTCHARToANSI_Convert ToAnsi;
		ANSICHAR* AnsiExpandedItems = ToAnsi.Convert( *WkExpandedItems(0), 0, 0 );
		check(AnsiExpandedItems);
		if(AnsiExpandedItems)
		{
			EditorPanel->RestoreExpandedState(AnsiExpandedItems);
		}
	}
}
// NVCHANGE_END: JCAO - US9197 Add functions for saving and restoring the expanded items

// NVCHANGE_BEGIN: JCAO - Fix DE5953 APEX properties don't work with LODs in Cascade
void ApexGenericEditorPanel::SetReadOnly(BOOL bReadOnly)
{
	if(EditorPanel)
	{
		EditorPanel->setObjectReadOnly(bReadOnly == TRUE ? true : false);
	}
}
// NVCHANGE_END: JCAO - Fix DE5953 APEX properties don't work with LODs in Cascade

/***************************
** ApexGenericEditorFrame **
***************************/

BEGIN_EVENT_TABLE(ApexGenericEditorFrame, wxFrame)
END_EVENT_TABLE()

// NVCHANGE_BEGIN: JCAO - US8900 BasicIOS collision channel support
ApexGenericEditorFrame::ApexGenericEditorFrame(void) :
	wxFrame(0, wxID_ANY, wxT(""), wxDefaultPosition, wxSize(500, 600), wxDEFAULT_FRAME_STYLE | wxSTAY_ON_TOP | wxFRAME_TOOL_WINDOW | wxFRAME_NO_TASKBAR)
	,FDockingParent(this)
{
	SetLabel(wxT("APEX Properties"));
	EditorPanel = new ApexGenericEditorPanel(*this);
	EditorPanel->SetSupportReadOnly(FALSE);

	PropertyWindow = new WxPropertyWindowHost;
	PropertyWindow->Create(this, 0, -1, FALSE);

	{
		AddDockingWindow( EditorPanel, FDockingParent::DH_None, TEXT("APEX Properties") );
		AddDockingWindow( PropertyWindow, FDockingParent::DH_None, TEXT("Properties") );
	}
}
// NVCHANGE_END: JCAO - US8900 BasicIOS collision channel support

ApexGenericEditorFrame::~ApexGenericEditorFrame(void)
{
	// NVCHANGE_BEGIN: JCAO - avoid to open two same apex generic editor frame
	RemoveApexEditorWidget(this);
	// NVCHANGE_END: JCAO - avoid to open two same apex generic editor frame

	// NVCHANGE_BEGIN: JCAO - US8900 BasicIOS collision channel support
	if(PropertyWindow)
	{
		delete PropertyWindow;
	}
	// NVCHANGE_END: JCAO - US8900 BasicIOS collision channel support

	if(EditorPanel) 
	{
		delete EditorPanel;
	}
}

void ApexGenericEditorFrame::ClearProperties(void)
{
	// NVCHANGE_BEGIN: JCAO - US8900 BasicIOS collision channel support
	if(PropertyWindow)
	{
		PropertyWindow->RemoveAllObjects();
	}
	// NVCHANGE_END: JCAO - US8900 BasicIOS collision channel support

	if(EditorPanel)
	{
		EditorPanel->ClearProperties();
	}
}

void ApexGenericEditorFrame::AddObject(UApexGenericAsset &ApexAsset)
{
	UpdateFrameLabel(ApexAsset);
	// NVCHANGE_BEGIN: JCAO - US8900 BasicIOS collision channel support
	if(EditorPanel)
	{
		EditorPanel->AddObject(ApexAsset);
}
	// NVCHANGE_END: JCAO - US8900 BasicIOS collision channel support

	if(PropertyWindow)
{
		PropertyWindow->SetObject(&ApexAsset, EPropertyWindowFlags::ShouldShowCategories | EPropertyWindowFlags::Sorted);
	}
}
// NVCHANGE_BEGIN: JCAO - US8900 BasicIOS collision channel support
const TCHAR* ApexGenericEditorFrame::GetDockingParentName() const
{
	return TEXT("APEXProperties");
}

const INT ApexGenericEditorFrame::GetDockingParentVersion() const
{
	return 0;
}
// NVCHANGE_END: JCAO - US8900 BasicIOS collision channel support

void ApexGenericEditorFrame::UpdateFrameLabel(UApexGenericAsset &ApexAsset)
	{
	char labelStr[1024];
	FIApexAsset *asset = ApexAsset.GetApexGenericAsset();
	asset->GetDesc(labelStr, sizeof(labelStr));

	wxString labelWxString;
	if(labelStr[0]) // oscar@snda
	{
		labelWxString = wxString::FromAscii(labelStr);
		labelWxString.Append( wxString::FromAscii(": ") );
	}

	labelWxString.Append( wxString::FromAscii(asset->GetAssetName()) );

	// remove the file extension (.apb, .apx)
	int strIdx = labelWxString.Last( '.' );
	if( strIdx != wxNOT_FOUND )
			{
		labelWxString.Truncate(strIdx);
			}

	SetLabel(labelWxString);
		}

void ApexGenericEditorPanel::SetSupportReadOnly(UBOOL state)
			{
	physx::PxEditorWidgetManager *WidgetManager = GApexManager->GetPxEditorWidgetManager();
	if ( WidgetManager )
				{
		WidgetManager->setSupportReadOnly( state ? true : false );
	}
				}

void ApexGenericEditorPanel::AddCustomHints(void)
{
	if(EditorPanel)
	{
		EditorPanel->addCustomHint("IofxAssetParameters", "iofxType", "GUI_VARIANT_FIXED", "1");
			}
		}

const char *ApexGenericEditorPanel::onFindNamedReference(const char *&variant,physx::PxU32 numVariants,const char **variantNames)
		{
	const char *ResourceName = NULL;

	variant = NULL;
	PX_FORCE_PARAMETER_REFERENCE(variant);
	UApexGenericAsset *genericAsset = NULL;
	// NVCHANGE_BEGIN: APAN - Apex 1.2 Fix DE4948 UI button to link an IOS asset to a particle system in Cascade doesn't work anymore
	USelection *Selection = GEditor->GetSelectedObjects();
	// NVCHANGE_END: APAN - Apex 1.2 Fix DE4948 UI button to link an IOS asset to a particle system in Cascade doesn't work anymore
	if ( Selection && Selection->Num() == 1 )
			{
		UObject *found = NULL;
		UObject *obj = Selection->GetTop(UObject::StaticClass());
		if ( obj->IsA(UStaticMesh::StaticClass()) )
				{
			variant = "ApexOpaqueMesh";
					found = obj;
				}
		else if ( obj->IsA(UApexGenericAsset::StaticClass()))
		{
			genericAsset = static_cast<UApexGenericAsset *>(obj);
			FIApexAsset *asset = genericAsset->GetApexGenericAsset();
			switch ( asset->GetType() )
			{
				// NVCHANGE_BEGIN: JCAO - Use WITH_APEX_FLUID_IOS to control whether to load Fluid IOS Module and create Fluid IOS Asset
#if WITH_APEX_FLUID_IOS
				case AAT_FLUID_IOS:
					found = obj;
					variant = "NxFluidIosAsset";
					break;
#endif
				// NVCHANGE_END: JCAO - Use WITH_APEX_FLUID_IOS to control whether to load Fluid IOS Module and create Fluid IOS Asset
				case AAT_RENDER_MESH:
					found = obj;
					variant = "ApexRenderMesh";
					break;
				case AAT_BASIC_IOS:
					found = obj;
					variant = "NxBasicIosAsset";
					break;
				case AAT_IOFX_MESH:
				case AAT_IOFX_SPRITE:
					found = obj;
					variant = "IOFX";
					break;
			}
		}
		else if ( obj->IsA(UMaterial::StaticClass()) )
		{
			found = obj;
			variant = "ApexMaterials";
		}
		if ( found )
		{
			if ( genericAsset )
			{
				FIApexAsset *apexAsset = genericAsset->GetApexGenericAsset();
				if ( apexAsset )
				{
					ResourceName = apexAsset->GetAssetName();
				}
			}
			else
			{
			FTCHARToANSI_Convert StringConverter;
				char* convertedName = StringConverter.Convert( *found->GetPathName(), mConvertedName, mConvertedNameSize );
				if (convertedName != mConvertedName)
				{
					if (mConvertedName != NULL)
					{
						delete[] mConvertedName;
					}
					mConvertedNameSize = StringConverter.Length(convertedName) + 1;
					mConvertedName = convertedName;
				}
				// Using mConvertedName is SAFE only if this method is called from a single thread!
				ResourceName = mConvertedName;
			}
		}
	}
	return ResourceName;
}


const char ** ApexGenericEditorPanel::getCustomEnumeration(const char *customEnum,PxU32 &count)
{
	check(0);
	return NULL;
}

/*************************
** ApexCurveEditorPanel **
*************************/

BEGIN_EVENT_TABLE(ApexCurveEditorPanel, wxPanel)
	EVT_SIZE(ApexCurveEditorPanel::OnSize)
END_EVENT_TABLE()

ApexCurveEditorPanel::ApexCurveEditorPanel(wxWindow &parent) :
	wxPanel(&parent)
{
	CurvePanel = 0;
	
	ApexEditorIdleHandle::ConditionalInitialize(); // make sure we process idle events...
	
	physx::PxEditorWidgetManager *WidgetManager = GApexManager->GetPxEditorWidgetManager();
	check(WidgetManager);
	if(WidgetManager)
	{
		physx::PxEditorPanelDesc PanelDesc;
		PanelDesc.parentWindow = (HWND)GetHWND();
		PanelDesc.GameScale = 50;
		CurvePanel = WidgetManager->createCurveEditor(PanelDesc);
		check(CurvePanel);
		// NVCHANGE_BEGIN: JCAO - using custom parameter of APEX Curve Panel
		if( CurvePanel )
		{
			NxParameterized::Interface *customParams = CurvePanel->getCustomParameter();
			if ( customParams )
			{
				NxParameterized::Handle handle(*customParams);
				if ( NxParameterized::findParam(*customParams, "useMeanAsVectorMagnitude",handle) )
				{
					handle.setParamBool( true );
				}
			}
		}
		// NVCHANGE_END: JCAO - using custom parameter of APEX Curve Panel
	}
}

ApexCurveEditorPanel::~ApexCurveEditorPanel(void)
{
	if(CurvePanel) 
	{
		CurvePanel->release();
	}
}

void ApexCurveEditorPanel::OnSize(wxSizeEvent &In)
{
	if(CurvePanel) 
	{
		CurvePanel->onResize();
	}
}


#endif // WITH_APEX_EDITOR


/***************************
** CreateApexEditorWidget **
***************************/
// NVCHANGE_BEGIN: JCAO - avoid to open two same apex generic editor frame
#if WITH_APEX_EDITOR
struct ApexEditorWidgetObject
{
	ApexEditorWidgetObject(void)
	{
		AssetObject = NULL;
		ApexFrame = NULL;
	}

	UApexGenericAsset *	AssetObject;
	ApexGenericEditorFrame * ApexFrame;
};

static TArray<ApexEditorWidgetObject>	s_ApexEditorWidgetObjectArray;
#endif

void CreateApexEditorWidget(UApexGenericAsset *object)
{
#if WITH_APEX_EDITOR
	if(object)
	{
		for (INT i=0; i<s_ApexEditorWidgetObjectArray.Num(); i++)
		{
			ApexEditorWidgetObject &apexEWObject = s_ApexEditorWidgetObjectArray(i);
			if(apexEWObject.AssetObject == object)
			{
				apexEWObject.ApexFrame->Show(true);
				return;
			}
		}

		ApexGenericEditorFrame *Editor = new ApexGenericEditorFrame();
		Editor->AddObject(*object);
		Editor->Show(true);
		ApexEditorWidgetObject apexEWObject;
		apexEWObject.AssetObject = object;
		apexEWObject.ApexFrame = Editor;
		s_ApexEditorWidgetObjectArray.AddItem(apexEWObject);
	}
#endif
}

#if WITH_APEX_EDITOR
void RemoveApexEditorWidget(ApexGenericEditorFrame * frame)
{
	for (INT i=0; i<s_ApexEditorWidgetObjectArray.Num(); i++)
	{
		ApexEditorWidgetObject &apexEWObject = s_ApexEditorWidgetObjectArray(i);
		if(apexEWObject.ApexFrame == frame)
		{
			s_ApexEditorWidgetObjectArray.Remove(i);
			break;
		}
	}
}
#endif
// NVCHANGE_END: JCAO - avoid to open two same apex generic editor frame
