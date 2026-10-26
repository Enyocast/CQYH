#ifndef _FRIEND_H_
#define _FRIEND_H_

#include "friend_def.h"

class CRole;

class CFriend
{
public:
    CFriend();
    void Clear();
    BOOL Load_v_1(const char* pcData, UINT32 dwSize);
    BOOL Save(const char* pcData, UINT32& rdwSize);
    void SetSignature(const char* szSignature);
    const char* GetSignature();
    void ChangeGroupName(UINT8 byGroupID, const char* szGroupName);
    void AddFriend(UINT8 byGroupID, UINT32 dwFriendID);
    void DelFriend(UINT8 byGroupID, UINT32 dwFriendID);
	INT32 GetFriendCount();
    INT32 GetPersonalEnemyCount();

    BOOL AddBeKilledToList(CRole *poRole, UINT32 dwRoleID);

	UINT32 Begin();
	UINT32 Next();

private:
    char m_szSignature[SIGNATURE_LEN];
    char m_szGroups[MAX_FRIEND_GROUP_COUNT][FRIEND_GROUP_NAME_LEN];

    typedef std::set<UINT32> FriendList;
    FriendList m_friends;

    FriendList  m_personalEnemy;
	FriendList::iterator m_Iterator;

public:
    const char* GetGroupName(UINT32 groupid) const;
};

#endif // _FRIEND_H_
