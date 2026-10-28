/********************************************************************
	created:	4:12:2013   15:32
	file:		cmd_manager.cpp
	author:		Allan Tao
	
	purpose:	命令管理器 UI层和逻辑层交互
*********************************************************************/


#include "stdafx.h"
#include "cmd_manager.h"
#include "string_ex.h"
#include <QtWidgets/QMessageBox>
#include "tl_config.h"
#include "executing.h"
#include "message_handler.h"
#include "gm_manager.h"
#include "data_mgr.h"
#include "role_info.h"
#include "gm_log.h"
#include "session_mgr.h"
#include <time.h>
#include "gmtool.h"

CCmdManager CCmdManager::m_Instance;

CCmdManager &CCmdManager::GetInstance()
{
    return m_Instance;
}

CCmdManager::CCmdManager()
{
    
}

CCmdManager::~CCmdManager()
{
    
}


BOOL CCmdManager::Init()
{
    INT32       nRetCode = 0;

    ////m_eCmdType = GM_CMD_NONE;
    //m_PreExecuteSvrList.clear();
    //m_Cursor = m_PreExecuteSvrList.end();

    ////nRetCode = m_CmdPool.Init(g_TLConfig.TLConfig.nCmdDataPoolCount);
    ////LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    return FALSE;
}

BOOL CCmdManager::UnInit()
{
    INT32       nRetCode = 0;

    //m_eCmdType = GM_CMD_NONE;
    m_PreExecuteSvrList.clear();
    m_Cursor = m_PreExecuteSvrList.end();

    //nRetCode = m_CmdPool.UnInit();
    //LOG_CHECK_ERROR(nRetCode);

    return TRUE;
}

BOOL CCmdManager::MainLoop()
{
    INT32       nRetCode = 0;

    if (m_pCmd)
    {
        if (time(NULL) > m_pCmd->nWashout || 0 == m_pCmd->nSvrNum)
        {
            if (time(NULL) > m_pCmd->nWashout)
            {
                //nRetCode = CCmdManager::GetInstance().Washout(m_pCmd);
                //LOG_CHECK_ERROR(nRetCode);

                nRetCode = CCmdManager::GetInstance().DelCmd(m_pCmd);
                LOG_CHECK_ERROR(nRetCode);
                CGMLog::GetInstance().Log("指令超时!");

                m_pCmd = NULL;
            }
            else if (0 == m_pCmd->nSvrNum)
            {
                nRetCode = CCmdManager::GetInstance().DelCmd(m_pCmd);
                LOG_CHECK_ERROR(nRetCode);
                //CGMLog::GetInstance().Log("指令成功!");
                //nRetCode = CCmdManager::GetInstance().Success(m_pCmd);
                //LOG_CHECK_ERROR(nRetCode);
                m_pCmd = NULL;
            }
        }
    }

    return TRUE;
}

BOOL CCmdManager::PreQuery(INT32 nCmdType, const char *pcszRoleName, CMD_BASE *pCmd)
{
    INT32       nRetCode = 0;
    PRE_QUERY   *pQueryCmd = NULL;

    LOG_PROCESS_ERROR(pCmd);

    m_pCmd = CCmdManager::GetInstance().NewCmd(CMD_QUERY_ROLE_ID);
    LOG_PROCESS_ERROR(m_pCmd);

    pQueryCmd = (PRE_QUERY *)m_pCmd;
    m_pCmd->nType = CMD_PRE_QUERY;
    m_pCmd->nSvrNum = 0;
    m_pCmd->nWashout = time(NULL) + GM_SVR_TIMEOUT;
    pQueryCmd->nCmdType = nCmdType;
    strxcpy(pQueryCmd->szRoleName, pcszRoleName, sizeof(pQueryCmd->szRoleName));
    pQueryCmd->pCmd = pCmd;

    nRetCode = CMessageHandler::GetInstance().DoPreQuery(pcszRoleName);
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (m_pCmd)
        CCmdManager::GetInstance().DelCmd(m_pCmd);
    return FALSE;
}

