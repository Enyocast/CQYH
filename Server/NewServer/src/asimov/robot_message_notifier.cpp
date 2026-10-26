#include "stdafx.h"
#include "robot_message_notifier.h"

#include "user_mgr.h"

BOOL CRobotMessageNotifier::SendToServer(UINT32 dwClientSessionID, PACKET_BUFFER* pData, UINT32 dwSize)
{
    INT32 nRetCode = 0;
    CUser* poUser = CUserMgr::GetInstance().FindUser(dwClientSessionID);
    LOG_PROCESS_ERROR(poUser);
    LOG_PROCESS_ERROR(pData);

    nRetCode = poUser->SendMsg(pData, (UINT16)dwSize);
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:

    return FALSE;
}
