#ifndef APEX_EDITOR_WIDGETS_H
#define APEX_EDITOR_WIDGETS_H

#include "UnrealEd.h"

#if WITH_APEX_EDITOR

//#include "stdwx.h" // oscar@snda

// NVCHANGE_BEGIN: LRR - use and include file that doesn't require FaceFX
#include <wx/wx.h>
// NVCHANGE_END: LRR - use and include file that doesn't require FaceFX
#pragma pack( push, 8 )
#include "PxGenericPropertiesEditorCallback.h"
#pragma pack(pop )
class UApexGenericAsset;
class ApexCurveEditorPanel;

namespace physx
{
	class PxGenericPropertiesEditorPanel;
	class PxCurveEditorPanel;
}

namespace NxParameterized
{
	class Interface;
}

struct ApexEditObject
{
	ApexEditObject(void)
	{
		AssetObject = NULL;
		AssetProperties = NULL;
		EditNotify = NULL;
	}
	NxParameterized::Interface            *AssetProperties;
	UApexGenericAsset					  *AssetObject;
	ApexEditNotify						  *EditNotify;
};

// generic apex asset editor that can be embedded in other windows.
class ApexGenericEditorPanel : public wxPanel, public physx::PxGenericPropertiesEditorCallback, public ApexEditInterface
{
	public:
		ApexGenericEditorPanel(wxWindow &parent);
		virtual ~ApexGenericEditorPanel(void);
		
		void ClearProperties(void);
		void AddObject(UApexGenericAsset &ApexAsset);
		void AddObject(NxParameterized::Interface *object,ApexEditNotify *callback);
		void SetCurveEditor(ApexCurveEditorPanel *CurveEditor);

		virtual void SetApexEditNotify(UApexAsset *obj,ApexEditNotify *notify);
		virtual void NotifyObjectDestroy(UApexAsset *obj);

		virtual const char *onFindNamedReference(const char *&variant,physx::PxU32 numVariants,const char **variantNames);

		virtual const char ** getCustomEnumeration(const char *customEnum, physx::PxU32 &count);
	
		virtual bool getCustomColor(const NxParameterized::Handle &handle,PxU32 &customColor)
		{
			return false;
		}

		virtual UBOOL NeedsReset(void)
		{
			UBOOL ret = mNeedsReset;
			mNeedsReset = FALSE;
			return ret;
		}

		void SetSupportReadOnly(UBOOL state);
		void AddCustomHints(void);

		// NVCHANGE_BEGIN: JCAO - US9197 Add functions for saving and restoring the expanded items
		/**
		 * Save off what nodes in the tree are expanded
		 */
		void SaveExpandedItems (void);
		/**
		 * Restore what nodes in the tree are expanded
		 */
		void RestoreExpandedItems (void);
		// NVCHANGE_END: JCAO - US9197 Add functions for saving and restoring the expanded items
		// NVCHANGE_BEGIN: JCAO - Fix DE5953 APEX properties don't work with LODs in Cascade
		void SetReadOnly(BOOL bReadOnly);
		// NVCHANGE_END: JCAO - Fix DE5953 APEX properties don't work with LODs in Cascade
	private:
		void OnSize(wxSizeEvent &In);
	
	private:
		//! called just after a property has been editted by the user.
		virtual physx::PxGenericPropertiesEditorCallback::RefreshAction onPostPropertyEdit(NxParameterized::Handle &handle,const char *tweakable,NxParameterized::Interface *parentInterface);
	
	private:
		physx::PxGenericPropertiesEditorPanel *EditorPanel;
		TArray< ApexEditObject >               EditObjects;
		UBOOL                                  mNeedsReset;
	
		int                                    mConvertedNameSize;
		char                                   *mConvertedName;	
	private:
		DECLARE_EVENT_TABLE()
};

// self contained window that includes a  ApexGenericEditorPanel.
// NVCHANGE_BEGIN: JCAO - US8900 BasicIOS collision channel support
class ApexGenericEditorFrame : public wxFrame, public FDockingParent
{
	public:
		ApexGenericEditorFrame(void);
		virtual ~ApexGenericEditorFrame(void);
		
		void ClearProperties(void);
		void AddObject(UApexGenericAsset &ApexAsset);
	protected:

		virtual const TCHAR* GetDockingParentName() const;
		virtual const INT GetDockingParentVersion() const;
		
	private:
		ApexGenericEditorPanel *EditorPanel;
		WxPropertyWindowHost				*PropertyWindow;

		void UpdateFrameLabel(UApexGenericAsset &ApexAsset);
	
	private:
		DECLARE_EVENT_TABLE()
};
// NVCHANGE_END: JCAO - US8900 BasicIOS collision channel support

// curve editor that can be embedded in other windows.
class ApexCurveEditorPanel : public wxPanel
{
	friend class ApexGenericEditorPanel;
	public:
		ApexCurveEditorPanel(wxWindow &parent);
		virtual ~ApexCurveEditorPanel(void);
	
	private:
		void OnSize(wxSizeEvent &In);
	
	private:
		physx::PxCurveEditorPanel   *CurvePanel;
	
	private:
		DECLARE_EVENT_TABLE()
};

#endif // #if WITH_APEX_EDITOR

class UApexGenericAsset;

void CreateApexEditorWidget(UApexGenericAsset *object);
// NVCHANGE_BEGIN: JCAO - avoid to open two same apex generic editor frame
#if WITH_APEX_EDITOR
void RemoveApexEditorWidget(ApexGenericEditorFrame * frame);
#endif
// NVCHANGE_END: JCAO - avoid to open two same apex generic editor frame
#endif