BOOL CCmdManager::QueryRoleID(INT32 nType, const char *pcszName)
{
    INT32       nRetCode = 0;
    QUERY_ROLE_ID   *pQueryCmd = NULL;

    LOG_PROCESS_ERROR(pcszName);

    m_pCmd = CCmdManager::GetInstance().NewCmd(CMD_QUERY_ROLE_ID);
    LOG_PROCESS_ERROR(m_pCmd);

    pQueryCmd = (QUERY_ROLE_ID *)m_pCmd;
    m_pCmd->nType = CMD_QUERY_ROLE_ID;
    m_pCmd->nSvrNum = 0;
    m_pCmd->nWashout = time(NULL) + TL_CMD_TIMEOUT_TIME;
    pQueryCmd->nQueryType = nType;
    strxcpy(pQueryCmd->szName, pcszName, sizeof(pQueryCmd->szName));

    nRetCode = CMessageHandler::GetInstance().DoQueryRoleID(nType, pQueryCmd->szName);
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (m_pCmd)
        CCmdManager::GetInstance().DelCmd(m_pCmd);
    return FALSE;
}

BOOL CCmdManager::QueryRoleData(CMD_BASE *pCmd)
{
    INT32       nRetCode = 0;

    LOG_PROCESS_ERROR(pCmd);
    m_pCmd = pCmd;
    pCmd->nWashout = time(NULL) + TL_CMD_LONG_TIMEOUT;

    nRetCode = CMessageHandler::GetInstance().DoQueryRoleData(((QUERY_ROLE_DATA*)m_pCmd)->dwRoleID);
    LOG_CHECK_ERROR(nRetCode);
    if (nRetCode == FALSE)
    {
        CGMLog::GetInstance().Log("查询角色[%s]失败", ((QUERY_ROLE_DATA*)m_pCmd)->szRoleName);
    }

    return TRUE;
Exit0:
    if (m_pCmd)
        CCmdManager::GetInstance().DelCmd(m_pCmd);
    return FALSE;
}

BOOL CCmdManager::ForbidChat(CMD_BASE *pCmd)
{
    INT32       nRetCode = 0;

    LOG_PROCESS_ERROR(pCmd);

    m_pCmd = pCmd;
    m_pCmd->nWashout = time(NULL) + TL_CMD_TIMEOUT_TIME;

    nRetCode = CMessageHandler::GetInstance().DoForbidChat(((FORBIDDEN_CHAT*)pCmd)->llTime, ((FORBIDDEN_CHAT*)pCmd)->roleList.begin()->dwRoleID);
    if (nRetCode == FALSE)
    {
        CGMLog::GetInstance().Log("发送角色[%d]禁言消息失败", ((FORBIDDEN_CHAT*)pCmd)->roleList.begin()->dwRoleID);
        LOG_PROCESS_ERROR(FALSE);
    }

    return TRUE;
Exit0:
    if (m_pCmd)
        CCmdManager::GetInstance().DelCmd(m_pCmd);
    return FALSE;
}

BOOL CCmdManager::FreezeRole(CMD_BASE *pCmd)
{
    INT32       nRetCode = 0;

    LOG_PROCESS_ERROR(pCmd);

    m_pCmd = pCmd;
    pCmd->nWashout = time(NULL) + TL_CMD_TIMEOUT_TIME;

    nRetCode = CMessageHandler::GetInstance().DoFreezeRole(((FREEZE_ROLE*)pCmd)->llTime, ((FREEZE_ROLE*)pCmd)->roleList.begin()->dwRoleID);
    if (nRetCode == FALSE)
    {
        CGMLog::GetInstance().Log("发送角色[%d]冻结消息失败", ((FREEZE_ROLE*)pCmd)->roleList.begin()->dwRoleID);
        LOG_PROCESS_ERROR(FALSE);
    }


    return TRUE;
Exit0:
    if (m_pCmd)
        CCmdManager::GetInstance().DelCmd(m_pCmd);
    return FALSE;
}

