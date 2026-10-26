#include "stdafx.h"
#include "MMOGameUIClasses.h"
#include "MMOFacade.h"

IMPLEMENT_CLASS(UMMOUILoadingBar)

void UMMOUILoadingBar::PreEnterCompleted()
{
	MMOUI::GetUIManager()->delegateCallBack_PreLoad();
}
void UMMOUILoadingBar::PreLeaveCompleted()
{

}
void UMMOUILoadingBar::NativeCallSet_Back(class UGFxObject* back)
{
	eventCallSet_Back(back);
}
