#ifndef __SOUNDMATEDITSTATE_H__
#define __SOUNDMATEDITSTATE_H__

#include "UnrealEd.h"
#include "UnLinkedObjEditor.h"

enum ESoundMaterialObject
{
	ETO_HitSounds = 0,
	ETO_FootstepSounds
};

#define DRAW_BLOCK_SIZE 64
#define DRAW_BLOCK_SPACE 10
#define DRAW_X_OFFSET 200
#define DRAW_Y_OFFSET 100

class SoundMaterialEditState
{
public:

	SoundMaterialEditState(SoundMaterialMatrix* ed);
	virtual ~SoundMaterialEditState();

	virtual void EmptySelection() {}
	virtual INT GetNumSelected() const { return 0; }

	virtual void ClickedAnyObject(struct HAnyObjectProxy* proxy){}
	virtual void CtrlClickedAnyObject(struct HAnyObjectProxy* proxy){}
	virtual void HighlightAnyObject(struct HAnyObjectProxy* proxy){}
	virtual void DoubleClickedAnyObject(struct HAnyObjectProxy* proxy){}

	virtual void DrawObjects(FViewport* Viewport, FCanvas* Canvas){}

	virtual void OnEnter() = 0;
	virtual void OnExit() = 0;
	virtual void SaveData() = 0;

	FString GetEnumDisplayName(BYTE enumID);
	FString GetEnumDisplayName(UEnum* InObject, INT InIdx);

protected:

	SoundMaterialMatrix* SoundMaterialEditor;

	FColor BorderColor;
	FColor BkgColor;
	FColor BorderColorHighlight;
	FColor BkgColorHighlight;

	FColor YellowColor;
	FColor GreenColor;
	FColor WhiteColor;
	FColor RedColor;

	UEnum* EnumObj;
};

#endif