BOOL CCmdManager::KickRole(CMD_BASE *pCmd)
{
    INT32       nRetCode = 0;

    LOG_PROCESS_ERROR(pCmd);

    m_pCmd = pCmd;
    m_pCmd->nWashout = time(NULL) + TL_CMD_TIMEOUT_TIME;

    nRetCode = CMessageHandler::GetInstance().DoKickRole(((KICK_ROLE*)pCmd)->roleList.begin()->dwRoleID);
    if (nRetCode == FALSE)
    {
        CGMLog::GetInstance().Log("发送角色[%d]强制下线消息失败", ((KICK_ROLE*)pCmd)->roleList.begin()->dwRoleID);
        LOG_PROCESS_ERROR(FALSE);
    }

    return TRUE;
Exit0:
    if (m_pCmd)
        CCmdManager::GetInstance().DelCmd(m_pCmd);
    return FALSE;
}

BOOL CCmdManager::SendMail(CMD_BASE *pCmd)
{
    INT32       nRetCode = 0;
    SEND_MAIL   *pSendMail = (SEND_MAIL *)pCmd;

    LOG_PROCESS_ERROR(pCmd);

    m_pCmd = pCmd;
    pCmd->nWashout = time(NULL) + TL_CMD_TIMEOUT_TIME;
    
    nRetCode = CMessageHandler::GetInstance().DoSendMail(pSendMail->roleList.begin()->dwRoleID, pSendMail->szTitle,
        pSendMail->szContent, pSendMail->szReason, pSendMail->dwItemID, pSendMail->nItemNum);
    if (nRetCode == FALSE)
    {
        CGMLog::GetInstance().Log("发送角色[%d]禁言消息失败", pSendMail->roleList.begin()->dwRoleID);
        LOG_PROCESS_ERROR(nRetCode);
    }

    return TRUE;
Exit0:
    if (m_pCmd)
        CCmdManager::GetInstance().DelCmd(m_pCmd);
    return FALSE;
}

BOOL CCmdManager::SendAnnounce(INT32 nGroupID, UINT32 dwBeginTime, INT32 nIntervalTime, INT32 nRepeatNum, const char *pcszAnnounce)
{
    INT32       nRetCode = 0;
    ANNOUNCE    *pAnnounceCmd = NULL;

    LOG_PROCESS_ERROR(pcszAnnounce);

    m_pCmd = CCmdManager::GetInstance().NewCmd(CMD_ANNOUNCE);
    LOG_PROCESS_ERROR(m_pCmd);

    m_pCmd->nType = CMD_ANNOUNCE;
    m_pCmd->nSvrNum = 0;
    m_pCmd->nWashout = time(NULL) + TL_CMD_TIMEOUT_TIME;

    pAnnounceCmd = (ANNOUNCE *)m_pCmd;
    pAnnounceCmd->nGroupID = nGroupID;
    pAnnounceCmd->dwBeginTime = dwBeginTime;
    pAnnounceCmd->nIntervalTime = nIntervalTime;
    pAnnounceCmd->nRepeatNum = nRepeatNum;
    strxcpy(pAnnounceCmd->szAnnounce, pcszAnnounce, sizeof(pAnnounceCmd->szAnnounce));

    nRetCode = CMessageHandler::GetInstance().DoAnnounce(nGroupID, dwBeginTime, nRepeatNum, nIntervalTime, pcszAnnounce);
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (m_pCmd)
        CCmdManager::GetInstance().DelCmd(m_pCmd);
    return FALSE;
}

BOOL CCmdManager::QueryAnnounceList(INT32 nGroupID)
{
    INT32       nRetCode = 0;

    m_pCmd = CCmdManager::GetInstance().NewCmd(CMD_GET_ANNOUNCE_LIST);
    LOG_PROCESS_ERROR(m_pCmd);

    m_pCmd->nType = CMD_GET_ANNOUNCE_LIST;
    m_pCmd->nSvrNum = 0;
    m_pCmd->nWashout = time(NULL) + TL_CMD_TIMEOUT_TIME;
    ((GET_ANNOUNCE_LIST*)m_pCmd)->nGroupID = nGroupID;

    nRetCode = CMessageHandler::GetInstance().DoGetAnnounceList(nGroupID);
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (m_pCmd)
        CCmdManager::GetInstance().DelCmd(m_pCmd);
    return FALSE;
}

