
#include "stdafx.h"
#include "MMOGameUIClasses.h"
#include "MMOFacade.h"
#include "attribute_def.h"
#include "MasterStudentManager.h"
#include "MMOMsgButtonManager.h"
#include "MMOChatManager.h"
#include "../net/message_handler_Quest.h"
#include "MMOGuideManager.h"
#include "MMOMsgBoxManager.h"

IMPLEMENT_CLASS(UMMOUIMasterCongratulationSub)


//==================================================Total()====================================================== 
void UMMOUIMasterCongratulationSub::NativeInitOnce()
{
	UMMOUIBase::NativeInitOnce();


}

void UMMOUIMasterCongratulationSub::OnNativeGameEvent(struct MMOGameEvent* evt)
{

}

void UMMOUIMasterCongratulationSub::UnInit()
{
	UMMOUIBase::UnInit();

}

void UMMOUIMasterCongratulationSub::PostOnShow(UBOOL v)
{
	UMMOUIBase::PostOnShow(v);
	if (v)
	{
	}
}
void UMMOUIMasterCongratulationSub::PostAdvance(float DeltaTime)
{
}