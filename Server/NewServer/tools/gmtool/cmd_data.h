/********************************************************************
	created:	13:1:2014   14:48
	file:		cmd_data.h
	author:		Allan Tao
	
	purpose:	
*********************************************************************/

#ifndef _H_CMD_DATA_H_
#define _H_CMD_DATA_H_

#include <list>
#include "gm_def.h"
#include "predefine.h"
#include "string_def.h"
#include "chat_def.h"
#include "tl_config.h"


enum CMD_TYPE_ENUM
{
    CMD_PRE_QUERY       = 1,

    CMD_QUERY_ROLE_ID   = 2,
    CMD_QUERY_ROLE_DATA = 3,

    CMD_FORBIDDEN_CHAT  = 4,
    CMD_FREEZE_ROLE     = 5,
    CMD_KICK_ROLE       = 6,
    CMD_ANNOUNCE        = 7,
    CMD_GET_ANNOUNCE_LIST = 8,
    CMD_DEL_ANNOUNCE    = 9,
    CMD_SEND_MAIL       = 10,
    CMD_LOG             = 11,
    CMD_EXECUTE_GM_STR  = 12,

    CMD_LOAD_ROLE_DATA = 13,
    CMD_MODIFY_ROLE_DATA = 14,

    CMD_QUERY_NAME_TO_ID = 15,

    CMD_EXE_ROLE_GM_CMD = 16,
    

};

struct CMD_BASE 
{
    INT32   nType;
    INT32   nSvrNum;
    INT32   dwSessionID[MAX_SESSION_COUNT];
    INT32   nWashout;
};



struct PRE_QUERY : CMD_BASE
{
    char        szRoleName[ROLE_NAME_LEN];
    INT32       nCmdType;
    CMD_BASE    *pCmd;
};

struct QUERY_ROLE_ID : CMD_BASE 
{
    char        szName[USER_NAME_LEN];
    INT32       nQueryType;
};

struct QUERY_ROLE_DATA : CMD_BASE
{
    //INT32   nRoleNum;
    UINT32  dwRoleID;
    char    szRoleName[ROLE_NAME_LEN];
};

struct ROLE_RESULT 
{
    char    szRoleName[ROLE_NAME_LEN];
    UINT32  dwRoleID;
    INT32   nResult;
};

struct FORBIDDEN_CHAT : CMD_BASE 
{
    INT64   llTime;
    char    szFileName[256];
    char    szRoleName[ROLE_NAME_LEN];
    std::list<ROLE_RESULT>  roleList;
    std::list<ROLE_RESULT>  roleResList;
};

struct FREEZE_ROLE : CMD_BASE 
{
    INT64   llTime;
    char    szFileName[256];
    char    szRoleName[ROLE_NAME_LEN];
    std::list<ROLE_RESULT>  roleList;
    std::list<ROLE_RESULT>  roleResList;
};

struct KICK_ROLE : CMD_BASE 
{
    char    szFileName[256];
    char    szRoleName[ROLE_NAME_LEN];
    std::list<ROLE_RESULT>  roleList;
    std::list<ROLE_RESULT>  roleResList;
};

struct SEND_MAIL : CMD_BASE
{
    char    szFileName[256];
    char    szRoleName[ROLE_NAME_LEN];
    std::list<ROLE_RESULT>  roleList;
    std::list<ROLE_RESULT>  roleResList;

    char    szTitle[MAIL_SUBJECT_LEN];
    char    szContent[MAIL_CONTENT_LEN];
    char    szReason[GM_REASON_LEN];
    UINT32  dwItemID;
    INT32   nItemNum;
};

struct ANNOUNCE : CMD_BASE 
{
    INT32       nGroupID;
    UINT32      dwBeginTime;
    INT32       nIntervalTime;
    INT32       nRepeatNum;
    char        szAnnounce[GM_ANNOUNCE_LENGTH];
};

struct GET_ANNOUNCE_LIST : CMD_BASE 
{
    INT32 nGroupID;
};

struct DEL_ANNOUNCE : CMD_BASE 
{
    INT32       nGroupID;
    UINT32      dwAnnounceSerial;
};