BOOL CCmdManager::DelAnnounce(INT32 nGroupID, INT32 nAnnounceSerial)
{
    INT32       nRetCode = 0;

    m_pCmd = CCmdManager::GetInstance().NewCmd(CMD_DEL_ANNOUNCE);
    LOG_PROCESS_ERROR(m_pCmd);

    m_pCmd->nType = CMD_DEL_ANNOUNCE;
    m_pCmd->nSvrNum = 0;
    m_pCmd->nWashout = time(NULL) + TL_CMD_TIMEOUT_TIME;
    ((DEL_ANNOUNCE*)m_pCmd)->nGroupID = nGroupID;

    nRetCode = CMessageHandler::GetInstance().DoDelAnnounce(nGroupID, nAnnounceSerial);
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (m_pCmd)
        CCmdManager::GetInstance().DelCmd(m_pCmd);
    return FALSE;
}

BOOL CCmdManager::QueryNameToID(std::map<INT32, ROLE_NAME_DATA> &map)
{
    INT32               nRetCode = 0;
    QUERY_NAME_TO_ID    *pNTICmd = NULL;
    std::map<INT32, ROLE_NAME_DATA>::iterator   temp_iter;
    //std::map<INT32, ROLE_NAME_DATA>::iterator   old_iter = map.end();

    m_pCmd = CCmdManager::GetInstance().NewCmd(CMD_QUERY_NAME_TO_ID);
    LOG_PROCESS_ERROR(m_pCmd);

    m_pCmd->nType = CMD_QUERY_NAME_TO_ID;
    m_pCmd->nSvrNum = 1;
    m_pCmd->nWashout = time(NULL) + TL_CMD_TIMEOUT_TIME;
    pNTICmd = (QUERY_NAME_TO_ID *)m_pCmd;

    //copy(map.begin(), map.end(), pNTICmd->RoleNameMap);

    //for (std::map<INT32, ROLE_NAME_DATA>::iterator iter = map.begin(); iter != map.end(); )
    //{
    //    old_iter = iter;
    //    ++iter;
    //    map.erase(old_iter);
        pNTICmd->RoleNameMap.insert(map.begin(), map.end());
    //}


    pNTICmd->nMaxCount = pNTICmd->RoleNameMap.size();

    temp_iter = pNTICmd->RoleNameMap.find(1);
    LOG_PROCESS_ERROR(temp_iter != pNTICmd->RoleNameMap.end());

    nRetCode = CMessageHandler::GetInstance().DoQueryNameToID(temp_iter->first, temp_iter->second.szRoleName);
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (m_pCmd)
        CCmdManager::GetInstance().DelCmd(m_pCmd);
    return FALSE;
}

BOOL CCmdManager::SendGMStrCmd(const char *pcszCmdStr)
{
    INT32       nRetCode = 0;
    EXECUTE_GM_STR    *pGMStrCmd = NULL;

    LOG_PROCESS_ERROR(pcszCmdStr);

    m_pCmd = CCmdManager::GetInstance().NewCmd(CMD_EXECUTE_GM_STR);
    LOG_PROCESS_ERROR(m_pCmd);

    m_pCmd->nType = CMD_EXECUTE_GM_STR;
    m_pCmd->nSvrNum = 0;
    m_pCmd->nWashout = time(NULL) + TL_CMD_TIMEOUT_TIME;

    pGMStrCmd = (EXECUTE_GM_STR *)m_pCmd;
    strxcpy(pGMStrCmd->szStr, pcszCmdStr, sizeof(pGMStrCmd->szStr));

    nRetCode = CMessageHandler::GetInstance().DoExecuteGMStrCmd(pGMStrCmd->szStr);
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (m_pCmd)
        CCmdManager::GetInstance().DelCmd(m_pCmd);
    return FALSE;
}

