/*=============================================================================
	hemu@snda 120416
	动画混合参数表，用于播放连击动作等情况下动作的平滑返回播放
=============================================================================*/

#ifndef __AnimMixEDITSTATE_H__
#define __AnimMixEDITSTATE_H__

#include "UnrealEd.h"
#include "UnLinkedObjEditor.h"

enum EAnimMixObject
{
	EAO_Normal = 0,
};

#define DRAW_BLOCK_SIZE 64
#define DRAW_BLOCK_SPACE 10
#define DRAW_X_OFFSET 200
#define DRAW_Y_OFFSET 100

class AnimMixEditState
{
public:

	AnimMixEditState(AnimMixMatrix* ed);
	virtual ~AnimMixEditState();

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

	FString GetEnumDisplayName(BYTE enumID,UBOOL bSource=true);

protected:

	AnimMixMatrix* AnimMixEditor;

	FColor BorderColor;
	FColor BkgColor;
	FColor BorderColorHighlight;
	FColor BkgColorHighlight;

	FColor YellowColor;
	FColor GreenColor;
	FColor WhiteColor;
	FColor RedColor;
	FColor CyanColor;

	UEnum* EnumObjSource;
	UEnum* EnumObjTarget;
};

#endif