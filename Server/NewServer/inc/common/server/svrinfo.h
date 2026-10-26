#ifndef __SDF_SERVER_INCLUDE_H_
#define __SDF_SERVER_INCLUDE_H_
#include <sdframework.h>
#include <string>
#include <map>
using namespace std;
class CSvrInfo
{
public:
    CSvrInfo(VOID);
public:
    ~CSvrInfo(VOID);
    VOID                    SetServerID(const UINT32 dwServerID);
    UINT32                  GetServerID() const;

    VOID                    SetOnlineNum(const INT32 nOnlineNum);
    INT32                   GetOnlineNum() const;

    VOID                    SetMaxUsers(const INT32 nMaxUsers);
    INT32                   GetMaxUsers() const;

    UINT16          		GetPort() const;
    VOID                    SetPort(const UINT16 nPort);

    UINT32                  GetAddress() const;
    VOID                    SetAddress(const UINT32 nAddress);

    INT32                   GetServerType() const;
    VOID                    SetServerType(const INT32 nType);

    BOOL                    GetConnected() const;
    VOID                    SetConnected(const BOOL bConnected);

    UINT8                   GetState() const;
    VOID                    SetState(const UINT8 bySatate);

    tstring                 GetDesc() const;
    VOID                    SetDesc(const tstring strDesc);
    VOID                    SetDesc(const CHAR* cpData,INT32 nLen);

    tstring                 GetName() const;
    VOID                    SetName(const tstring strName);

private:
    UINT32					m_dwServerID;
    INT32                   m_nOnlineNum;
    INT32                   m_nMaxUsers;
    UINT16          		m_wPort;
    UINT32                  m_dwAddress;
    INT32                   m_nServerType;
    BOOL                    m_bConnect;
    UINT8                   m_byState;
    tstring                 m_strDesc;
    tstring                 m_strName;
};


class CSvrInfoMgr 
{	
public:
    typedef map<UINT32,CSvrInfo*>       				 CSvrInfoMap;
    typedef map<UINT32,CSvrInfo*>::iterator				 CSvrInfoMapItr;
    CSvrInfoMgr(VOID);
public:
    ~CSvrInfoMgr(VOID);
    VOID                    DeleteAll();
    BOOL                    AddSvrInfo(CSvrInfo* poSvrInfo);
    CSvrInfo*               FindSvrInfo(UINT32 dwServerID);
    CSvrInfo*               RemoveSvrInfo(UINT32 dwServerID);
    CSvrInfoMap&            GetInfoMap(); 
    CSvrInfo*               GetGameServer();
    UINT32                  GetServerCount(UINT32 nType);
private:
    CSvrInfoMap             m_mapSvrInfo;
};

#endif