BOOL CCmdManager::LoadRoleData(CMD_BASE *pCmd)
{
    INT32       nRetCode = 0;

    LOG_PROCESS_ERROR(pCmd);

    m_pCmd = pCmd;
    m_pCmd->nWashout = time(NULL) + TL_CMD_LONG_TIMEOUT;

    nRetCode = CMessageHandler::GetInstance().DoLoadRoleData(((LOAD_ROLE_DATA*)m_pCmd)->dwRoleID);
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (m_pCmd)
        CCmdManager::GetInstance().DelCmd(m_pCmd);
    return FALSE;
}

BOOL CCmdManager::ModifyRole(UINT32 dwRoleID, UINT32 dwTargetRoleID, INT32 nLength, const char *pcszData, const char *pcszReason)
{
    INT32       nRetCode = 0;

    LOG_PROCESS_ERROR(pcszData);
    LOG_PROCESS_ERROR(pcszReason);

    m_pCmd = CCmdManager::GetInstance().NewCmd(CMD_MODIFY_ROLE_DATA);
    LOG_PROCESS_ERROR(m_pCmd);

    m_pCmd->nType = CMD_MODIFY_ROLE_DATA;
    m_pCmd->nSvrNum = 0;
    m_pCmd->nWashout = time(NULL) + TL_CMD_LONG_TIMEOUT;

    ((MODIFY_ROLE_DATA*)m_pCmd)->dwRoleID = dwRoleID;
    ((MODIFY_ROLE_DATA*)m_pCmd)->dwTargetRoleID = dwTargetRoleID;
    strxcpy(((MODIFY_ROLE_DATA*)m_pCmd)->szReason, pcszReason, COMMON_NAME_LEN);
    memcpy(((MODIFY_ROLE_DATA*)m_pCmd)->szData, pcszData, nLength);
    ((MODIFY_ROLE_DATA*)m_pCmd)->nLength = nLength;

    nRetCode = CMessageHandler::GetInstance().DoModifyRoleData(dwRoleID, dwTargetRoleID, nLength, pcszData, pcszReason);
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (m_pCmd)
        CCmdManager::GetInstance().DelCmd(m_pCmd);
    return FALSE;
}

BOOL CCmdManager::ExeRoleGMCmd(CMD_BASE *pCmd)
{
    INT32       nRetCode = 0;
    EXE_ROLE_CMD    *pGMCmd = (EXE_ROLE_CMD *)pCmd;
    LOG_PROCESS_ERROR(pCmd);

    m_pCmd = pCmd;
    m_pCmd->nWashout = time(NULL) + TL_CMD_LONG_TIMEOUT;

    nRetCode = CMessageHandler::GetInstance().DoExeRoleGMCmd(pGMCmd->dwRoleID, pGMCmd->szGM, pGMCmd->szReason);
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (m_pCmd)
        CCmdManager::GetInstance().DelCmd(m_pCmd);
    return FALSE;
}



// log
BOOL CCmdManager::QueryLog(INT32 nLogType, UINT32 dwBeginTime, UINT32 dwEndTime, const char *pcszQueryStr)
{
    INT32       nRetCode = 0;

    LOG_PROCESS_ERROR(pcszQueryStr);

    m_pCmd = CCmdManager::GetInstance().NewCmd(CMD_LOG);
    LOG_PROCESS_ERROR(m_pCmd);

    m_pCmd->nType = CMD_LOG;
    m_pCmd->nSvrNum = 0;
    m_pCmd->nWashout = time(NULL) + TL_CMD_LONG_TIMEOUT;
    ((LOG_DATA*)m_pCmd)->nLogType = nLogType;
    ((LOG_DATA*)m_pCmd)->dwBeginTime = dwBeginTime;
    ((LOG_DATA*)m_pCmd)->dwEndTime = dwEndTime;
    strxcpy(((LOG_DATA*)m_pCmd)->szQueryStr, pcszQueryStr, sizeof(((LOG_DATA*)m_pCmd)->szQueryStr));

    nRetCode = CMessageHandler::GetInstance().DoLog(nLogType, dwBeginTime, dwEndTime, pcszQueryStr);
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (m_pCmd)
        CCmdManager::GetInstance().DelCmd(m_pCmd);
    return FALSE;
}