struct LOG_DATA : CMD_BASE 
{
    INT32       nLogType;
    UINT32      dwBeginTime;
    UINT32      dwEndTime;
    char        szQueryStr[MAX_GM_COMMAND_LEN];
};


struct EXECUTE_GM_STR : CMD_BASE 
{
    char        szStr[MAX_GM_COMMAND_LEN];
};

struct LOAD_ROLE_DATA : CMD_BASE 
{
    UINT32      dwRoleID;
    char        szRoleName[ROLE_NAME_LEN];
};

struct MODIFY_ROLE_DATA : CMD_BASE
{
    UINT32      dwRoleID;
    char        szRoleName[ROLE_NAME_LEN];
    UINT32      dwTargetRoleID;
    INT32       nLength;
    char        szReason[GM_REASON_LEN];
    char        szData[1024 * 30];
};

struct ROLE_NAME_DATA 
{
    UINT32      dwRoleID;
    char        szRoleName[ROLE_NAME_LEN];
};

struct QUERY_NAME_TO_ID : CMD_BASE 
{
    std::map<INT32, ROLE_NAME_DATA> RoleNameMap;
    INT32       nMaxCount;
};

struct EXE_ROLE_CMD : CMD_BASE 
{
    UINT32      dwRoleID;
    char        szRoleName[ROLE_NAME_LEN];
    char        szGM[MAX_GM_COMMAND_LEN];
    char        szReason[GM_REASON_LEN];
};












struct SERVER_CMD_DATA 
{
    UINT32      dwSvrID;
    INT32       nState;
    INT32       nResult;

    bool operator== (SERVER_CMD_DATA &data)
    {
        return this->dwSvrID == data.dwSvrID;
    }

    bool operator == (UINT32 dwSvrIndex)
    {
        return this->dwSvrID == dwSvrIndex;
    }
};

class CCmdData 
{
public:
    CCmdData();
    virtual ~CCmdData();

    BOOL    Init();
    BOOL    UnInit();

    void    SetType(INT32 nType)     { m_nType = nType; }
    INT32   GetType()               { return m_nType; }

    UINT32  GetExeState()                           { return m_dwExeState; }
    void    SetExeState(CMD_EXE_STATE eState)       { m_dwExeState = eState; }

    void    SetExeSvrID(UINT32 dwSvrID)     { m_dwCurSvrID = dwSvrID; }
    UINT32  GetExeSvrID()                   { return m_dwCurSvrID; }

    void CompleteOne(UINT32 dwSvrID, INT32 nResult);
    BOOL IsCompleteAll();

    INT32   GetSvrNum();

    BOOL    AddPreExeSvr(UINT32 dwSvrID);

    SERVER_CMD_DATA* First();
    SERVER_CMD_DATA* Next();


private:
    INT32       m_nType;
    UINT32      m_dwExeState;
    UINT32      m_dwCurSvrID;

    INT32       m_nUncompleteCount;
    typedef     std::list<SERVER_CMD_DATA>        SVR_LIST;
    SVR_LIST::iterator      m_Cursor;
    SVR_LIST    m_ExecuteSvrList;

};

class CCmdGetRoleList : public CCmdData
{
public:
    CCmdGetRoleList()        {}
    virtual ~CCmdGetRoleList()       {}

    BOOL    AddNameList(const char *pBuffer, UINT32 dwLength);
    UINT32  GetNameBufferLength()       { return m_dwLength; }
    const char *GetNameBuffer()     { return m_szBuffer; }

    const char *FirstName();
    const char *NextName();

    //BOOL    SetName(const char *pcszName);
    //const char* GetName()       { return m_szRoleName; }

private:
    //char        m_szRoleName[ROLE_NAME_LEN];


    UINT32      m_dwCursor;
    UINT32      m_dwCount;
    char        m_szRoleName[MAX_SEARCH_ROLE_NUM][ROLE_NAME_LEN];


    UINT32      m_dwLength;
    char        m_szBuffer[MAX_SEARCH_ROLE_NUM * ROLE_NAME_LEN];

};


