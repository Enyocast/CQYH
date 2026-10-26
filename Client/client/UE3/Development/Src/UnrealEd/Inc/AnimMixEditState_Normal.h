/*=============================================================================
	hemu@snda 120416
	动画混合参数表，用于播放连击动作等情况下动作的平滑返回播放
=============================================================================*/
#ifndef __AnimMixEditState_Normal_H__
#define __AnimMixEditState_Normal_H__

#include "AnimMixEditState.h"

//混合动画参数表节点控件
class AnimMixEditState_Normal : public AnimMixEditState
{
public:

	AnimMixEditState_Normal(AnimMixMatrix* ed);
	virtual ~AnimMixEditState_Normal();

	virtual void ClickedAnyObject(struct HAnyObjectProxy* proxy);	
	virtual void HighlightAnyObject(struct HAnyObjectProxy* proxy);

	virtual void DrawObjects(FViewport* Viewport, FCanvas* Canvas);

	virtual void OnEnter();
	virtual void OnExit();

	void _DestroyEditProxyObject();

	virtual void EmptySelection();
	//从ArchiType中读取
	FAnimMixNode* FindAnimNodeObject(BYTE ST, BYTE TT);
	class UMMOAnimMixEditObject* FindEditProxyObject(BYTE SrcType, BYTE TargetType);
	//class UMMOAnimMixEditObject* FindEditProxyObject(FString SourceAnim, FString TargetAnim);
	virtual void SaveData();
protected:

	class UMMOAnimMixEditObject* SelectedObject;
	class UMMOAnimMixEditObject* HighlightObject;
	TArray<class UMMOAnimMixEditObject*> EditProxyObjectArray;
};

#endif