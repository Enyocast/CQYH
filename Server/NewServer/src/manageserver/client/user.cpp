#include "stdafx.h"
#include "user.h"
#include "message_handler.h"
#include "onlinerole/online_role_data.h"
#include "onlinerole/online_role_data_mgr.h"
#include "role_data.h"
#include "team/team.h"
#include "manageserver.h"

void MS_USER::SetFreeMode(BOOL fm)
{
    INT32 nRetCode = FALSE;

    bFreeMode = fm;

    if (fm)
    {
        dwBeginTime = 0;
        dwFreeModeLastCheckTime = CManageServer::GetInstance().GetGameTime();
    }
    else
    {
        dwBeginTime = CManageServer::GetInstance().GetGameTime();
        dwFreeModeLastCheckTime = 0;
    }

    MS_ONLINE_ROLE_DATA* role = COnlineRoleDataMgr::GetInstance().FindOnlineRoleByRoleID(dwCurRoleID);
    if (role)
    {
        if (fm)
        {
            // 离开队伍，代码复制于：CMessageHandler::OnClientTeamLeave
            CTeam* poTeam = CTeamMgr::GetInstance().Find(role->pRoleData->dwTeamID);
            if (poTeam)
            {
                UINT32 dwOldLeader = poTeam->GetLeader();
                if (dwOldLeader == role->pRoleData->dwRoleID)
                {
                    nRetCode = poTeam->SelectLeader(TRUE);
                    LOG_CHECK_ERROR(nRetCode);
                }

                nRetCode = poTeam->DelMember(role->pRoleData->dwRoleID);
                LOG_CHECK_ERROR(nRetCode);

                nRetCode = CMessageHandler::GetInstance().DoClientTeamLeave(role->dwCliSessionID, poTeam->GetTeamID());
                LOG_CHECK_ERROR(nRetCode);

                nRetCode = CMessageHandler::GetInstance().DoDLLeaveTeam(CManageServer::GetInstance().GetGameTime(), role->pRoleData->byGroup,
                    role->pRoleData->dwRoleID, poTeam->GetTeamID(), poTeam->GetLeader(), poTeam->GetMemberCount());
                LOG_CHECK_ERROR(nRetCode);

                if (poTeam->GetMemberCount() == 0)
                {
                    nRetCode = CMessageHandler::GetInstance().DoDLBreakDwonTeam(CManageServer::GetInstance().GetGameTime(),
                        role->pRoleData->byGroup, poTeam->GetTeamID());
                    LOG_CHECK_ERROR(nRetCode);

                    if (poTeam->GetActivityType() != etaatInvalid)
                    {
                        nRetCode = CTeamMgr::GetInstance().DeleteActivityTeam(poTeam->GetActivityType(), poTeam->GetActivityID(), poTeam->GetTeamID());
                        LOG_CHECK_ERROR(nRetCode);
                    }

                    nRetCode = poTeam->UnInit();
                    LOG_CHECK_ERROR(nRetCode);

                    nRetCode = CTeamMgr::GetInstance().Delete(poTeam);
                    LOG_CHECK_ERROR(nRetCode);
                }
                else
                {
                    nRetCode = CMessageHandler::GetInstance().DoClientRemoveMember(role->pRoleData->dwRoleID, poTeam);
                    LOG_CHECK_ERROR(nRetCode);

                    if (dwOldLeader != poTeam->GetLeader())
                    {
                        nRetCode = CMessageHandler::GetInstance().DoClientTeamChangeInfo(poTeam);
                        LOG_CHECK_ERROR(nRetCode);

                        nRetCode = CMessageHandler::GetInstance().DoGSTeamChangeInfo(poTeam);
                        LOG_CHECK_ERROR(nRetCode);
                    }
                }

                nRetCode = CMessageHandler::GetInstance().DoGSTeamRemoveMember(role->pRoleData->dwRoleID, poTeam);
                LOG_CHECK_ERROR(nRetCode);
            }
            // 离开队伍结束
        }

        CMessageHandler::GetInstance().DoGSFreeMode(role->dwGSSessionID, dwCurRoleID, fm);
    }

    CMessageHandler::GetInstance().DoClientFreeMode(dwCliSessionID, fm);
}