class CCmdViewRoleData : public CCmdData
{
public:
    CCmdViewRoleData()                {}
    virtual ~CCmdViewRoleData()       {}

    UINT32  GetRoleID()     { return m_dwRoleID; }
    void    SetRoleID(UINT32 dwRoleID)      { m_dwRoleID = dwRoleID; }

private:
    UINT32  m_dwRoleID;
};

class CCmdLoadRoleData : public CCmdData
{
public:
    CCmdLoadRoleData()                {}
    virtual ~CCmdLoadRoleData()       {}

    UINT32  GetRoleID()     { return m_dwRoleID; }
    void    SetRoleID(UINT32 dwRoleID)      { m_dwRoleID = dwRoleID; }

private:
    UINT32  m_dwRoleID;
};

class CCmdModifyItem : public CCmdData
{
public:
    CCmdModifyItem()                {}
    virtual ~CCmdModifyItem()       {}

    UINT32  GetRoleID()     { return m_dwRoleID; }
    void    SetRoleID(UINT32 dwRoleID)      { m_dwRoleID = dwRoleID; }

    const char *GetName()   { return szName; };
    void    SetName(const char *pcszBuffer);

    INT32   GetConSlot()    { return m_nConSlot; }
    INT32   GetItemSlot()   { return m_nItemSlot; }
    INT32   GetItemNum()    { return m_nItemNum; }

    void    SetConSlot(INT32 nConSlot)      { m_nConSlot = nConSlot; }
    void    SetItemSlot(INT32 nItemSlot)    { m_nItemSlot = nItemSlot; }
    void    SetItemNum(INT32 nNum)          { m_nItemNum = nNum; }

private:
    INT32       m_nConSlot;
    INT32       m_nItemSlot;
    INT32       m_nItemNum;
    UINT32  m_dwRoleID;
    char        szName[MAX_ITEM_NAME_LEN];
};

class CCmdModifyMoney : public CCmdData
{
public:
    CCmdModifyMoney()                {}
    virtual ~CCmdModifyMoney()       {}

    UINT32  GetRoleID()     { return m_dwRoleID; }
    void    SetRoleID(UINT32 dwRoleID)      { m_dwRoleID = dwRoleID; }

    INT32   GetMoneyType()    { return m_nMoneyType; }
    INT32   GetMoneyValue()   { return m_nMoneyValue; }

    void    SetMoneyType(INT32 nMoneyType)      { m_nMoneyType = nMoneyType; }
    void    SetMoneyValue(INT32 nMoenyValue)    { m_nMoneyValue = nMoenyValue; }

private:
    INT32       m_nMoneyType;
    INT32       m_nMoneyValue;
    INT32       m_nItemNum;
    UINT32  m_dwRoleID;
};


class CCmdDelItem : public CCmdData
{
public:
    CCmdDelItem()                {}
    virtual ~CCmdDelItem()       {}

    UINT32  GetRoleID()     { return m_dwRoleID; }
    void    SetRoleID(UINT32 dwRoleID)      { m_dwRoleID = dwRoleID; }

    const char *GetName()   { return szName; };
    void    SetName(const char *pcszBuffer);

    INT32   GetConSlot()    { return m_nConSlot; }
    INT32   GetItemSlot()   { return m_nItemSlot; }
    //INT32   GetItemNum()    { return m_nItemNum; }

    void    SetConSlot(INT32 nConSlot)      { m_nConSlot = nConSlot; }
    void    SetItemSlot(INT32 nItemSlot)    { m_nItemSlot = nItemSlot; }
    //void    SetItemNum(INT32 nNum)          { m_nItemNum = nNum; }

private:
    INT32       m_nConSlot;
    INT32       m_nItemSlot;
    //INT32       m_nItemNum;
    UINT32  m_dwRoleID;
    char        szName[MAX_ITEM_NAME_LEN];
};


class CCmdForbidChat : public CCmdData
{
public:
    CCmdForbidChat()        {}
    virtual ~CCmdForbidChat()       {}