BOOL CCmdManager::SetExeServerNum(INT32 nSvrNum)
{
    LOG_PROCESS_ERROR(m_pCmd);
    m_pCmd->nSvrNum = nSvrNum;

    return TRUE;
Exit0:
    return FALSE;
}

BOOL CCmdManager::IsCmdExecuting(BOOL isModifyRoleCmd /*= FALSE*/)
{
    if (isModifyRoleCmd == TRUE)
    {
        return m_pCmd != NULL;
    }
    else
    {
        return (m_pCmd != NULL) || (g_pRoleInfo != NULL);
    }
}

void CCmdManager::CmdEnd()
{
    m_pCmd = NULL;
}






BOOL CCmdManager::Success(CMD_BASE *pCmd)
{
    INT32       nRetCode = 0;

    LOG_PROCESS_ERROR(pCmd);

    switch (pCmd->nType)
    {
    case CMD_QUERY_ROLE_ID:
    {
        nRetCode = CGMLog::GetInstance().Log("查询角色ID指令执行成功");
        LOG_CHECK_ERROR(nRetCode);
    }
        break;
    case CMD_QUERY_ROLE_DATA:
    {
        nRetCode = CGMLog::GetInstance().Log("查询角色信息成功");
        LOG_CHECK_ERROR(nRetCode);
    }
        break;
    case CMD_FORBIDDEN_CHAT:
    {
        nRetCode = CGMLog::GetInstance().Log("禁言角色成功");
        LOG_CHECK_ERROR(nRetCode);
    }
        break;
    case CMD_FREEZE_ROLE:
    {
        nRetCode = CGMLog::GetInstance().Log("冻结角色成功");
        LOG_CHECK_ERROR(nRetCode);
    }
        break;
    case CMD_KICK_ROLE:
    {
        nRetCode = CGMLog::GetInstance().Log("踢线角色成功");
        LOG_CHECK_ERROR(nRetCode);
    }
        break;
    case CMD_ANNOUNCE:
    {
        nRetCode = CGMLog::GetInstance().Log("发布公告成功");
        LOG_CHECK_ERROR(nRetCode);
    }
        break;
    case CMD_SEND_MAIL:
    {
        nRetCode = CGMLog::GetInstance().Log("发送邮件成功");
        LOG_CHECK_ERROR(nRetCode);
    }
        break;
    case CMD_LOG:
    {
        nRetCode = CGMLog::GetInstance().Log("查询日志成功！");
        LOG_CHECK_ERROR(nRetCode);
    }
        break;
    case CMD_EXECUTE_GM_STR:
    {
        nRetCode = CGMLog::GetInstance().Log("执行gm lua成功");
        LOG_CHECK_ERROR(nRetCode);
    }
        break;
    case CMD_LOAD_ROLE_DATA:
    {
        nRetCode = CGMLog::GetInstance().Log("加载角色数据成功");
        LOG_CHECK_ERROR(nRetCode);
    }
        break;
    case CMD_MODIFY_ROLE_DATA:
    {
        nRetCode = CGMLog::GetInstance().Log("修改角色数据成功");
        LOG_CHECK_ERROR(nRetCode);
    }
        break;
    default:
        break;
    }

    CCmdManager::GetInstance().DelCmd(pCmd);

    return TRUE;
Exit0:
    return FALSE;
}

