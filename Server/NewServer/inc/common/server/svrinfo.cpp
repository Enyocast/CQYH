#include "stdafx.h"
#include "svrinfo.h"
#include "sdutil.h"

CSvrInfo::CSvrInfo(VOID)
{
    m_dwAddress       = 0;
    m_dwServerID      = 0;
    m_nMaxUsers       = 0;
    m_nOnlineNum      = 0;
    m_wPort           = 0;
    m_byState         = 0;
    m_nServerType     = TYPE_GATE_SERVER;
    m_strDesc.clear();
    m_strName.clear();
}

CSvrInfo::~CSvrInfo(void)
{
    m_strDesc.clear();
    m_strName.clear();
}

VOID CSvrInfo::SetAddress(const UINT32 nAddress)
{
    m_dwAddress = nAddress;
}

UINT32 CSvrInfo::GetAddress() const
{
    return m_dwAddress;
}

VOID CSvrInfo::SetMaxUsers(const INT32 nMaxUsers)
{
    m_nMaxUsers = nMaxUsers;
}

INT32 CSvrInfo::GetMaxUsers() const
{
    return m_nMaxUsers;
}

VOID CSvrInfo::SetOnlineNum(const INT32 nOnlineNum)
{
    m_nOnlineNum = nOnlineNum;
}

INT32 CSvrInfo::GetOnlineNum() const
{
    return m_nOnlineNum;
}

VOID CSvrInfo::SetPort(const UINT16 nPort)
{
    m_wPort = nPort;
}

UINT16 CSvrInfo::GetPort() const
{
    return m_wPort;
}

VOID CSvrInfo::SetServerID(const UINT32 dwServerID)
{
    m_dwServerID = dwServerID;
}

UINT32 CSvrInfo::GetServerID() const
{
    return m_dwServerID;
}

VOID CSvrInfo::SetServerType(const INT32 nType)
{
    m_nServerType = nType;
}

INT32 CSvrInfo::GetServerType() const
{
    return m_nServerType;
}

UINT8 CSvrInfo::GetState() const
{
    return m_byState;
}

VOID CSvrInfo::SetState(const UINT8 bySatate)
{
    m_byState = bySatate;
}

BOOL CSvrInfo::GetConnected() const
{
    return m_bConnect;
}

VOID CSvrInfo::SetConnected(const BOOL bConnected)
{
    m_bConnect = bConnected;
}

tstring CSvrInfo::GetDesc() const
{
    return m_strDesc;
}

VOID CSvrInfo::SetDesc(const tstring strDesc)
{
    m_strDesc = strDesc;
}

VOID CSvrInfo::SetDesc(const CHAR *cpData, INT32 nLen)
{
    m_strDesc.clear();
    for ( INT32 n = 0; n < nLen; n ++ )
    {
	    m_strDesc.push_back(cpData[nLen]);
    }
}

void CSvrInfo::SetName(const tstring strName)
{
    m_strName = strName;
}

tstring CSvrInfo::GetName() const
{
    return m_strName;
}

CSvrInfoMgr::CSvrInfoMgr()
{
    DeleteAll();
}

CSvrInfoMgr::~CSvrInfoMgr()
{
    DeleteAll();
}

VOID CSvrInfoMgr::DeleteAll()
{
    CSvrInfoMapItr itr;
    for (itr = m_mapSvrInfo.begin(); itr != m_mapSvrInfo.end(); itr ++ )
    {
	    CSvrInfo* pSvrinfo = (itr)->second;
	    if (pSvrinfo)
	    {
		    SDDelete pSvrinfo;
	    }
    }
    m_mapSvrInfo.clear();
}

BOOL CSvrInfoMgr::AddSvrInfo(CSvrInfo *poSvrInfo)
{
    CSvrInfo* pResult = FindSvrInfo(poSvrInfo->GetServerID());
    if (NULL != pResult)
        return FALSE;
    m_mapSvrInfo.insert(make_pair(poSvrInfo->GetServerID(),poSvrInfo));
    return TRUE;  
}

CSvrInfo* CSvrInfoMgr::FindSvrInfo(UINT32 dwServerID)
{
    CSvrInfoMapItr itr = m_mapSvrInfo.find(dwServerID);
    if (itr != m_mapSvrInfo.end())
    {
        return itr->second;
    }
    return NULL;
}

CSvrInfo* CSvrInfoMgr::RemoveSvrInfo(UINT32 dwServerID)
{
    CSvrInfo* pResult = NULL;
    CSvrInfoMapItr itr = m_mapSvrInfo.find(dwServerID);
    if (itr != m_mapSvrInfo.end())
    {
	    pResult = itr->second;
	    m_mapSvrInfo.erase(itr);
    }
    return pResult;
}

CSvrInfoMgr::CSvrInfoMap& CSvrInfoMgr::GetInfoMap() 
{
    return m_mapSvrInfo;
}

CSvrInfo*  CSvrInfoMgr::GetGameServer()
{
    CSvrInfo* pResult = NULL;
    for(CSvrInfoMapItr itr = m_mapSvrInfo.begin(); itr != m_mapSvrInfo.end(); ++itr)
    {
        CSvrInfo* poSvrInfo = itr->second;
        if (poSvrInfo->GetServerType() == TYPE_GAME_SERVER)
        {
            if(poSvrInfo->GetState() == 2)
                continue;

            if(pResult == NULL)
                pResult = poSvrInfo;
            else if(poSvrInfo->GetServerID() == 0x02040101)
                pResult = poSvrInfo;
        }
    }
    return pResult;
}

UINT32 CSvrInfoMgr::GetServerCount(UINT32 nType)
{
    UINT32 dwCount = 0;
    for(CSvrInfoMapItr itr = m_mapSvrInfo.begin(); itr != m_mapSvrInfo.end(); ++itr)
    {
        CSvrInfo* poSvrInfo = itr->second;
        if (poSvrInfo->GetServerType() == nType)
            ++dwCount;
    }
    return dwCount;
}



