#ifndef __SOUNDMATEDITSTATE_HITSOUNDS_H__
#define __SOUNDMATEDITSTATE_HITSOUNDS_H__

#include "SoundMatEditState.h"

class SoundMatEditState_HitSounds : public SoundMaterialEditState
{
public:

	SoundMatEditState_HitSounds(SoundMaterialMatrix* ed);
	virtual ~SoundMatEditState_HitSounds();

	virtual void ClickedAnyObject(struct HAnyObjectProxy* proxy);	
	virtual void HighlightAnyObject(struct HAnyObjectProxy* proxy);

	virtual void DrawObjects(FViewport* Viewport, FCanvas* Canvas);

	virtual void OnEnter();
	virtual void OnExit();

	void _DestroyEditProxyObject();

	virtual void EmptySelection();

	class UMMOSoundMaterialEditObject* FindEditProxyObject(BYTE SrcType, BYTE TargetType);
	FHitSoundNode* FindSoundMaterialGroupObject(BYTE SrcType, BYTE TargetType);

	virtual void SaveData();

	FString GetEnumEnglishName(UEnum* InObject, INT Idx);

protected:

	UEnum* WeaponHitEnumObj;
	UEnum* MaterialTypeEnumObj;

	class UMMOSoundMaterialEditObject* SelectedObject;
	class UMMOSoundMaterialEditObject* HighlightObject;
	TArray<class UMMOSoundMaterialEditObject*> EditProxyObjectArray;
};

#endif