    BOOL    AddNameList(const char *pBuffer, UINT32 dwLength);
    UINT32  GetNameBufferLength()       { return m_dwLength; }
    const char *GetNameBuffer()     { return m_szBuffer; }

    void    SetTime(UINT32 dwTime)      { m_dwTime = dwTime; }
    UINT32  GetTime()                   { return m_dwTime; }
private:
    UINT32      m_dwTime;
    UINT32      m_dwLength;
    char        m_szBuffer[MAX_SEARCH_ROLE_NUM * ROLE_NAME_LEN];

};


class CCmdFreezeRole : public CCmdData
{
public:
    CCmdFreezeRole()        {}
    virtual ~CCmdFreezeRole()       {}

    BOOL    AddNameList(const char *pBuffer, UINT32 dwLength);
    UINT32  GetNameBufferLength()       { return m_dwLength; }
    const char *GetNameBuffer()     { return m_szBuffer; }

    void    SetTime(UINT32 dwTime)      { m_dwTime = dwTime; }
    UINT32  GetTime()                   { return m_dwTime; }
private:
    UINT32      m_dwTime;
    UINT32      m_dwLength;
    char        m_szBuffer[MAX_SEARCH_ROLE_NUM * ROLE_NAME_LEN];

};

//class CCmdUnforbidChat : public CCmdData
//{
//public:
//    CCmdUnforbidChat()        {}
//    virtual ~CCmdUnforbidChat()       {}
//
//    BOOL    AddNameList(const char *pBuffer, UINT32 dwLength);
//    UINT32  GetNameBufferLength()       { return m_dwLength; }
//    const char *GetNameBuffer()     { return m_szBuffer; }
//
//private:
//    UINT32      m_dwLength;
//    char        m_szBuffer[MAX_SEARCH_ROLE_NUM * ROLE_NAME_LEN];
//
//};
//
//class CCmdUnfreezeRole : public CCmdData
//{
//public:
//    CCmdUnfreezeRole()        {}
//    virtual ~CCmdUnfreezeRole()       {}
//
//    BOOL    AddNameList(const char *pBuffer, UINT32 dwLength);
//    UINT32  GetNameBufferLength()       { return m_dwLength; }
//    const char *GetNameBuffer()     { return m_szBuffer; }
//
//private:
//    UINT32      m_dwLength;
//    char        m_szBuffer[MAX_SEARCH_ROLE_NUM * ROLE_NAME_LEN];
//
//};

class CCmdKickRole : public CCmdData
{
public:
    CCmdKickRole()        {}
    virtual ~CCmdKickRole()       {}

    BOOL    AddNameList(const char *pBuffer, UINT32 dwLength);
    UINT32  GetNameBufferLength()       { return m_dwLength; }
    const char *GetNameBuffer()     { return m_szBuffer; }

private:
    UINT32      m_dwLength;
    char        m_szBuffer[MAX_SEARCH_ROLE_NUM * ROLE_NAME_LEN];

};




















class CCmdLogSearchItem : public CCmdData
{
public:
    CCmdLogSearchItem()             {}
    virtual ~CCmdLogSearchItem()    {}

    UINT32      GetRoleID()         { return m_dwRoleID; }
    void        SetRoleID(UINT32 dwRoleID)          { m_dwRoleID = dwRoleID; }

    INT32       GetRoleType()       { return m_nLogRoleType; }
    void        SetRoleType(INT32 nType)            { m_nLogRoleType = nType; }

    INT32       GetItemType()       { return m_nLogItemType; }
    void        SetItemType(INT32 nType)            { m_nLogItemType = nType; }

    UINT64      GetItemGuidID()     { return m_llItemGuidID; }
    void        SetItemGuidID(UINT64 llGuidID)      { m_llItemGuidID = llGuidID; }

    const char* GetRoleName()       { return m_szRoleName; }
    BOOL        SetRoleName(const char *pcszName);

private:
    UINT32      m_dwRoleID;
    INT32       m_nLogRoleType;
    INT32       m_nLogItemType;
    char        m_szRoleName[ROLE_NAME_LEN];
    UINT64      m_llItemGuidID;
};


#endif //_H_CMD_DATA_H_






