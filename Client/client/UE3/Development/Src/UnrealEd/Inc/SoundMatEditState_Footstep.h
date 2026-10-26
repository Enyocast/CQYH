#ifndef _SOUNDMATEDITSTATE_FOOTSTEP_H_
#define  _SOUNDMATEDITSTATE_FOOTSTEP_H_

#include "UnrealEd.h"
#include "SoundMatEditState.h"

//#include "UnLinkedObjEditor.h"

struct FFootstepEffectNode;
class UMMOFootstepMaterialEditObject;
class UEnum;

class SoundMatEditState_Footstep : public SoundMaterialEditState
{
public:

	SoundMatEditState_Footstep(SoundMaterialMatrix* ed);
	virtual ~SoundMatEditState_Footstep();

	virtual void ClickedAnyObject(struct HAnyObjectProxy* proxy);	
	virtual void HighlightAnyObject(struct HAnyObjectProxy* proxy);

	virtual void DrawObjects(FViewport* Viewport, FCanvas* Canvas);

	virtual void OnEnter();
	virtual void OnExit();


	FString GetEnumDisplayName(UEnum* Obj, BYTE enumID);
	FFootstepEffectNode* FindEffectNodeObject(BYTE LT, BYTE BT);
	void DestroyEditProxyObject();

	/*
	class UMMOSoundMaterialEditObject* FindEditProxyObject(BYTE SrcType, BYTE TargetType);
	struct FHitSoundEffectGroup* FindSoundMaterialGroupObject(BYTE SrcType, BYTE TargetType);
	  */
	virtual void SaveData();

protected:
	TArray<UMMOFootstepMaterialEditObject*> FootstepObjectList;

	UEnum* BodyEnumObj;
	UEnum* LandEnumObj;



	UMMOFootstepMaterialEditObject* SelectedObject;
	UMMOFootstepMaterialEditObject* HighlightObject;
	//TArray<class UMMOSoundMaterialEditObject*> EditProxyObjectArray;
};



#endif