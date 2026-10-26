#include "..\stdafx.h"
#include "MMOFacade.h"

IMPLEMENT_CLASS(USeqAct_NotifyServerToStopMatinee)


void USeqAct_NotifyServerToStopMatinee::Activated()
{
	CMessageHandler::GetInstance().Send_CancelMatinee();
	ActivateOutputLink(0);

	// 过场结束时把镜头更新回去
	AMMOPlayerCamera* cam = Cast<AMMOPlayerCamera>(MMOFacade::getSingleton().GetMainController()->PlayerCamera);
	if(cam)
	{
		cam->EnableSmoothCameraPos = FALSE;
		cam->EnableSmoothCameraRot = FALSE;
		cam->eventUpdateCamera(0.0f);
	}
}
