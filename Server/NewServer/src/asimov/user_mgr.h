#ifndef _USER_MGR_H_
#define _USER_MGR_H_

#include <map>
#include <vector>

#include "string_def.h"
#include "server_def.h"
#include "object_pool.h"
#include "user.h"
#include "asimov_message_handler.h"
#include "packet_allocator.h"

#define DEFAULT_GROUP_ID (2)

class CLuaScript;

class CUserMgr
{
public:
    CUserMgr();
    virtual ~CUserMgr();

    BOOL Init(void);
    BOOL UnInit(void);
    BOOL MainLoop( CLuaScript* poScript );

    static CUserMgr& GetInstance(void);

    CUser* NewUser(const char* pcszUserName, const char* pcszUserType, const char* pcszPassword, UINT8 byGroupID);
    CUser* FindUser(INT32 nUserID);
    CUser* FindUserByName(const char* szUserName);
    CUser* FindUserByCoroutineName(const char* pcszCoroutineName);
    BOOL DelUser(CUser* poUser);
	CUser* RandAnotherUser(CUser* poSelfUser);

    BOOL AttachUserToCoroutine(CUser* poUser, const char* pcszCoroutineName);
    void DetachUserFromCoroutine(const char* pcszCoroutineName);

    template <class TFunc>
    inline BOOL TraverseUser(TFunc& rFunc);

    void AddChatValue(){m_qwChatSize++;}

    INT32 GetDefaultGroupID(){return DEFAULT_GROUP_ID;};
	INT32 GetScoreRate(UINT32 dwScore, BOOL bLow);

private:
    static CUserMgr                     ms_Instance;

    typedef std::map<INT32, CUser*>         MAP_ID_2_USER;
    typedef std::map<std::string, CUser*>   MAP_STR_2_USER;
    typedef std::multimap<std::string, CUser*> MAP_CNAME_2_USER;

	typedef std::vector<CUser*>			USER_SET;
private:
    INT32                               m_nUserIndex;
    CObjectPool<CUser>                  m_oUserPool;

    MAP_ID_2_USER                       m_mapUser;
    MAP_STR_2_USER                      m_mapName2User;
    MAP_CNAME_2_USER                    m_mapCName2User;
    UINT64                              m_qwChatSize;
    UINT32                              m_dwStartChatTick;

	USER_SET							m_aGroupUsers[MAX_SERVER_GROUP_COUNT];// for rand another user
};

template <class TFunc>
inline BOOL CUserMgr::TraverseUser(TFunc& rFunc)
{
    INT32 nRetCode = 0;

    for (MAP_ID_2_USER::iterator it = m_mapUser.begin();
        it != m_mapUser.end(); ++it)
    {
        nRetCode = rFunc(it->second);
        PROCESS_ERROR(nRetCode);
    }
    
    return TRUE;
Exit0:
    return FALSE;
}

#endif  // _USER_MGR_H_