BOOL CCmdManager::Washout(CMD_BASE *pCmd)
{
    INT32       nRetCode = 0;

    LOG_PROCESS_ERROR(pCmd);

    switch (pCmd->nType)
    {
    case CMD_QUERY_ROLE_ID:
    {
        nRetCode = CGMLog::GetInstance().Log("查询角色ID指令超时，部分服务器未执行完毕");
        LOG_CHECK_ERROR(nRetCode);
    }
        break;
    case CMD_QUERY_ROLE_DATA:
    {
        QUERY_ROLE_DATA *pQuery = (QUERY_ROLE_DATA *)pCmd;
        nRetCode = CGMLog::GetInstance().Log("查询角色数据指令超时");
        LOG_CHECK_ERROR(nRetCode);
    }
        break;
    case CMD_FORBIDDEN_CHAT:
    {
        FORBIDDEN_CHAT *pForbidChat = (FORBIDDEN_CHAT *)pCmd;
        nRetCode = CGMLog::GetInstance().Log("禁言角色指令超时");
        LOG_CHECK_ERROR(nRetCode);

    }
        break;
    case CMD_FREEZE_ROLE:
    {
        FREEZE_ROLE *pFreezeRole = (FREEZE_ROLE *)pCmd;
        nRetCode = CGMLog::GetInstance().Log("冻结角色指令超时");
        LOG_CHECK_ERROR(nRetCode);
    }
        break;
    case CMD_KICK_ROLE:
    {
        KICK_ROLE *pKickRole = (KICK_ROLE *)pCmd;
        nRetCode = CGMLog::GetInstance().Log("踢线角色指令超时");
        LOG_CHECK_ERROR(nRetCode);
    }
        break;
    case CMD_ANNOUNCE:
    {
        ANNOUNCE *pAnnounce = (ANNOUNCE*)pCmd;
        nRetCode = CGMLog::GetInstance().Log("发布公告指令超时， 剩余[%d]个服务器未执行", pAnnounce->nSvrNum);
        LOG_CHECK_ERROR(nRetCode);
    }
        break;
    case CMD_SEND_MAIL:
    {
        SEND_MAIL   *pSendMail = (SEND_MAIL*)pCmd;
        nRetCode = CGMLog::GetInstance().Log("发送邮件指令超时");
        LOG_CHECK_ERROR(nRetCode);
    }
        break;
    case CMD_LOG:
    {
        nRetCode = CGMLog::GetInstance().Log("查询日志超时！");
        LOG_CHECK_ERROR(nRetCode);
    }
        break;
    case CMD_EXECUTE_GM_STR:
    {
        EXECUTE_GM_STR *pExeStrCmd = (EXECUTE_GM_STR*)pCmd;
        nRetCode = CGMLog::GetInstance().Log("执行gm lua指令超时， 剩余[%d]个服务器未执行", pExeStrCmd->nSvrNum);
        LOG_CHECK_ERROR(nRetCode);
    }
        break;
    case CMD_LOAD_ROLE_DATA:
    {
        LOAD_ROLE_DATA *pLoadRoleCmd = (LOAD_ROLE_DATA *)pCmd;
        nRetCode = CGMLog::GetInstance().Log("加载角色[%u]数据超时", pLoadRoleCmd->dwRoleID);
        LOG_CHECK_ERROR(nRetCode);
    }
        break;
    case CMD_MODIFY_ROLE_DATA:
    {
        MODIFY_ROLE_DATA *pModifyRoleCmd = (MODIFY_ROLE_DATA *)pCmd;
        nRetCode = CGMLog::GetInstance().Log("修改角色数据类型[%d]超时", pModifyRoleCmd->nType);
        LOG_CHECK_ERROR(nRetCode);
    }
        break;
    default:
        break;
    }

    CCmdManager::GetInstance().DelCmd(pCmd);

    return TRUE;
Exit0:
    nRetCode = CGMLog::GetInstance().Log("指令错误！！");
    LOG_CHECK_ERROR(nRetCode);
    return FALSE;
}

