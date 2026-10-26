


#ifndef _H_TL_USER_INL_H_
#define _H_TL_USER_INL_H_


inline UINT32 CTLUser::GetID()
{
    return m_dwUserID;
}

inline void CTLUser::SetID(UINT32 dwID)
{
    m_dwUserID = dwID;
}

inline const char* CTLUser::GetUserName()
{
    return m_szUserName;
}

inline void CTLUser::SetUserName(const char *pcszName)
{
    LOG_PROCESS_ERROR(pcszName);
    strxcpy(m_szUserName, pcszName, ROLE_NAME_LEN);
Exit0:
    return;
}

inline UINT32 CTLUser::GetSessionID()
{
    return m_dwSessionID;
}

inline void CTLUser::SetSessionID(UINT32 dwSessionID)
{
    m_dwSessionID = dwSessionID;
}

inline BOOL CTLUser::IsBusy()
{
    return m_nState == TL_STATE_BUSY;
}

inline BOOL CTLUser::SetBusy()
{
    return m_nState = TL_STATE_BUSY;
}

inline BOOL CTLUser::SetIdel()
{
    return m_nState = TL_STATE_IDLE;
}

//inline INT32 CTLUser::GetState()
//{
//    return m_nState;
//}
//
//inline void CTLUser::SetState(INT32 nState)
//{
//    m_nState = nState;
//}

inline UINT32 CTLUser::GetIP()
{
    return m_dwIP;
}

inline void CTLUser::SetIP(UINT32 dwIP)
{
    m_dwIP = dwIP;
}

inline UINT16 CTLUser::GetPort()
{
    return m_wPort;
}

inline void CTLUser::SetPort(UINT16 wPort)
{
    m_wPort = wPort;
}

inline const char *CTLUser::GetComputerName()
{
    return m_szComputerName;
}

inline void CTLUser::SetComputerName(const char *pcszName)
{
    LOG_PROCESS_ERROR(pcszName);

    strxcpy(m_szComputerName, pcszName, sizeof(m_szComputerName));

Exit0:
    return;
}

inline GM_PERMISSION CTLUser::GetPermission()
{
    return m_ePermission;
}

inline void CTLUser::SetPermission(GM_PERMISSION ePermission)
{
    m_ePermission = ePermission;
}

inline void CTLUser::SetLD()
{
    m_bLD = TRUE;
}

inline BOOL CTLUser::IsLD()
{
    return m_bLD == TRUE;
}

inline BOOL CTLUser::CanExecuteCmd()
{
    return NULL == m_pCmd;
}

inline CMD_DATA_BASE* CTLUser::GetCmd()
{
    return m_pCmd;
}

inline void CTLUser::SetCmd(CMD_DATA_BASE *pCmd)
{
    LOG_PROCESS_ERROR(pCmd);
    m_pCmd = pCmd;
Exit0:
    return ;
}

inline void CTLUser::ClearCmd()
{
    m_pCmd = NULL;
}


#endif //_H_TL_USER_INL_H_