CMD_BASE* CCmdManager::NewCmd(INT32 nType)
{
    switch (nType)
    {
        case CMD_QUERY_ROLE_ID:
        {
            return new QUERY_ROLE_ID;
        }
        break;
        case CMD_QUERY_ROLE_DATA:
        {
            return new QUERY_ROLE_DATA;
        }
            break;
        case CMD_FORBIDDEN_CHAT:
        {
            return new FORBIDDEN_CHAT;
        }
            break;
        case  CMD_FREEZE_ROLE:
        {
            return new FREEZE_ROLE;
        }
            break;
        case CMD_KICK_ROLE:
        {
            return new KICK_ROLE;
        }
            break;
        case CMD_ANNOUNCE:
        {
            return new ANNOUNCE;
        }
            break;
        case CMD_GET_ANNOUNCE_LIST:
        {
            return new GET_ANNOUNCE_LIST;
        }
            break;
        case CMD_DEL_ANNOUNCE:
        {
            return new DEL_ANNOUNCE;
        }
            break;
        case CMD_SEND_MAIL:
            return new SEND_MAIL;
            break;
        case CMD_LOG:
            return new LOG_DATA;
            break;
        case CMD_EXECUTE_GM_STR:
            return new EXECUTE_GM_STR;
            break;
        case CMD_LOAD_ROLE_DATA:
            return new LOAD_ROLE_DATA;
            break;
        case CMD_MODIFY_ROLE_DATA:
            return new MODIFY_ROLE_DATA;
            break;
        case CMD_QUERY_NAME_TO_ID:
            return new QUERY_NAME_TO_ID;
            break;
        case CMD_EXE_ROLE_GM_CMD:
            return new EXE_ROLE_CMD;
            break;
    default:
        break;
    }

    return NULL;
}

BOOL CCmdManager::DelCmd(CMD_BASE *pCmd)
{
    LOG_PROCESS_ERROR(pCmd);

    switch (pCmd->nType)
    {
    case CMD_QUERY_ROLE_ID:
    {
        delete ((QUERY_ROLE_ID*)pCmd);
    }
        break;
    case CMD_QUERY_ROLE_DATA:
    {
        delete ((QUERY_ROLE_DATA*)pCmd);
    }
        break;
    case CMD_FORBIDDEN_CHAT:
    {
        delete ((FORBIDDEN_CHAT*)pCmd);
    }
        break;
    case CMD_FREEZE_ROLE:
    {
        delete ((FREEZE_ROLE*)pCmd);
    }
        break;
    case CMD_KICK_ROLE:
    {
        delete ((KICK_ROLE*)pCmd);
    }
        break;
    case CMD_ANNOUNCE:
    {
        delete ((ANNOUNCE*)pCmd);
    }
        break;
    case CMD_GET_ANNOUNCE_LIST:
    {
        delete ((GET_ANNOUNCE_LIST*)pCmd);
    }
        break;
    case CMD_DEL_ANNOUNCE:
    {
        delete ((DEL_ANNOUNCE*)pCmd);
    }
        break;
    case CMD_SEND_MAIL:
        delete ((SEND_MAIL*)pCmd);
        break;
    case CMD_LOG:
        delete ((LOG_DATA*)pCmd);
        break;
    case CMD_EXECUTE_GM_STR:
        delete ((EXECUTE_GM_STR*)pCmd);
        break;
    case CMD_LOAD_ROLE_DATA:
        delete ((LOAD_ROLE_DATA*)pCmd);
        break;
    case CMD_MODIFY_ROLE_DATA:
        delete ((MODIFY_ROLE_DATA*)pCmd);
        break;
    case CMD_QUERY_NAME_TO_ID:
        delete ((QUERY_NAME_TO_ID*)pCmd);
        break;
    case CMD_EXE_ROLE_GM_CMD:
        delete ((EXE_ROLE_CMD*)pCmd);
        break;
    default:
        break;
    }

    return TRUE;
Exit0:
    return FALSE;
}


BOOL CCmdManager::AddSvr(UINT32 dwSvrID)
{
    m_PreExecuteSvrList.push_back(dwSvrID);

    return TRUE;
}

UINT32 CCmdManager::First()
{
    m_Cursor = m_PreExecuteSvrList.begin();
    PROCESS_ERROR(m_Cursor != m_PreExecuteSvrList.end());

    return *m_Cursor;
Exit0:
    return 0xFFFFFFFF;
}

UINT32 CCmdManager::Next()
{
    ++m_Cursor;
    PROCESS_ERROR(m_Cursor != m_PreExecuteSvrList.end());

    return *m_Cursor;
Exit0:
    return 0xFFFFFFFF;
}


BOOL CCmdManager::IsCompleteAll()
{
    PROCESS_ERROR(TRUE == m_IsCmdComplete);

    return TRUE;
Exit0:
    return FALSE;
}


